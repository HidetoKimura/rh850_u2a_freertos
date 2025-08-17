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
* File Name        : r_systemTest.c
* Component Version: 1.0.0
* Description      : Check system functionality.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "thirdparty\shell\shell.h"
#include "modules\canfd\r_canfd.h"
#include "modules\lin\r_lin.h"
#include "modules\eth\r_eth.h"
#include "shared.h"
#include "SmartConfigurator\ADCJ2\ADCJ2.h"
#include "modules\sdcard\r_SDIO.h"
#include "SmartConfigurator\ADCJ1\ADCJ1.h"

r_systemTest_t g_systemTest;

/***********************************************************************************************************************
* Function Name: system_test
* Description  : Performs system test 
* Arguments    : none
* Return Value : Result
***********************************************************************************************************************/
r_SysTest_t r_systemTestExecute(void) {
  
  uint8_t failed = 0;
  uint8_t passed = 0;

  /* CANFD test*/
  if (R_CANFD_Test()==R_OK)
  {
    g_systemTest.CanTest = R_CAN_FD_TEST_OK;
    passed++;
  }
  else
  {
    g_systemTest.CanTest = R_CAN_FD_TEST_FAIL;
    failed++;
  }

  /* LIN test*/
  if (R_LIN_Test()==R_OK)
  {
    g_systemTest.LinTest = R_LIN_TEST_OK;
    passed++;
  }
  else
  {
    g_systemTest.LinTest = R_LIN_TEST_FAIL;
    failed++;
  }

  /* ETNB0 test*/ 
  if (g_SystemStatus.EthStatus->phy_loop_back_test == phy_loop_back_test_ok)
  {
    g_systemTest.EthernetTest = R_ETHERNET_TEST_OK;
    passed++;
  }
  else
  {
    g_systemTest.EthernetTest = R_ETHERNET_TEST_FAIL;
    failed++;
  }
  /* ADC test*/


  if (R_ADC_Test()==R_OK)
  {
    g_systemTest.AdcTest = R_ADC_OK;
    passed++;
  }
  else
  {
    g_systemTest.AdcTest = R_ADC_NOT_FAIL;
    failed++;
  }

  /* PWMDiag test*/ 
  if (R_ADCJ1_getError()==R_AD_OK)
  {
    g_systemTest.PwmDiagTest = R_PWMDiag_TEST_OK;
    passed++;
  }
  else
  {
    g_systemTest.PwmDiagTest = R_PWMDiag_TEST_FAIL;
    failed++;
  }

  /* SD (DISK-I/O) test*/

  if( SDIO_TEST_OK == SDIO_SystemTest() )
  {
    g_systemTest.SdTest = R_SD_TEST_OK;
    passed++;
  }
  else
  {
    g_systemTest.SdTest = R_SD_TEST_FAIL;
    failed++;
  }

  /* Display test*/
  if( (g_SystemStatus.DisplayStatus->state == R_DISPLAY_OK_STATE) )
  {
    g_systemTest.DisplayTest = R_DISPLAY_DETECTED;
    passed++;
  }
  else
  {
    g_systemTest.DisplayTest = R_DISPLAY_NOT_DETECTED;
    failed++;
  }

  if (failed>0)
  {
    g_systemTest.SysTest = R_SYS_TEST_FAIL; 
    return R_SYS_TEST_FAIL;
  }
  g_systemTest.SysTest = R_SYS_TEST_OK;
  return R_SYS_TEST_OK;
  

}

/***********************************************************************************************************************
* Function Name: system_test
* Description  : Performs system test when called from shell.
* Arguments    : Command arguments
* Return Value : Result
***********************************************************************************************************************/
int r_systemTestShellCommand(int argc, char **argv) 
{
 
  uint8_t failed = 0;
  uint8_t passed = 0;
  
  printf_esh("Start system test..\r\n");
  r_systemTestExecute();
  /* CANFD test*/
  if (g_systemTest.CanTest == R_CAN_FD_TEST_OK)
  {
    printf_esh("-> CANFD test passed\r\n");
    passed++;
  }
  else
  {
    printf_esh("-> CANFD test failed. please check loopback connection on can port.\r\n");
    failed++;
  }

  /* LIN test*/
  if (g_systemTest.LinTest == R_LIN_TEST_OK)
  {
    printf_esh("-> LIN test passed.\r\n");
    passed++;
  }
  else
  {
    printf_esh("-> LIN test failed.\r\n");
    failed++;
  }

  /* ETNB0 test*/ 
  if (g_systemTest.EthernetTest == R_ETHERNET_TEST_OK)
  {
    printf_esh("-> Ethernet start-up test passed.\r\n");
    passed++;
  }
  else
  {
    printf_esh("-> Ethernet start-up test failed.\r\n");
    failed++;
  }

  /* ADC test*/
  if (g_systemTest.AdcTest == R_ADC_OK)
  {

    printf_esh("-> ADC test passed.\r\n");
    passed++;
  }
  else
  {
    printf_esh("-> ADC test failed.\r\n");
    failed++;
  }

  /* PWMDiag test*/ 
  if (g_systemTest.PwmDiagTest == R_PWMDiag_TEST_OK)
  {
    printf_esh("-> PWMDiag test passed.\r\n");
    passed++;
  }
  else
  {
    printf_esh("-> PWMDiag test failed.\r\n");
    failed++;
  }

  /* SD (DISK-I/O) test*/

  if( g_systemTest.SdTest == R_SD_TEST_OK )
  {
    printf_esh("-> SD test passed.\r\n");
    passed++;
  }
  else
  {
    printf_esh("-> SD test failed. Please check if the SD card is inserted and formatted as FAT (ready for use).\r\n");
    failed++;
  }

  /* Display test*/
  if( g_systemTest.DisplayTest == R_DISPLAY_DETECTED )
  {
    printf_esh("-> Display test passed.\r\n");
    g_systemTest.DisplayTest = R_DISPLAY_DETECTED;
    passed++;
  }
  else
  {
    printf_esh("-> Display test failed. The communication took too long. Please check if the flexible printed circuit of display is connected properly. \r\n");
    failed++;
  }

  if (g_systemTest.SysTest ==  R_SYS_TEST_FAIL)
  {
    printf_esh("%u of %u system tests failed.\r\n",failed,failed+passed);
    g_systemTest.SysTest =  R_SYS_TEST_FAIL;
    return -1;
  }else
  {
    printf_esh("All system test passed\r\n");
    g_systemTest.SysTest = R_SYS_TEST_OK;
    return 0;
  }

}





ADD_CMD(test, "Executes system test", r_systemTestShellCommand);
