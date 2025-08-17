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
* File Name        :
* Component Version: 1.0.0
* Description      : 
***********************************************************************************************************************/
#include "inc\common.h"

#include "SmartConfigurator\STBC\STBC.h"
#include "SmartConfigurator\r_pincfg\Pin.h"
#include "SmartConfigurator\PORT\PORT.h"
#include "SmartConfigurator\general\r_cg_cgc.h"
#include "modules\systimer\r_systimer.h"
#include "shared.h"

/***********************************************************************************************************************
* Function Name: R_StartUp
* Description  : Call clock init and release standby used modules. 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_StartUp( void)
{
  R_CGC_Create();

  R_STBC_Cancel_Module_RSCFD_Standby_Mode(0);
  R_STBC_Cancel_Module_RSCFD_Standby_Mode(1);
  R_STBC_Cancel_Module_ETNB_Standby_Mode(0);
  R_STBC_Cancel_Module_RSENT_Standby_Mode(0);
  R_STBC_Cancel_Module_MSPI_Standby_Mode(3);
  R_STBC_Cancel_Module_RLIN3_Standby_Mode(1);
  R_STBC_Cancel_Module_RLIN3_Standby_Mode(9);
  R_STBC_Cancel_Module_ADCJ_ISO_Standby_Mode(0);
  R_STBC_Cancel_Module_MMCA_Standby_Mode();
  R_STBC_Cancel_Module_ENCA_Standby_Mode(0);
  R_STBC_Cancel_Module_PWMD_Standby_Mode();
  R_STBC_Cancel_Module_RIIC_Standby_Mode(0);
  R_STBC_Cancel_Module_TAUD_Standby_Mode(0);
  R_STBC_Cancel_Module_TAUD_Standby_Mode(2);
  R_STBC_Cancel_Module_OSTM_Standby_Mode(0);
  R_STBC_Cancel_Module_ADCJ_AWO_Standby_Mode();
  R_STBC_Cancel_Module_ADCJ_ISO_Standby_Mode(1);
}

/***********************************************************************************************************************
* Function Name: low_level_init_pe0
* Description  : Called during startup code by PE0 for early low level initializations. 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void low_level_init_pe0(void)
{
    /* Clock, timer and module standy init. */
    R_StartUp();
    R_SysTimer_Init();
    
    /* Port init */
    R_PORT_Create();
    R_Pins_Create();
    R_Pins_Create_UserInit();

    /* Clear word before first use. */
    g_GRAM_ClearFlag = 0x00000000u;

    /* Configure synchronization barrier channel 0 */
    R_BARR_Init(0, BARR_PE_ALL);

    /* Kick cores */
    SYSCTRL.BOOTCTRL.BIT.BC1 = 1;
    R_SysTimer_usWait(100u);
    SYSCTRL.BOOTCTRL.BIT.BC2 = 1;
    R_SysTimer_usWait(100u);
    SYSCTRL.BOOTCTRL.BIT.BC3 = 1;
}
