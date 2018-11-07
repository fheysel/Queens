#include "nios2_control.h"
#include "timer.h"
#include "chario.h"

#define SWITCHES	((volatile unsigned int *) 0x10000040)
#define HEXDISPLAY	((volatile unsigned int *) 0x10000020)

int flag; 

void	Init (void)
{
  /* initialize software variables */
	

  /* set timer start value for interval of HALF SECOND (0.5 sec) */
	*TIMER_START_LO = 25000000 & 0xFFFF; //50MHz clock * 0.5 sec
	*TIMER_START_HI = 25000000 >> 16;
	*TO_START_LO = 12500000 & 0xFFFF; //50 MHz clock * 0.25 sec
	*TO_START_HI = 12500000 >> 16;
		
  /* clear extraneous timer interrupt */
	*TIMER_STATUS = 0;
	*TO_STATUS = 0;
	
  /* set ITO, CONT, and START bits of timer control register */
	*TIMER_CONTROL = 7;
	*TO_CONTROL = 7;
	
  /* set device-specific bit for timer in Nios II ienable register */
	NIOS2_WRITE_IENABLE(0x2001); //enable timers TIMER and TO interrupts in ienable

  /* set IE bit in Nios II status register */
	NIOS2_WRITE_STATUS((0x1 | 1<<13)); //enable global interrupts
}


int	main (void)
{

  /* perform initialization */
  Init ();
  unsigned int hex_table[] =
	{
		0x3F, 0x06, 0x5B, 0x4F,
		0x66, 0x6D, 0x7D, 0x07,
		0x7F, 0X6F, 0X77, 0X7C,
		0X39, 0X5E, 0X79, 0X71
	};	
	
  printString("ELEC371 Lab 3\n");
  /* main program is an empty infinite loop */
  while (1){
	if(flag != 0){
		flag = 0;
		printChar('*');
	}
	int switchData = *SWITCHES & 0xF;
	*HEXDISPLAY = hex_table[switchData];
	
  }  
    


  return 0; /* never reached, but needed to avoid compiler warning */
}

int readSwitches(){
	return *SWITCHES;	
}





