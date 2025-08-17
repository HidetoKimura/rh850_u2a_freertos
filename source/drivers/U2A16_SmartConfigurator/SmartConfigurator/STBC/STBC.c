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
* File Name        : STBC.c
* Component Version: 1.3.1
* Device(s)        : R7F702300BFABA
* Description      : This file implements device driver for STBC.
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
#include "STBC.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_STBC_Prepare_Deep_Stop_Mode
* Description  : This function prepare STBC deep stop mode.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_STBC_Prepare_Deep_Stop_Mode(void)
{
    /* Stop all of the peripheral functions to which the clock supply is to be stopped */
    R_STBC_Prepare_Deep_Stop_Mode_Set_Peripheral();
    /* Disable interrupts */
    DI();
    /* Clear all interrupt flags */
    R_STBC_Prepare_Deep_Stop_Mode_Set_Interrupt();
    /* Clear wake-up factor */
    SYSCTRL.WUFC0_A0.UINT32 = _STBC_WUFC0_A0_CLEAR;
    SYSCTRL.WUFC0_A1.UINT32 = _STBC_WUFC0_A1_CLEAR;
    SYSCTRL.WUFC0_A2.UINT32 = _STBC_WUFC0_A2_CLEAR;
    /* Enable wake-up factor */
    SYSCTRL.WUFMSK0_A0.UINT32 = _STBC_FACTOR_DEFAULT_VALUE & _STBC_WUFMSK0_A0_FACTOR_INTP4 & 
                                _STBC_WUFMSK0_A0_FACTOR_INTP5;
    SYSCTRL.WUFMSK0_A1.UINT32 = _STBC_FACTOR_DEFAULT_VALUE;
    SYSCTRL.WUFMSK0_A2.UINT32 = _STBC_FACTOR_DEFAULT_VALUE & _STBC_WUFMSK0_A2_FACTOR_WUTRG1;
    /* Set the operation of module clock in STOP and DeepSTOP and Cyclic STOP mode */
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    SYSCTRL.MSR_ADCJ_AWO.BIT.STPMSK_ADCJ_AWO = _STBC_MODULE_CLOCK_MASK;
    SYSCTRL.MSR_RTCA.BIT.STPMSK_RTCA = _STBC_MODULE_CLOCK_NOT_MASK;
    SYSCTRL.MSR_TAUJ_AWO.BIT.STPMSK_TAUJ_AWO = _STBC_MODULE_CLOCK_MASK;
    SYSCTRL.MSR_WDTB_AWO.BIT.STPMSK_WDTB_AWO = _STBC_MODULE_CLOCK_NOT_MASK;
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;
    /* Set the masks for the source clocks */
    R_STBC_Prepare_Deep_Stop_Mode_Set_Clock_Source();
    /* Clear reset flag */
    SYSCTRL.RESFC.UINT32 |= _RESFC_RESET_FLAG_CLEAR;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Start_Deep_Stop_Mode
* Description  : This function Start Deep Stop Mode.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_STBC_Start_Deep_Stop_Mode(void)
{
    SYSCTRL.STBCKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    SYSCTRL.STBC0PSC.UINT32 = _STBC_DEEP_STOP_MODE_ENTERED;
    SYSCTRL.STBCKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;
    R_STBC_Deep_Stop_Loop();
}

/***********************************************************************************************************************
* Function Name: R_STBC_Deep_Stop_Loop
* Description  : This function Deep_Stop_Loop.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_STBC_Deep_Stop_Loop(void)
{
/* Start user code for R_STBC_Deep_Stop_Loop. Do not edit comment generated here */
    /* Re-Enable Interrupts */
    EI();
/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_RSCFD_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_RSCFD_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_RSCFD_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_RSCFD.BIT.SWMRESS_RSCFD_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }
        SYSCTRL.MSR_RSCFD.BIT.MS_RSCFD_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_RSCFD.BIT.SWMRESS_RSCFD_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }
        SYSCTRL.MSR_RSCFD.BIT.MS_RSCFD_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_FLXA_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_FLXA_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_FLXA_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_FLXA.BIT.SWMRESS_FLXA_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }
        SYSCTRL.MSR_FLXA.BIT.MS_FLXA_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_FLXA.BIT.SWMRESS_FLXA_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }
        SYSCTRL.MSR_FLXA.BIT.MS_FLXA_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_GTM_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_GTM_Standby_Mode(void)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_GTM_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    if((SYSCTRL.SWMRESS_GTM.BIT.SWMRESS_GTM_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
    {
            status = MD_BUSY1;
    }

    SYSCTRL.MSR_GTM.BIT.MS_GTM_0 = _STBC_MODULE_CLOCK_STOPPED;
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_ETNB_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_ETNB_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_ETNB_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_ETNB.BIT.SWMRESS_ETNB_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_ETNB.BIT.MS_ETNB_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_ETNB.BIT.SWMRESS_ETNB_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_ETNB.BIT.MS_ETNB_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_RSENT_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_RSENT_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_RSENT_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 2:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_2 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 3:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_3 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 4:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_4 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_4 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 5:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_5 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_5 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 6:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_6 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_6 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 7:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_7 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_7 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_MSPI_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_MSPI_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_MSPI_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 2:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_2 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 3:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_3 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 4:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_4 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_4 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 5:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_5 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_5 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 6:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_6 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_6 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 7:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_7 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_7 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 8:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_8 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_8 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 9:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_9 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_9 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_RLIN3_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_RLIN3_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_RLIN3_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 2:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_2 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 3:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_3 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 4:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_4 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_4 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 5:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_5 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_5 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 6:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_6 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_6 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 7:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_7 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_7 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 8:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_8 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_8 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 9:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_9 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_9 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 10:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_10 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_10 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 11:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_11 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_11 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 12:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_12 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_12 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 13:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_13 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_13 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 14:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_14 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_14 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 15:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_15 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_15 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 16:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_16 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_16 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 17:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_17 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_17 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 18:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_18 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_18 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 19:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_19 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_19 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 20:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_20 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_20 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 21:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_21 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_21 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 22:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_22 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_22 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 23:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_23 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_23 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_ADCJ_ISO_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_ADCJ_ISO_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_ADCJ_ISO_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_ADCJ_ISO.BIT.SWMRESS_ADCJ_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_ADCJ_ISO.BIT.MS_ADCJ_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_ADCJ_ISO.BIT.SWMRESS_ADCJ_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_ADCJ_ISO.BIT.MS_ADCJ_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_CXPI_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_CXPI_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_CXPI_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_CXPI.BIT.SWMRESS_CXPI_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_CXPI.BIT.MS_CXPI_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_CXPI.BIT.SWMRESS_CXPI_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_CXPI.BIT.MS_CXPI_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 2:
        if((SYSCTRL.SWMRESS_CXPI.BIT.SWMRESS_CXPI_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_CXPI.BIT.MS_CXPI_2 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 3:
        if((SYSCTRL.SWMRESS_CXPI.BIT.SWMRESS_CXPI_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_CXPI.BIT.MS_CXPI_3 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_MMCA_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_MMCA_Standby_Mode(void)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_MMCA_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    if((SYSCTRL.SWMRESS_MMCA.BIT.SWMRESS_MMCA_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
    {
        status = MD_BUSY1;
    }

    SYSCTRL.MSR_MMCA.BIT.MS_MMCA_0 = _STBC_MODULE_CLOCK_STOPPED;
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_ENCA_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_ENCA_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_ENCA_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_ENCA.BIT.SWMRESS_ENCA_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_ENCA.BIT.MS_ENCA_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_ENCA.BIT.SWMRESS_ENCA_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_ENCA.BIT.MS_ENCA_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_PSI5_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_PSI5_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_PSI5_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_PSI5.BIT.SWMRESS_PSI5_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_PSI5.BIT.MS_PSI5_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_PSI5.BIT.SWMRESS_PSI5_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_PSI5.BIT.MS_PSI5_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 2:
        if((SYSCTRL.SWMRESS_PSI5.BIT.SWMRESS_PSI5_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_PSI5.BIT.MS_PSI5_2 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 3:
        if((SYSCTRL.SWMRESS_PSI5.BIT.SWMRESS_PSI5_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_PSI5.BIT.MS_PSI5_3 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_PSI5S_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_PSI5S_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_PSI5S_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_PSI5S.BIT.SWMRESS_PSI5S_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }
                SYSCTRL.MSR_PSI5S.BIT.MS_PSI5S_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_PSI5S.BIT.SWMRESS_PSI5S_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_PSI5S.BIT.MS_PSI5S_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_PWMD_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_PWMD_Standby_Mode(void)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_PWMD_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    if((SYSCTRL.SWMRESS_PWMD.BIT.SWMRESS_PWMD & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
    {
        status = MD_BUSY1;
    }

    SYSCTRL.MSR_PWMD.BIT.MS_PWMD = _STBC_MODULE_CLOCK_STOPPED;
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_RHSIF_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_RHSIF_Standby_Mode(void)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_RHSIF_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    if((SYSCTRL.SWMRESS_RHSIF.BIT.SWMRESS_RHSIF_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
    {
        status = MD_BUSY1;
    }

    SYSCTRL.MSR_RHSIF.BIT.MS_RHSIF_0 = _STBC_MODULE_CLOCK_STOPPED;
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_RIIC_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_RIIC_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_RIIC_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_RIIC.BIT.SWMRESS_RIIC_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RIIC.BIT.MS_RIIC_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_RIIC.BIT.SWMRESS_RIIC_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RIIC.BIT.MS_RIIC_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_SCI3_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_SCI3_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_SCI3_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_SCI3.BIT.SWMRESS_SCI3_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_SCI3.BIT.MS_SCI3_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_SCI3.BIT.SWMRESS_SCI3_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_SCI3.BIT.MS_SCI3_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 2:
        if((SYSCTRL.SWMRESS_SCI3.BIT.SWMRESS_SCI3_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_SCI3.BIT.MS_SCI3_2 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_TAPA_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_TAPA_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_TAPA_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_TAPA.BIT.SWMRESS_TAPA_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAPA.BIT.MS_TAPA_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_TAPA.BIT.SWMRESS_TAPA_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAPA.BIT.MS_TAPA_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 2:
        if((SYSCTRL.SWMRESS_TAPA.BIT.SWMRESS_TAPA_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAPA.BIT.MS_TAPA_2 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 3:
        if((SYSCTRL.SWMRESS_TAPA.BIT.SWMRESS_TAPA_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAPA.BIT.MS_TAPA_3 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_TAUD_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_TAUD_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_TAUD_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_TAUD.BIT.SWMRESS_TAUD_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAUD.BIT.MS_TAUD_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_TAUD.BIT.SWMRESS_TAUD_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAUD.BIT.MS_TAUD_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 2:
        if((SYSCTRL.SWMRESS_TAUD.BIT.SWMRESS_TAUD_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAUD.BIT.MS_TAUD_2 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_TAUJ_ISO_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_TAUJ_ISO_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_TAUJ_ISO_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_TAUJ_ISO.BIT.SWMRESS_TAUJ_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAUJ_ISO.BIT.MS_TAUJ_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_TAUJ_ISO.BIT.SWMRESS_TAUJ_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAUJ_ISO.BIT.MS_TAUJ_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_TPBA_Standby_mode.
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_TPBA_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_TPBA_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_TPBA.BIT.SWMRESS_TPBA_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TPBA.BIT.MS_TPBA_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_TPBA.BIT.SWMRESS_TPBA_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TPBA.BIT.MS_TPBA_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_TSG3_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_TSG3_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_TSG3_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_TSG3.BIT.SWMRESS_TSG3_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TSG3.BIT.MS_TSG3_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_TSG3.BIT.SWMRESS_TSG3_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TSG3.BIT.MS_TSG3_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_OSTM_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_OSTM_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_OSTM_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_0 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 1:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_1 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 2:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_2 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 3:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_3 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 4:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_4 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_4 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 5:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_5 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_5 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 6:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_6 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_6 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 7:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_7 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_7 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 8:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_8 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_8 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 9:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_9 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_9 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_ADCJ_AWO_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_ADCJ_AWO_Standby_Mode(void)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_ADCJ_AWO_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    if((SYSCTRL.SWMRESS_ADCJ_AWO.BIT.SWMRESS_ADCJ_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
    {
        status = MD_BUSY1;
    }

    SYSCTRL.MSR_ADCJ_AWO.BIT.MS_ADCJ_2 = _STBC_MODULE_CLOCK_STOPPED;
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_RTCA_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_RTCA_Standby_Mode(void)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_RTCA_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    SYSCTRL.MSR_RTCA.BIT.MS_RTCA_0 = _STBC_MODULE_CLOCK_STOPPED;
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Set_Module_TAUJ_AWO_Standby_Mode
* Description  : This function transitions to module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be set
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Set_Module_TAUJ_AWO_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    R_STBC_Check_Module_TAUJ_AWO_Idle_State();

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 2:
        if((SYSCTRL.SWMRESS_TAUJ_AWO.BIT.SWMRESS_TAUJ_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAUJ_AWO.BIT.MS_TAUJ_2 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    case 3:
        if((SYSCTRL.SWMRESS_TAUJ_AWO.BIT.SWMRESS_TAUJ_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAUJ_AWO.BIT.MS_TAUJ_3 = _STBC_MODULE_CLOCK_STOPPED;
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_RSCFD_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_RSCFD_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_RSCFD.BIT.SWMRESS_RSCFD_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSCFD.BIT.MS_RSCFD_0 = _STBC_MODULE_CLOCK_OPERATED;

        if((SYSCTRL.MSR_RSCFD.BIT.MS_RSCFD_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_RSCFD.BIT.SWMRESS_RSCFD_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSCFD.BIT.MS_RSCFD_1 = _STBC_MODULE_CLOCK_OPERATED;

        if((SYSCTRL.MSR_RSCFD.BIT.MS_RSCFD_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_FLXA_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_FLXA_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_FLXA.BIT.SWMRESS_FLXA_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }
        SYSCTRL.MSR_FLXA.BIT.MS_FLXA_0 = _STBC_MODULE_CLOCK_OPERATED;

        if((SYSCTRL.MSR_FLXA.BIT.MS_FLXA_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_FLXA.BIT.SWMRESS_FLXA_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }
        SYSCTRL.MSR_FLXA.BIT.MS_FLXA_1 = _STBC_MODULE_CLOCK_OPERATED;

        if((SYSCTRL.MSR_FLXA.BIT.MS_FLXA_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_GTM_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_GTM_Standby_Mode(void)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    if((SYSCTRL.SWMRESS_GTM.BIT.SWMRESS_GTM_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
    {
        status = MD_BUSY1;
    }

    SYSCTRL.MSR_GTM.BIT.MS_GTM_0 = _STBC_MODULE_CLOCK_OPERATED;

    if((SYSCTRL.MSR_GTM.BIT.MS_GTM_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
    {
        status = MD_ERROR;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_ETNB_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_ETNB_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_ETNB.BIT.SWMRESS_ETNB_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_ETNB.BIT.MS_ETNB_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_ETNB.BIT.MS_ETNB_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_ETNB.BIT.SWMRESS_ETNB_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_ETNB.BIT.MS_ETNB_1 = _STBC_MODULE_CLOCK_OPERATED;

        if((SYSCTRL.MSR_ETNB.BIT.MS_ETNB_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_RSENT_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_RSENT_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RSENT.BIT.MS_RSENT_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RSENT.BIT.MS_RSENT_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 2:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_2 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RSENT.BIT.MS_RSENT_2 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 3:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_3 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RSENT.BIT.MS_RSENT_3 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 4:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_4 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_4 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RSENT.BIT.MS_RSENT_4 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 5:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_5 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_5 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RSENT.BIT.MS_RSENT_5 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 6:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_6 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_6 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RSENT.BIT.MS_RSENT_6 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 7:
        if((SYSCTRL.SWMRESS_RSENT.BIT.SWMRESS_RSENT_7 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RSENT.BIT.MS_RSENT_7 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RSENT.BIT.MS_RSENT_7 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_MSPI_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_MSPI_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_MSPI.BIT.MS_MSPI_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_MSPI.BIT.MS_MSPI_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 2:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_2 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_MSPI.BIT.MS_MSPI_2 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 3:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_3 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_MSPI.BIT.MS_MSPI_3 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 4:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_4 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_4 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_MSPI.BIT.MS_MSPI_4 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 5:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_5 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_5 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_MSPI.BIT.MS_MSPI_5 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 6:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_6 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_6 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_MSPI.BIT.MS_MSPI_6 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 7:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_7 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_7 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_MSPI.BIT.MS_MSPI_7 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 8:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_8 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_8 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_MSPI.BIT.MS_MSPI_8 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 9:
        if((SYSCTRL.SWMRESS_MSPI.BIT.SWMRESS_MSPI_9 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_MSPI.BIT.MS_MSPI_9 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_MSPI.BIT.MS_MSPI_9 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_RLIN3_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_RLIN3_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 2:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_2 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_2 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 3:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_3 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_3 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 4:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_4 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_4 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_4 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 5:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_5 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_5 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_5 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 6:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_6 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_6 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_6 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 7:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_7 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_7 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_7 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 8:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_8 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_8 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_8 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 9:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_9 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_9 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_9 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 10:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_10 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_10 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_10 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 11:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_11 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_11 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_11 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 12:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_12 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_12 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_12 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 13:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_13 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_13 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_13 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 14:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_14 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_14 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_14 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 15:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_15 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_15 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_15 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 16:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_16 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_16 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_16 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 17:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_17 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_17 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_17 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 18:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_18 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_18 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_18 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 19:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_19 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_19 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_19 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 20:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_20 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_20 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_20 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 21:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_21 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_21 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_21 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 22:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_22 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_22 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_22 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 23:
        if((SYSCTRL.SWMRESS_RLIN3.BIT.SWMRESS_RLIN3_23 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_23 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RLIN3.BIT.MS_RLIN3_23 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_ADCJ_ISO_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_ADCJ_ISO_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_ADCJ_ISO.BIT.SWMRESS_ADCJ_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_ADCJ_ISO.BIT.MS_ADCJ_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_ADCJ_ISO.BIT.MS_ADCJ_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_ADCJ_ISO.BIT.SWMRESS_ADCJ_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_ADCJ_ISO.BIT.MS_ADCJ_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_ADCJ_ISO.BIT.MS_ADCJ_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_CXPI_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_CXPI_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_CXPI.BIT.SWMRESS_CXPI_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_CXPI.BIT.MS_CXPI_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_CXPI.BIT.MS_CXPI_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_CXPI.BIT.SWMRESS_CXPI_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_CXPI.BIT.MS_CXPI_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_CXPI.BIT.MS_CXPI_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 2:
        if((SYSCTRL.SWMRESS_CXPI.BIT.SWMRESS_CXPI_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_CXPI.BIT.MS_CXPI_2 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_CXPI.BIT.MS_CXPI_2 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 3:
        if((SYSCTRL.SWMRESS_CXPI.BIT.SWMRESS_CXPI_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_CXPI.BIT.MS_CXPI_3 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_CXPI.BIT.MS_CXPI_3 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_MMCA_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_MMCA_Standby_Mode(void)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    if((SYSCTRL.SWMRESS_MMCA.BIT.SWMRESS_MMCA_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
    {
        status = MD_BUSY1;
    }

    SYSCTRL.MSR_MMCA.BIT.MS_MMCA_0 = _STBC_MODULE_CLOCK_OPERATED;
    if((SYSCTRL.MSR_MMCA.BIT.MS_MMCA_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
    {
        status = MD_ERROR;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_ENCA_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_ENCA_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_ENCA.BIT.SWMRESS_ENCA_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_ENCA.BIT.MS_ENCA_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_ENCA.BIT.MS_ENCA_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_ENCA.BIT.SWMRESS_ENCA_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_ENCA.BIT.MS_ENCA_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_ENCA.BIT.MS_ENCA_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_PSI5_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_PSI5_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_PSI5.BIT.SWMRESS_PSI5_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_PSI5.BIT.MS_PSI5_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_PSI5.BIT.MS_PSI5_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_PSI5.BIT.SWMRESS_PSI5_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_PSI5.BIT.MS_PSI5_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_PSI5.BIT.MS_PSI5_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 2:
        if((SYSCTRL.SWMRESS_PSI5.BIT.SWMRESS_PSI5_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_PSI5.BIT.MS_PSI5_2 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_PSI5.BIT.MS_PSI5_2 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 3:
        if((SYSCTRL.SWMRESS_PSI5.BIT.SWMRESS_PSI5_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_PSI5.BIT.MS_PSI5_3 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_PSI5.BIT.MS_PSI5_3 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_PSI5S_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_PSI5S_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_PSI5S.BIT.SWMRESS_PSI5S_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }
        SYSCTRL.MSR_PSI5S.BIT.MS_PSI5S_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_PSI5S.BIT.MS_PSI5S_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_PSI5S.BIT.SWMRESS_PSI5S_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_PSI5S.BIT.MS_PSI5S_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_PSI5S.BIT.MS_PSI5S_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_PWMD_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_PWMD_Standby_Mode(void)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    if((SYSCTRL.SWMRESS_PWMD.BIT.SWMRESS_PWMD & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
    {
        status = MD_BUSY1;
    }

    SYSCTRL.MSR_PWMD.BIT.MS_PWMD = _STBC_MODULE_CLOCK_OPERATED;
    if((SYSCTRL.MSR_PWMD.BIT.MS_PWMD & _STBC_MODULE_CLOCK_STOPPED) == 1)
    {
        status = MD_ERROR;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_RHSIF_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_RHSIF_Standby_Mode(void)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    if((SYSCTRL.SWMRESS_RHSIF.BIT.SWMRESS_RHSIF_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
    {
        status = MD_BUSY1;
    }

    SYSCTRL.MSR_RHSIF.BIT.MS_RHSIF_0 = _STBC_MODULE_CLOCK_OPERATED;
    if((SYSCTRL.MSR_RHSIF.BIT.MS_RHSIF_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
    {
        status = MD_ERROR;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_RIIC_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_RIIC_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_RIIC.BIT.SWMRESS_RIIC_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RIIC.BIT.MS_RIIC_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RIIC.BIT.MS_RIIC_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_RIIC.BIT.SWMRESS_RIIC_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_RIIC.BIT.MS_RIIC_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_RIIC.BIT.MS_RIIC_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_SCI3_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_SCI3_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_SCI3.BIT.SWMRESS_SCI3_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_SCI3.BIT.MS_SCI3_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_SCI3.BIT.MS_SCI3_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_SCI3.BIT.SWMRESS_SCI3_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_SCI3.BIT.MS_SCI3_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_SCI3.BIT.MS_SCI3_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 2:
        if((SYSCTRL.SWMRESS_SCI3.BIT.SWMRESS_SCI3_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }
        
        SYSCTRL.MSR_SCI3.BIT.MS_SCI3_2 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_SCI3.BIT.MS_SCI3_2 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_TAPA_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_TAPA_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_TAPA.BIT.SWMRESS_TAPA_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAPA.BIT.MS_TAPA_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TAPA.BIT.MS_TAPA_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_TAPA.BIT.SWMRESS_TAPA_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAPA.BIT.MS_TAPA_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TAPA.BIT.MS_TAPA_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 2:
        if((SYSCTRL.SWMRESS_TAPA.BIT.SWMRESS_TAPA_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAPA.BIT.MS_TAPA_2 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TAPA.BIT.MS_TAPA_2 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 3:
        if((SYSCTRL.SWMRESS_TAPA.BIT.SWMRESS_TAPA_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAPA.BIT.MS_TAPA_3 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TAPA.BIT.MS_TAPA_3 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_TAUD_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_TAUD_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_TAUD.BIT.SWMRESS_TAUD_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAUD.BIT.MS_TAUD_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TAUD.BIT.MS_TAUD_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_TAUD.BIT.SWMRESS_TAUD_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAUD.BIT.MS_TAUD_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TAUD.BIT.MS_TAUD_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 2:
        if((SYSCTRL.SWMRESS_TAUD.BIT.SWMRESS_TAUD_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAUD.BIT.MS_TAUD_2 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TAUD.BIT.MS_TAUD_2 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_TAUJ_ISO_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_TAUJ_ISO_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_TAUJ_ISO.BIT.SWMRESS_TAUJ_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAUJ_ISO.BIT.MS_TAUJ_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TAUJ_ISO.BIT.MS_TAUJ_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_TAUJ_ISO.BIT.SWMRESS_TAUJ_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAUJ_ISO.BIT.MS_TAUJ_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TAUJ_ISO.BIT.MS_TAUJ_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_TPBA_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_TPBA_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_TPBA.BIT.SWMRESS_TPBA_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TPBA.BIT.MS_TPBA_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TPBA.BIT.MS_TPBA_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_TPBA.BIT.SWMRESS_TPBA_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TPBA.BIT.MS_TPBA_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TPBA.BIT.MS_TPBA_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_TSG3_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_TSG3_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_TSG3.BIT.SWMRESS_TSG3_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TSG3.BIT.MS_TSG3_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TSG3.BIT.MS_TSG3_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_TSG3.BIT.SWMRESS_TSG3_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TSG3.BIT.MS_TSG3_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TSG3.BIT.MS_TSG3_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_OSTM_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_OSTM_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 0:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_0 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_0 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_OSTM.BIT.MS_OSTM_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 1:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_1 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_1 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_OSTM.BIT.MS_OSTM_1 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 2:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_2 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_OSTM.BIT.MS_OSTM_2 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 3:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_3 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_OSTM.BIT.MS_OSTM_3 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 4:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_4 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_4 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_OSTM.BIT.MS_OSTM_4 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 5:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_5 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_5 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_OSTM.BIT.MS_OSTM_5 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 6:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_6 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_6 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_OSTM.BIT.MS_OSTM_6 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 7:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_7 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_7 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_OSTM.BIT.MS_OSTM_7 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 8:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_8 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_8 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_OSTM.BIT.MS_OSTM_8 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 9:
        if((SYSCTRL.SWMRESS_OSTM.BIT.SWMRESS_OSTM_9 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_OSTM.BIT.MS_OSTM_9 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_OSTM.BIT.MS_OSTM_9 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_ADCJ_AWO_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_ADCJ_AWO_Standby_Mode(void)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    if((SYSCTRL.SWMRESS_ADCJ_AWO.BIT.SWMRESS_ADCJ_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
    {
        status = MD_BUSY1;
    }

    SYSCTRL.MSR_ADCJ_AWO.BIT.MS_ADCJ_2 = _STBC_MODULE_CLOCK_OPERATED;
    if((SYSCTRL.MSR_ADCJ_AWO.BIT.MS_ADCJ_2 & _STBC_MODULE_CLOCK_STOPPED) == 1)
    {
        status = MD_ERROR;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_RTCA_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_RTCA_Standby_Mode(void)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    SYSCTRL.MSR_RTCA.BIT.MS_RTCA_0 = _STBC_MODULE_CLOCK_OPERATED;
    if((SYSCTRL.MSR_RTCA.BIT.MS_RTCA_0 & _STBC_MODULE_CLOCK_STOPPED) == 1)
    {
        status = MD_ERROR;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/***********************************************************************************************************************
* Function Name: R_STBC_Cancel_Module_TAUJ_AWO_Standby_Mode
* Description  : This function cancels module standby mode.
* Arguments    : channel -
*                    module channel which stand-by mode will be canceled
* Return Value : status -
*                    MD_OK, MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_STBC_Cancel_Module_TAUJ_AWO_Standby_Mode(uint8_t channel)
{
    MD_STATUS status = MD_OK;

    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_ENABLE;
    switch (channel)
    {
    case 2:
        if((SYSCTRL.SWMRESS_TAUJ_AWO.BIT.SWMRESS_TAUJ_2 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAUJ_AWO.BIT.MS_TAUJ_2 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TAUJ_AWO.BIT.MS_TAUJ_2 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    case 3:
        if((SYSCTRL.SWMRESS_TAUJ_AWO.BIT.SWMRESS_TAUJ_3 & _MODULE_RESET_BEING_PROCESSED_YES) == 1)
        {
            status = MD_BUSY1;
        }

        SYSCTRL.MSR_TAUJ_AWO.BIT.MS_TAUJ_3 = _STBC_MODULE_CLOCK_OPERATED;
        if((SYSCTRL.MSR_TAUJ_AWO.BIT.MS_TAUJ_3 & _STBC_MODULE_CLOCK_STOPPED) == 1)
        {
            status = MD_ERROR;
        }
        break;
    default:
        break;
    }
    SYSCTRL.MSRKCPROT.UINT32 = _WRITE_PROTECT_DISABLE;

    if(SYSCTRL.MSRKCPROT.UINT32 != 0x00000000UL)
    {
        status = MD_ERROR;
    }

    return status;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
