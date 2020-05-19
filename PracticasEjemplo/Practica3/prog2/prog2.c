#include <p30f4011.h>
#include <stdio.h>

#include "delay.h"
#include "LCDlib.h"
#include "CADlib.h"

int main(){
	unsigned int value;
	char buffer[40];
	unsigned int i;

	LCDInit();

	// Initialize and start CAD
	CADInit(CAD_INTERACTION_BY_POLLING);
	CADStart(CAD_INTERACTION_BY_POLLING);

	// Request value from CAD
	CADRequestValue();

	while(1){
		
		if (CADReadyValue()){

			// Get value from CAD and request new value
			value = CADGetValue();
			CADRequestValue();
	
			// Update text at LCD
			sprintf(buffer, "%i", value);
			LCDClear();
			LCDPrint(buffer);
		}

		for(i=0; i<10; i++) Delay15ms();
	}
	return 0;
}