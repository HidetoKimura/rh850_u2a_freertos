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
*                Queue management: Using a queue
*******************************************************************************/

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
/* U2B driver */
#include "U2B_clock.h"
#include "U2B_pin.h"

/* FreeRTOS kernel */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define		MONPORT_N    			20
#define		MONPORT_TICK 			0	// for checking generation timing of tick interrupt
#define		MONPORT_TASK1			1	// for checking Task1 becomes Runing state
#define		MONPORT_TASK2			2	// for checking Task2 becomes Runing state
#define		MONPORT_TASK3			3	// for checking Task3 becomes Runing state

#define		QUEUE_DATA_TASK2	(0x5A5A5A5A)
#define		QUEUE_DATA_TASK3	(0xA5A5A5A5)

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
/* The queue used by both tasks. */
static QueueHandle_t Gx_queue = NULL;

/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/
void main( void );
static void Task1_main( void * ptr_parameters );
static void Task2_main( void * ptr_parameters );
static void Task3_main( void * ptr_parameters );

/******************************************************************************/

/*******************************************************************************
* Function Name: main
* Description  : main function for using a queue
* Arguments    : None
* Return Value : None
*******************************************************************************/
void main( void )
{
	/* System clock configure */
	CLK_GearUp_SystemClocks();

	/* Set monitor ports are output pin */
	PIN_InitMonitorPort( MONPORT_N );

	/* Create the queue */
	Gx_queue = xQueueCreate( 1, sizeof( uint32_t ) );

	/* Create task */
	xTaskCreate( Task1_main,
	             "Task1",
	             configMINIMAL_STACK_SIZE,
	             NULL,
	             tskIDLE_PRIORITY+3,
	             NULL );

	xTaskCreate( Task2_main,
	             "Task2",
	             configMINIMAL_STACK_SIZE,
	             NULL,
	             tskIDLE_PRIORITY+2,
	             NULL );

	xTaskCreate( Task3_main,
	             "Task3",
	             configMINIMAL_STACK_SIZE,
	             NULL,
	             tskIDLE_PRIORITY+1,
	             NULL );

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
	TickType_t	ux_received_value;	/* Declare the variable that will hold the values received from the queue. */


	/* This Task is implemented in an infinite loop. */
	while(1)
	{
		/* Output high level to monitor port before receiving Queue */
		PIN_OutputHighMonitorPort( MONPORT_N, MONPORT_TASK1 );

		/* Receive data from the queue. */
		xQueueReceive( Gx_queue, &ux_received_value, portMAX_DELAY );

		/* Check receive data */
		if( ux_received_value == QUEUE_DATA_TASK2 )
		{
			/* Output low level to monitor port of Task2 */
			PIN_OutputLowMonitorPort( MONPORT_N, MONPORT_TASK2 );
			ux_received_value = 0;
		}
		else if(ux_received_value == QUEUE_DATA_TASK3)
		{
			/* Output low level to monitor port of Task3 */
			PIN_OutputLowMonitorPort( MONPORT_N, MONPORT_TASK3 );
			ux_received_value = 0;
		}

		/* Output low level to monitor port of Task1 */
		PIN_OutputLowMonitorPort( MONPORT_N, MONPORT_TASK1 );
	}
}

/*******************************************************************************
* Function Name: Task2_main
* Description  : main function for Task2
* Arguments    : void * ptr_parameters
* Return Value : None
*******************************************************************************/
static void Task2_main( void * ptr_parameters )
{
	( void ) ptr_parameters;
	const uint32_t	u32_value_to_send = QUEUE_DATA_TASK2;


	while(1)
	{ 
		/* Output high level to monitor port before calling vTaskDelay */
		PIN_OutputHighMonitorPort( MONPORT_N, MONPORT_TASK2 );

		/* Sends data every 4 ticks. */
		vTaskDelay( 4 );

		/* Send the value to the queue. */
		xQueueSend( Gx_queue, &u32_value_to_send, 0U );
	}
}

/*******************************************************************************
* Function Name: Task3_main
* Description  : main function for Task3
* Arguments    : void * ptr_parameters
* Return Value : None
*******************************************************************************/
static void Task3_main( void * ptr_parameters )
{
	( void ) ptr_parameters;
	const uint32_t	u32_value_to_send = QUEUE_DATA_TASK3;


	while(1)
	{
		/* Output high level to monitor port before calling vTaskDelay */
		PIN_OutputHighMonitorPort( MONPORT_N, MONPORT_TASK3 );

		/* Sends data every 4 ticks */
		vTaskDelay( 4 );

		/* Send the value to the queue. */
		xQueueSend( Gx_queue, &u32_value_to_send, 0U );
	}
}
