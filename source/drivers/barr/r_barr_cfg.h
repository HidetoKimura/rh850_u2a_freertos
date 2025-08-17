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
 * Copyright (C)2022 Renesas Electronics Corporation. All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * File Name   : r_barr_cfg.h
 * Device(s)   : U2A
 * Description : BARR configuration types
 ******************************************************************************/

#ifndef R_BARR_CFG_H
#define R_BARR_CFG_H


/*##############################################################################
 # Global types
 #############################################################################*/

/*******************************************************************************
 * supported channels
 ******************************************************************************/
typedef enum
{
    BARR_CH_0  = 0x0,
    BARR_CH_1  = 0x1,
    BARR_CH_2  = 0x2,
    BARR_CH_3  = 0x3,
    BARR_CH_4  = 0x4,
    BARR_CH_5  = 0x5,
    BARR_CH_6  = 0x6,
    BARR_CH_7  = 0x7,
    BARR_CH_8  = 0x8,
    BARR_CH_9  = 0x9,
    BARR_CH_10 = 0xa,
    BARR_CH_11 = 0xb,
    BARR_CH_12 = 0xc,
    BARR_CH_13 = 0xd,
    BARR_CH_14 = 0xe,
    BARR_CH_15 = 0xf
} barr_ch_t;

/*******************************************************************************
 * supported Processor Elements
 ******************************************************************************/
typedef enum
{
	BARR_ENA_NONE     = 0x00,
	BARR_ENA_PE0      = 0x01,
	BARR_ENA_PE1      = 0x02,
	BARR_ENA_PE2      = 0x04,
	BARR_ENA_PE3      = 0x08,
	BARR_ENA_ALL      = 0x0f
} barr_ena_t;

/*******************************************************************************
 * channel synchronization status. This enumeration corresponds to bit BRSYNC
 * of registers BRnSYNCS
 *
 * BRnSYNCS             Barrier Synchronization Completions Register (self)
 *
 *   BRSYNC[0]          Barrier synchronization completion
 *                      0 = pending
 *                      1 = complete
 ******************************************************************************/
typedef enum
{
    BARR_CH_STAT_PENDING    = 0x0,
    BARR_CH_STAT_COMPLETE   = 0x1
} barr_ch_stat_t;

/*******************************************************************************
 * a channel configuration
 ******************************************************************************/
typedef struct
{
    barr_ch_t    barr_ch;
    barr_ena_t   pe_ena;
} barr_cfg_ch_t;


#endif /* R_BARR_CFG_H */

