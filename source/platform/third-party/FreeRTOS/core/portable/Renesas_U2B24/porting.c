/*******************************************************************************
* DISCLAIMER 
* This software is supplied by Renesas Electronics Corporation and is only  
* intended for use with Renesas products. No other uses are authorized. This  
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE  
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. 
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS  
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE  
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software. By using this software, 
* you agree to the additional terms and conditions found by accessing the  
* following link: 
* http://www.renesas.com/disclaimer 
* 
* Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.     
*******************************************************************************/
/*******************************************************************************
* File Name    : porting.c
* Version      : 1.00
* Device(s)    : RH850/U2B
* Description  : This is source file for FreeRTOS of sample program.
*                This file was diverted and modified from the FreeRTOS 
*                V202212.01 file.
*******************************************************************************/

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
/* Standard includes. */
#include <stdlib.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "U2B_OSTM.h"
#include "U2B_standby.h"
#include "U2B_interrupt.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define	OSTM_FREQUENCY	(80000000U)	/* 80MHz@Gearupped */

/* Critical nesting should be initialised to a non zero value so interrupts don't
accidentally get enabled before the scheduler is started. */
#define portINITIAL_CRITICAL_NESTING  (( StackType_t ) 10)

/* The PSW value assigned to tasks when they start to run for the first time. */
#define portPSW          

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
typedef void TCB_t;
extern volatile TCB_t * volatile pxCurrentTCB;

/* Keeps track of the nesting level of critical sections. */
volatile StackType_t usCriticalNesting = portINITIAL_CRITICAL_NESTING;

/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters );
BaseType_t xPortStartScheduler( void );
void vPortEndScheduler( void );
static void prvSetupTimerInterrupt( void );

/******************************************************************************/

/*******************************************************************************
* Function Name: pxPortInitialiseStack
* Description  : initializes the stack area at the address specified by 
*                the parameter pxTopOfStack.
*                These values are used when each task enters the Running state 
*                for the first time.
* Arguments    : ? StackType_t *pxTopOfStack:
*                      Address of top of the stack for task.
*                ? TaskFunction_t pxCode:
*                      Task function start address.
*                ? void *pvParameters:
*                      The value that is passed as the parameter to the created task
* Return Value : None
*******************************************************************************/
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
    *pxTopOfStack-- = ( StackType_t ) 0x01010101;      /* Initial Value of R1 */
    *pxTopOfStack-- = ( StackType_t ) 0x02020202;      /* Initial Value of R2 */
    *pxTopOfStack-- = ( StackType_t ) 0x04040404;      /* Initial Value of R4 */
    *pxTopOfStack-- = ( StackType_t ) 0x05050505;      /* Initial Value of R5 */
    *pxTopOfStack-- = ( StackType_t ) pvParameters;    /* Initial Value of R6 */
    *pxTopOfStack-- = ( StackType_t ) 0x07070707;      /* Initial Value of R7 */
    *pxTopOfStack-- = ( StackType_t ) 0x08080808;      /* Initial Value of R8 */
    *pxTopOfStack-- = ( StackType_t ) 0x09090909;      /* Initial Value of R9 */
    *pxTopOfStack-- = ( StackType_t ) 0x10101010;      /* Initial Value of R10 */
    *pxTopOfStack-- = ( StackType_t ) 0x11111111;      /* Initial Value of R11 */
    *pxTopOfStack-- = ( StackType_t ) 0x12121212;      /* Initial Value of R12 */
    *pxTopOfStack-- = ( StackType_t ) 0x13131313;      /* Initial Value of R13 */
    *pxTopOfStack-- = ( StackType_t ) 0x14141414;      /* Initial Value of R14 */
    *pxTopOfStack-- = ( StackType_t ) 0x15151515;      /* Initial Value of R15 */
    *pxTopOfStack-- = ( StackType_t ) 0x16161616;      /* Initial Value of R16 */
    *pxTopOfStack-- = ( StackType_t ) 0x17171717;      /* Initial Value of R17 */
    *pxTopOfStack-- = ( StackType_t ) 0x18181818;      /* Initial Value of R18 */
    *pxTopOfStack-- = ( StackType_t ) 0x19191919;      /* Initial Value of R19 */
    *pxTopOfStack-- = ( StackType_t ) 0x20202020;      /* Initial Value of R20 */
    *pxTopOfStack-- = ( StackType_t ) 0x21212121;      /* Initial Value of R21 */
    *pxTopOfStack-- = ( StackType_t ) 0x22222222;      /* Initial Value of R22 */
    *pxTopOfStack-- = ( StackType_t ) 0x23232323;      /* Initial Value of R23 */
    *pxTopOfStack-- = ( StackType_t ) 0x24242424;      /* Initial Value of R24 */
    *pxTopOfStack-- = ( StackType_t ) 0x25252525;      /* Initial Value of R25 */
    *pxTopOfStack-- = ( StackType_t ) 0x26262626;      /* Initial Value of R26 */
    *pxTopOfStack-- = ( StackType_t ) 0x27272727;      /* Initial Value of R27 */
    *pxTopOfStack-- = ( StackType_t ) 0x28282828;      /* Initial Value of R28 */
    *pxTopOfStack-- = ( StackType_t ) 0x29292929;      /* Initial Value of R29 */
    *pxTopOfStack-- = ( StackType_t ) 0x30303030;      /* Initial Value of R30 */
    *pxTopOfStack-- = ( StackType_t ) pxCode;          /* Pointer to the task entry function (R31) */
    *pxTopOfStack-- = ( StackType_t ) pxCode;          /* Pointer to the task entry function (EIPC) */
    *pxTopOfStack-- = ( StackType_t ) 0x03F38000;      /* Initial value of PSW  */
    *pxTopOfStack   = ( StackType_t ) portNO_CRITICAL_SECTION_NESTING;

    /*
     * Return a pointer to the top of the stack we have generated so this can
     * be stored in the task control block for the task.
     */
    return pxTopOfStack;
}

/*******************************************************************************
* Function Name: xPortStartScheduler
* Description  : start the first task after starting tick timer
* Arguments    : None
* Return Value : None
*******************************************************************************/
BaseType_t xPortStartScheduler( void )
{
    /* Setup the hardware to generate the tick.  Interrupts are disabled when
    this function is called. */
    prvSetupTimerInterrupt();

    /* Restore the context of the first task that is going to run. */
    vPortStart();

    /* Should not get here as the tasks are now running! */
    return pdTRUE;
}

/*******************************************************************************
* Function Name: vPortEndScheduler
* Description  : None
* Arguments    : None
* Return Value : None
*******************************************************************************/
void vPortEndScheduler( void )
{
    /* If required simply disable the tick interrupt here. */
}

/*******************************************************************************
* Function Name: prvSetupTimerInterrupt
* Description  : Sets up the timer to generate the tick interrupt
* Arguments    : None
* Return Value : None
*******************************************************************************/
static void prvSetupTimerInterrupt(void)
{
	uint8_t 		n=0;                    	/* OSTM unit */
	uint16_t 		dp=INTC_DP_INTOSTM0TINT;	/* OSTMn interrupt number */
	uint32_t		cmp;                    	/* interval time of OSTM interrupt */


	/* Release OSTMn from module standby */
	STB_ReleaseModuleStandby_Units( &rMSR_OSTM, 1 << n );

	/* Configure OSTMn interrupt */
	INTC_ConfigInterrupt( dp, INTC_NOMASK, INTC_TABLE_METHOD, 15 );

	/* Set tick period */
	cmp = (OSTM_FREQUENCY / configTICK_RATE_HZ) - 1;	/* OSTMn interrupt frequency(frequency configure by user)*/

	/* Configure and Start OSTMn */
	OSTM_ConfigStartInterval( n, cmp );
}
