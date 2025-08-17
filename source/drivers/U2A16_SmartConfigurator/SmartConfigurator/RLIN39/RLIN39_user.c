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
* Copyright (C) 2018, 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : RLIN39_user.c
* Component Version: 1.6.0
* Device(s)        : R7F702300BFABA
* Description      : This file implements device driver for RLIN39.
***********************************************************************************************************************/
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "RLIN39.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t  * gp_uart9_tx_address;       /* uart9 transmit data address */
extern volatile uint16_t   g_uart9_tx_count;          /* uart9 transmit data number */
extern volatile uint8_t  * gp_uart9_rx_address;       /* uart9 receive data address */
extern volatile uint16_t   g_uart9_rx_count;          /* uart9 receive data number */
extern volatile uint16_t   g_uart9_rx_length;         /* uart9 receive data length */
void r_RLIN39_callback_receiveend(void);
void r_RLIN39_callback_sendend(void);
void r_RLIN39_callback_error(uint32_t err_type);
/* Start user code for global. Do not edit comment generated here */
extern void uart_callback_receiveend_cb(void);
extern volatile uint8_t g_rlin39_busy;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_RLIN39_Create_UserInit
* Description  : This function adds user code after initializing UART module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_RLIN39_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
     /* Set LIN reset mode */
    RLN39.LCUC.UINT8 = _UART_LIN_RESET_MODE_CAUSED;
    while(RLN39.LMST.BIT.OMM0 != 0);
    /*  update prescaler to Baudrate 115200 */
    RLN39.LWBR.UINT8 = _UART_8_SAMPLING | _UART_PRESCALER_CLOCK_SELECT_1;
    RLN39.LBRP01.UINT16 = 86;
     /* leave  LIN reset mode */
    RLN39.LCUC.UINT8 = _UART_LIN_RESET_MODE_CANCELED;
    while(RLN39.LMST.BIT.OMM0 == 0);
    g_rlin39_busy=0;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_RLIN39_interrupt_receive
* Description  : This function is UART9 receive interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if defined (__CCRH__)
#pragma interrupt r_RLIN39_interrupt_receive(enable=false, channel=454, fpu=true, callt=false)
#elif defined (__ghs__)
#pragma ghs interrupt
#elif defined (__ICCRH850__)
#pragma type_attribute=__interrupt
#else
#error Unknown Compiler
#endif
void r_RLIN39_interrupt_receive(void)
{
    uint8_t  rx_data_8;
    uint16_t temp;
    rx_data_8 = RLN39.LURDR.UINT16;

    temp = g_uart9_rx_count;
    if (g_uart9_rx_length > temp)
    {
        *gp_uart9_rx_address = rx_data_8;
        gp_uart9_rx_address++;
        g_uart9_rx_count++;
        temp = g_uart9_rx_count;
        if (g_uart9_rx_length == temp)
        {
            r_RLIN39_callback_receiveend();
        }
    }
}

/***********************************************************************************************************************
* Function Name: r_RLIN39_interrupt_error
* Description  : This function is UART9 error interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if defined (__CCRH__)
#pragma interrupt r_RLIN39_interrupt_error(enable=false, channel=455, fpu=true, callt=false)
#elif defined (__ghs__)
#pragma ghs interrupt
#elif defined (__ICCRH850__)
#pragma type_attribute=__interrupt
#else
#error Unknown Compiler
#endif
void r_RLIN39_interrupt_error(void)
{
    uint32_t err_type;
    *gp_uart9_rx_address = RLN39.LURDR.UINT16;
    err_type = (uint8_t)(RLN39.LEST.UINT8);
    RLN39.LEST.UINT8 &= (uint8_t) ~_UART_CLEAR_ERROR_FLAG;
    r_RLIN39_callback_error(err_type);
}

/***********************************************************************************************************************
* Function Name: r_RLIN39_interrupt_send
* Description  : This function is UART9 send interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if defined (__CCRH__)
#pragma interrupt r_RLIN39_interrupt_send(enable=false, channel=453, fpu=true, callt=false)
#elif defined (__ghs__)
#pragma ghs interrupt
#elif defined (__ICCRH850__)
#pragma type_attribute=__interrupt
#else
#error Unknown Compiler
#endif
void r_RLIN39_interrupt_send(void)
{
    if (g_uart9_tx_count > 0U)
    {
        RLN39.LUTDR.UINT16= *gp_uart9_tx_address;
        gp_uart9_tx_address++;
        g_uart9_tx_count--;
    }
    else
    {
        r_RLIN39_callback_sendend();
    }
}

/***********************************************************************************************************************
* Function Name: r_RLIN39_callback_sendend
* Description  : This function is UART9 send end callback service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_RLIN39_callback_sendend(void)
{
    /* Start user code for r_RLIN39_callback_sendend. Do not edit comment generated here */
    g_rlin39_busy=0;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_RLIN39_callback_error
* Description  : This function is UART9 error callback service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_RLIN39_callback_error(uint32_t err_type)
{
    /* Start user code for r_RLIN39_callback_error. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_RLIN39_callback_receiveend
* Description  : This function is UART9 receive end callback service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_RLIN39_callback_receiveend(void)
{
    /* Start user code for r_RLIN39_callback_receiveend. Do not edit comment generated here */
    uart_callback_receiveend_cb();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
