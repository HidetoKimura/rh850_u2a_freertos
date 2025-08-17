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
* File Name         : r_ui.h
* Component Version : 1.0.0
* Description       : Header file for r_ui.c.
***********************************************************************************************************************/
#ifndef R_UI_H
#define R_UI_H

typedef enum 
{
    R_UiNoMode,
    R_UiMode1,
    R_UiMode2,
    R_UiStartUp,
    R_UiReset,

} r_UiModes_t;
typedef enum 
{
    R_UiDisplayNoMode,
    R_UiDisplayStartup,
    R_UiDisplayMenu,

} r_UiDisplayModes_t;
typedef struct 
{
  r_UiModes_t CurrentMode;
  r_UiModes_t RequestedMode;
  r_UiDisplayModes_t DisplayMode;
  uint16_t  poti;
  uint32_t  enc;
  uint16_t  cycle;
  uint8_t   larsonStep;
  uint8_t   encPatternNr; 
  uint16_t  ringPattern; 
  uint8_t   encColorNr;
} r_UiStatus_t;

extern r_UiStatus_t g_UiStatus;

/***********************************************************************************************************************
Public functions
***********************************************************************************************************************/
void R_UI_Init(void);
void R_UI_Task(void);
void R_UI_DisplayMenuTask(void);
#endif /* R_UI_H */
