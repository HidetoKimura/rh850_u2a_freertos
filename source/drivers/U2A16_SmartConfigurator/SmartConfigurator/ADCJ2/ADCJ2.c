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
* File Name        : ADCJ2.c
* Component Version: 1.7.0
* Device(s)        : R7F702300BFABA
* Description      : This file implements device driver for ADCJ2.
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
#include "ADCJ2.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_ADCJ2_Create
* Description  : This function initializes the ADC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADCJ2_Create(void)
{
    /* Set ADC2 global setting */
    ADCJ2.ADCR1.UINT8 = _ADC_SYNC_SUSPEND;
    ADCJ2.ADCR2.UINT8 = _ADC_12BIT_UNSIGNED_INTEGER_RIGHT | _ADC_ADDITION_COUNT_TWICE;
    ADCJ2.SFTCR.UINT8 = _ADC_READ_CLEAR_DISABLED;
    ADCJ2.VCULLMTBR0 = _ADC2_UPPER_LIMIT_TABLE0 | _ADC2_LOWER_LIMIT_TABLE0;
    ADCJ2.VCULLMTBR1 = _ADC2_UPPER_LIMIT_TABLE1 | _ADC2_LOWER_LIMIT_TABLE1;
    ADCJ2.VCULLMTBR2 = _ADC2_UPPER_LIMIT_TABLE2 | _ADC2_LOWER_LIMIT_TABLE2;
    ADCJ2.VCULLMTBR3 = _ADC2_UPPER_LIMIT_TABLE3 | _ADC2_LOWER_LIMIT_TABLE3;
    ADCJ2.VCULLMTBR4 = _ADC2_UPPER_LIMIT_TABLE4 | _ADC2_LOWER_LIMIT_TABLE4;
    ADCJ2.VCULLMTBR5 = _ADC2_UPPER_LIMIT_TABLE5 | _ADC2_LOWER_LIMIT_TABLE5;
    ADCJ2.VCULLMTBR6 = _ADC2_UPPER_LIMIT_TABLE6 | _ADC2_LOWER_LIMIT_TABLE6;
    ADCJ2.VCULLMTBR7 = _ADC2_UPPER_LIMIT_TABLE7 | _ADC2_LOWER_LIMIT_TABLE7;
    ADCJ2.VCLMINTER1.UINT32 = _ADC_VIR_CHAN00_LIMIT_INT_ENABLE;
    ADCJ2.MPXINTER.UINT8 = _ADC_MPX_INT_DISABLE;
    ADCJ2.MPXCURCR.UINT8 = _ADC_MASK_FORMAT_0000;
    /* Set sampling period and AMP setting */
    ADCJ2.SMPCR.UINT32 = _ADC_EXTENDED_SAMPLING_60_CYCLES | _ADC_BUFFER_AMPLIFIER_ENABLE | 
                         _ADC_SAMPLING_PERIOD_ENABLE | _ADC_SAMPLING_18_CYCLES;
    /* Set safety-related setting */
    ADCJ2.TDCR.UINT8 = _ADC_TH_PATH_SELF_DIAGNOSIS_DISABLE | _ADC_PIN_SELF_DIAGNOSIS_VOLTAGE3;
    ADCJ2.ODCR.UINT16 = _ADC_WIRING_BREAK_DETECTION_NORMAL | _ADC_DETECTION_PULSE_WIDTH_1;
    ADCJ2.TOCCR.UINT8 = _ADC_TRIGGER_OVERLAP_CHECK_DISABLE;
    /* Set A/D conversion monitor channel setting */
    ADCJ2.ADENDP0.UINT8 = _ADC2_SCAN_GRP0_MONITOR_CHANNEL;
    /* Set ADC2 wait registers */
    ADCJ2.WAITTR0.UINT16 = _ADC2_WAIT_TIME_TABLE0;
    ADCJ2.WAITTR1.UINT16 = _ADC2_WAIT_TIME_TABLE1;
    ADCJ2.WAITTR2.UINT16 = _ADC2_WAIT_TIME_TABLE2;
    ADCJ2.WAITTR3.UINT16 = _ADC2_WAIT_TIME_TABLE3;
    ADCJ2.WAITTR4.UINT16 = _ADC2_WAIT_TIME_TABLE4;
    ADCJ2.WAITTR5.UINT16 = _ADC2_WAIT_TIME_TABLE5;
    ADCJ2.WAITTR6.UINT16 = _ADC2_WAIT_TIME_TABLE6;
    ADCJ2.WAITTR7.UINT16 = _ADC2_WAIT_TIME_TABLE7;
    /* Set ADC2 start/end virtual channel pointer of scan groups */
    ADCJ2.SGVCPR0.UINT16 = _ADC2_SG0_END_POINTER | _ADC2_SG0_START_POINTER;
    /* Set ADC2 multicycle register of scan groups */
    ADCJ2.SGMCYCR0.UINT8 = _ADC2_SCAN_GRP0_SCAN_TIMES;
    /* Set ADC2 virtual channels setting */
    ADCJ2.VCR0.UINT32 = _ADC_LIMIT_TABLE_SELECT_0 | _ADC_WAIT_TIME_SELECT_NONE | _ADC_GTM_ENTRY_DISABLE | 
                        _ADC_NORMAL | _ADC_VIRTUAL_END_INT_DISABLE | _ADC_PHYSICAL_CHANNEL_AN00;
    /* Set ADC2 scan groups control setting */
    ADCJ2.SGCR0.UINT8 = _ADC_SIMULTANEOUS_CONVERSION_DISABLE | _ADC_SG_SCAN_MODE_MULTICYCLE | 
                        _ADC_SG_SCAN_END_INT_DISABLE | _ADC_SG_HARDWARE_TRIGGER;
    /* Synchronization processing */
    g_cg_sync_read = ADCJ2.ADHALTR.UINT8;
    __syncp();

    /* Set trigger input setting */
    ADCJ2_SELB.ADCJ2SGTSEL0.UINT32 = _ADC_SCAN_GRP_TRIGGER_SEQADTRG;
    FLCA12.FCLACTL0_ADCJ2.UINT8 = _FILTER_DETECTION_EDGE_RISING;
    DNFA8.DNFACTL_ADCJ2.UINT8 = _DIGITAL_FILTER_SAMPLING_NUMBER_2 | _DIGITAL_FILTER_SAMPLING_CLOCK_1;
    /* Set ADCJ2CNV0 pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(5U);
    PORT0.PCR4_11.UINT32 = (PORT0.PCR4_11.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR4_11.UINT32 |= _PCR_ALT_OUT5;
    PORT0.PCR4_11.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR4_11.UINT32 &= _PCR_CLEAR_PM;
    PORT0.PCR4_11.UINT32 &= _PCR_ALT_OUT_SETTING;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set ADCJ2I0 pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(25U);
    PORT0.APCR4_0.UINT32 = _PCR_ANALOG_INPUT;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;


    R_ADCJ2_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_ADCJ2_Halt
* Description  : This function halts ADC2.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADCJ2_Halt(void)
{
    /* Forcibly terminate and initialize all scan groups and all A/D timers */
    ADCJ2.ADHALTR.UINT8 = _ADC_HALT;
    /* Synchronization processing */
    g_cg_sync_read = ADCJ2.ADHALTR.UINT8;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_ADCJ2_SetMultiplexerCommand
* Description  : This function sets multiplexer command for ADC2.
* Arguments    : cmdData -
*                    multiplexer command
* Return Value : None
***********************************************************************************************************************/
void R_ADCJ2_SetMultiplexerCommand(uint8_t cmdData)
{
    ADCJ2.MPXCMDR.UINT8 = cmdData;
    /* Synchronization processing */
    g_cg_sync_read = ADCJ2.MPXCMDR.UINT8;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_ADCJ2_ScanGroup0_Start
* Description  : This function enables ADC2 scan group 0 end interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADCJ2_ScanGroup0_Start(void)
{
}

/***********************************************************************************************************************
* Function Name: R_ADCJ2_ScanGroup0_OperationOn
* Description  : This function starts ADC2 scan group 0 conversion.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADCJ2_ScanGroup0_OperationOn(void)
{
    /* Enable ADC2 SG0 operation */
    ADCJ2.SGSTCR0.UINT8 = _ADC_START;
}

/***********************************************************************************************************************
* Function Name: R_ADCJ2_ScanGroup0_OperationOff
* Description  : This function stops ADC2 scan group 0 conversion.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADCJ2_ScanGroup0_OperationOff(void)
{
    /* Disable ADC2 SG0 operation */
    ADCJ2.SGSTPCR0.UINT8 = _ADC_STOP;
}

/***********************************************************************************************************************
* Function Name: R_ADCJ2_ScanGroup0_GetResult
* Description  : This function gets A/D conversion results for ADC2 scan group 0.
* Arguments    : buffer -
*                    buffer pointer
*                buffer_size -
*                    the size of buffer
* Return Value : MD_STATUS -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_ADCJ2_ScanGroup0_GetResult(uint16_t * const buffer, uint8_t buffer_size)
{
    uint8_t start_pointer;
    uint8_t end_pointer;
    uint8_t count_num;
    uint8_t buffer_index;
    uint16_t * p_addr;

    start_pointer = (uint8_t) ADCJ2.SGVCPR0.UINT16;
    end_pointer = (uint8_t) (ADCJ2.SGVCPR0.UINT16 >> 8U);
    count_num = (end_pointer - start_pointer) + 1U;
    if (buffer_size < count_num)
    {
        return MD_ARGERROR;
    }

    p_addr = (uint16_t*)(_ADC2_VCHANNEL_DATA_BASE + (2U * start_pointer));

    for (buffer_index = 0U; buffer_index < count_num; buffer_index++ )
    {
        buffer[buffer_index] = (uint16_t) * p_addr;
        p_addr++;
    }

    return MD_OK;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
