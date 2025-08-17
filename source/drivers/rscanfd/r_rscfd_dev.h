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
* Copyright (C)2023 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/


/*******************************************************************************
* File Name   : r_rscfd_dev.h
* Device(s)   : R7F702Z19
* Description : RSCFD register and structure definitions
* Generated   : Wednesday, 14 March 2018 19:45:10 Eastern Daylight Time
*******************************************************************************/

#ifndef R_RSCFD_DEV_R7F702Z19_H
#define R_RSCFD_DEV_R7F702Z19_H



/*##############################################################################
# Macros
##############################################################################*/

/*******************************************************************************
* Base Address
*******************************************************************************/
#define RSCFD_ADDR_BASE              ((uint32)0xffd00000U)
#define RSCFD_ADDR_UNIT0             ((uint32)0xfff50000U)
#define RSCFD_ADDR_UNIT1             ((uint32)0xffd00000U)

/*******************************************************************************
* Number of Units
*******************************************************************************/
#define RSCFD_CNT_UNIT               ((uint8)2U)

/*******************************************************************************
 * Number of Channels (per unit)
 *
 * CH         = number of channels
 * BUFFDATA   = Buffer data registers
 * BUFFTX     = transmit Buffer
 * BUFFRX     = receive Buffers
 * FIFO       = FIFO data registers
 * FIFORX     = receive FIFOs
 * FIFORRXTX  = transmit/receive FIFOs
 * MSGRX      = receive messages
 * MSGTX      = transmit message
 *******************************************************************************/
#define RSCFD_CNT_CH                    ((uint8)8U)
#define RSCFD_CNT_BUFFDATA              ((uint8)16U)
#define RSCFD_CNT_BUFFTX                ((uint16)512U)
#define RSCFD_CNT_BUFFRX                ((uint8)128U)
#define RSCFD_CNT_FIFODATA              ((uint8)16U)
#define RSCFD_CNT_FIFORX                ((uint8)8U)
#define RSCFD_CNT_FIFORXTX              ((uint8)24U)
#define RSCFD_CNT_MSGRX                 ((uint8)4U)
#define RSCFD_CNT_MSGTX                 ((uint8)16U)

/*******************************************************************************
* Register: CFDCnNCFG
*******************************************************************************/
#define RSCFD_MASK_CFDCNCFG_NBRP        ((uint32)0x000003ffU)
#define RSCFD_MASK_CFDCNCFG_NSJW        ((uint32)0x0000f800U)
#define RSCFD_MASK_CFDCNCFG_NTSEG1      ((uint32)0x007f0000U)
#define RSCFD_MASK_CFDCNCFG_NTSEG2      ((uint32)0x1f000000U)

/*******************************************************************************
* Register: CFDCnCTR
*******************************************************************************/
#define RSCFD_MASK_CFDCCTR_CHMDC        ((uint32)0x00000003U)
#define RSCFD_MASK_CFDCCTR_CSLPR        ((uint32)0x00000004U)
#define RSCFD_MASK_CFDCCTR_RTBO         ((uint32)0x00000008U)
#define RSCFD_MASK_CFDCCTR_BEIE         ((uint32)0x00000100U)
#define RSCFD_MASK_CFDCCTR_EWIE         ((uint32)0x00000200U)
#define RSCFD_MASK_CFDCCTR_EPIE         ((uint32)0x00000400U)
#define RSCFD_MASK_CFDCCTR_BOEIE        ((uint32)0x00000800U)
#define RSCFD_MASK_CFDCCTR_BORIE        ((uint32)0x00001000U)
#define RSCFD_MASK_CFDCCTR_OLIE         ((uint32)0x00002000U)
#define RSCFD_MASK_CFDCCTR_BLIE         ((uint32)0x00004000U)
#define RSCFD_MASK_CFDCCTR_ALIE         ((uint32)0x00008000U)
#define RSCFD_MASK_CFDCCTR_TAIE         ((uint32)0x00010000U)
#define RSCFD_MASK_CFDCCTR_EOCOIE       ((uint32)0x00020000U)
#define RSCFD_MASK_CFDCCTR_SOCOIE       ((uint32)0x00040000U)
#define RSCFD_MASK_CFDCCTR_TDCVFIE      ((uint32)0x00080000U)
#define RSCFD_MASK_CFDCCTR_BOM          ((uint32)0x00600000U)
#define RSCFD_MASK_CFDCCTR_ERRD         ((uint32)0x00800000U)
#define RSCFD_MASK_CFDCCTR_CTME         ((uint32)0x01000000U)
#define RSCFD_MASK_CFDCCTR_CTMS         ((uint32)0x06000000U)
#define RSCFD_MASK_CFDCCTR_CRCT         ((uint32)0x40000000U)
#define RSCFD_MASK_CFDCCTR_ROM          ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDCnSTS
*******************************************************************************/
#define RSCFD_MASK_CFDCSTS_CRSTSTS      ((uint32)0x00000001U)
#define RSCFD_MASK_CFDCSTS_CHLTSTS      ((uint32)0x00000002U)
#define RSCFD_MASK_CFDCSTS_CSLPSTS      ((uint32)0x00000004U)
#define RSCFD_MASK_CFDCSTS_EPSTS        ((uint32)0x00000008U)
#define RSCFD_MASK_CFDCSTS_BOSTS        ((uint32)0x00000010U)
#define RSCFD_MASK_CFDCSTS_TRMSTS       ((uint32)0x00000020U)
#define RSCFD_MASK_CFDCSTS_RECSTS       ((uint32)0x00000040U)
#define RSCFD_MASK_CFDCSTS_COMSTS       ((uint32)0x00000080U)
#define RSCFD_MASK_CFDCSTS_ESIF         ((uint32)0x00000100U)
#define RSCFD_MASK_CFDCSTS_REC          ((uint32)0x00ff0000U)
#define RSCFD_MASK_CFDCSTS_TEC          ((uint32)0xff000000U)

/*******************************************************************************
* Register: CFDCnERFL
*******************************************************************************/
#define RSCFD_MASK_CFDCERFL_BEF         ((uint32)0x00000001U)
#define RSCFD_MASK_CFDCERFL_EWF         ((uint32)0x00000002U)
#define RSCFD_MASK_CFDCERFL_EPF         ((uint32)0x00000004U)
#define RSCFD_MASK_CFDCERFL_BOEF        ((uint32)0x00000008U)
#define RSCFD_MASK_CFDCERFL_BORF        ((uint32)0x00000010U)
#define RSCFD_MASK_CFDCERFL_OVLF        ((uint32)0x00000020U)
#define RSCFD_MASK_CFDCERFL_BLF         ((uint32)0x00000040U)
#define RSCFD_MASK_CFDCERFL_ALF         ((uint32)0x00000080U)
#define RSCFD_MASK_CFDCERFL_SERR        ((uint32)0x00000100U)
#define RSCFD_MASK_CFDCERFL_FERR        ((uint32)0x00000200U)
#define RSCFD_MASK_CFDCERFL_AERR        ((uint32)0x00000400U)
#define RSCFD_MASK_CFDCERFL_CERR        ((uint32)0x00000800U)
#define RSCFD_MASK_CFDCERFL_B1ERR       ((uint32)0x00001000U)
#define RSCFD_MASK_CFDCERFL_B0ERR       ((uint32)0x00002000U)
#define RSCFD_MASK_CFDCERFL_ADERR       ((uint32)0x00004000U)
#define RSCFD_MASK_CFDCERFL_CRCREG      ((uint32)0x7fff0000U)
#define RSCFD_MASK_CFDCERFL_ERR         ((uint32)0xFFFF8000U)

/*******************************************************************************
* Register: CFDGCFG
*******************************************************************************/
#define RSCFD_MASK_CFDGCFG_TPRI         ((uint32)0x00000001U)
#define RSCFD_MASK_CFDGCFG_DCE          ((uint32)0x00000002U)
#define RSCFD_MASK_CFDGCFG_DRE          ((uint32)0x00000004U)
#define RSCFD_MASK_CFDGCFG_MME          ((uint32)0x00000008U)
#define RSCFD_MASK_CFDGCFG_DCS          ((uint32)0x00000010U)
#define RSCFD_MASK_CFDGCFG_CMPOC        ((uint32)0x00000020U)
#define RSCFD_MASK_CFDGCFG_TSP          ((uint32)0x00000f00U)
#define RSCFD_MASK_CFDGCFG_TSSS         ((uint32)0x00001000U)
#define RSCFD_MASK_CFDGCFG_TSBTCS       ((uint32)0x0000e000U)
#define RSCFD_MASK_CFDGCFG_ITRCP        ((uint32)0xffff0000U)

/*******************************************************************************
* Register: CFDGCTR
*******************************************************************************/
#define RSCFD_MASK_CFDGCTR_GMDC         ((uint32)0x00000003U)
#define RSCFD_MASK_CFDGCTR_GSLPR        ((uint32)0x00000004U)
#define RSCFD_MASK_CFDGCTR_DEIE         ((uint32)0x00000100U)
#define RSCFD_MASK_CFDGCTR_MEIE         ((uint32)0x00000200U)
#define RSCFD_MASK_CFDGCTR_THLEIE       ((uint32)0x00000400U)
#define RSCFD_MASK_CFDGCTR_CMPOFIE      ((uint32)0x00000800U)
#define RSCFD_MASK_CFDGCTR_TSRST        ((uint32)0x00010000U)

/*******************************************************************************
* Register: CFDGSTS
*******************************************************************************/
#define RSCFD_MASK_CFDGSTS_GRSTSTS      ((uint32)0x00000001U)
#define RSCFD_MASK_CFDGSTS_GHLTSTS      ((uint32)0x00000002U)
#define RSCFD_MASK_CFDGSTS_GSLPSTS      ((uint32)0x00000004U)
#define RSCFD_MASK_CFDGSTS_GRAMINIT     ((uint32)0x00000008U)

/*******************************************************************************
* Register: CFDGERFL
*******************************************************************************/
#define RSCFD_MASK_CFDGERFL_DEF         ((uint32)0x00000001U)
#define RSCFD_MASK_CFDGERFL_MES         ((uint32)0x00000002U)
#define RSCFD_MASK_CFDGERFL_THLES       ((uint32)0x00000004U)
#define RSCFD_MASK_CFDGERFL_CMPOF       ((uint32)0x00000008U)
#define RSCFD_MASK_CFDGERFL_EEF0        ((uint32)0x00010000U)
#define RSCFD_MASK_CFDGERFL_EEF1        ((uint32)0x00020000U)
#define RSCFD_MASK_CFDGERFL_EEF2        ((uint32)0x00040000U)
#define RSCFD_MASK_CFDGERFL_EEF3        ((uint32)0x00080000U)
#define RSCFD_MASK_CFDGERFL_EEF4        ((uint32)0x00100000U)
#define RSCFD_MASK_CFDGERFL_EEF5        ((uint32)0x00200000U)

/*******************************************************************************
* Register: CFDGTSC
*******************************************************************************/
#define RSCFD_MASK_CFDGTSC_TS           ((uint32)0x0000ffffU)

/*******************************************************************************
* Register: CFDGAFLECTR
*******************************************************************************/
#define RSCFD_MASK_CFDGAFLECTR_AFLPN    ((uint32)0x0000001fU)
#define RSCFD_MASK_CFDGAFLECTR_AFLDAE   ((uint32)0x00000100U)

/*******************************************************************************
* Register: CFDGAFLCFG
*******************************************************************************/
#define RSCFD_MASK_CFDGAFLCFG_RNC       ((uint16)0x000001ffU)

/*******************************************************************************
* Register: CFDRMNB
*******************************************************************************/
#define RSCFD_MASK_CFDRMNB_NRXMB        ((uint32)0x000000ffU)
#define RSCFD_MASK_CFDRMNB_RMPLS        ((uint32)0x00000700U)

/*******************************************************************************
* Register: CFDRMND
*******************************************************************************/
#define RSCFD_MASK_CFDRMND_RMNS0        ((uint32)0x00000001U)
#define RSCFD_MASK_CFDRMND_RMNS1        ((uint32)0x00000002U)
#define RSCFD_MASK_CFDRMND_RMNS2        ((uint32)0x00000004U)
#define RSCFD_MASK_CFDRMND_RMNS3        ((uint32)0x00000008U)
#define RSCFD_MASK_CFDRMND_RMNS4        ((uint32)0x00000010U)
#define RSCFD_MASK_CFDRMND_RMNS5        ((uint32)0x00000020U)
#define RSCFD_MASK_CFDRMND_RMNS6        ((uint32)0x00000040U)
#define RSCFD_MASK_CFDRMND_RMNS7        ((uint32)0x00000080U)
#define RSCFD_MASK_CFDRMND_RMNS8        ((uint32)0x00000100U)
#define RSCFD_MASK_CFDRMND_RMNS9        ((uint32)0x00000200U)
#define RSCFD_MASK_CFDRMND_RMNS10       ((uint32)0x00000400U)
#define RSCFD_MASK_CFDRMND_RMNS11       ((uint32)0x00000800U)
#define RSCFD_MASK_CFDRMND_RMNS12       ((uint32)0x00001000U)
#define RSCFD_MASK_CFDRMND_RMNS13       ((uint32)0x00002000U)
#define RSCFD_MASK_CFDRMND_RMNS14       ((uint32)0x00004000U)
#define RSCFD_MASK_CFDRMND_RMNS15       ((uint32)0x00008000U)
#define RSCFD_MASK_CFDRMND_RMNS16       ((uint32)0x00010000U)
#define RSCFD_MASK_CFDRMND_RMNS17       ((uint32)0x00020000U)
#define RSCFD_MASK_CFDRMND_RMNS18       ((uint32)0x00040000U)
#define RSCFD_MASK_CFDRMND_RMNS19       ((uint32)0x00080000U)
#define RSCFD_MASK_CFDRMND_RMNS20       ((uint32)0x00100000U)
#define RSCFD_MASK_CFDRMND_RMNS21       ((uint32)0x00200000U)
#define RSCFD_MASK_CFDRMND_RMNS22       ((uint32)0x00400000U)
#define RSCFD_MASK_CFDRMND_RMNS23       ((uint32)0x00800000U)
#define RSCFD_MASK_CFDRMND_RMNS24       ((uint32)0x01000000U)
#define RSCFD_MASK_CFDRMND_RMNS25       ((uint32)0x02000000U)
#define RSCFD_MASK_CFDRMND_RMNS26       ((uint32)0x04000000U)
#define RSCFD_MASK_CFDRMND_RMNS27       ((uint32)0x08000000U)
#define RSCFD_MASK_CFDRMND_RMNS28       ((uint32)0x10000000U)
#define RSCFD_MASK_CFDRMND_RMNS29       ((uint32)0x20000000U)
#define RSCFD_MASK_CFDRMND_RMNS30       ((uint32)0x40000000U)
#define RSCFD_MASK_CFDRMND_RMNS31       ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDRFCC
*******************************************************************************/
#define RSCFD_MASK_CFDRFCC_RFE          ((uint32)0x00000001U)
#define RSCFD_MASK_CFDRFCC_RFIE         ((uint32)0x00000002U)
#define RSCFD_MASK_CFDRFCC_RFPLS        ((uint32)0x00000070U)
#define RSCFD_MASK_CFDRFCC_RFDC         ((uint32)0x00000700U)
#define RSCFD_MASK_CFDRFCC_RFIM         ((uint32)0x00001000U)
#define RSCFD_MASK_CFDRFCC_RFIGCV       ((uint32)0x0000e000U)

/*******************************************************************************
* Register: CFDRFSTS
*******************************************************************************/
#define RSCFD_MASK_CFDRFSTS_RFEMP       ((uint32)0x00000001U)
#define RSCFD_MASK_CFDRFSTS_RFFLL       ((uint32)0x00000002U)
#define RSCFD_MASK_CFDRFSTS_RFMLT       ((uint32)0x00000004U)
#define RSCFD_MASK_CFDRFSTS_RFIF        ((uint32)0x00000008U)
#define RSCFD_MASK_CFDRFSTS_RFFIF       ((uint32)0x00010000U)
#define RSCFD_MASK_CFDRFSTS_RFMC        ((uint32)0x0000ff00U)

/*******************************************************************************
* Register: CFDRFPCTR
*******************************************************************************/
#define RSCFD_MASK_CFDRFPCTR_RFPC       ((uint32)0x000000ffU)

/*******************************************************************************
* Register: CFDCFCC
*******************************************************************************/
#define RSCFD_MASK_CFDCFCC_CFE          ((uint32)0x00000001U)
#define RSCFD_MASK_CFDCFCC_CFRXIE       ((uint32)0x00000002U)
#define RSCFD_MASK_CFDCFCC_CFTXIE       ((uint32)0x00000004U)
#define RSCFD_MASK_CFDCFCC_CFPLS        ((uint32)0x00000070U)
#define RSCFD_MASK_CFDCFCC_CFM          ((uint32)0x00000300U)
#define RSCFD_MASK_CFDCFCC_CFITSS       ((uint32)0x00000400U)
#define RSCFD_MASK_CFDCFCC_CFITR        ((uint32)0x00000800U)
#define RSCFD_MASK_CFDCFCC_CFIM         ((uint32)0x00001000U)
#define RSCFD_MASK_CFDCFCC_CFIGCV       ((uint32)0x0000e000U)
#define RSCFD_MASK_CFDCFCC_CFTML        ((uint32)0x001f0000U)
#define RSCFD_MASK_CFDCFCC_CFDC         ((uint32)0x00e00000U)
#define RSCFD_MASK_CFDCFCC_CFITT        ((uint32)0xff000000U)

/*******************************************************************************
* Register: CFDCFCCE
*******************************************************************************/
#define RSCFD_MASK_CFDCFCCE_CFFIE       ((uint32)0x00000001U)
#define RSCFD_MASK_CFDCFCCE_CFOFRXIE    ((uint32)0x00000002U)
#define RSCFD_MASK_CFDCFCCE_CFOFTXIE    ((uint32)0x00000004U)
#define RSCFD_MASK_CFDCFCCE_CFMOWN      ((uint32)0x00000100U)
#define RSCFD_MASK_CFDCFCCE_CFBME       ((uint32)0x00010000U)

/*******************************************************************************
* Register: CFDCFSTS
*******************************************************************************/
#define RSCFD_MASK_CFDCFSTS_CFEMP       ((uint32)0x00000001U)
#define RSCFD_MASK_CFDCFSTS_CFFLL       ((uint32)0x00000002U)
#define RSCFD_MASK_CFDCFSTS_CFMLT       ((uint32)0x00000004U)
#define RSCFD_MASK_CFDCFSTS_CFRXIF      ((uint32)0x00000008U)
#define RSCFD_MASK_CFDCFSTS_CFTXIF      ((uint32)0x00000010U)
#define RSCFD_MASK_CFDCFSTS_CFMC        ((uint32)0x0000ff00U)
#define RSCFD_MASK_CFDCFSTS_CFFIF       ((uint32)0x00010000U)
#define RSCFD_MASK_CFDCFSTS_CFOFRXIF    ((uint32)0x00020000U)
#define RSCFD_MASK_CFDCFSTS_CFOFTXIF    ((uint32)0x00040000U)
#define RSCFD_MASK_CFDCFSTS_CFMOW       ((uint32)0x01000000U)

/*******************************************************************************
* Register: CFDCFPCTR
*******************************************************************************/
#define RSCFD_MASK_CFDCFPCTR_CFPC       ((uint32)0x000000ffU)

/*******************************************************************************
* Register: CFDFESTS
*******************************************************************************/
#define RSCFD_MASK_CFDFESTS_RF0EMP      ((uint32)0x00000001U)
#define RSCFD_MASK_CFDFESTS_RF1EMP      ((uint32)0x00000002U)
#define RSCFD_MASK_CFDFESTS_RF2EMP      ((uint32)0x00000004U)
#define RSCFD_MASK_CFDFESTS_RF3EMP      ((uint32)0x00000008U)
#define RSCFD_MASK_CFDFESTS_RF4EMP      ((uint32)0x00000010U)
#define RSCFD_MASK_CFDFESTS_RF5EMP      ((uint32)0x00000020U)
#define RSCFD_MASK_CFDFESTS_RF6EMP      ((uint32)0x00000040U)
#define RSCFD_MASK_CFDFESTS_RF7EMP      ((uint32)0x00000080U)
#define RSCFD_MASK_CFDFESTS_CF0EMP      ((uint32)0x00000100U)
#define RSCFD_MASK_CFDFESTS_CF1EMP      ((uint32)0x00000200U)
#define RSCFD_MASK_CFDFESTS_CF2EMP      ((uint32)0x00000400U)
#define RSCFD_MASK_CFDFESTS_CF3EMP      ((uint32)0x00000800U)
#define RSCFD_MASK_CFDFESTS_CF4EMP      ((uint32)0x00001000U)
#define RSCFD_MASK_CFDFESTS_CF5EMP      ((uint32)0x00002000U)
#define RSCFD_MASK_CFDFESTS_CF6EMP      ((uint32)0x00004000U)
#define RSCFD_MASK_CFDFESTS_CF7EMP      ((uint32)0x00008000U)
#define RSCFD_MASK_CFDFESTS_CF8EMP      ((uint32)0x00010000U)
#define RSCFD_MASK_CFDFESTS_CF9EMP      ((uint32)0x00020000U)
#define RSCFD_MASK_CFDFESTS_CF10EMP     ((uint32)0x00040000U)
#define RSCFD_MASK_CFDFESTS_CF11EMP     ((uint32)0x00080000U)
#define RSCFD_MASK_CFDFESTS_CF12EMP     ((uint32)0x00100000U)
#define RSCFD_MASK_CFDFESTS_CF13EMP     ((uint32)0x00200000U)
#define RSCFD_MASK_CFDFESTS_CF14EMP     ((uint32)0x00400000U)
#define RSCFD_MASK_CFDFESTS_CF15EMP     ((uint32)0x00800000U)
#define RSCFD_MASK_CFDFESTS_CF16EMP     ((uint32)0x01000000U)
#define RSCFD_MASK_CFDFESTS_CF17EMP     ((uint32)0x02000000U)
#define RSCFD_MASK_CFDFESTS_CF18EMP     ((uint32)0x04000000U)
#define RSCFD_MASK_CFDFESTS_CF19EMP     ((uint32)0x08000000U)
#define RSCFD_MASK_CFDFESTS_CF20EMP     ((uint32)0x10000000U)
#define RSCFD_MASK_CFDFESTS_CF21EMP     ((uint32)0x20000000U)
#define RSCFD_MASK_CFDFESTS_CF22EMP     ((uint32)0x40000000U)
#define RSCFD_MASK_CFDFESTS_CF23EMP     ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDFFSTS
*******************************************************************************/
#define RSCFD_MASK_CFDFFSTS_RF0FLL      ((uint32)0x00000001U)
#define RSCFD_MASK_CFDFFSTS_RF1FLL      ((uint32)0x00000002U)
#define RSCFD_MASK_CFDFFSTS_RF2FLL      ((uint32)0x00000004U)
#define RSCFD_MASK_CFDFFSTS_RF3FLL      ((uint32)0x00000008U)
#define RSCFD_MASK_CFDFFSTS_RF4FLL      ((uint32)0x00000010U)
#define RSCFD_MASK_CFDFFSTS_RF5FLL      ((uint32)0x00000020U)
#define RSCFD_MASK_CFDFFSTS_RF6FLL      ((uint32)0x00000040U)
#define RSCFD_MASK_CFDFFSTS_RF7FLL      ((uint32)0x00000080U)
#define RSCFD_MASK_CFDFFSTS_CF0FLL      ((uint32)0x00000100U)
#define RSCFD_MASK_CFDFFSTS_CF1FLL      ((uint32)0x00000200U)
#define RSCFD_MASK_CFDFFSTS_CF2FLL      ((uint32)0x00000400U)
#define RSCFD_MASK_CFDFFSTS_CF3FLL      ((uint32)0x00000800U)
#define RSCFD_MASK_CFDFFSTS_CF4FLL      ((uint32)0x00001000U)
#define RSCFD_MASK_CFDFFSTS_CF5FLL      ((uint32)0x00002000U)
#define RSCFD_MASK_CFDFFSTS_CF6FLL      ((uint32)0x00004000U)
#define RSCFD_MASK_CFDFFSTS_CF7FLL      ((uint32)0x00008000U)
#define RSCFD_MASK_CFDFFSTS_CF8FLL      ((uint32)0x00010000U)
#define RSCFD_MASK_CFDFFSTS_CF9FLL      ((uint32)0x00020000U)
#define RSCFD_MASK_CFDFFSTS_CF10FLL     ((uint32)0x00040000U)
#define RSCFD_MASK_CFDFFSTS_CF11FLL     ((uint32)0x00080000U)
#define RSCFD_MASK_CFDFFSTS_CF12FLL     ((uint32)0x00100000U)
#define RSCFD_MASK_CFDFFSTS_CF13FLL     ((uint32)0x00200000U)
#define RSCFD_MASK_CFDFFSTS_CF14FLL     ((uint32)0x00400000U)
#define RSCFD_MASK_CFDFFSTS_CF15FLL     ((uint32)0x00800000U)
#define RSCFD_MASK_CFDFFSTS_CF16FLL     ((uint32)0x01000000U)
#define RSCFD_MASK_CFDFFSTS_CF17FLL     ((uint32)0x02000000U)
#define RSCFD_MASK_CFDFFSTS_CF18FLL     ((uint32)0x04000000U)
#define RSCFD_MASK_CFDFFSTS_CF19FLL     ((uint32)0x08000000U)
#define RSCFD_MASK_CFDFFSTS_CF20FLL     ((uint32)0x10000000U)
#define RSCFD_MASK_CFDFFSTS_CF21FLL     ((uint32)0x20000000U)
#define RSCFD_MASK_CFDFFSTS_CF22FLL     ((uint32)0x40000000U)
#define RSCFD_MASK_CFDFFSTS_CF23FLL     ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDFMSTS
*******************************************************************************/
#define RSCFD_MASK_CFDFMSTS_RF0MLT      ((uint32)0x00000001U)
#define RSCFD_MASK_CFDFMSTS_RF1MLT      ((uint32)0x00000002U)
#define RSCFD_MASK_CFDFMSTS_RF2MLT      ((uint32)0x00000004U)
#define RSCFD_MASK_CFDFMSTS_RF3MLT      ((uint32)0x00000008U)
#define RSCFD_MASK_CFDFMSTS_RF4MLT      ((uint32)0x00000010U)
#define RSCFD_MASK_CFDFMSTS_RF5MLT      ((uint32)0x00000020U)
#define RSCFD_MASK_CFDFMSTS_RF6MLT      ((uint32)0x00000040U)
#define RSCFD_MASK_CFDFMSTS_RF7MLT      ((uint32)0x00000080U)
#define RSCFD_MASK_CFDFMSTS_CF0MLT      ((uint32)0x00000100U)
#define RSCFD_MASK_CFDFMSTS_CF1MLT      ((uint32)0x00000200U)
#define RSCFD_MASK_CFDFMSTS_CF2MLT      ((uint32)0x00000400U)
#define RSCFD_MASK_CFDFMSTS_CF3MLT      ((uint32)0x00000800U)
#define RSCFD_MASK_CFDFMSTS_CF4MLT      ((uint32)0x00001000U)
#define RSCFD_MASK_CFDFMSTS_CF5MLT      ((uint32)0x00002000U)
#define RSCFD_MASK_CFDFMSTS_CF6MLT      ((uint32)0x00004000U)
#define RSCFD_MASK_CFDFMSTS_CF7MLT      ((uint32)0x00008000U)
#define RSCFD_MASK_CFDFMSTS_CF8MLT      ((uint32)0x00010000U)
#define RSCFD_MASK_CFDFMSTS_CF9MLT      ((uint32)0x00020000U)
#define RSCFD_MASK_CFDFMSTS_CF10MLT     ((uint32)0x00040000U)
#define RSCFD_MASK_CFDFMSTS_CF11MLT     ((uint32)0x00080000U)
#define RSCFD_MASK_CFDFMSTS_CF12MLT     ((uint32)0x00100000U)
#define RSCFD_MASK_CFDFMSTS_CF13MLT     ((uint32)0x00200000U)
#define RSCFD_MASK_CFDFMSTS_CF14MLT     ((uint32)0x00400000U)
#define RSCFD_MASK_CFDFMSTS_CF15MLT     ((uint32)0x00800000U)
#define RSCFD_MASK_CFDFMSTS_CF16MLT     ((uint32)0x01000000U)
#define RSCFD_MASK_CFDFMSTS_CF17MLT     ((uint32)0x02000000U)
#define RSCFD_MASK_CFDFMSTS_CF18MLT     ((uint32)0x04000000U)
#define RSCFD_MASK_CFDFMSTS_CF19MLT     ((uint32)0x08000000U)
#define RSCFD_MASK_CFDFMSTS_CF20MLT     ((uint32)0x10000000U)
#define RSCFD_MASK_CFDFMSTS_CF21MLT     ((uint32)0x20000000U)
#define RSCFD_MASK_CFDFMSTS_CF22MLT     ((uint32)0x40000000U)
#define RSCFD_MASK_CFDFMSTS_CF23MLT     ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDRFISTS
*******************************************************************************/
#define RSCFD_MASK_CFDRFISTS_RF0IF      ((uint32)0x00000001U)
#define RSCFD_MASK_CFDRFISTS_RF1IF      ((uint32)0x00000002U)
#define RSCFD_MASK_CFDRFISTS_RF2IF      ((uint32)0x00000004U)
#define RSCFD_MASK_CFDRFISTS_RF3IF      ((uint32)0x00000008U)
#define RSCFD_MASK_CFDRFISTS_RF4IF      ((uint32)0x00000010U)
#define RSCFD_MASK_CFDRFISTS_RF5IF      ((uint32)0x00000020U)
#define RSCFD_MASK_CFDRFISTS_RF6IF      ((uint32)0x00000040U)
#define RSCFD_MASK_CFDRFISTS_RF7IF      ((uint32)0x00000080U)
#define RSCFD_MASK_CFDRFISTS_RF0FFLL    ((uint32)0x00010000U)
#define RSCFD_MASK_CFDRFISTS_RF1FFLL    ((uint32)0x00020000U)
#define RSCFD_MASK_CFDRFISTS_RF2FFLL    ((uint32)0x00040000U)
#define RSCFD_MASK_CFDRFISTS_RF3FFLL    ((uint32)0x00080000U)
#define RSCFD_MASK_CFDRFISTS_RF4FFLL    ((uint32)0x00100000U)
#define RSCFD_MASK_CFDRFISTS_RF5FFLL    ((uint32)0x00200000U)
#define RSCFD_MASK_CFDRFISTS_RF6FFLL    ((uint32)0x00400000U)
#define RSCFD_MASK_CFDRFISTS_RF7FFLL    ((uint32)0x00800000U)

/*******************************************************************************
* Register: CFDCFRISTS
*******************************************************************************/
#define RSCFD_MASK_CFDCFRISTS_CF0RXIF   ((uint32)0x00000001U)
#define RSCFD_MASK_CFDCFRISTS_CF1RXIF   ((uint32)0x00000002U)
#define RSCFD_MASK_CFDCFRISTS_CF2RXIF   ((uint32)0x00000004U)
#define RSCFD_MASK_CFDCFRISTS_CF3RXIF   ((uint32)0x00000008U)
#define RSCFD_MASK_CFDCFRISTS_CF4RXIF   ((uint32)0x00000010U)
#define RSCFD_MASK_CFDCFRISTS_CF5RXIF   ((uint32)0x00000020U)
#define RSCFD_MASK_CFDCFRISTS_CF6RXIF   ((uint32)0x00000040U)
#define RSCFD_MASK_CFDCFRISTS_CF7RXIF   ((uint32)0x00000080U)
#define RSCFD_MASK_CFDCFRISTS_CF8RXIF   ((uint32)0x00000100U)
#define RSCFD_MASK_CFDCFRISTS_CF9RXIF   ((uint32)0x00000200U)
#define RSCFD_MASK_CFDCFRISTS_CF10RXIF  ((uint32)0x00000400U)
#define RSCFD_MASK_CFDCFRISTS_CF11RXIF  ((uint32)0x00000800U)
#define RSCFD_MASK_CFDCFRISTS_CF12RXIF  ((uint32)0x00001000U)
#define RSCFD_MASK_CFDCFRISTS_CF13RXIF  ((uint32)0x00002000U)
#define RSCFD_MASK_CFDCFRISTS_CF14RXIF  ((uint32)0x00004000U)
#define RSCFD_MASK_CFDCFRISTS_CF15RXIF  ((uint32)0x00008000U)
#define RSCFD_MASK_CFDCFRISTS_CF16RXIF  ((uint32)0x00010000U)
#define RSCFD_MASK_CFDCFRISTS_CF17RXIF  ((uint32)0x00020000U)
#define RSCFD_MASK_CFDCFRISTS_CF18RXIF  ((uint32)0x00040000U)
#define RSCFD_MASK_CFDCFRISTS_CF19RXIF  ((uint32)0x00080000U)
#define RSCFD_MASK_CFDCFRISTS_CF20RXIF  ((uint32)0x00100000U)
#define RSCFD_MASK_CFDCFRISTS_CF21RXIF  ((uint32)0x00200000U)
#define RSCFD_MASK_CFDCFRISTS_CF22RXIF  ((uint32)0x00400000U)
#define RSCFD_MASK_CFDCFRISTS_CF23RXIF  ((uint32)0x00800000U)

/*******************************************************************************
* Register: CFDCFTISTS
*******************************************************************************/
#define RSCFD_MASK_CFDCFTISTS_CF0TXIF   ((uint32)0x00000001U)
#define RSCFD_MASK_CFDCFTISTS_CF1TXIF   ((uint32)0x00000002U)
#define RSCFD_MASK_CFDCFTISTS_CF2TXIF   ((uint32)0x00000004U)
#define RSCFD_MASK_CFDCFTISTS_CF3TXIF   ((uint32)0x00000008U)
#define RSCFD_MASK_CFDCFTISTS_CF4TXIF   ((uint32)0x00000010U)
#define RSCFD_MASK_CFDCFTISTS_CF5TXIF   ((uint32)0x00000020U)
#define RSCFD_MASK_CFDCFTISTS_CF6TXIF   ((uint32)0x00000040U)
#define RSCFD_MASK_CFDCFTISTS_CF7TXIF   ((uint32)0x00000080U)
#define RSCFD_MASK_CFDCFTISTS_CF8TXIF   ((uint32)0x00000100U)
#define RSCFD_MASK_CFDCFTISTS_CF9TXIF   ((uint32)0x00000200U)
#define RSCFD_MASK_CFDCFTISTS_CF10TXIF  ((uint32)0x00000400U)
#define RSCFD_MASK_CFDCFTISTS_CF11TXIF  ((uint32)0x00000800U)
#define RSCFD_MASK_CFDCFTISTS_CF12TXIF  ((uint32)0x00001000U)
#define RSCFD_MASK_CFDCFTISTS_CF13TXIF  ((uint32)0x00002000U)
#define RSCFD_MASK_CFDCFTISTS_CF14TXIF  ((uint32)0x00004000U)
#define RSCFD_MASK_CFDCFTISTS_CF15TXIF  ((uint32)0x00008000U)
#define RSCFD_MASK_CFDCFTISTS_CF16TXIF  ((uint32)0x00010000U)
#define RSCFD_MASK_CFDCFTISTS_CF17TXIF  ((uint32)0x00020000U)
#define RSCFD_MASK_CFDCFTISTS_CF18TXIF  ((uint32)0x00040000U)
#define RSCFD_MASK_CFDCFTISTS_CF19TXIF  ((uint32)0x00080000U)
#define RSCFD_MASK_CFDCFTISTS_CF20TXIF  ((uint32)0x00100000U)
#define RSCFD_MASK_CFDCFTISTS_CF21TXIF  ((uint32)0x00200000U)
#define RSCFD_MASK_CFDCFTISTS_CF22TXIF  ((uint32)0x00400000U)
#define RSCFD_MASK_CFDCFTISTS_CF23TXIF  ((uint32)0x00800000U)

/*******************************************************************************
* Register: CFDCFOFRISTS
*******************************************************************************/
#define RSCFD_MASK_CFDCFOFRISTS_CF0TX   ((uint32)0x00000001U)
#define RSCFD_MASK_CFDCFOFRISTS_CF1TX   ((uint32)0x00000002U)
#define RSCFD_MASK_CFDCFOFRISTS_CF2TX   ((uint32)0x00000004U)
#define RSCFD_MASK_CFDCFOFRISTS_CF3TX   ((uint32)0x00000008U)
#define RSCFD_MASK_CFDCFOFRISTS_CF4TX   ((uint32)0x00000010U)
#define RSCFD_MASK_CFDCFOFRISTS_CF5TX   ((uint32)0x00000020U)
#define RSCFD_MASK_CFDCFOFRISTS_CF6TX   ((uint32)0x00000040U)
#define RSCFD_MASK_CFDCFOFRISTS_CF7TX   ((uint32)0x00000080U)
#define RSCFD_MASK_CFDCFOFRISTS_CF8TX   ((uint32)0x00000100U)
#define RSCFD_MASK_CFDCFOFRISTS_CF9TX   ((uint32)0x00000200U)
#define RSCFD_MASK_CFDCFOFRISTS_CF10TX  ((uint32)0x00000400U)
#define RSCFD_MASK_CFDCFOFRISTS_CF11TX  ((uint32)0x00000800U)
#define RSCFD_MASK_CFDCFOFRISTS_CF12TX  ((uint32)0x00001000U)
#define RSCFD_MASK_CFDCFOFRISTS_CF13TX  ((uint32)0x00002000U)
#define RSCFD_MASK_CFDCFOFRISTS_CF14TX  ((uint32)0x00004000U)
#define RSCFD_MASK_CFDCFOFRISTS_CF15TX  ((uint32)0x00008000U)
#define RSCFD_MASK_CFDCFOFRISTS_CF16TX  ((uint32)0x00010000U)
#define RSCFD_MASK_CFDCFOFRISTS_CF17TX  ((uint32)0x00020000U)
#define RSCFD_MASK_CFDCFOFRISTS_CF18TX  ((uint32)0x00040000U)
#define RSCFD_MASK_CFDCFOFRISTS_CF19TX  ((uint32)0x00080000U)
#define RSCFD_MASK_CFDCFOFRISTS_CF20TX  ((uint32)0x00100000U)
#define RSCFD_MASK_CFDCFOFRISTS_CF21TX  ((uint32)0x00200000U)
#define RSCFD_MASK_CFDCFOFRISTS_CF22TX  ((uint32)0x00400000U)
#define RSCFD_MASK_CFDCFOFRISTS_CF23TX  ((uint32)0x00800000U)

/*******************************************************************************
* Register: CFDCFOFTISTS
*******************************************************************************/
#define RSCFD_MASK_CFDCFOFTISTS_CF0TXI  ((uint32)0x00000001U)
#define RSCFD_MASK_CFDCFOFTISTS_CF1TXI  ((uint32)0x00000002U)
#define RSCFD_MASK_CFDCFOFTISTS_CF2TXI  ((uint32)0x00000004U)
#define RSCFD_MASK_CFDCFOFTISTS_CF3TXI  ((uint32)0x00000008U)
#define RSCFD_MASK_CFDCFOFTISTS_CF4TXI  ((uint32)0x00000010U)
#define RSCFD_MASK_CFDCFOFTISTS_CF5TXI  ((uint32)0x00000020U)
#define RSCFD_MASK_CFDCFOFTISTS_CF6TXI  ((uint32)0x00000040U)
#define RSCFD_MASK_CFDCFOFTISTS_CF7TXI  ((uint32)0x00000080U)
#define RSCFD_MASK_CFDCFOFTISTS_CF8TXI  ((uint32)0x00000100U)
#define RSCFD_MASK_CFDCFOFTISTS_CF9TXI  ((uint32)0x00000200U)
#define RSCFD_MASK_CFDCFOFTISTS_CF10TXI ((uint32)0x00000400U)
#define RSCFD_MASK_CFDCFOFTISTS_CF11TXI ((uint32)0x00000800U)
#define RSCFD_MASK_CFDCFOFTISTS_CF12TXI ((uint32)0x00001000U)
#define RSCFD_MASK_CFDCFOFTISTS_CF13TXI ((uint32)0x00002000U)
#define RSCFD_MASK_CFDCFOFTISTS_CF14TXI ((uint32)0x00004000U)
#define RSCFD_MASK_CFDCFOFTISTS_CF15TXI ((uint32)0x00008000U)
#define RSCFD_MASK_CFDCFOFTISTS_CF16TXI ((uint32)0x00010000U)
#define RSCFD_MASK_CFDCFOFTISTS_CF17TXI ((uint32)0x00020000U)
#define RSCFD_MASK_CFDCFOFTISTS_CF18TXI ((uint32)0x00040000U)
#define RSCFD_MASK_CFDCFOFTISTS_CF19TXI ((uint32)0x00080000U)
#define RSCFD_MASK_CFDCFOFTISTS_CF20TXI ((uint32)0x00100000U)
#define RSCFD_MASK_CFDCFOFTISTS_CF21TXI ((uint32)0x00200000U)
#define RSCFD_MASK_CFDCFOFTISTS_CF22TXI ((uint32)0x00400000U)
#define RSCFD_MASK_CFDCFOFTISTS_CF23TXI ((uint32)0x00800000U)

/*******************************************************************************
* Register: CFDCFMOWSTS
*******************************************************************************/
#define RSCFD_MASK_CFDCFMOWSTS_CF0MOW   ((uint32)0x00000001U)
#define RSCFD_MASK_CFDCFMOWSTS_CF1MOW   ((uint32)0x00000002U)
#define RSCFD_MASK_CFDCFMOWSTS_CF2MOW   ((uint32)0x00000004U)
#define RSCFD_MASK_CFDCFMOWSTS_CF3MOW   ((uint32)0x00000008U)
#define RSCFD_MASK_CFDCFMOWSTS_CF4MOW   ((uint32)0x00000010U)
#define RSCFD_MASK_CFDCFMOWSTS_CF5MOW   ((uint32)0x00000020U)
#define RSCFD_MASK_CFDCFMOWSTS_CF6MOW   ((uint32)0x00000040U)
#define RSCFD_MASK_CFDCFMOWSTS_CF7MOW   ((uint32)0x00000080U)
#define RSCFD_MASK_CFDCFMOWSTS_CF8MOW   ((uint32)0x00000100U)
#define RSCFD_MASK_CFDCFMOWSTS_CF9MOW   ((uint32)0x00000200U)
#define RSCFD_MASK_CFDCFMOWSTS_CF10MOW  ((uint32)0x00000400U)
#define RSCFD_MASK_CFDCFMOWSTS_CF11MOW  ((uint32)0x00000800U)
#define RSCFD_MASK_CFDCFMOWSTS_CF12MOW  ((uint32)0x00001000U)
#define RSCFD_MASK_CFDCFMOWSTS_CF13MOW  ((uint32)0x00002000U)
#define RSCFD_MASK_CFDCFMOWSTS_CF14MOW  ((uint32)0x00004000U)
#define RSCFD_MASK_CFDCFMOWSTS_CF15MOW  ((uint32)0x00008000U)
#define RSCFD_MASK_CFDCFMOWSTS_CF16MOW  ((uint32)0x00010000U)
#define RSCFD_MASK_CFDCFMOWSTS_CF17MOW  ((uint32)0x00020000U)
#define RSCFD_MASK_CFDCFMOWSTS_CF18MOW  ((uint32)0x00040000U)
#define RSCFD_MASK_CFDCFMOWSTS_CF19MOW  ((uint32)0x00080000U)
#define RSCFD_MASK_CFDCFMOWSTS_CF20MOW  ((uint32)0x00100000U)
#define RSCFD_MASK_CFDCFMOWSTS_CF21MOW  ((uint32)0x00200000U)
#define RSCFD_MASK_CFDCFMOWSTS_CF22MOW  ((uint32)0x00400000U)
#define RSCFD_MASK_CFDCFMOWSTS_CF23MOW  ((uint32)0x00800000U)

/*******************************************************************************
* Register: CFDFFFSTS
*******************************************************************************/
#define RSCFD_MASK_CFDFFFSTS_RF0FFLL    ((uint32)0x00000001U)
#define RSCFD_MASK_CFDFFFSTS_RF1FFLL    ((uint32)0x00000002U)
#define RSCFD_MASK_CFDFFFSTS_RF2FFLL    ((uint32)0x00000004U)
#define RSCFD_MASK_CFDFFFSTS_RF3FFLL    ((uint32)0x00000008U)
#define RSCFD_MASK_CFDFFFSTS_RF4FFLL    ((uint32)0x00000010U)
#define RSCFD_MASK_CFDFFFSTS_RF5FFLL    ((uint32)0x00000020U)
#define RSCFD_MASK_CFDFFFSTS_RF6FFLL    ((uint32)0x00000040U)
#define RSCFD_MASK_CFDFFFSTS_RF7FFLL    ((uint32)0x00000080U)
#define RSCFD_MASK_CFDFFFSTS_CF0FFLL    ((uint32)0x00000100U)
#define RSCFD_MASK_CFDFFFSTS_CF1FFLL    ((uint32)0x00000200U)
#define RSCFD_MASK_CFDFFFSTS_CF2FFLL    ((uint32)0x00000400U)
#define RSCFD_MASK_CFDFFFSTS_CF3FFLL    ((uint32)0x00000800U)
#define RSCFD_MASK_CFDFFFSTS_CF4FFLL    ((uint32)0x00001000U)
#define RSCFD_MASK_CFDFFFSTS_CF5FFLL    ((uint32)0x00002000U)
#define RSCFD_MASK_CFDFFFSTS_CF6FFLL    ((uint32)0x00004000U)
#define RSCFD_MASK_CFDFFFSTS_CF7FFLL    ((uint32)0x00008000U)
#define RSCFD_MASK_CFDFFFSTS_CF8FFLL    ((uint32)0x00010000U)
#define RSCFD_MASK_CFDFFFSTS_CF9FFLL    ((uint32)0x00020000U)
#define RSCFD_MASK_CFDFFFSTS_CF10FFLL   ((uint32)0x00040000U)
#define RSCFD_MASK_CFDFFFSTS_CF11FFLL   ((uint32)0x00080000U)
#define RSCFD_MASK_CFDFFFSTS_CF12FFLL   ((uint32)0x00100000U)
#define RSCFD_MASK_CFDFFFSTS_CF13FFLL   ((uint32)0x00200000U)
#define RSCFD_MASK_CFDFFFSTS_CF14FFLL   ((uint32)0x00400000U)
#define RSCFD_MASK_CFDFFFSTS_CF15FFLL   ((uint32)0x00800000U)
#define RSCFD_MASK_CFDFFFSTS_CF16FFLL   ((uint32)0x01000000U)
#define RSCFD_MASK_CFDFFFSTS_CF17FFLL   ((uint32)0x02000000U)
#define RSCFD_MASK_CFDFFFSTS_CF18FFLL   ((uint32)0x04000000U)
#define RSCFD_MASK_CFDFFFSTS_CF19FFLL   ((uint32)0x08000000U)
#define RSCFD_MASK_CFDFFFSTS_CF20FFLL   ((uint32)0x10000000U)
#define RSCFD_MASK_CFDFFFSTS_CF21FFLL   ((uint32)0x20000000U)
#define RSCFD_MASK_CFDFFFSTS_CF22FFLL   ((uint32)0x40000000U)
#define RSCFD_MASK_CFDFFFSTS_CF23FFLL   ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDTMC
*******************************************************************************/
#define RSCFD_MASK_CFDTMC_TMTR          ((uint8)0x01U)
#define RSCFD_MASK_CFDTMC_TMTAR         ((uint8)0x02U)
#define RSCFD_MASK_CFDTMC_TMOM          ((uint8)0x04U)

/*******************************************************************************
* Register: CFDTMSTSn
*******************************************************************************/
#define RSCFD_MASK_CFDTMSTS_TMTSTS      ((uint8)0x01U)
#define RSCFD_MASK_CFDTMSTS_TMTRF       ((uint8)0x06U)
#define RSCFD_MASK_CFDTMSTS_TMTRM       ((uint8)0x08U)
#define RSCFD_MASK_CFDTMSTS_TMTARM      ((uint8)0x10U)


/*******************************************************************************
* Register: CFDTMTRSTS
*******************************************************************************/
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS0  ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS1  ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS2  ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS3  ((uint32)0x00000008U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS4  ((uint32)0x00000010U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS5  ((uint32)0x00000020U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS6  ((uint32)0x00000040U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS7  ((uint32)0x00000080U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS8  ((uint32)0x00000100U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS9  ((uint32)0x00000200U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS10 ((uint32)0x00000400U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS11 ((uint32)0x00000800U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS12 ((uint32)0x00001000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS13 ((uint32)0x00002000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS14 ((uint32)0x00004000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS15 ((uint32)0x00008000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS16 ((uint32)0x00010000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS17 ((uint32)0x00020000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS18 ((uint32)0x00040000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS19 ((uint32)0x00080000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS20 ((uint32)0x00100000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS21 ((uint32)0x00200000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS22 ((uint32)0x00400000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS23 ((uint32)0x00800000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS24 ((uint32)0x01000000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS25 ((uint32)0x02000000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS26 ((uint32)0x04000000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS27 ((uint32)0x08000000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS28 ((uint32)0x10000000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS29 ((uint32)0x20000000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS30 ((uint32)0x40000000U)
#define RSCFD_MASK_CFDTMTRSTS_TMTRSTS31 ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDTMTARSTS
*******************************************************************************/
#define RSCFD_MASK_CFDTMTARSTS_TARSTS0  ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS1  ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS2  ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS3  ((uint32)0x00000008U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS4  ((uint32)0x00000010U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS5  ((uint32)0x00000020U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS6  ((uint32)0x00000040U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS7  ((uint32)0x00000080U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS8  ((uint32)0x00000100U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS9  ((uint32)0x00000200U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS10 ((uint32)0x00000400U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS11 ((uint32)0x00000800U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS12 ((uint32)0x00001000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS13 ((uint32)0x00002000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS14 ((uint32)0x00004000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS15 ((uint32)0x00008000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS16 ((uint32)0x00010000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS17 ((uint32)0x00020000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS18 ((uint32)0x00040000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS19 ((uint32)0x00080000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS20 ((uint32)0x00100000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS21 ((uint32)0x00200000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS22 ((uint32)0x00400000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS23 ((uint32)0x00800000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS24 ((uint32)0x01000000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS25 ((uint32)0x02000000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS26 ((uint32)0x04000000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS27 ((uint32)0x08000000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS28 ((uint32)0x10000000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS29 ((uint32)0x20000000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS30 ((uint32)0x40000000U)
#define RSCFD_MASK_CFDTMTARSTS_TARSTS31 ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDTMTCSTS
*******************************************************************************/
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS0  ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS1  ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS2  ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS3  ((uint32)0x00000008U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS4  ((uint32)0x00000010U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS5  ((uint32)0x00000020U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS6  ((uint32)0x00000040U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS7  ((uint32)0x00000080U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS8  ((uint32)0x00000100U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS9  ((uint32)0x00000200U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS10 ((uint32)0x00000400U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS11 ((uint32)0x00000800U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS12 ((uint32)0x00001000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS13 ((uint32)0x00002000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS14 ((uint32)0x00004000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS15 ((uint32)0x00008000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS16 ((uint32)0x00010000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS17 ((uint32)0x00020000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS18 ((uint32)0x00040000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS19 ((uint32)0x00080000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS20 ((uint32)0x00100000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS21 ((uint32)0x00200000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS22 ((uint32)0x00400000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS23 ((uint32)0x00800000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS24 ((uint32)0x01000000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS25 ((uint32)0x02000000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS26 ((uint32)0x04000000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS27 ((uint32)0x08000000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS28 ((uint32)0x10000000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS29 ((uint32)0x20000000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS30 ((uint32)0x40000000U)
#define RSCFD_MASK_CFDTMTCSTS_TMTCSTS31 ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDTMTASTS
*******************************************************************************/
#define RSCFD_MASK_CFDTMTASTS_TMTASTS0  ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS1  ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS2  ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS3  ((uint32)0x00000008U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS4  ((uint32)0x00000010U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS5  ((uint32)0x00000020U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS6  ((uint32)0x00000040U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS7  ((uint32)0x00000080U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS8  ((uint32)0x00000100U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS9  ((uint32)0x00000200U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS10 ((uint32)0x00000400U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS11 ((uint32)0x00000800U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS12 ((uint32)0x00001000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS13 ((uint32)0x00002000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS14 ((uint32)0x00004000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS15 ((uint32)0x00008000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS16 ((uint32)0x00010000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS17 ((uint32)0x00020000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS18 ((uint32)0x00040000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS19 ((uint32)0x00080000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS20 ((uint32)0x00100000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS21 ((uint32)0x00200000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS22 ((uint32)0x00400000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS23 ((uint32)0x00800000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS24 ((uint32)0x01000000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS25 ((uint32)0x02000000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS26 ((uint32)0x04000000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS27 ((uint32)0x08000000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS28 ((uint32)0x10000000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS29 ((uint32)0x20000000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS30 ((uint32)0x40000000U)
#define RSCFD_MASK_CFDTMTASTS_TMTASTS31 ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDTMIEC
*******************************************************************************/
#define RSCFD_MASK_CFDTMIEC_TMIE0       ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTMIEC_TMIE1       ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTMIEC_TMIE2       ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTMIEC_TMIE3       ((uint32)0x00000008U)
#define RSCFD_MASK_CFDTMIEC_TMIE4       ((uint32)0x00000010U)
#define RSCFD_MASK_CFDTMIEC_TMIE5       ((uint32)0x00000020U)
#define RSCFD_MASK_CFDTMIEC_TMIE6       ((uint32)0x00000040U)
#define RSCFD_MASK_CFDTMIEC_TMIE7       ((uint32)0x00000080U)
#define RSCFD_MASK_CFDTMIEC_TMIE8       ((uint32)0x00000100U)
#define RSCFD_MASK_CFDTMIEC_TMIE9       ((uint32)0x00000200U)
#define RSCFD_MASK_CFDTMIEC_TMIE10      ((uint32)0x00000400U)
#define RSCFD_MASK_CFDTMIEC_TMIE11      ((uint32)0x00000800U)
#define RSCFD_MASK_CFDTMIEC_TMIE12      ((uint32)0x00001000U)
#define RSCFD_MASK_CFDTMIEC_TMIE13      ((uint32)0x00002000U)
#define RSCFD_MASK_CFDTMIEC_TMIE14      ((uint32)0x00004000U)
#define RSCFD_MASK_CFDTMIEC_TMIE15      ((uint32)0x00008000U)
#define RSCFD_MASK_CFDTMIEC_TMIE16      ((uint32)0x00010000U)
#define RSCFD_MASK_CFDTMIEC_TMIE17      ((uint32)0x00020000U)
#define RSCFD_MASK_CFDTMIEC_TMIE18      ((uint32)0x00040000U)
#define RSCFD_MASK_CFDTMIEC_TMIE19      ((uint32)0x00080000U)
#define RSCFD_MASK_CFDTMIEC_TMIE20      ((uint32)0x00100000U)
#define RSCFD_MASK_CFDTMIEC_TMIE21      ((uint32)0x00200000U)
#define RSCFD_MASK_CFDTMIEC_TMIE22      ((uint32)0x00400000U)
#define RSCFD_MASK_CFDTMIEC_TMIE23      ((uint32)0x00800000U)
#define RSCFD_MASK_CFDTMIEC_TMIE24      ((uint32)0x01000000U)
#define RSCFD_MASK_CFDTMIEC_TMIE25      ((uint32)0x02000000U)
#define RSCFD_MASK_CFDTMIEC_TMIE26      ((uint32)0x04000000U)
#define RSCFD_MASK_CFDTMIEC_TMIE27      ((uint32)0x08000000U)
#define RSCFD_MASK_CFDTMIEC_TMIE28      ((uint32)0x10000000U)
#define RSCFD_MASK_CFDTMIEC_TMIE29      ((uint32)0x20000000U)
#define RSCFD_MASK_CFDTMIEC_TMIE30      ((uint32)0x40000000U)
#define RSCFD_MASK_CFDTMIEC_TMIE31      ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDTXQCC
*******************************************************************************/
#define RSCFD_MASK_CFDTXQCC_TXQE        ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTXQCC_TXQDC       ((uint32)0x00000f00U)
#define RSCFD_MASK_CFDTXQCC_TXQIE       ((uint32)0x00001000U)
#define RSCFD_MASK_CFDTXQCC_TXQIM       ((uint32)0x00002000U)

/*******************************************************************************
* Register: CFDTXQSTS
*******************************************************************************/
#define RSCFD_MASK_CFDTXQSTS_TXQEMP     ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTXQSTS_TXQFLL     ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTXQSTS_TXQIF      ((uint32)0x00000004U)

/*******************************************************************************
* Register: CFDTXQPCTR
*******************************************************************************/
#define RSCFD_MASK_CFDTXQPCTR_TXQPC     ((uint32)0x000000ffU)

/*******************************************************************************
* Register: CFDTXQESTS
*******************************************************************************/
#define RSCFD_MASK_CFDTXQESTS_TXQ0EMP   ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTXQESTS_TXQ1EMP   ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTXQESTS_TXQ2EMP   ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTXQESTS_TXQ3EMP   ((uint32)0x00000008U)
#define RSCFD_MASK_CFDTXQESTS_TXQ4EMP   ((uint32)0x00000010U)
#define RSCFD_MASK_CFDTXQESTS_TXQ5EMP   ((uint32)0x00000020U)
#define RSCFD_MASK_CFDTXQESTS_TXQ6EMP   ((uint32)0x00000040U)
#define RSCFD_MASK_CFDTXQESTS_TXQ7EMP   ((uint32)0x00000080U)
#define RSCFD_MASK_CFDTXQESTS_TXQ8EMP   ((uint32)0x00000100U)
#define RSCFD_MASK_CFDTXQESTS_TXQ9EMP   ((uint32)0x00000200U)
#define RSCFD_MASK_CFDTXQESTS_TXQ10EMP  ((uint32)0x00000400U)
#define RSCFD_MASK_CFDTXQESTS_TXQ11EMP  ((uint32)0x00000800U)
#define RSCFD_MASK_CFDTXQESTS_TXQ12EMP  ((uint32)0x00001000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ13EMP  ((uint32)0x00002000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ14EMP  ((uint32)0x00004000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ15EMP  ((uint32)0x00008000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ16EMP  ((uint32)0x00010000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ17EMP  ((uint32)0x00020000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ18EMP  ((uint32)0x00040000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ19EMP  ((uint32)0x00080000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ20EMP  ((uint32)0x00100000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ21EMP  ((uint32)0x00200000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ22EMP  ((uint32)0x00400000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ23EMP  ((uint32)0x00800000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ24EMP  ((uint32)0x01000000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ25EMP  ((uint32)0x02000000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ26EMP  ((uint32)0x04000000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ27EMP  ((uint32)0x08000000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ28EMP  ((uint32)0x10000000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ29EMP  ((uint32)0x20000000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ30EMP  ((uint32)0x40000000U)
#define RSCFD_MASK_CFDTXQESTS_TXQ31EMP  ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDTXQFISTS
*******************************************************************************/
#define RSCFD_MASK_CFDTXQFISTS_Q0FULL   ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTXQFISTS_Q1FULL   ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTXQFISTS_Q2FULL   ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTXQFISTS_Q4FULL   ((uint32)0x00000010U)
#define RSCFD_MASK_CFDTXQFISTS_Q5FULL   ((uint32)0x00000020U)
#define RSCFD_MASK_CFDTXQFISTS_Q6FULL   ((uint32)0x00000040U)
#define RSCFD_MASK_CFDTXQFISTS_Q8FULL   ((uint32)0x00000100U)
#define RSCFD_MASK_CFDTXQFISTS_Q9FULL   ((uint32)0x00000200U)
#define RSCFD_MASK_CFDTXQFISTS_Q10FULL  ((uint32)0x00000400U)
#define RSCFD_MASK_CFDTXQFISTS_Q12FULL  ((uint32)0x00001000U)
#define RSCFD_MASK_CFDTXQFISTS_Q13FULL  ((uint32)0x00002000U)
#define RSCFD_MASK_CFDTXQFISTS_Q14FULL  ((uint32)0x00004000U)
#define RSCFD_MASK_CFDTXQFISTS_Q16FULL  ((uint32)0x00010000U)
#define RSCFD_MASK_CFDTXQFISTS_Q17FULL  ((uint32)0x00020000U)
#define RSCFD_MASK_CFDTXQFISTS_Q18FULL  ((uint32)0x00040000U)
#define RSCFD_MASK_CFDTXQFISTS_Q20FULL  ((uint32)0x00100000U)
#define RSCFD_MASK_CFDTXQFISTS_Q21FULL  ((uint32)0x00200000U)
#define RSCFD_MASK_CFDTXQFISTS_Q22FULL  ((uint32)0x00400000U)
#define RSCFD_MASK_CFDTXQFISTS_Q24FULL  ((uint32)0x01000000U)
#define RSCFD_MASK_CFDTXQFISTS_Q25FULL  ((uint32)0x02000000U)
#define RSCFD_MASK_CFDTXQFISTS_Q26FULL  ((uint32)0x04000000U)
#define RSCFD_MASK_CFDTXQFISTS_Q28FULL  ((uint32)0x10000000U)
#define RSCFD_MASK_CFDTXQFISTS_Q29FULL  ((uint32)0x20000000U)
#define RSCFD_MASK_CFDTXQFISTS_Q30FULL  ((uint32)0x40000000U)

/*******************************************************************************
* Register: CFDTXQMSTS
*******************************************************************************/
#define RSCFD_MASK_CFDTXQMSTS_TXQ0ML    ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ1ML    ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ2ML    ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ4ML    ((uint32)0x00000010U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ5ML    ((uint32)0x00000020U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ6ML    ((uint32)0x00000040U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ8ML    ((uint32)0x00000100U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ9ML    ((uint32)0x00000200U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ10ML   ((uint32)0x00000400U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ12ML   ((uint32)0x00001000U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ13ML   ((uint32)0x00002000U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ14ML   ((uint32)0x00004000U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ16ML   ((uint32)0x00010000U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ17ML   ((uint32)0x00020000U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ18ML   ((uint32)0x00040000U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ20ML   ((uint32)0x00100000U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ21ML   ((uint32)0x00200000U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ22ML   ((uint32)0x00400000U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ24ML   ((uint32)0x01000000U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ25ML   ((uint32)0x02000000U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ26ML   ((uint32)0x04000000U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ28ML   ((uint32)0x10000000U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ29ML   ((uint32)0x20000000U)
#define RSCFD_MASK_CFDTXQMSTS_TXQ30ML   ((uint32)0x40000000U)

/*******************************************************************************
* Register: CFDTXQOWSTS
*******************************************************************************/
#define RSCFD_MASK_CFDTXQOWSTS_TXQ0OW   ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ1OW   ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ2OW   ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ3OW   ((uint32)0x00000008U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ4OW   ((uint32)0x00000010U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ5OW   ((uint32)0x00000020U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ6OW   ((uint32)0x00000040U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ7OW   ((uint32)0x00000080U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ8OW   ((uint32)0x00000100U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ9OW   ((uint32)0x00000200U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ10OW  ((uint32)0x00000400U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ11OW  ((uint32)0x00000800U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ12OW  ((uint32)0x00001000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ13OW  ((uint32)0x00002000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ14OW  ((uint32)0x00004000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ15OW  ((uint32)0x00008000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ16OW  ((uint32)0x00010000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ17OW  ((uint32)0x00020000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ18OW  ((uint32)0x00040000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ19OW  ((uint32)0x00080000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ20OW  ((uint32)0x00100000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ21OW  ((uint32)0x00200000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ22OW  ((uint32)0x00400000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ23OW  ((uint32)0x00800000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ24OW  ((uint32)0x01000000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ25OW  ((uint32)0x02000000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ26OW  ((uint32)0x04000000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ27OW  ((uint32)0x08000000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ28OW  ((uint32)0x10000000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ29OW  ((uint32)0x20000000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ30OW  ((uint32)0x40000000U)
#define RSCFD_MASK_CFDTXQOWSTS_TXQ31OW  ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDTXQISTS
*******************************************************************************/
#define RSCFD_MASK_CFDTXQISTS_TXQ0ISF   ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTXQISTS_TXQ1ISF   ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTXQISTS_TXQ2ISF   ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTXQISTS_TXQ3ISF   ((uint32)0x00000008U)
#define RSCFD_MASK_CFDTXQISTS_TXQ4ISF   ((uint32)0x00000010U)
#define RSCFD_MASK_CFDTXQISTS_TXQ5ISF   ((uint32)0x00000020U)
#define RSCFD_MASK_CFDTXQISTS_TXQ6ISF   ((uint32)0x00000040U)
#define RSCFD_MASK_CFDTXQISTS_TXQ7ISF   ((uint32)0x00000080U)
#define RSCFD_MASK_CFDTXQISTS_TXQ8ISF   ((uint32)0x00000100U)
#define RSCFD_MASK_CFDTXQISTS_TXQ9ISF   ((uint32)0x00000200U)
#define RSCFD_MASK_CFDTXQISTS_TXQ10ISF  ((uint32)0x00000400U)
#define RSCFD_MASK_CFDTXQISTS_TXQ11ISF  ((uint32)0x00000800U)
#define RSCFD_MASK_CFDTXQISTS_TXQ12ISF  ((uint32)0x00001000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ13ISF  ((uint32)0x00002000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ14ISF  ((uint32)0x00004000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ15ISF  ((uint32)0x00008000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ16ISF  ((uint32)0x00010000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ17ISF  ((uint32)0x00020000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ18ISF  ((uint32)0x00040000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ19ISF  ((uint32)0x00080000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ20ISF  ((uint32)0x00100000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ21ISF  ((uint32)0x00200000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ22ISF  ((uint32)0x00400000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ23ISF  ((uint32)0x00800000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ24ISF  ((uint32)0x01000000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ25ISF  ((uint32)0x02000000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ26ISF  ((uint32)0x04000000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ27ISF  ((uint32)0x08000000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ28ISF  ((uint32)0x10000000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ29ISF  ((uint32)0x20000000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ30ISF  ((uint32)0x40000000U)
#define RSCFD_MASK_CFDTXQISTS_TXQ31ISF  ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDTXQOFTISTS
*******************************************************************************/
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ0O  ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ1O  ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ2O  ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ3O  ((uint32)0x00000008U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ4O  ((uint32)0x00000010U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ5O  ((uint32)0x00000020U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ6O  ((uint32)0x00000040U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ7O  ((uint32)0x00000080U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ8O  ((uint32)0x00000100U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ9O  ((uint32)0x00000200U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ10O ((uint32)0x00000400U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ11O ((uint32)0x00000800U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ12O ((uint32)0x00001000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ13O ((uint32)0x00002000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ14O ((uint32)0x00004000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ15O ((uint32)0x00008000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ16O ((uint32)0x00010000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ17O ((uint32)0x00020000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ18O ((uint32)0x00040000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ19O ((uint32)0x00080000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ20O ((uint32)0x00100000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ21O ((uint32)0x00200000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ22O ((uint32)0x00400000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ23O ((uint32)0x00800000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ24O ((uint32)0x01000000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ25O ((uint32)0x02000000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ26O ((uint32)0x04000000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ27O ((uint32)0x08000000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ28O ((uint32)0x10000000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ29O ((uint32)0x20000000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ30O ((uint32)0x40000000U)
#define RSCFD_MASK_CFDTXQOFTISTS_TXQ31O ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDTXQOFRISTS
*******************************************************************************/
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ0O  ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ1O  ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ2O  ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ4O  ((uint32)0x00000010U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ5O  ((uint32)0x00000020U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ6O  ((uint32)0x00000040U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ8O  ((uint32)0x00000100U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ9O  ((uint32)0x00000200U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ10O ((uint32)0x00000400U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ12O ((uint32)0x00001000U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ13O ((uint32)0x00002000U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ14O ((uint32)0x00004000U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ16O ((uint32)0x00010000U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ17O ((uint32)0x00020000U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ18O ((uint32)0x00040000U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ20O ((uint32)0x00100000U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ21O ((uint32)0x00200000U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ22O ((uint32)0x00400000U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ24O ((uint32)0x01000000U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ25O ((uint32)0x02000000U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ26O ((uint32)0x04000000U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ28O ((uint32)0x10000000U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ29O ((uint32)0x20000000U)
#define RSCFD_MASK_CFDTXQOFRISTS_TXQ30O ((uint32)0x40000000U)

/*******************************************************************************
* Register: CFDTXQFSTS
*******************************************************************************/
#define RSCFD_MASK_CFDTXQFSTS_TXQ0OO    ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ1OO    ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ2OO    ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ3OO    ((uint32)0x00000008U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ4OO    ((uint32)0x00000010U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ5OO    ((uint32)0x00000020U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ6OO    ((uint32)0x00000040U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ7OO    ((uint32)0x00000080U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ8OO    ((uint32)0x00000100U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ9OO    ((uint32)0x00000200U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ10OO   ((uint32)0x00000400U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ11OO   ((uint32)0x00000800U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ12OO   ((uint32)0x00001000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ13OO   ((uint32)0x00002000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ14OO   ((uint32)0x00004000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ15OO   ((uint32)0x00008000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ16OO   ((uint32)0x00010000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ17OO   ((uint32)0x00020000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ18OO   ((uint32)0x00040000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ19OO   ((uint32)0x00080000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ20OO   ((uint32)0x00100000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ21OO   ((uint32)0x00200000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ22OO   ((uint32)0x00400000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ23OO   ((uint32)0x00800000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ24OO   ((uint32)0x01000000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ25OO   ((uint32)0x02000000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ26OO   ((uint32)0x04000000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ27OO   ((uint32)0x08000000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ28OO   ((uint32)0x10000000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ29OO   ((uint32)0x20000000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ30OO   ((uint32)0x40000000U)
#define RSCFD_MASK_CFDTXQFSTS_TXQ31OO   ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDTHLCC
*******************************************************************************/
#define RSCFD_MASK_CFDTHLCC_THLE        ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTHLCC_THLIE       ((uint32)0x00000100U)
#define RSCFD_MASK_CFDTHLCC_THLIM       ((uint32)0x00000200U)
#define RSCFD_MASK_CFDTHLCC_THLDTE      ((uint32)0x00000400U)

/*******************************************************************************
* Register: CFDTHLSTS
*******************************************************************************/
#define RSCFD_MASK_CFDTHLSTS_THLEMP     ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTHLSTS_THLFLL     ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTHLSTS_THLELT     ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTHLSTS_THLIF      ((uint32)0x00000008U)
#define RSCFD_MASK_CFDTHLSTS_THLMC      ((uint32)0x00001f00U)

/*******************************************************************************
* Register: CFDTHLPCTR
*******************************************************************************/
#define RSCFD_MASK_CFDTHLPCTR_THLPC     ((uint32)0x000000ffU)

/*******************************************************************************
* Register: CFDGTINTSTS
*******************************************************************************/
#define RSCFD_MASK_CFDGTINTSTS_TSIF0    ((uint32)0x00000001U)
#define RSCFD_MASK_CFDGTINTSTS_TAIF0    ((uint32)0x00000002U)
#define RSCFD_MASK_CFDGTINTSTS_TQIF0    ((uint32)0x00000004U)
#define RSCFD_MASK_CFDGTINTSTS_CFTIF0   ((uint32)0x00000008U)
#define RSCFD_MASK_CFDGTINTSTS_THIF0    ((uint32)0x00000010U)
#define RSCFD_MASK_CFDGTINTSTS_TSIF1    ((uint32)0x00000100U)
#define RSCFD_MASK_CFDGTINTSTS_TAIF1    ((uint32)0x00000200U)
#define RSCFD_MASK_CFDGTINTSTS_TQIF1    ((uint32)0x00000400U)
#define RSCFD_MASK_CFDGTINTSTS_CFTIF1   ((uint32)0x00000800U)
#define RSCFD_MASK_CFDGTINTSTS_THIF1    ((uint32)0x00001000U)
#define RSCFD_MASK_CFDGTINTSTS_TSIF2    ((uint32)0x00010000U)
#define RSCFD_MASK_CFDGTINTSTS_TAIF2    ((uint32)0x00020000U)
#define RSCFD_MASK_CFDGTINTSTS_TQIF2    ((uint32)0x00040000U)
#define RSCFD_MASK_CFDGTINTSTS_CFTIF2   ((uint32)0x00080000U)
#define RSCFD_MASK_CFDGTINTSTS_THIF2    ((uint32)0x00100000U)
#define RSCFD_MASK_CFDGTINTSTS_TSIF3    ((uint32)0x01000000U)
#define RSCFD_MASK_CFDGTINTSTS_TAIF3    ((uint32)0x02000000U)
#define RSCFD_MASK_CFDGTINTSTS_TQIF3    ((uint32)0x04000000U)
#define RSCFD_MASK_CFDGTINTSTS_CFTIF3   ((uint32)0x08000000U)
#define RSCFD_MASK_CFDGTINTSTS_THIF3    ((uint32)0x10000000U)

/*******************************************************************************
* Register: CFDGTSTCFG
*******************************************************************************/
#define RSCFD_MASK_CFDGTSTCFG_C0ICBCE   ((uint32)0x00000001U)
#define RSCFD_MASK_CFDGTSTCFG_C1ICBCE   ((uint32)0x00000002U)
#define RSCFD_MASK_CFDGTSTCFG_C2ICBCE   ((uint32)0x00000004U)
#define RSCFD_MASK_CFDGTSTCFG_C3ICBCE   ((uint32)0x00000008U)
#define RSCFD_MASK_CFDGTSTCFG_C4ICBCE   ((uint32)0x00000010U)
#define RSCFD_MASK_CFDGTSTCFG_C5ICBCE   ((uint32)0x00000020U)
#define RSCFD_MASK_CFDGTSTCFG_RTMPS     ((uint32)0x007f0000U)

/*******************************************************************************
* Register: CFDGTSTCTR
*******************************************************************************/
#define RSCFD_MASK_CFDGTSTCTR_ICBCTME   ((uint32)0x00000001U)
#define RSCFD_MASK_CFDGTSTCTR_RTME      ((uint32)0x00000004U)

/*******************************************************************************
* Register: CFDGFDCFG
*******************************************************************************/
#define RSCFD_MASK_CFDGFDCFG_RPED       ((uint32)0x00000001U)
#define RSCFD_MASK_CFDGFDCFG_TSCCFG     ((uint32)0x00000300U)

/*******************************************************************************
* Register: CFDGLOCKK
*******************************************************************************/
#define RSCFD_MASK_CFDGLOCKK_LOCK       ((uint32)0x0000ffffU)

/*******************************************************************************
* Register: CFDCDTCT
*******************************************************************************/
#define RSCFD_MASK_CFDCDTCT_RFDMAE0     ((uint32)0x00000001U)
#define RSCFD_MASK_CFDCDTCT_RFDMAE1     ((uint32)0x00000002U)
#define RSCFD_MASK_CFDCDTCT_RFDMAE2     ((uint32)0x00000004U)
#define RSCFD_MASK_CFDCDTCT_RFDMAE3     ((uint32)0x00000008U)
#define RSCFD_MASK_CFDCDTCT_RFDMAE4     ((uint32)0x00000010U)
#define RSCFD_MASK_CFDCDTCT_RFDMAE5     ((uint32)0x00000020U)
#define RSCFD_MASK_CFDCDTCT_RFDMAE6     ((uint32)0x00000040U)
#define RSCFD_MASK_CFDCDTCT_RFDMAE7     ((uint32)0x00000080U)
#define RSCFD_MASK_CFDCDTCT_CFDMAE0     ((uint32)0x00000100U)
#define RSCFD_MASK_CFDCDTCT_CFDMAE1     ((uint32)0x00000200U)
#define RSCFD_MASK_CFDCDTCT_CFDMAE2     ((uint32)0x00000400U)
#define RSCFD_MASK_CFDCDTCT_CFDMAE3     ((uint32)0x00000800U)
#define RSCFD_MASK_CFDCDTCT_CFDMAE4     ((uint32)0x00001000U)
#define RSCFD_MASK_CFDCDTCT_CFDMAE5     ((uint32)0x00002000U)

/*******************************************************************************
* Register: CFDCDTSTS
*******************************************************************************/
#define RSCFD_MASK_CFDCDTSTS_RFDMASTS0  ((uint32)0x00000001U)
#define RSCFD_MASK_CFDCDTSTS_RFDMASTS1  ((uint32)0x00000002U)
#define RSCFD_MASK_CFDCDTSTS_RFDMASTS2  ((uint32)0x00000004U)
#define RSCFD_MASK_CFDCDTSTS_RFDMASTS3  ((uint32)0x00000008U)
#define RSCFD_MASK_CFDCDTSTS_RFDMASTS4  ((uint32)0x00000010U)
#define RSCFD_MASK_CFDCDTSTS_RFDMASTS5  ((uint32)0x00000020U)
#define RSCFD_MASK_CFDCDTSTS_RFDMASTS6  ((uint32)0x00000040U)
#define RSCFD_MASK_CFDCDTSTS_RFDMASTS7  ((uint32)0x00000080U)
#define RSCFD_MASK_CFDCDTSTS_CFDMASTS0  ((uint32)0x00000100U)
#define RSCFD_MASK_CFDCDTSTS_CFDMASTS1  ((uint32)0x00000200U)
#define RSCFD_MASK_CFDCDTSTS_CFDMASTS2  ((uint32)0x00000400U)
#define RSCFD_MASK_CFDCDTSTS_CFDMASTS3  ((uint32)0x00000800U)
#define RSCFD_MASK_CFDCDTSTS_CFDMASTS4  ((uint32)0x00001000U)
#define RSCFD_MASK_CFDCDTSTS_CFDMASTS5  ((uint32)0x00002000U)

/*******************************************************************************
* Register: CFDGRINTSTS
*******************************************************************************/
#define RSCFD_MASK_CFDGRINTSTS_QFIF     ((uint32)0x00000007U)
#define RSCFD_MASK_CFDGRINTSTS_BQFIF    ((uint32)0x00000030U)
#define RSCFD_MASK_CFDGRINTSTS_QOFRIF   ((uint32)0x00000700U)
#define RSCFD_MASK_CFDGRINTSTS_BQOFRIF  ((uint32)0x00003000U)
#define RSCFD_MASK_CFDGRINTSTS_CFRIF    ((uint32)0x00070000U)
#define RSCFD_MASK_CFDGRINTSTS_CFRFIF   ((uint32)0x07000000U)
#define RSCFD_MASK_CFDGRINTSTS_CFOFRIF  ((uint32)0x70000000U)

/*******************************************************************************
* Register: CFDGRSTC
*******************************************************************************/
#define RSCFD_MASK_CFDGRSTC_SRST        ((uint32)0x00000001U)
#define RSCFD_MASK_CFDGRSTC_KEY         ((uint32)0x0000ff00U)

/*******************************************************************************
* Register: CFDGFCMC
*******************************************************************************/
#define RSCFD_MASK_CFDGFCMC_FLXC0       ((uint32)0x00000001U)
#define RSCFD_MASK_CFDGFCMC_FLXC1       ((uint32)0x00000002U)
#define RSCFD_MASK_CFDGFCMC_FLXC2       ((uint32)0x00000004U)
#define RSCFD_MASK_CFDGFCMC_FLXC3       ((uint32)0x00000008U)

/*******************************************************************************
* Register: CFDGFTBAC
*******************************************************************************/
#define RSCFD_MASK_CFDGFTBAC_FLXMB0     ((uint32)0x0000000fU)
#define RSCFD_MASK_CFDGFTBAC_FLXMB1     ((uint32)0x00000f00U)
#define RSCFD_MASK_CFDGFTBAC_FLXMB2     ((uint32)0x000f0000U)
#define RSCFD_MASK_CFDGFTBAC_FLXMB3     ((uint32)0x0f000000U)

/*******************************************************************************
* Register: CFDCnDCFG
*******************************************************************************/
#define RSCFD_MASK_CFDCDCFG_DBRP        ((uint32)0x000000ffU)
#define RSCFD_MASK_CFDCDCFG_DTSEG1      ((uint32)0x00001f00U)
#define RSCFD_MASK_CFDCDCFG_DTSEG2      ((uint32)0x000f0000U)
#define RSCFD_MASK_CFDCDCFG_DSJW        ((uint32)0x0f000000U)

/*******************************************************************************
* Register: CFDCnFDCFG
*******************************************************************************/
#define RSCFD_MASK_CFDCFDCFG_EOCCFG     ((uint32)0x00000007U)
#define RSCFD_MASK_CFDCFDCFG_TDCOC      ((uint32)0x00000100U)
#define RSCFD_MASK_CFDCFDCFG_TDCE       ((uint32)0x00000200U)
#define RSCFD_MASK_CFDCFDCFG_ESIC       ((uint32)0x00000400U)
#define RSCFD_MASK_CFDCFDCFG_TDCO       ((uint32)0x00ff0000U)
#define RSCFD_MASK_CFDCFDCFG_GWEN       ((uint32)0x01000000U)
#define RSCFD_MASK_CFDCFDCFG_GWFDF      ((uint32)0x02000000U)
#define RSCFD_MASK_CFDCFDCFG_GWBRS      ((uint32)0x04000000U)
#define RSCFD_MASK_CFDCFDCFG_FDOE       ((uint32)0x10000000U)
#define RSCFD_MASK_CFDCFDCFG_REFE       ((uint32)0x20000000U)
#define RSCFD_MASK_CFDCFDCFG_CLOE       ((uint32)0x40000000U)

/*******************************************************************************
* Register: CFDCnFDCTR
*******************************************************************************/
#define RSCFD_MASK_CFDCFDCTR_EOCCLR     ((uint32)0x00000001U)
#define RSCFD_MASK_CFDCFDCTR_SOCCLR     ((uint32)0x00000002U)

/*******************************************************************************
* Register: CFDCnFDSTS
*******************************************************************************/
#define RSCFD_MASK_CFDCFDSTS_TDCR       ((uint32)0x000000ffU)
#define RSCFD_MASK_CFDCFDSTS_EOCO       ((uint32)0x00000100U)
#define RSCFD_MASK_CFDCFDSTS_SOCO       ((uint32)0x00000200U)
#define RSCFD_MASK_CFDCFDSTS_TDCVF      ((uint32)0x00008000U)
#define RSCFD_MASK_CFDCFDSTS_EOC        ((uint32)0x00ff0000U)
#define RSCFD_MASK_CFDCFDSTS_SOC        ((uint32)0xff000000U)

/*******************************************************************************
* Register: CFDCnFDCRC
*******************************************************************************/
#define RSCFD_MASK_CFDCFDCRC_CRCREG     ((uint32)0x001fffffU)
#define RSCFD_MASK_CFDCFDCRC_SCNT       ((uint32)0x0f000000U)

/*******************************************************************************
* Register: CFDCnBLCT
*******************************************************************************/
#define RSCFD_MASK_CFDC0BLCT_BLCE       ((uint32)0x00000001U)
#define RSCFD_MASK_CFDC0BLCT_BLCLD      ((uint32)0x00000100U)

/*******************************************************************************
* Register: CFDCnBLSTS
*******************************************************************************/
#define RSCFD_MASK_CFDC0BLSTS_BLC       ((uint32)0xfffffff8U)

/*******************************************************************************
* Register: CFDGAFLIDn
*******************************************************************************/
#define RSCFD_MASK_CFDGAFLID_GAFLID     ((uint32)0x1fffffffU)
#define RSCFD_MASK_CFDGAFLID_GAFLLB     ((uint32)0x20000000U)
#define RSCFD_MASK_CFDGAFLID_GAFLRTR    ((uint32)0x40000000U)
#define RSCFD_MASK_CFDGAFLID_GAFLIDE    ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDGAFLMn
*******************************************************************************/
#define RSCFD_MASK_CFDGAFLM_GAFLIDM     ((uint32)0x1fffffffU)
#define RSCFD_MASK_CFDGAFLM_GAFLIFL1    ((uint32)0x20000000U)
#define RSCFD_MASK_CFDGAFLM_GAFLRTRM    ((uint32)0x40000000U)
#define RSCFD_MASK_CFDGAFLM_GAFLIDEM    ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDGAFLP0n
*******************************************************************************/
#define RSCFD_MASK_CFDGAFLP0_GAFLDLC    ((uint32)0x0000000fU)
#define RSCFD_MASK_CFDGAFLP0_GAFLSRD0   ((uint32)0x00000010U)
#define RSCFD_MASK_CFDGAFLP0_GAFLSRD1   ((uint32)0x00000020U)
#define RSCFD_MASK_CFDGAFLP0_GAFLSRD2   ((uint32)0x00000040U)
#define RSCFD_MASK_CFDGAFLP0_GAFLIFL0   ((uint32)0x00000080U)
#define RSCFD_MASK_CFDGAFLP0_GAFLRMDP   ((uint32)0x00007f00U)
#define RSCFD_MASK_CFDGAFLP0_GAFLRMV    ((uint32)0x00008000U)
#define RSCFD_MASK_CFDGAFLP0_GAFLPTR    ((uint32)0xffff0000U)

/*******************************************************************************
* Register: CFDGAFLP1n
*******************************************************************************/
#define RSCFD_MASK_CFDGAFLP1_GAFLFDP    ((uint32)0xffffffffU)
#define RSCFD_MASK_CFDGAFLP1_RXFIFO     ((uint32)0x000000ffU)
#define RSCFD_MASK_CFDGAFLP1_COMMFIFO   ((uint32)0xffffff00U)

/*******************************************************************************
* Register: CFDRMIDn
*******************************************************************************/
#define RSCFD_MASK_CFDRMID_RMID         ((uint32)0x1fffffffU)
#define RSCFD_MASK_CFDRMID_RMRTR        ((uint32)0x40000000U)
#define RSCFD_MASK_CFDRMID_RMIDE        ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDRMPTRn
*******************************************************************************/
#define RSCFD_MASK_CFDRMPTR_RMTS        ((uint32)0x0000ffffU)
#define RSCFD_MASK_CFDRMPTR_RMDLC       ((uint32)0xf0000000U)

/*******************************************************************************
* Register: CFDRMFDSTSn
*******************************************************************************/
#define RSCFD_MASK_CFDRMFDSTS_RMESI     ((uint32)0x00000001U)
#define RSCFD_MASK_CFDRMFDSTS_RMBRS     ((uint32)0x00000002U)
#define RSCFD_MASK_CFDRMFDSTS_RMFDF     ((uint32)0x00000004U)
#define RSCFD_MASK_CFDRMFDSTS_RMIFL     ((uint32)0x00000300U)
#define RSCFD_MASK_CFDRMFDSTS_RMPTR     ((uint32)0xffff0000U)

/*******************************************************************************
* Register: CFDRMDFnq
*******************************************************************************/
#define RSCFD_MASK_CFDRMDF_RMDB0        ((uint32)0x000000ffU)
#define RSCFD_MASK_CFDRMDF_RMDB1        ((uint32)0x0000ff00U)
#define RSCFD_MASK_CFDRMDF_RMDB2        ((uint32)0x00ff0000U)
#define RSCFD_MASK_CFDRMDF_RMDB3        ((uint32)0xff000000U)

/*******************************************************************************
* Register: CFDRFIDn
*******************************************************************************/
#define RSCFD_MASK_CFDRFID_RFID         ((uint32)0x1fffffffU)
#define RSCFD_MASK_CFDRFID_RFRTR        ((uint32)0x40000000U)
#define RSCFD_MASK_CFDRFID_RFIDE        ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDRFPTRn
*******************************************************************************/
#define RSCFD_MASK_CFDRFPTR_RFTS        ((uint32)0x0000ffffU)
#define RSCFD_MASK_CFDRFPTR_RFDLC       ((uint32)0xf0000000U)

/*******************************************************************************
* Register: CFDRFFDSTSn
*******************************************************************************/
#define RSCFD_MASK_CFDRFFDSTS_RFESI     ((uint32)0x00000001U)
#define RSCFD_MASK_CFDRFFDSTS_RFBRS     ((uint32)0x00000002U)
#define RSCFD_MASK_CFDRFFDSTS_RFFDF     ((uint32)0x00000004U)
#define RSCFD_MASK_CFDRFFDSTS_RFIFL     ((uint32)0x00000300U)
#define RSCFD_MASK_CFDRFFDSTS_RFPTR     ((uint32)0xffff0000U)

/*******************************************************************************
* Register: CFDRFDFnx
*******************************************************************************/
#define RSCFD_MASK_CFDRFDF_RFDB0        ((uint32)0x000000ffU)
#define RSCFD_MASK_CFDRFDF_RFDB1        ((uint32)0x0000ff00U)
#define RSCFD_MASK_CFDRFDF_RFDB2        ((uint32)0x00ff0000U)
#define RSCFD_MASK_CFDRFDF_RFDB3        ((uint32)0xff000000U)

/*******************************************************************************
* Register: CFDCFIDn
*******************************************************************************/
#define RSCFD_MASK_CFDCFID_CFID         ((uint32)0x1fffffffU)
#define RSCFD_MASK_CFDCFID_THLEN        ((uint32)0x20000000U)
#define RSCFD_MASK_CFDCFID_CFRTR        ((uint32)0x40000000U)
#define RSCFD_MASK_CFDCFID_CFIDE        ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDCFPTRn
*******************************************************************************/
#define RSCFD_MASK_CFDCFPTR_CFTS        ((uint32)0x0000ffffU)
#define RSCFD_MASK_CFDCFPTR_CFDLC       ((uint32)0xf0000000U)

/*******************************************************************************
* Register: CFDCFFDCSTSn
*******************************************************************************/
#define RSCFD_MASK_CFDCFFDCSTS_CFESI    ((uint32)0x00000001U)
#define RSCFD_MASK_CFDCFFDCSTS_CFBRS    ((uint32)0x00000002U)
#define RSCFD_MASK_CFDCFFDCSTS_CFFDF    ((uint32)0x00000004U)
#define RSCFD_MASK_CFDCFFDCSTS_CFIFL    ((uint32)0x00000300U)
#define RSCFD_MASK_CFDCFFDCSTS_CFPTR    ((uint32)0xffff0000U)

/*******************************************************************************
* Register: CFDCFDFnk
*******************************************************************************/
#define RSCFD_MASK_CFDCFDF_CFDB0        ((uint32)0x000000ffU)
#define RSCFD_MASK_CFDCFDF_CFDB1        ((uint32)0x0000ff00U)
#define RSCFD_MASK_CFDCFDF_CFDB2        ((uint32)0x00ff0000U)
#define RSCFD_MASK_CFDCFDF_CFDB3        ((uint32)0xff000000U)

/*******************************************************************************
* Register: CFDTMIDn
*******************************************************************************/
#define RSCFD_MASK_CFDTMID_TMID         ((uint32)0x1fffffffU)
#define RSCFD_MASK_CFDTMID_TMLEN        ((uint32)0x20000000U)
#define RSCFD_MASK_CFDTMID_TMRTR        ((uint32)0x40000000U)
#define RSCFD_MASK_CFDTMID_TMIDE        ((uint32)0x80000000U)

/*******************************************************************************
* Register: CFDTMPTRn
*******************************************************************************/
#define RSCFD_MASK_CFDTMPTR_TMPTR       ((uint32)0x00ff0000U)
#define RSCFD_MASK_CFDTMPTR_TMDLC       ((uint32)0xf0000000U)

/*******************************************************************************
* Register: CFDTMFDCTRn
*******************************************************************************/
#define RSCFD_MASK_CFDTMFDCTR_TMESI     ((uint32)0x00000001U)
#define RSCFD_MASK_CFDTMFDCTR_TMBRS     ((uint32)0x00000002U)
#define RSCFD_MASK_CFDTMFDCTR_TMFDF     ((uint32)0x00000004U)
#define RSCFD_MASK_CFDTMFDCTR_TMIFL     ((uint32)0x00000300U)
#define RSCFD_MASK_CFDTMFDCTR_TMPTR     ((uint32)0xffff0000U)

/*******************************************************************************
* Register: CFDTMDFnp
*******************************************************************************/
#define RSCFD_MASK_CFDTMDF_TMDB0        ((uint32)0x000000ffU)
#define RSCFD_MASK_CFDTMDF_TMDB1        ((uint32)0x0000ff00U)
#define RSCFD_MASK_CFDTMDF_TMDB2        ((uint32)0x00ff0000U)
#define RSCFD_MASK_CFDTMDF_TMDB3        ((uint32)0xff000000U)

/*******************************************************************************
* Register: CFDTHLACC0
*******************************************************************************/
#define RSCFD_MASK_CFDTHLACC0_BT        ((uint32)0x00000007U)
#define RSCFD_MASK_CFDTHLACC0_BN        ((uint32)0x000003F8U)
#define RSCFD_MASK_CFDTHLACC0_TGW       ((uint32)0x00008000U)
#define RSCFD_MASK_CFDTHLACC0_TMTS      ((uint32)0xffff0000U)

/*******************************************************************************
* Register: CFDTHLACC1
*******************************************************************************/
#define RSCFD_MASK_CFDTHLACC1_TID       ((uint32)0x0000ffffU)
#define RSCFD_MASK_CFDTHLACC1_TIFL      ((uint32)0x00030000U)

/*******************************************************************************
* Register: CFDRPGACC
*******************************************************************************/
#define RSCFD_MASK_CFDRPGACC_RDTA       ((uint32)0xffffffffU)


/*##############################################################################
 # Register Definitions
 ##############################################################################*/

/*******************************************************************************
* Register: CFDCnNCFG
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 NBRP   : 10;
        uint32 NSJW   : 7;
        uint32 NTSEG1 : 8;
        uint32 NTSEG2 : 7;
    } BIT;
} rscfd_cfdcncfg_t;

/*******************************************************************************
* Register: CFDCnCTR
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 CHMDC            : 2;
        uint32 CSLPR            : 1;
        uint32 RTBO             : 1;
        const uint32 reserved4  : 4;
        uint32 BEIE             : 1;
        uint32 EWIE             : 1;
        uint32 EPIE             : 1;
        uint32 BOEIE            : 1;
        uint32 BORIE            : 1;
        uint32 OLIE             : 1;
        uint32 BLIE             : 1;
        uint32 ALIE             : 1;
        uint32 TAIE             : 1;
        uint32 EOCOIE           : 1;
        uint32 SOCOIE           : 1;
        uint32 TDCVFIE          : 1;
        const uint32 reserved20 : 1;
        uint32 BOM              : 2;
        uint32 ERRD             : 1;
        uint32 CTME             : 1;
        uint32 CTMS             : 2;
        const uint32 reserved27 : 3;
        uint32 CRCT             : 1;
        uint32 ROM              : 1;
    } BIT;
} rscfd_cfdcctr_t;

/*******************************************************************************
* Register: CFDCnSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        uint8       BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 CRSTSTS   : 1;
        const uint32 CHLTSTS   : 1;
        const uint32 CSLPSTS   : 1;
        const uint32 EPSTS     : 1;
        const uint32 BOSTS     : 1;
        const uint32 TRMSTS    : 1;
        const uint32 RECSTS    : 1;
        const uint32 COMSTS    : 1;
        const uint32 ESIF      : 1;
        const uint32 reserved9 : 7;
        const uint32 REC       : 8;
        const uint32 TEC       : 8;
    } BIT;
} rscfd_cfdcsts_t;

/*******************************************************************************
* Register: CFDCnERFL
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        uint8       BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 BEF              : 1;
        uint32 EWF              : 1;
        uint32 EPF              : 1;
        uint32 BOEF             : 1;
        uint32 BORF             : 1;
        uint32 OVLF             : 1;
        uint32 BLF              : 1;
        uint32 ALF              : 1;
        uint32 SERR             : 1;
        uint32 FERR             : 1;
        uint32 AERR             : 1;
        uint32 CERR             : 1;
        uint32 B1ERR            : 1;
        uint32 B0ERR            : 1;
        uint32 ADERR            : 1;
        const uint32 reserved15 : 1;
        uint32 CRCREG           : 15;
        const uint32 reserved31 : 1;
    } BIT;
} rscfd_cfdcerfl_t;

/*******************************************************************************
* Register: CFDGIPV
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        uint8       BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 IPV              : 8;
        uint32 IPT              : 2;
        const uint32 reserved10 : 22;
    } BIT;
} rscfd_cfdgipv_t;

/*******************************************************************************
* Register: CFDGCFG
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 TPRI            : 1;
        uint32 DCE             : 1;
        uint32 DRE             : 1;
        uint32 MME             : 1;
        uint32 DCS             : 1;
        uint32 CMPOC           : 1;
        const uint32 reserved6 : 2;
        uint32 TSP             : 4;
        uint32 TSSS            : 1;
        uint32 TSBTCS          : 3;
        uint32 ITRCP           : 16;
    } BIT;
} rscfd_cfdgcfg_t;

/*******************************************************************************
* Register: CFDGCTR
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        uint8       BYTE1;
        uint8       BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 GMDC             : 2;
        uint32 GSLPR            : 1;
        const uint32 reserved3  : 5;
        uint32 DEIE             : 1;
        uint32 MEIE             : 1;
        uint32 THLEIE           : 1;
        uint32 CMPOFIE          : 1;
        uint32 QOWEIE           : 1;
        const uint32 reserved13 : 1;
        uint32 QMEIE            : 1;
        uint32 MOWEIE           : 1;
        uint32 TSRST            : 1;
        const uint32 reserved17 : 15;
    } BIT;
} rscfd_cfdgctr_t;

/*******************************************************************************
* Register: CFDGSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 GRSTSTS   : 1;
        const uint32 GHLTSTS   : 1;
        const uint32 GSLPSTS   : 1;
        const uint32 GRAMINIT  : 1;
        const uint32 reserved4 : 28;
    } BIT;
} rscfd_cfdgsts_t;

/*******************************************************************************
* Register: CFDGERFL
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        uint8       BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 DEF             : 1;
        uint32 MES             : 1;
        uint32 THLES           : 1;
        uint32 CMPOF           : 1;
        uint32 QOWES           : 1;
        const uint32 reserved5 : 1;
        uint32 WMES            : 1;
        uint32 MOWES           : 1;
        const uint32 reserved8 : 8;
        uint32 EEF0            : 1;
        uint32 EEF1            : 1;
        uint32 EEF2            : 1;
        uint32 EEF3            : 1;
        uint32 EEF4            : 1;
        uint32 EEF5            : 1;
        uint32 EEF6            : 1;
        uint32 EEF7            : 1;
        const uint32 reserved4 : 8;
    } BIT;
} rscfd_cfdgerfl_t;

/*******************************************************************************
* Register: CFDGTSC
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint32 TS         : 16;
        const uint32 reserved16 : 16;
    } BIT;
} rscfd_cfdgtsc_t;

/*******************************************************************************
* Register: CFDGAFLECTR
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        uint8       BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 AFLPN           : 7;
        const uint32 reserved7 : 1;
        uint32 AFLDAE          : 1;
        const uint32 reserved9 : 23;
    } BIT;
} rscfd_cfdgaflectr_t;

/*******************************************************************************
* Register: CFDGAFLCFG (access x16 to simplify software)
*******************************************************************************/
typedef union
{
    uint16 HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
    } BYTE;
    struct
    {
        uint16 RNC             : 9;
        const uint16 reserved9 : 7;
    } BIT;
} rscfd_cfdgaflcfg_t;

/*******************************************************************************
* Register: CFDRMNB
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        uint8       BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 NRXMB            : 8;
        uint32 RMPLS            : 3;
        const uint32 reserved11 : 21;
    } BIT;
} rscfd_cfdrmnb_t;

/*******************************************************************************
* Register: CFDRMND
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 RMNS0  : 1;
        uint32 RMNS1  : 1;
        uint32 RMNS2  : 1;
        uint32 RMNS3  : 1;
        uint32 RMNS4  : 1;
        uint32 RMNS5  : 1;
        uint32 RMNS6  : 1;
        uint32 RMNS7  : 1;
        uint32 RMNS8  : 1;
        uint32 RMNS9  : 1;
        uint32 RMNS10 : 1;
        uint32 RMNS11 : 1;
        uint32 RMNS12 : 1;
        uint32 RMNS13 : 1;
        uint32 RMNS14 : 1;
        uint32 RMNS15 : 1;
        uint32 RMNS16 : 1;
        uint32 RMNS17 : 1;
        uint32 RMNS18 : 1;
        uint32 RMNS19 : 1;
        uint32 RMNS20 : 1;
        uint32 RMNS21 : 1;
        uint32 RMNS22 : 1;
        uint32 RMNS23 : 1;
        uint32 RMNS24 : 1;
        uint32 RMNS25 : 1;
        uint32 RMNS26 : 1;
        uint32 RMNS27 : 1;
        uint32 RMNS28 : 1;
        uint32 RMNS29 : 1;
        uint32 RMNS30 : 1;
        uint32 RMNS31 : 1;
    } BIT;
} rscfd_cfdrmnd_t;

/*******************************************************************************
* Register: CFDRFCC
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        uint8       BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 RFE              : 1;
        uint32 RFIE             : 1;
        const uint32 reserved2  : 2;
        uint32 RFPLS            : 3;
        const uint32 reserved7  : 1;
        uint32 RFDC             : 3;
        const uint32 reserved11 : 1;
        uint32 RFIM             : 1;
        uint32 RFIGCV           : 3;
        uint32 RFFIE            : 1;
        const uint32 reserved17 : 15;
    } BIT;
} rscfd_cfdrfcc_t;

/*******************************************************************************
* Register: CFDRFSTS
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 RFEMP            : 1;
        uint32 RFFLL            : 1;
        uint32 RFMLT            : 1;
        uint32 RFIF             : 1;
        const uint32 reserved4  : 4;
        uint32 RFMC             : 8;
        uint32 RFFIF            : 1;
        const uint32 reserved17 : 15;
    } BIT;
} rscfd_cfdrfsts_t;

/*******************************************************************************
* Register: CFDRFPCTR
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 RFPC            : 8;
        const uint32 reserved8 : 24;
    } BIT;
} rscfd_cfdrfpctr_t;

/*******************************************************************************
* Register: CFDCFCC
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 CFE             : 1;
        uint32 CFRXIE          : 1;
        uint32 CFTXIE          : 1;
        const uint32 reserved3 : 1;
        uint32 CFPLS           : 3;
        const uint32 reserved7 : 1;
        uint32 CFM             : 2;
        uint32 CFITSS          : 1;
        uint32 CFITR           : 1;
        uint32 CFIM            : 1;
        uint32 CFIGCV          : 3;
        uint32 CFTML           : 5;
        uint32 CFDC            : 3;
        uint32 CFITT           : 8;
    } BIT;
} rscfd_cfdcfcc_t;

/*******************************************************************************
* Register: CFDCFCCE
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 CFFIE            : 1;
        uint32 CFORXIE          : 1;
        uint32 CFOTXIE          : 1;
        const uint32 reserved3  : 5;
        uint32 CFMOWN           : 1;
        const uint32 reserved9  : 7;
        uint32 CFBME            : 1;
        const uint32 reserved17 : 15;
    } BIT;
} rscfd_cfdcfcce_t;

/*******************************************************************************
* Register: CFDCFSTS
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 CFEMP            : 1;
        uint32 CFFLL            : 1;
        uint32 CFMLT            : 1;
        uint32 CFRXIF           : 1;
        uint32 CFTXIF           : 1;
        const uint32 reserved5  : 3;
        uint32 CFMC             : 8;
        uint32 CFFIF            : 1;
        uint32 CFOFRXIF         : 1;
        uint32 CFOFTXIF         : 1;
        const uint32 reserved19 : 5;
        uint32 CFMOW            : 1;
        const uint32 reserved25 : 7;
    } BIT;
} rscfd_cfdcfsts_t;

/*******************************************************************************
* Register: CFDCFPCTR
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 CFPC            : 8;
        const uint32 reserved8 : 24;
    } BIT;
} rscfd_cfdcfpctr_t;

/*******************************************************************************
* Register: CFDFESTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 RF0EMP  : 1;
        const uint32 RF1EMP  : 1;
        const uint32 RF2EMP  : 1;
        const uint32 RF3EMP  : 1;
        const uint32 RF4EMP  : 1;
        const uint32 RF5EMP  : 1;
        const uint32 RF6EMP  : 1;
        const uint32 RF7EMP  : 1;
        const uint32 CF0EMP  : 1;
        const uint32 CF1EMP  : 1;
        const uint32 CF2EMP  : 1;
        const uint32 CF3EMP  : 1;
        const uint32 CF4EMP  : 1;
        const uint32 CF5EMP  : 1;
        const uint32 CF6EMP  : 1;
        const uint32 CF7EMP  : 1;
        const uint32 CF8EMP  : 1;
        const uint32 CF9EMP  : 1;
        const uint32 CF10EMP : 1;
        const uint32 CF11EMP : 1;
        const uint32 CF12EMP : 1;
        const uint32 CF13EMP : 1;
        const uint32 CF14EMP : 1;
        const uint32 CF15EMP : 1;
        const uint32 CF16EMP : 1;
        const uint32 CF17EMP : 1;
        const uint32 CF18EMP : 1;
        const uint32 CF19EMP : 1;
        const uint32 CF20EMP : 1;
        const uint32 CF21EMP : 1;
        const uint32 CF22EMP : 1;
        const uint32 CF23EMP : 1;
    } BIT;
} rscfd_cfdfests_t;

/*******************************************************************************
* Register: CFDFFSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 RF0FLL  : 1;
        const uint32 RF1FLL  : 1;
        const uint32 RF2FLL  : 1;
        const uint32 RF3FLL  : 1;
        const uint32 RF4FLL  : 1;
        const uint32 RF5FLL  : 1;
        const uint32 RF6FLL  : 1;
        const uint32 RF7FLL  : 1;
        const uint32 CF0FLL  : 1;
        const uint32 CF1FLL  : 1;
        const uint32 CF2FLL  : 1;
        const uint32 CF3FLL  : 1;
        const uint32 CF4FLL  : 1;
        const uint32 CF5FLL  : 1;
        const uint32 CF6FLL  : 1;
        const uint32 CF7FLL  : 1;
        const uint32 CF8FLL  : 1;
        const uint32 CF9FLL  : 1;
        const uint32 CF10FLL : 1;
        const uint32 CF11FLL : 1;
        const uint32 CF12FLL : 1;
        const uint32 CF13FLL : 1;
        const uint32 CF14FLL : 1;
        const uint32 CF15FLL : 1;
        const uint32 CF16FLL : 1;
        const uint32 CF17FLL : 1;
        const uint32 CF18FLL : 1;
        const uint32 CF19FLL : 1;
        const uint32 CF20FLL : 1;
        const uint32 CF21FLL : 1;
        const uint32 CF22FLL : 1;
        const uint32 CF23FLL : 1;
    } BIT;
} rscfd_cfdffsts_t;

/*******************************************************************************
* Register: CFDFMSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 RF0MLT  : 1;
        const uint32 RF1MLT  : 1;
        const uint32 RF2MLT  : 1;
        const uint32 RF3MLT  : 1;
        const uint32 RF4MLT  : 1;
        const uint32 RF5MLT  : 1;
        const uint32 RF6MLT  : 1;
        const uint32 RF7MLT  : 1;
        const uint32 CF0MLT  : 1;
        const uint32 CF1MLT  : 1;
        const uint32 CF2MLT  : 1;
        const uint32 CF3MLT  : 1;
        const uint32 CF4MLT  : 1;
        const uint32 CF5MLT  : 1;
        const uint32 CF6MLT  : 1;
        const uint32 CF7MLT  : 1;
        const uint32 CF8MLT  : 1;
        const uint32 CF9MLT  : 1;
        const uint32 CF10MLT : 1;
        const uint32 CF11MLT : 1;
        const uint32 CF12MLT : 1;
        const uint32 CF13MLT : 1;
        const uint32 CF14MLT : 1;
        const uint32 CF15MLT : 1;
        const uint32 CF16MLT : 1;
        const uint32 CF17MLT : 1;
        const uint32 CF18MLT : 1;
        const uint32 CF19MLT : 1;
        const uint32 CF20MLT : 1;
        const uint32 CF21MLT : 1;
        const uint32 CF22MLT : 1;
        const uint32 CF23MLT : 1;
    } BIT;
} rscfd_cfdfmsts_t;

/*******************************************************************************
* Register: CFDRFISTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 RF0IF      : 1;
        const uint32 RF1IF      : 1;
        const uint32 RF2IF      : 1;
        const uint32 RF3IF      : 1;
        const uint32 RF4IF      : 1;
        const uint32 RF5IF      : 1;
        const uint32 RF6IF      : 1;
        const uint32 RF7IF      : 1;
        const uint32 reserved8  : 8;
        const uint32 RF0FFLL    : 1;
        const uint32 RF1FFLL    : 1;
        const uint32 RF2FFLL    : 1;
        const uint32 RF3FFLL    : 1;
        const uint32 RF4FFLL    : 1;
        const uint32 RF5FFLL    : 1;
        const uint32 RF6FFLL    : 1;
        const uint32 RF7FFLL    : 1;
        const uint32 reserved24 : 8;
    } BIT;
} rscfd_cfdrfists_t;

/*******************************************************************************
* Register: CFDCFRISTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 CF0RXIF    : 1;
        const uint32 CF1RXIF    : 1;
        const uint32 CF2RXIF    : 1;
        const uint32 CF3RXIF    : 1;
        const uint32 CF4RXIF    : 1;
        const uint32 CF5RXIF    : 1;
        const uint32 CF6RXIF    : 1;
        const uint32 CF7RXIF    : 1;
        const uint32 CF8RXIF    : 1;
        const uint32 CF9RXIF    : 1;
        const uint32 CF10RXIF   : 1;
        const uint32 CF11RXIF   : 1;
        const uint32 CF12RXIF   : 1;
        const uint32 CF13RXIF   : 1;
        const uint32 CF14RXIF   : 1;
        const uint32 CF15RXIF   : 1;
        const uint32 CF16RXIF   : 1;
        const uint32 CF17RXIF   : 1;
        const uint32 CF18RXIF   : 1;
        const uint32 CF19RXIF   : 1;
        const uint32 CF20RXIF   : 1;
        const uint32 CF21RXIF   : 1;
        const uint32 CF22RXIF   : 1;
        const uint32 CF23RXIF   : 1;
        const uint32 reserved24 : 8;
    } BIT;
} rscfd_cfdcfrists_t;

/*******************************************************************************
* Register: CFDCFTISTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 CF0TXIF    : 1;
        const uint32 CF1TXIF    : 1;
        const uint32 CF2TXIF    : 1;
        const uint32 CF3TXIF    : 1;
        const uint32 CF4TXIF    : 1;
        const uint32 CF5TXIF    : 1;
        const uint32 CF6TXIF    : 1;
        const uint32 CF7TXIF    : 1;
        const uint32 CF8TXIF    : 1;
        const uint32 CF9TXIF    : 1;
        const uint32 CF10TXIF   : 1;
        const uint32 CF11TXIF   : 1;
        const uint32 CF12TXIF   : 1;
        const uint32 CF13TXIF   : 1;
        const uint32 CF14TXIF   : 1;
        const uint32 CF15TXIF   : 1;
        const uint32 CF16TXIF   : 1;
        const uint32 CF17TXIF   : 1;
        const uint32 CF18TXIF   : 1;
        const uint32 CF19TXIF   : 1;
        const uint32 CF20TXIF   : 1;
        const uint32 CF21TXIF   : 1;
        const uint32 CF22TXIF   : 1;
        const uint32 CF23TXIF   : 1;
        const uint32 reserved24 : 8;
    } BIT;
} rscfd_cfdcftists_t;

/*******************************************************************************
* Register: CFDCFOFRISTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 CF0RXIF    : 1;
        const uint32 CF1RXIF    : 1;
        const uint32 CF2RXIF    : 1;
        const uint32 CF3RXIF    : 1;
        const uint32 CF4RXIF    : 1;
        const uint32 CF5RXIF    : 1;
        const uint32 CF6RXIF    : 1;
        const uint32 CF7RXIF    : 1;
        const uint32 CF8RXIF    : 1;
        const uint32 CF9RXIF    : 1;
        const uint32 CF10RXIF   : 1;
        const uint32 CF11RXIF   : 1;
        const uint32 CF12RXIF   : 1;
        const uint32 CF13RXIF   : 1;
        const uint32 CF14RXIF   : 1;
        const uint32 CF15RXIF   : 1;
        const uint32 CF16RXIF   : 1;
        const uint32 CF17RXIF   : 1;
        const uint32 CF18RXIF   : 1;
        const uint32 CF19RXIF   : 1;
        const uint32 CF20RXIF   : 1;
        const uint32 CF21RXIF   : 1;
        const uint32 CF22RXIF   : 1;
        const uint32 CF23RXIF   : 1;
        const uint32 reserved24 : 8;
    } BIT;
} rscfd_cfdcfofrists_t;

/*******************************************************************************
* Register: CFDCFOFTISTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 CF0TXIF    : 1;
        const uint32 CF1TXIF    : 1;
        const uint32 CF2TXIF    : 1;
        const uint32 CF3TXIF    : 1;
        const uint32 CF4TXIF    : 1;
        const uint32 CF5TXIF    : 1;
        const uint32 CF6TXIF    : 1;
        const uint32 CF7TXIF    : 1;
        const uint32 CF8TXIF    : 1;
        const uint32 CF9TXIF    : 1;
        const uint32 CF10TXIF   : 1;
        const uint32 CF11TXIF   : 1;
        const uint32 CF12TXIF   : 1;
        const uint32 CF13TXIF   : 1;
        const uint32 CF14TXIF   : 1;
        const uint32 CF15TXIF   : 1;
        const uint32 CF16TXIF   : 1;
        const uint32 CF17TXIF   : 1;
        const uint32 CF18TXIF   : 1;
        const uint32 CF19TXIF   : 1;
        const uint32 CF20TXIF   : 1;
        const uint32 CF21TXIF   : 1;
        const uint32 CF22TXIF   : 1;
        const uint32 CF23TXIF   : 1;
        const uint32 reserved24 : 8;
    } BIT;
} rscfd_cfdcfoftists_t;

/*******************************************************************************
* Register: CFDCFMOWSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 CF0MOW     : 1;
        const uint32 CF1MOW     : 1;
        const uint32 CF2MOW     : 1;
        const uint32 CF3MOW     : 1;
        const uint32 CF4MOW     : 1;
        const uint32 CF5MOW     : 1;
        const uint32 CF6MOW     : 1;
        const uint32 CF7MOW     : 1;
        const uint32 CF8MOW     : 1;
        const uint32 CF9MOW     : 1;
        const uint32 CF10MOW    : 1;
        const uint32 CF11MOW    : 1;
        const uint32 CF12MOW    : 1;
        const uint32 CF13MOW    : 1;
        const uint32 CF14MOW    : 1;
        const uint32 CF15MOW    : 1;
        const uint32 CF16MOW    : 1;
        const uint32 CF17MOW    : 1;
        const uint32 CF18MOW    : 1;
        const uint32 CF19MOW    : 1;
        const uint32 CF20MOW    : 1;
        const uint32 CF21MOW    : 1;
        const uint32 CF22MOW    : 1;
        const uint32 CF23MOW    : 1;
        const uint32 reserved24 : 8;
    } BIT;
} rscfd_cfdcfmowsts_t;

/*******************************************************************************
* Register: CFDFFFSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 RF0FFLL  : 1;
        const uint32 RF1FFLL  : 1;
        const uint32 RF2FFLL  : 1;
        const uint32 RF3FFLL  : 1;
        const uint32 RF4FFLL  : 1;
        const uint32 RF5FFLL  : 1;
        const uint32 RF6FFLL  : 1;
        const uint32 RF7FFLL  : 1;
        const uint32 CF0FFLL  : 1;
        const uint32 CF1FFLL  : 1;
        const uint32 CF2FFLL  : 1;
        const uint32 CF3FFLL  : 1;
        const uint32 CF4FFLL  : 1;
        const uint32 CF5FFLL  : 1;
        const uint32 CF6FFLL  : 1;
        const uint32 CF7FFLL  : 1;
        const uint32 CF8FFLL  : 1;
        const uint32 CF9FFLL  : 1;
        const uint32 CF10FFLL : 1;
        const uint32 CF11FFLL : 1;
        const uint32 CF12FFLL : 1;
        const uint32 CF13FFLL : 1;
        const uint32 CF14FFLL : 1;
        const uint32 CF15FFLL : 1;
        const uint32 CF16FFLL : 1;
        const uint32 CF17FFLL : 1;
        const uint32 CF18FFLL : 1;
        const uint32 CF19FFLL : 1;
        const uint32 CF20FFLL : 1;
        const uint32 CF21FFLL : 1;
        const uint32 CF22FFLL : 1;
        const uint32 CF23FFLL : 1;
    } BIT;
} rscfd_cfdfffsts_t;

/*******************************************************************************
* Register: CFDTMC
*******************************************************************************/
typedef union
{
    uint8 BYTE;
    struct
    {
        uint8 TMTR            : 1;
        uint8 TMTAR           : 1;
        uint8 TMOM            : 1;
        const uint8 reserved3 : 5;
    } BIT;
} rscfd_cfdtmc_t;

/*******************************************************************************
* Register: CFDTMSTS
*******************************************************************************/
typedef union
{
    uint8 BYTE;
    struct
    {
        uint8 TMTSTS          : 1;
        uint8 TMTRF           : 2;
        uint8 TMTRM           : 1;
        uint8 TMTARM          : 1;
        const uint8 reserved5 : 3;
    } BIT;
} rscfd_cfdtmsts_t;

/*******************************************************************************
* Register: CFDTMTRSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 TMTRSTS0  : 1;
        const uint32 TMTRSTS1  : 1;
        const uint32 TMTRSTS2  : 1;
        const uint32 TMTRSTS3  : 1;
        const uint32 TMTRSTS4  : 1;
        const uint32 TMTRSTS5  : 1;
        const uint32 TMTRSTS6  : 1;
        const uint32 TMTRSTS7  : 1;
        const uint32 TMTRSTS8  : 1;
        const uint32 TMTRSTS9  : 1;
        const uint32 TMTRSTS10 : 1;
        const uint32 TMTRSTS11 : 1;
        const uint32 TMTRSTS12 : 1;
        const uint32 TMTRSTS13 : 1;
        const uint32 TMTRSTS14 : 1;
        const uint32 TMTRSTS15 : 1;
        const uint32 TMTRSTS16 : 1;
        const uint32 TMTRSTS17 : 1;
        const uint32 TMTRSTS18 : 1;
        const uint32 TMTRSTS19 : 1;
        const uint32 TMTRSTS20 : 1;
        const uint32 TMTRSTS21 : 1;
        const uint32 TMTRSTS22 : 1;
        const uint32 TMTRSTS23 : 1;
        const uint32 TMTRSTS24 : 1;
        const uint32 TMTRSTS25 : 1;
        const uint32 TMTRSTS26 : 1;
        const uint32 TMTRSTS27 : 1;
        const uint32 TMTRSTS28 : 1;
        const uint32 TMTRSTS29 : 1;
        const uint32 TMTRSTS30 : 1;
        const uint32 TMTRSTS31 : 1;
    } BIT;
} rscfd_cfdtmtrsts_t;

/*******************************************************************************
* Register: CFDTMTARSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 TMTARSTS0  : 1;
        const uint32 TMTARSTS1  : 1;
        const uint32 TMTARSTS2  : 1;
        const uint32 TMTARSTS3  : 1;
        const uint32 TMTARSTS4  : 1;
        const uint32 TMTARSTS5  : 1;
        const uint32 TMTARSTS6  : 1;
        const uint32 TMTARSTS7  : 1;
        const uint32 TMTARSTS8  : 1;
        const uint32 TMTARSTS9  : 1;
        const uint32 TMTARSTS10 : 1;
        const uint32 TMTARSTS11 : 1;
        const uint32 TMTARSTS12 : 1;
        const uint32 TMTARSTS13 : 1;
        const uint32 TMTARSTS14 : 1;
        const uint32 TMTARSTS15 : 1;
        const uint32 TMTARSTS16 : 1;
        const uint32 TMTARSTS17 : 1;
        const uint32 TMTARSTS18 : 1;
        const uint32 TMTARSTS19 : 1;
        const uint32 TMTARSTS20 : 1;
        const uint32 TMTARSTS21 : 1;
        const uint32 TMTARSTS22 : 1;
        const uint32 TMTARSTS23 : 1;
        const uint32 TMTARSTS24 : 1;
        const uint32 TMTARSTS25 : 1;
        const uint32 TMTARSTS26 : 1;
        const uint32 TMTARSTS27 : 1;
        const uint32 TMTARSTS28 : 1;
        const uint32 TMTARSTS29 : 1;
        const uint32 TMTARSTS30 : 1;
        const uint32 TMTARSTS31 : 1;
    } BIT;
} rscfd_cfdtmtarsts_t;

/*******************************************************************************
* Register: CFDTMTCSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 TMTCSTS0  : 1;
        const uint32 TMTCSTS1  : 1;
        const uint32 TMTCSTS2  : 1;
        const uint32 TMTCSTS3  : 1;
        const uint32 TMTCSTS4  : 1;
        const uint32 TMTCSTS5  : 1;
        const uint32 TMTCSTS6  : 1;
        const uint32 TMTCSTS7  : 1;
        const uint32 TMTCSTS8  : 1;
        const uint32 TMTCSTS9  : 1;
        const uint32 TMTCSTS10 : 1;
        const uint32 TMTCSTS11 : 1;
        const uint32 TMTCSTS12 : 1;
        const uint32 TMTCSTS13 : 1;
        const uint32 TMTCSTS14 : 1;
        const uint32 TMTCSTS15 : 1;
        const uint32 TMTCSTS16 : 1;
        const uint32 TMTCSTS17 : 1;
        const uint32 TMTCSTS18 : 1;
        const uint32 TMTCSTS19 : 1;
        const uint32 TMTCSTS20 : 1;
        const uint32 TMTCSTS21 : 1;
        const uint32 TMTCSTS22 : 1;
        const uint32 TMTCSTS23 : 1;
        const uint32 TMTCSTS24 : 1;
        const uint32 TMTCSTS25 : 1;
        const uint32 TMTCSTS26 : 1;
        const uint32 TMTCSTS27 : 1;
        const uint32 TMTCSTS28 : 1;
        const uint32 TMTCSTS29 : 1;
        const uint32 TMTCSTS30 : 1;
        const uint32 TMTCSTS31 : 1;
    } BIT;
} rscfd_cfdtmtcsts_t;

/*******************************************************************************
* Register: CFDTMTASTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 TMTASTS0  : 1;
        const uint32 TMTASTS1  : 1;
        const uint32 TMTASTS2  : 1;
        const uint32 TMTASTS3  : 1;
        const uint32 TMTASTS4  : 1;
        const uint32 TMTASTS5  : 1;
        const uint32 TMTASTS6  : 1;
        const uint32 TMTASTS7  : 1;
        const uint32 TMTASTS8  : 1;
        const uint32 TMTASTS9  : 1;
        const uint32 TMTASTS10 : 1;
        const uint32 TMTASTS11 : 1;
        const uint32 TMTASTS12 : 1;
        const uint32 TMTASTS13 : 1;
        const uint32 TMTASTS14 : 1;
        const uint32 TMTASTS15 : 1;
        const uint32 TMTASTS16 : 1;
        const uint32 TMTASTS17 : 1;
        const uint32 TMTASTS18 : 1;
        const uint32 TMTASTS19 : 1;
        const uint32 TMTASTS20 : 1;
        const uint32 TMTASTS21 : 1;
        const uint32 TMTASTS22 : 1;
        const uint32 TMTASTS23 : 1;
        const uint32 TMTASTS24 : 1;
        const uint32 TMTASTS25 : 1;
        const uint32 TMTASTS26 : 1;
        const uint32 TMTASTS27 : 1;
        const uint32 TMTASTS28 : 1;
        const uint32 TMTASTS29 : 1;
        const uint32 TMTASTS30 : 1;
        const uint32 TMTASTS31 : 1;
    } BIT;
} rscfd_cfdtmtasts_t;

/*******************************************************************************
* Register: CFDTMIEC
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 TMIE0  : 1;
        uint32 TMIE1  : 1;
        uint32 TMIE2  : 1;
        uint32 TMIE3  : 1;
        uint32 TMIE4  : 1;
        uint32 TMIE5  : 1;
        uint32 TMIE6  : 1;
        uint32 TMIE7  : 1;
        uint32 TMIE8  : 1;
        uint32 TMIE9  : 1;
        uint32 TMIE10 : 1;
        uint32 TMIE11 : 1;
        uint32 TMIE12 : 1;
        uint32 TMIE13 : 1;
        uint32 TMIE14 : 1;
        uint32 TMIE15 : 1;
        uint32 TMIE16 : 1;
        uint32 TMIE17 : 1;
        uint32 TMIE18 : 1;
        uint32 TMIE19 : 1;
        uint32 TMIE20 : 1;
        uint32 TMIE21 : 1;
        uint32 TMIE22 : 1;
        uint32 TMIE23 : 1;
        uint32 TMIE24 : 1;
        uint32 TMIE25 : 1;
        uint32 TMIE26 : 1;
        uint32 TMIE27 : 1;
        uint32 TMIE28 : 1;
        uint32 TMIE29 : 1;
        uint32 TMIE30 : 1;
        uint32 TMIE31 : 1;
    } BIT;
} rscfd_cfdtmiec_t;

/*******************************************************************************
* Register: CFDTXQCC
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        uint8       BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 TXQE             : 1;
        uint32 TXQGWE           : 1;
        uint32 TXQOWE           : 1;
        const uint32 reserved3  : 2;
        uint32 TXQTXIE          : 1;
        const uint32 reserved6  : 1;
        uint32 TXQIM            : 1;
        uint32 TXQDC            : 5;
        const uint32 reserved13 : 3;
        uint32 TXQFIE           : 1;
        uint32 TXQOFRXIE        : 1;
        uint32 TXQOFTXIE        : 1;
        const uint32 reserved19 : 13;
    } BIT;
} rscfd_cfdtxqcc_t;

/*******************************************************************************
* Register: CFDTXQSTS
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 TXQEMP           : 1;
        uint32 TXQFLL           : 1;
        uint32 TXQIF            : 1;
        const uint32 reserved3  : 5;
        uint32 TXQMC            : 6;
        const uint32 reserved14 : 2;
        uint32 TXQFIF           : 1;
        uint32 TXQOFRXIF        : 1;
        uint32 TXQOFTXIF        : 1;
        uint32 TXQMLT           : 1;
        uint32 TXQMOW           : 1;
        const uint32 reserved21 : 11;
    } BIT;
} rscfd_cfdtxqsts_t;

/*******************************************************************************
* Register: CFDTXQPCTR
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 TXQPC           : 8;
        const uint32 reserved8 : 24;
    } BIT;
} rscfd_cfdtxqpctr_t;

/*******************************************************************************
* Register: CFDTXQESTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 TXQ0EMP  : 1;
        const uint32 TXQ1EMP  : 1;
        const uint32 TXQ2EMP  : 1;
        const uint32 TXQ3EMP  : 1;
        const uint32 TXQ4EMP  : 1;
        const uint32 TXQ5EMP  : 1;
        const uint32 TXQ6EMP  : 1;
        const uint32 TXQ7EMP  : 1;
        const uint32 TXQ8EMP  : 1;
        const uint32 TXQ9EMP  : 1;
        const uint32 TXQ10EMP : 1;
        const uint32 TXQ11EMP : 1;
        const uint32 TXQ12EMP : 1;
        const uint32 TXQ13EMP : 1;
        const uint32 TXQ14EMP : 1;
        const uint32 TXQ15EMP : 1;
        const uint32 TXQ16EMP : 1;
        const uint32 TXQ17EMP : 1;
        const uint32 TXQ18EMP : 1;
        const uint32 TXQ19EMP : 1;
        const uint32 TXQ20EMP : 1;
        const uint32 TXQ21EMP : 1;
        const uint32 TXQ22EMP : 1;
        const uint32 TXQ23EMP : 1;
        const uint32 TXQ24EMP : 1;
        const uint32 TXQ25EMP : 1;
        const uint32 TXQ26EMP : 1;
        const uint32 TXQ27EMP : 1;
        const uint32 TXQ28EMP : 1;
        const uint32 TXQ29EMP : 1;
        const uint32 TXQ30EMP : 1;
        const uint32 TXQ31EMP : 1;
    } BIT;
} rscfd_cfdtxqests_t;

/*******************************************************************************
* Register: CFDTXQFISTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 TXQ0FULL   : 1;
        const uint32 TXQ1FULL   : 1;
        const uint32 TXQ2FULL   : 1;
        const uint32 reserved3  : 1;
        const uint32 TXQ4FULL   : 1;
        const uint32 TXQ5FULL   : 1;
        const uint32 TXQ6FULL   : 1;
        const uint32 reserved7  : 1;
        const uint32 TXQ8FULL   : 1;
        const uint32 TXQ9FULL   : 1;
        const uint32 TXQ10FULL  : 1;
        const uint32 reserved11 : 1;
        const uint32 TXQ12FULL  : 1;
        const uint32 TXQ13FULL  : 1;
        const uint32 TXQ14FULL  : 1;
        const uint32 reserved15 : 1;
        const uint32 TXQ16FULL  : 1;
        const uint32 TXQ17FULL  : 1;
        const uint32 TXQ18FULL  : 1;
        const uint32 reserved19 : 1;
        const uint32 TXQ20FULL  : 1;
        const uint32 TXQ21FULL  : 1;
        const uint32 TXQ22FULL  : 1;
        const uint32 reserved23 : 1;
        const uint32 TXQ24FULL  : 1;
        const uint32 TXQ25FULL  : 1;
        const uint32 TXQ26FULL  : 1;
        const uint32 reserved27 : 1;
        const uint32 TXQ28FULL  : 1;
        const uint32 TXQ29FULL  : 1;
        const uint32 TXQ30FULL  : 1;
        const uint32 reserved31 : 1;
    } BIT;
} rscfd_cfdtxqfists_t;

/*******************************************************************************
* Register: CFDTXQMSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 TXQ0ML     : 1;
        const uint32 TXQ1ML     : 1;
        const uint32 TXQ2ML     : 1;
        const uint32 reserved3  : 1;
        const uint32 TXQ4ML     : 1;
        const uint32 TXQ5ML     : 1;
        const uint32 TXQ6ML     : 1;
        const uint32 reserved7  : 1;
        const uint32 TXQ8ML     : 1;
        const uint32 TXQ9ML     : 1;
        const uint32 TXQ10ML    : 1;
        const uint32 reserved11 : 1;
        const uint32 TXQ12ML    : 1;
        const uint32 TXQ13ML    : 1;
        const uint32 TXQ14ML    : 1;
        const uint32 reserved15 : 1;
        const uint32 TXQ16ML    : 1;
        const uint32 TXQ17ML    : 1;
        const uint32 TXQ18ML    : 1;
        const uint32 reserved19 : 1;
        const uint32 TXQ20ML    : 1;
        const uint32 TXQ21ML    : 1;
        const uint32 TXQ22ML    : 1;
        const uint32 reserved23 : 1;
        const uint32 TXQ24ML    : 1;
        const uint32 TXQ25ML    : 1;
        const uint32 TXQ26ML    : 1;
        const uint32 reserved27 : 1;
        const uint32 TXQ28ML    : 1;
        const uint32 TXQ29ML    : 1;
        const uint32 TXQ30ML    : 1;
        const uint32 reserved31 : 1;
    } BIT;
} rscfd_cfdtxqmsts_t;

/*******************************************************************************
* Register: CFDTXQOWSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 TXQ0OW  : 1;
        const uint32 TXQ1OW  : 1;
        const uint32 TXQ2OW  : 1;
        const uint32 TXQ3OW  : 1;
        const uint32 TXQ4OW  : 1;
        const uint32 TXQ5OW  : 1;
        const uint32 TXQ6OW  : 1;
        const uint32 TXQ7OW  : 1;
        const uint32 TXQ8OW  : 1;
        const uint32 TXQ9OW  : 1;
        const uint32 TXQ10OW : 1;
        const uint32 TXQ11OW : 1;
        const uint32 TXQ12OW : 1;
        const uint32 TXQ13OW : 1;
        const uint32 TXQ14OW : 1;
        const uint32 TXQ15OW : 1;
        const uint32 TXQ16OW : 1;
        const uint32 TXQ17OW : 1;
        const uint32 TXQ18OW : 1;
        const uint32 TXQ19OW : 1;
        const uint32 TXQ20OW : 1;
        const uint32 TXQ21OW : 1;
        const uint32 TXQ22OW : 1;
        const uint32 TXQ23OW : 1;
        const uint32 TXQ24OW : 1;
        const uint32 TXQ25OW : 1;
        const uint32 TXQ26OW : 1;
        const uint32 TXQ27OW : 1;
        const uint32 TXQ28OW : 1;
        const uint32 TXQ29OW : 1;
        const uint32 TXQ30OW : 1;
        const uint32 TXQ31OW : 1;
    } BIT;
} rscfd_cfdtxqowsts_t;

/*******************************************************************************
* Register: CFDTXQISTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 TXQ0ISF  : 1;
        const uint32 TXQ1ISF  : 1;
        const uint32 TXQ2ISF  : 1;
        const uint32 TXQ3ISF  : 1;
        const uint32 TXQ4ISF  : 1;
        const uint32 TXQ5ISF  : 1;
        const uint32 TXQ6ISF  : 1;
        const uint32 TXQ7ISF  : 1;
        const uint32 TXQ8ISF  : 1;
        const uint32 TXQ9ISF  : 1;
        const uint32 TXQ10ISF : 1;
        const uint32 TXQ11ISF : 1;
        const uint32 TXQ12ISF : 1;
        const uint32 TXQ13ISF : 1;
        const uint32 TXQ14ISF : 1;
        const uint32 TXQ15ISF : 1;
        const uint32 TXQ16ISF : 1;
        const uint32 TXQ17ISF : 1;
        const uint32 TXQ18ISF : 1;
        const uint32 TXQ19ISF : 1;
        const uint32 TXQ20ISF : 1;
        const uint32 TXQ21ISF : 1;
        const uint32 TXQ22ISF : 1;
        const uint32 TXQ23ISF : 1;
        const uint32 TXQ24ISF : 1;
        const uint32 TXQ25ISF : 1;
        const uint32 TXQ26ISF : 1;
        const uint32 TXQ27ISF : 1;
        const uint32 TXQ28ISF : 1;
        const uint32 TXQ29ISF : 1;
        const uint32 TXQ30ISF : 1;
        const uint32 TXQ31ISF : 1;
    } BIT;
} rscfd_cfdtxqists_t;

/*******************************************************************************
* Register: CFDTXQOFTISTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 TXQ0OFTISTS  : 1;
        const uint32 TXQ1OFTISTS  : 1;
        const uint32 TXQ2OFTISTS  : 1;
        const uint32 TXQ3OFTISTS  : 1;
        const uint32 TXQ4OFTISTS  : 1;
        const uint32 TXQ5OFTISTS  : 1;
        const uint32 TXQ6OFTISTS  : 1;
        const uint32 TXQ7OFTISTS  : 1;
        const uint32 TXQ8OFTISTS  : 1;
        const uint32 TXQ9OFTISTS  : 1;
        const uint32 TXQ10OFTISTS : 1;
        const uint32 TXQ11OFTISTS : 1;
        const uint32 TXQ12OFTISTS : 1;
        const uint32 TXQ13OFTISTS : 1;
        const uint32 TXQ14OFTISTS : 1;
        const uint32 TXQ15OFTISTS : 1;
        const uint32 TXQ16OFTISTS : 1;
        const uint32 TXQ17OFTISTS : 1;
        const uint32 TXQ18OFTISTS : 1;
        const uint32 TXQ19OFTISTS : 1;
        const uint32 TXQ20OFTISTS : 1;
        const uint32 TXQ21OFTISTS : 1;
        const uint32 TXQ22OFTISTS : 1;
        const uint32 TXQ23OFTISTS : 1;
        const uint32 TXQ24OFTISTS : 1;
        const uint32 TXQ25OFTISTS : 1;
        const uint32 TXQ26OFTISTS : 1;
        const uint32 TXQ27OFTISTS : 1;
        const uint32 TXQ28OFTISTS : 1;
        const uint32 TXQ29OFTISTS : 1;
        const uint32 TXQ30OFTISTS : 1;
        const uint32 TXQ31OFTISTS : 1;
    } BIT;
} rscfd_cfdtxqoftists_t;

/*******************************************************************************
* Register: CFDTXQOFRISTS
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 TXQ0OFRISF        : 1;
        uint32 TXQ1OFRISF        : 1;
        uint32 TXQ2OFRISF        : 1;
        const uint32 reserved3   : 1;
        uint32 TXQ4OFRISF        : 1;
        uint32 TXQ5OFRISF        : 1;
        uint32 TXQ6OFRISF        : 1;
        const uint32 reserved7   : 1;
        uint32 TXQ8OFRISF        : 1;
        uint32 TXQ9OFRISF        : 1;
        uint32 TXQ10OFRISF       : 1;
        const uint32 reserved11  : 1;
        uint32 TXQ12OFRISF       : 1;
        uint32 TXQ13OFRISF       : 1;
        uint32 TXQ14OFRISF       : 1;
        const uint32 reserved15  : 1;
        uint32 TXQ16OFRISF       : 1;
        uint32 TXQ17OFRISF       : 1;
        uint32 TXQ18OFRISF       : 1;
        const uint32 reserved19  : 1;
        uint32 TXQ20OFRISF       : 1;
        uint32 TXQ21OFRISF       : 1;
        uint32 TXQ22OFRISF       : 1;
        const uint32 reserved23  : 1;
        uint32 TXQ24OFRISF       : 1;
        uint32 TXQ25OFRISF       : 1;
        uint32 TXQ26OFRISF       : 1;
        const uint32 reserved27  : 1;
        uint32 TXQ28OFRISF       : 1;
        uint32 TXQ29OFRISF       : 1;
        uint32 TXQ30OFRISF       : 1;
        const uint32 reserved31  : 1;
    } BIT;
} rscfd_cfdtxqofrists_t;

/*******************************************************************************
* Register: CFDTXQFSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 TXQ0OOFTISF  : 1;
        const uint32 TXQ1OOFTISF  : 1;
        const uint32 TXQ2OOFTISF  : 1;
        const uint32 TXQ3OOFTISF  : 1;
        const uint32 TXQ4OOFTISF  : 1;
        const uint32 TXQ5OOFTISF  : 1;
        const uint32 TXQ6OOFTISF  : 1;
        const uint32 TXQ7OOFTISF  : 1;
        const uint32 TXQ8OOFTISF  : 1;
        const uint32 TXQ9OOFTISF  : 1;
        const uint32 TXQ10OOFTISF : 1;
        const uint32 TXQ11OOFTISF : 1;
        const uint32 TXQ12OOFTISF : 1;
        const uint32 TXQ13OOFTISF : 1;
        const uint32 TXQ14OOFTISF : 1;
        const uint32 TXQ15OOFTISF : 1;
        const uint32 TXQ16OOFTISF : 1;
        const uint32 TXQ17OOFTISF : 1;
        const uint32 TXQ18OOFTISF : 1;
        const uint32 TXQ19OOFTISF : 1;
        const uint32 TXQ20OOFTISF : 1;
        const uint32 TXQ21OOFTISF : 1;
        const uint32 TXQ22OOFTISF : 1;
        const uint32 TXQ23OOFTISF : 1;
        const uint32 TXQ24OOFTISF : 1;
        const uint32 TXQ25OOFTISF : 1;
        const uint32 TXQ26OOFTISF : 1;
        const uint32 TXQ27OOFTISF : 1;
        const uint32 TXQ28OOFTISF : 1;
        const uint32 TXQ29OOFTISF : 1;
        const uint32 TXQ30OOFTISF : 1;
        const uint32 TXQ31OOFTISF : 1;
    } BIT;
} rscfd_cfdtxqfsts_t;

/*******************************************************************************
* Register: CFDTHLCC
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        uint8       BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 THLE             : 1;
        const uint32 reserved1  : 7;
        uint32 THLIE            : 1;
        uint32 THLIM            : 1;
        uint32 THLDTE           : 1;
        uint32 THLDGE           : 1;
        const uint32 reserved12 : 20;
    } BIT;
} rscfd_cfdthlcc_t;

/*******************************************************************************
* Register: CFDTHLSTS
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 THLEMP           : 1;
        uint32 THLFLL           : 1;
        uint32 THLELT           : 1;
        uint32 THLIF            : 1;
        const uint32 reserved4  : 4;
        uint32 THLMC            : 6;
        const uint32 reserved14 : 18;
    } BIT;
} rscfd_cfdthlsts_t;

/*******************************************************************************
* Register: CFDTHLPCTR
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 THLPC           : 8;
        const uint32 reserved8 : 24;
    } BIT;
} rscfd_cfdthlpctr_t;

/*******************************************************************************
* Register: CFDGTINTSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 TSIF0      : 1;
        const uint32 TAIF0      : 1;
        const uint32 TQIF0      : 1;
        const uint32 CFTIF0     : 1;
        const uint32 THIF0      : 1;
        const uint32 TQOFIF0    : 1;
        const uint32 CFOTIF0    : 1;
        const uint32 reserved7  : 1;
        const uint32 TSIF1      : 1;
        const uint32 TAIF1      : 1;
        const uint32 TQIF1      : 1;
        const uint32 CFTIF1     : 1;
        const uint32 THIF1      : 1;
        const uint32 TQOFIF1    : 1;
        const uint32 CFOTIF1    : 1;
        const uint32 reserved15 : 1;
        const uint32 TSIF2      : 1;
        const uint32 TAIF2      : 1;
        const uint32 TQIF2      : 1;
        const uint32 CFTIF2     : 1;
        const uint32 THIF2      : 1;
        const uint32 TQOFIF2    : 1;
        const uint32 CFOTIF2    : 1;
        const uint32 reserved23 : 1;
        const uint32 TSIF3      : 1;
        const uint32 TAIF3      : 1;
        const uint32 TQIF3      : 1;
        const uint32 CFTIF3     : 1;
        const uint32 THIF3      : 1;
        const uint32 TQOFIF3    : 1;
        const uint32 CFOTIF3    : 1;
        const uint32 reserved31 : 1;
    } BIT;
} rscfd_cfdgtintsts_t;

/*******************************************************************************
* Register: CFDGTSTCFG
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        uint8       BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 C0ICBCE          : 1;
        uint32 C1ICBCE          : 1;
        uint32 C2ICBCE          : 1;
        uint32 C3ICBCE          : 1;
        uint32 C4ICBCE          : 1;
        uint32 C5ICBCE          : 1;
        uint32 C6ICBCE          : 1;
        uint32 C7ICBCE          : 1;
        const uint32 reserved8  : 8;
        uint32 RTMPS            : 10;
        const uint32 reserved26 : 6;
    } BIT;
} rscfd_cfdgtstcfg_t;

/*******************************************************************************
* Register: CFDGTSTCTR
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 ICBCTME         : 1;
        const uint32 reserved1 : 1;
        uint32 RTME            : 1;
        const uint32 reserved3 : 29;
    } BIT;
} rscfd_cfdgtstctr_t;

/*******************************************************************************
* Register: CFDGFDCFG
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        uint8       BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 RPED             : 1;
        const uint32 reserved1  : 7;
        uint32 TSCCFG           : 2;
        const uint32 reserved10 : 22;
    } BIT;
} rscfd_cfdgfdcfg_t;

/*******************************************************************************
* Register: CFDGCRCCFG
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
} rscfd_cfdgcrccfg_t;

/*******************************************************************************
* Register: CFDGLOCKK
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint32 LOCK             : 16;
        const uint32 reserved16 : 16;
    } BIT;
} rscfd_cfdglockk_t;

/*******************************************************************************
* Register: CFDCDTCT
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        uint8       BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 RFDMAE0          : 1;
        uint32 RFDMAE1          : 1;
        uint32 RFDMAE2          : 1;
        uint32 RFDMAE3          : 1;
        uint32 RFDMAE4          : 1;
        uint32 RFDMAE5          : 1;
        uint32 RFDMAE6          : 1;
        uint32 RFDMAE7          : 1;
        uint32 CFDMAE0          : 1;
        uint32 CFDMAE1          : 1;
        uint32 CFDMAE2          : 1;
        uint32 CFDMAE3          : 1;
        uint32 CFDMAE4          : 1;
        uint32 CFDMAE5          : 1;
        uint32 CFDMAE6          : 1;
        uint32 CFDMAE7          : 1;
        const uint32 reserved16 : 16;
    } BIT;
} rscfd_cfdcdtct_t;

/*******************************************************************************
* Register: CFDCDTSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 RFDMASTS0  : 1;
        const uint32 RFDMASTS1  : 1;
        const uint32 RFDMASTS2  : 1;
        const uint32 RFDMASTS3  : 1;
        const uint32 RFDMASTS4  : 1;
        const uint32 RFDMASTS5  : 1;
        const uint32 RFDMASTS6  : 1;
        const uint32 RFDMASTS7  : 1;
        const uint32 CFDMASTS0  : 1;
        const uint32 CFDMASTS1  : 1;
        const uint32 CFDMASTS2  : 1;
        const uint32 CFDMASTS3  : 1;
        const uint32 CFDMASTS4  : 1;
        const uint32 CFDMASTS5  : 1;
        const uint32 CFDMASTS6  : 1;
        const uint32 CFDMASTS7  : 1;
        const uint32 reserved16 : 16;
    } BIT;
} rscfd_cfdcdtsts_t;

/*******************************************************************************
* Register: CFDCDTTCT
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 TQ0DMAE0   : 1;
        const uint32 TQ0DMAE1   : 1;
        const uint32 TQ0DMAE2   : 1;
        const uint32 TQ0DMAE3   : 1;
        const uint32 TQ0DMAE4   : 1;
        const uint32 TQ0DMAE5   : 1;
        const uint32 TQ0DMAE6   : 1;
        const uint32 TQ0DMAE7   : 1;
        const uint32 TQ3DMAE0   : 1;
        const uint32 TQ3DMAE1   : 1;
        const uint32 TQ3DMAE2   : 1;
        const uint32 TQ3DMAE3   : 1;
        const uint32 TQ3DMAE4   : 1;
        const uint32 TQ3DMAE5   : 1;
        const uint32 TQ3DMAE6   : 1;
        const uint32 TQ3DMAE7   : 1;
        const uint32 CFDMAE0    : 1;
        const uint32 CFDMAE1    : 1;
        const uint32 CFDMAE2    : 1;
        const uint32 CFDMAE3    : 1;
        const uint32 CFDMAE4    : 1;
        const uint32 CFDMAE5    : 1;
        const uint32 CFDMAE6    : 1;
        const uint32 CFDMAE7    : 1;
        const uint32 reserved24 : 8;
    } BIT;
} rscfd_cfdcdttct_t;

/*******************************************************************************
* Register: CFDGRINTSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 QFIF       : 3;
        const uint32 reserved3  : 1;
        const uint32 BQFIF      : 2;
        const uint32 reserved6  : 2;
        const uint32 QOFRIF     : 3;
        const uint32 reserved11 : 1;
        const uint32 BQOFRIF    : 2;
        const uint32 reserved14 : 2;
        const uint32 CFRIF      : 3;
        const uint32 reserved19 : 5;
        const uint32 CFRFIF     : 3;
        const uint32 reserved27 : 1;
        const uint32 CFOFRIF    : 3;
        const uint32 reserved31 : 1;
    } BIT;
} rscfd_cfdgrintsts_t;

/*******************************************************************************
* Register: CFDGRSTC
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        uint8       BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 SRST             : 1;
        const uint32 reserved1  : 7;
        uint32 KEY              : 8;
        const uint32 reserved16 : 16;
    } BIT;
} rscfd_cfdgrstc_t;

/*******************************************************************************
* Register: CFDGFCMC
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 FLXC0           : 1;
        uint32 FLXC1           : 1;
        uint32 FLXC2           : 1;
        uint32 FLXC3           : 1;
        const uint32 reserved4 : 28;
    } BIT;
} rscfd_cfdgfcmc_t;

/*******************************************************************************
* Register: CFDGBISC
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
} rscfd_cfdgbisc_t;

/*******************************************************************************
* Register: CFDGFTBAC
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 FLXMB0           : 4;
        const uint32 reserved4  : 4;
        uint32 FLXMB1           : 4;
        const uint32 reserved12 : 4;
        uint32 FLXMB2           : 4;
        const uint32 reserved20 : 4;
        uint32 FLXMB3           : 4;
        const uint32 reserved28 : 4;
    } BIT;
} rscfd_cfdgftbac_t;

/*******************************************************************************
* Register: CFDCnDCFG
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        uint8       BYTE2;
        uint8       BYTE3;
    } BYTE;
    struct
    {
        uint32 DBRP             : 8;
        uint32 DTSEG1           : 5;
        const uint32 reserved13 : 3;
        uint32 DTSEG2           : 4;
        const uint32 reserved20 : 4;
        uint32 DSJW             : 4;
        const uint32 reserved27 : 4;
    } BIT;
} rscfd_cfdcdcfg_t;

/*******************************************************************************
* Register: CFDCnFDCFG
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 EOCCFG           : 3;
        const uint32 reserved3  : 5;
        uint32 TDCOC            : 1;
        uint32 TDCE             : 1;
        uint32 ESIC             : 1;
        const uint32 reserved11 : 5;
        uint32 TDCO             : 8;
        uint32 GWEN             : 1;
        uint32 GWFDF            : 1;
        uint32 GWBRS            : 1;
        const uint32 reserved27 : 1;
        uint32 FDOE             : 1;
        uint32 REFE             : 1;
        uint32 CLOE             : 1;
        const uint32 reserved31 : 1;
    } BIT;
} rscfd_cfdcfdcfg_t;

/*******************************************************************************
* Register: CFDCnFDCTR
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 EOCCLR          : 1;
        uint32 SOCCLR          : 1;
        const uint32 reserved2 : 30;
    } BIT;
} rscfd_cfdcfdctr_t;

/*******************************************************************************
* Register: CFDCnFDSTS
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        uint8       BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 TDCR             : 8;
        uint32 EOCO             : 1;
        uint32 SOCO             : 1;
        const uint32 reserved10 : 5;
        uint32 TDCVF            : 1;
        uint32 EOC              : 8;
        uint32 SOC              : 8;
    } BIT;
} rscfd_cfdcfdsts_t;

/*******************************************************************************
* Register: CFDCnFDCRC
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 CRCREG     : 21;
        const uint32 reserved21 : 3;
        const uint32 SCNT       : 4;
        const uint32 reserved28 : 4;
    } BIT;
} rscfd_cfdcfdcrc_t;

/*******************************************************************************
* Register: CFDCBLCT
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        uint8       BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 BLCE            : 1;
        const uint32 reserved1 : 7;
        uint32 BLCLD           : 1;
        const uint32 reserved9 : 23;
    } BIT;
} rscfd_cfdcblct_t;

/*******************************************************************************
* Register: CFDCBLSTS
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 reserved0 : 3;
        const uint32 BLC       : 29;
    } BIT;
} rscfd_cfdcblsts_t;

/*******************************************************************************
* Register: CFDGAFLIDn
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 GAFLID  : 29;
        uint32 GAFLLB  : 1;
        uint32 GAFLRTR : 1;
        uint32 GAFLIDE : 1;
    } BIT;
} rscfd_cfdgaflid_t;

/*******************************************************************************
* Register: CFDGAFLMn
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 GAFLIDM  : 29;
        uint32 GAFLIFL1 : 1;
        uint32 GAFLRTRM : 1;
        uint32 GAFLIDEM : 1;
    } BIT;
} rscfd_cfdgaflm_t;

/*******************************************************************************
* Register: CFDGAFLP0n
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 GAFLDLC  : 4;
        uint32 GAFLSRD0 : 1;
        uint32 GAFLSRD1 : 1;
        uint32 GAFLSRD2 : 1;
        uint32 GAFLIFL0 : 1;
        uint32 GAFLRMDP : 7;
        uint32 GAFLRMV  : 1;
        uint32 GAFLPTR  : 16;
    } BIT;
} rscfd_cfdgaflp0_t;

/*******************************************************************************
* Register: CFDGAFLP1n
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 GAFLFDP : 32;
    } BIT;
} rscfd_cfdgaflp1_t;


/*******************************************************************************
* Register: CFDRMIDq
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 RMID       : 29;
        const uint32 reserved29 : 1;
        const uint32 RMRTR      : 1;
        const uint32 RMIDE      : 1;
    } BIT;
} rscfd_cfdrmid_t;

/*******************************************************************************
* Register: CFDRMPTRq
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 RMTS       : 16;
        const uint32 reserved16 : 12;
        const uint32 RMDLC      : 4;
    } BIT;
} rscfd_cfdrmptr_t;

/*******************************************************************************
* Register: CFDRMFDSTSq
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 RMESI      : 1;
        const uint32 RMBRS      : 1;
        const uint32 RMFDF      : 1;
        const uint32 reserved3  : 5;
        const uint32 RMIFL      : 2;
        const uint32 reserved10 : 6;
        const uint32 RMPTR      : 16;
    } BIT;
} rscfd_cfdrmfdsts_t;

/*******************************************************************************
* Register: CFDRMDF
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 RMDB0 : 8;
        const uint32 RMDB1 : 8;
        const uint32 RMDB2 : 8;
        const uint32 RMDB3 : 8;
    } BIT;
} rscfd_cfdrmdf_t;

/*******************************************************************************
* Register: CFDRFIDx
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 RFID       : 29;
        const uint32 reserved29 : 1;
        const uint32 RFRTR      : 1;
        const uint32 RFIDE      : 1;
    } BIT;
} rscfd_cfdrfid_t;

/*******************************************************************************
* Register: CFDRFPTRx
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 RFTS       : 16;
        const uint32 reserved16 : 12;
        const uint32 RFDLC      : 4;
    } BIT;
} rscfd_cfdrfptr_t;

/*******************************************************************************
* Register: CFDRFFDSTSx
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 RFESI      : 1;
        const uint32 RFBRS      : 1;
        const uint32 RFFDF      : 1;
        const uint32 reserved3  : 5;
        const uint32 RFIFL      : 2;
        const uint32 reserved10 : 6;
        const uint32 RFPTR      : 16;
    } BIT;
} rscfd_cfdrffdsts_t;

/*******************************************************************************
* Register: CFDRFDFdx
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 RFDB0 : 8;
        const uint32 RFDB1 : 8;
        const uint32 RFDB2 : 8;
        const uint32 RFDB3 : 8;
    } BIT;
} rscfd_cfdrfdf_t;

/*******************************************************************************
* Register: CFDCFIDk
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 CFID  : 29;
        uint32 THLEN : 1;
        uint32 CFRTR : 1;
        uint32 CFIDE : 1;
    } BIT;
} rscfd_cfdcfid_t;

/*******************************************************************************
* Register: CFDCFPTRk
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 CFTS             : 16;
        const uint32 reserved16 : 12;
        uint32 CFDLC            : 4;
    } BIT;
} rscfd_cfdcfptr_t;

/*******************************************************************************
* Register: CFDCFFDCSTSk
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 CFESI            : 1;
        uint32 CFBRS            : 1;
        uint32 CFFDF            : 1;
        const uint32 reserved3  : 5;
        uint32 CFIFL            : 2;
        const uint32 reserved10 : 6;
        uint32 CFPTR            : 16;
    } BIT;
} rscfd_cfdcffdcsts_t;

/*******************************************************************************
* Register: CFDCFDFdk
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 CFDB0 : 8;
        uint32 CFDB1 : 8;
        uint32 CFDB2 : 8;
        uint32 CFDB3 : 8;
    } BIT;
} rscfd_cfdcfdf_t;

/*******************************************************************************
* Register: CFDTMIDp
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 TMID  : 29;
        uint32 THLEN : 1;
        uint32 TMRTR : 1;
        uint32 TMIDE : 1;
    } BIT;
} rscfd_cfdtmid_t;

/*******************************************************************************
* Register: CFDTMPTRp
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        const uint16 LHALF;
        uint16       UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        uint8       BYTE3;
    } BYTE;
    struct
    {
        const uint32 reserved0 : 28;
        uint32 TMDLC           : 4;
    } BIT;
} rscfd_cfdtmptr_t;

/*******************************************************************************
* Register: CFDTMFDCTRp
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16       LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        uint8       BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 TMESI            : 1;
        uint32 TMBRS            : 1;
        uint32 TMFDF            : 1;
        const uint32 reserved3  : 5;
        uint32 TMIFL            : 2;
        const uint32 reserved10 : 6;
        uint32 TMPTR            : 16;
    } BIT;
} rscfd_cfdtmfdctr_t;

/*******************************************************************************
* Register: CFDTMDFdp
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 TMDB0 : 8;
        uint32 TMDB1 : 8;
        uint32 TMDB2 : 8;
        uint32 TMDB3 : 8;
    } BIT;
} rscfd_cfdtmdf_t;

/*******************************************************************************
* Register: CFDTHLACC0
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 BT         : 3;
        const uint32 BN         : 7;
        const uint32 reserved10 : 5;
        const uint32 TGW        : 1;
        const uint32 TMTS       : 16;
    } BIT;
} rscfd_cfdthlacc0_t;

/*******************************************************************************
* Register: CFDTHLACC1
*******************************************************************************/
typedef union
{
    const uint32 WORD;
    struct
    {
        const uint16 LHALF;
        const uint16 UHALF;
    } HALF;
    struct
    {
        const uint8 BYTE0;
        const uint8 BYTE1;
        const uint8 BYTE2;
        const uint8 BYTE3;
    } BYTE;
    struct
    {
        const uint32 TID        : 16;
        const uint32 TIFL       : 2;
        const uint32 reserved18 : 14;
    } BIT;
} rscfd_cfdthlacc1_t;

/*******************************************************************************
* Register: CFDRPGACC
*******************************************************************************/
typedef union
{
    uint32 WORD;
    struct
    {
        uint16 LHALF;
        uint16 UHALF;
    } HALF;
    struct
    {
        uint8 BYTE0;
        uint8 BYTE1;
        uint8 BYTE2;
        uint8 BYTE3;
    } BYTE;
    struct
    {
        uint32 RDTA : 32;
    } BIT;
} rscfd_cfdrpgacc_t;


/*##############################################################################
* Structures of registers
 ##############################################################################*/

/*******************************************************************************
* Channel related registers (CH1)
* NOTE: size 10H
*******************************************************************************/
typedef struct
{
    rscfd_cfdcncfg_t CFDCNCFG;                               /* 0x0000 */
    rscfd_cfdcctr_t  CFDCCTR;                                /* 0x0004 */
    rscfd_cfdcsts_t  CFDCSTS;                                /* 0x0008 */
    rscfd_cfdcerfl_t CFDCERFL;                               /* 0x000c */
}   rscfd_st1_regmap_t;

/*******************************************************************************
* Channel related registers (CH2)
* NOTE: size 20H
*******************************************************************************/
typedef struct
{
    rscfd_cfdcdcfg_t  CFDCDCFG;                              /* 0x0000 */
    rscfd_cfdcfdcfg_t CFDCFDCFG;                             /* 0x0004 */
    rscfd_cfdcfdctr_t CFDCFDCTR;                             /* 0x0008 */
    rscfd_cfdcfdsts_t CFDCFDSTS;                             /* 0x000C */
    rscfd_cfdcfdcrc_t CFDCFDCRC;                             /* 0x0010 */
    const uint32      reserved0014;                          /* 0x0014 */
    rscfd_cfdcblct_t  CFDCBLCT;                              /* 0x0018 */
    rscfd_cfdcblsts_t CFDCBLSTS;                             /* 0x001c */
}   rscfd_st2_regmap_t;

/*******************************************************************************
* Receive rule related registers (RRULE)
* NOTE: size 10H
*******************************************************************************/
typedef struct
{
    rscfd_cfdgaflid_t CFDGAFLID;                             /* 0x0000 */
    rscfd_cfdgaflm_t  CFDGAFLM;                              /* 0x0004 */
    rscfd_cfdgaflp0_t CFDGAFLP0;                             /* 0x0008 */
    rscfd_cfdgaflp1_t CFDGAFLP1;                             /* 0x000c */
}   rscfd_st3_regmap_t;

/*******************************************************************************
* Receive buffer related registers (RBUF)
* NOTE: padded to 80H for array like access
*******************************************************************************/
typedef struct
{
    rscfd_cfdrmid_t    CFDRMID;                              /* 0x0000 */
    rscfd_cfdrmptr_t   CFDRMPTR;                             /* 0x0004 */
    rscfd_cfdrmfdsts_t CFDRMFDSTS;                           /* 0x0008 */
    rscfd_cfdrmdf_t    CFDRMDF[RSCFD_CNT_BUFFDATA];          /* 0x000C */
    const uint32       reserved004C[13];                     /* 0x004c */
}   rscfd_st4_regmap_t;

/*******************************************************************************
* Receive FIFO buffer related registers (RFIFO)
* NOTE: padded to 80H for array like access
*******************************************************************************/
typedef struct
{
    rscfd_cfdrfid_t    CFDRFID;                              /* 0x0000 */
    rscfd_cfdrfptr_t   CFDRFPTR;                             /* 0x0004 */
    rscfd_cfdrffdsts_t CFDRFFDSTS;                           /* 0x0008 */
    rscfd_cfdrfdf_t    CFDRFDF[RSCFD_CNT_FIFODATA];          /* 0x000c */
    const uint32       reserved004C[13];                     /* 0x004c */
}   rscfd_st5_regmap_t;

/*******************************************************************************
* Transmit/Receive FIFO buffer related registers (TFIFO)
* NOTE: padded to 80H
*******************************************************************************/
typedef struct
{
    rscfd_cfdcfid_t     CFDCFID;                             /* 0x0000 */
    rscfd_cfdcfptr_t    CFDCFPTR;                            /* 0x0004 */
    rscfd_cfdcffdcsts_t CFDCFFDCSTS;                         /* 0x0008 */
    rscfd_cfdcfdf_t     CFDCFDF[RSCFD_CNT_FIFODATA];         /* 0x000c */
    const uint32        reserved004C[13];                    /* 0x004c */
}   rscfd_st6_regmap_t;

/*******************************************************************************
* Transmit buffer related registers (TBUF)
* NOTE: padded to 80H
*******************************************************************************/
typedef struct
{
    rscfd_cfdtmid_t    CFDTMID;                              /* 0x0000 */
    rscfd_cfdtmptr_t   CFDTMPTR;                             /* 0x0004 */
    rscfd_cfdtmfdctr_t CFDTMFDCTR;                           /* 0x0008 */
    rscfd_cfdtmdf_t    CFDTMDF[RSCFD_CNT_BUFFDATA];          /* 0x000c */
    const uint32       reserved004C[13];                     /* 0x004c */
} rscfd_st7_regmap_t;

/*******************************************************************************
* Transmit history list related registers (THL)
* NOTE: size 8H
*******************************************************************************/
typedef struct
{
    rscfd_cfdthlacc0_t CFDTHLACC0;                           /* 0x0000 */
    rscfd_cfdthlacc1_t CFDTHLACC1;                           /* 0x0004 */
} rscfd_st8_regmap_t;

/*******************************************************************************
* RSCFD unit
* NOTE: padded to
*******************************************************************************/
typedef struct
{
    rscfd_st1_regmap_t    CH1[RSCFD_CNT_CH];                 /* 0x0000 */
    rscfd_cfdgipv_t       CFDGIPV;                           /* 0x0020 */
    rscfd_cfdgcfg_t       CFDGCFG;                           /* 0x0084 */
    rscfd_cfdgctr_t       CFDGCTR;                           /* 0x0088 */
    rscfd_cfdgsts_t       CFDGSTS;                           /* 0x008C */
    rscfd_cfdgerfl_t      CFDGERFL;                          /* 0x0090 */
    rscfd_cfdgtsc_t       CFDGTSC;                           /* 0x0094 */
    rscfd_cfdgaflectr_t   CFDGAFLECTR;                       /* 0x0098 */
    rscfd_cfdgaflcfg_t    CFDGAFLCFG[RSCFD_CNT_CH];          /* 0x009C */
    rscfd_cfdrmnb_t       CFDRMNB;                           /* 0x00AC */
    rscfd_cfdrmnd_t       CFDRMND[RSCFD_CNT_MSGRX];          /* 0x00B0 */
    rscfd_cfdrfcc_t       CFDRFCC[RSCFD_CNT_FIFORX];         /* 0x00C0 */
    rscfd_cfdrfsts_t      CFDRFSTS[RSCFD_CNT_FIFORX];        /* 0x00E0 */
    rscfd_cfdrfpctr_t     CFDRFPCTR[RSCFD_CNT_FIFORX];       /* 0x0100 */
    rscfd_cfdcfcc_t       CFDCFCC[RSCFD_CNT_FIFORXTX];       /* 0x0120 */
    rscfd_cfdcfcce_t      CFDCFCCE[RSCFD_CNT_FIFORXTX];      /* 0x0180 */
    rscfd_cfdcfsts_t      CFDCFSTS[RSCFD_CNT_FIFORXTX];      /* 0x01E0 */
    rscfd_cfdcfpctr_t     CFDCFPCTR[RSCFD_CNT_FIFORXTX];     /* 0x0240 */
    rscfd_cfdfests_t      CFDFESTS;                          /* 0x02A0 */
    rscfd_cfdffsts_t      CFDFFSTS;                          /* 0x02A4 */
    rscfd_cfdfmsts_t      CFDFMSTS;                          /* 0x02A8 */
    rscfd_cfdrfists_t     CFDRFISTS;                         /* 0x02AC */
    rscfd_cfdcfrists_t    CFDCFRISTS;                        /* 0x02B0 */
    rscfd_cfdcftists_t    CFDCFTISTS;                        /* 0x02B4 */
    rscfd_cfdcfofrists_t  CFDCFOFRISTS;                      /* 0x02B8 */
    rscfd_cfdcfoftists_t  CFDCFOFTISTS;                      /* 0x02BC */
    rscfd_cfdcfmowsts_t   CFDCFMOWSTS;                       /* 0x02C0 */
    rscfd_cfdfffsts_t     CFDFFFSTS;                         /* 0x02C4 */
    const uint32          reserved02c8[2];                   /* 0x02C8 */
    rscfd_cfdtmc_t        CFDTMC[RSCFD_CNT_BUFFTX];          /* 0x02D0 */
    const uint32          reserved04D0[192];                 /* 0x04D0 */
    rscfd_cfdtmsts_t      CFDTMSTS[RSCFD_CNT_BUFFTX];        /* 0x07D0 */
    const uint32          reserved09D0[192];                 /* 0x09D0 */
    rscfd_cfdtmtrsts_t    CFDTMTRSTS[RSCFD_CNT_MSGTX];       /* 0x0CD0 */
    const uint32          reserved0D10[24];                  /* 0x0D10 */
    rscfd_cfdtmtarsts_t   CFDTMTARSTS[RSCFD_CNT_MSGTX];      /* 0x0D70 */
    const uint32          reserved0DB0[24];                  /* 0x0DB0 */
    rscfd_cfdtmtcsts_t    CFDTMTCSTS[RSCFD_CNT_MSGTX];       /* 0x0E10 */
    const uint32          reserved0E50[24];                  /* 0x0E50 */
    rscfd_cfdtmtasts_t    CFDTMTASTS[RSCFD_CNT_MSGTX];       /* 0x0EB0 */
    const uint32          reserved0EF0[24];                  /* 0x0EF0 */
    rscfd_cfdtmiec_t      CFDTMIEC[RSCFD_CNT_MSGTX];         /* 0x0F50 */
    const uint32          reserved0F90[28];                  /* 0x0F90 */
    rscfd_cfdtxqcc_t      CFDTXQCC0[RSCFD_CNT_CH];           /* TSQUEUE 0x1000 */
    rscfd_cfdtxqsts_t     CFDTXQSTS0[RSCFD_CNT_CH];          /* 0x1020 */
    rscfd_cfdtxqpctr_t    CFDTXQPCTR0[RSCFD_CNT_CH];         /* 0x1040 */
    rscfd_cfdtxqcc_t      CFDTXQCC1[RSCFD_CNT_CH];           /* 0x1060 */
    rscfd_cfdtxqsts_t     CFDTXQSTS1[RSCFD_CNT_CH];          /* 0x1080 */
    rscfd_cfdtxqpctr_t    CFDTXQPCTR1[RSCFD_CNT_CH];         /* 0x10A0 */
    rscfd_cfdtxqcc_t      CFDTXQCC2[RSCFD_CNT_CH];           /* 0x10C0 */
    rscfd_cfdtxqsts_t     CFDTXQSTS2[RSCFD_CNT_CH];          /* 0x10E0 */
    rscfd_cfdtxqpctr_t    CFDTXQPCTR2[RSCFD_CNT_CH];         /* 0x1100 */
    rscfd_cfdtxqcc_t      CFDTXQCC3[RSCFD_CNT_CH];           /* 0x1120 */
    rscfd_cfdtxqsts_t     CFDTXQSTS3[RSCFD_CNT_CH];          /* 0x1140 */
    rscfd_cfdtxqpctr_t    CFDTXQPCTR3[RSCFD_CNT_CH];         /* 0x1160 */
    rscfd_cfdtxqests_t    CFDTXQESTS;                        /* 0x1180 */
    rscfd_cfdtxqfists_t   CFDTXQFISTS;                       /* 0x1184 */
    rscfd_cfdtxqmsts_t    CFDTXQMSTS;                        /* 0x1188 */
    rscfd_cfdtxqowsts_t   CFDTXQOWSTS;                       /* 0x118C */
    rscfd_cfdtxqists_t    CFDTXQISTS;                        /* 0x1190 */
    rscfd_cfdtxqoftists_t CFDTXQOFTISTS;                     /* 0x1194 */
    rscfd_cfdtxqofrists_t CFDTXQOFRISTS;                     /* 0x1198 */
    rscfd_cfdtxqfsts_t    CFDTXQFSTS;                        /* 0x119C */
    const uint32          reserved11A0[24];                  /* 0x11A0 */
    rscfd_cfdthlcc_t      CFDTHLCC[RSCFD_CNT_CH];            /* TSHISTORYLIST 0x1200 */
    rscfd_cfdthlsts_t     CFDTHLSTS[RSCFD_CNT_CH];           /* 0x1220 */
    rscfd_cfdthlpctr_t    CFDTHLPCTR[RSCFD_CNT_CH];          /* 0x1240 */
    const uint32          reserved1260[40];                  /* 0x1260 */
    rscfd_cfdgtintsts_t   CFDGTINTSTS[2];                    /* GLOBAL 0x1300 */
    rscfd_cfdgtstcfg_t    CFDGTSTCFG;                        /* 0x1308 */
    rscfd_cfdgtstctr_t    CFDGTSTCTR;                        /* 0x130C */
    const uint32          reserved1310;                      /* 0x1310 */
    rscfd_cfdgfdcfg_t     CFDGFDCFG;                         /* 0x1314 */
    rscfd_cfdgcrccfg_t    CFDGCRCCFG;                        /* 0x1318 */
    rscfd_cfdglockk_t     CFDGLOCKK;                         /* 0x131C */
    const uint32          reserved1320[4];                   /* 0x1320 */
    rscfd_cfdcdtct_t      CFDCDTCT;                          /* 0x1330 */
    rscfd_cfdcdtsts_t     CFDCDTSTS;                         /* 0x1334 */
    const uint32          reserved1338[2];                   /* 0x1338 */
    rscfd_cfdcdttct_t     CFDCDTTCT;                         /* DMATRIGGER 0x1340 */
    uint32                CFDCDTTSTS;                        /* 0x1344 */
    const uint32          reserved1348[2];                   /* 0x1348 */
    rscfd_cfdgrintsts_t   CFDGRINTSTS[RSCFD_CNT_CH];         /* 0x1350 */
    const uint32          reserved1370[4];                   /* 0x1370 */
    rscfd_cfdgrstc_t      CFDGRSTC;                          /* 0x1380 */
    rscfd_cfdgfcmc_t      CFDGFCMC;                          /* 0x1384 */
    rscfd_cfdgbisc_t      CFDGBISC;                          /* 0x1388 */
    rscfd_cfdgftbac_t     CFDGFTBAC;                         /* 0x138C */
    const uint32          reserved1390[28];                  /* 0x1390 */
    rscfd_st2_regmap_t    CH2[RSCFD_CNT_CH];                 /* 0x1400 */
    const uint32          reserved1500[192];                 /* 0x1500 */
    rscfd_st3_regmap_t    RRULE[16];                         /* 0x1800 */
    const uint32          reserved1900[448];                 /* 0x1900 */
    rscfd_st4_regmap_t    RBUF[RSCFD_CNT_BUFFRX];            /* 0x2000 */
    rscfd_st5_regmap_t    RFIFO[RSCFD_CNT_FIFORX];           /* 0x6000 */
    rscfd_st6_regmap_t    TFIFO[RSCFD_CNT_FIFORXTX];         /* 0x6400 */
    const uint32          reserved7000[1024];                /* 0x7000 */
    rscfd_st8_regmap_t    THL[RSCFD_CNT_CH];                 /* 0x8000 */
    const uint32          reserved8040[240];                 /* 0x8040 */
    rscfd_cfdrpgacc_t     CFDRPGACC[64];                     /* 0x8400 */
    const uint32          reserved8500[7872];                /* 0x8500 */
    rscfd_st7_regmap_t    TBUF[RSCFD_CNT_BUFFTX];            /* 0x10000 */
    const uint32          reserved20000[573440];             /* REMOVE THIS 0x0D10 */
} rscfd_n_t;


/*##############################################################################
* Access to RSCFD Registers
##############################################################################*/

/*******************************************************************************
* #define Instantiation Option
*
* Usage: RSCFD[RSCFD_UNIT_0].REG.WORD = <value>
*        RSCFD[RSCFD_UNIT_1].REG.WORD = <value>
*
* FIXME: instantiation RSCFD willbe removed aftrer RSCFD driver is updated
*******************************************************************************/
#define RSCFD                           ((volatile rscfd_n_t *)RSCFD_ADDR_BASE)
#define RSCFD0                          ((volatile rscfd_n_t *)RSCFD_ADDR_UNIT0)
#define RSCFD1                          ((volatile rscfd_n_t *)RSCFD_ADDR_UNIT1)

#endif   /* R_RSCFD_DEV_R7F702Z19_H */


