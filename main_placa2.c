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

#define TASK_CTRL_P         OSTCBP(1)   //Task 1, Control luminosidad
#define TASK_TX_AP          OSTCBP(2)   //Task 2, Transmision CAN
#define TASK_LCD_AP         OSTCBP(3)   //Task 3, Act. LCD

//Task priorities
#define PRIO_CTRL           10
#define PRIO_TX             10
#define PRIO_LCD            10

//Herramientas de concurrencia
#define EFLAG_P_CTRL        OSECBP(1)   // Flag para control de luz

#define DESPIERTA_TX        0x01  		// Valor del flag para despertar envÔøΩo CAN

#define MSG_RX_LCD          OSECBP(3)   // Mailbox para actualizar LCD
#define BINSEM_CTRL_LCD     OSECBP(3)   // Semaforo para actualizar LCD

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
volatile unsigned int luz1_man = 2, luz2_man = 2, luz3_man = 2; // Intensidad luz (recibida)
volatile unsigned int lums1 = 0, lums2 = 0, lums3 = 0; // Intensidad luz artificial en lumenes

char rx_uart[16];
char * datos = rx_uart;

#define LUMS_STEP   1000     // Cada incremento de lums es +- 1000
#define MAX_ARGS    5        // Maximo argumentos para comandos UART

/******************************************************************************/
/* Procedures declaration                                                     */
/******************************************************************************/
void UARTConfig();
int checkComando();

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
 * Tarea periodica, decide la intensidad de la luz en cada hab.
 */
void P_ctrl(void) {

    while (1) {

		// Guardamos los valores actuales
        unsigned int luz1_previa = luz1;
        unsigned int luz2_previa = luz2;
        unsigned int luz3_previa = luz3;

        unsigned int luz1_m_pr = luz1_man;
        unsigned int luz2_m_pr = luz2_man;
        unsigned int luz3_m_pr = luz3_man;

        // Determinacion automatica de la intensidad de las luces

        if (lumenes <= 341) { // Segun la luz exterior
            // Luz baja (noche), si hay gente enciende
            switch (hab1) { // Segun el n. de personas
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
        } else if (lumenes <= 682) {
            // Luz media (tarde), si hay mas de una persona enciende 1 luz
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
            // Luz alta (dia), no enciende nada
            luz1 = 0;
            luz2 = 0;
            luz3 = 0;
        }

        // Ahora se calcula teniendo en cuenta los comandos manuales
        // impartidos a traves de los botones en la placa 1

        // Al enviar un numero sin signo, hemos adoptado como medida un rango
        // de 0 a 4 para los valores manuales, donde:
        // El 0 = -2 (Apaga dos luces)
        // El 1 = -1 (Apaga una luz)
        // El 2 = 0	 (No hacer nada)
        // El 3 = 1  (Enciende una luz)
        // El 4 = 2  (Enciende dos luces)
		
		// Para cada luz, se mira el valor manual deseado y se adapta
		// Los 'if's miran que los valores queden dentro del rango [0,4]
		
		// Si se quiere encender o apagar más luces de las que hay,
		// entonces se fija el valor de luz a 2 (max.) o 0 (min.) respectivamente

        // Luz 1
        switch (((int) luz1_man) - 2) {
            case -2:
                if (((int) luz1) - 2 >= 0) {
                    luz1 = luz1 - 2;
                } else {
                    luz1 = 0;
                }
                break;
            case -1:
                if (((int) luz1) - 1 >= 0) {
                    luz1 = luz1 - 1;
                } else {
                    luz1 = 0;
                }
                break;
            case 1:
                if (((int) luz1) + 1 <= 2) {
                    luz1 = luz1 + 1;
                } else {
                    luz1 = 2;
                }
                break;
            case 2:
                if (((int) luz1) + 2 <= 2) {
                    luz1 = luz1 + 2;
                } else {
                    luz1 = 2;
                }
                break;
        }
        
        // Luz 2
        switch (((int) luz2_man) - 2) {
            case -2:
                if (((int) luz2) - 2 >= 0) {
                    luz2 = luz2 - 2;
                } else {
                    luz2 = 0;
                }
                break;
            case -1:
                if (((int) luz2) - 1 >= 0) {
                    luz2 = luz2 - 1;
                } else {
                    luz2 = 0;
                }
                break;
            case 1:
                if (((int) luz2) + 1 <= 2) {
                    luz2 = luz2 + 1;
                } else {
                    luz2 = 2;
                }
                break;
            case 2:
                if (((int) luz2) + 2 <= 2) {
                    luz2 = luz2 + 2;
                } else {
                    luz2 = 2;
                }
                break;
        }
        
        // Luz 3
        switch (((int) luz3_man) - 2) {
            case -2:
                if (((int) luz3) - 2 >= 0) {
                    luz3 = luz3 - 2;
                } else {
                    luz3 = 0;
                }
                break;
            case -1:
                if (((int) luz3) - 1 >= 0) {
                    luz3 = luz3 - 1;
                } else {
                    luz3 = 0;
                }
                break;
            case 1:
                if (((int) luz3) + 1 <= 2) {
                    luz3 = luz3 + 1;
                } else {
                    luz3 = 2;
                }
                break;
            case 2:
                if (((int) luz3) + 2 <= 2) {
                    luz3 = luz3 + 2;
                } else {
                    luz3 = 2;
                }
                break;
        }

        // Si se ha producido algun cambio, dile al CAN de enviar la info actualizada
        if (luz1 != luz1_previa || luz2 != luz2_previa || luz3 != luz3_previa ||
                luz1_man != luz1_m_pr || luz2_man != luz2_m_pr || luz3_man != luz3_m_pr) {
            OSSetEFlag(EFLAG_P_CTRL, DESPIERTA_TX);
        }

        OSSignalBinSem(BINSEM_CTRL_LCD); // Senyala al LCD que puede actualizarse

        OS_Delay(1);
    }

}

/**
 * Muestra en el LCD:
 * - Los lumenes del exterior
 * - Los lumenes en cada habitacion
 */
void AP_act_LCD(void) {
    // Calcula la intensidad actual de lumenes y la muestra
    // lums1..3

    OStypeMsgP msg_recibido;	// Variable para mensaje recibido en Mbox

    while (1) {

        // Espera a que la tarea de CAN indique que hay que actualizar
        OS_WaitMsg(MSG_RX_LCD, &msg_recibido, OSNO_TIMEOUT);

        // Espera a que se hayan calculado los valores de luz
        OS_WaitBinSem(BINSEM_CTRL_LCD, OSNO_TIMEOUT);

        LCDClear();	// Limpia la pantalla
        char linea1 [20];
        char linea2 [20];

		// Cada luz encendida suma 1000 lumenes
        lums1 = luz1 * LUMS_STEP;
        lums2 = luz2 * LUMS_STEP;
        lums3 = luz3 * LUMS_STEP;

        //sprintf(linea1, "EX:%u H1:%u", lumenes, lums1);
        //sprintf(linea2, "H2:%u H3:%u", lums2, lums3);

        // DEBUG
        //sprintf(linea1, "EX:%u H1:%u", lumenes, luz1_man);
        //sprintf(linea2, "H2:%u H3:%u", luz2_man, luz3_man);
        sprintf(linea1, "HL %u %u %u", lums1, lums2, lums3);
        sprintf(linea2, "Man %d %d %d", (int) luz1_man, (int) luz2_man, (int) luz3_man);


        LCDMoveFirstLine();
        LCDPrint(linea1);
        LCDMoveSecondLine();
        LCDPrint(linea2);

        IFS0bits.ADIF = 0; // Reset interrupt

        //unsigned int i;
        //for (i = 0; i < 5; i++) Delay15ms();

        OS_Yield();
    }

}

/**
 * Envia:
 * - Los lumenes de luz exterior
 * - El nivel de luz deseado en cada hab. (manual)
 */
void AP_tx_datos(void) {
    // Llamado despues de P_ctrl
    // Envia los valores actualizados de lumenes y luces

    // Cada unsigned char es 1 byte
    // Cada unsigned int son 2 bytes (hasta 65.535, luego 4 bytes)

    /*
     SISTEMA DE IDENTIFICADORES
     *
     * SID = 0x0001 (1)      --> Mensaje recibido desde la placa 1
     * SID = 0x0002 (2)      --> Enviar luz1..3
	 * SID = 0x0010 - 0x0030 --> Comandos impartidos por UART
     *
     */

    static unsigned char mensaje_mbox_LCD = 1;

    while (1) {

        // Espera a que la tarea de control senyales que hay nuevos datos para enviar
        OS_WaitEFlag(EFLAG_P_CTRL, DESPIERTA_TX, OSEXACT_BITS, OSNO_TIMEOUT);
        OSClrEFlag(EFLAG_P_CTRL, DESPIERTA_TX); // Limpia el flag y ejecuta la rutina

        unsigned char data_buffer[3];
        unsigned int ID = 0x0002;
        unsigned char tamDatos = sizeof (data_buffer);

        // Evio informaciones
        if (CANtxInt) { // Si se puede enviar
            CANclearTxInt(); // Clear del interrupt de transmision CAN

            data_buffer[0] = (unsigned char) luz1;
            data_buffer[1] = (unsigned char) luz2;
            data_buffer[2] = (unsigned char) luz3;

            CANsendMessage(ID, data_buffer, tamDatos);
        }

        // Avisa al LCD que puede actualizarse y esperar al semaforo de control
        OSSignalMsg(MSG_RX_LCD, (OStypeMsgP) & mensaje_mbox_LCD);

        OS_Yield();
    }

}

/******************************************************************************/
/* Interrupts                                                                 */
/******************************************************************************/


/******************************************************************************/
/* CAN ISR - Recepcion datos                                                  */
/* Recibe info de num. personas y luz deseada (manual) en cada habitacion     */
/* Tambien recibe el numero de lumenes exteriores                             */
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
            luz1_man = (unsigned int) rxMsgData[5];
            luz2_man = (unsigned int) rxMsgData[6];
            luz3_man = (unsigned int) rxMsgData[7];

            lumenes = (unsigned int) rxMsgData[1] << 8; // lum_l
            lumenes += (unsigned int) rxMsgData[0];		// Se suma lum_h

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

    //char linea1[20]; // Mensaje a ensenyar en la primera linea de LCD (DEBUG)
    //sprintf(linea1, "Recibido de UART");

    while (DataRdyUART1()) { // Hasta que haya datos
        c = ReadUART1(); // Leemos el caracter
        (*(datos)++) = c; // Lo ponemos en el string rx_uart (var. global)
    }

    if (c == '\r' || c == '\n') { // Si se detecta un Enter

        //        LCDClear(); // Limpio pantalla
        //
        rx_uart[strcspn(rx_uart, "\r\n")] = 0; // Elimino los \r y \n del string
        //
        //        // Escribo en pantalla
        //        LCDMoveFirstLine();
        //        LCDPrint(linea1);
        //        LCDMoveSecondLine();
        //        LCDPrint(rx_uart);
        //
        //        IFS0bits.ADIF = 0; // Reset interrupt del LCD

        checkComando();

        //        // Que quede en la pantalla durante 1 seg.
        //        unsigned int i;
        //        for (i = 0; i < 200; i++) {
        //            Delay5ms();
        //        }
        //        LCDClear();
        //        IFS0bits.ADIF = 0; // Reset interrupt del LCD

        strncpy(rx_uart, "", sizeof (rx_uart)); // Reset string a vacio
        datos = rx_uart; // Reset puntero a principio

    }


}

/******************************************************************************/
/* Timer ISR - Calculo intensidad                                             */
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

    CANinit(NORMAL_MODE, TRUE, TRUE, 0, 0);

    UARTConfig();


    // =========================
    // Create Salvo structures
    // =========================
    // Init Salvo
    OSInit();

    // Create tasks (name, tcb, priority) and push them to ELIGIBLE STATE
    // From 1 up to OSTASKS tcbs available
    // Priorities from 0 (highest) down to 15 (lowest)

    OSCreateTask(P_ctrl, OSTCBP(1), PRIO_CTRL);
    OSCreateTask(AP_tx_datos, OSTCBP(2), PRIO_TX);
    OSCreateTask(AP_act_LCD, OSTCBP(3), PRIO_LCD);

    // Creamos herramientas de concurrencia
    OSCreateMsg(MSG_RX_LCD, (OStypeMsgP) 0);	// Mailbox
	
    //            OSTCBP(1)      eso mismo  val. inicial
    OSCreateEFlag(EFLAG_P_CTRL, OSEFCBP(1), 0x00);	// Flag

    OSCreateBinSem(BINSEM_CTRL_LCD, 0);	// Sem. binario

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
    // Activar RXint -->1 111 <-- Prioridad entre 0 y 7
    ConfigIntUART1(0x000F); // Enable RX Interrupt, highest priority


    // Config UART
    OpenUART1(UART_EN & // Enable UART
            UART_DIS_LOOPBACK &  // Disable loopback mode
            UART_NO_PAR_8BIT &   // 8bits / No parity
            UART_1STOPBIT, 		 // 1 Stop bit
            UART_TX_PIN_NORMAL & // Tx break bit normal
            UART_TX_ENABLE &	 // Enable Tx
            UART_INT_RX_CHAR & 	 // Interrupt para cada char recibido
            UART_RX_INT_EN, 	 // Enable Transmission and RX Interruptions
            BRG); // Baudrate
}

/**
 * Comprueba si el comando recibido por UART y acabado por enter
 * es valido, y si es asi, envia comandos a la placa 1 mediante CAN
 */
int checkComando() {
    char string[30];
    memset(string, '\0', sizeof (string));
    strcpy(string, rx_uart); // Copiamos el string porque strtok es destructivo
    const char * s = " "; 	 // Caracter delimitador de los tokens
    int contador = 0; 		 // Contador de cuantos tokens se crean

    char *token;
    char *args[MAX_ARGS];	   // Array para los tokens
    memset(args, '\0', sizeof (args));
    token = strtok(string, s); // Sacamos el primer token

    while (token != NULL) { // Hasta que siga habiendo o hasta 5, sacamos mas tokens
        args[contador++] = token;
        token = strtok(NULL, s);
        if (contador >= MAX_ARGS)
            break; // Si se llega al maximo de argumentos (5)
    }

    if (contador == 1) args[1] = NULL;	// Para evitar fallos

    // DEBUG
    LCDClear(); // Limpio pantalla

    char debug1[20];
    char debug2[20];
    memset(debug2, '\0', sizeof (debug2));
    sprintf(debug1, "toks num: %d", contador);

    unsigned int x;
    for (x = 0; x < contador; x++) {
        strcat(debug2, args[x]);
        strcat(debug2, " ");
    }

    // Escribo en pantalla
    LCDMoveFirstLine();
    LCDPrint(debug1);
    LCDMoveSecondLine();
    LCDPrint(debug2);

    // Que quede en la pantalla durante 1 seg.
    unsigned int i;
    for (i = 0; i < 200; i++) {
        Delay5ms();
    }

    IFS0bits.ADIF = 0; // Reset interrupt del LCD
    LCDClear();
    // FIN DEBUG


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

            return ID;

        } else if (strcmp(args[0], "turnAllOn") == 0 && args[1] != NULL) { // Se comprueba que no sea NULL el segundo argumento
            ID = 0x0011;

            int nivel = atoi(args[1]);
            // El nivel puede ir de 0 hasta maximo 2
            if (nivel >= 0 && nivel <= 2) {
                unsigned char data_buffer[2];   // Solo hay que enviar un valor, pero si no se hace asi no funciona
                data_buffer[0] = (unsigned char) atoi(args[1]);
                tamDatos = sizeof (data_buffer);

                if (CANtxInt) {
                    CANclearTxInt();
                    CANsendMessage(ID, data_buffer, tamDatos);
                }
				
                return ID;
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

        return ID;

    } else if (strcmp(args[0], "setLights") == 0) {

        if (args[1] != NULL && args[2] != NULL) {

            // atoi convierte de string a int, devuelve 0 si no se puede convertir
            // En este caso, la hab. no puede ser 0, pero el nivel de luz si
            // y no podemos saber si el 0 es por un error de conversion o porque
            // el usuario quiere poner a cero (apagar) las luces de una hab.
			
            unsigned int num_hab = (unsigned int) atoi(args[1]);
            unsigned int val_luz = (unsigned int) atoi(args[2]);

            char debug_1[20];
            char debug_2[20];
            sprintf(debug_1, "N_H: %u", (unsigned char) atoi(args[1]));
            sprintf(debug_2, "V_L: %u", (unsigned char) atoi(args[2]));

            // DEBUG
            LCDClear(); // Limpio pantalla

            // Escribo en pantalla
            LCDMoveFirstLine();
            LCDPrint(debug_1);
            LCDMoveSecondLine();
            LCDPrint(debug_2);

            IFS0bits.ADIF = 0; // Reset interrupt del LCD

            // Que quede en la pantalla durante 1 seg.
            unsigned int i;
            for (i = 0; i < 200; i++) {
                Delay5ms();
            }
            LCDClear();
            IFS0bits.ADIF = 0; // Reset interrupt del LCD

            // Si los valores son validos, enviamos los datos
            if (num_hab >= 1 && num_hab <= 3 && val_luz >= 0 && val_luz <= 2) {

                ID = 0x0030;
                unsigned char data_buffer[2];
                data_buffer[0] = (unsigned char) atoi(args[1]); // Num. habitacion
                data_buffer[1] = (unsigned char) atoi(args[2]); // Valor luces
                tamDatos = sizeof (data_buffer);

                if (CANtxInt) {
                    CANclearTxInt();
                    CANsendMessage(ID, data_buffer, tamDatos);
                }

                return ID;
            }
        }
    }
	
    return 0;
}
