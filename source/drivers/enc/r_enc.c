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
* File Name        : r_enc.c
* Component Version: 1.0.0
* Description      : Provide encoder driver functions.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "inc\common.h"
#include "r_enc.h"

/***********************************************************************************************************************
Public functions
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: R_ENCA0_Init
* Description  : Initializes the ENCA encoder module Unit 0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ENCA0_Init(void)
{
    DNFA12.DNFAEN_TSG3	= 0xFF; /* Digital noise elimination enable register for TSG3 Group. (NFENL0 to NFENL7) */
    DNFA9.DNFAEN_ENCA = 0xF;    /* Digital noise elimination enable register for ENCA Group. (NFENL0 to NFEL3) */
    ENCA0.CTL.UINT16 = 0x02;    /* ENCA Control Register Up/down Count Selection. */
                                /* ENCAnUDS[1:0]: 10 */
                                /* At rising edge of ENCAnE0, down-count; */
                                /* At falling edge of ENCAnE0, up-count; */
                                /* However, count operation is performed only when ENCAnE1 = L. */
}

/***********************************************************************************************************************
* Function Name: R_ENCA0_Start
* Description  : Starts the ENCA0 operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ENCA0_Start(void)
{
   ENCA0.TS.UINT8 = 0x01; /* ENCA Timer Start Trigger Register. */
                   /* |----------------------------------------------------| */
                   /* | Bit Position | Bit Name | Function                 | */
                   /* |----------------------------------------------------| */
                   /* | 0            | ENCAnTS  | Timer Start Trigger      | */
                   /* |              |          | This is the trigger bit  | */
                   /* |              |          | that sets the ENCAn to   | */ 
                   /* |              |          | operation enabled state. | */
                   /* |              |          | 0: Writing is ignored.   | */
                   /* |              |          | 1: The ENCAn is set to   | */
                   /* |              |          |operation enabled state by| */ 
                   /* |              |          |setting ENCAnTE.ENCAnTE=1.| */
                   /* |----------------------------------------------------| */
}  

/***********************************************************************************************************************
* Function Name: R_ENCA0_Stop
* Description  : Stops the ENCA0 operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ENCA0_Stop(void)
{
   ENCA0.TT.UINT8 = 0x01; /* ENCA Timer Stop Trigger Register */
                   /* |----------------------------------------------------| */
                   /* | Bit Position | Bit Name | Function                 | */
                   /* |----------------------------------------------------| */
                   /* | 0            | ENCAnTT  | Timer Stop Trigger       | */
                   /* |              |          | This is the trigger bit  | */
                   /* |              |          | that sets the ENCAn to   | */ 
                   /* |              |          | operation stopped state. | */
                   /* |              |          | 0: Writing is ignored.   | */
                   /* |              |          | 1: Clears ENCAnTE.ENCAnTE| */
                   /* |              |          |to 0, to set the ENCAn to | */ 
                   /* |              |          |the count operation       | */
                   /* |              |          |stopped state             | */
                   /* |----------------------------------------------------| */
}

/***********************************************************************************************************************
* Function Name: R_ENCA0_Read
* Description  : Returns the value of the ENCA0 count register.
* Arguments    : None
* Return Value : uint16_t ENCA0CNT - ENCA Counter Register
***********************************************************************************************************************/
uint16_t R_ENCA0_Read(void)
{
    return ENCA0.CNT.UINT16;/* ENCA Counter Register */
    /* |--------------------------------------------------------------------|*/
    /* | Bit Position | Bit Name       | Function                           |*/
    /* |--------------------------------------------------------------------|*/
    /* | 15 to 0      | ENCAnCNT[15:0] | Counter Register                   |*/
    /* |              |                | ENCAnTE status: 0 (initial setting)|*/
    /* |              |                |        -> Count stop.              |*/ 
    /* |              |                | ENCAnTE status: 0 → 1              |*/
    /* |              |                | (operation start)                  |*/
    /* |              |                |        -> Count operation start.   |*/
    /* |              |                | ENCAnTE status: 1 (operating):     |*/ 
    /* |              |                |        ->Counting.                 |*/
    /* |              |                | ENCAnTE status: 1 → 0 (stopped):   |*/
    /* |              |                |        ->Count stop.               |*/
    /* |--------------------------------------------------------------------|*/
}

/***********************************************************************************************************************
* Function Name: R_ENCA0_GetFlags
* Description  : Returns the ENCA0 status flag.
* Arguments    : None
* Return Value : uint8_t ENCA0FLG - ENCA Status Flag Register
***********************************************************************************************************************/
uint8_t R_ENCA0_GetFlags(void)
{
    return ENCA0.FLG.UINT8;                            /* ENCA Status Flag Register */
    /* |--------------------------------------------------------------------|*/
    /* | Bit Position | Bit Name       | Function                           |*/
    /* |--------------------------------------------------------------------|*/
    /* |      2       | ENCAnCSF       |     Counter Status Flag            |*/
    /* |      1       | ENCAnUDFb      |     Underflow Flag                 |*/ 
    /* |      0       | ENCAnOVF       |     Overflow Flag                  |*/
    /* |--------------------------------------------------------------------|*/

}

/***********************************************************************************************************************
* Function Name: R_ENCA0_GetStatus
* Description  : Returns the ENCA0 status
* Arguments    : None
* Return Value : uint8_t ENCA0TE - ENCA Timer Enable Status Register
***********************************************************************************************************************/
uint8_t R_ENCA0_GetStatus(void)
{
    return ENCA0.TE.UINT8;/* ENCA Timer Enable Status Register */
    /* |--------------------------------------------------------------------|*/
    /* | Bit Position | Bit Name       | Function                           |*/
    /* |--------------------------------------------------------------------|*/
    /* |      0       | ENCAnTE        |     Timer Status Enable            |*/
    /* |              |                |     0: Operation stopped status    |*/
    /* |              |                |     1: Operation enabled status    |*/
    /* |--------------------------------------------------------------------|*/

}

/***********************************************************************************************************************
* Function Name: R_ENCA0_Write
* Description  : Write a count value to the ENCA Counter Register
* Arguments    : uint16_t cnt - Counter value
* Return Value : None
***********************************************************************************************************************/
void R_ENCA0_Write(uint16_t cnt)
{
    ENCA0.CNT.UINT16 = cnt;
}

