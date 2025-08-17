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
* File Name        : r_ltsc.c
* Component Version: 1.0
* Description      : This file implements long-term system timer functionalities running at PCLK.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "inc\common.h"
#include "r_ltsc.h"

/***********************************************************************************************************************
Public functions
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: R_LTSC_Start
* Description  : Start timer. 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LTSC_Start(void)
{
    LTSC0.TCS.BIT.TS = 1u;
}

/***********************************************************************************************************************
* Function Name: R_LTSC_Stop
* Description  : Stop timer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LTSC_Stop(void)
{
    LTSC0.TCT.BIT.TT = 1u;
}

/***********************************************************************************************************************
* Function Name: R_LTSC_GetStatus
* Description  : Set reset mask to enble/disable timer reset at SW reset. 
* Arguments    : None
* Return Value : uint32_t - Counter Status
                    0 = disabled
                    1 = enabled
***********************************************************************************************************************/
uint32_t R_LTSC_GetStatus(void)
{
    return LTSC0.CSTR.BIT.CST;
}

/***********************************************************************************************************************
* Function Name: R_LTSC_SetResetMask
* Description  : Set reset mask to enble/disable timer reset at SW reset. 
* Arguments    : uint32_t ltsc_rm_mask = R_LTSC_RM_ON  (1)
*                                        R_LTSC_RM_OFF (0)
* Return Value : None
***********************************************************************************************************************/
void R_LTSC_SetResetMask(uint32_t ltsc_rm_mask)
{
    LTSC0.RMSK.BIT.RM = ltsc_rm_mask;
}

/***********************************************************************************************************************
* Function Name: R_LTSC_Read
* Description  : Return current counter value.
* Arguments    : None
* Return Value : uint64_t counter
***********************************************************************************************************************/
uint64_t R_LTSC_Read(void)
{
    uint32_t cntl;
    uint32_t cnth, cnth2;
    uint64_t counter;

    cnth = LTSC0.CNTH.UINT32;
    cntl = LTSC0.CNTL.UINT32;
    cnth2 = LTSC0.CNTH.UINT32;  /* For overflow check */

    if (cnth != cnth2)
    {
        cnth = LTSC0.CNTH.UINT32;
        cntl = LTSC0.CNTL.UINT32;
    }

    counter = (uint64_t)cnth << 31; 
    counter += cntl;

    return counter;
}

