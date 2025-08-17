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
*******************************************************************************/


/*******************************************************************************
* File Name   : r_barr_dev.h
* Device(s)   : U2A
* Description : BARR register and structure definitions
* Generated   : Thursday, 12 May 2022 10:35:18 Eastern Daylight Time
*******************************************************************************/

#ifndef R_BARR_DEV_U2A_H
#define R_BARR_DEV_U2A_H


/*##############################################################################
# Macros
##############################################################################*/


/*******************************************************************************
* Base Address
*******************************************************************************/
#define BARR_ADDR_BASE                  ((uint32)0xFFFB8000U)

/*******************************************************************************
* Number of Units
*******************************************************************************/
#define BARR_CNT_UNIT                   ((uint8)1U)

/*******************************************************************************
* Number of Channels
*******************************************************************************/
#define BARR_CNT_CH                     ((uint8)16U)

/*******************************************************************************
* Number of Processor Elements
*******************************************************************************/
#define BARR_CNT_PE                     ((uint8)4U)

/*******************************************************************************
* Register: BRnINIT (n=0..15)
*******************************************************************************/
#define BARR_MASK_BRINIT_BRINIT         ((uint8)0x01U)

/*******************************************************************************
* Register: BRnEN (n=0..15)
*******************************************************************************/
#define BARR_MASK_BREN_BREN             ((uint8)0x3FU)

/*******************************************************************************
* Register: BRnCHKS (n=0..15)
*******************************************************************************/
#define BARR_MASK_BRCHKS_BRCHK          ((uint8)0x01U)

/*******************************************************************************
* Register: BRnSYNCS (n=0..15)
*******************************************************************************/
#define BARR_MASK_BRSYNCS_BRSYNC        ((uint8)0x01U)

/*******************************************************************************
* Register: BRnCHKm (n=0..15, m=0..5)
*******************************************************************************/
#define BARR_MASK_BRCHK_BRCHK           ((uint8)0x01U)

/*******************************************************************************
* Register: BRnSYNCm (n=0..15, m=0..5)
*******************************************************************************/
#define BARR_MASK_BRSYNC_BRSYNC         ((uint8)0x01U)


/*##############################################################################
# Register Definitions
##############################################################################*/

/*******************************************************************************
* Register: BRnINIT, (n=0..15)
*******************************************************************************/
typedef union
{
    uint8_t BYTE;
    struct
    {
        uint8_t BRINIT          : 1;
        uint8_t reserved1       : 7;
    } BIT;
} barr_brinit_t;

/*******************************************************************************
* Register: BRnEN (n=0..15)
*******************************************************************************/
typedef union
{
    uint8_t BYTE;
    struct
    {
        uint8_t BREN            : 4;
        uint8_t reserved6       : 4;
    } BIT;
} barr_bren_t;

/*******************************************************************************
* Register: BRnCHKS (n=0..15)
*******************************************************************************/
typedef union
{
    uint8_t BYTE;
    struct
    {
        uint8_t BRCHK           : 1;
        uint8_t reserved1       : 7;
    } BIT;
} barr_brchks_t;

/*******************************************************************************
* Register: BRnSYNCS (n=0..15)
*******************************************************************************/
typedef union
{
    uint8_t BYTE;
    struct
    {
        uint8_t BRSYNC          : 1;
        uint8_t reserved1       : 7;
    } BIT;
} barr_brsyncs_t;

/*******************************************************************************
* Register: BRnCHKm (n=0..15, m=0..5)
*******************************************************************************/
typedef union
{
    uint8_t BYTE;
    struct
    {
        uint8_t BRCHK           : 1;
        uint8_t reserved1       : 7;
    } BIT;
} barr_brchk_t;

/*******************************************************************************
* Register: BRnSYNCm (n=0..15, m=0..5)
*******************************************************************************/
typedef union
{
    uint8_t BYTE;
    struct
    {
        uint8_t BRSYNC          : 1;
        uint8_t reserved1       : 7;
    } BIT;
} barr_brsync_t;


/*##############################################################################
# Module Structures
##############################################################################*/

/*******************************************************************************
* BARR channel initialization/enable structure
*******************************************************************************/
typedef struct
{
	barr_brinit_t             INIT;                     /* 0x00 */
    uint8_t                     reserved0001;            	/* 0x01 */
    uint16                    reserved0002;            	/* 0x02 */
    barr_bren_t               EN;                   	/* 0x04 */
    uint8_t                     reserved0005;            	/* 0x05 */
    uint16                    reserved0006;            	/* 0x06 */
    uint32                    reserved0008[2];         	/* 0x08 */
} barr_ch_init_ena_t;

/*******************************************************************************
* BARR synchronization/check structure self single channel
*******************************************************************************/
typedef struct
{
    barr_brchks_t             CHKS;                 	/* 0x00 */
    uint8_t                     reserved0001;            	/* 0x01 */
    uint16                    reserved0002;            	/* 0x02 */
    barr_brsyncs_t            SYNCS;                	/* 0x04 */
    uint8_t                     reserved0005;            	/* 0x05 */
    uint16                    reserved0006;            	/* 0x06 */
    uint32                    reserved0008[2];         	/* 0x08 */
} barr_ch_sync_self_t;

/*******************************************************************************
* BARR synchronization/check structure single channel single PE
*******************************************************************************/
typedef struct
{
    barr_brchks_t             CHK;                   	/* 0x00 */
    uint8_t                     reserved0001;            	/* 0x01 */
    uint16                    reserved0002;            	/* 0x02 */
    barr_brsyncs_t            SYNC;                 	/* 0x04 */
    uint8_t                     reserved0005;            	/* 0x05 */
    uint16                    reserved0006;            	/* 0x06 */
    uint32                    reserved0008[2];         	/* 0x08 */
} barr_ch_sync_pe_t;

/*******************************************************************************
* BARR synchronization/check structure single PE
*******************************************************************************/
typedef struct
{
	barr_ch_sync_pe_t         BR[BARR_CNT_CH];
} barr_sync_pe_t;

/*******************************************************************************
* Module: BARR
*******************************************************************************/
typedef struct
{
	barr_ch_init_ena_t        BR[BARR_CNT_CH];          /* 0xfffb8000 */
	barr_ch_sync_self_t       SELF[BARR_CNT_CH];        /* 0xfffb8100 */
	uint32                    reserved8200[384];       	/* 0xfffb8200 */
	barr_sync_pe_t            PE[BARR_CNT_PE];          /* 0xfffb8800 */
} barr_t;


/*##############################################################################
# Instantiation
##############################################################################*/

/*******************************************************************************
* #define Instantiation Option
* Usage: BARR[0].REG.WORD = <value>
*
*******************************************************************************/
#define BARR ((volatile barr_t *) BARR_ADDR_BASE)

#endif   /* R_BARR_DEV_R7F702Z19_H */


