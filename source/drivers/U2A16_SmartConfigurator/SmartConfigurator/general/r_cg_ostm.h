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
* File Name        : r_cg_ostm.h
* Version          : 1.0.140
* Device(s)        : R7F702300BFABA
* Description      : General header file for OSTM peripheral.
***********************************************************************************************************************/

#ifndef OSTM_H
#define OSTM_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    OSTM Count Start Trigger Register (OSTMnTS)
*/
/* Start the counter (OSTMnTS) */
#define _OSTM_COUNTER_START                       (0x01U) /* Starts the counter */

/*
    OSTM Count Stop Trigger Register (OSTMnTT)
*/
/* Stop the counter (OSTMnTT) */
#define _OSTM_COUNTER_STOP                        (0x01U) /* Stops the counter */

/*
    OSTM Output Register (OSTMnTO)
*/
/* Specify/read the level of OSTMnTTOUT output signals. (OSTMnTO) */
#define _OSTM_OUTPUT_LOW_LEVEL                    (0x00U) /* Low level */
#define _OSTM_OUTPUT_HIGH_LEVEL                   (0x01U) /* High level */

/*
    OSTM Output Enable Register (OSTMnTOE)
*/
/* Specify the OSTMnTTOUT output mode. (OSTMnTOE) */
#define _OSTM_OUTPUT_MODE_SOFTWARE                (0x00U) /* Software control mode */
#define _OSTM_OUTPUT_MODE_TOGGLING                (0x01U) /* Timer-output toggling mode */

/*
    OSTM Control Register (OSTMnCTL)
*/
/* OSTM Interrupt enable (OSTMnIE) */
#define _OSTM_INT_REQUEST_DISABLE                 (0x00U) /* OSTMn interrupt request is disabled. */
#define _OSTM_INT_REQUEST_ENABLE                  (0x80U) /* OSTMn interrupt request is enabled */
/* Control of the counter operation at counter operation start (OSTMnMD2) */
#define _OSTM_CNT_RELOAD_ENABLE                   (0x00U) /* OSTMnCNT is loaded at counter operation start */
#define _OSTM_CNT_RELOAD_DISABLE                  (0x04U) /* OSTMnCNT is not loaded at counter operation start */
/* Specify the operating mode for the counter (OSTMnMD1) */
#define _OSTM_MODE_INTERVAL_TIMER                 (0x00U) /* Interval timer mode */
#define _OSTM_MODE_FREE_RUNNING                   (0x02U) /* Free-running comparison mode */
/* Specify the operating mode for the counter (OSTMnMD0) */
#define _OSTM_START_INTERRUPT_DISABLE             (0x00U) /* Disables the interrupts when counting starts */
#define _OSTM_START_INTERRUPT_ENABLE              (0x01U) /* Enables the interrupts when counting starts */

/*
    OSTM Clock Select Register (IC0CKSELn)
*/
/* Select the counter-clock-enable signal for OSTMn (IC0TMENn) */
#define _OSTM_COUNT_CLOCK_PCLK                    (0x0000U) /* PCLK is selected as the source of the clock signal */
#define _OSTM_COUNT_CLOCK_TCKE                    (0x8000U) /* Selects the peripheral module as
                                                               the counter-clock-enable signal */
/* Select the module for counter-clock-enable signal (IC0TMSELn) */
#define _OSTM_CLOCK_SIGNAL_TAUD0                  (0x0000U) /* TAUD0 */
#define _OSTM_CLOCK_SIGNAL_TAUD1                  (0x1000U) /* TAUD1 */
#define _OSTM_CLOCK_SIGNAL_TAUJ0                  (0x2000U) /* TAUJ0 */
#define _OSTM_CLOCK_SIGNAL_TAUJ1                  (0x3000U) /* TAUJ1 */
/* Select the TAUJ1 channel for counter-clock-enable signal (IC0CKSELn3) */
#define _OSTM_CLOCK_SIGNAL_TAUJ1_CHANNEL0         (0x0000U) /* TAUJ1 channel 0 */
#define _OSTM_CLOCK_SIGNAL_TAUJ1_CHANNEL1         (0x0400U) /* TAUJ1 channel 1 */
#define _OSTM_CLOCK_SIGNAL_TAUJ1_CHANNEL2         (0x0800U) /* TAUJ1 channel 2 */
#define _OSTM_CLOCK_SIGNAL_TAUJ1_CHANNEL3         (0x0C00U) /* TAUJ1 channel 3 */
/* Select the TAUJ0 channel for counter-clock-enable signal (IC0CKSELn2) */
#define _OSTM_CLOCK_SIGNAL_TAUJ0_CHANNEL0         (0x0000U) /* TAUJ0 channel 0 */
#define _OSTM_CLOCK_SIGNAL_TAUJ0_CHANNEL1         (0x0100U) /* TAUJ0 channel 1 */
#define _OSTM_CLOCK_SIGNAL_TAUJ0_CHANNEL2         (0x0200U) /* TAUJ0 channel 2 */
#define _OSTM_CLOCK_SIGNAL_TAUJ0_CHANNEL3         (0x0300U) /* TAUJ0 channel 3 */
/* Select the TAUD1 channel for counter-clock-enable signal (IC0CKSELn1) */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL0         (0x0000U) /* TAUD1 channel 0 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL1         (0x0010U) /* TAUD1 channel 1 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL2         (0x0020U) /* TAUD1 channel 2 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL3         (0x0030U) /* TAUD1 channel 3 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL4         (0x0040U) /* TAUD1 channel 4 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL5         (0x0050U) /* TAUD1 channel 5 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL6         (0x0060U) /* TAUD1 channel 6 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL7         (0x0070U) /* TAUD1 channel 7 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL8         (0x0080U) /* TAUD1 channel 8 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL9         (0x0090U) /* TAUD1 channel 9 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL10        (0x00A0U) /* TAUD1 channel 10 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL11        (0x00B0U) /* TAUD1 channel 11 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL12        (0x00C0U) /* TAUD1 channel 12 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL13        (0x00D0U) /* TAUD1 channel 13 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL14        (0x00E0U) /* TAUD1 channel 14 */
#define _OSTM_CLOCK_SIGNAL_TAUD1_CHANNEL15        (0x00F0U) /* TAUD1 channel 15 */
/* Select the TAUD0 channel for counter-clock-enable signal (IC0CKSELn0) */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL0         (0x0000U) /* TAUD0 channel 0 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL1         (0x0001U) /* TAUD0 channel 1 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL2         (0x0002U) /* TAUD0 channel 2 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL3         (0x0003U) /* TAUD0 channel 3 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL4         (0x0004U) /* TAUD0 channel 4 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL5         (0x0005U) /* TAUD0 channel 5 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL6         (0x0006U) /* TAUD0 channel 6 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL7         (0x0007U) /* TAUD0 channel 7 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL8         (0x0008U) /* TAUD0 channel 8 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL9         (0x0009U) /* TAUD0 channel 9 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL10        (0x000AU) /* TAUD0 channel 10 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL11        (0x000BU) /* TAUD0 channel 11 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL12        (0x000CU) /* TAUD0 channel 12 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL13        (0x000DU) /* TAUD0 channel 13 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL14        (0x000EU) /* TAUD0 channel 14 */
#define _OSTM_CLOCK_SIGNAL_TAUD0_CHANNEL15        (0x000FU) /* TAUD0 channel 15 */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
