/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name         : 
* Component Version : 1.0.0
* Description       : 
***********************************************************************************************************************/
#ifndef R_GPIO_HELPER_H
#define R_GPIO_HELPER_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "inc\common.h"

/***********************************************************************************************************************
Macros
***********************************************************************************************************************/
#define setGpioHigh(PORT,PIN){\
  PORT0.PKCPROT = KCE_EN;\
  PORT0.PWE |= (1<<PORT)<<1;\
  PORT0.PSR##PORT.UINT32= (1<<PIN )|((1<<PIN)<<16);\
  PORT0.PWE &= ~((1<<PORT)<<1);\
  PORT0.PKCPROT = KCE_DIS; }

#define setGpioLow(PORT,PIN){\
  PORT0.PKCPROT = KCE_EN;\
  PORT0.PWE |= (1<<PORT)<<1;\
  PORT0.PSR##PORT.UINT32= ((1<<PIN)<<16);\
  PORT0.PWE &= ~((1<<PORT)<<1);\
  PORT0.PKCPROT = KCE_DIS; }

#define setPipc(PORT,PIN){\
  PORT0.PKCPROT = KCE_EN;\
  PORT0.PWE |= (1<<PORT)<<1;\
  PORT0.PIPC##PORT= PORT0.PIPC##PORT | (1<<PIN);\
  PORT0.PWE &= ~((1<<PORT)<<1);\
  PORT0.PKCPROT = KCE_DIS; }

#define readGpio(PORT,PIN) ( (PORT0.PPR##PORT.BIT.PPR##PORT##_##PIN) )

#endif /* R_GPIO_HELPER_H */
