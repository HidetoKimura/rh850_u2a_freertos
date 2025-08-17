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
* File Name    : U2B_OSTM.h
* Version      : 1.00
* Device(s)    : RH850/U2B
* Description  : This is header file for OSTM configuration.
*******************************************************************************/

#ifndef	__U2B_OSTM_H__
#define	__U2B_OSTM_H__


#include "U2x_typedef.h"

//////////////////////////////////////////////////////////////////////
// Const Value Definition
//////////////////////////////////////////////////////////////////////
	
	
//////////////////////////////////////////////////////////////////////
// Function Prototype Declaration
//////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Function Name: OSTM_ConfigStartInterval
// Description  : OSTMn initial setting and start as interval timer mode.
// Arguments    : 
//	u08 n   : unit number of OSTM
//	u32 time; interval time
// Return Value : (non)
//////////////////////////////////////////////////////////////////////
void OSTM_ConfigStartInterval( u08 n, u32 time );
	
#endif
