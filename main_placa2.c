// SI TODO ESTÁ COMENTADO ES PORQUE SI NO NO ME DEJA COMPILAR PORQUE
// HAY DOS MAINS


/******************************************************************************/
/*                                                                            */
/*  Description: Práctica Final Sistemas Empotrados                           */
/*               Curso 2019-2020                                              */
/*               Ingeniería Informática UIB                                   */
/*                                                                            */
/*  Authors:     Izar Castorina                                               */
/*               Lisandro Rocha                                               */
/*               Joan Albert Vallori Aguiló                                   */
/*                                                                            */
/******************************************************************************/

/**
 TODO:
 * - Control de la luminosidad
 * - Envío por CAN
 * 
 */

#include <p30f4011.h>
#include <stdio.h>
#include <salvo.h>

#include <string.h>
#include <stdlib.h>

#include "libLEDs.h"
#include "libCAD.h"
#include "libLCD.h"

#define TASK_CTRL_P         OSTCBP(1)   //Task 1
#define TASK_TX_AP          OSTCBP(2)   //Task 2
#define TASK_RX_AP          OSTCBP(3)   //Task 3
#define TASK_LCD_AP         OSTCBP(4)   //Task 4

//Task priorities
#define PRIO_CTRL           10
#define PRIO_TX             10
#define PRIO_RX             10
#define PRIO_LCD            10

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
/* Salvo elements declarations                                                */
/******************************************************************************/


/******************************************************************************/
/* Global Variable and macros declaration                                     */
/******************************************************************************/

unsigned int lumenes = 0;
unsigned int hab1 = 0, hab2 = 0, hab3 = 0; // Cant. personas en habitaciones
unsigned int luz1 = 0, luz2 = 0, luz3 = 0; // Intensidad luz en habitaciones (manual)
unsigned int lums1 = 0, lums2 = 0, lums3 = 0;   // Intensidad luz artificial en lumenes

#define LUMS_STEP   341     // Cada incremento de lums es +- 341

/******************************************************************************/
/* Procedures declaration                                                     */
/******************************************************************************/


/******************************************************************************/
/* TASKS declaration and implementation                                       */
/******************************************************************************/

/* Task states

   DESTROYED / uninitialized
   STOPPED
   WAITING
   DELAYED
   ELIGIBLE /READY
   RUNNING

 */

/**
 * Decide la intensidad de la luz en cada hab.
 */
void P_ctrl(void){
    
}

/**
 * Muestra en el LCD:
 * - Los lúmenes del exterior
 * - Los lúmenes por habitación
 */
void AP_act_LCD(void){
    // Calcula la intensidad actual de lúmenes y la enseña
    // lums1..3
}


/**
 * Envia: 
 * - Los lúmenes de luz exterior
 * - El nivel de luz deseado en cada hab. (manual)
 */
void AP_tx_datos(void){
    // Llamado después de P_ctrl
    // Envía los valores actualizados de lumenes y luces
}

/******************************************************************************/
/* Interrupts                                                                 */
/******************************************************************************/


/******************************************************************************/
/* CAN ISR - Recepción datos                                                  */
/******************************************************************************/
void _ISR _C1Interrupt(void) {
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
        
        if (rxMsgSID == 0x0001) {
            
            lumenes = (unsigned int) rxMsgData[0];
            hab1 = (unsigned int) rxMsgData[1];
            hab2 = (unsigned int) rxMsgData[2];
            hab3 = (unsigned int) rxMsgData[3];
            luz1 = (unsigned int) rxMsgData[4];
            luz2 = (unsigned int) rxMsgData[5];
            luz3 = (unsigned int) rxMsgData[6];
            
        }
	}
    
    
}

/******************************************************************************/
/* Main                                                                       */
/******************************************************************************/

int main(void) {
    return 0;
}

/******************************************************************************/
/* Procedures implementation                                                  */
/******************************************************************************/
