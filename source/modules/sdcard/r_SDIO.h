/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2023 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/* Warranty Disclaimer                                                       */
/*                                                                           */
/* Because the Product(s) is licensed free of charge, there is no warranty   */
/* of any kind whatsoever and expressly disclaimed and excluded by Renesas,  */
/* either expressed or implied, including but not limited to those for       */
/* non-infringement of intellectual property, merchantability and/or         */
/* fitness for the particular purpose.                                       */
/* Renesas shall not have any obligation to maintain, service or provide bug */
/* fixes for the supplied Product(s) and/or the Application.                 */
/*                                                                           */
/* Each User is solely responsible for determining the appropriateness of    */
/* using the Product(s) and assumes all risks associated with its exercise   */
/* of rights under this Agreement, including, but not limited to the risks   */
/* and costs of program errors, compliance with applicable laws, damage to   */
/* or loss of data, programs or equipment, and unavailability or             */
/* interruption of operations.                                               */
/*                                                                           */
/* Limitation of Liability                                                   */
/*                                                                           */
/* In no event shall Renesas be liable to the User for any incidental,       */
/* consequential, indirect, or punitive damage (including but not limited    */
/* to lost profits) regardless of whether such liability is based on breach  */
/* of contract, tort, strict liability, breach of warranties, failure of     */
/* essential purpose or otherwise and even if advised of the possibility of  */
/* such damages. Renesas shall not be liable for any services or products    */
/* provided by third party vendors, developers or consultants identified or  */
/* referred to the User by Renesas in connection with the Product(s) and/or  */
/* the Application.                                                          */
/*                                                                           */
/*===========================================================================*/
/* Module :  r_SDIO.c                                                        */
/* History:                                                                  */
/*              V1.00: Initial version                                       */
/*                                                                           */
/*===========================================================================*/
/* Description:                                                              */
/* Header file.                                                              */
/*                                                                           */
/*===========================================================================*/

#ifndef __SDIO_H__
#define __SDIO_H__
/*******************************************************************************
  Includes
*******************************************************************************/
#include "inc\common.h"
#include "drivers\mmca\r_MMCA.h"
#include "thirdparty\fatfs\ff.h"
#include "thirdparty\shell\shell.h"

/*******************************************************************************
  Defines
*******************************************************************************/
/* Configurations */
#define SDIO_SLOW_CONFIG        SDIO_CLKEN_ENABLE | SDIO_CLKDIV_256 | SDIO_SRSPTO_256 | SDIO_SRBSYTO_29 | SDIO_SRWDTO_29 // 80MHz / 2^8 = 312.5kHz
#define SDIO_FAST_CONFIG        SDIO_CLKEN_ENABLE | SDIO_CLKDIV_2   | SDIO_SRSPTO_256 | SDIO_SRBSYTO_29 | SDIO_SRWDTO_29 // 80MHz / 2^1 = 40MHz
#define SDIO_BUS_WIDTH          0x00000002      /* [31:2] Stuff bits = 0b0000000000000000000000000000000 */
                                                /* [1:0] bus width = 0b10 (4 bits bus) */
#define SDIO_CMD8_ARG			0x000001FF		/* RESERVED0 = 0, pcie_12v_sup = 0, pcie_avail = 0, vhs = SDIO_VHS_27_36V, check_pattern = SDIO_CHECK_FF  */
#define SDIO_ACMD41_ARG			0x50100000		/* busy = 0, hcs = SDIO_HCS_SDHC_SDXC, fb = 0, xpc = SDIO_XPC_MAX_PERFORMANCE, ho2t = 0, RESERVED0 = 0, s18r = SDIO_S18R_CURRENT_VOLTAGE, vdd_vw = SDIO_OCR_32V_33V */

/* SDIO commands (4-bits DAT) */
#define CMD0      	0x00000000  /* GO_IDLE_STATE */
#define CMD2        0x02806000  /* ALL_SEND_CID */
#define CMD3        0x03400000  /* SET_RELATIVE_ADDR */
#define CMD4        0x04000000  /* SET_DSR */
#define CMD5        0x05400000  /* IO_SEND_OP_COND */
#define CMD6        0x06480001  /* SWITCH_FUNC */
#define CMD7        0x07400000  /* SELECT/DESELECT_CARD */
#define CMD7_R1B    0x07600000  /* Response R1B is expected only from the selected card */
#define CMD8		0x08400000	/* SEND_IF_COND */
#define CMD9        0x09806000  /* SEND_CSD */
#define CMD10       0x0A806000  /* SEND_CID */
#define CMD11       0x0B400000  /* VOLTAGE_SWITCH */
#define CMD12       0x0C600000  /* STOP_TRANSMISSION */
#define CMD13       0x0D400000  /* SEND_STATUS/SEND_TASK_STATUS */
#define CMD15       0x0F000000  /* GO_INACTIVE_STATE */
#define CMD16       0x10400000  /* SET_BLOCKLEN */
#define CMD17       0x11480001  /* READ_SINGLE_BLOCK */
#define CMD18_O     0x124B0001  /* READ_MULTIPLE_BLOCK, Open End */
#define CMD18		0x124A0001  /* READ_MULTIPLE_BLOCK, Pre-Defined */
#define CMD19       0x134C0101  /* SEND_TUNING_BLOCK */
//#define CMD20     0x14  /* SPEED_CLASS_CONTROL */
//#define CMD22     0x16  /* ADDRESS_EXTENSION */
#define CMD23       0x17400000  /* SET_BLOCK_COUNT */
#define CMD24       0x184C0001  /* WRITE_BLOCK */
#define CMD25_O     0x194F0001  /* WRITE_MULTIPLE_BLOCK, Open End */
#define CMD25     	0x194E0001  /* WRITE_MULTIPLE_BLOCK, Pre-Defined */
#define CMD27       0x1B4C0001  /* PROGRAM_CSD */
#define CMD28       0x1C600000  /* SET_WRITE_PROT */
#define CMD29       0x1D600000  /* CLR_WRITE_PROT */
#define CMD30       0x1E480001  /* SEND_WRITE_PROT */
#define CMD32       0x20400000  /* ERASE_WR_BLK_START */
#define CMD33       0x21400000  /* ERASE_WE_BLK_END */
#define CMD38       0x26600000  /* ERASE */
//#define CMD40     0x28  /* Defined by DPS Spec. */
#define CMD42       0x2A4C0001  /* LOCK_UNLOCK */
//#define CMD43     0x2B  /* Q_MANAGEMENT */
//#define CMD44     0x2C  /* Q_TASK_INFO_A */
//#define CMD45     0x2D  /* Q_TASK_INFO_B */
//#define CMD46     0x2E  /* Q_RD_TASK */
//#define CMD47     0x2F  /* Q_WR_TASK */
//#define CMD48     0x30  /* READ_EXTR_SINGLE */
//#define CMD49     0x31  /* WRITE_EXTR_SINGLE */
#define CMD52       0x34400000  /* IO_RW_DIRECT */
#define CMD53       0x35000000  /* IO_RW_EXTENDED, */    /* WARNING: Wrong CMD53 value, it has different variations,*/
                                                         /* must be used with care and modified according to needs. */
//#define CMD54     0x36  /* SDIO Specific */
#define CMD55       0x37400000  /* APP_CMD */
#define CMD56_R     0x38480001  /* GEN_CMD, Read */
#define CMD56_W     0x384C0001  /* GEN_CMD, Write */
//#define CMD58     0x3A  /* READ_EXTR_MULTI */
//#define CMD59     0x3B  /* WRITE_EXTR_MULTI */
#define ACMD6       0x06400000  /* SET_BUS_WIDTH */
#define ACMD13      0x0D480001  /* SD_STATUS */
#define ACMD22      0x16480001  /* SEND_NUM_WR_BLOCKS */
#define ACMD23      0x17400000  /* SET_WR_BLK_ERASE_COUNT */
#define ACMD41		0x29405000  /* SD_SEND_OP_COND */
#define ACMD42      0x2A400000  /* SET_CLR_CARD_DETECT */
#define ACMD51      0x33480001  /* SEND_SCR */




/* VHS: Voltage Supplied */
#define SDIO_VHS_27_36V             1  /* 2.7-3.6V */
#define SDIO_VHS_LOW_VOLTAGE        2  /* Reserved for Low Voltage Range */
/* Check pattern */
#define SDIO_CHECK_00               0x00  /* Pattern: 0x00 */
#define SDIO_CHECK_FF               0xFF  /* Pattern: 0xFF */

/* HCS: Host Capacity Support */
#define SDIO_HCS_SDSC               0  /* SDSC Only Host */
#define SDIO_HCS_SDHC_SDXC          1  /* SDHC or SDXC Supported */
/* XPC: SDXC Power Control */
#define SDIO_XPC_POWER_SAVING       0  /* Power Saving */
#define SDIO_XPC_MAX_PERFORMANCE    1  /* Maximum Performance */
/* S18R: Switching to 1.8V Request */
#define SDIO_S18R_CURRENT_VOLTAGE   0  /* Use current signal voltage */
#define SDIO_S18R_SWITCH_TO_18V     1  /* Switch to 1.8V signal voltage */
/* OCR VDD voltage Window */
#define SDIO_OCR_35V_36V            0x800000  /* 3.5-3.6V */
#define SDIO_OCR_34V_35V            0x400000  /* 3.4-3.5V */
#define SDIO_OCR_33V_34V            0x200000  /* 3.3-3.4V */
#define SDIO_OCR_32V_33V            0x100000  /* 3.2-3.3V */
#define SDIO_OCR_31V_32V            0x080000  /* 3.1-3.2V */
#define SDIO_OCR_30V_31V            0x040000  /* 3.0-3.1V */
#define SDIO_OCR_29V_30V            0x020000  /* 2.9-3.0V */
#define SDIO_OCR_28V_29V            0x010000  /* 2.8-2.9V */
#define SDIO_OCR_27V_28V            0x008000  /* 2.7-2.8V */

/* BUSY: Busy Status */
#define SDIO_BUSY_ON_INIT           0  /* On Initialization */
#define SDIO_BUSY_INIT_COMPLETE     1  /* Initialization Complete */
/* CCS: Card Capacity Status */
#define SDIO_CCS_SDSC               0  /* SDSC */
#define SDIO_CCS_SDHC_SDXC          1  /* SDHC or SDXC */
/* S18A: Switching to 1.8V Accepted */
#define SDIO_S18A_CURRENT_VOLTAGE   0  /* Continues current voltage signaling */
#define SDIO_S18A_READY_SWITCH      1  /* Ready for switching signal voltage */

/*******************************************************************************
  Enumeration definitions
*******************************************************************************/
typedef enum
{
    SDIO_OK			= 0,
    SDIO_BUSY		= 1,
    SDIO_ERROR
} sdio_status_t;

typedef enum
{
    SDIO_TEST_OK			= 0,
    SDIO_TEST_ERROR		= 1,
    SDIO_TEST_NO_CARD  =   2
} sdio_test_result_t;

typedef enum
{
    SDIO_STATE_INIT 		= 0,
    SDIO_STATE_INIT_DELAYED,
    SDIO_STATE_IDLE,
    SDIO_STATE_READY,
    SDIO_STATE_IDENTIFICATION,
    SDIO_STATE_STANDBY,
    SDIO_STATE_IDENTIFICATION_CSD,
    SDIO_STATE_TRANSFER,
    SDIO_STATE_SENDING_DATA,
    SDIO_STATE_RECEIVE_DATA,
    SDIO_STATE_PROGRAMMING,
    SDIO_STATE_DISCONNECT,
    SDIO_STATE_INACTIVE
} sdio_state_t;

typedef enum
{
    SDIO_STEP_0	= 0,
    SDIO_STEP_1,
    SDIO_STEP_2,
    SDIO_STEP_3,
    SDIO_STEP_4,
    SDIO_STEP_5,
    SDIO_STEP_6,
    SDIO_STEP_7,
    SDIO_STEP_8,
    SDIO_STEP_9
} sdio_step_t;

typedef enum
{
    SDIO_WAITING = 0,
    SDIO_READ_SINGLE,
    SDIO_READ_MULTI,
    SDIO_WRITE_SINGLE,
    SDIO_WRITE_MULTI
} sdio_tx_type_t;

/*******************************************************************************
  Type definitions
*******************************************************************************/
typedef struct sdio_cmd6_t2{
    uint32_t function_g1  	: 4; /* Function group 1 for Access Mode */
    uint32_t function_g2  	: 4; /* Function group 2 for Command System */
    uint32_t function_g3  	: 4; /* Function group 3 for Drive Strength */
    uint32_t function_g4  	: 4; /* Function group 4 for Power Limit */
    uint32_t function_g5  	: 4; /* Function group 5 for RESERVED */
    uint32_t function_g6  	: 4; /* Function group 6 for RESERVED  */
    uint32_t RESERVED0   	: 7; /* RESERVED (All '0') */
    uint32_t mode      		: 1; /* Mode: 0 - Check function, 1 - Switch function */
}sdio_cmd6_t2;

typedef union sdio_cmd6_t{
    struct 		sdio_cmd6_t2 	reg;
    volatile	uint32_t 		u32;
} sdio_cmd6_t;

typedef struct sdio_cmd8_t2{
    uint32_t check_pattern  : 8; /* Check Pattern */
    uint32_t vhs            : 4; /* VHS: Voltage Supplied */
    uint32_t pcie_avail     : 1; /* PCIe Availability */
    uint32_t pcie_12v_sup   : 1; /* PCIe 1.2V Support */
    uint32_t RESERVED0      :18;	
}sdio_cmd8_t2;

typedef union sdio_cmd8_t{
    struct 		sdio_cmd8_t2 	reg;
    volatile	uint32_t 		u32;
} sdio_cmd8_t;

typedef struct sdio_acmd41_t2{
    uint32_t vdd_vw     :24; /* OCR VDD voltage Window */
    uint32_t s18r       : 1; /* S18R: Switching to 1.8V Request */
    uint32_t RESERVED0  : 2;
    uint32_t ho2t       : 1; /* HO2T: Host Capacity Support 2 */
    uint32_t xpc        : 1; /* XPC: SDXC Power Control */
    uint32_t fb         : 1; /* FB: Fast Boot (reserved for eSD) */
    uint32_t hcs        : 1; /* HCS: Host Capacity Support */
    uint32_t busy       : 1; /* Busy: must be 0 */
} sdio_acmd41_t2;

typedef union sdio_acmd41_t{
    struct 		sdio_acmd41_t2 	reg;
    volatile	uint32_t 		u32;
} sdio_acmd41_t;

typedef struct sdio_r1_t2{
    uint32_t RESERVED0          : 3;
    uint32_t ake_seq_error      : 1; /* Error in the sequence of the authentication process */
    uint32_t RESERVED1          : 1;
    uint32_t app_cmd            : 1; /* The card will expect ACMD, or an indication that the command has benn interpreted as ACMD */
    uint32_t fx_event           : 1; /* Extension Functions may set this bit to get host to deal with events */
    uint32_t RESERVED2          : 1;
    uint32_t ready_for_data     : 1; /* Corresponds to buffer empty signaling on the bus */
    uint32_t current_state      : 4; /* The state of the card when receiving the command */
    uint32_t erase_reset        : 1; /* An erase sequence was cleared before executing because an out of erase sequence command was received */
    uint32_t card_ecc_disabled  : 1; /* The command has been executed without using the internal ECC */
    uint32_t wp_erase_skip      : 1; /* Set when only partial address space was erased due to existing write protected blocks or the temporary or permanent write protected card was erased */
    uint32_t csd_overwrite      : 1; /* Can be either one of the following errors: The read only section of the CSD does not match the card content, or an attempt to reverse the copy or permanent WP bits was made */
    uint32_t deferred_response  : 1; /* Refer to eSD Addendum */
    uint32_t RESERVED3          : 1;
    uint32_t error              : 1; /* A general or an unknown error occurred during the operation */
    uint32_t cc_error           : 1; /* Internal card controller error */
    uint32_t card_ecc_failed    : 1; /* Card internal ECC was applied but failed to correct the data */
    uint32_t illegal_command    : 1; /* Command not legal for the card state */
    uint32_t com_crc_error      : 1; /* The CRC check of the previous command failed */
    uint32_t lock_unlock_failed : 1; /* Set when a sequence or password error has been detected in lock/unlock card command */
    uint32_t card_is_locked     : 1; /* When set, signals that the card is locked by the host */
    uint32_t wp_violation       : 1; /* Set when the host attempts to write to a protected block or to the temporary or permanent write protected card */
    uint32_t erase_param        : 1; /* An invalid selection of write-blocks for erase occurred */
    uint32_t erase_seq_error    : 1; /* An error in the sequence of erase commands occurred */
    uint32_t block_len_error    : 1; /* The transferred block length is not allowed for this card, or the number of transferred bytes does not match the block length */
    uint32_t address_error      : 1; /* A misaligned address which did not match the block length was used in the command */
    uint32_t out_of_range       : 1; /* The command's argument was out of the allowed range for this card */
} sdio_r1_t2;

typedef union sdio_r1_t{
    struct 		sdio_r1_t2		reg;
    volatile	uint32_t 		u32;
} sdio_r1_t;


typedef struct sdio_r2_csd_t{   /* CSD version 2.0 */
    uint64_t NOT_USED           :  1; /* NOT USED, ALWAYS 1 */
    uint64_t crc                :  7; /* CRC */
    uint64_t RESERVED1          :  1; /* not used, always '0' */
    uint64_t wp_upc             :  1; /* Write protect until power cycle */
    uint64_t file_format        :  2; /* File format. Value 00b */
    uint64_t tmp_write_protect  :  1; /* Temporary write protection */
    uint64_t perm_write_protect :  1; /* Permanent write protection */
    uint64_t copy               :  1; /* Copy flag */
    uint64_t file_format_grp    :  1; /* File format group */
    uint64_t RESERVED2          :  5;
    uint64_t write_bl_partial   :  1; /* Partial blocks for write allowed */
    uint64_t write_bl_len       :  4; /* Max. write data block length */
    uint64_t r2w_factor         :  3; /* Write speed factor */
    uint64_t RESERVED3          :  2;
    uint64_t wp_grp_enable      :  1; /* Write protect group enable */
    uint64_t wp_grp_size        :  7; /* Write protect group size */
    uint64_t sector_size        :  7; /* erase sector size */
    uint64_t erase_blk_en       :  1; /* erase single block enable */
    uint64_t RESERVED4          :  1;
    
    /* csize needs to be splitted here as it would go over 64bit boundary */
    uint64_t c_size_high_16bits : 16; /* device size (higher 16bits) */

    /* <-- 64bit boundary here */

    uint64_t c_size_low_6bits   :  6; /* device size (lower 6bits) */

    uint64_t RESERVED5          :  6;
    uint64_t dsr_imp            :  1; /* DSR implemented */
    uint64_t read_blk_misalign  :  1; /* Read block misalignment */
    uint64_t write_blk_misalign :  1; /* Write block misalignment */
    uint64_t read_bl_partial    :  1; /* Partial blocks for read allowed */
    uint64_t read_bl_len        :  4; /* Max. read data block length */
    uint64_t ccc                : 12; /* Card command classes */
    uint64_t tran_speed         :  8; /* Max. data transfer rate */
    uint64_t nsac               :  8; /* Data read access-time in CLK cycles *NSAC*100) */
    uint64_t taac               :  8; /* Data read access-time */
    uint64_t RESERVED6          :  6;
    uint64_t csd_structure      :  2; /* CSD structure */   
} sdio_r2_csd_t;



typedef struct sdio_r2_cid_t{
    uint64_t NOT_USED           : 1; /* NOT USED, ALWAYS 1 */
    uint64_t crc                : 7; /* CRC7 checksum */
    uint64_t mdt                :12; /* Manufacturing date */
    uint64_t RESERVED           : 4;
    uint64_t psn                :32; /* Product serial number */
    uint64_t prv                : 8; /* Product revision */
    uint64_t pnm                :40; /* Product name */
    uint64_t oid                :16; /* OEM/Application ID */
    uint64_t mid                : 8; /* Manufacturer ID */
} sdio_r2_cid_t;


typedef union sdio_r2_t{
    struct 		sdio_r2_csd_t	csd;
    struct 		sdio_r2_cid_t	cid;
    volatile	uint32_t 		u32[4];
} sdio_r2_t;

typedef struct sdio_r3_t2{
    uint32_t vdd_vw             :24; /* OCR VDD voltage Window */
    uint32_t s18a               : 1; /* S18A: Switching to 1.8V Accepted */
    uint32_t RESERVED0          : 2; 
    uint32_t co2t               : 1; /* CO2T: Card Capacity Status 2 */
    uint32_t RESERVED1          : 1; 
    uint32_t uhs_ii             : 1; /* UHS-II: UHS-II Card Status */
    uint32_t ccs                : 1; /* CCS: Card Capacity Status */
    uint32_t busy               : 1; /* Busy: Busy status */
} sdio_r3_t2;

typedef union sdio_r3_t{
    struct 		sdio_r3_t2 		reg;
    volatile	uint32_t 		u32;
} sdio_r3_t;

typedef struct sdio_r6_t2{
    uint32_t RESERVED0          : 3;
    uint32_t ake_seq_error      : 1; /* Error in the sequence of the authentication process */
    uint32_t RESERVED1          : 1;
    uint32_t app_cmd            : 1; /* The card will expect ACMD, or an indication that the command has benn interpreted as ACMD */
    uint32_t fx_event           : 1; /* Extension Functions may set this bit to get host to deal with events */
    uint32_t RESERVED2          : 1;
    uint32_t ready_for_data     : 1; /* Corresponds to buffer empty signaling on the bus */
    uint32_t current_state      : 4; /* The state of the card when receiving the command */
    uint32_t error              : 1; /* A general or an unknown error occurred during the operation */
    uint32_t illegal_command    : 1; /* Command not legal for the card state */
    uint32_t com_crc_error      : 1; /* The CRC check of the previous command failed */
    uint32_t rca                :16; /* New published RCA of the card */
} sdio_r6_t2;

typedef union sdio_r6_t{
    struct 		sdio_r6_t2		reg;
    volatile	uint32_t 		u32;
} sdio_r6_t;

typedef struct sdio_r7_t2{
    uint32_t echo_pattern       : 8; /* Echo-back of check pattern */
    uint32_t vha                : 4; /* VHA: Voltage accepted */
    uint32_t pcie_resp          : 1; /* PCIe Response */
    uint32_t pcie_12v_sup       : 1; /* PCIe 1.2V Support */
    uint32_t RESERVED0          :18;
} sdio_r7_t2;

typedef union sdio_r7_t{
    struct sdio_r7_t2 			reg;
    uint32_t 					u32;
} sdio_r7_t;

typedef struct sdio_sw_function_sts_t2{
    // [511:480]
    uint32_t supp_bits_fg6		:16; /* Support Bits of Functions in Function Group 6 */
    uint32_t max_current		:16; /* Maximum Current/Power Consumption */
    // [479:448]
    uint32_t supp_bits_fg4		:16; /* Support Bits of Functions in Function Group 4 */
    uint32_t supp_bits_fg5		:16; /* Support Bits of Functions in Function Group 5 */
    // [447:416]
    uint32_t supp_bits_fg2		:16; /* Support Bits of Functions in Function Group 2 */
    uint32_t supp_bits_fg3		:16; /* Support Bits of Functions in Function Group 3 */
    // [415:384]
    uint32_t func_sel_fg3		: 4; /* Function Selection of Function Group 3 */
    uint32_t func_sel_fg4		: 4; /* Function Selection of Function Group 4 */
    uint32_t func_sel_fg5		: 4; /* Function Selection of Function Group 5 */
    uint32_t func_sel_fg6		: 4; /* Function Selection of Function Group 6 */
    uint32_t supp_bits_fg1		:16; /* Support Bits of Functions in Function Group 1 */
    // [383:352]
    uint32_t busy_sts_fg6		:16; /* Reserved for Busy Status of functions in group 6 */
    uint32_t data_struct_ver	: 8; /* Data Structure Version */
    uint32_t func_sel_fg1		: 4; /* Function Selection of Function Group 1 */
    uint32_t func_sel_fg2		: 4; /* Function Selection of Function Group 2 */
    // [351:320]
    uint32_t busy_sts_fg4		:16; /* Reserved for Busy Status of functions in group 4 */
    uint32_t busy_sts_fg5		:16; /* Reserved for Busy Status of functions in group 5 */
    // [319:288]
    uint32_t busy_sts_fg2		:16; /* Busy Status of functions in group 2 */
    uint32_t busy_sts_fg3		:16; /* Reserved for Busy Status of functions in group 3 */
    // [287:256]
    uint32_t RESERVED0			:16; /* Reserved (All '0') */
    uint32_t busy_sts_fg1		:16; /* Reserved for Busy Status of functions in group 1 */
    // [255:0]
    uint32_t RESERVED1[8];			 /* Reserved (All '0') */
} sdio_sw_function_sts_t2;

typedef union sdio_sw_function_sts_t{
    struct 		sdio_sw_function_sts_t2 reg;
    uint32_t 							u32[16];
} sdio_sw_function_sts_t;


typedef struct sdio_flags_t2{
    uint32_t delay				: 1; /* 0: Delay off. 1: Delay on */
    uint32_t bus_width			: 1; /* 0: 1bit DATA bus is set. 1: 4bit DATA bus is set */
    uint32_t high_speed			: 1; /* 0: low speed. 1: high speed */
    uint32_t hcs				: 1; /* ACMD41 argument value for HCS according to CMD8 response */
    uint32_t tx_ready			: 1; /* 0: Not ready to transfer. 1: Ready to transfer */
    uint32_t tx_type			: 5; /* Values according to sdio_tx_type_t enumeration */
    uint32_t RESERVED0          :22;
} sdio_flags_t2;

typedef union sdio_flags_t{
    struct 		sdio_flags_t2 		reg;
    volatile	uint32_t			u32;
} sdio_flags_t;

typedef struct sdio_info_t
{
    volatile	sdio_state_t				state;
    volatile	sdio_status_t				status;
    volatile	sdio_step_t					step;
    volatile	uint32_t					rca;
    volatile	uint32_t					address;
    volatile	uint32_t					size;
    union		sdio_r1_t					r1;
    union		sdio_r2_t					r2_cid;
    union		sdio_r2_t					r2_csd;
    union		sdio_r3_t					r3;
    union		sdio_r6_t					r6;
    union		sdio_r7_t					r7;
    union		sdio_flags_t				flags;
    struct 		mmca_attributes_t			mmca;
} sdio_info_t;

typedef enum
{
    card_detected		= 0,
    card_not_detected	= 1
} SDIO_cardDetectionState_t;


typedef struct 
{
    SDIO_cardDetectionState_t cardDetection;
    sdio_test_result_t              SdTest;
    
} r_SdioStatus_t;

extern r_SdioStatus_t g_SdioStatus;

typedef void sdio_callback_t(void);



/*******************************************************************************
  Function definition
*******************************************************************************/
void 			SDIO_default_callback(void);
void		  	SDIO_Init(void);
void 		  	SDIO_Update(void);
sdio_status_t	SDIO_Start_Transmission(sdio_tx_type_t tx_type, uint32_t *data, uint32_t size, uint32_t address, sdio_callback_t *sdio_callback_p);
sdio_state_t  	SDIO_Get_State(void);
sdio_status_t 	SDIO_Get_Status(void);
uint32_t 		SDIO_Ready_To_Transfer(void);
void            SD_Card_Info(void);
void            SD_Card_Info_Print(void);
void            SDIO_Read_Memory_Single_Callback(void);
void            SDIO_Write_Memory_Multi_Callback(void);
void            SDIO_Write_Memory_Single_Callback(void);
void            SDIO_Read_Memory_Multi_Callback(void);
SDIO_cardDetectionState_t SDIO_card_detection(void);
void run_SD_read(BYTE pdrv, uint32_t *buff_run, LBA_t sector_run, UINT count_run);
void run_SD_write(BYTE pdrv, uint32_t *buff_wr_run, LBA_t sector_run, UINT count_run);
sdio_test_result_t         SDIO_SystemTest(void);
#endif
   
