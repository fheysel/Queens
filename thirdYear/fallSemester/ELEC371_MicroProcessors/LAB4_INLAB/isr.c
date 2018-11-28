#include "nios2_control.h"
#include "timer.h"
#include "hex_display.h"

#define PUSHBUTTON_DATA (volatile unsigned int*) 0x10000050
#define PUSHBUTTON_MASK (volatile unsigned int*) 0x10000058
#define PUSHBUTTON_EDGE (volatile unsigned int*) 0x1000005C

//global variabls
int minutes_tens;
int minutes_ones;
int seconds_tens;
int seconds_ones;

int flag;
int state = 0;
int shift = 0;

unsigned int hex_table[] =
	{
		0x3F, 0x06, 0x5B, 0x4F,
		0x66, 0x6D, 0x7D, 0x07,
		0x7F, 0X6F, 0X77, 0X7C,
		0X39, 0X5E, 0X79, 0X71
	};

void Init(){
	//initialize varaibles
	minutes_tens = minutes_ones = seconds_tens = seconds_ones = 0;
	
	//initialize HEX Displays
	*HEXDISPLAY = (hex_table[minutes_tens] << 24 |
				   hex_table[minutes_ones] << 16 |
				   hex_table[seconds_tens] << 8 |
				   hex_table[seconds_ones]);				   
	
	//set timer start value for an interval of ONE SECOND
	*TIMER_START_LO = 50000000 & 0xFFFF; //50MHz clock 
	*TIMER_START_HI = 50000000 >> 16;
	
	*TO_START_LO = 5000000 & 0xFFFF; //50 MHz clock * 0.1 sec
	*TO_START_HI = 5000000 >> 16;
	
	//clear extraneous timer interrupt
	*TIMER_STATUS = 0;
	*TO_STATUS = 0;
	*PUSHBUTTON_EDGE = 0;//writing anything to edge reg will clear it
	
	//set ITO, CONT, and START bits of timer control register
	*TIMER_CONTROL = 0x7;
	*TO_CONTROL = 0x7;
	*PUSHBUTTON_MASK = 0x2;//enable push button 1
	
	//set timer bit in NIOS II ienable register
	NIOS2_WRITE_IENABLE(0X2001 | 0x2);
	
	//enable global interrupts
	NIOS2_WRITE_STATUS(0X1 | 1<<13);
	return;
}


void interrupt_handler(void)
{
	unsigned int ipending;	


	/* read current value in ipending register */
	ipending = NIOS2_READ_IPENDING();

	/* _if_ ipending bit for timer is set,
	
	   _then_
	       clear timer interrupt,
	       Update the tiem on the Hex displays
	*/
	
	if((ipending & 0x1)){
		*TIMER_STATUS = 0; //clear interrupt
		flag = 1;
		seconds_ones++;
		if(seconds_ones == 10){
			seconds_ones = 0;
			seconds_tens++;
			if(seconds_tens == 6){
				seconds_tens = 0;
				minutes_ones++;
				if(minutes_ones == 10){
					minutes_ones = 0;
					minutes_tens++;
				}
			}
		}
		
		//update HEX Displays
		*HEXDISPLAY = (hex_table[minutes_tens] << 24 |
					   hex_table[minutes_ones] << 16 |
					   hex_table[seconds_tens] << 8 |
					   hex_table[seconds_ones]);
		
	}	
	
	if(ipending & (1<<13)){
		*TO_STATUS = 0;
		state++;
		if(state >= 4){
			state = 0;
			shift++;
			if( shift > 9){
				shift = 0;
			}
		}
	}
	
	if(ipending & 0x2){
		*PUSHBUTTON_EDGE = 0;//CLEAR THE SOURCE!!!!!
		state = 0;
		shift = 0;
	}
}
