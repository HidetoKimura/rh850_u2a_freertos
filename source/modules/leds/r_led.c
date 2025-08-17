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
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "inc\common.h"
#include "r_led.h"

#include "drivers\pwmd\r_pwmd.h"
#include "drivers\gpio\r_gpio_helper.h"
#include "SmartConfigurator\TAUD0\TAUD0.h"
#include "SmartConfigurator\TAUD2\TAUD2.h"
#include "SmartConfigurator\MSPI30\MSPI30.h"
#include "SmartConfigurator\general\r_cg_mspi_common.h"


r_LedStatus_t g_LedStatus;
/*===========================================================================*/
/* Functions */
/*===========================================================================*/

/*****************************************************************************
** Function:    R_LED_PwmInit
** Description: Initializes PWM usage for specified LED.
** Parameter:   LED1
**              LED2
**              LEDR - Red LED
**              LEDG - Green LED
**              LEDB - Blue LED
** Return:      None
******************************************************************************/
void R_LED_PwmInit(void){
  


    R_TAUD0_Create();
    R_TAUD0_Start(); // Start TAUD0C0 Master as PWM Base

    R_TAUD2_Create();
    R_TAUD2_Start(); // Start TAUD0C0 Master as PWM Base
    R_PWMD_SetPeriod();
    R_PWMD_ClockInit();
    R_PWMD_Channel66Init();
    R_PWMD_Channel67Init();
    R_PWMD_Channel68Init();
    R_PWMD_StartChannel(66);
    R_PWMD_StartChannel(67);
    R_PWMD_StartChannel(68);
   
}

/*****************************************************************************
** Function:    R_LED_SetPwmDuty
** Description: Sets the duty cycle of specified LED correspondingly.
** Parameter:   LED1
**              LED2
**              LEDR - Red LED
**              LEDG - Green LED
**              LEDB - Blue LED
**
**              CompareValue - compare value [0-4095]
** Return:      None
******************************************************************************/
void R_LED_SetPwmDuty(r_Leds_t LED, uint16_t CompareValue){

   switch(LED)
    {
        case LED4:
            R_TAUD0_CDR_Update(1, CompareValue);
            g_LedStatus.Leds[LED4] = CompareValue;
        break;
        
        case LED5:
            R_TAUD0_CDR_Update(2, CompareValue);
            g_LedStatus.Leds[LED5] = CompareValue;
        break;

        case LED6:
            R_TAUD2_CDR_Update(13, CompareValue);
            g_LedStatus.Leds[LED6] = CompareValue;
        break;
        
        case LED7:
            R_TAUD2_CDR_Update(14, CompareValue);
            g_LedStatus.Leds[LED7] = CompareValue;
        break;
        
        case LEDR:
            R_PWMD_Channel66DutyUpdate(CompareValue);	
            g_LedStatus.Leds[LEDR] = CompareValue/8;
        break;

        case LEDG:
            R_PWMD_Channel67DutyUpdate(CompareValue);
            g_LedStatus.Leds[LEDG] = CompareValue/8;
        break;
        
        case LEDB:
            R_PWMD_Channel68DutyUpdate(CompareValue);	
            g_LedStatus.Leds[LEDB] = CompareValue/8;
        break;
        
        default:
        break;
    }
}

/*****************************************************************************
** Function:    R_LED_RingInit
** Description: Initializes the LED Ring, MSPI30 and sets all LEDs to low
** Parameter:   none
** Return:      None
******************************************************************************/
void R_LED_RingInit(void){
   R_MSPI30_Create();	// init MSPI
   R_MSPI30_Start();	// start MSPI
   R_MSPI_Start_Interrupt_MSPI3TX();
   R_MSPI_Start_Interrupt_MSPI3RX();
   R_MSPI_Start_Interrupt_MSPI3FE();
   /* LED Init - LED10-25 Low */
   R_LED_RingUpdate(0x0000);	// Set all LEDs to off
   R_LED_RingOutputEnable();
}


/*****************************************************************************
** Function:    R_LED_RingOutputDisable
** Description: Disables LED Ring
** Parameter:   none
** Return:      None
******************************************************************************/
void R_LED_RingOutputDisable(void){
   setGpioHigh(10,10); // Output Enable High (LED off)
   g_LedStatus.LEDRing = 0x0000;
}

/*****************************************************************************
** Function:    R_LED_RingOutputEnable
** Description: Enables LED Ring
** Parameter:   none
** Return:      None
******************************************************************************/
void R_LED_RingOutputEnable(void){
   setGpioLow(10,10); // Output Enable Low (LED on)
}

/*****************************************************************************
** Function:    R_LED_RingUpdate
** Description: Updates LED Ring Setting
** Parameter:   uint16_t* LedBitMask
** Return:      None
******************************************************************************/
void R_LED_RingUpdate(uint16_t LedBitMask){
   uint16_t SPI_data;
   SPI_data= LedBitMask;
   R_MSPI30_Send(&SPI_data);	// set Bitmask
   R_MSPI30_set_busy();
   R_MSPI30_Software_Trigger();	// send Bitmask
   R_MSPI30_busy_wait();
   setGpioHigh(22,2);
   setGpioLow(22,2);
   g_LedStatus.LEDRing = LedBitMask;
}
