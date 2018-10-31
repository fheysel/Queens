#--------------------------------------------------------------------------
# ELEC 371 template file for basic use of timer interrupt
# (the original timer interface from the DE0 computer system is used)
#--------------------------------------------------------------------------

# directives to define symbolic labels for addresses/constants 

	.equ	INITIAL_STACK_TOP, 0x007FFFFC	# start of stack in RAM 

	.equ	LEDs, 0x10000010		# LED output port address 

	.equ	TIMER_STATUS, 0x10002000	# timer status register 
	.equ	TIMER_CONTROL, 0x10002004	# timer control register 
	.equ	TIMER_START_LO, 0x10002008	# low bits of start value 
	.equ	TIMER_START_HI, 0x1000200C	# high bits of start value 
	.equ	TIMER_SNAP_LO, 0x10002010	# low bits of count value 
	.equ	TIMER_SNAP_HI, 0x10002014	# high bits of count value 

	.equ TIMER_TO_BIT, 0x1			# pattern to represent the
						# bit in timer status register
						# that is set on timeout
						# (when count reaches zero)

	.equ	IENABLE_TIMER_IE, 0x1		# pattern to represent the
						# bit in procr ienable reg. 
						# for recognizing interrupts 
						# from timer hardware 

	.equ	NIOS2_IE, 0x1			# pattern to represent the
						# bit in procr status reg. 
						# for global recognition 
						# of all interrupts 
                        
    .equ	BUTTONS_MASK_REGISTER, 0x10000058
	.equ	BUTTONS_EDGE_REGISTER, 0x1000005C
    .equ	BUTTONS_IE, 0x02			# bit in processor ienable reg. to
										# recognize pushbutton interrupts
										
	.equ	JTAG_UART_BASE,	0x10001000 #address of the first JTAG UART reg
	.equ 	DATA_OFFSET,	0 #offset of JTAG UART data register
	.equ	STATUS_OFFSET,	4 #offset of JTAG UART register
	.equ	WSPACE_MASK,	0xFFFF #used in AND operation to check status
#--------------------------------------------------------------------------

	.text		# start a code segment 

	.global	_start	# export _start symbol for linker 

	.org	0x0000	# this is the _reset_ address 
_start:
	br	main	# branch to actual start of main() routine 

	.org	0x0020	# this is the _exception/interrupt_ address
 
	br	isr	# branch to start of interrupt service routine 
			# (rather than placing all of the service code here) 

#--------------------------------------------------------------------------

main:
	# initialize stack pointer (make it a habit to always do this)
	movia sp, INITIAL_STACK_TOP

	# perform initialization
	call Init

	# main loop
mloop:
	call GetChar
	call PrintChar
	br	mloop

#--------------------------------------------------------------------------
GetChar:
	subi sp, sp, 8
	stw r3, 0(sp)
	stw r4, 4(sp)
	
	movia r3, JTAG_UART_BASE 
gc_loop:
	ldwio r2, DATA_OFFSET(r3) #get data
	andi r4, r2, 0x8000 #isolate the valid bit
	beq r4, r0, gc_loop #while the 15th bit (VALID bit) is low - ie while there is nothing to read
	
	andi r2, r2, 0xFF #broken out of loop therefore data is available and in r2, isolate that data by masking top 8 bits
	
	#return r2 by value
    ldw r4, 4(sp)
	ldw r3, 0(sp)
	addi sp, sp, 8
#--------------------------------------------------------------------------	
PrintChar:
	subi sp, sp, 8 
	stw r3, 0(sp)
	stw r4, 4(sp)
	
	movia r3, JTAG_UART_BASE

pc_loop:
	ldwio r4, STATUS_OFFSET(r3) #read bits from status reg
	andhi r4, r4, WSPACE_MASK #mask off lower bits to isolate upper bits
	beq r4, r0, pc_loop #if upper bits are zero loop
	stwio r2, DATA_OFFSET(r3) #else, write character to data register
	
	ldw r4, 4(sp)
	ldw r3, 0(sp)
	addi sp, sp, 8
	ret
#--------------------------------------------------------------------------
Init:
				# body of Init() subroutine
   	#SAVE REGS TO STACK
    subi sp, sp, 8
   # stw ra, 0(sp)
    stw r2, 0(sp)
    stw r3, 4(sp)
    
    movia r2, LEDs
    stwio r0, 0(r2) #set LEDs off
    
    movia r2, TIMER_STATUS
    stwio r0, 0(r2) #clear status reg
   	
    movia r3, 0x017D7840 #with a 50MHz clock this is equivalent to the number of cycles in 0.5s
    movia r2, TIMER_START_LO #set lower 16 bits
  	stwio r3, 0(r2)
    srli  r3, r3, 16 #shift so we only have the top 16 bits
    stwio r3, 4(r2) #set upper 16 start bits
    
    #start timer in contiuous mode with interrupts
    movia r2, TIMER_CONTROL 
    movi r3, 0x7
    stwio r3, 0(r2)
    
    #allow for interrupts from timer
    movia r2, IENABLE_TIMER_IE  
    wrctl ienable, r2 #set IE bit for timer to 1
    
    
    ###########################
    ###BUTTON INITIALIZATION###
    ###########################
    
    movia r2, BUTTONS_MASK_REGISTER #get address of button mask into register
	movi r3, 0x06 #bits to turn high in BUTTONS_MASK_REGISTER
	stwio r3, 0(r2) #set bits 1 and 2 high, enabling button interrups
	
	movia r2, BUTTONS_EDGE_REGISTER
	stwio r3, 0(r2) #stw anying in edge register sets value to low
	
	movi	r2, BUTTONS_IE			# bit to enable button interrupts 
    rdctl	r3, ienable				
	or		r2, r2, r3
    wrctl	ienable, r2				# allow interrupts from buttons while not afecting timer interrupts

    #allow global interrupts
    movia r2, NIOS2_IE
    wrctl status, r2
    
    #restore registers
   # ldw ra, 0(sp)
    ldw r3, 4(sp)
    ldw r2, 0(sp)
    addi sp, sp, 8
    
    ret

#-----------------------------------------------------------------------------
# The code for the interrupt service routine is below. Note that the branch
# instruction at 0x0020 is executed first upon recognition of interrupts,
# and that branch brings the flow of execution to the code below.
# This exercise involves only hardware-generated interrupts. Therefore, the
# return-address adjustment on the ea register is performed unconditionally.
#-----------------------------------------------------------------------------

isr:
   	addi	ea, ea, -4	# this is _required_ for hardware interrupts
    # body of interrupt service routine
	# (save/restore registers that are modified)
	subi	sp, sp, 12
	stw		r2, 0(sp)
	stw		r3, 4(sp)
    stw		ra, 8(sp)
	
    movia	r3, BUTTONS_EDGE_REGISTER
    ldwio	r2, 0(r3)
    bne		r2, r0, buttonISR #if button is requesting interrrupt branch to its isr
	
	#else handle timer interrupts
timerISR:
	movia 	r2, TIMER_STATUS
    ldwio	r0, 0(r2) #clear IRQ
    
	movia	r3, LEDs
    ldwio	r2, 0(r3)#load LED bits into r2
	xori	r2, r2, 1 #toggle the 0th bit of LEDs

	stwio	r2, 0(r3) #set the LEDs
	br		endISR
	
buttonISR:
	movia r2, BUTTONS_EDGE_REGISTER #moving address of edge register into r3
	ldwio r3, 0(r2) #getting value of edge register if non-zero interrupt pending
	
	#if
	beq r3, r0, endISR #if edge register is equal to zero no interrupt necesarry
	#then
	stwio r3, 0(r2) #storing anything into edge register resets value to zero
	movia r2, LEDs #address of led data into r2
	ldwio r3, 0(r2) #get led data
	xori r3, r3, 2 #toggle led 0
	stwio r3, 0(r2) #setting led
    
endISR:
	ldw		ra, 8(sp)
	ldw		r3, 4(sp)
	ldw		r2, 0(sp)
	addi	sp, sp, 12

	eret			# interrupt service routines end _differently_
				# than normal subroutines; the eret goes back
				# to wherever execution was at the time the
				# interrupt request triggered invocation of
				# the service routine

	.end