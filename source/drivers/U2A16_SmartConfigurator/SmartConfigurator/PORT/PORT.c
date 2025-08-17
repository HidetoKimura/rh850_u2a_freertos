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
* File Name        : PORT.c
* Component Version: 1.6.0
* Device(s)        : R7F702300BFABA
* Description      : This file implements device driver for PORT.
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
#include "PORT.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_PORT_Create
* Description  : This function initializes the PORT
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = _PORT_PWEP02_WRITE_ENABLE | _PORT_PWEP10_WRITE_ENABLE | _PORT_PWEP20_WRITE_ENABLE | 
                _PORT_PWEP22_WRITE_ENABLE | _PORT_PWEP24_WRITE_ENABLE;
    PORT0.PIBC2.UINT16 = _PORT_PIBC_INIT;
    PORT0.PIBC10.UINT16 = _PORT_PIBC_INIT;
    PORT0.PIBC20.UINT16 = _PORT_PIBC_INIT;
    PORT0.PIBC22.UINT16 = _PORT_PIBC_INIT;
    PORT0.PIBC24.UINT16 = _PORT_PIBC_INIT;
    PORT0.PBDC2.UINT16 = _PORT_PBDC_INIT;
    PORT0.PBDC10.UINT16 = _PORT_PBDC_INIT;
    PORT0.PBDC20.UINT16 = _PORT_PBDC_INIT;
    PORT0.PBDC22.UINT16 = _PORT_PBDC_INIT;
    PORT0.PBDC24.UINT16 = _PORT_PBDC_INIT;
    PORT0.PM2.UINT16 = _PORT_PM_INIT;
    PORT0.PM10.UINT16 = _PORT_PM_INIT;
    PORT0.PM20.UINT16 = _PORT_PM_INIT;
    PORT0.PM22.UINT16 = _PORT_PM_INIT;
    PORT0.PM24.UINT16 = _PORT_PM_INIT;
    PORT0.PMC2.UINT16 = _PORT_PMC_INIT;
    PORT0.PMC10.UINT16 = _PORT_PMC_INIT;
    PORT0.PMC20.UINT16 = _PORT_PMC_INIT;
    PORT0.PMC22.UINT16 = _PORT_PMC_INIT;
    PORT0.PMC24.UINT16 = _PORT_PMC_INIT;
    PORT0.PIPC2.UINT16 = _PORT_PIPC_INIT;
    PORT0.PIPC10.UINT16 = _PORT_PIPC_INIT;
    PORT0.PIPC20.UINT16 = _PORT_PIPC_INIT;
    PORT0.PIPC22.UINT16 = _PORT_PIPC_INIT;
    PORT0.PIPC24.UINT16 = _PORT_PIPC_INIT;
    /* PORT2 setting */
    PORT0.PDSC2.UINT16 = _PORT_PDSCn14_DRIVE_STRENGTH_0 | _PORT_PDSCn15_DRIVE_STRENGTH_0;
    PORT0.PUCC2.UINT16 = _PORT_PUCCn14_DRIVE_STRENGTH_0 | _PORT_PUCCn15_DRIVE_STRENGTH_0;
    PORT0.PODC2.UINT16 = _PORT_PODCn14_PUSH_PULL | _PORT_PODCn15_PUSH_PULL;
    PORT0.PINV2.UINT16 = _PORT_PINVn14_OUTPUTINVERTED_OFF | _PORT_PINVn15_OUTPUTINVERTED_OFF;
    PORT0.PBDC2.UINT16 = _PORT_PBDCn14_MODE_DISABLED | _PORT_PBDCn15_MODE_DISABLED;
    PORT0.P2.UINT16 = _PORT_Pn14_OUTPUT_LOW | _PORT_Pn15_OUTPUT_LOW;
    PORT0.PM2.UINT16 = _PORT_PMn0_MODE_UNUSED | _PORT_PMn1_MODE_UNUSED | _PORT_PMn2_MODE_UNUSED | 
                       _PORT_PMn3_MODE_UNUSED | _PORT_PMn4_MODE_UNUSED | _PORT_PMn5_MODE_UNUSED | 
                       _PORT_PMn6_MODE_UNUSED | _PORT_PMn7_MODE_UNUSED | _PORT_PMn8_MODE_UNUSED | 
                       _PORT_PMn9_MODE_UNUSED | _PORT_PMn10_MODE_UNUSED | _PORT_PMn11_MODE_UNUSED | 
                       _PORT_PMn12_MODE_UNUSED | _PORT_PMn13_MODE_UNUSED | _PORT_PMn14_MODE_OUTPUT | 
                       _PORT_PMn15_MODE_OUTPUT;
    PORT0.PSFC2.UINT16 = _PORT_PSFCn14_SAFE_DISABLE | _PORT_PSFCn15_SAFE_DISABLE;
    /* PORT10 setting */
    PORT0.PDSC10.UINT16 = _PORT_PDSCn10_DRIVE_STRENGTH_0;
    PORT0.PUCC10.UINT16 = _PORT_PUCCn10_DRIVE_STRENGTH_0;
    PORT0.PODC10.UINT16 = _PORT_PODCn10_PUSH_PULL;
    PORT0.PINV10.UINT16 = _PORT_PINVn10_OUTPUTINVERTED_OFF;
    PORT0.PBDC10.UINT16 = _PORT_PBDCn10_MODE_DISABLED;
    PORT0.P10.UINT16 = _PORT_Pn10_OUTPUT_LOW;
    PORT0.PM10.UINT16 = _PORT_PM10_DEFAULT_VALUE | _PORT_PMn0_MODE_UNUSED | _PORT_PMn1_MODE_UNUSED | 
                        _PORT_PMn2_MODE_UNUSED | _PORT_PMn3_MODE_UNUSED | _PORT_PMn4_MODE_UNUSED | 
                        _PORT_PMn5_MODE_UNUSED | _PORT_PMn6_MODE_UNUSED | _PORT_PMn7_MODE_UNUSED | 
                        _PORT_PMn8_MODE_UNUSED | _PORT_PMn9_MODE_UNUSED | _PORT_PMn10_MODE_OUTPUT | 
                        _PORT_PMn11_MODE_UNUSED | _PORT_PMn12_MODE_UNUSED | _PORT_PMn13_MODE_UNUSED | 
                        _PORT_PMn14_MODE_UNUSED;
    PORT0.PSFC10.UINT16 = _PORT_PSFCn10_SAFE_DISABLE;
    /* PORT20 setting */
    PORT0.PDSC20.UINT16 = _PORT_PDSCn0_DRIVE_STRENGTH_0;
    PORT0.PUCC20.UINT16 = _PORT_PUCCn0_DRIVE_STRENGTH_0;
    PORT0.PODC20.UINT16 = _PORT_PODCn0_PUSH_PULL;
    PORT0.PINV20.UINT16 = _PORT_PINVn0_OUTPUTINVERTED_OFF;
    PORT0.PBDC20.UINT16 = _PORT_PBDCn0_MODE_DISABLED;
    PORT0.P20.UINT16 = _PORT_Pn0_OUTPUT_LOW;
    PORT0.PM20.UINT16 = _PORT_PM20_DEFAULT_VALUE | _PORT_PMn0_MODE_OUTPUT | _PORT_PMn1_MODE_UNUSED | 
                        _PORT_PMn2_MODE_UNUSED | _PORT_PMn3_MODE_UNUSED | _PORT_PMn4_MODE_UNUSED | 
                        _PORT_PMn5_MODE_UNUSED | _PORT_PMn6_MODE_UNUSED | _PORT_PMn7_MODE_UNUSED | 
                        _PORT_PMn8_MODE_UNUSED | _PORT_PMn9_MODE_UNUSED | _PORT_PMn10_MODE_UNUSED | 
                        _PORT_PMn12_MODE_UNUSED | _PORT_PMn13_MODE_UNUSED | _PORT_PMn14_MODE_UNUSED;
    PORT0.PSFC20.UINT16 = _PORT_PSFCn0_SAFE_DISABLE;
    /* PORT22 setting */
    PORT0.PDSC22.UINT16 = _PORT_PDSCn2_DRIVE_STRENGTH_0;
    PORT0.PUCC22.UINT16 = _PORT_PUCCn2_DRIVE_STRENGTH_0;
    PORT0.PODC22.UINT16 = _PORT_PODCn2_PUSH_PULL;
    PORT0.PINV22.UINT16 = _PORT_PINVn2_OUTPUTINVERTED_OFF;
    PORT0.PBDC22.UINT16 = _PORT_PBDCn2_MODE_DISABLED;
    PORT0.P22.UINT16 = _PORT_Pn2_OUTPUT_LOW;
    PORT0.PM22.UINT16 = _PORT_PM22_DEFAULT_VALUE | _PORT_PMn0_MODE_UNUSED | _PORT_PMn1_MODE_UNUSED | 
                        _PORT_PMn2_MODE_OUTPUT | _PORT_PMn3_MODE_UNUSED | _PORT_PMn4_MODE_UNUSED;
    PORT0.PSFC22.UINT16 = _PORT_PSFCn2_SAFE_DISABLE;
    /* PORT24 setting */
    PORT0.PU24.UINT16 = _PORT_PUn4_PULLUP_OFF | _PORT_PUn5_PULLUP_OFF | _PORT_PUn6_PULLUP_OFF | 
                        _PORT_PUn7_PULLUP_OFF | _PORT_PUn8_PULLUP_OFF | _PORT_PUn9_PULLUP_OFF | 
                        _PORT_PUn10_PULLUP_OFF | _PORT_PUn11_PULLUP_OFF | _PORT_PUn12_PULLUP_OFF | 
                        _PORT_PUn13_PULLUP_OFF;
    PORT0.PD24.UINT16 = _PORT_PDn4_PULLDOWN_OFF | _PORT_PDn5_PULLDOWN_OFF | _PORT_PDn6_PULLDOWN_OFF | 
                        _PORT_PDn7_PULLDOWN_OFF | _PORT_PDn8_PULLDOWN_OFF | _PORT_PDn9_PULLDOWN_OFF | 
                        _PORT_PDn10_PULLDOWN_OFF | _PORT_PDn11_PULLDOWN_OFF | _PORT_PDn12_PULLDOWN_OFF | 
                        _PORT_PDn13_PULLDOWN_OFF;
    PORT0.PIS24.UINT16 = _PORT_PISn4_TYPE_SHMT1 | _PORT_PISn5_TYPE_SHMT1 | _PORT_PISn6_TYPE_SHMT1 | 
                         _PORT_PISn7_TYPE_SHMT1 | _PORT_PISn8_TYPE_SHMT1 | _PORT_PISn9_TYPE_SHMT1 | 
                         _PORT_PISn10_TYPE_SHMT1 | _PORT_PISn11_TYPE_SHMT1 | _PORT_PISn12_TYPE_SHMT1 | 
                         _PORT_PISn13_TYPE_SHMT1;
    PORT0.PM24.UINT16 = _PORT_PM24_DEFAULT_VALUE | _PORT_PMn4_MODE_UNUSED | _PORT_PMn5_MODE_UNUSED | 
                        _PORT_PMn6_MODE_UNUSED | _PORT_PMn7_MODE_UNUSED | _PORT_PMn8_MODE_UNUSED | 
                        _PORT_PMn9_MODE_UNUSED | _PORT_PMn10_MODE_INPUT | _PORT_PMn11_MODE_UNUSED | 
                        _PORT_PMn12_MODE_UNUSED | _PORT_PMn13_MODE_UNUSED;
    PORT0.PIBC24.UINT16 = _PORT_PIBCn10_INPUT_BUFFER_ENABLE;
    PORT0.PWE = _PORT_PWEP02_WRITE_DISABLE | _PORT_PWEP10_WRITE_DISABLE | _PORT_PWEP20_WRITE_DISABLE | 
                _PORT_PWEP22_WRITE_DISABLE | _PORT_PWEP24_WRITE_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;
    /* Synchronization processing */
    g_cg_sync_read = PORT0.PM2.UINT16;
    __syncp();

    R_PORT_Create_UserInit();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
