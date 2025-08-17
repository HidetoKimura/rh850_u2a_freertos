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
* File Name        : r_menu.h
* Component Version: 1.0.0
* Description      : Menu system header file for handling hierarchical menu structures and navigation
***********************************************************************************************************************/
#ifndef R_MENU_H
#define R_MENU_H


// Menu item types - defines the behavior of each menu entry
typedef enum {
    MENU_ACTION,    // Menu item that triggers a function when selected
    MENU_SUBMENU,   // Menu item that opens a submenu when selected
    MENU_INFO       // Menu item that displays information/status
} MenuItemType_t;




// Menu item structure - represents a single menu entry
typedef struct MenuItem_t{
    char* text;                 // Display text for the menu item
    MenuItemType_t type;        // Type of menu item (action/submenu/info)
    void (*action)();           // Function pointer for MENU_ACTION items
    struct Menu_t* submenu;     // Pointer to submenu for MENU_SUBMENU items
    void (*getvalue)(char*);    // Function to get current value for MENU_INFO items
} MenuItem_t;

// Types of UI interactions possible with menu items
typedef enum {
    MENU_NOACTION,     // No button press, typically just navigation
    MENU_BUTTON,       // Button press detected
} MenuUIActionType_t;

// Menu structure - represents a complete menu page
typedef struct Menu_t{
    MenuItem_t * Items;     // Array of menu items
    uint8_t Size;          // Number of items in the menu
    char* Name;            // Name/title of the menu
}Menu_t;

// Function to handle menu display and navigation based on encoder input
void r_menu_displayMenu(uint32_t enc, MenuUIActionType_t action);

// Initialize the menu system with the starting menu
void r_menu_init(Menu_t* active_menu);

// Render the menu screen with specified mode
void R_menu_renderScreen(char mode, Menu_t * active_menu);
#endif /* R_MENU_H */
