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
* File Name    : U2x_general.h
* Version      : 1.00
* Device(s)    : RH850/U2B
* Description  : This is header file for general function.
*******************************************************************************/

#ifndef	__U2x_general_H__
#define	__U2x_general_H__

#include "U2x_typedef.h"

//////////////////////////////////////////////////////////////////////
// Const Value Definition
//////////////////////////////////////////////////////////////////////
// return value
#define	RET_OK  	(0U)	// no error
#define	RET_ERR_REG	(1U)	// register compare check error
#define	RET_ERR_PARAM	(2U)	// argument error
#define	RET_ERR_STATE	(3U)	// status error
#define	RET_NONEED  	(4U)	// not need to execute this function

#define	TRUE	(1U)
#define	FALSE	(0U)

	
//////////////////////////////////////////////////////////////////////
// Function Prototype Declaration
//////////////////////////////////////////////////////////////////////
// waits by CPU execute
void wait( u32 count );
	
// register write, read and check
u08 Reg32WRC( volatile u32 *write_reg, u32 write_data, u32 mask );
u08 Reg16WRC( volatile u16 *write_reg, u16 write_data, u16 mask );
u08 Reg08WRC( volatile u08 *write_reg, u08 write_data, u08 mask );

// register read and check
u08 Reg32RC( volatile u32 *read_reg, u32 expect_data, u32 mask );
u08 Reg16RC( volatile u16 *read_reg, u16 expect_data, u16 mask );
u08 Reg08RC( volatile u08 *read_reg, u08 expect_data, u08 mask );

// register write, read and check for only specified bits
u08 Reg32RMWC( volatile u32 *write_reg, u32 write_data, u32 bitrange, u08 position );
u08 Reg16RMWC( volatile u16 *write_reg, u16 write_data, u16 bitrange, u08 position );
u08 Reg08RMWC( volatile u08 *write_reg, u08 write_data, u08 bitrange, u08 position );

// register write for only specified bits
void Reg32RMW( volatile u32 *write_reg, u32 write_data, u32 bitrange, u08 position );
void Reg16RMW( volatile u16 *write_reg, u16 write_data, u16 bitrange, u08 position );
void Reg08RMW( volatile u08 *write_reg, u08 write_data, u08 bitrange, u08 position );

// register set specified bit and check
u08 Reg32SetBitCheck( volatile u32 *write_reg, u08 bit );
u08 Reg16SetBitCheck( volatile u16 *write_reg, u08 bit );
u08 Reg08SetBitCheck( volatile u08 *write_reg, u08 bit );

// register clear specified bit and check
u08 Reg32ClearBitCheck( volatile u32 *write_reg, u08 bit );
u08 Reg16ClearBitCheck( volatile u16 *write_reg, u08 bit );
u08 Reg08ClearBitCheck( volatile u08 *write_reg, u08 bit );

// register set specified bit
void Reg32SetBit( volatile u32 *write_reg, u08 bit );
void Reg16SetBit( volatile u16 *write_reg, u08 bit );
void Reg08SetBit( volatile u08 *write_reg, u08 bit );

// register clear specified bit
void Reg32ClearBit( volatile u32 *write_reg, u08 bit );
void Reg16ClearBit( volatile u16 *write_reg, u08 bit );
void Reg08ClearBit( volatile u08 *write_reg, u08 bit );

// wait until specified bit becomes 1
void Reg32Wait1( volatile u32 *reg, u08 position );
void Reg16Wait1( volatile u16 *reg, u08 position );
void Reg08Wait1( volatile u08 *reg, u08 position );

// wait until specified bit becomes 0
void Reg32Wait0( volatile u32 *reg, u08 position );
void Reg16Wait0( volatile u16 *reg, u08 position );
void Reg08Wait0( volatile u08 *reg, u08 position );

// extrace bits
u32 Reg32GetsBits( u32 value, u32 bitrange, u08 position );
u32 Reg16GetsBits( u16 value, u16 bitrange, u08 position );
u32 Reg08GetsBits( u08 value, u08 bitrange, u08 position );

#endif
