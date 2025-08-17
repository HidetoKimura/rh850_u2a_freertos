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
* File Name    : FreeRTOSConfig.h
* Version      : 1.00
* Device(s)    : RH850/U2B
* Description  : This is configuration file for FreeRTOS of sample program.
*                This file was diverted and modified from the FreeRTOS 
*                V202212.01 file.
*******************************************************************************/

#ifndef FREERTOS_CONFIG_H
#define	FREERTOS_CONFIG_H


/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 -----------------------------------------------------------*/
#define	configUSE_PREEMPTION            			1

#define	configUSE_IDLE_HOOK             			1
#define	configUSE_TICK_HOOK             			0
#define	configTICK_RATE_HZ              			( ( TickType_t ) 1000 )
#define	configMAX_PRIORITIES            			4
#define	configMINIMAL_STACK_SIZE        			( ( unsigned short ) 128 )
#define	configMAX_TASK_NAME_LEN         			10 
#define	configUSE_TRACE_FACILITY        			0
#define	configUSE_16_BIT_TICKS          			0
#define	configIDLE_SHOULD_YIELD         			0
#define	configUSE_CO_ROUTINES           			0
#define	configUSE_MUTEXES               			1
#define	configCHECK_FOR_STACK_OVERFLOW  			2
#define	configUSE_RECURSIVE_MUTEXES     			1
#define	configQUEUE_REGISTRY_SIZE       			0
#define	configUSE_COUNTING_SEMAPHORES   			1
#define	configUSE_MALLOC_FAILED_HOOK    			1
#define	configUSE_QUEUE_SETS            			0

#define	configSUPPORT_STATIC_ALLOCATION 			0
#define	configSUPPORT_DYNAMIC_ALLOCATION			1

/* Co-routine definitions. */
#define	configUSE_CO_ROUTINES           			0
#define	configMAX_CO_ROUTINE_PRIORITIES 			2
#define	configHEAP_CLEAR_MEMORY_ON_FREE 			1

/* Software timer definitions. */
#define	configUSE_TIMERS                			1
#define	configTIMER_TASK_PRIORITY       			( configMAX_PRIORITIES - 1 )
#define	configTIMER_QUEUE_LENGTH        			5
#define	configTIMER_TASK_STACK_DEPTH    			( configMINIMAL_STACK_SIZE * 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define	INCLUDE_vTaskPrioritySet        			1
#define	INCLUDE_uxTaskPriorityGet       			1
#define	INCLUDE_vTaskDelete             			1
#define	INCLUDE_vTaskCleanUpResources   			0
#define	INCLUDE_vTaskSuspend            			1
#define	INCLUDE_vTaskDelayUntil         			1
#define	INCLUDE_vTaskDelay              			1
#define	INCLUDE_eTaskGetState           			1

/* This IAR workspace contains several different projects - each of which
is targeted at a different device variant.  The definitions past this point
are dependent on the variant being used. */
#define	configTOTAL_HEAP_SIZE           			( (size_t ) ( 8*1024 ) )
#define	configCPU_CLOCK_HZ              			( ( unsigned long ) 400000000 )

#endif /* FREERTOS_CONFIG_H */
