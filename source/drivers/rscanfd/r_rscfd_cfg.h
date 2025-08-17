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
 *******************************************************************************/

/*****************************************************************************
 * File Name   : r_rscfd_cfg.h
 * Device(s)   : RH850/U2A
 * Description : RSCFD (CAN-FD) configuration
 ******************************************************************************/
#ifndef R_RSCFD_CFG_H
#define R_RSCFD_CFG_H

/*******************************************************************************
 * Include files
 ******************************************************************************/

/*##############################################################################
 # global enumerations
 ##############################################################################*/

/*******************************************************************************
 * RSCFD units in the MCU.
 * The number of CAN units varies by device.
 *******************************************************************************/
typedef enum
{
    RSCFD_UNIT_0 = 1,
    RSCFD_UNIT_1 = 0
}   rscfd_unit_t;

/*******************************************************************************
 * RSCFD channels in the MCU.
 * [31:24]   RSCFD unit
 * [23:16]   RSCFD rule register
 * [7:0]     RSCFD channel number
 *******************************************************************************/
typedef enum
{
    RSCFD_CHNL_0  = (RSCFD_UNIT_0 << 24) | (1 << 16) | 0,
    RSCFD_CHNL_1  = (RSCFD_UNIT_0 << 24) | (0 << 16) | 1,
    RSCFD_CHNL_2  = (RSCFD_UNIT_0 << 24) | (3 << 16) | 2,
    RSCFD_CHNL_3  = (RSCFD_UNIT_0 << 24) | (2 << 16) | 3,
    RSCFD_CHNL_4  = (RSCFD_UNIT_0 << 24) | (5 << 16) | 4,
    RSCFD_CHNL_5  = (RSCFD_UNIT_0 << 24) | (4 << 16) | 5,
    RSCFD_CHNL_6  = (RSCFD_UNIT_0 << 24) | (7 << 16) | 6,
    RSCFD_CHNL_7  = (RSCFD_UNIT_0 << 24) | (6 << 16) | 7,

    RSCFD_CHNL_8  = (RSCFD_UNIT_1 << 24) | (1 << 16) | 0,
    RSCFD_CHNL_9  = (RSCFD_UNIT_1 << 24) | (0 << 16) | 1,
    RSCFD_CHNL_10 = (RSCFD_UNIT_1 << 24) | (3 << 16) | 2,
    RSCFD_CHNL_11 = (RSCFD_UNIT_1 << 24) | (2 << 16) | 3,
    RSCFD_CHNL_12 = (RSCFD_UNIT_1 << 24) | (5 << 16) | 4,
    RSCFD_CHNL_13 = (RSCFD_UNIT_1 << 24) | (4 << 16) | 5,
    RSCFD_CHNL_14 = (RSCFD_UNIT_1 << 24) | (7 << 16) | 6,
    RSCFD_CHNL_15 = (RSCFD_UNIT_1 << 24) | (6 << 16) | 7
}   rscfd_chnl_t;

/*******************************************************************************
 * TX buffer label field
 * Specify in register CFDTMFDCTR bit field TMIFL
 * Enumeration matches bit field position
 *******************************************************************************/
typedef enum
{
    RSCFD_LABEL_0     = 0 << 8,
    RSCFD_LABEL_1     = 1 << 8,
    RSCFD_LABEL_2     = 2 << 8,
    RSCFD_LABEL_3     = 3 << 8
}   rscfd_label_t;

/*******************************************************************************
 * RSCFD transmit path (buffer, fifo, queue) in the MCU.
 * Alignment for inclusion in enumeration rscfd_tx_dst_t (b23:16)
 *******************************************************************************/
typedef enum
{
    RSCFD_TX_FIFO = 0x000000,
    RSCFD_TX_BUFF = 0x010000,
    RSCFD_TX_QUE  = 0x020000
}   rscfd_tx_t;

/*******************************************************************************
 * RSCFD receive path (RX buffer, RX FIFO, common/RX FIFO) in the MCU.
 * Register CFDGAFLP0 bit field GAFLRMV
 * Enumeration matches register bit field
 * Alignment for inclusion in enumeration rscfd_rx_dst_t
 *******************************************************************************/
typedef enum
{
    RSCFD_RX_FIFO = 0x0000,
    RSCFD_RX_BUFF = 0x8000
}   rscfd_rx_t;

/*******************************************************************************
 * RSCFD Clock Source
 * Specify in register GCFG bit field DCS
 * Enumeration values correspond to DCS bit settings within register.
 * RSCFD_CLK_SRC_HSB:   CLK_HSB / Peripheral high speed clock / CAN clock CLKC
 * RSCFD_CLK_SRC_OSC:   CLK_MOSC / Main Oscillator / CAN clock CLK_XINCAN
 *******************************************************************************/
typedef enum
{
    RSCFD_CLK_SRC_HSB = 0x00,
    RSCFD_CLK_SRC_OSC = 0x10
}   rscfd_clock_src_t;

/*******************************************************************************
 * RSCFD time segment 1 for data bit rate
 * Specify in register CFDCDCFG bit field DTSEG1
 * Enumeration values correspond to DTSEG1 bit settings within register.
 * NOTE: values valid for RSCANFD V4
 *******************************************************************************/
typedef enum
{
    RSCFD_DT1_3  = (2 << 8),
    RSCFD_DT1_4  = (3 << 8),
    RSCFD_DT1_5  = (4 << 8),
    RSCFD_DT1_6  = (5 << 8),
    RSCFD_DT1_7  = (6 << 8),
    RSCFD_DT1_8  = (7 << 8),
    RSCFD_DT1_9  = (8 << 8),
    RSCFD_DT1_10 = (9 << 8),
    RSCFD_DT1_11 = (10 << 8),
    RSCFD_DT1_12 = (11 << 8),
    RSCFD_DT1_13 = (12 << 8),
    RSCFD_DT1_14 = (13 << 8),
    RSCFD_DT1_15 = (14 << 8),
    RSCFD_DT1_16 = (15 << 8),
    RSCFD_DT1_17 = (16 << 8),
    RSCFD_DT1_18 = (17 << 8),
    RSCFD_DT1_19 = (18 << 8),
    RSCFD_DT1_20 = (19 << 8),
    RSCFD_DT1_21 = (20 << 8),
    RSCFD_DT1_22 = (21 << 8),
    RSCFD_DT1_23 = (22 << 8),
    RSCFD_DT1_24 = (23 << 8),
    RSCFD_DT1_25 = (24 << 8),
    RSCFD_DT1_26 = (25 << 8),
    RSCFD_DT1_27 = (26 << 8),
    RSCFD_DT1_28 = (27 << 8),
    RSCFD_DT1_29 = (28 << 8),
    RSCFD_DT1_30 = (29 << 8),
    RSCFD_DT1_31 = (30 << 8),
    RSCFD_DT1_32 = (31 << 8)
}   rscfd_dt1_t;

/*******************************************************************************
 * RSCFD time segment 2 for data bit rate
 * Specify in register CFDCDCFG bit field DTSEG2
 * Enumeration values correspond to DTSEG2 bit settings within register.
 * NOTE: values valid for RSCANFD V4
 *******************************************************************************/
typedef enum
{
    RSCFD_DT2_1  = (0 << 16),
    RSCFD_DT2_2  = (1 << 16),
    RSCFD_DT2_3  = (2 << 16),
    RSCFD_DT2_4  = (3 << 16),
    RSCFD_DT2_5  = (4 << 16),
    RSCFD_DT2_6  = (5 << 16),
    RSCFD_DT2_7  = (6 << 16),
    RSCFD_DT2_8  = (7 << 16),
    RSCFD_DT2_9  = (8 << 16),
    RSCFD_DT2_10 = (9 << 16),
    RSCFD_DT2_11 = (10 << 16),
    RSCFD_DT2_12 = (11 << 16),
    RSCFD_DT2_13 = (12 << 16),
    RSCFD_DT2_14 = (13 << 16),
    RSCFD_DT2_15 = (14 << 16),
    RSCFD_DT2_16 = (15 << 16)
}   rscfd_dt2_t;

/*******************************************************************************
 * RSCFD re-synchronization jump width for data bit rate
 * Specify in register CFDCDCFG bit field DSJW
 * Enumeration values correspond to DSJW bit settings within register.
 * NOTE: values valid for RSCANFD V4
 *******************************************************************************/
typedef enum
{
    RSCFD_DSJW_1  = (0 << 24),
    RSCFD_DSJW_2  = (1 << 24),
    RSCFD_DSJW_3  = (2 << 24),
    RSCFD_DSJW_4  = (3 << 24),
    RSCFD_DSJW_5  = (4 << 24),
    RSCFD_DSJW_6  = (5 << 24),
    RSCFD_DSJW_7  = (6 << 24),
    RSCFD_DSJW_8  = (7 << 24),
    RSCFD_DSJW_9  = (8 << 24),
    RSCFD_DSJW_10 = (9 << 24),
    RSCFD_DSJW_11 = (10 << 24),
    RSCFD_DSJW_12 = (11 << 24),
    RSCFD_DSJW_13 = (12 << 24),
    RSCFD_DSJW_14 = (13 << 24),
    RSCFD_DSJW_15 = (14 << 24),
    RSCFD_DSJW_16 = (15 << 24)
} rscfd_dsjw_t;

/*******************************************************************************
 * RSCFD pre-scaler for data baud rate
 * Specify in register CFDCDCFG bit field DBRP
 * Enumeration values correspond to DBRP bit settings within register.
 * NOTE: values valid for RSCANFD V4
 *******************************************************************************/
typedef enum
{
    RSCFD_DPR_1   = 0,
    RSCFD_DPR_2   = 1,
    RSCFD_DPR_3   = 2,
    RSCFD_DPR_4   = 3,
    RSCFD_DPR_5   = 4,
    RSCFD_DPR_6   = 5,
    RSCFD_DPR_7   = 6,
    RSCFD_DPR_8   = 7,
    RSCFD_DPR_9   = 8,
    RSCFD_DPR_10  = 9,
    RSCFD_DPR_11  = 10,
    RSCFD_DPR_12  = 11,
    RSCFD_DPR_13  = 12,
    RSCFD_DPR_14  = 13,
    RSCFD_DPR_15  = 14,
    RSCFD_DPR_16  = 15,
    RSCFD_DPR_17  = 16,
    RSCFD_DPR_18  = 17,
    RSCFD_DPR_19  = 18,
    RSCFD_DPR_20  = 19,
    RSCFD_DPR_21  = 20,
    RSCFD_DPR_22  = 21,
    RSCFD_DPR_23  = 22,
    RSCFD_DPR_24  = 23,
    RSCFD_DPR_25  = 24,
    RSCFD_DPR_26  = 25,
    RSCFD_DPR_27  = 26,
    RSCFD_DPR_28  = 27,
    RSCFD_DPR_29  = 28,
    RSCFD_DPR_30  = 29,
    RSCFD_DPR_31  = 30,
    RSCFD_DPR_32  = 31,
    RSCFD_DPR_33  = 32,
    RSCFD_DPR_34  = 33,
    RSCFD_DPR_35  = 34,
    RSCFD_DPR_36  = 35,
    RSCFD_DPR_37  = 36,
    RSCFD_DPR_38  = 37,
    RSCFD_DPR_39  = 38,

    RSCFD_DPR_128 = 127
} rscfd_dpr_t;

/*******************************************************************************
 * RSCFD time segment 1 for nominal bit rate
 * Specify in register CFDCNCFG bit field NTSEG1
 * Enumeration values correspond to NTSEG1 bit settings within register.
 * NOTE: values valid for RSCANFD V4
 *******************************************************************************/
typedef enum
{
    RSCFD_NT1_5   = (4 << 17),
    RSCFD_NT1_6   = (5 << 17),
    RSCFD_NT1_7   = (6 << 17),
    RSCFD_NT1_8   = (7 << 17),
    RSCFD_NT1_9   = (8 << 17),
    RSCFD_NT1_10  = (9 << 17),
    RSCFD_NT1_11  = (10 << 17),
    RSCFD_NT1_12  = (11 << 17),
    RSCFD_NT1_13  = (12 << 17),
    RSCFD_NT1_14  = (13 << 17),
    RSCFD_NT1_15  = (14 << 17),
    RSCFD_NT1_16  = (15 << 17),
    RSCFD_NT1_17  = (16 << 17),
    RSCFD_NT1_18  = (17 << 17),
    RSCFD_NT1_19  = (18 << 17),
    RSCFD_NT1_20  = (19 << 17),
    RSCFD_NT1_21  = (20 << 17),
    RSCFD_NT1_22  = (21 << 17),
    RSCFD_NT1_23  = (22 << 17),
    RSCFD_NT1_24  = (23 << 17),
    RSCFD_NT1_25  = (24 << 17),
    RSCFD_NT1_26  = (25 << 17),
    RSCFD_NT1_27  = (26 << 17),
    RSCFD_NT1_28  = (27 << 17),
    RSCFD_NT1_29  = (28 << 17),
    RSCFD_NT1_30  = (29 << 17),
    RSCFD_NT1_31  = (30 << 17),
    RSCFD_NT1_32  = (31 << 17),
    RSCFD_NT1_33  = (32 << 17),
    RSCFD_NT1_34  = (33 << 17),
    RSCFD_NT1_35  = (34 << 17),
    RSCFD_NT1_36  = (35 << 17),
    RSCFD_NT1_37  = (36 << 17),
    RSCFD_NT1_38  = (37 << 17),
    RSCFD_NT1_39  = (38 << 17),
    RSCFD_NT1_40  = (39 << 17),
    RSCFD_NT1_41  = (40 << 17),
    RSCFD_NT1_42  = (41 << 17),
    RSCFD_NT1_43  = (42 << 17),
    RSCFD_NT1_44  = (43 << 17),
    RSCFD_NT1_45  = (44 << 17),
    RSCFD_NT1_46  = (45 << 17),
    RSCFD_NT1_47  = (46 << 17),
    RSCFD_NT1_48  = (47 << 17),
    RSCFD_NT1_49  = (48 << 17),
    RSCFD_NT1_50  = (49 << 17),
    RSCFD_NT1_51  = (50 << 17),
    RSCFD_NT1_52  = (51 << 17),
    RSCFD_NT1_53  = (52 << 17),
    RSCFD_NT1_54  = (53 << 17),
    RSCFD_NT1_55  = (54 << 17),
    RSCFD_NT1_56  = (55 << 17),
    RSCFD_NT1_57  = (56 << 17),
    RSCFD_NT1_58  = (57 << 17),
    RSCFD_NT1_59  = (58 << 17),
    RSCFD_NT1_60  = (59 << 17),
    RSCFD_NT1_61  = (60 << 17),
    RSCFD_NT1_62  = (61 << 17),
    RSCFD_NT1_63  = (62 << 17),
    RSCFD_NT1_64  = (63 << 17),
    RSCFD_NT1_65  = (64 << 17),
    RSCFD_NT1_66  = (65 << 17),
    RSCFD_NT1_67  = (66 << 17),
    RSCFD_NT1_68  = (67 << 17),
    RSCFD_NT1_69  = (68 << 17),
    RSCFD_NT1_70  = (69 << 17),
    RSCFD_NT1_71  = (70 << 17),
    RSCFD_NT1_72  = (71 << 17),
    RSCFD_NT1_73  = (72 << 17),
    RSCFD_NT1_74  = (73 << 17),
    RSCFD_NT1_75  = (74 << 17),
    RSCFD_NT1_76  = (75 << 17),
    RSCFD_NT1_77  = (76 << 17),
    RSCFD_NT1_78  = (77 << 17),
    RSCFD_NT1_79  = (78 << 17),
    RSCFD_NT1_80  = (79 << 17),
    RSCFD_NT1_81  = (80 << 17),
    RSCFD_NT1_82  = (81 << 17),
    RSCFD_NT1_83  = (82 << 17),
    RSCFD_NT1_84  = (83 << 17),
    RSCFD_NT1_85  = (84 << 17),
    RSCFD_NT1_86  = (85 << 17),
    RSCFD_NT1_87  = (86 << 17),
    RSCFD_NT1_88  = (87 << 17),
    RSCFD_NT1_89  = (88 << 17),
    RSCFD_NT1_90  = (89 << 17),
    RSCFD_NT1_91  = (90 << 17),
    RSCFD_NT1_92  = (91 << 17),
    RSCFD_NT1_93  = (92 << 17),
    RSCFD_NT1_94  = (93 << 17),
    RSCFD_NT1_95  = (94 << 17),
    RSCFD_NT1_96  = (95 << 17),
    RSCFD_NT1_97  = (96 << 17),
    RSCFD_NT1_98  = (97 << 17),
    RSCFD_NT1_99  = (98 << 17),
    RSCFD_NT1_100 = (99 << 17),
    RSCFD_NT1_101 = (100 << 17),
    RSCFD_NT1_102 = (101 << 17),
    RSCFD_NT1_103 = (102 << 17),
    RSCFD_NT1_104 = (103 << 17),
    RSCFD_NT1_105 = (104 << 17),
    RSCFD_NT1_106 = (105 << 17),
    RSCFD_NT1_107 = (106 << 17),
    RSCFD_NT1_108 = (107 << 17),
    RSCFD_NT1_109 = (108 << 17),
    RSCFD_NT1_110 = (109 << 17),
    RSCFD_NT1_111 = (110 << 17),
    RSCFD_NT1_112 = (111 << 17),
    RSCFD_NT1_113 = (112 << 17),
    RSCFD_NT1_114 = (113 << 17),
    RSCFD_NT1_115 = (114 << 17),
    RSCFD_NT1_116 = (115 << 17),
    RSCFD_NT1_117 = (116 << 17),
    RSCFD_NT1_118 = (117 << 17),
    RSCFD_NT1_119 = (118 << 17),
    RSCFD_NT1_120 = (119 << 17),
    RSCFD_NT1_121 = (120 << 17),
    RSCFD_NT1_122 = (121 << 17),
    RSCFD_NT1_123 = (122 << 17),
    RSCFD_NT1_124 = (123 << 17),
    RSCFD_NT1_125 = (124 << 17),
    RSCFD_NT1_126 = (125 << 17),
    RSCFD_NT1_127 = (126 << 17),
    RSCFD_NT1_128 = (127 << 17),
    RSCFD_NT1_256 = (255 << 17)
} rscfd_nt1_t;

/*******************************************************************************
 * RSCFD time segment 2 for nominal bit rate
 * Specify in register CFDCNCFG bit field NTSEG2
 * Enumeration values correspond to NTSEG2 bit settings within register.
 * NOTE: values valid for RSCANFD V4
 *******************************************************************************/
typedef enum
{
    RSCFD_NT2_3   = (2 << 25),
    RSCFD_NT2_4   = (3 << 25),
    RSCFD_NT2_5   = (4 << 25),
    RSCFD_NT2_6   = (5 << 25),
    RSCFD_NT2_7   = (6 << 25),
    RSCFD_NT2_8   = (7 << 25),
    RSCFD_NT2_9   = (8 << 25),
    RSCFD_NT2_10  = (9 << 25),
    RSCFD_NT2_11  = (10 << 25),
    RSCFD_NT2_12  = (11 << 25),
    RSCFD_NT2_13  = (12 << 25),
    RSCFD_NT2_14  = (13 << 25),
    RSCFD_NT2_15  = (14 << 25),
    RSCFD_NT2_16  = (15 << 25),
    RSCFD_NT2_17  = (16 << 25),
    RSCFD_NT2_18  = (17 << 25),
    RSCFD_NT2_19  = (18 << 25),
    RSCFD_NT2_20  = (19 << 25),
    RSCFD_NT2_21  = (20 << 25),
    RSCFD_NT2_22  = (21 << 25),
    RSCFD_NT2_23  = (22 << 25),
    RSCFD_NT2_24  = (23 << 25),
    RSCFD_NT2_25  = (24 << 25),
    RSCFD_NT2_26  = (25 << 25),
    RSCFD_NT2_27  = (26 << 25),
    RSCFD_NT2_28  = (27 << 25),
    RSCFD_NT2_29  = (28 << 25),
    RSCFD_NT2_30  = (29 << 25),
    RSCFD_NT2_31  = (30 << 25),
    RSCFD_NT2_32  = (31 << 25),
    RSCFD_NT2_33  = (32 << 25),
    RSCFD_NT2_34  = (33 << 25),
    RSCFD_NT2_128 = (127 << 25)
} rscfd_nt2_t;

/*******************************************************************************
 * RSCFD re-synchronization jump width for nominal bit rate
 * Specify in register CFDCNCFG bit field NSJW
 * Enumeration values correspond to NSJW bit settings within register.
 * NOTE: values valid for RSCANFD V4
 *******************************************************************************/
typedef enum
{
    RSCFD_NSJW_1   = (0 << 10),
    RSCFD_NSJW_2   = (1 << 10),
    RSCFD_NSJW_3   = (2 << 10),
    RSCFD_NSJW_4   = (3 << 10),
    RSCFD_NSJW_5   = (4 << 10),
    RSCFD_NSJW_6   = (5 << 10),
    RSCFD_NSJW_7   = (6 << 10),
    RSCFD_NSJW_8   = (7 << 10),
    RSCFD_NSJW_9   = (8 << 10),
    RSCFD_NSJW_10  = (9 << 10),
    RSCFD_NSJW_11  = (10 << 10),
    RSCFD_NSJW_12  = (11 << 10),
    RSCFD_NSJW_13  = (12 << 10),
    RSCFD_NSJW_14  = (13 << 10),
    RSCFD_NSJW_15  = (14 << 10),
    RSCFD_NSJW_16  = (15 << 10),
    RSCFD_NSJW_17  = (16 << 10),
    RSCFD_NSJW_18  = (17 << 10),
    RSCFD_NSJW_19  = (18 << 10),
    RSCFD_NSJW_20  = (19 << 10),
    RSCFD_NSJW_21  = (20 << 10),
    RSCFD_NSJW_22  = (21 << 10),
    RSCFD_NSJW_23  = (22 << 10),
    RSCFD_NSJW_24  = (23 << 10),
    RSCFD_NSJW_25  = (24 << 10),
    RSCFD_NSJW_26  = (25 << 10),
    RSCFD_NSJW_27  = (26 << 10),
    RSCFD_NSJW_28  = (27 << 10),
    RSCFD_NSJW_29  = (28 << 10),
    RSCFD_NSJW_30  = (29 << 10),
    RSCFD_NSJW_31  = (30 << 10),
    RSCFD_NSJW_32  = (31 << 10),
    RSCFD_NSJW_33  = (32 << 10),
    RSCFD_NSJW_34  = (33 << 10),
    RSCFD_NSJW_35  = (34 << 10),
    RSCFD_NSJW_36  = (35 << 10),
    RSCFD_NSJW_37  = (36 << 10),
    RSCFD_NSJW_38  = (37 << 10),
    RSCFD_NSJW_39  = (38 << 10),
    RSCFD_NSJW_40  = (39 << 10),
    RSCFD_NSJW_41  = (40 << 10),
    RSCFD_NSJW_42  = (41 << 10),
    RSCFD_NSJW_43  = (42 << 10),
    RSCFD_NSJW_44  = (43 << 10),
    RSCFD_NSJW_45  = (44 << 10),
    RSCFD_NSJW_46  = (45 << 10),
    RSCFD_NSJW_47  = (46 << 10),
    RSCFD_NSJW_48  = (47 << 10),
    RSCFD_NSJW_49  = (48 << 10),
    RSCFD_NSJW_50  = (49 << 10),
    RSCFD_NSJW_51  = (50 << 10),
    RSCFD_NSJW_52  = (51 << 10),
    RSCFD_NSJW_53  = (52 << 10),
    RSCFD_NSJW_54  = (53 << 10),
    RSCFD_NSJW_55  = (54 << 10),
    RSCFD_NSJW_56  = (55 << 10),
    RSCFD_NSJW_57  = (56 << 10),
    RSCFD_NSJW_58  = (57 << 10),
    RSCFD_NSJW_59  = (58 << 10),
    RSCFD_NSJW_60  = (59 << 10),
    RSCFD_NSJW_61  = (60 << 10),
    RSCFD_NSJW_62  = (61 << 10),
    RSCFD_NSJW_63  = (62 << 10),
    RSCFD_NSJW_64  = (63 << 10),
    RSCFD_NSJW_65  = (64 << 10),
    RSCFD_NSJW_66  = (65 << 10),
    RSCFD_NSJW_67  = (66 << 10),
    RSCFD_NSJW_68  = (67 << 10),
    RSCFD_NSJW_69  = (68 << 10),
    RSCFD_NSJW_70  = (69 << 10),
    RSCFD_NSJW_71  = (70 << 10),
    RSCFD_NSJW_72  = (71 << 10),
    RSCFD_NSJW_73  = (72 << 10),
    RSCFD_NSJW_74  = (73 << 10),
    RSCFD_NSJW_75  = (74 << 10),
    RSCFD_NSJW_76  = (75 << 10),
    RSCFD_NSJW_77  = (76 << 10),
    RSCFD_NSJW_78  = (77 << 10),
    RSCFD_NSJW_79  = (78 << 10),
    RSCFD_NSJW_80  = (79 << 10),
    RSCFD_NSJW_81  = (80 << 10),
    RSCFD_NSJW_82  = (81 << 10),
    RSCFD_NSJW_83  = (82 << 10),
    RSCFD_NSJW_84  = (83 << 10),
    RSCFD_NSJW_85  = (84 << 10),
    RSCFD_NSJW_86  = (85 << 10),
    RSCFD_NSJW_87  = (86 << 10),
    RSCFD_NSJW_88  = (87 << 10),
    RSCFD_NSJW_89  = (88 << 10),
    RSCFD_NSJW_90  = (89 << 10),
    RSCFD_NSJW_91  = (90 << 10),
    RSCFD_NSJW_92  = (91 << 10),
    RSCFD_NSJW_93  = (92 << 10),
    RSCFD_NSJW_94  = (93 << 10),
    RSCFD_NSJW_95  = (94 << 10),
    RSCFD_NSJW_96  = (95 << 10),
    RSCFD_NSJW_97  = (96 << 10),
    RSCFD_NSJW_98  = (97 << 10),
    RSCFD_NSJW_99  = (98 << 10),
    RSCFD_NSJW_100 = (99 << 10),
    RSCFD_NSJW_101 = (100 << 10),
    RSCFD_NSJW_102 = (101 << 10),
    RSCFD_NSJW_103 = (102 << 10),
    RSCFD_NSJW_104 = (103 << 10),
    RSCFD_NSJW_105 = (104 << 10),
    RSCFD_NSJW_106 = (105 << 10),
    RSCFD_NSJW_107 = (106 << 10),
    RSCFD_NSJW_108 = (107 << 10),
    RSCFD_NSJW_109 = (108 << 10),
    RSCFD_NSJW_110 = (109 << 10),
    RSCFD_NSJW_111 = (110 << 10),
    RSCFD_NSJW_112 = (111 << 10),
    RSCFD_NSJW_113 = (112 << 10),
    RSCFD_NSJW_114 = (113 << 10),
    RSCFD_NSJW_115 = (114 << 10),
    RSCFD_NSJW_116 = (115 << 10),
    RSCFD_NSJW_117 = (116 << 10),
    RSCFD_NSJW_118 = (117 << 10),
    RSCFD_NSJW_119 = (118 << 10),
    RSCFD_NSJW_120 = (119 << 10),
    RSCFD_NSJW_121 = (120 << 10),
    RSCFD_NSJW_122 = (121 << 10),
    RSCFD_NSJW_123 = (122 << 10),
    RSCFD_NSJW_124 = (123 << 10),
    RSCFD_NSJW_125 = (124 << 10),
    RSCFD_NSJW_126 = (125 << 10),
    RSCFD_NSJW_127 = (126 << 10),
    RSCFD_NSJW_128 = (127 << 10)
} rscfd_nsjw_t;

/*******************************************************************************
 * RSCFD pre-scaler for nominal baud rate
 * Specify in register CFDCNCFG bit field NBRP
 * Enumeration values correspond to NBRP bit settings within register.
 * NOTE: values valid for RSCANFD V4
 *******************************************************************************/
typedef enum
{
    RSCFD_NPR_1    = 0,
    RSCFD_NPR_2    = 1,
    RSCFD_NPR_3    = 2,
    RSCFD_NPR_4    = 3,
    RSCFD_NPR_5    = 4,
    RSCFD_NPR_6    = 5,
    RSCFD_NPR_7    = 6,
    RSCFD_NPR_8    = 7,
    RSCFD_NPR_9    = 8,
    RSCFD_NPR_10   = 9,
    RSCFD_NPR_11   = 10,
    RSCFD_NPR_12   = 11,
    RSCFD_NPR_13   = 12,
    RSCFD_NPR_14   = 13,
    RSCFD_NPR_15   = 14,
    RSCFD_NPR_16   = 15,
    RSCFD_NPR_17   = 16,
    RSCFD_NPR_18   = 17,
    RSCFD_NPR_19   = 18,
    RSCFD_NPR_20   = 19,
    RSCFD_NPR_21   = 20,
    RSCFD_NPR_22   = 21,
    RSCFD_NPR_23   = 22,
    RSCFD_NPR_24   = 23,
    RSCFD_NPR_25   = 24,
    RSCFD_NPR_26   = 25,
    RSCFD_NPR_27   = 26,
    RSCFD_NPR_28   = 27,
    RSCFD_NPR_29   = 28,
    RSCFD_NPR_30   = 29,
    RSCFD_NPR_31   = 30,
    RSCFD_NPR_32   = 31,
    RSCFD_NPR_33   = 32,
    RSCFD_NPR_34   = 33,
    RSCFD_NPR_35   = 34,
    RSCFD_NPR_36   = 35,
    RSCFD_NPR_37   = 36,
    RSCFD_NPR_38   = 37,
    RSCFD_NPR_39   = 38,

    RSCFD_NPR_1024 = 1023
} rscfd_npr_t;

/*******************************************************************************
 * RSCFD Acceptance Filter - DLC check
 * Specify in register GCFG bit fields DCE and DRE
 * - DIS          = DLC field will not be checked
 * - MIN          = Message with DLC less than filter will be rejected
 * - MIN_REPLACE  = Message with DLC less than filter will be rejected
 *                  DLC will be replaced with the filter mask value
 *                  for accepted messages
 * Enumeration values correspond to DCE/DRE bit settings within register.
 *******************************************************************************/
typedef enum
{
    RSCFD_DLC_CHECK_DIS         = 0x00,
    RSCFD_DLC_CHECK_MIN         = 0x02,
    RSCFD_DLC_CHECK_MIN_REPLACE = 0x06
}   rscfd_dlc_check_t;

/*******************************************************************************
 * RSCFD RAM initialization Status
 * Status specified by register GSTS bit GRAMINIT
 * Enumeration corresponds to bit position within register.
 * CAN RAM is initialized by hardware following MCU reset.
 *******************************************************************************/
typedef enum
{
    RSCFD_RAM_INIT_COMPLETE = 0,
    RSCFD_RAM_INIT_ONGOING  = 0x08
}   rscfd_ram_init_t;

/*******************************************************************************
 * RSCFD Global Mode Select
 * Specify in register GCTR bitfields GSLPR and GMDC[1:0]
 * Verify  in register GSTS bitfields GSLPSTS, GHLTSTS, GRSTSTS
 * Enumerations correspond to bitfield settings.
 *******************************************************************************/
typedef enum
{
    RSCFD_GLBL_MODE_OPER = 0,
    RSCFD_GLBL_MODE_RST  = 1,
    RSCFD_GLBL_MODE_TEST = 2,
    RSCFD_GLBL_MODE_STOP = 4
}   rscfd_glbl_mode_t;

/*******************************************************************************
 * RSCFD Channel Mode Select
 * Specify in register CmCTR bitfields CSLPR, CHMDC[1:0]
 * Verify  in register CmSTS bitfields CSLPSTS, CHLTSTS, CRSTSTS
 * Enumerations correspond to bitfield settings.
 *******************************************************************************/
typedef enum
{
    RSCFD_CHNL_MODE_COMM = 0,
    RSCFD_CHNL_MODE_RST  = 1,
    RSCFD_CHNL_MODE_HALT = 2,
    RSCFD_CHNL_MODE_STOP = 4
}   rscfd_chnl_mode_t;


/*******************************************************************************
 * RSCFD Channel Mode Select
 * Specify in register FDCFG bit fields CLOE and EDOE
 * Enumerations correspond to bit field settings.
 *******************************************************************************/
typedef enum
{
    RSCFD_CHNL_INTERF_BOTH          = 0x0 << 28,
        RSCFD_CHNL_INTERF_CANFD     = 0x1 << 28,
        RSCFD_CHNL_INTERF_CLASSICAL = 0x5 << 28
} rscfd_chnl_interf_t;

/*******************************************************************************
 * RSCFD mode transition type
 * mode transition can be direct or indirect same for channel and unit
 * NOTE: indirect transitions results in RESET mode of unit or channel
 ******************************************************************************/
typedef enum
{
    RSCFD_MODE_TRANS_INVALID = 0,
    RSCFD_MODE_TRANS_VALID   = 1
} rscfd_mode_trans_t;

/*******************************************************************************
 * CAN Channel Comm Test Select
 * Specify test mode in register CmCTR bit fields CTMS[1:0] and CTME.
 * Enumeration corresponds to bit field position within register.
 *
 * External Test mode - Transmitted messages loop back through CAN transceiver.
 *                      The CAN channel is still externally connected (network
 *                      communication still works).
 * Internal Test Mode - Transmitted messages loop back internal to the MCU.
 *                      The CAN channel is isolated from external connections.
 *******************************************************************************/
typedef enum
{
    RSCFD_CHNL_TEST_DIS              = 0 << 24,
        RSCFD_CHNL_TEST_STANDARD     = 1 << 24,
        RSCFD_CHNL_TEST_LISTEN       = 3 << 24,
        RSCFD_CHNL_TEST_LOOPBACK_EXT = 5 << 24,
        RSCFD_CHNL_TEST_LOOPBACK_INT = 7 << 24
}   rscfd_chnl_test_t;

/*******************************************************************************
 * CAN Channel Baud Rate Settings (Nominal)
 * Bit layout is identical to CFDCmNCFG register
 * Baud Rate Clock Source = 16MHz, 20MHz, 24MHz, 40MHz, 80MHz
 *
 * NOTE: the synchronization segment (SS) is fixed to SS=1.
 * NOTE: the re-synchronization jump (NSJW) at NTQ1-1
 * NOTE: the sample point at 75% (SS+NTQ1)/(SS+NTQ1+NTQ2) at 75%
 * NOTE: the segment for nominal bit rate must be in range [8..385].
 * NOTE: the formula for segment for nominal bit rate if SS + NTQ1 + NTQ2
 * NOTE: the baud rate formula is CLOCK/[NPR*(SS+NTQ1+NTQ2)]
 *******************************************************************************/
typedef enum
{
    /* Baud Rate Source Clock set to RSCFD_CLK_SRC_OSC and MainOsc = 16MHz */
    RSCFD_CHNL_NBR_100K_16M = RSCFD_NSJW_9 | RSCFD_NT1_29 | RSCFD_NT2_10 | RSCFD_NPR_4,
    RSCFD_CHNL_NBR_125K_16M = RSCFD_NSJW_7 | RSCFD_NT1_23 | RSCFD_NT2_8 | RSCFD_NPR_4,
    RSCFD_CHNL_NBR_250K_16M = RSCFD_NSJW_7 | RSCFD_NT1_23 | RSCFD_NT2_8 | RSCFD_NPR_2,
    RSCFD_CHNL_NBR_500K_16M = RSCFD_NSJW_7 | RSCFD_NT1_23 | RSCFD_NT2_8 | RSCFD_NPR_1,
    RSCFD_CHNL_NBR_1M_16M   = RSCFD_NSJW_3 | RSCFD_NT1_11 | RSCFD_NT2_4 | RSCFD_NPR_1,

    /* Baud Rate Source Clock set to RSCFD_CLK_SRC_OSC and MainOsc = 20MHz */
    RSCFD_CHNL_NBR_100K_20M = RSCFD_NSJW_9 | RSCFD_NT1_29 | RSCFD_NT2_10 | RSCFD_NPR_5,
    RSCFD_CHNL_NBR_125K_20M = RSCFD_NSJW_7 | RSCFD_NT1_23 | RSCFD_NT2_8 | RSCFD_NPR_5,
    RSCFD_CHNL_NBR_250K_20M = RSCFD_NSJW_9 | RSCFD_NT1_29 | RSCFD_NT2_10 | RSCFD_NPR_2,
    RSCFD_CHNL_NBR_500K_20M = RSCFD_NSJW_9 | RSCFD_NT1_29 | RSCFD_NT2_10 | RSCFD_NPR_1,
    RSCFD_CHNL_NBR_1M_20M   = RSCFD_NSJW_4 | RSCFD_NT1_14 | RSCFD_NT2_5 | RSCFD_NPR_1,

    /* Baud Rate Source Clock set to RSCFD_CLK_SRC_OSC and MainOsc = 24MHz */
    RSCFD_CHNL_NBR_100K_24M = RSCFD_NSJW_9 | RSCFD_NT1_29 | RSCFD_NT2_10 | RSCFD_NPR_6,
    RSCFD_CHNL_NBR_125K_24M = RSCFD_NSJW_7 | RSCFD_NT1_23 | RSCFD_NT2_8 | RSCFD_NPR_6,
    RSCFD_CHNL_NBR_250K_24M = RSCFD_NSJW_7 | RSCFD_NT1_23 | RSCFD_NT2_8 | RSCFD_NPR_3,
    RSCFD_CHNL_NBR_500K_24M = RSCFD_NSJW_11 | RSCFD_NT1_35 | RSCFD_NT2_12 | RSCFD_NPR_1,
    RSCFD_CHNL_NBR_1M_24M   = RSCFD_NSJW_5 | RSCFD_NT1_17 | RSCFD_NT2_6 | RSCFD_NPR_1,

    /* Baud Rate Source Clock set to RSCFD_CLK_SRC_OSC and MainOsc = 40MHz */
    RSCFD_CHNL_NBR_100K_40M = RSCFD_NSJW_9 | RSCFD_NT1_29 | RSCFD_NT2_10 | RSCFD_NPR_10,
    RSCFD_CHNL_NBR_125K_40M = RSCFD_NSJW_7 | RSCFD_NT1_23 | RSCFD_NT2_8 | RSCFD_NPR_10,
    RSCFD_CHNL_NBR_250K_40M = RSCFD_NSJW_9 | RSCFD_NT1_29 | RSCFD_NT2_10 | RSCFD_NPR_4,
    RSCFD_CHNL_NBR_500K_40M = RSCFD_NSJW_9 | RSCFD_NT1_29 | RSCFD_NT2_10 | RSCFD_NPR_2,
    RSCFD_CHNL_NBR_1M_40M   = RSCFD_NSJW_4 | RSCFD_NT1_14 | RSCFD_NT2_5 | RSCFD_NPR_2,

    /* Baud Rate Source Clock set to RSCFD_CLK_SRC_HSB (80MHz) */
    RSCFD_CHNL_NBR_100K_80M = RSCFD_NSJW_9 | RSCFD_NT1_29 | RSCFD_NT2_10 | RSCFD_NPR_20,
    RSCFD_CHNL_NBR_125K_80M = RSCFD_NSJW_7 | RSCFD_NT1_23 | RSCFD_NT2_8 | RSCFD_NPR_20,
    RSCFD_CHNL_NBR_250K_80M = RSCFD_NSJW_9 | RSCFD_NT1_29 | RSCFD_NT2_10 | RSCFD_NPR_8,
    RSCFD_CHNL_NBR_500K_80M = RSCFD_NSJW_9 | RSCFD_NT1_29 | RSCFD_NT2_10 | RSCFD_NPR_4,
    RSCFD_CHNL_NBR_1M_80M   = RSCFD_NSJW_4 | RSCFD_NT1_14 | RSCFD_NT2_5 | RSCFD_NPR_4
}   rscfd_chnl_nbr_t;

/*******************************************************************************
 * CAN Channel Baud Rate Settings (Data)
 * Bit layout is identical to CFDCmDCFG register
 * Baud Rate Clock Source = 16MHz, 20MHz, 24MHz, 40MHz, 80MHz
 *
 * NOTE: the synchronization segment (SS) is fixed to SS=1.
 * NOTE: the re-synchronization jump (NSJW) at NTQ1-1
 * NOTE: the sample point @75% except for 2Mbps @80% (SS+NTQ1)/(SS+NTQ1+NTQ2)
 * NOTE: the 2Mpbs sample point @80% except for 24MHz clock @75%
 * NOTE: the segment for nominal bit rate must be in range [8..385].
 * NOTE: the formula for segment for nominal bit rate if SS + NTQ1 + NTQ2
 * NOTE: the baud rate formula is CLOCK/[NPR*(SS+NTQ1+NTQ2)]
 * NOTE: DSJ (SJW) set to (DT1 - 1)
 *******************************************************************************/
typedef enum
{
    /* Baud Rate Source Clock set to RSCFD_CLK_SRC_OSC and MainOsc = 16MHz
     * NOTE: 2Mbps not possible with 16MHz source clock (fewer than 10TQ/bit) */
    RSCFD_CHNL_DBR_100K_16M = RSCFD_DSJW_9 | RSCFD_DT1_29 | RSCFD_DT2_10 | RSCFD_DPR_4,
    RSCFD_CHNL_DBR_125K_16M = RSCFD_DSJW_7 | RSCFD_DT1_23 | RSCFD_DT2_8 | RSCFD_DPR_4,
    RSCFD_CHNL_DBR_250K_16M = RSCFD_DSJW_7 | RSCFD_DT1_23 | RSCFD_DT2_8 | RSCFD_DPR_2,
    RSCFD_CHNL_DBR_500K_16M = RSCFD_DSJW_7 | RSCFD_DT1_23 | RSCFD_DT2_8 | RSCFD_DPR_1,
    RSCFD_CHNL_DBR_1M_16M   = RSCFD_DSJW_3 | RSCFD_DT1_11 | RSCFD_DT2_4 | RSCFD_DPR_1,

    /* Baud Rate Source Clock set to RSCFD_CLK_SRC_OSC and MainOsc = 20MHz */
    RSCFD_CHNL_DBR_100K_20M = RSCFD_DSJW_9 | RSCFD_DT1_29 | RSCFD_DT2_10 | RSCFD_DPR_5,
    RSCFD_CHNL_DBR_125K_20M = RSCFD_DSJW_7 | RSCFD_DT1_23 | RSCFD_DT2_8 | RSCFD_DPR_5,
    RSCFD_CHNL_DBR_250K_20M = RSCFD_DSJW_9 | RSCFD_DT1_29 | RSCFD_DT2_10 | RSCFD_DPR_2,
    RSCFD_CHNL_DBR_500K_20M = RSCFD_DSJW_9 | RSCFD_DT1_29 | RSCFD_DT2_10 | RSCFD_DPR_1,
    RSCFD_CHNL_DBR_1M_20M   = RSCFD_DSJW_4 | RSCFD_DT1_14 | RSCFD_DT2_5 | RSCFD_DPR_1,
    RSCFD_CHNL_DBR_2M_20M   = RSCFD_DSJW_1 | RSCFD_DT1_7 | RSCFD_DT2_2 | RSCFD_DPR_1,

    /* Baud Rate Source Clock set to RSCFD_CLK_SRC_OSC and MainOsc = 24MHz */
    RSCFD_CHNL_DBR_100K_24M = RSCFD_DSJW_9 | RSCFD_DT1_29 | RSCFD_DT2_10 | RSCFD_DPR_6,
    RSCFD_CHNL_DBR_125K_24M = RSCFD_DSJW_7 | RSCFD_DT1_23 | RSCFD_DT2_8 | RSCFD_DPR_6,
    RSCFD_CHNL_DBR_250K_24M = RSCFD_DSJW_7 | RSCFD_DT1_23 | RSCFD_DT2_8 | RSCFD_DPR_3,
    RSCFD_CHNL_DBR_500K_24M = RSCFD_DSJW_11 | RSCFD_DT1_29 | RSCFD_DT2_12 | RSCFD_DPR_1,
    RSCFD_CHNL_DBR_1M_24M   = RSCFD_DSJW_5 | RSCFD_DT1_17 | RSCFD_DT2_6 | RSCFD_DPR_1,
    RSCFD_CHNL_DBR_2M_24M   = RSCFD_DSJW_2 | RSCFD_DT1_8 | RSCFD_DT2_3 | RSCFD_DPR_1,

    /* Baud Rate Source Clock set to RSCFD_CLK_SRC_OSC and MainOsc = 40MHz */
    RSCFD_CHNL_DBR_100K_40M = RSCFD_DSJW_9 | RSCFD_DT1_29 | RSCFD_DT2_10 | RSCFD_DPR_10,
    RSCFD_CHNL_DBR_125K_40M = RSCFD_DSJW_7 | RSCFD_DT1_23 | RSCFD_DT2_8 | RSCFD_DPR_10,
    RSCFD_CHNL_DBR_250K_40M = RSCFD_DSJW_9 | RSCFD_DT1_29 | RSCFD_DT2_10 | RSCFD_DPR_4,
    RSCFD_CHNL_DBR_500K_40M = RSCFD_DSJW_9 | RSCFD_DT1_29 | RSCFD_DT2_10 | RSCFD_DPR_2,
    RSCFD_CHNL_DBR_1M_40M   = RSCFD_DSJW_4 | RSCFD_DT1_14 | RSCFD_DT2_5 | RSCFD_DPR_2,
    RSCFD_CHNL_DBR_2M_40M   = RSCFD_DSJW_3 | RSCFD_DT1_15 | RSCFD_DT2_4 | RSCFD_DPR_1,

    /* Baud Rate Source Clock set to RSCFD_CLK_SRC_HSB (80MHz) */
    RSCFD_CHNL_DBR_100K_80M = RSCFD_DSJW_9 | RSCFD_DT1_29 | RSCFD_DT2_10 | RSCFD_DPR_20,
    RSCFD_CHNL_DBR_125K_80M = RSCFD_DSJW_7 | RSCFD_DT1_23 | RSCFD_DT2_8 | RSCFD_DPR_20,
    RSCFD_CHNL_DBR_250K_80M = RSCFD_DSJW_9 | RSCFD_DT1_29 | RSCFD_DT2_10 | RSCFD_DPR_8,
    RSCFD_CHNL_DBR_500K_80M = RSCFD_DSJW_9 | RSCFD_DT1_29 | RSCFD_DT2_10 | RSCFD_DPR_4,
    RSCFD_CHNL_DBR_1M_80M   = RSCFD_DSJW_4 | RSCFD_DT1_14 | RSCFD_DT2_5 | RSCFD_DPR_4,
    RSCFD_CHNL_DBR_2M_80M   = RSCFD_DSJW_3 | RSCFD_DT1_15 | RSCFD_DT2_4 | RSCFD_DPR_2
}   rscfd_chnl_dbr_t;

/*******************************************************************************
 * CAN Channel Transmit History Buffer Enable/Disable
 * Transmit history is enabled/disabled in register CFDTHLCC bitfield THLE.
 * Enumeration corresponds to bit position within register.
 *******************************************************************************/
typedef enum
{
    RSCFD_CHNL_HIST_DIS = 0,
    RSCFD_CHNL_HIST_EN  = 1
}   rscfd_chnl_hist_en_t;

/*******************************************************************************
 * CAN Receive Rule Table Write Enable
 * Receive Rule Table Writes are enabled/disabled in register CFDGAFLECTR
 * bitfield AFLDAE.
 * Enumeration corresponds to bit position within register.
 *******************************************************************************/
typedef enum
{
    RSCFD_RX_RULE_WR_DIS = 0,
    RSCFD_RX_RULE_WR_EN  = 0x0100
}   rscfd_rx_rule_wr_t;

/*******************************************************************************
 * CAN Receive Rule Mask - mask bit definition
 * If mask bit          = 0 then that bit is not used in filter.
 * Enumeration corresponds to bit position within RSCFDnCFDGAFLMj
 *******************************************************************************/
typedef enum
{
    RSCFD_RX_ID_TYPE_MASK_ON      = 0x0,                 /* IDE/RTR ignored */
    RSCFD_RX_ID_TYPE_MASK_OFF_RTR = 0x40000000,          /* RTR not ignored */
    RSCFD_RX_ID_TYPE_MASK_OFF_IDE = (sint32) 0x80000000  /* IDE not ignored */
}   rscfd_rx_id_type_mask_t;

/*******************************************************************************
 * CAN Transmitter Delay Compensation Enable.
 * Specify in register FDCFG bit fields TDCE and TDCOC.
 * Enumeration corresponds to bit position in register.
 *******************************************************************************/
typedef enum
{
    RSCFD_CHNL_COMP_DIS     = 0x0,
    RSCFD_CHNL_COMP_EN      = 0x200,
    RSCFD_CHNL_COMP_EN_OFST = 0x300
}   rscfd_chnl_comp_t;

/*******************************************************************************
 * Source of message that Receive Rule will Select
 * Specify in register CFDGAFLID bitfield GAFLLB
 * Enumeration corresponds to bit position in register.
 *******************************************************************************/
typedef enum
{
    RSCFD_RX_SRC_OTHER_NODE    = 0 << 29,
        RSCFD_RX_SRC_THIS_NODE = 1 << 29
}   rscfd_rx_src_t;

/*******************************************************************************
 * Transmit/Receive FIFO Buffer Status
 * Specify in register CFDCFSTS bit fields CFFLL, CFEMP, CFMLT, CFFLL, CFMOW,
 *******************************************************************************/
typedef enum
{
    RSCFD_TX_FIFO_STAT_EMPTY     = 0x1,
    RSCFD_TX_FIFO_STAT_FULL      = 0x2,
    RSCFD_TX_FIFO_STAT_LOST      = 0x4,
    RSCFD_TX_FIFO_STAT_IRQ_RX    = 0x8,
    RSCFD_TX_FIFO_STAT_IRQ_TX    = 0x10,
    RSCFD_TX_FIFO_STAT_IRQ_FULL  = 0x10000,
    RSCFD_TX_FIFO_STAT_OVERWRITE = 0x1000000,
    RSCFD_TX_FIFO_STAT_ALL       = 0x101001F
}   rscfd_tx_fifo_stat_t;

/*******************************************************************************
 * Receive FIFO Buffer Status
 * Specify in register CFDRFSTS bit fields RFEMP, RFFLL, RFMLT, RFIF, RFFIF,
 *******************************************************************************/
typedef enum
{
    RSCFD_RX_FIFO_STAT_EMPTY    = 0x1,
    RSCFD_RX_FIFO_STAT_FULL     = 0x2,
    RSCFD_RX_FIFO_STAT_LOST     = 0x4,
    RSCFD_RX_FIFO_STAT_IRQ      = 0x8,
    RSCFD_RX_FIFO_STAT_IRQ_FULL = 0x10000,
    RSCFD_RX_FIFO_STAT_ALL      = 0x1000F
}   rscfd_rx_fifo_stat_t;

/*******************************************************************************
 * Channel status
 * Specify in register CFDCSTS bit fields CRSTSTS, CHLTSTS, CSLPSTS, EPSTS,
 * BOSTS, TRMSTS, RECSTS, COMSTS, ESIF
 *******************************************************************************/
typedef enum
{
    RSCFD_CHNL_STAT_ERR_PASSIVE = 0x08,
    RSCFD_CHNL_STAT_BUS_OFF     = 0x10,
    RSCFD_CHNL_STAT_TX_PROGRESS = 0x20,
    RSCFD_CHNL_STAT_RX_PROGRESS = 0x40,
    RSCFD_CHNL_STAT_READY       = 0x80,
    RSCFD_CHNL_STAT_ERR_STATE   = 0x100,
    RSCFD_CHNL_STAT_ALL         = 0x1F8
}   rscfd_chnl_stat_t;

/*******************************************************************************
 * Set message ID type Standard/Extended ID and Normal/Remote Frame. Applies
 * to register CFDCFID[31] (RFIDE) and CFDCFID[30] (RFRTR). Also applies to
 * registers CFDGAFLID, CFDRFID, CFDRMID and CFDTMID
 * Enumeration corresponds to bit position within registers.
 ******************************************************************************/
typedef enum
{
    RSCFD_ID_TYPE_STD     = 0x0,
    RSCFD_ID_TYPE_RTR     = 0x40000000,
    RSCFD_ID_TYPE_EXT     = (sint32) 0x80000000,
    RSCFD_ID_TYPE_EXT_RTR = (sint32) 0xc0000000
}   rscfd_id_type_t;


/*******************************************************************************
 * Rx Buffer - Set payload storage size
 * Specify in register CFDRMNB bitfield RMPLS
 * Enumeration corresponds to bit position in register.
 ******************************************************************************/
typedef enum
{
    RSCFD_RX_BUFF_SIZE_8      = 0 << 8,
        RSCFD_RX_BUFF_SIZE_12 = 1 << 8,
        RSCFD_RX_BUFF_SIZE_16 = 2 << 8,
        RSCFD_RX_BUFF_SIZE_20 = 3 << 8,
        RSCFD_RX_BUFF_SIZE_24 = 4 << 8,
        RSCFD_RX_BUFF_SIZE_32 = 5 << 8,
        RSCFD_RX_BUFF_SIZE_48 = 6 << 8,
        RSCFD_RX_BUFF_SIZE_64 = 7 << 8
}   rscfd_rx_buff_size_t;

/*******************************************************************************
 * CAN Data Length Configuration (DLC)
 * Specify in register CFPTR or CFDGAFLP0
 * Enumeration matching CFPTR but not CFDGAFLP0
 *******************************************************************************/
typedef enum
{
    RSCFD_DLC_0_BYTES  = (0x00 << 28),
    RSCFD_DLC_1_BYTES  = (0x01 << 28),
    RSCFD_DLC_2_BYTES  = (0x02 << 28),
    RSCFD_DLC_3_BYTES  = (0x03 << 28),
    RSCFD_DLC_4_BYTES  = (0x04 << 28),
    RSCFD_DLC_5_BYTES  = (0x05 << 28),
    RSCFD_DLC_6_BYTES  = (0x06 << 28),
    RSCFD_DLC_7_BYTES  = (0x07 << 28),
    RSCFD_DLC_8_BYTES  = (0x08 << 28),
    RSCFD_DLC_12_BYTES = (0x09 << 28),
    RSCFD_DLC_16_BYTES = (0x0a << 28),
    RSCFD_DLC_20_BYTES = (0x0b << 28),
    RSCFD_DLC_24_BYTES = (0x0c << 28),
    RSCFD_DLC_32_BYTES = (0x0d << 28),
    RSCFD_DLC_48_BYTES = (0x0e << 28),
    RSCFD_DLC_64_BYTES = (0x0f << 28)
}   rscfd_dlc_t;

/*******************************************************************************
 * Return codes for function R_RSCFD_ReadRxFifo
 ******************************************************************************/
typedef enum
{
    RSCFD_PAYLOAD_SIZE_0_BYTES  = 0,
    RSCFD_PAYLOAD_SIZE_1_BYTES  = 1,
    RSCFD_PAYLOAD_SIZE_2_BYTES  = 2,
    RSCFD_PAYLOAD_SIZE_3_BYTES  = 3,
    RSCFD_PAYLOAD_SIZE_4_BYTES  = 4,
    RSCFD_PAYLOAD_SIZE_5_BYTES  = 5,
    RSCFD_PAYLOAD_SIZE_6_BYTES  = 6,
    RSCFD_PAYLOAD_SIZE_7_BYTES  = 7,
    RSCFD_PAYLOAD_SIZE_8_BYTES  = 8,
    RSCFD_PAYLOAD_SIZE_12_BYTES = 12,
    RSCFD_PAYLOAD_SIZE_16_BYTES = 16,
    RSCFD_PAYLOAD_SIZE_20_BYTES = 20,
    RSCFD_PAYLOAD_SIZE_24_BYTES = 24,
    RSCFD_PAYLOAD_SIZE_32_BYTES = 32,
    RSCFD_PAYLOAD_SIZE_48_BYTES = 48,
    RSCFD_PAYLOAD_SIZE_64_BYTES = 64
} rscfd_payload_size_t;

/*******************************************************************************
 * Receive FIFO Depth Configuration (RFDC)
 * Specify in register RFCC bitfield RFDC
 * Enumeration corresponds to bit position in register.
 *******************************************************************************/
typedef enum
{
    RSCFD_RFDC_0_MSGS       = 0 << 8,
        RSCFD_RFDC_4_MSGS   = 1 << 8,
        RSCFD_RFDC_8_MSGS   = 2 << 8,
        RSCFD_RFDC_16_MSGS  = 3 << 8,
        RSCFD_RFDC_32_MSGS  = 4 << 8,
        RSCFD_RFDC_48_MSGS  = 5 << 8,
        RSCFD_RFDC_64_MSGS  = 6 << 8,
        RSCFD_RFDC_128_MSGS = 7 << 8
}   rscfd_rfdc_t;

/*******************************************************************************
 * Transmit/Receive FIFO Depth Configuration (CFDC)
 * Specify in register CFCC bitfield CFDC
 * Enumeration corresponds to bit position in register.
 *******************************************************************************/
typedef enum
{
    RSCFD_CFDC_0_MSGS       = 0 << 21,
        RSCFD_CFDC_4_MSGS   = 1 << 21,
        RSCFD_CFDC_8_MSGS   = 2 << 21,
        RSCFD_CFDC_16_MSGS  = 3 << 21,
        RSCFD_CFDC_32_MSGS  = 4 << 21,
        RSCFD_CFDC_48_MSGS  = 5 << 21,
        RSCFD_CFDC_64_MSGS  = 6 << 21,
        RSCFD_CFDC_128_MSGS = 7 << 21
}   rscfd_cfdc_t;


/*******************************************************************************
 * Transmit/Receive FIFO PayLoad Size (FPLS)
 * Specify in register CFCC bitfield CFPLS or RFCC bitfield RFPLS
 * Enumeration corresponds to bit position in register.
 *******************************************************************************/
typedef enum
{
    RSCFD_FPLS_8_BYTES      = 0 << 4,
        RSCFD_FPLS_12_BYTES = 1 << 4,
        RSCFD_FPLS_16_BYTES = 2 << 4,
        RSCFD_FPLS_20_BYTES = 3 << 4,
        RSCFD_FPLS_24_BYTES = 4 << 4,
        RSCFD_FPLS_32_BYTES = 5 << 4,
        RSCFD_FPLS_48_BYTES = 6 << 4,
        RSCFD_FPLS_64_BYTES = 7 << 4
}   rscfd_fpls_t;

/*******************************************************************************
 * Transmit buffer CANFD control
 * Register CFDTMFDCTR. Bit fields TMFDF and TMBRS
 * Enumeration corresponds to bit fields
 * NOTE: TMESI not used (0 = error active node)
 *******************************************************************************/
typedef enum
{
    RSCFD_MSG_MODE_CLASSICAL = 0,
    RSCFD_MSG_MODE_FD_SLOW   = 4,
    RSCFD_MSG_MODE_FD_FAST   = 6
}   rscfd_msg_mode_t;

/*******************************************************************************
 * Set Transmit/Receive FIFO Mode
 * Register CFCC bit field CFM
 * Enumeration corresponds to bit field position in register.
 *******************************************************************************/
typedef enum
{
    RSCFD_RXTX_FIFO_MODE_RX     = 0 << 8,
        RSCFD_RXTX_FIFO_MODE_TX = 1 << 8,
        RSCFD_RXTX_FIFO_MODE_GW = 2 << 8
}   rscfd_rxtx_fifo_mode_t;

/*******************************************************************************
 * Disable/Enable bus off error interrupt
 * Register CmCTR bit field BOEIE
 * Enumeration corresponds to bit position within register.
 *******************************************************************************/
typedef enum
{
    RSCFD_ERR_IRQ_DIS = 0,
    RSCFD_ERR_IRQ_EN  = 0x0800
}   rscfd_chnl_err_irq_t;

/*******************************************************************************
 * Receive FIFO Enable
 * Register CFDRFCCx bit field RFE
 * Enumeration corresponds to bit position within register.
 *******************************************************************************/
typedef enum
{
    RSCFD_FIFO_DIS = 0,
    RSCFD_FIFO_EN  = 1
}   rscfd_fifo_en_t;

/*******************************************************************************
 * Receive FIFO Buffer Empty Status Flag
 * Register CFDRFSTSx bitfield RFEMP
 *******************************************************************************/
typedef enum
{
    RSCFD_FIFO_NOT_EMPTY = 0,
    RSCFD_FIFO_EMPTY     = 1
}   rscfd_fifo_empty_t;

/*******************************************************************************
 * FIFO interrupt identification return value based on either
 * 1) Register CFTISTS bits CFxTXIF - Common FIFO Buffer Transmit
 *    Interrupt Request Status Flag.
 * 2) Register CFDRFISTS bits RFxIF - Receive FIFO Buffer Interrupt Request
 *    Status Flags.
 *******************************************************************************/
typedef enum
{
    RSCFD_FIFO_IRQ_NOT_PRESENT = 0,
    RSCFD_FIFO_IRQ_PRESENT     = 1
}   rscfd_fifo_irq_t;


/*******************************************************************************
 * Receive FIFO Interrupt Configuration.
 * Register CFDRFCCx bit field
 * RFIE in bit 1 (Rx Interrupt enable/disable)
 * RFIM in bit 12 (Rx Interrupt on every receive or at a FIFO fullness level)
 * RFIGCV in bits 13-15 (Rx FIFO fullness)
 *******************************************************************************/
typedef enum
{
    RSCFD_RX_FIFO_INT_NONE      = 0x0000,
    RSCFD_RX_FIFO_INT_ALL       = 0x1002,
    RSCFD_RX_FIFO_INT_LVL_1_8TH = 0x0002,
    RSCFD_RX_FIFO_INT_LVL_2_8TH = 0x2002,
    RSCFD_RX_FIFO_INT_LVL_3_8TH = 0x4002,
    RSCFD_RX_FIFO_INT_LVL_4_8TH = 0x6002,
    RSCFD_RX_FIFO_INT_LVL_5_8TH = 0x8002,
    RSCFD_RX_FIFO_INT_LVL_6_8TH = 0xA002,
    RSCFD_RX_FIFO_INT_LVL_7_8TH = 0xC002,
    RSCFD_RX_FIFO_INT_LVL_FULL  = 0xE002
}   rscfd_rx_fifo_int_t;

/*******************************************************************************
 * Common Tx FIFO Interrupt Configuration.
 * Register CFDCFCCx bit field
 * CFTXIE in bit 2 (Tx Interrupt enable/disable)
 * CFIM in bit 12 (Interrupt on every transmit or when FIFO becomes empty)
 *******************************************************************************/
typedef enum
{
    RSCFD_TX_FIFO_INT_NONE  = 0x0000,
    RSCFD_TX_FIFO_INT_EMPTY = 0x0004,
    RSCFD_TX_FIFO_INT_ALL   = 0x1004
}   rscfd_tx_fifo_int_t;


/*##############################################################################
 # Rx and Tx buffers, fifos, ...
 ##############################################################################*/

/*******************************************************************************
 * Rx FIFO number combination of RSCFD unit and FIFO number
 * - sometimes written directly to a register bit field
 * - sometimes identifies bit position within a register (shift)
 *******************************************************************************/
typedef enum
{
    RSCFD_RX_FIFO_0_0 = (RSCFD_UNIT_0 << 24) | 0,
    RSCFD_RX_FIFO_0_1 = (RSCFD_UNIT_0 << 24) | 1,
    RSCFD_RX_FIFO_0_2 = (RSCFD_UNIT_0 << 24) | 2,
    RSCFD_RX_FIFO_0_3 = (RSCFD_UNIT_0 << 24) | 3,
    RSCFD_RX_FIFO_0_4 = (RSCFD_UNIT_0 << 24) | 4,
    RSCFD_RX_FIFO_0_5 = (RSCFD_UNIT_0 << 24) | 5,
    RSCFD_RX_FIFO_0_6 = (RSCFD_UNIT_0 << 24) | 6,
    RSCFD_RX_FIFO_0_7 = (RSCFD_UNIT_0 << 24) | 7,

    RSCFD_RX_FIFO_1_0 = (RSCFD_UNIT_1 << 24) | 0,
    RSCFD_RX_FIFO_1_1 = (RSCFD_UNIT_1 << 24) | 1,
    RSCFD_RX_FIFO_1_2 = (RSCFD_UNIT_1 << 24) | 2,
    RSCFD_RX_FIFO_1_3 = (RSCFD_UNIT_1 << 24) | 3,
    RSCFD_RX_FIFO_1_4 = (RSCFD_UNIT_1 << 24) | 4,
    RSCFD_RX_FIFO_1_5 = (RSCFD_UNIT_1 << 24) | 5,
    RSCFD_RX_FIFO_1_6 = (RSCFD_UNIT_1 << 24) | 6,
    RSCFD_RX_FIFO_1_7 = (RSCFD_UNIT_1 << 24) | 7
}   rscfd_rx_fifo_t;

/*******************************************************************************
 * Rx Buffer number - 128 buffers shared by all channels.
 *******************************************************************************/
typedef enum
{
    RSCFD_RX_BUFF_0_0   = (RSCFD_UNIT_0 << 24) | 0,
    RSCFD_RX_BUFF_0_1   = (RSCFD_UNIT_0 << 24) | 1,
    RSCFD_RX_BUFF_0_2   = (RSCFD_UNIT_0 << 24) | 2,
    RSCFD_RX_BUFF_0_3   = (RSCFD_UNIT_0 << 24) | 3,
    RSCFD_RX_BUFF_0_4   = (RSCFD_UNIT_0 << 24) | 4,
    RSCFD_RX_BUFF_0_5   = (RSCFD_UNIT_0 << 24) | 5,
    RSCFD_RX_BUFF_0_6   = (RSCFD_UNIT_0 << 24) | 6,
    RSCFD_RX_BUFF_0_7   = (RSCFD_UNIT_0 << 24) | 7,
    RSCFD_RX_BUFF_0_8   = (RSCFD_UNIT_0 << 24) | 8,
    RSCFD_RX_BUFF_0_9   = (RSCFD_UNIT_0 << 24) | 9,
    RSCFD_RX_BUFF_0_10  = (RSCFD_UNIT_0 << 24) | 10,
    RSCFD_RX_BUFF_0_11  = (RSCFD_UNIT_0 << 24) | 11,
    RSCFD_RX_BUFF_0_12  = (RSCFD_UNIT_0 << 24) | 12,
    RSCFD_RX_BUFF_0_13  = (RSCFD_UNIT_0 << 24) | 13,
    RSCFD_RX_BUFF_0_14  = (RSCFD_UNIT_0 << 24) | 14,
    RSCFD_RX_BUFF_0_15  = (RSCFD_UNIT_0 << 24) | 15,
    RSCFD_RX_BUFF_0_16  = (RSCFD_UNIT_0 << 24) | 16,
    RSCFD_RX_BUFF_0_17  = (RSCFD_UNIT_0 << 24) | 17,
    RSCFD_RX_BUFF_0_18  = (RSCFD_UNIT_0 << 24) | 18,
    RSCFD_RX_BUFF_0_19  = (RSCFD_UNIT_0 << 24) | 19,
    RSCFD_RX_BUFF_0_20  = (RSCFD_UNIT_0 << 24) | 20,
    RSCFD_RX_BUFF_0_21  = (RSCFD_UNIT_0 << 24) | 21,
    RSCFD_RX_BUFF_0_22  = (RSCFD_UNIT_0 << 24) | 22,
    RSCFD_RX_BUFF_0_23  = (RSCFD_UNIT_0 << 24) | 23,
    RSCFD_RX_BUFF_0_24  = (RSCFD_UNIT_0 << 24) | 24,
    RSCFD_RX_BUFF_0_25  = (RSCFD_UNIT_0 << 24) | 25,
    RSCFD_RX_BUFF_0_26  = (RSCFD_UNIT_0 << 24) | 26,
    RSCFD_RX_BUFF_0_27  = (RSCFD_UNIT_0 << 24) | 27,
    RSCFD_RX_BUFF_0_28  = (RSCFD_UNIT_0 << 24) | 28,
    RSCFD_RX_BUFF_0_29  = (RSCFD_UNIT_0 << 24) | 29,
    RSCFD_RX_BUFF_0_30  = (RSCFD_UNIT_0 << 24) | 30,
    RSCFD_RX_BUFF_0_31  = (RSCFD_UNIT_0 << 24) | 31,
    RSCFD_RX_BUFF_0_32  = (RSCFD_UNIT_0 << 24) | 32,
    RSCFD_RX_BUFF_0_33  = (RSCFD_UNIT_0 << 24) | 33,
    RSCFD_RX_BUFF_0_34  = (RSCFD_UNIT_0 << 24) | 34,
    RSCFD_RX_BUFF_0_35  = (RSCFD_UNIT_0 << 24) | 35,
    RSCFD_RX_BUFF_0_36  = (RSCFD_UNIT_0 << 24) | 36,
    RSCFD_RX_BUFF_0_37  = (RSCFD_UNIT_0 << 24) | 37,
    RSCFD_RX_BUFF_0_38  = (RSCFD_UNIT_0 << 24) | 38,
    RSCFD_RX_BUFF_0_39  = (RSCFD_UNIT_0 << 24) | 39,
    RSCFD_RX_BUFF_0_40  = (RSCFD_UNIT_0 << 24) | 40,
    RSCFD_RX_BUFF_0_41  = (RSCFD_UNIT_0 << 24) | 41,
    RSCFD_RX_BUFF_0_42  = (RSCFD_UNIT_0 << 24) | 42,
    RSCFD_RX_BUFF_0_43  = (RSCFD_UNIT_0 << 24) | 43,
    RSCFD_RX_BUFF_0_44  = (RSCFD_UNIT_0 << 24) | 44,
    RSCFD_RX_BUFF_0_45  = (RSCFD_UNIT_0 << 24) | 45,
    RSCFD_RX_BUFF_0_46  = (RSCFD_UNIT_0 << 24) | 46,
    RSCFD_RX_BUFF_0_47  = (RSCFD_UNIT_0 << 24) | 47,
    RSCFD_RX_BUFF_0_48  = (RSCFD_UNIT_0 << 24) | 48,
    RSCFD_RX_BUFF_0_49  = (RSCFD_UNIT_0 << 24) | 49,
    RSCFD_RX_BUFF_0_50  = (RSCFD_UNIT_0 << 24) | 50,
    RSCFD_RX_BUFF_0_51  = (RSCFD_UNIT_0 << 24) | 51,
    RSCFD_RX_BUFF_0_52  = (RSCFD_UNIT_0 << 24) | 52,
    RSCFD_RX_BUFF_0_53  = (RSCFD_UNIT_0 << 24) | 53,
    RSCFD_RX_BUFF_0_54  = (RSCFD_UNIT_0 << 24) | 54,
    RSCFD_RX_BUFF_0_55  = (RSCFD_UNIT_0 << 24) | 55,
    RSCFD_RX_BUFF_0_56  = (RSCFD_UNIT_0 << 24) | 56,
    RSCFD_RX_BUFF_0_57  = (RSCFD_UNIT_0 << 24) | 57,
    RSCFD_RX_BUFF_0_58  = (RSCFD_UNIT_0 << 24) | 58,
    RSCFD_RX_BUFF_0_59  = (RSCFD_UNIT_0 << 24) | 59,
    RSCFD_RX_BUFF_0_60  = (RSCFD_UNIT_0 << 24) | 60,
    RSCFD_RX_BUFF_0_61  = (RSCFD_UNIT_0 << 24) | 61,
    RSCFD_RX_BUFF_0_62  = (RSCFD_UNIT_0 << 24) | 62,
    RSCFD_RX_BUFF_0_63  = (RSCFD_UNIT_0 << 24) | 63,
    RSCFD_RX_BUFF_0_64  = (RSCFD_UNIT_0 << 24) | 64,
    RSCFD_RX_BUFF_0_65  = (RSCFD_UNIT_0 << 24) | 65,
    RSCFD_RX_BUFF_0_66  = (RSCFD_UNIT_0 << 24) | 66,
    RSCFD_RX_BUFF_0_67  = (RSCFD_UNIT_0 << 24) | 67,
    RSCFD_RX_BUFF_0_68  = (RSCFD_UNIT_0 << 24) | 68,
    RSCFD_RX_BUFF_0_69  = (RSCFD_UNIT_0 << 24) | 69,
    RSCFD_RX_BUFF_0_70  = (RSCFD_UNIT_0 << 24) | 70,
    RSCFD_RX_BUFF_0_71  = (RSCFD_UNIT_0 << 24) | 71,
    RSCFD_RX_BUFF_0_72  = (RSCFD_UNIT_0 << 24) | 72,
    RSCFD_RX_BUFF_0_73  = (RSCFD_UNIT_0 << 24) | 73,
    RSCFD_RX_BUFF_0_74  = (RSCFD_UNIT_0 << 24) | 74,
    RSCFD_RX_BUFF_0_75  = (RSCFD_UNIT_0 << 24) | 75,
    RSCFD_RX_BUFF_0_76  = (RSCFD_UNIT_0 << 24) | 76,
    RSCFD_RX_BUFF_0_77  = (RSCFD_UNIT_0 << 24) | 77,
    RSCFD_RX_BUFF_0_78  = (RSCFD_UNIT_0 << 24) | 78,
    RSCFD_RX_BUFF_0_79  = (RSCFD_UNIT_0 << 24) | 79,
    RSCFD_RX_BUFF_0_80  = (RSCFD_UNIT_0 << 24) | 80,
    RSCFD_RX_BUFF_0_81  = (RSCFD_UNIT_0 << 24) | 81,
    RSCFD_RX_BUFF_0_82  = (RSCFD_UNIT_0 << 24) | 82,
    RSCFD_RX_BUFF_0_83  = (RSCFD_UNIT_0 << 24) | 83,
    RSCFD_RX_BUFF_0_84  = (RSCFD_UNIT_0 << 24) | 84,
    RSCFD_RX_BUFF_0_85  = (RSCFD_UNIT_0 << 24) | 85,
    RSCFD_RX_BUFF_0_86  = (RSCFD_UNIT_0 << 24) | 86,
    RSCFD_RX_BUFF_0_87  = (RSCFD_UNIT_0 << 24) | 87,
    RSCFD_RX_BUFF_0_88  = (RSCFD_UNIT_0 << 24) | 88,
    RSCFD_RX_BUFF_0_89  = (RSCFD_UNIT_0 << 24) | 89,
    RSCFD_RX_BUFF_0_90  = (RSCFD_UNIT_0 << 24) | 90,
    RSCFD_RX_BUFF_0_91  = (RSCFD_UNIT_0 << 24) | 91,
    RSCFD_RX_BUFF_0_92  = (RSCFD_UNIT_0 << 24) | 92,
    RSCFD_RX_BUFF_0_93  = (RSCFD_UNIT_0 << 24) | 93,
    RSCFD_RX_BUFF_0_94  = (RSCFD_UNIT_0 << 24) | 94,
    RSCFD_RX_BUFF_0_95  = (RSCFD_UNIT_0 << 24) | 95,
    RSCFD_RX_BUFF_0_96  = (RSCFD_UNIT_0 << 24) | 96,
    RSCFD_RX_BUFF_0_97  = (RSCFD_UNIT_0 << 24) | 97,
    RSCFD_RX_BUFF_0_98  = (RSCFD_UNIT_0 << 24) | 98,
    RSCFD_RX_BUFF_0_99  = (RSCFD_UNIT_0 << 24) | 99,
    RSCFD_RX_BUFF_0_100 = (RSCFD_UNIT_0 << 24) | 100,
    RSCFD_RX_BUFF_0_101 = (RSCFD_UNIT_0 << 24) | 101,
    RSCFD_RX_BUFF_0_102 = (RSCFD_UNIT_0 << 24) | 102,
    RSCFD_RX_BUFF_0_103 = (RSCFD_UNIT_0 << 24) | 103,
    RSCFD_RX_BUFF_0_104 = (RSCFD_UNIT_0 << 24) | 104,
    RSCFD_RX_BUFF_0_105 = (RSCFD_UNIT_0 << 24) | 105,
    RSCFD_RX_BUFF_0_106 = (RSCFD_UNIT_0 << 24) | 106,
    RSCFD_RX_BUFF_0_107 = (RSCFD_UNIT_0 << 24) | 107,
    RSCFD_RX_BUFF_0_108 = (RSCFD_UNIT_0 << 24) | 108,
    RSCFD_RX_BUFF_0_109 = (RSCFD_UNIT_0 << 24) | 109,
    RSCFD_RX_BUFF_0_110 = (RSCFD_UNIT_0 << 24) | 110,
    RSCFD_RX_BUFF_0_111 = (RSCFD_UNIT_0 << 24) | 111,
    RSCFD_RX_BUFF_0_112 = (RSCFD_UNIT_0 << 24) | 112,
    RSCFD_RX_BUFF_0_113 = (RSCFD_UNIT_0 << 24) | 113,
    RSCFD_RX_BUFF_0_114 = (RSCFD_UNIT_0 << 24) | 114,
    RSCFD_RX_BUFF_0_115 = (RSCFD_UNIT_0 << 24) | 115,
    RSCFD_RX_BUFF_0_116 = (RSCFD_UNIT_0 << 24) | 116,
    RSCFD_RX_BUFF_0_117 = (RSCFD_UNIT_0 << 24) | 117,
    RSCFD_RX_BUFF_0_118 = (RSCFD_UNIT_0 << 24) | 118,
    RSCFD_RX_BUFF_0_119 = (RSCFD_UNIT_0 << 24) | 119,
    RSCFD_RX_BUFF_0_120 = (RSCFD_UNIT_0 << 24) | 120,
    RSCFD_RX_BUFF_0_121 = (RSCFD_UNIT_0 << 24) | 121,
    RSCFD_RX_BUFF_0_122 = (RSCFD_UNIT_0 << 24) | 122,
    RSCFD_RX_BUFF_0_123 = (RSCFD_UNIT_0 << 24) | 123,
    RSCFD_RX_BUFF_0_124 = (RSCFD_UNIT_0 << 24) | 124,
    RSCFD_RX_BUFF_0_125 = (RSCFD_UNIT_0 << 24) | 125,
    RSCFD_RX_BUFF_0_126 = (RSCFD_UNIT_0 << 24) | 126,
    RSCFD_RX_BUFF_0_127 = (RSCFD_UNIT_0 << 24) | 127,

    RSCFD_RX_BUFF_1_0   = (RSCFD_UNIT_1 << 24) | 0,
    RSCFD_RX_BUFF_1_1   = (RSCFD_UNIT_1 << 24) | 1,
    RSCFD_RX_BUFF_1_2   = (RSCFD_UNIT_1 << 24) | 2,
    RSCFD_RX_BUFF_1_3   = (RSCFD_UNIT_1 << 24) | 3,
    RSCFD_RX_BUFF_1_4   = (RSCFD_UNIT_1 << 24) | 4,
    RSCFD_RX_BUFF_1_5   = (RSCFD_UNIT_1 << 24) | 5,
    RSCFD_RX_BUFF_1_6   = (RSCFD_UNIT_1 << 24) | 6,
    RSCFD_RX_BUFF_1_7   = (RSCFD_UNIT_1 << 24) | 7,
    RSCFD_RX_BUFF_1_8   = (RSCFD_UNIT_1 << 24) | 8,
    RSCFD_RX_BUFF_1_9   = (RSCFD_UNIT_1 << 24) | 9,
    RSCFD_RX_BUFF_1_10  = (RSCFD_UNIT_1 << 24) | 10,
    RSCFD_RX_BUFF_1_11  = (RSCFD_UNIT_1 << 24) | 11,
    RSCFD_RX_BUFF_1_12  = (RSCFD_UNIT_1 << 24) | 12,
    RSCFD_RX_BUFF_1_13  = (RSCFD_UNIT_1 << 24) | 13,
    RSCFD_RX_BUFF_1_14  = (RSCFD_UNIT_1 << 24) | 14,
    RSCFD_RX_BUFF_1_15  = (RSCFD_UNIT_1 << 24) | 15,
    RSCFD_RX_BUFF_1_16  = (RSCFD_UNIT_1 << 24) | 16,
    RSCFD_RX_BUFF_1_17  = (RSCFD_UNIT_1 << 24) | 17,
    RSCFD_RX_BUFF_1_18  = (RSCFD_UNIT_1 << 24) | 18,
    RSCFD_RX_BUFF_1_19  = (RSCFD_UNIT_1 << 24) | 19,
    RSCFD_RX_BUFF_1_20  = (RSCFD_UNIT_1 << 24) | 20,
    RSCFD_RX_BUFF_1_21  = (RSCFD_UNIT_1 << 24) | 21,
    RSCFD_RX_BUFF_1_22  = (RSCFD_UNIT_1 << 24) | 22,
    RSCFD_RX_BUFF_1_23  = (RSCFD_UNIT_1 << 24) | 23,
    RSCFD_RX_BUFF_1_24  = (RSCFD_UNIT_1 << 24) | 24,
    RSCFD_RX_BUFF_1_25  = (RSCFD_UNIT_1 << 24) | 25,
    RSCFD_RX_BUFF_1_26  = (RSCFD_UNIT_1 << 24) | 26,
    RSCFD_RX_BUFF_1_27  = (RSCFD_UNIT_1 << 24) | 27,
    RSCFD_RX_BUFF_1_28  = (RSCFD_UNIT_1 << 24) | 28,
    RSCFD_RX_BUFF_1_29  = (RSCFD_UNIT_1 << 24) | 29,
    RSCFD_RX_BUFF_1_30  = (RSCFD_UNIT_1 << 24) | 30,
    RSCFD_RX_BUFF_1_31  = (RSCFD_UNIT_1 << 24) | 31,
    RSCFD_RX_BUFF_1_32  = (RSCFD_UNIT_1 << 24) | 32,
    RSCFD_RX_BUFF_1_33  = (RSCFD_UNIT_1 << 24) | 33,
    RSCFD_RX_BUFF_1_34  = (RSCFD_UNIT_1 << 24) | 34,
    RSCFD_RX_BUFF_1_35  = (RSCFD_UNIT_1 << 24) | 35,
    RSCFD_RX_BUFF_1_36  = (RSCFD_UNIT_1 << 24) | 36,
    RSCFD_RX_BUFF_1_37  = (RSCFD_UNIT_1 << 24) | 37,
    RSCFD_RX_BUFF_1_38  = (RSCFD_UNIT_1 << 24) | 38,
    RSCFD_RX_BUFF_1_39  = (RSCFD_UNIT_1 << 24) | 39,
    RSCFD_RX_BUFF_1_40  = (RSCFD_UNIT_1 << 24) | 40,
    RSCFD_RX_BUFF_1_41  = (RSCFD_UNIT_1 << 24) | 41,
    RSCFD_RX_BUFF_1_42  = (RSCFD_UNIT_1 << 24) | 42,
    RSCFD_RX_BUFF_1_43  = (RSCFD_UNIT_1 << 24) | 43,
    RSCFD_RX_BUFF_1_44  = (RSCFD_UNIT_1 << 24) | 44,
    RSCFD_RX_BUFF_1_45  = (RSCFD_UNIT_1 << 24) | 45,
    RSCFD_RX_BUFF_1_46  = (RSCFD_UNIT_1 << 24) | 46,
    RSCFD_RX_BUFF_1_47  = (RSCFD_UNIT_1 << 24) | 47,
    RSCFD_RX_BUFF_1_48  = (RSCFD_UNIT_1 << 24) | 48,
    RSCFD_RX_BUFF_1_49  = (RSCFD_UNIT_1 << 24) | 49,
    RSCFD_RX_BUFF_1_50  = (RSCFD_UNIT_1 << 24) | 50,
    RSCFD_RX_BUFF_1_51  = (RSCFD_UNIT_1 << 24) | 51,
    RSCFD_RX_BUFF_1_52  = (RSCFD_UNIT_1 << 24) | 52,
    RSCFD_RX_BUFF_1_53  = (RSCFD_UNIT_1 << 24) | 53,
    RSCFD_RX_BUFF_1_54  = (RSCFD_UNIT_1 << 24) | 54,
    RSCFD_RX_BUFF_1_55  = (RSCFD_UNIT_1 << 24) | 55,
    RSCFD_RX_BUFF_1_56  = (RSCFD_UNIT_1 << 24) | 56,
    RSCFD_RX_BUFF_1_57  = (RSCFD_UNIT_1 << 24) | 57,
    RSCFD_RX_BUFF_1_58  = (RSCFD_UNIT_1 << 24) | 58,
    RSCFD_RX_BUFF_1_59  = (RSCFD_UNIT_1 << 24) | 59,
    RSCFD_RX_BUFF_1_60  = (RSCFD_UNIT_1 << 24) | 60,
    RSCFD_RX_BUFF_1_61  = (RSCFD_UNIT_1 << 24) | 61,
    RSCFD_RX_BUFF_1_62  = (RSCFD_UNIT_1 << 24) | 62,
    RSCFD_RX_BUFF_1_63  = (RSCFD_UNIT_1 << 24) | 63,
    RSCFD_RX_BUFF_1_64  = (RSCFD_UNIT_1 << 24) | 64,
    RSCFD_RX_BUFF_1_65  = (RSCFD_UNIT_1 << 24) | 65,
    RSCFD_RX_BUFF_1_66  = (RSCFD_UNIT_1 << 24) | 66,
    RSCFD_RX_BUFF_1_67  = (RSCFD_UNIT_1 << 24) | 67,
    RSCFD_RX_BUFF_1_68  = (RSCFD_UNIT_1 << 24) | 68,
    RSCFD_RX_BUFF_1_69  = (RSCFD_UNIT_1 << 24) | 69,
    RSCFD_RX_BUFF_1_70  = (RSCFD_UNIT_1 << 24) | 70,
    RSCFD_RX_BUFF_1_71  = (RSCFD_UNIT_1 << 24) | 71,
    RSCFD_RX_BUFF_1_72  = (RSCFD_UNIT_1 << 24) | 72,
    RSCFD_RX_BUFF_1_73  = (RSCFD_UNIT_1 << 24) | 73,
    RSCFD_RX_BUFF_1_74  = (RSCFD_UNIT_1 << 24) | 74,
    RSCFD_RX_BUFF_1_75  = (RSCFD_UNIT_1 << 24) | 75,
    RSCFD_RX_BUFF_1_76  = (RSCFD_UNIT_1 << 24) | 76,
    RSCFD_RX_BUFF_1_77  = (RSCFD_UNIT_1 << 24) | 77,
    RSCFD_RX_BUFF_1_78  = (RSCFD_UNIT_1 << 24) | 78,
    RSCFD_RX_BUFF_1_79  = (RSCFD_UNIT_1 << 24) | 79,
    RSCFD_RX_BUFF_1_80  = (RSCFD_UNIT_1 << 24) | 80,
    RSCFD_RX_BUFF_1_81  = (RSCFD_UNIT_1 << 24) | 81,
    RSCFD_RX_BUFF_1_82  = (RSCFD_UNIT_1 << 24) | 82,
    RSCFD_RX_BUFF_1_83  = (RSCFD_UNIT_1 << 24) | 83,
    RSCFD_RX_BUFF_1_84  = (RSCFD_UNIT_1 << 24) | 84,
    RSCFD_RX_BUFF_1_85  = (RSCFD_UNIT_1 << 24) | 85,
    RSCFD_RX_BUFF_1_86  = (RSCFD_UNIT_1 << 24) | 86,
    RSCFD_RX_BUFF_1_87  = (RSCFD_UNIT_1 << 24) | 87,
    RSCFD_RX_BUFF_1_88  = (RSCFD_UNIT_1 << 24) | 88,
    RSCFD_RX_BUFF_1_89  = (RSCFD_UNIT_1 << 24) | 89,
    RSCFD_RX_BUFF_1_90  = (RSCFD_UNIT_1 << 24) | 90,
    RSCFD_RX_BUFF_1_91  = (RSCFD_UNIT_1 << 24) | 91,
    RSCFD_RX_BUFF_1_92  = (RSCFD_UNIT_1 << 24) | 92,
    RSCFD_RX_BUFF_1_93  = (RSCFD_UNIT_1 << 24) | 93,
    RSCFD_RX_BUFF_1_94  = (RSCFD_UNIT_1 << 24) | 94,
    RSCFD_RX_BUFF_1_95  = (RSCFD_UNIT_1 << 24) | 95,
    RSCFD_RX_BUFF_1_96  = (RSCFD_UNIT_1 << 24) | 96,
    RSCFD_RX_BUFF_1_97  = (RSCFD_UNIT_1 << 24) | 97,
    RSCFD_RX_BUFF_1_98  = (RSCFD_UNIT_1 << 24) | 98,
    RSCFD_RX_BUFF_1_99  = (RSCFD_UNIT_1 << 24) | 99,
    RSCFD_RX_BUFF_1_100 = (RSCFD_UNIT_1 << 24) | 100,
    RSCFD_RX_BUFF_1_101 = (RSCFD_UNIT_1 << 24) | 101,
    RSCFD_RX_BUFF_1_102 = (RSCFD_UNIT_1 << 24) | 102,
    RSCFD_RX_BUFF_1_103 = (RSCFD_UNIT_1 << 24) | 103,
    RSCFD_RX_BUFF_1_104 = (RSCFD_UNIT_1 << 24) | 104,
    RSCFD_RX_BUFF_1_105 = (RSCFD_UNIT_1 << 24) | 105,
    RSCFD_RX_BUFF_1_106 = (RSCFD_UNIT_1 << 24) | 106,
    RSCFD_RX_BUFF_1_107 = (RSCFD_UNIT_1 << 24) | 107,
    RSCFD_RX_BUFF_1_108 = (RSCFD_UNIT_1 << 24) | 108,
    RSCFD_RX_BUFF_1_109 = (RSCFD_UNIT_1 << 24) | 109,
    RSCFD_RX_BUFF_1_110 = (RSCFD_UNIT_1 << 24) | 110,
    RSCFD_RX_BUFF_1_111 = (RSCFD_UNIT_1 << 24) | 111,
    RSCFD_RX_BUFF_1_112 = (RSCFD_UNIT_1 << 24) | 112,
    RSCFD_RX_BUFF_1_113 = (RSCFD_UNIT_1 << 24) | 113,
    RSCFD_RX_BUFF_1_114 = (RSCFD_UNIT_1 << 24) | 114,
    RSCFD_RX_BUFF_1_115 = (RSCFD_UNIT_1 << 24) | 115,
    RSCFD_RX_BUFF_1_116 = (RSCFD_UNIT_1 << 24) | 116,
    RSCFD_RX_BUFF_1_117 = (RSCFD_UNIT_1 << 24) | 117,
    RSCFD_RX_BUFF_1_118 = (RSCFD_UNIT_1 << 24) | 118,
    RSCFD_RX_BUFF_1_119 = (RSCFD_UNIT_1 << 24) | 119,
    RSCFD_RX_BUFF_1_120 = (RSCFD_UNIT_1 << 24) | 120,
    RSCFD_RX_BUFF_1_121 = (RSCFD_UNIT_1 << 24) | 121,
    RSCFD_RX_BUFF_1_122 = (RSCFD_UNIT_1 << 24) | 122,
    RSCFD_RX_BUFF_1_123 = (RSCFD_UNIT_1 << 24) | 123,
    RSCFD_RX_BUFF_1_124 = (RSCFD_UNIT_1 << 24) | 124,
    RSCFD_RX_BUFF_1_125 = (RSCFD_UNIT_1 << 24) | 125,
    RSCFD_RX_BUFF_1_126 = (RSCFD_UNIT_1 << 24) | 126,
    RSCFD_RX_BUFF_1_127 = (RSCFD_UNIT_1 << 24) | 127
}   rscfd_rx_buff_t;


/*******************************************************************************
 * Number of RX message buffers
 * Register CFDRMNB bit field NRXMB
 * Enumeration matches register bit field
 *******************************************************************************/
typedef enum
{
    RSCFD_RX_BUFF_CNT_0   = 0,            /* no receive buffers allocated */
    RSCFD_RX_BUFF_CNT_1   = 1,
    RSCFD_RX_BUFF_CNT_2   = 2,
    RSCFD_RX_BUFF_CNT_3   = 3,
    RSCFD_RX_BUFF_CNT_4   = 4,
    RSCFD_RX_BUFF_CNT_5   = 5,
    RSCFD_RX_BUFF_CNT_6   = 6,
    RSCFD_RX_BUFF_CNT_7   = 7,
    RSCFD_RX_BUFF_CNT_8   = 8,
    RSCFD_RX_BUFF_CNT_9   = 9,
    RSCFD_RX_BUFF_CNT_10  = 10,
    RSCFD_RX_BUFF_CNT_11  = 11,
    RSCFD_RX_BUFF_CNT_12  = 12,
    RSCFD_RX_BUFF_CNT_13  = 13,
    RSCFD_RX_BUFF_CNT_14  = 14,
    RSCFD_RX_BUFF_CNT_15  = 15,
    RSCFD_RX_BUFF_CNT_16  = 16,
    RSCFD_RX_BUFF_CNT_17  = 17,
    RSCFD_RX_BUFF_CNT_18  = 18,
    RSCFD_RX_BUFF_CNT_19  = 19,
    RSCFD_RX_BUFF_CNT_20  = 20,
    RSCFD_RX_BUFF_CNT_21  = 21,
    RSCFD_RX_BUFF_CNT_22  = 22,
    RSCFD_RX_BUFF_CNT_23  = 23,
    RSCFD_RX_BUFF_CNT_24  = 24,
    RSCFD_RX_BUFF_CNT_25  = 25,
    RSCFD_RX_BUFF_CNT_26  = 26,
    RSCFD_RX_BUFF_CNT_27  = 27,
    RSCFD_RX_BUFF_CNT_28  = 28,
    RSCFD_RX_BUFF_CNT_29  = 29,
    RSCFD_RX_BUFF_CNT_30  = 30,
    RSCFD_RX_BUFF_CNT_31  = 31,
    RSCFD_RX_BUFF_CNT_32  = 32,
    RSCFD_RX_BUFF_CNT_33  = 33,
    RSCFD_RX_BUFF_CNT_34  = 34,
    RSCFD_RX_BUFF_CNT_35  = 35,
    RSCFD_RX_BUFF_CNT_36  = 36,
    RSCFD_RX_BUFF_CNT_37  = 37,
    RSCFD_RX_BUFF_CNT_38  = 38,
    RSCFD_RX_BUFF_CNT_39  = 39,
    RSCFD_RX_BUFF_CNT_40  = 40,
    RSCFD_RX_BUFF_CNT_41  = 41,
    RSCFD_RX_BUFF_CNT_42  = 42,
    RSCFD_RX_BUFF_CNT_43  = 43,
    RSCFD_RX_BUFF_CNT_44  = 44,
    RSCFD_RX_BUFF_CNT_45  = 45,
    RSCFD_RX_BUFF_CNT_46  = 46,
    RSCFD_RX_BUFF_CNT_47  = 47,
    RSCFD_RX_BUFF_CNT_48  = 48,
    RSCFD_RX_BUFF_CNT_49  = 49,
    RSCFD_RX_BUFF_CNT_50  = 50,
    RSCFD_RX_BUFF_CNT_51  = 51,
    RSCFD_RX_BUFF_CNT_52  = 52,
    RSCFD_RX_BUFF_CNT_53  = 53,
    RSCFD_RX_BUFF_CNT_54  = 54,
    RSCFD_RX_BUFF_CNT_55  = 55,
    RSCFD_RX_BUFF_CNT_56  = 56,
    RSCFD_RX_BUFF_CNT_57  = 57,
    RSCFD_RX_BUFF_CNT_58  = 58,
    RSCFD_RX_BUFF_CNT_59  = 59,
    RSCFD_RX_BUFF_CNT_60  = 60,
    RSCFD_RX_BUFF_CNT_61  = 61,
    RSCFD_RX_BUFF_CNT_62  = 62,
    RSCFD_RX_BUFF_CNT_63  = 63,
    RSCFD_RX_BUFF_CNT_64  = 64,
    RSCFD_RX_BUFF_CNT_65  = 65,
    RSCFD_RX_BUFF_CNT_66  = 66,
    RSCFD_RX_BUFF_CNT_67  = 67,
    RSCFD_RX_BUFF_CNT_68  = 68,
    RSCFD_RX_BUFF_CNT_69  = 69,
    RSCFD_RX_BUFF_CNT_70  = 70,
    RSCFD_RX_BUFF_CNT_71  = 71,
    RSCFD_RX_BUFF_CNT_72  = 72,
    RSCFD_RX_BUFF_CNT_73  = 73,
    RSCFD_RX_BUFF_CNT_74  = 74,
    RSCFD_RX_BUFF_CNT_75  = 75,
    RSCFD_RX_BUFF_CNT_76  = 76,
    RSCFD_RX_BUFF_CNT_77  = 77,
    RSCFD_RX_BUFF_CNT_78  = 78,
    RSCFD_RX_BUFF_CNT_79  = 79,
    RSCFD_RX_BUFF_CNT_80  = 80,
    RSCFD_RX_BUFF_CNT_81  = 81,
    RSCFD_RX_BUFF_CNT_82  = 82,
    RSCFD_RX_BUFF_CNT_83  = 83,
    RSCFD_RX_BUFF_CNT_84  = 84,
    RSCFD_RX_BUFF_CNT_85  = 85,
    RSCFD_RX_BUFF_CNT_86  = 86,
    RSCFD_RX_BUFF_CNT_87  = 87,
    RSCFD_RX_BUFF_CNT_88  = 88,
    RSCFD_RX_BUFF_CNT_89  = 89,
    RSCFD_RX_BUFF_CNT_90  = 90,
    RSCFD_RX_BUFF_CNT_91  = 91,
    RSCFD_RX_BUFF_CNT_92  = 92,
    RSCFD_RX_BUFF_CNT_93  = 93,
    RSCFD_RX_BUFF_CNT_94  = 94,
    RSCFD_RX_BUFF_CNT_95  = 95,
    RSCFD_RX_BUFF_CNT_96  = 96,
    RSCFD_RX_BUFF_CNT_97  = 97,
    RSCFD_RX_BUFF_CNT_98  = 98,
    RSCFD_RX_BUFF_CNT_99  = 99,
    RSCFD_RX_BUFF_CNT_100 = 100,
    RSCFD_RX_BUFF_CNT_101 = 101,
    RSCFD_RX_BUFF_CNT_102 = 102,
    RSCFD_RX_BUFF_CNT_103 = 103,
    RSCFD_RX_BUFF_CNT_104 = 104,
    RSCFD_RX_BUFF_CNT_105 = 105,
    RSCFD_RX_BUFF_CNT_106 = 106,
    RSCFD_RX_BUFF_CNT_107 = 107,
    RSCFD_RX_BUFF_CNT_108 = 108,
    RSCFD_RX_BUFF_CNT_109 = 109,
    RSCFD_RX_BUFF_CNT_110 = 110,
    RSCFD_RX_BUFF_CNT_111 = 111,
    RSCFD_RX_BUFF_CNT_112 = 112,
    RSCFD_RX_BUFF_CNT_113 = 113,
    RSCFD_RX_BUFF_CNT_114 = 114,
    RSCFD_RX_BUFF_CNT_115 = 115,
    RSCFD_RX_BUFF_CNT_116 = 116,
    RSCFD_RX_BUFF_CNT_117 = 117,
    RSCFD_RX_BUFF_CNT_118 = 118,
    RSCFD_RX_BUFF_CNT_119 = 119,
    RSCFD_RX_BUFF_CNT_120 = 120,
    RSCFD_RX_BUFF_CNT_121 = 121,
    RSCFD_RX_BUFF_CNT_122 = 122,
    RSCFD_RX_BUFF_CNT_123 = 123,
    RSCFD_RX_BUFF_CNT_124 = 124,
    RSCFD_RX_BUFF_CNT_125 = 125,
    RSCFD_RX_BUFF_CNT_126 = 126,
    RSCFD_RX_BUFF_CNT_127 = 127,
    RSCFD_RX_BUFF_CNT_128 = 128
} rscfd_rx_buff_cnt_t;

/*******************************************************************************
 * Enumerations of destinations for received messages.
 *   Rx FIFO number - 8 per unit
 *   Rx Buffer number - 128 in unit 0, 128 in unit 1 (shared by all channels).
 *******************************************************************************/
typedef enum
{
    /* Unit 0 - Rx FIFO */
    RSCFD_RX_DST_FIFO_0_0   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_0_0,
    RSCFD_RX_DST_FIFO_0_1   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_0_1,
    RSCFD_RX_DST_FIFO_0_2   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_0_2,
    RSCFD_RX_DST_FIFO_0_3   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_0_3,
    RSCFD_RX_DST_FIFO_0_4   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_0_4,
    RSCFD_RX_DST_FIFO_0_5   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_0_5,
    RSCFD_RX_DST_FIFO_0_6   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_0_6,
    RSCFD_RX_DST_FIFO_0_7   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_0_7,

    /* Unit 1 - Rx FIFO */
    RSCFD_RX_DST_FIFO_1_0   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_1_0,
    RSCFD_RX_DST_FIFO_1_1   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_1_1,
    RSCFD_RX_DST_FIFO_1_2   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_1_2,
    RSCFD_RX_DST_FIFO_1_3   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_1_3,
    RSCFD_RX_DST_FIFO_1_4   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_1_4,
    RSCFD_RX_DST_FIFO_1_5   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_1_5,
    RSCFD_RX_DST_FIFO_1_6   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_1_6,
    RSCFD_RX_DST_FIFO_1_7   = RSCFD_RX_FIFO | RSCFD_RX_FIFO_1_7,

    /* Unit 0 - Rx Buffer */
    RSCFD_RX_DST_BUFF_0_0   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_0,
    RSCFD_RX_DST_BUFF_0_1   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_1,
    RSCFD_RX_DST_BUFF_0_2   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_2,
    RSCFD_RX_DST_BUFF_0_3   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_3,
    RSCFD_RX_DST_BUFF_0_4   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_4,
    RSCFD_RX_DST_BUFF_0_5   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_5,
    RSCFD_RX_DST_BUFF_0_6   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_6,
    RSCFD_RX_DST_BUFF_0_7   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_7,
    RSCFD_RX_DST_BUFF_0_8   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_8,
    RSCFD_RX_DST_BUFF_0_9   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_9,
    RSCFD_RX_DST_BUFF_0_10  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_10,
    RSCFD_RX_DST_BUFF_0_11  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_11,
    RSCFD_RX_DST_BUFF_0_12  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_12,
    RSCFD_RX_DST_BUFF_0_13  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_13,
    RSCFD_RX_DST_BUFF_0_14  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_14,
    RSCFD_RX_DST_BUFF_0_15  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_15,
    RSCFD_RX_DST_BUFF_0_16  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_16,
    RSCFD_RX_DST_BUFF_0_17  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_17,
    RSCFD_RX_DST_BUFF_0_18  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_18,
    RSCFD_RX_DST_BUFF_0_19  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_19,
    RSCFD_RX_DST_BUFF_0_20  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_20,
    RSCFD_RX_DST_BUFF_0_21  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_21,
    RSCFD_RX_DST_BUFF_0_22  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_22,
    RSCFD_RX_DST_BUFF_0_23  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_23,
    RSCFD_RX_DST_BUFF_0_24  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_24,
    RSCFD_RX_DST_BUFF_0_25  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_25,
    RSCFD_RX_DST_BUFF_0_26  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_26,
    RSCFD_RX_DST_BUFF_0_27  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_27,
    RSCFD_RX_DST_BUFF_0_28  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_28,
    RSCFD_RX_DST_BUFF_0_29  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_29,
    RSCFD_RX_DST_BUFF_0_30  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_30,
    RSCFD_RX_DST_BUFF_0_31  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_31,
    RSCFD_RX_DST_BUFF_0_32  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_32,
    RSCFD_RX_DST_BUFF_0_33  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_33,
    RSCFD_RX_DST_BUFF_0_34  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_34,
    RSCFD_RX_DST_BUFF_0_35  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_35,
    RSCFD_RX_DST_BUFF_0_36  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_36,
    RSCFD_RX_DST_BUFF_0_37  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_37,
    RSCFD_RX_DST_BUFF_0_38  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_38,
    RSCFD_RX_DST_BUFF_0_39  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_39,
    RSCFD_RX_DST_BUFF_0_40  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_40,
    RSCFD_RX_DST_BUFF_0_41  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_41,
    RSCFD_RX_DST_BUFF_0_42  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_42,
    RSCFD_RX_DST_BUFF_0_43  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_43,
    RSCFD_RX_DST_BUFF_0_44  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_44,
    RSCFD_RX_DST_BUFF_0_45  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_45,
    RSCFD_RX_DST_BUFF_0_46  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_46,
    RSCFD_RX_DST_BUFF_0_47  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_47,
    RSCFD_RX_DST_BUFF_0_48  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_48,
    RSCFD_RX_DST_BUFF_0_49  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_49,
    RSCFD_RX_DST_BUFF_0_50  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_50,
    RSCFD_RX_DST_BUFF_0_51  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_51,
    RSCFD_RX_DST_BUFF_0_52  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_52,
    RSCFD_RX_DST_BUFF_0_53  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_53,
    RSCFD_RX_DST_BUFF_0_54  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_54,
    RSCFD_RX_DST_BUFF_0_55  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_55,
    RSCFD_RX_DST_BUFF_0_56  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_56,
    RSCFD_RX_DST_BUFF_0_57  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_57,
    RSCFD_RX_DST_BUFF_0_58  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_58,
    RSCFD_RX_DST_BUFF_0_59  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_59,
    RSCFD_RX_DST_BUFF_0_60  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_60,
    RSCFD_RX_DST_BUFF_0_61  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_61,
    RSCFD_RX_DST_BUFF_0_62  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_62,
    RSCFD_RX_DST_BUFF_0_63  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_63,
    RSCFD_RX_DST_BUFF_0_64  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_64,
    RSCFD_RX_DST_BUFF_0_65  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_65,
    RSCFD_RX_DST_BUFF_0_66  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_66,
    RSCFD_RX_DST_BUFF_0_67  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_67,
    RSCFD_RX_DST_BUFF_0_68  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_68,
    RSCFD_RX_DST_BUFF_0_69  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_69,
    RSCFD_RX_DST_BUFF_0_70  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_70,
    RSCFD_RX_DST_BUFF_0_71  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_71,
    RSCFD_RX_DST_BUFF_0_72  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_72,
    RSCFD_RX_DST_BUFF_0_73  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_73,
    RSCFD_RX_DST_BUFF_0_74  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_74,
    RSCFD_RX_DST_BUFF_0_75  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_75,
    RSCFD_RX_DST_BUFF_0_76  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_76,
    RSCFD_RX_DST_BUFF_0_77  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_77,
    RSCFD_RX_DST_BUFF_0_78  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_78,
    RSCFD_RX_DST_BUFF_0_79  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_79,
    RSCFD_RX_DST_BUFF_0_80  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_80,
    RSCFD_RX_DST_BUFF_0_81  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_81,
    RSCFD_RX_DST_BUFF_0_82  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_82,
    RSCFD_RX_DST_BUFF_0_83  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_83,
    RSCFD_RX_DST_BUFF_0_84  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_84,
    RSCFD_RX_DST_BUFF_0_85  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_85,
    RSCFD_RX_DST_BUFF_0_86  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_86,
    RSCFD_RX_DST_BUFF_0_87  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_87,
    RSCFD_RX_DST_BUFF_0_88  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_88,
    RSCFD_RX_DST_BUFF_0_89  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_89,
    RSCFD_RX_DST_BUFF_0_90  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_90,
    RSCFD_RX_DST_BUFF_0_91  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_91,
    RSCFD_RX_DST_BUFF_0_92  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_92,
    RSCFD_RX_DST_BUFF_0_93  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_93,
    RSCFD_RX_DST_BUFF_0_94  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_94,
    RSCFD_RX_DST_BUFF_0_95  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_95,
    RSCFD_RX_DST_BUFF_0_96  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_96,
    RSCFD_RX_DST_BUFF_0_97  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_97,
    RSCFD_RX_DST_BUFF_0_98  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_98,
    RSCFD_RX_DST_BUFF_0_99  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_99,
    RSCFD_RX_DST_BUFF_0_100 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_100,
    RSCFD_RX_DST_BUFF_0_101 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_101,
    RSCFD_RX_DST_BUFF_0_102 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_102,
    RSCFD_RX_DST_BUFF_0_103 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_103,
    RSCFD_RX_DST_BUFF_0_104 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_104,
    RSCFD_RX_DST_BUFF_0_105 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_105,
    RSCFD_RX_DST_BUFF_0_106 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_106,
    RSCFD_RX_DST_BUFF_0_107 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_107,
    RSCFD_RX_DST_BUFF_0_108 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_108,
    RSCFD_RX_DST_BUFF_0_109 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_109,
    RSCFD_RX_DST_BUFF_0_110 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_110,
    RSCFD_RX_DST_BUFF_0_111 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_111,
    RSCFD_RX_DST_BUFF_0_112 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_112,
    RSCFD_RX_DST_BUFF_0_113 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_113,
    RSCFD_RX_DST_BUFF_0_114 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_114,
    RSCFD_RX_DST_BUFF_0_115 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_115,
    RSCFD_RX_DST_BUFF_0_116 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_116,
    RSCFD_RX_DST_BUFF_0_117 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_117,
    RSCFD_RX_DST_BUFF_0_118 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_118,
    RSCFD_RX_DST_BUFF_0_119 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_119,
    RSCFD_RX_DST_BUFF_0_120 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_120,
    RSCFD_RX_DST_BUFF_0_121 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_121,
    RSCFD_RX_DST_BUFF_0_122 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_122,
    RSCFD_RX_DST_BUFF_0_123 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_123,
    RSCFD_RX_DST_BUFF_0_124 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_124,
    RSCFD_RX_DST_BUFF_0_125 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_125,
    RSCFD_RX_DST_BUFF_0_126 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_126,
    RSCFD_RX_DST_BUFF_0_127 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_0_127,

    /* Unit 1 - Rx Buffer */
    RSCFD_RX_DST_BUFF_1_0   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_0,
    RSCFD_RX_DST_BUFF_1_1   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_1,
    RSCFD_RX_DST_BUFF_1_2   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_2,
    RSCFD_RX_DST_BUFF_1_3   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_3,
    RSCFD_RX_DST_BUFF_1_4   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_4,
    RSCFD_RX_DST_BUFF_1_5   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_5,
    RSCFD_RX_DST_BUFF_1_6   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_6,
    RSCFD_RX_DST_BUFF_1_7   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_7,
    RSCFD_RX_DST_BUFF_1_8   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_8,
    RSCFD_RX_DST_BUFF_1_9   = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_9,
    RSCFD_RX_DST_BUFF_1_10  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_10,
    RSCFD_RX_DST_BUFF_1_11  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_11,
    RSCFD_RX_DST_BUFF_1_12  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_12,
    RSCFD_RX_DST_BUFF_1_13  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_13,
    RSCFD_RX_DST_BUFF_1_14  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_14,
    RSCFD_RX_DST_BUFF_1_15  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_15,
    RSCFD_RX_DST_BUFF_1_16  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_16,
    RSCFD_RX_DST_BUFF_1_17  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_17,
    RSCFD_RX_DST_BUFF_1_18  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_18,
    RSCFD_RX_DST_BUFF_1_19  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_19,
    RSCFD_RX_DST_BUFF_1_20  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_20,
    RSCFD_RX_DST_BUFF_1_21  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_21,
    RSCFD_RX_DST_BUFF_1_22  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_22,
    RSCFD_RX_DST_BUFF_1_23  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_23,
    RSCFD_RX_DST_BUFF_1_24  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_24,
    RSCFD_RX_DST_BUFF_1_25  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_25,
    RSCFD_RX_DST_BUFF_1_26  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_26,
    RSCFD_RX_DST_BUFF_1_27  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_27,
    RSCFD_RX_DST_BUFF_1_28  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_28,
    RSCFD_RX_DST_BUFF_1_29  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_29,
    RSCFD_RX_DST_BUFF_1_30  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_30,
    RSCFD_RX_DST_BUFF_1_31  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_31,
    RSCFD_RX_DST_BUFF_1_32  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_32,
    RSCFD_RX_DST_BUFF_1_33  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_33,
    RSCFD_RX_DST_BUFF_1_34  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_34,
    RSCFD_RX_DST_BUFF_1_35  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_35,
    RSCFD_RX_DST_BUFF_1_36  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_36,
    RSCFD_RX_DST_BUFF_1_37  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_37,
    RSCFD_RX_DST_BUFF_1_38  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_38,
    RSCFD_RX_DST_BUFF_1_39  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_39,
    RSCFD_RX_DST_BUFF_1_40  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_40,
    RSCFD_RX_DST_BUFF_1_41  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_41,
    RSCFD_RX_DST_BUFF_1_42  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_42,
    RSCFD_RX_DST_BUFF_1_43  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_43,
    RSCFD_RX_DST_BUFF_1_44  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_44,
    RSCFD_RX_DST_BUFF_1_45  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_45,
    RSCFD_RX_DST_BUFF_1_46  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_46,
    RSCFD_RX_DST_BUFF_1_47  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_47,
    RSCFD_RX_DST_BUFF_1_48  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_48,
    RSCFD_RX_DST_BUFF_1_49  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_49,
    RSCFD_RX_DST_BUFF_1_50  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_50,
    RSCFD_RX_DST_BUFF_1_51  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_51,
    RSCFD_RX_DST_BUFF_1_52  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_52,
    RSCFD_RX_DST_BUFF_1_53  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_53,
    RSCFD_RX_DST_BUFF_1_54  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_54,
    RSCFD_RX_DST_BUFF_1_55  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_55,
    RSCFD_RX_DST_BUFF_1_56  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_56,
    RSCFD_RX_DST_BUFF_1_57  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_57,
    RSCFD_RX_DST_BUFF_1_58  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_58,
    RSCFD_RX_DST_BUFF_1_59  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_59,
    RSCFD_RX_DST_BUFF_1_60  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_60,
    RSCFD_RX_DST_BUFF_1_61  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_61,
    RSCFD_RX_DST_BUFF_1_62  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_62,
    RSCFD_RX_DST_BUFF_1_63  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_63,
    RSCFD_RX_DST_BUFF_1_64  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_64,
    RSCFD_RX_DST_BUFF_1_65  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_65,
    RSCFD_RX_DST_BUFF_1_66  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_66,
    RSCFD_RX_DST_BUFF_1_67  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_67,
    RSCFD_RX_DST_BUFF_1_68  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_68,
    RSCFD_RX_DST_BUFF_1_69  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_69,
    RSCFD_RX_DST_BUFF_1_70  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_70,
    RSCFD_RX_DST_BUFF_1_71  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_71,
    RSCFD_RX_DST_BUFF_1_72  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_72,
    RSCFD_RX_DST_BUFF_1_73  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_73,
    RSCFD_RX_DST_BUFF_1_74  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_74,
    RSCFD_RX_DST_BUFF_1_75  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_75,
    RSCFD_RX_DST_BUFF_1_76  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_76,
    RSCFD_RX_DST_BUFF_1_77  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_77,
    RSCFD_RX_DST_BUFF_1_78  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_78,
    RSCFD_RX_DST_BUFF_1_79  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_79,
    RSCFD_RX_DST_BUFF_1_80  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_80,
    RSCFD_RX_DST_BUFF_1_81  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_81,
    RSCFD_RX_DST_BUFF_1_82  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_82,
    RSCFD_RX_DST_BUFF_1_83  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_83,
    RSCFD_RX_DST_BUFF_1_84  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_84,
    RSCFD_RX_DST_BUFF_1_85  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_85,
    RSCFD_RX_DST_BUFF_1_86  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_86,
    RSCFD_RX_DST_BUFF_1_87  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_87,
    RSCFD_RX_DST_BUFF_1_88  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_88,
    RSCFD_RX_DST_BUFF_1_89  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_89,
    RSCFD_RX_DST_BUFF_1_90  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_90,
    RSCFD_RX_DST_BUFF_1_91  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_91,
    RSCFD_RX_DST_BUFF_1_92  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_92,
    RSCFD_RX_DST_BUFF_1_93  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_93,
    RSCFD_RX_DST_BUFF_1_94  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_94,
    RSCFD_RX_DST_BUFF_1_95  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_95,
    RSCFD_RX_DST_BUFF_1_96  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_96,
    RSCFD_RX_DST_BUFF_1_97  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_97,
    RSCFD_RX_DST_BUFF_1_98  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_98,
    RSCFD_RX_DST_BUFF_1_99  = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_99,
    RSCFD_RX_DST_BUFF_1_100 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_100,
    RSCFD_RX_DST_BUFF_1_101 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_101,
    RSCFD_RX_DST_BUFF_1_102 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_102,
    RSCFD_RX_DST_BUFF_1_103 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_103,
    RSCFD_RX_DST_BUFF_1_104 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_104,
    RSCFD_RX_DST_BUFF_1_105 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_105,
    RSCFD_RX_DST_BUFF_1_106 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_106,
    RSCFD_RX_DST_BUFF_1_107 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_107,
    RSCFD_RX_DST_BUFF_1_108 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_108,
    RSCFD_RX_DST_BUFF_1_109 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_109,
    RSCFD_RX_DST_BUFF_1_110 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_110,
    RSCFD_RX_DST_BUFF_1_111 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_111,
    RSCFD_RX_DST_BUFF_1_112 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_112,
    RSCFD_RX_DST_BUFF_1_113 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_113,
    RSCFD_RX_DST_BUFF_1_114 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_114,
    RSCFD_RX_DST_BUFF_1_115 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_115,
    RSCFD_RX_DST_BUFF_1_116 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_116,
    RSCFD_RX_DST_BUFF_1_117 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_117,
    RSCFD_RX_DST_BUFF_1_118 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_118,
    RSCFD_RX_DST_BUFF_1_119 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_119,
    RSCFD_RX_DST_BUFF_1_120 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_120,
    RSCFD_RX_DST_BUFF_1_121 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_121,
    RSCFD_RX_DST_BUFF_1_122 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_122,
    RSCFD_RX_DST_BUFF_1_123 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_123,
    RSCFD_RX_DST_BUFF_1_124 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_124,
    RSCFD_RX_DST_BUFF_1_125 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_125,
    RSCFD_RX_DST_BUFF_1_126 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_126,
    RSCFD_RX_DST_BUFF_1_127 = RSCFD_RX_BUFF | RSCFD_RX_BUFF_1_127
}   rscfd_rx_dst_t;

/*******************************************************************************
 * Common FIFO used for Transmit. Tx FIFO number - 3 per channel
 * (CH0=0-2, CH1=3-5, ... CH5=15-17)
 *******************************************************************************/
typedef enum
{
    RSCFD_TX_FIFO_0_0  = (RSCFD_UNIT_0 << 24) | 0,               /* CH0 */
    RSCFD_TX_FIFO_0_1  = (RSCFD_UNIT_0 << 24) | 1,               /* CH0 */
    RSCFD_TX_FIFO_0_2  = (RSCFD_UNIT_0 << 24) | 2,               /* CH0 */

    RSCFD_TX_FIFO_1_0  = (RSCFD_UNIT_0 << 24) | 3,                   /* CH1 */
    RSCFD_TX_FIFO_1_1  = (RSCFD_UNIT_0 << 24) | 4,               /* CH1 */
    RSCFD_TX_FIFO_1_2  = (RSCFD_UNIT_0 << 24) | 5,               /* CH1 */

    RSCFD_TX_FIFO_2_0  = (RSCFD_UNIT_0 << 24) | 6,                   /* CH2 */
    RSCFD_TX_FIFO_2_1  = (RSCFD_UNIT_0 << 24) | 7,               /* CH2 */
    RSCFD_TX_FIFO_2_2  = (RSCFD_UNIT_0 << 24) | 8,               /* CH2 */

    RSCFD_TX_FIFO_3_0  = (RSCFD_UNIT_0 << 24) | 9,                   /* CH3 */
    RSCFD_TX_FIFO_3_1  = (RSCFD_UNIT_0 << 24) | 10,              /* CH3 */
    RSCFD_TX_FIFO_3_2  = (RSCFD_UNIT_0 << 24) | 11,              /* CH3 */

    RSCFD_TX_FIFO_4_0  = (RSCFD_UNIT_0 << 24) | 12,                  /* CH4 */
    RSCFD_TX_FIFO_4_1  = (RSCFD_UNIT_0 << 24) | 13,              /* CH4 */
    RSCFD_TX_FIFO_4_2  = (RSCFD_UNIT_0 << 24) | 14,              /* CH4 */

    RSCFD_TX_FIFO_5_0  = (RSCFD_UNIT_0 << 24) | 15,                  /* CH5 */
    RSCFD_TX_FIFO_5_1  = (RSCFD_UNIT_0 << 24) | 16,              /* CH5 */
    RSCFD_TX_FIFO_5_2  = (RSCFD_UNIT_0 << 24) | 17,              /* CH5 */

    RSCFD_TX_FIFO_6_0  = (RSCFD_UNIT_0 << 24) | 18,                  /* CH6 */
    RSCFD_TX_FIFO_6_1  = (RSCFD_UNIT_0 << 24) | 19,              /* CH6 */
    RSCFD_TX_FIFO_6_2  = (RSCFD_UNIT_0 << 24) | 20,              /* CH6 */

    RSCFD_TX_FIFO_7_0  = (RSCFD_UNIT_0 << 24) | 21,                  /* CH7 */
    RSCFD_TX_FIFO_7_1  = (RSCFD_UNIT_0 << 24) | 22,              /* CH7 */
    RSCFD_TX_FIFO_7_2  = (RSCFD_UNIT_0 << 24) | 23,              /* CH7 */

    RSCFD_TX_FIFO_8_0  = (RSCFD_UNIT_1 << 24) | 0,                   /* CH8 */
    RSCFD_TX_FIFO_8_1  = (RSCFD_UNIT_1 << 24) | 1,               /* CH8 */
    RSCFD_TX_FIFO_8_2  = (RSCFD_UNIT_1 << 24) | 2,               /* CH8 */

    RSCFD_TX_FIFO_9_0  = (RSCFD_UNIT_1 << 24) | 3,                   /* CH9 */
    RSCFD_TX_FIFO_9_1  = (RSCFD_UNIT_1 << 24) | 4,               /* CH9 */
    RSCFD_TX_FIFO_9_2  = (RSCFD_UNIT_1 << 24) | 5,               /* CH9 */

    RSCFD_TX_FIFO_10_0 = (RSCFD_UNIT_1 << 24) | 6,                   /* CH10 */
    RSCFD_TX_FIFO_10_1 = (RSCFD_UNIT_1 << 24) | 7,               /* CH10 */
    RSCFD_TX_FIFO_10_2 = (RSCFD_UNIT_1 << 24) | 8,               /* CH10 */

    RSCFD_TX_FIFO_11_0 = (RSCFD_UNIT_1 << 24) | 9,                   /* CH11 */
    RSCFD_TX_FIFO_11_1 = (RSCFD_UNIT_1 << 24) | 10,              /* CH11 */
    RSCFD_TX_FIFO_11_2 = (RSCFD_UNIT_1 << 24) | 11,              /* CH11 */

    RSCFD_TX_FIFO_12_0 = (RSCFD_UNIT_1 << 24) | 12,                  /* CH12 */
    RSCFD_TX_FIFO_12_1 = (RSCFD_UNIT_1 << 24) | 13,              /* CH12 */
    RSCFD_TX_FIFO_12_2 = (RSCFD_UNIT_1 << 24) | 14,              /* CH12 */

    RSCFD_TX_FIFO_13_0 = (RSCFD_UNIT_1 << 24) | 15,                  /* CH13 */
    RSCFD_TX_FIFO_13_1 = (RSCFD_UNIT_1 << 24) | 16,              /* CH13 */
    RSCFD_TX_FIFO_13_2 = (RSCFD_UNIT_1 << 24) | 17,              /* CH13 */

    RSCFD_TX_FIFO_14_0 = (RSCFD_UNIT_1 << 24) | 18,                  /* CH14 */
    RSCFD_TX_FIFO_14_1 = (RSCFD_UNIT_1 << 24) | 19,              /* CH14 */
    RSCFD_TX_FIFO_14_2 = (RSCFD_UNIT_1 << 24) | 20,              /* CH14 */

    RSCFD_TX_FIFO_15_0 = (RSCFD_UNIT_1 << 24) | 21,                  /* CH15 */
    RSCFD_TX_FIFO_15_1 = (RSCFD_UNIT_1 << 24) | 22,              /* CH15 */
    RSCFD_TX_FIFO_15_2 = (RSCFD_UNIT_1 << 24) | 23               /* CH15 */
}   rscfd_tx_fifo_t;

/*******************************************************************************
 * Tx Buffer status
 * Register CFDTMSTS bit fields TMTSTS, TMTARM, TMTRM
 * Enumeration matches bit field positions
 *******************************************************************************/
typedef enum
{
    RSCFD_TX_BUFF_STAT_IDLE      = 0x0,
    RSCFD_TX_BUFF_STAT_BUSY      = 0x1,
    RSCFD_TX_BUFF_STAT_BUSY_REQ  = 0x8,
    RSCFD_TX_BUFF_STAT_ABORT_REQ = 0x10
} rscfd_tx_buff_stat_t;

/*******************************************************************************
 * Tx Buffer number - 64 per channel
 *  (CH0=0-64, CH1=64-127, ... )
 *******************************************************************************/
typedef enum
{
    RSCFD_TX_BUFF_0_0   = (RSCFD_UNIT_0 << 24) | 0,               /* CH0 */
    RSCFD_TX_BUFF_0_1   = (RSCFD_UNIT_0 << 24) | 1,               /* CH0 */
    RSCFD_TX_BUFF_0_2   = (RSCFD_UNIT_0 << 24) | 2,               /* CH0 */
    RSCFD_TX_BUFF_0_3   = (RSCFD_UNIT_0 << 24) | 3,               /* CH0 */
    RSCFD_TX_BUFF_0_4   = (RSCFD_UNIT_0 << 24) | 4,               /* CH0 */
    RSCFD_TX_BUFF_0_5   = (RSCFD_UNIT_0 << 24) | 5,               /* CH0 */
    RSCFD_TX_BUFF_0_6   = (RSCFD_UNIT_0 << 24) | 6,               /* CH0 */
    RSCFD_TX_BUFF_0_7   = (RSCFD_UNIT_0 << 24) | 7,               /* CH0 */
    RSCFD_TX_BUFF_0_8   = (RSCFD_UNIT_0 << 24) | 8,               /* CH0 */
    RSCFD_TX_BUFF_0_9   = (RSCFD_UNIT_0 << 24) | 9,               /* CH0 */
    RSCFD_TX_BUFF_0_10  = (RSCFD_UNIT_0 << 24) | 10,              /* CH0 */
    RSCFD_TX_BUFF_0_11  = (RSCFD_UNIT_0 << 24) | 11,              /* CH0 */
    RSCFD_TX_BUFF_0_12  = (RSCFD_UNIT_0 << 24) | 12,              /* CH0 */
    RSCFD_TX_BUFF_0_13  = (RSCFD_UNIT_0 << 24) | 13,              /* CH0 */
    RSCFD_TX_BUFF_0_14  = (RSCFD_UNIT_0 << 24) | 14,              /* CH0 */
    RSCFD_TX_BUFF_0_15  = (RSCFD_UNIT_0 << 24) | 15,              /* CH0 */
    RSCFD_TX_BUFF_0_16  = (RSCFD_UNIT_0 << 24) | 16,              /* CH0 */
    RSCFD_TX_BUFF_0_17  = (RSCFD_UNIT_0 << 24) | 17,              /* CH0 */
    RSCFD_TX_BUFF_0_18  = (RSCFD_UNIT_0 << 24) | 18,              /* CH0 */
    RSCFD_TX_BUFF_0_19  = (RSCFD_UNIT_0 << 24) | 19,              /* CH0 */
    RSCFD_TX_BUFF_0_20  = (RSCFD_UNIT_0 << 24) | 20,              /* CH0 */
    RSCFD_TX_BUFF_0_21  = (RSCFD_UNIT_0 << 24) | 21,              /* CH0 */
    RSCFD_TX_BUFF_0_22  = (RSCFD_UNIT_0 << 24) | 22,              /* CH0 */
    RSCFD_TX_BUFF_0_23  = (RSCFD_UNIT_0 << 24) | 23,              /* CH0 */
    RSCFD_TX_BUFF_0_24  = (RSCFD_UNIT_0 << 24) | 24,              /* CH0 */
    RSCFD_TX_BUFF_0_25  = (RSCFD_UNIT_0 << 24) | 25,              /* CH0 */
    RSCFD_TX_BUFF_0_26  = (RSCFD_UNIT_0 << 24) | 26,              /* CH0 */
    RSCFD_TX_BUFF_0_27  = (RSCFD_UNIT_0 << 24) | 27,              /* CH0 */
    RSCFD_TX_BUFF_0_28  = (RSCFD_UNIT_0 << 24) | 28,              /* CH0 */
    RSCFD_TX_BUFF_0_29  = (RSCFD_UNIT_0 << 24) | 29,              /* CH0 */
    RSCFD_TX_BUFF_0_30  = (RSCFD_UNIT_0 << 24) | 30,              /* CH0 */
    RSCFD_TX_BUFF_0_31  = (RSCFD_UNIT_0 << 24) | 31,              /* CH0 */
    RSCFD_TX_BUFF_0_32  = (RSCFD_UNIT_0 << 24) | 32,              /* CH0 */
    RSCFD_TX_BUFF_0_33  = (RSCFD_UNIT_0 << 24) | 33,              /* CH0 */
    RSCFD_TX_BUFF_0_34  = (RSCFD_UNIT_0 << 24) | 34,              /* CH0 */
    RSCFD_TX_BUFF_0_35  = (RSCFD_UNIT_0 << 24) | 35,              /* CH0 */
    RSCFD_TX_BUFF_0_36  = (RSCFD_UNIT_0 << 24) | 36,              /* CH0 */
    RSCFD_TX_BUFF_0_37  = (RSCFD_UNIT_0 << 24) | 37,              /* CH0 */
    RSCFD_TX_BUFF_0_38  = (RSCFD_UNIT_0 << 24) | 38,              /* CH0 */
    RSCFD_TX_BUFF_0_39  = (RSCFD_UNIT_0 << 24) | 39,              /* CH0 */
    RSCFD_TX_BUFF_0_40  = (RSCFD_UNIT_0 << 24) | 40,              /* CH0 */
    RSCFD_TX_BUFF_0_41  = (RSCFD_UNIT_0 << 24) | 41,              /* CH0 */
    RSCFD_TX_BUFF_0_42  = (RSCFD_UNIT_0 << 24) | 42,              /* CH0 */
    RSCFD_TX_BUFF_0_43  = (RSCFD_UNIT_0 << 24) | 43,              /* CH0 */
    RSCFD_TX_BUFF_0_44  = (RSCFD_UNIT_0 << 24) | 44,              /* CH0 */
    RSCFD_TX_BUFF_0_45  = (RSCFD_UNIT_0 << 24) | 45,              /* CH0 */
    RSCFD_TX_BUFF_0_46  = (RSCFD_UNIT_0 << 24) | 46,              /* CH0 */
    RSCFD_TX_BUFF_0_47  = (RSCFD_UNIT_0 << 24) | 47,              /* CH0 */
    RSCFD_TX_BUFF_0_48  = (RSCFD_UNIT_0 << 24) | 48,              /* CH0 */
    RSCFD_TX_BUFF_0_49  = (RSCFD_UNIT_0 << 24) | 49,              /* CH0 */
    RSCFD_TX_BUFF_0_50  = (RSCFD_UNIT_0 << 24) | 50,              /* CH0 */
    RSCFD_TX_BUFF_0_51  = (RSCFD_UNIT_0 << 24) | 51,              /* CH0 */
    RSCFD_TX_BUFF_0_52  = (RSCFD_UNIT_0 << 24) | 52,              /* CH0 */
    RSCFD_TX_BUFF_0_53  = (RSCFD_UNIT_0 << 24) | 53,              /* CH0 */
    RSCFD_TX_BUFF_0_54  = (RSCFD_UNIT_0 << 24) | 54,              /* CH0 */
    RSCFD_TX_BUFF_0_55  = (RSCFD_UNIT_0 << 24) | 55,              /* CH0 */
    RSCFD_TX_BUFF_0_56  = (RSCFD_UNIT_0 << 24) | 56,              /* CH0 */
    RSCFD_TX_BUFF_0_57  = (RSCFD_UNIT_0 << 24) | 57,              /* CH0 */
    RSCFD_TX_BUFF_0_58  = (RSCFD_UNIT_0 << 24) | 58,              /* CH0 */
    RSCFD_TX_BUFF_0_59  = (RSCFD_UNIT_0 << 24) | 59,              /* CH0 */
    RSCFD_TX_BUFF_0_60  = (RSCFD_UNIT_0 << 24) | 60,              /* CH0 */
    RSCFD_TX_BUFF_0_61  = (RSCFD_UNIT_0 << 24) | 61,              /* CH0 */
    RSCFD_TX_BUFF_0_62  = (RSCFD_UNIT_0 << 24) | 62,              /* CH0 */
    RSCFD_TX_BUFF_0_63  = (RSCFD_UNIT_0 << 24) | 63,              /* CH0 */

    RSCFD_TX_BUFF_1_0   = (RSCFD_UNIT_0 << 24) | 64,              /* CH1 */
    RSCFD_TX_BUFF_1_1   = (RSCFD_UNIT_0 << 24) | 65,              /* CH1 */
    RSCFD_TX_BUFF_1_2   = (RSCFD_UNIT_0 << 24) | 66,              /* CH1 */
    RSCFD_TX_BUFF_1_3   = (RSCFD_UNIT_0 << 24) | 67,              /* CH1 */
    RSCFD_TX_BUFF_1_4   = (RSCFD_UNIT_0 << 24) | 68,              /* CH1 */
    RSCFD_TX_BUFF_1_5   = (RSCFD_UNIT_0 << 24) | 69,              /* CH1 */
    RSCFD_TX_BUFF_1_6   = (RSCFD_UNIT_0 << 24) | 70,              /* CH1 */
    RSCFD_TX_BUFF_1_7   = (RSCFD_UNIT_0 << 24) | 71,              /* CH1 */
    RSCFD_TX_BUFF_1_8   = (RSCFD_UNIT_0 << 24) | 72,              /* CH1 */
    RSCFD_TX_BUFF_1_9   = (RSCFD_UNIT_0 << 24) | 73,              /* CH1 */
    RSCFD_TX_BUFF_1_10  = (RSCFD_UNIT_0 << 24) | 74,              /* CH1 */
    RSCFD_TX_BUFF_1_11  = (RSCFD_UNIT_0 << 24) | 75,              /* CH1 */
    RSCFD_TX_BUFF_1_12  = (RSCFD_UNIT_0 << 24) | 76,              /* CH1 */
    RSCFD_TX_BUFF_1_13  = (RSCFD_UNIT_0 << 24) | 77,              /* CH1 */
    RSCFD_TX_BUFF_1_14  = (RSCFD_UNIT_0 << 24) | 78,              /* CH1 */
    RSCFD_TX_BUFF_1_15  = (RSCFD_UNIT_0 << 24) | 79,              /* CH1 */
    RSCFD_TX_BUFF_1_16  = (RSCFD_UNIT_0 << 24) | 80,              /* CH1 */
    RSCFD_TX_BUFF_1_17  = (RSCFD_UNIT_0 << 24) | 81,              /* CH1 */
    RSCFD_TX_BUFF_1_18  = (RSCFD_UNIT_0 << 24) | 82,              /* CH1 */
    RSCFD_TX_BUFF_1_19  = (RSCFD_UNIT_0 << 24) | 83,              /* CH1 */
    RSCFD_TX_BUFF_1_20  = (RSCFD_UNIT_0 << 24) | 84,              /* CH1 */
    RSCFD_TX_BUFF_1_21  = (RSCFD_UNIT_0 << 24) | 85,              /* CH1 */
    RSCFD_TX_BUFF_1_22  = (RSCFD_UNIT_0 << 24) | 86,              /* CH1 */
    RSCFD_TX_BUFF_1_23  = (RSCFD_UNIT_0 << 24) | 87,              /* CH1 */
    RSCFD_TX_BUFF_1_24  = (RSCFD_UNIT_0 << 24) | 88,              /* CH1 */
    RSCFD_TX_BUFF_1_25  = (RSCFD_UNIT_0 << 24) | 89,              /* CH1 */
    RSCFD_TX_BUFF_1_26  = (RSCFD_UNIT_0 << 24) | 90,              /* CH1 */
    RSCFD_TX_BUFF_1_27  = (RSCFD_UNIT_0 << 24) | 91,              /* CH1 */
    RSCFD_TX_BUFF_1_28  = (RSCFD_UNIT_0 << 24) | 92,              /* CH1 */
    RSCFD_TX_BUFF_1_29  = (RSCFD_UNIT_0 << 24) | 93,              /* CH1 */
    RSCFD_TX_BUFF_1_30  = (RSCFD_UNIT_0 << 24) | 94,              /* CH1 */
    RSCFD_TX_BUFF_1_31  = (RSCFD_UNIT_0 << 24) | 95,              /* CH1 */
    RSCFD_TX_BUFF_1_32  = (RSCFD_UNIT_0 << 24) | 96,              /* CH1 */
    RSCFD_TX_BUFF_1_33  = (RSCFD_UNIT_0 << 24) | 97,              /* CH1 */
    RSCFD_TX_BUFF_1_34  = (RSCFD_UNIT_0 << 24) | 98,              /* CH1 */
    RSCFD_TX_BUFF_1_35  = (RSCFD_UNIT_0 << 24) | 99,              /* CH1 */
    RSCFD_TX_BUFF_1_36  = (RSCFD_UNIT_0 << 24) | 100,             /* CH1 */
    RSCFD_TX_BUFF_1_37  = (RSCFD_UNIT_0 << 24) | 101,             /* CH1 */
    RSCFD_TX_BUFF_1_38  = (RSCFD_UNIT_0 << 24) | 102,             /* CH1 */
    RSCFD_TX_BUFF_1_39  = (RSCFD_UNIT_0 << 24) | 103,             /* CH1 */
    RSCFD_TX_BUFF_1_40  = (RSCFD_UNIT_0 << 24) | 104,             /* CH1 */
    RSCFD_TX_BUFF_1_41  = (RSCFD_UNIT_0 << 24) | 105,             /* CH1 */
    RSCFD_TX_BUFF_1_42  = (RSCFD_UNIT_0 << 24) | 106,             /* CH1 */
    RSCFD_TX_BUFF_1_43  = (RSCFD_UNIT_0 << 24) | 107,             /* CH1 */
    RSCFD_TX_BUFF_1_44  = (RSCFD_UNIT_0 << 24) | 108,             /* CH1 */
    RSCFD_TX_BUFF_1_45  = (RSCFD_UNIT_0 << 24) | 109,             /* CH1 */
    RSCFD_TX_BUFF_1_46  = (RSCFD_UNIT_0 << 24) | 110,             /* CH1 */
    RSCFD_TX_BUFF_1_47  = (RSCFD_UNIT_0 << 24) | 111,             /* CH1 */
    RSCFD_TX_BUFF_1_48  = (RSCFD_UNIT_0 << 24) | 112,             /* CH1 */
    RSCFD_TX_BUFF_1_49  = (RSCFD_UNIT_0 << 24) | 113,             /* CH1 */
    RSCFD_TX_BUFF_1_50  = (RSCFD_UNIT_0 << 24) | 114,             /* CH1 */
    RSCFD_TX_BUFF_1_51  = (RSCFD_UNIT_0 << 24) | 115,             /* CH1 */
    RSCFD_TX_BUFF_1_52  = (RSCFD_UNIT_0 << 24) | 116,             /* CH1 */
    RSCFD_TX_BUFF_1_53  = (RSCFD_UNIT_0 << 24) | 117,             /* CH1 */
    RSCFD_TX_BUFF_1_54  = (RSCFD_UNIT_0 << 24) | 118,             /* CH1 */
    RSCFD_TX_BUFF_1_55  = (RSCFD_UNIT_0 << 24) | 119,             /* CH1 */
    RSCFD_TX_BUFF_1_56  = (RSCFD_UNIT_0 << 24) | 120,             /* CH1 */
    RSCFD_TX_BUFF_1_57  = (RSCFD_UNIT_0 << 24) | 121,             /* CH1 */
    RSCFD_TX_BUFF_1_58  = (RSCFD_UNIT_0 << 24) | 122,             /* CH1 */
    RSCFD_TX_BUFF_1_59  = (RSCFD_UNIT_0 << 24) | 123,             /* CH1 */
    RSCFD_TX_BUFF_1_60  = (RSCFD_UNIT_0 << 24) | 124,             /* CH1 */
    RSCFD_TX_BUFF_1_61  = (RSCFD_UNIT_0 << 24) | 125,             /* CH1 */
    RSCFD_TX_BUFF_1_62  = (RSCFD_UNIT_0 << 24) | 126,             /* CH1 */
    RSCFD_TX_BUFF_1_63  = (RSCFD_UNIT_0 << 24) | 127,             /* CH1 */

    RSCFD_TX_BUFF_2_0   = (RSCFD_UNIT_0 << 24) | 128,             /* CH2 */
    RSCFD_TX_BUFF_2_1   = (RSCFD_UNIT_0 << 24) | 129,             /* CH2 */
    RSCFD_TX_BUFF_2_2   = (RSCFD_UNIT_0 << 24) | 130,             /* CH2 */
    RSCFD_TX_BUFF_2_3   = (RSCFD_UNIT_0 << 24) | 131,             /* CH2 */
    RSCFD_TX_BUFF_2_4   = (RSCFD_UNIT_0 << 24) | 132,             /* CH2 */
    RSCFD_TX_BUFF_2_5   = (RSCFD_UNIT_0 << 24) | 133,             /* CH2 */
    RSCFD_TX_BUFF_2_6   = (RSCFD_UNIT_0 << 24) | 134,             /* CH2 */
    RSCFD_TX_BUFF_2_7   = (RSCFD_UNIT_0 << 24) | 135,             /* CH2 */
    RSCFD_TX_BUFF_2_8   = (RSCFD_UNIT_0 << 24) | 136,             /* CH2 */
    RSCFD_TX_BUFF_2_9   = (RSCFD_UNIT_0 << 24) | 137,             /* CH2 */
    RSCFD_TX_BUFF_2_10  = (RSCFD_UNIT_0 << 24) | 138,             /* CH2 */
    RSCFD_TX_BUFF_2_11  = (RSCFD_UNIT_0 << 24) | 139,             /* CH2 */
    RSCFD_TX_BUFF_2_12  = (RSCFD_UNIT_0 << 24) | 140,             /* CH2 */
    RSCFD_TX_BUFF_2_13  = (RSCFD_UNIT_0 << 24) | 141,             /* CH2 */
    RSCFD_TX_BUFF_2_14  = (RSCFD_UNIT_0 << 24) | 142,             /* CH2 */
    RSCFD_TX_BUFF_2_15  = (RSCFD_UNIT_0 << 24) | 143,             /* CH2 */
    RSCFD_TX_BUFF_2_16  = (RSCFD_UNIT_0 << 24) | 144,             /* CH2 */
    RSCFD_TX_BUFF_2_17  = (RSCFD_UNIT_0 << 24) | 145,             /* CH2 */
    RSCFD_TX_BUFF_2_18  = (RSCFD_UNIT_0 << 24) | 146,             /* CH2 */
    RSCFD_TX_BUFF_2_19  = (RSCFD_UNIT_0 << 24) | 147,             /* CH2 */
    RSCFD_TX_BUFF_2_20  = (RSCFD_UNIT_0 << 24) | 148,             /* CH2 */
    RSCFD_TX_BUFF_2_21  = (RSCFD_UNIT_0 << 24) | 149,             /* CH2 */
    RSCFD_TX_BUFF_2_22  = (RSCFD_UNIT_0 << 24) | 150,             /* CH2 */
    RSCFD_TX_BUFF_2_23  = (RSCFD_UNIT_0 << 24) | 151,             /* CH2 */
    RSCFD_TX_BUFF_2_24  = (RSCFD_UNIT_0 << 24) | 152,             /* CH2 */
    RSCFD_TX_BUFF_2_25  = (RSCFD_UNIT_0 << 24) | 153,             /* CH2 */
    RSCFD_TX_BUFF_2_26  = (RSCFD_UNIT_0 << 24) | 154,             /* CH2 */
    RSCFD_TX_BUFF_2_27  = (RSCFD_UNIT_0 << 24) | 155,             /* CH2 */
    RSCFD_TX_BUFF_2_28  = (RSCFD_UNIT_0 << 24) | 156,             /* CH2 */
    RSCFD_TX_BUFF_2_29  = (RSCFD_UNIT_0 << 24) | 157,             /* CH2 */
    RSCFD_TX_BUFF_2_30  = (RSCFD_UNIT_0 << 24) | 158,             /* CH2 */
    RSCFD_TX_BUFF_2_31  = (RSCFD_UNIT_0 << 24) | 159,             /* CH2 */
    RSCFD_TX_BUFF_2_32  = (RSCFD_UNIT_0 << 24) | 160,             /* CH2 */
    RSCFD_TX_BUFF_2_33  = (RSCFD_UNIT_0 << 24) | 161,             /* CH2 */
    RSCFD_TX_BUFF_2_34  = (RSCFD_UNIT_0 << 24) | 162,             /* CH2 */
    RSCFD_TX_BUFF_2_35  = (RSCFD_UNIT_0 << 24) | 163,             /* CH2 */
    RSCFD_TX_BUFF_2_36  = (RSCFD_UNIT_0 << 24) | 164,             /* CH2 */
    RSCFD_TX_BUFF_2_37  = (RSCFD_UNIT_0 << 24) | 165,             /* CH2 */
    RSCFD_TX_BUFF_2_38  = (RSCFD_UNIT_0 << 24) | 166,             /* CH2 */
    RSCFD_TX_BUFF_2_39  = (RSCFD_UNIT_0 << 24) | 167,             /* CH2 */
    RSCFD_TX_BUFF_2_40  = (RSCFD_UNIT_0 << 24) | 168,             /* CH2 */
    RSCFD_TX_BUFF_2_41  = (RSCFD_UNIT_0 << 24) | 169,             /* CH2 */
    RSCFD_TX_BUFF_2_42  = (RSCFD_UNIT_0 << 24) | 170,             /* CH2 */
    RSCFD_TX_BUFF_2_43  = (RSCFD_UNIT_0 << 24) | 171,             /* CH2 */
    RSCFD_TX_BUFF_2_44  = (RSCFD_UNIT_0 << 24) | 172,             /* CH2 */
    RSCFD_TX_BUFF_2_45  = (RSCFD_UNIT_0 << 24) | 173,             /* CH2 */
    RSCFD_TX_BUFF_2_46  = (RSCFD_UNIT_0 << 24) | 174,             /* CH2 */
    RSCFD_TX_BUFF_2_47  = (RSCFD_UNIT_0 << 24) | 175,             /* CH2 */
    RSCFD_TX_BUFF_2_48  = (RSCFD_UNIT_0 << 24) | 176,             /* CH2 */
    RSCFD_TX_BUFF_2_49  = (RSCFD_UNIT_0 << 24) | 177,             /* CH2 */
    RSCFD_TX_BUFF_2_50  = (RSCFD_UNIT_0 << 24) | 178,             /* CH2 */
    RSCFD_TX_BUFF_2_51  = (RSCFD_UNIT_0 << 24) | 179,             /* CH2 */
    RSCFD_TX_BUFF_2_52  = (RSCFD_UNIT_0 << 24) | 180,             /* CH2 */
    RSCFD_TX_BUFF_2_53  = (RSCFD_UNIT_0 << 24) | 181,             /* CH2 */
    RSCFD_TX_BUFF_2_54  = (RSCFD_UNIT_0 << 24) | 182,             /* CH2 */
    RSCFD_TX_BUFF_2_55  = (RSCFD_UNIT_0 << 24) | 183,             /* CH2 */
    RSCFD_TX_BUFF_2_56  = (RSCFD_UNIT_0 << 24) | 184,             /* CH2 */
    RSCFD_TX_BUFF_2_57  = (RSCFD_UNIT_0 << 24) | 185,             /* CH2 */
    RSCFD_TX_BUFF_2_58  = (RSCFD_UNIT_0 << 24) | 186,             /* CH2 */
    RSCFD_TX_BUFF_2_59  = (RSCFD_UNIT_0 << 24) | 187,             /* CH2 */
    RSCFD_TX_BUFF_2_60  = (RSCFD_UNIT_0 << 24) | 188,             /* CH2 */
    RSCFD_TX_BUFF_2_61  = (RSCFD_UNIT_0 << 24) | 189,             /* CH2 */
    RSCFD_TX_BUFF_2_62  = (RSCFD_UNIT_0 << 24) | 190,             /* CH2 */
    RSCFD_TX_BUFF_2_63  = (RSCFD_UNIT_0 << 24) | 191,             /* CH2 */

    RSCFD_TX_BUFF_3_0   = (RSCFD_UNIT_0 << 24) | 192,             /* CH3 */
    RSCFD_TX_BUFF_3_1   = (RSCFD_UNIT_0 << 24) | 193,             /* CH3 */
    RSCFD_TX_BUFF_3_2   = (RSCFD_UNIT_0 << 24) | 194,             /* CH3 */
    RSCFD_TX_BUFF_3_3   = (RSCFD_UNIT_0 << 24) | 195,             /* CH3 */
    RSCFD_TX_BUFF_3_4   = (RSCFD_UNIT_0 << 24) | 196,             /* CH3 */
    RSCFD_TX_BUFF_3_5   = (RSCFD_UNIT_0 << 24) | 197,             /* CH3 */
    RSCFD_TX_BUFF_3_6   = (RSCFD_UNIT_0 << 24) | 198,             /* CH3 */
    RSCFD_TX_BUFF_3_7   = (RSCFD_UNIT_0 << 24) | 199,             /* CH3 */
    RSCFD_TX_BUFF_3_8   = (RSCFD_UNIT_0 << 24) | 200,             /* CH3 */
    RSCFD_TX_BUFF_3_9   = (RSCFD_UNIT_0 << 24) | 201,             /* CH3 */
    RSCFD_TX_BUFF_3_10  = (RSCFD_UNIT_0 << 24) | 202,             /* CH3 */
    RSCFD_TX_BUFF_3_11  = (RSCFD_UNIT_0 << 24) | 203,             /* CH3 */
    RSCFD_TX_BUFF_3_12  = (RSCFD_UNIT_0 << 24) | 204,             /* CH3 */
    RSCFD_TX_BUFF_3_13  = (RSCFD_UNIT_0 << 24) | 205,             /* CH3 */
    RSCFD_TX_BUFF_3_14  = (RSCFD_UNIT_0 << 24) | 206,             /* CH3 */
    RSCFD_TX_BUFF_3_15  = (RSCFD_UNIT_0 << 24) | 207,             /* CH3 */
    RSCFD_TX_BUFF_3_16  = (RSCFD_UNIT_0 << 24) | 208,             /* CH3 */
    RSCFD_TX_BUFF_3_17  = (RSCFD_UNIT_0 << 24) | 209,             /* CH3 */
    RSCFD_TX_BUFF_3_18  = (RSCFD_UNIT_0 << 24) | 210,             /* CH3 */
    RSCFD_TX_BUFF_3_19  = (RSCFD_UNIT_0 << 24) | 211,             /* CH3 */
    RSCFD_TX_BUFF_3_20  = (RSCFD_UNIT_0 << 24) | 212,             /* CH3 */
    RSCFD_TX_BUFF_3_21  = (RSCFD_UNIT_0 << 24) | 213,             /* CH3 */
    RSCFD_TX_BUFF_3_22  = (RSCFD_UNIT_0 << 24) | 214,             /* CH3 */
    RSCFD_TX_BUFF_3_23  = (RSCFD_UNIT_0 << 24) | 215,             /* CH3 */
    RSCFD_TX_BUFF_3_24  = (RSCFD_UNIT_0 << 24) | 216,             /* CH3 */
    RSCFD_TX_BUFF_3_25  = (RSCFD_UNIT_0 << 24) | 217,             /* CH3 */
    RSCFD_TX_BUFF_3_26  = (RSCFD_UNIT_0 << 24) | 218,             /* CH3 */
    RSCFD_TX_BUFF_3_27  = (RSCFD_UNIT_0 << 24) | 219,             /* CH3 */
    RSCFD_TX_BUFF_3_28  = (RSCFD_UNIT_0 << 24) | 220,             /* CH3 */
    RSCFD_TX_BUFF_3_29  = (RSCFD_UNIT_0 << 24) | 221,             /* CH3 */
    RSCFD_TX_BUFF_3_30  = (RSCFD_UNIT_0 << 24) | 222,             /* CH3 */
    RSCFD_TX_BUFF_3_31  = (RSCFD_UNIT_0 << 24) | 223,             /* CH3 */
    RSCFD_TX_BUFF_3_32  = (RSCFD_UNIT_0 << 24) | 224,             /* CH3 */
    RSCFD_TX_BUFF_3_33  = (RSCFD_UNIT_0 << 24) | 225,             /* CH3 */
    RSCFD_TX_BUFF_3_34  = (RSCFD_UNIT_0 << 24) | 226,             /* CH3 */
    RSCFD_TX_BUFF_3_35  = (RSCFD_UNIT_0 << 24) | 227,             /* CH3 */
    RSCFD_TX_BUFF_3_36  = (RSCFD_UNIT_0 << 24) | 228,             /* CH3 */
    RSCFD_TX_BUFF_3_37  = (RSCFD_UNIT_0 << 24) | 229,             /* CH3 */
    RSCFD_TX_BUFF_3_38  = (RSCFD_UNIT_0 << 24) | 230,             /* CH3 */
    RSCFD_TX_BUFF_3_39  = (RSCFD_UNIT_0 << 24) | 231,             /* CH3 */
    RSCFD_TX_BUFF_3_40  = (RSCFD_UNIT_0 << 24) | 232,             /* CH3 */
    RSCFD_TX_BUFF_3_41  = (RSCFD_UNIT_0 << 24) | 233,             /* CH3 */
    RSCFD_TX_BUFF_3_42  = (RSCFD_UNIT_0 << 24) | 234,             /* CH3 */
    RSCFD_TX_BUFF_3_43  = (RSCFD_UNIT_0 << 24) | 235,             /* CH3 */
    RSCFD_TX_BUFF_3_44  = (RSCFD_UNIT_0 << 24) | 236,             /* CH3 */
    RSCFD_TX_BUFF_3_45  = (RSCFD_UNIT_0 << 24) | 237,             /* CH3 */
    RSCFD_TX_BUFF_3_46  = (RSCFD_UNIT_0 << 24) | 238,             /* CH3 */
    RSCFD_TX_BUFF_3_47  = (RSCFD_UNIT_0 << 24) | 239,             /* CH3 */
    RSCFD_TX_BUFF_3_48  = (RSCFD_UNIT_0 << 24) | 240,             /* CH3 */
    RSCFD_TX_BUFF_3_49  = (RSCFD_UNIT_0 << 24) | 241,             /* CH3 */
    RSCFD_TX_BUFF_3_50  = (RSCFD_UNIT_0 << 24) | 242,             /* CH3 */
    RSCFD_TX_BUFF_3_51  = (RSCFD_UNIT_0 << 24) | 243,             /* CH3 */
    RSCFD_TX_BUFF_3_52  = (RSCFD_UNIT_0 << 24) | 244,             /* CH3 */
    RSCFD_TX_BUFF_3_53  = (RSCFD_UNIT_0 << 24) | 245,             /* CH3 */
    RSCFD_TX_BUFF_3_54  = (RSCFD_UNIT_0 << 24) | 246,             /* CH3 */
    RSCFD_TX_BUFF_3_55  = (RSCFD_UNIT_0 << 24) | 247,             /* CH3 */
    RSCFD_TX_BUFF_3_56  = (RSCFD_UNIT_0 << 24) | 248,             /* CH3 */
    RSCFD_TX_BUFF_3_57  = (RSCFD_UNIT_0 << 24) | 249,             /* CH3 */
    RSCFD_TX_BUFF_3_58  = (RSCFD_UNIT_0 << 24) | 250,             /* CH3 */
    RSCFD_TX_BUFF_3_59  = (RSCFD_UNIT_0 << 24) | 251,             /* CH3 */
    RSCFD_TX_BUFF_3_60  = (RSCFD_UNIT_0 << 24) | 252,             /* CH3 */
    RSCFD_TX_BUFF_3_61  = (RSCFD_UNIT_0 << 24) | 253,             /* CH3 */
    RSCFD_TX_BUFF_3_62  = (RSCFD_UNIT_0 << 24) | 254,             /* CH3 */
    RSCFD_TX_BUFF_3_63  = (RSCFD_UNIT_0 << 24) | 255,             /* CH3 */

    RSCFD_TX_BUFF_4_0   = (RSCFD_UNIT_0 << 24) | 256,             /* CH4 */
    RSCFD_TX_BUFF_4_1   = (RSCFD_UNIT_0 << 24) | 257,             /* CH4 */
    RSCFD_TX_BUFF_4_2   = (RSCFD_UNIT_0 << 24) | 258,             /* CH4 */
    RSCFD_TX_BUFF_4_3   = (RSCFD_UNIT_0 << 24) | 259,             /* CH4 */
    RSCFD_TX_BUFF_4_4   = (RSCFD_UNIT_0 << 24) | 260,             /* CH4 */
    RSCFD_TX_BUFF_4_5   = (RSCFD_UNIT_0 << 24) | 261,             /* CH4 */
    RSCFD_TX_BUFF_4_6   = (RSCFD_UNIT_0 << 24) | 262,             /* CH4 */
    RSCFD_TX_BUFF_4_7   = (RSCFD_UNIT_0 << 24) | 263,             /* CH4 */
    RSCFD_TX_BUFF_4_8   = (RSCFD_UNIT_0 << 24) | 264,             /* CH4 */
    RSCFD_TX_BUFF_4_9   = (RSCFD_UNIT_0 << 24) | 265,             /* CH4 */
    RSCFD_TX_BUFF_4_10  = (RSCFD_UNIT_0 << 24) | 266,             /* CH4 */
    RSCFD_TX_BUFF_4_11  = (RSCFD_UNIT_0 << 24) | 267,             /* CH4 */
    RSCFD_TX_BUFF_4_12  = (RSCFD_UNIT_0 << 24) | 268,             /* CH4 */
    RSCFD_TX_BUFF_4_13  = (RSCFD_UNIT_0 << 24) | 269,             /* CH4 */
    RSCFD_TX_BUFF_4_14  = (RSCFD_UNIT_0 << 24) | 270,             /* CH4 */
    RSCFD_TX_BUFF_4_15  = (RSCFD_UNIT_0 << 24) | 271,             /* CH4 */
    RSCFD_TX_BUFF_4_16  = (RSCFD_UNIT_0 << 24) | 272,             /* CH4 */
    RSCFD_TX_BUFF_4_17  = (RSCFD_UNIT_0 << 24) | 273,             /* CH4 */
    RSCFD_TX_BUFF_4_18  = (RSCFD_UNIT_0 << 24) | 274,             /* CH4 */
    RSCFD_TX_BUFF_4_19  = (RSCFD_UNIT_0 << 24) | 275,             /* CH4 */
    RSCFD_TX_BUFF_4_20  = (RSCFD_UNIT_0 << 24) | 276,             /* CH4 */
    RSCFD_TX_BUFF_4_21  = (RSCFD_UNIT_0 << 24) | 277,             /* CH4 */
    RSCFD_TX_BUFF_4_22  = (RSCFD_UNIT_0 << 24) | 278,             /* CH4 */
    RSCFD_TX_BUFF_4_23  = (RSCFD_UNIT_0 << 24) | 279,             /* CH4 */
    RSCFD_TX_BUFF_4_24  = (RSCFD_UNIT_0 << 24) | 280,             /* CH4 */
    RSCFD_TX_BUFF_4_25  = (RSCFD_UNIT_0 << 24) | 281,             /* CH4 */
    RSCFD_TX_BUFF_4_26  = (RSCFD_UNIT_0 << 24) | 282,             /* CH4 */
    RSCFD_TX_BUFF_4_27  = (RSCFD_UNIT_0 << 24) | 283,             /* CH4 */
    RSCFD_TX_BUFF_4_28  = (RSCFD_UNIT_0 << 24) | 284,             /* CH4 */
    RSCFD_TX_BUFF_4_29  = (RSCFD_UNIT_0 << 24) | 285,             /* CH4 */
    RSCFD_TX_BUFF_4_30  = (RSCFD_UNIT_0 << 24) | 286,             /* CH4 */
    RSCFD_TX_BUFF_4_31  = (RSCFD_UNIT_0 << 24) | 287,             /* CH4 */
    RSCFD_TX_BUFF_4_32  = (RSCFD_UNIT_0 << 24) | 288,             /* CH4 */
    RSCFD_TX_BUFF_4_33  = (RSCFD_UNIT_0 << 24) | 289,             /* CH4 */
    RSCFD_TX_BUFF_4_34  = (RSCFD_UNIT_0 << 24) | 290,             /* CH4 */
    RSCFD_TX_BUFF_4_35  = (RSCFD_UNIT_0 << 24) | 291,             /* CH4 */
    RSCFD_TX_BUFF_4_36  = (RSCFD_UNIT_0 << 24) | 292,             /* CH4 */
    RSCFD_TX_BUFF_4_37  = (RSCFD_UNIT_0 << 24) | 293,             /* CH4 */
    RSCFD_TX_BUFF_4_38  = (RSCFD_UNIT_0 << 24) | 294,             /* CH4 */
    RSCFD_TX_BUFF_4_39  = (RSCFD_UNIT_0 << 24) | 295,             /* CH4 */
    RSCFD_TX_BUFF_4_40  = (RSCFD_UNIT_0 << 24) | 296,             /* CH4 */
    RSCFD_TX_BUFF_4_41  = (RSCFD_UNIT_0 << 24) | 297,             /* CH4 */
    RSCFD_TX_BUFF_4_42  = (RSCFD_UNIT_0 << 24) | 298,             /* CH4 */
    RSCFD_TX_BUFF_4_43  = (RSCFD_UNIT_0 << 24) | 299,             /* CH4 */
    RSCFD_TX_BUFF_4_44  = (RSCFD_UNIT_0 << 24) | 300,             /* CH4 */
    RSCFD_TX_BUFF_4_45  = (RSCFD_UNIT_0 << 24) | 301,             /* CH4 */
    RSCFD_TX_BUFF_4_46  = (RSCFD_UNIT_0 << 24) | 302,             /* CH4 */
    RSCFD_TX_BUFF_4_47  = (RSCFD_UNIT_0 << 24) | 303,             /* CH4 */
    RSCFD_TX_BUFF_4_48  = (RSCFD_UNIT_0 << 24) | 304,             /* CH4 */
    RSCFD_TX_BUFF_4_49  = (RSCFD_UNIT_0 << 24) | 305,             /* CH4 */
    RSCFD_TX_BUFF_4_50  = (RSCFD_UNIT_0 << 24) | 306,             /* CH4 */
    RSCFD_TX_BUFF_4_51  = (RSCFD_UNIT_0 << 24) | 307,             /* CH4 */
    RSCFD_TX_BUFF_4_52  = (RSCFD_UNIT_0 << 24) | 308,             /* CH4 */
    RSCFD_TX_BUFF_4_53  = (RSCFD_UNIT_0 << 24) | 309,             /* CH4 */
    RSCFD_TX_BUFF_4_54  = (RSCFD_UNIT_0 << 24) | 310,             /* CH4 */
    RSCFD_TX_BUFF_4_55  = (RSCFD_UNIT_0 << 24) | 311,             /* CH4 */
    RSCFD_TX_BUFF_4_56  = (RSCFD_UNIT_0 << 24) | 312,             /* CH4 */
    RSCFD_TX_BUFF_4_57  = (RSCFD_UNIT_0 << 24) | 313,             /* CH4 */
    RSCFD_TX_BUFF_4_58  = (RSCFD_UNIT_0 << 24) | 314,             /* CH4 */
    RSCFD_TX_BUFF_4_59  = (RSCFD_UNIT_0 << 24) | 315,             /* CH4 */
    RSCFD_TX_BUFF_4_60  = (RSCFD_UNIT_0 << 24) | 316,             /* CH4 */
    RSCFD_TX_BUFF_4_61  = (RSCFD_UNIT_0 << 24) | 317,             /* CH4 */
    RSCFD_TX_BUFF_4_62  = (RSCFD_UNIT_0 << 24) | 318,             /* CH4 */
    RSCFD_TX_BUFF_4_63  = (RSCFD_UNIT_0 << 24) | 319,             /* CH4 */

    RSCFD_TX_BUFF_5_0   = (RSCFD_UNIT_0 << 24) | 320,             /* CH5 */
    RSCFD_TX_BUFF_5_1   = (RSCFD_UNIT_0 << 24) | 321,             /* CH5 */
    RSCFD_TX_BUFF_5_2   = (RSCFD_UNIT_0 << 24) | 322,             /* CH5 */
    RSCFD_TX_BUFF_5_3   = (RSCFD_UNIT_0 << 24) | 323,             /* CH5 */
    RSCFD_TX_BUFF_5_4   = (RSCFD_UNIT_0 << 24) | 324,             /* CH5 */
    RSCFD_TX_BUFF_5_5   = (RSCFD_UNIT_0 << 24) | 325,             /* CH5 */
    RSCFD_TX_BUFF_5_6   = (RSCFD_UNIT_0 << 24) | 326,             /* CH5 */
    RSCFD_TX_BUFF_5_7   = (RSCFD_UNIT_0 << 24) | 327,             /* CH5 */
    RSCFD_TX_BUFF_5_8   = (RSCFD_UNIT_0 << 24) | 328,             /* CH5 */
    RSCFD_TX_BUFF_5_9   = (RSCFD_UNIT_0 << 24) | 329,             /* CH5 */
    RSCFD_TX_BUFF_5_10  = (RSCFD_UNIT_0 << 24) | 330,             /* CH5 */
    RSCFD_TX_BUFF_5_11  = (RSCFD_UNIT_0 << 24) | 331,             /* CH5 */
    RSCFD_TX_BUFF_5_12  = (RSCFD_UNIT_0 << 24) | 332,             /* CH5 */
    RSCFD_TX_BUFF_5_13  = (RSCFD_UNIT_0 << 24) | 333,             /* CH5 */
    RSCFD_TX_BUFF_5_14  = (RSCFD_UNIT_0 << 24) | 334,             /* CH5 */
    RSCFD_TX_BUFF_5_15  = (RSCFD_UNIT_0 << 24) | 335,             /* CH5 */
    RSCFD_TX_BUFF_5_16  = (RSCFD_UNIT_0 << 24) | 336,             /* CH5 */
    RSCFD_TX_BUFF_5_17  = (RSCFD_UNIT_0 << 24) | 337,             /* CH5 */
    RSCFD_TX_BUFF_5_18  = (RSCFD_UNIT_0 << 24) | 338,             /* CH5 */
    RSCFD_TX_BUFF_5_19  = (RSCFD_UNIT_0 << 24) | 339,             /* CH5 */
    RSCFD_TX_BUFF_5_20  = (RSCFD_UNIT_0 << 24) | 340,             /* CH5 */
    RSCFD_TX_BUFF_5_21  = (RSCFD_UNIT_0 << 24) | 341,             /* CH5 */
    RSCFD_TX_BUFF_5_22  = (RSCFD_UNIT_0 << 24) | 342,             /* CH5 */
    RSCFD_TX_BUFF_5_23  = (RSCFD_UNIT_0 << 24) | 343,             /* CH5 */
    RSCFD_TX_BUFF_5_24  = (RSCFD_UNIT_0 << 24) | 344,             /* CH5 */
    RSCFD_TX_BUFF_5_25  = (RSCFD_UNIT_0 << 24) | 345,             /* CH5 */
    RSCFD_TX_BUFF_5_26  = (RSCFD_UNIT_0 << 24) | 346,             /* CH5 */
    RSCFD_TX_BUFF_5_27  = (RSCFD_UNIT_0 << 24) | 347,             /* CH5 */
    RSCFD_TX_BUFF_5_28  = (RSCFD_UNIT_0 << 24) | 348,             /* CH5 */
    RSCFD_TX_BUFF_5_29  = (RSCFD_UNIT_0 << 24) | 349,             /* CH5 */
    RSCFD_TX_BUFF_5_30  = (RSCFD_UNIT_0 << 24) | 350,             /* CH5 */
    RSCFD_TX_BUFF_5_31  = (RSCFD_UNIT_0 << 24) | 351,             /* CH5 */
    RSCFD_TX_BUFF_5_32  = (RSCFD_UNIT_0 << 24) | 352,             /* CH5 */
    RSCFD_TX_BUFF_5_33  = (RSCFD_UNIT_0 << 24) | 353,             /* CH5 */
    RSCFD_TX_BUFF_5_34  = (RSCFD_UNIT_0 << 24) | 354,             /* CH5 */
    RSCFD_TX_BUFF_5_35  = (RSCFD_UNIT_0 << 24) | 355,             /* CH5 */
    RSCFD_TX_BUFF_5_36  = (RSCFD_UNIT_0 << 24) | 356,             /* CH5 */
    RSCFD_TX_BUFF_5_37  = (RSCFD_UNIT_0 << 24) | 357,             /* CH5 */
    RSCFD_TX_BUFF_5_38  = (RSCFD_UNIT_0 << 24) | 358,             /* CH5 */
    RSCFD_TX_BUFF_5_39  = (RSCFD_UNIT_0 << 24) | 359,             /* CH5 */
    RSCFD_TX_BUFF_5_40  = (RSCFD_UNIT_0 << 24) | 360,             /* CH5 */
    RSCFD_TX_BUFF_5_41  = (RSCFD_UNIT_0 << 24) | 361,             /* CH5 */
    RSCFD_TX_BUFF_5_42  = (RSCFD_UNIT_0 << 24) | 362,             /* CH5 */
    RSCFD_TX_BUFF_5_43  = (RSCFD_UNIT_0 << 24) | 363,             /* CH5 */
    RSCFD_TX_BUFF_5_44  = (RSCFD_UNIT_0 << 24) | 364,             /* CH5 */
    RSCFD_TX_BUFF_5_45  = (RSCFD_UNIT_0 << 24) | 365,             /* CH5 */
    RSCFD_TX_BUFF_5_46  = (RSCFD_UNIT_0 << 24) | 366,             /* CH5 */
    RSCFD_TX_BUFF_5_47  = (RSCFD_UNIT_0 << 24) | 367,             /* CH5 */
    RSCFD_TX_BUFF_5_48  = (RSCFD_UNIT_0 << 24) | 368,             /* CH5 */
    RSCFD_TX_BUFF_5_49  = (RSCFD_UNIT_0 << 24) | 369,             /* CH5 */
    RSCFD_TX_BUFF_5_50  = (RSCFD_UNIT_0 << 24) | 370,             /* CH5 */
    RSCFD_TX_BUFF_5_51  = (RSCFD_UNIT_0 << 24) | 371,             /* CH5 */
    RSCFD_TX_BUFF_5_52  = (RSCFD_UNIT_0 << 24) | 372,             /* CH5 */
    RSCFD_TX_BUFF_5_53  = (RSCFD_UNIT_0 << 24) | 373,             /* CH5 */
    RSCFD_TX_BUFF_5_54  = (RSCFD_UNIT_0 << 24) | 374,             /* CH5 */
    RSCFD_TX_BUFF_5_55  = (RSCFD_UNIT_0 << 24) | 375,             /* CH5 */
    RSCFD_TX_BUFF_5_56  = (RSCFD_UNIT_0 << 24) | 376,             /* CH5 */
    RSCFD_TX_BUFF_5_57  = (RSCFD_UNIT_0 << 24) | 377,             /* CH5 */
    RSCFD_TX_BUFF_5_58  = (RSCFD_UNIT_0 << 24) | 378,             /* CH5 */
    RSCFD_TX_BUFF_5_59  = (RSCFD_UNIT_0 << 24) | 379,             /* CH5 */
    RSCFD_TX_BUFF_5_60  = (RSCFD_UNIT_0 << 24) | 380,             /* CH5 */
    RSCFD_TX_BUFF_5_61  = (RSCFD_UNIT_0 << 24) | 381,             /* CH5 */
    RSCFD_TX_BUFF_5_62  = (RSCFD_UNIT_0 << 24) | 382,             /* CH5 */
    RSCFD_TX_BUFF_5_63  = (RSCFD_UNIT_0 << 24) | 383,             /* CH5 */

    RSCFD_TX_BUFF_6_0   = (RSCFD_UNIT_0 << 24) | 384,                 /* CH6 */
    RSCFD_TX_BUFF_6_1   = (RSCFD_UNIT_0 << 24) | 385,             /* CH6 */
    RSCFD_TX_BUFF_6_2   = (RSCFD_UNIT_0 << 24) | 386,             /* CH6 */
    RSCFD_TX_BUFF_6_3   = (RSCFD_UNIT_0 << 24) | 387,             /* CH6 */
    RSCFD_TX_BUFF_6_4   = (RSCFD_UNIT_0 << 24) | 388,             /* CH6 */
    RSCFD_TX_BUFF_6_5   = (RSCFD_UNIT_0 << 24) | 389,             /* CH6 */
    RSCFD_TX_BUFF_6_6   = (RSCFD_UNIT_0 << 24) | 390,             /* CH6 */
    RSCFD_TX_BUFF_6_7   = (RSCFD_UNIT_0 << 24) | 391,             /* CH6 */
    RSCFD_TX_BUFF_6_8   = (RSCFD_UNIT_0 << 24) | 392,             /* CH6 */
    RSCFD_TX_BUFF_6_9   = (RSCFD_UNIT_0 << 24) | 393,             /* CH6 */
    RSCFD_TX_BUFF_6_10  = (RSCFD_UNIT_0 << 24) | 394,             /* CH6 */
    RSCFD_TX_BUFF_6_11  = (RSCFD_UNIT_0 << 24) | 395,             /* CH6 */
    RSCFD_TX_BUFF_6_12  = (RSCFD_UNIT_0 << 24) | 396,             /* CH6 */
    RSCFD_TX_BUFF_6_13  = (RSCFD_UNIT_0 << 24) | 397,             /* CH6 */
    RSCFD_TX_BUFF_6_14  = (RSCFD_UNIT_0 << 24) | 398,             /* CH6 */
    RSCFD_TX_BUFF_6_15  = (RSCFD_UNIT_0 << 24) | 399,             /* CH6 */
    RSCFD_TX_BUFF_6_16  = (RSCFD_UNIT_0 << 24) | 400,             /* CH6 */
    RSCFD_TX_BUFF_6_17  = (RSCFD_UNIT_0 << 24) | 401,             /* CH6 */
    RSCFD_TX_BUFF_6_18  = (RSCFD_UNIT_0 << 24) | 402,             /* CH6 */
    RSCFD_TX_BUFF_6_19  = (RSCFD_UNIT_0 << 24) | 403,             /* CH6 */
    RSCFD_TX_BUFF_6_20  = (RSCFD_UNIT_0 << 24) | 404,             /* CH6 */
    RSCFD_TX_BUFF_6_21  = (RSCFD_UNIT_0 << 24) | 405,             /* CH6 */
    RSCFD_TX_BUFF_6_22  = (RSCFD_UNIT_0 << 24) | 406,             /* CH6 */
    RSCFD_TX_BUFF_6_23  = (RSCFD_UNIT_0 << 24) | 407,             /* CH6 */
    RSCFD_TX_BUFF_6_24  = (RSCFD_UNIT_0 << 24) | 408,             /* CH6 */
    RSCFD_TX_BUFF_6_25  = (RSCFD_UNIT_0 << 24) | 409,             /* CH6 */
    RSCFD_TX_BUFF_6_26  = (RSCFD_UNIT_0 << 24) | 410,             /* CH6 */
    RSCFD_TX_BUFF_6_27  = (RSCFD_UNIT_0 << 24) | 411,             /* CH6 */
    RSCFD_TX_BUFF_6_28  = (RSCFD_UNIT_0 << 24) | 412,             /* CH6 */
    RSCFD_TX_BUFF_6_29  = (RSCFD_UNIT_0 << 24) | 413,             /* CH6 */
    RSCFD_TX_BUFF_6_30  = (RSCFD_UNIT_0 << 24) | 414,             /* CH6 */
    RSCFD_TX_BUFF_6_31  = (RSCFD_UNIT_0 << 24) | 415,             /* CH6 */
    RSCFD_TX_BUFF_6_32  = (RSCFD_UNIT_0 << 24) | 416,             /* CH6 */
    RSCFD_TX_BUFF_6_33  = (RSCFD_UNIT_0 << 24) | 417,             /* CH6 */
    RSCFD_TX_BUFF_6_34  = (RSCFD_UNIT_0 << 24) | 418,             /* CH6 */
    RSCFD_TX_BUFF_6_35  = (RSCFD_UNIT_0 << 24) | 419,             /* CH6 */
    RSCFD_TX_BUFF_6_36  = (RSCFD_UNIT_0 << 24) | 420,             /* CH6 */
    RSCFD_TX_BUFF_6_37  = (RSCFD_UNIT_0 << 24) | 421,             /* CH6 */
    RSCFD_TX_BUFF_6_38  = (RSCFD_UNIT_0 << 24) | 422,             /* CH6 */
    RSCFD_TX_BUFF_6_39  = (RSCFD_UNIT_0 << 24) | 423,             /* CH6 */
    RSCFD_TX_BUFF_6_40  = (RSCFD_UNIT_0 << 24) | 424,             /* CH6 */
    RSCFD_TX_BUFF_6_41  = (RSCFD_UNIT_0 << 24) | 425,             /* CH6 */
    RSCFD_TX_BUFF_6_42  = (RSCFD_UNIT_0 << 24) | 426,             /* CH6 */
    RSCFD_TX_BUFF_6_43  = (RSCFD_UNIT_0 << 24) | 427,             /* CH6 */
    RSCFD_TX_BUFF_6_44  = (RSCFD_UNIT_0 << 24) | 428,             /* CH6 */
    RSCFD_TX_BUFF_6_45  = (RSCFD_UNIT_0 << 24) | 429,             /* CH6 */
    RSCFD_TX_BUFF_6_46  = (RSCFD_UNIT_0 << 24) | 430,             /* CH6 */
    RSCFD_TX_BUFF_6_47  = (RSCFD_UNIT_0 << 24) | 431,             /* CH6 */
    RSCFD_TX_BUFF_6_48  = (RSCFD_UNIT_0 << 24) | 432,             /* CH6 */
    RSCFD_TX_BUFF_6_49  = (RSCFD_UNIT_0 << 24) | 433,             /* CH6 */
    RSCFD_TX_BUFF_6_50  = (RSCFD_UNIT_0 << 24) | 434,             /* CH6 */
    RSCFD_TX_BUFF_6_51  = (RSCFD_UNIT_0 << 24) | 435,             /* CH6 */
    RSCFD_TX_BUFF_6_52  = (RSCFD_UNIT_0 << 24) | 436,             /* CH6 */
    RSCFD_TX_BUFF_6_53  = (RSCFD_UNIT_0 << 24) | 437,             /* CH6 */
    RSCFD_TX_BUFF_6_54  = (RSCFD_UNIT_0 << 24) | 438,             /* CH6 */
    RSCFD_TX_BUFF_6_55  = (RSCFD_UNIT_0 << 24) | 439,             /* CH6 */
    RSCFD_TX_BUFF_6_56  = (RSCFD_UNIT_0 << 24) | 440,             /* CH6 */
    RSCFD_TX_BUFF_6_57  = (RSCFD_UNIT_0 << 24) | 441,             /* CH6 */
    RSCFD_TX_BUFF_6_58  = (RSCFD_UNIT_0 << 24) | 442,             /* CH6 */
    RSCFD_TX_BUFF_6_59  = (RSCFD_UNIT_0 << 24) | 443,             /* CH6 */
    RSCFD_TX_BUFF_6_60  = (RSCFD_UNIT_0 << 24) | 444,             /* CH6 */
    RSCFD_TX_BUFF_6_61  = (RSCFD_UNIT_0 << 24) | 445,             /* CH6 */
    RSCFD_TX_BUFF_6_62  = (RSCFD_UNIT_0 << 24) | 446,             /* CH6 */
    RSCFD_TX_BUFF_6_63  = (RSCFD_UNIT_0 << 24) | 447,             /* CH6 */

    RSCFD_TX_BUFF_7_0   = (RSCFD_UNIT_0 << 24) | 448,             /* CH7 */
    RSCFD_TX_BUFF_7_1   = (RSCFD_UNIT_0 << 24) | 449,             /* CH7 */
    RSCFD_TX_BUFF_7_2   = (RSCFD_UNIT_0 << 24) | 450,             /* CH7 */
    RSCFD_TX_BUFF_7_3   = (RSCFD_UNIT_0 << 24) | 451,             /* CH7 */
    RSCFD_TX_BUFF_7_4   = (RSCFD_UNIT_0 << 24) | 452,             /* CH7 */
    RSCFD_TX_BUFF_7_5   = (RSCFD_UNIT_0 << 24) | 453,             /* CH7 */
    RSCFD_TX_BUFF_7_6   = (RSCFD_UNIT_0 << 24) | 454,             /* CH7 */
    RSCFD_TX_BUFF_7_7   = (RSCFD_UNIT_0 << 24) | 455,             /* CH7 */
    RSCFD_TX_BUFF_7_8   = (RSCFD_UNIT_0 << 24) | 456,             /* CH7 */
    RSCFD_TX_BUFF_7_9   = (RSCFD_UNIT_0 << 24) | 457,             /* CH7 */
    RSCFD_TX_BUFF_7_10  = (RSCFD_UNIT_0 << 24) | 458,             /* CH7 */
    RSCFD_TX_BUFF_7_11  = (RSCFD_UNIT_0 << 24) | 459,             /* CH7 */
    RSCFD_TX_BUFF_7_12  = (RSCFD_UNIT_0 << 24) | 460,             /* CH7 */
    RSCFD_TX_BUFF_7_13  = (RSCFD_UNIT_0 << 24) | 461,             /* CH7 */
    RSCFD_TX_BUFF_7_14  = (RSCFD_UNIT_0 << 24) | 462,             /* CH7 */
    RSCFD_TX_BUFF_7_15  = (RSCFD_UNIT_0 << 24) | 463,             /* CH7 */
    RSCFD_TX_BUFF_7_16  = (RSCFD_UNIT_0 << 24) | 464,             /* CH7 */
    RSCFD_TX_BUFF_7_17  = (RSCFD_UNIT_0 << 24) | 465,             /* CH7 */
    RSCFD_TX_BUFF_7_18  = (RSCFD_UNIT_0 << 24) | 466,             /* CH7 */
    RSCFD_TX_BUFF_7_19  = (RSCFD_UNIT_0 << 24) | 467,             /* CH7 */
    RSCFD_TX_BUFF_7_20  = (RSCFD_UNIT_0 << 24) | 468,             /* CH7 */
    RSCFD_TX_BUFF_7_21  = (RSCFD_UNIT_0 << 24) | 469,             /* CH7 */
    RSCFD_TX_BUFF_7_22  = (RSCFD_UNIT_0 << 24) | 470,             /* CH7 */
    RSCFD_TX_BUFF_7_23  = (RSCFD_UNIT_0 << 24) | 471,             /* CH7 */
    RSCFD_TX_BUFF_7_24  = (RSCFD_UNIT_0 << 24) | 472,             /* CH7 */
    RSCFD_TX_BUFF_7_25  = (RSCFD_UNIT_0 << 24) | 473,             /* CH7 */
    RSCFD_TX_BUFF_7_26  = (RSCFD_UNIT_0 << 24) | 474,             /* CH7 */
    RSCFD_TX_BUFF_7_27  = (RSCFD_UNIT_0 << 24) | 475,             /* CH7 */
    RSCFD_TX_BUFF_7_28  = (RSCFD_UNIT_0 << 24) | 476,             /* CH7 */
    RSCFD_TX_BUFF_7_29  = (RSCFD_UNIT_0 << 24) | 477,             /* CH7 */
    RSCFD_TX_BUFF_7_30  = (RSCFD_UNIT_0 << 24) | 478,             /* CH7 */
    RSCFD_TX_BUFF_7_31  = (RSCFD_UNIT_0 << 24) | 479,             /* CH7 */
    RSCFD_TX_BUFF_7_32  = (RSCFD_UNIT_0 << 24) | 480,             /* CH7 */
    RSCFD_TX_BUFF_7_33  = (RSCFD_UNIT_0 << 24) | 481,             /* CH7 */
    RSCFD_TX_BUFF_7_34  = (RSCFD_UNIT_0 << 24) | 482,             /* CH7 */
    RSCFD_TX_BUFF_7_35  = (RSCFD_UNIT_0 << 24) | 483,             /* CH7 */
    RSCFD_TX_BUFF_7_36  = (RSCFD_UNIT_0 << 24) | 484,             /* CH7 */
    RSCFD_TX_BUFF_7_37  = (RSCFD_UNIT_0 << 24) | 485,             /* CH7 */
    RSCFD_TX_BUFF_7_38  = (RSCFD_UNIT_0 << 24) | 486,             /* CH7 */
    RSCFD_TX_BUFF_7_39  = (RSCFD_UNIT_0 << 24) | 487,             /* CH7 */
    RSCFD_TX_BUFF_7_40  = (RSCFD_UNIT_0 << 24) | 488,             /* CH7 */
    RSCFD_TX_BUFF_7_41  = (RSCFD_UNIT_0 << 24) | 489,             /* CH7 */
    RSCFD_TX_BUFF_7_42  = (RSCFD_UNIT_0 << 24) | 490,             /* CH7 */
    RSCFD_TX_BUFF_7_43  = (RSCFD_UNIT_0 << 24) | 491,             /* CH7 */
    RSCFD_TX_BUFF_7_44  = (RSCFD_UNIT_0 << 24) | 492,             /* CH7 */
    RSCFD_TX_BUFF_7_45  = (RSCFD_UNIT_0 << 24) | 493,             /* CH7 */
    RSCFD_TX_BUFF_7_46  = (RSCFD_UNIT_0 << 24) | 494,             /* CH7 */
    RSCFD_TX_BUFF_7_47  = (RSCFD_UNIT_0 << 24) | 495,             /* CH7 */
    RSCFD_TX_BUFF_7_48  = (RSCFD_UNIT_0 << 24) | 496,             /* CH7 */
    RSCFD_TX_BUFF_7_49  = (RSCFD_UNIT_0 << 24) | 497,             /* CH7 */
    RSCFD_TX_BUFF_7_50  = (RSCFD_UNIT_0 << 24) | 498,             /* CH7 */
    RSCFD_TX_BUFF_7_51  = (RSCFD_UNIT_0 << 24) | 499,             /* CH7 */
    RSCFD_TX_BUFF_7_52  = (RSCFD_UNIT_0 << 24) | 500,             /* CH7 */
    RSCFD_TX_BUFF_7_53  = (RSCFD_UNIT_0 << 24) | 501,             /* CH7 */
    RSCFD_TX_BUFF_7_54  = (RSCFD_UNIT_0 << 24) | 502,             /* CH7 */
    RSCFD_TX_BUFF_7_55  = (RSCFD_UNIT_0 << 24) | 503,             /* CH7 */
    RSCFD_TX_BUFF_7_56  = (RSCFD_UNIT_0 << 24) | 504,             /* CH7 */
    RSCFD_TX_BUFF_7_57  = (RSCFD_UNIT_0 << 24) | 505,             /* CH7 */
    RSCFD_TX_BUFF_7_58  = (RSCFD_UNIT_0 << 24) | 506,             /* CH7 */
    RSCFD_TX_BUFF_7_59  = (RSCFD_UNIT_0 << 24) | 507,             /* CH7 */
    RSCFD_TX_BUFF_7_60  = (RSCFD_UNIT_0 << 24) | 508,             /* CH7 */
    RSCFD_TX_BUFF_7_61  = (RSCFD_UNIT_0 << 24) | 509,             /* CH7 */
    RSCFD_TX_BUFF_7_62  = (RSCFD_UNIT_0 << 24) | 510,             /* CH7 */
    RSCFD_TX_BUFF_7_63  = (RSCFD_UNIT_0 << 24) | 511,             /* CH7 */

    RSCFD_TX_BUFF_8_0   = (RSCFD_UNIT_1 << 24) | 0,               /* CH8 */
    RSCFD_TX_BUFF_8_1   = (RSCFD_UNIT_1 << 24) | 1,               /* CH8 */
    RSCFD_TX_BUFF_8_2   = (RSCFD_UNIT_1 << 24) | 2,               /* CH8 */
    RSCFD_TX_BUFF_8_3   = (RSCFD_UNIT_1 << 24) | 3,               /* CH8 */
    RSCFD_TX_BUFF_8_4   = (RSCFD_UNIT_1 << 24) | 4,               /* CH8 */
    RSCFD_TX_BUFF_8_5   = (RSCFD_UNIT_1 << 24) | 5,               /* CH8 */
    RSCFD_TX_BUFF_8_6   = (RSCFD_UNIT_1 << 24) | 6,               /* CH8 */
    RSCFD_TX_BUFF_8_7   = (RSCFD_UNIT_1 << 24) | 7,               /* CH8 */
    RSCFD_TX_BUFF_8_8   = (RSCFD_UNIT_1 << 24) | 8,               /* CH8 */
    RSCFD_TX_BUFF_8_9   = (RSCFD_UNIT_1 << 24) | 9,               /* CH8 */
    RSCFD_TX_BUFF_8_10  = (RSCFD_UNIT_1 << 24) | 10,              /* CH8 */
    RSCFD_TX_BUFF_8_11  = (RSCFD_UNIT_1 << 24) | 11,              /* CH8 */
    RSCFD_TX_BUFF_8_12  = (RSCFD_UNIT_1 << 24) | 12,              /* CH8 */
    RSCFD_TX_BUFF_8_13  = (RSCFD_UNIT_1 << 24) | 13,              /* CH8 */
    RSCFD_TX_BUFF_8_14  = (RSCFD_UNIT_1 << 24) | 14,              /* CH8 */
    RSCFD_TX_BUFF_8_15  = (RSCFD_UNIT_1 << 24) | 15,              /* CH8 */
    RSCFD_TX_BUFF_8_16  = (RSCFD_UNIT_1 << 24) | 16,              /* CH8 */
    RSCFD_TX_BUFF_8_17  = (RSCFD_UNIT_1 << 24) | 17,              /* CH8 */
    RSCFD_TX_BUFF_8_18  = (RSCFD_UNIT_1 << 24) | 18,              /* CH8 */
    RSCFD_TX_BUFF_8_19  = (RSCFD_UNIT_1 << 24) | 19,              /* CH8 */
    RSCFD_TX_BUFF_8_20  = (RSCFD_UNIT_1 << 24) | 20,              /* CH8 */
    RSCFD_TX_BUFF_8_21  = (RSCFD_UNIT_1 << 24) | 21,              /* CH8 */
    RSCFD_TX_BUFF_8_22  = (RSCFD_UNIT_1 << 24) | 22,              /* CH8 */
    RSCFD_TX_BUFF_8_23  = (RSCFD_UNIT_1 << 24) | 23,              /* CH8 */
    RSCFD_TX_BUFF_8_24  = (RSCFD_UNIT_1 << 24) | 24,              /* CH8 */
    RSCFD_TX_BUFF_8_25  = (RSCFD_UNIT_1 << 24) | 25,              /* CH8 */
    RSCFD_TX_BUFF_8_26  = (RSCFD_UNIT_1 << 24) | 26,              /* CH8 */
    RSCFD_TX_BUFF_8_27  = (RSCFD_UNIT_1 << 24) | 27,              /* CH8 */
    RSCFD_TX_BUFF_8_28  = (RSCFD_UNIT_1 << 24) | 28,              /* CH8 */
    RSCFD_TX_BUFF_8_29  = (RSCFD_UNIT_1 << 24) | 29,              /* CH8 */
    RSCFD_TX_BUFF_8_30  = (RSCFD_UNIT_1 << 24) | 30,              /* CH8 */
    RSCFD_TX_BUFF_8_31  = (RSCFD_UNIT_1 << 24) | 31,              /* CH8 */
    RSCFD_TX_BUFF_8_32  = (RSCFD_UNIT_1 << 24) | 32,              /* CH8 */
    RSCFD_TX_BUFF_8_33  = (RSCFD_UNIT_1 << 24) | 33,              /* CH8 */
    RSCFD_TX_BUFF_8_34  = (RSCFD_UNIT_1 << 24) | 34,              /* CH8 */
    RSCFD_TX_BUFF_8_35  = (RSCFD_UNIT_1 << 24) | 35,              /* CH8 */
    RSCFD_TX_BUFF_8_36  = (RSCFD_UNIT_1 << 24) | 36,              /* CH8 */
    RSCFD_TX_BUFF_8_37  = (RSCFD_UNIT_1 << 24) | 37,              /* CH8 */
    RSCFD_TX_BUFF_8_38  = (RSCFD_UNIT_1 << 24) | 38,              /* CH8 */
    RSCFD_TX_BUFF_8_39  = (RSCFD_UNIT_1 << 24) | 39,              /* CH8 */
    RSCFD_TX_BUFF_8_40  = (RSCFD_UNIT_1 << 24) | 40,              /* CH8 */
    RSCFD_TX_BUFF_8_41  = (RSCFD_UNIT_1 << 24) | 41,              /* CH8 */
    RSCFD_TX_BUFF_8_42  = (RSCFD_UNIT_1 << 24) | 42,              /* CH8 */
    RSCFD_TX_BUFF_8_43  = (RSCFD_UNIT_1 << 24) | 43,              /* CH8 */
    RSCFD_TX_BUFF_8_44  = (RSCFD_UNIT_1 << 24) | 44,              /* CH8 */
    RSCFD_TX_BUFF_8_45  = (RSCFD_UNIT_1 << 24) | 45,              /* CH8 */
    RSCFD_TX_BUFF_8_46  = (RSCFD_UNIT_1 << 24) | 46,              /* CH8 */
    RSCFD_TX_BUFF_8_47  = (RSCFD_UNIT_1 << 24) | 47,              /* CH8 */
    RSCFD_TX_BUFF_8_48  = (RSCFD_UNIT_1 << 24) | 48,              /* CH8 */
    RSCFD_TX_BUFF_8_49  = (RSCFD_UNIT_1 << 24) | 49,              /* CH8 */
    RSCFD_TX_BUFF_8_50  = (RSCFD_UNIT_1 << 24) | 50,              /* CH8 */
    RSCFD_TX_BUFF_8_51  = (RSCFD_UNIT_1 << 24) | 51,              /* CH8 */
    RSCFD_TX_BUFF_8_52  = (RSCFD_UNIT_1 << 24) | 52,              /* CH8 */
    RSCFD_TX_BUFF_8_53  = (RSCFD_UNIT_1 << 24) | 53,              /* CH8 */
    RSCFD_TX_BUFF_8_54  = (RSCFD_UNIT_1 << 24) | 54,              /* CH8 */
    RSCFD_TX_BUFF_8_55  = (RSCFD_UNIT_1 << 24) | 55,              /* CH8 */
    RSCFD_TX_BUFF_8_56  = (RSCFD_UNIT_1 << 24) | 56,              /* CH8 */
    RSCFD_TX_BUFF_8_57  = (RSCFD_UNIT_1 << 24) | 57,              /* CH8 */
    RSCFD_TX_BUFF_8_58  = (RSCFD_UNIT_1 << 24) | 58,              /* CH8 */
    RSCFD_TX_BUFF_8_59  = (RSCFD_UNIT_1 << 24) | 59,              /* CH8 */
    RSCFD_TX_BUFF_8_60  = (RSCFD_UNIT_1 << 24) | 60,              /* CH8 */
    RSCFD_TX_BUFF_8_61  = (RSCFD_UNIT_1 << 24) | 61,              /* CH8 */
    RSCFD_TX_BUFF_8_62  = (RSCFD_UNIT_1 << 24) | 62,              /* CH8 */
    RSCFD_TX_BUFF_8_63  = (RSCFD_UNIT_1 << 24) | 63,              /* CH8 */

    RSCFD_TX_BUFF_9_0   = (RSCFD_UNIT_1 << 24) | 64,              /* CH9 */
    RSCFD_TX_BUFF_9_1   = (RSCFD_UNIT_1 << 24) | 65,              /* CH9 */
    RSCFD_TX_BUFF_9_2   = (RSCFD_UNIT_1 << 24) | 66,              /* CH9 */
    RSCFD_TX_BUFF_9_3   = (RSCFD_UNIT_1 << 24) | 67,              /* CH9 */
    RSCFD_TX_BUFF_9_4   = (RSCFD_UNIT_1 << 24) | 68,              /* CH9 */
    RSCFD_TX_BUFF_9_5   = (RSCFD_UNIT_1 << 24) | 69,              /* CH9 */
    RSCFD_TX_BUFF_9_6   = (RSCFD_UNIT_1 << 24) | 70,              /* CH9 */
    RSCFD_TX_BUFF_9_7   = (RSCFD_UNIT_1 << 24) | 71,              /* CH9 */
    RSCFD_TX_BUFF_9_8   = (RSCFD_UNIT_1 << 24) | 72,              /* CH9 */
    RSCFD_TX_BUFF_9_9   = (RSCFD_UNIT_1 << 24) | 73,              /* CH9 */
    RSCFD_TX_BUFF_9_10  = (RSCFD_UNIT_1 << 24) | 74,              /* CH9 */
    RSCFD_TX_BUFF_9_11  = (RSCFD_UNIT_1 << 24) | 75,              /* CH9 */
    RSCFD_TX_BUFF_9_12  = (RSCFD_UNIT_1 << 24) | 76,              /* CH9 */
    RSCFD_TX_BUFF_9_13  = (RSCFD_UNIT_1 << 24) | 77,              /* CH9 */
    RSCFD_TX_BUFF_9_14  = (RSCFD_UNIT_1 << 24) | 78,              /* CH9 */
    RSCFD_TX_BUFF_9_15  = (RSCFD_UNIT_1 << 24) | 79,              /* CH9 */
    RSCFD_TX_BUFF_9_16  = (RSCFD_UNIT_1 << 24) | 80,              /* CH9 */
    RSCFD_TX_BUFF_9_17  = (RSCFD_UNIT_1 << 24) | 81,              /* CH9 */
    RSCFD_TX_BUFF_9_18  = (RSCFD_UNIT_1 << 24) | 82,              /* CH9 */
    RSCFD_TX_BUFF_9_19  = (RSCFD_UNIT_1 << 24) | 83,              /* CH9 */
    RSCFD_TX_BUFF_9_20  = (RSCFD_UNIT_1 << 24) | 84,              /* CH9 */
    RSCFD_TX_BUFF_9_21  = (RSCFD_UNIT_1 << 24) | 85,              /* CH9 */
    RSCFD_TX_BUFF_9_22  = (RSCFD_UNIT_1 << 24) | 86,              /* CH9 */
    RSCFD_TX_BUFF_9_23  = (RSCFD_UNIT_1 << 24) | 87,              /* CH9 */
    RSCFD_TX_BUFF_9_24  = (RSCFD_UNIT_1 << 24) | 88,              /* CH9 */
    RSCFD_TX_BUFF_9_25  = (RSCFD_UNIT_1 << 24) | 89,              /* CH9 */
    RSCFD_TX_BUFF_9_26  = (RSCFD_UNIT_1 << 24) | 90,              /* CH9 */
    RSCFD_TX_BUFF_9_27  = (RSCFD_UNIT_1 << 24) | 91,              /* CH9 */
    RSCFD_TX_BUFF_9_28  = (RSCFD_UNIT_1 << 24) | 92,              /* CH9 */
    RSCFD_TX_BUFF_9_29  = (RSCFD_UNIT_1 << 24) | 93,              /* CH9 */
    RSCFD_TX_BUFF_9_30  = (RSCFD_UNIT_1 << 24) | 94,              /* CH9 */
    RSCFD_TX_BUFF_9_31  = (RSCFD_UNIT_1 << 24) | 95,              /* CH9 */
    RSCFD_TX_BUFF_9_32  = (RSCFD_UNIT_1 << 24) | 96,              /* CH9 */
    RSCFD_TX_BUFF_9_33  = (RSCFD_UNIT_1 << 24) | 97,              /* CH9 */
    RSCFD_TX_BUFF_9_34  = (RSCFD_UNIT_1 << 24) | 98,              /* CH9 */
    RSCFD_TX_BUFF_9_35  = (RSCFD_UNIT_1 << 24) | 99,              /* CH9 */
    RSCFD_TX_BUFF_9_36  = (RSCFD_UNIT_1 << 24) | 100,             /* CH9 */
    RSCFD_TX_BUFF_9_37  = (RSCFD_UNIT_1 << 24) | 101,             /* CH9 */
    RSCFD_TX_BUFF_9_38  = (RSCFD_UNIT_1 << 24) | 102,             /* CH9 */
    RSCFD_TX_BUFF_9_39  = (RSCFD_UNIT_1 << 24) | 103,             /* CH9 */
    RSCFD_TX_BUFF_9_40  = (RSCFD_UNIT_1 << 24) | 104,             /* CH9 */
    RSCFD_TX_BUFF_9_41  = (RSCFD_UNIT_1 << 24) | 105,             /* CH9 */
    RSCFD_TX_BUFF_9_42  = (RSCFD_UNIT_1 << 24) | 106,             /* CH9 */
    RSCFD_TX_BUFF_9_43  = (RSCFD_UNIT_1 << 24) | 107,             /* CH9 */
    RSCFD_TX_BUFF_9_44  = (RSCFD_UNIT_1 << 24) | 108,             /* CH9 */
    RSCFD_TX_BUFF_9_45  = (RSCFD_UNIT_1 << 24) | 109,             /* CH9 */
    RSCFD_TX_BUFF_9_46  = (RSCFD_UNIT_1 << 24) | 110,             /* CH9 */
    RSCFD_TX_BUFF_9_47  = (RSCFD_UNIT_1 << 24) | 111,             /* CH9 */
    RSCFD_TX_BUFF_9_48  = (RSCFD_UNIT_1 << 24) | 112,             /* CH9 */
    RSCFD_TX_BUFF_9_49  = (RSCFD_UNIT_1 << 24) | 113,             /* CH9 */
    RSCFD_TX_BUFF_9_50  = (RSCFD_UNIT_1 << 24) | 114,             /* CH9 */
    RSCFD_TX_BUFF_9_51  = (RSCFD_UNIT_1 << 24) | 115,             /* CH9 */
    RSCFD_TX_BUFF_9_52  = (RSCFD_UNIT_1 << 24) | 116,             /* CH9 */
    RSCFD_TX_BUFF_9_53  = (RSCFD_UNIT_1 << 24) | 117,             /* CH9 */
    RSCFD_TX_BUFF_9_54  = (RSCFD_UNIT_1 << 24) | 118,             /* CH9 */
    RSCFD_TX_BUFF_9_55  = (RSCFD_UNIT_1 << 24) | 119,             /* CH9 */
    RSCFD_TX_BUFF_9_56  = (RSCFD_UNIT_1 << 24) | 120,             /* CH9 */
    RSCFD_TX_BUFF_9_57  = (RSCFD_UNIT_1 << 24) | 121,             /* CH9 */
    RSCFD_TX_BUFF_9_58  = (RSCFD_UNIT_1 << 24) | 122,             /* CH9 */
    RSCFD_TX_BUFF_9_59  = (RSCFD_UNIT_1 << 24) | 123,             /* CH9 */
    RSCFD_TX_BUFF_9_60  = (RSCFD_UNIT_1 << 24) | 124,             /* CH9 */
    RSCFD_TX_BUFF_9_61  = (RSCFD_UNIT_1 << 24) | 125,             /* CH9 */
    RSCFD_TX_BUFF_9_62  = (RSCFD_UNIT_1 << 24) | 126,             /* CH9 */
    RSCFD_TX_BUFF_9_63  = (RSCFD_UNIT_1 << 24) | 127,             /* CH9 */

    RSCFD_TX_BUFF_10_0  = (RSCFD_UNIT_1 << 24) | 128,             /* CH10 */
    RSCFD_TX_BUFF_10_1  = (RSCFD_UNIT_1 << 24) | 129,             /* CH10 */
    RSCFD_TX_BUFF_10_2  = (RSCFD_UNIT_1 << 24) | 130,             /* CH10 */
    RSCFD_TX_BUFF_10_3  = (RSCFD_UNIT_1 << 24) | 131,             /* CH10 */
    RSCFD_TX_BUFF_10_4  = (RSCFD_UNIT_1 << 24) | 132,             /* CH10 */
    RSCFD_TX_BUFF_10_5  = (RSCFD_UNIT_1 << 24) | 133,             /* CH10 */
    RSCFD_TX_BUFF_10_6  = (RSCFD_UNIT_1 << 24) | 134,             /* CH10 */
    RSCFD_TX_BUFF_10_7  = (RSCFD_UNIT_1 << 24) | 135,             /* CH10 */
    RSCFD_TX_BUFF_10_8  = (RSCFD_UNIT_1 << 24) | 136,             /* CH10 */
    RSCFD_TX_BUFF_10_9  = (RSCFD_UNIT_1 << 24) | 137,             /* CH10 */
    RSCFD_TX_BUFF_10_10 = (RSCFD_UNIT_1 << 24) | 138,             /* CH10 */
    RSCFD_TX_BUFF_10_11 = (RSCFD_UNIT_1 << 24) | 139,             /* CH10 */
    RSCFD_TX_BUFF_10_12 = (RSCFD_UNIT_1 << 24) | 140,             /* CH10 */
    RSCFD_TX_BUFF_10_13 = (RSCFD_UNIT_1 << 24) | 141,             /* CH10 */
    RSCFD_TX_BUFF_10_14 = (RSCFD_UNIT_1 << 24) | 142,             /* CH10 */
    RSCFD_TX_BUFF_10_15 = (RSCFD_UNIT_1 << 24) | 143,             /* CH10 */
    RSCFD_TX_BUFF_10_16 = (RSCFD_UNIT_1 << 24) | 144,             /* CH10 */
    RSCFD_TX_BUFF_10_17 = (RSCFD_UNIT_1 << 24) | 145,             /* CH10 */
    RSCFD_TX_BUFF_10_18 = (RSCFD_UNIT_1 << 24) | 146,             /* CH10 */
    RSCFD_TX_BUFF_10_19 = (RSCFD_UNIT_1 << 24) | 147,             /* CH10 */
    RSCFD_TX_BUFF_10_20 = (RSCFD_UNIT_1 << 24) | 148,             /* CH10 */
    RSCFD_TX_BUFF_10_21 = (RSCFD_UNIT_1 << 24) | 149,             /* CH10 */
    RSCFD_TX_BUFF_10_22 = (RSCFD_UNIT_1 << 24) | 150,             /* CH10 */
    RSCFD_TX_BUFF_10_23 = (RSCFD_UNIT_1 << 24) | 151,             /* CH10 */
    RSCFD_TX_BUFF_10_24 = (RSCFD_UNIT_1 << 24) | 152,             /* CH10 */
    RSCFD_TX_BUFF_10_25 = (RSCFD_UNIT_1 << 24) | 153,             /* CH10 */
    RSCFD_TX_BUFF_10_26 = (RSCFD_UNIT_1 << 24) | 154,             /* CH10 */
    RSCFD_TX_BUFF_10_27 = (RSCFD_UNIT_1 << 24) | 155,             /* CH10 */
    RSCFD_TX_BUFF_10_28 = (RSCFD_UNIT_1 << 24) | 156,             /* CH10 */
    RSCFD_TX_BUFF_10_29 = (RSCFD_UNIT_1 << 24) | 157,             /* CH10 */
    RSCFD_TX_BUFF_10_30 = (RSCFD_UNIT_1 << 24) | 158,             /* CH10 */
    RSCFD_TX_BUFF_10_31 = (RSCFD_UNIT_1 << 24) | 159,             /* CH10 */
    RSCFD_TX_BUFF_10_32 = (RSCFD_UNIT_1 << 24) | 160,             /* CH10 */
    RSCFD_TX_BUFF_10_33 = (RSCFD_UNIT_1 << 24) | 161,             /* CH10 */
    RSCFD_TX_BUFF_10_34 = (RSCFD_UNIT_1 << 24) | 162,             /* CH10 */
    RSCFD_TX_BUFF_10_35 = (RSCFD_UNIT_1 << 24) | 163,             /* CH10 */
    RSCFD_TX_BUFF_10_36 = (RSCFD_UNIT_1 << 24) | 164,             /* CH10 */
    RSCFD_TX_BUFF_10_37 = (RSCFD_UNIT_1 << 24) | 165,             /* CH10 */
    RSCFD_TX_BUFF_10_38 = (RSCFD_UNIT_1 << 24) | 166,             /* CH10 */
    RSCFD_TX_BUFF_10_39 = (RSCFD_UNIT_1 << 24) | 167,             /* CH10 */
    RSCFD_TX_BUFF_10_40 = (RSCFD_UNIT_1 << 24) | 168,             /* CH10 */
    RSCFD_TX_BUFF_10_41 = (RSCFD_UNIT_1 << 24) | 169,             /* CH10 */
    RSCFD_TX_BUFF_10_42 = (RSCFD_UNIT_1 << 24) | 170,             /* CH10 */
    RSCFD_TX_BUFF_10_43 = (RSCFD_UNIT_1 << 24) | 171,             /* CH10 */
    RSCFD_TX_BUFF_10_44 = (RSCFD_UNIT_1 << 24) | 172,             /* CH10 */
    RSCFD_TX_BUFF_10_45 = (RSCFD_UNIT_1 << 24) | 173,             /* CH10 */
    RSCFD_TX_BUFF_10_46 = (RSCFD_UNIT_1 << 24) | 174,             /* CH10 */
    RSCFD_TX_BUFF_10_47 = (RSCFD_UNIT_1 << 24) | 175,             /* CH10 */
    RSCFD_TX_BUFF_10_48 = (RSCFD_UNIT_1 << 24) | 176,             /* CH10 */
    RSCFD_TX_BUFF_10_49 = (RSCFD_UNIT_1 << 24) | 177,             /* CH10 */
    RSCFD_TX_BUFF_10_50 = (RSCFD_UNIT_1 << 24) | 178,             /* CH10 */
    RSCFD_TX_BUFF_10_51 = (RSCFD_UNIT_1 << 24) | 179,             /* CH10 */
    RSCFD_TX_BUFF_10_52 = (RSCFD_UNIT_1 << 24) | 180,             /* CH10 */
    RSCFD_TX_BUFF_10_53 = (RSCFD_UNIT_1 << 24) | 181,             /* CH10 */
    RSCFD_TX_BUFF_10_54 = (RSCFD_UNIT_1 << 24) | 182,             /* CH10 */
    RSCFD_TX_BUFF_10_55 = (RSCFD_UNIT_1 << 24) | 183,             /* CH10 */
    RSCFD_TX_BUFF_10_56 = (RSCFD_UNIT_1 << 24) | 184,             /* CH10 */
    RSCFD_TX_BUFF_10_57 = (RSCFD_UNIT_1 << 24) | 185,             /* CH10 */
    RSCFD_TX_BUFF_10_58 = (RSCFD_UNIT_1 << 24) | 186,             /* CH10 */
    RSCFD_TX_BUFF_10_59 = (RSCFD_UNIT_1 << 24) | 187,             /* CH10 */
    RSCFD_TX_BUFF_10_60 = (RSCFD_UNIT_1 << 24) | 188,             /* CH10 */
    RSCFD_TX_BUFF_10_61 = (RSCFD_UNIT_1 << 24) | 189,             /* CH10 */
    RSCFD_TX_BUFF_10_62 = (RSCFD_UNIT_1 << 24) | 190,             /* CH10 */
    RSCFD_TX_BUFF_10_63 = (RSCFD_UNIT_1 << 24) | 191,             /* CH10 */

    RSCFD_TX_BUFF_11_0  = (RSCFD_UNIT_1 << 24) | 192,             /* CH11 */
    RSCFD_TX_BUFF_11_1  = (RSCFD_UNIT_1 << 24) | 193,             /* CH11 */
    RSCFD_TX_BUFF_11_2  = (RSCFD_UNIT_1 << 24) | 194,             /* CH11 */
    RSCFD_TX_BUFF_11_3  = (RSCFD_UNIT_1 << 24) | 195,             /* CH11 */
    RSCFD_TX_BUFF_11_4  = (RSCFD_UNIT_1 << 24) | 196,             /* CH11 */
    RSCFD_TX_BUFF_11_5  = (RSCFD_UNIT_1 << 24) | 197,             /* CH11 */
    RSCFD_TX_BUFF_11_6  = (RSCFD_UNIT_1 << 24) | 198,             /* CH11 */
    RSCFD_TX_BUFF_11_7  = (RSCFD_UNIT_1 << 24) | 199,             /* CH11 */
    RSCFD_TX_BUFF_11_8  = (RSCFD_UNIT_1 << 24) | 200,             /* CH11 */
    RSCFD_TX_BUFF_11_9  = (RSCFD_UNIT_1 << 24) | 201,             /* CH11 */
    RSCFD_TX_BUFF_11_10 = (RSCFD_UNIT_1 << 24) | 202,             /* CH11 */
    RSCFD_TX_BUFF_11_11 = (RSCFD_UNIT_1 << 24) | 203,             /* CH11 */
    RSCFD_TX_BUFF_11_12 = (RSCFD_UNIT_1 << 24) | 204,             /* CH11 */
    RSCFD_TX_BUFF_11_13 = (RSCFD_UNIT_1 << 24) | 205,             /* CH11 */
    RSCFD_TX_BUFF_11_14 = (RSCFD_UNIT_1 << 24) | 206,             /* CH11 */
    RSCFD_TX_BUFF_11_15 = (RSCFD_UNIT_1 << 24) | 207,             /* CH11 */
    RSCFD_TX_BUFF_11_16 = (RSCFD_UNIT_1 << 24) | 208,             /* CH11 */
    RSCFD_TX_BUFF_11_17 = (RSCFD_UNIT_1 << 24) | 209,             /* CH11 */
    RSCFD_TX_BUFF_11_18 = (RSCFD_UNIT_1 << 24) | 210,             /* CH11 */
    RSCFD_TX_BUFF_11_19 = (RSCFD_UNIT_1 << 24) | 211,             /* CH11 */
    RSCFD_TX_BUFF_11_20 = (RSCFD_UNIT_1 << 24) | 212,             /* CH11 */
    RSCFD_TX_BUFF_11_21 = (RSCFD_UNIT_1 << 24) | 213,             /* CH11 */
    RSCFD_TX_BUFF_11_22 = (RSCFD_UNIT_1 << 24) | 214,             /* CH11 */
    RSCFD_TX_BUFF_11_23 = (RSCFD_UNIT_1 << 24) | 215,             /* CH11 */
    RSCFD_TX_BUFF_11_24 = (RSCFD_UNIT_1 << 24) | 216,             /* CH11 */
    RSCFD_TX_BUFF_11_25 = (RSCFD_UNIT_1 << 24) | 217,             /* CH11 */
    RSCFD_TX_BUFF_11_26 = (RSCFD_UNIT_1 << 24) | 218,             /* CH11 */
    RSCFD_TX_BUFF_11_27 = (RSCFD_UNIT_1 << 24) | 219,             /* CH11 */
    RSCFD_TX_BUFF_11_28 = (RSCFD_UNIT_1 << 24) | 220,             /* CH11 */
    RSCFD_TX_BUFF_11_29 = (RSCFD_UNIT_1 << 24) | 221,             /* CH11 */
    RSCFD_TX_BUFF_11_30 = (RSCFD_UNIT_1 << 24) | 222,             /* CH11 */
    RSCFD_TX_BUFF_11_31 = (RSCFD_UNIT_1 << 24) | 223,             /* CH11 */
    RSCFD_TX_BUFF_11_32 = (RSCFD_UNIT_1 << 24) | 224,             /* CH11 */
    RSCFD_TX_BUFF_11_33 = (RSCFD_UNIT_1 << 24) | 225,             /* CH11 */
    RSCFD_TX_BUFF_11_34 = (RSCFD_UNIT_1 << 24) | 226,             /* CH11 */
    RSCFD_TX_BUFF_11_35 = (RSCFD_UNIT_1 << 24) | 227,             /* CH11 */
    RSCFD_TX_BUFF_11_36 = (RSCFD_UNIT_1 << 24) | 228,             /* CH11 */
    RSCFD_TX_BUFF_11_37 = (RSCFD_UNIT_1 << 24) | 229,             /* CH11 */
    RSCFD_TX_BUFF_11_38 = (RSCFD_UNIT_1 << 24) | 230,             /* CH11 */
    RSCFD_TX_BUFF_11_39 = (RSCFD_UNIT_1 << 24) | 231,             /* CH11 */
    RSCFD_TX_BUFF_11_40 = (RSCFD_UNIT_1 << 24) | 232,             /* CH11 */
    RSCFD_TX_BUFF_11_41 = (RSCFD_UNIT_1 << 24) | 233,             /* CH11 */
    RSCFD_TX_BUFF_11_42 = (RSCFD_UNIT_1 << 24) | 234,             /* CH11 */
    RSCFD_TX_BUFF_11_43 = (RSCFD_UNIT_1 << 24) | 235,             /* CH11 */
    RSCFD_TX_BUFF_11_44 = (RSCFD_UNIT_1 << 24) | 236,             /* CH11 */
    RSCFD_TX_BUFF_11_45 = (RSCFD_UNIT_1 << 24) | 237,             /* CH11 */
    RSCFD_TX_BUFF_11_46 = (RSCFD_UNIT_1 << 24) | 238,             /* CH11 */
    RSCFD_TX_BUFF_11_47 = (RSCFD_UNIT_1 << 24) | 239,             /* CH11 */
    RSCFD_TX_BUFF_11_48 = (RSCFD_UNIT_1 << 24) | 240,             /* CH11 */
    RSCFD_TX_BUFF_11_49 = (RSCFD_UNIT_1 << 24) | 241,             /* CH11 */
    RSCFD_TX_BUFF_11_50 = (RSCFD_UNIT_1 << 24) | 242,             /* CH11 */
    RSCFD_TX_BUFF_11_51 = (RSCFD_UNIT_1 << 24) | 243,             /* CH11 */
    RSCFD_TX_BUFF_11_52 = (RSCFD_UNIT_1 << 24) | 244,             /* CH11 */
    RSCFD_TX_BUFF_11_53 = (RSCFD_UNIT_1 << 24) | 245,             /* CH11 */
    RSCFD_TX_BUFF_11_54 = (RSCFD_UNIT_1 << 24) | 246,             /* CH11 */
    RSCFD_TX_BUFF_11_55 = (RSCFD_UNIT_1 << 24) | 247,             /* CH11 */
    RSCFD_TX_BUFF_11_56 = (RSCFD_UNIT_1 << 24) | 248,             /* CH11 */
    RSCFD_TX_BUFF_11_57 = (RSCFD_UNIT_1 << 24) | 249,             /* CH11 */
    RSCFD_TX_BUFF_11_58 = (RSCFD_UNIT_1 << 24) | 250,             /* CH11 */
    RSCFD_TX_BUFF_11_59 = (RSCFD_UNIT_1 << 24) | 251,             /* CH11 */
    RSCFD_TX_BUFF_11_60 = (RSCFD_UNIT_1 << 24) | 252,             /* CH11 */
    RSCFD_TX_BUFF_11_61 = (RSCFD_UNIT_1 << 24) | 253,             /* CH11 */
    RSCFD_TX_BUFF_11_62 = (RSCFD_UNIT_1 << 24) | 254,             /* CH11 */
    RSCFD_TX_BUFF_11_63 = (RSCFD_UNIT_1 << 24) | 255,             /* CH11 */

    RSCFD_TX_BUFF_12_0  = (RSCFD_UNIT_1 << 24) | 256,             /* CH12 */
    RSCFD_TX_BUFF_12_1  = (RSCFD_UNIT_1 << 24) | 257,             /* CH12 */
    RSCFD_TX_BUFF_12_2  = (RSCFD_UNIT_1 << 24) | 258,             /* CH12 */
    RSCFD_TX_BUFF_12_3  = (RSCFD_UNIT_1 << 24) | 259,             /* CH12 */
    RSCFD_TX_BUFF_12_4  = (RSCFD_UNIT_1 << 24) | 260,             /* CH12 */
    RSCFD_TX_BUFF_12_5  = (RSCFD_UNIT_1 << 24) | 261,             /* CH12 */
    RSCFD_TX_BUFF_12_6  = (RSCFD_UNIT_1 << 24) | 262,             /* CH12 */
    RSCFD_TX_BUFF_12_7  = (RSCFD_UNIT_1 << 24) | 263,             /* CH12 */
    RSCFD_TX_BUFF_12_8  = (RSCFD_UNIT_1 << 24) | 264,             /* CH12 */
    RSCFD_TX_BUFF_12_9  = (RSCFD_UNIT_1 << 24) | 265,             /* CH12 */
    RSCFD_TX_BUFF_12_10 = (RSCFD_UNIT_1 << 24) | 266,             /* CH12 */
    RSCFD_TX_BUFF_12_11 = (RSCFD_UNIT_1 << 24) | 267,             /* CH12 */
    RSCFD_TX_BUFF_12_12 = (RSCFD_UNIT_1 << 24) | 268,             /* CH12 */
    RSCFD_TX_BUFF_12_13 = (RSCFD_UNIT_1 << 24) | 269,             /* CH12 */
    RSCFD_TX_BUFF_12_14 = (RSCFD_UNIT_1 << 24) | 270,             /* CH12 */
    RSCFD_TX_BUFF_12_15 = (RSCFD_UNIT_1 << 24) | 271,             /* CH12 */
    RSCFD_TX_BUFF_12_16 = (RSCFD_UNIT_1 << 24) | 272,             /* CH12 */
    RSCFD_TX_BUFF_12_17 = (RSCFD_UNIT_1 << 24) | 273,             /* CH12 */
    RSCFD_TX_BUFF_12_18 = (RSCFD_UNIT_1 << 24) | 274,             /* CH12 */
    RSCFD_TX_BUFF_12_19 = (RSCFD_UNIT_1 << 24) | 275,             /* CH12 */
    RSCFD_TX_BUFF_12_20 = (RSCFD_UNIT_1 << 24) | 276,             /* CH12 */
    RSCFD_TX_BUFF_12_21 = (RSCFD_UNIT_1 << 24) | 277,             /* CH12 */
    RSCFD_TX_BUFF_12_22 = (RSCFD_UNIT_1 << 24) | 278,             /* CH12 */
    RSCFD_TX_BUFF_12_23 = (RSCFD_UNIT_1 << 24) | 279,             /* CH12 */
    RSCFD_TX_BUFF_12_24 = (RSCFD_UNIT_1 << 24) | 280,             /* CH12 */
    RSCFD_TX_BUFF_12_25 = (RSCFD_UNIT_1 << 24) | 281,             /* CH12 */
    RSCFD_TX_BUFF_12_26 = (RSCFD_UNIT_1 << 24) | 282,             /* CH12 */
    RSCFD_TX_BUFF_12_27 = (RSCFD_UNIT_1 << 24) | 283,             /* CH12 */
    RSCFD_TX_BUFF_12_28 = (RSCFD_UNIT_1 << 24) | 284,             /* CH12 */
    RSCFD_TX_BUFF_12_29 = (RSCFD_UNIT_1 << 24) | 285,             /* CH12 */
    RSCFD_TX_BUFF_12_30 = (RSCFD_UNIT_1 << 24) | 286,             /* CH12 */
    RSCFD_TX_BUFF_12_31 = (RSCFD_UNIT_1 << 24) | 287,             /* CH12 */
    RSCFD_TX_BUFF_12_32 = (RSCFD_UNIT_1 << 24) | 288,             /* CH12 */
    RSCFD_TX_BUFF_12_33 = (RSCFD_UNIT_1 << 24) | 289,             /* CH12 */
    RSCFD_TX_BUFF_12_34 = (RSCFD_UNIT_1 << 24) | 290,             /* CH12 */
    RSCFD_TX_BUFF_12_35 = (RSCFD_UNIT_1 << 24) | 291,             /* CH12 */
    RSCFD_TX_BUFF_12_36 = (RSCFD_UNIT_1 << 24) | 292,             /* CH12 */
    RSCFD_TX_BUFF_12_37 = (RSCFD_UNIT_1 << 24) | 293,             /* CH12 */
    RSCFD_TX_BUFF_12_38 = (RSCFD_UNIT_1 << 24) | 294,             /* CH12 */
    RSCFD_TX_BUFF_12_39 = (RSCFD_UNIT_1 << 24) | 295,             /* CH12 */
    RSCFD_TX_BUFF_12_40 = (RSCFD_UNIT_1 << 24) | 296,             /* CH12 */
    RSCFD_TX_BUFF_12_41 = (RSCFD_UNIT_1 << 24) | 297,             /* CH12 */
    RSCFD_TX_BUFF_12_42 = (RSCFD_UNIT_1 << 24) | 298,             /* CH12 */
    RSCFD_TX_BUFF_12_43 = (RSCFD_UNIT_1 << 24) | 299,             /* CH12 */
    RSCFD_TX_BUFF_12_44 = (RSCFD_UNIT_1 << 24) | 300,             /* CH12 */
    RSCFD_TX_BUFF_12_45 = (RSCFD_UNIT_1 << 24) | 301,             /* CH12 */
    RSCFD_TX_BUFF_12_46 = (RSCFD_UNIT_1 << 24) | 302,             /* CH12 */
    RSCFD_TX_BUFF_12_47 = (RSCFD_UNIT_1 << 24) | 303,             /* CH12 */
    RSCFD_TX_BUFF_12_48 = (RSCFD_UNIT_1 << 24) | 304,             /* CH12 */
    RSCFD_TX_BUFF_12_49 = (RSCFD_UNIT_1 << 24) | 305,             /* CH12 */
    RSCFD_TX_BUFF_12_50 = (RSCFD_UNIT_1 << 24) | 306,             /* CH12 */
    RSCFD_TX_BUFF_12_51 = (RSCFD_UNIT_1 << 24) | 307,             /* CH12 */
    RSCFD_TX_BUFF_12_52 = (RSCFD_UNIT_1 << 24) | 308,             /* CH12 */
    RSCFD_TX_BUFF_12_53 = (RSCFD_UNIT_1 << 24) | 309,             /* CH12 */
    RSCFD_TX_BUFF_12_54 = (RSCFD_UNIT_1 << 24) | 310,             /* CH12 */
    RSCFD_TX_BUFF_12_55 = (RSCFD_UNIT_1 << 24) | 311,             /* CH12 */
    RSCFD_TX_BUFF_12_56 = (RSCFD_UNIT_1 << 24) | 312,             /* CH12 */
    RSCFD_TX_BUFF_12_57 = (RSCFD_UNIT_1 << 24) | 313,             /* CH12 */
    RSCFD_TX_BUFF_12_58 = (RSCFD_UNIT_1 << 24) | 314,             /* CH12 */
    RSCFD_TX_BUFF_12_59 = (RSCFD_UNIT_1 << 24) | 315,             /* CH12 */
    RSCFD_TX_BUFF_12_60 = (RSCFD_UNIT_1 << 24) | 316,             /* CH12 */
    RSCFD_TX_BUFF_12_61 = (RSCFD_UNIT_1 << 24) | 317,             /* CH12 */
    RSCFD_TX_BUFF_12_62 = (RSCFD_UNIT_1 << 24) | 318,             /* CH12 */
    RSCFD_TX_BUFF_12_63 = (RSCFD_UNIT_1 << 24) | 319,             /* CH12 */

    RSCFD_TX_BUFF_13_0  = (RSCFD_UNIT_1 << 24) | 320,             /* CH13 */
    RSCFD_TX_BUFF_13_1  = (RSCFD_UNIT_1 << 24) | 321,             /* CH13 */
    RSCFD_TX_BUFF_13_2  = (RSCFD_UNIT_1 << 24) | 322,             /* CH13 */
    RSCFD_TX_BUFF_13_3  = (RSCFD_UNIT_1 << 24) | 323,             /* CH13 */
    RSCFD_TX_BUFF_13_4  = (RSCFD_UNIT_1 << 24) | 324,             /* CH13 */
    RSCFD_TX_BUFF_13_5  = (RSCFD_UNIT_1 << 24) | 325,             /* CH13 */
    RSCFD_TX_BUFF_13_6  = (RSCFD_UNIT_1 << 24) | 326,             /* CH13 */
    RSCFD_TX_BUFF_13_7  = (RSCFD_UNIT_1 << 24) | 327,             /* CH13 */
    RSCFD_TX_BUFF_13_8  = (RSCFD_UNIT_1 << 24) | 328,             /* CH13 */
    RSCFD_TX_BUFF_13_9  = (RSCFD_UNIT_1 << 24) | 329,             /* CH13 */
    RSCFD_TX_BUFF_13_10 = (RSCFD_UNIT_1 << 24) | 330,             /* CH13 */
    RSCFD_TX_BUFF_13_11 = (RSCFD_UNIT_1 << 24) | 331,             /* CH13 */
    RSCFD_TX_BUFF_13_12 = (RSCFD_UNIT_1 << 24) | 332,             /* CH13 */
    RSCFD_TX_BUFF_13_13 = (RSCFD_UNIT_1 << 24) | 333,             /* CH13 */
    RSCFD_TX_BUFF_13_14 = (RSCFD_UNIT_1 << 24) | 334,             /* CH13 */
    RSCFD_TX_BUFF_13_15 = (RSCFD_UNIT_1 << 24) | 335,             /* CH13 */
    RSCFD_TX_BUFF_13_16 = (RSCFD_UNIT_1 << 24) | 336,             /* CH13 */
    RSCFD_TX_BUFF_13_17 = (RSCFD_UNIT_1 << 24) | 337,             /* CH13 */
    RSCFD_TX_BUFF_13_18 = (RSCFD_UNIT_1 << 24) | 338,             /* CH13 */
    RSCFD_TX_BUFF_13_19 = (RSCFD_UNIT_1 << 24) | 339,             /* CH13 */
    RSCFD_TX_BUFF_13_20 = (RSCFD_UNIT_1 << 24) | 340,             /* CH13 */
    RSCFD_TX_BUFF_13_21 = (RSCFD_UNIT_1 << 24) | 341,             /* CH13 */
    RSCFD_TX_BUFF_13_22 = (RSCFD_UNIT_1 << 24) | 342,             /* CH13 */
    RSCFD_TX_BUFF_13_23 = (RSCFD_UNIT_1 << 24) | 343,             /* CH13 */
    RSCFD_TX_BUFF_13_24 = (RSCFD_UNIT_1 << 24) | 344,             /* CH13 */
    RSCFD_TX_BUFF_13_25 = (RSCFD_UNIT_1 << 24) | 345,             /* CH13 */
    RSCFD_TX_BUFF_13_26 = (RSCFD_UNIT_1 << 24) | 346,             /* CH13 */
    RSCFD_TX_BUFF_13_27 = (RSCFD_UNIT_1 << 24) | 347,             /* CH13 */
    RSCFD_TX_BUFF_13_28 = (RSCFD_UNIT_1 << 24) | 348,             /* CH13 */
    RSCFD_TX_BUFF_13_29 = (RSCFD_UNIT_1 << 24) | 349,             /* CH13 */
    RSCFD_TX_BUFF_13_30 = (RSCFD_UNIT_1 << 24) | 350,             /* CH13 */
    RSCFD_TX_BUFF_13_31 = (RSCFD_UNIT_1 << 24) | 351,             /* CH13 */
    RSCFD_TX_BUFF_13_32 = (RSCFD_UNIT_1 << 24) | 352,             /* CH13 */
    RSCFD_TX_BUFF_13_33 = (RSCFD_UNIT_1 << 24) | 353,             /* CH13 */
    RSCFD_TX_BUFF_13_34 = (RSCFD_UNIT_1 << 24) | 354,             /* CH13 */
    RSCFD_TX_BUFF_13_35 = (RSCFD_UNIT_1 << 24) | 355,             /* CH13 */
    RSCFD_TX_BUFF_13_36 = (RSCFD_UNIT_1 << 24) | 356,             /* CH13 */
    RSCFD_TX_BUFF_13_37 = (RSCFD_UNIT_1 << 24) | 357,             /* CH13 */
    RSCFD_TX_BUFF_13_38 = (RSCFD_UNIT_1 << 24) | 358,             /* CH13 */
    RSCFD_TX_BUFF_13_39 = (RSCFD_UNIT_1 << 24) | 359,             /* CH13 */
    RSCFD_TX_BUFF_13_40 = (RSCFD_UNIT_1 << 24) | 360,             /* CH13 */
    RSCFD_TX_BUFF_13_41 = (RSCFD_UNIT_1 << 24) | 361,             /* CH13 */
    RSCFD_TX_BUFF_13_42 = (RSCFD_UNIT_1 << 24) | 362,             /* CH13 */
    RSCFD_TX_BUFF_13_43 = (RSCFD_UNIT_1 << 24) | 363,             /* CH13 */
    RSCFD_TX_BUFF_13_44 = (RSCFD_UNIT_1 << 24) | 364,             /* CH13 */
    RSCFD_TX_BUFF_13_45 = (RSCFD_UNIT_1 << 24) | 365,             /* CH13 */
    RSCFD_TX_BUFF_13_46 = (RSCFD_UNIT_1 << 24) | 366,             /* CH13 */
    RSCFD_TX_BUFF_13_47 = (RSCFD_UNIT_1 << 24) | 367,             /* CH13 */
    RSCFD_TX_BUFF_13_48 = (RSCFD_UNIT_1 << 24) | 368,             /* CH13 */
    RSCFD_TX_BUFF_13_49 = (RSCFD_UNIT_1 << 24) | 369,             /* CH13 */
    RSCFD_TX_BUFF_13_50 = (RSCFD_UNIT_1 << 24) | 370,             /* CH13 */
    RSCFD_TX_BUFF_13_51 = (RSCFD_UNIT_1 << 24) | 371,             /* CH13 */
    RSCFD_TX_BUFF_13_52 = (RSCFD_UNIT_1 << 24) | 372,             /* CH13 */
    RSCFD_TX_BUFF_13_53 = (RSCFD_UNIT_1 << 24) | 373,             /* CH13 */
    RSCFD_TX_BUFF_13_54 = (RSCFD_UNIT_1 << 24) | 374,             /* CH13 */
    RSCFD_TX_BUFF_13_55 = (RSCFD_UNIT_1 << 24) | 375,             /* CH13 */
    RSCFD_TX_BUFF_13_56 = (RSCFD_UNIT_1 << 24) | 376,             /* CH13 */
    RSCFD_TX_BUFF_13_57 = (RSCFD_UNIT_1 << 24) | 377,             /* CH13 */
    RSCFD_TX_BUFF_13_58 = (RSCFD_UNIT_1 << 24) | 378,             /* CH13 */
    RSCFD_TX_BUFF_13_59 = (RSCFD_UNIT_1 << 24) | 379,             /* CH13 */
    RSCFD_TX_BUFF_13_60 = (RSCFD_UNIT_1 << 24) | 380,             /* CH13 */
    RSCFD_TX_BUFF_13_61 = (RSCFD_UNIT_1 << 24) | 381,             /* CH13 */
    RSCFD_TX_BUFF_13_62 = (RSCFD_UNIT_1 << 24) | 382,             /* CH13 */
    RSCFD_TX_BUFF_13_63 = (RSCFD_UNIT_1 << 24) | 383,             /* CH13 */

    RSCFD_TX_BUFF_14_0  = (RSCFD_UNIT_1 << 24) | 384,             /* CH14 */
    RSCFD_TX_BUFF_14_1  = (RSCFD_UNIT_1 << 24) | 385,             /* CH14 */
    RSCFD_TX_BUFF_14_2  = (RSCFD_UNIT_1 << 24) | 386,             /* CH14 */
    RSCFD_TX_BUFF_14_3  = (RSCFD_UNIT_1 << 24) | 387,             /* CH14 */
    RSCFD_TX_BUFF_14_4  = (RSCFD_UNIT_1 << 24) | 388,             /* CH14 */
    RSCFD_TX_BUFF_14_5  = (RSCFD_UNIT_1 << 24) | 389,             /* CH14 */
    RSCFD_TX_BUFF_14_6  = (RSCFD_UNIT_1 << 24) | 390,             /* CH14 */
    RSCFD_TX_BUFF_14_7  = (RSCFD_UNIT_1 << 24) | 391,             /* CH14 */
    RSCFD_TX_BUFF_14_8  = (RSCFD_UNIT_1 << 24) | 392,             /* CH14 */
    RSCFD_TX_BUFF_14_9  = (RSCFD_UNIT_1 << 24) | 393,             /* CH14 */
    RSCFD_TX_BUFF_14_10 = (RSCFD_UNIT_1 << 24) | 394,             /* CH14 */
    RSCFD_TX_BUFF_14_11 = (RSCFD_UNIT_1 << 24) | 395,             /* CH14 */
    RSCFD_TX_BUFF_14_12 = (RSCFD_UNIT_1 << 24) | 396,             /* CH14 */
    RSCFD_TX_BUFF_14_13 = (RSCFD_UNIT_1 << 24) | 397,             /* CH14 */
    RSCFD_TX_BUFF_14_14 = (RSCFD_UNIT_1 << 24) | 398,             /* CH14 */
    RSCFD_TX_BUFF_14_15 = (RSCFD_UNIT_1 << 24) | 399,             /* CH14 */
    RSCFD_TX_BUFF_14_16 = (RSCFD_UNIT_1 << 24) | 400,             /* CH14 */
    RSCFD_TX_BUFF_14_17 = (RSCFD_UNIT_1 << 24) | 401,             /* CH14 */
    RSCFD_TX_BUFF_14_18 = (RSCFD_UNIT_1 << 24) | 402,             /* CH14 */
    RSCFD_TX_BUFF_14_19 = (RSCFD_UNIT_1 << 24) | 403,             /* CH14 */
    RSCFD_TX_BUFF_14_20 = (RSCFD_UNIT_1 << 24) | 404,             /* CH14 */
    RSCFD_TX_BUFF_14_21 = (RSCFD_UNIT_1 << 24) | 405,             /* CH14 */
    RSCFD_TX_BUFF_14_22 = (RSCFD_UNIT_1 << 24) | 406,             /* CH14 */
    RSCFD_TX_BUFF_14_23 = (RSCFD_UNIT_1 << 24) | 407,             /* CH14 */
    RSCFD_TX_BUFF_14_24 = (RSCFD_UNIT_1 << 24) | 408,             /* CH14 */
    RSCFD_TX_BUFF_14_25 = (RSCFD_UNIT_1 << 24) | 409,             /* CH14 */
    RSCFD_TX_BUFF_14_26 = (RSCFD_UNIT_1 << 24) | 410,             /* CH14 */
    RSCFD_TX_BUFF_14_27 = (RSCFD_UNIT_1 << 24) | 411,             /* CH14 */
    RSCFD_TX_BUFF_14_28 = (RSCFD_UNIT_1 << 24) | 412,             /* CH14 */
    RSCFD_TX_BUFF_14_29 = (RSCFD_UNIT_1 << 24) | 413,             /* CH14 */
    RSCFD_TX_BUFF_14_30 = (RSCFD_UNIT_1 << 24) | 414,             /* CH14 */
    RSCFD_TX_BUFF_14_31 = (RSCFD_UNIT_1 << 24) | 415,             /* CH14 */
    RSCFD_TX_BUFF_14_32 = (RSCFD_UNIT_1 << 24) | 416,             /* CH14 */
    RSCFD_TX_BUFF_14_33 = (RSCFD_UNIT_1 << 24) | 417,             /* CH14 */
    RSCFD_TX_BUFF_14_34 = (RSCFD_UNIT_1 << 24) | 418,             /* CH14 */
    RSCFD_TX_BUFF_14_35 = (RSCFD_UNIT_1 << 24) | 419,             /* CH14 */
    RSCFD_TX_BUFF_14_36 = (RSCFD_UNIT_1 << 24) | 420,             /* CH14 */
    RSCFD_TX_BUFF_14_37 = (RSCFD_UNIT_1 << 24) | 421,             /* CH14 */
    RSCFD_TX_BUFF_14_38 = (RSCFD_UNIT_1 << 24) | 422,             /* CH14 */
    RSCFD_TX_BUFF_14_39 = (RSCFD_UNIT_1 << 24) | 423,             /* CH14 */
    RSCFD_TX_BUFF_14_40 = (RSCFD_UNIT_1 << 24) | 424,             /* CH14 */
    RSCFD_TX_BUFF_14_41 = (RSCFD_UNIT_1 << 24) | 425,             /* CH14 */
    RSCFD_TX_BUFF_14_42 = (RSCFD_UNIT_1 << 24) | 426,             /* CH14 */
    RSCFD_TX_BUFF_14_43 = (RSCFD_UNIT_1 << 24) | 427,             /* CH14 */
    RSCFD_TX_BUFF_14_44 = (RSCFD_UNIT_1 << 24) | 428,             /* CH14 */
    RSCFD_TX_BUFF_14_45 = (RSCFD_UNIT_1 << 24) | 429,             /* CH14 */
    RSCFD_TX_BUFF_14_46 = (RSCFD_UNIT_1 << 24) | 430,             /* CH14 */
    RSCFD_TX_BUFF_14_47 = (RSCFD_UNIT_1 << 24) | 431,             /* CH14 */
    RSCFD_TX_BUFF_14_48 = (RSCFD_UNIT_1 << 24) | 432,             /* CH14 */
    RSCFD_TX_BUFF_14_49 = (RSCFD_UNIT_1 << 24) | 433,             /* CH14 */
    RSCFD_TX_BUFF_14_50 = (RSCFD_UNIT_1 << 24) | 434,             /* CH14 */
    RSCFD_TX_BUFF_14_51 = (RSCFD_UNIT_1 << 24) | 435,             /* CH14 */
    RSCFD_TX_BUFF_14_52 = (RSCFD_UNIT_1 << 24) | 436,             /* CH14 */
    RSCFD_TX_BUFF_14_53 = (RSCFD_UNIT_1 << 24) | 437,             /* CH14 */
    RSCFD_TX_BUFF_14_54 = (RSCFD_UNIT_1 << 24) | 438,             /* CH14 */
    RSCFD_TX_BUFF_14_55 = (RSCFD_UNIT_1 << 24) | 439,             /* CH14 */
    RSCFD_TX_BUFF_14_56 = (RSCFD_UNIT_1 << 24) | 440,             /* CH14 */
    RSCFD_TX_BUFF_14_57 = (RSCFD_UNIT_1 << 24) | 441,             /* CH14 */
    RSCFD_TX_BUFF_14_58 = (RSCFD_UNIT_1 << 24) | 442,             /* CH14 */
    RSCFD_TX_BUFF_14_59 = (RSCFD_UNIT_1 << 24) | 443,             /* CH14 */
    RSCFD_TX_BUFF_14_60 = (RSCFD_UNIT_1 << 24) | 444,             /* CH14 */
    RSCFD_TX_BUFF_14_61 = (RSCFD_UNIT_1 << 24) | 445,             /* CH14 */
    RSCFD_TX_BUFF_14_62 = (RSCFD_UNIT_1 << 24) | 446,             /* CH14 */
    RSCFD_TX_BUFF_14_63 = (RSCFD_UNIT_1 << 24) | 447,             /* CH14 */

    RSCFD_TX_BUFF_15_0  = (RSCFD_UNIT_1 << 24) | 448,             /* CH15 */
    RSCFD_TX_BUFF_15_1  = (RSCFD_UNIT_1 << 24) | 449,             /* CH15 */
    RSCFD_TX_BUFF_15_2  = (RSCFD_UNIT_1 << 24) | 450,             /* CH15 */
    RSCFD_TX_BUFF_15_3  = (RSCFD_UNIT_1 << 24) | 451,             /* CH15 */
    RSCFD_TX_BUFF_15_4  = (RSCFD_UNIT_1 << 24) | 452,             /* CH15 */
    RSCFD_TX_BUFF_15_5  = (RSCFD_UNIT_1 << 24) | 453,             /* CH15 */
    RSCFD_TX_BUFF_15_6  = (RSCFD_UNIT_1 << 24) | 454,             /* CH15 */
    RSCFD_TX_BUFF_15_7  = (RSCFD_UNIT_1 << 24) | 455,             /* CH15 */
    RSCFD_TX_BUFF_15_8  = (RSCFD_UNIT_1 << 24) | 456,             /* CH15 */
    RSCFD_TX_BUFF_15_9  = (RSCFD_UNIT_1 << 24) | 457,             /* CH15 */
    RSCFD_TX_BUFF_15_10 = (RSCFD_UNIT_1 << 24) | 458,             /* CH15 */
    RSCFD_TX_BUFF_15_11 = (RSCFD_UNIT_1 << 24) | 459,             /* CH15 */
    RSCFD_TX_BUFF_15_12 = (RSCFD_UNIT_1 << 24) | 460,             /* CH15 */
    RSCFD_TX_BUFF_15_13 = (RSCFD_UNIT_1 << 24) | 461,             /* CH15 */
    RSCFD_TX_BUFF_15_14 = (RSCFD_UNIT_1 << 24) | 462,             /* CH15 */
    RSCFD_TX_BUFF_15_15 = (RSCFD_UNIT_1 << 24) | 463,             /* CH15 */
    RSCFD_TX_BUFF_15_16 = (RSCFD_UNIT_1 << 24) | 464,             /* CH15 */
    RSCFD_TX_BUFF_15_17 = (RSCFD_UNIT_1 << 24) | 465,             /* CH15 */
    RSCFD_TX_BUFF_15_18 = (RSCFD_UNIT_1 << 24) | 466,             /* CH15 */
    RSCFD_TX_BUFF_15_19 = (RSCFD_UNIT_1 << 24) | 467,             /* CH15 */
    RSCFD_TX_BUFF_15_20 = (RSCFD_UNIT_1 << 24) | 468,             /* CH15 */
    RSCFD_TX_BUFF_15_21 = (RSCFD_UNIT_1 << 24) | 469,             /* CH15 */
    RSCFD_TX_BUFF_15_22 = (RSCFD_UNIT_1 << 24) | 470,             /* CH15 */
    RSCFD_TX_BUFF_15_23 = (RSCFD_UNIT_1 << 24) | 471,             /* CH15 */
    RSCFD_TX_BUFF_15_24 = (RSCFD_UNIT_1 << 24) | 472,             /* CH15 */
    RSCFD_TX_BUFF_15_25 = (RSCFD_UNIT_1 << 24) | 473,             /* CH15 */
    RSCFD_TX_BUFF_15_26 = (RSCFD_UNIT_1 << 24) | 474,             /* CH15 */
    RSCFD_TX_BUFF_15_27 = (RSCFD_UNIT_1 << 24) | 475,             /* CH15 */
    RSCFD_TX_BUFF_15_28 = (RSCFD_UNIT_1 << 24) | 476,             /* CH15 */
    RSCFD_TX_BUFF_15_29 = (RSCFD_UNIT_1 << 24) | 477,             /* CH15 */
    RSCFD_TX_BUFF_15_30 = (RSCFD_UNIT_1 << 24) | 478,             /* CH15 */
    RSCFD_TX_BUFF_15_31 = (RSCFD_UNIT_1 << 24) | 479,             /* CH15 */
    RSCFD_TX_BUFF_15_32 = (RSCFD_UNIT_1 << 24) | 480,             /* CH15 */
    RSCFD_TX_BUFF_15_33 = (RSCFD_UNIT_1 << 24) | 481,             /* CH15 */
    RSCFD_TX_BUFF_15_34 = (RSCFD_UNIT_1 << 24) | 482,             /* CH15 */
    RSCFD_TX_BUFF_15_35 = (RSCFD_UNIT_1 << 24) | 483,             /* CH15 */
    RSCFD_TX_BUFF_15_36 = (RSCFD_UNIT_1 << 24) | 484,             /* CH15 */
    RSCFD_TX_BUFF_15_37 = (RSCFD_UNIT_1 << 24) | 485,             /* CH15 */
    RSCFD_TX_BUFF_15_38 = (RSCFD_UNIT_1 << 24) | 486,             /* CH15 */
    RSCFD_TX_BUFF_15_39 = (RSCFD_UNIT_1 << 24) | 487,             /* CH15 */
    RSCFD_TX_BUFF_15_40 = (RSCFD_UNIT_1 << 24) | 488,             /* CH15 */
    RSCFD_TX_BUFF_15_41 = (RSCFD_UNIT_1 << 24) | 489,             /* CH15 */
    RSCFD_TX_BUFF_15_42 = (RSCFD_UNIT_1 << 24) | 490,             /* CH15 */
    RSCFD_TX_BUFF_15_43 = (RSCFD_UNIT_1 << 24) | 491,             /* CH15 */
    RSCFD_TX_BUFF_15_44 = (RSCFD_UNIT_1 << 24) | 492,             /* CH15 */
    RSCFD_TX_BUFF_15_45 = (RSCFD_UNIT_1 << 24) | 493,             /* CH15 */
    RSCFD_TX_BUFF_15_46 = (RSCFD_UNIT_1 << 24) | 494,             /* CH15 */
    RSCFD_TX_BUFF_15_47 = (RSCFD_UNIT_1 << 24) | 495,             /* CH15 */
    RSCFD_TX_BUFF_15_48 = (RSCFD_UNIT_1 << 24) | 496,             /* CH15 */
    RSCFD_TX_BUFF_15_49 = (RSCFD_UNIT_1 << 24) | 497,             /* CH15 */
    RSCFD_TX_BUFF_15_50 = (RSCFD_UNIT_1 << 24) | 498,             /* CH15 */
    RSCFD_TX_BUFF_15_51 = (RSCFD_UNIT_1 << 24) | 499,             /* CH15 */
    RSCFD_TX_BUFF_15_52 = (RSCFD_UNIT_1 << 24) | 500,             /* CH15 */
    RSCFD_TX_BUFF_15_53 = (RSCFD_UNIT_1 << 24) | 501,             /* CH15 */
    RSCFD_TX_BUFF_15_54 = (RSCFD_UNIT_1 << 24) | 502,             /* CH15 */
    RSCFD_TX_BUFF_15_55 = (RSCFD_UNIT_1 << 24) | 503,             /* CH15 */
    RSCFD_TX_BUFF_15_56 = (RSCFD_UNIT_1 << 24) | 504,             /* CH15 */
    RSCFD_TX_BUFF_15_57 = (RSCFD_UNIT_1 << 24) | 505,             /* CH15 */
    RSCFD_TX_BUFF_15_58 = (RSCFD_UNIT_1 << 24) | 506,             /* CH15 */
    RSCFD_TX_BUFF_15_59 = (RSCFD_UNIT_1 << 24) | 507,             /* CH15 */
    RSCFD_TX_BUFF_15_60 = (RSCFD_UNIT_1 << 24) | 508,             /* CH15 */
    RSCFD_TX_BUFF_15_61 = (RSCFD_UNIT_1 << 24) | 509,             /* CH15 */
    RSCFD_TX_BUFF_15_62 = (RSCFD_UNIT_1 << 24) | 510,             /* CH15 */
    RSCFD_TX_BUFF_15_63 = (RSCFD_UNIT_1 << 24) | 511              /* CH15 */
}   rscfd_tx_buff_t;

/*******************************************************************************
 * Tx Buffer number for FIFO assignment - 32 per FIFO
 *******************************************************************************/
typedef enum
{
    RSCFD_TX_FIFO_BUFF_0  = 0x00000,
    RSCFD_TX_FIFO_BUFF_1  = 0x10000,
    RSCFD_TX_FIFO_BUFF_2  = 0x20000,
    RSCFD_TX_FIFO_BUFF_3  = 0x30000,
    RSCFD_TX_FIFO_BUFF_4  = 0x40000,
    RSCFD_TX_FIFO_BUFF_5  = 0x50000,
    RSCFD_TX_FIFO_BUFF_6  = 0x60000,
    RSCFD_TX_FIFO_BUFF_7  = 0x70000,
    RSCFD_TX_FIFO_BUFF_8  = 0x80000,
    RSCFD_TX_FIFO_BUFF_9  = 0x90000,
    RSCFD_TX_FIFO_BUFF_10 = 0xa0000,
    RSCFD_TX_FIFO_BUFF_11 = 0xb0000,
    RSCFD_TX_FIFO_BUFF_12 = 0xc0000,
    RSCFD_TX_FIFO_BUFF_13 = 0xd0000,
    RSCFD_TX_FIFO_BUFF_14 = 0xe0000,
    RSCFD_TX_FIFO_BUFF_15 = 0xf0000,
    RSCFD_TX_FIFO_BUFF_16 = 0x100000,
    RSCFD_TX_FIFO_BUFF_17 = 0x110000,
    RSCFD_TX_FIFO_BUFF_18 = 0x120000,
    RSCFD_TX_FIFO_BUFF_19 = 0x130000,
    RSCFD_TX_FIFO_BUFF_20 = 0x140000,
    RSCFD_TX_FIFO_BUFF_21 = 0x150000,
    RSCFD_TX_FIFO_BUFF_22 = 0x160000,
    RSCFD_TX_FIFO_BUFF_23 = 0x170000,
    RSCFD_TX_FIFO_BUFF_24 = 0x180000,
    RSCFD_TX_FIFO_BUFF_25 = 0x190000,
    RSCFD_TX_FIFO_BUFF_26 = 0x1a0000,
    RSCFD_TX_FIFO_BUFF_27 = 0x1b0000,
    RSCFD_TX_FIFO_BUFF_28 = 0x1c0000,
    RSCFD_TX_FIFO_BUFF_29 = 0x1d0000,
    RSCFD_TX_FIFO_BUFF_30 = 0x1e0000,
    RSCFD_TX_FIFO_BUFF_31 = 0x1f0000
} rscfd_tx_fifo_buff_t;

/*******************************************************************************
 * Enumerations of buffers, fifos, and queues available to transmit messages.
 *   Tx/Rx FIFO number - 3 per channel (CH0=0/1/2, CH1=3/4/5, ... CH7=21/22/23)
 *   Tx Buffer number - 64 per channel (CH0=0-63, CH1=64-127, ... CH7=448-511)
 *******************************************************************************/
typedef enum
{
    /* Unit 0 - TxRx FIFO */
    RSCFD_TX_DST_FIFO_0_0   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_0_0,     /* CH0 */
    RSCFD_TX_DST_FIFO_0_1   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_0_1,     /* CH0 */
    RSCFD_TX_DST_FIFO_0_2   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_0_2,     /* CH0 */

    RSCFD_TX_DST_FIFO_1_0   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_1_0,         /* CH1 */
    RSCFD_TX_DST_FIFO_1_1   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_1_1,     /* CH1 */
    RSCFD_TX_DST_FIFO_1_2   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_1_2,     /* CH1 */

    RSCFD_TX_DST_FIFO_2_0   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_2_0,         /* CH2 */
    RSCFD_TX_DST_FIFO_2_1   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_2_1,     /* CH2 */
    RSCFD_TX_DST_FIFO_2_2   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_2_2,     /* CH2 */

    RSCFD_TX_DST_FIFO_3_0   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_3_0,         /* CH3 */
    RSCFD_TX_DST_FIFO_3_1   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_3_1,     /* CH3 */
    RSCFD_TX_DST_FIFO_3_2   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_3_2,     /* CH3 */

    RSCFD_TX_DST_FIFO_4_0   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_4_0,         /* CH4 */
    RSCFD_TX_DST_FIFO_4_1   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_4_1,     /* CH4 */
    RSCFD_TX_DST_FIFO_4_2   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_4_2,     /* CH4 */

    RSCFD_TX_DST_FIFO_5_0   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_5_0,         /* CH5 */
    RSCFD_TX_DST_FIFO_5_1   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_5_1,     /* CH5 */
    RSCFD_TX_DST_FIFO_5_2   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_5_2,     /* CH5 */

    RSCFD_TX_DST_FIFO_6_0   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_6_0,         /* CH6 */
    RSCFD_TX_DST_FIFO_6_1   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_6_1,     /* CH6 */
    RSCFD_TX_DST_FIFO_6_2   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_6_2,     /* CH6 */

    RSCFD_TX_DST_FIFO_7_0   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_7_0,         /* CH7 */
    RSCFD_TX_DST_FIFO_7_1   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_7_1,     /* CH7 */
    RSCFD_TX_DST_FIFO_7_2   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_7_2,     /* CH7 */

    /* Unit 1 - TxRx FIFO */
    RSCFD_TX_DST_FIFO_8_0   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_8_0,     /* CH8 */
    RSCFD_TX_DST_FIFO_8_1   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_8_1,     /* CH8 */
    RSCFD_TX_DST_FIFO_8_2   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_8_2,     /* CH8 */

    RSCFD_TX_DST_FIFO_9_0   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_9_0,         /* CH9 */
    RSCFD_TX_DST_FIFO_9_1   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_9_1,     /* CH9 */
    RSCFD_TX_DST_FIFO_9_2   = RSCFD_TX_FIFO | RSCFD_TX_FIFO_9_2,     /* CH9 */

    RSCFD_TX_DST_FIFO_10_0  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_10_0,        /* CH10 */
    RSCFD_TX_DST_FIFO_10_1  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_10_1,    /* CH10 */
    RSCFD_TX_DST_FIFO_10_2  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_10_2,    /* CH10 */

    RSCFD_TX_DST_FIFO_11_0  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_11_0,        /* CH11 */
    RSCFD_TX_DST_FIFO_11_1  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_11_1,    /* CH11 */
    RSCFD_TX_DST_FIFO_11_2  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_11_2,    /* CH11 */

    RSCFD_TX_DST_FIFO_12_0  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_12_0,        /* CH12 */
    RSCFD_TX_DST_FIFO_12_1  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_12_1,    /* CH12 */
    RSCFD_TX_DST_FIFO_12_2  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_12_2,    /* CH12 */

    RSCFD_TX_DST_FIFO_13_0  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_13_0,        /* CH13 */
    RSCFD_TX_DST_FIFO_13_1  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_13_1,    /* CH13 */
    RSCFD_TX_DST_FIFO_13_2  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_13_2,    /* CH13 */

    RSCFD_TX_DST_FIFO_14_0  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_14_0,        /* CH14 */
    RSCFD_TX_DST_FIFO_14_1  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_14_1,    /* CH14 */
    RSCFD_TX_DST_FIFO_14_2  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_14_2,    /* CH14 */

    RSCFD_TX_DST_FIFO_15_0  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_15_0,        /* CH15 */
    RSCFD_TX_DST_FIFO_15_1  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_15_1,    /* CH15 */
    RSCFD_TX_DST_FIFO_15_2  = RSCFD_TX_FIFO | RSCFD_TX_FIFO_15_2,    /* CH15 */

    /* Unit 0 Tx Buffer */
    RSCFD_TX_DST_BUFF_0_0   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_0,     /* CH0 */
    RSCFD_TX_DST_BUFF_0_1   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_1,     /* CH0 */
    RSCFD_TX_DST_BUFF_0_2   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_2,     /* CH0 */
    RSCFD_TX_DST_BUFF_0_3   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_3,     /* CH0 */
    RSCFD_TX_DST_BUFF_0_4   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_4,     /* CH0 */
    RSCFD_TX_DST_BUFF_0_5   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_5,     /* CH0 */
    RSCFD_TX_DST_BUFF_0_6   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_6,     /* CH0 */
    RSCFD_TX_DST_BUFF_0_7   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_7,     /* CH0 */
    RSCFD_TX_DST_BUFF_0_8   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_8,     /* CH0 */
    RSCFD_TX_DST_BUFF_0_9   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_9,     /* CH0 */
    RSCFD_TX_DST_BUFF_0_10  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_10,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_11  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_11,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_12  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_12,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_13  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_13,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_14  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_14,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_15  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_15,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_16  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_16,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_17  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_17,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_18  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_18,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_19  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_19,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_20  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_20,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_21  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_21,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_22  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_22,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_23  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_23,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_24  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_24,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_25  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_25,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_26  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_26,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_27  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_27,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_28  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_28,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_29  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_29,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_30  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_30,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_31  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_31,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_32  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_32,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_33  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_33,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_34  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_34,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_35  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_35,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_36  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_36,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_37  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_37,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_38  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_38,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_39  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_39,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_40  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_40,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_41  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_41,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_42  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_42,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_43  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_43,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_44  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_44,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_45  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_45,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_46  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_46,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_47  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_47,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_48  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_48,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_49  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_49,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_50  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_50,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_51  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_51,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_52  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_52,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_53  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_53,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_54  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_54,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_55  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_55,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_56  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_56,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_57  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_57,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_58  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_58,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_59  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_59,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_60  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_60,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_61  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_61,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_62  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_62,    /* CH0 */
    RSCFD_TX_DST_BUFF_0_63  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_0_63,    /* CH0 */

    RSCFD_TX_DST_BUFF_1_0   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_0,     /* CH1 */
    RSCFD_TX_DST_BUFF_1_1   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_1,     /* CH1 */
    RSCFD_TX_DST_BUFF_1_2   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_2,     /* CH1 */
    RSCFD_TX_DST_BUFF_1_3   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_3,     /* CH1 */
    RSCFD_TX_DST_BUFF_1_4   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_4,     /* CH1 */
    RSCFD_TX_DST_BUFF_1_5   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_5,     /* CH1 */
    RSCFD_TX_DST_BUFF_1_6   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_6,     /* CH1 */
    RSCFD_TX_DST_BUFF_1_7   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_7,     /* CH1 */
    RSCFD_TX_DST_BUFF_1_8   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_8,     /* CH1 */
    RSCFD_TX_DST_BUFF_1_9   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_9,     /* CH1 */
    RSCFD_TX_DST_BUFF_1_10  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_10,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_11  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_11,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_12  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_12,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_13  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_13,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_14  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_14,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_15  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_15,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_16  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_16,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_17  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_17,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_18  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_18,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_19  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_19,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_20  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_20,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_21  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_21,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_22  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_22,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_23  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_23,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_24  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_24,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_25  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_25,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_26  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_26,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_27  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_27,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_28  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_28,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_29  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_29,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_30  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_30,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_31  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_31,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_32  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_32,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_33  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_33,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_34  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_34,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_35  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_35,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_36  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_36,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_37  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_37,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_38  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_38,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_39  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_39,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_40  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_40,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_41  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_41,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_42  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_42,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_43  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_43,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_44  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_44,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_45  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_45,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_46  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_46,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_47  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_47,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_48  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_48,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_49  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_49,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_50  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_50,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_51  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_51,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_52  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_52,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_53  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_53,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_54  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_54,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_55  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_55,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_56  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_56,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_57  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_57,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_58  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_58,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_59  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_59,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_60  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_60,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_61  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_61,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_62  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_62,    /* CH1 */
    RSCFD_TX_DST_BUFF_1_63  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_1_63,    /* CH1 */

    RSCFD_TX_DST_BUFF_2_0   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_0,     /* CH2 */
    RSCFD_TX_DST_BUFF_2_1   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_1,     /* CH2 */
    RSCFD_TX_DST_BUFF_2_2   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_2,     /* CH2 */
    RSCFD_TX_DST_BUFF_2_3   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_3,     /* CH2 */
    RSCFD_TX_DST_BUFF_2_4   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_4,     /* CH2 */
    RSCFD_TX_DST_BUFF_2_5   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_5,     /* CH2 */
    RSCFD_TX_DST_BUFF_2_6   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_6,     /* CH2 */
    RSCFD_TX_DST_BUFF_2_7   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_7,     /* CH2 */
    RSCFD_TX_DST_BUFF_2_8   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_8,     /* CH2 */
    RSCFD_TX_DST_BUFF_2_9   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_9,     /* CH2 */
    RSCFD_TX_DST_BUFF_2_10  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_10,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_11  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_11,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_12  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_12,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_13  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_13,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_14  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_14,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_15  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_15,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_16  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_16,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_17  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_17,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_18  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_18,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_19  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_19,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_20  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_20,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_21  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_21,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_22  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_22,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_23  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_23,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_24  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_24,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_25  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_25,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_26  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_26,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_27  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_27,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_28  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_28,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_29  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_29,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_30  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_30,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_31  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_31,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_32  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_32,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_33  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_33,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_34  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_34,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_35  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_35,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_36  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_36,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_37  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_37,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_38  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_38,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_39  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_39,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_40  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_40,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_41  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_41,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_42  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_42,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_43  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_43,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_44  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_44,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_45  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_45,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_46  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_46,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_47  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_47,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_48  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_48,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_49  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_49,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_50  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_50,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_51  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_51,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_52  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_52,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_53  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_53,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_54  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_54,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_55  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_55,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_56  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_56,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_57  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_57,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_58  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_58,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_59  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_59,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_60  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_60,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_61  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_61,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_62  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_62,    /* CH2 */
    RSCFD_TX_DST_BUFF_2_63  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_2_63,    /* CH2 */

    RSCFD_TX_DST_BUFF_3_0   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_0,     /* CH3 */
    RSCFD_TX_DST_BUFF_3_1   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_1,     /* CH3 */
    RSCFD_TX_DST_BUFF_3_2   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_2,     /* CH3 */
    RSCFD_TX_DST_BUFF_3_3   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_3,     /* CH3 */
    RSCFD_TX_DST_BUFF_3_4   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_4,     /* CH3 */
    RSCFD_TX_DST_BUFF_3_5   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_5,     /* CH3 */
    RSCFD_TX_DST_BUFF_3_6   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_6,     /* CH3 */
    RSCFD_TX_DST_BUFF_3_7   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_7,     /* CH3 */
    RSCFD_TX_DST_BUFF_3_8   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_8,     /* CH3 */
    RSCFD_TX_DST_BUFF_3_9   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_9,     /* CH3 */
    RSCFD_TX_DST_BUFF_3_10  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_10,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_11  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_11,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_12  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_12,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_13  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_13,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_14  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_14,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_15  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_15,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_16  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_16,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_17  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_17,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_18  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_18,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_19  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_19,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_20  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_20,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_21  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_21,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_22  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_22,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_23  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_23,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_24  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_24,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_25  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_25,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_26  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_26,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_27  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_27,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_28  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_28,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_29  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_29,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_30  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_30,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_31  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_31,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_32  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_32,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_33  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_33,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_34  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_34,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_35  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_35,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_36  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_36,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_37  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_37,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_38  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_38,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_39  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_39,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_40  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_40,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_41  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_41,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_42  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_42,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_43  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_43,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_44  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_44,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_45  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_45,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_46  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_46,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_47  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_47,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_48  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_48,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_49  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_49,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_50  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_50,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_51  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_51,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_52  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_52,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_53  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_53,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_54  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_54,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_55  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_55,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_56  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_56,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_57  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_57,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_58  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_58,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_59  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_59,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_60  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_60,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_61  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_61,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_62  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_62,    /* CH3 */
    RSCFD_TX_DST_BUFF_3_63  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_3_63,    /* CH3 */

    RSCFD_TX_DST_BUFF_4_0   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_0,     /* CH4 */
    RSCFD_TX_DST_BUFF_4_1   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_1,     /* CH4 */
    RSCFD_TX_DST_BUFF_4_2   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_2,     /* CH4 */
    RSCFD_TX_DST_BUFF_4_3   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_3,     /* CH4 */
    RSCFD_TX_DST_BUFF_4_4   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_4,     /* CH4 */
    RSCFD_TX_DST_BUFF_4_5   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_5,     /* CH4 */
    RSCFD_TX_DST_BUFF_4_6   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_6,     /* CH4 */
    RSCFD_TX_DST_BUFF_4_7   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_7,     /* CH4 */
    RSCFD_TX_DST_BUFF_4_8   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_8,     /* CH4 */
    RSCFD_TX_DST_BUFF_4_9   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_9,     /* CH4 */
    RSCFD_TX_DST_BUFF_4_10  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_10,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_11  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_11,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_12  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_12,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_13  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_13,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_14  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_14,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_15  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_15,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_16  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_16,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_17  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_17,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_18  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_18,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_19  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_19,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_20  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_20,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_21  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_21,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_22  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_22,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_23  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_23,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_24  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_24,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_25  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_25,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_26  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_26,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_27  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_27,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_28  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_28,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_29  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_29,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_30  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_30,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_31  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_31,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_32  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_32,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_33  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_33,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_34  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_34,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_35  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_35,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_36  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_36,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_37  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_37,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_38  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_38,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_39  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_39,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_40  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_40,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_41  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_41,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_42  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_42,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_43  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_43,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_44  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_44,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_45  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_45,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_46  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_46,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_47  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_47,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_48  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_48,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_49  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_49,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_50  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_50,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_51  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_51,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_52  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_52,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_53  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_53,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_54  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_54,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_55  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_55,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_56  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_56,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_57  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_57,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_58  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_58,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_59  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_59,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_60  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_60,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_61  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_61,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_62  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_62,    /* CH4 */
    RSCFD_TX_DST_BUFF_4_63  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_4_63,    /* CH4 */

    RSCFD_TX_DST_BUFF_5_0   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_0,     /* CH5 */
    RSCFD_TX_DST_BUFF_5_1   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_1,     /* CH5 */
    RSCFD_TX_DST_BUFF_5_2   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_2,     /* CH5 */
    RSCFD_TX_DST_BUFF_5_3   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_3,     /* CH5 */
    RSCFD_TX_DST_BUFF_5_4   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_4,     /* CH5 */
    RSCFD_TX_DST_BUFF_5_5   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_5,     /* CH5 */
    RSCFD_TX_DST_BUFF_5_6   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_6,     /* CH5 */
    RSCFD_TX_DST_BUFF_5_7   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_7,     /* CH5 */
    RSCFD_TX_DST_BUFF_5_8   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_8,     /* CH5 */
    RSCFD_TX_DST_BUFF_5_9   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_9,     /* CH5 */
    RSCFD_TX_DST_BUFF_5_10  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_10,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_11  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_11,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_12  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_12,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_13  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_13,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_14  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_14,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_15  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_15,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_16  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_16,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_17  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_17,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_18  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_18,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_19  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_19,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_20  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_20,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_21  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_21,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_22  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_22,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_23  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_23,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_24  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_24,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_25  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_25,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_26  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_26,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_27  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_27,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_28  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_28,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_29  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_29,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_30  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_30,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_31  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_31,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_32  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_32,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_33  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_33,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_34  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_34,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_35  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_35,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_36  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_36,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_37  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_37,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_38  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_38,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_39  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_39,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_40  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_40,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_41  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_41,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_42  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_42,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_43  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_43,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_44  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_44,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_45  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_45,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_46  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_46,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_47  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_47,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_48  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_48,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_49  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_49,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_50  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_50,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_51  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_51,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_52  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_52,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_53  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_53,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_54  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_54,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_55  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_55,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_56  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_56,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_57  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_57,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_58  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_58,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_59  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_59,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_60  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_60,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_61  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_61,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_62  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_62,    /* CH5 */
    RSCFD_TX_DST_BUFF_5_63  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_5_63,    /* CH5 */

    RSCFD_TX_DST_BUFF_6_0   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_0,     /* CH6 */
    RSCFD_TX_DST_BUFF_6_1   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_1,     /* CH6 */
    RSCFD_TX_DST_BUFF_6_2   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_2,     /* CH6 */
    RSCFD_TX_DST_BUFF_6_3   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_3,     /* CH6 */
    RSCFD_TX_DST_BUFF_6_4   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_4,     /* CH6 */
    RSCFD_TX_DST_BUFF_6_5   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_5,     /* CH6 */
    RSCFD_TX_DST_BUFF_6_6   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_6,     /* CH6 */
    RSCFD_TX_DST_BUFF_6_7   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_7,     /* CH6 */
    RSCFD_TX_DST_BUFF_6_8   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_8,     /* CH6 */
    RSCFD_TX_DST_BUFF_6_9   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_9,     /* CH6 */
    RSCFD_TX_DST_BUFF_6_10  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_10,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_11  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_11,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_12  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_12,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_13  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_13,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_14  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_14,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_15  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_15,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_16  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_16,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_17  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_17,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_18  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_18,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_19  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_19,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_20  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_20,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_21  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_21,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_22  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_22,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_23  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_23,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_24  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_24,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_25  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_25,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_26  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_26,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_27  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_27,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_28  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_28,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_29  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_29,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_30  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_30,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_31  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_31,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_32  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_32,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_33  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_33,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_34  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_34,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_35  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_35,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_36  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_36,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_37  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_37,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_38  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_38,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_39  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_39,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_40  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_40,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_41  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_41,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_42  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_42,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_43  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_43,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_44  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_44,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_45  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_45,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_46  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_46,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_47  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_47,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_48  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_48,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_49  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_49,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_50  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_50,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_51  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_51,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_52  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_52,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_53  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_53,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_54  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_54,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_55  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_55,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_56  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_56,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_57  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_57,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_58  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_58,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_59  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_59,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_60  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_60,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_61  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_61,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_62  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_62,    /* CH6 */
    RSCFD_TX_DST_BUFF_6_63  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_6_63,    /* CH6 */

    RSCFD_TX_DST_BUFF_7_0   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_0,     /* CH7 */
    RSCFD_TX_DST_BUFF_7_1   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_1,     /* CH7 */
    RSCFD_TX_DST_BUFF_7_2   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_2,     /* CH7 */
    RSCFD_TX_DST_BUFF_7_3   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_3,     /* CH7 */
    RSCFD_TX_DST_BUFF_7_4   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_4,     /* CH7 */
    RSCFD_TX_DST_BUFF_7_5   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_5,     /* CH7 */
    RSCFD_TX_DST_BUFF_7_6   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_6,     /* CH7 */
    RSCFD_TX_DST_BUFF_7_7   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_7,     /* CH7 */
    RSCFD_TX_DST_BUFF_7_8   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_8,     /* CH7 */
    RSCFD_TX_DST_BUFF_7_9   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_9,     /* CH7 */
    RSCFD_TX_DST_BUFF_7_10  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_10,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_11  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_11,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_12  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_12,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_13  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_13,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_14  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_14,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_15  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_15,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_16  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_16,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_17  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_17,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_18  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_18,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_19  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_19,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_20  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_20,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_21  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_21,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_22  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_22,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_23  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_23,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_24  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_24,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_25  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_25,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_26  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_26,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_27  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_27,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_28  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_28,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_29  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_29,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_30  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_30,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_31  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_31,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_32  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_32,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_33  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_33,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_34  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_34,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_35  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_35,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_36  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_36,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_37  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_37,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_38  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_38,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_39  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_39,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_40  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_40,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_41  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_41,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_42  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_42,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_43  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_43,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_44  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_44,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_45  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_45,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_46  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_46,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_47  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_47,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_48  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_48,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_49  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_49,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_50  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_50,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_51  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_51,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_52  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_52,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_53  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_53,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_54  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_54,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_55  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_55,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_56  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_56,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_57  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_57,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_58  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_58,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_59  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_59,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_60  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_60,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_61  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_61,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_62  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_62,    /* CH7 */
    RSCFD_TX_DST_BUFF_7_63  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_7_63,    /* CH7 */

    /* Unit 1 Tx Buffer */
    RSCFD_TX_DST_BUFF_8_0   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_0,     /* CH8 */
    RSCFD_TX_DST_BUFF_8_1   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_1,     /* CH8 */
    RSCFD_TX_DST_BUFF_8_2   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_2,     /* CH8 */
    RSCFD_TX_DST_BUFF_8_3   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_3,     /* CH8 */
    RSCFD_TX_DST_BUFF_8_4   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_4,     /* CH8 */
    RSCFD_TX_DST_BUFF_8_5   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_5,     /* CH8 */
    RSCFD_TX_DST_BUFF_8_6   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_6,     /* CH8 */
    RSCFD_TX_DST_BUFF_8_7   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_7,     /* CH8 */
    RSCFD_TX_DST_BUFF_8_8   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_8,     /* CH8 */
    RSCFD_TX_DST_BUFF_8_9   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_9,     /* CH8 */
    RSCFD_TX_DST_BUFF_8_10  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_10,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_11  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_11,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_12  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_12,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_13  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_13,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_14  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_14,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_15  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_15,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_16  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_16,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_17  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_17,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_18  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_18,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_19  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_19,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_20  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_20,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_21  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_21,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_22  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_22,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_23  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_23,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_24  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_24,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_25  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_25,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_26  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_26,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_27  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_27,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_28  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_28,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_29  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_29,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_30  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_30,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_31  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_31,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_32  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_32,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_33  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_33,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_34  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_34,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_35  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_35,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_36  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_36,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_37  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_37,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_38  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_38,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_39  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_39,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_40  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_40,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_41  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_41,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_42  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_42,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_43  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_43,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_44  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_44,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_45  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_45,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_46  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_46,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_47  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_47,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_48  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_48,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_49  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_49,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_50  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_50,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_51  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_51,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_52  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_52,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_53  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_53,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_54  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_54,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_55  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_55,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_56  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_56,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_57  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_57,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_58  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_58,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_59  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_59,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_60  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_60,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_61  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_61,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_62  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_62,    /* CH8 */
    RSCFD_TX_DST_BUFF_8_63  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_8_63,    /* CH8 */

    RSCFD_TX_DST_BUFF_9_0   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_0,     /* CH9 */
    RSCFD_TX_DST_BUFF_9_1   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_1,     /* CH9 */
    RSCFD_TX_DST_BUFF_9_2   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_2,     /* CH9 */
    RSCFD_TX_DST_BUFF_9_3   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_3,     /* CH9 */
    RSCFD_TX_DST_BUFF_9_4   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_4,     /* CH9 */
    RSCFD_TX_DST_BUFF_9_5   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_5,     /* CH9 */
    RSCFD_TX_DST_BUFF_9_6   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_6,     /* CH9 */
    RSCFD_TX_DST_BUFF_9_7   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_7,     /* CH9 */
    RSCFD_TX_DST_BUFF_9_8   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_8,     /* CH9 */
    RSCFD_TX_DST_BUFF_9_9   = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_9,     /* CH9 */
    RSCFD_TX_DST_BUFF_9_10  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_10,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_11  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_11,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_12  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_12,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_13  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_13,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_14  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_14,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_15  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_15,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_16  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_16,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_17  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_17,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_18  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_18,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_19  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_19,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_20  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_20,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_21  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_21,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_22  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_22,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_23  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_23,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_24  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_24,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_25  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_25,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_26  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_26,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_27  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_27,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_28  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_28,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_29  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_29,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_30  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_30,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_31  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_31,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_32  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_32,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_33  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_33,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_34  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_34,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_35  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_35,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_36  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_36,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_37  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_37,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_38  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_38,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_39  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_39,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_40  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_40,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_41  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_41,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_42  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_42,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_43  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_43,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_44  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_44,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_45  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_45,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_46  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_46,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_47  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_47,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_48  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_48,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_49  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_49,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_50  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_50,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_51  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_51,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_52  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_52,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_53  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_53,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_54  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_54,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_55  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_55,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_56  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_56,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_57  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_57,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_58  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_58,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_59  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_59,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_60  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_60,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_61  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_61,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_62  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_62,    /* CH9 */
    RSCFD_TX_DST_BUFF_9_63  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_9_63,    /* CH9 */

    RSCFD_TX_DST_BUFF_10_0  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_0,    /* CH10 */
    RSCFD_TX_DST_BUFF_10_1  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_1,    /* CH10 */
    RSCFD_TX_DST_BUFF_10_2  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_2,    /* CH10 */
    RSCFD_TX_DST_BUFF_10_3  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_3,    /* CH10 */
    RSCFD_TX_DST_BUFF_10_4  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_4,    /* CH10 */
    RSCFD_TX_DST_BUFF_10_5  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_5,    /* CH10 */
    RSCFD_TX_DST_BUFF_10_6  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_6,    /* CH10 */
    RSCFD_TX_DST_BUFF_10_7  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_7,    /* CH10 */
    RSCFD_TX_DST_BUFF_10_8  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_8,    /* CH10 */
    RSCFD_TX_DST_BUFF_10_9  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_9,    /* CH10 */
    RSCFD_TX_DST_BUFF_10_10 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_10,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_11 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_11,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_12 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_12,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_13 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_13,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_14 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_14,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_15 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_15,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_16 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_16,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_17 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_17,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_18 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_18,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_19 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_19,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_20 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_20,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_21 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_21,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_22 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_22,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_23 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_23,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_24 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_24,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_25 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_25,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_26 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_26,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_27 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_27,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_28 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_28,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_29 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_29,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_30 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_30,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_31 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_31,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_32 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_32,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_33 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_33,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_34 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_34,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_35 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_35,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_36 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_36,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_37 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_37,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_38 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_38,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_39 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_39,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_40 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_40,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_41 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_41,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_42 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_42,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_43 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_43,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_44 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_44,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_45 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_45,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_46 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_46,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_47 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_47,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_48 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_48,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_49 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_49,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_50 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_50,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_51 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_51,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_52 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_52,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_53 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_53,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_54 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_54,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_55 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_55,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_56 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_56,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_57 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_57,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_58 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_58,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_59 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_59,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_60 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_60,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_61 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_61,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_62 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_62,   /* CH10 */
    RSCFD_TX_DST_BUFF_10_63 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_10_63,   /* CH10 */

    RSCFD_TX_DST_BUFF_11_0  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_0,    /* CH11 */
    RSCFD_TX_DST_BUFF_11_1  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_1,    /* CH11 */
    RSCFD_TX_DST_BUFF_11_2  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_2,    /* CH11 */
    RSCFD_TX_DST_BUFF_11_3  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_3,    /* CH11 */
    RSCFD_TX_DST_BUFF_11_4  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_4,    /* CH11 */
    RSCFD_TX_DST_BUFF_11_5  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_5,    /* CH11 */
    RSCFD_TX_DST_BUFF_11_6  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_6,    /* CH11 */
    RSCFD_TX_DST_BUFF_11_7  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_7,    /* CH11 */
    RSCFD_TX_DST_BUFF_11_8  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_8,    /* CH11 */
    RSCFD_TX_DST_BUFF_11_9  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_9,    /* CH11 */
    RSCFD_TX_DST_BUFF_11_10 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_10,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_11 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_11,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_12 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_12,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_13 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_13,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_14 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_14,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_15 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_15,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_16 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_16,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_17 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_17,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_18 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_18,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_19 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_19,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_20 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_20,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_21 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_21,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_22 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_22,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_23 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_23,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_24 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_24,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_25 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_25,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_26 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_26,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_27 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_27,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_28 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_28,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_29 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_29,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_30 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_30,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_31 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_31,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_32 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_32,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_33 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_33,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_34 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_34,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_35 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_35,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_36 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_36,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_37 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_37,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_38 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_38,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_39 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_39,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_40 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_40,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_41 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_41,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_42 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_42,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_43 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_43,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_44 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_44,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_45 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_45,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_46 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_46,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_47 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_47,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_48 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_48,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_49 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_49,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_50 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_50,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_51 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_51,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_52 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_52,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_53 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_53,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_54 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_54,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_55 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_55,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_56 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_56,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_57 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_57,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_58 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_58,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_59 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_59,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_60 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_60,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_61 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_61,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_62 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_62,   /* CH11 */
    RSCFD_TX_DST_BUFF_11_63 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_11_63,   /* CH11 */

    RSCFD_TX_DST_BUFF_12_0  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_0,    /* CH12 */
    RSCFD_TX_DST_BUFF_12_1  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_1,    /* CH12 */
    RSCFD_TX_DST_BUFF_12_2  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_2,    /* CH12 */
    RSCFD_TX_DST_BUFF_12_3  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_3,    /* CH12 */
    RSCFD_TX_DST_BUFF_12_4  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_4,    /* CH12 */
    RSCFD_TX_DST_BUFF_12_5  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_5,    /* CH12 */
    RSCFD_TX_DST_BUFF_12_6  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_6,    /* CH12 */
    RSCFD_TX_DST_BUFF_12_7  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_7,    /* CH12 */
    RSCFD_TX_DST_BUFF_12_8  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_8,    /* CH12 */
    RSCFD_TX_DST_BUFF_12_9  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_9,    /* CH12 */
    RSCFD_TX_DST_BUFF_12_10 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_10,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_11 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_11,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_12 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_12,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_13 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_13,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_14 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_14,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_15 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_15,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_16 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_16,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_17 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_17,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_18 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_18,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_19 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_19,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_20 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_20,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_21 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_21,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_22 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_22,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_23 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_23,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_24 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_24,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_25 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_25,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_26 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_26,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_27 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_27,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_28 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_28,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_29 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_29,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_30 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_30,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_31 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_31,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_32 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_32,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_33 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_33,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_34 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_34,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_35 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_35,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_36 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_36,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_37 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_37,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_38 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_38,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_39 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_39,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_40 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_40,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_41 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_41,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_42 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_42,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_43 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_43,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_44 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_44,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_45 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_45,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_46 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_46,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_47 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_47,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_48 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_48,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_49 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_49,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_50 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_50,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_51 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_51,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_52 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_52,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_53 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_53,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_54 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_54,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_55 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_55,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_56 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_56,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_57 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_57,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_58 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_58,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_59 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_59,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_60 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_60,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_61 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_61,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_62 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_62,   /* CH12 */
    RSCFD_TX_DST_BUFF_12_63 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_12_63,   /* CH12 */

    RSCFD_TX_DST_BUFF_13_0  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_0,    /* CH13 */
    RSCFD_TX_DST_BUFF_13_1  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_1,    /* CH13 */
    RSCFD_TX_DST_BUFF_13_2  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_2,    /* CH13 */
    RSCFD_TX_DST_BUFF_13_3  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_3,    /* CH13 */
    RSCFD_TX_DST_BUFF_13_4  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_4,    /* CH13 */
    RSCFD_TX_DST_BUFF_13_5  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_5,    /* CH13 */
    RSCFD_TX_DST_BUFF_13_6  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_6,    /* CH13 */
    RSCFD_TX_DST_BUFF_13_7  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_7,    /* CH13 */
    RSCFD_TX_DST_BUFF_13_8  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_8,    /* CH13 */
    RSCFD_TX_DST_BUFF_13_9  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_9,    /* CH13 */
    RSCFD_TX_DST_BUFF_13_10 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_10,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_11 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_11,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_12 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_12,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_13 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_13,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_14 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_14,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_15 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_15,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_16 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_16,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_17 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_17,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_18 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_18,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_19 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_19,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_20 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_20,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_21 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_21,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_22 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_22,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_23 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_23,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_24 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_24,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_25 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_25,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_26 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_26,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_27 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_27,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_28 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_28,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_29 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_29,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_30 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_30,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_31 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_31,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_32 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_32,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_33 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_33,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_34 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_34,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_35 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_35,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_36 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_36,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_37 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_37,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_38 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_38,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_39 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_39,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_40 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_40,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_41 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_41,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_42 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_42,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_43 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_43,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_44 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_44,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_45 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_45,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_46 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_46,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_47 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_47,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_48 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_48,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_49 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_49,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_50 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_50,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_51 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_51,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_52 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_52,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_53 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_53,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_54 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_54,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_55 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_55,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_56 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_56,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_57 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_57,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_58 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_58,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_59 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_59,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_60 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_60,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_61 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_61,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_62 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_62,   /* CH13 */
    RSCFD_TX_DST_BUFF_13_63 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_13_63,   /* CH13 */

    RSCFD_TX_DST_BUFF_14_0  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_0,    /* CH14 */
    RSCFD_TX_DST_BUFF_14_1  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_1,    /* CH14 */
    RSCFD_TX_DST_BUFF_14_2  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_2,    /* CH14 */
    RSCFD_TX_DST_BUFF_14_3  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_3,    /* CH14 */
    RSCFD_TX_DST_BUFF_14_4  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_4,    /* CH14 */
    RSCFD_TX_DST_BUFF_14_5  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_5,    /* CH14 */
    RSCFD_TX_DST_BUFF_14_6  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_6,    /* CH14 */
    RSCFD_TX_DST_BUFF_14_7  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_7,    /* CH14 */
    RSCFD_TX_DST_BUFF_14_8  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_8,    /* CH14 */
    RSCFD_TX_DST_BUFF_14_9  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_9,    /* CH14 */
    RSCFD_TX_DST_BUFF_14_10 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_10,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_11 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_11,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_12 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_12,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_13 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_13,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_14 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_14,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_15 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_15,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_16 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_16,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_17 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_17,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_18 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_18,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_19 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_19,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_20 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_20,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_21 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_21,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_22 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_22,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_23 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_23,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_24 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_24,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_25 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_25,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_26 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_26,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_27 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_27,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_28 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_28,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_29 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_29,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_30 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_30,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_31 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_31,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_32 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_32,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_33 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_33,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_34 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_34,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_35 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_35,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_36 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_36,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_37 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_37,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_38 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_38,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_39 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_39,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_40 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_40,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_41 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_41,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_42 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_42,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_43 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_43,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_44 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_44,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_45 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_45,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_46 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_46,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_47 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_47,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_48 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_48,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_49 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_49,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_50 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_50,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_51 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_51,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_52 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_52,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_53 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_53,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_54 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_54,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_55 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_55,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_56 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_56,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_57 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_57,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_58 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_58,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_59 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_59,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_60 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_60,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_61 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_61,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_62 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_62,   /* CH14 */
    RSCFD_TX_DST_BUFF_14_63 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_14_63,   /* CH14 */

    RSCFD_TX_DST_BUFF_15_0  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_0,    /* CH15 */
    RSCFD_TX_DST_BUFF_15_1  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_1,    /* CH15 */
    RSCFD_TX_DST_BUFF_15_2  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_2,    /* CH15 */
    RSCFD_TX_DST_BUFF_15_3  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_3,    /* CH15 */
    RSCFD_TX_DST_BUFF_15_4  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_4,    /* CH15 */
    RSCFD_TX_DST_BUFF_15_5  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_5,    /* CH15 */
    RSCFD_TX_DST_BUFF_15_6  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_6,    /* CH15 */
    RSCFD_TX_DST_BUFF_15_7  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_7,    /* CH15 */
    RSCFD_TX_DST_BUFF_15_8  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_8,    /* CH15 */
    RSCFD_TX_DST_BUFF_15_9  = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_9,    /* CH15 */
    RSCFD_TX_DST_BUFF_15_10 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_10,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_11 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_11,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_12 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_12,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_13 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_13,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_14 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_14,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_15 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_15,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_16 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_16,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_17 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_17,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_18 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_18,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_19 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_19,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_20 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_20,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_21 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_21,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_22 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_22,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_23 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_23,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_24 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_24,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_25 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_25,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_26 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_26,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_27 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_27,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_28 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_28,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_29 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_29,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_30 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_30,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_31 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_31,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_32 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_32,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_33 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_33,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_34 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_34,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_35 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_35,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_36 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_36,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_37 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_37,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_38 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_38,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_39 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_39,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_40 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_40,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_41 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_41,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_42 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_42,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_43 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_43,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_44 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_44,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_45 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_45,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_46 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_46,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_47 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_47,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_48 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_48,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_49 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_49,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_50 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_50,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_51 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_51,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_52 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_52,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_53 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_53,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_54 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_54,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_55 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_55,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_56 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_56,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_57 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_57,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_58 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_58,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_59 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_59,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_60 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_60,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_61 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_61,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_62 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_62,   /* CH15 */
    RSCFD_TX_DST_BUFF_15_63 = RSCFD_TX_BUFF | RSCFD_TX_BUFF_15_63    /* CH15 */
}   rscfd_tx_dst_t;

/*******************************************************************************
 * Rx Rule number (as many as 384 rules/channel are possible)
 * Rx Rules configured per page (16 rules / page).
 *******************************************************************************/
typedef enum
{
    RSCFD_RX_RULE_0  = 0,
    RSCFD_RX_RULE_1  = 1,
    RSCFD_RX_RULE_2  = 2,
    RSCFD_RX_RULE_3  = 3,
    RSCFD_RX_RULE_4  = 4,
    RSCFD_RX_RULE_5  = 5,
    RSCFD_RX_RULE_6  = 6,
    RSCFD_RX_RULE_7  = 7,
    RSCFD_RX_RULE_8  = 8,
    RSCFD_RX_RULE_9  = 9,
    RSCFD_RX_RULE_10 = 10,
    RSCFD_RX_RULE_11 = 11,
    RSCFD_RX_RULE_12 = 12,
    RSCFD_RX_RULE_13 = 13,
    RSCFD_RX_RULE_14 = 14,
    RSCFD_RX_RULE_15 = 15
}   rscfd_rx_rule_t;

/*******************************************************************************
 * Valid Receive Rule Table Page Numbers and RSCFD units
 * Configured in register RSCFDnCFDGAFLECTR bit field AFLPN.
 * Enumeration corresponds to bit field position within register.
 *******************************************************************************/
typedef enum
{
    RSCFD_RX_PAGE_0_0  = (RSCFD_UNIT_0 << 24) | 0,
    RSCFD_RX_PAGE_0_1  = (RSCFD_UNIT_0 << 24) | 1,
    RSCFD_RX_PAGE_0_2  = (RSCFD_UNIT_0 << 24) | 2,
    RSCFD_RX_PAGE_0_3  = (RSCFD_UNIT_0 << 24) | 3,
    RSCFD_RX_PAGE_0_4  = (RSCFD_UNIT_0 << 24) | 4,
    RSCFD_RX_PAGE_0_5  = (RSCFD_UNIT_0 << 24) | 5,
    RSCFD_RX_PAGE_0_6  = (RSCFD_UNIT_0 << 24) | 6,
    RSCFD_RX_PAGE_0_7  = (RSCFD_UNIT_0 << 24) | 7,
    RSCFD_RX_PAGE_0_8  = (RSCFD_UNIT_0 << 24) | 8,
    RSCFD_RX_PAGE_0_9  = (RSCFD_UNIT_0 << 24) | 9,
    RSCFD_RX_PAGE_0_10 = (RSCFD_UNIT_0 << 24) | 10,
    RSCFD_RX_PAGE_0_11 = (RSCFD_UNIT_0 << 24) | 11,
    RSCFD_RX_PAGE_0_12 = (RSCFD_UNIT_0 << 24) | 12,
    RSCFD_RX_PAGE_0_13 = (RSCFD_UNIT_0 << 24) | 13,
    RSCFD_RX_PAGE_0_14 = (RSCFD_UNIT_0 << 24) | 14,
    RSCFD_RX_PAGE_0_15 = (RSCFD_UNIT_0 << 24) | 15,
    RSCFD_RX_PAGE_0_16 = (RSCFD_UNIT_0 << 24) | 16,
    RSCFD_RX_PAGE_0_17 = (RSCFD_UNIT_0 << 24) | 17,
    RSCFD_RX_PAGE_0_18 = (RSCFD_UNIT_0 << 24) | 18,
    RSCFD_RX_PAGE_0_19 = (RSCFD_UNIT_0 << 24) | 19,
    RSCFD_RX_PAGE_0_20 = (RSCFD_UNIT_0 << 24) | 20,
    RSCFD_RX_PAGE_0_21 = (RSCFD_UNIT_0 << 24) | 21,
    RSCFD_RX_PAGE_0_22 = (RSCFD_UNIT_0 << 24) | 22,
    RSCFD_RX_PAGE_0_23 = (RSCFD_UNIT_0 << 24) | 23,
    RSCFD_RX_PAGE_0_24 = (RSCFD_UNIT_0 << 24) | 24,
    RSCFD_RX_PAGE_0_25 = (RSCFD_UNIT_0 << 24) | 25,
    RSCFD_RX_PAGE_0_26 = (RSCFD_UNIT_0 << 24) | 26,
    RSCFD_RX_PAGE_0_27 = (RSCFD_UNIT_0 << 24) | 27,
    RSCFD_RX_PAGE_0_28 = (RSCFD_UNIT_0 << 24) | 28,
    RSCFD_RX_PAGE_0_29 = (RSCFD_UNIT_0 << 24) | 29,
    RSCFD_RX_PAGE_0_30 = (RSCFD_UNIT_0 << 24) | 30,
    RSCFD_RX_PAGE_0_31 = (RSCFD_UNIT_0 << 24) | 31,
    RSCFD_RX_PAGE_0_32 = (RSCFD_UNIT_0 << 24) | 32,
    RSCFD_RX_PAGE_0_33 = (RSCFD_UNIT_0 << 24) | 33,
    RSCFD_RX_PAGE_0_34 = (RSCFD_UNIT_0 << 24) | 34,
    RSCFD_RX_PAGE_0_35 = (RSCFD_UNIT_0 << 24) | 35,
    RSCFD_RX_PAGE_0_36 = (RSCFD_UNIT_0 << 24) | 36,
    RSCFD_RX_PAGE_0_37 = (RSCFD_UNIT_0 << 24) | 37,
    RSCFD_RX_PAGE_0_38 = (RSCFD_UNIT_0 << 24) | 38,
    RSCFD_RX_PAGE_0_39 = (RSCFD_UNIT_0 << 24) | 39,
    RSCFD_RX_PAGE_0_40 = (RSCFD_UNIT_0 << 24) | 40,
    RSCFD_RX_PAGE_0_41 = (RSCFD_UNIT_0 << 24) | 41,
    RSCFD_RX_PAGE_0_42 = (RSCFD_UNIT_0 << 24) | 42,
    RSCFD_RX_PAGE_0_43 = (RSCFD_UNIT_0 << 24) | 43,
    RSCFD_RX_PAGE_0_44 = (RSCFD_UNIT_0 << 24) | 44,
    RSCFD_RX_PAGE_0_45 = (RSCFD_UNIT_0 << 24) | 45,
    RSCFD_RX_PAGE_0_46 = (RSCFD_UNIT_0 << 24) | 46,
    RSCFD_RX_PAGE_0_47 = (RSCFD_UNIT_0 << 24) | 47,
    RSCFD_RX_PAGE_0_48 = (RSCFD_UNIT_0 << 24) | 48,
    RSCFD_RX_PAGE_0_49 = (RSCFD_UNIT_0 << 24) | 49,
    RSCFD_RX_PAGE_0_50 = (RSCFD_UNIT_0 << 24) | 50,
    RSCFD_RX_PAGE_0_51 = (RSCFD_UNIT_0 << 24) | 51,
    RSCFD_RX_PAGE_0_52 = (RSCFD_UNIT_0 << 24) | 52,
    RSCFD_RX_PAGE_0_53 = (RSCFD_UNIT_0 << 24) | 53,
    RSCFD_RX_PAGE_0_54 = (RSCFD_UNIT_0 << 24) | 54,
    RSCFD_RX_PAGE_0_55 = (RSCFD_UNIT_0 << 24) | 55,
    RSCFD_RX_PAGE_0_56 = (RSCFD_UNIT_0 << 24) | 56,
    RSCFD_RX_PAGE_0_57 = (RSCFD_UNIT_0 << 24) | 57,
    RSCFD_RX_PAGE_0_58 = (RSCFD_UNIT_0 << 24) | 58,
    RSCFD_RX_PAGE_0_59 = (RSCFD_UNIT_0 << 24) | 59,
    RSCFD_RX_PAGE_0_60 = (RSCFD_UNIT_0 << 24) | 60,
    RSCFD_RX_PAGE_0_61 = (RSCFD_UNIT_0 << 24) | 61,
    RSCFD_RX_PAGE_0_62 = (RSCFD_UNIT_0 << 24) | 62,
    RSCFD_RX_PAGE_0_63 = (RSCFD_UNIT_0 << 24) | 63,
    RSCFD_RX_PAGE_0_64 = (RSCFD_UNIT_0 << 24) | 64,
    RSCFD_RX_PAGE_0_65 = (RSCFD_UNIT_0 << 24) | 65,
    RSCFD_RX_PAGE_0_66 = (RSCFD_UNIT_0 << 24) | 66,
    RSCFD_RX_PAGE_0_67 = (RSCFD_UNIT_0 << 24) | 67,
    RSCFD_RX_PAGE_0_68 = (RSCFD_UNIT_0 << 24) | 68,
    RSCFD_RX_PAGE_0_69 = (RSCFD_UNIT_0 << 24) | 69,
    RSCFD_RX_PAGE_0_70 = (RSCFD_UNIT_0 << 24) | 70,
    RSCFD_RX_PAGE_0_71 = (RSCFD_UNIT_0 << 24) | 71,
    RSCFD_RX_PAGE_0_72 = (RSCFD_UNIT_0 << 24) | 72,
    RSCFD_RX_PAGE_0_73 = (RSCFD_UNIT_0 << 24) | 73,
    RSCFD_RX_PAGE_0_74 = (RSCFD_UNIT_0 << 24) | 74,
    RSCFD_RX_PAGE_0_75 = (RSCFD_UNIT_0 << 24) | 75,
    RSCFD_RX_PAGE_0_76 = (RSCFD_UNIT_0 << 24) | 76,
    RSCFD_RX_PAGE_0_77 = (RSCFD_UNIT_0 << 24) | 77,
    RSCFD_RX_PAGE_0_78 = (RSCFD_UNIT_0 << 24) | 78,
    RSCFD_RX_PAGE_0_79 = (RSCFD_UNIT_0 << 24) | 79,
    RSCFD_RX_PAGE_0_80 = (RSCFD_UNIT_0 << 24) | 80,
    RSCFD_RX_PAGE_0_81 = (RSCFD_UNIT_0 << 24) | 81,
    RSCFD_RX_PAGE_0_82 = (RSCFD_UNIT_0 << 24) | 82,
    RSCFD_RX_PAGE_0_83 = (RSCFD_UNIT_0 << 24) | 83,
    RSCFD_RX_PAGE_0_84 = (RSCFD_UNIT_0 << 24) | 84,
    RSCFD_RX_PAGE_0_85 = (RSCFD_UNIT_0 << 24) | 85,
    RSCFD_RX_PAGE_0_86 = (RSCFD_UNIT_0 << 24) | 86,
    RSCFD_RX_PAGE_0_87 = (RSCFD_UNIT_0 << 24) | 87,
    RSCFD_RX_PAGE_0_88 = (RSCFD_UNIT_0 << 24) | 88,
    RSCFD_RX_PAGE_0_89 = (RSCFD_UNIT_0 << 24) | 89,
    RSCFD_RX_PAGE_0_90 = (RSCFD_UNIT_0 << 24) | 90,
    RSCFD_RX_PAGE_0_91 = (RSCFD_UNIT_0 << 24) | 91,
    RSCFD_RX_PAGE_0_92 = (RSCFD_UNIT_0 << 24) | 92,
    RSCFD_RX_PAGE_0_93 = (RSCFD_UNIT_0 << 24) | 93,
    RSCFD_RX_PAGE_0_94 = (RSCFD_UNIT_0 << 24) | 94,
    RSCFD_RX_PAGE_0_95 = (RSCFD_UNIT_0 << 24) | 95,

    RSCFD_RX_PAGE_1_0  = (RSCFD_UNIT_1 << 24) | 0,
    RSCFD_RX_PAGE_1_1  = (RSCFD_UNIT_1 << 24) | 1,
    RSCFD_RX_PAGE_1_2  = (RSCFD_UNIT_1 << 24) | 2,
    RSCFD_RX_PAGE_1_3  = (RSCFD_UNIT_1 << 24) | 3,
    RSCFD_RX_PAGE_1_4  = (RSCFD_UNIT_1 << 24) | 4,
    RSCFD_RX_PAGE_1_5  = (RSCFD_UNIT_1 << 24) | 5,
    RSCFD_RX_PAGE_1_6  = (RSCFD_UNIT_1 << 24) | 6,
    RSCFD_RX_PAGE_1_7  = (RSCFD_UNIT_1 << 24) | 7,
    RSCFD_RX_PAGE_1_8  = (RSCFD_UNIT_1 << 24) | 8,
    RSCFD_RX_PAGE_1_9  = (RSCFD_UNIT_1 << 24) | 9,
    RSCFD_RX_PAGE_1_10 = (RSCFD_UNIT_1 << 24) | 10,
    RSCFD_RX_PAGE_1_11 = (RSCFD_UNIT_1 << 24) | 11,
    RSCFD_RX_PAGE_1_12 = (RSCFD_UNIT_1 << 24) | 12,
    RSCFD_RX_PAGE_1_13 = (RSCFD_UNIT_1 << 24) | 13,
    RSCFD_RX_PAGE_1_14 = (RSCFD_UNIT_1 << 24) | 14,
    RSCFD_RX_PAGE_1_15 = (RSCFD_UNIT_1 << 24) | 15,
    RSCFD_RX_PAGE_1_16 = (RSCFD_UNIT_1 << 24) | 16,
    RSCFD_RX_PAGE_1_17 = (RSCFD_UNIT_1 << 24) | 17,
    RSCFD_RX_PAGE_1_18 = (RSCFD_UNIT_1 << 24) | 18,
    RSCFD_RX_PAGE_1_19 = (RSCFD_UNIT_1 << 24) | 19,
    RSCFD_RX_PAGE_1_20 = (RSCFD_UNIT_1 << 24) | 20,
    RSCFD_RX_PAGE_1_21 = (RSCFD_UNIT_1 << 24) | 21,
    RSCFD_RX_PAGE_1_22 = (RSCFD_UNIT_1 << 24) | 22,
    RSCFD_RX_PAGE_1_23 = (RSCFD_UNIT_1 << 24) | 23,
    RSCFD_RX_PAGE_1_24 = (RSCFD_UNIT_1 << 24) | 24,
    RSCFD_RX_PAGE_1_25 = (RSCFD_UNIT_1 << 24) | 25,
    RSCFD_RX_PAGE_1_26 = (RSCFD_UNIT_1 << 24) | 26,
    RSCFD_RX_PAGE_1_27 = (RSCFD_UNIT_1 << 24) | 27,
    RSCFD_RX_PAGE_1_28 = (RSCFD_UNIT_1 << 24) | 28,
    RSCFD_RX_PAGE_1_29 = (RSCFD_UNIT_1 << 24) | 29,
    RSCFD_RX_PAGE_1_30 = (RSCFD_UNIT_1 << 24) | 30,
    RSCFD_RX_PAGE_1_31 = (RSCFD_UNIT_1 << 24) | 31,
    RSCFD_RX_PAGE_1_32 = (RSCFD_UNIT_1 << 24) | 32,
    RSCFD_RX_PAGE_1_33 = (RSCFD_UNIT_1 << 24) | 33,
    RSCFD_RX_PAGE_1_34 = (RSCFD_UNIT_1 << 24) | 34,
    RSCFD_RX_PAGE_1_35 = (RSCFD_UNIT_1 << 24) | 35,
    RSCFD_RX_PAGE_1_36 = (RSCFD_UNIT_1 << 24) | 36,
    RSCFD_RX_PAGE_1_37 = (RSCFD_UNIT_1 << 24) | 37,
    RSCFD_RX_PAGE_1_38 = (RSCFD_UNIT_1 << 24) | 38,
    RSCFD_RX_PAGE_1_39 = (RSCFD_UNIT_1 << 24) | 39,
    RSCFD_RX_PAGE_1_40 = (RSCFD_UNIT_1 << 24) | 40,
    RSCFD_RX_PAGE_1_41 = (RSCFD_UNIT_1 << 24) | 41,
    RSCFD_RX_PAGE_1_42 = (RSCFD_UNIT_1 << 24) | 42,
    RSCFD_RX_PAGE_1_43 = (RSCFD_UNIT_1 << 24) | 43,
    RSCFD_RX_PAGE_1_44 = (RSCFD_UNIT_1 << 24) | 44,
    RSCFD_RX_PAGE_1_45 = (RSCFD_UNIT_1 << 24) | 45,
    RSCFD_RX_PAGE_1_46 = (RSCFD_UNIT_1 << 24) | 46,
    RSCFD_RX_PAGE_1_47 = (RSCFD_UNIT_1 << 24) | 47,
    RSCFD_RX_PAGE_1_48 = (RSCFD_UNIT_1 << 24) | 48,
    RSCFD_RX_PAGE_1_49 = (RSCFD_UNIT_1 << 24) | 49,
    RSCFD_RX_PAGE_1_50 = (RSCFD_UNIT_1 << 24) | 50,
    RSCFD_RX_PAGE_1_51 = (RSCFD_UNIT_1 << 24) | 51,
    RSCFD_RX_PAGE_1_52 = (RSCFD_UNIT_1 << 24) | 52,
    RSCFD_RX_PAGE_1_53 = (RSCFD_UNIT_1 << 24) | 53,
    RSCFD_RX_PAGE_1_54 = (RSCFD_UNIT_1 << 24) | 54,
    RSCFD_RX_PAGE_1_55 = (RSCFD_UNIT_1 << 24) | 55,
    RSCFD_RX_PAGE_1_56 = (RSCFD_UNIT_1 << 24) | 56,
    RSCFD_RX_PAGE_1_57 = (RSCFD_UNIT_1 << 24) | 57,
    RSCFD_RX_PAGE_1_58 = (RSCFD_UNIT_1 << 24) | 58,
    RSCFD_RX_PAGE_1_59 = (RSCFD_UNIT_1 << 24) | 59,
    RSCFD_RX_PAGE_1_60 = (RSCFD_UNIT_1 << 24) | 60,
    RSCFD_RX_PAGE_1_61 = (RSCFD_UNIT_1 << 24) | 61,
    RSCFD_RX_PAGE_1_62 = (RSCFD_UNIT_1 << 24) | 62,
    RSCFD_RX_PAGE_1_63 = (RSCFD_UNIT_1 << 24) | 63,
    RSCFD_RX_PAGE_1_64 = (RSCFD_UNIT_1 << 24) | 64,
    RSCFD_RX_PAGE_1_65 = (RSCFD_UNIT_1 << 24) | 65,
    RSCFD_RX_PAGE_1_66 = (RSCFD_UNIT_1 << 24) | 66,
    RSCFD_RX_PAGE_1_67 = (RSCFD_UNIT_1 << 24) | 67,
    RSCFD_RX_PAGE_1_68 = (RSCFD_UNIT_1 << 24) | 68,
    RSCFD_RX_PAGE_1_69 = (RSCFD_UNIT_1 << 24) | 69,
    RSCFD_RX_PAGE_1_70 = (RSCFD_UNIT_1 << 24) | 70,
    RSCFD_RX_PAGE_1_71 = (RSCFD_UNIT_1 << 24) | 71,
    RSCFD_RX_PAGE_1_72 = (RSCFD_UNIT_1 << 24) | 72,
    RSCFD_RX_PAGE_1_73 = (RSCFD_UNIT_1 << 24) | 73,
    RSCFD_RX_PAGE_1_74 = (RSCFD_UNIT_1 << 24) | 74,
    RSCFD_RX_PAGE_1_75 = (RSCFD_UNIT_1 << 24) | 75,
    RSCFD_RX_PAGE_1_76 = (RSCFD_UNIT_1 << 24) | 76,
    RSCFD_RX_PAGE_1_77 = (RSCFD_UNIT_1 << 24) | 77,
    RSCFD_RX_PAGE_1_78 = (RSCFD_UNIT_1 << 24) | 78,
    RSCFD_RX_PAGE_1_79 = (RSCFD_UNIT_1 << 24) | 79,
    RSCFD_RX_PAGE_1_80 = (RSCFD_UNIT_1 << 24) | 80,
    RSCFD_RX_PAGE_1_81 = (RSCFD_UNIT_1 << 24) | 81,
    RSCFD_RX_PAGE_1_82 = (RSCFD_UNIT_1 << 24) | 82,
    RSCFD_RX_PAGE_1_83 = (RSCFD_UNIT_1 << 24) | 83,
    RSCFD_RX_PAGE_1_84 = (RSCFD_UNIT_1 << 24) | 84,
    RSCFD_RX_PAGE_1_85 = (RSCFD_UNIT_1 << 24) | 85,
    RSCFD_RX_PAGE_1_86 = (RSCFD_UNIT_1 << 24) | 86,
    RSCFD_RX_PAGE_1_87 = (RSCFD_UNIT_1 << 24) | 87,
    RSCFD_RX_PAGE_1_88 = (RSCFD_UNIT_1 << 24) | 88,
    RSCFD_RX_PAGE_1_89 = (RSCFD_UNIT_1 << 24) | 89,
    RSCFD_RX_PAGE_1_90 = (RSCFD_UNIT_1 << 24) | 90,
    RSCFD_RX_PAGE_1_91 = (RSCFD_UNIT_1 << 24) | 91,
    RSCFD_RX_PAGE_1_92 = (RSCFD_UNIT_1 << 24) | 92,
    RSCFD_RX_PAGE_1_93 = (RSCFD_UNIT_1 << 24) | 93,
    RSCFD_RX_PAGE_1_94 = (RSCFD_UNIT_1 << 24) | 94,
    RSCFD_RX_PAGE_1_95 = (RSCFD_UNIT_1 << 24) | 95
}   rscfd_rx_page_t;

/*******************************************************************************
 * Status of TX History buffer
 * Register CFDTHLSTS bit fields THLELT, THFLL, THEMP and THLIF
 * Enumeration matches register bit field
 ******************************************************************************/
typedef enum
{
    RSCFD_HIST_STAT_EMPTY = 0x1,
    RSCFD_HIST_STAT_FULL  = 0x2,
    RSCFD_HIST_STAT_LOST  = 0x4,
    RSCFD_HIST_STAT_IRQ   = 0x8,
    RSCFD_HIST_STAT_ALL   = 0xF
}   rscfd_hist_stat_t;

/*******************************************************************************
 * Return codes for function R_RSCFD_ReadRxFifo
 ******************************************************************************/
typedef enum
{
    RSCFD_RX_FIFO_OK,
    RSCFD_RX_FIFO_LAST_MSG,
    RSCFD_RX_FIFO_EMPTY
}   rscfd_rx_return_t;

/*******************************************************************************
 * Return codes for functions demonstrating transmit/receive sequences by
 * either TX/RX FIFO or TX/RX buffers
 ******************************************************************************/
typedef enum
{
    RSCFD_RESULT_NOFAULT  = 0,               /* successful transmission */
    RSCFD_RESULT_NEWMSG   = 1,               /* new data available to read */
    RSCFD_RESULT_ERR      = 2,               /* unknown path */
    RSCFD_RESULT_EMPTY    = 2,               /* no new data to read */
    RSCFD_RESULT_OVERFLOW = 3,           /* data incoherent during read */
    RSCFD_RESULT_BUSY     = 4,               /* TX buffer busy */
    RSCFD_RESULT_FULL     = 5                /* TXFIFO full */
} rscfd_result_t;

/*##############################################################################
 # global data structures
 ##############################################################################*/

/*******************************************************************************
 * RSCFD pay load buffer type
 * NOTE: ensures placement on 32-bit boundary
 ******************************************************************************/
typedef union
{
    uint32 WORD[16];
    uint8  BYTE[64];
} rscfd_payload_t;

/*******************************************************************************
 * CAN message data structure
 * NOTE: used by aggregate APIs reading RX buffer and RX FIFO
 * or transmitting using TX FIFO or TX buffer
 ******************************************************************************/
typedef struct
{
    uint32               id;           /* message ID */
    rscfd_id_type_t      id_type;      /* message ID type (STD/EXT, NORM/RTR) */
    uint16               ptr;          /* message pointer */
    rscfd_label_t        label;        /* message label */
    uint16               timestamp;    /* message time stamp */
    rscfd_payload_size_t bytes;        /* number of bytes in payload */
    rscfd_payload_t *    payload;      /* message payload */
}   rscfd_msg_t;

/*******************************************************************************
 * CAN Transmit FIFO configuration (uses TX/RX/GW FIFOs)
 *   Transmit FIFO number
 *   TxBuffer the FIFO is linked to (for setting priority)
 *   CFIM field of register CFCC - configures interrupt occurrence
 *   CFIGCV field of register CFCC - configures interrupt occurrence
 *   Number of messages the Transmit FIFO can hold
 *   Number of data bytes each message can hold
 ******************************************************************************/
typedef struct
{
    rscfd_tx_fifo_t      num;                           /* TX FIFO number */
    rscfd_tx_fifo_buff_t link_buf;          /* associated TX buffer */
    rscfd_tx_fifo_int_t  irq;               /* interrupts */
    rscfd_cfdc_t         depth;             /* FIFO depth */
    rscfd_fpls_t         msg_length;        /* message length */
}   rscfd_tx_fifo_cfg_t;

/*******************************************************************************
 * CAN Receive FIFO configuration (uses RX FIFOs)
 *   Receive FIFO number
 *   RFIM field of register RFCC - configures interrupt occurrence
 *   RFIGCV field of register RFCC - configures interrupt occurrence
 *   Number of messages the Receive FIFO can hold
 *   Number of data bytes each message can hold
 ******************************************************************************/
typedef struct
{
    rscfd_rx_fifo_t     num;                /* RX FIFO number */
    rscfd_rx_fifo_int_t irq;                /* interrupts */
    rscfd_rfdc_t        depth;              /* depth */
    rscfd_fpls_t        msg_length;         /* message length */
}   rscfd_rx_fifo_cfg_t;

/*******************************************************************************
 * CAN Receive Rules configuration
 *
 * A:Acceptance Filter Parameters
 *   id               : ID used to filter messages
 *                    : Reg CFDGAFLID.GAFLID
 *   id_type          : IDE and RTR to filter messages
 *                    : Reg CFDGAFLID.GAFLIDE
 *   source           : Sets filter to only accept messages from
 *                    : - other senders
 *                    : - this node in loop back mode
 *                    : Reg CFDGAFLID.GAFLLB
 *   min_dlc          : Messages with payload size less than specified
 *                    : by this DLC field will not pass filter.
 *                    : Reg CFDGAFLP0.GAFLDLC
 *
 * B:Acceptance Filter Masks
 *   mask_id          : Allows masking of ID bits used by filter -
 *                    : Used to pass a range of message IDs.
 *                    : Reg CFDGAFLM.GAFLIDM
 *   mask_ide         : Allows masking of IDE bit use by filter.
 *                    : Reg CFDGAFLM.GAFLIDEM
 *
 * C:Accepted Message Mapping
 *   dst              : Maps message to a Rx Buffer or Rx FIFO.
 *                    : Routing to common FIFO or Tx Queue not supported.
 *                    : RxBuf - Reg CFDGAFLP0.GAFLRMV and .GAFLRMDP
 *                    : RxFIFO - Reg CFDGAFLP1.GAFLFDP[7:0]
 *   ptr              : 16-bit number saved with accepted message
 *                    : Reg CFDGAFLP0.GAFLPTR
 ******************************************************************************/
typedef struct
{
    rscfd_rx_page_t         page;               /* which RSCFD unit and page */
    rscfd_rx_rule_t         rule;               /* which rule within the page */
    uint32                  id;             /* A: ID filter */
    rscfd_id_type_t         id_type;        /* A: standard/extended ID */
    rscfd_rx_src_t          source;         /* A: messages origin */
    rscfd_dlc_t             min_dlc;        /* A: minimum payload to accept */
    uint32                  mask_id;        /* B: ID bits mask */
    rscfd_rx_id_type_mask_t mask_id_type;   /* B: IDE bit mask */
    rscfd_rx_dst_t          dest;           /* C: message destination */
    uint16                  ptr;            /* C: message pointer to store */
}   rscfd_rx_rule_cfg_t;

/*******************************************************************************
 * CAN Channel configuration
 *   CAN channel number.
 *   Loopback test mode
 *   Test mode enabled/disabled.
 *   Error interrupt enabled/disabled.
 *   Communication bit rate: Arbitration and Data.
 *   Number of Rx Rules used by this channel.
 ******************************************************************************/
typedef struct
{
    rscfd_chnl_t         chnl;
    rscfd_chnl_interf_t  interface;
    rscfd_chnl_test_t    testmode;
    rscfd_chnl_err_irq_t error_irq;
    rscfd_chnl_nbr_t     nom_rate;
    rscfd_chnl_dbr_t     data_rate;
    rscfd_chnl_hist_en_t hist_en;
    rscfd_chnl_comp_t    comp;
    uint16               rx_rule_cnt;
    uint8                comp_ofst;
    uint32               hw_delay;
}   rscfd_chnl_cfg_t;

/*******************************************************************************
 * User configurations per CAN unit
 *   CAN Unit - 0 or 1.
 *   CAN Mode - Classic (2.0A/B) or CAN-FD.
 *   Clock source - Oscillator or CLK_LSB.
 *   RX Buffers - number and size per unit.
 *   Wait - maximum wait time for global mode transitions to take place.
 * Note: TX Buffers do not require initialization.
 * Note: maximum wait time is to prevent the unit initialization routines from
 * never returning in case of HW failure.
 ******************************************************************************/
typedef struct
{
    rscfd_unit_t         unit;
    rscfd_clock_src_t    clock_source;
    rscfd_dlc_check_t    dlc_check;
    rscfd_rx_buff_cnt_t  rx_buff_cnt;
    rscfd_rx_buff_size_t rx_buff_size;
    uint32               hw_delay;
}   rscfd_unit_cfg_t;

/*******************************************************************************
 * Combined RSCFD configurations when using FIFO mechanisms.
 *   Global Unit
 *   Channels
 *   Receive rules
 *   RX FIFOs
 *   Common FIFOs used as TX FIFOs
 ******************************************************************************/
typedef struct
{
    const rscfd_unit_cfg_t *    unit_cfg;
    const rscfd_chnl_cfg_t *    chnl_cfg;
    const rscfd_rx_rule_cfg_t * rx_rules_cfg;
    const rscfd_rx_fifo_cfg_t * rx_fifo_cfg;
    const rscfd_tx_fifo_cfg_t * tx_fifo_cfg;
    uint8                       unit_cfg_cnt;
    uint8                       chnl_cfg_cnt;
    uint8                       rx_rules_cfg_cnt;
    uint8                       rx_fifo_cfg_cnt;
    uint8                       tx_fifo_cfg_cnt;
} rscfd_fifo_cfg_t;

/*******************************************************************************
 * Combined RSCFD configurations when using buffer mechanisms.
 *   Global Unit
 *   Channels
 *   Receive rules
 ******************************************************************************/
typedef struct
{
    const rscfd_unit_cfg_t *    unit_cfg;
    const rscfd_chnl_cfg_t *    chnl_cfg;
    const rscfd_rx_rule_cfg_t * rx_rules_cfg;
    uint8                       unit_cfg_cnt;
    uint8                       chnl_cfg_cnt;
    uint8                       rx_rules_cfg_cnt;
} rscfd_buff_cfg_t;

#endif /* R_RSCFD_CFG_H */

