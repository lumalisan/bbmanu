
#include <p30f4011.h>
#include "leds.h"
#include "delay.h"
#include "keyb.h"
#include "libBuzz.h"

_FOSC(CSW_FSCM_OFF & EC_PLL16);
_FWDT(WDT_OFF);
_FBORPOR(MCLR_EN & PBOR_OFF & PWRT_OFF);
_FGS(CODE_PROT_OFF);

int main (void)
{

	char c;
	char lastc = 0;
	unsigned int i = 0;

	initLEDs();
	initKeyb();
	initBuzzer();

	while (1)
	{
	/*	c = getKey(1);
		c = c % 6;

		if (c != lastc)
		{
			offLED(lastc);
		}

		onLED(c);

		lastc = c;
	}
	*/
		// 0: test
		// 1: test2
		// 2: scale
		// 3: S A N S

		switch(getKey(0)) {
			case 0: playBuzzer(420,1000); break;
			case 1: playNote(1,1,300); break;
			case 2: playNote(1,0,250);
					playNote(3,0,250);
					playNote(5,0,250);
					playNote(6,0,250);
					playNote(8,0,250);
					playNote(10,0,250);
					playNote(12,0,250);
					playNote(1,1,250);
					break;
			case 3: playNote(3,0,100); // D
					playNote(-1,0,10); // Pause
					playNote(3,0,100); // D
					playNote(-1,0,10); // Pause
					playNote(3,1,100); // D3
					playNote(-1,0,80); // Pause
					playNote(10,0,250); // A
					playNote(-1,0,80); // Pause
					playNote(9,0,200); // G#
					playNote(-1,0,50); // Pause
					playNote(8,0,200); // G
					playNote(-1,0,50); // Pause
					playNote(6,0,300); // F
					playNote(-1,0,10); // Pause
					playNote(3,0,100); // D
					playNote(-1,0,10); // Pause
					playNote(6,0,100); // F
					playNote(-1,0,10); // Pause
					playNote(8,0,125); // G
					break;
			default: break;
		}
		
		// 300 ms delay so the keys are not oversampled
		for(i=0; i<60; i++) Delay5ms();
		
	}

	return 0;
}
