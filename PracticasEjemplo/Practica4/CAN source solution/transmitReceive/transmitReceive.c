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

	unsigned int i;

	// Declare and initialize message-related data
	// Configure SID and DLC of first message
	unsigned int frameCount = 0;
	unsigned int txMsgSID = frameCount;
	unsigned char txMsgData[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
	unsigned char txMsgDLC = (frameCount % 8) + 1;
	
	initLEDs();
	LCDInit();

	CANinit(LOOPBACK_MODE, TRUE, FALSE, 0, 0);
	
	LCDClear();
	onLED(5);

	//LCDPrint("hola");
	//while(1);

	// Print and Send first message
	offLED((txMsgSID + 1) % 2);
	onLED(txMsgSID % 2);
	printMessage(txMsgSID, txMsgData, txMsgDLC);
	CANsendMessage(txMsgSID, txMsgData, txMsgDLC);

	while(1)
	{
		if (CANtransmissionCompleted())
		{
			for(i=0; i<200; i++) Delay5ms();

			// Configure SID and DLC of next message
			frameCount = (frameCount + 1) % 2048;	// SID MAX = 2047 (SID of 11 bits)
			txMsgSID = frameCount;
			txMsgDLC = (frameCount % 8) + 1;

			// Print and Send message
			offLED((txMsgSID + 1) % 2);
			onLED(txMsgSID % 2);
 			printMessage(txMsgSID, txMsgData, txMsgDLC);
			CANsendMessage(txMsgSID, txMsgData, txMsgDLC);
		
			for(i=0; i<200; i++) Delay5ms();
		}

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
