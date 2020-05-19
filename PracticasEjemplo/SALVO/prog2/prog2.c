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
#define TASK_COUNT_P		OSTCBP(1) /* task #1 */
#define TASK_SHOW_P			OSTCBP(2) /* task #2 */

// Tasks priorities
#define PRIO_COUNT			10 
#define PRIO_SHOW			10

// Binary Semaphores (number of OS EVENT)
// Recall that the number of OS event must range from 1 to OSEVENTS (defined in salvocfg.h)
#define BINSEM_UPDATE_PORT_P OSECBP(1)


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


void TaskCount (void)
{
	unsigned char i;

	while(1)
	{
		for (i=0; i < 10; i++)
			Delay15ms();

		count = (count + 1) % 64;
		if ( (count % 2) == 0 )
			OSSignalBinSem(BINSEM_UPDATE_PORT_P);

		OS_Yield();
	}
}


void TaskShow (void)
{
	unsigned char i;

	while(1)
	{
		for (i=0; i < 10; i++)
			Delay15ms();

		OS_WaitBinSem(BINSEM_UPDATE_PORT_P, OSNO_TIMEOUT);
		printNumInLED(count);
	}
}


/******************************************************************************/
/* Interrupts                                                                 */
/******************************************************************************/





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
	OSCreateTask(TaskCount, TASK_COUNT_P, PRIO_COUNT);
	OSCreateTask(TaskShow, TASK_SHOW_P, PRIO_SHOW);

	// Create binary semaphores (pointer, initial value)
	OSCreateBinSem(BINSEM_UPDATE_PORT_P, 0);

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