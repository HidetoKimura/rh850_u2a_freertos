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
* File Name        : r_ui.c
* Component Version: 1.0.0
* Description      : This file implements the UI module.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "inc\common.h"
#include "shared.h"
#include "r_ui.h"
#include <stdio.h>
#include "drivers\enc\r_enc.h"
#include "SmartConfigurator\ADCJ1\ADCJ1.h"
#include "drivers\pwmd\r_pwmd.h"
#include "drivers\gpio\r_gpio_helper.h"
#include "modules\leds\r_led.h"
#include "modules\userInput\r_userInput.h"
#include "modules\display\r_display.h"
#include "modules\display\r_menu.h"
#include "modules\uart\r_uart.h"
#include "modules\systimer\r_systimer.h"
#include "apps\standby\r_standby.h"
#include "apps\systemTest\r_systemTest.h"

/***********************************************************************************************************************
local function prototypes
***********************************************************************************************************************/
static void do_systest(void) ;
static void change_mode(void);
static void gettxframes (char* buffer) ;
static void getrxframes (char* buffer) ;
static void getlink (char* buffer) ;
static void getip (char* buffer) ;
static void getruntime(char* buffer) ;
static void getsystest(char* buffer) ;

/***********************************************************************************************************************
Global variables
***********************************************************************************************************************/

/* Global variable to hold the UI status */
r_UiStatus_t g_UiStatus;                                
const uint16_t g_FixedRGBColors[7][3] = \
{{3000,0,0},{3000,3000,0},{0,3000,0},{0,3000,3000},{0,0,3000},{3000,0,3000},{3000,3000,3000}};
/* RED       YELLOW           GREEN     CYAN        BLUE      MAGENTA      WHITE       */ 


/* Display menu configuration*/
MenuItem_t EthMenuItems[];
Menu_t EthMenu;
MenuItem_t SystemInfoMenuItems[];
Menu_t SystemInfoMenu;
MenuItem_t mainMenuItems[];
Menu_t  mainMenu;

MenuItem_t EthMenuItems[] = {
    {"Frames TX", MENU_INFO, NULL, NULL,  gettxframes},
    {"Frames RX", MENU_INFO, NULL, NULL,  getrxframes},
    {"Link", MENU_INFO, NULL, NULL,  getlink},
    {"IP", MENU_INFO, NULL, NULL,  getip},
    {" ", MENU_INFO, NULL, NULL,  NULL},
    {"return", MENU_SUBMENU, NULL, &mainMenu,  NULL},
};

Menu_t EthMenu = {
    EthMenuItems,
    sizeof(EthMenuItems)/sizeof(EthMenuItems[0]),
    "Ethernet Info"
};


MenuItem_t SystemInfoMenuItems[] = {
    {"Runtime ms", MENU_INFO, NULL, NULL,  getruntime},
    {"System Test", MENU_INFO, NULL, NULL,  getsystest},
    {" ", MENU_INFO, NULL, NULL,  NULL},
    {"Do System Test", MENU_ACTION, do_systest, NULL,  NULL},
    {"return", MENU_SUBMENU, NULL, &mainMenu,  NULL},
};
Menu_t SystemInfoMenu = {
    SystemInfoMenuItems,
    sizeof(SystemInfoMenuItems)/sizeof(SystemInfoMenuItems[0]),
    "System Info"
};


MenuItem_t mainMenuItems[] = {
    {"Change Mode", MENU_ACTION, change_mode, NULL,  NULL},
    {"System Info", MENU_SUBMENU, NULL, &SystemInfoMenu,  NULL},
    {"Ethernet Info", MENU_SUBMENU, NULL, &EthMenu,  NULL},
    {"Go to DeepStop", MENU_ACTION, stbc_controller_deepSTOP, NULL,  NULL},
    {"Reset MCU", MENU_ACTION, r_standby_reset, NULL,  NULL},
};
Menu_t  mainMenu = {
    mainMenuItems,
    sizeof(mainMenuItems)/sizeof(mainMenuItems[0]),
    "MainMenu"
};





/***********************************************************************************************************************
Private functions
***********************************************************************************************************************/

/*****************************************************************************
** Function:    change_mode
** Description: Changes the mode.
** Parameter:   None
** Return:      None
******************************************************************************/
static void change_mode(void) {
    if(g_UiStatus.CurrentMode== R_UiMode1)
    {
        g_UiStatus.RequestedMode= R_UiMode2;
    }
    else
    {
        g_UiStatus.RequestedMode= R_UiMode1;
    }
}

/*****************************************************************************
** Function:    do_systest
** Description: Performs a system test.
** Parameter:   None
** Return:      None
******************************************************************************/
static void do_systest(void) 
{
    r_systemTestExecute();
}

/*****************************************************************************
** Function:    gettxframes
** Description: writes the number of transmitted frames to the buffer.
** Parameter:   pointer to the text buffer
** Return:      None
******************************************************************************/
static void gettxframes (char* buffer) 
{
    sprintf(buffer,"%i",g_SystemStatus.EthStatus->sent_frames);
}

/*****************************************************************************
** Function:    getrxframes
** Description: writes the number of received frames to the buffer.
** Parameter:   pointer to the text buffer
** Return:      None
******************************************************************************/
static void getrxframes (char* buffer) 
{
    sprintf(buffer,"%i",g_SystemStatus.EthStatus->received_frames);
}

/*****************************************************************************
** Function:    getlink
** Description: writes the link status to the buffer.
** Parameter:   pointer to the text buffer
** Return:      None
******************************************************************************/
static void getlink (char* buffer) 
{
    if(g_SystemStatus.EthStatus->link_status==link_status_up)
    {
        sprintf(buffer,"UP");
    }
    else
    {
        sprintf(buffer,"DOWN");
    } 
}

/*****************************************************************************
** Function:    getip
** Description: writes the ip address to the buffer.
** Parameter:   pointer to the text buffer
** Return:      None
******************************************************************************/
static void getip (char* buffer) 
{
    sprintf(buffer,"%i.%i.%i.%i",g_SystemStatus.EthStatus->ip_address[0],g_SystemStatus.EthStatus->ip_address[1],g_SystemStatus.EthStatus->ip_address[2],g_SystemStatus.EthStatus->ip_address[3]);
}

/*****************************************************************************
** Function:    getruntime
** Description: writes the runtime to the buffer.   
** Parameter:   pointer to the text buffer
** Return:      None
******************************************************************************/
static void getruntime(char* buffer) 
{
    sprintf(buffer,"%i",g_SystemStatus.RunTimeMs);
}

/*****************************************************************************
** Function:    getsystest
** Description: writes the system test status to the buffer.
** Parameter:   pointer to the text buffer
** Return:      None
******************************************************************************/
static void getsystest(char* buffer) 
{
    if(g_SystemStatus.SystemTest->SysTest==R_SYS_TEST_OK)
    {
        sprintf(buffer,"OK");
    }
    else if (g_SystemStatus.SystemTest->SysTest==R_SYS_TEST_FAIL)
    {
        sprintf(buffer,"FAIL");
    } else
    {
        sprintf(buffer,"NOT DONE");
    }
}

/*****************************************************************************
** Function:    generateRainbowValue
** Description: Generate a RGB value based on the input value.
** Parameter:   input - input value
**              r - pointer to the red value
**              g - pointer to the green value
**              b - pointer to the blue value
** Return:      None
******************************************************************************/
static void generateRainbowValue(uint16_t input, uint8_t* r, uint8_t* g, uint8_t* b) 
{
    // Normalize the input to a value between 0 and 1
    float normalized = (float)input / 4095.0;

    // Calculate the RGB values based on the normalized input
    if (normalized < 1.0 / 6.0) {
        *b = 255;
        *g = (uint8_t)(normalized * 6.0 * 255.0);
        *r = 0;
    } else if (normalized < 2.0 / 6.0) {
        *b = (uint8_t)((2.0 / 6.0 - normalized) * 6.0 * 255.0);
        *g = 255;
        *r = 0;
    } else if (normalized < 3.0 / 6.0) {
        *b = 0;
        *g = 255;
        *r = (uint8_t)((normalized - 2.0 / 6.0) * 6.0 * 255.0);
    } else if (normalized < 4.0 / 6.0) {
        *b = 0;
        *g = (uint8_t)((4.0 / 6.0 - normalized) * 6.0 * 255.0);
        *r = 255;
    } else if (normalized < 5.0 / 6.0) {
        *b = (uint8_t)((normalized - 4.0 / 6.0) * 6.0 * 255.0);
        *g = 0;
        *r = 255;
    } else {
        *b = 255;
        *g = 0;
        *r = (uint8_t)((6.0 / 6.0 - normalized) * 6.0 * 255.0);
    }
}

/*****************************************************************************
 * Function:    fillupled
 * Description: Fill up the LEDs in a circular pattern.
 * Parameter:   cycle - cycle value
 * Return:      None
 * ***************************************************************************/
static void fillupled(uint16_t cycle)
{
    uint8_t dutyCycle = cycle % 256;
    uint8_t stage = cycle / 256;

    switch (stage)
    {
        case 0:
            R_LED_SetPwmDuty(LED4, dutyCycle);
            R_LED_SetPwmDuty(LED5, 0);
            R_LED_SetPwmDuty(LED6, 0);
            R_LED_SetPwmDuty(LED7, 0);
            break;
        case 1:
            R_LED_SetPwmDuty(LED4, 255);
            R_LED_SetPwmDuty(LED5, dutyCycle);
            R_LED_SetPwmDuty(LED6, 0);
            R_LED_SetPwmDuty(LED7, 0);
            break;
        case 2:
            R_LED_SetPwmDuty(LED4, 255);
            R_LED_SetPwmDuty(LED5, 255);
            R_LED_SetPwmDuty(LED6, dutyCycle);
            R_LED_SetPwmDuty(LED7, 0);
            break;
        case 3:
            R_LED_SetPwmDuty(LED4, 255);
            R_LED_SetPwmDuty(LED5, 255);
            R_LED_SetPwmDuty(LED6, 255);
            R_LED_SetPwmDuty(LED7, dutyCycle);
            break;
        case 4:
            R_LED_SetPwmDuty(LED4, 255 - dutyCycle);
            R_LED_SetPwmDuty(LED5, 255);
            R_LED_SetPwmDuty(LED6, 255);
            R_LED_SetPwmDuty(LED7, 255);
            break;
        case 5:
            R_LED_SetPwmDuty(LED4, 0);
            R_LED_SetPwmDuty(LED5, 255 - dutyCycle);
            R_LED_SetPwmDuty(LED6, 255);
            R_LED_SetPwmDuty(LED7, 255);
            break;
        case 6:
            R_LED_SetPwmDuty(LED4, 0);
            R_LED_SetPwmDuty(LED5, 0);
            R_LED_SetPwmDuty(LED6, 255 - dutyCycle);
            R_LED_SetPwmDuty(LED7, 255);
            break;
        case 7:
            R_LED_SetPwmDuty(LED4, 0);
            R_LED_SetPwmDuty(LED5, 0);
            R_LED_SetPwmDuty(LED6, 0);
            R_LED_SetPwmDuty(LED7, 255 - dutyCycle);
            break;
        default:
            break;
    }
}


/***********************************************************************************************************************
Public functions
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: R_UI_Init
* Description  : Initialize the UI module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UI_Init(void)
{
    
 
    R_LED_PwmInit();
    R_LED_RingInit();
    R_userInput_init();
    R_UART_Init();

    R_DISPLAY_ResetRelease();
    R_DISPLAY_Init();
    R_DISPLAY_StartScreen();
    r_menu_init(&mainMenu);
    g_UiStatus.DisplayMode=R_UiDisplayStartup;


    g_UiStatus.CurrentMode=R_UiStartUp;
    
    if(R_DEEPSTOP == g_SystemStatus.PreviousMode)
    {
        R_UART_SendString("\n\rWakeup from DeepSTOP\n\r");

        /* Restore previous color. */
        R_LED_SetPwmDuty(LEDR,g_SystemStatus.LedStatus->Leds[LEDR]); /* Set value for red LED */
        R_LED_SetPwmDuty(LEDG,g_SystemStatus.LedStatus->Leds[LEDR]); /* Set value for green LED */
        R_LED_SetPwmDuty(LEDB,g_SystemStatus.LedStatus->Leds[LEDR]); /* Set value for blue LED */
    }
    else 
    {
        R_UART_SendString("\n\rHello World!!!\n\r");
        R_UART_SendString("U2A Starterkit\n\r");
        
        R_LED_RingUpdate(0x0000);   // Set all LEDs off

        /* Initial setting of the RGB Encoder Button to off. */
        R_LED_SetPwmDuty(LEDR,0); /* Set value for red LED */
        R_LED_SetPwmDuty(LEDG,0); /* Set value for green LED */
        R_LED_SetPwmDuty(LEDB,0); /* Set value for blue LED */

        
    }

    /* PWM Output/Dianostic (PWM-Diag) related settings. */
    R_ADCJ1_Create();
    R_Config_ADCJ1_SetUpperLowerLimit(0,100,0); /* Lowest Safety Upper Limit measured 69.*/
    R_PWMD_DiagInit();
    R_PWMD_DiagStart();


    g_UiStatus.cycle=0;
}

/***********************************************************************************************************************
* Function Name: R_UI_Task
* Description  : This function reads the encoder and poti values and updates the LEDs.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UI_Task(void)
{
    uint8_t rgb[3];

    /* Update led ring based on encoder */
    g_UiStatus.enc = R_userInput_Enc_read();
    
    /* Read poti value */
    g_UiStatus.poti =R_userInput_Poti0_read();
    
    if (g_UiStatus.CurrentMode == R_UiStartUp)
    {
        if(g_UiStatus.cycle%32==0)
        {
            if(g_UiStatus.cycle<512)
            {
                g_UiStatus.ringPattern|=(1<< (15-g_UiStatus.cycle/32));
               
            }
            else 
            { 
                g_UiStatus.ringPattern&=~(1<< (g_UiStatus.cycle/32-16));
                g_UiStatus.ringPattern|=1<<15;
                
            }
            R_LED_RingUpdate(g_UiStatus.ringPattern);
        }
      
      
        generateRainbowValue(g_UiStatus.cycle*4, &rgb[0], &rgb[1], &rgb[2]);
        R_LED_SetPwmDuty(LEDR,rgb[0]*8); /* Set value for red LED */
        R_LED_SetPwmDuty(LEDG,rgb[1]*8); /* Set value for green LED */
        R_LED_SetPwmDuty(LEDB,rgb[2]*8); /* Set value for blue LED */


        if(g_UiStatus.cycle>1024)
        {
            g_UiStatus.CurrentMode= R_UiMode1;
            g_UiStatus.cycle=0;
        }
        else
        {
            g_UiStatus.cycle++;
        }

    }

    if (g_UiStatus.CurrentMode == R_UiMode1)
    {
        
        g_UiStatus.encPatternNr= g_UiStatus.enc%16;
        R_LED_RingUpdate(1<<(15-g_UiStatus.encPatternNr));
        
        g_UiStatus.encColorNr=4;
        R_LED_SetPwmDuty(LEDR,g_FixedRGBColors[g_UiStatus.encColorNr][LEDR]); /* Set value for red LED */
        R_LED_SetPwmDuty(LEDG,g_FixedRGBColors[g_UiStatus.encColorNr][LEDG]); /* Set value for green LED */
        R_LED_SetPwmDuty(LEDB,g_FixedRGBColors[g_UiStatus.encColorNr][LEDB]); /* Set value for blue LED */
        
        /* Create fill up on 4 leds*/
        fillupled(g_UiStatus.cycle%2048);

        
        g_UiStatus.cycle++;

    }   
    else if (g_UiStatus.CurrentMode== R_UiMode2)
    {
        g_UiStatus.encPatternNr= g_UiStatus.enc%16;
        R_LED_RingUpdate(1<<(15-g_UiStatus.encPatternNr));
        generateRainbowValue(g_UiStatus.poti, &rgb[0], &rgb[1], &rgb[2]);
        R_LED_SetPwmDuty(LEDR,rgb[0]*8); /* Set value for red LED */
        R_LED_SetPwmDuty(LEDG,rgb[1]*8); /* Set value for green LED */
        R_LED_SetPwmDuty(LEDB,rgb[2]*8); /* Set value for blue LED */

        R_LED_SetPwmDuty(LED4, 0);
        R_LED_SetPwmDuty(LED5, 0);
        R_LED_SetPwmDuty(LED6, 0);
        R_LED_SetPwmDuty(LED7, 0);
    }
   


    if ( R_userInput_GetButtonEvent(R_USERINPUT_SW20BUTTON) == R_BUTTON_PRESSED_SHORT)
    {
        if(g_UiStatus.CurrentMode== R_UiMode1)
        {
            g_UiStatus.CurrentMode= R_UiMode2;
        }
        else
        {
            g_UiStatus.CurrentMode= R_UiMode1;
        }
    }


    if ( g_UiStatus.RequestedMode != R_UiNoMode)
    {
        if(g_UiStatus.RequestedMode == R_UiReset)
        {
           r_standby_reset();
        }
        else if (g_UiStatus.RequestedMode == R_UiMode1)
        {
            g_UiStatus.CurrentMode = R_UiMode1;
            g_UiStatus.RequestedMode = R_UiNoMode;
        }
        else if (g_UiStatus.RequestedMode == R_UiMode2)
        {
            g_UiStatus.CurrentMode = R_UiMode2;
            g_UiStatus.RequestedMode = R_UiNoMode;
        }
    
      
    }
}

/***********************************************************************************************************************
 * Function Name: R_UI_DisplayMenuTask
 * Description  : This function displays the menu based on the encoder input.
 * Arguments    : None
 * Return Value : None
 * ***********************************************************************************************************************/
void R_UI_DisplayMenuTask(void)
{
    
    if (g_UiStatus.DisplayMode == R_UiDisplayStartup)
    {
        if ( R_userInput_GetButtonEvent(R_USERINPUT_ENCBUTTON) == R_BUTTON_PRESSED_SHORT)
        {
            R_DISPLAY_StartScreenStop();
            g_UiStatus.DisplayMode = R_UiDisplayMenu;

        }
      
    }
    if(g_SystemStatus.RunTimeMs%100==0)
    {
        if(g_UiStatus.DisplayMode == R_UiDisplayMenu)
        {
            if ( R_userInput_GetButtonEvent(R_USERINPUT_ENCBUTTON) == R_BUTTON_PRESSED_SHORT)
            {
                r_menu_displayMenu(g_UiStatus.enc,MENU_BUTTON);
            }
            else
            {
                r_menu_displayMenu(g_UiStatus.enc,MENU_NOACTION);
            }
        } 
    }
}
