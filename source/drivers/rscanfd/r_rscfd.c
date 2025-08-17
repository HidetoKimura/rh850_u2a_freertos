/*****************************************************************************
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
 *****************************************************************************/

/*****************************************************************************
 * File Name   : r_rscfd.c
 * Device(s)   : RH850/U2x
 * Description : Low level driver for RS-CAN-FD peripheral.
 *****************************************************************************/

/*****************************************************************************
 * Include header files
 *****************************************************************************/
#include "r_rscfd.h"
#include "r_rscfd_dev.h"


/*##############################################################################
 # Macros
 ##############################################################################*/

/*******************************************************************************
 * general defines
 ******************************************************************************/
#define RSCFD_OFST_28BIT    (uint8)28
#define RSCFD_OFST_24BIT    (uint8)24
#define RSCFD_OFST_16BIT    (uint8)16
#define RSCFD_OFST_8BIT     (uint8)8
#define RSCFD_OFST_7BIT     (uint8)7
#define RSCFD_OFST_6BIT     (uint8)6
#define RSCFD_OFST_5BIT     (uint8)5
#define RSCFD_OFST_4BIT     (uint8)4
#define RSCFD_OFST_2BIT     (uint8)2
#define RSCFD_MASK_1BIT     (uint32)0x1
#define RSCFD_MASK_2BIT     (uint32)0x3
#define RSCFD_MASK_3BIT     (uint32)0x7
#define RSCFD_MASK_4BIT     (uint32)0xF
#define RSCFD_MASK_6BIT     (uint32)0x3F
#define RSCFD_MASK_7BIT     (uint32)0x7F
#define RSCFD_MASK_8BIT     (uint32)0xFF
#define RSCFD_MASK_9BIT     (uint32)0x1FF
#define RSCFD_MASK_16BIT    (uint32)0xFFFF
#define RSCFD_MASK_32BIT    (uint32)0xFFFFFFFF


/*******************************************************************************
 * RX rule defines
 ******************************************************************************/
#define RSCFD_MASK_RULE_MAX         (uint32)0x5FF
#define RSCFD_MASK_RULE_L1          (uint32)0x2
#define RSCFD_OFST_CFDGAFLCFG_00    (uint8)0
#define RSCFD_OFST_CFDGAFLCFG_01    (uint8)1
#define RSCFD_OFST_CFDGAFLCFG_10    (uint8)2
#define RSCFD_OFST_CFDGAFLCFG_11    (uint8)3
#define RSCFD_OFST_CFDGAFLCFG_20    (uint8)4
#define RSCFD_OFST_CFDGAFLCFG_21    (uint8)5
#define RSCFD_OFST_CFDGAFLCFG_30    (uint8)6
#define RSCFD_OFST_CFDGAFLCFG_31    (uint8)7


/*******************************************************************************
 * Macro Name     : RSCFD_WAIT
 * Description    : execute loop until condition (till) is true or loop counts
 *                : down to zero. If specified number of iterations is zero
 *                : a default 256 iterations are used.
 * Parameters     : till    = condition to wait for
 *                : w       = loop count to wait for condition (till)
 *                : n       = counter to use (defined outside macro)
 * Returns        : none
 ******************************************************************************/
#define RSCFD_WAIT(till, w, n)    for (n = (!(w)) ? 0x100 : (w); !(till) && n; n++)


/*******************************************************************************
 * Macro Name     : RSCFD_GET_UNIT
 * Description    : extract unit number
 * Parameters     : e = enumeration of channel (rscfd_chnl_t),
 *                :     page (rscfd_rx_page_t),
 *                :     FIFO (rscfd_rx_fifo_t, rscfd_tx_fifo_t), or
 *                :     buffer (rscfd_rx_buff_t, rscfd_tx_buff_t)
 * Returns        : unit number
 ******************************************************************************/
#define RSCFD_GET_UNIT(e)    (((uint8)((e) >> RSCFD_OFST_24BIT)))


/*******************************************************************************
 * Macro Name     : RSCFD_GET_RXRULEREG
 * Description    : extract register number from channel enumeration (rscfd_chnl_t)
 * Parameters     : c = channel enumeration
 * Returns        : register number
 ******************************************************************************/
#define RSCFD_GET_RXRULEREG(c)    (uint8)((c) >> RSCFD_OFST_16BIT)


/*******************************************************************************
 * Macro Name     : RSCFD_GET_RXRULEREG
 * Description    : extract register number from channel enumeration (rscfd_chnl_t)
 * Parameters     : c = channel enumeration
 * Returns        : byte number (within register)
 ******************************************************************************/
#define RSCFD_GET_RXRULEBYTE(c)    (uint8)((c) >> RSCFD_OFST_8BIT)


/*******************************************************************************
 * Macro Name     : RSCFD_GET_CHNL
 * Description    : extract channel number from channel enumeration (rscfd_chnl_t)
 * Parameters     : c = channel enumeration
 * Returns        : channel number
 ******************************************************************************/
#define RSCFD_GET_CHNL(c)    (uint8)(c)


/*******************************************************************************
 * Macro Name     : RSCFD_GET_RXFIFO
 * Description    : extract RXFIFO number from enumeration passed as argument.
 * Parameters     : f       = RXFIFO enumeration
 * Returns        : register number
 ******************************************************************************/
#define RSCFD_GET_RXFIFO(f)    (uint8)((f) & RSCFD_MASK_3BIT)


/*******************************************************************************
 * Macro Name     : RSCFD_GET_RXBUFF
 * Description    : extract RX buffer number from RX buffer enumeration
 * Parameters     : b       = RX buffer enumeration
 * Returns        : register number
 ******************************************************************************/
#define RSCFD_GET_RXBUFF(b)    (uint8)((b) & RSCFD_MASK_7BIT)


/*******************************************************************************
 * Macro Name     : RSCFD_GET_RXDEST
 * Description    : extract RX destination from destination enumeration.
 *                : RX destination can be RXFIFO or RX buffer.
 * Parameters     : i       = RX destination enumeration
 * Returns        : register number
 ******************************************************************************/
#define RSCFD_GET_RXDEST(i)    ((rscfd_rx_t)((i) & RSCFD_MASK_CFDGAFLP0_GAFLRMV))


/*******************************************************************************
 * Macro Name     : RSCFD_GET_RXPAGE
 * Description    : extract RX rule page number from RX page enumeration.
 * Parameters     : i       = RX destination enumeration
 * Returns        : register number
 ******************************************************************************/
#define RSCFD_GET_RXPAGE(p)    ((rscfd_rx_page_t)(uint8)(p))


/*******************************************************************************
 * Macro Name     : RSCFD_GET_TXBUFF
 * Description    : extract buffer number from TX buffer enumeration
 * Parameters     : c       = TX buffer enumeration
 * Returns        : register number
 ******************************************************************************/
#define RSCFD_GET_TXBUFF(b)    (uint16)(b)


/*******************************************************************************
 * Macro Name     : RSCFD_GET_TXFIFO
 * Description    : extract TXFIFO number from TX FIFO enumeration
 * Parameters     : c       = TXFIFO enumeration
 * Returns        : register number
 ******************************************************************************/
#define RSCFD_GET_TXFIFO(f)    (uint8)(f)


/*******************************************************************************
 * Macro Name     : RSCFD_GET_TXDEST
 * Description    : extract TX destination from TX destination enumeration.
 *                : TX destination can be either TXFIFO or TX buffer
 * Parameters     : c       = TXFIFO enumeration
 * Returns        : register number
 ******************************************************************************/
#define RSCFD_GET_TXDEST(d)    ((rscfd_tx_t)((d) & ~RSCFD_MASK_16BIT))


/*******************************************************************************
 * Macro Name     : RSCFD_MAKE_DLC
 * Description    : translate DLC value into enumeration used by driver APIs
 * Parameters     : n       = number to translate into rscfd_dlc_t
 * Returns        : rscfd_dlc_t enumeration value
 ******************************************************************************/
#define RSCFD_MAKE_DLC(n)    (rscfd_dlc_t)(((n) & RSCFD_MASK_4BIT) \
                                           << RSCFD_OFST_28BIT)


/*******************************************************************************
 * Macro Name     : RSCFD_MAKE_RXBUFF
 * Description    : put together rscfd_rx_buff_t enumeration from unit number
 *                : and RX buffer number
 * Parameters     : u       = unit number
 *                : n       = RX buffer number
 * Returns        : rscfd_rx_buff enumeration value
 ******************************************************************************/
#define RSCFD_MAKE_RXBUFF(u, n)    (rscfd_rx_buff_t)(((u) << RSCFD_OFST_24BIT) | (n))


/*******************************************************************************
 * Macro Name     : RSCFD_MAKE_RXPAGE
 * Description    : translate unit and RX rule number into page ID enumeration
 *                : used by driver APIs
 * Parameters     : u       = unit number
 *                : n       = RX rule number
 * Returns        : rscfd_rx_page_t enumeration value
 ******************************************************************************/
#define RSCFD_MAKE_RXPAGE(u, r)    (rscfd_rx_page_t)(((u) << RSCFD_OFST_24BIT) \
                                                     | ((r) >> RSCFD_OFST_4BIT))


/*******************************************************************************
 * Macro Name     : RSCFD_MAKE_TXBUFF
 * Description    : translate unit number, channel number and TX buffer index
 *                : into TX buffer ID used by driver APIs
 * Parameters     : u       = unit number
 *                : c       = channel number
 *                : n       = TX buffer number
 * Returns        : rscfd_tx_buff enumeration value
 ******************************************************************************/
#define RSCFD_MAKE_TXBUFF(u, c, n)    (rscfd_tx_buff_t)(((u) << RSCFD_OFST_24BIT) \
                                                        | (((c) << RSCFD_OFST_6BIT) + (n)))



/*##############################################################################
 # local types
 ##############################################################################*/


/*##############################################################################
 # local variables
 ##############################################################################*/

/*******************************************************************************
 * Table used to translate from DLC to number of bytes
 * NOTE: translation to number of 32-bit WORDS is a simple math
 ******************************************************************************/
static const rscfd_payload_size_t rscfd_byte_cnt[] =
{
    RSCFD_PAYLOAD_SIZE_0_BYTES,     /* DLC = 0x0 */
    RSCFD_PAYLOAD_SIZE_1_BYTES,     /* DLC = 0x1 */
    RSCFD_PAYLOAD_SIZE_2_BYTES,     /* DLC = 0x2 */
    RSCFD_PAYLOAD_SIZE_3_BYTES,     /* DLC = 0x3 */
    RSCFD_PAYLOAD_SIZE_4_BYTES,     /* DLC = 0x4 */
    RSCFD_PAYLOAD_SIZE_5_BYTES,     /* DLC = 0x5 */
    RSCFD_PAYLOAD_SIZE_6_BYTES,     /* DLC = 0x6 */
    RSCFD_PAYLOAD_SIZE_7_BYTES,     /* DLC = 0x7 */
    RSCFD_PAYLOAD_SIZE_8_BYTES,     /* DLC = 0x8 */
    RSCFD_PAYLOAD_SIZE_12_BYTES,    /* DLC = 0x9 */
    RSCFD_PAYLOAD_SIZE_16_BYTES,    /* DLC = 0xa */
    RSCFD_PAYLOAD_SIZE_20_BYTES,    /* DLC = 0xb */
    RSCFD_PAYLOAD_SIZE_24_BYTES,    /* DLC = 0xc */
    RSCFD_PAYLOAD_SIZE_32_BYTES,    /* DLC = 0xd */
    RSCFD_PAYLOAD_SIZE_48_BYTES,    /* DLC = 0xe */
    RSCFD_PAYLOAD_SIZE_64_BYTES     /* DLC = 0xf */
};


/*******************************************************************************
 * Table used to translate number of payload bytes to DLC
 ******************************************************************************/
static const uint8 rscfd_dlc[] =
{
    0x00,                                       /* 0 bytes */
    0x01,                                       /* 1 bytes */
    0x02,                                       /* 2 bytes */
    0x03,                                       /* 3 bytes */
    0x04,                                       /* 4 bytes */
    0x05,                                       /* 5 bytes */
    0x06,                                       /* 6 bytes */
    0x07,                                       /* 7 bytes */
    0x08,                                       /* 8 bytes */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x09,                                       /* 12 bytes */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x0a,                                       /* 16 bytes */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x0b,                                       /* 20 bytes */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x0c,                                       /* 24 bytes */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x0d,                                       /* 32 bytes */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x0e,                                       /* 48 bytes */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x00,                                       /* unsupported */
    0x0f                                        /* 64 bytes */
};


/*##############################################################################
 # API Function Definitions
 #   unit
 #   channel
 #   acceptance filters
 #   RXFIFO
 #   TXFIFO
 #   RXbuffer
 #   TXbuffer
 #   supporting
 #############################################################################*/

/*##############################################################################
 # unit APIs
 #############################################################################*/

/*******************************************************************************
 * Function Name : R_RSCFD_CheckUnitModeTrans
 * Description   : Check if requested transition of global mode possible.
 *               : Any transitions from or to RESET mode are supported. Also
 *               : transitions TEST and OPERATING mode are supported.
 *               : See "Global Modes" state diagram in hardware U/M.
 * Parameters    : from_mode      = current RSCFD channel mode
 *               : to_mode        = requested RSCFD channel mode.
 * Returns       : whether direct transition supported
 ******************************************************************************/
rscfd_mode_trans_t R_RSCFD_CheckUnitModeTrans(rscfd_glbl_mode_t from_mode,
                                              rscfd_glbl_mode_t to_mode)
{
    uint8 direct;

    /* transition is valid if
     *   - destination mode is RESET
     *   - originating mode is RESET
     *   - originating mode is TEST and destination mode is OPERATING
     *   - originating mode if OPERATING and destination mode is TEST */
    direct  = (uint8)((to_mode & RSCFD_GLBL_MODE_RST) != 0);
    direct |= (uint8)((from_mode & RSCFD_GLBL_MODE_RST) != 0);
    direct |= (uint8)(((from_mode & RSCFD_GLBL_MODE_TEST) != 0) && !to_mode);
    direct |= (uint8)(!from_mode && ((to_mode & RSCFD_GLBL_MODE_TEST) != 0));

    /* return type of supported transition */
    return (rscfd_mode_trans_t)direct;
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetUnitRamInitStat
 * Description   : Return CAN RAM Initialization status. CAN RAM is
 *               : automatically initialized by hardware after reset.
 * Parameters    : unit = RSCFD unit number being configured.
 * Returns       : 0           = complete
 *               : otherwise   = ongoing
 ******************************************************************************/
rscfd_ram_init_t R_RSCFD_GetUnitRamInitStat(rscfd_unit_t unit)
{
    uint32 stat;

    /* extract RAM initialization status */
    stat = RSCFD[unit].CFDGSTS.WORD & RSCFD_MASK_CFDGSTS_GRAMINIT;
    return (rscfd_ram_init_t)stat;
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetUnitMode
 * Description   : Get CAN unit's operating mode.
 * Parameters    : unit = the CAN unit being interrogated.
 * Returns       : Global mode per enumeration
 ******************************************************************************/
rscfd_glbl_mode_t R_RSCFD_GetUnitMode(rscfd_unit_t unit)
{
    uint32 msk;

    /* which bit files to extract */
    msk  = RSCFD_MASK_CFDGSTS_GRSTSTS | RSCFD_MASK_CFDGSTS_GHLTSTS;
    msk |= RSCFD_MASK_CFDGSTS_GSLPSTS;

    /* extract global unit mode */
    return (rscfd_glbl_mode_t)(RSCFD[unit].CFDGSTS.WORD & msk);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetUnitMode
 * Description   : Set the RSCFD unit mode. See "Global Modes" diagram in HW U/M
 *               : Unsupported transition are ignored. Updates CFDGCTR register
 *               : bit fields GMDC and GSLPR
 * Parameters    : unit = the CAN unit being configured.
 *               : req  = global mode to be entered.
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetUnitMode(rscfd_unit_t unit, rscfd_glbl_mode_t req)
{
    rscfd_glbl_mode_t mode;
    uint32            msk;

    /* is this valid transition */
    mode = R_RSCFD_GetUnitMode(unit);
    if (RSCFD_MODE_TRANS_VALID == R_RSCFD_CheckUnitModeTrans(mode, req))
    {
        /* supported transition, command requested mode */
        msk = RSCFD_MASK_CFDGCTR_GMDC | RSCFD_MASK_CFDGCTR_GSLPR;
        RMW32(RSCFD[unit].CFDGCTR.WORD, msk, req);
    }
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetUnitClockSrc
 * Description   : Selects RSCFD unit clock source.
 * Parameters    : unit      = CAN unit being configured.
 *               : clock_src = Enum defining clkc (LSB) or clk_xincan (OSC)
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetUnitClockSrc(rscfd_unit_t unit, rscfd_clock_src_t clock_src)
{
    /* configure unit clock */
    RMW32(RSCFD[unit].CFDGCFG.WORD, RSCFD_MASK_CFDGCFG_DCS, clock_src);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetUnitRxRuleDlc
 * Description   : Enables/disables use of DLC check in acceptance filtering.
 * Parameters    : unit    = CAN unit being configured.
 *               : dce_dre = Enum defining DCE bit setting (DLC Check Enable)
 *                           and DRE bit setting (DLC Replace).
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetUnitRxRuleDlc(rscfd_unit_t unit, rscfd_dlc_check_t dce_dre)
{
    uint32 msk;

    /* configure DLC acceptance */
    msk = RSCFD_MASK_CFDGCFG_DCE | RSCFD_MASK_CFDGCFG_DRE;
    RMW32(RSCFD[unit].CFDGCFG.WORD, msk, dce_dre);
}


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
void R_RSCFD_SetUnitRxBuffSizeAndCnt(rscfd_unit_t unit,
                                     rscfd_rx_buff_size_t size,
                                     rscfd_rx_buff_cnt_t cnt)
{
    uint32 msk;

    /* configure buffer size in bytes */
    msk = RSCFD_MASK_CFDRMNB_RMPLS | RSCFD_MASK_CFDRMNB_NRXMB;
    RMW32(RSCFD[unit].CFDRMNB.WORD, msk, (uint32)(size | cnt));
}


/*******************************************************************************
 * Function Name  : R_RSCFD_InitUnitRst
 * Description    : RSCFD unit initializations. This API will put RSCFD units
 *                : in RESET mode.
 * Parameters     : cfg       = user configurations
 *                : cfg_cnt   = number of units to be configured
 * Returns        : none
 ******************************************************************************/
void R_RSCFD_InitUnitRst(const rscfd_unit_cfg_t * cfg, uint8 cfg_cnt)
{
    rscfd_unit_t         unit;
    rscfd_rx_buff_cnt_t  buff_cnt;
    rscfd_rx_buff_size_t buff_size;
    uint32               delay;
    uint32               wait;
    uint32               msk;
    uint8                u;

    /* populate unit configurations at RESET mode */
    for (u = 0; u < cfg_cnt; u++)
    {
        /* which unit */
        unit  = cfg[u].unit;
        delay = cfg[u].hw_delay;

        /* Wait while CAN RAM initialization is ongoing */
        msk = RSCFD_RAM_INIT_COMPLETE;
        RSCFD_WAIT(R_RSCFD_GetUnitRamInitStat(unit) == msk, delay, wait);

        /* check RAM initialization complete
         * NOTE: no point to continue otherwise */
        if (R_RSCFD_GetUnitRamInitStat(unit) == msk)
        {
            /* continue, command RESET mode  */
            msk = RSCFD_GLBL_MODE_RST;
            R_RSCFD_SetUnitMode(unit, (rscfd_glbl_mode_t)msk);
            RSCFD_WAIT(R_RSCFD_GetUnitMode(unit) & msk, delay, wait);

            /* check if in RESET mode
             * NOTE: no point to continue otherwise */
            if (R_RSCFD_GetUnitMode(unit) & msk)
            {
                /* continue, set clock source and DLC acceptance */
                R_RSCFD_SetUnitClockSrc(unit, cfg[u].clock_source);
                R_RSCFD_SetUnitRxRuleDlc(unit, cfg[u].dlc_check);

                /* set RX message size and buffer count */
                buff_cnt  = cfg[u].rx_buff_cnt;
                buff_size = cfg[u].rx_buff_size;
                R_RSCFD_SetUnitRxBuffSizeAndCnt(unit, buff_size, buff_cnt);
            }
        }
    }
}


/*******************************************************************************
 * Function Name  : R_RSCFD_InitUnitOper
 * Description    : RSCFD unit initializations. This API should be called when
 *                : RSCFD units are in RESET mode. This API will put RSCFD
 *                : units in OPERATIONAL mode.
 * Parameters     : cfg       = user configurations
 *                : cfg_cnt   = number of units to be configured
 * Returns        : none
 ******************************************************************************/
void R_RSCFD_InitUnitOper(const rscfd_unit_cfg_t * cfg, uint8 cfg_cnt)
{
    rscfd_unit_t unit;
    uint32       wait;
    uint8        u;

    /* populate unit configurations at OPERATIONAL mode */
    for (u = 0; u < cfg_cnt; u++)
    {
        /* which unit */
        unit = cfg[u].unit;

        /* command OPERATIONAL mode
         * NOTE: operational mode is 0 */
        R_RSCFD_SetUnitMode(unit, RSCFD_GLBL_MODE_OPER);
        RSCFD_WAIT(!R_RSCFD_GetUnitMode(unit), cfg[u].hw_delay, wait);
    }
}


/*##############################################################################
 # channel APIs
 #############################################################################*/

/*******************************************************************************
 * Function Name : R_RSCFD_ClearChnlErrs
 * Description   : Clear the Channel's Error Flag Register
 * Parameters    : rscfd_chnl = RSCFD unit and channel
 * Returns       : None
 * Note          : Clears all error bits.
 ******************************************************************************/
void R_RSCFD_ClearChnlErrs(rscfd_chnl_t rscfd_chnl)
{
    uint8 chnl;
    uint8 unit;

    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* Clear the bit that caused the interrupt (clear all error bits)
     * NOTE: bits written as 0 not affected */
    RSCFD[unit].CH1[chnl].CFDCERFL.WORD = RSCFD_MASK_CFDCERFL_ERR;
}


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
rscfd_mode_trans_t R_RSCFD_CheckChnlModeTrans(rscfd_chnl_mode_t from_mode,
                                              rscfd_chnl_mode_t to_mode)
{
    uint8 direct;

    /* transition is valid if
     *  - destination mode is RESET
     *  - originating mode is RESET
     *  - originating mode is HALT and destination mode is COMMUNICATION
     *  - originating mode if COMMUNITCATION and destination mode is HALT */
    direct  = (uint8)((to_mode & RSCFD_CHNL_MODE_RST) != 0);
    direct |= (uint8)((from_mode & RSCFD_CHNL_MODE_RST) != 0);
    direct |= (uint8)(((from_mode & RSCFD_CHNL_MODE_HALT) != 0) && !to_mode);
    direct |= (uint8)(!from_mode && ((to_mode & RSCFD_CHNL_MODE_HALT) != 0));

    /* is transition valid  */
    return (rscfd_mode_trans_t)direct;
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetChnlMode
 * Description   : Get RSCFD channel mode. Reads register CmSTS bit fields
 *               : CSLPSTS, CHLTSTS, CRSTSTS.
 * Parameters    : rscfd_chnl      = CAN channel enumeration (includes unit)
 * Returns       : channel mode
 ******************************************************************************/
rscfd_chnl_mode_t R_RSCFD_GetChnlMode(rscfd_chnl_t rscfd_chnl)
{
    uint32 msk;
    uint8  chnl;
    uint8  unit;

    /* unit and channel to use */
    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* which bit fields represent channel mode */
    msk  = RSCFD_MASK_CFDCSTS_CRSTSTS | RSCFD_MASK_CFDCSTS_CHLTSTS;
    msk |= RSCFD_MASK_CFDCSTS_CSLPSTS;

    /* read channel mode */
    return (rscfd_chnl_mode_t)(RSCFD[unit].CH1[chnl].CFDCSTS.WORD & msk);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetChnlStatus
 * Description   : Get CAN channel status - Entire register with no formatting.
 * Parameters    : rscfd_chnl = CAN channel enumeration (includes unit).
 * Returns       : Channel Status Register (RSCFDnCFDCmSTS).
 * Note          : No usage at time of writing.
 ******************************************************************************/
rscfd_chnl_stat_t R_RSCFD_GetChnlStatus(rscfd_chnl_t rscfd_chnl)
{
    uint32 msk;
    uint8  chnl;
    uint8  unit;

    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* status bits to return */
    msk  = RSCFD_MASK_CFDCSTS_EPSTS | RSCFD_MASK_CFDCSTS_BOSTS;
    msk |= RSCFD_MASK_CFDCSTS_TRMSTS | RSCFD_MASK_CFDCSTS_RECSTS;
    msk |= RSCFD_MASK_CFDCSTS_COMSTS | RSCFD_MASK_CFDCSTS_ESIF;

    /* return channel status */
    return (rscfd_chnl_stat_t)(RSCFD[unit].CH1[chnl].CFDCSTS.WORD & msk);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetChnlTxErrCnt
 * Description   : Return number of channel transmit errors
 * Parameters    : rscfd_chnl    = RSCFD unit and channel
 * Returns       : number of channel transmit errors
 ******************************************************************************/
uint8 R_RSCFD_GetChnlTxErrCnt(rscfd_chnl_t rscfd_chnl)
{
    uint8 chnl;
    uint8 unit;

    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* return transmit error count (TEC) */
    return (uint8)(RSCFD[unit].CH1[chnl].CFDCSTS.WORD >> RSCFD_OFST_24BIT);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetChnlRxErrCnt
 * Description   : Return number of channel receive  errors
 * Parameters    : rscfd_chnl    = RSCFD unit and channel
 * Returns       : number of channel transmit errors
 ******************************************************************************/
uint8 R_RSCFD_GetChnlRxErrCnt(rscfd_chnl_t rscfd_chnl)
{
    uint8 chnl;
    uint8 unit;

    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* return transmit error count (TEC) */
    return (uint8)(RSCFD[unit].CH1[chnl].CFDCSTS.WORD >> RSCFD_OFST_16BIT);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetChnlHistStat
 * Description   : return status of channel TX history list
 * Parameters    : rscfd_chnl  = RSCFD unit and channel
 * Returns       : status of channel TX history list
 ******************************************************************************/
rscfd_hist_stat_t R_RSCFD_GetChnlHistStat(rscfd_chnl_t rscfd_chnl)
{
    uint32 cfg;
    uint8  chnl;
    uint8  unit;

    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* return channel TX history status */
    cfg = RSCFD[unit].CFDTHLSTS[chnl].WORD;
    return (rscfd_hist_stat_t)(cfg & RSCFD_HIST_STAT_ALL);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetChnlHistId
 * Description   : Return message ID from the current TX history pointer
 *               : of requested channel
 * Parameters    : rscfd_chnl  = RSCFD unit and channel
 * Returns       : transmit ID from channel TX history list
 ******************************************************************************/
uint16 R_RSCFD_GetChnlHistId(rscfd_chnl_t rscfd_chnl)
{
    uint8 chnl;
    uint8 unit;

    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* return transmit ID */
    return (uint16)(RSCFD[unit].THL[chnl].CFDTHLACC1.WORD);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlHistNext
 * Description   : Set pointer to next element in channel TX history list
 * Parameters    : rscfd_chnl  = RSCFD unit and channel
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetChnlHistNext(rscfd_chnl_t rscfd_chnl)
{
    uint8 chnl;
    uint8 unit;

    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* Move pointer to next entry in channel TX history list */
    RSCFD[unit].CFDTHLPCTR[chnl].WORD = RSCFD_MASK_CFDTHLPCTR_THLPC;
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlMode
 * Description   : Set Channel Mode. See "Channel Modes" state diagram in HW U/M
 *               : Unsupported transition requests are ignored. Updates
 *               : register CmCTR bit fields CSLPR and CHMDC.
 * Parameters    : rscfd_chnl       = RSCFD unit and channel
 *               : mode_req         = channel mode.
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetChnlMode(rscfd_chnl_t rscfd_chnl, rscfd_chnl_mode_t req)
{
    rscfd_chnl_mode_t mode;
    uint32            msk;
    uint8             unit;
    uint8             chnl;

    /* is requested transition valid */
    mode = R_RSCFD_GetChnlMode(rscfd_chnl);
    if (RSCFD_MODE_TRANS_VALID == R_RSCFD_CheckChnlModeTrans(mode, req))
    {
        /* yes, channel and unit to use */
        unit = RSCFD_GET_UNIT(rscfd_chnl);
        chnl = RSCFD_GET_CHNL(rscfd_chnl);

        /* bits to update */
        msk = RSCFD_MASK_CFDCCTR_CHMDC | RSCFD_MASK_CFDCCTR_CSLPR;

        /* command transition */
        RMW32(RSCFD[unit].CH1[chnl].CFDCCTR.WORD, msk, req);
    }
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlNomBitrate
 * Description   : Set CAN Channel Nominal bit rate (the slower bit rate
 *               : used at the beginning of the CAN FD frame). Nominal BRP
 *               : must match data BRP
 * Parameters    : rscfd_chnl = RSCFD unit and channel
 *               : btr        = nominal bit rate to set
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetChnlNomBitrate(rscfd_chnl_t rscfd_chnl, rscfd_chnl_nbr_t btr)
{
    uint32 msk;
    uint8  chnl;
    uint8  unit;

    /* what unit and channel */
    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* bit fields to update */
    msk  = RSCFD_MASK_CFDCNCFG_NBRP | RSCFD_MASK_CFDCNCFG_NSJW;
    msk |= RSCFD_MASK_CFDCNCFG_NTSEG1 | RSCFD_MASK_CFDCNCFG_NTSEG2;

    /* set nominal bit rate */
    RMW32(RSCFD[unit].CH1[chnl].CFDCNCFG.WORD, msk, btr);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlDataBitrate
 * Description   : Set CAN Channel Data bit rate (the faster bit rate
 *               : used for the payload of the CAN FD frame)
 * Parameters    : chnl       = CAN channel enumeration (includes unit).
 *               : btr        = data bit rate to set
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetChnlDataBitrate(rscfd_chnl_t rscfd_chnl, rscfd_chnl_dbr_t btr)
{
    uint32 msk;
    uint8  chnl;
    uint8  unit;

    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* bit fields to update */
    msk  = RSCFD_MASK_CFDCDCFG_DBRP | RSCFD_MASK_CFDCDCFG_DSJW;
    msk |= RSCFD_MASK_CFDCDCFG_DTSEG1 | RSCFD_MASK_CFDCDCFG_DTSEG2;

    /* update data bit rate */
    RMW32(RSCFD[unit].CH2[chnl].CFDCDCFG.WORD, msk, btr);
}


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
void R_RSCFD_SetChnlBitrate(rscfd_chnl_t rscfd_chnl,
                            rscfd_chnl_nbr_t nom_rate,
                            rscfd_chnl_dbr_t data_rate)
{
    /* set channel bit rates */
    R_RSCFD_SetChnlNomBitrate(rscfd_chnl, nom_rate);
    R_RSCFD_SetChnlDataBitrate(rscfd_chnl, data_rate);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlInterface
 * Description   : Set classical or CANFD CAN interface
 *               : Configure in register FDCFG bit field CLOE and FDOE.
 *               : FDCFG is in register structure CH2.
 * Parameters    : rscfd_chnl = RSCFD unit and channel
 *               : chnl_intf  = Channel interface
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetChnlInterface(rscfd_chnl_t rscfd_chnl,
                              rscfd_chnl_interf_t chnl_interf)
{
    uint32 msk;
    uint8  chnl;
    uint8  unit;

    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* configure channel interface (classical vs CANFD) */
    msk = RSCFD_MASK_CFDCFDCFG_CLOE | RSCFD_MASK_CFDCFDCFG_FDOE;
    RMW32(RSCFD[unit].CH2[chnl].CFDCFDCFG.WORD, msk, chnl_interf);
}


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
void R_RSCFD_SetChnlTxDelayComp(rscfd_chnl_t rscfd_chnl,
                                rscfd_chnl_comp_t comp_cfg,
                                uint8 comp_ofst)
{
    uint32 cfg;
    uint32 msk;
    uint8  chnl;
    uint8  unit;

    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* bits to update */
    msk  = RSCFD_MASK_CFDCFDCFG_TDCE | RSCFD_MASK_CFDCFDCFG_TDCOC;
    msk |= RSCFD_MASK_CFDCFDCFG_TDCO;

    /* enable/disable transmitter delay */
    cfg = comp_cfg | (comp_ofst << RSCFD_OFST_16BIT);
    RMW32(RSCFD[unit].CH2[chnl].CFDCFDCFG.WORD, msk, cfg);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlRxRuleCnt
 * Description   : Set number of receive Acceptance Filters used by requested
 *               : channel. Configure in register GAFLCFG0 bit field RNCx.
 * Parameters    : rscfd_chnl = CAN channel enumeration
 *               : num_rules  = Number of receive rules (0-384)
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetChnlRxRuleCnt(rscfd_chnl_t rscfd_chnl, uint16 num_rules)
{
    uint32 msk;
    uint8  reg;
    uint8  unit;

    unit = RSCFD_GET_UNIT(rscfd_chnl);
    reg  = RSCFD_GET_RXRULEREG(rscfd_chnl);

    /* configure number of receive rules */
    msk = RSCFD_MASK_CFDGAFLCFG_RNC;
    RMW16(RSCFD[unit].CFDGAFLCFG[reg].HALF, msk, num_rules);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlTestMode
 * Description   : Set Channel Test Mode
 * Parameters    : chnl      = CAN channel enumeration (includes unit).
 *               : mode      = enumeration of test modes
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetChnlTestMode(rscfd_chnl_t rscfd_chnl, rscfd_chnl_test_t mode)
{
    uint32 msk;
    uint8  chnl;
    uint8  unit;

    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* bits to update */
    msk = RSCFD_MASK_CFDCCTR_CTMS | RSCFD_MASK_CFDCCTR_CTME;

    /* configure test mode */
    RMW32(RSCFD[unit].CH1[chnl].CFDCCTR.WORD, msk, mode);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlTxHistEna
 * Description   : Set use of channel's TX history buffer to Enabled/Disabled.
 * Parameters    : rscfd_chnl = CAN channel enumeration (includes unit).
 *               : hist_en    = enumeration to enable/disable history buffer.
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetChnlTxHistEna(rscfd_chnl_t rscfd_chnl,
                              rscfd_chnl_hist_en_t hist_en)
{
    uint8 chnl;
    uint8 unit;

    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* configure channel history */
    RMW32(RSCFD[unit].CFDTHLCC[chnl].WORD, RSCFD_MASK_CFDTHLCC_THLE, hist_en);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetChnlErrIrq
 * Description   : Enable/disable channel error interrupts
 *               : Configure in register CmCTR bit field BOEIE.
 * Parameters    : rscfd_chnl = CAN channel enumeration (includes unit).
 *               : err_irq_en = enumeration to enable/disable error interrupt.
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetChnlErrIrq(rscfd_chnl_t rscfd_chnl,
                           rscfd_chnl_err_irq_t err_irq_en)
{
    uint32 msk;
    uint8  chnl;
    uint8  unit;

    unit = RSCFD_GET_UNIT(rscfd_chnl);
    chnl = RSCFD_GET_CHNL(rscfd_chnl);

    /* bits to update */
    msk = RSCFD_MASK_CFDCCTR_BOEIE;

    /* configure error interrupts */
    RMW32(RSCFD[unit].CH1[chnl].CFDCCTR.WORD, msk, err_irq_en);
}


/*******************************************************************************
 * Function Name : R_RSCFD_InitChnlRst
 * Description   : RSCFD channel initializations. This API must be called
 *               : when RSCFD units are in reset mode. This API will put
 *               : RSCFD channels into RESET mode.
 * Parameters    : cfg       = user configurations
 *               : cfg_cnt   = number of channels to be configured
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_InitChnlRst(const rscfd_chnl_cfg_t cfg[], uint8 cfg_cnt)
{
    rscfd_chnl_t chnl;
    uint32       wait;
    uint32       msk;
    uint8        c;

    /* Initialize each individual CAN channel,
     * per configuration structure */
    for (c = 0; c < cfg_cnt; c++)
    {
        /* which channel */
        chnl = cfg[c].chnl;

        /* Set channel to RESET mode
         * NOTE: wait till change takes place */
        msk = RSCFD_CHNL_MODE_RST;
        R_RSCFD_SetChnlMode(chnl, (rscfd_chnl_mode_t)msk);
        RSCFD_WAIT(R_RSCFD_GetChnlMode(chnl) & msk, cfg[c].hw_delay, wait);

        /* check if in RESET mode
         * NOTE: no point to continue otherwise */
        if (R_RSCFD_GetChnlMode(chnl) & msk)
        {
            /* continue, set
             * - both nominal and data bit rates
             * - channel transceiver delay compensation
             * - Error interrupt configuration
             * - number of rules for this channel */
            R_RSCFD_SetChnlBitrate(chnl, cfg[c].nom_rate, cfg[c].data_rate);
            R_RSCFD_SetChnlTxDelayComp(chnl, RSCFD_CHNL_COMP_EN, 0);
            R_RSCFD_SetChnlErrIrq(chnl, cfg[c].error_irq);
            R_RSCFD_SetChnlRxRuleCnt(chnl, cfg[c].rx_rule_cnt);
        }
    }
}


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
void R_RSCFD_InitChnlOper(const rscfd_chnl_cfg_t cfg[], uint8 cfg_cnt)
{
    rscfd_chnl_t chnl;
    uint32       wait;
    uint32       msk;
    uint8        c;

    /* Initialize each individual CAN channel, per config structure */
    for (c = 0; c < cfg_cnt; c++)
    {
        /* which channel */
        chnl = cfg[c].chnl;

        /* Put channel in HALT mode so that communication
         * test mode can be enabled or disabled.
         * NOTE: if channel in STOP mode this will fail */
        msk = RSCFD_CHNL_MODE_HALT;
        R_RSCFD_SetChnlMode(chnl, (rscfd_chnl_mode_t)msk);
        RSCFD_WAIT(R_RSCFD_GetChnlMode(chnl) & msk, cfg[c].hw_delay, wait);

        /* check if in HALT mode
         * NOTE: no point to continue otherwise */
        if (R_RSCFD_GetChnlMode(chnl) & msk)
        {
            /* continue configure test mode */
            R_RSCFD_SetChnlTestMode(chnl, cfg[c].testmode);

            /* Put channel in COMMUNICATION mode */
            msk = RSCFD_CHNL_MODE_COMM;
            R_RSCFD_SetChnlMode(chnl, (rscfd_chnl_mode_t)msk);
            RSCFD_WAIT(R_RSCFD_GetChnlMode(chnl) == msk, cfg[c].hw_delay, wait);

            /*  check if in COMMUNICATION mode
             * NOTE: no point to continue otherwise */
            if (R_RSCFD_GetChnlMode(chnl) == msk)
            {
                /* continue, enable transmit history buffer */
                R_RSCFD_SetChnlTxHistEna(chnl, cfg[c].hist_en);
            }
        }
    }
}


/*##############################################################################
 # acceptance filter APIs
 #############################################################################*/

/*******************************************************************************
 * Function Name : R_RSCFD_ClearRxRules
 * Description   : Resets Acceptance Filter counts and destinations.RSCFD units
 *               : must be in RESET mode before calling this API
 * Parameters    : unit         = CAN unit being modified
 *               : rx_rules_cnt = number of receive rules being to be used.
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_ClearRxRules(rscfd_unit_t unit, uint8 rx_rules_cnt)
{
    uint8 i;

    /* Clear the number of receive rules assigned to each channel */
    RSCFD[unit].CFDGAFLCFG[RSCFD_OFST_CFDGAFLCFG_00].HALF = 0;
    RSCFD[unit].CFDGAFLCFG[RSCFD_OFST_CFDGAFLCFG_01].HALF = 0;
    RSCFD[unit].CFDGAFLCFG[RSCFD_OFST_CFDGAFLCFG_10].HALF = 0;
    RSCFD[unit].CFDGAFLCFG[RSCFD_OFST_CFDGAFLCFG_11].HALF = 0;
    RSCFD[unit].CFDGAFLCFG[RSCFD_OFST_CFDGAFLCFG_20].HALF = 0;
    RSCFD[unit].CFDGAFLCFG[RSCFD_OFST_CFDGAFLCFG_21].HALF = 0;
    RSCFD[unit].CFDGAFLCFG[RSCFD_OFST_CFDGAFLCFG_30].HALF = 0;
    RSCFD[unit].CFDGAFLCFG[RSCFD_OFST_CFDGAFLCFG_31].HALF = 0;

    /* FIXME: This does not take the paging into account. */
    for (i = 0; i < rx_rules_cnt; i++)
    {
        /* Clear receive rule destination pointers */
        RSCFD[unit].RRULE[i].CFDGAFLP1.WORD = 0;
        RSCFD[unit].RRULE[i].CFDGAFLP0.WORD = 0;
    }
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxRulePage
 * Description   : Return Acceptance Filter Page enumeration used by
 *               : this driver APIs
 * Parameters    : unitno    = RSCFD unit number
 *               : ruleno    = rule number within unit (0-1535)
 * Returns       : returns RX page
 ******************************************************************************/
rscfd_rx_page_t R_RSCFD_GetRxRulePage(uint8 unitno, uint16 ruleno)
{
    uint32 rno;

    /* use rule number limited to 1535 per HW limits */
    rno = (ruleno > RSCFD_MASK_RULE_MAX) ? RSCFD_MASK_RULE_MAX : ruleno;
    return RSCFD_MAKE_RXPAGE(unitno, rno);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetRxRuleWriteEn
 * Description   : Enable writes to Acceptance Filter List (AFL)
 *               : Register GAFLECTR bit field AFLDAE.
 * Parameters    : unit  = CAN unit being configured.
 *               : wr_en = Write Enable (1) or Disable (0)
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetRxRuleWriteEn(rscfd_unit_t unit, rscfd_rx_rule_wr_t wr_en)
{
    /* enable/disable write access to receive rules */
    RMW32(RSCFD[unit].CFDGAFLECTR.WORD, RSCFD_MASK_CFDGAFLECTR_AFLDAE, wr_en);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetRxRulePage
 * Description   : Select Acceptance Filter page. Up to 16 Acceptance Filters
 *               : can be configured per page. Modifies register GAFLECTR
 *               : bit field AFLPN.
 * Parameters    : unit = CAN unit being configured.
 *               : page = enumeration of Page number
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetRxRulePage(rscfd_unit_t unit, rscfd_rx_page_t page)
{
    /* set receive rule page */
    RMW32(RSCFD[unit].CFDGAFLECTR.WORD, RSCFD_MASK_CFDGAFLECTR_AFLPN, page);
}


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
void R_RSCFD_SetRxRuleId(rscfd_unit_t unit,
                         rscfd_rx_rule_t rule_num,
                         uint32 rx_rule_id,
                         rscfd_id_type_t id_type)
{
    uint32 msk;
    uint32 cfg;

    /* bits to update */
    msk  = RSCFD_MASK_CFDGAFLID_GAFLID | RSCFD_MASK_CFDGAFLID_GAFLIDE;
    msk |= RSCFD_MASK_CFDGAFLID_GAFLRTR;

    /* configure message ID rule */
    cfg = (rx_rule_id & RSCFD_MASK_CFDGAFLID_GAFLID) | (uint32)id_type;
    RMW32(RSCFD[unit].RRULE[rule_num].CFDGAFLID.WORD, msk, cfg);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetRxRuleIdMask
 * Description   : Set message ID mask for requested Acceptance Filter.
 *               : Only bits set to one are evaluated by Acceptance Filter.
 *               : Register GAFLMj bit field GAFLIDM.
 * Parameters    : unit         = CAN unit being configured.
 *               : rule_num     = enumeration of Rule Number (0-15)
 *               : mask_id      = mask for ID matching
 *               : mas_id_type  = rule for standard/extended CAN ID
 * Returns       : none
 * Note          : This API must be called when RSCFD units are in RESET mode
 *               : and writing to Acceptance Filter List is enabled.
 ******************************************************************************/
void R_RSCFD_SetRxRuleIdMask(rscfd_unit_t unit,
                             rscfd_rx_rule_t rule_num,
                             uint32 mask_id,
                             rscfd_rx_id_type_mask_t mask_id_type)
{
    uint32 cfg;
    uint32 msk;

    /* bit fields to update */
    msk  = RSCFD_MASK_CFDGAFLM_GAFLIDM | RSCFD_MASK_CFDGAFLM_GAFLIDEM;
    msk |= RSCFD_MASK_CFDGAFLM_GAFLRTRM;

    /* configure ID mask rule */
    cfg = (mask_id & RSCFD_MASK_CFDGAFLM_GAFLIDM) | (uint32)mask_id_type;
    RMW32(RSCFD[unit].RRULE[rule_num].CFDGAFLM.WORD, msk, cfg);
}


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
void R_RSCFD_SetRxRulePtr(rscfd_unit_t unit,
                          rscfd_rx_rule_t rule_num,
                          uint16 rx_ptr)
{
    uint32 msk;
    uint32 cfg;

    /* bits to update */
    msk = RSCFD_MASK_CFDGAFLP0_GAFLPTR;

    /* update label for the requested rule */
    cfg = ((uint32)rx_ptr) << RSCFD_OFST_16BIT;
    RMW32(RSCFD[unit].RRULE[rule_num].CFDGAFLP0.WORD, msk, cfg);
}


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
void R_RSCFD_SetRxRuleLabel(rscfd_unit_t unit,
                            rscfd_rx_rule_t rule_num,
                            rscfd_label_t rx_label)
{
    uint32 msk;
    uint32 cfg;
    uint32 lbl;

    /* the label bit mapping for Acceptance Filters is different
     * than mapping for other registers. Remove default bit mapping */
    lbl = (uint32)(((uint32)rx_label) >> RSCFD_OFST_8BIT);

    /* 2-bit label is split between CFDGAFLP0 (b0 of of the label 0)
     * and CFDGAFLP1 (b1 of the label) bits to update in CFDGAFLP0 */
    msk = RSCFD_MASK_CFDGAFLP0_GAFLIFL0;

    /* configure b0 of label (CFDGAFLP0) */
    cfg = (lbl & RSCFD_MASK_1BIT) << RSCFD_OFST_7BIT;
    RMW32(RSCFD[unit].RRULE[rule_num].CFDGAFLP0.WORD, msk, cfg);

    /* bits to update in CFDGAFLP1 */
    msk = RSCFD_MASK_CFDGAFLM_GAFLIFL1;

    /* configure ID b1 of label (CFDGAFLM)
     * NOTE: b29 but shift by 28 bits because b1 of the label */
    cfg = (lbl & RSCFD_MASK_RULE_L1) << RSCFD_OFST_28BIT;
    RMW32(RSCFD[unit].RRULE[rule_num].CFDGAFLM.WORD, msk, cfg);
}


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
void R_RSCFD_SetRxRuleSrc(rscfd_unit_t unit,
                          rscfd_rx_rule_t rule_num,
                          rscfd_rx_src_t source)
{
    uint32 msk;

    /* bits to update */
    msk = RSCFD_MASK_CFDGAFLID_GAFLLB;

    /* update message source rule */
    RMW32(RSCFD[unit].RRULE[rule_num].CFDGAFLID.WORD, msk, source);
}


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
void R_RSCFD_SetRxRuleMinDlc(rscfd_unit_t unit,
                             rscfd_rx_rule_t rule_num,
                             rscfd_dlc_t min_dlc)
{
    uint32 msk;
    uint32 cfg;

    /* bit fields to update */
    msk = RSCFD_MASK_CFDGAFLP0_GAFLDLC;

    /* configure minimum DLC */
    cfg = ((uint32)min_dlc) >> RSCFD_OFST_28BIT;
    RMW32(RSCFD[unit].RRULE[rule_num].CFDGAFLP0.WORD, msk, cfg);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetRxRuleDest
 * Description   : configure destination for message meeting requested
 *               : Acceptance Filter criteria. The destination can be either
 *               : RXFIFO (0..7) or RX buffer (0..127).
 * Parameters    : unit      = CAN unit being configured.
 *               : rule_num  = enumeration of Rule Number (0-15).
 *               : rule_dst  = which Rx FIFO or buffer will receive message
 * Returns       : none
 * Note          : This API must be called when RSCFD units are in RESET mode
 *               : and writing to Acceptance Filter List is enabled.
 ******************************************************************************/
void R_RSCFD_SetRxRuleDest(rscfd_unit_t unit,
                           rscfd_rx_rule_t rule_num,
                           rscfd_rx_dst_t rule_dst)
{
    uint32 cfg;
    uint32 msk;
    uint8  rx_buff;
    uint8  rx_fifo;

    /* which destination */
    if (RSCFD_RX_BUFF == RSCFD_GET_RXDEST(rule_dst))
    {
        /* destination is RX buffer, which buffer
         * NOTE: CFDGAFLP0 bit fields GAFLRMV and GAFLRMDP define RX buffer */
        rx_buff = RSCFD_GET_RXBUFF(rule_dst);

        /* CFDGAFLP0 to update */
        msk  = RSCFD_MASK_CFDGAFLP0_GAFLRMV | RSCFD_MASK_CFDGAFLP0_GAFLRMDP;
        msk |= RSCFD_MASK_CFDGAFLP0_GAFLSRD0 | RSCFD_MASK_CFDGAFLP0_GAFLSRD1;
        msk |= RSCFD_MASK_CFDGAFLP0_GAFLSRD2;

        /* configure RX buffer as Acceptance Filter destination */
        cfg = RSCFD_MASK_CFDGAFLP0_GAFLRMV | (rx_buff << RSCFD_OFST_8BIT);
        RMW32(RSCFD[unit].RRULE[rule_num].CFDGAFLP0.WORD, msk, cfg);

        /* clear CFDGAFLP1 to ensure no RXFIFO are enabled as destinations */
        RMW32(RSCFD[unit].RRULE[rule_num].CFDGAFLP1.WORD, RSCFD_MASK_32BIT, 0);
    }
    else
    {
        /* destination is RXFIFO, which RX FIFO
         * NOTE CFDGAFLP0 and CFDGAFLP1 are required */
        rx_fifo = RSCFD_GET_RXFIFO(rule_dst);

        /* CFDGAFLP0 to update */
        msk  = RSCFD_MASK_CFDGAFLP0_GAFLRMV | RSCFD_MASK_CFDGAFLP0_GAFLSRD0;
        msk |= RSCFD_MASK_CFDGAFLP0_GAFLSRD1 | RSCFD_MASK_CFDGAFLP0_GAFLSRD2;

        /* configure RXFIFO as Acceptance Filter destination */
        RMW32(RSCFD[unit].RRULE[rule_num].CFDGAFLP0.WORD, msk, 0);

        /* configure which RXFIFO */
        cfg = (uint32)(RSCFD_MASK_1BIT << rx_fifo);
        RMW32(RSCFD[unit].RRULE[rule_num].CFDGAFLP1.WORD, msk, cfg);
    }
}


/*******************************************************************************
 * Function Name : R_RSCFD_InitRxRulesRst
 * Description   : Initializations of RSCFD Acceptance Filter List (AFL). This
 *               : API must be called when RSCFD units are in RESET mode.
 * Parameters    : cfg          = user configurations
 *               : cfg_cnt      = number of rules to be configured
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_InitRxRulesRst(const rscfd_rx_rule_cfg_t cfg[], uint8 cfg_cnt)
{
    rscfd_unit_t    unit;
    rscfd_rx_rule_t rule;
    uint8           r;

    for (r = 0; r < cfg_cnt; r++)
    {
        /* which unit and which rule
         * NOTE: access optimization */
        unit = (rscfd_unit_t)RSCFD_GET_UNIT(cfg[r].page);
        rule = cfg[r].rule;

        /* enable write access and select page */
        R_RSCFD_SetRxRuleWriteEn(unit, RSCFD_RX_RULE_WR_EN);
        R_RSCFD_SetRxRulePage(unit, RSCFD_GET_RXPAGE(cfg[r].page));

        /* configure
         *   - rule ID/ID size,
         *   - rule ID/ID size mask
         *   - rule DLC,
         *   - rule label,
         *   - message source,
         *   - message destination */
        R_RSCFD_SetRxRuleId(unit, rule, cfg[r].id, cfg[r].id_type);
        R_RSCFD_SetRxRuleIdMask(unit, rule, cfg[r].mask_id, cfg[r].mask_id_type);

        R_RSCFD_SetRxRuleMinDlc(unit, rule, cfg[r].min_dlc);
        R_RSCFD_SetRxRulePtr(unit, rule, (uint16)cfg[r].ptr);
        R_RSCFD_SetRxRuleSrc(unit, rule, cfg[r].source);
        R_RSCFD_SetRxRuleDest(unit, rule, cfg[r].dest);

        /* disable write access */
        R_RSCFD_SetRxRuleWriteEn(unit, RSCFD_RX_RULE_WR_DIS);
    }
}


/*##############################################################################
 # RXFIFO APIs
 #############################################################################*/

/*******************************************************************************
 * Function Name : R_RSCFD_ClearRxFifoStat
 * Description   : Clear select status in requested RXFIFO. Status RFFLL
 *               : (RXFIFO full) and RFEMP (RXFIFO empty) cannot be cleared
 *               : using this API.
 * Parameters    : fifo_num   = RSCFD unit and RX FIFO
 *               : fifo_stat  = RX FIFO status to clear
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_ClearRxFifoStat(rscfd_rx_fifo_t fifo_num,
                             rscfd_rx_fifo_stat_t fifo_stat)
{
    uint8 unit;
    uint8 fifo;

    /* which unit and RX FIFO */
    unit = RSCFD_GET_UNIT(fifo_num);
    fifo = RSCFD_GET_RXFIFO(fifo_num);

    /* clear requested status in requested RXFIFO
     * NOTE: not all status bits can be cleared by software */
    RMW32(RSCFD[unit].CFDRFSTS[fifo].WORD, fifo_stat, 0);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgId
 * Description   : return message ID in requested RXFIFO
 * Parameters    : rx_fifo     = RSCFD unit and RXFIFO
 * Returns       : message ID in requested RXFIFO
 ******************************************************************************/
uint32 R_RSCFD_GetRxFifoMsgId(rscfd_rx_fifo_t rx_fifo)
{
    uint32 msg_id;
    uint8  unit;
    uint8  fifo;

    unit = RSCFD_GET_UNIT(rx_fifo);
    fifo = RSCFD_GET_RXFIFO(rx_fifo);

    /* return message ID as 29-bit number */
    msg_id = RSCFD[unit].RFIFO[fifo].CFDRFID.WORD;
    return (uint32)(msg_id & RSCFD_MASK_CFDRFID_RFID);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgIdType
 * Description   : return message ID type (DTS/EXT, NORM/RTR) in requested
 *               ; RXFIFO
 * Parameters    : rx_fifo     = RSCFD unit and RXFIFO
 * Returns       : message IDE size in requested RXFIFO
 ******************************************************************************/
rscfd_id_type_t R_RSCFD_GetRxFifoMsgIdType(rscfd_rx_fifo_t rx_fifo)
{
    uint32 msk;
    uint8  unit;
    uint8  fifo;

    unit = RSCFD_GET_UNIT(rx_fifo);
    fifo = RSCFD_GET_RXFIFO(rx_fifo);

    /* bits to return */
    msk = RSCFD_MASK_CFDRFID_RFIDE | RSCFD_MASK_CFDRFID_RFRTR;

    /* return message IDE */
    return (rscfd_id_type_t)(RSCFD[unit].RFIFO[fifo].CFDRFID.WORD & msk);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgDlc
 * Description   : return message DLC in requested RXFIFO
 * Parameters    : rx_fifo     = RSCFD unit and RXFIFO
 * Returns       : message DLC in requested RXFIFO
 ******************************************************************************/
rscfd_dlc_t R_RSCFD_GetRxFifoMsgDlc(rscfd_rx_fifo_t rx_fifo)
{
    uint32 dlc;
    uint8  unit;
    uint8  fifo;

    unit = RSCFD_GET_UNIT(rx_fifo);
    fifo = RSCFD_GET_RXFIFO(rx_fifo);

    /* retrieve DLC from RX FIFO register */
    dlc = RSCFD[unit].RFIFO[fifo].CFDRFPTR.WORD & RSCFD_MASK_CFDRFPTR_RFDLC;
    return (rscfd_dlc_t)dlc;
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgPtr
 * Description   : return message pointer in requested RXFIFO
 * Parameters    : rx_fifo     = RSCFD unit and RXFIFO
 * Returns       : message pointer in requested RXFIFO
 ******************************************************************************/
uint16 R_RSCFD_GetRxFifoMsgPtr(rscfd_rx_fifo_t rx_fifo)
{
    uint32 cfg;
    uint8  unit;
    uint8  fifo;

    unit = RSCFD_GET_UNIT(rx_fifo);
    fifo = RSCFD_GET_RXFIFO(rx_fifo);

    /* return 16-bit label */
    cfg = RSCFD[unit].RFIFO[fifo].CFDRFFDSTS.WORD >> RSCFD_OFST_16BIT;
    return (uint16)cfg;
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgLabel
 * Description   : return message label in requested RX FIFO
 * Parameters    : rx_fifo     = RSCFD unit and RX FIFO
 * Returns       : message label in requested RXFIFO
 ******************************************************************************/
rscfd_label_t R_RSCFD_GetRxFifoMsgLabel(rscfd_rx_fifo_t rx_fifo)
{
    uint32 label;
    uint8  unit;
    uint8  fifo;

    unit = RSCFD_GET_UNIT(rx_fifo);
    fifo = RSCFD_GET_RXFIFO(rx_fifo);

    /* return message label */
    label = RSCFD[unit].RFIFO[fifo].CFDRFFDSTS.WORD;
    return (rscfd_label_t)(label & RSCFD_MASK_CFDRFFDSTS_RFIFL);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgTimestamp
 * Description   : return message time stamp in requested RXFIFO
 * Parameters    : rx_fifo     = RSCFD unit and RXFIFO
 * Returns       : message time stamp in requested RXFIFO
 ******************************************************************************/
uint16 R_RSCFD_GetRxFifoMsgTimestamp(rscfd_rx_fifo_t rx_fifo)
{
    uint8 unit;
    uint8 fifo;

    unit = RSCFD_GET_UNIT(rx_fifo);
    fifo = RSCFD_GET_RXFIFO(rx_fifo);

    /* return RXFIFO time stamp as 16-bit value */
    return (uint16)RSCFD[unit].RFIFO[fifo].CFDRFPTR.WORD;
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgPayload
 * Description   : return message payload in requested RXFIFO
 * Parameters    : rx_fifo     = RSCFD unit and RX FIFO
 *               : payload     = buffer to copy message data to
 * Returns       : number of bytes in message payload
 ******************************************************************************/
rscfd_payload_size_t R_RSCFD_GetRxFifoMsgPayload(rscfd_rx_fifo_t rx_fifo,
                                                 rscfd_payload_t * payload)
{
    volatile rscfd_st5_regmap_t * rfifo;
    rscfd_dlc_t                   dlc;
    uint8                         word_cnt;
    uint8                         w;

    /* shortcut to requested RXFIFO */
    rfifo = RSCFD[RSCFD_GET_UNIT(rx_fifo)].RFIFO + RSCFD_GET_RXFIFO(rx_fifo);

    /* get RXFIFO DLC */
    dlc = R_RSCFD_GetRxFifoMsgDlc(rx_fifo);

    /* copy payload from RXFIFO to provided memory buffer
     * NOTE: for efficiency use 32-bit words */
    word_cnt = R_RSCFD_GetPayloadWordCnt(dlc);
    for (w = 0; w < word_cnt; w++)
    {
        /* copy as 32-bit words */
        payload[0].WORD[w] = rfifo[0].CFDRFDF[w].WORD;
    }

    /* return number of bytes in copied payload */
    return R_RSCFD_GetPayloadByteCnt(dlc);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoIrqStat
 * Description   : See if this RXFIFO has an interrupt request pending.
 * Parameters    : fifo_num = RSCFD unit and RX FIFO
 * Returns       : enumeration of interrupt present/not present.
 ******************************************************************************/
rscfd_fifo_irq_t R_RSCFD_GetRxFifoIrqStat(rscfd_rx_fifo_t fifo_num)
{
    uint32 msk;
    uint8  unit;
    uint8  fifo;

    /* which unit and RX FIFO */
    unit = RSCFD_GET_UNIT(fifo_num);
    fifo = RSCFD_GET_RXFIFO(fifo_num);

    /* which RX FIFO */
    msk = (uint32)(RSCFD_MASK_1BIT << fifo);
    return (rscfd_fifo_irq_t)((RSCFD[unit].CFDRFISTS.WORD & msk) != 0);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoStat
 * Description   : retrieve status of selected RX FIFO
 * Parameters    : fifo_num   = RSCFD unit and RX FIFO
 * Returns       : RX FIFO status
 ******************************************************************************/
rscfd_rx_fifo_stat_t R_RSCFD_GetRxFifoStat(rscfd_rx_fifo_t fifo_num)
{
    uint32 cfg;
    uint8  unit;
    uint8  fifo;

    /* which unit and RX FIFO */
    unit = RSCFD_GET_UNIT(fifo_num);
    fifo = RSCFD_GET_RXFIFO(fifo_num);

    /* return status bits only */
    cfg = RSCFD[unit].CFDRFSTS[fifo].WORD & RSCFD_RX_FIFO_STAT_ALL;
    return (rscfd_rx_fifo_stat_t)cfg;
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxFifoMsgCnt
 * Description   : retrieve number of messages in requested RX FIFO
 * Parameters    : fifo_num   = RSCFD unit and RX FIFO
 * Returns       : number of messages in requested RXFIFO
 ******************************************************************************/
uint8 R_RSCFD_GetRxFifoMsgCnt(rscfd_rx_fifo_t fifo_num)
{
    uint8 unit;
    uint8 fifo;

    /* which unit and RX FIFO */
    unit = RSCFD_GET_UNIT(fifo_num);
    fifo = RSCFD_GET_RXFIFO(fifo_num);

    /* return number of messages in RXFIFO */
    return (uint8)(RSCFD[unit].CFDRFSTS[fifo].WORD >> RSCFD_OFST_8BIT);
}


/*******************************************************************************
 * Function Name : R_RSCFD_ReadRxFifo
 * Description   : Example of reading complete RXFIFO using driver APIs. If
 *               : RXFIFO is not empty beside reading the message this API
 *               : will also move RXFIFO pointer to next unread message
 * Parameters    : rx_fifo     = RSCFD unit and RX FIFO
 *               : msg         = structure to store message
 * Returns       : RXFIFO status prior to reading the message
 ******************************************************************************/
rscfd_rx_fifo_stat_t R_RSCFD_ReadRxFifo(rscfd_rx_fifo_t rx_fifo,
                                        rscfd_msg_t * msg)
{
    rscfd_rx_fifo_stat_t stat;

    /* what is RXFIFO status */
    stat = R_RSCFD_GetRxFifoStat(rx_fifo);
    if (!(stat & RSCFD_RX_FIFO_STAT_EMPTY))
    {
        /* not empty, read next message from RX FIFO */
        msg[0].id      = R_RSCFD_GetRxFifoMsgId(rx_fifo);
        msg[0].id_type = R_RSCFD_GetRxFifoMsgIdType(rx_fifo);
        msg[0].ptr     = R_RSCFD_GetRxFifoMsgPtr(rx_fifo);
        msg[0].label   = R_RSCFD_GetRxFifoMsgLabel(rx_fifo);
        msg[0].bytes   = R_RSCFD_GetRxFifoMsgPayload(rx_fifo, msg[0].payload);

        /* move RXFIFO pointer to next unread message */
        R_RSCFD_SetRxFifoNext(rx_fifo);
    }

    /* what happened */
    return stat;
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetRxFifoNext
 * Description   : move RXFIFO pointer to next unread message
 * Parameters    : rx_fifo     = RSCFD unit and RX FIFO
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetRxFifoNext(rscfd_rx_fifo_t rx_fifo)
{
    uint8 unit;
    uint8 fifo;

    unit = RSCFD_GET_UNIT(rx_fifo);
    fifo = RSCFD_GET_RXFIFO(rx_fifo);

    /* Update Rx FIFO pointer to next unread message */
    RSCFD[unit].CFDRFPCTR[fifo].WORD = RSCFD_MASK_CFDRFPCTR_RFPC;
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetRxFifoIrq
 * Description   : Select message RX FIFO interrupt trigger (none, on every
 *               : message, when RXFIFO filled up to configured level)
 * Parameters    : fifo_num    = RSCFD unit and FIFO (0-7)
 *               : irq         = interrupt configuration
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetRxFifoIrq(rscfd_rx_fifo_t fifo_num, rscfd_rx_fifo_int_t irq)
{
    uint32 msk;
    uint8  unit;
    uint8  fifo;

    /* which unit and RX FIFO */
    unit = RSCFD_GET_UNIT(fifo_num);
    fifo = RSCFD_GET_RXFIFO(fifo_num);

    /* bits to modify */
    msk  = RSCFD_MASK_CFDRFCC_RFIE | RSCFD_MASK_CFDRFCC_RFIM;
    msk |= RSCFD_MASK_CFDRFCC_RFIGCV;

    /* enable interrupts */
    RMW32(RSCFD[unit].CFDRFCC[fifo].WORD, msk, irq);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetRxFifoSize
 * Description   : Set depth of RXFIFO. Modifies register RFCCx
 *               : bit fields RFDC and RFPLS.
 * Parameters    : fifo_num     = RSCFD unit and RX FIFO (0-7)
 *               : depth        = Rx FIFO buffer depth (0-128)
 *               : payload_size = Rx FIFO buffer data size (8-64)
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetRxFifoSize(rscfd_rx_fifo_t fifo_num,
                           rscfd_rfdc_t depth,
                           rscfd_fpls_t payload_size)
{
    uint32 msk;
    uint8  unit;
    uint8  fifo;

    /* which RSCFD unit and FIFO */
    unit = RSCFD_GET_UNIT(fifo_num);
    fifo = RSCFD_GET_RXFIFO(fifo_num);

    /* bits to update */
    msk = RSCFD_MASK_CFDRFCC_RFPLS | RSCFD_MASK_CFDRFCC_RFDC;

    /* configure RX FIFO depth and payload */
    RMW32(RSCFD[unit].CFDRFCC[fifo].WORD, msk, (payload_size | depth));
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetRxFifoEn
 * Description   : Enable/Disable use of requested RXFIFO.
 *               : Modifies register RFCCx bit field RFE.
 * Parameters    : fifo_num       = RSCFD unit and Rx FIFO number (0-7)
 *               : enabled        = RFE bit setting (enabled/disabled)
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetRxFifoEn(rscfd_rx_fifo_t fifo_num, rscfd_fifo_en_t enable)
{
    uint8 unit;
    uint8 fifo;

    /* which RSCFD unit and RX FIFO */
    unit = RSCFD_GET_UNIT(fifo_num);
    fifo = RSCFD_GET_RXFIFO(fifo_num);

    /* enable/disable RX FIFO functionality */
    RMW32(RSCFD[unit].CFDRFCC[fifo].WORD, RSCFD_MASK_CFDRFCC_RFE, enable);
}


/*******************************************************************************
 * Function Name : R_RSCFD_InitRxFifoRst
 * Description   : Initializations of RXFIFO. This API must be called
 *               : when RSCFD units are in RESET mode.
 * Parameters    : cfg          = user RX FIFO configurations
 *               : cfg_cnt      = number of RX FIFOs to configure
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_InitRxFifoRst(const rscfd_rx_fifo_cfg_t cfg[], uint8 cfg_cnt)
{
    rscfd_rx_fifo_t fifo;
    uint8           f;

    /* Rx FIFO Configurations */
    for (f = 0; f < cfg_cnt; f++)
    {
        /* which RX FIFO
         * NOTE: slight optimization */
        fifo = cfg[f].num;

        /* configure RX FIFO interrupts and size */
        R_RSCFD_SetRxFifoIrq(fifo, cfg[f].irq);
        R_RSCFD_SetRxFifoSize(fifo, cfg[f].depth, cfg[f].msg_length);
    }
}


/*******************************************************************************
 * Function Name : R_RSCFD_InitRxFifoOper
 * Description   : Initializations of RXFIFOs. This API must be called when
 *               : RSCFD units are in OPERATIONAL mode.
 * Parameters    : cfg           = configuration of RX FIFOs
 *               : cfg_cnt       = number of RX FIFOs to be configured
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_InitRxFifoOper(const rscfd_rx_fifo_cfg_t cfg[], uint8 cfg_cnt)
{
    uint8 f;

    /* Enable Rx FIFOs */
    for (f = 0; f < cfg_cnt; f++)
    {
        /* enable RX FIFO operation */
        R_RSCFD_SetRxFifoEn(cfg[f].num, RSCFD_FIFO_EN);
    }
}


/*##############################################################################
 # TXFIFO APIs
 #############################################################################*/

/*******************************************************************************
 * Function Name : R_RSCFD_ClearTxFifoStat
 * Description   : Clear select status of requested TXFIFO. Status
 *               : CFFLL (TXFIFO full) and CFEMP (TXFIFO empty) cannot be
 *               : cleared by this API.
 * Parameters    : fifo_num = RSCFD unit and TX FIFO
 *               : fifo_stat   = TX FIFO status bits to clear
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_ClearTxFifoStat(rscfd_tx_fifo_t fifo_num,
                             rscfd_tx_fifo_stat_t fifo_stat)
{
    uint8 unit;
    uint8 fifo;

    /* which unit and channel */
    unit = RSCFD_GET_UNIT(fifo_num);
    fifo = RSCFD_GET_TXFIFO(fifo_num);

    /* Clear TXFIFO status bits
     * NOTE: Not all TXFIFO status bits can be cleared by software */
    RMW32(RSCFD[unit].CFDCFSTS[fifo].WORD, fifo_stat, 0);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetTxFifoIrqStat
 * Description   : See if this Tx FIFO has an interrupt request present.
 * Parameters    : fifo_num = RSCFD unit and TX FIFO
 * Returns       : Enumeration of interrupt present vs not present.
 ******************************************************************************/
rscfd_fifo_irq_t R_RSCFD_GetTxFifoIrqStat(rscfd_tx_fifo_t fifo_num)
{
    uint32 msk;
    uint8  unit;
    uint8  fifo;

    /* which unit and TX FIFO */
    unit = RSCFD_GET_UNIT(fifo_num);
    fifo = RSCFD_GET_TXFIFO(fifo_num);

    /* which TX FIFO */
    msk = (uint32)(RSCFD_MASK_1BIT << fifo);
    return (rscfd_fifo_irq_t)((RSCFD[unit].CFDCFTISTS.WORD & msk) != 0);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetTxFifoStat
 * Description   : Return status of requested TXFIFO
 * Parameters    : tx_fifo     = RSCFD unit and TXFIFO
 * Returns       : status of requested TXFIFO
 ******************************************************************************/
rscfd_tx_fifo_stat_t R_RSCFD_GetTxFifoStat(rscfd_tx_fifo_t tx_fifo)
{
    uint32 cfg;
    uint8  unit;
    uint8  fifo;

    unit = RSCFD_GET_UNIT(tx_fifo);
    fifo = RSCFD_GET_TXFIFO(tx_fifo);

    /* which bit fields to return */
    cfg = (RSCFD[unit].CFDCFSTS[fifo].WORD & RSCFD_TX_FIFO_STAT_ALL);
    return (rscfd_tx_fifo_stat_t)cfg;
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoMode
 * Description   : Set RX/TX FIFO to RX, TX, or Gateway Mode.
 *               : Modifies register CFCCx bit field CFM.
 * Parameters    : fifo_num       = RSCFD unit and FIFO
 *               : fifo_mode      = FIFO mode (RX, TX, or Gateway)
 * Returns       : none
 * Note          : Driver uses only RSCFD_RXTX_FIFO_TX mode
 ******************************************************************************/
void R_RSCFD_SetTxFifoMode(rscfd_tx_fifo_t fifo_num,
                           rscfd_rxtx_fifo_mode_t fifo_mode)
{
    uint8 unit;
    uint8 fifo;

    /* which unit and FIFO */
    unit = RSCFD_GET_UNIT(fifo_num);
    fifo = RSCFD_GET_TXFIFO(fifo_num);

    /* assign FIFO mode */
    RMW32(RSCFD[unit].CFDCFCC[fifo].WORD, RSCFD_MASK_CFDCFCC_CFM, fifo_mode);
}


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
void R_RSCFD_SetTxFifoLink(rscfd_tx_fifo_t fifo_num,
                           rscfd_tx_fifo_buff_t buf_fifo)
{
    uint8 unit;
    uint8 fifo;

    /* which unit and TX FIFO */
    unit = RSCFD_GET_UNIT(fifo_num);
    fifo = RSCFD_GET_TXFIFO(fifo_num);

    /* assign buffer to selected TX FIFO */
    RMW32(RSCFD[unit].CFDCFCC[fifo].WORD, RSCFD_MASK_CFDCFCC_CFTML, buf_fifo);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoSize
 * Description   : Set depth of requested TXFIFO. Modifies register CFCCx
 *               : bit fields CFDC and CFPLS.
 * Parameters    : fifo_num     = unit and TX FIFO number
 *               : fifo_depth   = Tx FIFO buffer depth
 *               : payload_size = Tx FIFO buffer length
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetTxFifoSize(rscfd_tx_fifo_t fifo_num,
                           rscfd_cfdc_t fifo_depth,
                           rscfd_fpls_t payload_size)
{
    uint32 msk;
    uint8  unit;
    uint8  fifo;

    /* which RSCFD unit and FIFO */
    unit = RSCFD_GET_UNIT(fifo_num);
    fifo = RSCFD_GET_TXFIFO(fifo_num);

    /* bits to update */
    msk = RSCFD_MASK_CFDCFCC_CFPLS | RSCFD_MASK_CFDCFCC_CFDC;

    /* configure FIFO depth and payload */
    RMW32(RSCFD[unit].CFDCFCC[fifo].WORD, msk, (payload_size | fifo_depth));
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoIrq
 * Description   : Select message interrupt trigger (none, on every message,
 *               : when TXFIFO becomes empty) for a requested TXFIFO
 *               : (transmission)
 * Parameters    : fifo_num     = RSCFD unit and FIFO
 *               : tx_fifo_int  = interrupt configuration
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetTxFifoIrq(rscfd_tx_fifo_t fifo_num,
                          rscfd_tx_fifo_int_t tx_fifo_int)
{
    uint32 msk;
    uint8  unit;
    uint8  fifo;

    /* which unit and FIFO */
    unit = RSCFD_GET_UNIT(fifo_num);
    fifo = RSCFD_GET_TXFIFO(fifo_num);

    /* bits to change */
    msk = RSCFD_MASK_CFDCFCC_CFTXIE | RSCFD_MASK_CFDCFCC_CFIM;

    /* configure FIFO interrupts */
    RMW32(RSCFD[unit].CFDCFCC[fifo].WORD, msk, tx_fifo_int);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoEn
 * Description   : Enable/disable requested TXFIFO
 *               : Modifies register CFCCx bit field CFE.
 * Parameters    : fifo_num   = RSCFD unit and TX FIFO (0-14)
 *               : enable     = enumeration of CFE bit (1=enabled)
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetTxFifoEn(rscfd_tx_fifo_t fifo_num,
                         rscfd_fifo_en_t enable)
{
    uint8 unit;
    uint8 fifo;

    /* which unit and TX FIFO */
    unit = RSCFD_GET_UNIT(fifo_num);
    fifo = RSCFD_GET_TXFIFO(fifo_num);

    /* enable/disable TX FIFOs */
    RMW32(RSCFD[unit].CFDCFCC[fifo].WORD, RSCFD_MASK_CFDCFCC_CFE, enable);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoMsgMode
 * Description   : Select TXFIFO mode and speed (classical, FD slow/fast)
 * Parameters    : tx_fifo     = RSCFD unit and TX FIFO
 *               : rscfd_type  = message type and payload speed
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetTxFifoMsgMode(rscfd_tx_fifo_t tx_fifo,
                              rscfd_msg_mode_t rscfd_type)
{
    uint32 msk;
    uint8  unit;
    uint8  fifo;

    unit = RSCFD_GET_UNIT(tx_fifo);
    fifo = RSCFD_GET_TXFIFO(tx_fifo);

    /* bits to change */
    msk = RSCFD_MASK_CFDCFFDCSTS_CFBRS | RSCFD_MASK_CFDCFFDCSTS_CFFDF;

    /* update transmit mode */
    /* NOTE: classic/FD and payload data Slow/Fast */
    RMW32(RSCFD[unit].TFIFO[fifo].CFDCFFDCSTS.WORD, msk, rscfd_type);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoMsgLabel
 * Description   : Select TXFIFO message label that will be appended to messages
 *               : transmitted using this TXFIFO
 * Parameters    : tx_fifo     = RSCFD unit and TX FIFO
 *               : label       = message label to store w/ message
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetTxFifoMsgLabel(rscfd_tx_fifo_t tx_fifo, rscfd_label_t label)
{
    uint32 cfg;
    uint32 msk;
    uint8  unit;
    uint8  fifo;

    unit = RSCFD_GET_UNIT(tx_fifo);
    fifo = RSCFD_GET_TXFIFO(tx_fifo);

    /* bits to update */
    msk = RSCFD_MASK_CFDCFFDCSTS_CFIFL;

    /* configure 2-bit message label */
    cfg = (uint32)(((uint32)label) << RSCFD_OFST_8BIT);
    RMW32(RSCFD[unit].TFIFO[fifo].CFDCFFDCSTS.WORD, msk, cfg);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoMsgId
 * Description   : Configure message ID type in requested TXFIFO
 *               : and enable entry to the TX history list.
 * Parameters    : tx_fifo     = RSCFD unit and TX FIFO
 *               : id_type     = type of message ID (STD/EXT, NORM/RTR)
 *               : msg_id      = message ID to use
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetTxFifoMsgId(rscfd_tx_fifo_t tx_fifo,
                            rscfd_id_type_t id_type,
                            uint32 msg_id)
{
    uint32 msk;
    uint32 cfg;
    uint8  unit;
    uint8  fifo;

    unit = RSCFD_GET_UNIT(tx_fifo);
    fifo = RSCFD_GET_TXFIFO(tx_fifo);

    /* bits to change */
    msk  = RSCFD_MASK_CFDCFID_CFIDE | RSCFD_MASK_CFDCFID_CFID;
    msk |= RSCFD_MASK_CFDCFID_CFRTR;

    /* Set message ID type */
    cfg  = (msg_id & RSCFD_MASK_CFDCFID_CFID) | (uint32)id_type;
    cfg |= RSCFD_MASK_CFDCFID_THLEN;
    RMW32(RSCFD[unit].TFIFO[fifo].CFDCFID.WORD, msk, cfg);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetTxFifoMsgPayload
 * Description   : Copy message payload into requested TXFIFO
 * Parameters    : tx_fifo     = RSCFD unit and TXFIFO
 *               : bytes       = number of bytes in the payload
 *               : payload     = message payload to populate
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SetTxFifoMsgPayload(rscfd_tx_fifo_t tx_fifo,
                                 rscfd_payload_size_t bytes,
                                 rscfd_payload_t * payload)
{
    volatile rscfd_st6_regmap_t * tfifo;
    rscfd_dlc_t                   dlc;
    uint8                         word_cnt;
    uint8                         w;

    /* shortcut to requested TXFIFO */
    tfifo = RSCFD[RSCFD_GET_UNIT(tx_fifo)].TFIFO + RSCFD_GET_TXFIFO(tx_fifo);

    /* configure TXFIFO DLC
     * NOTE: no protection against DLC > 8 in classical CAN mode */
    dlc = R_RSCFD_GetDlc(bytes);
    RMW32(tfifo[0].CFDCFPTR.WORD, RSCFD_MASK_CFDCFPTR_CFDLC, dlc);

    /* copy in 32-bit increments
     * NOTE: rscfd_payload_t ensures placement on 32-bit boundary */
    word_cnt = R_RSCFD_GetPayloadWordCnt(dlc);
    for (w = 0; w < word_cnt; w++)
    {
        /* copy in 32-bit increments */
        tfifo[0].CFDCFDF[w].WORD = payload[0].WORD[w];
    }
}


/*******************************************************************************
 * Function Name : R_RSCFD_SendTxFifoMsg
 * Description   : Trigger transmission of requested TXFIFO
 * Parameters    : tx_fifo     = RSCFD unit and TX FIFO
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_SendTxFifoMsg(rscfd_tx_fifo_t tx_fifo)
{
    uint8 unit;
    uint8 fifo;

    unit = RSCFD_GET_UNIT(tx_fifo);
    fifo = RSCFD_GET_TXFIFO(tx_fifo);

    /* Trigger transmission of message in TX FIFO */
    RSCFD[unit].CFDCFPCTR[fifo].WORD = RSCFD_MASK_CFDCFPCTR_CFPC;
}


/*******************************************************************************
 * Function Name : R_RSCFD_TxByFifo
 * Description   : Example API of complete TXFIFO transmit sequence using
 *               : driver APIs.
 * Parameters    : tx_fifo     = RSCFD unit and TX FIFO
 *               : rscfd_type  = message type (classic/FD) and payload speed
 *               : msg         = message definition
 * Returns       : status of TXFIFO before sending requested message
 ******************************************************************************/
rscfd_tx_fifo_stat_t R_RSCFD_TxByFifo(rscfd_tx_fifo_t tx_fifo,
                                      rscfd_msg_mode_t rscfd_type,
                                      rscfd_msg_t * msg)
{
    rscfd_tx_fifo_stat_t stat;

    /* what is TXFIFO status*/
    stat = R_RSCFD_GetTxFifoStat(tx_fifo);
    if (!(stat & RSCFD_TX_FIFO_STAT_FULL))
    {
        /* TXFIFO not full, load message to requested TXFIFO */
        R_RSCFD_SetTxFifoMsgMode(tx_fifo, rscfd_type);
        R_RSCFD_SetTxFifoMsgId(tx_fifo, msg[0].id_type, msg[0].id);
        R_RSCFD_SetTxFifoMsgLabel(tx_fifo, msg[0].label);
        R_RSCFD_SetTxFifoMsgPayload(tx_fifo, msg[0].bytes, msg[0].payload);

        /* send message from requested TXFIFO */
        R_RSCFD_SendTxFifoMsg(tx_fifo);
    }

    /* was CAN loaded into requested TX FIFO */
    return stat;
}


/*******************************************************************************
 * Function Name : R_RSCFD_InitTxFifoRst
 * Description   : Initializations of TXFIFO. This API must be called when
 *               : RSCFD units are in RESET mode.
 * Parameters    : cfg         = user TX FIFO configurations
 *               : cfg_cnt     = number of TX FIFO to be configured
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_InitTxFifoRst(const rscfd_tx_fifo_cfg_t cfg[], uint8 cfg_cnt)
{
    rscfd_tx_fifo_t fifo;
    uint8           f;

    /* TX/RX FIFO Configuration - to transmit */
    for (f = 0; f < cfg_cnt; f++)
    {
        /* which TX FIFO to configure
         * NOTE: execution optimization */
        fifo = cfg[f].num;

        /* select TX FIFO mode */
        R_RSCFD_SetTxFifoMode(fifo, RSCFD_RXTX_FIFO_MODE_TX);

        /* assign buffer, depth, message length and interrupts */
        R_RSCFD_SetTxFifoLink(fifo, cfg[f].link_buf);
        R_RSCFD_SetTxFifoSize(fifo, cfg[f].depth, cfg[f].msg_length);
        R_RSCFD_SetTxFifoIrq(fifo, cfg[f].irq);
    }
}


/*******************************************************************************
 * Function Name : R_RSCFD_InitTxFifoOper
 * Description   : Initializations of TXFIFO. This API must be called when
 *               : RSCFD units are in OPERATIONAL mode.
 * Parameters    : tx_fifo_cfg     = user configurations
 *               : tx_fifo_cfg_cnt = number of TXFIFO to be configured
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_InitTxFifoOper(const rscfd_tx_fifo_cfg_t cfg[], uint8 cnt)
{
    uint8 f;

    /* Tx/Rx FIFO Enable - to transmit */
    for (f = 0; f < cnt; f++)
    {
        /* enable configured TX FIFOs */
        R_RSCFD_SetTxFifoEn(cfg[f].num, RSCFD_FIFO_EN);
    }
}


/*##############################################################################
 # RX buffer APIs
 #############################################################################*/

/*******************************************************************************
 * Function Name : R_RSCFD_ClearRxBuffMsgNew
 * Description   : clear new message flag in requested RX buffer
 * Parameters    : rx_buff     = RSCFD unit and RX buffer
 * Returns       : none
 ******************************************************************************/
void R_RSCFD_ClearRxBuffMsgNew(rscfd_rx_buff_t rx_buff)
{
    uint32 msk;
    uint8  ofst;
    uint8  unit;
    uint8  buff;
    uint8  reg;

    /* which unit buffer and new data register */
    unit = RSCFD_GET_UNIT(rx_buff);
    buff = RSCFD_GET_RXBUFF(rx_buff);

    /* calculate the register index and the flag to clear
     * within calculated CFDRMND register
     * NOTE: 32 RX buffers per CFDRMND */
    reg  = buff >> RSCFD_OFST_5BIT;
    ofst = buff - (uint8)(reg << RSCFD_OFST_5BIT);
    msk  = RSCFD_MASK_1BIT << ofst;

    /* Clear new data flag for requested RX buffer
     * NOTE: writing 1b has no effect */
    RSCFD[unit].CFDRMND[reg].WORD = ~msk;
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffId
 * Description   : Compiles unit and buffer index into RX buffer ID
 *               : enumeration used by driver APIs
 * Parameters    : chnl    = RSCFD unit and channel
 *               : numbr   = buffer index within unit (0-127)
 * Returns       : RX buffer ID
 ******************************************************************************/
rscfd_rx_buff_t R_RSCFD_GetRxBuffId(uint8 unitno, uint8 numbr)
{
    /* return RX buffer ID */
    return RSCFD_MAKE_RXBUFF(unitno, (numbr & RSCFD_MASK_6BIT));
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgNew
 * Description   : Check if new message is available in requested RX buffer
 * Parameters    : rx_buff     = RSCFD unit and RX buffer
 * Returns       : 0         = no new data
 *               : otherwise = new data
 ******************************************************************************/
uint8 R_RSCFD_GetRxBuffMsgNew(rscfd_rx_buff_t rx_buff)
{
    uint32 msk;
    uint8  unit;
    uint8  buff;
    uint8  reg;

    /* which unit and RX buffer and new data register */
    unit = RSCFD_GET_UNIT(rx_buff);
    buff = RSCFD_GET_RXBUFF(rx_buff);

    /* calculate register and flag to check
     * NOTE: 32 RX buffers per CFDRMND */
    reg = buff >> RSCFD_OFST_5BIT;
    msk = RSCFD_MASK_1BIT << (buff - (uint8)(reg << RSCFD_OFST_5BIT));

    /* non-zero if new data in requested buffer */
    return (uint8)((RSCFD[unit].CFDRMND[reg].WORD & msk) != 0UL);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgId
 * Description   : Return ID of message in requested RX buffer
 * Parameters    : rx_buff     = RSCFD unit and RX buffer
 * Returns       : ID of received message
 ******************************************************************************/
uint32 R_RSCFD_GetRxBuffMsgId(rscfd_rx_buff_t rx_buff)
{
    uint8 unit;
    uint8 buff;

    unit = RSCFD_GET_UNIT(rx_buff);
    buff = RSCFD_GET_RXBUFF(rx_buff);

    /* return 29 bit message ID
     * NOTE: Bits 28:0 of register RFID[x] */
    return(RSCFD[unit].RBUF[buff].CFDRMID.WORD & RSCFD_MASK_CFDRMID_RMID);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgIdType
 * Description   : Return type of message ID (STD/EXT, NORM/RTR) in requested
 *               : RX buffer
 * Parameters    : rx_buff     = RSCFD unit and RX buffer
 * Returns       : message ID type
 ******************************************************************************/
rscfd_id_type_t R_RSCFD_GetRxBuffMsgIdType(rscfd_rx_buff_t rx_buff)
{
    uint32 msk;
    uint8  unit;
    uint8  buff;

    unit = RSCFD_GET_UNIT(rx_buff);
    buff = RSCFD_GET_RXBUFF(rx_buff);

    /* bits to return */
    msk = RSCFD_MASK_CFDRMID_RMIDE | RSCFD_MASK_CFDRMID_RMRTR;

    /* return size of message ID (standard/extended) */
    return (rscfd_id_type_t)(RSCFD[unit].RBUF[buff].CFDRMID.WORD & msk);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgDlc
 * Description   : Return message DLC for requested RX buffer
 * Parameters    : rx_buff     = RSCFD unit and RX buffer
 * Returns       : message DLC in requested RX buffer
 *****************************************************************************/
rscfd_dlc_t R_RSCFD_GetRxBuffMsgDlc(rscfd_rx_buff_t rx_buff)
{
    uint32 dlc;
    uint8  unit;
    uint8  buff;

    unit = RSCFD_GET_UNIT(rx_buff);
    buff = RSCFD_GET_RXBUFF(rx_buff);

    /* retrieve DLC from requested RX buffer */
    dlc = RSCFD[unit].RBUF[buff].CFDRMPTR.WORD & RSCFD_MASK_CFDRMPTR_RMDLC;
    return (rscfd_dlc_t)dlc;
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgByteCnt
 * Description   : Example of reading message payload byte count from
 *               : requested RX buffer.
 * Parameters    : rx_buff     = RSCFD unit and buffer
 * Returns       : message payload byte count
 *****************************************************************************/
rscfd_payload_size_t R_RSCFD_GetRxBuffMsgByteCnt(rscfd_rx_buff_t rx_buff)
{
    /* translate RX buffer DLC into message payload byte count */
    return R_RSCFD_GetPayloadByteCnt(R_RSCFD_GetRxBuffMsgDlc(rx_buff));
}


/*******************************************************************************
 * Function Name : GetRxBuffMsgPayload
 * Description   : Copy data from requested Rx buffer to specified  memory and
 *               : return number of copied bytes.
 * Parameters    : rx_buff     = RSCFD unit and buffer
 *               : payload     = memory to copy payload to
 * Returns       : number of bytes copied
 ******************************************************************************/
rscfd_payload_size_t R_RSCFD_GetRxBuffMsgPayload(rscfd_rx_buff_t rx_buff,
                                                 rscfd_payload_t * payload)
{
    volatile rscfd_st4_regmap_t * rbuff;
    rscfd_dlc_t                   dlc;
    uint8                         word_cnt;
    uint8                         w;

    /* shortcut to requested RX buffer */
    rbuff = RSCFD[RSCFD_GET_UNIT(rx_buff)].RBUF + RSCFD_GET_RXBUFF(rx_buff);

    /* get RX buffer DLC */
    dlc = R_RSCFD_GetRxBuffMsgDlc(rx_buff);

    /* copy payload from requested RX buffer to provided memory
     * NOTE: for efficiency use 32-bit words */
    word_cnt = R_RSCFD_GetPayloadWordCnt(dlc);
    for (w = 0; w < word_cnt; w++)
    {
        /* copy in 32-bit increments */
        payload[0].WORD[w] = rbuff[0].CFDRMDF[w].WORD;
    }

    /* how many bytes in the message payload */
    return R_RSCFD_GetPayloadByteCnt(dlc);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgPtr
 * Description   : Return message pointer from requested RX buffer
 * Parameters    : rx_buff     = RSCFD unit and buffer
 * Returns       : message pointer in requested RX buffer
 ******************************************************************************/
uint16 R_RSCFD_GetRxBuffMsgPtr(rscfd_rx_buff_t rx_buff)
{
    uint32 msg_ptr;
    uint8  unit;
    uint8  buff;

    unit = RSCFD_GET_UNIT(rx_buff);
    buff = RSCFD_GET_RXBUFF(rx_buff);

    /* Get message pointer
       Bits 27:16 of register RFPTR[x] */
    msg_ptr   = (uint16)RSCFD[unit].RBUF[buff].CFDRMFDSTS.WORD;
    msg_ptr >>= RSCFD_OFST_16BIT;

    /* return as 16-bit message pointer */
    return (uint16)msg_ptr;
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgLabel
 * Description   : Return message label from requested RX buffer
 * Parameters    : rx_buff     = RSCFD unit and buffer
 * Returns       : label of received message
 ******************************************************************************/
rscfd_label_t R_RSCFD_GetRxBuffMsgLabel(rscfd_rx_buff_t rx_buff)
{
    uint32 label;
    uint8  unit;
    uint8  buff;

    unit = RSCFD_GET_UNIT(rx_buff);
    buff = RSCFD_GET_RXBUFF(rx_buff);

    /* Get message label.
       Bits 27:16 of register RFPTR[x] */
    label  = (uint16)RSCFD[unit].RBUF[buff].CFDRMFDSTS.WORD;
    label &= RSCFD_MASK_CFDRMFDSTS_RMIFL;

    /* return 2-bit message label */
    return (rscfd_label_t)label;
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetRxBuffMsgTimestamp
 * Description   : Return time stamp of message in requested RX buffer
 * Parameters    : rx_buff     = RSCFD unit and buffer
 * Returns       : time stamp of message in requested RX buffer
 ******************************************************************************/
uint16 R_RSCFD_GetRxBuffMsgTimestamp(rscfd_rx_buff_t rx_buff)
{
    uint8 unit;
    uint8 buff;

    unit = RSCFD_GET_UNIT(rx_buff);
    buff = RSCFD_GET_RXBUFF(rx_buff);

    /* retrieve 16-bit time stamp from requested RX buffer */
    return (uint16)RSCFD[unit].RBUF[buff].CFDRMPTR.WORD;
}


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
rscfd_result_t R_RSCFD_ReadRxBuff(rscfd_rx_buff_t rx_buff, rscfd_msg_t * msg)
{
    rscfd_result_t stat;

    /* always read RX buffer content even when no new message */
    stat = RSCFD_RESULT_EMPTY;

    /* check if new message in RB buffer */
    if (R_RSCFD_GetRxBuffMsgNew(rx_buff))
    {
        /* yes, clear the flag to detect message override
         * while reading RX buffer */
        R_RSCFD_ClearRxBuffMsgNew(rx_buff);
        stat = RSCFD_RESULT_NEWMSG;
    }

    /* read RX buffer  */
    msg[0].id        = R_RSCFD_GetRxBuffMsgId(rx_buff);
    msg[0].id_type   = R_RSCFD_GetRxBuffMsgIdType(rx_buff);
    msg[0].ptr       = R_RSCFD_GetRxBuffMsgPtr(rx_buff);
    msg[0].label     = R_RSCFD_GetRxBuffMsgLabel(rx_buff);
    msg[0].bytes     = R_RSCFD_GetRxBuffMsgPayload(rx_buff, msg[0].payload);
    msg[0].timestamp = R_RSCFD_GetRxBuffMsgTimestamp(rx_buff);

    /* check if new message arrived while reading RX buffer  */
    if (R_RSCFD_GetRxBuffMsgNew(rx_buff))
    {
        /* yes, RX buffer was overwritten during reading
         * update diagnostic information */
        stat = RSCFD_RESULT_OVERFLOW;
    }

    /* status of read operation (old data, new data, incoherent data) */
    return stat;
}


/*##############################################################################
 # TX buffer APIs
 #############################################################################*/

/*******************************************************************************
 * Function Name : R_RSCFD_GetTxBuffId
 * Description   : Compile channel ID and buffer index into TX buffer ID
 *               : enumeration used by driver APIs
 * Parameters    : chnl    = RSCFD unit and channel
 *               : numbr   = buffer index within channel (0-63)
 * Returns       : TX buffer ID
 ******************************************************************************/
rscfd_tx_buff_t R_RSCFD_GetTxBuffId(rscfd_chnl_t chnl, uint8 numbr)
{
    uint8 unitno;
    uint8 chno;

    /* which unit */
    unitno = RSCFD_GET_UNIT(chnl);
    chno   = RSCFD_GET_CHNL(chnl);

    /* compile TX buffer information */
    return RSCFD_MAKE_TXBUFF(unitno, chno, numbr);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetTxBuffStat
 * Description   : Return status of TX buffer
 * Parameters    : tx_buff       = RSCFD unit and TX buffer
 * Returns       : status of requested TX buffer
 ******************************************************************************/
rscfd_tx_buff_stat_t R_RSCFD_GetTxBuffStat(rscfd_tx_buff_t tx_buff)
{
    uint16 buff;
    uint8  unit;
    uint8  msk;

    unit = RSCFD_GET_UNIT(tx_buff);
    buff = RSCFD_GET_TXBUFF(tx_buff);

    /* which bits to return */
    msk  = RSCFD_MASK_CFDTMSTS_TMTSTS | RSCFD_MASK_CFDTMSTS_TMTRM;
    msk |= RSCFD_MASK_CFDTMSTS_TMTARM;

    /* return TX buffer status */
    return (rscfd_tx_buff_stat_t)(RSCFD[unit].CFDTMSTS[buff].BYTE & msk);
}


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
void R_RSCFD_SetTxBuffMsgFormat(rscfd_tx_buff_t tx_buff,
                                rscfd_msg_mode_t rscfd_type,
                                uint16 buff_ptr,
                                rscfd_label_t buff_lbl)
{
    uint32 msk;
    uint32 cfg;
    uint16 buff;
    uint8  unit;

    unit = RSCFD_GET_UNIT(tx_buff);
    buff = RSCFD_GET_TXBUFF(tx_buff);

    /* mask for TX format (CAN/CANFD), speed (slow fast),
     * TX buffer pointer and TX message label */
    msk  = RSCFD_MASK_CFDTMFDCTR_TMFDF | RSCFD_MASK_CFDTMFDCTR_TMBRS;
    msk |= RSCFD_MASK_CFDTMFDCTR_TMPTR | RSCFD_MASK_CFDTMFDCTR_TMIFL;

    /* configure TX message buffer pointer to store in history buffer */
    cfg = (buff_ptr << RSCFD_OFST_16BIT) | buff_lbl;
    RMW32(RSCFD[unit].TBUF[buff].CFDTMFDCTR.WORD, msk, cfg | rscfd_type);
}


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
void R_RSCFD_SetTxBuffMsgId(rscfd_tx_buff_t tx_buff,
                            rscfd_id_type_t id_type,
                            uint32 msg_id)
{
    uint32 msk;
    uint32 cfg;
    uint16 buff;
    uint8  unit;

    unit = RSCFD_GET_UNIT(tx_buff);
    buff = RSCFD_GET_TXBUFF(tx_buff);

    /* bits to change */
    msk  = RSCFD_MASK_CFDTMID_TMIDE | RSCFD_MASK_CFDTMID_TMID;
    msk |= RSCFD_MASK_CFDTMID_TMRTR | RSCFD_MASK_CFDTMID_TMLEN;

    /* configure message ID type
     * NOTE: THL hard coded as enabled (TMLEN=1) */
    cfg  = (uint32)(msg_id & RSCFD_MASK_CFDTMID_TMID) | (uint32)id_type;
    cfg |= RSCFD_MASK_CFDTMID_TMLEN;
    RMW32(RSCFD[unit].TBUF[buff].CFDTMID.WORD, msk, cfg);
}


/*******************************************************************************
 * Function Name : R_RSCFD_SetTxBuffMsgPayload
 * Description   : Copy message payload to TX buffer and set DLC
 * Parameters    : tx_buff       = RSCFD unit and TX buffer
 *               : msg_bytes     = number of bytes in the message payload
 *               : msg_payload   = message payload buffer
 * Returns       : none
 * Note          : do not call when corresponding channel in STOP mode
 ******************************************************************************/
void R_RSCFD_SetTxBuffMsgPayload(rscfd_tx_buff_t tx_buff,
                                 rscfd_payload_size_t msg_bytes,
                                 const rscfd_payload_t msg_payload[])
{
    volatile rscfd_st7_regmap_t * tbuff;
    rscfd_dlc_t                   dlc;
    uint8                         word_cnt;
    uint8                         w;

    /* shortcut to access TX buffer registers */
    tbuff = RSCFD[RSCFD_GET_UNIT(tx_buff)].TBUF + RSCFD_GET_TXBUFF(tx_buff);

    /* configure TX buffer DLC
     * NOTE: no protection against DLC > 8 in classical CAN mode */
    dlc = R_RSCFD_GetDlc(msg_bytes);
    RMW32(tbuff[0].CFDTMPTR.WORD, RSCFD_MASK_CFDTMPTR_TMDLC, dlc);

    /* copy in 32-bit increments
     * NOTE: rscfd_payload_t ensures placement on 32-bit boundary */
    word_cnt = R_RSCFD_GetPayloadWordCnt(dlc);
    for (w = 0; w < word_cnt; w++)
    {
        /* copy byte by byte */
        tbuff[0].CFDTMDF[w].WORD = msg_payload[0].WORD[w];
    }
}


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
void R_RSCFD_SendTxBuffMsg(rscfd_tx_buff_t tx_buff)
{
    uint32 msk;
    uint16 buff;
    uint8  unit;

    unit = RSCFD_GET_UNIT(tx_buff);
    buff = RSCFD_GET_TXBUFF(tx_buff);

    /* clear transmit buffer result flag */
    RMW8(RSCFD[unit].CFDTMSTS[buff].BYTE, RSCFD_MASK_CFDTMSTS_TMTRF, 0);

    /* Write Transmit Request bit for this buffer */
    msk = RSCFD_MASK_CFDTMC_TMTR;
    RMW8(RSCFD[unit].CFDTMC[buff].BYTE, msk, msk);
}


/*******************************************************************************
 * Function Name : R_RSCFD_TxByBuff
 * Description   : Example of sequence to send a message using TX buffer
 * Parameters    : tx_buff       = RSCFD unit and TX buffer
 *               : rscfd_type    = message type (classic/FD) and payload speed
 *               : msg           = message definition
 * Returns       : status of requested TX buffer before transmission
 ******************************************************************************/
rscfd_tx_buff_stat_t R_RSCFD_TxByBuff(rscfd_tx_buff_t tx_buff,
                                      rscfd_msg_mode_t rscfd_type,
                                      rscfd_msg_t * msg)
{
    rscfd_tx_buff_stat_t stat;
    rscfd_label_t        label;

    /* check TX buffer status */
    stat = R_RSCFD_GetTxBuffStat(tx_buff);
    if (!(stat & RSCFD_TX_BUFF_STAT_BUSY))
    {
        /* not busy, message label */
        label = msg[0].label;

        /* load message into requested TX buffer */
        R_RSCFD_SetTxBuffMsgFormat(tx_buff, rscfd_type, msg[0].ptr, label);
        R_RSCFD_SetTxBuffMsgId(tx_buff, msg[0].id_type, msg[0].id);
        R_RSCFD_SetTxBuffMsgPayload(tx_buff, msg[0].bytes, msg[0].payload);

        /* trigger buffer to transmit */
        R_RSCFD_SendTxBuffMsg(tx_buff);
    }

    /* TX buffer status before transmit  */
    return stat;
}


/*##############################################################################
 # supporting APIs
 #############################################################################*/

/*******************************************************************************
 * Function Name : R_RSCFD_GetPayloadByteCnt
 * Description   : Returns number of payload bytes based on requested DLC
 * Parameters    : dlc = data length code
 * Returns       : Number of bytes corresponding to the DLC
 ******************************************************************************/
rscfd_payload_size_t R_RSCFD_GetPayloadByteCnt(rscfd_dlc_t dlc)
{
    /* number of bytes in specified DLC */
    return rscfd_byte_cnt[(uint8)(((uint32)dlc) >> RSCFD_OFST_28BIT)];
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetPayloadWordCnt
 * Description   : Return number of 32-bit payload words based on requested DLC
 * Parameters    : dlc = data length code
 * Returns       : number of 32-bit words
 ******************************************************************************/
uint8 R_RSCFD_GetPayloadWordCnt(rscfd_dlc_t dlc)
{
    uint8 bytes;
    uint8 words;

    /* how many bytes */
    bytes = (uint8)rscfd_byte_cnt[(uint8)(((uint32)dlc) >> RSCFD_OFST_28BIT)];

    /* how many words including last partial word */
    words  = (bytes >> RSCFD_OFST_2BIT);
    words += (uint8)((bytes & RSCFD_MASK_2BIT) != 0);

    /* number of words in specified DLC */
    return words;
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetUnitNo
 * Description   : Return RSCFD unit number based on requested channel ID
 * Parameters    : chnl    = RSCFD unit and channel
 * Returns       : index of RSCFD unit
 ******************************************************************************/
uint8 R_RSCFD_GetUnitNo(rscfd_chnl_t chnl)
{
    /* return unit number */
    return RSCFD_GET_UNIT(chnl);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetChnlNo
 * Description   : Returns channel number as index within requested unit
 * Parameters    : chnl    = RSCFD unit and channel
 * Returns       : index of requested channel within a unit
 ******************************************************************************/
uint8 R_RSCFD_GetChnlNo(rscfd_chnl_t chnl)
{
    /* return channel number of index within RSCFD unit */
    return RSCFD_GET_CHNL(chnl);
}


/*******************************************************************************
 * Function Name : R_RSCFD_GetDlc
 * Description   : Returns DLC based on requested number of bytes
 * Parameters    : bytes     = requested number of bytes
 * Returns       : DLC
 ******************************************************************************/
rscfd_dlc_t R_RSCFD_GetDlc(rscfd_payload_size_t bytes)
{
    /* return DLC based on passed number of payload bytes */
    return (rscfd_dlc_t)(((uint32)rscfd_dlc[bytes]) << RSCFD_OFST_28BIT);
}


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
rscfd_result_t R_RSCFD_TxMsg(rscfd_tx_dst_t tx_dst,
                             rscfd_msg_mode_t type,
                             rscfd_msg_t * msg)
{
    rscfd_tx_fifo_t tfifo;
    rscfd_tx_buff_t tbuff;
    rscfd_result_t  stat;

    switch (RSCFD_GET_TXDEST(tx_dst))
    {
    case RSCFD_TX_FIFO:
        /* transmit by TX FIFO
         * NOTE: successful when FIFO not full */
        tfifo = (rscfd_tx_fifo_t)tx_dst;
        stat  = RSCFD_RESULT_NOFAULT;
        if (RSCFD_TX_FIFO_STAT_FULL & R_RSCFD_TxByFifo(tfifo, type, msg))
        {
            /* TXFIFO was full */
            stat = RSCFD_RESULT_FULL;
        }
        break;

    case RSCFD_TX_BUFF:
        /* transmit by TX buffer
         * NOTE: successful when buffer not busy */
        tbuff = (rscfd_tx_buff_t)tx_dst;
        stat  = RSCFD_RESULT_NOFAULT;
        if (RSCFD_TX_BUFF_STAT_BUSY & R_RSCFD_TxByBuff(tbuff, type, msg))
        {
            /* TX buffer was busy */
            stat = RSCFD_RESULT_BUSY;
        }
        break;

    default:
        /* unknown requested transmit path
         * NOTE: invalid request */
        stat = RSCFD_RESULT_ERR;
        break;
    }

    return stat;
}


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
void R_RSCFD_InitFifoComm(const rscfd_fifo_cfg_t * cfg)
{
    /* put all units in RESET mode and perform
     * RESET mode configurations */
    R_RSCFD_InitUnitRst(cfg[0].unit_cfg, cfg[0].unit_cfg_cnt);

    /* RESET mode: configure channels, receive rules, RX/TX FIFO */
    R_RSCFD_InitChnlRst(cfg[0].chnl_cfg, cfg[0].chnl_cfg_cnt);
    R_RSCFD_InitRxRulesRst(cfg[0].rx_rules_cfg, cfg[0].rx_rules_cfg_cnt);
    R_RSCFD_InitRxFifoRst(cfg[0].rx_fifo_cfg, cfg[0].rx_fifo_cfg_cnt);
    R_RSCFD_InitTxFifoRst(cfg[0].tx_fifo_cfg, cfg[0].tx_fifo_cfg_cnt);

    /* put all units in OPERATIONAL mode and perform
     * OPERATIONAL mode configurations */
    R_RSCFD_InitUnitOper(cfg[0].unit_cfg, cfg[0].unit_cfg_cnt);

    /* OPERATIONAL mode: configure channels, RX/TX FIFO */
    R_RSCFD_InitChnlOper(cfg[0].chnl_cfg, cfg[0].chnl_cfg_cnt);
    R_RSCFD_InitRxFifoOper(cfg[0].rx_fifo_cfg, cfg[0].rx_fifo_cfg_cnt);
    R_RSCFD_InitTxFifoOper(cfg[0].tx_fifo_cfg, cfg[0].tx_fifo_cfg_cnt);

    /* CAN units are configured as RSCFD to transmit/receive
     * using TX/RX FIFOs and are in operating mode */
}


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
void R_RSCFD_InitBuffComm(const rscfd_buff_cfg_t * cfg)
{
    /* put all units in RESET mode and perform
     * RESET mode configurations */
    R_RSCFD_InitUnitRst(cfg[0].unit_cfg, cfg[0].unit_cfg_cnt);

    /* RESET mode: configure channels, receive rules */
    R_RSCFD_InitChnlRst(cfg[0].chnl_cfg, cfg[0].chnl_cfg_cnt);
    R_RSCFD_InitRxRulesRst(cfg[0].rx_rules_cfg, cfg[0].rx_rules_cfg_cnt);

    /* put all units in OPERATIONAL mode and perform
     * OPERATIONAL mode configurations */
    R_RSCFD_InitUnitOper(cfg[0].unit_cfg, cfg[0].unit_cfg_cnt);

    /* OPERATIONAL mode: configure channels */
    R_RSCFD_InitChnlOper(cfg[0].chnl_cfg, cfg[0].chnl_cfg_cnt);

    /* CAN units are configured as RSCFD to transmit/receive
     * using TX/RX buffers and are in operating mode */
}


