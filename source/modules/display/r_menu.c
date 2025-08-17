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
* File Name        : r_menu.c
* Component Version: 1.0.0
* Description      : Menu system   for handling hierarchical menu structures and navigation
***********************************************************************************************************************/

#include "inc/common.h"
#include "shared.h"
#include <stdio.h>
#include <string.h>
#include "r_menu.h"
#include "modules/display/r_display.h"
#include "apps/ui/r_ui.h"
#include "apps/standby/r_standby.h"

//#define NULL 0
int32_t g_menu_selected=0;
int32_t g_menu_encPrevious=0;
Menu_t*  g_active_menu;


/*****************************************************************************
** Function:    r_menu_getActiveEntries
** Description: Gets the number of active menu entries.
** Parameter:   items - array of menu items
**              size - size of the menu items array
** Return:      Number of active menu entries
******************************************************************************/
uint32_t r_menu_getActiveEntries(MenuItem_t * items, uint32_t size)
{
    uint32_t i,count;
    count=0;
    for (i = 0; i < size; i++) {
        if (items[i].type != MENU_INFO) {
            count++;
        }
    }
    return count;
}

/*****************************************************************************
** Function:    r_menu_getSelectedEntry
** Description: Gets the selected menu entry based on the current selection and direction.
** Parameter:   items - array of menu items
**              size - size of the menu items array
**              current - current selected index
**              direction - direction to move the selection
** Return:      New selected index
******************************************************************************/
uint32_t r_menu_getSelectedEntry(MenuItem_t * items, uint32_t size, uint32_t current ,int32_t direction)
{
    int32_t i,newSelection;
    newSelection=current;
    if(direction>0)
    {
        for (i = current+1; i < size; i++) {
            if (items[i].type != MENU_INFO) {
                newSelection=i;
                direction--;
                if (direction==0)
                {
                    break;
                }
                
            }
        }
    }
    else if(direction<0)
    {
        for (i = current-1; i >= 0; i--) {
            if (items[i].type != MENU_INFO) {
                newSelection=i;
                direction++;
                if (direction==0)
                {
                    break;
                }
            }
        }
    }

 
    return newSelection;
}

/*****************************************************************************
** Function:    r_menu_getfirstActivEntry
** Description: Gets the first active menu entry.
** Parameter:   items - array of menu items
**              size - size of the menu items array
** Return:      Index of the first active menu entry
******************************************************************************/
uint32_t r_menu_getfirstActivEntry(MenuItem_t * items, uint32_t size )
{
    int32_t i;
    for (i = 0; i < size; i++) {
        if (items[i].type != MENU_INFO) {
            return i;
        }
    }
    return 0;   
}

/*****************************************************************************
** Function:    r_menu_init
** Description: Initializes the menu system with the active menu.
** Parameter:   active_menu - pointer to the active menu
** Return:      None
******************************************************************************/
void r_menu_init(Menu_t* active_menu)
{
    g_active_menu=active_menu;
    g_menu_selected=r_menu_getfirstActivEntry(g_active_menu->Items,g_active_menu->Size);
}

/*****************************************************************************
** Function:    R_menu_renderScreen
** Description: Renders the menu screen.
** Parameter:   mode - display mode
**              active_menu - pointer to the active menu
** Return:      None
******************************************************************************/
void R_menu_renderScreen(char mode, Menu_t * active_menu)
{
    char buffer[25];
    uint32_t length,offset,activeCounter;
    activeCounter=0;
    R_DISPLAY_clearBuffer();
    sprintf(buffer, "Mode%i ", mode);
    R_DISPLAY_DrawText(0,95,buffer,R_BLACK,R_FILL);
    sprintf(buffer, " %s", active_menu->Name);
    R_DISPLAY_DrawText(0,0,buffer,R_BLACK,R_NO_FILL);

        for (int i = 0; i < active_menu->Size; i++) {
            if(active_menu->Items[i].type==MENU_INFO){

                if(active_menu->Items[i].getvalue!=NULL)
                {
                    R_DISPLAY_DrawText(i+2,0,active_menu->Items[i].text,R_WHITE,R_FILL);
                    active_menu->Items[i].getvalue(buffer);
                    length=strlen(buffer);
                    offset=DISPLAY_WIDTH-(length*6);
                    R_DISPLAY_DrawText(i+2,offset,buffer,R_WHITE,R_NO_FILL);
                }
                else
                {
                    R_DISPLAY_DrawText(i+2,0,active_menu->Items[i].text,R_WHITE,R_FILL);
                }
            }
            else
            {

                if (i == g_menu_selected)
                {
                    R_DISPLAY_DrawText(i+2,0,">",R_WHITE,R_FILL);
                }
                R_DISPLAY_DrawText(i+2,10,active_menu->Items[i].text,R_WHITE,R_NO_FILL);
                activeCounter++;
            }
        }


    R_DISPLAY_writeBuffer_ifIDLE();	
}

/*****************************************************************************
** Function:    r_menu_displayMenu
** Description: Displays the menu based on encoder input and action.
** Parameter:   enc - encoder value
**              action - menu action type
** Return:      None
******************************************************************************/
void r_menu_displayMenu(uint32_t enc, MenuUIActionType_t action) {
    uint8_t mode;
    
    int32_t encOffset;
    
    if(g_UiStatus.CurrentMode== R_UiMode1)
    {
        mode=1;
    }
    else if (g_UiStatus.CurrentMode== R_UiMode2)
    {
        mode=2;
    }


    encOffset=enc-g_menu_encPrevious;
    g_menu_encPrevious=enc;

    if (encOffset != 0)
    {
        g_menu_selected=r_menu_getSelectedEntry(g_active_menu->Items,g_active_menu->Size,g_menu_selected,encOffset*(-1));
    }

    if (action == MENU_BUTTON) 
    {
        if (g_active_menu->Items[g_menu_selected].type == MENU_ACTION) 
        {
            g_active_menu->Items[g_menu_selected].action();
        } 
        else if(g_active_menu->Items[g_menu_selected].type == MENU_SUBMENU) 
        {
            g_active_menu = g_active_menu->Items[g_menu_selected].submenu;
            g_menu_selected=r_menu_getfirstActivEntry(g_active_menu->Items,g_active_menu->Size);

        } 
       
    }

    R_menu_renderScreen(mode, g_active_menu);
}
