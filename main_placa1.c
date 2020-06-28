/******************************************************************************/
/*                                                                            */
/*  Description: Pr�ctica Final Sistemas Empotrados                           */
/*               Curso 2019-2020                                              */
/*               Ingenier�a Inform�tica UIB                                   */
/*                                                                            */
/*  Authors:     Izar Castorina                                               */
/*               Lisandro Rocha                                               */
/*               Joan Albert Vallori Aguil�                                   */
/*                                                                            */
/******************************************************************************/

/**
 TODO:
 * - Implementar UART
 */

#include <libpic30.h>

#include <p30f4011.h>
#include <stdio.h>
#include <salvo.h>

#include <string.h>
#include <stdlib.h>

#include "libLEDs.h"
#include "libCAD.h"
#include "libLCD.h"
#include "libCAN.h"
#include "libTIMER.h"
#include "delay.h"

#define TASK_MUESTREAR_P    OSTCBP(1)   //Task 1, Botones
#define TASK_TX_AP          OSTCBP(2)   //Task 2, Transmisi�n CAN
#define TASK_LCD_AP         OSTCBP(3)   //Task 3, Act. LCD
#define TASK_LEDS_AP        OSTCBP(4)   //Task 4, Act. LEDs
// NO CREO QUE HAGA FALTA DEFINIR TAREA RX_AP PORQUE ES POR INT.
// #define TASK_RX_AP          OSTCBP(5)   //Task 5, Recepci�n CAN

//Task priorities
#define PRIO_MUESTREAR      10
#define PRIO_TX             10
#define PRIO_LCD            10
#define PRIO_LEDS           10

//Herramientas de concurrencia
#define EFLAG_BOTONES       OSECBP(1)   // Flag para muestreo botones

#define DESPIERTA_CAN       0b00000011  // Valor del flag para despertar ISR CAN
#define DESPIERTA_LCD       0b00000001  // Valor del flag para despertar rutina LCD

#define MSG_CAN             OSECBP(4)   // Mailbox para mensajes CAN


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
volatile unsigned int luz1 = 0, luz2 = 0, luz3 = 0; // Intensidad luz en habitaciones, max 2
volatile int luz1_man = 0, luz2_man = 0, luz3_man = 0;

/******************************************************************************/
/* Procedures declaration                                                     */
/******************************************************************************/

/*  NO BORRAR TODAV�A: PERMITE ACTUALIZAR LEDS SEG�N PAR�METROS
int actualizaLeds(unsigned int habitacion, unsigned int nivelLuz) {

    // 3 habitaciones, niveles de luz: 0 (off), 1 (media), 2 (alta)
    // Hab.     LED
    //  1      0   1
    //  2      2   3
    //  3      4   5

    if (habitacion < 1 || habitacion > 3)   // Fuera de rango
        return -1;                          // Error

    if (habitacion == 1) {
        switch (nivelLuz) {
            case 0: offLED(0); offLED(1); break;
            case 1: onLED(0);  offLED(1); break;
            case 2: onLED(0);  onLED(1);  break;
            default: break;
        }
        return 0;
    }
    if (habitacion == 2) {
        switch (nivelLuz) {
            case 0: offLED(2); offLED(3); break;
            case 1: onLED(2);  offLED(3); break;
            case 2: onLED(2);  onLED(3);  break;
            default: break;
        }
        return 0;
    }
    if (habitacion == 3) {
        switch (nivelLuz) {
            case 0: offLED(4); offLED(5); break;
            case 1: onLED(4);  offLED(5); break;
            case 2: onLED(4);  onLED(5);  break;
            default: break;
        }
        return 0;
    }
}
 * */


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
 * Muestrea la pulsaci�n de botones
 */
void P_muestrear_botones(void) {

    while (1) {

      //  printf("DEBUG - muestreo botones\n");

        volatile unsigned char key = getKeyNotBlocking(); // O getKeyNotBlocking ?

        unsigned char modificados = 1; // Para saber si ha habido cambios o no

        switch (key) {
            case 0: hab1++; // A�adir persona H1
                break;
            case 1: hab2++; // A�adir persona H2
                break;
            case 2: hab3++; // A�adir persona H3
                break;
            case 3: if (hab1 > 0) hab1--; // Quitar persona H1
                break;
            case 4: if (hab2 > 0) hab2--; // Quitar persona H2
                break;
            case 5: if (hab3 > 0) hab3--; // Quitar persona H3
                break;
            case 6: if (luz1_man < 3) luz1_man++; // Subir luz H1
                break;
            case 7: if (luz2_man < 3) luz2_man++; // Subir luz H2
                break;
            case 8: if (luz3_man < 3) luz3_man++; // Subir luz H3
                break;
            case 9: if (luz1_man > -3) luz1_man--; // Bajar luz H1
                break;
            case 10: if (luz2_man > -3) luz2_man--; // Bajar luz H2
                break;
            case 11: if (luz3_man > -3) luz3_man--; // Bajar luz H3
                break;
            default: modificados = 0;
                break; // Si no se ha tocado nada
        }

        if (modificados == 1) // Env�a actualizaci�n CAN solo si se ha tocado alg�n bot�n
            OSSetEFlag(EFLAG_BOTONES, DESPIERTA_CAN);

      //  printf("DEBUG - Acabo el muestreo botones\n");
        OS_Delay(1);

    }

    // 300 ms delay so the keys are not oversampled
    //for (i = 0; i < 60; i++) Delay5ms();
}

/**
 * Envia:
 * - Los l�menes de luz exterior
 * - El n�mero de personas en cada hab.
 * - El nivel de luz deseado en cada hab. (manual)
 */
void AP_tx_datos(void) {

    // Cada unsigned char tiene tama�o de 1 byte (0 - 255)
    // Cada char tiene tama�o de 1 byte (-128, 127)
    // Cada unsigned int tiene tama�o de 2 bytes (hasta 65.535, luego 4)
    // Se puede pasar de int a char y luego otra vez a int sin perder info
    // En total hay que enviar 1+(3*1)+(3*1) = 7 bytes

    /*
     SISTEMA DE IDENTIFICADORES
     *
     * SID = 0x0001 (1)   --> El mensaje es de 7 bytes y contiene todo
     * SID = 0x0002 (2)   --> Mensaje recibido desde la placa 2
     *
     */

    // ***CUIDADO***
    // Puede que haga falta un delay despu�s de clearTxInt, pero el profe no
    // quiere esperas activas. Si no funciona la transmisi�n, podr�a ser esta
    // la raz�n

    while (1) {

        // Espera a que la tarea de botones se�ale que hay nuevos datos para enviar
        OS_WaitEFlag(EFLAG_BOTONES, DESPIERTA_CAN, OSEXACT_BITS, OSNO_TIMEOUT);
        OSClrEFlag(EFLAG_BOTONES, DESPIERTA_CAN); // Limpia el flag y ejecuta la rutina
        OSSetEFlag(EFLAG_BOTONES, DESPIERTA_LCD); // Dice al LCD de actualizarse

        unsigned char data_buffer[8];
        unsigned int ID = 0x0001;
        unsigned char tamDatos = sizeof (data_buffer);

        // Dividimos los l�menes (2 bytes) en dos uns. chars
        unsigned char *lum_chars = (unsigned char *) &lumenes;
        unsigned char lum_h = lum_chars[0];
        unsigned char lum_l = lum_chars[1];

        // Env�o informaciones
        if (CANtxInt) { // Si se puede enviar
            CANclearTxInt(); // Clear del interrupt de transmisi�n CAN

            data_buffer[0] = lum_h;
            data_buffer[1] = lum_l;
            data_buffer[2] = (unsigned char) hab1;
            data_buffer[3] = (unsigned char) hab2;
            data_buffer[4] = (unsigned char) hab3;
            data_buffer[5] = (char) luz1_man;
            data_buffer[6] = (char) luz2_man;
            data_buffer[7] = (char) luz3_man;

            CANsendMessage(ID, data_buffer, tamDatos);
        }

        OS_Yield();
    }

}

/**
 * Muestra en el LCD:
 * - Los l�menes del exterior
 * - El n�mero de personas en cada hab.
 */
void AP_act_LCD(void) {

    while (1) {

        // Espera a que la tarea de CAN se�ale que hay que actualizar
        OS_WaitEFlag(EFLAG_BOTONES, DESPIERTA_LCD, OSEXACT_BITS, OSNO_TIMEOUT);
        OSClrEFlag(EFLAG_BOTONES, DESPIERTA_LCD); // Limpia el flag y ejecuta la rutina

        // Max. longitud l�nea: 16 chars.
        char linea1, linea2 [16];

        sprintf(linea1, "H.1:%u 2:%u 3:%u", hab1, hab2, hab3);
        sprintf(linea2, "Lumens: %u", lumenes);

        LCDMoveFirstLine();
        LCDPrint(linea1);
        LCDMoveSecondLine();
        LCDPrint(linea2);

        IFS0bits.ADIF = 0; // Reset interrupt

        unsigned int i;
        for(i=0; i<10; i++) Delay5ms();

        OS_Yield();
    }

}

/**
 * Muestra en los LEDs:
 * - Los l�menes del exterior
 * - El n�mero de personas en cada hab.
 */
void AP_act_LEDs(void) {
    // 3 habitaciones, niveles de luz: 0 (off), 1 (media), 2 (alta)
    // Hab.     LED
    //  0      0   1
    //  1      2   3
    //  2      4   5

    OStypeMsgP msg_recibido;

    while (1) {

        // Espera al mensaje en el mailbox para actualizar los LEDs
        OS_WaitMsg(MSG_CAN, &msg_recibido, OSNO_TIMEOUT);

        // Habitaci�n 1
        switch (luz1) {
            case 0: offLED(0);
                offLED(1);
                break;
            case 1: onLED(0);
                offLED(1);
                break;
            case 2: onLED(0);
                onLED(1);
                break;
            default: break;
        }
        // Habitaci�n 2
        switch (luz2) {
            case 0: offLED(2);
                offLED(3);
                break;
            case 1: onLED(2);
                offLED(3);
                break;
            case 2: onLED(2);
                onLED(3);
                break;
            default: break;
        }
        // Habitaci�n 3
        switch (luz3) {
            case 0: offLED(4);
                offLED(5);
                break;
            case 1: onLED(4);
                offLED(5);
                break;
            case 2: onLED(4);
                onLED(5);
                break;
            default: break;
        }

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

    OSSetEFlag(EFLAG_BOTONES, DESPIERTA_CAN); // Dice al CAN de enviar datos nuevos

    // COMENTADO POR AHORA, SI LA TAREA SE QUEDA PILLADA ES QUE HACE FALTA PONERLO
    // OS_Yield();
}

/******************************************************************************/
/* Timer ISR - Muestreo botones                                               */

/******************************************************************************/

void _ISR _T1Interrupt(void) {

    TimerClearInt();
    OSTimer();

}

/******************************************************************************/
/* CAN ISR - Recepci�n datos (nivel de luz para cada habitaci�n               */

/******************************************************************************/
void _ISR _C1Interrupt(void) {


    static unsigned char mensaje_mbox_LEDs = 1;

    unsigned int rxMsgSID;
    unsigned char rxMsgData[8];
    unsigned char rxMsgDLC;

    // Clear CAN global interrupt
    CANclearGlobalInt();

    if (CANrxInt()) {
        // Clear RX interrupt
        CANclearRxInt();

        // Read SID, DLC and DATA
        rxMsgSID = CANreadRxMessageSID();
        rxMsgDLC = CANreadRxMessageDLC();
        CANreadRxMessageDATA(rxMsgData);

        // Clear RX buffer
        CANclearRxBuffer();

        if (rxMsgSID == 0x0002) {

            luz1 = (unsigned int) rxMsgData[0];
            luz2 = (unsigned int) rxMsgData[1];
            luz3 = (unsigned int) rxMsgData[2];

        }
    }

    // Env�a mensaje en mailbox para que se actualicen los LEDs
    OSSignalMsg(MSG_CAN, (OStypeMsgP) & mensaje_mbox_LEDs);

    // COMENTADO POR AHORA, SI LA TAREA SE QUEDA PILLADA ES QUE HACE FALTA PONERLO
    // OS_Yield();

}

/******************************************************************************/
/* Main                                                                       */

/******************************************************************************/

int main(void) {

    // ===================
    // Init peripherals
    // ===================
    initLEDs();
    CADInit(CAD_INTERACTION_BY_INTERRUPT, 5);
    CADStart(CAD_INTERACTION_BY_INTERRUPT);

    LCDInit();
    KeybInit();

    Timer1Init(TIMER_PERIOD_FOR_10ms, TIMER_PSCALER_FOR_10ms, 5);
    Timer1Start();

    CANinit(NORMAL_MODE, FALSE, FALSE, 0, 0);  // Comentado por ahora, da problemas con la simulaci�n
/*
    lumenes = 2560;
    unsigned char *lum_chars = (unsigned char *) &lumenes;
    unsigned char lum_h = lum_chars[0];
    unsigned char lum_l = lum_chars[1];

    unsigned int lums_reconv = (unsigned int) lum_l << 8;
    unsigned int aux = (unsigned int) lum_h;
    lums_reconv += aux;
*/


  //  printf("--------------------Nueva ejecucion-------------------\n");
    ////printf("DEBUG: sizeof lumenes: %d | sizeof hab1: %d\n", sizeof(lumenes), sizeof(hab1));
    ////printf("DEBUG: sizeof de un sizeof: %d\n", sizeof(sizeof(lumenes)));

  //  printf("DEBUG: lumenes en unsigned char: %c | %c\n", lum_h, lum_l);
  //  printf("DEBUG: lumenes reconvertido: %d\n", lums_reconv);

  //  printf("DEBUG - test signed char: %c\n", test_c);
  //  printf("DEBUG - test signed char reconv: %d\n", (int) test_c);

    // =========================
    // Create Salvo structures
    // =========================
    // Init Salvo
    OSInit();

    // Create tasks (name, tcb, priority) and push them to ELIGIBLE STATE
    // From 1 up to OSTASKS tcbs available
    // Priorities from 0 (highest) down to 15 (lowest)

    OSCreateTask(P_muestrear_botones, OSTCBP(1), 10);
    OSCreateTask(AP_tx_datos, OSTCBP(2), 10);
    OSCreateTask(AP_act_LCD, OSTCBP(3), 10);
    OSCreateTask(AP_act_LEDs, OSTCBP(4), 10);

    // Creamos herramientas de concurrencia
    OSCreateMsg(MSG_CAN, (OStypeMsgP) 0);
    // Honestamente, no s� porque OSEFCBP(1), podr�a ser otro
    //            OSTCBP(1)      eso mismo  val. inicial
    OSCreateEFlag(EFLAG_BOTONES, OSEFCBP(1), 0x00);

    // =============================================
    // Enter multitasking environment
    // =============================================
    while (1) {
        OSSched();
    }

}

/******************************************************************************/
/* Procedures implementation                                                  */
/******************************************************************************/
