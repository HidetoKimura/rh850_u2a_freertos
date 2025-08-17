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
* File Name    : U2B_interrupt.h
* Version      : 1.00
* Device(s)    : RH850/U2B
* Description  : This is header file for TAUD configuration.
*******************************************************************************/

#ifndef	__U2B_interrupt_H__
#define	__U2B_interrupt_H__


#include "U2x_typedef.h"


//////////////////////////////////////////////////////////////////////
// Const Value Definition
//////////////////////////////////////////////////////////////////////
// for function INTC_ConfigInterrupt
#define	INTC_DIRECT_METHOD	(0U)	// Direct vector method
#define	INTC_TABLE_METHOD	(1U)	// Table reference method
#define	INTC_NOMASK		(0U)	// release interrupt mask
#define	INTC_MASK  		(1U)	// set interrupt mask


//////////////////////////////////////////////////////////////////////
// Interrupt number Definition
//////////////////////////////////////////////////////////////////////
// channel number of INTOSTMnTINT
#define	INTC_DP_INTOSTM0TINT         	360
#define	INTC_DP_INTOSTM1TINT         	361
#define	INTC_DP_INTOSTM2TINT         	841
#define	INTC_DP_INTOSTM3TINT         	842
#define	INTC_DP_INTOSTM4TINT         	968
#define	INTC_DP_INTOSTM5TINT         	969

#define	INTC_DP_INTTAUD2I0          	344
	
#define	INTC_DP_INTOSTMnTINT(n)	Intc_dp_intostmntint[n]
extern const u16		Intc_dp_intostmntint[];

#define	INTC_DP_INTRLIN3nUR0(n)			621		// only support RLIN30


//////////////////////////////////////////////////////////////////////
// Function Prototype Declaration
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Function Name: INTC_ConfigInterrupt
// Description  : This function configures interrupt mask, method and priority.
// Arguments    : 
//	u16 dp:
//		DP number of interrupt
//	u08 mask:
//		0: release interrupt mask
//		1: set interrupt mask
//	u08 method:
//		0: Direct vector method
//		1: table referencing method
//	u08 priority:
//		priority of this interrupt (0: highest priority, 15: lowest priority)
// Return Value : none
// Example      : 
//	// setting INTIPIR0 interrupt
//	INTC_ConfigInterrupt( INTC_DP_INTIPIR0, INTC_NOMASK, INTC_TABLE_METHOD, 0 );
//////////////////////////////////////////////////////////////////////
void INTC_ConfigInterrupt( u16 dp, u08 mask, u08 method, u08 priority );


//////////////////////////////////////////////////////////////////////
// Function Name: INTC_ConfigInterruptBind
// Description  : This function configures bind distination.
// Arguments    : 
//	u16 dp:
//		DP number of interrupt
//	u08 gm:
//		0: bound to host partition
//		1: bound to guest partition
//	u08 gpid:
//		distination partition when gm=1
//	u08 peid:
//		bound to PEID
// Return Value : none
// Example      : 
//	// setting INTIPIR0 interrupt bind
//	INTC_ConfigInterruptBind( INTC_DP_INTIPIR0, 1, 2, 0 );
//////////////////////////////////////////////////////////////////////
void INTC_ConfigInterruptBind( u16 dp, u08 gm, u08 gpid, u08 peid );


//////////////////////////////////////////////////////////////////////
// Function Name: INTC_WaitInterrupt
// Description  : This function waits until specified interrupt generate.
// Arguments    : 
//	u16 dp:
//		DP number of interrupt
// Return Value : none
//////////////////////////////////////////////////////////////////////
void INTC_WaitInterrupt( u16 dp );


//////////////////////////////////////////////////////////////////////
// Function Name: INTC_ClearInterruptFlag
// Description  : This function clears specified interrupt flag.
// Arguments    : 
//	u16 dp:
//		DP number of interrupt
// Return Value : none
//////////////////////////////////////////////////////////////////////
void INTC_ClearInterruptFlag( u16 dp );

#endif
