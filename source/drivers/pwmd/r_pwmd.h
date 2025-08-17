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
* Copyright (C) 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name         : r_pwmd.h
* Component Version : 1.0.0
* Description       : Header file for r_pwmd.c.
***********************************************************************************************************************/
#ifndef R_PWMD_H
#define R_PWMD_H

/***********************************************************************************************************************
Public functions
***********************************************************************************************************************/
void R_PWMD_Channel66Init(void);
void R_PWMD_Channel67Init(void);
void R_PWMD_Channel68Init(void);
void R_PWMD_Channel66DutyUpdate(uint32_t duty);
void R_PWMD_Channel67DutyUpdate(uint32_t duty);
void R_PWMD_Channel68DutyUpdate(uint32_t duty);
void R_PWMD_StartChannel(uint32_t PWGC_Channel);
void R_PWMD_StopChannel(uint32_t PWGC_Channel);
void R_PWMD_SetPeriod(void);
void R_PWMD_ClockInit(void);
void R_PWMD_DiagInit(void);
void R_PWMD_DiagStart(void);
void R_PWMD_DiagStop(void);
uint16_t R_PWMD_PwmDiag_read(void);
void R_PWMD_PwmDiag_status(void);

#endif /* R_PWMD_H */
