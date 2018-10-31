#-----------------------------------------------------------------------------
# template source file for ELEC 371 Lab 1 Part 3
#-----------------------------------------------------------------------------

	.text		# start a code segment 

	.global	_start	# export _start symbol for linker 

#-----------------------------------------------------------------------------
# define symbols for memory-mapped I/O register addresses and use them in code
#-----------------------------------------------------------------------------
	.equ 	LAST_RAM_WORD, 0x007FFFFC #location of stack pointer
	.equ	BUTTONS_IE, 0x02			# bit in processor ienable reg. to
										# recognize pushbutton interrupts
	.equ	NIOS2_IE, 0x1		        # bit in processor status reg. for
										# global recognition all interrupts
	
	.equ	BUTTONS_MASK_REGISTER, 0x10000058
	.equ	BUTTONS_EDGE_REGISTER, 0x1000005C
	.equ	LEDS_DATA_REGISTER, 0x10000010

#-----------------------------------------------------------------------------

	.org	0x0000	# this is the _reset_ address 
_start:
	br	main	# branch to actual start of main() routine 

	.org	0x0020	# this is the _exception/interrupt_ address
 
	br	isr	# branch to start of interrupt service routine 
			# (rather than placing all of the service code here) 

#-----------------------------------------------------------------------------

main:
	
	movia	sp, LAST_RAM_WORD # initialize stack pointer
	
	call Init 
	
mainloop:
				# body of loop in main() routine
	br mainloop

#-----------------------------------------------------------------------------

Init:
	# body of Init() subroutine
				
	subi sp, sp, 12
	stw ra, 0(sp)
	stw r2, 4(sp)
	stw r3, 8(sp)
	
	movia r2, BUTTONS_MASK_REGISTER #get address of button mask into register
	movi r3, 0x06 #bits to turn high in BUTTONS_MASK_REGISTER
	stwio r3, 0(r2) #set bits 1 and 2 high, enabling button interrups
	
	movia r2, BUTTONS_EDGE_REGISTER
	stwio r3, 0(r2) #stw anying in edge register sets value to low
	
	movi	r1, BUTTONS_IE			# bit to enable button interrupts 
	wrctl	ienable, r1				# allow interrupts from buttons

	# modify status register in processor to recognize all interrupts 
	movi	r1, NIOS2_IE			# master interrupt control
	wrctl	status, r1				# processor will now take hardware
									# interrupts.
	
	ldw r3, 8(sp)
	ldw r2, 4(sp)
	ldw ra, 0(sp)
	addi sp, sp, 12
	
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
				# (save/restore registers that are modified
				#  except ea which must be modified as above)
	subi sp, sp, 8
	stw r2, 0(sp)
	stw r3, 4(sp)
	
	movia r2, BUTTONS_EDGE_REGISTER #moving address of edge register into r3
	ldwio r3, 0(r2) #getting value of edge register if non-zero interrupt pending
	
	#if
	beq r3, r0, noInt #if edge register is equal to zero no interrupt necesarry
	#then
	stwio r3, 0(r2) #storing anything into edge register resets value to zero
	movia r2, LEDS_DATA_REGISTER #address of led data into r2
	ldwio r3, 0(r2) #get led data
	xori r3, r3, 1 #toggle led 0
	stwio r3, 0(r2) #setting led
	
	
	#else
	noInt:
		
		ldw r3, 4(sp)
		ldw r2, 0(sp)
		addi sp, sp, 8
	
	
	eret			# interrupt service routines end _differently_
				# than normal subroutines; the eret goes back
				# to wherever execution was at the time the
				# interrupt request triggered invocation of
				# the service routine

	.end
