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
* File Name    : U2B_clock.h
* Version      : 1.00
* Device(s)    : RH850/U2B
* Description  : This is header file for clock controller configuration.
*******************************************************************************/

#ifndef	__U2B_Clock_H__
#define	__U2B_Clock_H__


#include "U2x_typedef.h"
#include "U2x_general.h"


//////////////////////////////////////////////////////////////////////
// Const Value Definition
//////////////////////////////////////////////////////////////////////
// internal use in function CLK_GearUpCLK_SYS
#define	CLK_SYS_IOSC	(1U)	// not use as register value	
#define	CLK_SYS_CLEAN	(2U)	// not use as register value
#define	CLK_SYS_SSCG	(3U)	// not use as register value
#define	CLK_SYS_SSCG1	(4U)	// not use as register value

// return value of definition CLK_GetCKDIVMD
#define	CLK_CKDIVMD_240MHz	(0U)	// 0xB: CPU Frequency = 240MHz
#define	CLK_CKDIVMD_320MHz	(2U)	// 10B: CPU Frequency = 320MHz
#define	CLK_CKDIVMD_400MHz	(3U)	// 11B: CPU Frequency = 400MHz

// argument clock of function CLK_ChangeCLK_RLIN3
#define	RLIN3_CLK_EMG	(0U)	// CLK_EMG (default)
#define	RLIN3_CLKC_HSB	(1U)	// CLKC_HSB
#define	RLIN3_CLK_MOSC	(2U)	// CLK_MOSC
#define	RLIN3_CLK_MOSC4	(3U)	// CLK_MOSC/4
#define	RLIN3_CLK_MOSC8	(4U)	// CLK_MOSC/8


//////////////////////////////////////////////////////////////////////
// functional definition
//////////////////////////////////////////////////////////////////////
// release write protection for clock related registers
#define	CLK_ReleaseWriteProtect()	rCLKKCPROT1 = 0xA5A5A501

// set write protection for clock related registers
#define	CLK_SetWriteProtect()    	rCLKKCPROT1 = 0xA5A5A500

// get OPBT11.CKDIVMD bit value
#define CLK_GetCKDIVMD()	((u08)((rOPBT11 >> 30) & 0x03 ))


//////////////////////////////////////////////////////////////////////
// Function Prototype Declaration
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Function Name: CLK_EnableMOSC
// Description  : This function enables Main OSC.
// target device: [U2B]
// Arguments    : (none)
// Return Value : processing result of this function
//	RET_OK       : no error occured
//	RET_NONEED   : not execute this function due to Main OSC has 
//	               already enabled
//	RET_ERR_STATE: not execute this function because Main OSC does 
//	               not stoppped
//	               (ether rMOSCEN=0 or MOSCSTAB=1: abnormal state)
// Example      :
//   [code]
//	CLK_EnableMOSC();	// enables Main OSC
//
//   [result]
//	Main OSC is enabled.
//////////////////////////////////////////////////////////////////////
u08 CLK_EnableMOSC( void );


//////////////////////////////////////////////////////////////////////
// Function Name: CLK_EnablePLL
// Description  : This function enables PLL.
// target device: [U2B]
// Arguments    : (none)
// Return Value : processing result of this function
//	RET_OK       : no error occured
//	RET_NONEED   : not execute this function due to PLL has 
//	               already enabled
//	RET_ERR_STATE: not execute this function because PLL does 
//	               not stoppped
//	               (ether PLLEN=0 or PLLSTAB=1: abnormal state)
// Example      :
//   [code]
//	CLK_EnablePLL();	// enables PLL
//
//   [result]
//	PLL is enabled.
//////////////////////////////////////////////////////////////////////
u08 CLK_EnablePLL( void );


//////////////////////////////////////////////////////////////////////
// Function Name: CLK_GearUpCLK_SYS
// Description  : This function changes CLK_SYS_CLEAN or CLK_SYS_SSCG or
//                CLK_SYS_SSCG1 from CLK_HSIOSC/2 to CLK_PLLO or CLK_SSCG
//                CLK_SSCG1. 
// target device: [U2B]
// Arguments    : u08 source
//	CLK_SYS_CLEAN: change CLK_SYS_CLEAN to CLK_PLLO
//	CLK_SYS_SSCG : change CLK_SYS_SSCG to CLK_SSCG
//	CLK_SYS_SSCG1: change CLK_SYS_SSCG1 to CLK_SSCG1
// Return Value : Function return value defined in U2x_general.h	
//	RET_OK: no error
//	RET_ERR_PARAM: argument is out of range
// remarkable   : This flow is same as Figure 15.11 in U2B UM Rev.0.40.
//                If CLK_SYS_SSCG or CLK_SYS_SSCG1 specify as argument,
//                SSCGC or SSCGC1 register need to configurate previously.
//                - need to set OPBT36.SSCG1_DIS (bit 23)=0 if SSCG1 Gearup. 
// Example      :
//   [code]
//	CLK_GearUpCLK_SYS( CLK_SYS_CLEAN );	// changes CLK_SYS_CLEAN from CLK_HSIOSC/2 to CLK_PLLO/1
//
//   [result]
//	CLK_CPU = CLK_PLLO/1
//////////////////////////////////////////////////////////////////////
u08 CLK_GearUpCLK_SYS( u08 source );


//////////////////////////////////////////////////////////////////////
// Function Name: CLK_GearUp_SystemClocks
// Description  : This function changes system clocks:
//                  CLK_SYS_CLEAN = CLK_PLLO
//                  CLK_SYS_SSCG  = CLK_SSCG
//                  CLK_SYS_SSCG1 = CLK_SSCG1
// target device: [U2B]
// Arguments    : none
// Return Value : 
//	RET_OK: no error
//	others: some error occured
//////////////////////////////////////////////////////////////////////
u08 CLK_GearUp_SystemClocks( void );


//////////////////////////////////////////////////////////////////////
// Function Name: CLK_ChangeCLK_RLIN3
// Description  : This function changes CLK_RLIN3 source clock.
// target device: [U2B]
// Arguments    : 
//	u08 clock ... target CLK_RLIN3 source clock
//                    (value of rCKS_RLINC register)
//		RLIN3_CLK_EMG    	// CLK_EMG (default)
//		RLIN3_CLKC_HSB   	// CLKC_HSB
//		RLIN3_CLK_MOSC   	// CLK_MOSC
//		RLIN3_CLK_MOSC4  	// CLK_MOSC/4
//		RLIN3_CLK_MOSC8  	// CLK_MOSC/8
// Return Value : (none)
// Exapmpe      :
//	RLIN3u_ChangeCLK_RLIN3( RLIN3_CLK_EMG );  	// CLK_EMG (default)
//	RLIN3u_ChangeCLK_RLIN3( RLIN3_CLKC_HSB ); 	// CLKC_HSB
//	RLIN3u_ChangeCLK_RLIN3( RLIN3_CLK_MOSC ); 	// CLK_MOSC
//	RLIN3u_ChangeCLK_RLIN3( RLIN3_CLK_MOSC4 );	// CLK_MOSC/4
//	RLIN3u_ChangeCLK_RLIN3( RLIN3_CLK_MOSC8 );	// CLK_MOSC/8
//////////////////////////////////////////////////////////////////////
void CLK_ChangeCLK_RLIN3( u32 clock );

#endif 