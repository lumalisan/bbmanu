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

// TASKS DE EJEMPLO
void TaskA(void) {
    unsigned char i;

    while (1) {
        for (i = 0; i < 15; i++)
            Delay15ms();

        count = (count + 1) % 64;
        OS_Yield(); // Indica al SO que quiere salir de la CPU
    }
}

void TaskB(void) {
    unsigned char i;

    while (1) {
        for (i = 0; i < 15; i++)
            Delay15ms();

        printNumInLED(count);
        //printf("DEBUG: %d\n", count);
        OS_Yield();
    }
}

/******************************************************************************/
/* Interrupts                                                                 */
/******************************************************************************/


/******************************************************************************/
/* ADC ISR - CAD Reading                                                      */
/******************************************************************************/

void _ISR _ADCInterrupt(void) {

    lumenes = CADGetValue(); // Leemos el valor
    // CADRequestValue();    // Pedimos el siguiente valor

    IFS0bits.ADIF = 0; // Reset del interrupt

}

/******************************************************************************/
/* Main                                                                       */
/******************************************************************************/

int main(void) {
    
}

/******************************************************************************/
/* Procedures implementation                                                  */
/******************************************************************************/
