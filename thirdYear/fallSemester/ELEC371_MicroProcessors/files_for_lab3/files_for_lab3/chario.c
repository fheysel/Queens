#include "chario.h"

void printChar(int ch){
	unsigned int wstatus;
	
	do{//wait for the UART to have 
		wstatus = *JTAG_UART_STATUS;
		wstatus = wstatus & 0xFFFF0000;
	}while(wstatus == 0);
	
	*JTAG_UART_DATA = ch;
}

void printString(char* s){
	int i = 0;
	while(s[i] != 0){
		printChar(s[i]);
		i++;
	}
}




