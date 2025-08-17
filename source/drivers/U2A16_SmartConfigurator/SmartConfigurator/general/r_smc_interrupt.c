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
* File Name        : r_smc_interrupt.c
* Version          : 1.4.0
* Device(s)        : R7F702300BFABA
* Description      : None
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
#include "r_smc_interrupt.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
void R_Interrupt_Create(void)
{

}

void INTETNB0DATA_enable_interrupt(void)
{
    /* Clear INTETNB0DATA request and enable operation */
    INTC2.EIC645.BIT.EIRF645 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC645.BIT.EIMK645 = _INT_PROCESSING_ENABLED;
}

void INTETNB0DATA_disable_interrupt(void)
{
    /* Disable INTETNB0DATA operation and clear request */
    INTC2.EIC645.BIT.EIMK645 = _INT_PROCESSING_DISABLED;
    INTC2.EIC645.BIT.EIRF645 = _INT_REQUEST_NOT_OCCUR;
}

void INTETNB0ERR_enable_interrupt(void)
{
    /* Clear INTETNB0ERR request and enable operation */
    INTC2.EIC646.BIT.EIRF646 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC646.BIT.EIMK646 = _INT_PROCESSING_ENABLED;
}

void INTETNB0ERR_disable_interrupt(void)
{
    /* Disable INTETNB0ERR operation and clear request */
    INTC2.EIC646.BIT.EIMK646 = _INT_PROCESSING_DISABLED;
    INTC2.EIC646.BIT.EIRF646 = _INT_REQUEST_NOT_OCCUR;
}

void INTETNB0MNG_enable_interrupt(void)
{
    /* Clear INTETNB0MNG request and enable operation */
    INTC2.EIC647.BIT.EIRF647 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC647.BIT.EIMK647 = _INT_PROCESSING_ENABLED;
}

void INTETNB0MNG_disable_interrupt(void)
{
    /* Disable INTETNB0MNG operation and clear request */
    INTC2.EIC647.BIT.EIMK647 = _INT_PROCESSING_DISABLED;
    INTC2.EIC647.BIT.EIRF647 = _INT_REQUEST_NOT_OCCUR;
}

void INTETNB0MAC_enable_interrupt(void)
{
    /* Clear INTETNB0MAC request and enable operation */
    INTC2.EIC648.BIT.EIRF648 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC648.BIT.EIMK648 = _INT_PROCESSING_ENABLED;
}

void INTETNB0MAC_disable_interrupt(void)
{
    /* Disable INTETNB0MAC operation and clear request */
    INTC2.EIC648.BIT.EIMK648 = _INT_PROCESSING_DISABLED;
    INTC2.EIC648.BIT.EIRF648 = _INT_REQUEST_NOT_OCCUR;
}
