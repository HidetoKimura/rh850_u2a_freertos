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
* File Name        : ADCJ1.c
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
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_ADCJ1_Create
* Description  : This function initializes the ADC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADCJ1_Create(void)
{
    /* Set ADC1 global setting */
    ADCJ1.ADCR1.UINT8 = _ADC_SYNC_SUSPEND;
    ADCJ1.ADCR2.UINT8 = _ADC_12BIT_UNSIGNED_INTEGER_RIGHT | _ADC_ADDITION_COUNT_FOUR_TIMES;
    ADCJ1.SFTCR.UINT8 = _ADC_READ_CLEAR_DISABLED | _ADC_OVERWRITE_ERROR_INT_DISABLE | _ADC_PARITY_ERROR_INT_DISABLE | 
                        _ADC_ID_ERROR_INT_DISABLE;
    ADCJ1.VCULLMTBR0 = _ADC1_UPPER_LIMIT_TABLE0 | _ADC1_LOWER_LIMIT_TABLE0;
    ADCJ1.VCULLMTBR1 = _ADC1_UPPER_LIMIT_TABLE1 | _ADC1_LOWER_LIMIT_TABLE1;
    ADCJ1.VCULLMTBR2 = _ADC1_UPPER_LIMIT_TABLE2 | _ADC1_LOWER_LIMIT_TABLE2;
    ADCJ1.VCULLMTBR3 = _ADC1_UPPER_LIMIT_TABLE3 | _ADC1_LOWER_LIMIT_TABLE3;
    ADCJ1.VCULLMTBR4 = _ADC1_UPPER_LIMIT_TABLE4 | _ADC1_LOWER_LIMIT_TABLE4;
    ADCJ1.VCULLMTBR5 = _ADC1_UPPER_LIMIT_TABLE5 | _ADC1_LOWER_LIMIT_TABLE5;
    ADCJ1.VCULLMTBR6 = _ADC1_UPPER_LIMIT_TABLE6 | _ADC1_LOWER_LIMIT_TABLE6;
    ADCJ1.VCULLMTBR7 = _ADC1_UPPER_LIMIT_TABLE7 | _ADC1_LOWER_LIMIT_TABLE7;
    ADCJ1.PWVCLMINTER.UINT8 = _ADC_PWM_DIAG_LIMIT_INT_ENABLE;
    ADCJ1.MPXINTER.UINT8 = _ADC_MPX_INT_DISABLE;
    ADCJ1.MPXCURCR.UINT8 = _ADC_MASK_FORMAT_0000;
    /* Set sampling period and AMP setting */
    ADCJ1.SMPCR.UINT32 = _ADC_EXTENDED_SAMPLING_60_CYCLES | _ADC_BUFFER_AMPLIFIER_ENABLE | 
                         _ADC_SAMPLING_PERIOD_ENABLE | _ADC_SAMPLING_18_CYCLES;
    /* Set safety-related setting */
    ADCJ1.TDCR.UINT8 = _ADC_TH_PATH_SELF_DIAGNOSIS_DISABLE | _ADC_PIN_SELF_DIAGNOSIS_VOLTAGE0;
    ADCJ1.ODCR.UINT16 = _ADC_WIRING_BREAK_DETECTION_NORMAL | _ADC_DETECTION_PULSE_WIDTH_5;
    ADCJ1.TOCCR.UINT8 = _ADC_TRIGGER_OVERLAP_CHECK_DISABLE;
    /* Set ADC1 wait registers */
    ADCJ1.WAITTR0.UINT16 = _ADC1_WAIT_TIME_TABLE0;
    ADCJ1.WAITTR1.UINT16 = _ADC1_WAIT_TIME_TABLE1;
    ADCJ1.WAITTR2.UINT16 = _ADC1_WAIT_TIME_TABLE2;
    ADCJ1.WAITTR3.UINT16 = _ADC1_WAIT_TIME_TABLE3;
    ADCJ1.WAITTR4.UINT16 = _ADC1_WAIT_TIME_TABLE4;
    ADCJ1.WAITTR5.UINT16 = _ADC1_WAIT_TIME_TABLE5;
    ADCJ1.WAITTR6.UINT16 = _ADC1_WAIT_TIME_TABLE6;
    ADCJ1.WAITTR7.UINT16 = _ADC1_WAIT_TIME_TABLE7;
    /* Set ADC1 start/end virtual channel pointer of scan groups */
    /* Set ADC1 virtual channels setting */
    /* Set ADC1 PWM-Diag setting */
    ADCJ1.PWDCR.UINT8 = _ADC_PWM_DIAG_ENABLE;
    /* Set ADC1 scan groups control setting */
    /* Set PWM-Diag control setting */
    ADCJ1.PWDSGCR.UINT8 = _ADC_PWM_DIAG_HW_TRIGGER_ENABLE;
    /* Synchronization processing */
    g_cg_sync_read = ADCJ1.ADHALTR.UINT8;
    __syncp();

    /* Set trigger input setting */
    PIC20.ADCJ1EDGSEL.UINT16 = _ADC_TRG4_VALID_EDGE_RISING;
    DNFA7.DNFACTL_ADCJ1.UINT8 = _DIGITAL_FILTER_SAMPLING_NUMBER_2 | _DIGITAL_FILTER_SAMPLING_CLOCK_1;
    /* Set ADCJ1CNV4 pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(17U);
    PORT0.PCR21_7.UINT32 = (PORT0.PCR21_7.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR21_7.UINT32 |= _PCR_ALT_OUT5;
    PORT0.PCR21_7.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR21_7.UINT32 &= _PCR_CLEAR_PM;
    PORT0.PCR21_7.UINT32 &= _PCR_ALT_OUT_SETTING;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Clear ADC1 error interrupt (INTADCJ1ERR) request and enable operation */
    INTC2.EIC232.BIT.EIRF232 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC232.BIT.EIMK232 = _INT_PROCESSING_ENABLED;

    R_ADCJ1_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_ADCJ1_Halt
* Description  : This function halts ADC1.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADCJ1_Halt(void)
{
    /* Forcibly terminate and initialize all scan groups and all A/D timers */
    ADCJ1.ADHALTR.UINT8 = _ADC_HALT;
    /* Disable ADC1 SG4 end interrupt (INTADCJ1I4) operation and clear request */
    INTC2.EIC237.BIT.EIMK237 = _INT_PROCESSING_DISABLED;
    INTC2.EIC237.BIT.EIRF237 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = ADCJ1.ADHALTR.UINT8;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_ADCJ1_SetMultiplexerCommand
* Description  : This function sets multiplexer command for ADC1.
* Arguments    : cmdData -
*                    multiplexer command
* Return Value : None
***********************************************************************************************************************/
void R_ADCJ1_SetMultiplexerCommand(uint8_t cmdData)
{
    ADCJ1.MPXCMDR.UINT8 = cmdData;
    /* Synchronization processing */
    g_cg_sync_read = ADCJ1.MPXCMDR.UINT8;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_ADCJ1_ScanGroup4_Start
* Description  : This function enables ADC1 scan group 4 end interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADCJ1_ScanGroup4_Start(void)
{
    /* Clear ADC1 SG4 end interrupt (INTADCJ1I4) request and enable operation */
    INTC2.EIC237.BIT.EIRF237 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC237.BIT.EIMK237 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_ADCJ1_ScanGroup4_GetPWMDiagResult
* Description  : This function gets A/D conversion results for ADC1 scan group 4 (PWM-Diag).
* Arguments    : buffer -
*                    buffer pointer
* Return Value : MD_STATUS -
*                    MD_OK
***********************************************************************************************************************/
MD_STATUS R_ADCJ1_ScanGroup4_GetPWMDiagResult(uint16_t * const buffer)
{
    uint16_t * p_addr;

    p_addr = (uint16_t*)_ADC1_PWD_VCHANNEL_DATA_BASE;
    buffer[0] = (uint16_t) * p_addr;

    return MD_OK;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
