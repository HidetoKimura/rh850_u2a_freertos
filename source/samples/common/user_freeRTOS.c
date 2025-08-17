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
/* FreeRTOS kernel */
#include "FreeRTOS.h"
#include "task.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
	
/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName );
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize );
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize );
									
/******************************************************************************/

/**
 * @brief :     When malloc over flow then call this function
 * @param[out]: None
 * @param[in]:  xTask: Task has an error
 *              *pcTaskName: Task name error occurred
 * @retval:     None
 */
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
	while(1){}
}

/**
 * @brief :     When malloc fail then call this function
 * @param[out]: None
 * @param[in]:  None
 * @retval:     None
 */
void vApplicationMallocFailedHook( void )
{
	while(1){}
}

/**
 * @brief :     Extern declaration is present in RTOS file
 * @param[out]: None
 * @param[in]:  None
 * @retval:     None
 */
void vApplicationIdleHook( void )
{
	/* Monitor(); */
}

/**
 * @brief :     The application must provide an implementation of 
 *              vApplicationGetIdleTaskMemory() to provide the memory that
 *              is used by the Idle task.
 * @param[out]: None
 * @param[in]:  **ppxIdleTaskTCBBuffer: pointer of Idle task's will be stored
 *              **ppxIdleTaskStackBuffer: pointer of Idle task's stack
 *              *pulIdleTaskStackSize: the size of the array pointed
 * @retval:     None
 */
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
	/* If the buffers to be provided to the Idle task are declared inside this
	 * function then they must be declared static - otherwise they will be 
	 * allocated on the stack and so not exists after this function exits. */
	static StaticTask_t xIdleTaskTCB;
	static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

	/* Pass out a pointer to the StaticTask_t structure in which the Idle
	 * task's state will be stored. */
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

	/* Pass out the array that will be used as the Idle task's stack. */
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;

	/* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
	 * Note that, as the array is necessarily of type StackType_t,
	 * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

#if ( configSUPPORT_STATIC_ALLOCATION == 1 )
#ifdef configTIMER_TASK_STACK_DEPTH
/**
 * @brief :     The application must provide an implementation of 
 *              vApplicationGetTimerTaskMemory() to provide the memory that
 *              is used by the Timer service task.
 * @param[out]: None
 * @param[in]:  **ppxIdleTaskTCBBuffer: pointer of Timer task's will be stored
 *              **ppxIdleTaskStackBuffer: pointer of Timer task's stack
 *              *pulIdleTaskStackSize: the size of the array pointed
 * @retval:     None
 */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
	/* If the buffers to be provided to the Timer task are declared inside this
	function then they must be declared static - otherwise they will be
	 allocated on the stack and so not exists after this function exits. */
	static StaticTask_t xTimerTaskTCB;
	static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

	/* Pass out a pointer to the StaticTask_t structure in which the Timer
	task's state will be stored. */
	*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

	/* Pass out the array that will be used as the Timer task's stack. */
	*ppxTimerTaskStackBuffer = uxTimerTaskStack;

	/* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
	Note that, as the array is necessarily of type StackType_t,
	configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
#endif /* configTIMER_TASK_STACK_DEPTH */
#endif /* configSUPPORT_STATIC_ALLOCATION == 1 */
