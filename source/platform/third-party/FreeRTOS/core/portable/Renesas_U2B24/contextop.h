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
; * File Name    : contextop.h
; * Version      : 1.00
; * Device(s)    : RH850/U2B
; * Description  : This is hader file for sample program using FreeRTOS.
; *                This file contains the macros for context switching.
; *******************************************************************************/

;------------------------------------------------------------------------------
;   portSAVE_CONTEXT MACRO
;   Saves the context of the remaining general purpose registers
;   and the usCriticalNesting Value of the active Task onto the task stack
;   saves stack pointer to the TCB
;------------------------------------------------------------------------------	
portSAVE_CONTEXT .macro

	; store general purpose register
$nowarning
	pushsp	r1, r2
$warning
	pushsp	r4, r31
	
	; store EIPC to stack
	stsr	0, r10, 0
	st.w	r10, -0x4[sp]
	
	; store EIPSW to stack
	stsr	1, r10, 0
	st.w	r10, -0x8[sp]

	; decrement stack pointer for previous relative access
	add 	-0xC, sp
	
	; store usCriticalNesting value to stack
	movhi	highw1(#_usCriticalNesting), r0, r12
	ld.w	loww(#_usCriticalNesting)[r12], r10
	st.w	r10, 0[sp]
	
	; store SP to top of pxCurrentTCB.pxTopOfStack
	movhi	highw1(#_pxCurrentTCB), r0, r12
	ld.w	loww(#_pxCurrentTCB)[r12], r10
	st.w	sp, 0[r10]

.endm
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
;   portRESTORE_CONTEXT MACRO
;   Gets stack pointer from the current TCB
;   Restores the context of the usCriticalNesting value and general purpose
;   registers of the selected task from the task stack
;------------------------------------------------------------------------------
portRESTORE_CONTEXT .macro

	; get stack pointer from pxCurrentTCB.pxTopOfStack
	movhi	highw1(#_pxCurrentTCB), r0, r12
	ld.w	loww(#_pxCurrentTCB)[r12], r10
	syncp
	ld.w	0[r10], sp
	
	; restore usCriticalNesting value from stack
	ld.w	0[sp], r10
	movhi	highw1(#_usCriticalNesting), r0, r12
	st.w	r10, loww(#_usCriticalNesting)[r12]
	
	; restore EIPSW from stack
	ld.w	0x4[sp], r10
	ldsr	r10, 1, 0
	
	; restore EIPC from stack
	ld.w	0x8[sp], r10		
	ldsr	r10, 0, 0
	
	; increment stack pointer for previous relative access
	add		0xC, sp
	
	; restore general purpose registers
	popsp	r4, r31
$nowarning
	popsp	r1, r2
$warning

.endm
;------------------------------------------------------------------------------
