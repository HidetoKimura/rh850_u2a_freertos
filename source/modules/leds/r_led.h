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
#ifndef R_LED_H
#define R_LED_H

typedef enum 
{
    LEDR,
    LEDG,
    LEDB,
    LED4,
    LED5,
    LED6,
    LED7
} r_Leds_t;

/* Fixed available RGB colors */
typedef enum 
{
    RED,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    MAGENTA,
    WHITE
} r_RgbColor_t;

typedef struct 
{
  uint16_t  Leds[7];
  r_Error_t LEDR_Error;
  r_Error_t LEDG_Error;
  r_Error_t LEDB_Error;
  uint16_t  LEDRing;
} r_LedStatus_t;

extern r_LedStatus_t g_LedStatus;

/*===========================================================================*/
/* Defines */
/*===========================================================================*/




/*===========================================================================*/
/* Function defines */
/*===========================================================================*/
//void R_LED_GpioInit(enum LEDs LED);
//void R_LED_GpioOn(enum LEDs LED);
//void R_LED_GpioOff(enum LEDs LED);
void R_LED_PwmInit(void);
void R_LED_SetPwmDuty(r_Leds_t LED, uint16_t CompareValue);
//void R_LED_PwmStop(enum LEDs LED);
//void R_LED_RgbDiagInit(void);
//void R_LED_RgbDiagStart(void);
//void R_LED_RgbDiagStop(void);


void R_LED_RingUpdate(uint16_t LedBitMask);
void R_LED_RingOutputEnable(void);
void R_LED_RingOutputDisable(void);
void R_LED_RingInit(void);
void R_LED_RingBootUp(void);

//void R_LED_EnableRGB(void);
//void R_LED_RingBootUp(void);

//void R_LED_EnableRGB_CCW(void); /* Encoder Counter-Clock-Wise */
//void R_LED_EnableRGB_CW(void);  /* Encoder Clock-Wise */

#endif /* R_LED_H */
