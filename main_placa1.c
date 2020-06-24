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
 * - Crear main para la placa 2
 * - Crear tareas para comunicación via bus CAN
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

#define TASK_MUESTREAR_P    OSTCBP(1)   //Task 1
#define TASK_TX_AP          OSTCBP(2)   //Task 2
#define TASK_LCD_AP         OSTCBP(3)   //Task 3
#define TASK_LEDS_AP        OSTCBP(4)   //Task 4

//Task priorities
#define PRIO_MUESTREAR      10
#define PRIO_TX             10
#define PRIO_LCD            10
#define PRIO_LEDS           10

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
        
        OS_Yield();
    }
}

/**
 * Muestrea la pulsación de botones
 */
void P_muestrear_botones(void) {

    volatile unsigned char key = getKey(); // O getKeyNotBlocking ?

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
        default: break;
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
    // Se van a dividir en tres mensajes de 2, 6 y 6 bytes
    // Mensaje 1: Lumenes
    // Mensaje 2: hab1, hab2 y hab3
    // Mensaje 3: luz1, luz2 y luz3
    
    /*
     SISTEMA DE IDENTIFICADORES
     * 
     * SID = 0x0001 (1)   --> El mensaje es de 2 bytes y contiene Lumenes
     * SID = 0x0010 (16)  --> El mensaje es de 3 bytes y contiene los hab1..3
     * SID = 0x0100 (256) --> El mensaje es de 3 bytes y contiene los luz1..3
     * 
     */
    
    // ***CUIDADO***
    // Puede que haga falta un delay después de clearTxInt, pero el profe no
    // quiere esperas activas. Si no funciona la transmisión, podría ser esta
    // la razón
    
    
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

/**
 * Muestra en el LCD:
 * - Los lúmenes del exterior
 * - El número de personas en cada hab.
 */
void AP_act_LCD(unsigned int cantHab1, unsigned int cantHab2,
        unsigned int cantHab3, unsigned int lumens){

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
    
    // ===================
    // Init peripherals
    // ===================
    initLEDs();
    CADInit(CAD_INTERACTION_BY_INTERRUPT, 5);
    CADStart(CAD_INTERACTION_BY_INTERRUPT);

    LCDInit();
    KeybInit();
    
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
    OSCreateTask(TaskA, OSTCBP(1), 10);
    OSCreateTask(TaskB, OSTCBP(2), 10);

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