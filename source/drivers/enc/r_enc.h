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
* File Name        : r_enc.h
* Component Version: 1.0.0
* Description      : Header file for r_enc.c.
***********************************************************************************************************************/
#ifndef R_ENC_H
#define R_ENC_H

/***********************************************************************************************************************
Macros
***********************************************************************************************************************/
#define R_ENCA_DOWN_COUNT   0x04    /* Definition reflecting the down-count flag in the ENCA0 status register */
#define R_ENCA_UP_COUNT     0x00    /* Definition reflecting the up-count flag in the ENCA0 status register */

/***********************************************************************************************************************
Public functions
***********************************************************************************************************************/
void R_ENCA0_Init (void);
void R_ENCA0_Start(void);
void R_ENCA0_Stop(void);
uint16_t R_ENCA0_Read(void);
uint8_t R_ENCA0_GetFlags(void);
uint8_t R_ENCA0_GetStatus(void);
void R_ENCA0_Write(uint16_t cnt);

#endif /* R_ENC_H */
