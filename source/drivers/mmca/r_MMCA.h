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
* File Name         : r_MMCA.h
* Component Version : 1.0.0
* Description       : Header file for r_MMCA.c.
***********************************************************************************************************************/
#ifndef R_MMCA_H
#define R_MMCA_H

/**********************************************************************************************************************
Macros
**********************************************************************************************************************/
#define MMCA0_BASE_ADDRESS		0xFFD55000		/* <MMCAn_base> */

#define MMCA_PROT_DISABLE		0xA5A5A500		/* Disable writing protect register value */
#define MMCA_PROT_ENABLE		0xA5A5A501		/* Enable writing protect register value */

#define MMCA_CLEAR_REGISTER		0x00000000

#define MMCA_PORT				PORT_24
#define MMCA_PIN_CLK			PIN_4
#define MMCA_PIN_CMD			PIN_5
#define MMCA_PIN_DAT0			PIN_6
#define MMCA_PIN_DAT1			PIN_7
#define MMCA_PIN_DAT2			PIN_8
#define MMCA_PIN_DAT3			PIN_9
#define MMCA_PIN_DET			PIN_10


/************** CMD_SET register **************/
/* BOOT[30] - Boot Operations */
#define MMCA_BOOT_BITS          0x40000000      /* BOOT bits */
#define MMCA_BOOT_NOT_BOOT      0x00000000      /* Command sequence other than for boot operations */
#define MMCA_BOOT_BOOT          0x40000000      /* Command sequence for boot operations */
/* CMD[29:24] - Command Index */
#define MMCA_CMD_BITS           0x3F000000      /* CMD bits */
#define MMCA_CMD_00             0x00000000      /* CMD0 */
#define MMCA_CMD_01             0x01000000      /* CMD1 */
#define MMCA_CMD_02             0x02000000      /* CMD2 */
#define MMCA_CMD_03             0x03000000      /* CMD3 */
#define MMCA_CMD_04             0x04000000      /* CMD4 */
#define MMCA_CMD_05             0x05000000      /* CMD5 */
#define MMCA_CMD_06             0x06000000      /* CMD6 */
#define MMCA_CMD_07             0x07000000      /* CMD7 */
#define MMCA_CMD_08             0x08000000      /* CMD8 */
#define MMCA_CMD_09             0x09000000      /* CMD9 */
#define MMCA_CMD_10             0x0A000000      /* CMD10 */
#define MMCA_CMD_11             0x0B000000      /* CMD11 */
#define MMCA_CMD_12             0x0C000000      /* CMD12 */
#define MMCA_CMD_13             0x0D000000      /* CMD13 */
#define MMCA_CMD_14             0x0E000000      /* CMD14 */
#define MMCA_CMD_15             0x0F000000      /* CMD15 */
#define MMCA_CMD_16             0x10000000      /* CMD16 */
#define MMCA_CMD_17             0x11000000      /* CMD17 */
#define MMCA_CMD_18             0x12000000      /* CMD18 */
#define MMCA_CMD_19             0x13000000      /* CMD19 */
#define MMCA_CMD_20             0x14000000      /* CMD20 */
#define MMCA_CMD_21             0x15000000      /* CMD21 */
#define MMCA_CMD_22             0x16000000      /* CMD22 */
#define MMCA_CMD_23             0x17000000      /* CMD23 */
#define MMCA_CMD_24             0x18000000      /* CMD24 */
#define MMCA_CMD_25             0x19000000      /* CMD25 */
#define MMCA_CMD_26             0x1A000000      /* CMD26 */
#define MMCA_CMD_27             0x1B000000      /* CMD27 */
#define MMCA_CMD_28             0x1C000000      /* CMD28 */
#define MMCA_CMD_29             0x1D000000      /* CMD29 */
#define MMCA_CMD_30             0x1E000000      /* CMD30 */
#define MMCA_CMD_31             0x1F000000      /* CMD31 */
#define MMCA_CMD_32             0x20000000      /* CMD32 */
#define MMCA_CMD_33             0x21000000      /* CMD33 */
#define MMCA_CMD_34             0x22000000      /* CMD34 */
#define MMCA_CMD_35             0x23000000      /* CMD35 */
#define MMCA_CMD_36             0x24000000      /* CMD36 */
#define MMCA_CMD_37             0x25000000      /* CMD37 */
#define MMCA_CMD_38             0x26000000      /* CMD38 */
#define MMCA_CMD_39             0x27000000      /* CMD39 */
#define MMCA_CMD_40             0x28000000      /* CMD40 */
#define MMCA_CMD_41             0x29000000      /* CMD41 */
#define MMCA_CMD_42             0x2A000000      /* CMD42 */
#define MMCA_CMD_43             0x2B000000      /* CMD43 */
#define MMCA_CMD_44             0x2C000000      /* CMD44 */
#define MMCA_CMD_45             0x2D000000      /* CMD45 */
#define MMCA_CMD_46             0x2E000000      /* CMD46 */
#define MMCA_CMD_47             0x2F000000      /* CMD47 */
#define MMCA_CMD_48             0x30000000      /* CMD48 */
#define MMCA_CMD_49             0x31000000      /* CMD49 */
#define MMCA_CMD_50             0x32000000      /* CMD50 */
#define MMCA_CMD_51             0x33000000      /* CMD51 */
#define MMCA_CMD_52             0x34000000      /* CMD52 */
#define MMCA_CMD_53             0x35000000      /* CMD53 */
#define MMCA_CMD_54             0x36000000      /* CMD54 */
#define MMCA_CMD_55             0x37000000      /* CMD55 */
#define MMCA_CMD_56             0x38000000      /* CMD56 */
#define MMCA_CMD_57             0x39000000      /* CMD57 */
#define MMCA_CMD_58             0x3A000000      /* CMD58 */
#define MMCA_CMD_59             0x3B000000      /* CMD59 */
#define MMCA_CMD_60             0x3C000000      /* CMD60 */
#define MMCA_CMD_61             0x3D000000      /* CMD61 */
#define MMCA_CMD_62             0x3E000000      /* CMD62 */
#define MMCA_CMD_63             0x3F000000      /* CMD63 */
/* RTYP[23:22] - Response type */
#define MMCA_RTYP_BITS          0x00C00000      /* RTYP bits */
#define MMCA_RTYP_NO_RESPONSE   0x00000000      /* No response */
#define MMCA_RTYP_6BYTE         0x00400000      /* 6-byte response (R1, R1b, R3, R4, R5) */
#define MMCA_RTYP_17BYTE        0x00800000      /* 17-byte response (R2) */
/* RBSY[21] - Response Busy Select */
#define MMCA_RBSY_BITS          0x00200000      /* RBSY bits */
#define MMCA_RBSY_NO_BUSY       0x00000000      /* No response busy */
#define MMCA_RBSY_BUSY_INVOLVED 0x00200000      /* Response busy involved (R1b) */
/* WDAT[19] - Presence/Absence of Data */
#define MMCA_WDAT_BITS          0x00080000      /* WDAT bits */
#define MMCA_WDAT_NO_DATA       0x00000000      /* No data */
#define MMCA_WDAT_WITH_DATA     0x00080000      /* With data */
/* DWEN[18] - Read/Write (valid when "with data" is selected) */
#define MMCA_DWEN_BITS          0x00040000      /* DWEN bits */
#define MMCA_DWEN_READ_CARD     0x00000000      /* Read from card */
#define MMCA_DWEN_WRITE_CARD    0x00040000      /* Write to card */
/* CMLTE[17] - Single/Multi Block Transfer Select (valid when "with data" is selected) */
#define MMCA_CMLTE_BITS         0x00020000      /* CMLTE bits */
#define MMCA_CMLTE_SINGLE_BLOCK 0x00000000      /* Single-block transfer */
#define MMCA_CMLTE_MULTI_BLOCK  0x00020000      /* Multi-block transfer */
/* CMD12EN[16] - Automatic CMD12 Issuance (valid when multi-block transfer is selected) */
#define MMCA_CMD12EN_BITS       0x00010000      /* CMD12EN bits */
#define MMCA_CMD12EN_DISABLED   0x00000000      /* Disables automatic CMD12 issuance */
#define MMCA_CMD12EN_ENABLED    0x00010000      /* Enables automatic CMD12 issuance */
/* RIDXC[15:14] - Response Index Check */
#define MMCA_RIDXC_BITS         0x0000C000      /* RIDXC bits */
#define MMCA_RIDXC_CHECK_RESP   0x00000000      /* Checks the response index (check whether matched with a command index) */
#define MMCA_RIDXC_CHECK_BITS   0x00004000      /* Checks the check bits (check wheter all the bits are set to 1) */
#define MMCA_RIDXC_NO_CHECK     0x00008000      /* No checking */
/* RCRC7C[13:12] - Response CRC7 Check */
#define MMCA_RCRC7C_BITS        0x00003000      /* RCRC7C bits */
#define MMCA_RCRC7C_CHECK_CRC7  0x00000000      /* Checks CRC7 */
#define MMCA_RCRC7C_CHECK_BITS  0x00001000      /* Checks the check bits (check whether all the bits are set to 1) */
#define MMCA_RCRC7C_NO_CHECK    0x00002000      /* No checking */
/* CRC16C[10] - Check in Reception (valid when "with data" and "read" are selected) */
#define MMCA_CRC16C_BITS        0x00000400      /* CRC16C bits */
#define MMCA_CRC16C_CHECK_CRC16 0x00000000      /* Checks CRC16 in reception */
#define MMCA_CRC16C_NO_CHECK    0x00000400      /* Does not check CRC16 in reception */
/* BOOTACK[9] - Receive Boot Acknowledge (valid in boot mode) */
#define MMCA_BOOTACK_BITS       0x00000200      /* BOOTACK bits */
#define MMCA_BOOTACK_NOT_REC    0x00000000      /* Boot acknowledge is not received */
#define MMCA_BOOTACK_RECEIVED   0x00000200      /* Boot acknowledge is received */
/* CRCSTE[8] - CRC Status Reception (valid when "with data" and "write" are selected) */
#define MMCA_CRCSTE_BITS        0x00000100      /* CRCSTE bits */
#define MMCA_CRCSTE_REC_CRC_STS 0x00000000      /* Receives CRC status */
#define MMCA_CRCSTE_NOT_REC     0x00000100      /* Does not receive CRC status */
/* TBIT[7] - Transmission Bit Setting */
#define MMCA_TBIT_BITS          0x00000080      /* TBIT bits */
#define MMCA_TBIT_TX_BIT_1      0x00000000      /* Sets the transmission bit ([46]) to 1 */
#define MMCA_TBIT_TX_BIT_0      0x00000080      /* Sets the transmission bit ([46]) to 0 */
/* OPDM[6] - Open-Drain Output Mode */
#define MMCA_OPDM_BITS          0x00000040      /* OPDM bits */
#define MMCA_OPDM_NORMAL_OUT    0x00000000      /* Normal output */
#define MMCA_OPDM_OPENDRAIN_OUT 0x00000040      /* Open-drain output */
/* SBIT[3] - Read Data Start Bit Detection Setting (valid when "with data" and "read" are selected) */
#define MMCA_SBIT_BITS          0x00000008      /* SBIT bits */
#define MMCA_SBIT_ALL_DAT       0x00000000      /* Detects a start bit when the valid DAT signals specified by the DATW bis are all 0 */
#define MMCA_SBIT_DAT0          0x00000008      /* Detects a start bit when DAT[0] is 0 */
/* DATW[1:0] - Data Bus Width Setting (valid when "with data" is selected) */
#define MMCA_DATW_BITS          0x00000003      /* DATW bits */
#define MMCA_DATW_1BIT          0x00000000      /* 1 bit */
#define MMCA_DATW_4BITS         0x00000001      /* 4 bits */
#define MMCA_DATW_8BITS         0x00000002      /* 8 bits */

/************** CMD_CTRL register **************/
/* BREAK[0] - Forcible Termination of Command Sequence */
#define MMCA_BREAK_BITS         0x00000001      /* BREAK bits */
#define MMCA_BREAK_NO_END       0x00000000      /* Does nothing */
#define MMCA_BREAK_FORCE_END    0x00000001      /* Forces Termination of Command Sequence */

/************** CLK_CTRL register **************/
/* MMCBUSBSY[31] - MMC CLock Output control / Division setting prohibition */
#define MMCA_MMCBUSBSY_BITS     0x80000000      /* MMCBUSBSY bits */
#define MMCA_MMCBUSBSY_NOT_BUSY 0x00000000      /* MMC bus is not busy (During the command sequence + 10 cycles) */
#define MMCA_MMCBUSBSY_BUSY     0x80000000      /* MMC bus is busy (During the command sequence + 10 cycles) */
/* CLKEN[24] - MMC Clock Output Control */
#define MMCA_CLKEN_BITS			0x01000000		/* CLKEN bits */
#define MMCA_CLKEN_DISABLE      0x00000000      /* Does not output the MMC clock (fixed to low level) */
#define MMCA_CLKEN_ENABLE       0x01000000      /* Outputs the MMC clock */
/* CLKDIV[19:16] - MMC Clock Frequency Setting */
#define MMCA_CLKDIV_BITS        0x000F0000      /* CLKDIV bits */
#define MMCA_CLKDIV_2           0x00000000      /* MMCA module clock / 2 */
#define MMCA_CLKDIV_4           0x00010000      /* MMCA module clock / 4 */
#define MMCA_CLKDIV_8           0x00020000      /* MMCA module clock / 8 */
#define MMCA_CLKDIV_16          0x00030000      /* MMCA module clock / 16 */
#define MMCA_CLKDIV_32          0x00040000      /* MMCA module clock / 32 */
#define MMCA_CLKDIV_64          0x00050000      /* MMCA module clock / 64 */
#define MMCA_CLKDIV_128         0x00060000      /* MMCA module clock / 128 */
#define MMCA_CLKDIV_256         0x00070000      /* MMCA module clock / 256 */
#define MMCA_CLKDIV_512         0x00080000      /* MMCA module clock / 512 */
#define MMCA_CLKDIV_1024        0x00090000      /* MMCA module clock / 1024 */
/* SRSPTO[13:12] - Response Timeout Setting */
#define MMCA_SRSPTO_BITS        0x00003000      /* SRSPTO bits */
#define MMCA_SRSPTO_64          0x00000000      /* 64 MMC clock cycles */
#define MMCA_SRSPTO_128         0x00001000      /* 128 MMC clock cycles */
#define MMCA_SRSPTO_256         0x00002000      /* 256 MMC clock cycles */
/* SRBSYTO[11:8] - Response Busy Timeout Setting */
#define MMCA_SRBSYTO_BITS       0x00000F00      /* SRBSYTO bits */
#define MMCA_SRBSYTO_14         0x00000000      /* 2^14 (16384) MMC clock cycles */
#define MMCA_SRBSYTO_15         0x00000100      /* 2^15 (32768) MMC clock cycles */
#define MMCA_SRBSYTO_16         0x00000200      /* 2^16 (65536) MMC clock cycles */
#define MMCA_SRBSYTO_17         0x00000300      /* 2^17 (131072) MMC clock cycles */
#define MMCA_SRBSYTO_18         0x00000400      /* 2^18 (262144) MMC clock cycles */
#define MMCA_SRBSYTO_19         0x00000500      /* 2^19 (524288) MMC clock cycles */
#define MMCA_SRBSYTO_20         0x00000600      /* 2^20 (1048576) MMC clock cycles */
#define MMCA_SRBSYTO_21         0x00000700      /* 2^21 (2097152) MMC clock cycles */
#define MMCA_SRBSYTO_22         0x00000800      /* 2^22 (4194304) MMC clock cycles */
#define MMCA_SRBSYTO_23         0x00000900      /* 2^23 (8388608) MMC clock cycles */
#define MMCA_SRBSYTO_24         0x00000A00      /* 2^24 (16777216) MMC clock cycles */
#define MMCA_SRBSYTO_25         0x00000B00      /* 2^25 (33554432) MMC clock cycles */
#define MMCA_SRBSYTO_26         0x00000C00      /* 2^26 (67108864) MMC clock cycles */
#define MMCA_SRBSYTO_27         0x00000D00      /* 2^27 (134217728) MMC clock cycles */
#define MMCA_SRBSYTO_28         0x00000E00      /* 2^28 (268435456) MMC clock cycles */
#define MMCA_SRBSYTO_29         0x00000F00      /* 2^29 (536870912) MMC clock cycles */
/* SRWDTO[7:4] - Write Data/Read Data Timeout Setting */
#define MMCA_SRWDTO_BITS        0x000000F0      /* SRWDTO bits */
#define MMCA_SRWDTO_14          0x00000000      /* 2^14 (16384) MMC clock cycles */
#define MMCA_SRWDTO_15          0x00000010      /* 2^15 (32768) MMC clock cycles */
#define MMCA_SRWDTO_16          0x00000020      /* 2^16 (65536) MMC clock cycles */
#define MMCA_SRWDTO_17          0x00000030      /* 2^17 (131072) MMC clock cycles */
#define MMCA_SRWDTO_18          0x00000040      /* 2^18 (262144) MMC clock cycles */
#define MMCA_SRWDTO_19          0x00000050      /* 2^19 (524288) MMC clock cycles */
#define MMCA_SRWDTO_20          0x00000060      /* 2^20 (1048576) MMC clock cycles */
#define MMCA_SRWDTO_21          0x00000070      /* 2^21 (2097152) MMC clock cycles */
#define MMCA_SRWDTO_22          0x00000080      /* 2^22 (4194304) MMC clock cycles */
#define MMCA_SRWDTO_23          0x00000090      /* 2^23 (8388608) MMC clock cycles */
#define MMCA_SRWDTO_24          0x000000A0      /* 2^24 (16777216) MMC clock cycles */
#define MMCA_SRWDTO_25          0x000000B0      /* 2^25 (33554432) MMC clock cycles */
#define MMCA_SRWDTO_26          0x000000C0      /* 2^26 (67108864) MMC clock cycles */
#define MMCA_SRWDTO_27          0x000000D0      /* 2^27 (134217728) MMC clock cycles */
#define MMCA_SRWDTO_28          0x000000E0      /* 2^28 (268435456) MMC clock cycles */
#define MMCA_SRWDTO_29          0x000000F0      /* 2^29 (536870912) MMC clock cycles */

/************** BUF_ACC register **************/
/* DMATYP[26] - DMA Transfer setting */
#define MMCA_DMATYP_BITS        0x04000000      /* DMATYP bits */
#define MMCA_DMATYP_CLEAR       0x00000000      /* DMATYP = 0 */
#define MMCA_DMATYP_SET         0x04000000      /* DMATYP = 1 */
/* DMAWEN[25] - Buffer Write DMA Transfer Request Enable */
#define MMCA_DMAWEN_BITS        0x02000000      /* DMAWEN bits */
#define MMCA_DMAWEN_W_DISABLED  0x00000000      /* Disables DMA transfer request for buffer writing */
#define MMCA_DMAWEN_W_ENABLED   0x02000000      /* Enables DMA transfer request for buffer writing */
/* DMAREN[24] - Buffer Read DMA Transfer Request Enable */
#define MMCA_DMAREN_BITS        0x01000000      /* DMAREN bits */
#define MMCA_DMAREN_R_DISABLED  0x00000000      /* Disables DMA transfer request for buffer reading */
#define MMCA_DMAREN_R_ENABLED   0x01000000      /* Enables DMA transfer request for buffer reading */
/* ATYP[16] - Buffer access selection */
#define MMCA_ATYP_BITS          0x00010000      /* ATYP bits */
#define MMCA_ATYP_NOT_SWAP_BYTE 0x00000000      /* When not swapped byte-wise */
#define MMCA_ATYP_SWAP_BYTE     0x00010000      /* When swapped byte-wise */

/************** BOOT register **************/
/* BTCLKDIV[31:28] - MMC Clock Frequency Setting in Boot Mode */
#define MMCA_BTCLKDIV_BITS      0xF0000000      /* BTCLKDIV bits */
#define MMCA_BTCLKDIV_2         0x00000000      /* MMCA module clock / 2 */
#define MMCA_BTCLKDIV_4         0x10000000      /* MMCA module clock / 4 */
#define MMCA_BTCLKDIV_8         0x20000000      /* MMCA module clock / 8 */
#define MMCA_BTCLKDIV_16        0x30000000      /* MMCA module clock / 16 */
#define MMCA_BTCLKDIV_32        0x40000000      /* MMCA module clock / 32 */
/* SBTACKTO[27:24]: Boot Acknowledge Timeout Setting */
#define MMCA_SBTACKTO_BITS      0x0F000000      /* SBTACKTO bits */
#define MMCA_SBTACKTO_14        0x00000000      /* 2^14 (16384) MMC clock cycles */
#define MMCA_SBTACKTO_15        0x01000000      /* 2^15 (32768) MMC clock cycles */
#define MMCA_SBTACKTO_16        0x02000000      /* 2^16 (65536) MMC clock cycles */
#define MMCA_SBTACKTO_17        0x03000000      /* 2^17 (131072) MMC clock cycles */
#define MMCA_SBTACKTO_18        0x04000000      /* 2^18 (262144) MMC clock cycles */
#define MMCA_SBTACKTO_19        0x05000000      /* 2^19 (524288) MMC clock cycles */
#define MMCA_SBTACKTO_20        0x06000000      /* 2^20 (1048576) MMC clock cycles */
#define MMCA_SBTACKTO_21        0x07000000      /* 2^21 (2097152) MMC clock cycles */
#define MMCA_SBTACKTO_22        0x08000000      /* 2^22 (4194304) MMC clock cycles */
#define MMCA_SBTACKTO_23        0x09000000      /* 2^23 (8388608) MMC clock cycles */
#define MMCA_SBTACKTO_24        0x0A000000      /* 2^24 (16777216) MMC clock cycles */
#define MMCA_SBTACKTO_25        0x0B000000      /* 2^25 (33554432) MMC clock cycles */
#define MMCA_SBTACKTO_26        0x0C000000      /* 2^26 (67108864) MMC clock cycles */
#define MMCA_SBTACKTO_27        0x0D000000      /* 2^27 (134217728) MMC clock cycles */
#define MMCA_SBTACKTO_28        0x0E000000      /* 2^28 (268435456) MMC clock cycles */
#define MMCA_SBTACKTO_29        0x0F000000      /* 2^29 (536870912) MMC clock cycles */
/* S1STBTDATTO[23:20] - 1st Boot Data Timeout Setting */
#define MMCA_S1STBTDATTO_BITS   0x00F00000      /* SBTACKTO bits */
#define MMCA_S1STBTDATTO_14     0x00000000      /* 2^14 (16384) MMC clock cycles */
#define MMCA_S1STBTDATTO_15     0x00100000      /* 2^15 (32768) MMC clock cycles */
#define MMCA_S1STBTDATTO_16     0x00200000      /* 2^16 (65536) MMC clock cycles */
#define MMCA_S1STBTDATTO_17     0x00300000      /* 2^17 (131072) MMC clock cycles */
#define MMCA_S1STBTDATTO_18     0x00400000      /* 2^18 (262144) MMC clock cycles */
#define MMCA_S1STBTDATTO_19     0x00500000      /* 2^19 (524288) MMC clock cycles */
#define MMCA_S1STBTDATTO_20     0x00600000      /* 2^20 (1048576) MMC clock cycles */
#define MMCA_S1STBTDATTO_21     0x00700000      /* 2^21 (2097152) MMC clock cycles */
#define MMCA_S1STBTDATTO_22     0x00800000      /* 2^22 (4194304) MMC clock cycles */
#define MMCA_S1STBTDATTO_23     0x00900000      /* 2^23 (8388608) MMC clock cycles */
#define MMCA_S1STBTDATTO_24     0x00A00000      /* 2^24 (16777216) MMC clock cycles */
#define MMCA_S1STBTDATTO_25     0x00B00000      /* 2^25 (33554432) MMC clock cycles */
#define MMCA_S1STBTDATTO_26     0x00C00000      /* 2^26 (67108864) MMC clock cycles */
#define MMCA_S1STBTDATTO_27     0x00D00000      /* 2^27 (134217728) MMC clock cycles */
#define MMCA_S1STBTDATTO_28     0x00E00000      /* 2^28 (268435456) MMC clock cycles */
#define MMCA_S1STBTDATTO_29     0x00F00000      /* 2^29 (536870912) MMC clock cycles */
/* SBTDATTO[19:16] - Interval Between Boot Data Timeout Setting */
#define MMCA_SBTDATTO_BITS      0x000F0000      /* SBTACKTO bits */
#define MMCA_SBTDATTO_14        0x00000000      /* 2^14 (16384) MMC clock cycles */
#define MMCA_SBTDATTO_15        0x00010000      /* 2^15 (32768) MMC clock cycles */
#define MMCA_SBTDATTO_16        0x00020000      /* 2^16 (65536) MMC clock cycles */
#define MMCA_SBTDATTO_17        0x00030000      /* 2^17 (131072) MMC clock cycles */
#define MMCA_SBTDATTO_18        0x00040000      /* 2^18 (262144) MMC clock cycles */
#define MMCA_SBTDATTO_19        0x00050000      /* 2^19 (524288) MMC clock cycles */
#define MMCA_SBTDATTO_20        0x00060000      /* 2^20 (1048576) MMC clock cycles */
#define MMCA_SBTDATTO_21        0x00070000      /* 2^21 (2097152) MMC clock cycles */
#define MMCA_SBTDATTO_22        0x00080000      /* 2^22 (4194304) MMC clock cycles */
#define MMCA_SBTDATTO_23        0x00090000      /* 2^23 (8388608) MMC clock cycles */
#define MMCA_SBTDATTO_24        0x000A0000      /* 2^24 (16777216) MMC clock cycles */
#define MMCA_SBTDATTO_25        0x000B0000      /* 2^25 (33554432) MMC clock cycles */
#define MMCA_SBTDATTO_26        0x000C0000      /* 2^26 (67108864) MMC clock cycles */
#define MMCA_SBTDATTO_27        0x000D0000      /* 2^27 (134217728) MMC clock cycles */
#define MMCA_SBTDATTO_28        0x000E0000      /* 2^28 (268435456) MMC clock cycles */
#define MMCA_SBTDATTO_29        0x000F0000      /* 2^29 (536870912) MMC clock cycles */

/************** INT register **************/
//#define MMCA_INT_ERRORS         0x00007FFF    /* Interrupt errors mask without CMDVIO */
#define MMCA_INT_STATUS			0xFFFF0000		/* Interrupt status mask */
#define MMCA_INT_ERRORS         0x0000FFFF      /* Interrupt errors mask */
#define MMCA_INT_CLEAR_ALL      0x00000000
/* CMD12DRE[26] - Automatic CMD12 Issuance & Buffer Read Complete */
#define MMCA_CMD12DRE_BITS      0x04000000      /* CMD12DRE bits */
#define MMCA_CMD12DRE_CLEAR     0xFBFFFFFF      /* CMD12DRE clear mask */
#define MMCA_CMD12DRE_OFF       0x00000000      /* Flag off */
#define MMCA_CMD12DRE_ON        0x04000000      /* Response busy automatically-issued CMD12 and buffer reading have been completed */
/* CMD12RBE[25] - Automatic CMD12 Issuance Response Busy Complete */
#define MMCA_CMD12RBE_BITS      0x02000000      /* CMD12RBE bits */
#define MMCA_CMD12RBE_CLEAR     0xFDFFFFFF      /* CMD12RBE clear mask */
#define MMCA_CMD12RBE_OFF       0x00000000      /* Flag off */
#define MMCA_CMD12RBE_ON        0x02000000      /* Reception of the response and response busy for an automatically-issued CMD12 have been completed */
/* CMD12CRE[24] - Automatic CMD12 Response Complete */
#define MMCA_CMD12CRE_BITS      0x01000000      /* CMD12CRE bits */
#define MMCA_CMD12CRE_CLEAR     0xFEFFFFFF      /* CMD12CRE clear mask */
#define MMCA_CMD12CRE_OFF       0x00000000      /* Flag off */
#define MMCA_CMD12CRE_ON        0x01000000      /* The response to an automatically-issued CMD12 has been received */
/* DTRANE[23] - Data Transmission Complete */
#define MMCA_DTRANE_BITS        0x00800000      /* DTRANE bits */
#define MMCA_DTRANE_CLEAR       0xFF7FFFFF      /* DTRANE clear mask */
#define MMCA_DTRANE_OFF         0x00000000      /* Flag off */
#define MMCA_DTRANE_ON          0x00800000      /* Transmission of all blocks of data has been completed */
/* BUFRE[22] - Buffer Read Complete */
#define MMCA_BUFRE_BITS         0x00400000      /* BUFRE bits */
#define MMCA_BUFRE_CLEAR        0xFFBFFFFF      /* BUFRE clear mask */
#define MMCA_BUFRE_OFF          0x00000000      /* Flag off */
#define MMCA_BUFRE_ON           0x00400000      /* All blocks of data have been received and the data have been read from the buffer */
/* BUFWEN[21] - Buffer Write Ready */
#define MMCA_BUFWEN_BITS        0x00200000      /* BUFWEN bits */
#define MMCA_BUFWEN_CLEAR       0xFFDFFFFF      /* BUFWEN clear mask */
#define MMCA_BUFWEN_OFF         0x00000000      /* Flag off */
#define MMCA_BUFWEN_ON          0x00200000      /* The buffer has become empty and ready for writing */
/* BUFREN[20] - Buffer Read Ready */
#define MMCA_BUFREN_BITS        0x00100000      /* BUFREN bits */
#define MMCA_BUFREN_CLEAR       0xFFEFFFFF      /* BUFREN clear mask */
#define MMCA_BUFREN_OFF         0x00000000      /* Flag off */
#define MMCA_BUFREN_ON          0x00100000      /* Transfer block size of data have been stored in the buffer and it has become ready for reading */
/* RBSYE[17] - Response Busy Complete */
#define MMCA_RBSYE_BITS         0x00020000      /* RBSYE bits */
#define MMCA_RBSYE_CLEAR        0xFFFDFFFF      /* RBSYE clear mask */
#define MMCA_RBSYE_OFF          0x00000000      /* Flag off */
#define MMCA_RBSYE_ON           0x00020000      /* Reception of a response and response busy have been completed */
/* CRSPE[16] - Command/Response Complete */
#define MMCA_CRSPE_BITS         0x00010000      /* CRSPE bits */
#define MMCA_CRSPE_CLEAR        0xFFFEFFFF      /* CRSPE clear mask */
#define MMCA_CRSPE_OFF          0x00000000      /* Flag off */
#define MMCA_CRSPE_ON           0x00010000      /* A Command/Response has been transmitted/received */
/* CMDVIO[15] - Command Issuance Error */
#define MMCA_CMDVIO_BITS        0x00008000      /* CMDVIO bits */
#define MMCA_CMDVIO_CLEAR       0xFFFF7FFF      /* CMDVIO clear mask */
#define MMCA_CMDVIO_OFF         0x00000000      /* Flag off */
#define MMCA_CMDVIO_ON          0x00008000      /* Illegal setting has been made in CMD_SET or BLOCK_SET register */
/* BUFVIO[14] - Buffer Access Error */
#define MMCA_BUFVIO_BITS        0x00004000      /* BUFVIO bits */
#define MMCA_BUFVIO_CLEAR       0xFFFFBFFF      /* BUFVIO clear mask */
#define MMCA_BUFVIO_OFF         0x00000000      /* Flag off */
#define MMCA_BUFVIO_ON          0x00004000      /* Illegal buffer access has been attempted */
/* WDATERR[11] - Write Data Error */
#define MMCA_WDATERR_BITS       0x00000800      /* WDATERR bits */
#define MMCA_WDATERR_CLEAR      0xFFFFF7FF      /* WDATERR clear mask */
#define MMCA_WDATERR_OFF        0x00000000      /* Flag off */
#define MMCA_WDATERR_ON         0x00000800      /* Error is found in the data that has been written */
/* RDATERR[10] - Read Data Error */
#define MMCA_RDATERR_BITS       0x00000400      /* RDATERR bits */
#define MMCA_RDATERR_CLEAR      0xFFFFFBFF      /* RDATERR clear mask */
#define MMCA_RDATERR_OFF        0x00000000      /* Flag off */
#define MMCA_RDATERR_ON         0x00000400      /* Error is found in the read data */
/* RIDXERR[9] - Response Index Error */
#define MMCA_RIDXERR_BITS       0x00000200      /* RIDXERR bits */
#define MMCA_RIDXERR_CLEAR      0xFFFFFDFF      /* RIDXERR clear mask */
#define MMCA_RIDXERR_OFF        0x00000000      /* Flag off */
#define MMCA_RIDXERR_ON         0x00000200      /* Error has been found in the index value of the response */
/* RSPERR[8] - Response Error */
#define MMCA_RSPERR_BITS        0x00000100      /* RSPERR bits */
#define MMCA_RSPERR_CLEAR       0xFFFFFEFF      /* RSPERR clear mask */
#define MMCA_RSPERR_OFF         0x00000000      /* Flag off */
#define MMCA_RSPERR_ON          0x00000100      /* Error has been found in the response values of the response */
/* CRCSTO[4] - CRC Status Timeout */
#define MMCA_CRCSTO_BITS        0x00000010      /* CRCSTO bits */
#define MMCA_CRCSTO_CLEAR       0xFFFFFFEF      /* CRCSTO clear mask */
#define MMCA_CRCSTO_OFF         0x00000000      /* Flag off */
#define MMCA_CRCSTO_ON          0x00000010      /* CRC status could not be received */
/* WDATTO[3] - Write Data Timeout */
#define MMCA_WDATTO_BITS        0x00000008      /* WDATTO bits */
#define MMCA_WDATTO_CLEAR       0xFFFFFFF7      /* WDATTO clear mask */
#define MMCA_WDATTO_OFF         0x00000000      /* Flag off */
#define MMCA_WDATTO_ON          0x00000008      /* The busy status remains unchanged after the period set by SRWDTO in CLK_CTRL after the CRC status was received */
/* RDATTO[2] - Read Data Timeout */
#define MMCA_RDATTO_BITS        0x00000004      /* RDATTO bits */
#define MMCA_RDATTO_CLEAR       0xFFFFFFFB      /* RDATTO clear mask */
#define MMCA_RDATTO_OFF         0x00000000      /* Flag off */
#define MMCA_RDATTO_ON          0x00000004      /* Read data could not be received within the period set by SRWDTO */
/* RBSYTO[1] - Response Busy Timeout */
#define MMCA_RBSYTO_BITS        0x00000002      /* RBSYTO bits */
#define MMCA_RBSYTO_CLEAR       0xFFFFFFFD      /* RBSYTO clear mask */
#define MMCA_RBSYTO_OFF         0x00000000      /* Flag off */
#define MMCA_RBSYTO_ON          0x00000002      /* The busy status remains unchanged after the period set by SRBSYTO in CLK_CTRL after the command was transmitted */
/* RSPTO[0] - Response Timeout */
#define MMCA_RSPTO_BITS         0x00000001      /* RSPTO bits */
#define MMCA_RSPTO_CLEAR        0xFFFFFFFE      /* RSPTO clear mask */
#define MMCA_RSPTO_OFF          0x00000000      /* Flag off */
#define MMCA_RSPTO_ON           0x00000001      /* Response could not be received within the period set by SRSPTO in CLK_CTRL after the command was transmitted */


/************** INT_EN register **************/
/* MCMD12DRE[26] - CMD12DRE Interrupt Enable */
#define MMCA_MCMD12DRE_ENABLE   0x04000000  /* Enables interrupt output by the CMD12DRE flag */
#define MMCA_MCMD12DRE_DISABLE  0x00000000  /* Disables interrupt output by the CMD12DRE flag */
/* MCMD12RBE[25] - CMD12RBE Interrupt Enable */
#define MMCA_MCMD12RBE_ENABLE   0x02000000  /* Enables interrupt output by the CMD12RBE flag */
#define MMCA_MCMD12RBE_DISABLE  0x00000000  /* Disables interrupt output by the CMD12RBE flag */
/* MCMD12CRE[24] - CMD12CRE Interrupt Enable */
#define MMCA_MCMD12CRE_ENABLE   0x01000000  /* Enables interrupt output by the CMD12CRE flag */
#define MMCA_MCMD12CRE_DISABLE  0x00000000  /* Disables interrupt output by the CMD12CRE flag */
/* MDTRANE[23] - DTRANE Interrupt Enable */
#define MMCA_MDTRANE_ENABLE     0x00800000  /* Enables interrupt output by the DTRANE flag */
#define MMCA_MDTRANE_DISABLE    0x00000000  /* Disables interrupt output by the DTRANE flag */
/* MBUFRE[22] - BUFRE Interrupt Enable */
#define MMCA_MBUFRE_ENABLE      0x00400000  /* Enables interrupt output by the BUFRE flag */
#define MMCA_MBUFRE_DISABLE     0x00000000  /* Disables interrupt output by the BUFRE flag */
/* MBUFWEN[21] - BUFWEN Interrupt Enable */
#define MMCA_MBUFWEN_ENABLE     0x00200000  /* Enables interrupt output by the BUFWEN flag */
#define MMCA_MBUFWEN_DISABLE    0x00000000  /* Disables interrupt output by the BUFWEN flag */
/* MBUFREN[20] - BUFREN Interrupt Enable */
#define MMCA_MBUFREN_ENABLE     0x00100000  /* Enables interrupt output by the BUFREN flag */
#define MMCA_MBUFREN_DISABLE    0x00000000  /* Disables interrupt output by the BUFREN flag */
/* MRBSYE[17] - RBSYE Interrupt Enable */
#define MMCA_MRBSYE_ENABLE      0x00020000  /* Enables interrupt output by the RBSY flag */
#define MMCA_MRBSYE_DISABLE     0x00000000  /* Disables interrupt output by the RBSYE flag */
/* MCRSPE[16] - CRSPE Interrupt Enable */
#define MMCA_MCRSPE_ENABLE      0x00010000  /* Enables interrupt output by the CRSPE flag */
#define MMCA_MCRSPE_DISABLE     0x00000000  /* Disables interrupt output by the CRSPE flag */
/* MCMDVIO[15] - CMDVIO Interrupt Enable */
#define MMCA_MCMDVIO_ENABLE     0x00008000  /* Enables interrupt output by the CMDVIO flag */
#define MMCA_MCMDVIO_DISABLE    0x00000000  /* Disables interrupt output by the CMDVIO flag */
/* MBUFVIO[14] - BUFVIO Interrupt Enable */
#define MMCA_MBUFVIO_ENABLE     0x00004000  /* Enables interrupt output by the BUFVIO flag */
#define MMCA_MBUFVIO_DISABLE    0x00000000  /* Disables interrupt output by the BUFVIO flag */
/* MWDATERR[11] - WDATERR Interrupt Enable */
#define MMCA_MWDATERR_ENABLE    0x00000800  /* Enables interrupt output by the WDATERR flag */
#define MMCA_MWDATERR_DISABLE   0x00000000  /* Disables interrupt output by the WDATERR flag */
/* MRDATERR[10] - RDATERR Interrupt Enable */
#define MMCA_MRDATERR_ENABLE    0x00000400  /* Enables interrupt output by the RDATERR flag */
#define MMCA_MRDATERR_DISABLE   0x00000000  /* Disables interrupt output by the RDATERR flag */
/* MRIDXERR[9] - RIDXERR Interrupt Enable */
#define MMCA_MRIDXERR_ENABLE    0x00000200  /* Enables interrupt output by the RIDXERR flag */
#define MMCA_MRIDXERR_DISABLE   0x00000000  /* Disables interrupt output by the RIDXERR flag */
/* MRSPERR[8] - RSPERR Interrupt Enable */
#define MMCA_MRSPERR_ENABLE     0x00000100  /* Enables interrupt output by the RSPERR flag */
#define MMCA_MRSPERR_DISABLE    0x00000000  /* Disables interrupt output by the RSPERR flag */
/* MCRCSTO[4] - CRCSTO Interrupt Enable */
#define MMCA_MCRCSTO_ENABLE     0x00000010  /* Enables interrupt output by the CRCSTO flag */
#define MMCA_MCRCSTO_DISABLE    0x00000000  /* Disables interrupt output by the CRCSTO flag */
/* MWDATTO[3] - WDATTO Interrupt Enable */
#define MMCA_MWDATTO_ENABLE     0x00000008  /* Enables interrupt output by the WDATTO flag */
#define MMCA_MWDATTO_DISABLE    0x00000000  /* Disables interrupt output by the WDATTO flag */
/* MRDATTO[2] - RDATTO Interrupt Enable */
#define MMCA_MRDATTO_ENABLE     0x00000004  /* Enables interrupt output by the RDATTO flag */
#define MMCA_MRDATTO_DISABLE    0x00000000  /* Disables interrupt output by the RDATTO flag */
/* MRBSYTO[1] - RBSYTO Interrupt Enable */
#define MMCA_MRBSYTO_ENABLE     0x00000002  /* Enables interrupt output by the RBSYTO flag */
#define MMCA_MRBSYTO_DISABLE    0x00000000  /* Disables interrupt output by the RBSYTO flag */
/* MRSPTO[0] - RSPTO Interrupt Enable */
#define MMCA_MRSPTO_ENABLE      0x00000001  /* Enables interrupt output by the RSPTO flag */
#define MMCA_MRSPTO_DISABLE     0x00000000  /* Disables interrupt output by the RSPTO flag */

/************** HOST_STS1 register **************/
/* CMDSEQ[31] - Command Sequence in Progress */
#define MMCA_CMDSEQ_BITS        0x80000000  /* CMDSEQ bits */
#define MMCA_CMDSEQ_INIT        0x00000000  /* Command sequence is in the initial state */
#define MMCA_CMDSEQ_EXEC        0x80000000  /* Command sequence is being executed */
/* CMDSIG[31] - Command Sequence in Progress */
#define MMCA_CMDSIG_BITS        0x40000000  /* CMDSIG bits */
/* RSPIDX[29:24] - Response Index */
#define MMCA_RSPIDX_BITS        0x3F000000  /* RSPIDX bits */
/* DATSIG[23:16] - DAT[7:0] State */
#define MMCA_DATSIG_BITS        0x00FF0000  /* DATSIG bits */
/* RCVBLK[15:0] - Number of Transferred Blocks */
#define MMCA_RCVBLK_BITS        0x0000FFFF  /* RCVBLK bits */

/************** HOST_STS2 register **************/
/* CRCSTE[31] - CRC Status Error */
#define MMCA_HOST_CRCSTE_BITS   0x80000000  /* CRCSTE bits */
#define MMCA_HOST_CRCSTE_OFF    0x00000000  /* Flag OFF */
#define MMCA_HOST_CRCSTE_ON     0x80000000  /* Flag ON */
/* CRC16E[30] - Read Data CRC16 Error */
#define MMCA_CRC16E_BITS        0x40000000  /* CRC16E bits */
#define MMCA_CRC16E_OFF         0x00000000  /* Flag OFF */
#define MMCA_CRC16E_ON          0x40000000  /* Flag ON */
/* AC12CRCE[29] - Automatic CMD12 Response CRC7 Error */
#define MMCA_AC12CRCE_BITS      0x20000000  /* AC12CRCE bits */
#define MMCA_AC12CRCE_OFF       0x00000000  /* Flag OFF */
#define MMCA_AC12CRCE_ON        0x20000000  /* Flag ON */
/* RSPCRC7E[28] - Command Response CRC7 Error */
#define MMCA_RSPCRC7E_BITS      0x10000000  /* RSPCRC7E bits */
#define MMCA_RSPCRC7E_OFF       0x00000000  /* Flag OFF */
#define MMCA_RSPCRC7E_ON        0x10000000  /* Flag ON */
/* CRCSTEBE[27] - CRC Status End Bit Error */
#define MMCA_CRCSTEBE_BITS      0x08000000  /* CRCSTEBE bits */
#define MMCA_CRCSTEBE_OFF       0x00000000  /* Flag OFF */
#define MMCA_CRCSTEBE_ON        0x08000000  /* Flag ON */
/* RDATEBE[26] - Read Data End Bit Error */
#define MMCA_RDATEBE_BITS       0x04000000  /* RDATEBE bits */
#define MMCA_RDATEBE_OFF        0x00000000  /* Flag OFF */
#define MMCA_RDATEBE_ON         0x04000000  /* Flag ON */
/* AC12REBE[25] - Automatic CMD12 Response End Bit Error */
#define MMCA_AC12REBE_BITS      0x02000000  /* AC12REBE bits */
#define MMCA_AC12REBE_OFF       0x00000000  /* Flag OFF */
#define MMCA_AC12REBE_ON        0x02000000  /* Flag ON */
/* RSPEBE[24] - Command Response End Bit Error (Other than Auto CMD12) */
#define MMCA_RSPEBE_BITS        0x01000000  /* RSPEBE bits */
#define MMCA_RSPEBE_OFF         0x00000000  /* Flag OFF */
#define MMCA_RSPEBE_ON          0x01000000  /* Flag ON */
/* AC12IIDXE[23] - Automatic CMD12 Response Index Error */
#define MMCA_AC12IIDXE_BITS     0x00800000  /* AC12IIDXE bits */
#define MMCA_AC12IIDXE_OFF      0x00000000  /* Flag OFF */
#define MMCA_AC12IIDXE_ON       0x00800000  /* Flag ON */
/* RSPIDXE[22] - Command Response Index Error (Other Than Auto CMD12) */
#define MMCA_RSPIDXE_BITS       0x00400000  /* RSPIDXE bits */
#define MMCA_RSPIDXE_OFF        0x00000000  /* Flag OFF */
#define MMCA_RSPIDXE_ON         0x00400000  /* Flag ON */
/* BTACKPATE[21] - Boot Acknowledge Pattern Error */
#define MMCA_BTACKPATE_BITS     0x00200000  /* BTACKPATE bits */
#define MMCA_BTACKPATE_OFF      0x00000000  /* Flag OFF */
#define MMCA_BTACKPATE_ON       0x00200000  /* Flag ON */
/* BTACKEBE[20] - Boot Acknowledge End Bit Error */
#define MMCA_BTACKEBE_BITS      0x00100000  /* BTACKEBE bits */
#define MMCA_BTACKEBE_OFF       0x00000000  /* Flag OFF */
#define MMCA_BTACKEBE_ON        0x00100000  /* Flag ON */
/* CRCST[18:16] - CRC Status/Boot Acknowledge Pattern Indication */
#define MMCA_CRCST_BITS         0x00070000  /* CRCST bits */
/* STRDATTO[14] - Read Data Timeout (valid other than in boot operations */
#define MMCA_STRDATTO_BITS      0x00004000  /* STRDATTO bits */
#define MMCA_STRDATTO_OFF       0x00000000  /* Flag OFF */
#define MMCA_STRDATTO_ON        0x00004000  /* Flag ON */
/* DATBSYTO[13] -  Data Busy Timeout */
#define MMCA_DATBSYTO_BITS      0x00002000  /* DATBSYTO bits */
#define MMCA_DATBSYTO_OFF       0x00000000  /* Flag OFF */
#define MMCA_DATBSYTO_ON        0x00002000  /* Flag ON */
/* CRCSTTO[12] - CRC Status Timeout */
#define MMCA_CRCSTTO_BITS       0x00001000  /* CRCSTTO bits */
#define MMCA_CRCSTTO_OFF        0x00000000  /* Flag OFF */
#define MMCA_CRCSTTO_ON         0x00001000  /* Flag ON */
/* AC12BSYTO[11] - Automatic CMD12 Response Busy Timeout */
#define MMCA_AC12BSYTO_BITS     0x00000800  /* AC12BSYTO bits */
#define MMCA_AC12BSYTO_OFF      0x00000000  /* Flag OFF */
#define MMCA_AC12BSYTO_ON       0x00000800  /* Flag ON */
/* RSPBSYTO[10] - Response Busy Timeout */
#define MMCA_RSPBSYTO_BITS      0x00000400  /* RSPBSYTO bits */
#define MMCA_RSPBSYTO_OFF       0x00000000  /* Flag OFF */
#define MMCA_RSPBSYTO_ON        0x00000400  /* Flag ON */
/* AC12RSPTO[9] - Automatic CMD12 Response Timeout */
#define MMCA_AC12RSPTO_BITS     0x00000200  /* AC12RSPTO bits */
#define MMCA_AC12RSPTO_OFF      0x00000000  /* Flag OFF */
#define MMCA_AC12RSPTO_ON       0x00000200  /* Flag ON */
/* STRSPTO[8] - Response Timeout */
#define MMCA_STRSPTO_BITS       0x00000100  /* STRSPTO bits */
#define MMCA_STRSPTO_OFF        0x00000000  /* Flag OFF */
#define MMCA_STRSPTO_ON         0x00000100  /* Flag ON */
/* BTACKTO[7] - Boot Acknowledge Timeout */
#define MMCA_BTACKTO_BITS       0x00000080  /* BTACKTO bits */
#define MMCA_BTACKTO_OFF        0x00000000  /* Flag OFF */
#define MMCA_BTACKTO_ON         0x00000080  /* Flag ON */
/* 1STBTDATTO[6] - 1st Boot Data Timeout */
#define MMCA_1STBTDATTO_BITS    0x00000040  /* 1STBTDATTO bits */
#define MMCA_1STBTDATTO_OFF     0x00000000  /* Flag OFF */
#define MMCA_1STBTDATTO_ON      0x00000040  /* Flag ON */
/* BTDATTO[5] - Interval between boot Data Timeout */
#define MMCA_BTDATTO_BITS       0x00000020  /* BTDATTO bits */
#define MMCA_BTDATTO_OFF        0x00000000  /* Flag OFF */
#define MMCA_BTDATTO_ON         0x00000020  /* Flag ON */


/************** SWRESA register **************/
/* SWRST[31] - Software Reset */
#define MMCA_SWRST_BITS         0x80000000  /* SWRST bits */
#define MMCA_SWRST_CLR_RESET    0x00000000  /* Software reset cleared (normal operation) */
#define MMCA_SWRST_EXE_RESET    0x80000000  /* Executes software reset */

/************************************************************************************************
Typedefs
*************************************************************************************************/
typedef struct mmca_cmd_set_t2
{
    volatile 	uint32_t			datw		: 2;	/* Data Bus Width Setting */
    volatile 	uint32_t			RESERVED0	: 1;	/*  */
    volatile 	uint32_t			sbit		: 1;	/* Read Data Start Bit Detection Setting */
    volatile 	uint32_t			RESERVED1	: 2;	/*  */
    volatile 	uint32_t			opdm		: 1;	/* Open-Drain Output Mode */
    volatile 	uint32_t			tbit		: 1;	/* Transmission Bit Setting */
    volatile 	uint32_t			crcste		: 1;	/* CRC Status Reception */
    volatile 	uint32_t			bootack		: 1;	/* Receive Boot Acknowledge */
    volatile 	uint32_t			crc16c		: 1;	/* CRC16 Check in Reception */
    volatile 	uint32_t			RESERVED2	: 1;	/*  */
    volatile 	uint32_t			rcrc7c		: 2;	/* Response CRC7 Check */
    volatile 	uint32_t			ridxc		: 2;	/* Response Index Check */
    volatile 	uint32_t			cmd12en		: 1;	/* Automatic CMD12 Issuance */
    volatile 	uint32_t			cmlte		: 1;	/* Single/Multi Block Transfer Select */
    volatile 	uint32_t			dwen		: 1;	/* Read/Write */
    volatile 	uint32_t			wdat		: 1;	/* Presence/Absence of Data */
    volatile 	uint32_t			RESERVED3	: 1;	/*  */
    volatile 	uint32_t			rbsy		: 1;	/* Response Busy Select */
    volatile 	uint32_t			rtyp		: 2;	/* Response Type */
    volatile 	uint32_t			cmd			: 6;	/* Command Index */
    volatile 	uint32_t			boot		: 1;	/* Boot Operations */
    volatile 	uint32_t			RESERVED4	: 1;	/*  */
} mmca_cmd_set_t2;

typedef union mmca_cmd_set_t
{
    struct 		mmca_cmd_set_t2 	reg;
    volatile	uint32_t			u32;
} mmca_cmd_set_t;

typedef struct mmca_cmd_ctrl_t2
{
    volatile 	uint32_t			break_bit	: 1;	/* Forcible Termination of Command Sequence */
    volatile 	uint32_t			RESERVED0	:31;	/*  */
} mmca_cmd_ctrl_t2;

typedef union mmca_cmd_ctrl_t
{
    struct 		mmca_cmd_ctrl_t2 	reg;
    volatile	uint32_t			u32;
} mmca_cmd_ctrl_t;

typedef struct mmca_block_set_t2
{
    volatile 	uint32_t			blksiz		:16;	/* Transfer Block Size */
    volatile 	uint32_t			blkcnt		:16;	/* Number of Blocks for Transfer */
} mmca_block_set_t2;

typedef union mmca_block_set_t
{
    struct 		mmca_block_set_t2	reg;
    volatile	uint32_t			u32;
} mmca_block_set_t;

typedef struct mmca_clk_ctrl_t2
{
    volatile 	uint32_t			RESERVED0	: 4;	/*  */
    volatile 	uint32_t			srwdto		: 4;	/* Write Data/Read Data Timeout Setting */
    volatile 	uint32_t			srbsyto		: 4;	/* Response Busy Timeout Setting */
    volatile 	uint32_t			srspto		: 2;	/* Response Timeout Setting */
    volatile 	uint32_t			RESERVED1	: 2;	/*  */
    volatile 	uint32_t			clkdiv		: 4;	/* MMC Clock Frequency Setting */
    volatile 	uint32_t			RESERVED2	: 4;	/*  */
    volatile 	uint32_t			clken		: 1;	/* MMC Clock Output Control */
    volatile 	uint32_t			RESERVED3	: 6;	/*  */
    volatile 	uint32_t			mmcbusbsy	: 1;	/* MMC Clock Output control / Division setting prohibition */
} mmca_clk_ctrl_t2;

typedef union mmca_clk_ctrl_t
{
    struct 		mmca_clk_ctrl_t2	reg;
    volatile	uint32_t			u32;
} mmca_clk_ctrl_t;

typedef struct mmca_buf_acc_t2
{
    volatile 	uint32_t			RESERVED0	:16;	/*  */
    volatile 	uint32_t			atyp		: 1;	/* Buffer access selection */
    volatile 	uint32_t			RESERVED1	: 7;	/*  */
    volatile 	uint32_t			dmaren		: 1;	/* Buffer Read DMA Transfer Request Enable */
    volatile 	uint32_t			dmawen		: 1;	/* Buffer Write DMA Transfer Request Enable */
    volatile 	uint32_t			dmatyp		: 1;	/* DMA Transfer setting */
    volatile 	uint32_t			RESERVED2	: 5;	/*  */
} mmca_buf_acc_t2;

typedef union mmca_buf_acc_t
{
    struct 		mmca_buf_acc_t2		reg;
    volatile	uint32_t			u32;
} mmca_buf_acc_t;

typedef struct mmca_boot_t2
{
    volatile 	uint32_t			RESERVED0	:16;	/*  */
    volatile 	uint32_t			sbtdatto	: 4;	/* Interval Between Boot Data Timeout Setting */
    volatile 	uint32_t			s1stbtdatto	: 4;	/* 1st Boot Data Timeout Setting */
    volatile 	uint32_t			sbtackto	: 4;	/* Boot Acknowledge Timeout Setting */
    volatile 	uint32_t			btclkdiv	: 4;	/* MMC Clock Frequency Setting in Boot Mode */
} mmca_boot_t2;

typedef union mmca_boot_t
{
    struct 		mmca_boot_t2		reg;
    volatile	uint32_t			u32;
} mmca_boot_t;

typedef struct mmca_int_t2
{
    volatile 	uint32_t			rspto		: 1;	/* Response Timeout */
    volatile 	uint32_t			rbsyto		: 1;	/* Response Busy Timeout */
    volatile 	uint32_t			rdatto		: 1;	/* Read Data Timeout */
    volatile 	uint32_t			wdatto		: 1;	/* Write Data Timeout */
    volatile 	uint32_t			crcsto		: 1;	/* CRC Status Timeout */
    volatile 	uint32_t			RESERVED0	: 3;	/*  */
    volatile 	uint32_t			rsperr		: 1;	/* Response Error */
    volatile 	uint32_t			ridxerr		: 1;	/* Response Index Error */
    volatile 	uint32_t			rdaterr		: 1;	/* Read Data Error */
    volatile 	uint32_t			wdaterr		: 1;	/* Write Data Error */
    volatile 	uint32_t			RESERVED1	: 2;	/*  */
    volatile 	uint32_t			bufvio		: 1;	/* Buffer Access Error */
    volatile 	uint32_t			cmdvio		: 1;	/* Command Issuance Error */
    volatile 	uint32_t			crspe		: 1;	/* Command/Response Complete */
    volatile 	uint32_t			rbsye		: 1;	/* Response Busy Complete */
    volatile 	uint32_t			RESERVED2	: 2;	/*  */
    volatile 	uint32_t			bufren		: 1;	/* Buffer Read Ready */
    volatile 	uint32_t			bufwen		: 1;	/* Buffer Write Ready */
    volatile 	uint32_t			bufre		: 1;	/* Buffer Read Complete */
    volatile 	uint32_t			dtrane		: 1;	/* Data Transmission Complete */
    volatile 	uint32_t			cmd12cre	: 1;	/* Automatic CMD12 Response Complete */
    volatile 	uint32_t			cmd12rbe	: 1;	/* Automatic CMD12 Issuance Response Busy Complete */
    volatile 	uint32_t			cmd12dre	: 1;	/* Automatic CMD12 Issuance & Buffer Read Complete */
    volatile 	uint32_t			RESERVED3	: 5;	/*  */
} mmca_int_t2;

typedef union mmca_int_t
{
    struct 		mmca_int_t2			reg;
    volatile	uint32_t			u32;
} mmca_int_t;

typedef struct mmca_int_en_t2
{
    volatile 	uint32_t			mrspto		: 1;	/* RSPTO Interrupt Enable */
    volatile 	uint32_t			mrbsyto		: 1;	/* RBSYTO Interrupt Enable */
    volatile 	uint32_t			mrdatto		: 1;	/* RDATTO Interrupt Enable */
    volatile 	uint32_t			mwdatto		: 1;	/* WDATTO Interrupt Enable */
    volatile 	uint32_t			mcrcsto		: 1;	/* CRCSTO Interrupt Enable */
    volatile 	uint32_t			RESERVED0	: 3;	/*  */
    volatile 	uint32_t			mrsperr		: 1;	/* RSPERR Interrupt Enable */
    volatile 	uint32_t			mridxerr	: 1;	/* RIDXERR Interrupt Enable */
    volatile 	uint32_t			mrdaterr	: 1;	/* RDATERR Interrupt Enable */
    volatile 	uint32_t			mwdaterr	: 1;	/* WDATERR Interrupt Enable */
    volatile 	uint32_t			RESERVED1	: 2;	/*  */
    volatile 	uint32_t			mbufvio		: 1;	/* BUFVIO Interrupt Enable */
    volatile 	uint32_t			mcmdvio		: 1;	/* CMDVIO Interrupt Enable */
    volatile 	uint32_t			mcrspe		: 1;	/* CRSPE Interrupt Enable */
    volatile 	uint32_t			mrbsye		: 1;	/* RBSYE Interrupt Enable */
    volatile 	uint32_t			RESERVED2	: 2;	/*  */
    volatile 	uint32_t			mbufren		: 1;	/* BUFREN Interrupt Enable */
    volatile 	uint32_t			mbufwen		: 1;	/* BUFWEN Interrupt Enable */
    volatile 	uint32_t			mbufre		: 1;	/* BUFRE Interrupt Enable */
    volatile 	uint32_t			mdtrane		: 1;	/* DTRANE Interrupt Enable */
    volatile 	uint32_t			mcmd12cre	: 1;	/* CMD12CRE Interrupt Enable */
    volatile 	uint32_t			mcmd12rbe	: 1;	/* CMD12RBE Interrupt Enable */
    volatile 	uint32_t			mcmd12dre	: 1;	/* CMD12DRE Interrupt Enable */
    volatile 	uint32_t			RESERVED3	: 5;	/*  */
} mmca_int_en_t2;

typedef union mmca_int_en_t
{
    struct 		mmca_int_en_t2		reg;
    volatile	uint32_t			u32;
} mmca_int_en_t;

typedef struct mmca_host_sts1_t2
{
    volatile 	uint32_t			rcvblk		:16;	/* Number of Transferred Blocks */
    volatile 	uint32_t			datsig		: 8;	/* MMCAnDAT[7:0] State */
    volatile 	uint32_t			rspidx		: 6;	/* Response Index */
    volatile 	uint32_t			cmdsig		: 1;	/* MMCAnCMD State */
    volatile 	uint32_t			cmdseq		: 1;	/* Command Sequence in Progress */
} mmca_host_sts1_t2;

typedef union mmca_host_sts1_t
{
    struct 		mmca_host_sts1_t2	reg;
    volatile	uint32_t			u32;
} mmca_host_sts1_t;

typedef struct mmca_host_sts2_t2
{
    volatile 	uint32_t			RESERVED0	: 5;	/*  */
    volatile 	uint32_t			btdatto		: 1;	/* Interval between Boot Data Timeout */
    volatile 	uint32_t			fstbtdatto	: 1;	/* 1st Boot Data Timeout */
    volatile 	uint32_t			btackto		: 1;	/* Boot Acknowledge Timeout */
    volatile 	uint32_t			strspto		: 1;	/* Response Timeout */
    volatile 	uint32_t			ac12rspto	: 1;	/* Automatic CMD12 Response Timeout */
    volatile 	uint32_t			rspbsyto	: 1;	/* Response Busy Timeout */
    volatile 	uint32_t			ac12bsyto	: 1;	/* Automatic CMD12 Response Busy Timeout */
    volatile 	uint32_t			crcstto		: 1;	/* CRC Status Timeout */
    volatile 	uint32_t			datbsyto	: 1;	/* Data Busy Timeout */
    volatile 	uint32_t			strdatto	: 1;	/* Read Data Timeout */
    volatile 	uint32_t			RESERVED1	: 1;	/*  */
    volatile 	uint32_t			crcst		: 3;	/* CRC Status/Boot Acknowledge Pattern Indication */
    volatile 	uint32_t			RESERVED2	: 1;	/*  */
    volatile 	uint32_t			btackebe	: 1;	/* Boot Acknowledge End Bit Error */
    volatile 	uint32_t			btackpate	: 1;	/* Boot Acknowledge Pattern Error */
    volatile 	uint32_t			rspidxe		: 1;	/* Command Response Index Error */
    volatile 	uint32_t			ac12idxe	: 1;	/* Automatic CMD12 Response Index Error */
    volatile 	uint32_t			rspebe		: 1;	/* Command Response End Bit Error */
    volatile 	uint32_t			ac12rebe	: 1;	/* Automatic CMD12 Response End Bit Error */
    volatile 	uint32_t			rdatebe		: 1;	/* Read Data End Bit Error */
    volatile 	uint32_t			crcstebe	: 1;	/* CRC Status End Bit Error */
    volatile 	uint32_t			rspcrc7e	: 1;	/* Command Response CRC7 Error */
    volatile 	uint32_t			ac12crce	: 1;	/* Automatic CMD12 Response CRC7 Error */
    volatile 	uint32_t			crc16e		: 1;	/* Read Data CRC16 Error */
    volatile 	uint32_t			crcste		: 1;	/* CRC Status Error */
} mmca_host_sts2_t2;

typedef union mmca_host_sts2_t
{
    struct 		mmca_host_sts2_t2	reg;
    volatile	uint32_t			u32;
} mmca_host_sts2_t;

typedef struct mmca_swresa_t2
{
    volatile 	uint32_t			RESERVED0	:31;	/*  */
    volatile 	uint32_t			swrst		: 1;	/* Software Reset */
} mmca_swresa_t2;

typedef union mmca_swresa_t
{
    struct 		mmca_swresa_t2		reg;
    volatile	uint32_t			u32;
} mmca_swresa_t;

typedef struct mmca_t
{
    union 		mmca_cmd_set_t		cmd_set;			/* MMCAn Command Setting Register */
    volatile 	uint32_t   			RESERVED0;			/*  */
    volatile	uint32_t			arg;				/* MMCAn Argument Register */
    volatile	uint32_t			arg_cmd12;			/* MMCAn Argument Register for Automatically-Issued CMD12 */
    union		mmca_cmd_ctrl_t		cmd_ctrl;			/* MMCAn Command Control Register */
    union		mmca_block_set_t	block_set;			/* MMCAn Transfer Block Setting Register */
    union		mmca_clk_ctrl_t		clk_ctrl;			/* MMCAn Clock Control Register */
    union		mmca_buf_acc_t		buf_acc;			/* MMCAn Buffer Access Configuration Register */
    volatile	uint32_t			resp3;				/* MMCAn Response Register 3 */
    volatile	uint32_t			resp2;				/* MMCAn Response Register 2 */
    volatile	uint32_t			resp1;				/* MMCAn Response Register 1 */
    volatile	uint32_t			resp0;				/* MMCAn Response Register 0 */
    volatile	uint32_t			resp_cmd12;			/* MMCAn Response Register for Automatically-Issued CMD12 */
    volatile	uint32_t			data;				/* MMCAn Data Register */
    volatile	uint32_t			RESERVED1;			/*  */
    union		mmca_boot_t			boot;				/* MMCAn Boot Operation Setting Register */
    union		mmca_int_t			int_reg;			/* MMCAn Interrupt Flag Register */
    union		mmca_int_en_t		int_en;				/* MMCAn Interrupt Enable Register */
    union		mmca_host_sts1_t	host_sts1;			/* MMCAn Status Register 1 */
    union		mmca_host_sts2_t	host_sts2;			/* MMCAn Status Register 2 */
    volatile	uint32_t			RESERVED2[11];		/*  */
    union		mmca_swresa_t		swresa;				/* MMCAn Software Reset Register */
} mmca_t;

typedef struct mmca_attributes_t
{
    union 		mmca_cmd_set_t		cmd_set;			/* Command */
    volatile	uint32_t			arg;				/* Argument */
    volatile	uint32_t*			data;				/* Data pointer */
    union		mmca_block_set_t	block_set;			/* Data block size and count */
} mmca_attributes_t;

typedef void mmca_int_function_t(void);

/***************************************************************************************
  Enumeration definitions
***************************************************************************************/
typedef enum
{
    MMCA_STATE_0		= 0,
    MMCA_STATE_1		= 1,
    MMCA_STATE_2		= 2,
    MMCA_STATE_3		= 3,
    MMCA_STATE_4		= 4,
    MMCA_STATE_5		= 5,
    MMCA_STATE_6		= 6,
    MMCA_STATE_7		= 7,
    MMCA_STATE_8		= 8,
    MMCA_STATE_9		= 9
} mmca_state_t;




/***************************************************************************************
Variables
***************************************************************************************/
static struct mmca_t *mmca_p = (mmca_t *) MMCA0_BASE_ADDRESS;

/***************************************************************************************
Public functions
***************************************************************************************/
void R_MMCA_IrqDefault(void);
void R_MMCA_Interrupt(void);
void R_MMCA_Init(void);
void R_MMCA_EnableInterrupt(mmca_int_function_t *mmca_int_function_p);
void R_MMCA_Reset(void);
void R_MMCA_SetLowSpeed(void);
void R_MMCA_SetHighSpeed(void);
void R_MMCA_SendCommand(mmca_attributes_t* attr);


#endif
