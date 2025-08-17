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
#ifndef R_SHARED_H
#define R_SHARED_H
#include "modules\leds\r_led.h"
#include "apps\ui\r_ui.h"
#include "apps\systemTest\r_systemTest.h"
#include "modules\eth\r_eth.h"
#include "modules\display\r_display.h"
/***********************************************************************************************************************
Typedefs
***********************************************************************************************************************/
/* Mode definition type */
typedef enum 
{
  R_RESET,
  R_MODE1,
  R_MODE2,
  R_DEEPSTOP
}r_Modes_t;


/* Test types */

/* Ethernet Link Status */
typedef enum
{
    R_ETHERNET_LINK_DOWN,
    R_ETHERNET_LINK_UP
}r_EthLink_t;

typedef enum
{
    R_SYSTEM_INIT,
    R_SYSTEM_INIT_DONE
}r_SystemInit_t;

/* Create a new type for the system status which contains the the mode types */
typedef struct 
{
  r_Modes_t CurrentMode;
  r_Modes_t PreviousMode;
  r_SystemInit_t SystemInit;
  uint32_t  ResetFlags;
  uint32_t  RunTimeMs;
  uint32_t  DeepSTOP_Counter;
  uint32_t  CpuLoad;
  r_LedStatus_t* LedStatus;
  r_UiStatus_t* UiStatus;
  r_systemTest_t* SystemTest;
  r_SdioStatus_t* SdioStatus;
  ethernet_t* EthStatus;
  r_displayStatus_t* DisplayStatus;
}r_System_t;



/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
#if defined (__ghs__)
    #pragma ghs startdata 
    #pragma ghs section bss  = ".rbss"
    extern r_System_t g_SystemStatus;
    #pragma ghs section bss = default
    #pragma ghs enddata
#elif defined (__ICCRH850__)
    #pragma location="RETENTION_RAM.noinit"
    extern __no_init __huge r_System_t g_SystemStatus;	
#elif defined (__CCRH__)
    #pragma section r0_disp32 "RETENTION_RAM"
    extern r_System_t g_SystemStatus;
    #pragma section default
#else
    #error Unknown Compiler
#endif
    extern void r_SystemStatusInit(void);
    void r_SystemStatusSetLedStatus();
    extern uint32_t g_GRAM_ClearFlag;
    extern uint32_t ATF_Ram_area[0x8000]; /*128 KByte*/

#endif /* R_SHARED_H */
