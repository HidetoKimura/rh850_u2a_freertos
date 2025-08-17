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
#ifndef R_SYSTEMTEST_H
#define R_SYSTEMTEST_H


#include "thirdparty\shell\shell.h"
#include "modules\canfd\r_canfd.h"
#include "modules\lin\r_lin.h"
#include "shared.h"
#include "modules\sdcard\r_SDIO.h"


typedef enum
{ 
    R_CAN_FD_TEST_NOT_EXECUTED,
    R_CAN_FD_TEST_FAIL,
    R_CAN_FD_TEST_OK
}r_CanTest_t;

typedef enum
{
    R_LIN_TEST_NOT_EXECUTED,
    R_LIN_TEST_FAIL,
    R_LIN_TEST_OK 
}r_LinTest_t;

typedef enum
{
    R_ETHERNET_TEST_NOT_EXECUTED,
    R_ETHERNET_TEST_FAIL,
    R_ETHERNET_TEST_OK 
}r_EthTest_t;

typedef enum
{
    R_PWMDiag_TEST_NOT_EXECUTED,
    R_PWMDiag_TEST_FAIL,
    R_PWMDiag_TEST_OK
}r_PwmDiagTest_t;

typedef enum
{
    R_SD_TEST_NOT_EXECUTED,
    R_SD_TEST_FAIL,
    R_SD_TEST_OK,
    R_SD_TEST_NO_CARD,
}r_SdTest_t;


typedef enum
{
    R_DISPLAY_NOT_EXECUTED,
    R_DISPLAY_NOT_DETECTED,
    R_DISPLAY_DETECTED
}r_DspTest_t;

typedef enum
{
    R_ADC_NOT_EXECUTED,
    R_ADC_NOT_FAIL,
    R_ADC_OK,
}r_AdcTest_t;

typedef enum
{
    R_PWMD_NOT_EXECUTED,
    R_PWMD_NOT_FAIL,
    R_PWMD_OK,
}r_PWMDTest_t; 

typedef enum
{
    R_SYS_TEST_NOT_EXECUTED,
    R_SYS_TEST_FAIL,
    R_SYS_TEST_OK,
}r_SysTest_t;


typedef struct r_systemTest_s
{
    r_CanTest_t CanTest;
    r_LinTest_t LinTest;
    r_EthTest_t EthernetTest;
    r_PwmDiagTest_t PwmDiagTest;
    r_SdTest_t SdTest;
    r_DspTest_t DisplayTest;
    r_AdcTest_t AdcTest;
    r_PWMDTest_t PwmdTest;
    r_SysTest_t SysTest;
   
}r_systemTest_t;

extern r_systemTest_t g_systemTest;


/***********************************************************************************************************************
* Function Name: system_test
* Description  : Performs system test 
* Arguments    : none
* Return Value : Result
***********************************************************************************************************************/
extern r_SysTest_t r_systemTestExecute(void);

/***********************************************************************************************************************
* Function Name: system_test
* Description  : Performs system test when called from shell.
* Arguments    : Command arguments
* Return Value : Result
***********************************************************************************************************************/
extern int r_systemTestShellCommand(int argc, char **argv);

#endif /* R_SYSTEMTEST_H */
