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
#ifndef R_USERINPUT_H
#define R_USERINPUT_H

/*===========================================================================*/
/* Defines */
/*===========================================================================*/
typedef enum
{
    R_BUTTON_NOT_PRESSED,
    R_BUTTON_PRESSED_SHORT,
    R_BUTTON_PRESSED_LONG
}r_UserInput_ButtonEvent_t;

typedef enum
{
    R_USERINPUT_NOTACTIVE,
    R_USERINPUT_ACTIVE,

} r_UserInput_ButtonLevel_t;

typedef enum
{
    R_USERINPUT_SW20BUTTON,
    R_USERINPUT_ENCBUTTON,
    R_USERINPUT_SW17BUTTON,
} r_UserInput_ButtonType_t;

typedef struct 
{
    r_UserInput_ButtonEvent_t encButton;
    r_UserInput_ButtonEvent_t sw20Button;
    uint32_t encButtonCounter;
    uint32_t sw20ButtonCounter;
    uint32_t encValue;
    uint16_t potiValue;
}r_userInputStatus_t;

/*===========================================================================*/
/* Function defines */
/*===========================================================================*/



r_UserInput_ButtonLevel_t R_userInput_Get_ButtonSw20_State(void);
r_UserInput_ButtonLevel_t R_userInput_Get_ButtonEncoder_State(void);
void R_userInput_init(void);
void R_userInput_ButtonSW20_Init(void);
void R_userInput_Poti0_Init(void);
void R_userInput_ButtonEncoder_Init(void);
uint16_t R_userInput_Enc_read(void);
void R_userInput_handler(void);
uint16_t R_userInput_Poti0_read(void);

r_UserInput_ButtonEvent_t R_userInput_GetButtonEvent(r_UserInput_ButtonType_t button);

void R_userInput_handler(void);





#endif /* R_userInput_H */

