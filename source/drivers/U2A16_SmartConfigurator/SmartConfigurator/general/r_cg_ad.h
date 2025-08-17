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
* File Name        : r_cg_ad.h
* Version          : 1.0.140
* Device(s)        : R7F702300BFABA
* Description      : General header file for ADCJ peripheral.
***********************************************************************************************************************/

#ifndef ADCJ_H
#define ADCJ_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Virtual Channel Register j (ADCJnVCRj)
*/
/* Upper/lower limit check table register select (VCULLMTBS[3:0]) */
#define _ADC_LIMIT_TABLE_SELECT_NONE              (0x00000000UL) /* Upper/lower limit are not checked */
#define _ADC_LIMIT_TABLE_SELECT_0                 (0x10000000UL) /* Upper/lower limit are checked for VCULLMTBR0 */
#define _ADC_LIMIT_TABLE_SELECT_1                 (0x20000000UL) /* Upper/lower limit are checked for VCULLMTBR1 */
#define _ADC_LIMIT_TABLE_SELECT_2                 (0x30000000UL) /* Upper/lower limit are checked for VCULLMTBR2 */
#define _ADC_LIMIT_TABLE_SELECT_3                 (0x40000000UL) /* Upper/lower limit are checked for VCULLMTBR3 */
#define _ADC_LIMIT_TABLE_SELECT_4                 (0x50000000UL) /* Upper/lower limit are checked for VCULLMTBR4 */
#define _ADC_LIMIT_TABLE_SELECT_5                 (0x60000000UL) /* Upper/lower limit are checked for VCULLMTBR5 */
#define _ADC_LIMIT_TABLE_SELECT_6                 (0x70000000UL) /* Upper/lower limit are checked for VCULLMTBR6 */
#define _ADC_LIMIT_TABLE_SELECT_7                 (0x80000000UL) /* Upper/lower limit are checked for VCULLMTBR7 */
/* Wait time table select (WTTS[3:0]) */
#define _ADC_WAIT_TIME_SELECT_NONE                (0x00000000UL) /* Wait time are not checked */
#define _ADC_WAIT_TIME_TABLE_0                    (0x01000000UL) /* Wait time are checked for WAITTR0 */
#define _ADC_WAIT_TIME_TABLE_1                    (0x02000000UL) /* Wait time are checked for WAITTR1 */
#define _ADC_WAIT_TIME_TABLE_2                    (0x03000000UL) /* Wait time are checked for WAITTR2 */
#define _ADC_WAIT_TIME_TABLE_3                    (0x04000000UL) /* Wait time are checked for WAITTR3 */
#define _ADC_WAIT_TIME_TABLE_4                    (0x05000000UL) /* Wait time are checked for WAITTR4 */
#define _ADC_WAIT_TIME_TABLE_5                    (0x06000000UL) /* Wait time are checked for WAITTR5 */
#define _ADC_WAIT_TIME_TABLE_6                    (0x07000000UL) /* Wait time are checked for WAITTR6 */
#define _ADC_WAIT_TIME_TABLE_7                    (0x08000000UL) /* Wait time are checked for WAITTR7 */
/* GTM entry enable (GTMENT) */
#define _ADC_GTM_ENTRY_DISABLE                    (0x00000000UL) /* GTM entry disabled */
#define _ADC_GTM_ENTRY_ENABLE                     (0x00100000UL) /* GTM entry enable */
/* Conversion type (CNVCLS[3:0]) */
#define _ADC_NORMAL                               (0x00000000UL) /* Normal A/D conversion */
#define _ADC_HOLD_VALUE                           (0x00000800UL) /* Hold value A/D conversion */
#define _ADC_EXTENDED_SAMPLING                    (0x00001000UL) /* Normal A/D conversion at extended sampling cycle */
#define _ADC_AD_CORE_DIAGNOSIS                    (0x00001800UL) /* ADcore self-diagnosis A/D conversion */
#define _ADC_ADDITION_MODE                        (0x00002000UL) /* Addition mode A/D conversion */
#define _ADC_MPX_NORMAL                           (0x00002800UL) /* MPX normal A/D conversion */
#define _ADC_MPX_ADDITION_MODE                    (0x00003000UL) /* MPX addition mode A/D conversion */
#define _ADC_PIN_LEVEL_DIAGNOSIS                  (0x00003800UL) /* Pin level self-diagnosis A/D conversion */
#define _ADC_BREAK_MODE1                          (0x00004000UL) /* A/D conversion in wiring-break detection mode 1 */
#define _ADC_BREAK_MODE2_PULLDOWN                 (0x00004800UL) /* A/D conversion in wiring-break detection mode 2
                                                                                     (physical channel IO pull-down) */
#define _ADC_BREAK_MODE2_PULLUP                   (0x00005000UL) /* A/D conversion in wiring-break detection mode 2
                                                                                     (physical channel IO pull-up) */
#define _ADC_BREAK_MODE1_DIAGNOSIS                (0x00005800UL) /* Self-diagnosis A/D conversion in wiring-break
                                                                                                detection mode 1 */
#define _ADC_BREAK_MODE2_PULLDOWN_DIAGNOSIS       (0x00006000UL) /* Self-diagnosis A/D conversion in wiring-break
                                                                detection mode 2 (physical channel IO pull-down) */
#define _ADC_BREAK_MODE2_PULLUP_DIAGNOSIS         (0x00006800UL) /* Self-diagnosis A/D conversion in wiring-break
                                                                  detection mode 2 (physical channel IO pull-up) */
#define _ADC_DATA_PATH_DIAGNOSIS                  (0x00007000UL) /* A/D conversion of A/D conversion data path
                                                                                       diagnosis (ADVAL mode) */
/* Virtual channel end interrupt enable (ADIE) */
#define _ADC_VIRTUAL_END_INT_DISABLE              (0x00000000UL) /* INT_ADx is not output at the end of virtual
                                                                                                       channel */
#define _ADC_VIRTUAL_END_INT_ENABLE               (0x00000080UL) /* INT_ADx is output at the end of virtual channel */
/* A/D conversion for each conversion mode (GCTRL[5:0]) */
#define _ADC_PHYSICAL_CHANNEL_AN00                (0x00000000UL) /* ANn00 */
#define _ADC_PHYSICAL_CHANNEL_AN01                (0x00000001UL) /* ANn01 */
#define _ADC_PHYSICAL_CHANNEL_AN02                (0x00000002UL) /* ANn02 */
#define _ADC_PHYSICAL_CHANNEL_AN03                (0x00000003UL) /* ANn03 */
#define _ADC_PHYSICAL_CHANNEL_AN10                (0x00000004UL) /* ANn10 */
#define _ADC_PHYSICAL_CHANNEL_AN11                (0x00000005UL) /* ANn11 */
#define _ADC_PHYSICAL_CHANNEL_AN12                (0x00000006UL) /* ANn12 */
#define _ADC_PHYSICAL_CHANNEL_AN13                (0x00000007UL) /* ANn13 */
#define _ADC_PHYSICAL_CHANNEL_AN20                (0x00000008UL) /* ANn20 */
#define _ADC_PHYSICAL_CHANNEL_AN21                (0x00000009UL) /* ANn21 */
#define _ADC_PHYSICAL_CHANNEL_AN22                (0x0000000AUL) /* ANn22 */
#define _ADC_PHYSICAL_CHANNEL_AN23                (0x0000000BUL) /* ANn23 */
#define _ADC_PHYSICAL_CHANNEL_AN30                (0x0000000CUL) /* ANn30 */
#define _ADC_PHYSICAL_CHANNEL_AN31                (0x0000000DUL) /* ANn31 */
#define _ADC_PHYSICAL_CHANNEL_AN32                (0x0000000EUL) /* ANn32 */
#define _ADC_PHYSICAL_CHANNEL_AN33                (0x0000000FUL) /* ANn33 */
#define _ADC_PHYSICAL_CHANNEL_AN40                (0x00000010UL) /* ANn40 */
#define _ADC_PHYSICAL_CHANNEL_AN41                (0x00000011UL) /* ANn41 */
#define _ADC_PHYSICAL_CHANNEL_AN42                (0x00000012UL) /* ANn42 */
#define _ADC_PHYSICAL_CHANNEL_AN43                (0x00000013UL) /* ANn43 */
#define _ADC_PHYSICAL_CHANNEL_VMON_VCC            (0x00000014UL) /* VMON_VCC */
#define _ADC_PHYSICAL_CHANNEL_VMON_E0VCC          (0x00000015UL) /* VMON_E0VCC */
#define _ADC_PHYSICAL_CHANNEL_VMON_ISOVDD         (0x00000016UL) /* VMON_ISOVDD */
#define _ADC_PHYSICAL_CHANNEL_VMON_AWOVDD         (0x00000017UL) /* VMON_AWOVDD */
#define _ADC_PHYSICAL_CHANNEL_AN50                (0x00000014UL) /* ANn50 */
#define _ADC_PHYSICAL_CHANNEL_AN51                (0x00000015UL) /* ANn51 */
#define _ADC_PHYSICAL_CHANNEL_AN52                (0x00000016UL) /* ANn52 */
#define _ADC_PHYSICAL_CHANNEL_AN53                (0x00000017UL) /* ANn53 */
#define _ADC_PHYSICAL_CHANNEL_AN60                (0x00000018UL) /* ANn60 */
#define _ADC_PHYSICAL_CHANNEL_AN61                (0x00000019UL) /* ANn61 */
#define _ADC_PHYSICAL_CHANNEL_AN62                (0x0000001AUL) /* ANn62 */
#define _ADC_PHYSICAL_CHANNEL_AN63                (0x0000001BUL) /* ANn63 */
#define _ADC_PHYSICAL_CHANNEL_AN70                (0x0000001CUL) /* ANn70 */
#define _ADC_PHYSICAL_CHANNEL_AN71                (0x0000001DUL) /* ANn71 */
#define _ADC_PHYSICAL_CHANNEL_AN72                (0x0000001EUL) /* ANn72 */
#define _ADC_PHYSICAL_CHANNEL_AN73                (0x0000001FUL) /* ANn73 */
#define _ADC_PHYSICAL_CHANNEL_AN80                (0x00000020UL) /* ANn80 */
#define _ADC_PHYSICAL_CHANNEL_AN81                (0x00000021UL) /* ANn81 */

/* Hold value A/D conversion */
#define _ADC_TH_CHANNEL_0                         (0x00000000UL) /* T&H channel 0 */
#define _ADC_TH_CHANNEL_1                         (0x00000001UL) /* T&H channel 1 */
#define _ADC_TH_CHANNEL_2                         (0x00000002UL) /* T&H channel 2 */
#define _ADC_TH_CHANNEL_3                         (0x00000003UL) /* T&H channel 3 */

/* ADcore self-diagnosis voltage level */
#define _ADC_SELF_DIAGNOSIS_VOLTAGE_0             (0x00000000UL) /* AVREFH x 0 */
#define _ADC_SELF_DIAGNOSIS_VOLTAGE_1_4           (0x00000004UL) /* AVREFH x 1/4 */
#define _ADC_SELF_DIAGNOSIS_VOLTAGE_1_2           (0x00000008UL) /* AVREFH x 1/2 */
#define _ADC_SELF_DIAGNOSIS_VOLTAGE_3_4           (0x0000000CUL) /* AVREFH x 3/4 */
#define _ADC_SELF_DIAGNOSIS_VOLTAGE_1             (0x00000010UL) /* AVREFH x 1 */

/* A/D conversion data path diagnosis A/D conversion (ADVAL mode) */
#define _ADC_FIX_CONVERSION_DATA_AAA              (0x00000000UL) /* Fix the A/D conversion data from ADCore to AAAH */
#define _ADC_FIX_CONVERSION_DATA_555              (0x00000001UL) /* Fix the A/D conversion data from ADCore to 555H */

/*
    Scan Group x Control Register (ADCJnSGCRx)
*/
/* A/D timer simultaneous start enable (ADTSTARTE) */
#define _ADC_TIMER_SIMULTANEOUS_START_DISABLE     (0x00U) /* Disable the A/D timer synchronization start */
#define _ADC_TIMER_SIMULTANEOUS_START_ENABLE      (0x80U) /* Enable the A/D timer synchronization start */
/* A/D conversion simultaneous start enable (ADSTARTE) */
#define _ADC_SIMULTANEOUS_CONVERSION_ENABLE       (0x40U) /* A/D conversion simultaneous start enable */
#define _ADC_SIMULTANEOUS_CONVERSION_DISABLE      (0x00U) /* A/D conversion simultaneous start disable */
/* Scan mode (SCANMD) */
#define _ADC_SG_SCAN_MODE_MULTICYCLE              (0x00U) /* Multicycle scan mode */
#define _ADC_SG_SCAN_MODE_CONTINUOUS              (0x20U) /* Continuous scan mode */
/* Scan end interrupt enable (ADIE) */
#define _ADC_SG_SCAN_END_INT_DISABLE              (0x00U) /* INT_SG is not output */
#define _ADC_SG_SCAN_END_INT_ENABLE               (0x10U) /* INT_SG is output */
/* Trigger mode (TRGMD[1:0]) */
#define _ADC_SG_SOFTWARE_TRIGGER                  (0x00U) /* Software trigger */
#define _ADC_SG_HARDWARE_TRIGGER                  (0x01U) /* Hardware trigger */
#define _ADC_SG_TIMER_SOFTWARE_TRIGGER            (0x02U) /* A/D timer trigger with software trigger */
#define _ADC_SG_TIMER_HARDWARE_TRIGGER            (0x03U) /* A/D timer trigger with hardware trigger */

/*
    PWM-Diag Control Register (ADCJnPWDCR)
*/
/* PWM-Diag enable (PWE) */
#define _ADC_PWM_DIAG_DISABLE                     (0x00U) /* PWM-Diag is disabled */
#define _ADC_PWM_DIAG_ENABLE                      (0x01U) /* PWM-Diag is enabled */

/*
    PWM-Diag Scan Group Control Register (ADCJnPWDSGCR)
*/
/* Trigger mode (TRGMD) */
#define _ADC_PWM_DIAG_HW_TRIGGER_DISABLE          (0x00U) /* PWM-Diag hardware triggers is disabled */
#define _ADC_PWM_DIAG_HW_TRIGGER_ENABLE           (0x01U) /* PWM-Diag hardware triggers is enabled */

/*
    A/D Halt Register (ADCJnADHALTR)
*/
/* Forced termination (HALT) */
#define _ADC_HALT                                 (0x01U) /* All scan groups and A/D timers are forcibly terminated */

/*
    A/D Control Register 1 (ADCJnADCR1)
*/
/* Suspending method (SUSMTD[1:0]) */
#define _ADC_SYNC_SUSPEND                         (0x00U) /* Synchronous suspend */
#define _ADC_ASYNC_SYNC_SUSPEND                   (0x01U) /* Synchronous/asynchronous mixed suspend */
#define _ADC_ASYNC_SUSPEND                        (0x02U) /* Asynchronous suspend */

/*
    A/D Control Register 2 (ADCJnADCR2)
*/
/* Data format (DFMT[2:0]) */
#define _ADC_12BIT_SIGNED_FIXED_POINT             (0x00U) /* Resolution 12-bit signed fixed-point format */
#define _ADC_12BIT_SIGNED_INTEGER                 (0x10U) /* Resolution 12-bit signed integer format */
#define _ADC_12BIT_UNSIGNED_FIXED_POINT           (0x20U) /* Resolution 12-bit unsigned fixed-point format */
#define _ADC_12BIT_UNSIGNED_INTEGER_RIGHT         (0x40U) /* Resolution 12-bit unsigned integer format
                                                                                    (right-justified) */
#define _ADC_12BIT_UNSIGNED_INTEGER_LEFT          (0x50U) /* Resolution 12-bit unsigned integer format
                                                                                     (left-justified) */
/* Addition count select (ADDNT) */
#define _ADC_ADDITION_COUNT_TWICE                 (0x00U) /* Addition twice */
#define _ADC_ADDITION_COUNT_FOUR_TIMES            (0x01U) /* Addition four times */

/*
    Sampling Control Register (ADCJnSMPCR)
*/
/* Extended sampling period (EXSMPT[7:0]) */
#define _ADC_EXTENDED_SAMPLING_60_CYCLES          (0x00000000UL) /* Set to 60 states */
#define _ADC_EXTENDED_SAMPLING_99_CYCLES          (0x00630000UL) /* Set to 99 states */
#define _ADC_EXTENDED_SAMPLING_138_CYCLES         (0x008A0000UL) /* Set to 138 states */
#define _ADC_EXTENDED_SAMPLING_252_CYCLES         (0x00FC0000UL) /* Set to 252 states */
/* Buffer amplifier disable (BUFAMPD) */
#define _ADC_BUFFER_AMPLIFIER_DISABLE             (0x00008000UL) /* No buffer amplifier is used */
#define _ADC_BUFFER_AMPLIFIER_ENABLE              (0x00000000UL) /* A buffer amplifier is used */
/* Sampling Period Select (SMPTS) */
#define _ADC_SAMPLING_PERIOD_DISABLE              (0x00000000UL) /* The SMPT[7:0] bits are not selected */
#define _ADC_SAMPLING_PERIOD_ENABLE               (0x00001000UL) /* The SMPT[7:0] bits are selected */
/* Sampling period (SMPT[7:0]) */
#define _ADC_SAMPLING_18_CYCLES                   (0x00000000UL) /* Set to 18 states */
#define _ADC_SAMPLING_99_CYCLES                   (0x00000063UL) /* Set to 99 states */
#define _ADC_SAMPLING_204_CYCLES                  (0x000000CCUL) /* Set to 204 states */
#define _ADC_SAMPLING_252_CYCLES                  (0x000000FCUL) /* Set to 252 states */

/*
    MPX Current Control Register (ADCJnMPXCURCR)
*/
/* Mask control format (MSKCFMT[3:0]) */
#define _ADC_MASK_FORMAT_0000                     (0x00U) /* Mask Value: 0000 0000 0000 0000 */
#define _ADC_MASK_FORMAT_0001                     (0x01U) /* Mask Value: 0000 0000 0000 0111 */
#define _ADC_MASK_FORMAT_0100                     (0x04U) /* Mask Value: 0000 1111 0000 0000 */
#define _ADC_MASK_FORMAT_0101                     (0x05U) /* Mask Value: 0000 1111 0000 0111 */
#define _ADC_MASK_FORMAT_1000                     (0x08U) /* Mask Value: 1111 0000 0000 0000 */
#define _ADC_MASK_FORMAT_1001                     (0x09U) /* Mask Value: 1111 0000 0000 0111 */
#define _ADC_MASK_FORMAT_1100                     (0x0CU) /* Mask Value: 1111 1111 0000 0000 */
#define _ADC_MASK_FORMAT_1101                     (0x0DU) /* Mask Value: 1111 1111 0000 0111 */

/*
    MPX Interrupt Enable Register (ADCJnMPXINTER)
*/
/* MPX interrupt enable (ADMPXIE) */
#define _ADC_MPX_INT_DISABLE                      (0x00U) /* INT_MPX is not output */
#define _ADC_MPX_INT_ENABLE                       (0x01U) /* INT_MPX is output */

/*
    GTM Entry Scan Group Enable Register (ADCJnGTMENTSGER)
*/
/* GTM entry scan group enable (GTMENTSGxE)*/
#define _ADC_SG0_GTM_ENTRY_ENABLE                 (0x0100U) /* GTM entry when SG0 is activated is enabled */
#define _ADC_SG1_GTM_ENTRY_ENABLE                 (0x0200U) /* GTM entry when SG1 is activated is enabled */
#define _ADC_SG2_GTM_ENTRY_ENABLE                 (0x0400U) /* GTM entry when SG2 is activated is enabled */
#define _ADC_SG3_GTM_ENTRY_ENABLE                 (0x0800U) /* GTM entry when SG3 is activated is enabled */
#define _ADC_SG4_GTM_ENTRY_ENABLE                 (0x1000U) /* GTM entry when SG4 is activated is enabled */

/*
    T&H Sampling Start Control Register (ADCJnTHSMPSTCR)
*/
/* T&H sampling start (SMPST) */
#define _ADC_TH_SAMPLING_START                    (0x01U) /* Sampling for T&H is started */

/*
    T&H Stop Control Register (ADCJnTHSTPCR)
*/
/* T&H sampling stop (THSTP) */
#define _ADC_TH_SAMPLING_STOP                     (0x01U) /* All T&H is stopped */

/*
    T&H Control Register (ADCJnTHCR)
*/
/* Automatic sampling mask (ASMPMSK) */
#define _ADC_TH_SAMPLING_AUTOMATIC                (0x00U) /* Sampling starts automatically */
#define _ADC_TH_SAMPLING_MANUAL                   (0x01U) /* Sampling does not start automatically */

/*
    T&H Group A Control Register (ADCJnTHACR)
*/
/* Hold control enable (HLDCTE) */
#define _ADC_TH_GRPA_HOLD_DISABLE                 (0x00U) /* Hold control is disabled */
#define _ADC_TH_GRPA_HOLD_ENABLE                  (0x20U) /* Hold control is enabled */
/* Hold trigger enable (HLDTE) */
#define _ADC_TH_GRPA_SOFTWARE_TRIGGER             (0x00U) /* Hardware trigger of scan group selected is disabled */
#define _ADC_TH_GRPA_HARDWARE_TRIGGER             (0x10U) /* Hardware trigger of scan group selected is enabled */
/* Selecting scan group (SGS[1:0]) */
#define _ADC_TH_GRPA_SELECT_SG1                   (0x00U) /* SG1 is selected for T&H group A */
#define _ADC_TH_GRPA_SELECT_SG2                   (0x01U) /* SG2 is selected for T&H group A */
#define _ADC_TH_GRPA_SELECT_SG3                   (0x02U) /* SG3 is selected for T&H group A */
#define _ADC_TH_GRPA_SELECT_SG4                   (0x03U) /* SG4 is selected for T&H group A */

/*
    T&H Enable Register (ADCJnTHER)
*/
/* T&H3 enable (TH3E) */
#define _ADC_TH3_DISABLED                         (0x00U) /* T&H3 is disabled */
#define _ADC_TH3_ENABLED                          (0x08U) /* T&H3 is enabled */
/* T&H2 enable (TH2E) */
#define _ADC_TH2_DISABLED                         (0x00U) /* T&H2 is disabled */
#define _ADC_TH2_ENABLED                          (0x04U) /* T&H2 is enabled */
/* T&H1 enable (TH1E) */
#define _ADC_TH1_DISABLED                         (0x00U) /* T&H1 is disabled */
#define _ADC_TH1_ENABLED                          (0x02U) /* T&H1 is enabled */
/* T&H0 enable (TH0E) */
#define _ADC_TH0_DISABLED                         (0x00U) /* T&H0 is disabled */
#define _ADC_TH0_ENABLED                          (0x01U) /* T&H0 is enabled */

/*
    T&H Group Select Register (ADCJnTHGSR)
*/
/* T&H3 group select (TH3GS) */
#define _ADC_TH3_GROUP_A                          (0x0000U) /* T&H3 is selected to group A */
#define _ADC_TH3_GROUP_B                          (0x0040U) /* T&H3 is selected to group B */
/* T&H2 group select (TH2GS) */
#define _ADC_TH2_GROUP_A                          (0x0000U) /* T&H2 is selected to group A */
#define _ADC_TH2_GROUP_B                          (0x0010U) /* T&H2 is selected to group B */
/* T&H1 group select (TH1GS) */
#define _ADC_TH1_GROUP_A                          (0x0000U) /* T&H1 is selected to group A */
#define _ADC_TH1_GROUP_B                          (0x0004U) /* T&H1 is selected to group B */
/* T&H0 group select (TH0GS) */
#define _ADC_TH0_GROUP_A                          (0x0000U) /* T&H0 is selected to group A */
#define _ADC_TH0_GROUP_B                          (0x0001U) /* T&H0 is selected to group B */

/*
    Pin Level Self-Diagnostic Control Register (ADCJnTDCR)
*/
/* T&H path self-diagnosis enable (THSDE) */
#define _ADC_TH_PATH_SELF_DIAGNOSIS_DISABLE       (0x00U) /* T&H path self-diagnosis is disabled */
#define _ADC_TH_PATH_SELF_DIAGNOSIS_ENABLE        (0x80U) /* T&H path self-diagnosis is enabled */
/* Pin-Level self-diagnosis voltage level (TDLV[1:0]) */
#define _ADC_PIN_SELF_DIAGNOSIS_VOLTAGE0          (0x00U) /* High accuracy: Even groups are discharged to AnVSS and odd
                                                             groups are charged to AnVCC
                                                             Low accuracy: Even groups are discharged to AnVSS and odd
                                                             groups are charged to EnVCC */
#define _ADC_PIN_SELF_DIAGNOSIS_VOLTAGE1          (0x01U) /* High accuracy: Even groups are charged to AnVCC and odd
                                                             groups are discharged to AnVSS
                                                             Low accuracy: Even groups are charged to EnVCC and odd
                                                             groups are discharged to AnVSS */
#define _ADC_PIN_SELF_DIAGNOSIS_VOLTAGE2          (0x02U) /* High accuracy: Even groups are discharged to AnVSS and odd
                                                             groups are charged to 1/2xAnVCC
                                                             Low accuracy: Not supported */
#define _ADC_PIN_SELF_DIAGNOSIS_VOLTAGE3          (0x03U) /* High accuracy: Even groups are charged to 1/2xAnVCC and odd
                                                             groups are discharged to AnVSS
                                                             Low accuracy: Not supported */

/*
    Wiring Break Detection Control Register (ADCJnODCR)
*/
/* Addition mode wiring-break detection enable (WADDE) */
#define _ADC_WIRING_BREAK_DETECTION_NORMAL        (0x0000U) /* Wiring-break detection mode is performed in normal
                                                                                                            mode */
#define _ADC_WIRING_BREAK_DETECTION_ADDITION      (0x0100U) /* Wiring-break detection mode is performed in addition
                                                                                                            mode */
/* Wiring-break detection pulse width for wiring-break eetection mode 1 (ODPW[4:0]) */
#define _ADC_DETECTION_PULSE_WIDTH_1              (0x0004U) /* 1 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_2              (0x0005U) /* 2 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_3              (0x0006U) /* 3 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_4              (0x0007U) /* 4 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_5              (0x0008U) /* 5 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_6              (0x0009U) /* 6 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_7              (0x000AU) /* 7 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_8              (0x000BU) /* 8 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_9              (0x000CU) /* 9 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_10             (0x000DU) /* 10 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_11             (0x000EU) /* 11 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_12             (0x000FU) /* 12 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_13             (0x0010U) /* 13 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_14             (0x0011U) /* 14 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_15             (0x0012U) /* 15 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_16             (0x0013U) /* 16 state (of internal clock) */
#define _ADC_DETECTION_PULSE_WIDTH_17             (0x0014U) /* 17 state (of internal clock) */

/*
    PWM-Diag Upper/Lower Limit Check Interrupt Enable Register (ADCJnPWVCLMINTER)
*/
/* PWM-Diag upper/lower limit check interrupt enable (PWADULIE) */
#define _ADC_PWM_DIAG_LIMIT_INT_DISABLE           (0x00U) /* An upper/lower limit check interrupt is not output */
#define _ADC_PWM_DIAG_LIMIT_INT_ENABLE            (0x01U) /* An upper/lower limit check interrupt is output */

/*
    Safety Control Register (ADCJnSFTCR)
*/
/* Trigger overlap check error interrupt enable (TOCEIE) */
#define _ADC_OVERLAP_ERROR_INT_DISABLE            (0x00U) /* Disable trigger overlap check error interrupt */
#define _ADC_OVERLAP_ERROR_INT_ENABLE             (0x40U) /* Enable trigger overlap check error interrupt */
/* Read and clear enable (RDCLRE) */
#define _ADC_READ_CLEAR_DISABLED                  (0x00U) /* The A/D conversion result is not cleared by reading */
#define _ADC_READ_CLEAR_ENABLED                   (0x10U) /* The A/D conversion result is cleared by reading */
/* Overwrite error interrupt enable (OWEIE) */
#define _ADC_OVERWRITE_ERROR_INT_DISABLE          (0x00U) /* Disable overwrite error interrupt */
#define _ADC_OVERWRITE_ERROR_INT_ENABLE           (0x04U) /* Enable overwrite error interrupt */
/* Parity error interrupt enable (PEIE) */
#define _ADC_PARITY_ERROR_INT_DISABLE             (0x00U) /* Disable parity error interrupt */
#define _ADC_PARITY_ERROR_INT_ENABLE              (0x02U) /* Enable parity error interrupt */
/* ID error interrupt enable (IDEIE) */
#define _ADC_ID_ERROR_INT_DISABLE                 (0x00U) /* Disable ID error interrupt */
#define _ADC_ID_ERROR_INT_ENABLE                  (0x01U) /* Enable ID error interrupt */

/*
    Trigger Overlap Check Control Register (ADCJnTOCCR)
*/
/* Trigger overlap check function enable (TOCE)*/
#define _ADC_TRIGGER_OVERLAP_CHECK_DISABLE        (0x00U) /* Trigger overlap check disable */
#define _ADC_TRIGGER_OVERLAP_CHECK_ENABLE         (0x01U) /* Trigger overlap check enable */

/*
    Upper/Lower Limit Check Interrupt Enable Register 1 (ADCJnVCLMINTER1)
*/
/* Upper/Lower limit check interrupt enable (ADUL31IE) */
#define _ADC_VIR_CHAN31_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN31_LIMIT_INT_ENABLE          (0x80000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL30IE) */
#define _ADC_VIR_CHAN30_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN30_LIMIT_INT_ENABLE          (0x40000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL29IE) */
#define _ADC_VIR_CHAN29_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN29_LIMIT_INT_ENABLE          (0x20000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL28IE) */
#define _ADC_VIR_CHAN28_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN28_LIMIT_INT_ENABLE          (0x10000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL27IE) */
#define _ADC_VIR_CHAN27_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN27_LIMIT_INT_ENABLE          (0x08000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL26IE) */
#define _ADC_VIR_CHAN26_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN26_LIMIT_INT_ENABLE          (0x04000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL25IE) */
#define _ADC_VIR_CHAN25_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN25_LIMIT_INT_ENABLE          (0x02000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL24IE) */
#define _ADC_VIR_CHAN24_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN24_LIMIT_INT_ENABLE          (0x01000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL23IE) */
#define _ADC_VIR_CHAN23_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN23_LIMIT_INT_ENABLE          (0x00800000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL22IE) */
#define _ADC_VIR_CHAN22_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN22_LIMIT_INT_ENABLE          (0x00400000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL21IE) */
#define _ADC_VIR_CHAN21_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN21_LIMIT_INT_ENABLE          (0x00200000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL20IE) */
#define _ADC_VIR_CHAN20_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN20_LIMIT_INT_ENABLE          (0x00100000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL19IE) */
#define _ADC_VIR_CHAN19_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN19_LIMIT_INT_ENABLE          (0x00080000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL18IE) */
#define _ADC_VIR_CHAN18_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN18_LIMIT_INT_ENABLE          (0x00040000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL17IE) */
#define _ADC_VIR_CHAN17_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN17_LIMIT_INT_ENABLE          (0x00020000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL16IE) */
#define _ADC_VIR_CHAN16_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN16_LIMIT_INT_ENABLE          (0x00010000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL15IE) */
#define _ADC_VIR_CHAN15_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN15_LIMIT_INT_ENABLE          (0x00008000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL14IE) */
#define _ADC_VIR_CHAN14_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN14_LIMIT_INT_ENABLE          (0x00004000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL13IE) */
#define _ADC_VIR_CHAN13_LIMIT_INT_ENABLE          (0x00002000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
#define _ADC_VIR_CHAN13_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
/* Upper/Lower limit check interrupt enable (ADUL12IE) */
#define _ADC_VIR_CHAN12_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN12_LIMIT_INT_ENABLE          (0x00001000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL11IE) */
#define _ADC_VIR_CHAN11_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN11_LIMIT_INT_ENABLE          (0x00000800UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL10IE) */
#define _ADC_VIR_CHAN10_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN10_LIMIT_INT_ENABLE          (0x00000400UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL09IE) */
#define _ADC_VIR_CHAN09_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN09_LIMIT_INT_ENABLE          (0x00000200UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL08IE) */
#define _ADC_VIR_CHAN08_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN08_LIMIT_INT_ENABLE          (0x00000100UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL07IE) */
#define _ADC_VIR_CHAN07_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN07_LIMIT_INT_ENABLE          (0x00000080UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL06IE) */
#define _ADC_VIR_CHAN06_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN06_LIMIT_INT_ENABLE          (0x00000040UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL05IE) */
#define _ADC_VIR_CHAN05_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN05_LIMIT_INT_ENABLE          (0x00000020UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL04IE) */
#define _ADC_VIR_CHAN04_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN04_LIMIT_INT_ENABLE          (0x00000010UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL03IE) */
#define _ADC_VIR_CHAN03_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN03_LIMIT_INT_ENABLE          (0x00000008UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL02IE) */
#define _ADC_VIR_CHAN02_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN02_LIMIT_INT_ENABLE          (0x00000004UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL01IE) */
#define _ADC_VIR_CHAN01_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN01_LIMIT_INT_ENABLE          (0x00000002UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL00IE) */
#define _ADC_VIR_CHAN00_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN00_LIMIT_INT_ENABLE          (0x00000001UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */

/*
    Upper/Lower Limit Check Interrupt Enable Register 2 (ADCJnVCLMINTER2)
*/
/* Upper/Lower limit check interrupt enable (ADUL63IE) */
#define _ADC_VIR_CHAN63_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN63_LIMIT_INT_ENABLE          (0x80000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL62IE) */
#define _ADC_VIR_CHAN62_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN62_LIMIT_INT_ENABLE          (0x40000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL61IE) */
#define _ADC_VIR_CHAN61_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN61_LIMIT_INT_ENABLE          (0x20000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL60IE) */
#define _ADC_VIR_CHAN60_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN60_LIMIT_INT_ENABLE          (0x10000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL59IE) */
#define _ADC_VIR_CHAN59_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN59_LIMIT_INT_ENABLE          (0x08000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL58IE) */
#define _ADC_VIR_CHAN58_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN58_LIMIT_INT_ENABLE          (0x04000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL57IE) */
#define _ADC_VIR_CHAN57_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN57_LIMIT_INT_ENABLE          (0x02000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL56IE) */
#define _ADC_VIR_CHAN56_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN56_LIMIT_INT_ENABLE          (0x01000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL55IE) */
#define _ADC_VIR_CHAN55_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN55_LIMIT_INT_ENABLE          (0x00800000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL54IE) */
#define _ADC_VIR_CHAN54_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN54_LIMIT_INT_ENABLE          (0x00400000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL53IE) */
#define _ADC_VIR_CHAN53_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN53_LIMIT_INT_ENABLE          (0x00200000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL52IE) */
#define _ADC_VIR_CHAN52_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN52_LIMIT_INT_ENABLE          (0x00100000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL51IE) */
#define _ADC_VIR_CHAN51_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN51_LIMIT_INT_ENABLE          (0x00080000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL50IE) */
#define _ADC_VIR_CHAN50_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN50_LIMIT_INT_ENABLE          (0x00040000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL49IE) */
#define _ADC_VIR_CHAN49_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN49_LIMIT_INT_ENABLE          (0x00020000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL48IE) */
#define _ADC_VIR_CHAN48_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN48_LIMIT_INT_ENABLE          (0x00010000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL47IE) */
#define _ADC_VIR_CHAN47_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN47_LIMIT_INT_ENABLE          (0x00008000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL46IE) */
#define _ADC_VIR_CHAN46_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN46_LIMIT_INT_ENABLE          (0x00004000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL45IE) */
#define _ADC_VIR_CHAN45_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN45_LIMIT_INT_ENABLE          (0x00002000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL44IE) */
#define _ADC_VIR_CHAN44_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN44_LIMIT_INT_ENABLE          (0x00001000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL43IE) */
#define _ADC_VIR_CHAN43_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN43_LIMIT_INT_ENABLE          (0x00000800UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL42IE) */
#define _ADC_VIR_CHAN42_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN42_LIMIT_INT_ENABLE          (0x00000400UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL41IE) */
#define _ADC_VIR_CHAN41_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN41_LIMIT_INT_ENABLE          (0x00000200UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL40IE) */
#define _ADC_VIR_CHAN40_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN40_LIMIT_INT_ENABLE          (0x00000100UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL39IE) */
#define _ADC_VIR_CHAN39_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN39_LIMIT_INT_ENABLE          (0x00000080UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL38IE) */
#define _ADC_VIR_CHAN38_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN38_LIMIT_INT_ENABLE          (0x00000040UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL37IE) */
#define _ADC_VIR_CHAN37_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN37_LIMIT_INT_ENABLE          (0x00000020UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL36IE) */
#define _ADC_VIR_CHAN36_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN36_LIMIT_INT_ENABLE          (0x00000010UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL35IE) */
#define _ADC_VIR_CHAN35_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN35_LIMIT_INT_ENABLE          (0x00000008UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL34IE) */
#define _ADC_VIR_CHAN34_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN34_LIMIT_INT_ENABLE          (0x00000004UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL33IE) */
#define _ADC_VIR_CHAN33_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN33_LIMIT_INT_ENABLE          (0x00000002UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */
/* Upper/Lower limit check interrupt enable (ADUL32IE) */
#define _ADC_VIR_CHAN32_LIMIT_INT_DISABLE         (0x00000000UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                         not output */
#define _ADC_VIR_CHAN32_LIMIT_INT_ENABLE          (0x00000001UL) /* An upper/lower limit check interrupt (INT_UL) is
                                                                                                             output */

/*
    Scan Group x Start Control Register (ADCJnSGSTCRx)
*/
/* Scan group start (SGST) */
#define _ADC_START                                (0x01U) /* A/D conversion start */

/*
    Scan Group x Stop Control Register (ADCJnSGSTPCRx)
*/
/* Scan group stop (SGSTP) */
#define _ADC_STOP                                 (0x01U) /* A/D conversion stop */

/*
    A/D Timer x Start Control Register (ADCJnADTSTCRx)
*/
/* A/D timer start (ADTST) */
#define _ADC_TIMER_START                          (0x01U) /* A/D timer start */

/*
    A/D Timer x End Control Register (ADCJnADTENDCRx)
*/
/* A/D timer end (ADTEND) */
#define _ADC_TIMER_END                            (0x01U) /* A/D timer end */

/*
    A/D Synchronization Start Control Register (ADCJnADSYNSTCR)
*/
/* A/D conversion simultaneous start (ADSTART) */
#define _ADC_SYNC_START                           (0x01U) /* Simultaneously start A/D conversion of scan groups */

/*
    A/D Timer Synchronization Start Control Register (ADCJnADTSYNSTCR)
*/
/* A/D timer simultaneous start (ADTSTART) */
#define _ADC_TIMER_SYNC_START                     (0x01U) /* Simultaneously start A/D timer count operation */

/*
    T&H Group A Hold Start Control Register (ADCJnTHAHLDSTCR)
*/
/* T&H hold start (HLDST) */
#define _ADC_TH_GROUP_A_START                     (0x01U) /* Start hold of T&H group A */

/*
    Voltage Monitoring Voltage Divider Control Register 1 (ADCJnVMONVDCR1)
*/
/* Voltage divider enable (VDE1) */
#define _ADC_VDE1_VALUE_0                         (0x00U) /* VDE1 value is 0 */
#define _ADC_VDE1_VALUE_1                         (0x01U) /* VDE1 value is 1 */

/*
    Voltage Monitoring Voltage Divider Control Register 2 (ADCJnVMONVDCR2)
*/
/* Voltage divider enable (VDE2) */
#define _ADC_VDE2_VALUE_0                         (0x00U) /* VDE2 value is 0 */
#define _ADC_VDE2_VALUE_1                         (0x01U) /* VDE2 value is 1 */

/*
    Filter Counter Control Register VCC (AVSEGVCCCNTCR)
*/
/* Filter enable (AVSEGVCCENB) */
#define _ADC_AVSEG_VCC_FILTER_DISABLE             (0x00000000UL) /* Disable VCC filter */
#define _ADC_AVSEG_VCC_FILTER_ENABLE              (0x10000000UL) /* Enable VCC filter */

/*
    Filter Counter Control Register EVCC (AVSEGEVCCCNTCR)
*/
/* Filter enable (AVSEGEVCCENB) */
#define _ADC_AVSEG_E0VCC_FILTER_DISABLE           (0x00000000UL) /* Disable E0VCC filter */
#define _ADC_AVSEG_E0VCC_FILTER_ENABLE            (0x10000000UL) /* Enable E0VCC filter */

/*
    Filter Counter Control Register ISOVDD (AVSEGISOVDDCNTCR)
*/
/* Filter enable (AVSEGISOVDDENB) */
#define _ADC_AVSEG_ISOVDD_FILTER_DISABLE          (0x00000000UL) /* Disable ISOVDD filter */
#define _ADC_AVSEG_ISOVDD_FILTER_ENABLE           (0x10000000UL) /* Enable ISOVDD filter */

/*
    Filter Counter Control Register AWOVDD (AVSEGAWOVDDCNTCR)
*/
/* Filter enable (AVSEGAWOVDDENB) */
#define _ADC_AVSEG_AWOVDD_FILTER_DISABLE          (0x00000000UL) /* Disable AWOVDD filter */
#define _ADC_AVSEG_AWOVDD_FILTER_ENABLE           (0x10000000UL) /* Enable AWOVDD filter */

/*
    Secondary Voltage Monitor Error Clear Register (AVSEGSECVMONCLR)
*/
/* Upper limit voltage error AWOVDD clear (AWOVDD_ULMEC) */
#define _ADC_AWOVDD_UP_LIMIT_ERROR_CLEAR          (0x00080000UL) /* Upper limit voltage error AWOVDD clear */
/* Upper limit voltage error ISOVDD clear (ISOVDD_ULMEC) */
#define _ADC_ISOVDD_UP_LIMIT_ERROR_CLEAR          (0x00040000UL) /* Upper limit voltage error ISOVDD clear */
/* Upper limit voltage error E0VCC clear (EVCC_ULMEC) */
#define _ADC_EVCC_UP_LIMIT_ERROR_CLEAR            (0x00020000UL) /* Upper limit voltage error EVCC clear */
/* Upper limit voltage error VCC clear (VCC_ULMEC) */
#define _ADC_VCC_UP_LIMIT_ERROR_CLEAR             (0x00010000UL) /* Upper limit voltage error VCC clear */
/* Lower limit voltage error AWOVDD clear (AWOVDD_LLMEC) */
#define _ADC_AWOVDD_LOW_LIMIT_ERROR_CLEAR         (0x00000008UL) /* Lower limit voltage error AWOVDD clear */
/* Lower limit voltage error ISOVDD clear (ISOVDD_LLMEC) */
#define _ADC_ISOVDD_LOW_LIMIT_ERROR_CLEAR         (0x00000004UL) /* Lower limit voltage error ISOVDD clear */
/* Lower limit voltage error E0VCC clear (EVCC_LLMEC) */
#define _ADC_EVCC_LOW_LIMIT_ERROR_CLEAR           (0x00000002UL) /* Lower limit voltage error EVCC clear */
/* Lower limit voltage error VCC clear (VCC_LLMEC) */
#define _ADC_VCC_LOW_LIMIT_ERROR_CLEAR            (0x00000001UL) /* Lower limit voltage error VCC clear */

/*
    Scan Group x Start Trigger Control Register (ADCJnSGTSELx)
*/
/* A/D conversion trigger (hardware trigger) select (TxSEL5) */
#define _ADC_SCAN_GRP_TRIGGER_SEQADTRG            (0x00000020UL) /* Trigger signal SEQADTRG */
/* A/D conversion trigger (hardware trigger) select (TxSEL4) */
#define _ADC_SCAN_GRP_TRIGGER_ADCJ2TRG            (0x00000010UL) /* Trigger signal ADCJ2TRGn */
/* A/D conversion trigger (hardware trigger) select (TxSEL3) */
#define _ADC_SCAN_GRP_TRIGGER_INTTAUJ3I3          (0x00000008UL) /* Trigger signal INTTAUJ3I3 */
/* A/D conversion trigger (hardware trigger) select (TxSEL2) */
#define _ADC_SCAN_GRP_TRIGGER_INTTAUJ2I3          (0x00000004UL) /* Trigger signal INTTAUJ2I3 */
/* A/D conversion trigger (hardware trigger) select (TxSEL1) */
#define _ADC_SCAN_GRP_TRIGGER_INTTAUD2I15         (0x00000002UL) /* Trigger signal INTTAUD2I15 */
/* A/D conversion trigger (hardware trigger) select (TxSEL0) */
#define _ADC_SCAN_GRP_TRIGGER_INTTAUD2I7          (0x00000001UL) /* Trigger signal INTTAUD2I7 */

/*
    A/D Converter Trigger Edge Control Register (PIC2ADCJnEDGSEL)
*/
/* Selects an effective edge of ADCJn scan group 4 (PIC2ADCJnEDGSEL[9:8]) */
#define _ADC_TRG4_VALID_EDGE_RISING               (0x0000U) /* Rising edge */
#define _ADC_TRG4_VALID_EDGE_FALLING              (0x0100U) /* Falling edge */
#define _ADC_TRG4_VALID_EDGE_BOTH                 (0x0200U) /* Both edge */
/* Selects an effective edge of ADCJn scan group 3 (PIC2ADCJnEDGSEL[7:6]) */
#define _ADC_TRG3_VALID_EDGE_RISING               (0x0000U) /* Rising edge */
#define _ADC_TRG3_VALID_EDGE_FALLING              (0x0040U) /* Falling edge */
#define _ADC_TRG3_VALID_EDGE_BOTH                 (0x0080U) /* Both edge */
/* Selects an effective edge of ADCJn scan group 2 (PIC2ADCJnEDGSEL[5:4]) */
#define _ADC_TRG2_VALID_EDGE_RISING               (0x0000U) /* Rising edge */
#define _ADC_TRG2_VALID_EDGE_FALLING              (0x0010U) /* Falling edge */
#define _ADC_TRG2_VALID_EDGE_BOTH                 (0x0020U) /* Both edge */
/* Selects an effective edge of ADCJn scan group 1 (PIC2ADCJnEDGSEL[3:2]) */
#define _ADC_TRG1_VALID_EDGE_RISING               (0x0000U) /* Rising edge */
#define _ADC_TRG1_VALID_EDGE_FALLING              (0x0004U) /* Falling edge */
#define _ADC_TRG1_VALID_EDGE_BOTH                 (0x0008U) /* Both edge */
/* Selects an effective edge of ADCJn scan group 0 (PIC2ADCJnEDGSEL[1:0]) */
#define _ADC_TRG0_VALID_EDGE_RISING               (0x0000U) /* Rising edge */
#define _ADC_TRG0_VALID_EDGE_FALLING              (0x0001U) /* Falling edge */
#define _ADC_TRG0_VALID_EDGE_BOTH                 (0x0002U) /* Both edge */

/*
    A/D Converter n Trigger Select Control Register j (PIC2ADCJnTSELj)
*/
/* ENCAn interrupt signal selected by PIC2ADTEN42j (ADCJnTSELj28) */
#define _ADC_SCAN_GRP_TRIGGER_ENCA                (0x10000000UL) /* Trigger signal ENCAn */
/* INTTSG31I12 signal (ADCJnTSELj27) */
#define _ADC_SCAN_GRP_TRIGGER_INTTSG31I12         (0x08000000UL) /* Trigger signal INTTSG31I12 */
/* INTTSG31I11 signal (ADCJnTSELj26) */
#define _ADC_SCAN_GRP_TRIGGER_INTTSG31I11         (0x04000000UL) /* Trigger signal INTTSG31I11 */
/* INTTSG31I8 signal (ADCJnTSELj25) */
#define _ADC_SCAN_GRP_TRIGGER_INTTSG31I8          (0x02000000UL) /* Trigger signal INTTSG31I8 */
/* INTTSG31I7 signal (ADCJnTSELj24) */
#define _ADC_SCAN_GRP_TRIGGER_INTTSG31I7          (0x01000000UL) /* Trigger signal INTTSG31I7 */
/* INTTSG31I4 signal (ADCJnTSELj23) */
#define _ADC_SCAN_GRP_TRIGGER_INTTSG31I4          (0x00800000UL) /* Trigger signal INTTSG31I4 */
/* INTTSG31I3 signal (ADCJnTSELj22) */
#define _ADC_SCAN_GRP_TRIGGER_INTTSG31I3          (0x00400000UL) /* Trigger signal INTTSG31I3 */
/* TAPATADOUT1 signal (ADCJnTSELj21) */
#define _ADC_SCAN_GRP_TRIGGER_TAPATADOUT1         (0x00200000UL) /* Trigger signal TAPATADOUT1 */
/* TAPATADOUT0 signal (ADCJnTSELj20) */
#define _ADC_SCAN_GRP_TRIGGER_TAPATADOUT0         (0x00100000UL) /* Trigger signal TAPATADOUT0 */
/* INTTSG30I12 signal (ADCJnTSELj19) */
#define _ADC_SCAN_GRP_TRIGGER_INTTSG30I12         (0x00080000UL) /* Trigger signal INTTSG30I12 */
/* INTTSG30I11 signal (ADCJnTSELj18) */
#define _ADC_SCAN_GRP_TRIGGER_INTTSG30I11         (0x00040000UL) /* Trigger signal INTTSG30I11 */
/* INTTSG30I8 signal (ADCJnTSELj17) */
#define _ADC_SCAN_GRP_TRIGGER_INTTSG30I8          (0x00020000UL) /* Trigger signal INTTSG30I8 */
/* INTTSG30I7 signal (ADCJnTSELj16) */
#define _ADC_SCAN_GRP_TRIGGER_INTTSG30I7          (0x00010000UL) /* Trigger signal INTTSG30I7 */
/* INTTSG30I4 signal (ADCJnTSELj15) */
#define _ADC_SCAN_GRP_TRIGGER_INTTSG30I4          (0x00008000UL) /* Trigger signal INTTSG30I4 */
/* INTTSG30I3 signal (ADCJnTSELj14) */
#define _ADC_SCAN_GRP_TRIGGER_INTTSG30I3          (0x00004000UL) /* Trigger signal INTTSG30I3 */
/* ADCJnTRG4 signal (ADCJnTSELj13) */
#define _ADC_SCAN_GRP_TRIGGER_ADCJnTRG4           (0x00002000UL) /* Trigger signal ADCJnTRG4 */
/* ADCJnTRG3 signal (ADCJnTSELj12) */
#define _ADC_SCAN_GRP_TRIGGER_ADCJnTRG3           (0x00001000UL) /* Trigger signal ADCJnTRG3 */
/* ADCJnTRG2 signal (ADCJnTSELj11) */
#define _ADC_SCAN_GRP_TRIGGER_ADCJnTRG2           (0x00000800UL) /* Trigger signal ADCJnTRG2 */
/* ADCJnTRG1 signal (ADCJnTSELj10) */
#define _ADC_SCAN_GRP_TRIGGER_ADCJnTRG1           (0x00000400UL) /* Trigger signal ADCJnTRG1 */
/* ADCJnTRG0 signal (ADCJnTSELj09) */
#define _ADC_SCAN_GRP_TRIGGER_ADCJnTRG0           (0x00000200UL) /* Trigger signal ADCJnTRG0 */
/* TSG31ADTRG1 signal (ADCJnTSELj08) */
#define _ADC_SCAN_GRP_TRIGGER_TSG31ADTRG1         (0x00000100UL) /* Trigger signal TSG31ADTRG1 */
/* TSG31ADTRG0 signal (ADCJnTSELj07) */
#define _ADC_SCAN_GRP_TRIGGER_TSG31ADTRG0         (0x00000080UL) /* Trigger signal TSG31ADTRG0 */
/* TSG30ADTRG1 signal (ADCJnTSELj06) */
#define _ADC_SCAN_GRP_TRIGGER_TSG30ADTRG1         (0x00000040UL) /* Trigger signal TSG30ADTRG1 */
/* TSG30ADTRG0 signal (ADCJnTSELj05) */
#define _ADC_SCAN_GRP_TRIGGER_TSG30ADTRG0         (0x00000020UL) /* Trigger signal TSG30ADTRG0 */
/* INTTAUJ1I3 interrupt signal (ADCJnTSELj04) */
#define _ADC_SCAN_GRP_TRIGGER_INTTAUJ1I3          (0x00000010UL) /* Trigger signal INTTAUJ1I3 */
/* INTTAUJ0I3 interrupt signal (ADCJnTSELj03) */
#define _ADC_SCAN_GRP_TRIGGER_INTTAUJ0I3          (0x00000008UL) /* Trigger signal INTTAUJ0I3 */
/* GTM timer output selected by PIC2ADTEN50j, PIC2ADTEN60j,PIC2ADTEN70j, PIC2ADTEN80j (ADCJnTSELj02) */
#define _ADC_SCAN_GRP_TRIGGER_GTM                 (0x00000004UL) /* Trigger signal GTM timer output */
/* TAUD1 interrupt signal selected by PIC2ADTEN41j (ADCJnTSELj01) */
#define _ADC_SCAN_GRP_TRIGGER_TAUD1               (0x00000002UL) /* Trigger signal TAUD1 interrupt */
/* TAUD0 interrupt signal selected by PIC2ADTEN40j (ADCJnTSELj00) */
#define _ADC_SCAN_GRP_TRIGGER_TAUD0               (0x00000001UL) /* Trigger signal TAUD0 interrupt */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _ADC0_VCHANNEL_DATA_BASE                  (0xFFCA01A0UL) /* ADCJ0DRj register bass address */
#define _ADC1_VCHANNEL_DATA_BASE                  (0xFFF201A0UL) /* ADCJ1DRj register bass address */
#define _ADC2_VCHANNEL_DATA_BASE                  (0xFF9A21A0UL) /* ADCJ2DRj register bass address */
#define _ADC0_PWD_VCHANNEL_DATA_BASE              (0xFFCA0260UL) /* ADCJ0PWDDR register bass address */
#define _ADC1_PWD_VCHANNEL_DATA_BASE              (0xFFF20260UL) /* ADCJ1PWDDR register bass address */
#define _ADC2_PWD_VCHANNEL_DATA_BASE              (0xFF9A2260UL) /* ADCJ2PWDDR register bass address */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/* Start user code for function. Do not edit comment generated here */
typedef enum
{
  R_AD_OK = 0u,
  R_AD_ERROR,
} r_AD_Error_t; 
/* End user code. Do not edit comment generated here */
#endif
