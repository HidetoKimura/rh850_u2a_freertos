/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : r_timer.h
* Component Version: 1.0
* Description      : Header file for r_timer.c.
***********************************************************************************************************************/
#ifndef R_TIMER_H
#define R_TIMER_H

#include "inc\common.h"

/***********************************************************************************************************************
Defines
***********************************************************************************************************************/
#define R_SYSTIMER_USECOND     80u
#define R_SYSTIMER_MSECOND     80000u
#define R_SYSTIMER_10MSECOND   800000u
#define R_SYSTIMER_50MSECOND   4000000u
#define R_SYSTIMER_100MSECOND  8000000u
#define R_SYSTIMER_MS(x)  (80000u*x)

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
void R_SysTimer_Init(void);
r_Error_t R_SysTimer_usWait(uint32_t useconds);
r_Error_t R_SysTimer_msWait(uint32_t mseconds);
uint64_t R_SysTimer_Read(void);

#endif

