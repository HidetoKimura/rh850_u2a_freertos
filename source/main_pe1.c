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
* File Name        : main_pe1.c
* Component Version: 1.0.0
* Description      : Main function for PE1 core.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Standard library functions */
#include "inc\common.h" /* Common definitions and functions */
#include "shared.h"     /* Shared resources between cores */
#include "modules\eth\r_eth.h" /* Ethernet module functions */

/* Redefine main function name for ICC RH850 compiler */
#if defined (__ICCRH850__)
#define main main_pe1
#endif

/* Global pointer to system status structure for PE1 core */
r_System_t*  g_pe1SysStatusPtr;

/***********************************************************************************************************************
* Function Name: Pe1SystemStatusInit
* Description : Initializes the system status for PE1 core
* Arguments   : none
* Return Value: none
***********************************************************************************************************************/
void Pe1SystemStatusInit()
{
    /* Initialize Ethernet status in system configuration */
    g_SystemStatus.EthStatus = &eth_config[0];
    /* Store system status pointer for PE1 core */
    g_pe1SysStatusPtr=&g_SystemStatus;
} 

/***********************************************************************************************************************
* Function Name: main
* Description : Main function for PE1 core
* Arguments   : int argc - Number of command line arguments
*               char *argv[] - Array of command line argument strings
* Return Value: int - Program exit code
***********************************************************************************************************************/
int main(int argc, char *argv[])
{
    /* Synchronize with other cores */
    R_BARR_Sync(0);
    
    /* Initialize PE1 system status */
    Pe1SystemStatusInit();

    /* Print startup message */
    printf("Hello World from PE1\n");
    
    /* Enable interrupts for the core */
    __EI();
    
    /* Initialize the Ethernet module */
    R_ETH_Init();
     
    /* Main processing loop */
    while(1)
    {
        /* Handle Ethernet operations */
        R_ETH_Handler();
    }
}
