#include "adc.h"
#include "chario.h"
//#include "interrupt_handler.h"
#include "timer.h"



#define LEDs (volatile unsigned int*) 0x10000010
#define HEXDISPLAY	((volatile unsigned int *) 0x10000020)

extern int flag;
extern int state;
extern int shift;

int main(){
	Init();
	unsigned int hex_table[] =
	{
		0x3F, 0x06, 0x5B, 0x4F,
		0x66, 0x6D, 0x7D, 0x07,
		0x7F, 0X6F, 0X77, 0X7C,
		0X39, 0X5E, 0X79, 0X71
	};
	
	printString("ELEC 371 Lab 4\n");
	InitADC(2, 2);
	unsigned int value = 0;
	printString(" ");
	int temp;
	while(1){
		value = ADConvert();
		//*LEDs = value;
		
		if(flag){
			flag = 0;
			printString("\b");
			temp = value >> 6;
			if(temp == 0){
				printString(".");
			}else if(temp == 1){
				printString(":");
			}else if(temp == 2){
				printString("!");
			}else if(temp == 3){
				printString("|");
			}else{
				printString("error");
			}
		}
		if(state == 1 || state == 3){
			*LEDs = (1<<shift);
		}
		else{
			*LEDs = 0;
		}
	}
	return 0;
}