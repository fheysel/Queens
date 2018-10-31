#-----------------------------------------------------------------------------
# template source file for ELEC 371 Lab 1 Part 2
#-----------------------------------------------------------------------------

	.text			# inform assembler that code section begins
				#   (but note that in this course, we also
				#    place "data" in what would normally be
				#    a section with only instructions)
	.global _start		# export _start symbol for linker

#-----------------------------------------------------------------------------
# define symbols for memory-mapped I/O register addresses and use them in code
#-----------------------------------------------------------------------------

	.equ	SWITCHES_DATA_REGISTER, 0x10000040 #starting location of switches

	.equ	HEX_DISPLAYS_DATA_REGISTER, 0x10000020 #starting location of seven-segment display

#-----------------------------------------------------------------------------

	.org 0			# place first instruction below at address 0
_start:				# start of main() routine in this case
				# initialize stack pointer
mainloop:

	br readSwitches #get values from switches returns data in r3
	br writeHexDisplays #sends data from readSwitches to writeHexDisplays in r3		

br mainloop

#-----------------------------------------------------------------------------

ReadSwitches: #reads data from switches and returns information in r3
	
	subi sp, sp, 8 #saving return address and used register on stack not saving r3 as it is the 
	stw ra, 0(sp)  #register we return the data in
	stw r2, 4(sp)


	movia r2, SWITCHES_DATA_REGISTER #set r3 to address of switches
	ldwio r3, r1 #load switches data into r3

	ldw r2, 4(sp) #restore registers, clear stack
	ldw ra, 0(sp)
	addi sp, sp, 8
	
ret

#-----------------------------------------------------------------------------

WriteHexDisplays: #takes input data in r3 and displays data to seven-segment display
		
	subi sp, sp, 8 #saving registers to stack
	stw ra, 0(sp)
	stw r2, 4(sp)

	movia r2, HEX_DISPLAYS_DATA_REGISTER #set r2 to address of seven-segment display
	stw r3, 0(r2) #send data from switches to seven-segment display

	ldw r2, 4(sp) #restore registers and clear stack
	ldw ra, 0(sp)
	addi sp, sp, 8

ret
  
	.end
