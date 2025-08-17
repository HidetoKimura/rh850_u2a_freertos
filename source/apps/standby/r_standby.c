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
* Copyright (C) 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : r_standby.c
* Component Version: 1.0
* Description      : This file implements application for standby controller.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "inc\common.h"
#include "SmartConfigurator\STBC\STBC.h"
#include "SmartConfigurator\INTC\INTC.h"
#include "SmartConfigurator\RIIC0\RIIC0.h"
#include "modules\leds\r_led.h"
#include "modules\display\r_display.h"
#include "thirdparty\shell\shell.h"
#include <stdbool.h>

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: stbc_controller_deepSTOP
* Description  : This function prepares and enters into deepSTOP mode.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void stbc_controller_deepSTOP(void)
{
    /* External Interrupt which can be used for wake */
    R_INTC_Create();
    R_INTC_INTP4_Start();   /* SW17 EX INT1 */
    R_INTC_INTP5_Start();   /* Encoder PushButton */

    R_LED_RingUpdate(0);
    R_LED_SetPwmDuty(LEDR,0);
    R_LED_SetPwmDuty(LEDG,0);
    R_LED_SetPwmDuty(LEDB,0);
    R_DISPLAY_waitForIdle(200);
    R_DISPLAY_StartScreenStop();
    R_DISPLAY_clear();
    R_DISPLAY_DrawText(4,0,"    MCU DeepSTOP  ",R_WHITE,R_FILL);
    R_DISPLAY_writeBuffer();
    R_DISPLAY_waitForIdle(200);

    /* Enter deepSTOP mode */
    R_STBC_Prepare_Deep_Stop_Mode();
    R_STBC_Start_Deep_Stop_Mode();
}


/***********************************************************************************************************************
* Function Name: mcu_deep_stop
* Description  : This shell command function will cause the µC to enter the deepSTOP mode and will wait for an 
                 WAKE-UP factor to get out. Current Wake-Up factors are External INT SW21 or Encoder PushButton.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
int mcu_deep_stop(int argc, char **argv) {



  printf_esh("Entering deepSTOP mode.\n\n");
  printf_esh("To exit, press INT SW17 or Encoder PushButton.\n\n");
  stbc_controller_deepSTOP();


  return 0;
}

void r_standby_reset(void)
{
  SYSCTRL.RESKCPROT0.UINT32=KCE_EN;
  SYSCTRL.SWARESA.UINT32=1;
  while(1);
}

int mcu_reset_command(int argc, char **argv)
{
  printf_esh("System reset.\n\n");
  r_standby_reset();
  return 0;
}


ADD_CMD(deep_stop, "Enter deepSTOP mode", mcu_deep_stop);
ADD_CMD(reset, "System reset", mcu_reset_command);
