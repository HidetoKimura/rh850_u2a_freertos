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
* File Name        : r_systimer.c
* Component Version: 1.0
* Description      : Provide system timer and wait functions. 
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "inc\common.h"
#include "r_systimer.h"

#include "drivers\ltsc\r_ltsc.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: R_SysTimer_Init()
* Description  : Start long term system timer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SysTimer_Init(void)
{
    if(R_LTSC_GetStatus()==R_LTSC_DISABLED)
    {
        R_LTSC_Start();
    }
}

/***********************************************************************************************************************
* Function Name: R_SysTimer_usWait()
* Description  : Snooze for a given number of microseconds. 
* Arguments    : useconds - Number of microseconds to wait.
* Return Value : r_Error_t
***********************************************************************************************************************/
r_Error_t R_SysTimer_usWait(uint32_t useconds)
{
    uint64_t counterValue;
    uint64_t compareValue;

    if(R_LTSC_GetStatus()==R_LTSC_DISABLED)
    {
        return R_ERROR;
    }
    
    counterValue = R_LTSC_Read();
    compareValue = counterValue + (useconds * R_SYSTIMER_USECOND);
    while(counterValue<compareValue)
    {
        SNOOZE();
        counterValue = R_LTSC_Read();
    }
    
    return R_OK;
}

/***********************************************************************************************************************
* Function Name: R_SysTimer_msWait()
* Description  : Snooze for a given number of milliseconds. 
* Arguments    : mseconds - Number of milliseconds to wait.
* Return Value : r_Error_t
***********************************************************************************************************************/
r_Error_t R_SysTimer_msWait(uint32_t mseconds)
{
    uint64_t counterValue;
    uint64_t compareValue;

    if(R_LTSC_GetStatus()==R_LTSC_DISABLED)
    {
        return R_ERROR;
    }
    
    counterValue = R_LTSC_Read();
    compareValue = counterValue + (mseconds * R_SYSTIMER_MSECOND);
    while(counterValue<compareValue)
    {
        SNOOZE();
        counterValue = R_LTSC_Read();
    }
    
    return R_OK;
}

/***********************************************************************************************************************
* Function Name: R_SysTimer_Read()
* Description  : Read the current value of the system timer.
* Arguments    : None
* Return Value : uint64_t - Current system timer value.
***********************************************************************************************************************/
uint64_t R_SysTimer_Read(void)
{
    return R_LTSC_Read();
}
