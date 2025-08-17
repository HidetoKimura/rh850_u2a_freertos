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
 * www.renesas.com/disclaimer
 * Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * File Name   : r_types.h
 * Device(s)   : RH850
 * Description : common types
 ******************************************************************************/

#ifndef R_TYPES_H
#define R_TYPES_H
#include "common.h"
/*##############################################################################
 # Dependencies:
 #############################################################################*/

/*##############################################################################
 # global macros
 #############################################################################*/

/*******************************************************************************
 * Name          : RMW
 * Description   : macro to read modify write any size register
 * Arguments     : reg = Register to be modified.
 *               : clr_mask = Bitmask of bitfields to be cleared.
 *               : set_mask = Bitmask of bits to be set.
 * Return Value  : None
 * NOTE          : obsolete DO NOT USE!!!
 ******************************************************************************/
#define RMW(reg, clr_mask, set_mask)     (reg) = ((reg) & ~(clr_mask)) \
	                                             | (set_mask)


/*******************************************************************************
 * Name          : RMW8
 * Description   : Macro to read modify write 8-bit registers
 * Arguments     : reg8       = 8-bit register to update
 *               : clr_mask   = Bit mask of bits to be cleared.
 *               : set_mask   = Bit mask of bits to be set.
 * Return Value  : None
 ******************************************************************************/
#define RMW8(reg8, clr_mask, set_mask)    (reg8) = (uint8)(                 \
		                                            ((reg8) & ~(clr_mask))  \
                                                    | (set_mask))


/*******************************************************************************
 * Name          : RMW16
 * Description   : Macro to read modify write 16-bit registers
 * Arguments     : reg16      = 16-bit register to update
 *               : clr_mask   = Bit-mask of bits to be cleared.
 *               : set_mask   = Bit-mask of bits to be set.
 * Return Value  : None
 ******************************************************************************/
#define RMW16(reg16, clr_mask, set_mask)    (reg16) = (uint16)(                \
		                                               ((reg16) & ~(clr_mask)) \
                                                       | (set_mask))


/*******************************************************************************
 * Name          : RMW32
 * Description   : Macro to read modify write 32-bit registers
 * Arguments     : reg32      = 32-bit register to update
 *               : clr_mask   = Bit-mask of bits to be cleared.
 *               : set_mask   = Bit-mask of bits to be set.
 * Return Value  : None
 ******************************************************************************/
#define RMW32(reg32, clr_mask, set_mask)    (reg32) = (uint32)(                \
                                                       ((reg32) & ~(clr_mask)) \
                                                       | (set_mask))


/*******************************************************************************
 * Function Name : ADDR32
 * Description   : Address of 32-bit location as WORD
 * Arguments     : obj        = object to obtain address for
 * Return Value  : address to 32-bit location as WORD
 ******************************************************************************/
#define ADDR32(obj)                         (uint32)((uint32 *)&(obj))


/*##############################################################################
 # global types
 #############################################################################*/

/*******************************************************************************
 * compact notation for native types (unsigned)
 * NOTE: this is exception to Renesas naming conventions
 ******************************************************************************/

#if defined (__CCRH__)
typedef unsigned char        uint8;
typedef unsigned short       uint16;
typedef unsigned long        uint32;
typedef unsigned long long   uint64;
#endif

#if defined (__ICCRH850__)
typedef unsigned char        uint8;
typedef unsigned short       uint16;
typedef unsigned long        uint32;
typedef unsigned long long   uint64;
#endif

/*******************************************************************************
 * compact notation for native types (signed)
 * NOTE: this is exception to Renesas naming conventions
 ******************************************************************************/
typedef signed char          sint8;
typedef signed short         sint16;
typedef signed long          sint32;


#endif /* R_TYPES_H */

