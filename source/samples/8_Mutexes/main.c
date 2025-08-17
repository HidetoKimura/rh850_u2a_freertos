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
*                Resource management: Mutexes
*******************************************************************************/

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
/* U2B driver */
#include "U2B_clock.h"
#include "U2B_pin.h"

/* U2B application */
#include "U2B_UART_App.h"

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

#define		USE_MUTEX    				// if defined, Use Mutex for exclusive control of RLIN30.

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
SemaphoreHandle_t	Gx_mutex = NULL;

/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/
void main( void );
static void Tasks_main( void * ptr_parameters );

/******************************************************************************/

/*******************************************************************************
* Function Name: main
* Description  : main function for using mutex
* Arguments    : None
* Return Value : None
*******************************************************************************/
void main( void )
{
	/* System clock configure */
	CLK_GearUp_SystemClocks();

	/* Set monitor ports are output pin */
	PIN_InitMonitorPort( MONPORT_N );

	/* UART Init */
	InitialSettingUART();

	/* Create the mutex */
	Gx_mutex = xSemaphoreCreateMutex();

	/* Create task */
	xTaskCreate( Tasks_main,
	             "Task1",
	             configMINIMAL_STACK_SIZE,
	             "Task1 show the value",
	             tskIDLE_PRIORITY+1,
	             NULL );
	 
	xTaskCreate( Tasks_main,
	             "Task2",
	             configMINIMAL_STACK_SIZE,
	             "Task2 show the value",
	             tskIDLE_PRIORITY+1,
	             NULL );

	/* Start the scheduler */
	vTaskStartScheduler();

	/* End of program */
	while(1){}
}

/*******************************************************************************
* Function Name: Tasks_main
* Description  : Using semaphore take for mutex
* Arguments    : void * ptr_parameters
* Return Value : None
*******************************************************************************/
static void Tasks_main( void * ptr_parameters )
{
	uint8_t        	*message;	/* to hold message */
	static uint32_t	count=0;   	/* entry number of this function */


	/* set message to transmit */
	message = (uint8_t *)ptr_parameters;

	/* This Task is implemented in an infinite loop. */
	while(1)
	{
#ifdef USE_MUTEX 
		/* The call to xSemaphoreTake() will only return when the mutex has been successfully obtained. */
		xSemaphoreTake( Gx_mutex, portMAX_DELAY );
#endif 

		/* output high level to monitor port of each Task */
		if( message[4] == '1' ){
			PIN_OutputHighMonitorPort( MONPORT_N, MONPORT_TASK1 );
		}else if( message[4] == '2' ){
			PIN_OutputHighMonitorPort( MONPORT_N, MONPORT_TASK2 );
		}

		/* Increment gro*/
		count++;

		/* output message to COM port */
		COM_printf( "%s %d\r\n", message, count );

		/* output low level to monitor port of each Task */
		if( message[4] == '1' ){
			PIN_OutputLowMonitorPort( MONPORT_N, MONPORT_TASK1 );
		}else if( message[4] == '2' ){
			PIN_OutputLowMonitorPort( MONPORT_N, MONPORT_TASK2 );
		}

#ifdef USE_MUTEX 
		/* The mutex must be given back. */
		xSemaphoreGive( Gx_mutex );
#endif 

		vTaskDelay( 1 );
	}
}
