#include <p30f4011.h>

#include "LCDlib.h"
#include "Keyblib.h"
#include "delay.h"

#include <stdio.h>

#define PRECIO 123.4567890


int main(void)
{
	char i;
	char buffer[20];

	LCDInit();
	KeybInit();

	while(1){
		switch(getKey()){
			case  0 : LCDPrint("0"); break;
			case  1 : LCDPrint("1"); break;
			case  2 : LCDPrint("2"); break;
			case  3 : LCDMoveHome(); break;
			case  4 : LCDMoveLeft(); break;
			case  5 : LCDMoveRight(); break;
			case  6 : LCDScrollLeft(); break;
			case  7 : LCDScrollRight(); break;
			case  8 :
					  sprintf(buffer, "%.2f Eu", PRECIO);
					  LCDPrint(buffer);
					  break;

			case 9 	: LCDChangeCursorMode(); break;
			case 10 : break;
			case 11 : LCDClear(); break;
			default : break;
		}

		// 300 ms delay so the keys are not oversampled
		for(i=0; i<60; i++) Delay5ms();

	}

	return 0;
}
