
#include <p30F4011.h>
#include <stdio.h>

#include "libLEDs.h"
#include "keyblib.h"
#include "TIMERlib.h"
#include "delay.h"


////////////////////////////////////////////////
// Global variables
////////////////////////////////////////////////

unsigned char LEDS_ON = 0;


////////////////////////////////////////////////
// Timer 1 ISR
////////////////////////////////////////////////

void _ISR _T1Interrupt(void){
    
	unsigned char iLed;

	if (LEDS_ON){
		LEDS_ON = 0;
		for(iLed = 0; iLed < NUMLEDS; iLed++)
			offLED(iLed);
	}
	else{
		LEDS_ON = 1;
		for(iLed = 0; iLed < NUMLEDS; iLed++)
			onLED(iLed);
	}
    
    IFS0bits.T1IF = 0;
}

////////////////////////////////////////////////
// Programa principal
////////////////////////////////////////////////

int main(void){

	unsigned char c;
	unsigned char i;

	// Inicializar LEDs
	initLEDs();

	// Inicializar teclado
	KeybInit();

	// Inicializamos timer
	Timer1Init(TIMER_PERIOD_FOR_500ms,TIMER_PSCALER_FOR_500ms); // Timer expires every 500 ms
	Timer1Start();

    while(1){
		
		c = getKey();

		switch (c){
			case 0:	// (Re)Initialize Timer to 500 ms
                    Timer1ReInitialize(TIMER_PERIOD_FOR_500ms,TIMER_PSCALER_FOR_500ms);
					break;

			case 1:	// Start Timer
					Timer1Start();
					break;

			case 2:	// Stop Timer
					Timer1Stop();
					break;

			case 3:	// (Re)Initialize Timer to 62,5 ms
                    Timer1ReInitialize(TIMER_PERIOD_FOR_62_5ms,TIMER_PSCALER_FOR_62_5ms);
					break;

			case 4:	// (Re)Initialize Timer to 125 ms
                    Timer1ReInitialize(TIMER_PERIOD_FOR_125ms,TIMER_PSCALER_FOR_125ms);
					break;


			case 5:	// (Re)Initialize Timer to 250 ms
                    Timer1ReInitialize(TIMER_PERIOD_FOR_250ms,TIMER_PSCALER_FOR_250ms);
					break;


			case 6:	// (Re)Initialize Timer to 1,25 ms
                    Timer1ReInitialize(TIMER_PERIOD_FOR_1_25ms,TIMER_PSCALER_FOR_1_25ms);
					break;

			case 7:	// (Re)Initialize Timer to 10 ms
                    Timer1ReInitialize(TIMER_PERIOD_FOR_10ms,TIMER_PSCALER_FOR_10ms);
					break;

			case 8:	// (Re)Initialize Timer to 50 ms
                    Timer1ReInitialize(TIMER_PERIOD_FOR_50ms,TIMER_PSCALER_FOR_50ms);
					break;

			default:
					break;
		}

		// 300 ms delay so the keys are not oversampled
		for(i=0; i<60; i++) Delay5ms();
	}

    return 0;
}

