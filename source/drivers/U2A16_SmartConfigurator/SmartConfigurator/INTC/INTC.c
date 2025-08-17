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
* File Name        : INTC.c
* Component Version: 1.5.0
* Device(s)        : R7F702300BFABA
* Description      : This file implements device driver for INTC.
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
#include "INTC.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_INTC_Create
* Description  : This function initializes the INTC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC_Create(void)
{
    /* Set INTP4 pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(3U);
    PORT0.PCR2_0.UINT32 = (PORT0.PCR2_0.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR2_0.UINT32 |= _PCR_ALT_IN4;
    PORT0.PCR2_0.UINT32 |= _PCR_SET_PMC;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set INTP5 pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(3U);
    PORT0.PCR2_7.UINT32 = (PORT0.PCR2_7.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR2_7.UINT32 |= _PCR_ALT_IN2;
    PORT0.PCR2_7.UINT32 |= _PCR_SET_PMC;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set INTP21 pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(3U);
    PORT0.PCR2_3.UINT32 = (PORT0.PCR2_3.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR2_3.UINT32 |= _PCR_ALT_IN4;
    PORT0.PCR2_3.UINT32 |= _PCR_SET_PMC;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set INTP4 setting */
    FLCA7.FCLACTL4_INTP_0.UINT8 = _FILTER_DETECTION_EDGE_FALLING;
    /* Set INTP5 setting */
    FLCA7.FCLACTL5_INTP_0.UINT8 = _FILTER_DETECTION_EDGE_FALLING;
    /* Set INTP21 setting */
    FLCA9.FCLACTL5_INTP_2.UINT8 = _FILTER_DETECTION_EDGE_FALLING;
    /* Synchronization processing */
    g_cg_sync_read = FLCA9.FCLACTL5_INTP_2.UINT8;
    __syncp();

    R_INTC_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_INTC_INTP4_Start
* Description  : This function enables INTP4 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC_INTP4_Start(void)
{
    /* Clear INTP4 request and enable operation */
    INTC2.EIC548.BIT.EIRF548 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC548.BIT.EIMK548 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_INTC_INTP4_Stop
* Description  : This function disables INTP4 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC_INTP4_Stop(void)
{
    /* Disable INTP4 operation and clear request */
    INTC2.EIC548.BIT.EIMK548 = _INT_PROCESSING_DISABLED;
    INTC2.EIC548.BIT.EIRF548 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.EIC548.UINT16;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_INTC_INTP5_Start
* Description  : This function enables INTP5 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC_INTP5_Start(void)
{
    /* Clear INTP5 request and enable operation */
    INTC2.EIC549.BIT.EIRF549 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC549.BIT.EIMK549 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_INTC_INTP5_Stop
* Description  : This function disables INTP5 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC_INTP5_Stop(void)
{
    /* Disable INTP5 operation and clear request */
    INTC2.EIC549.BIT.EIMK549 = _INT_PROCESSING_DISABLED;
    INTC2.EIC549.BIT.EIRF549 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.EIC549.UINT16;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_INTC_INTP21_Start
* Description  : This function enables INTP21 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC_INTP21_Start(void)
{
    /* Clear INTP21 request and enable operation */
    INTC2.EIC565.BIT.EIRF565 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC565.BIT.EIMK565 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_INTC_INTP21_Stop
* Description  : This function disables INTP21 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC_INTP21_Stop(void)
{
    /* Disable INTP21 operation and clear request */
    INTC2.EIC565.BIT.EIMK565 = _INT_PROCESSING_DISABLED;
    INTC2.EIC565.BIT.EIRF565 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.EIC565.UINT16;
    __syncp();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
