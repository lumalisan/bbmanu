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
 * - Implementar UART
 * - Crear tareas concurrentes
 * - Implementar sistema de flags y MBox
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

#define TASK_MUESTREAR_P    OSTCBP(1)   //Task 1, Botones
#define TASK_TX_AP          OSTCBP(2)   //Task 2, Transmisión CAN
#define TASK_LCD_AP         OSTCBP(3)   //Task 3, Act. LCD
#define TASK_LEDS_AP        OSTCBP(4)   //Task 4, Act. LEDs
#define TASK_RX_AP          OSTCBP(5)   //Task 5, Recepción CAN

//Task priorities
#define PRIO_MUESTREAR      10
#define PRIO_TX             10
#define PRIO_LCD            10
#define PRIO_LEDS           10

//Herramientas de concurrencia
#define EFLAG_BOTONES       OSECBP(1)   // Flag para muestreo botones

#define DESPIERTA_CAN       0b00000011  // Valor del flag para despertar ISR CAN
#define DESPIERTA_LCD       0b00000001  // Valor del flag para despertar rutina LCD

#define MSG_CAN             OSECBP(5)   // Mailbox para mensajes CAN


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

unsigned char count = 0;
unsigned int lumenes = 0;
unsigned int hab1 = 0, hab2 = 0, hab3 = 0; // Cant. personas en habitaciones
unsigned int luz1 = 0, luz2 = 0, luz3 = 0; // Intensidad luz en habitaciones

/******************************************************************************/
/* Procedures declaration                                                     */
/******************************************************************************/

/*  NO BORRAR TODAVÍA: PERMITE ACTUALIZAR LEDS SEGÚN PARÁMETROS
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

// TASKS DE EJEMPLO
void TaskA(void) {
    unsigned char i;

    while (1) {
        for (i = 0; i < 15; i++)
            // Delay15ms();

        count = (count + 1) % 64;
        OS_Yield(); // Indica al SO que quiere salir de la CPU
    }
}

void TaskB(void) {
    unsigned char i;

    while (1) {
        for (i = 0; i < 15; i++)
            // Delay15ms();

        //printNumInLED(count);
        
        OS_Yield();
    }
}

/**
 * Muestrea la pulsación de botones
 */
void P_muestrear_botones(void) {
    
    while(1) {
            
        printf("DEBUG - muestreo botones\n");

        volatile unsigned char key = getKeyNotBlocking(); // O getKeyNotBlocking ?
        
        unsigned char modificados = 1;  // Para saber si ha habido cambios o no

        switch (key) {
            case 0: hab1++; // Añadir persona H1
                break;
            case 1: hab2++; // Añadir persona H2
                break;
            case 2: hab3++; // Añadir persona H3
                break;
            case 3: if (hab1 > 0) hab1--; // Quitar persona H1
                break;
            case 4: if (hab2 > 0) hab2--; // Quitar persona H2
                break;
            case 5: if (hab3 > 0) hab3--; // Quitar persona H3
                break;
            case 6: luz1++; // Subir luz H1
                break;
            case 7: luz2++; // Subir luz H2
                break;
            case 8: luz3++; // Subir luz H3
                break;
            case 9: if (luz1 > 0) luz1--; // Bajar luz H1
                break;
            case 10: if (luz2 > 0) luz2--; // Bajar luz H2
                break;
            case 11: if (luz3 > 0) luz3--; // Bajar luz H3
                break;
            default: modificados = 0; break; // Si no se ha tocado nada
        }
        
        if (modificados == 1)   // Envía actualización CAN solo si se ha tocado algún botón
            OSSetEFlag(EFLAG_BOTONES, DESPIERTA_CAN);

        printf("DEBUG - Acabo el muestreo botones\n");
        OS_Delay(1);
        
    }
    
    // 300 ms delay so the keys are not oversampled
    //for (i = 0; i < 60; i++) Delay5ms();
}

/**
 * Envia: 
 * - Los lúmenes de luz exterior
 * - El número de personas en cada hab.
 * - El nivel de luz deseado en cada hab. (manual)
 */
void AP_tx_datos(void){
    
    // Cada unsigned char tiene tamaño de 1 byte
    // Cada unsigned int tiene tamaño de 2 bytes (hasta 65.535, luego 4)
    // Se puede pasar de int a char y luego otra vez a int sin perder info
    // En total hay que enviar 1+(3*1)+(3*1) = 7 bytes
    
    /*
     SISTEMA DE IDENTIFICADORES
     * 
     * SID = 0x0001 (1)   --> El mensaje es de 7 bytes y contiene todo
     * 
     *
    */
    
    // ***CUIDADO***
    // Puede que haga falta un delay después de clearTxInt, pero el profe no
    // quiere esperas activas. Si no funciona la transmisión, podría ser esta
    // la razón
    
    while(1) {
        
        // Espera a que la tarea de botones señale que hay nuevos datos para enviar
        OS_WaitEFlag(EFLAG_BOTONES, DESPIERTA_CAN, OSEXACT_BITS, OSNO_TIMEOUT);
        OSClrEFlag(EFLAG_BOTONES, DESPIERTA_CAN);   // Limpia el flag y ejecuta la rutina
        OSSetEFlag(EFLAG_BOTONES, DESPIERTA_LCD);   // Dice al LCD de actualizarse

        unsigned char data_buffer[7];
        unsigned int ID = 0x0001;
        unsigned char tamDatos = sizeof(data_buffer);

        // Envío informaciones
        if (CANtxInt) {         // Si se puede enviar
            CANclearTxInt();    // Clear del interrupt de transmisión CAN

            ID = 0x0001;
            data_buffer[0] = (unsigned char) lumenes;
            data_buffer[1] = (unsigned char) hab1;
            data_buffer[2] = (unsigned char) hab2;
            data_buffer[3] = (unsigned char) hab3;
            data_buffer[4] = (unsigned char) luz1;
            data_buffer[5] = (unsigned char) luz2;
            data_buffer[6] = (unsigned char) luz3;

            CANsendMessage(ID, data_buffer, tamDatos);
        }
    }

}

/**
 * Muestra en el LCD:
 * - Los lúmenes del exterior
 * - El número de personas en cada hab.
 */
void AP_act_LCD(unsigned int cantHab1, unsigned int cantHab2,
        unsigned int cantHab3, unsigned int lumens){

    while(1) {
        
        // Espera a que la tarea de CAN señale que hay que actualizar
        OS_WaitEFlag(EFLAG_BOTONES, DESPIERTA_LCD, OSEXACT_BITS, OSNO_TIMEOUT);
        OSClrEFlag(EFLAG_BOTONES, DESPIERTA_LCD);   // Limpia el flag y ejecuta la rutina
        
        // Max. longitud línea: 16 chars.
        char linea1, linea2 [16];

        sprintf(linea1, "H.1:%d 2:%d 3:%d", cantHab1, cantHab2, cantHab3);
        sprintf(linea2, "Lumens: %d", lumens);

        LCDMoveFirstLine();
        LCDPrint(linea1);
        LCDMoveSecondLine();
        LCDPrint(linea2);

        IFS0bits.ADIF = 0; // Reset interrupt
    }
    
        

}

/**
 * Muestra en los LEDs:
 * - Los lúmenes del exterior
 * - El número de personas en cada hab.
 */
void AP_act_LEDs(void){
    // 3 habitaciones, niveles de luz: 0 (off), 1 (media), 2 (alta)
    // Hab.     LED
    //  0      0   1
    //  1      2   3
    //  2      4   5
    
    OStypeMsgP msg_recibido;

    while(1) {
        
        // Espera al mensaje en el mailbox para actualizar los LEDs
        OS_WaitMsg(MSG_CAN, &msg_recibido, OSNO_TIMEOUT);
        
        // Habitación 1
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
        // Habitación 2
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
        // Habitación 3
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
    
    OSSetEFlag(EFLAG_BOTONES, DESPIERTA_CAN);   // Dice al CAN de enviar datos nuevos

}

/******************************************************************************/
/* Timer ISR - Muestreo botones                                               */
/******************************************************************************/

void _ISR _T1Interrupt(void) {

    TimerClearInt();
    OSTimer();

}

/******************************************************************************/
/* CAN ISR - Recepción datos (nivel de luz para cada habitación               */
/******************************************************************************/
void _ISR _C1Interrupt(void) {
    
    static unsigned char mensaje_mbox_LEDs = 1;
        
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
    
    // Envía mensaje en mailbox para que se actualicen los LEDs
    OSSignalMsg(MSG_CAN, (OStypeMsgP) &mensaje_mbox_LEDs);
    
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
    
    // CANinit(NORMAL_MODE, FALSE, FALSE, 0, 0);  // Comentado por ahora, da problemas con la simulación
    
    lumenes = 123;
    
    printf("--------------------Nueva ejecucion-------------------\n");
    printf("DEBUG: sizeof lumenes: %d | sizeof hab1: %d\n", sizeof(lumenes), sizeof(hab1));
    printf("DEBUG: sizeof de un sizeof: %d\n", sizeof(sizeof(lumenes)));
    
    unsigned char test_char = (unsigned char) lumenes;
    unsigned int test_conv = (unsigned int) test_char;
    printf("DEBUG: lumenes en unsigned char: %c\n", test_char);
    printf("DEBUG: lumenes en unsigned char (int): %d\n", test_char);
    printf("DEBUG: lumenes reconvertido: %d\n", test_conv);
    

    // =========================
    // Create Salvo structures
    // =========================
    // Init Salvo
    OSInit();

    // Create tasks (name, tcb, priority) and push them to ELIGIBLE STATE
    // From 1 up to OSTASKS tcbs available
    // Priorities from 0 (highest) down to 15 (lowest)
    OSCreateTask(TaskA, OSTCBP(2), 10);
    OSCreateTask(TaskB, OSTCBP(3), 10);
    OSCreateTask(P_muestrear_botones, OSTCBP(1), 10);
    
    // Creamos herramientas de concurrencia
    OSCreateMsg(MSG_CAN, (OStypeMsgP) 0);
    // Honestamente, no sé porque OSEFCBP(1), podría ser otro
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