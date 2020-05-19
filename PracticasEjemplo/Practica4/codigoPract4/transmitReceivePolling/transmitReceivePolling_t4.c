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


/******************************************************************************/
/* Main                                                                       */
/******************************************************************************/

int main(void){

	unsigned int i;

	// Declare and initialize TX message-related data
	// Configure SID and DLC of first TX message
	unsigned int frameCount = 0;        // Contador de tramas enviadas
	unsigned int txMsgSID = frameCount; // ID trama enviada
    
    // El payload de una trama CAN es max. 8 bytes
	unsigned char txMsgData[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    
    // N. de bytes a transmitir
	unsigned char txMsgDLC = (frameCount % 8) + 1;
	
	// Declare RX message-related data (recepción)
	unsigned int rxMsgSID;      // ID trama recibida
	unsigned char rxMsgData[8]; // Bytes recibidos
	unsigned char rxMsgDLC;     // N. bytes recibido

	// Initializations
	initLEDs();
	LCDInit();

    // Inicializamos el bus CAN
    // En modo Loopback, interrupción de RX y TX desactivadas, filtro y máscara a cero
	CANinit(LOOPBACK_MODE, FALSE, FALSE, 0x0000, 0x0000);
	
	LCDClear();
	onLED(5);


	// Print and Send first message
	offLED((txMsgSID + 1) % 2);
	onLED(txMsgSID % 2);
    // Envía trama    ID       Datos    Tam.datos
	CANsendMessage(txMsgSID, txMsgData, txMsgDLC);

	while(1)
	{
		// Poll reception
		if (CANreceptionCompleted())    // Si se ha recibido algo nuevo
		{

			// Read SID, DLC and DATA
			rxMsgSID = CANreadRxMessageSID();
			rxMsgDLC = CANreadRxMessageDLC();
			CANreadRxMessageDATA (rxMsgData);
	
			// Clear rx buffer
			CANclearRxBuffer();
			
			// Print frame information on LCD
			offLED(2 + ((rxMsgSID + 1) % 2));
			onLED(2 + (rxMsgSID % 2));
			printMessage(rxMsgSID, rxMsgData, rxMsgDLC);
		}

		// Poll transmission
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
 			//printMessage(txMsgSID, txMsgData, txMsgDLC);
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
