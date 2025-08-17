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
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * File Name   : r_rscfd.h
 * Device(s)   : RH850/E1x, RH850/E2x
 * Description : Include file for low level driver for RS-CAN-FD peripheral
 ******************************************************************************/

#ifndef R_RSCFD_H
#define R_RSCFD_H

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "r_types.h"
#include "r_rscfd_cfg.h"


/*##############################################################################
 # API
 #
 #  Unit
 #
 #  R_RSCFD_CheckUnitModeTrans
 #  R_RSCFD_GetUnitRamInitStat
 #  R_RSCFD_GetUnitMode
 #  R_RSCFD_SetUnitMode
 #  R_RSCFD_SetUnitClockSrc
 #  R_RSCFD_SetUnitRxRuleDlc
 #  R_RSCFD_SetUnitRxBuffSizeAndCnt
 #  R_RSCFD_InitUnitRst
 #  R_RSCFD_InitUnitOper
 #
 #  Channel
 #
 #  R_RSCFD_ClearChnlErrs
 #  R_RSCFD_CheckChnlModeTrans
 #  R_RSCFD_GetChnlMode
 #  R_RSCFD_GetChnlStatus
 #  R_RSCFD_GetChnlTxErrCnt
 #  R_RSCFD_GetChnlRxErrCnt
 #  R_RSCFD_GetChnlHistStat
 #  R_RSCFD_GetChnlHistId
 #  R_RSCFD_SetChnlHistNext
 #  R_RSCFD_SetChnlMode
 #  R_RSCFD_SetChnlNomBitrate
 #  R_RSCFD_SetChnlDataBitrate
 #  R_RSCFD_SetChnlBitrate
 #  R_RSCFD_SetChnlInterface
 #  R_RSCFD_SetChnlTxDelayComp
 #  R_RSCFD_SetChnlRxRuleCnt
 #  R_RSCFD_SetChnlTestMode
 #  R_RSCFD_SetChnlTxHistEna
 #  R_RSCFD_SetChnlErrIrq
 #  R_RSCFD_InitChnlRst
 #  R_RSCFD_InitChnlOper
 #
 #  Acceptance Filter (AFL)
 #
 #  R_RSCFD_ClearRxRules
 #  R_RSCFD_GetRxRulePage
 #  R_RSCFD_SetRxRuleWriteEn
 #  R_RSCFD_SetRxRulePage
 #  R_RSCFD_SetRxRuleId
 #  R_RSCFD_SetRxRuleIdMask
 #  R_RSCFD_SetRxRulePtr
 #  R_RSCFD_SetRxRuleLabel
 #  R_RSCFD_SetRxRuleSrc
 #  R_RSCFD_SetRxRuleMinDlc
 #  R_RSCFD_SetRxRuleDest
 #  R_RSCFD_InitRxRulesRst
 #
 #  RXFIFO
 #
 #  R_RSCFD_ClearRxFifoStat
 #  R_RSCFD_GetRxFifoMsgId
 #  R_RSCFD_GetRxFifoMsgIdType
 #  R_RSCFD_GetRxFifoMsgDlc
 #  R_RSCFD_GetRxFifoMsgPtr
 #  R_RSCFD_GetRxFifoMsgLabel
 #  R_RSCFD_GetRxFifoMsgTimestamp
 #  R_RSCFD_GetRxFifoMsgPayload
 #  R_RSCFD_GetRxFifoIrqStat
 #  R_RSCFD_GetRxFifoStat
 #  R_RSCFD_GetRxFifoMsgCnt
 #  R_RSCFD_SetRxFifoNext
 #  R_RSCFD_SetRxFifoIrq
 #  R_RSCFD_SetRxFifoSize
 #  R_RSCFD_SetRxFifoEn
 #  R_RSCFD_ReadRxFifo
 #  R_RSCFD_InitRxFifoRst
 #  R_RSCFD_InitRxFifoOper
 #
 #  TXFIFO
 #
 #  R_RSCFD_SetTxFifoMode
 #  R_RSCFD_SetTxFifoLink
 #  R_RSCFD_SetTxFifoSize
 #  R_RSCFD_SetTxFifoIrq
 #  R_RSCFD_SetTxFifoEn
 #  R_RSCFD_SetTxFifoMsgMode
 #  R_RSCFD_SetTxFifoMsgLabel
 #  R_RSCFD_SetTxFifoMsgId
 #  R_RSCFD_SetTxFifoMsgPayload
 #  R_RSCFD_SendTxFifoMsg
 #  R_RSCFD_TxByFifo
 #  R_RSCFD_InitTxFifoRst
 #  R_RSCFD_InitTxFifoOper
 #
 #  RX buffer
 #
 #  R_RSCFD_ClearRxBuffMsgNew
 #  R_RSCFD_GetRxBuffId
 #  R_RSCFD_GetRxBuffMsgNew
 #  R_RSCFD_GetRxBuffMsgId
 #  R_RSCFD_GetRxBuffMsgIdType
 #  R_RSCFD_GetRxBuffMsgDlc
 #  R_RSCFD_GetRxBuffMsgByteCnt
 #  R_RSCFD_GetRxBuffMsgPayload
 #  R_RSCFD_GetRxBuffMsgPtr
 #  R_RSCFD_GetRxBuffMsgLabel
 #  R_RSCFD_GetRxBuffMsgTimestamp
 #  R_RSCFD_ReadRxBuff
 #
 #  TX buffer
 #
 #  R_RSCFD_GetTxBuffId
 #  R_RSCFD_GetTxBuffStat
 #  R_RSCFD_SetTxBuffMsgFormat
 #  R_RSCFD_SetTxBuffMsgId
 #  R_RSCFD_SetTxBuffMsgPayload
 #  R_RSCFD_SendTxBuffMsg
 #  R_RSCFD_TxByBuff
 #
 #  Supporting
 #
 #  R_RSCFD_GetPayloadByteCnt
 #  R_RSCFD_GetPayloadWordCnt
 #  R_RSCFD_GetUnitNo
 #  R_RSCFD_GetChnlNo
 #  R_RSCFD_GetDlc
 #  R_RSCFD_TxMsg
 #  R_RSCFD_InitFifoComm
 #  R_RSCFD_InitBuffComm
 #
 #
 #############################################################################*/

/*******************************************************************************
 * Function Name  : R_RSCFD_InitUnitRst
 * Description    : RSCFD unit initializations. This API will put RSCFD units
 *                : in RESET mode.
 * Parameters     : cfg       = user configurations
 *                : cfg_cnt   = number of units to be configured
 * Returns        : none
 ******************************************************************************/
extern void R_RSCFD_InitUnitRst(const rscfd_unit_cfg_t unit_cfg[],
                                uint8 unit_cfg_cnt);

/*******************************************************************************
 * Function Name  : R_RSCFD_InitUnitOper
 * Description    : RSCFD unit initializations. This API should be called when
 *                : RSCFD units are in RESET mode. This API will put RSCFD
 *                : units in OPERATIONAL mode.
 * Parameters     : cfg       = user configurations
 *                : cfg_cnt   = number of units to be configured
 * Returns        : none
 ******************************************************************************/
extern void R_RSCFD_InitUnitOper(const rscfd_unit_cfg_t cfg[], uint8 cfg_cnt);

/*******************************************************************************
 * Function Name : R_RSCFD_InitChnlRst
 * Description   : RSCFD channel initializations. This API must be called
 *               : when RSCFD units are in reset mode. This API will put
 *               : RSCFD channels into RESET mode.
 * Parameters    : cfg       = user configurations
 *               : cfg_cnt   = number of channels to be configured
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_InitChnlRst(const rscfd_chnl_cfg_t cfg[],
                                uint8 cfg_cnt);

/*******************************************************************************
 * Function Name : R_RSCFD_InitChnlOper
 * Description   : RSCFD channel initializations. This API must be called
 *               : when RSCFD units are in OPERATING mode. This API will
 *               : switch RSCFD channels into OPERATING mode.
 * Parameters    : chnl_cfg       = user configurations
 *               : cfg_cnt        = number of channels to be configured
 *               : wait           = maximum delay for a channel transition
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_InitChnlOper(const rscfd_chnl_cfg_t chnl_cfg[],
                                 uint8 cfg_cnt);

/*******************************************************************************
 * Function Name  : R_RSCFD_InitFifoComm
 * Description    : RSCFD initialization sequence for communication by FIFOs.
 *                : This is an example of complete RSCFD initialization
 *                : sequence when using RSCFD FIFO mechanism. It can be used
 *                : as reference for creating own initialization sequences
 *                : when using RSCFD FIFOs.
 * Parameters     : cfg = user configurations of RSCFD peripheral
 * Returns        : none
 ******************************************************************************/
extern void R_RSCFD_InitFifoComm(const rscfd_fifo_cfg_t * cfg);

/*******************************************************************************
 * Function Name : R_RSCFD_InitRxRulesRst
 * Description   : Initializations RSCFD Acceptance Filter List (AFL). This
 *               : API must be called when RSCFD units are in RESET mode.
 * Parameters    : cfg          = user configurations
 *               : cfg_cnt      = number of rules to be configured
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_InitRxRulesRst(const rscfd_rx_rule_cfg_t cfg[],
                                   uint8 cfg_cnt);

/*******************************************************************************
 * Function Name : R_RSCFD_InitRxFifoRst
 * Description   : Initializations of RXFIFOs. This API must be called
 *               : when RSCFD units are in RESET mode.
 * Parameters    : cfg          = user RX FIFO configurations
 *               : cfg_cnt      = number of RX FIFOs to configure
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_InitRxFifoRst(const rscfd_rx_fifo_cfg_t cfg[],
                                  uint8 cfg_cnt);

/*******************************************************************************
 * Function Name : R_RSCFD_InitRxFifoOper
 * Description   : Initializations of RXFIFOs. This API must be called when
 *               : RSCFD units are in OPERATIONAL mode.
 * Parameters    : cfg           = configuration of RX FIFOs
 *               : cfg_cnt       = number of RX FIFOs to be configured
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_InitRxFifoOper(const rscfd_rx_fifo_cfg_t cfg[],
                                   uint8 cfg_cnt);

/*******************************************************************************
 * Function Name : R_RSCFD_InitTxFifoRst
 * Description   : Initializations of TXFIFOs. This API must be called when
 *               : RSCFD units are in RESET mode.
 * Parameters    : cfg         = user TX FIFO configurations
 *               : cfg_cnt     = number of TX FIFO to be configured
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_InitTxFifoRst(const rscfd_tx_fifo_cfg_t cfg[],
                                  uint8 cfg_cnt);

/*******************************************************************************
 * Function Name : R_RSCFD_InitTxFifoOper
 * Description   : Initializations of Transmit FIFOs for specified
 *               : These initializations require the UNIT be in operating mode.
 * Parameters    : unit            = CAN unit being configured.
 *               : tx_fifo_cfg     = user configurations
 *               : tx_fifo_cfg_cnt = number of tx fifos to be configured
 * Returns       : none
 * Note          : CAN unit must be in OPERATING mode
 *               : (see R_RSCFD_SetUnitMode).
 ******************************************************************************/
extern void R_RSCFD_InitTxFifoOper(const rscfd_tx_fifo_cfg_t cfg[],
                                   uint8 cnt);

/*******************************************************************************
 * Function Name : R_RSCFD_GetUnitRamInitStat
 * Description   : Return CAN RAM Initialization status. CAN RAM is
 *               : automatically initialized by hardware after reset.
 * Parameters    : unit = RSCFD unit number being configured.
 * Returns       : 0           = complete
 *               : otherwise   = ongoing
 ******************************************************************************/
extern rscfd_ram_init_t R_RSCFD_GetUnitRamInitStat(rscfd_unit_t unit);

/*******************************************************************************
 * Function Name : R_RSCFD_SetUnitClockSrc
 * Description   : Selects RSCFD unit clock source.
 * Parameters    : unit      = CAN unit being configured.
 *               : clock_src = Enum defining clkc (LSB) or clk_xincan (OSC)
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetUnitClockSrc(rscfd_unit_t unit,
                                    rscfd_clock_src_t clock_src);

/*******************************************************************************
 * Function Name : R_RSCFD_SetUnitRxRuleDlc
 * Description   : Enables/disables use of DLC check in acceptance filtering.
 * Parameters    : unit = CAN unit being configured.
 *               : dce  = Enum defining DCE bit setting (DLC Check Enable)
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetUnitRxRuleDlc(rscfd_unit_t unit, rscfd_dlc_check_t dce);

/*******************************************************************************
 * Function Name : R_RSCFD_GetUnitMode
 * Description   : Get CAN unit's operating mode.
 * Parameters    : unit = the CAN unit being interrogated.
 * Returns       : Global mode per enumeration
 * *****************************************************************************/
extern rscfd_glbl_mode_t R_RSCFD_GetUnitMode(rscfd_unit_t unit);

/*******************************************************************************
 * Function Name : R_RSCFD_SetUnitMode
 * Description   : Set the CAN peripheral's Global Mode using RSCFDnCFDGCTR
 *               : (Global Control Register) bit fields GSLPR and GMDC.
 *               : See "Global Modes" state diagram in hardware user manual.
 *               : If unsupported transition is requested (STOP -> OPERATING,
 *               : OPERATING -> STOP, TEST -> STOP, STOP -> TEST) the unit will
 *               : be put in RESET mode.
 * Parameters    : unit = the CAN unit being configured.
 *               : req  = global mode to be entered.
 * Returns       : none
 * Caution       : requesting RESET mode resets some CAN register bit fields.
 ******************************************************************************/
extern void R_RSCFD_SetUnitMode(rscfd_unit_t unit,
                                rscfd_glbl_mode_t mode_req);

/*******************************************************************************
 * Function Name : R_RSCFD_GetChnlMode
 * Description   : Get RSCFD channel mode. Reads register CmSTS bit fields
 *               : CSLPSTS, CHLTSTS, CRSTSTS.
 * Parameters    : rscfd_chnl      = CAN channel enumeration (includes unit)
 * Returns       : channel mode
 ******************************************************************************/
extern rscfd_chnl_mode_t R_RSCFD_GetChnlMode(rscfd_chnl_t rscfd_chnl);

/*******************************************************************************
 * Function Name : R_RSCFD_CheckUnitModeTrans
 * Description   : Check if direct transition of global mode possible. Direct
 *               : transitions supported if starting from RESET mode
 *               : or going to a RESET mode. Also for transitions between TEST
 *               : and OPERATING modes. Otherwise the first transition
 *               : must be to RESET mode
 * Parameters    : from      = current RSCFD channel mode
 *               : to        = requested RSCFD channel mode.
 * Returns       : whether direct transition supported
 ******************************************************************************/
extern rscfd_mode_trans_t R_RSCFD_CheckUnitModeTrans(rscfd_glbl_mode_t from,
                                                     rscfd_glbl_mode_t to);

/*******************************************************************************
 * Function Name : R_RSCFD_CheckChnlModeTrans
 * Description   : Check if requested transition of channel mode is supported.
 *               : Transitions starting from or to RESET mode are supported.
 *               : Also transitions between HALT and COMMUNICATION modes are
 *               : supported. See "Channel Modes" state diagram in HW U/M.
 * Parameters    : org        = current RSCFD channel mode
 *               : req        = requested RSCFD channel mode.
 * Returns       : whether direct transition supported
 ******************************************************************************/
extern rscfd_mode_trans_t R_RSCFD_CheckChnlModeTrans(rscfd_chnl_mode_t org,
                                                     rscfd_chnl_mode_t req);

/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlMode
 * Description   : Set Channel Mode. See "Channel Modes" state diagram in HW U/M
 *               : Unsupported transition requests are ignored. Updates
 *               : register CmCTR bit fields CSLPR and CHMDC.
 * Parameters    : rscfd_chnl       = RSCFD unit and channel
 *               : mode_req         = channel mode.
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetChnlMode(rscfd_chnl_t rscfd_chnl, rscfd_chnl_mode_t req);

/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlTestMode
 * Description   : Set Channel Test Mode.
 * Parameters    : chnl      = CAN channel enumeration (includes unit).
 *               : test_mode = enumeration of test modes
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetChnlTestMode(rscfd_chnl_t rscfd_chnl,
                                    rscfd_chnl_test_t test_mode);

/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlTxHistEna
 * Description   : Set use of channel's Tx history buffer to Enabled or Disabled.
 * Parameters    : rscfd_chnl = CAN channel enumeration (includes unit).
 *               : hist_en    = enumeration to enable/disable history buffer.
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetChnlTxHistEna(rscfd_chnl_t rscfd_chnl,
                                     rscfd_chnl_hist_en_t hist_en);

/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlErrIrq
 * Description   : Enable/disable channel error interrupts
 *               : Configure in register CmCTR bit field BEIE.
 * Parameters    : rscfd_chnl = CAN channel enumeration (includes unit).
 *               : err_irq_en = enumeration to enable/disable error interrupt.
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetChnlErrIrq(rscfd_chnl_t rscfd_chnl,
                                  rscfd_chnl_err_irq_t err_irq_en);

/*******************************************************************************
 * Function Name : R_RSCFD_GetChnlTxErrCnt
 * Description   : Return number of channel transmit errors
 * Parameters    : rscfd_chnl    = RSCFD unit and channel
 * Returns       : number of channel transmit errors
 ******************************************************************************/
extern uint8 R_RSCFD_GetChnlTxErrCnt(rscfd_chnl_t rscfd_chnl);

/*******************************************************************************
 * Function Name : R_RSCFD_GetChnlRxErrCnt
 * Description   : Return number of channel receive  errors
 * Parameters    : rscfd_chnl    = RSCFD unit and channel
 * Returns       : number of channel transmit errors
 ******************************************************************************/
extern uint8 R_RSCFD_GetChnlRxErrCnt(rscfd_chnl_t rscfd_chnl);

/*******************************************************************************
 * Function Name : R_RSCFD_GetChnlStatus
 * Description   : Get CAN channel status - Entire register with no formatting.
 * Parameters    : rscfd_chnl = CAN channel enumeration (includes unit).
 * Returns       : Channel Status Register (RSCFDnCFDCmSTS).
 * Note          : No usage at time of writing.
 ******************************************************************************/
extern rscfd_chnl_stat_t R_RSCFD_GetChnlStatus(rscfd_chnl_t rscfd_chnl);

/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlBitrate
 * Description   : Helper function to simplify setting channel bit rate.
 *               : Configures both Nominal bit rate (the slower bit rate used
 *               : at the beginning of the CAN FD frame) and Data bit rate (the
 *               : faster bit rate used for the pay load of the CAN FD frame)
 * Parameters    : rscfd_chnl        = CAN channel enumeration (includes unit).
 *               : nom_rate          = enumeration of nominal bit rate
 *               : data_rate         = enumeration of data bit rate
 * Returns       : None
 ******************************************************************************/
extern void R_RSCFD_SetChnlBitrate(rscfd_chnl_t chnl,
                                   rscfd_chnl_nbr_t nom_rate,
                                   rscfd_chnl_dbr_t data_rate);

/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlNomBitrate
 * Description   : Set CAN Channel Nominal bit rate (the slower bit rate
 *               : used at the beginning of the CAN FD frame). Nominal BRP
 *               : must match data BRP
 * Parameters    : rscfd_chnl = RSCFD unit and channel
 *               : btr        = nominal bit rate to set
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetChnlNomBitrate(rscfd_chnl_t rscfd_chnl,
                                      rscfd_chnl_nbr_t btr);

/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlDataBitrate
 * Description   : Set CAN Channel Data bit rate (the faster bit rate
 *               : used for the payload of the CAN FD frame)
 * Parameters    : chnl       = CAN channel enumeration (includes unit).
 *               : btr        = data bit rate to set
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetChnlDataBitrate(rscfd_chnl_t rscfd_chnl,
                                       rscfd_chnl_dbr_t btr);

/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlInterface
 * Description   : Set classical or CANRD CAN interface
 *               : Configure in register FDCFG bit field CLOE and FDOE.
 *               : FDCFG is in register structure CH2.
 * Parameters    : rscfd_chnl = RSCFD unit and channel
 *               : chnl_intf  = Channel interface
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetChnlInterface(rscfd_chnl_t rscfd_chnl,
                                     rscfd_chnl_interf_t chnl_interf);

/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlTxDelayComp
 * Description   : Configure channel Transmitter Delay Compensation.
 *               : Configure in register FDCFG bit field TDCE, TDCOC and TDCO.
 *               : FDCFG is in register structure CH2.
 * Parameters    : rscfd_chnl  = RSCFD unit and channel
 *               : comp_cfg    = Channel tx delay compensation configuration
 *               : comp_ofst   = channel compensation offset
 * Returns       : none
 * Notes         : Not used by the driver.
 ******************************************************************************/
extern void R_RSCFD_SetChnlTxDelayComp(rscfd_chnl_t rscfd_chnl,
                                       rscfd_chnl_comp_t comp_cfg,
                                       uint8 comp_ofst);

/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlRxRuleCnt
 * Description   : Set number of receive Acceptance Filters used by requested
 *               : channel. Configure in register GAFLCFG0 bit field RNCx.
 * Parameters    : rscfd_chnl = CAN channel enumeration
 *               : num_rules  = Number of receive rules (0-384)
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetChnlRxRuleCnt(rscfd_chnl_t rscfd_chnl,
                                     uint16 num_rules);

/*******************************************************************************
 * Function Name : R_RSCFD_ClearRxRules
 * Description   : Resets Acceptance Filter counts and destinations. RSCFD units
 *               : must be in RESET mode before calling this API
 * Parameters    : unit         = CAN unit being modified
 *               : rx_rules_cnt = number of receive rules being to be used.
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_ClearRxRules(rscfd_unit_t unit, uint8 rx_rules_cnt);

/*******************************************************************************
 * Function Name : R_RSCFD_SetRxRuleWriteEn
 * Description   : Enable writes to Acceptance Filter List (AFL)
 *               : Register GAFLECTR bit field AFLDAE.
 * Parameters    : unit  = CAN unit being configured.
 *               : wr_en = Write Enable (1) or Disable (0)
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetRxRuleWriteEn(rscfd_unit_t unit,
                                     rscfd_rx_rule_wr_t wr_en);

/*******************************************************************************
 * Function Name : R_RSCFD_SetRxRulePage
 * Description   : Select Acceptance Filter page. Up to 16 Acceptance Filters
 *               : can be configured per page. Modifies register GAFLECTR
 *               : bit field AFLPN.
 * Parameters    : unit = CAN unit being configured.
 *               : page = enumeration of Page number
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetRxRulePage(rscfd_unit_t unit, rscfd_rx_page_t page);

/*******************************************************************************
 * Function Name : R_RSCFD_SetRxRuleId
 * Description   : Set message ID type rule (STD/EXT, NORM/RTR) for requested
 *               : Acceptance Filter. Incoming messages are filtered depending
 *               : on this rule and selected ID mask.
 * Parameters    : unit       = CAN unit being configured.
 *               : rule_num   = enumeration of Rule Number within page (0-15)
 *               : rx_id      = receive rule's message ID
 *               : id_type    = receive rule's message ID type
 * Returns       : none
 * Note          : This API must be called when RSCFD units are in RESET mode
 *               : and writing to Acceptance Filter List is enabled.
 ******************************************************************************/
extern void R_RSCFD_SetRxRuleId(rscfd_unit_t unit,
                                rscfd_rx_rule_t rule_num,
                                uint32 rx_id,
                                rscfd_id_type_t id_type);

/*******************************************************************************
 * Function Name : R_RSCFD_SetRxRuleIdMask
 * Description   : Set message ID mask for requested Acceptance Filter.
 *               : Only bits set to one are evaluated by Acceptance Filter.
 *               : Register GAFLMj bit field GAFLIDM.
 * Parameters    : unit        = CAN unit being configured.
 *               : rule_num      = enumeration of Rule Number (0-15)
 *               : mask_id       = mask for ID matching
 *               : mask_id_type  = rule for standard/extended CAN ID
 * Returns       : none
 * Note          : This API must be called when RSCFD units are in RESET mode
 *               : and writing to Acceptance Filter List is enabled.
 ******************************************************************************/
extern void R_RSCFD_SetRxRuleIdMask(rscfd_unit_t unit,
                                    rscfd_rx_rule_t rule_num,
                                    uint32 mask_id,
                                    rscfd_rx_id_type_mask_t mask_id_type);

/*******************************************************************************
 * Function Name : R_RSCFD_SetRxRulePtr
 * Description   : Set the pointer for requested Acceptance Filter. The pointer
 *               : is populated along with messages accepted by this rule. This
 *               : API must be called when RSCFD units are in RESET mode
 *               : and writing to Acceptance Filter List is enabled.
 *               : Modifies register GAFLP0j bit field GAFLPTR.
 * Parameters    : unit     = CAN unit being configured.
 *               : rule_num = enumeration of Rule Number (0-15)
 *               : rx_ptr   = pointer
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetRxRulePtr(rscfd_unit_t unit,
                                 rscfd_rx_rule_t rule_num,
                                 uint16 rx_ptr);

/*******************************************************************************
 * Function Name : R_RSCFD_SetRxRuleLabel
 * Description   : Set the message label for requested Acceptance Filter.
 *               : The label is populated along with messages accepted by
 *               : this rule. This API must be called when RSCFD units are
 *               : in RESET mode and writing to Acceptance Filter List is
 *               : enabled. Modifies register GAFLP0j bit field GAFLPTR.
 * Parameters    : unit     = CAN unit being configured.
 *               : rule_num = enumeration of Rule Number (0-15)
 *               : rx_ptr   = pointer
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetRxRuleLabel(rscfd_unit_t unit,
                                   rscfd_rx_rule_t rule_num,
                                   rscfd_label_t rx_label);

/*******************************************************************************
 * Function Name : R_RSCFD_SetRxRuleSrc
 * Description   : Set message source for requested Acceptance Filter. The
 *               : message source can be the same channel (loopback mode) or
 *               : any other node on the network. Modifies register
 *               : GAFLIDj bit field GAFLLB.
 * Parameters    : unit     = CAN unit being configured.
 *               : rule_num = enumeration of Rule Number (0-15)
 *               : source   = enumeration of receive rule message source
 * Returns       : none
 * Note          : This API must be called when RSCFD units are in RESET mode
 *               : and writing to Acceptance Filter List is enabled.
 ******************************************************************************/
extern void R_RSCFD_SetRxRuleSrc(rscfd_unit_t unit,
                                 rscfd_rx_rule_t rule_num,
                                 rscfd_rx_src_t source);

/*******************************************************************************
 * Function Name : R_RSCFD_SetRxRuleMinDlc
 * Description   : Set minimum message payload size (DLC) to pass requested
 *               : Acceptance Filter. Modifies GAFLP0 bit field GAFLDLC.
 * Parameters    : unit           = CAN unit being configured.
 *               : rule_num       = Rule Number (0-15)
 *               : min_dlc        = minimum DLC to accept
 * Returns       : none
 * Note          : This API must be called when RSCFD units are in RESET mode
 *               : and writing to Acceptance Filter List is enabled.
 ******************************************************************************/
extern void R_RSCFD_SetRxRuleMinDlc(rscfd_unit_t unit,
                                    rscfd_rx_rule_t rule_num,
                                    rscfd_dlc_t min_dlc);

/*******************************************************************************
 * Function Name : R_RSCFD_SetRxRuleDest
 * Description   : configure message destination based on receive rule
 * Parameters    : unit      = CAN unit being configured.
 *               : rule_num  = enumeration of Rule Number (0-15).
 *               : rule_dst  = which Rx FIFO or buffer will receive message
 * Returns       : none
 * Note          : Requires that Rx Rule Table Writes are enabled
 ******************************************************************************/
extern void R_RSCFD_SetRxRuleDest(rscfd_unit_t unit,
                                  rscfd_rx_rule_t rule_num,
                                  rscfd_rx_dst_t rule_dst);

/*******************************************************************************
 * Function Name : R_RSCFD_SetRxFifoIrq
 * Description   : Select message RX FIFO interrupt trigger (none, on every
 *               : message, when RXFIFO filled up to configured level)
 * Parameters    : fifo_num    = RSCFD unit and FIFO (0-7)
 *               : irq         = interrupt configuration
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetRxFifoIrq(rscfd_rx_fifo_t fifo_num,
                                 rscfd_rx_fifo_int_t irq);

/*******************************************************************************
 * Function Name : R_RSCFD_SetRxFifoSize
 * Description   : Set depth of RXFIFO. Modifies register RFCCx
 *               : bit fields RFDC and RFPLS.
 * Parameters    : fifo_num     = RSCFD unit and RX FIFO (0-7)
 *               : depth        = Rx FIFO buffer depth (0-128)
 *               : payload_size = Rx FIFO buffer data size (8-64)
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetRxFifoSize(rscfd_rx_fifo_t fifo_num,
                                  rscfd_rfdc_t depth,
                                  rscfd_fpls_t payload_size);

/*******************************************************************************
 * Function Name : R_RSCFD_SetRxFifoEn
 * Description   : Enable/Disable use of requested RXFIFO.
 *               : Modifies register RFCCx bit field RFE.
 * Parameters    : fifo_num       = RSCFD unit and Rx FIFO number (0-7)
 *               : enabled        = RFE bit setting (enabled/disabled)
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetRxFifoEn(rscfd_rx_fifo_t fifo_num,
                                rscfd_fifo_en_t enable);

/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoMode
 * Description   : Set RX/TX FIFO to RX, TX, or Gateway Mode.
 *               : Modifies register CFCCx bit field CFM.
 * Parameters    : fifo_num       = RSCFD unit and FIFO
 *               : fifo_mode      = FIFO mode (RX, TX, or Gateway)
 * Returns       : none
 * Note          : Driver uses only RSCFD_RXTX_FIFO_TX mode
 ******************************************************************************/
extern void R_RSCFD_SetTxFifoMode(rscfd_tx_fifo_t fifo_num,
                                  rscfd_rxtx_fifo_mode_t fifo_mode);

/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoLink
 * Description   : Set RX/TX FIFO link to tx buffer. This assigns the TX FIFO
 *               : the priority of the linked TX buffer in the transmit
 *               : priority determination scheme used by TX Buffers.
 *               : Register CFCCx bit field CFTML.
 * Parameters    : fifo_num      = unit and FIFO number
 *               : buf_num       = TX buffer linked to TX FIFO
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetTxFifoLink(rscfd_tx_fifo_t fifo_num,
                                  rscfd_tx_fifo_buff_t buf_fifo);

/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoSize
 * Description   : Set depth of requested TXFIFO. Modifies register CFCCx
 *               : bit fields CFDC and CFPLS.
 * Parameters    : fifo_num     = unit and TX FIFO number
 *               : fifo_depth   = Tx FIFO buffer depth
 *               : payload_size = Tx FIFO buffer length
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetTxFifoSize(rscfd_tx_fifo_t fifo_num,
                                  rscfd_cfdc_t fifo_depth,
                                  rscfd_fpls_t payload_size);

/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoIrq
 * Description   : Select message interrupt trigger (none, on every message,
 *               : when TXFIFO becomes empty) for a requested TXFIFO
 *               : (transmission)
 * Parameters    : fifo_num     = RSCFD unit and FIFO
 *               : tx_fifo_int  = interrupt configuration
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetTxFifoIrq(rscfd_tx_fifo_t fifo_num,
                                 rscfd_tx_fifo_int_t tx_fifo_int);

/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoEn
 * Description   : Enable/disable requested TXFIFO
 *               : Modifies register CFCCx bit field CFE.
 * Parameters    : fifo_num   = RSCFD unit and TX FIFO (0-14)
 *               : enable     = enumeration of CFE bit (1=enabled)
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetTxFifoEn(rscfd_tx_fifo_t fifo_num,
                                rscfd_fifo_en_t enable);

/*******************************************************************************
 * Function Name : R_RSCFD_SetUnitRxBuffSizeAndCnt
 * Description   : Configure size and number of RX buffers per RSCFD unit.
 *               : Modifies register CFDRMNB bit field RMPLS and NRXMB.
 * Parameters    : unit = CAN unit being configured.
 *               : size = enumeration of RX buffer payload size.
 *               : cnt  = enumeration of RX buffers in the unit.
 * Returns       : none
 * Note          : CAN unit must be in Global Reset mode
 ******************************************************************************/
extern void R_RSCFD_SetUnitRxBuffSizeAndCnt(rscfd_unit_t unit,
                                            rscfd_rx_buff_size_t size,
                                            rscfd_rx_buff_cnt_t cnt);

/*******************************************************************************
 * Function Name : R_RSCFD_SetTxBuffMsgFormat
 * Description   : Configure TX buffer message type and payload speed
 * Parameters    : tx_buff       = RSCFD unit and TX buffer
 *               : rscfd_type    = message type and Speed
 *               : buff_ptr      = message buffer pointer
 *               : buff_label    = message label
 * Returns       : none
 * Note          : do not call when corresponding channel in STOP mode
 ******************************************************************************/
extern void R_RSCFD_SetTxBuffMsgFormat(rscfd_tx_buff_t tx_buff,
                                       rscfd_msg_mode_t rscfd_type,
                                       uint16 buff_ptr,
                                       rscfd_label_t buff_lbl);

/*******************************************************************************
 * Function Name : R_RSCFD_SetTxBuffMsgId
 * Description   : Configure message ID type (STD/EXT, NORM/RTR) for requested
 *               : TX buffer and enable entry into the history list.
 * Parameters    : tx_buff       = RSCFD unit and TX buffer
 *               : msg_id        = message ID to be transmitted
 *               : tmide         = ID size standard/extended
 * Returns       : none
 * Note          : do not call when corresponding channel in STOP mode
 ******************************************************************************/
extern void R_RSCFD_SetTxBuffMsgId(rscfd_tx_buff_t tx_buff,
                                   rscfd_id_type_t id_type,
                                   uint32 msg_id);

/*******************************************************************************
 * Function Name : R_RSCFD_SetTxBuffMsgPayload
 * Description   : Copy message payload to TX buffer and set DLC
 * Parameters    : tx_buff       = RSCFD unit and TX buffer
 *               : msg_bytes     = number of bytes in the message payload
 *               : msg_payload   = message payload buffer
 * Returns       : none
 * Note          : do not call when corresponding channel in STOP mode
 ******************************************************************************/
extern void R_RSCFD_SetTxBuffMsgPayload(rscfd_tx_buff_t tx_buff,
                                        rscfd_payload_size_t msg_bytes,
                                        const rscfd_payload_t msg_payload[]);

/*******************************************************************************
 * Function Name : R_RSCFD_GetTxBuffStat
 * Description   : Return status of TX buffer
 * Parameters    : tx_buff       = RSCFD unit and TX buffer
 * Returns       : status of requested TX buffer
 ******************************************************************************/
extern rscfd_tx_buff_stat_t R_RSCFD_GetTxBuffStat(rscfd_tx_buff_t tx_buff);

/*******************************************************************************
 * Function Name : R_RSCFD_SendTxBuffMsg
 * Description   : Trigger transmission of CAN message currently in the buffer
 *               : This API will clears transmit result status flag TMTRF
 * Parameters    : tx_buff       = RSCFD unit and TX buffer
 *               : buff_dlc      = message length
 *               : buff_data     = buffer data
 * Returns       : none
 * Note          : do not call when corresponding channel in STOP mode
 ******************************************************************************/
extern void R_RSCFD_SendTxBuffMsg(rscfd_tx_buff_t tx_buff);

/*******************************************************************************
 * Function Name : R_RSCFD_TxByBuff
 * Description   : Example of sequence to send a message using TX buffer
 * Parameters    : tx_buff       = RSCFD unit and TX buffer
 *               : rscfd_type    = message type (classic/FD) and payload speed
 *               : msg           = message definition
 * Returns       : status of requested TX buffer before transmission
 ******************************************************************************/
extern rscfd_tx_buff_stat_t R_RSCFD_TxByBuff(rscfd_tx_buff_t tx_buff,
                                             rscfd_msg_mode_t rscfd_type,
                                             rscfd_msg_t * msg);

/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoMsgMode
 * Description   : Select TXFIFO mode and speed (classical, FD slow/fast)
 * Parameters    : tx_fifo     = RSCFD unit and TX FIFO
 *               : rscfd_type  = message type and payload speed
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetTxFifoMsgMode(rscfd_tx_fifo_t tx_fifo,
                                     rscfd_msg_mode_t rscfd_type);

/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoMsgLabel
 * Description   : Select TXFIFO message label that will be appended to messages
 *               : transmitted using this TXFIFO
 * Parameters    : tx_fifo     = RSCFD unit and TX FIFO
 *               : label       = message label to store w/ message
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetTxFifoMsgLabel(rscfd_tx_fifo_t tx_fifo,
                                      rscfd_label_t label);

/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoMsgId
 * Description   : Configure message ID type in requested TXFIFO
 *               : and enable entry to the TX history list.
 * Parameters    : tx_fifo     = RSCFD unit and TX FIFO
 *               : id_type     = type of message ID (STD/EXT, NORM/RTR)
 *               : msg_id      = message ID to use
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetTxFifoMsgId(rscfd_tx_fifo_t tx_fifo,
                                   rscfd_id_type_t id_type,
                                   uint32 msg_id);

/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoMsgPayload
 * Description   : Copy message payload into requested TXFIFO
 * Parameters    : tx_fifo     = RSCFD unit and TXFIFO
 *               : bytes       = number of bytes in the payload
 *               : payload     = message payload to populate
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetTxFifoMsgPayload(rscfd_tx_fifo_t tx_fifo,
                                        rscfd_payload_size_t bytes,
                                        rscfd_payload_t * payload);

/*******************************************************************************
 * Function Name : R_RSCFD_SendTxFifoMsg
 * Description   : Trigger transmission of requested Tx FIFO
 * Parameters    : tx_fifo     = RSCFD unit and TX FIFO
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SendTxFifoMsg(rscfd_tx_fifo_t tx_fifo);

/*******************************************************************************
 * Function Name : R_RSCFD_TxByFifo
 * Description   : Example API of complete TXFIFO transmit sequence using
 *               : driver APIs.
 * Parameters    : tx_fifo     = RSCFD unit and TX FIFO
 *               : rscfd_type  = message type (classic/FD) and payload speed
 *               : msg         = message definition
 * Returns       : status of TXFIFO before sending requested message
 ******************************************************************************/
extern rscfd_tx_fifo_stat_t R_RSCFD_TxByFifo(rscfd_tx_fifo_t tx_fifo,
                                             rscfd_msg_mode_t rscfd_type,
                                             rscfd_msg_t * msg);

/*******************************************************************************
 * Function Name : R_RSCFD_TxMsg
 * Description   : Example of transmit sequence using either TXFIFO or TX buffer
 * Parameters    : tx_dst     = how to send (TX FIFO/TX buffer)
 *               : type       = message type (classic/FD) and payload speed
 *               : msg        = message information to send
 * Returns       : status of the request
 *               : NOFAULT    = message was sent successfully
 *               : FULL       = TXFIFO was full
 *               : BUSY       = TX buffer was busy
 ******************************************************************************/
extern rscfd_result_t R_RSCFD_TxMsg(rscfd_tx_dst_t tx_dst,
                                    rscfd_msg_mode_t type,
                                    rscfd_msg_t * msg);

/*******************************************************************************
 * Function Name : R_RSCFD_GetChnlHistStat
 * Description   : return status of channel TX history list
 * Parameters    : rscfd_chnl  = RSCFD unit and channel
 * Returns       : status of channel TX history list
 ******************************************************************************/
extern rscfd_hist_stat_t R_RSCFD_GetChnlHistStat(rscfd_chnl_t rscfd_chnl);

/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlHistNext
 * Description   : Set pointer to next element in channel TX history list
 * Parameters    : rscfd_chnl  = RSCFD unit and channel
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetChnlHistNext(rscfd_chnl_t rscfd_chnl);

/*******************************************************************************
 * Function Name : R_RSCFD_GetHistId
 * Description   : Get transmit ID from the current channel TX history pointer
 * Parameters    : rscfd_chnl  = RSCFD unit and channel
 * Returns       : transmit ID from channel TX history list
 ******************************************************************************/
extern uint16 R_RSCFD_GetChnlHistId(rscfd_chnl_t rscfd_chnl);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgId
 * Description   : return message ID in requested RXFIFO
 * Parameters    : rx_fifo     = RSCFD unit and RXFIFO
 * Returns       : message ID in requested RXFIFO
 ******************************************************************************/
extern uint32 R_RSCFD_GetRxFifoMsgId(rscfd_rx_fifo_t rx_fifo);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgIdType
 * Description   : return message ID type (DTS/EXT, NORM/RTR) in requested
 *               ; RXFIFO
 * Parameters    : rx_fifo     = RSCFD unit and RXFIFO
 * Returns       : message IDE size in requested RXFIFO
 ******************************************************************************/
extern rscfd_id_type_t R_RSCFD_GetRxFifoMsgIdType(rscfd_rx_fifo_t rx_fifo);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgDlc
 * Description   : return message DLC in requested RXFIFO
 * Parameters    : rx_fifo     = RSCFD unit and RXFIFO
 * Returns       : message DLC in requested RXFIFO
 ******************************************************************************/
extern rscfd_dlc_t R_RSCFD_GetRxFifoMsgDlc(rscfd_rx_fifo_t rx_fifo);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgPtr
 * Description   : return message pointer in requested RXFIFO
 * Parameters    : rx_fifo     = RSCFD unit and RXFIFO
 * Returns       : message pointer in requested RXFIFO
 ******************************************************************************/
extern uint16 R_RSCFD_GetRxFifoMsgPtr(rscfd_rx_fifo_t rx_fifo);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgLabel
 * Description   : return message label in requested RX FIFO
 * Parameters    : rx_fifo     = RSCFD unit and RX FIFO
 * Returns       : message label in requested RXFIFO
 ******************************************************************************/
extern rscfd_label_t R_RSCFD_GetRxFifoMsgLabel(rscfd_rx_fifo_t rx_fifo);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgTimestamp
 * Description   : return message time stamp in requested RXFIFO
 * Parameters    : rx_fifo     = RSCFD unit and RXFIFO
 * Returns       : message time stamp in requested RXFIFO
 ******************************************************************************/
extern uint16 R_RSCFD_GetRxFifoMsgTimestamp(rscfd_rx_fifo_t rx_fifo);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgPayload
 * Description   : return message payload in requested RXFIFO
 * Parameters    : rx_fifo     = RSCFD unit and RX FIFO
 *               : payload     = buffer to copy message data to
 * Returns       : number of bytes in message payload
 ******************************************************************************/
extern rscfd_payload_size_t R_RSCFD_GetRxFifoMsgPayload(
    rscfd_rx_fifo_t rx_fifo,
    rscfd_payload_t * payload);

/*******************************************************************************
 * Function Name : R_RSCFD_SetRxFifoNext
 * Description   : move RX FIFO pointer to next unread message
 * Parameters    : rx_fifo     = RSCFD unit and RX FIFO
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_SetRxFifoNext(rscfd_rx_fifo_t rx_fifo);

/*******************************************************************************
 * Function Name : R_RSCFD_ReadRxFifo
 * Description   : Example of reading complete RXFIFO using driver APIs. If
 *               : RXFIFO is not empty beside reading the message this API
 *               : will also move RXFIFO pointer to next unread message
 * Parameters    : rx_fifo     = RSCFD unit and RX FIFO
 *               : msg         = structure to store message
 * Returns       : RXFIFO status prior to reading the message
 ******************************************************************************/
extern rscfd_rx_fifo_stat_t R_RSCFD_ReadRxFifo(rscfd_rx_fifo_t rx_fifo,
                                               rscfd_msg_t * msg);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgNew
 * Description   : Check if new message is available in requested RX buffer
 * Parameters    : rx_buff     = RSCFD unit and RX buffer
 * Returns       : 0         = no new data
 *               : otherwise = new data
 ******************************************************************************/
extern uint8 R_RSCFD_GetRxBuffMsgNew(rscfd_rx_buff_t rx_buff);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgId
 * Description   : Return ID of message in requested RX buffer
 * Parameters    : rx_buff     = RSCFD unit and RX buffer
 * Returns       : ID of received message
 *               : otherwise   = new message in the RX buffer
 ******************************************************************************/
extern uint32 R_RSCFD_GetRxBuffMsgId(rscfd_rx_buff_t rx_buff);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgIdType
 * Description   : Return type of message ID (STD/EXT, NORM/RTR) in requested
 *               : RX buffer
 * Parameters    : rx_buff     = RSCFD unit and RX buffer
 * Returns       : message ID type
 ******************************************************************************/
extern rscfd_id_type_t R_RSCFD_GetRxBuffMsgIdType(rscfd_rx_buff_t rx_buff);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgDlc
 * Description   : Return message DLC for requested RX buffer
 * Parameters    : rx_buff     = RSCFD unit and RX buffer
 * Returns       : message DLC in requested RX buffer
 *****************************************************************************/
extern rscfd_dlc_t R_RSCFD_GetRxBuffMsgDlc(rscfd_rx_buff_t rx_buff);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgByteCnt
 * Description   : Example of reading message payload byte count from
 *               : requested RX buffer.
 * Parameters    : rx_buff     = RSCFD unit and buffer
 * Returns       : message payload byte count
 *****************************************************************************/
extern rscfd_payload_size_t R_RSCFD_GetRxBuffMsgByteCnt(rscfd_rx_buff_t rx_buff);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgPtr
 * Description   : Return message pointer from requested RX buffer
 * Parameters    : rx_buff     = RSCFD unit and buffer
 * Returns       : message pointer in requested RX buffer
 ******************************************************************************/
extern uint16 R_RSCFD_GetRxBuffMsgPtr(rscfd_rx_buff_t rx_buff);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgLabel
 * Description   : Return message label from requested RX buffer
 * Parameters    : rx_buff     = RSCFD unit and buffer
 * Returns       : label of received message
 ******************************************************************************/
extern rscfd_label_t R_RSCFD_GetRxBuffMsgLabel(rscfd_rx_buff_t rx_buff);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgTimestamp
 * Description   : Return time stamp of message in requested RX buffer
 * Parameters    : rx_buff     = RSCFD unit and buffer
 * Returns       : time stamp of message in requested RX buffer
 ******************************************************************************/
extern uint16 R_RSCFD_GetRxBuffMsgTimestamp(rscfd_rx_buff_t rx_buff);

/*******************************************************************************
 * Function Name : GetRxBuffMsgPayload
 * Description   : Copy data from requested Rx buffer to specified  memory and
 *               : return number of copied bytes.
 * Parameters    : rx_buff     = RSCFD unit and buffer
 *               : payload     = memory to copy payload to
 * Returns       : number of bytes copied
 ******************************************************************************/
extern rscfd_payload_size_t R_RSCFD_GetRxBuffMsgPayload(
    rscfd_rx_buff_t rx_buff,
    rscfd_payload_t payload[]);

/*******************************************************************************
 * Function Name : R_RSCFD_ClearRxBuffMsgNew
 * Description   : clear new message flag in requested RX buffer
 * Parameters    : rx_buff     = RSCFD unit and RX buffer
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_ClearRxBuffMsgNew(rscfd_rx_buff_t rx_buff);

/*******************************************************************************
 * Function Name : R_RSCFD_ReadRxBuff
 * Description   : Example of reading message information from requested
 *               : RX buffer using driver APIs. The sequence is sensitive to
 *               : incoherent data (new message while reading RX buffer)
 * Parameters    : rx_buff     = unit and RX buffer
 *               : msg         = buffer to store message information
 * Returns       : status of requested RX buffer before message read
 *               : EMPTY    = no new message data from RX buffer
 *               : NEWMSG   = new message data from RX buffer
 *               : OVERFLOW = incoherent data from RX buffer
 ******************************************************************************/
extern rscfd_result_t R_RSCFD_ReadRxBuff(rscfd_rx_buff_t rx_buff,
                                         rscfd_msg_t * msg);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoIrqStat
 * Description   : See if this Rx FIFO has an interrupt request pending.
 * Parameters    : fifo_num = RSCFD unit and RX FIFO
 * Returns       : enumeration of interrupt present/not present.
 ******************************************************************************/
extern rscfd_fifo_irq_t R_RSCFD_GetRxFifoIrqStat(rscfd_rx_fifo_t fifo_num);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoStat
 * Description   : retrieve status of selected RX FIFO
 * Parameters    : fifo_num   = RSCFD unit and RX FIFO
 * Returns       : RX FIFO status
 ******************************************************************************/
extern rscfd_rx_fifo_stat_t R_RSCFD_GetRxFifoStat(rscfd_rx_fifo_t fifo_num);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgCnt
 * Description   : retrieve number of messages in requested RX FIFO
 * Parameters    : fifo_num   = RSCFD unit and RX FIFO
 * Returns       : number of messages in requested RXFIFO
 ******************************************************************************/
extern uint8 R_RSCFD_GetRxFifoMsgCnt(rscfd_rx_fifo_t fifo_num);

/*******************************************************************************
 * Function Name : R_RSCFD_ClearRxFifoStat
 * Description   : Clear select status in requested RXFIFO. Status RFFLL
 *               : (RXFIFO full) and RFEMP (RXFIFO empty) cannot be cleared
 *               : using this API.
 * Parameters    : fifo_num   = RSCFD unit and RX FIFO
 *               : fifo_stat  = RX FIFO status to clear
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_ClearRxFifoStat(rscfd_rx_fifo_t fifo_num,
                                    rscfd_rx_fifo_stat_t fifo_stat);

/*******************************************************************************
 * Function Name : R_RSCFD_GetTxFifoStat
 * Description   : Return status of requested TX FIFO
 * Parameters    : tx_fifo     = RSCFD unit and TX FIFO
 * Returns       : status of requested TX FIFO
 ******************************************************************************/
extern rscfd_tx_fifo_stat_t R_RSCFD_GetTxFifoStat(rscfd_tx_fifo_t tx_fifo);

/*******************************************************************************
 * Function Name : R_RSCFD_ClearTxFifoStat
 * Description   : Clear select status of requested TXFIFO. Status
 *               : CFFLL (TXFIFO full) and CFEMP (TXFIFO empty) cannot be
 *               : cleared by this API.
 * Parameters    : fifo_num = RSCFD unit and TX FIFO
 *               : fifo_stat   = TX FIFO status bits to clear
 * Returns       : none
 ******************************************************************************/
extern void R_RSCFD_ClearTxFifoStat(rscfd_tx_fifo_t fifo_num,
                                    rscfd_tx_fifo_stat_t fifo_stat);

/*******************************************************************************
 * Function Name : R_RSCFD_ClearChnlErrs
 * Description   : Clear the Channel's Error Flag Register
 * Parameters    : rscfd_chnl = RSCFD unit and channel
 * Returns       : None
 * Note          : Clears all error bits.
 ******************************************************************************/
extern void R_RSCFD_ClearChnlErrs(rscfd_chnl_t rscfd_chnl);

/*******************************************************************************
 * Function Name : R_RSCFD_GetTxBuffId
 * Description   : Compile channel ID and buffer index into TX buffer ID
 *               : enumeration used by driver APIs
 * Parameters    : chnl    = RSCFD unit and channel
 *               : numbr   = buffer index within channel (0-63)
 * Returns       : TX buffer ID
 ******************************************************************************/
extern rscfd_tx_buff_t R_RSCFD_GetTxBuffId(rscfd_chnl_t chnl, uint8 numbr);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffId
 * Description   : Compiles unit and buffer index into RX buffer ID
 *               : enumeration used by driver APIs
 * Parameters    : chnl    = RSCFD unit and channel
 *               : numbr   = buffer index within unit (0-127)
 * Returns       : RX buffer ID
 ******************************************************************************/
extern rscfd_rx_buff_t R_RSCFD_GetRxBuffId(uint8 unitno, uint8 numbr);

/*******************************************************************************
 * Function Name : R_RSCFD_GetChnlNo
 * Description   : Returns channel number as index within requested unit
 * Parameters    : chnl    = RSCFD unit and channel
 * Returns       : index of requested channel within a unit
 ******************************************************************************/
extern uint8 R_RSCFD_GetChnlNo(rscfd_chnl_t chnl);

/*******************************************************************************
 * Function Name : R_RSCFD_GetUnitNo
 * Description   : Return RSCFD unit number based on requested channel ID
 * Parameters    : chnl    = RSCFD unit and channel
 * Returns       : index of RSCFD unit
 ******************************************************************************/
extern uint8 R_RSCFD_GetUnitNo(rscfd_chnl_t chnl);

/*******************************************************************************
 * Function Name : R_RSCFD_GetDlc
 * Description   : Returns DLC based on requested number of bytes
 * Parameters    : bytes     = requested number of bytes
 * Returns       : DLC
 ******************************************************************************/
extern rscfd_dlc_t R_RSCFD_GetDlc(rscfd_payload_size_t bytes);

/*******************************************************************************
 * Function Name : R_RSCFD_GetPayloadByteCnt
 * Description   : Returns number of payload bytes based on requested DLC
 * Parameters    : dlc = data length code
 * Returns       : Number of bytes corresponding to the DLC
 ******************************************************************************/
extern rscfd_payload_size_t R_RSCFD_GetPayloadByteCnt(rscfd_dlc_t dlc);

/*******************************************************************************
 * Function Name : R_RSCFD_GetPayloadWordCnt
 * Description   : Return number of 32-bit payload words based on requested DLC
 * Parameters    : dlc = data length code
 * Returns       : number of 32-bit words
 ******************************************************************************/
extern uint8 R_RSCFD_GetPayloadWordCnt(rscfd_dlc_t dlc);

/*******************************************************************************
 * Function Name : R_RSCFD_GetRxRulePage
 * Description   : Return Acceptance Filter Page enumeration used by
 *               : this driver APIs
 * Parameters    : unitno    = RSCFD unit number
 *               : ruleno    = rule number within unit (0-1535)
 * Returns       : returns RX page
 ******************************************************************************/
extern rscfd_rx_page_t R_RSCFD_GetRxRulePage(uint8 unitno, uint16 ruleno);

/*******************************************************************************
 * Function Name  : R_RSCFD_InitBuffComm
 * Description    : RSCFD initialization sequence for communication by buffers.
 *                : This is an example of complete RSCFD initialization
 *                : sequence when using RSCFD buffer mechanism. It can be used
 *                : as reference for creating own initialization sequences
 *                : when using RSCFD FIFOs.
 * Parameters     : cfg = user configurations of RSCFD peripheral
 * Returns        : none
 ******************************************************************************/
extern void R_RSCFD_InitBuffComm(const rscfd_buff_cfg_t * cfg);


#endif /* R_RSCFD_H */

