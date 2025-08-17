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
#include "r_userInput.h"

#include "drivers\gpio\r_gpio_helper.h"
#include "drivers\enc\r_enc.h"
#include "SmartConfigurator\ADCJ2\ADCJ2.h"

/*===========================================================================*/
/* Defines */
/*===========================================================================*/
#define R_PRESS_SHORT         10
#define R_PRESS_LONG        3000

r_userInputStatus_t g_userInputStatus;

/*===========================================================================*/
/* Functions */
/*===========================================================================*/

void R_userInput_init(void)
{ 
    R_userInput_Poti0_Init();
    g_userInputStatus.potiValue = R_userInput_Poti0_read();
    R_ENCA0_Init();
    R_ENCA0_Start();
    g_userInputStatus.encValue = R_userInput_Enc_read();

 
}


/*****************************************************************************
** Function:    R_userInput_ButtonSw20_Handler
** Description: Function to check if the button Sw20 is pressed long or short. 
** Parameter:   None
** Return:      R_BUTTON_NOT_PRESSED or
**              R_BUTTON_PRESSED_SHORT or
**              R_BUTTON_PRESSED_LONG
******************************************************************************/
void R_userInput_handler(void)
{ 
    if(R_userInput_Get_ButtonSw20_State() == R_USERINPUT_ACTIVE)
    {
        g_userInputStatus.sw20ButtonCounter++;
    }
    else
    {   
        if(g_userInputStatus.sw20ButtonCounter >= R_PRESS_SHORT && g_userInputStatus.sw20ButtonCounter < R_PRESS_LONG)
        {
            g_userInputStatus.sw20Button = R_BUTTON_PRESSED_SHORT;
        }
        else if(g_userInputStatus.sw20ButtonCounter >= R_PRESS_LONG)
        {
            g_userInputStatus.sw20Button = R_BUTTON_PRESSED_LONG;
        }
        g_userInputStatus.sw20ButtonCounter = 0;
    }

    if(R_userInput_Get_ButtonEncoder_State() == R_USERINPUT_ACTIVE)
    {
        g_userInputStatus.encButtonCounter++;
    }
    else
    {   
        if(g_userInputStatus.encButtonCounter >= R_PRESS_SHORT && g_userInputStatus.encButtonCounter < R_PRESS_LONG)
        {
            g_userInputStatus.encButton = R_BUTTON_PRESSED_SHORT;
        }
        else if(g_userInputStatus.encButtonCounter >= R_PRESS_LONG)
        {
            g_userInputStatus.encButton = R_BUTTON_PRESSED_LONG;
        }
        g_userInputStatus.encButtonCounter = 0;
    }
}

/*****************************************************************************
** Function:    R_userInput_Poti0_Init
** Description: Configure AP0_0 to high impedant input mode of potentiometer 
**              POT1.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_userInput_Poti0_Init(void)
{ 
  R_ADCJ2_Create();
  R_ADCJ2_ScanGroup0_OperationOn();

}

/*****************************************************************************
** Function:    R_userInput_Poti0_Init
** Description: Configure AP0_0 to high impedant input mode of potentiometer 
**              POT1.
** Parameter:   None
** Return:      None
******************************************************************************/
uint16_t R_userInput_Poti0_read(void)
{ 
  uint16_t buffer;
   R_ADCJ2_ScanGroup0_OperationOn();
  R_ADCJ2_ScanGroup0_GetResult(&buffer, 1);
  return buffer;
}


/*****************************************************************************
** Function:    R_userInput_ButtonSw20_Init
** Description: Configures the port pin connected to switch Sw20 to input.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_userInput_ButtonSw20_Init(void)
{
    //R_PORT_SetGpioInput(Port0, 9);
}



/*****************************************************************************
** Function:    R_userInput_Get_ButtonSw20_State
** Description: Returns whether button Sw20 is pressed or not.
** Parameter:   None
** Return:      R_BUTTON_PRESSED or
**              R_BUTTON_NOT_PRESSED
******************************************************************************/
r_UserInput_ButtonLevel_t R_userInput_Get_ButtonSw20_State(void)
{
    /*  Button Sw20 is pressed when level is low */
    if(readGpio(2,3))
    {
        return R_USERINPUT_NOTACTIVE;
    
    }
    else
    {
        return R_USERINPUT_ACTIVE;
    }
        
    
}





/*****************************************************************************
** Function:    R_userInput_Get_ButtonEncoder_State
** Description: Returns whether button of ENC1 is pressed or not.
** Parameter:   None
** Return:      R_BUTTON_PRESSED or
**              R_BUTTON_NOT_PRESSED
******************************************************************************/
r_UserInput_ButtonLevel_t R_userInput_Get_ButtonEncoder_State(void)
{
    
    /*  Encoder button is pressed when level is high */
    if(readGpio(2,7))
    {
        return R_USERINPUT_ACTIVE;
    }
    else
    {
        return R_USERINPUT_NOTACTIVE;
    }
}



uint16_t R_userInput_Enc_read(void)
{
return R_ENCA0_Read();
}


r_UserInput_ButtonEvent_t R_userInput_GetButtonEvent(r_UserInput_ButtonType_t button)
{
    r_UserInput_ButtonEvent_t buttonState;
    switch(button)
    {
        case R_USERINPUT_SW20BUTTON:
            buttonState=g_userInputStatus.sw20Button;
            g_userInputStatus.sw20Button=R_BUTTON_NOT_PRESSED;
            return buttonState;
        case R_USERINPUT_ENCBUTTON:
            buttonState=g_userInputStatus.encButton;
            g_userInputStatus.encButton=R_BUTTON_NOT_PRESSED;
            return buttonState;
        default:
            return R_BUTTON_NOT_PRESSED;
    }

}


