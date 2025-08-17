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
* Copyright (C) 2018, 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : OSTM0.c
* Component Version: 1.5.0
* Device(s)        : R7F702300BFABA
* Description      : This file implements device driver for OSTM0.
***********************************************************************************************************************/
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "OSTM0.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_OSTM0_Create
* Description  : This function initializes the OS timer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_OSTM0_Create(void)
{
    /* Disable OSTM0 operation */
    OSTM0.TT.UINT8 = _OSTM_COUNTER_STOP;
    /* Set OSTM0 control setting */
    OSTM0.CTL.UINT8 = _OSTM_INT_REQUEST_ENABLE | _OSTM_CNT_RELOAD_ENABLE | _OSTM_MODE_INTERVAL_TIMER | 
                      _OSTM_START_INTERRUPT_ENABLE;
    OSTM0.CMP.UINT32 = _OSTM0_COMPARING_COUNTER;
    OSTM0.TO.UINT8 = _OSTM_OUTPUT_LOW_LEVEL;
    OSTM0.TOE.UINT8 = _OSTM_OUTPUT_MODE_SOFTWARE;
    /* Synchronization processing */
    g_cg_sync_read = OSTM0.CTL.UINT8;
    __syncp();

    R_OSTM0_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: r_OSTM0_enable_interrupt
* Description  : This function enables OSTM0 interrupts.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_OSTM0_enable_interrupt(void)
{
    /* Clear OSTM0 interrupt request and enable operation */
    INTC2.EIC199.BIT.EIRF199 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC199.BIT.EIMK199 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: r_OSTM0_disable_interrupt
* Description  : This function disables OSTM0 interrupts.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_OSTM0_disable_interrupt(void)
{
    /* Disable OSTM0 interrupt operation and clear request */
    INTC2.EIC199.BIT.EIMK199 = _INT_PROCESSING_DISABLED;
    INTC2.EIC199.BIT.EIRF199 = _INT_REQUEST_NOT_OCCUR;
}

/***********************************************************************************************************************
* Function Name: R_OSTM0_Start
* Description  : This function enables the OS timer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_OSTM0_Start(void)
{
    /* Clear OSTM0 interrupt request and enable operation */
    r_OSTM0_enable_interrupt();
    /* Enable OSTM0 operation */
    OSTM0.TS.UINT8 = _OSTM_COUNTER_START;
}

/***********************************************************************************************************************
* Function Name: R_OSTM0_Stop
* Description  : This function stops the OS timer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_OSTM0_Stop(void)
{
    /* Disable OSTM0 operation */
    OSTM0.TT.UINT8 = _OSTM_COUNTER_STOP;
    /* Disable OSTM0 interrupt operation and clear request */
    r_OSTM0_disable_interrupt();
    /* Synchronization processing */
    g_cg_sync_read = OSTM0.TT.UINT8;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_OSTM0_Set_CompareValue
* Description  : This function sets counter value of OS timer.
* Arguments    : value -
*                    counter value
* Return Value : None
***********************************************************************************************************************/
void R_OSTM0_Set_CompareValue(uint32_t value)
{
    OSTM0.CMP.UINT32 = value;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
