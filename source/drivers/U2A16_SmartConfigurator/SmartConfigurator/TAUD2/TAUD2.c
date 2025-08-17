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
* File Name        : TAUD2.c
* Component Version: 1.6.0
* Device(s)        : R7F702300BFABA
* Description      : This file implements device driver for TAUD2.
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
#include "TAUD2.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_TAUD2_Create
* Description  : This function initializes the TAUD2 channel.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUD2_Create(void)
{
    /* Disable channel counter operation */
    TAUD2.TT.UINT16 |= (_TAUD_CHANNEL14_COUNTER_STOP | _TAUD_CHANNEL13_COUNTER_STOP | _TAUD_CHANNEL12_COUNTER_STOP);
    TAUD2.TPS.UINT16 &= _TAUD_CK0_PRS_CLEAR;
    TAUD2.TPS.UINT16 |= _TAUD_CK0_PRE_PCLK_4;
    /* Set channel 12 setting */
    TAUD2.CMOR12.UINT16 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_MASTER_CHANNEL | 
                          _TAUD_START_TRIGGER_SOFTWARE | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_INTERVAL_TIMER_MODE | 
                          _TAUD_START_INT_GENERATED;
    /* Set compare match register */
    TAUD2.CMUR12.UINT8 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD2.CDR12.UINT16 = _TAUD2_CHANNEL12_COMPARE_VALUE;
    /* Set output mode setting */
    TAUD2.TOE.UINT16 &= _TAUD_CHANNEL12_DISABLES_OUTPUT_MODE;
    /* Set channel 13 setting */
    TAUD2.CMOR13.UINT16 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL | 
                          _TAUD_START_TRIGGER_MASTER_INT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_ONE_COUNT_MODE | 
                          _TAUD_START_TRIGGER_ENABLE;
    /* Set compare match register */
    TAUD2.CMUR13.UINT8 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD2.CDR13.UINT16 = _TAUD2_CHANNEL13_COMPARE_VALUE;
    /* Set output mode setting */
    TAUD2.TOE.UINT16 |= _TAUD_CHANNEL13_ENABLES_OUTPUT_MODE;
    TAUD2.TOM.UINT16 |= _TAUD_CHANNEL13_SYNCHRONOUS_OUTPUT_MODE;
    TAUD2.TOC.UINT16 &= _TAUD_CHANNEL13_OPERATION_MODE1;
    TAUD2.TOL.UINT16 &= _TAUD_CHANNEL13_POSITIVE_LOGIC;
    TAUD2.TDE.UINT16 &= _TAUD_CHANNEL13_DISABLE_DEAD_TIME_OPERATE;
    TAUD2.TDM.UINT16 &= _TAUD_CHANNEL13_DETECTING_DUTY_CYCLE;
    TAUD2.TDL.UINT16 &= _TAUD_CHANNEL13_NORMAL_PHASE;
    TAUD2.TRE.UINT16 &= _TAUD_CHANNEL13_REAL_TIME_OUTPUT_DISABLES;
    /* Set channel 14 setting */
    TAUD2.CMOR14.UINT16 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL | 
                          _TAUD_START_TRIGGER_MASTER_INT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_ONE_COUNT_MODE | 
                          _TAUD_START_TRIGGER_ENABLE;
    /* Set compare match register */
    TAUD2.CMUR14.UINT8 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD2.CDR14.UINT16 = _TAUD2_CHANNEL14_COMPARE_VALUE;
    /* Set output mode setting */
    TAUD2.TOE.UINT16 |= _TAUD_CHANNEL14_ENABLES_OUTPUT_MODE;
    TAUD2.TOM.UINT16 |= _TAUD_CHANNEL14_SYNCHRONOUS_OUTPUT_MODE;
    TAUD2.TOC.UINT16 &= _TAUD_CHANNEL14_OPERATION_MODE1;
    TAUD2.TOL.UINT16 &= _TAUD_CHANNEL14_POSITIVE_LOGIC;
    TAUD2.TDE.UINT16 &= _TAUD_CHANNEL14_DISABLE_DEAD_TIME_OPERATE;
    TAUD2.TDM.UINT16 &= _TAUD_CHANNEL14_DETECTING_DUTY_CYCLE;
    TAUD2.TDL.UINT16 &= _TAUD_CHANNEL14_NORMAL_PHASE;
    TAUD2.TRE.UINT16 &= _TAUD_CHANNEL14_REAL_TIME_OUTPUT_DISABLES;
    /* Synchronization processing */
    g_cg_sync_read = TAUD2.TPS.UINT16;
    __syncp();

    /* Set TAUD2O13 pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(7U);
    PORT0.PCR6_5.UINT32 = (PORT0.PCR6_5.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR6_5.UINT32 |= _PCR_ALT_OUT6;
    PORT0.PCR6_5.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR6_5.UINT32 &= _PCR_CLEAR_PM;
    PORT0.PCR6_5.UINT32 &= _PCR_ALT_OUT_SETTING;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set TAUD2O14 pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(7U);
    PORT0.PCR6_6.UINT32 = (PORT0.PCR6_6.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR6_6.UINT32 |= _PCR_ALT_OUT6;
    PORT0.PCR6_6.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR6_6.UINT32 &= _PCR_CLEAR_PM;
    PORT0.PCR6_6.UINT32 &= _PCR_ALT_OUT_SETTING;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    R_TAUD2_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_TAUD2_Start
* Description  : This function starts the TAUD2 channel counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUD2_Start(void)
{
    /* Enable channel counter operation */
    TAUD2.TS.UINT16 |= (_TAUD_CHANNEL14_COUNTER_START | _TAUD_CHANNEL13_COUNTER_START | _TAUD_CHANNEL12_COUNTER_START);
}

/***********************************************************************************************************************
* Function Name: R_TAUD2_Stop
* Description  : This function stops the TAUD2 channel counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUD2_Stop(void)
{
    /* Disable channel counter operation */
    TAUD2.TT.UINT16 |= (_TAUD_CHANNEL14_COUNTER_STOP | _TAUD_CHANNEL13_COUNTER_STOP | _TAUD_CHANNEL12_COUNTER_STOP);
    /* Synchronization processing */
    g_cg_sync_read = TAUD2.TT.UINT16;
    __syncp();
}

/* Start user code for adding. Do not edit comment generated here */
void R_TAUD2_CDR_Update(uint8_t TAUD2_Channel, uint16_t CDR_val)
{
  switch(TAUD2_Channel)
  {

    case 13:
        TAUD2.CDR13.UINT16 = CDR_val;
        TAUD2.RDT.UINT16 = _TAUD_CHANNEL1_COUNTER_START;
    break;

    case 14:
        TAUD2.CDR14.UINT16 = CDR_val;
        TAUD2.RDT.UINT16 = _TAUD_CHANNEL2_COUNTER_START;
    break;
    
    default:
    break;
  }
  
}
/* End user code. Do not edit comment generated here */
