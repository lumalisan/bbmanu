/******************************************************************************/
/*                                                                            */
/*  Description:                                                              */
/*                                                                            */
/*  Author:                                                                   */
/*                                                                            */
/******************************************************************************/

#include <p30f4011.h>
#include <uart.h>

#include <stdio.h>

#include "LCDlib.h"

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
#define FXT 7372800 // Oscillator frequency
#define PLL 16
#define FCY (FXT * PLL) / 4 // Real system frequency

//#define TCY 1000000.0 / FCY //33.90842014 // microseconds
#define TCY 33.90842014 // nsecs

// UART configuration
#define BAUD_RATE 115200
#define BRG       (FCY / (16L * BAUD_RATE)) - 1L


/************************************************************************************/
// UART functions available at <uart.h>
/************************************************************************************/
/*

// Initialization
void OpenUART1(unsigned int config1,unsigned int config2, unsigned int ubrg);

// Transmission
putsUART1(unsigned int *buffer);
void WriteUART1(unsigned int data);
char BusyUART1(void);

// Reception
char DataRdyUART1(void);
unsigned int ReadUART1(void);

// Other functions
void CloseUART1(void);
void ConfigIntUART1(unsigned int config);
unsigned int getsUART1(unsigned int length,unsigned int *buffer,
                       unsigned int uart_data_wait);

*/

/******************************************************************************/
/* Additional procedure prototypes                                            */
/******************************************************************************/

void UARTConfig();

/******************************************************************************/
/* Main program                                                               */
/******************************************************************************/

int main(void)
{
	char c;
	char buffer[3];
	unsigned char posLCD = 0;

	UARTConfig();
	LCDInit();
	
    while(1){

        while(!DataRdyUART1()); // Wait for a new char coming from the serial connection
		c = ReadUART1(); // Read char
		
		sprintf(buffer, "%c", c);	// Print character into string
		LCDPrint(buffer);
		posLCD++;

		switch(posLCD){
			case    16 : LCDMoveSecondLine(); break;
			case    32 : LCDMoveHome(); posLCD = 0; break;
			default   : break;
		}

    }
	return 0;
}


/******************************************************************************/
/* Implementation of additional procedure prototypes                          */
/******************************************************************************/


void UARTConfig(){
    U1MODE = 0;                     // Clear UART config - to avoid problems with bootloader

    // Config UART
	OpenUART1(UART_EN &             // Enable UART
              UART_DIS_LOOPBACK &   // Disable loopback mode
              UART_NO_PAR_8BIT &    // 8bits / No parity 
              UART_1STOPBIT,        // 1 Stop bit

              UART_TX_PIN_NORMAL &  // Tx break bit normal
              UART_TX_ENABLE,       // Enable Transmition
              
			  BRG);                 // Baudrate
}

