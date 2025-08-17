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
* File Name        : r_cg_mspi_common.c
* Version          : 1.0.140
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
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_MSPI_Start_Interrupt_MSPI3TX
* Description  : This function This function enable MSPI3 transmit interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Start_Interrupt_MSPI3TX(void)
{
    /* Clear MSPI3 transmit interrupt request and enable operation */
    INTC2.EIC268.BIT.EIRF268 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC268.BIT.EIMK268 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_MSPI_Stop_Interrupt_MSPI3TX
* Description  : This function This function disable MSPI3 transmit interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Stop_Interrupt_MSPI3TX(void)
{
    /* Disable MSPI3 transmit interrupt operation and clear request */
    INTC2.EIC268.BIT.EIMK268 = _INT_PROCESSING_DISABLED;
    INTC2.EIC268.BIT.EIRF268 = _INT_REQUEST_NOT_OCCUR;
}

/***********************************************************************************************************************
* Function Name: R_MSPI_Start_Interrupt_MSPI3RX
* Description  : This function This function enable MSPI3 receive interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Start_Interrupt_MSPI3RX(void)
{
    /* Clear MSPI3 receive interrupt request and enable operation */
    INTC2.EIC269.BIT.EIRF269 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC269.BIT.EIMK269 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_MSPI_Stop_Interrupt_MSPI3RX
* Description  : This function This function disable MSPI3 receive interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Stop_Interrupt_MSPI3RX(void)
{
    /* Disable MSPI3 receive interrupt operation and clear request */
    INTC2.EIC269.BIT.EIMK269 = _INT_PROCESSING_DISABLED;
    INTC2.EIC269.BIT.EIRF269 = _INT_REQUEST_NOT_OCCUR;
}

/***********************************************************************************************************************
* Function Name: R_MSPI_Start_Interrupt_MSPI3FE
* Description  : This function This function enable MSPI3 frame end interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Start_Interrupt_MSPI3FE(void)
{
    /* Clear MSPI3 frame end interrupt request and enable operation */
    INTC2.EIC270.BIT.EIRF270 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC270.BIT.EIMK270 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_MSPI_Stop_Interrupt_MSPI3FE
* Description  : This function This function disable MSPI3 frame end interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Stop_Interrupt_MSPI3FE(void)
{
    /* Disable MSPI3 frame end interrupt operation and clear request */
    INTC2.EIC270.BIT.EIMK270 = _INT_PROCESSING_DISABLED;
    INTC2.EIC270.BIT.EIRF270 = _INT_REQUEST_NOT_OCCUR;
}

/***********************************************************************************************************************
* Function Name: R_MSPI_Start_Interrupt_MSPI3ERR
* Description  : This function This function enable MSPI3 error interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Start_Interrupt_MSPI3ERR(void)
{
    /* Clear MSPI3 error interrupt request and enable operation */
    INTC2.EIC271.BIT.EIRF271 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC271.BIT.EIMK271 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_MSPI_Stop_Interrupt_MSPI3ERR
* Description  : This function This function disable MSPI3 error interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI_Stop_Interrupt_MSPI3ERR(void)
{
    /* Disable MSPI3 error interrupt operation and clear request */
    INTC2.EIC271.BIT.EIMK271 = _INT_PROCESSING_DISABLED;
    INTC2.EIC271.BIT.EIRF271 = _INT_REQUEST_NOT_OCCUR;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
