#include "nios2_control.h"
#include "leds.h"
#include "timer.h"

extern int flag;

void interrupt_handler(void)
{
	unsigned int ipending;	

	/* read current value in ipending register */
	ipending = NIOS2_READ_IPENDING();

	/* _if_ ipending bit for timer is set,
	
	   _then_
	       clear timer interrupt,
	       and toggle the least-sig. LED
	       (use the C '^' operator for XOR with constant 1)
	*/
	
	if((ipending & 0x1)){
		*TIMER_STATUS = 0; //clear interrupt
		*LEDS = 0x1 ^ *LEDS;//toggle led 0
		flag = 1;
	}
	
	if((ipending & (1<<13))){ 
		*TO_STATUS = 0; //clear interrupt
		*LEDS = 0x2 ^ *LEDS; //toggle led 1
	}
	
}
