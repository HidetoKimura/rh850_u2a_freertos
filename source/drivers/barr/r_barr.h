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
 * File Name   : r_barr.h
 * Device(s)   : RH850
 * Description : Barrier Synchronization (BARR) APIs
 ******************************************************************************/

#ifndef R_BARR_H
#define R_BARR_H

/*##############################################################################
 # dependencies
 #############################################################################*/
#include "r_barr_cfg.h"


/*##############################################################################
 # API
 #
 #   R_BARR_ClrChChks
 #   R_BARR_GetChEna
 #   R_BARR_GetChStat
 #   R_BARR_SetChEna
 #   R_BARR_SetChStat
 #   R_BARR_InitCh
 #
 #############################################################################*/

/*******************************************************************************
 * Function Name : R_BARR_ClearChStat
 * Description   : clear previous checks for requested channel
 * Arguments     : barr_ch = BARR channel
 * Return Value  : none
 ******************************************************************************/
extern void R_BARR_ClearChStat(barr_ch_t barr_ch);

/*******************************************************************************
 * Function Name : R_BARR_SetChEna
 * Description   : Enable/disable channel for requested PEs
 * Arguments     : barr_ch = BARR channel
 *               : ena_pe  = mask of PEs to enable/disable (1=participate)
 * Return Value  : none
 ******************************************************************************/
extern void R_BARR_SetChEna(barr_ch_t barr_ch, barr_ena_t ena_pe);

/*******************************************************************************
 * Function Name : R_BARR_GetChEna
 * Description   : which Processor Elements (PEs) are enabled for
 *               : a requested channel
 * Arguments     : barr_ch = BARR channel
 * Return Value  : Processor Elements enabled for requested channel
 *               : (0=does not participate)
 ******************************************************************************/
extern barr_ena_t R_BARR_GetChEna(barr_ch_t barr_ch);

/*******************************************************************************
 * Function Name : R_BARR_SetChStat
 * Description   : set synchronization complete for PE calling this API.
 * Arguments     : barr_ch = BARR channel
 * Return Value  : none
 ******************************************************************************/
extern void R_BARR_SetChStat(barr_ch_t barr_ch);

/*******************************************************************************
 * Function Name : R_BARR_GetChStat
 * Description   : return synchronization status of participating PEs
 * Arguments     : barr_ch   = BARR channel
 * Return Value  : channel sync status (0=pending)
 ******************************************************************************/
extern barr_ch_stat_t R_BARR_GetChStat(barr_ch_t barr_ch);

/*******************************************************************************
 * Function Name : R_BARR_InitCh
 * Description   : populate channels configurations
 * Arguments     : barr_cfg    = channel configurations
 *               : cfg_cnt     = number of configurations to populate
 * Return Value  : none
 ******************************************************************************/
extern void R_BARR_InitCh(const barr_cfg_ch_t barr_cfg[], uint8_t cfg_cnt);




#endif /* R_BARR_H */

