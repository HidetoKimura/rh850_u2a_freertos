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
* File Name        : TAUD0.c
* Component Version: 1.6.0
* Device(s)        : R7F702300BFABA
* Description      : This file implements device driver for TAUD0.
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
#include "TAUD0.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_TAUD0_Create
* Description  : This function initializes the TAUD0 channel.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUD0_Create(void)
{
    /* Disable channel counter operation */
    TAUD0.TT.UINT16 |= (_TAUD_CHANNEL2_COUNTER_STOP | _TAUD_CHANNEL1_COUNTER_STOP | _TAUD_CHANNEL0_COUNTER_STOP);
    TAUD0.TPS.UINT16 &= _TAUD_CK0_PRS_CLEAR;
    TAUD0.TPS.UINT16 |= _TAUD_CK0_PRE_PCLK_4;
    /* Set channel 0 setting */
    TAUD0.CMOR0.UINT16 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_MASTER_CHANNEL | 
                         _TAUD_START_TRIGGER_SOFTWARE | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_INTERVAL_TIMER_MODE | 
                         _TAUD_START_INT_GENERATED;
    /* Set compare match register */
    TAUD0.CMUR0.UINT8 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR0.UINT16 = _TAUD0_CHANNEL0_COMPARE_VALUE;
    /* Set output mode setting */
    TAUD0.TOE.UINT16 &= _TAUD_CHANNEL0_DISABLES_OUTPUT_MODE;
    /* Set channel 1 setting */
    TAUD0.CMOR1.UINT16 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL | 
                         _TAUD_START_TRIGGER_MASTER_INT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_ONE_COUNT_MODE | 
                         _TAUD_START_TRIGGER_ENABLE;
    /* Set compare match register */
    TAUD0.CMUR1.UINT8 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR1.UINT16 = _TAUD0_CHANNEL1_COMPARE_VALUE;
    /* Set output mode setting */
    TAUD0.TOE.UINT16 |= _TAUD_CHANNEL1_ENABLES_OUTPUT_MODE;
    TAUD0.TOM.UINT16 |= _TAUD_CHANNEL1_SYNCHRONOUS_OUTPUT_MODE;
    TAUD0.TOC.UINT16 &= _TAUD_CHANNEL1_OPERATION_MODE1;
    TAUD0.TOL.UINT16 &= _TAUD_CHANNEL1_POSITIVE_LOGIC;
    TAUD0.TDE.UINT16 &= _TAUD_CHANNEL1_DISABLE_DEAD_TIME_OPERATE;
    TAUD0.TDM.UINT16 &= _TAUD_CHANNEL1_DETECTING_DUTY_CYCLE;
    TAUD0.TDL.UINT16 &= _TAUD_CHANNEL1_NORMAL_PHASE;
    TAUD0.TRE.UINT16 &= _TAUD_CHANNEL1_REAL_TIME_OUTPUT_DISABLES;
    /* Set channel 2 setting */
    TAUD0.CMOR2.UINT16 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL | 
                         _TAUD_START_TRIGGER_MASTER_INT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_ONE_COUNT_MODE | 
                         _TAUD_START_TRIGGER_ENABLE;
    /* Set compare match register */
    TAUD0.CMUR2.UINT8 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR2.UINT16 = _TAUD0_CHANNEL2_COMPARE_VALUE;
    /* Set output mode setting */
    TAUD0.TOE.UINT16 |= _TAUD_CHANNEL2_ENABLES_OUTPUT_MODE;
    TAUD0.TOM.UINT16 |= _TAUD_CHANNEL2_SYNCHRONOUS_OUTPUT_MODE;
    TAUD0.TOC.UINT16 &= _TAUD_CHANNEL2_OPERATION_MODE1;
    TAUD0.TOL.UINT16 &= _TAUD_CHANNEL2_POSITIVE_LOGIC;
    TAUD0.TDE.UINT16 &= _TAUD_CHANNEL2_DISABLE_DEAD_TIME_OPERATE;
    TAUD0.TDM.UINT16 &= _TAUD_CHANNEL2_DETECTING_DUTY_CYCLE;
    TAUD0.TDL.UINT16 &= _TAUD_CHANNEL2_NORMAL_PHASE;
    TAUD0.TRE.UINT16 &= _TAUD_CHANNEL2_REAL_TIME_OUTPUT_DISABLES;
    /* Synchronization processing */
    g_cg_sync_read = TAUD0.TPS.UINT16;
    __syncp();

    /* Set TAUD0O1 pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(3U);
    PORT0.PCR2_1.UINT32 = (PORT0.PCR2_1.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR2_1.UINT32 |= _PCR_ALT_OUT6;
    PORT0.PCR2_1.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR2_1.UINT32 &= _PCR_CLEAR_PM;
    PORT0.PCR2_1.UINT32 &= _PCR_ALT_OUT_SETTING;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set TAUD0O2 pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(3U);
    PORT0.PCR2_2.UINT32 = (PORT0.PCR2_2.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR2_2.UINT32 |= _PCR_ALT_OUT6;
    PORT0.PCR2_2.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR2_2.UINT32 &= _PCR_CLEAR_PM;
    PORT0.PCR2_2.UINT32 &= _PCR_ALT_OUT_SETTING;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    R_TAUD0_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_TAUD0_Start
* Description  : This function starts the TAUD0 channel counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUD0_Start(void)
{
    /* Enable channel counter operation */
    TAUD0.TS.UINT16 |= (_TAUD_CHANNEL2_COUNTER_START | _TAUD_CHANNEL1_COUNTER_START | _TAUD_CHANNEL0_COUNTER_START);
}

/***********************************************************************************************************************
* Function Name: R_TAUD0_Stop
* Description  : This function stops the TAUD0 channel counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAUD0_Stop(void)
{
    /* Disable channel counter operation */
    TAUD0.TT.UINT16 |= (_TAUD_CHANNEL2_COUNTER_STOP | _TAUD_CHANNEL1_COUNTER_STOP | _TAUD_CHANNEL0_COUNTER_STOP);
    /* Synchronization processing */
    g_cg_sync_read = TAUD0.TT.UINT16;
    __syncp();
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: R_TAUD0_Update_CounterValue
* Description  : This function updates the CDR value for Channel x of TAUD0
* Arguments    : CDR_val - new CDR value for TAUD0 Channel x - uint16_t
*		 TAUD0_Channel - Select Channel for new CDR Value - uint16_t
* Return Value : None
***********************************************************************************************************************/

void R_TAUD0_CDR_Update(uint8_t TAUD0_Channel, uint16_t CDR_val)
{
  switch(TAUD0_Channel)
  {

    case 1:
        TAUD0.CDR1.UINT16 = CDR_val;

    break;

    case 2:
        TAUD0.CDR2.UINT16 = CDR_val;

    break;
    
    default:
    break;
  }
  
}

/* End user code. Do not edit comment generated here */
