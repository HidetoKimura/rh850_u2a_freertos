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
* File Name        : main_pe0.c
* Component Version: 1.0.0
* Description      : Main function for PE0 core.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "inc\common.h"
#include "shared.h"

#include "SmartConfigurator\OSTM0\OSTM0.h"
#include "SmartConfigurator\general\r_cg_macrodriver.h"
#include "drivers\stbc_iohold\r_stbc_iohold.h"
#include "thirdparty\shell\shell.h"
#include "modules\uart\r_uart.h"
#include "modules\canfd\r_canfd.h"
#include "modules\lin\r_lin.h"
#include "modules\userInput\r_userInput.h"
#include "apps\ui\r_ui.h"

/***********************************************************************************************************************
Defines
***********************************************************************************************************************/
#if defined (__ICCRH850__)
#define main main_pe0
#endif

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
static uint64_t task_time;

/***********************************************************************************************************************
* Function Name: callback_1ms
* Description  : System tick callback triggered every millisecond by OSTM timer
* Arguments    : None
* Return Value : None
* Notes       : - Used for system-wide timing and task scheduling
***********************************************************************************************************************/
#if 0
void callback_1ms(void)
{
    g_SystemStatus.RunTimeMs++;
}
#endif
/***********************************************************************************************************************
* Function Name: Pe0PeripheralInit
* Description  : Initializes core peripherals for PE0 processor
* Arguments    : None
* Return Value : None
* Notes       : - Must be called before enabling interrupts
*             : - Initializes OSTM0 timer, LIN, and CANFD interfaces
***********************************************************************************************************************/
void Pe0PeripheralInit(void)
{
    R_OSTM0_Create();    /* Initialize 1ms system timer */
//    R_LIN_Init();        /* Initialize Local Interconnect Network */
//    R_CANFD_Init();      /* Initialize CAN-FD communication */
}

/***********************************************************************************************************************
* Function Name: Pe0SystemStatusInit
* Description  : Initializes system status structure with default values
* Arguments    : None
* Return Value : None
* Notes       : - Called after reset, but not after DeepSTOP wakeup
*             : - Maintains system state information shared between cores
***********************************************************************************************************************/
void Pe0SystemStatusInit(void)
{
    /* Initialize system mode states */
    g_SystemStatus.CurrentMode = R_RESET;
    g_SystemStatus.PreviousMode = R_RESET;
    g_SystemStatus.SystemInit = R_SYSTEM_INIT;
    
    /* Clear system runtime counters */
    g_SystemStatus.ResetFlags = 0;
    g_SystemStatus.RunTimeMs = 0;        /* System uptime in milliseconds */
    g_SystemStatus.DeepSTOP_Counter = 0;   
    g_SystemStatus.CpuLoad = 0;
    
    /* Initialize subsystem status pointers */
    g_SystemStatus.LedStatus = &g_LedStatus;
    g_SystemStatus.UiStatus = &g_UiStatus;
    g_SystemStatus.SystemTest = &g_systemTest;
    g_SystemStatus.SdioStatus = &g_SdioStatus;
    g_SystemStatus.DisplayStatus = &g_DisplayStatus;
    
}

/***********************************************************************************************************************
* Function Name: main
* Description  : Main entry point for PE0 core
* Arguments    : argc - Number of command line arguments (unused)
*             : argv - Array of command line argument strings (unused)
* Return Value : Should never return
* Notes       : - Synchronizes with other cores at startup
*             : - Handles DeepSTOP recovery
*             : - Initializes peripherals and enables interrupts
*             : - Sets up UART shell interface
***********************************************************************************************************************/
#if 0
int main(int argc, char *argv[])
{
    /* Ensure multi-core synchronization */
    R_BARR_Sync(0);
     
    /* Handle reset condition detection */
    g_SystemStatus.ResetFlags = SYSCTRL.RESF.UINT32;
    SYSCTRL.RESFC.UINT32 = 0x0000F5DD;  /* Clear reset flags */

    /* Check if waking from DeepSTOP mode */
    if(g_SystemStatus.ResetFlags & 0x8000)
    {
        g_SystemStatus.PreviousMode = R_DEEPSTOP;
        R_STBC_ReleaseIoHold();         /* Release I/O pins from hold state */
    }
    else
    {
        Pe0SystemStatusInit();           /* Normal reset initialization */
        g_SystemStatus.PreviousMode = R_RESET;
    }

    /* Initialize task timestamp */
    task_time = 0;

    /* Initialize hardware and system services */
    Pe0PeripheralInit();

    /* Initialize interrupts for PE0 */  
    R_Interrupt_Initialize_ForPE0();

    /* Start system tick timer */
    R_OSTM0_Start();       

    /* Enable interrupts */
    __EI();                             

    /* Initialize user interface */
    R_UI_Init();                        
        
    /* Configure uart shell module  */
    set_read_char((int (*)(void))R_UartReceiveChar);
    set_write_char(R_UART_SendChar);
    prompt();
    
    /* should never reach this point */
    while(1);                          
}
#endif
/***********************************************************************************************************************
* Function Name: loop
* Description  : Main system task loop, called by shell handler
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void loop(void){

#if 0
    /* Check if 1ms has elapsed since last task execution */
    if(g_SystemStatus.RunTimeMs>task_time)
    {
        /* Update task timestamp */
        task_time=g_SystemStatus.RunTimeMs;
        
        /* Execute periodic UI tasks */
        R_UI_Task();             /* Handle UI state machine */
        R_UI_DisplayMenuTask();  /* Update display menu */
        R_userInput_handler();   /* Process user inputs */
    }
#endif

}
