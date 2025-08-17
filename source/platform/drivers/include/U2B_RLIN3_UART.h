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
* File Name    : U2B_RLIN3_UART.h
* Version      : 1.00
* Device(s)    : RH850/U2B
* Description  : This is header file for UART mode of RLIN3 configuration.
*                This driver supports only followings:
*                 - unit     : RLIN30
*                 - mode     : UART mode
*                 - pin      : P02_6 (RLIN30TX)
*                 - clock    : X1 = 20MHz, CLK_RLIN3 = CLK_MOSC/4 (5MHz) 
*                 - communication format:
*                     - baudrate : 115,200bps or 230,400bps
*                     - data no invert
*                     - no parity
*                     - 1 stop bit
*                     - LSB first
*                     - 8 bit data length
*                     - inter byte space: 0 Tbit
*******************************************************************************/

#ifndef	__U2x_RLIN3_UART_H__
#define	__U2x_RLIN3_UART_H__

//////////////////////////////////////////////////////////
// include
//////////////////////////////////////////////////////////
#include "U2x_typedef.h"
#include "U2x_general.h"


//////////////////////////////////////////////////////////
// Type Definition
//////////////////////////////////////////////////////////
typedef enum{
	// CLK_RLIN = 5MHz (MainOSC=20MHz, CLK_RLIN=MainOSC/4)
	RLIN3u_BAUDRATE5MHzto9600bps,          // 9615.38bps (error: 0.160%)
	RLIN3u_BAUDRATE5MHzto14400bps,         // 14367.82bps (error: 0.223%)
	RLIN3u_BAUDRATE5MHzto19200bps,         // 19230.77bps (error: 0.160%)
	RLIN3u_BAUDRATE5MHzto38400bps,         // 38461.54bps (error: 0.160%)
	RLIN3u_BAUDRATE5MHzto57600bps,         // 56818.18bps (error: -1.357%)
	RLIN3u_BAUDRATE5MHzto115200bps,        // 113636.36bps (error: -1.357%)
	RLIN3u_BAUDRATE5MHzto230400bps,        // 227272.73bps (error: -1.357%)
	RLIN3u_BAUDRATE5MHzto460800bps,        // 454545.45bps (error: -1.357%)
	RLIN3u_BAUDRATE5MHzto921600bps,        // 833333.33bps (error: -9.578%)
	// end
	RLIN3U_BAUDRATE_END
}RLIN3u_baudrate;


//////////////////////////////////////////////////////////
// general definition
//////////////////////////////////////////////////////////
	#define	COM_UNIT         		(0U)		// RLIN3 unit to use
	#define	COM_PIN         		(0U)		// P02_6 ALT OUT8 @COM_UNIT=0
	#define	RLIN3u_BUFFER_MAX     	(256)		// receive buffer max


//////////////////////////////////////////////////////////
// function and related definition
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Function Name: OpenCOMport
// Description  : This function is COM port quick open using definition
//                 - unit     : RLIN30
//                 - mode     : UART mode
//                 - pin      : P02_6 (RLIN30TX)
//                 - clock    : X1 = 20MHz, CLK_RLIN3 = CLK_MOSC/4 (5MHz) 
//                 - communication format
//                     - baudrate : 230,400bps
//                     - data no invert
//                     - no parity
//                     - 1 stop bit
//                     - LSB first
//                     - 8 bit data length
//                     - inter byte space: 0 Tbit
// Arguments    : (none) 
// Return Value : (none)
//////////////////////////////////////////////////////////////////////
void OpenCOMport( void );


//////////////////////////////////////////////////////////////////////
// Function Name: RLIN3u_Initialize
// Description  : This function initializes UART specified RLIN3n unit.
//                    - error: all disable
//                    - communication format
//                        - data no invert
//                        - no parity
//                        - 1 stop bit
//                        - LSB first
//                        - 8 bit data length
//                    - inter byte space: 0 Tbit
// Arguments    : 
//	u08 n:
//		unit number of RLIN3n
//	RLIN3u_baudrate baudrate
//		baud rate (RLIN3u_BAUDRATExxMHztoXXXbps)
// Return Value : (none)
// Example      : 
//	RLIN3u_Initialize( 0, RLIN3u_BAUDRATE5MHzto230400bps );	// initialize RLIN30 UART with baud rate 227273bps@MOSC=20MHz
//////////////////////////////////////////////////////////////////////
u08 RLIN3u_Initialize( u08 n, RLIN3u_baudrate baudrate );
	

//////////////////////////////////////////////////////////////////////
// Function Name: RLIN3u_SetBaudrate
// Description  : This function sets UART baud rate specified RLIN3n 
//                unit.
// Arguments    :
//	u08 n:
//		unit number of RLIN3n
//	RLIN3u_baudrate baudrate
//		baud rate (RLIN3u_BAUDRATExxMHztoXXXbps)
// Return Value : 
//	RET_OK: writing registers were successful
//	count : failed count of writing registers
// Example      : 
//	RLIN3u_SetBaudrate( 0, RLIN3u_BAUDRATE5MHzto230400bps );	// initialize RLIN30 UART with baud rate 227273bps@MOSC=20MHz
//////////////////////////////////////////////////////////////////////
u08 RLIN3u_SetBaudrate( u08 n, RLIN3u_baudrate baudrate );



//////////////////////////////////////////////////////////////////////
// Function Name: RLIN3u_OpenTXpin
// Description  : This function opens the alternative function of 
//                RLIN3nTX pin.
// Arguments    :
//	u08 n:
//		unit number of RLIN3n
//	u08 m:
//		index of share port
// Return Value : (none)
// Example      : 
//    [U2B]
//	RLIN3u_OpenTXpin( 0, 0 );	// RLIN30TX(P02_6)
//////////////////////////////////////////////////////////////////////
void RLIN3u_OpenTXpin( u08 n, u08 m );


//////////////////////////////////////////////////////////////////////
// Function Name: RLIN3u_Tx
// Description  : This function transmits data by specified RLIN3n unit.
// Arguments    :
//	u08 n:
//		unit number of RLIN3n
//	u16 tx_data
//		transmit data
// Return Value : (none)
// Example      : 
//	RLIN3u_Tx( 0, 0xAA );	// transmit 0xAA from RLIN30
//////////////////////////////////////////////////////////////////////
void RLIN3u_Tx( u08 n, u16 tx_data );


 //////////////////////////////////////////////////////////////////////
// Function Name: COM_printf
// Description  : This function outputs charactor with format like printf function.
// Arguments    :
//	char *fmt: string with format to output
//	    [format]
//		%c: output charactor (ex."%c")
//		%s: output charactors (ex. %8s", "%-10s")
//		%d: output decimal integer number  (ex. "%-2d","%03d")
//		%o: output octadecimal integer number (ex. "%06o","%03o")
//		%x: output hexadecimal integer number (ex. "%04x")
//		%f: output floating point number (ex. "%5.3f")
// Return Value : non
//////////////////////////////////////////////////////////////////////
void COM_printf( s08 *fmt, ... );


#endif	// __U2x_RLIN3_UART_H__

