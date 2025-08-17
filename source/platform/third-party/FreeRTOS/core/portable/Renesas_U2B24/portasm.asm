; /*******************************************************************************
; * DISCLAIMER 
; * This software is supplied by Renesas Electronics Corporation and is only  
; * intended for use with Renesas products. No other uses are authorized. This  
; * software is owned by Renesas Electronics Corporation and is protected under 
; * all applicable laws, including copyright laws. 
; * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
; * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
; * LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE  
; * AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. 
; * TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS  
; * ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE  
; * FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
; * ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
; * BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
; * Renesas reserves the right, without notice, to make changes to this software 
; * and to discontinue the availability of this software. By using this software, 
; * you agree to the additional terms and conditions found by accessing the  
; * following link: 
; * http://www.renesas.com/disclaimer 
; * 
; * Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.     
; *******************************************************************************/
; /*******************************************************************************
; * File Name    : portasm.asm
; * Version      : 1.00
; * Device(s)    : RH850/U2B
; * Description  : This is source file for sample program using FreeRTOS.
; *                This file contains functions that involve task switching.
; *                This file was diverted and modified from the FreeRTOS 
; *                V202212.01 file.
; *******************************************************************************/

; /******************************************************************************/
; /*                              INCLUDE FILES                                 */
; /******************************************************************************/
$include "contextop.h"

; /******************************************************************************/
; /*                     EXPORTED TYPES and DEFINITIONS                         */
; /******************************************************************************/
    ; for monitor port
	aPSR20	.set	0xFFD90504	; address of PSR20

; /******************************************************************************/
; /*                                FUNCTIONS                                   */
; /******************************************************************************/

; /*******************************************************************************
; * Function Name: _vPortStart
; * Description  :  Restore the context of the first task that is going to run.
; * Arguments    : None
; * Return Value : None
; * Call         : vPortStart
; *******************************************************************************/
	.align 2
	.public _vPortStart
_vPortStart:
	; Initerrupt disable to prevent unintended interrupts from occurring 
	di
	
	; Restore initial value of context
	portRESTORE_CONTEXT
	
	; Return to interrupt enable
	ei
	
	jmp	[lp]

; /*******************************************************************************
; * Function Name: _Intfunc_INTOSTM0TINT
; * Description  :  Port Yield function to check for a Task switch 
; *                 in the cooperative and preemptive mode
; * Arguments    : None
; * Return Value : None
; * Call         : vPortYield
; *******************************************************************************/
	.align 2
	.public _vPortYield
_vPortYield: 
	; Initerrupt disable to prevent unintended interrupts from occurring 
	di
	
	; Save the context of the current task.
	portSAVE_CONTEXT
	
	; Call the scheduler.
	jarl	_vTaskSwitchContext, lp
	
	; Restore the context of whichever task the  scheduler decided should run.
	portRESTORE_CONTEXT
	
	; Return to interrupt enable
	ei

	eiret

; /*******************************************************************************
; * Function Name: _Intfunc_INTOSTM0TINT
; * Description  :  Perform the necessary steps of the Tick Count Increment and 
; *                 Task Switch depending on the chosen kernel configuration
; * Arguments    : None
; * Return Value : None
; * Call         : ISR
; *******************************************************************************/
	.align 2
	.public _Intfunc_INTOSTM0TINT
_Intfunc_INTOSTM0TINT:
	; Output high level to monitor port
	mov 	0x00010001, r10
	st.w	r10, aPSR20[r0]
	
	; Save the context of the current task.
	portSAVE_CONTEXT
	
	; Call the timer tick function.
	jarl	_xTaskIncrementTick, lp
	
	; Call the scheduler.
	jarl	_vTaskSwitchContext, lp
	
	; Restore the context of whichever task the scheduler decided should run
	portRESTORE_CONTEXT
	
	; Output low level to monitor port
	mov 	0x00010000, r10
	st.w	r10, aPSR20[r0]
	
	eiret

; /*******************************************************************************
; * Function Name: _trap_0
; * Description  :  Execute trap 0 instruction
; * Arguments    : None
; * Return Value : None
; * Call         : ISR
; *******************************************************************************/
	.align 2
	.public _trap_0
_trap_0:
	trap	0
	
	jmp	[lp]

