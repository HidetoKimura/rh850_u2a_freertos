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
*                heap management: using static memory to allocate.
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

#define		TEST_SIZE    			78	// stack size for R/W test [word]

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
#pragma section static_data
static StackType_t	Gx_Task1_stack[ configMINIMAL_STACK_SIZE ];
static StaticTask_t	Gx_Task1_TCB;
static StackType_t	Gx_Task2_stack[ configMINIMAL_STACK_SIZE ];
static StaticTask_t	Gx_Task2_TCB;
#pragma section default
	
/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/
void main( void );
static void Task1_main( void * ptr_parameters );
static void Task2_main( void * ptr_parameters );
static void CompareError( void );

/******************************************************************************/

/*******************************************************************************
* Function Name: main
* Description  : main function for using static memory to allocate
* Arguments    : None
* Return Value : None
*******************************************************************************/
void main( void )
{
	/* System clock configure */
	CLK_GearUp_SystemClocks();

	/* Set monitor ports are output pin */
	PIN_InitMonitorPort( MONPORT_N );

	/* Create static task */
	xTaskCreateStatic( Task1_main,
	                   "TASK1",
	                   configMINIMAL_STACK_SIZE,
	                   NULL,
	                   tskIDLE_PRIORITY+1,
	                   &Gx_Task1_stack[0],
	                   &Gx_Task1_TCB );

	xTaskCreateStatic( Task2_main,
	                   "TASK2",
	                   configMINIMAL_STACK_SIZE,
	                   NULL,
	                   tskIDLE_PRIORITY+1,
	                   &Gx_Task2_stack[0],
	                   &Gx_Task2_TCB );

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
	volatile uint32_t	variable_in_task1[TEST_SIZE];


	/* This Task is implemented in an infinite loop. */
	while(1)
	{
		/* Toggle monitor port */
		PIN_ToggleMonitorPort( MONPORT_N, MONPORT_TASK1 );

		/* Set arbitrary value to stack arae */
		for( int i=0; i < TEST_SIZE; i++ )
		{
			variable_in_task1[i] = 0x11111100 | i;
		}

		/* check write value */
		for( int i=0; i < TEST_SIZE; i++ )
		{
			if( variable_in_task1[i] != (0x11111100 | i) )
			{
				/* if unmatched, the monitor port will stop toggling */
				CompareError();
			}
		}
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
	volatile uint32_t	variable_in_task2[TEST_SIZE];


	/* This Task is implemented in an infinite loop. */
	while(1)
	{
		/* Toggle monitor port */
		PIN_ToggleMonitorPort( MONPORT_N, MONPORT_TASK2 );

		/* Set arbitrary value to stack arae */
		for( int i=0; i < TEST_SIZE; i++ )
		{
			variable_in_task2[i] = 0x22222200 | i;
		}

		/* check write value */
		for( int i=0; i < TEST_SIZE; i++ )
		{
			if( variable_in_task2[i] != (0x22222200 | i) )
			{
				/* if unmatched, the monitor port will stop toggling */
				CompareError();
			}
		}
	}
}

/*******************************************************************************
* Function Name: CompareError
* Description  : error proccesing
* Arguments    : None
* Return Value : None
*******************************************************************************/
static void CompareError( void )
{
	while( 1 ){}
}
