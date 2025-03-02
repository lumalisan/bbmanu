/******************************************************************************/
/*                                                                            */
/*  Description:                                                              */
/*                                                                            */
/*  Author:                                                                   */
/*                                                                            */
/******************************************************************************/

#include <p30f4011.h>

#include <stdio.h>

#include "libLCD.h"
#include "libLEDs.h"
#include "libCAN.h"

/******************************************************************************/
/* Configuration words                                                        */
/******************************************************************************/
_FOSC(CSW_FSCM_OFF & EC_PLL16);
_FWDT(WDT_OFF);
_FBORPOR(MCLR_EN & PBOR_OFF & PWRT_OFF);
_FGS(CODE_PROT_OFF);

/******************************************************************************/
/* Hardware                                                                   */
/******************************************************************************/

/******************************************************************************/
/* Global Variable and macros declaration                                     */
/******************************************************************************/

#define TRUE	1
#define FALSE	0


/******************************************************************************/
/* Procedures declaration                                                     */
/******************************************************************************/

void printMessage(unsigned int msgSID, unsigned char * msgData, unsigned char msgDLC);


/******************************************************************************/
/* Interrupts                                                                 */
/******************************************************************************/

void _ISR _C1Interrupt(void){

	unsigned int rxMsgSID;
	unsigned char rxMsgData[8];
	unsigned char rxMsgDLC;

	// Clear CAN global interrupt
	CANclearGlobalInt();

	if (CANrxInt())
	{
		// Clear RX interrupt
		CANclearRxInt ();

		// Read SID, DLC and DATA
		rxMsgSID = CANreadRxMessageSID();
		rxMsgDLC = CANreadRxMessageDLC();
		CANreadRxMessageDATA (rxMsgData);

		// Clear RX buffer
		CANclearRxBuffer();

		// Print frame information on LCD
		offLED(2 + ((rxMsgSID + 1) % 2));
		onLED(2 + (rxMsgSID % 2));
		printMessage(rxMsgSID, rxMsgData, rxMsgDLC);
	}

}


/******************************************************************************/
/* Main                                                                       */
/******************************************************************************/

int main(void){

	initLEDs();
	LCDInit();
	CANinit(NORMAL_MODE, TRUE, FALSE, 2, 7);
	
	LCDClear();
	
	//LCDPrint("hola");
	//while(1);

	onLED(4);
	while(1)
	{
		onLED(4);
	}
    return 0;
}



/******************************************************************************/
/* Procedures implementation                                                  */
/******************************************************************************/

void printMessage(unsigned int msgSID, unsigned char * msgData, unsigned char msgDLC)
{
	unsigned char i;
	char buffer[20];

	// Print frame information on LCD
	LCDClear();
	LCDMoveFirstLine();
	sprintf(buffer, "SID=%u DLC=%u", msgSID, msgDLC);
	LCDPrint(buffer);
	
	LCDMoveSecondLine();
	for(i=0; i < msgDLC; i++)
	{
		sprintf(buffer, "%c", msgData[i]);
		LCDPrint(buffer);
	}
	
}
