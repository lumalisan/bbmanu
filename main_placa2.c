// SI TODO EST� COMENTADO ES PORQUE SI NO NO ME DEJA COMPILAR PORQUE
// HAY DOS MAINS


///******************************************************************************/
///*                                                                            */
///*  Description: Pr�ctica Final Sistemas Empotrados                           */
///*               Curso 2019-2020                                              */
///*               Ingenier�a Inform�tica UIB                                   */
///*                                                                            */
///*  Authors:     Izar Castorina                                               */
///*               Lisandro Rocha                                               */
///*               Joan Albert Vallori Aguil�                                   */
///*                                                                            */
///******************************************************************************/
//
///**
// TODO:
// * 
// */
//
//#include <p30f4011.h>
//#include <stdio.h>
//#include <salvo.h>
//
//#include <string.h>
//#include <stdlib.h>
//
//#include "libLEDs.h"
//#include "libCAD.h"
//#include "libLCD.h"
//
//#define TASK_CTRL_P         OSTCBP(1)   //Task 1
//#define TASK_TX_AP          OSTCBP(2)   //Task 2
//#define TASK_RX_AP          OSTCBP(3)   //Task 3
//#define TASK_LCD_AP         OSTCBP(4)   //Task 4
//
////Task priorities
//#define PRIO_CTRL           10
//#define PRIO_TX             10
//#define PRIO_RX             10
//#define PRIO_LCD            10
//
///******************************************************************************/
///* Configuration words                                                        */
///******************************************************************************/
//_FOSC(CSW_FSCM_OFF & EC_PLL16);
//_FWDT(WDT_OFF);
//_FBORPOR(MCLR_EN & PBOR_OFF & PWRT_OFF);
//_FGS(CODE_PROT_OFF);
//
///******************************************************************************/
///* Hardware                                                                   */
///******************************************************************************/
//
//
///******************************************************************************/
///* Salvo elements declarations                                                */
///******************************************************************************/
//
//
///******************************************************************************/
///* Global Variable and macros declaration                                     */
///******************************************************************************/
//
//unsigned int lumenes;
//
///******************************************************************************/
///* Procedures declaration                                                     */
///******************************************************************************/
//
//
///******************************************************************************/
///* TASKS declaration and implementation                                       */
///******************************************************************************/
//
///* Task states
//
//   DESTROYED / uninitialized
//   STOPPED
//   WAITING
//   DELAYED
//   ELIGIBLE /READY
//   RUNNING
//
// */
//
///**
// * Decide la intensidad de la luz en cada hab.
// */
//void P_ctrl(void){
//
//}
//
///**
// * Muestra en el LCD:
// * - Los l�menes del exterior
// * - El n�mero de personas en cada hab.
// */
//void AP_act_LCD(void){
//
//}
//
///**
// * Recibe: 
// * - Los l�menes de luz exterior
// * - El n�mero de personas en cada hab.
// * - El nivel de luz deseado en cada hab. (manual)
// */
//void AP_rx_datos(void){
//
//}
//
///**
// * Envia: 
// * - Los l�menes de luz exterior
// * - El n�mero de personas en cada hab.
// * - El nivel de luz deseado en cada hab. (manual)
// */
//void AP_tx_datos(void){
//
//}
//
///******************************************************************************/
///* Interrupts                                                                 */
///******************************************************************************/
//
//
///******************************************************************************/
///* ADC ISR - CAD Reading                                                      */
///******************************************************************************/
//
//void _ISR _ADCInterrupt(void) {
//
//    lumenes = CADGetValue(); // Leemos el valor
//    // CADRequestValue();    // Pedimos el siguiente valor
//
//    IFS0bits.ADIF = 0; // Reset del interrupt
//
//}
//
///******************************************************************************/
///* CAN ISR - Recepci�n datos                                                  */
///******************************************************************************/
//void _ISR _C1Interrupt(void) {
//    
//}
//
///******************************************************************************/
///* Main                                                                       */
///******************************************************************************/
//
//int main(void) {
//    return 0;
//}
//
///******************************************************************************/
///* Procedures implementation                                                  */
///******************************************************************************/
