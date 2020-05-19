#include <p30f4011.h>
#include <stdio.h>

#include "libLCD.h"
#include "libLEDs.h"
#include "libCAD.h"

volatile unsigned int value = 0;

////////////////////////////////////////////////
// ADC ISR
////////////////////////////////////////////////

void _ISR _ADCInterrupt(void){

	// Get value
	value = CADGetValue();

	toggleLED(0);

	// Clear interrupt
	CADClearInt();
}

int main()
{
	char buffer[8];

	initLEDs();
	LCDInit();

	// Initialize and start CAD
	CADInit(CAD_INTERACTION_BY_INTERRUPT, 5);
	CADStart(CAD_INTERACTION_BY_INTERRUPT);

	while(1)
	{
		// Update text at LCD
		sprintf(buffer, "%u   ", value);
		LCDMoveHome();
		LCDPrint(buffer);
	}
	return 0;
}

