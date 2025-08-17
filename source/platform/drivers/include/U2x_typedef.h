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
* File Name    : U2x_typedef.h
* Version      : 1.00
* Device(s)    : RH850/U2B
* Description  : This is header file for typedef.
*******************************************************************************/

#ifndef	__U2x_typedef_H__
#define	__U2x_typedef_H__

//////////////////////////////////////////////////////////////////////
// type definition
//////////////////////////////////////////////////////////////////////
typedef	unsigned char	u08;
typedef	signed char 	s08;
typedef	unsigned short	u16;
typedef	signed short	s16;
typedef	unsigned long	u32;
typedef	signed long  	s32;
typedef	unsigned long long	u64;
typedef	signed long  long 	s64;
typedef	float        	f32;	// E: 8 bit, M 23 bit
typedef	double       	f64;	// E: 11 bit, M 52 bit

#endif // __U2x_typedef_H__
