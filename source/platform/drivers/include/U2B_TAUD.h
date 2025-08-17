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
* File Name    : U2B_TAUD.c
* Version	    : 1.00
* Device(s) 	: RH850/U2B
* Description  : This is header file for TAUD configuration.
*******************************************************************************/

#ifndef	__U2B_TAUD_H__
#define	__U2B_TAUD_H__

//////////////////////////////////////////////////////////
// include
//////////////////////////////////////////////////////////
#include "U2x_typedef.h"
#include "U2x_general.h"


//////////////////////////////////////////////////////////
// register definition
//////////////////////////////////////////////////////////
// register base address
#define	TAUD0_base	(0xFFBF4000)	// P-Bus Group 5
#define	TAUD1_base	(0xFF894000)	// P-Bus Group 11H
#define	TAUD2_base	(0xFFBF6000)	// P-Bus Group 5
#define	TAUD3_base	(0xFF896000)	// P-Bus Group 11H
		
extern const u32	TAUDn_base_addr[];
#define	TAUDn_base(n)	TAUDn_base_addr[n]
			
// TAUD register
// TAUDn Prescaler Registers			
#define	rTAUDnTPS(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x240) )        	// TAUDn Prescaler Clock Select Register
#define	rTAUDnBRS(n)    	(*(volatile unsigned char  *) (TAUDn_base(n) + 0x244) )        	// TAUDn Prescaler Baud Rate Setting Register
// TAUDn Control Registers			
#define	rTAUDnCDRm(n,m) 	(*(volatile unsigned short *) (TAUDn_base(n) + 0x0 + m*0x4) )  	// TAUDn Channel Data Register m
#define	rTAUDnCNTm(n,m) 	(*(volatile unsigned short *) (TAUDn_base(n) + 0x80 + m*0x4) ) 	// TAUDn Channel Counter Register m
#define	rTAUDnCMORm(n,m)	(*(volatile unsigned short *) (TAUDn_base(n) + 0x200 + m*0x4) )	// TAUDn Channel Mode OS Register m
#define	rTAUDnCMURm(n,m)	(*(volatile unsigned char  *) (TAUDn_base(n) + 0xC0 + m*0x4) ) 	// TAUDn Channel Mode User Register m
#define	rTAUDnCSRm(n,m) 	(*(volatile unsigned char  *) (TAUDn_base(n) + 0x140 + m*0x4) )	// TAUDn Channel Status Register m
#define	rTAUDnCSCm(n,m) 	(*(volatile unsigned char  *) (TAUDn_base(n) + 0x180 + m*0x4) )	// TAUDn Channel Status Clear Trigger Register m
#define	rTAUDnTS(n)     	(*(volatile unsigned short *) (TAUDn_base(n) + 0x1C4) )        	// TAUDn Channel Start Trigger Register
#define	rTAUDnTE(n)     	(*(volatile unsigned short *) (TAUDn_base(n) + 0x1C0) )        	// TAUDn Channel Enable Status Register
#define	rTAUDnTT(n)     	(*(volatile unsigned short *) (TAUDn_base(n) + 0x1C8) )        	// TAUDn Channel Stop Trigger Register
// TAUDn Output Registers			
#define	rTAUDnTOE(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x5C) )         	// TAUDn Channel Output Enable Register
#define	rTAUDnTO(n)     	(*(volatile unsigned short *) (TAUDn_base(n) + 0x58) )         	// TAUDn Channel Output Register
#define	rTAUDnTOM(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x248) )        	// TAUDn Channel Output Mode Register
#define	rTAUDnTOC(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x24C) )        	// TAUDn Channel Output Configuration Register
#define	rTAUDnTOL(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x040) )        	// TAUDn Channel Output Active Level Register
#define	rTAUDnTDE(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x250) )        	// TAUDn Channel Dead Time Output Enable Register
#define	rTAUDnTDM(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x254) )        	// TAUDn Channel Dead Time Output Mode Register
#define	rTAUDnTDL(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x54) )         	// TAUDn Channel Dead Time Output Level Register
#define	rTAUDnTRO(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x4C) )         	// TAUDn Channel Real-time Output Register
#define	rTAUDnTRE(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x258) )        	// TAUDn Channel Real-time Output Enable Register
#define	rTAUDnTRC(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x25C) )        	// TAUDn Channel Real-time Output Control Register
#define	rTAUDnTME(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x50) )         	// TAUDn Channel Modulation Output Enable Register
// TAUDn Reload Data Registers			
#define	rTAUDnRDE(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x260) )        	// TAUDn Channel Reload Data Enable Register
#define	rTAUDnRDM(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x264) )        	// TAUDn Channel Reload Data Mode Register
#define	rTAUDnRDS(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x268) )        	// TAUDn Channel Reload Data Control Channel Select Register
#define	rTAUDnRDC(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x26C) )        	// TAUDn Channel Reload Data Control Register
#define	rTAUDnRDT(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x44) )         	// TAUDn Channel Reload Data Trigger Register
#define	rTAUDnRSF(n)    	(*(volatile unsigned short *) (TAUDn_base(n) + 0x48) )         	// TAUDn Channel Reload Status Register

	
//////////////////////////////////////////////////////////
// Definition
//////////////////////////////////////////////////////////

	// Configuration Value
	//////////////////////////////////////////////////////////
	// Interval timer function [TAUD_InitializeIntervalTimer]
	#define	TAUD_CFG_IT_MD0	(0U)	// TAUDnMD0=0: Disables the interrupts when counting starts
//	#define	TAUD_CFG_IT_MD0	(1U)	// TAUDnMD0=1: Enables the interrupts when counting starts.


//////////////////////////////////////////////////////////
// function and related definition
//////////////////////////////////////////////////////////
// Configuration
//////////////////////////////////////////////////////////////////////
// sets TAUDn PRS clock divide rate
u08 TAUD_SetPrsDiv( u08 n, u08 prs, u08 div );

// sets compare value "cmp_value" to TAUD unit "n" channel "m"
#define TAUD_SetCompareValue(n,m,cmp_value)  	Reg16WRC( &rTAUDnCDRm(n,m), cmp_value, 0xFFFF )

// initializes TAUDn channel m with the interval timer mode
u08 TAUD_InitializeIntervalTimer( u08 unit, u08 ch, u08 prs );

// Operation
//////////////////////////////////////////////////////////////////////
// starts count of TAUD unit "n" channel "m"
#define	TAUD_StartCount(n,m)	rTAUDnTS(n) = (1 << m)

// stops count of TAUD unit "n" channel "m"
#define	TAUD_StopCount(n,m)			rTAUDnTT(n) = (1 << m)

// Configuration TAUDnOm Output
//////////////////////////////////////////////////////////////////////
// enables TAUDnOm output of TAUD unit "n" channel "m"
#define	TAUD_EnableOutput(n,m)			Reg16SetBitCheck( &rTAUDnTOE(n), m )

// disables TAUDnOm output of TAUD unit "n" channel "m"
#define	TAUD_DisableOutput(n,m)			Reg16ClearBitCheck( &rTAUDnTOE(n), m )

// sets output level to high level of TAUD unit "n" channel "m"
#define	TAUD_SetOutputLevelHigh(n,m)		Reg16SetBitCheck( &rTAUDnTO(n), m )

// sets output level to Low level of TAUD unit "n" channel "m"
#define	TAUD_SetOutputLevelLow(n,m)		Reg16ClearBitCheck( &rTAUDnTO(n), m )

// Open pin
//////////////////////////////////////////////////////////////////////
void TAUD_OpenTOpin( u08 n, u08 m );

#endif // __U2B_TAUD_H__
