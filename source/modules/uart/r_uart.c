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
* File Name        : r_uart.c
* Component Version: 1.0.0
* Description      : 
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include <string.h>
#include "inc\common.h"
#include "r_uart.h"

#include "SmartConfigurator\RLIN39\RLIN39.h"


char rx_buffer[256];
uint8_t  rx_buffer_wr_ptr;
uint8_t  tx_buffer_rd_ptr;
/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/*****************************************************************************
** Function:    R_UART_Init
** Description: Configures Ports and RLIN39 for UART usage and enables the Tx 
**              interrupt for string transmission.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UART_Init(void)
{

   R_RLIN39_Create();
   R_RLIN39_Start();
   rx_buffer_wr_ptr=0;
   tx_buffer_rd_ptr=0;
   R_RLIN39_Receive((uint8_t *) &rx_buffer[rx_buffer_wr_ptr],1);
}

/*****************************************************************************
** Function:    R_UART_SendString
** Description: Waits if transmission is still in progress and then sends a string.
**              string - Buffer with string to send.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UART_SendChar(char character)
{
    uint32_t length=1;
    R_RLIN39_busy_wait();
    R_RLIN39_set_busy();
    R_RLIN39_Send((uint8_t *)&character,length);
    

}


/*****************************************************************************
** Function:    R_UART_SendString
** Description: Waits if transmission is still in progress and then sends a string.
**              string - Buffer with string to send.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UART_SendString(char string[])
{
    uint32_t length=strlen(string);
    R_RLIN39_busy_wait();
    R_RLIN39_set_busy();
    R_RLIN39_Send((uint8_t *)string,length);
    
    

}

void uart_callback_receiveend_cb(void){

rx_buffer_wr_ptr++;
R_RLIN39_Receive((uint8_t *) &rx_buffer[rx_buffer_wr_ptr],1);
}

/*****************************************************************************
** Function:    R_UartReceiveChar
** Description: Receives the character from user over UART.
** Parameter:   None
** Return:      char
******************************************************************************/
char R_UartReceiveChar (void)
{
    char chr = '\0';
    if (rx_buffer_wr_ptr!=tx_buffer_rd_ptr)
    {
        chr=rx_buffer[tx_buffer_rd_ptr++];
    }
        
    return chr;
}

/*****************************************************************************
** Function:    R_UartClearDataRx
** Description: Clear the received data over UART.
** Parameter:   None
** Return:      char
******************************************************************************/
void R_UartClearDataRx (void)
{
    
}
