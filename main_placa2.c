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
#define TASK_LCD_AP         OSTCBP(3)   //Task 4

//Task priorities
#define PRIO_CTRL           10
#define PRIO_TX             10
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

volatile unsigned int lumenes = 0;
volatile unsigned int hab1 = 0, hab2 = 0, hab3 = 0; // Cant. personas en habitaciones
volatile unsigned int luz1 = 0, luz2 = 0, luz3 = 0; // Intensidad luz en habitaciones (calculada)
volatile int luz1_man = 0, luz2_man = 0, luz3_man = 0; // Intensidad luz (recibida)
volatile unsigned int lums1 = 0, lums2 = 0, lums3 = 0;   // Intensidad luz artificial en lumenes

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
    
    while(1) {
        
        // Determinación automática de la intensidad de las luces
        
        if (lumenes <= 341) {    // Según la luz exterior
            // Luz baja (noche), si hay gente enciende
            switch (hab1) { // Según el n. de personas
                case 0: luz1 = 0; break;
                case 1: luz1 = 1; break;
                default: luz1 = 2; break;
            }
            switch (hab2) {
                case 0: luz2 = 0; break;
                case 1: luz2 = 1; break;
                default: luz2 = 2; break;
            }
            switch (hab3) {
                case 0: luz2 = 0; break;
                case 1: luz2 = 1; break;
                default: luz2 = 2; break;
            }
        } else if (lumenes > 341 && lumenes <= 682) {
            // Luz media (tarde), si hay más de una persona enciende 1 luz
            switch (hab1) {
                case 0: luz1 = 0; break;
                case 1: luz1 = 0; break;
                default: luz1 = 1; break;
            }
            switch (hab2) {
                case 0: luz2 = 0; break;
                case 1: luz2 = 0; break;
                default: luz2 = 1; break;
            }
            switch (hab3) {
                case 0: luz3 = 0; break;
                case 1: luz3 = 0; break;
                default: luz3 = 1; break;
            }
        } else if (lumenes > 682) {
            // Luz alta (día), no enciende nada
            luz1 = 0;
            luz2 = 0;
            luz3 = 0;
        }
        
        // Ahora se calcula teniendo en cuenta los comandos manuales
        // impartidos a través de los botones en la placa 1
        
        luz1 = luz1 + luz1_man;
        luz2 = luz2 + luz2_man;
        luz3 = luz3 + luz3_man;
        
        OS_Delay(3);
    }
    
}

/**
 * Muestra en el LCD:
 * - Los lúmenes del exterior
 * - Los lúmenes por habitación
 */
void AP_act_LCD(void){
    // Calcula la intensidad actual de lúmenes y la enseña
    // lums1..3
    
    while (1) {

        // Espera a que la tarea de CAN señale que hay que actualizar
        //OS_WaitEFlag(EFLAG_BOTONES, DESPIERTA_LCD, OSEXACT_BITS, OSNO_TIMEOUT);
        //OSClrEFlag(EFLAG_BOTONES, DESPIERTA_LCD); // Limpia el flag y ejecuta la rutina

        // Max. longitud línea: 16 chars.
        char linea1, linea2 [16];
        
        lums1 = luz1 * LUMS_STEP;
        lums2 = luz2 * LUMS_STEP;
        lums3 = luz3 * LUMS_STEP;

        sprintf(linea1, "EX:%d H1:%d", lumenes, lums1);
        sprintf(linea2, "H2:%d H3:%d", lums2, lums3);

        LCDMoveFirstLine();
        LCDPrint(linea1);
        LCDMoveSecondLine();
        LCDPrint(linea2);

        IFS0bits.ADIF = 0; // Reset interrupt

        OS_Yield();
    }
    
}


/**
 * Envia: 
 * - Los lúmenes de luz exterior
 * - El nivel de luz deseado en cada hab. (manual)
 */
void AP_tx_datos(void){
    // Llamado después de P_ctrl
    // Envía los valores actualizados de lumenes y luces
    
    // Cada unsigned char tiene tamaño de 1 byte
    // Cada unsigned int tiene tamaño de 2 bytes (hasta 65.535, luego 4)

    /*
     SISTEMA DE IDENTIFICADORES
     * 
     * SID = 0x0001 (1)   --> Mensaje recibido desde la placa 1
     * SID = 0x0002 (2)   --> Enviar luz1..3
     *
     */

    // ***CUIDADO***
    // Puede que haga falta un delay después de clearTxInt, pero el profe no
    // quiere esperas activas. Si no funciona la transmisión, podría ser esta
    // la razón

    while (1) {

        // Espera a que la tarea de botones señale que hay nuevos datos para enviar
        //OS_WaitEFlag(EFLAG_BOTONES, DESPIERTA_CAN, OSEXACT_BITS, OSNO_TIMEOUT);
        //OSClrEFlag(EFLAG_BOTONES, DESPIERTA_CAN); // Limpia el flag y ejecuta la rutina
        //OSSetEFlag(EFLAG_BOTONES, DESPIERTA_LCD); // Dice al LCD de actualizarse

        unsigned char data_buffer[3];
        unsigned int ID = 0x0002;
        unsigned char tamDatos = sizeof (data_buffer);

        // Envío informaciones
        if (CANtxInt) { // Si se puede enviar
            CANclearTxInt(); // Clear del interrupt de transmisión CAN

            data_buffer[0] = (unsigned char) luz1;
            data_buffer[1] = (unsigned char) luz2;
            data_buffer[2] = (unsigned char) luz3;

            CANsendMessage(ID, data_buffer, tamDatos);
        }

        OS_Yield();
    }
    
}

/******************************************************************************/
/* Interrupts                                                                 */
/******************************************************************************/


/******************************************************************************/
/* CAN ISR - Recepción datos                                                  */
/* Recibe info de num. personas y luz deseada (manual) en cada habitación     */
/* También recibe el número de lúmenes exteriores                             */
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
            
            hab1 = (unsigned int) rxMsgData[2];
            hab2 = (unsigned int) rxMsgData[3];
            hab3 = (unsigned int) rxMsgData[4];
            luz1_man = (int) rxMsgData[5];
            luz2_man = (int) rxMsgData[6];
            luz3_man = (int) rxMsgData[7];
            
            lumenes = (unsigned int) rxMsgData[1] << 8; // lum_l
            lumenes += (unsigned int) rxMsgData[0];

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
