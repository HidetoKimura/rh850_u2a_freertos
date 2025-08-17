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
* File Name        : MSPI30.h
* Component Version: 1.4.0
* Device(s)        : R7F702300BFABA
* Description      : This file implements device driver for MSPI30.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_mspi.h"

#ifndef CFG_MSPI30_H
#define CFG_MSPI30_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _MSPI30_CLOCK_FREQUENCY_DIVISION                          (0x0002U) /* MSPI clock frequency division */
#define _MSPI30_FRAME_LENGTH                                      (0x0010U) /* MSPI frame length */
#define _MSPI30_HARDWARE_TRIGGER_DISABLE                          (0x00000000UL) /* MSPI hardware trigger disable */
#define _MSPI30_SETUP_TIME                                        (0x0001U) /* MSPI setup time */
#define _MSPI30_HOLD_TIME                                         (0x0001U) /* MSPI hold time */
#define _MSPI30_IDLE_TIME                                         (0x0001U) /* MSPI idle time */
#define _MSPI30_INTER_DATA_TIME                                   (0x0001U) /* MSPI inter time */
#define _MSPI30_FRAME_COUNT                                       (0x0001U) /* MSPI frame count */
#define _MSPI30_RAMSTART_ADDRESS                                  (0x0000U) /* MSPI RAM start address */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_MSPI30_Create(void);
void R_MSPI30_Start(void);
void R_MSPI30_Stop(void);
MD_STATUS R_MSPI30_Send(uint16_t* const tx_buf);
MD_STATUS R_MSPI30_Receive(uint16_t* const rx_buf);
void R_MSPI30_Software_Trigger(void);
void R_MSPI30_Callback_Interrupt_Send(void);
void R_MSPI30_Callback_Interrupt_Receive(void);
void R_MSPI30_Callback_Interrupt_Error(void);
void R_MSPI30_Callback_Interrupt_Frameend(void);
void R_MSPI30_Create_UserInit(void);
/* Start user code for function. Do not edit comment generated here */
void R_MSPI30_busy_wait(void);
void R_MSPI30_set_busy(void);
/* End user code. Do not edit comment generated here */
#endif
