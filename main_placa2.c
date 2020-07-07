// SI TODO ESTA COMENTADO ES PORQUE SI NO NO ME DEJA COMPILAR PORQUE
// HAY DOS MAINS


/******************************************************************************/
/*                                                                            */
/*  Description: Practica Final Sistemas Empotrados                           */
/*               Curso 2019-2020                                              */
/*               Ingenieria Informatica UIB                                   */
/*                                                                            */
/*  Authors:     Izar Castorina                                               */
/*               Lisandro Rocha                                               */
/*               Joan Albert Vallori Aguilo                                   */
/*                                                                            */
/******************************************************************************/

/**
 TODO:
 * - Control de la luminosidad
 * - EnvÔøΩo por CAN
 *
 */

#include <p30f4011.h>
#include <stdio.h>
#include <salvo.h>

#include <string.h>
#include <stdlib.h>

#include "libLCD.h"
#include "libTIMER.h"
#include "libCAN.h"

#include "uart.h"
#include "variables.h"

#define TASK_CTRL_P         OSTCBP(1)   //Task 1
#define TASK_TX_AP          OSTCBP(2)   //Task 2
#define TASK_LCD_AP         OSTCBP(3)   //Task 4

//Task priorities
#define PRIO_CTRL           10
#define PRIO_TX             10
#define PRIO_LCD            10

//Herramientas de concurrencia
#define EFLAG_P_CTRL        OSECBP(1)   // Flag para control de luz

#define DESPIERTA_TX        0x01  // Valor del flag para despertar envÔøΩo CAN

#define MSG_RX_LCD          OSECBP(3)   // Mailbox para actualizar LCD
#define BINSEM_CTRL_LCD     OSECBP(3)   // SemÔøΩforo para actualizar LCD

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


/******************************************************************************/
/* Salvo elements declarations                                                */
/******************************************************************************/


/******************************************************************************/
/* Global Variable and macros declaration                                     */
/******************************************************************************/

volatile unsigned int lumenes = 0;
volatile unsigned int hab1 = 0, hab2 = 0, hab3 = 0; // Cant. personas en habitaciones
volatile unsigned int luz1 = 0, luz2 = 0, luz3 = 0; // Intensidad luz en habitaciones (calculada)
volatile unsigned int luz1_man = 3, luz2_man = 3, luz3_man = 3; // Intensidad luz (recibida)
volatile unsigned int lums1 = 0, lums2 = 0, lums3 = 0; // Intensidad luz artificial en lumenes

char rx_uart[16];
char * datos = rx_uart;

#define LUMS_STEP   1000     // Cada incremento de lums es +- 1000
#define MAX_ARGS    5        // Maximo argumentos para comandos UART

/******************************************************************************/
/* Procedures declaration                                                     */
/******************************************************************************/
void UARTConfig();
void checkComando();

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
void P_ctrl(void) {

    while (1) {

        unsigned int luz1_previa = luz1;
        unsigned int luz2_previa = luz2;
        unsigned int luz3_previa = luz3;

        // DeterminaciÔøΩn automÔøΩtica de la intensidad de las luces

        if (lumenes <= 341) { // SegÔøΩn la luz exterior
            // Luz baja (noche), si hay gente enciende
            switch (hab1) { // SegÔøΩn el n. de personas
                case 0: luz1 = 0;
                    break;
                case 1: luz1 = 1;
                    break;
                default: luz1 = 2;
                    break;
            }
            switch (hab2) {
                case 0: luz2 = 0;
                    break;
                case 1: luz2 = 1;
                    break;
                default: luz2 = 2;
                    break;
            }
            switch (hab3) {
                case 0: luz3 = 0;
                    break;
                case 1: luz3 = 1;
                    break;
                default: luz3 = 2;
                    break;
            }
        } else if (lumenes > 341 && lumenes <= 682) {
            // Luz media (tarde), si hay mÔøΩs de una persona enciende 1 luz
            switch (hab1) {
                case 0: luz1 = 0;
                    break;
                case 1: luz1 = 0;
                    break;
                default: luz1 = 1;
                    break;
            }
            switch (hab2) {
                case 0: luz2 = 0;
                    break;
                case 1: luz2 = 0;
                    break;
                default: luz2 = 1;
                    break;
            }
            switch (hab3) {
                case 0: luz3 = 0;
                    break;
                case 1: luz3 = 0;
                    break;
                default: luz3 = 1;
                    break;
            }
        } else if (lumenes > 682) {
            // Luz alta (dÔøΩa), no enciende nada
            luz1 = 0;
            luz2 = 0;
            luz3 = 0;
        }

        // Ahora se calcula teniendo en cuenta los comandos manuales
        // impartidos a travÔøΩs de los botones en la placa 1


        if (luz1_man - 3 > luz1) luz1 = 0;
        else luz1 = luz1 + luz1_man - 3;
        if (luz2_man - 3 > luz1) luz2 = 0;
        else luz2 = luz2 + luz2_man - 3;
        if (luz3_man - 3 > luz1) luz3 = 0;
        else luz3 = luz3 + luz3_man - 3;

        // Si se ha producido algÔøΩn cambio, dile al CAN de enviar la info actualizada
        if (luz1 != luz1_previa || luz2 != luz2_previa || luz3 != luz3_previa) {
            OSSetEFlag(EFLAG_P_CTRL, DESPIERTA_TX);
        }

        OSSignalBinSem(BINSEM_CTRL_LCD); // SeÔøΩala al LCD que puede actualizarse

        OS_Delay(1);
    }

}

/**
 * Muestra en el LCD:
 * - Los lÔøΩmenes del exterior
 * - Los lÔøΩmenes por habitaciÔøΩn
 */
void AP_act_LCD(void) {
    // Calcula la intensidad actual de lÔøΩmenes y la enseÔøΩa
    // lums1..3

    OStypeMsgP msg_recibido;

    while (1) {

        // Espera a que la tarea de CAN seÔøΩale que hay que actualizar
        OS_WaitMsg(MSG_RX_LCD, &msg_recibido, OSNO_TIMEOUT);

        // Espera a que se hayan calculado los valores de luz
        OS_WaitBinSem(BINSEM_CTRL_LCD, OSNO_TIMEOUT);

        // Max. longitud lÔøΩnea: 16 chars.
        LCDClear();
        char linea1 [20];
        char linea2 [20];

        lums1 = luz1 * LUMS_STEP;
        lums2 = luz2 * LUMS_STEP;
        lums3 = luz3 * LUMS_STEP;

        sprintf(linea1, "EX:%u H1:%u", lumenes, lums1);
        sprintf(linea2, "H2:%u H3:%u", lums2, lums3);

        // DEBUG
        //sprintf(linea1, "EX:%u H1:%u", lumenes, luz1_man);
        //sprintf(linea2, "H2:%u H3:%u", luz2_man, luz3_man);

        LCDMoveFirstLine();
        LCDPrint(linea1);
        LCDMoveSecondLine();
        LCDPrint(linea2);

        IFS0bits.ADIF = 0; // Reset interrupt

        unsigned int i;
        for (i = 0; i < 5; i++) Delay15ms();

        OS_Yield();
    }

}

/**
 * Envia:
 * - Los lÔøΩmenes de luz exterior
 * - El nivel de luz deseado en cada hab. (manual)
 */
void AP_tx_datos(void) {
    // Llamado despuÔøΩs de P_ctrl
    // EnvÔøΩa los valores actualizados de lumenes y luces

    // Cada unsigned char tiene tamaÔøΩo de 1 byte
    // Cada unsigned int tiene tamaÔøΩo de 2 bytes (hasta 65.535, luego 4)

    /*
     SISTEMA DE IDENTIFICADORES
     *
     * SID = 0x0001 (1)   --> Mensaje recibido desde la placa 1
     * SID = 0x0002 (2)   --> Enviar luz1..3
     *
     */

    static unsigned char mensaje_mbox_LCD = 1;

    while (1) {

        // Espera a que la tarea de control seÔøΩale que hay nuevos datos para enviar
        OS_WaitEFlag(EFLAG_P_CTRL, DESPIERTA_TX, OSEXACT_BITS, OSNO_TIMEOUT);
        OSClrEFlag(EFLAG_P_CTRL, DESPIERTA_TX); // Limpia el flag y ejecuta la rutina

        unsigned char data_buffer[3];
        unsigned int ID = 0x0002;
        unsigned char tamDatos = sizeof (data_buffer);

        // EnvÔøΩo informaciones
        if (CANtxInt) { // Si se puede enviar
            CANclearTxInt(); // Clear del interrupt de transmisiÔøΩn CAN

            data_buffer[0] = (unsigned char) luz1;
            data_buffer[1] = (unsigned char) luz2;
            data_buffer[2] = (unsigned char) luz3;

            CANsendMessage(ID, data_buffer, tamDatos);
        }

        // Avisa al LCD que puede actualizarse y esperar al semÔøΩforo de control
        OSSignalMsg(MSG_RX_LCD, (OStypeMsgP) & mensaje_mbox_LCD);

        OS_Yield();
    }

}

/******************************************************************************/
/* Interrupts                                                                 */
/******************************************************************************/


/******************************************************************************/
/* CAN ISR - RecepciÔøΩn datos                                                  */
/* Recibe info de num. personas y luz deseada (manual) en cada habitaciÔøΩn     */
/* TambiÔøΩn recibe el nÔøΩmero de lÔøΩmenes exteriores                             */

/******************************************************************************/
void _ISR _C1Interrupt(void) {
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
/* UART ISR - Lectura de datos por UART                                       */
/* La rutina ha sido programada para activarse cada vez que se detecta un char*/

/******************************************************************************/

void _ISR _U1RXInterrupt(void) {

    IFS0bits.U1RXIF = 0; // Reset del interrupt UART RX

    char c;

    char linea1[20]; // Mensaje a ense�ar en la primera linea de LCD (DEBUG)
    sprintf(linea1, "Recibido de UART");

    while (DataRdyUART1()) { // Hasta que haya datos
        c = ReadUART1(); // Leemos el car�cter
        (*(datos)++) = c; // Lo ponemos en el string rx_uart (var. global)
    }

    if (c == '\r' || c == '\n') { // Si se detecta un Enter

        LCDClear(); // Limpio pantalla

        rx_uart[strcspn(rx_uart, "\r\n")] = 0; // Elimino los \r y \n del string

        // Escribo en pantalla
        LCDMoveFirstLine();
        LCDPrint(linea1);
        LCDMoveSecondLine();
        LCDPrint(rx_uart);

        IFS0bits.ADIF = 0; // Reset interrupt del LCD  

        // Que quede en la pantalla durante 1 seg.
        unsigned int i;
        for (i = 0; i < 200; i++) {
            Delay5ms();
        }

        checkComando();


        strncpy(rx_uart, "", sizeof (rx_uart)); // Reset string a vacio
        datos = rx_uart; // Reset puntero a principio

    }


}

/******************************************************************************/
/* Timer ISR - CÔøΩlculo intensidad                                             */

/******************************************************************************/

void _ISR _T1Interrupt(void) {

    TimerClearInt();
    OSTimer();

}

/******************************************************************************/
/* Main                                                                       */

/******************************************************************************/

int main(void) {
    // ===================
    // Init peripherals
    // ===================

    LCDInit();

    Timer1Init(TIMER_PERIOD_FOR_250ms, TIMER_PSCALER_FOR_250ms, 5);
    Timer1Start();

    CANinit(NORMAL_MODE, TRUE, TRUE, 0, 0); // Comentado por ahora, da problemas con la simulaciÔøΩn

    UARTConfig();


    // ========================= 
    // Create Salvo structures
    // =========================
    // Init Salvo
    OSInit();

    // Create tasks (name, tcb, priority) and push them to ELIGIBLE STATE
    // From 1 up to OSTASKS tcbs available
    // Priorities from 0 (highest) down to 15 (lowest)

    OSCreateTask(P_ctrl, OSTCBP(1), 10);
    OSCreateTask(AP_tx_datos, OSTCBP(2), 10);
    OSCreateTask(AP_act_LCD, OSTCBP(3), 10);

    // Creamos herramientas de concurrencia
    OSCreateMsg(MSG_RX_LCD, (OStypeMsgP) 0);
    // Honestamente, no sÔøΩ porque OSEFCBP(1), podrÔøΩa ser otro
    //            OSTCBP(1)      eso mismo  val. inicial
    OSCreateEFlag(EFLAG_P_CTRL, OSEFCBP(1), 0x00);

    OSCreateBinSem(BINSEM_CTRL_LCD, 0);

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
void UARTConfig() {
    U1MODE = 0; // Clear UART config - to avoid problems with bootloader
    // Activar int. RX -->1 111 <-- Prioridad entre 0 y 7
    ConfigIntUART1(0x000F); // Enable RX Interrupt, highest priority


    // Config UART
    OpenUART1(UART_EN & // Enable UART
            UART_DIS_LOOPBACK & // Disable loopback mode
            UART_NO_PAR_8BIT & // 8bits / No parity
            UART_1STOPBIT, // 1 Stop bit
            UART_TX_PIN_NORMAL & // Tx break bit normal
            UART_TX_ENABLE &
            UART_INT_RX_CHAR & // Interrupt para cada char recibido
            UART_RX_INT_EN, // Enable Transmission and RX Interruptions
            BRG); // Baudrate
}

void checkComando() {
    char *string;
    strcpy(string, rx_uart); // Copiamos el string porque strtok es destructivo
    const char s[2] = " "; // Caracter delimitador de los tokens
    unsigned int contador = 0; // Contador de cuantos tokens se crean

    char *token;
    char *args[MAX_ARGS];
    token = strtok(string, s); // Sacamos el primer token

    while (token != NULL) { // Hasta que siga habiendo y hasta 5, sacamos mas
        if (contador < MAX_ARGS) {
            args[contador] = token;
            contador++;
            token = strtok(NULL, s);
        }
    }

    // Variables para el envio por CAN
    unsigned int ID;
    unsigned char tamDatos;

    // Procesamos el comando
    // Comandos posibles:
    // - turnAllOn (x): Enciende todas las luces al nivel x (si especificado, si no al maximo)
    // - turnAllOff:    Apaga todas las luces
    // - setLights x y: Pone las luces de la hab. x al nivel y

    if (strcmp(args[0], "turnAllOn") == 0) {

        if (contador == 1) { // Si no se ha especificado otro parametro
            ID = 0x0010;
            unsigned char data_buffer = 0;
            tamDatos = sizeof (data_buffer);

            if (CANtxInt) {
                CANclearTxInt();
                CANsendMessage(ID, data_buffer, tamDatos);
            }

        } else if (args[1] != NULL) { // Se comprueba que no sea NULL el segundo argumento
            ID = 0x0011;

            int nivel = atoi(args[1]);
            // El nivel puede ir de 0 hasta maximo 2
            if (nivel >= 0 && nivel <= 2) {
                unsigned char data_buffer = (unsigned char) args[1];
                tamDatos = sizeof (data_buffer);

                if (CANtxInt) {
                    CANclearTxInt();
                    CANsendMessage(ID, data_buffer, tamDatos);
                }
            }
        }

    } else if (strcmp(args[0], "turnAllOff") == 0) {
        ID = 0x0020;
        unsigned char data_buffer = 0;
        tamDatos = sizeof (data_buffer);

        if (CANtxInt) {
            CANclearTxInt();
            CANsendMessage(ID, data_buffer, tamDatos);
        }

    } else if (strcmp(args[0], "setLights") == 0) {
        
        if (args[1] != NULL && args[2] != NULL) {
            
            // atoi convierte de string a int, devuelve 0 si no se puede convertir
            // En este caso, la hab. no puede ser 0, pero el nivel de luz si
            // y no podemos saber si el 0 es por un error de conversion o porque
            // el usuario quiere poner a cero (apagar) las luces de una hab.
            int num_hab = atoi(args[1]);
            int val_luz = atoi(args[2]);

            // Si los valores son validos, enviamos los datos
            if (num_hab >= 1 && num_hab <= 3 && val_luz >= 0 && val_luz <= 2) {

                ID = 0x0030;
                unsigned char data_buffer[2];
                data_buffer[0] = (unsigned char) args[1]; // Num. habitacion
                data_buffer[1] = (unsigned char) args[2]; // Valor luces
                tamDatos = sizeof (data_buffer);

                if (CANtxInt) {
                    CANclearTxInt();
                    CANsendMessage(ID, data_buffer, tamDatos);
                }
            }
        }
    }
}