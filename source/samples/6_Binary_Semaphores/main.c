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
* File Name    : main.c
* Version      : 1.00
* Device(s)    : RH850/U2B
* Description  : This is source file for sample program using FreeRTOS.
*                Interrupt Management: Create and use binary semaphore
*******************************************************************************/

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "inc\common.h"
#include "shared.h"

/* U2B driver */
#include "U2B_clock.h"
#include "U2B_pin.h"

/* U2B application */
#include "U2B_TAUD_App.h"

/* FreeRTOS kernel */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "SmartConfigurator\OSTM0\OSTM0.h"
#include "SmartConfigurator\general\r_cg_macrodriver.h"
#include "drivers\stbc_iohold\r_stbc_iohold.h"
#include "thirdparty\shell\shell.h"
#include "modules\uart\r_uart.h"
#include "modules\canfd\r_canfd.h"
#include "modules\lin\r_lin.h"
#include "modules\userInput\r_userInput.h"
#include "apps\ui\r_ui.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
static uint64_t task_time;

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define		MONPORT_N    			20
#define		MONPORT_TICK 			0	// for checking generation timing of tick interrupt
#define		MONPORT_TASK1			1	// for checking Task1 becomes Runing state

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
static SemaphoreHandle_t Gx_tx_semaphore = NULL;

/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/
void main( void );
static void Task1_main( void * ptr_parameters );
void Intfunc_INTTAUD2I0( void );

/******************************************************************************/

/*******************************************************************************
* Function Name: main
* Description  : main function for using binary semaphore
* Arguments    : None
* Return Value : None
*******************************************************************************/
#if 1
void main( void )
{
	uint8_t 	n=TAUD_UNIT;	// unit number of TAUD
	uint8_t 	m=TAUD_CH;  	// channel number of TAUDn
	uint32_t	cmp=1.5*(TAUD_FREQUENCY / configTICK_RATE_HZ) - 1;	// CDR value of TAUDn ch.m = 1.5 ticks

#if 1
    /* Ensure multi-core synchronization */
    R_BARR_Sync(0);

    /* Initialize task timestamp */
    task_time = 0;

    /* Initialize hardware and system services */
    Pe0PeripheralInit();

    /* Initialize interrupts for PE0 */  
    R_Interrupt_Initialize_ForPE0();

    /* Start system tick timer */
    R_OSTM0_Start();       

    /* Enable interrupts */
//    __EI();   	

    /* System clock configure */
//	CLK_GearUp_SystemClocks();

	/* Set monitor ports are output pin */
//	PIN_InitMonitorPort( MONPORT_N );

	/* Configure TAUDn ch.m */
//	Config_TAUD( n, m, cmp );
#endif
#if 0
	
    /* Ensure multi-core synchronization */
    R_BARR_Sync(0);
     
    /* Handle reset condition detection */
    g_SystemStatus.ResetFlags = SYSCTRL.RESF.UINT32;
    SYSCTRL.RESFC.UINT32 = 0x0000F5DD;  /* Clear reset flags */

    /* Check if waking from DeepSTOP mode */
    if(g_SystemStatus.ResetFlags & 0x8000)
    {
        g_SystemStatus.PreviousMode = R_DEEPSTOP;
        R_STBC_ReleaseIoHold();         /* Release I/O pins from hold state */
    }
    else
    {
        Pe0SystemStatusInit();           /* Normal reset initialization */
        g_SystemStatus.PreviousMode = R_RESET;
    }

    /* Initialize task timestamp */
    task_time = 0;

    /* Initialize hardware and system services */
    Pe0PeripheralInit();

    /* Initialize interrupts for PE0 */  
    R_Interrupt_Initialize_ForPE0();

    /* Start system tick timer */
    R_OSTM0_Start();       

    /* Enable interrupts */
    __EI();   	
    
    /* Initialize user interface */
    R_UI_Init();                        
        
    /* Configure uart shell module  */
    set_read_char((int (*)(void))R_UartReceiveChar);
    set_write_char(R_UART_SendChar);
    prompt();

#endif	
	
	/* Create the semaphore */
	Gx_tx_semaphore = xSemaphoreCreateBinary();
	configASSERT( Gx_tx_semaphore );

	/* Create task */
	xTaskCreate( Task1_main,
	             "Task1",
	             configMINIMAL_STACK_SIZE,
	             NULL,
	             tskIDLE_PRIORITY+1,
	             NULL );

	/* Start the scheduler */
	vTaskStartScheduler();

	/* End of program */
	while(1){}
}
#endif
/*******************************************************************************
* Function Name: Task1_main
* Description  : main function for Task1
* Arguments    : void * ptr_parameters
* Return Value : None
*******************************************************************************/
static void Task1_main( void * ptr_parameters )
{
	( void ) ptr_parameters;
	static uint8_t	entry_count=0;


	/* This Task is implemented in an infinite loop. */
	while(1)
	{
		/* Output high level to monitor port */
		PIN_OutputHighMonitorPort( MONPORT_N, MONPORT_TASK1 );

		/* increment entry count of this function */
		entry_count++;

		if( (entry_count % 2 ) == 0 ){
			/* TAUDn count start */
			TAUD_StartCount( TAUD_UNIT, TAUD_CH );
		}

		/* Take Semaphore with timeout 3 ticks */
		xSemaphoreTake( Gx_tx_semaphore, 3 );

		/* Output low level to monitor port */
		PIN_OutputLowMonitorPort( MONPORT_N, MONPORT_TASK1 );

		/* wait 5 ticks */
		vTaskDelay( 5 );
	}
}

/*******************************************************************************
* Function Name: Intfunc_INTTAUD2I0
* Description  : unlock Task1
*                This function is called on INTTAUD2I0 interrupt handler.
* Arguments    : None
* Return Value : None
*******************************************************************************/

/* TAUD2 CHANNEL 0 INTERRUPT */
#if defined (__CCRH__)
#pragma interrupt Intfunc_INTTAUD2I0(enable=false, channel=400, fpu=true, callt=false)
#elif defined (__ghs__)
#pragma ghs interrupt
#elif defined (__ICCRH850__)
#pragma type_attribute=__interrupt
#else
#error Unknown Compiler
#endif

void Intfunc_INTTAUD2I0( void )
{
	portBASE_TYPE x_higher_priority_task_woken = pdFALSE;


	/* TAUDn count stop */
	TAUD_StopCount( TAUD_UNIT, TAUD_CH );

	/* set low level to TAUD2O0 */
	TAUD_DisableOutput( TAUD_UNIT, TAUD_CH );
	TAUD_SetOutputLevelLow( TAUD_UNIT, TAUD_CH );
	TAUD_EnableOutput( TAUD_UNIT, TAUD_CH );

	/* Unblock the Task1 */
	xSemaphoreGiveFromISR( Gx_tx_semaphore, (BaseType_t*)&x_higher_priority_task_woken );

	/* Request a yield if calling xSemaphoreGiveFromISR() caused a task to
	leave the Blocked state (which it will have done) and the task that left
	the Blocked state has a priority higher than the currently running task
	(which it will have). */
	portYIELD_FROM_ISR( x_higher_priority_task_woken );
}

/* OSTM0 INTERRUPT */
#if 0

#if defined (__CCRH__)
#pragma interrupt Entry_INTOSTM0TINT(enable=false, channel=199, fpu=true, callt=false)
#elif defined (__ghs__)
#pragma ghs interrupt
#elif defined (__ICCRH850__)
#pragma type_attribute=__interrupt
#else
#error Unknown Compiler
#endif

#endif

void callback_1ms(void)
{
    Intfunc_INTOSTM0TINT();
}
