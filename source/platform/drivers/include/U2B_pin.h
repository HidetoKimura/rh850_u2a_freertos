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
* File Name    : U2B_pin.h
* Version      : 1.00
* Device(s)    : RH850/U2B
* Description  : This is header file for pin function configuration.
*******************************************************************************/

#ifndef	__U2B_port_H__
#define	__U2B_port_H__

#include "U2x_typedef.h"

//////////////////////////////////////////////////////////////////////
// specification
//////////////////////////////////////////////////////////////////////
//	AWO port: JP0, P31, P33, P27(only _RESETOUT)
//	ISO port: P00, P01, P02, P10, P11, P12, P13, P14, P15, P20, P21,
//	          P22, P23, P24, P25, P30, P32, P34
//	PWE protectoin port: P21, P24_4~P24_7, P25_3~P25_6, P25_12~P25_15, P27
	

//////////////////////////////////////////////////////////////////////
// Register Definition
//////////////////////////////////////////////////////////////////////
	#define	PORT_base	(0xFFD90000U)	// P-Bus Group 2L

	#define	rPn(n)       	(*(volatile unsigned short *) (PORT_base + 0x0000 + 0x40*n) )         	// Port register
	#define	rPNOTn(n)    	(*(volatile unsigned short *) (PORT_base + 0x0008 + 0x40*n) )         	// Port NOT register
	#define	rPMn(n)      	(*(volatile unsigned short *) (PORT_base + 0x0010 + 0x40*n) )         	// Port Mode register
	#define	rPSRn(n)     	(*(volatile unsigned long  *) (PORT_base + 0x0004 + 0x40 * n))			// Port Set/Reset Register
	#define	rPCRn_m(n,m) 	(*(volatile unsigned long  *) (PORT_base + 0x2000 + 0x40*n  + 0x4*m) )	// Port Control register
	#define	rPKCPROT     	(*(volatile unsigned long  *) (PORT_base + 0x2F40) )                  	// Port Keycode Protection Register
	#define	rPWE         	(*(volatile unsigned long  *) (PORT_base + 0x2F44) )                  	// Port Write Enable register

//////////////////////////////////////////////////////////////////////
// Const Value Definition
//////////////////////////////////////////////////////////////////////
	// PM register value
	#define	PIN_OUT		(0U)	// output
	#define	PIN_IN 		(1U)	// input
	#define	PIN_INOUT	(2U)	// input/output
	
	
//////////////////////////////////////////////////////////////////////
// functional Definition
//////////////////////////////////////////////////////////////////////
// initialize monitor port for port ouput mode 
#define	PIN_InitMonitorPort(n)     	rPn(n) = 0; rPMn(n) = 0;

// reverse output level of specified monitor port bit
#define	PIN_ToggleMonitorPort(n,m)	rPNOTn(n) |=  (1 << m) 

// output high level of specified monitor port bit
#define	PIN_OutputHighMonitorPort(n,m)    	PIN_OutputPort( n, m, 1 )

// output low level of specified monitor port bit
#define	PIN_OutputLowMonitorPort(n,m)    	PIN_OutputPort( n, m, 0 )

// release write protection of specified
void PIN_ReleaseWriteProtect( u08 port );

// set write protection of specified
void PIN_SetWriteProtect( u08 port );

// set alternative function of specified Pn_m
u08 PIN_SetAltPORT( u08 n, u08 m, u08 alt, u08 io_mode );

// sets output level to specified port
void PIN_OutputPort( u08 n, u08 m, u08 level );

#endif // __U2B_port_H__
