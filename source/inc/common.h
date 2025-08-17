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
* File Name        : common.h
* Component Version: 1.0.0
* Description      : Provide common and compiler specific defines and functions. 
***********************************************************************************************************************/
#ifndef __TYPEDEF__
    #define __TYPEDEF__
    #include <stdint.h>

    #if defined (__CCRH__)
    #include "iodefine.h"
    #define DI()          __DI()
    #define EI()          __EI()
    #define HALT()        __halt()
    #define NOP()         __nop()
    
    #pragma inline_asm SNOOZE
    static void SNOOZE(void)
    {
        snooze
    }
    #pragma inline_asm sys_htonl
    static uint32_t sys_htonl(uint32_t word)
    {
        bsw r6, r10
    }
    #pragma inline_asm sys_htons
    static uint16_t sys_htons(uint16_t hword)
    {
        bsh r6, r10
    }
    
    #elif defined (__ghs__)
    #include "device.h"
    #define EI()          __asm("ei")
    #define DI()          __asm("di")
    #define NOP()         __asm("nop")
    #define HALT()        __asm("halt")
    #define __syncp()     __asm("syncp")
    #define SNOOZE()      __SNOOZE();
    asm uint32_t sys_htonl(uint32_t word)
    {
%reg word
        bsw word, r10
%mem word
        ld.w word, r6
        bsw r6, r10
%error
    }
    asm uint16_t sys_htons(uint16_t hword)
    {
%reg hword
        bsh hword, r10
%mem hword
        ld.w hword, r6
        bsh r6, r10
%error
    }

    #elif defined (__ICCRH850__)
    #include "iodefine.h"
    #include <intrinsics.h>
    #define EI()          __enable_interrupt()
    #define DI()          __disable_interrupt()
    #define NOP()         __no_operation()
    #define HALT()        __halt()
    #define __syncp()     __SYNCP()
    #define SNOOZE()       asm("snooze")
    #define sys_htonl(x)   __BSW(x)
    #define sys_htons(x)   __BSH(x)
    #else
    #error Unknown Compiler
    #endif

    #define SETBIT(x)     (1U << x)
    typedef unsigned short        MD_STATUS; // from SmartConfigurator cg_macrodriver
#endif

#include "inc\r_barr.h"

/* Key Code Enable/Disable value used to enable/disable access to write protected registers. */
#ifndef KCE_EN
#define KCE_EN  0xA5A5A501
#endif 
#ifndef KCE_DIS
#define KCE_DIS 0xA5A5A500
#endif

#ifndef __r_Error_t__
#define __r_Error_t__
typedef enum
{
  R_OK = 0u,
  R_ERROR,
  R_ERROR_NOTIFY,
  R_PARAMETER_MISSING,
  R_PARAMETER_RANGE,
  R_PARAMETER_INCORRECT,
  R_DATA_MISMATCH
} r_Error_t;   
#endif
