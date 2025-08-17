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
* File Name    : U2B_TAUD_App.h
* Version      : 1.00
* Device(s)    : RH850/U2B
* Description  : This is header file for TAUD application.
*******************************************************************************/

#ifndef	__U2B_TAUD_App_H__
#define	__U2B_TAUD_App_H__

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
/* U2B driver */
#include "U2B_clock.h"
#include "U2B_interrupt.h"
#include "U2B_standby.h"
#include "U2B_TAUD.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define		TAUD_UNIT     	2
#define		TAUD_CH       	0
#define		TAUD_INT       	INTC_DP_INTTAUD2I0
#define		TAUD_FREQUENCY	(80000000U/256)	/* 312.5kHz@Gearupped */

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/
/* initial setting of TAUD */
extern void Config_TAUD( unsigned char n, unsigned char m, unsigned long cmp );

#endif /* __U2B_TAUD_App_H__ */
