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
* File Name        : 
* Component Version: 1.0.0
* Description      : 
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "inc\common.h"
#include "shared.h"

/***********************************************************************************************************************
Global variables
***********************************************************************************************************************/
#if defined (__ghs__)
    #pragma ghs startdata 
    #pragma ghs section bss  = ".rbss"
    r_System_t g_SystemStatus;	
    #pragma ghs section bss = default
    #pragma ghs enddata
#elif defined (__ICCRH850__)
    #pragma location="RETENTION_RAM.noinit"
    __no_init __huge r_System_t g_SystemStatus;	
#elif defined (__CCRH__)
    #pragma section r0_disp32 "RETENTION_RAM"
    r_System_t g_SystemStatus;	
    #pragma section default
#else
    #error Unknown Compiler
#endif

uint32_t g_GRAM_ClearFlag;
uint32_t  ATF_Ram_area[0x8000]; /*128 KByte*/



