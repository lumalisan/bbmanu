/******************************************************************************/
/*                                                                            */
/*  Description:                                                              */
/*                                                                            */
/*  Author:                                                                   */
/*                                                                            */
/******************************************************************************/

#include <p30f4011.h>
#include <stdio.h>
#include <salvo.h>

#include <string.h>
#include <stdlib.h>


#include "libLEDs.h"
#include "libTIMER.h"


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


// Tasks TCBs
#define TASK_BLINK_P 		OSTCBP(1) /* task #3 */

// Tasks priorities
#define PRIO_BLINK			2
 

/******************************************************************************/
/* Global Variable and macros declaration                                     */
/******************************************************************************/

unsigned char count = 0;

/******************************************************************************/
/* Procedures declaration                                                     */
/******************************************************************************/


/******************************************************************************/
/* TASKS declaration and implementation                                       */
/******************************************************************************/

 /* Task states

	DESTROYED / uninitalized
	STOPPED
	WAITING
	DELAYED
	ELIGIBLE /READY
	RUNNING

*/


void TaskBlink( void )
{
	unsigned char i;
	while (1)
	{
		toggleLED(0);
		for (i=0; i < 10; i++)
			Delay15ms();

		OS_Delay(1);
	}
}



/******************************************************************************/
/* Interrupts                                                                 */
/******************************************************************************/

void _ISR _T1Interrupt(void){
   
    TimerClearInt();

	OSTimer();
}




/******************************************************************************/
/* Main                                                                       */
/******************************************************************************/

int main (void)
{

	// ===================
	// Init peripherals
	// ===================
	initLEDs();

	// =========================
	// Create Salvo structures
	// =========================
	OSInit();

	// Create tasks (name, tcb, priority) and push them to ELIGIBLE STATE
	// From 1 up to OSTASKS tcbs available
	// Priorities from 0 (highest) down to 15 (lowest)
	OSCreateTask(TaskBlink, TASK_BLINK_P, PRIO_BLINK);

	// =============================================
	// Enable peripherals that trigger interrupts
	// =============================================
	Timer1Init(TIMER_PERIOD_FOR_250ms,TIMER_PSCALER_FOR_250ms, 4); // Timer expires every 250 ms
	Timer1Start();

	// =============================================
	// Enter multitasking envinronment
	// =============================================
	while (1)
	{
		OSSched();
	}

}


/******************************************************************************/
/* Procedures implementation                                                  */
/******************************************************************************/