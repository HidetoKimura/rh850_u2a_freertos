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
*                Resource management: Gatekeeper Tasks
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
#include "queue.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define		MONPORT_N    			20
#define		MONPORT_TICK 			0	// for checking generation timing of tick interrupt
#define		MONPORT_TASK1			1	// for checking Task1 becomes Runing state
#define		MONPORT_TASK2			2	// for checking Task2 becomes Runing state
#define		MONPORT_TASKGK			3	// for checking Task2 becomes Runing state

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
QueueHandle_t	Gx_queue;
static char  	*Gptr_message[] =
{
	"Message from Task1\r\n",
	"Message from Task2\r\n",
};

/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/
void main( void );
static void Tasks_main( void * ptr_parameters );
static void GatekeeperTask_main( void *pvParameters );

/******************************************************************************/

/*******************************************************************************
* Function Name: main
* Description  : main function for using Gatekeeper
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

	/* Create queue */
	Gx_queue = xQueueCreate( 5, sizeof( char * ) );

	/* Create task */
	xTaskCreate( Tasks_main,
	             "Task1",
	             configMINIMAL_STACK_SIZE,
	             ( void * ) 0,		/* index of Gptr_message[] */
	             tskIDLE_PRIORITY+1,
	             NULL );

	xTaskCreate( Tasks_main,
	             "Task2",
	             configMINIMAL_STACK_SIZE,
	             ( void * ) 1,		/* index of Gptr_message[] */
	             tskIDLE_PRIORITY+1,
	             NULL );

	xTaskCreate( GatekeeperTask_main,
	             "Gatekeeper",
	             1000,
	             NULL,
	             tskIDLE_PRIORITY+0,
	             NULL );

	/* Start the scheduler */
	vTaskStartScheduler();

	/* End of program */
	while(1){}
}

/*******************************************************************************
* Function Name: Tasks_main
* Description  : main function for each Task
*                Send value to queue
* Arguments    : void * ptr_parameters
* Return Value : None
*******************************************************************************/
static void Tasks_main( void * ptr_parameters )
{
	uint8_t        	index;		/* index of Gptr_message[] */


	/* set index of message */
	index = (uint32_t) ptr_parameters;

	/* This Task is implemented in an infinite loop. */
	while(1)
	{
		/* output high level to monitor port of each Task */
		if( index == 0 ){
			PIN_OutputHighMonitorPort( MONPORT_N, MONPORT_TASK1 );
		}else if( index == 1 ){
			PIN_OutputHighMonitorPort( MONPORT_N, MONPORT_TASK2 );
		}
		
		/* Send message to the Queue */
		xQueueSendToBack( Gx_queue, &Gptr_message[index], portMAX_DELAY );

		/* output low level to monitor port of each Task */
		if( index == 0 ){
			PIN_OutputLowMonitorPort( MONPORT_N, MONPORT_TASK1 );
		}else if( index == 1 ){
			PIN_OutputLowMonitorPort( MONPORT_N, MONPORT_TASK2 );
		}

		vTaskDelay( 1 );
	}
}

/*******************************************************************************
* Function Name: GatekeeperTask_main
* Description  : Gatekeepper Task
* Arguments    : void * ptr_parameters
* Return Value : None
*******************************************************************************/
static void GatekeeperTask_main( void *pvParameters )
{
	char	*rx_message;


	/* This Task is implemented in an infinite loop. */
	while(1)
	{
		/* Wait for a message to arrive. */
		xQueueReceive( Gx_queue, &rx_message, portMAX_DELAY );

		/* output high level to monitor port */
		PIN_OutputHighMonitorPort( MONPORT_N, MONPORT_TASKGK );

		/* output message to COM port */
		COM_printf( "%s", rx_message );

		/* output low level to monitor port */
		PIN_OutputLowMonitorPort( MONPORT_N, MONPORT_TASKGK );
	}
}
