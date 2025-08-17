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
* File Name        : ADCJ1_user.c
* Component Version: 1.7.0
* Device(s)        : R7F702300BFABA
* Description      : This file implements device driver for ADCJ1.
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
#include "ADCJ1.h"
/* Start user code for include. Do not edit comment generated here */
#include "inc\common.h"
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
r_AD_Error_t  g_ADCJ1_error=R_AD_OK;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_ADCJ1_Create_UserInit
* Description  : This function adds user code after initializing the ADCJ1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADCJ1_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
     
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_ADCJ1_error_interrupt
* Description  : This function handles the INTADCJ1ERR interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if defined (__CCRH__)
#pragma interrupt r_ADCJ1_error_interrupt(enable=false, channel=232, fpu=true, callt=false)
#elif defined (__ghs__)
#pragma ghs interrupt
#elif defined (__ICCRH850__)
#pragma type_attribute=__interrupt
#else
#error Unknown Compiler
#endif
void r_ADCJ1_error_interrupt(void)
{
    /* Start user code for r_ADCJ1_error_interrupt. Do not edit comment generated here */
     g_ADCJ1_error=R_AD_ERROR;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_ADCJ1_scan_group4_end_interrupt
* Description  : This function handles the INTADCJ1I4 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if defined (__CCRH__)
#pragma interrupt r_ADCJ1_scan_group4_end_interrupt(enable=false, channel=237, fpu=true, callt=false)
#elif defined (__ghs__)
#pragma ghs interrupt
#elif defined (__ICCRH850__)
#pragma type_attribute=__interrupt
#else
#error Unknown Compiler
#endif
void r_ADCJ1_scan_group4_end_interrupt(void)
{
    /* Start user code for r_ADCJ1_scan_group4_end_interrupt. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */


r_AD_Error_t R_ADCJ1_getError(void){
	
        return g_ADCJ1_error;
    
}

/******************************************************************************
** Function:    R_Config_ADCJ1_SetUpperLowerLimit
** Description: This function sets the upper/lower limit for the corresponding
**              Upper/Lower Limit Table.
** Parameter:   limit_channel - Limit Channel [0-7]
**              upper - Upper Limit
**              lower - Lower Limit
** Return:      None
******************************************************************************/
void R_Config_ADCJ1_SetUpperLowerLimit(uint32_t limit_table, uint16_t upper, uint16_t lower)
{
  /* Select the upper and lower limit values */
  switch(limit_table)
  {
    /* Limit registers: [31:20] Upper limit, [15:4] Lower limit */
    case 0u:
      ADCJ1.VCULLMTBR0 =  ((uint32_t)upper << 16);   /* Set upper limit */
      ADCJ1.VCULLMTBR0 |=  (uint32_t)lower;   /* Set lower limit */
    break;
    
    case 1u:
      ADCJ1.VCULLMTBR1 =  ((uint32_t)upper << 16);   /* Set upper limit */
      ADCJ1.VCULLMTBR1 |=  (uint32_t)lower;   /* Set lower limit */
    break;
    
    case 2u:
      ADCJ1.VCULLMTBR2 =  ((uint32_t)upper << 16);   /* Set upper limit */
      ADCJ1.VCULLMTBR2 |=  (uint32_t)lower;   /* Set lower limit */
    break;
    
    case 3u:
      ADCJ1.VCULLMTBR3 =  ((uint32_t)upper << 16);   /* Set upper limit */
      ADCJ1.VCULLMTBR3 |=  (uint32_t)lower;   /* Set lower limit */
    break;
    
    case 4u:
      ADCJ1.VCULLMTBR4 =  ((uint32_t)upper << 16);   /* Set upper limit */
      ADCJ1.VCULLMTBR4 |=  (uint32_t)lower;   /* Set lower limit */
    break;
    
    case 5u:
      ADCJ1.VCULLMTBR5 =  ((uint32_t)upper << 16);   /* Set upper limit */
      ADCJ1.VCULLMTBR5 |=  (uint32_t)lower;   /* Set lower limit */
    break;

    case 6u:
      ADCJ1.VCULLMTBR6 =  ((uint32_t)upper << 16);   /* Set upper limit */
      ADCJ1.VCULLMTBR6 |=  (uint32_t)lower;   /* Set lower limit */
    break;

    case 7u:
      ADCJ1.VCULLMTBR7 =  ((uint32_t)upper << 16);   /* Set upper limit */
      ADCJ1.VCULLMTBR7 |=  (uint32_t)lower;   /* Set lower limit */
    break;
    default:
        
    break;
  }

}

/* End user code. Do not edit comment generated here */
