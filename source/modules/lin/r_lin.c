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
* File Name         : 
* Component Version : 1.0.0
* Description       : 
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "inc\common.h"
#include "r_lin.h"

#include "drivers\rlin\r_rlin.h"

/***********************************************************************************************************************
Global fcuntions
***********************************************************************************************************************/
/*****************************************************************************
** Function:    R_LIN_Init
** Description: LIN initialization
** Parameter:   None
** Return:      None
******************************************************************************/
void R_LIN_Init(void)
{
    R_RLIN31_BaudrateInit();
    R_RLIN31_Init();
    
    PORT0.PKCPROT = KCE_EN;             /* Enable writes to PWE register */
    PORT0.PWE |= 1<<3;                  /* PWEP2:Enable Write Access for Port 2 */

    /*Port2 Pin4 as Alternative peripheral function 7 (Control Mode 7) Input */
    PORT0.PCR2_4.UINT32 |= 1<<2;                                    /* PFCAEn_4 = 1. */
    PORT0.PCR2_4.UINT32 |= 1<<1;                                     /* PFCEn_4 = 1. */
    PORT0.PCR2_4.UINT32 &= ~1;                                        /* PFCn_4 = 0. */
    PORT0.PCR2_4.UINT32 |= 1<<4;                                       /* PMn_4 = 1. */
    PORT0.PCR2_4.UINT32 |= 1<<6;                  /* Set Alternative Mode: PMCn_4 = 1*/
    
    PORT0.PCR2_5.UINT32 &= ~(1<<2);                                 /* PFCAEn_5 = 0. */
    PORT0.PCR2_5.UINT32 |= 1<<1;                                     /* PFCEn_5 = 1. */
    PORT0.PCR2_5.UINT32 &= ~1;                                        /* PFCn_5 = 0. */
    PORT0.PCR2_5.UINT32 &= ~(1<<4);                                    /* PMn_5 = 1. */
    PORT0.PCR2_5.UINT32 |= 1<<6;                  /* Set Alternative Mode: PMCn_5 = 1*/
        
    PORT0.PWE &= ~(1<<3);               /* PWEP2:Disable Write Access for Port 2 */
    SYSCTRL.MSRKCPROT.UINT32 = KCE_DIS; /* Disable writes to PWE register */
}

/*****************************************************************************
** Function:    R_LIN_Deinit
** Description: LIN De-initialization
** Parameter:   None
** Return:      None
******************************************************************************/
void R_LIN_Deinit(void)
{
    PORT0.PKCPROT = KCE_EN;             /* Enable writes to PWE register */
    PORT0.PWE |= 1<<3;                  /* PWEP2:Enable Write Access for Port 2 */
    
    /* Set Port_Pin to GPIO High Impedant Input  */
    PORT0.PCR2_4.UINT32 &= ~(1<<16);    /* Port2 Pin4: Input buffer is disabled. PIBCn_4 = 0. */
    PORT0.PCR2_4.UINT32 |= 1<<4;        /* Port2 Pin4:Input Mode. PMn_4 = 1. */
    PORT0.PCR2_5.UINT32 &= ~(1<<16);    /* Port2 Pin5: Input buffer is disabled. PIBCn_5 = 0. */
    PORT0.PCR2_5.UINT32 |= 1<<4;        /* Port2 Pin5:Input Mode. PMn_5 = 1. */
    
    PORT0.PWE &= ~(1<<3);               /* PWEP2:Enable Write Access for Port 2 */
    SYSCTRL.MSRKCPROT.UINT32 = KCE_DIS; /* Disable writes to PWE register */
}

/*****************************************************************************
** Function:    R_LIN_Test
** Description: 
** Parameter:   None
** Return:      r_Error_t
******************************************************************************/
r_Error_t R_LIN_Test(void)
{
    uint8_t ID = 0x00;
        
    uint8_t TxDB[8] = {
        0x55,
        0x55,
        0x55,
        0x55,
        0x55,
        0x55,
        0x55,
        0x55
    };

    if(R_RLIN31_TxFrame(ID, TxDB) == RLIN_OK)
        {
            return R_OK;
        }
    else
        {
            return R_ERROR;
        }
}

/*****************************************************************************
** Function:    R_LIN_TxFrame
** Description: 
** Parameter:   uint8_t ID, uint8_t TxDB[]
** Return:      uint8_t
******************************************************************************/
uint8_t R_LIN_TxFrame(uint8_t ID, uint8_t TxDB[])
{
    if(R_RLIN31_TxFrame(ID, TxDB)==RLIN_OK)
        {
            return LIN_OK;
        }
    else
        {
            return LIN_ERROR;
        }
}

/*****************************************************************************
** Function:    R_LIN_RxFrame
** Description: 
** Parameter:   uint8_t RxDB[]
** Return:      uint8_t
******************************************************************************/
uint8_t R_LIN_RxFrame(uint8_t RxDB[])
{
    if(R_RLIN31_RxFrame(RxDB)==RLIN_OK)
        {
            return LIN_OK;
        }
    else
        {
            return LIN_ERROR;
        }
}
