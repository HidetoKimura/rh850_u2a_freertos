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
* File Name        : STBC.h
* Component Version: 1.3.1
* Device(s)        : R7F702300BFABA
* Description      : This file implements device driver for STBC.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_stbc.h"

#ifndef CFG_STBC_H
#define CFG_STBC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Cycle time */
#define _STBC_WAITTIME                                          (0x5U)
#define _STBC_FACTOR_DEFAULT_VALUE                              (0xFFFFFFFFUL)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_RSCFD_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_FLXA_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_GTM_Standby_Mode(void);
MD_STATUS R_STBC_Set_Module_ETNB_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_RSENT_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_MSPI_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_RLIN3_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_ADCJ_ISO_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_CXPI_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_MMCA_Standby_Mode(void);
MD_STATUS R_STBC_Set_Module_ENCA_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_PSI5_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_PSI5S_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_PWMD_Standby_Mode(void);
MD_STATUS R_STBC_Set_Module_RHSIF_Standby_Mode(void);
MD_STATUS R_STBC_Set_Module_RIIC_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_SCI3_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_TAPA_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_TAUD_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_TAUJ_ISO_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_TPBA_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_TSG3_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_OSTM_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Set_Module_ADCJ_AWO_Standby_Mode(void);
MD_STATUS R_STBC_Set_Module_RTCA_Standby_Mode(void);
MD_STATUS R_STBC_Set_Module_TAUJ_AWO_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_RSCFD_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_FLXA_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_GTM_Standby_Mode(void);
MD_STATUS R_STBC_Cancel_Module_ETNB_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_RSENT_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_MSPI_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_RLIN3_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_ADCJ_ISO_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_CXPI_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_MMCA_Standby_Mode(void);
MD_STATUS R_STBC_Cancel_Module_ENCA_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_PSI5_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_PSI5S_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_PWMD_Standby_Mode(void);
MD_STATUS R_STBC_Cancel_Module_RHSIF_Standby_Mode(void);
MD_STATUS R_STBC_Cancel_Module_RIIC_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_SCI3_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_TAPA_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_TAUD_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_TAUJ_ISO_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_TPBA_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_TSG3_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_OSTM_Standby_Mode(uint8_t channel);
MD_STATUS R_STBC_Cancel_Module_ADCJ_AWO_Standby_Mode(void);
MD_STATUS R_STBC_Cancel_Module_RTCA_Standby_Mode(void);
MD_STATUS R_STBC_Cancel_Module_TAUJ_AWO_Standby_Mode(uint8_t channel);
void R_STBC_Check_Module_RSCFD_Idle_State(void);
void R_STBC_Check_Module_FLXA_Idle_State(void);
void R_STBC_Check_Module_GTM_Idle_State(void);
void R_STBC_Check_Module_ETNB_Idle_State(void);
void R_STBC_Check_Module_RSENT_Idle_State(void);
void R_STBC_Check_Module_MSPI_Idle_State(void);
void R_STBC_Check_Module_RLIN3_Idle_State(void);
void R_STBC_Check_Module_ADCJ_ISO_Idle_State(void);
void R_STBC_Check_Module_CXPI_Idle_State(void);
void R_STBC_Check_Module_MMCA_Idle_State(void);
void R_STBC_Check_Module_ENCA_Idle_State(void);
void R_STBC_Check_Module_PSI5_Idle_State(void);
void R_STBC_Check_Module_PSI5S_Idle_State(void);
void R_STBC_Check_Module_PWMD_Idle_State(void);
void R_STBC_Check_Module_RHSIF_Idle_State(void);
void R_STBC_Check_Module_RIIC_Idle_State(void);
void R_STBC_Check_Module_SCI3_Idle_State(void);
void R_STBC_Check_Module_TAPA_Idle_State(void);
void R_STBC_Check_Module_TAUD_Idle_State(void);
void R_STBC_Check_Module_TAUJ_ISO_Idle_State(void);
void R_STBC_Check_Module_TPBA_Idle_State(void);
void R_STBC_Check_Module_TSG3_Idle_State(void);
void R_STBC_Check_Module_OSTM_Idle_State(void);
void R_STBC_Check_Module_ADCJ_AWO_Idle_State(void);
void R_STBC_Check_Module_RTCA_Idle_State(void);
void R_STBC_Check_Module_TAUJ_AWO_Idle_State(void);
void R_STBC_Prepare_Deep_Stop_Mode(void);
void R_STBC_Start_Deep_Stop_Mode(void);
void R_STBC_Deep_Stop_Loop(void);
void R_STBC_Prepare_Deep_Stop_Mode_Set_Peripheral(void);
void R_STBC_Prepare_Deep_Stop_Mode_Set_Interrupt(void);
void R_STBC_Prepare_Deep_Stop_Mode_Set_Clock_Source(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
