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
* File Name    : U2B_TAUD_App.c
* Version      : 1.00
* Device(s)    : RH850/U2B
* Description  : This is source file for TAUD application.
*******************************************************************************/

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
/* U2B application */
#include "U2B_TAUD_App.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/

/******************************************************************************/

/*******************************************************************************
* Function Name: Config_TAUD
* Description  : initial setting of TAUD
*                 - unit     : TAUDn (n: argument n)
*                 - channel  : ch.m (m: argument m)
*                 - mode     : interval timer function
*                 - pin      : P22_0 (if n=2, m=0)
*                 - clock    : 20MHz/8
* Arguments    : uint8_t n    : unit number of TAUD to config
*                uint8_t m    : channel number of TAUDn to config
*                uint32_t cmp : interval period count (TAUDnCDRm register value)
* Return Value : None
*******************************************************************************/
void Config_TAUD( unsigned char n, unsigned char m, unsigned long cmp )
{
	unsigned char	prs=0;
	
	
	/* Configure TAUDn ch.m interrupt */
	/////////////////////////////////////////////////////
	STB_ReleaseModuleStandby_Units( &rMSR_TAUD, 1 << n );
	INTC_ConfigInterrupt( TAUD_INT, INTC_NOMASK, INTC_TABLE_METHOD, 15 );
	
	/* release module standby */
	/////////////////////////////////////////////////////
	STB_ReleaseModuleStandby_Units( &rMSR_TAUD, 1 << n );
	
	/* Configure TAUDn ch.m */
	/////////////////////////////////////////////////////
	/* TAUDn initialize by interval timer function */
	TAUD_InitializeIntervalTimer( n, m, prs );
	
	/* change divition rate of TAUDn prescaler */
	TAUD_SetPrsDiv( n, prs, 8 );	// change divition rate of TAUDn prescaler to PCLK/2^8 = PCLK/256
	
	/* TAUDn output setting */
	TAUD_EnableOutput( n, m );		// TAUDnOm output enable
	
	/* port setting */
	TAUD_OpenTOpin( n, m );			// open TAUDnOm
	
	/* set compare value */
	TAUD_SetCompareValue( n, m, cmp );
}
