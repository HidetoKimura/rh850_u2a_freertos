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
*                Interrupt Management: Create and use counting semaphore
*******************************************************************************/

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
/* U2B driver */
#include "U2B_clock.h"
#include "U2B_pin.h"

/* U2B application */
#include "U2B_TAUD_App.h"

/* FreeRTOS kernel */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define		MONPORT_N    			20
#define		MONPORT_TICK 			0	// for checking generation timing of tick interrupt
#define		MONPORT_TASK1			1	// for checking Task1 becomes Runing state
#define		MONPORT_TASK2			2	// for checking Task2 becomes Runing state

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
static SemaphoreHandle_t	Gx_counting_semaphore = NULL;

/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/
void main( void );
static void Task1_main( void * ptr_parameters );
void Intfunc_INTTAUD2I0( void );

/******************************************************************************/

/*******************************************************************************
* Function Name: main
* Description  : main function for using counting semaphore
* Arguments    : None
* Return Value : None
*******************************************************************************/
void main( void )
{
	uint8_t 	n=TAUD_UNIT;	// unit number of TAUD
	uint8_t 	m=TAUD_CH;  	// channel number of TAUDn
	uint32_t	cmp=1*(TAUD_FREQUENCY / configTICK_RATE_HZ) - 1;	// CDR value of TAUDn ch.m = 1 ticks


	/* System clock configure */
	CLK_GearUp_SystemClocks();

	/* Set monitor ports are output pin */
	PIN_InitMonitorPort( MONPORT_N );

	/* Configure TAUDn ch.m */
	Config_TAUD( n, m, cmp );

	/* Create the semaphore */
	Gx_counting_semaphore = xSemaphoreCreateCounting( 100, 0 );
	configASSERT( Gx_counting_semaphore );

	/* Create task */
	xTaskCreate( Task1_main,
	             "Task1",
	             configMINIMAL_STACK_SIZE,
	             NULL,
	             tskIDLE_PRIORITY+2,
	             NULL );

	/* TAUDn count start */
	TAUD_StartCount( TAUD_UNIT, TAUD_CH );

	/* Start the scheduler */
	vTaskStartScheduler();

	/* End of program */
	while(1){}
}

/*******************************************************************************
* Function Name: Task1_main
* Description  : main function for Task1
* Arguments    : void * ptr_parameters
* Return Value : None
*******************************************************************************/
static void Task1_main( void * ptr_parameters )
{
	( void ) ptr_parameters;
	uint32_t	count_value;


	/* This Task is implemented in an infinite loop. */
	while(1)
	{
		/* Output high level to monitor port */
		PIN_OutputHighMonitorPort( MONPORT_N, MONPORT_TASK1 );

		/* Get value of Counting Semaphore */		
		count_value = uxSemaphoreGetCount( Gx_counting_semaphore );

		/* wait until Gx_count reaches threshold */
		if( count_value <= 4 )
		{
			/* Output low pulse to monitor port */
			PIN_OutputLowMonitorPort( MONPORT_N, MONPORT_TASK1 );
			PIN_OutputHighMonitorPort( MONPORT_N, MONPORT_TASK1 );
			
			/* transit Blocked state at 1 tick */
			vTaskDelay( 1 );
		}else{
			/* Output low level to monitor port */
			PIN_OutputLowMonitorPort( MONPORT_N, MONPORT_TASK1 );
		
			/* transit Blocked state at 5 tick */
			vTaskDelay( 5 );
		}
	}
}

/*******************************************************************************
* Function Name: Intfunc_INTTAUD2I0
* Description  : unlock Task1
*                This function is called on INTTAUD2I0 interrupt handler.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void Intfunc_INTTAUD2I0( void )
{
	portBASE_TYPE x_higher_priority_task_woken = pdFALSE;
	uint16_t	rmw;
	uint32_t	count_value;


	/* Increment Counting Semaphore */
	xSemaphoreGiveFromISR( Gx_counting_semaphore, 
	                       (BaseType_t*)&x_higher_priority_task_woken );

	/* Get value of Counting Semaphore */
	count_value = uxSemaphoreGetCount( Gx_counting_semaphore );

	/* output value of Counting Semaphore */
	rmw = rPn(MONPORT_N) & ~(0xF << 4);
	rPn(MONPORT_N) = rmw | (count_value << 4);

	/* Request a yield if calling xSemaphoreGiveFromISR() caused a task to
	leave the Blocked state (which it will have done) and the task that left
	the Blocked state has a priority higher than the currently running task
	(which it will have). */
	portYIELD_FROM_ISR( x_higher_priority_task_woken );
}
