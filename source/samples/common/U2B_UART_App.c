/*******************************************************************************
* DISCLAIMER 
* This software is supplied by Renesas Electronics Corporation and is only  
* intended for use with Renesas products. No other uses are authorized. This  
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE  
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. 
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS  
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE  
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software. By using this software, 
* you agree to the additional terms and conditions found by accessing the  
* following link: 
* http://www.renesas.com/disclaimer 
* 
* Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.     
*******************************************************************************/
/*******************************************************************************
* File Name    : U2B_UART_App.c
* Version      : 1.00
* Device(s)    : RH850/U2B
* Description  : This is source file for UART application.
*******************************************************************************/

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
/* U2B driver */
#include "U2B_clock.h"
#include "U2B_standby.h"
#include "U2B_RLIN3_UART.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/
void InitialSettingUART( void );

/******************************************************************************/

/*******************************************************************************
* Function Name: InitialSettingUART
* Description  : Initialize RLIN30 as UART mode.
*                 - unit     : RLIN30
*                 - mode     : UART mode
*                 - pin      : P02_6 (RLIN30TX)
*                 - clock    : X1 = 20MHz, CLK_RLIN3 = CLK_MOSC/4 (5MHz) 
*                 - communication format:
*                     - baudrate : 115,200bps
*                     - data no invert
*                     - no parity
*                     - 1 stop bit
*                     - LSB first
*                     - 8 bit data length
*                     - inter byte space: 0 Tbit
* Arguments    : None
* Return Value : None
*******************************************************************************/
void InitialSettingUART( void )
{
	unsigned char		n=COM_UNIT;	/* RLIN3 unit to use */
	
	
	/* Release RLIN30 from standby mode */
	STB_ReleaseModuleStandby_Units( &rMSR_RLIN3, 1 << n );
	
	/* Changes CLK_RLIN=CLK_MOSC/4 */
	CLK_ChangeCLK_RLIN3( RLIN3_CLK_MOSC4 );
	
	/* initialize RLIN30 UART */
	RLIN3u_Initialize( n, RLIN3u_BAUDRATE5MHzto115200bps );
	
	/* open UART port */
	RLIN3u_OpenTXpin( n, COM_PIN );
	
	/* output message to COM port */
	COM_printf( "Power up!\r\n" );
}
