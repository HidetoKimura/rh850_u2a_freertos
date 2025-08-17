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
* File Name        : ADCJ2.h
* Component Version: 1.7.0
* Device(s)        : R7F702300BFABA
* Description      : This file implements device driver for ADCJ2.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_ad.h"

#ifndef CFG_ADCJ2_H
#define CFG_ADCJ2_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#define _ADC2_UPPER_LIMIT_TABLE0                  (0x7FFE0000UL)
#define _ADC2_LOWER_LIMIT_TABLE0                  (0x00000000UL)
#define _ADC2_UPPER_LIMIT_TABLE1                  (0x7FFE0000UL)
#define _ADC2_LOWER_LIMIT_TABLE1                  (0x00000000UL)
#define _ADC2_UPPER_LIMIT_TABLE2                  (0x7FFE0000UL)
#define _ADC2_LOWER_LIMIT_TABLE2                  (0x00000000UL)
#define _ADC2_UPPER_LIMIT_TABLE3                  (0x7FFE0000UL)
#define _ADC2_LOWER_LIMIT_TABLE3                  (0x00000000UL)
#define _ADC2_UPPER_LIMIT_TABLE4                  (0x7FFE0000UL)
#define _ADC2_LOWER_LIMIT_TABLE4                  (0x00000000UL)
#define _ADC2_UPPER_LIMIT_TABLE5                  (0x7FFE0000UL)
#define _ADC2_LOWER_LIMIT_TABLE5                  (0x00000000UL)
#define _ADC2_UPPER_LIMIT_TABLE6                  (0x7FFE0000UL)
#define _ADC2_LOWER_LIMIT_TABLE6                  (0x00000000UL)
#define _ADC2_UPPER_LIMIT_TABLE7                  (0x7FFE0000UL)
#define _ADC2_LOWER_LIMIT_TABLE7                  (0x00000000UL)
#define _ADC2_WAIT_TIME_TABLE0                    (0x0000U)
#define _ADC2_WAIT_TIME_TABLE1                    (0x0000U)
#define _ADC2_WAIT_TIME_TABLE2                    (0x0000U)
#define _ADC2_WAIT_TIME_TABLE3                    (0x0000U)
#define _ADC2_WAIT_TIME_TABLE4                    (0x0000U)
#define _ADC2_WAIT_TIME_TABLE5                    (0x0000U)
#define _ADC2_WAIT_TIME_TABLE6                    (0x0000U)
#define _ADC2_WAIT_TIME_TABLE7                    (0x0000U)
#define _ADC2_SG0_START_POINTER                   (0x0000U)
#define _ADC2_SG0_END_POINTER                     (0x0000U)
#define _ADC2_SCAN_GRP0_SCAN_TIMES                (0x00U)
#define _ADC2_SCAN_GRP0_MONITOR_CHANNEL           (0x00U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_ADCJ2_Create(void);
void R_ADCJ2_Halt(void);
void R_ADCJ2_SetMultiplexerCommand(uint8_t cmdData);
void R_ADCJ2_ScanGroup0_Start(void);
void R_ADCJ2_ScanGroup0_OperationOn(void);
void R_ADCJ2_ScanGroup0_OperationOff(void);
MD_STATUS R_ADCJ2_ScanGroup0_GetResult(uint16_t * const buffer, uint8_t buffer_size);
void R_ADCJ2_Create_UserInit(void);
/* Start user code for function. Do not edit comment generated here */
#include "inc\common.h"
r_Error_t R_ADC_Test(void);
/* End user code. Do not edit comment generated here */
#endif
