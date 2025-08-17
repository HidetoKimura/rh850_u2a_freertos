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
* File Name        : r_barr.h
* Component Version: 1.0.0
* Description      : Provide macros for BARR barrier synchronization. 
***********************************************************************************************************************/
#ifndef R_BARR_H

/***********************************************************************************************************************
Definitions
***********************************************************************************************************************/
#define BARR_PE_NONE 0
#define BARR_PE0 1
#define BARR_PE1 2
#define BARR_PE2 4
#define BARR_PE3 8
#define BARR_PE_ALL 15

/***********************************************************************************************************************
Macros
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: R_BARR_Init
* Description  : Initialize BARR barrier synchronization for corresponding channel. 
* Arguments    : channel - BARR channel
*                pe - PEs to synchronize  
* Return Value : None
***********************************************************************************************************************/
#define R_BARR_Init(channel, pe){\
    BARR.BR##channel##EN.UINT8 = 0x00;\
    BARR.BR##channel##EN.UINT8 = pe;\
    BARR.BR##channel##INIT.UINT8 = 0x01;}

/***********************************************************************************************************************
* Function Name: R_BARR_Sync
* Description  : Synchronize PEs using BARR barrier synchronization for corresponding channel.
* Arguments    : channel - BARR channel
* Return Value : None
***********************************************************************************************************************/
#define R_BARR_Sync(channel){\
    while(0 == BARR.BR##channel##EN.UINT8){}\
    BARR.BR##channel##CHKS.BIT.BRCHK = 0x01;\
    while(0 == BARR.BR##channel##SYNCS.BIT.BRSYNC){};}

#endif /* R_BARR_H */
