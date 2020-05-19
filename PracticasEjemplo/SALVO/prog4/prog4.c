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
#include "delay.h"


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
#define TASK_COUNT_P			OSTCBP(1)
#define TASK_SHOW_0_P			OSTCBP(2)
#define TASK_SHOW_1_P			OSTCBP(3)
#define TASK_SHOW_2_P			OSTCBP(4)

// Tasks priorities
#define PRIO_COUNT			10 
#define PRIO_SHOW_0			10
#define PRIO_SHOW_1			10
#define PRIO_SHOW_2			10

// OS events control blocks (number of OS EVENT)
// Recall that the number of OS event must range from 1 to OSEVENTS (defined in salvocfg.h)
#define BINSEM_ENABLE_SHOW_0	OSECBP(1)

#define MSG_FOR_SHOW_1			OSECBP(2)

#define EFLAG_FOR_SHOW_2		OSECBP(3)
#define EFLAG_FOR_SHOW_2_EFCB		OSEFCBP(1)




/******************************************************************************/
/* Global Variable and macros declaration                                     */
/******************************************************************************/

unsigned char count = 0;
unsigned char numShowTasks = 3;

// Message for Task Show 1
struct structMessage
	{
		unsigned char x;
		unsigned char y;
};

typedef struct structMessage typeMessage;

// Eflag for Task Show 2 related macros
#define iniValueEventForShow2	0x00
#define eventForShow2			0b00001110
#define maskEventForShow2		0b00001111



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
	
	// IMPORTANT: note that SALVO does not preserve the value
	// of tasks' local variables when switches the context
	// Thus, if you want to preserve task local variables
	// declare them as static (they will be stored at the heap
	// instead of at the stack)
	static typeMessage messageForShow1 = { 2, 3 };

	while(1)
	{
		for (i=0; i < 10; i++)
			Delay15ms();
	
		count++;
		switch (count % numShowTasks)
		{
			case 0:
				OSSignalBinSem(BINSEM_ENABLE_SHOW_0);
				OS_Yield();
				break;

			case 1:
				OSSignalMsg(MSG_FOR_SHOW_1, (OStypeMsgP) &messageForShow1);
				OS_Yield();
				break;

			case 2:
				OSSetEFlag(EFLAG_FOR_SHOW_2, (eventForShow2 & maskEventForShow2));
				OS_Yield();
				break;

			default:
				break;
		}
	}
}


void TaskShow0 (void)
{
	unsigned char i;

	while(1)
	{
		for (i=0; i < 10; i++)
			Delay15ms();

		OS_WaitBinSem(BINSEM_ENABLE_SHOW_0, OSNO_TIMEOUT);
		toggleLED(0);
	}
}


void TaskShow1 (void)
{
	unsigned char i;

	OStypeMsgP msgP;
	typeMessage * pMessage;

	while(1)
	{
		for (i=0; i < 10; i++)
			Delay15ms();

		OS_WaitMsg(MSG_FOR_SHOW_1, &msgP, OSNO_TIMEOUT);
		
		pMessage = (typeMessage *) msgP;
		toggleLED((*pMessage).x);
		toggleLED((*pMessage).y);
	}
}



void TaskShow2 (void)
{
	unsigned char i;
	static unsigned char nextEvent;

	OStypeEFlag eFlag;

	nextEvent = 2;
	while(1)
	{
		for (i=0; i < 10; i++)
			Delay15ms();

		// Waith (ecbp, mask, options, timeout)
		// Options for waiting flag value: OSALL_BITS, OSANY_BITS, OSEXACT_BITS
			// Autosuspend task until EFLAG_FOR_SHOW_2 = XXXX 1110
		OS_WaitEFlag(EFLAG_FOR_SHOW_2, eventForShow2, OSEXACT_BITS, OSNO_TIMEOUT);
		eFlag = OSReadEFlag(EFLAG_FOR_SHOW_2);
		OSClrEFlag(EFLAG_FOR_SHOW_2, maskEventForShow2);

		toggleLED(4);

		// Just check this task has waked up due to the appropriate event
		if (eFlag == eventForShow2)
		{
			onLED(5);
		}
		else
		{
			offLED(5);
		}
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
	OSCreateTask(TaskShow0, TASK_SHOW_0_P, PRIO_SHOW_0);
	OSCreateTask(TaskShow1, TASK_SHOW_1_P, PRIO_SHOW_1);
	OSCreateTask(TaskShow2, TASK_SHOW_2_P, PRIO_SHOW_2);

	// Create binary semaphores (pointer, initial value)
	OSCreateBinSem(BINSEM_ENABLE_SHOW_0, 0);

	// Create mailbox
	OSCreateMsg(MSG_FOR_SHOW_1, (OStypeMsgP) 0);

	// Create event flag (ecbP, efcbP, initial value)
	OSCreateEFlag(EFLAG_FOR_SHOW_2, EFLAG_FOR_SHOW_2_EFCB, iniValueEventForShow2);

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