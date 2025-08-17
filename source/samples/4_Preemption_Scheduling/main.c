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
*                task management: Save and restore context of Preemption
*                scheduling
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

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define		MONPORT_N    			20
#define		MONPORT_TICK 			0	// for checking generation timing of tick interrupt
#define		MONPORT_TASK1			1	// for checking Task1 becomes Runing state
#define		MONPORT_TASK2			2	// for checking Task2 becomes Runing state
#define		MONPORT_TASK3			3	// for checking Task3 becomes Runing state

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

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
* Description  : main function for saving and restoring context of Preemption
*                scheduling
* Arguments    : None
* Return Value : None
*******************************************************************************/
void main( void )
{
	/* System clock configure */
	CLK_GearUp_SystemClocks();

	/* Set monitor ports are output pin */
	PIN_InitMonitorPort( MONPORT_N );

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


	/* Toggle monitor port in 600us */
	for( int i = 0; i < 4000; i++ )
	{
		PIN_ToggleMonitorPort( MONPORT_N, MONPORT_TASK1 );
	}

	/* Output low level to monitor port */
	PIN_OutputLowMonitorPort( MONPORT_N, MONPORT_TASK1 );

	/* transit to blocked state for 3 ticks */
	vTaskDelay( 3 );
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


	/* toggle port in 600us */
	for( int i = 0; i < 4000; i++ )
	{
		PIN_ToggleMonitorPort( MONPORT_N, MONPORT_TASK2 );
	}

	/* Output low level to monitor port */
	PIN_OutputLowMonitorPort( MONPORT_N, MONPORT_TASK2 );

	/* transit to blocked state */
	vTaskDelay( 4 );
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


	/* This Task is implemented in an infinite loop. */
	while(1)
	{
		/* Toggle monitor port */
		PIN_ToggleMonitorPort( MONPORT_N, MONPORT_TASK3 );
	}
}
