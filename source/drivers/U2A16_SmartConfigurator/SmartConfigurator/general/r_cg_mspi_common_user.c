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
* File Name        : r_cg_mspi_common_user.c
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
#include "MSPI30.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_mspi3_interrupt_send
* Description  : This function handles the MSPI_MSPI3TX interrupt
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if defined (__CCRH__)
#pragma interrupt r_mspi3_interrupt_send(enable=false, channel=268, fpu=true, callt=false)
#elif defined (__ghs__)
#pragma ghs interrupt
#elif defined (__ICCRH850__)
#pragma type_attribute=__interrupt
#else
#error Unknown Compiler
#endif
void r_mspi3_interrupt_send(void)
{
    R_MSPI30_Callback_Interrupt_Send();
}

/***********************************************************************************************************************
* Function Name: r_mspi3_interrupt_receive
* Description  : This function handles the MSPI_MSPI3RX interrupt
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if defined (__CCRH__)
#pragma interrupt r_mspi3_interrupt_receive(enable=false, channel=269, fpu=true, callt=false)
#elif defined (__ghs__)
#pragma ghs interrupt
#elif defined (__ICCRH850__)
#pragma type_attribute=__interrupt
#else
#error Unknown Compiler
#endif
void r_mspi3_interrupt_receive(void)
{
    R_MSPI30_Callback_Interrupt_Receive();
}

/***********************************************************************************************************************
* Function Name: r_mspi3_interrupt_frameend
* Description  : This function handles the MSPI_MSPI3FE interrupt
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if defined (__CCRH__)
#pragma interrupt r_mspi3_interrupt_frameend(enable=false, channel=270, fpu=true, callt=false)
#elif defined (__ghs__)
#pragma ghs interrupt
#elif defined (__ICCRH850__)
#pragma type_attribute=__interrupt
#else
#error Unknown Compiler
#endif
void r_mspi3_interrupt_frameend(void)
{
    R_MSPI30_Callback_Interrupt_Frameend();
}

/***********************************************************************************************************************
* Function Name: r_mspi3_interrupt_error
* Description  : This function handles the MSPI_MSPI3ERR interrupt
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if defined (__CCRH__)
#pragma interrupt r_mspi3_interrupt_error(enable=false, channel=271, fpu=true, callt=false)
#elif defined (__ghs__)
#pragma ghs interrupt
#elif defined (__ICCRH850__)
#pragma type_attribute=__interrupt
#else
#error Unknown Compiler
#endif
void r_mspi3_interrupt_error(void)
{
    R_MSPI30_Callback_Interrupt_Error();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
