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
#include "inc\common.h"
#include "r_typedefs.h"
#include "r_at_ram_if.h"
/***********************************************************
  Section: Defines
*/


/***********************************************************
  Section: Variables
*/
static uint32_t locRamBaseAddr = 0;
static uint32_t locRamEndAddr = 0;

static uint32_t locRamCurrAddr = 0;
static uint32_t locRamNextFreeAddr = 0;


/***********************************************************
  Section: Functions
*/

/***********************************************************
  Function: R_ATF_Ram_Init
*/
void R_ATF_Ram_Init(uint32_t BaseAddr, uint32_t RamSize)
{
    uint32_t i;
    uint32_t* dataptr;
    dataptr=(uint32_t *) BaseAddr;
    for(i=0;i<RamSize/4;i++)
    {
      *dataptr=0;
      dataptr++;
    }

    locRamBaseAddr     = BaseAddr;
    locRamEndAddr      = BaseAddr + RamSize;
    locRamCurrAddr     = BaseAddr;
    locRamNextFreeAddr = BaseAddr;
}


/***********************************************************
  Function: R_ATF_Ram_Alloc
*/
uint32_t R_ATF_Ram_Alloc(uint32_t RamSize)
{

    /* 32-bit aligned address */
    locRamCurrAddr      = locRamNextFreeAddr;

    if (RamSize % 4 == 0)
    {
        locRamNextFreeAddr += RamSize;
    }
    else
    {
        locRamNextFreeAddr += (RamSize + (4 - RamSize%4));
    }

    if (locRamNextFreeAddr < locRamEndAddr)
    {
        return locRamCurrAddr;
    }
    else
    {
        locRamNextFreeAddr = locRamCurrAddr;
        return 0;
    }
}


/***********************************************************
  Function: R_ATF_Ram_NextFreeAddrGet
*/
uint32_t R_ATF_Ram_NextFreeAddrGet(void)
{
    return locRamNextFreeAddr;
}


/***********************************************************
  Function: R_ATF_Ram_FreeMemSizeGet
*/
uint32_t R_ATF_Ram_FreeMemSizeGet(void)
{
    uint32_t val;

    val = locRamEndAddr - locRamNextFreeAddr;
    return val;
}


/***********************************************************
  Function: R_ATF_Ram_BaseAddrGet
*/
uint32_t R_ATF_Ram_BaseAddrGet(void)
{
    return locRamBaseAddr;
}

