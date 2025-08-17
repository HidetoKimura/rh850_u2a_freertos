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
* File Name        : 
* Component Version: 1.0.0
* Description      : 
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#ifndef AVB_API_H_
#define AVB_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
  Title: AVB Driver API

  An application using AVB should only need to include r_avb_api.h
*/

/*******************************************************************************
  Section: Global Constants
*/


/*******************************************************************************
  Constant:  R_AVB_VERSION_HI and R_AVB_VERSION_LO

  Driver version information
*/

#define R_AVB_VERSION_HI 0
#define R_AVB_VERSION_LO 1

#define R_AVB_DESCINT_NUM       15
#define R_AVB_RXDESCINT_OFFSET  4

/* PHY status */
#define LINK_DOWN 0
#define LINK_UP   1

/* Rx descriptor chain offset in descriptor base address table */
#define R_AVB_RXBEQ_OFFSET      4
#define R_AVB_RXNCQ_OFFSET      5
#define R_AVB_RXSQ_OFFSET       6

/* Descriptor Types */
#define R_AVB_DESC_DT0          0
#define R_AVB_DESC_DT1          1
#define R_AVB_DESC_DT11         11

#define R_AVB_DESC_FSTART       5
#define R_AVB_DESC_FMID         4
#define R_AVB_DESC_FEND         6
#define R_AVB_DESC_FSINGLE      7

#define R_AVB_DESC_LINK         8
#define R_AVB_DESC_LINKFIX      9
#define R_AVB_DESC_EOS          10

#define R_AVB_DESC_FEMPTY       12
#define R_AVB_DESC_FEMPTY_IS    13
#define R_AVB_DESC_FEMPTY_IC    14
#define R_AVB_DESC_FEMPTY_ND    15
#define R_AVB_DESC_LEMPTY       2
#define R_AVB_DESC_EEMPTY       3

/* Frame size */
#define R_AVB_NORMALMAC_HSIZE   14  /* normal mac header size */
#define R_AVB_VLANMAC_HSIZE     18  /* MAC header with VLAN field */
#define R_AVB_BFRAME_SIZE       1518
#define R_AVB_VLFRAME_SIZE      1522 + 2 /* add 2 bytes to make 4-byte aligned */

/***********************************************************
  size of Tx/Rx descriptor
*/
#define R_AVB_NORMAL_DESC_SIZE   8      /* normal descriptor size (in byte) */
#define R_AVB_SPECIAL_DESC_SIZE  20     /* special descriptor size (in byte) */

/* Descriptor error type */
#define R_AVB_DESCERR_RURAM      0x0    /* read descriptor from URAM */
#define R_AVB_DESCERR_WURAM      0x1    /* write descriptor to URAM */
#define R_AVB_DESCERR_IRDESC     0x2    /* interpret read descriptor */
#define R_AVB_DESCERR_TBCORR     0x3    /* Tx buffer is corrupted */
#define R_AVB_DESCERR_RDURAM     0x4    /* read data from URAM */
#define R_AVB_DESCERR_WDURAM     0x5    /* write data or timestamp to URAM */
#define R_AVB_DESCERR_RFIFO      0x6    /* reading from rx FIFO */
#define R_AVB_DESCERR_RFCORR     0x7    /* rx FIFO is corrupted */
#define R_AVB_DESCERR_RFSERR     0x8    /* frame size error during reception detected */
#define R_AVB_DESCERR_TFSERR     0x9    /* frame size error during transmission detected */
#define R_AVB_DESCERR_TBUFOF     0x10   /* tx buffer overflow */

/* common status */
#define R_AVB_RXONGOING         0x10  /* reception process ongoing */
#define R_AVB_TXSAONGOING       0x08  /* transmission process ongoing (stram class A) */
#define R_AVB_TXSBONGOING       0x04  /* transmission process ongoing (stram class B) */
#define R_AVB_TXNCONGOING       0x02  /* transmission process ongoing (network control) */
#define R_AVB_TXBEONGOING       0x01  /* transmission process ongoing (best effort) */

/* Gptp timer loading action */
#define R_AVB_GPTPMAXTXTIME_LOAD    0x20    /* load max transit time */
#define R_AVB_GPTPPRETCOMP_LOAD     0x10    /* load presentation time comparison */
#define R_AVB_GPTPTIMERINC_LOAD     0x08    /* load timer increment */
#define R_AVB_GPTPTIMEROFF_LOAD     0x04    /* load timer offset */

/* gPTP interrupt status */
#define R_AVB_GPTPPRESTIME_CAP      0x1     /* presentation time captured */
#define R_AVB_GPTPPRESTIME_OVR      0x2     /* presentation time overrun */
#define R_AVB_GPTPPRESTIME_EXC      0x4     /* presentation time exceeded */

/* Error interrupt status */
#define R_AVB_ERR_STATUS_MREF    0x1        /* MAC reception error */
#define R_AVB_ERR_STATUS_MTEF    0x2        /* MAC transmission error */
#define R_AVB_ERR_STATUS_QEF     0x4        /* queue error */
#define R_AVB_ERR_STATUS_SEF     0x8        /* separation error */
#define R_AVB_ERR_STATUS_CLLF0   0x10       /* CBS lower limit reached (class B) */
#define R_AVB_ERR_STATUS_CLLF1   0x20       /* CBS lower limit reached (class A) */
#define R_AVB_ERR_STATUS_CULF0   0x40       /* CBS upper limit reached (class B) */
#define R_AVB_ERR_STATUS_CULF1   0x80       /* CBS upper limit reached (class A) */
#define R_AVB_ERR_STATUS_TFFF    0x100      /* timestamp FIFO full */
#define R_AVB_ERR_STATUS_MFFF    0x200      /* MAC status FIFO full */
#define R_AVB_ERR_STATUS_QFS     0x10000    /* queue full */

/* Interrupt summary status */
#define R_AVB_INTSUM_FRS     0x1        /* frame received summary */
#define R_AVB_INTSUM_RWS     0x2        /* reception warning summary */
#define R_AVB_INTSUM_FTS     0x4        /* frame transmitted summary */
#define R_AVB_INTSUM_ES      0x40       /* error summary */
#define R_AVB_INTSUM_MS      0x80       /* MAC summary */
#define R_AVB_INTSUM_TFUS    0x100      /* timestamp FIFO updated summary */
#define R_AVB_INTSUM_TFWS    0x200      /* timestamp FIFO warning summary */
#define R_AVB_INTSUM_MFUS    0x400      /* MAC status FIFO updated summary */
#define R_AVB_INTSUM_MFWS    0x800      /* MAC status FIFO warning summary */
#define R_AVB_INTSUM_RFWS    0x1000     /* rx FIFO warning summary */
#define R_AVB_INTSUM_CGIS    0x2000     /* combined gptp interrupt summary */
#define R_AVB_INTSUM_DPS     0xfffe0000 /* descriptor processed summary 1 - 15 */

/* Tx interrupt status */
#define R_AVB_TXINT_FTF0     0x1        /* frame transmitted queue 0 */
#define R_AVB_TXINT_FTF1     0x2        /* frame transmitted queue 1 */
#define R_AVB_TXINT_FTF2     0x4        /* frame transmitted queue 2 */
#define R_AVB_TXINT_FTF3     0x8        /* frame transmitted queue 3 */
#define R_AVB_TXINT_TFUF     0x100      /* timestamp FIFO udpated */
#define R_AVB_TXINT_TFWF     0x200      /* timestamp FIFO warning */
#define R_AVB_TXINT_MFUF     0x400      /* MAC status FIFO updated */
#define R_AVB_TXINT_MFWF     0x800      /* MAC status FIFO warning */


/*******************************************************************************
  Section: Global Types
*/

/*******************************************************************************
  Enum: r_avb_Error_t

  AVB macro driver error code.

  If an error occures these enums give information about the
  reason.

  Values:
  R_AVB_ERR_OK           - No error
  R_AVB_ERR_NG           - Unspecified error
  R_AVB_ERR_RANGE        - Instance out of range
  R_AVB_ERR_OPMODE       - Wrong operation mode
  R_AVB_ERR_INVNUM       - Invalid number
  R_AVB_ERR_LOCKED       - Device locked
  R_AVB_ERR_NOTLOCKED    - Device not locked
*/

typedef enum {
    R_AVB_ERR_OK         = 0x00,
    R_AVB_ERR_NG         ,
    R_AVB_ERR_RANGE      ,
    R_AVB_ERR_OPMODE     ,
    R_AVB_ERR_INVNUM     ,
    R_AVB_ERR_LOCKED     ,
    R_AVB_ERR_NOTLOCKED
} r_avb_Error_t;


/*******************************************************************************
  Enum: r_avb_Interrupt_t

  AVB macro interrupt type.

  List of all available interrupts for this macro.

  Values:
    R_AVB_INT_DATA  - data related interrupt
    R_AVB_INT_ERR   - error related interrupt
    R_AVB_INT_MNG   - management related interrupt
    R_AVB_INT_MAC   - MAC interrupt
    R_AVB_INT_LAST  - Delimeter
*/
typedef enum {
    R_AVB_INT_DATA,
    R_AVB_INT_ERR,
    R_AVB_INT_MNG,
    R_AVB_INT_MAC,
    R_AVB_INT_NUM
} r_avb_Interrupt_t;


/***********************************************************
  Enum: r_avb_OpStatus_t

  AVB operation status

  Members:
    R_AVB_RESET      - reset
    R_AVB_CONFIG     - config
    R_AVB_OPERATION  - operation
    R_AVB_STANDBY    - standby
*/
typedef enum {
    R_AVB_RESET      = 0,
    R_AVB_CONFIG,
    R_AVB_OPERATION,
    R_AVB_STANDBY
} r_avb_OpStatus_t;


/***********************************************************
  Enum: r_avb_GPtpClk_t

  gPTP clock source

  Members:
    R_AVB_GPTP_DISABLE   - gPTP support disabled
    R_AVB_GPTP_PBUS      - gPTP based on peripheral bus clock
    R_AVB_GPTP_ETHTX     - gPTP based on ethernet Tx clock
    R_AVB_GPTP_EXTERN    - gPTP based on external clock
*/
typedef enum {
    R_AVB_GPTP_DISABLE    = 0,
    R_AVB_GPTP_PBUS,
    R_AVB_GPTP_ETHTX,
    R_AVB_GPTP_EXTERN
} r_avb_GPtpClk_t;


/***********************************************************
  Type: r_avb_Option_t

  Setting option

  Members:
    R_AVB_DISABLE  - setting is disabled
    R_AVB_ENABLE   - setting is enabled
*/
typedef enum {
    R_AVB_DISABLE    = 0,
    R_AVB_ENABLE
} r_avb_Option_t;


/***********************************************************
  Type: r_avb_IntStatus_t

  Interrupt status

  Members:
    R_AVB_NOINT      - no interrupt
    R_AVB_INTPENDING - interrupt pending
*/
typedef enum {
    R_AVB_NOINT    = 0,
    R_AVB_PENDING
} r_avb_IntStatus_t;


/***********************************************************
  Type: r_avb_SFOption_t

  Stream filtering option

  Members:
    R_AVB_DISABLE   - receive queues r>=2 are disabled
    R_AVB_SEPFILTER - separation filtering only
    R_AVB_AVBNMDISC - avb stream with separation filtering, no matching frames discarded
    R_AVB_AVBNMQUE0 - avb stream with separation filtering, no matching frames into queue0
*/
typedef enum {
    R_AVB_SFDISABLE    = 0,
    R_AVB_SEPFILTER,
    R_AVB_AVBNMDISC,
    R_AVB_AVBNMQUE0
} r_avb_SFOption_t;


/***********************************************************
  Type: r_avb_UFCConfig_t

  unread frame counter configuration

  Members:
    R_AVB_UFCC0 - unread frame counter configuration 0
    R_AVB_UFCC1 - unread frame counter configuration 1
    R_AVB_UFCC2 - unread frame counter configuration 2
    R_AVB_UFCC3 - unread frame counter configuration 3
*/
typedef enum {
    R_AVB_UFCC0    = 0,
    R_AVB_UFCC1,
    R_AVB_UFCC2,
    R_AVB_UFCC3
} r_avb_UFCConfig_t;


/***********************************************************
  Type: r_avb_TSel_t

  truncation selection

  Members:
    R_AVB_MAXF0 - maximum frame length defined by RTC0.MFL0
    R_AVB_MAXF1 - maximum frame length defined by RTC0.MFL1
*/
typedef enum {
    R_AVB_MAXF0    = 0,
    R_AVB_MAXF1,
} r_avb_TSel_t;


/***********************************************************
  Type: r_avb_RxSyncMode_t

  receive synchronisation mode

  Members:
    R_AVB_NORMAL  - normal mode (full descriptor write back)
    R_AVB_KEEPDT  - keep DT mode (no update of DT field at descriptor write back)
    R_AVB_NOWB    - no write back (no descriptor write back)
*/
typedef enum {
    R_AVB_RXNORMAL    = 0,
    R_AVB_RXKEEPDT,
    R_AVB_RXNOWB
} r_avb_RxSyncMode_t;


/***********************************************************
  Type: r_avb_TxSyncMode_t

  Transmission synchronisation mode

  Members:
    R_AVB_TXNORMAL  - normal mode, full descriptor write back
    R_AVB_TXNOWB    - no write back, no descriptor write back
*/
typedef enum {
    R_AVB_TXNORMAL    = 0,
    R_AVB_TXNOWB
} r_avb_TxSyncMode_t;


/***********************************************************
  Type: r_avb_TxQPrio_t

  Transmission queue priority

  Members:
    R_AVB_NONAVB  - non-AVB mode (Q3 > Q2 > Q1 > Q0)
    R_AVB_AVBDEF  - default AVB priority (Q3 > Q2 > Q1 > Q0)
    R_AVB_AVBALT  - alternate AVB priority (Q1 > Q3 > Q2 > Q0)
*/
typedef enum {
    R_AVB_NONAVB    = 0,
    R_AVB_AVBDEF,
    R_AVB_AVBALT
} r_avb_TxQPrio_t;


/***********************************************************
  Type: r_avb_CBSCntStatus_t

  CBS counter status

  Members:
    R_AVB_ILIMIT  - current credit value inside limit range
    R_AVB_BLIMIT  - current credit value below lower limit
    R_AVB_ULIMIT  - current credit value exceeds upper limit
*/
typedef enum {
    R_AVB_ILIMIT    = 0,
    R_AVB_BLIMIT,
    R_AVB_ULIMIT
} r_avb_CBSCntStatus_t;


/***********************************************************
  Type: r_avb_CBSCntClass_t

  CBS counter class

  Members:
    R_AVB_CBSCNTB  - CBS counter class B
    R_AVB_CBSCNTA  - CBS counter class A
*/
typedef enum {
    R_AVB_CBSCNTB    = 0,
    R_AVB_CBSCNTA
} r_avb_CBSCntClass_t;


/***********************************************************
  Type: r_avb_TCapSrc_t

  time capture source

  Members:
    R_AVB_GPTPTIMER  - gPTP timer value
    R_AVB_CGPTPTIMER - corrected gPTP timer value
    R_AVB_AVTPPTIME  - AVTP presentation time value
*/
typedef enum {
    R_AVB_GPTPTIMER    = 0,
    R_AVB_CGPTPTIMER,
    R_AVB_AVTPPTIME
} r_avb_TCapSrc_t;


/***********************************************************
  Enum: r_avb_MacCounter_t

  MAC counter

  Members:
    R_AVB_CNT_FIRST  - first counter
    R_AVB_CNT_TROCR  - transmit retry over counter
    R_AVB_CNT_CDCR   - delayed collision detect counter
    R_AVB_CNT_LCCR   - lost carrier counter
    R_AVB_CNT_CEFCR  - CRC error frame receive counter
    R_AVB_CNT_FRECR  - frame receive error counter
    R_AVB_CNT_TSFRCR - too short frame receive counter
    R_AVB_CNT_TLFRCR - too long frame receive counter
    R_AVB_CNT_RFCR   - residual-bit frame receive counter
    R_AVB_CNT_MAFCR  - multicast address frame counter
    R_AVB_CNT_LAST   - last counter
*/
typedef enum {
    R_AVB_CNT_FIRST = 0,
    R_AVB_CNT_TROCR = R_AVB_CNT_FIRST,
    R_AVB_CNT_CDCR,
    R_AVB_CNT_LCCR,
    R_AVB_CNT_CEFCR,
    R_AVB_CNT_FRECR,
    R_AVB_CNT_TSFRCR,
    R_AVB_CNT_TLFRCR,
    R_AVB_CNT_RFCR,
    R_AVB_CNT_MAFCR,
    R_AVB_CNT_LAST
} r_avb_MacCounter_t;


/***********************************************************
  Enum: r_avb_Speed_t

  Mac speed

  Members:
    R_AVB_100M  - 10/100MBps
*/
typedef enum {
    R_AVB_100M    = 0,
    R_AVB_1G      = 1
} r_avb_Speed_t;


/***********************************************************
  Enum: r_avb_Duplex_t

  Mac duplex mode

  Members:
    R_AVB_HDUPLEX  - half duplex
    R_AVB_FDUPLEX  - full duplex
*/
typedef enum {
    R_AVB_HDUPLEX    = 0,
    R_AVB_FDUPLEX
} r_avb_Duplex_t;


/***********************************************************
  Enum: r_avb_TxRxOption_t

  AVB Tx/Rx option

  Members:
    R_AVB_RX  - reception
    R_AVB_TX  - transmission
*/
typedef enum {
    R_AVB_RX    = 0,
    R_AVB_TX
} r_avb_TxRxOption_t;


/***********************************************************
  Enum: r_avb_RxBufMode_t

  AVB Rx buffer mode

  Members:
    R_AVB_RX_SFSB    - single frame single buffer
    R_AVB_RX_SFMB    - single frame multi buffer
    R_AVB_RX_SFMBINC - single frame multi buffer (incremental data area)
*/
typedef enum {
    R_AVB_RX_SFSB    = 0,
    R_AVB_RX_SFMB,
    R_AVB_RX_SFMBINC
} r_avb_RxBufMode_t;


/***********************************************************
  Enum: r_avb_RxCh_t

  AVB Rx Channel

  Members:
    R_AVB_RX_BE    - best effort
    R_AVB_RX_NC    - network control
    R_AVB_RX_S     - stream
*/
typedef enum {
    R_AVB_RX_BE    = 0,
    R_AVB_RX_NC,
    R_AVB_RX_S
} r_avb_RxCh_t;


/***********************************************************
  Section: Structures
*/

/***********************************************************
  Type: r_avb_CbsParam_t

  CBS parameter

  Members:
    CbsInc      - CBS increment value
    CbsDec      - CBS decrement value
    CbsUppLimit - CBS upper limit
    CbsLowLimit - CBS lower limit
*/
typedef struct {
    int32_t CbsInc;
    int32_t CbsDec;
    int32_t CbsUppLimit;
    int32_t CbsLowLimit;
} r_avb_CbsParam_t;


/***********************************************************
  Type: r_avb_TimeStamp_t

  Timestamp structure

  Members:
    Timestamp0  - timestamp[31:0]
    Timestamp1  - timestamp[63:32]
    Timestamp2  - timestamp[79:64]
*/

typedef struct {
    uint32_t Timestamp0;
    uint32_t Timestamp1;
    uint16_t Timestamp2;
} r_avb_TimeStamp_t;


/***********************************************************
  Type: r_avb_TSFifo_t

  Timestamp FIFO item structure

  Members:
    Valid      - timestamp value valid
    Tag        - tag number from descriptor identifying the frame timestamp relation
    Timestamp  - timestamp[79:0]
*/

typedef struct {
    uint8_t           Valid;
    uint16_t          Tag;
    r_avb_TimeStamp_t Timestamp;
} r_avb_TSFifo_t;


/***********************************************************
  Type: r_avb_MACStatusFifo_t

  MAC status FIFO item structure

  Members:
    Valid         - status value valid
    StatusTag     - tag number from descriptor identifying the frame MAC status relation
    StatusValue   - MAC staus value

*/
typedef struct {
    uint8_t  Valid;
    uint32_t StatusTag;
    uint32_t StatusValue;
} r_avb_MACStatusFifo_t;


/***********************************************************
  Type: r_avb_ErrStatus_t

  Error status

  Members:
    ErrLost       - Error information lost
    ErrQueueNum   - Queue number which was handled by the error
    ErrType       - Error type of which the AVBED has detected

*/
typedef struct {
    uint8_t ErrLost;
    uint8_t ErrQueueNum;
    uint8_t ErrType;
} r_avb_ErrStatus_t;


/***********************************************************
  Type: r_avb_QConfig_t

  Queue configuration

  Members:
    Ufcc  - unread frame counter configuration
    Tsel  - truncation selection
    Rsm   - receive synchronisation mode
*/
typedef struct {
    r_avb_UFCConfig_t  Ufcc;
    r_avb_TSel_t       Tsel;
    r_avb_RxSyncMode_t Rsm;
} r_avb_QConfig_t;


/***********************************************************
  Type: r_avb_PaddingConfig_t

  Rx padding configuration

  Members:
    Dcnt  - data count value
    Pcnt  - padding count value
*/
typedef struct {
    uint8_t Dcnt;
    uint8_t Pcnt;
} r_avb_PaddingConfig_t;


/***********************************************************
  Type: r_avb_TruncConfig_t

  Rx truncation configuration

  Members:
    Mfl0  - max. frame length 0
    Mfl1  - max. frame length 1
*/
typedef struct {
    uint16_t Mfl0;
    uint16_t Mfl1;
} r_avb_TruncConfig_t;


/***********************************************************
  Type: r_avb_SepFilter_t

  Rx seperation filter

  Members:
    QIndex   - Queue index
    Offset   - first byte position
    LPattern - low 32-bit of the pattern
    HPattern - high 32-bit of the pattern
    LMask    - low 32-bit of mask
    HMask    - high 32-bit of mask
*/
typedef struct {
    uint32_t QIndex;
    uint32_t Offset;
    uint32_t LPattern;
    uint32_t HPattern;
    uint32_t LMask;
    uint32_t HMask;
} r_avb_SepFilter_t;


/***********************************************************
  Type: r_avb_ComConfig_t

  Common configuration structure

  Members:
    Lbme    - loopback mode
    Boc     - byte order (0: first byte in URAM[7:0], 1: first byte in URAM[31:24])
    Csel    - clock selection, see <r_avb_GPtpClk_t>
*/
typedef struct {
    uint8_t            Lbme;
    uint8_t            Boc;
    r_avb_GPtpClk_t    Csel;
} r_avb_ComConfig_t;


/***********************************************************
  Type: r_avb_RxConfig_t

  reception configuration structure

  Members:
    Effs    - enable faulty frame storage
    Encf    - enable network control filtering
    Esf     - enable stream filtering
    Ets0    - enable timestamp storage (best effort)
    Ets2    - enable timestamp storage (stream)
    Rfcl    - reception FIFO critical level
*/
typedef struct {
    r_avb_Option_t    Effs;
    r_avb_Option_t    Encf;
    r_avb_SFOption_t  Esf;
    r_avb_Option_t    Ets0;
    r_avb_Option_t    Ets2;
    uint32_t          Rfcl;
} r_avb_RxConfig_t;


/***********************************************************
  Type: r_avb_TxConfig_t

  Transmission configuration structure

  Members:
    Tsm0   - transmit synchronisation mode0 (best effort)
    Tsm1   - transmit synchronisation mode1 (network control)
    Tsm2   - transmit synchronisation mode2 (stream class B)
    Tsm3   - transmit synchronisation mode3 (stream class A)
    Tqp    - transmission queues priority
*/
typedef struct {
    r_avb_TxSyncMode_t    Tsm0;
    r_avb_TxSyncMode_t    Tsm1;
    r_avb_TxSyncMode_t    Tsm2;
    r_avb_TxSyncMode_t    Tsm3;
    r_avb_TxQPrio_t       Tqp;
} r_avb_TxConfig_t;


/***********************************************************
  Type: r_avb_ErrorInt_t

  Error interrupt

  Members:
    Mree    - MAC reception error interrupt
    Mtee    - MAC transmission error interrupt
    Qee     - Queue error interrupt
    See     - Separation error interrupt
    Clle0   - CBS lower limit reached interrupt (class B)
    Clle1   - CBS lower limit reached interrupt (class A)
    Cule0   - CBS upper limit reached interrupt (class B)
    Cule1   - CBS upper limit reached interrupt (class A)
    Tffe    - Timerstamp FIFO full interrupt
    Mffe    - MAC status FIFO full interrupt
*/
typedef struct {
    r_avb_Option_t    Mree;
    r_avb_Option_t    Mtee;
    r_avb_Option_t    Qee;
    r_avb_Option_t    See;
    r_avb_Option_t    Clle0;
    r_avb_Option_t    Clle1;
    r_avb_Option_t    Cule0;
    r_avb_Option_t    Cule1;
    r_avb_Option_t    Tffe;
    r_avb_Option_t    Mffe;
} r_avb_ErrorInt_t;


/***********************************************************
  Type: r_avb_Config_t

  AVB part configuration structure

  Members:
    BufBaseAddr - buffer base address
    ComConfig   - see <r_avb_ComConfig_t>
    RxConfig    - see <r_avb_RxConfig_t>
    TxConfig    - see <r_avb_TxConfig_t>
    ErrorInt    - see <r_avb_ErrorInt_t>
*/
typedef struct {
    uint32_t          BufBaseAddr;
    r_avb_ComConfig_t *ComConfig;
    r_avb_RxConfig_t  *RxConfig;
    r_avb_TxConfig_t  *TxConfig;
    r_avb_ErrorInt_t  *ErrorInt;
} r_avb_Config_t;


/***********************************************************
  Type: r_avb_MacMode_t

  MAC config data structure

  Members:
    Speed           - MAC speed
    Duplex          - duplex mode
    PromMode        - promiscuous mode
    MagicDetection  - magic packet detection
    TxFlowCtrl      - transmission flow control
    RxFlowCtrl      - reception flow control
    PFrameRxMode    - pause frame reception mode
    ZPFrameTx       - zero pause frame transmission with Time = 0
    ZPFrameRx       - zero pause frame reception with Time = 0
    DPad            - data padding
    RxCrcMode       - reception checksum calculation
    Tpe             - transmission enable
    Rpe             - reception enable
*/
typedef struct {
    r_avb_Speed_t  Speed;
    r_avb_Duplex_t Duplex;
    r_avb_Option_t PromMode;
    r_avb_Option_t MagicDection;
    r_avb_Option_t TxFlowCtrl;
    r_avb_Option_t RxFlowCtrl;
    r_avb_Option_t PFrameRxMode;
    r_avb_Option_t ZPFrameTx;
    r_avb_Option_t ZPFrameRx;
    r_avb_Option_t DPad;
    r_avb_Option_t RxCrcMode;
    r_avb_Option_t Tpe;
    r_avb_Option_t Rpe;
} r_avb_MacMode_t;


/***********************************************************
  Type: r_avb_MacInt_t

  MAC interrupt structure

  Members:
    Icdim   - false carrier detect interrupt enable
    Mpdim   - magic packet detection interrupt enable
    Linkim  - link signal change interrupt enable
    Phyim   - PHY Pin interrupt enable
*/
typedef struct {
    r_avb_Option_t  Icdim;
    r_avb_Option_t  Mpdim;
    r_avb_Option_t  Linkim;
    r_avb_Option_t  Phyim;
} r_avb_MacInt_t;


/***********************************************************
  Type: r_avb_MacConfig_t

  MAC config data structure

  Members:
    MacAddr      - 48-bit MAC address
    MaxFrameLen  - max. frame length
    Mac_Mode     - see <r_avb_MacMode_t>
    Mac_Int_Mask - Mac interrupt mask, see <r_avb_MacInt_t>
*/
typedef struct {
    uint8_t           *MacAddr;
    uint32_t          MaxFrameLen;
    r_avb_MacMode_t   *Mac_Mode;
    r_avb_MacInt_t    *Mac_Int_Mask;
    uint8_t           SelfTestLoop;
} r_avb_MacConfig_t;


/***********************************************************
  Type: r_avb_TxMultiFrame_t

  Tx Frame structure in 3 parts

  Members:
    Timestamp  - timestamp function on/off
    MacStatus  - mac status on/off
    Tag        - Tag field
    MacHeader  - Mac header address
    MacLength  - Mac header length
    PlHeader   - Payload header address
    PlHLength  - Payload header length
    Payload    - Payload address
    PlLength   - Payload length
*/
typedef struct {
    r_avb_Option_t Timestamp;
    r_avb_Option_t MacStatus;
    uint16_t       Tag;
    uint32_t       MacHeader;
    uint32_t       MacLength;
    uint32_t       PlHeader;
    uint32_t       PlHLength;
    uint32_t       Payload;
    uint32_t       PlLength;
} r_avb_TxMultiFrame_t;


/***********************************************************
  Type: r_avb_TxSingleFrame_t

  Single frame structure for Tx

  Members:
    Timestamp  - timestamp function on/off
    MacStatus  - mac status on/off
    Tag        - Tag field
    Address    - frame address
    Length     - frame length
*/
typedef struct {
    r_avb_Option_t Timestamp;
    r_avb_Option_t MacStatus;
    uint16_t       Tag;
    uint32_t       Address;
    uint32_t       Length;
} r_avb_TxSingleFrame_t;


/***********************************************************
  Type: r_avb_RxSingleFrame_t

  Rx frame information structure (single frame single buffer)

  Members:
    FrameAddr    - frame address
    FrameLength  - frame length
    Timestamp    - timestamp if enabled
*/
typedef struct {
    uint32_t          FrameAddr;
    uint32_t          DescAddr;
    uint32_t          FrameLength;
    r_avb_TimeStamp_t Timestamp;
} r_avb_RxSingleFrame_t;


/***********************************************************
  Type: r_avb_RxMultiFrame_t

  Rx frame information structure (single frame multi buffer)

  Members:
    MacHeader    - MAC header address
    MacHLength   - MAC header length
    PlHeader     - payload header address
    PlHLength    - payload header length
    PlData       - payload data address
    PlDLength    - payload data length
    Timestamp    - timestamp value if enabled
*/
typedef struct {
    uint32_t          MacHeader;
    uint32_t          MacHLength;
    uint32_t          PlHeader;
    uint32_t          PlHLength;
    uint32_t          PlData;
    uint32_t          PlDLength;
    r_avb_TimeStamp_t Timestamp;
} r_avb_RxMultiFrame_t;


/***********************************************************
  Type: r_avb_RxChConfig_t

  Rx channel configuration structure

  Members:
    ChNum           - channel number
    ChType          - channel type, see <r_avb_RxCh_t>
    BufMode         - buffer mode, see <r_avb_RxBufMode_t>
    PHLength        - payload header length (for single frame multi buffer)
    PLength         - payload length (for single frame multi buffer)
*/
typedef struct {
    uint32_t            ChNum;
    r_avb_RxCh_t        ChType;
    r_avb_RxBufMode_t   BufMode;
    uint32_t            PHLength;
    uint32_t            PLength;
} r_avb_RxChConfig_t;


/***********************************************************
  Type: r_avb_RxCtrlTag_t

  Rx specific control field structure

  Members:
    Tr   - truncation indication
    Ei   - frame corruption detection
    Ps   - padding selection
    Msc  - MAC status code
*/
typedef struct {
    uint32_t Tr   : 1;
    uint32_t Ei   : 1;
    uint32_t Ps   : 2;
    uint32_t Msc  : 8;
} r_avb_RxCtrlTag_t;


/***********************************************************
  Type: r_avb_TxCtrlTag_t

  Tx specific control field structure

  Members:
    Tag  - frame tag
    Tsr  - timestamp storage request
    Msr  - MAC status storage request
*/
typedef struct {
    uint32_t Tag   : 10;
    uint32_t Tsr   : 1;
    uint32_t Msr   : 1;
} r_avb_TxCtrlTag_t;


/***********************************************************
  Union: r_avb_TxRxCtrl_t

  Simplifies Bit and Byte access

  Members:
    RxCtrl  - Rx control field
    TxCtrl  - Tx control field
    Word    - Allow access of the whole word.
*/
typedef union {
    r_avb_RxCtrlTag_t  RxCtrl;
    r_avb_TxCtrlTag_t  TxCtrl;
    uint32_t           Word;
} r_avb_TxRxCtrl_t;


/***********************************************************
  Type: r_avb_DataDesc_L_t

  Data descriptor structure low word

  Members:
    Ds   - Size of descriptor data
    Ctrl - content control code for Tx/Rx
    Die  - descriptor interrupt enable
    Dt   - descriptor type
*/
typedef struct {
    uint32_t Ds   : 12;
    uint32_t Ctrl : 12;
    uint32_t Die  : 4;
    uint32_t Dt   : 4;
} r_avb_DataDesc_L_t;


/***********************************************************
  Type: r_avb_LinkDesc_L_t

  Link descriptor structure low word

  Members:
    Res  - Reserved
    Die  - descriptor interrupt enable
    Dt   - descriptor type
*/
typedef struct {
    uint32_t Res  : 24;
    uint32_t Die  : 4;
    uint32_t Dt   : 4;
} r_avb_LinkDesc_L_t;


/***********************************************************
  Type: r_avb_OthDesc_L_t

  Other descriptor structure low word

  Members:
    Res  - Reserved
    Die  - descriptor interrupt enable
    Dt   - descriptor type
*/
typedef struct {
    uint32_t Res  : 24;
    uint32_t Die  : 4;
    uint32_t Dt   : 4;
} r_avb_OthDesc_L_t;


/***********************************************************
  Type: r_avb_DataDesc_t

  Data descriptor structure

  Members:
    Header - low word of the data descriptor
    Dptr   - point to the descriptor data
*/
typedef struct {
    r_avb_DataDesc_L_t Header;
    uint32_t           Dptr;
} r_avb_DataDesc_t;


/***********************************************************
  Type: r_avb_ExtDataDesc_t

  Extended data descriptor structure

  Members:
    Header    - low word of the data descriptor
    Dptr      - point to the descriptor data
    Timestamp - timestamp for received frame
*/
typedef struct {
    r_avb_DataDesc_L_t Header;
    uint32_t           Dptr;
    r_avb_TimeStamp_t  Timestamp;
} r_avb_ExtDataDesc_t;


/***********************************************************
  Type: r_avb_LinkDesc_t

  Link descriptor structure

  Members:
    Header    - low word of the link descriptor
    Dptr      - point to the next descriptor
*/
typedef struct {
    r_avb_LinkDesc_L_t Header;
    uint32_t           Dptr;
} r_avb_LinkDesc_t;


/***********************************************************
  Type: r_avb_OthDesc_t

  Other descriptor structure

  Members:
    Header  - low word of the descriptor
    Res     - reserved area
*/
typedef struct {
    r_avb_OthDesc_L_t   Header;
    uint32_t            Res;
} r_avb_OthDesc_t;


/*******************************************************************************
  Section: Global API Functions
*/

/*******************************************************************************
  Group: Common part
*/

/*******************************************************************************
  Function: R_AVB_GetVersionStr

  Get the driver version number in human readable form (string).

  Parameters:
  void

  Returns:
  ReceiveString     - Pointer to receive string destination

*/
const int8_t * R_AVB_GetVersionStr(void);


/*******************************************************************************
  Function: R_AVB_GetMajorVersion

  Get the driver major version number.

  Parameters:
  void

  Returns:
     - Major version number

*/
uint16_t R_AVB_GetMajorVersion(void);


/*******************************************************************************
  Function: R_AVB_GetMinorVersion

  Get the driver minor version number.

  Parameters:
  void

  Returns:
     - Minor version number

*/
uint16_t R_AVB_GetMinorVersion(void);


/*******************************************************************************
  Function: R_AVB_Init

  Driver init function.

  Parameters:
  Unit          - Macro instance number
  AvbConfig     - see <r_avb_Config_t>
  MacConfig     - see <r_avb_MacConfig_t>

  Returns:
  see: <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_Init(uint32_t Unit, r_avb_Config_t *AvbConfig, r_avb_MacConfig_t *MacConfig);


/*******************************************************************************
  Function: R_AVB_DeInit

  Driver deinit function.

  Parameters:
  Unit       - Macro Instance number

  Returns:
  see: <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_DeInit(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_OpModeChange

  Change AVB operation mode

  Parameters:
    Unit  - Instance number
    Mode  - see <r_avb_OpStatus_t>

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_OpModeChange(uint32_t Unit, r_avb_OpStatus_t Mode);


/*******************************************************************************
  Function: R_AVB_OpModeGet

  get AVB operation mode

  Parameters:
    Unit    - Instance number

  Returns:
    see <r_avb_OpStatus_t>
*/
r_avb_OpStatus_t R_AVB_OpModeGet(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_TxStatusGet

  get Tx status

  Parameters:
    Unit    - Instance number

  Returns:
    transmission status
*/
uint8_t R_AVB_TxStatusGet(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_RxStatusGet

  get Rx status

  Parameters:
    Unit    - Instance number

  Returns:
    reception status
*/
uint8_t R_AVB_RxStatusGet(uint32_t Unit);



/*******************************************************************************
  Group: MAC part
*/

/*******************************************************************************
  Function: R_AVB_MacInit

  MAC intialization

  Parameters:
    Unit      - Instance number
    MacConfig - see <r_avb_MacConfig_t>

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_MacInit(uint32_t Unit, r_avb_MacConfig_t *MacConfig);


/*******************************************************************************
  Function: R_AVB_MacPhyRead

  read PHY device

  Parameters:
    Unit    - Instance number
    PhyAddr - Phy address
    RegAddr - Phy register address

  Returns:
    value read from Phy
*/
uint16_t R_AVB_MacPhyRead(uint32_t Unit, uint8_t PhyAddr, uint8_t RegAddr);


/*******************************************************************************
  Function: R_AVB_MacPhyWrite

  write Phy device

  Parameters:
    Unit    - Instance number
    PhyAddr - Phy address
    RegAddr - Phy register address
    Value   - value to be written

  Returns:
    void
*/
void R_AVB_MacPhyWrite(uint32_t Unit, uint8_t PhyAddr, uint8_t RegAddr, uint16_t Value);


/*******************************************************************************
  Function: R_AVB_MacAllCounterClear

  clear all Mac counters

  Parameters:
    Unit   - Instance number

  Returns:
    void
*/
void R_AVB_MacAllCounterClear(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_MacCounterClear

  clear Mac counter

  Parameters:
    Unit    - Instance number
    Counter - counter to be cleared

  Returns:
    void
*/
void R_AVB_MacCounterClear(uint32_t Unit, r_avb_MacCounter_t Counter);


/*******************************************************************************
  Function: R_AVB_MacCounterGet

  get Mac counter value

  Parameters:
    Unit    - Instance number
    Counter - counter to be read

  Returns:
    counter value
*/
uint16_t R_AVB_MacCounterGet(uint32_t Unit, r_avb_MacCounter_t Counter);


/*******************************************************************************
  Function: R_AVB_MacIntStatusGet

  get Mac interrupt status

  Parameters:
    Unit   - Instance number

  Returns:
    interrupt status
*/
uint32_t R_AVB_MacIntStatusGet(uint32_t Unit);


/*******************************************************************************  
  Function: R_AVB_MacCommunicationSet

  Configure Tx & Rx in MAC

  Parameters:
    Unit      - Instance number
    Direction - Tx or Rx, see <r_avb_TxRxOption_t>
    Option    - enable or disable, see <r_avb_Option_t>
    
  Returns:
    void
*/
void R_AVB_MacCommunicationSet(uint32_t Unit, r_avb_TxRxOption_t Direction, r_avb_Option_t Option);



/*******************************************************************************
  Group: gPTP part
*/

/*******************************************************************************
  Function: R_AVB_GPtpTimeSrcSelect

  select time capture source

  Parameters:
    Unit    - Instance number
    TCapSrc - see <r_avb_TCapSrc_t>

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_GPtpTimeCapSrcSel(uint32_t Unit, r_avb_TCapSrc_t TCapSrc);


/*******************************************************************************
  Function: R_AVB_GPtpMaxTxTimeSet

  set max. transit time

  Parameters:
    Unit    - Instance number
    MaxTime - max. transit time

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_GPtpMaxTxTimeSet(uint32_t Unit, uint32_t MaxTime);


/*******************************************************************************
  Function: R_AVB_GPtpMaxTxTimeLoad

  load max. transit time

  Parameters:
    Unit    - Instance number

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_GPtpMaxTxTimeLoad(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_GPtpTimerIncSet

  set timer increment value

  Parameters:
    Unit      - Instance number
    Increment - gPTP timer increment value

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_GPtpTimerIncSet(uint32_t Unit, uint32_t Increment);


/*******************************************************************************
  Function: R_AVB_GPtpTimerIncLoad

  load timer increment value

  Parameters:
    Unit      - Instance number

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_GPtpTimerIncLoad(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_GPtpTimerOffsetSet

  set gPTP timer offset

  Parameters:
    Unit   - Instance number
    Offset - timer offset value

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_GPtpTimerOffsetSet(uint32_t Unit, r_avb_TimeStamp_t *Offset);


/*******************************************************************************
  Function: R_AVB_GPtpTimerOffsetLoad

  load timer offset

  Parameters:
    Unit   - Instance number

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_GPtpTimerOffsetLoad(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_PresTimeCompSet

  set presentation time comparison value

  Parameters:
    Unit     - Instance number
    CompTime - presentation time comparison value

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_PresTimeCompSet(uint32_t Unit, uint32_t CompTime);


/*******************************************************************************
  Function: R_AVB_PresTimeCompLoad

  load presentation time comparison value

  Parameters:
    Unit     - Instance number

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_PresTimeCompLoad(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_GPtpTimeCapture

  capture gPTP time

  Parameters:
    Unit   - Instance number
    Time   - captured time

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_GPtpTimeCapture(uint32_t Unit, r_avb_TimeStamp_t *Time);


/*******************************************************************************
  Function: R_AVB_GPtpTimerReset

  Reset gPTP timer

  Parameters:
    Unit   - Instance number

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_GPtpTimerReset(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_SwPresTimeCapture

  capture presentation time (sw trigger)

  Parameters:
    Unit   - Instance number

  Returns:
    captured presentation time
*/
uint32_t R_AVB_SwPresTimeCapture(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_HwPresTimeCapture

  capture presentation time (hw trigger)

  Parameters:
    Unit   - Instance number

  Returns:
    captured presentation time
*/
uint32_t R_AVB_HwPresTimeCapture(uint32_t Unit);


/*******************************************************************************
  Group: Message handler part
*/
/*******************************************************************************
  Function: R_AVB_DescTableBaseSet

  set descriptor base address table

  Parameters:
    Unit     - Instance number
    BaseAddr - base address to be set

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_DescTableBaseSet(uint32_t Unit, uint32_t BaseAddr);


/*******************************************************************************
  Function: R_AVB_QBaseAddrLoad

  load queue base address

  Parameters:
    Unit   - Instance number
    QIndex - queue index

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_QBaseAddrLoad(uint32_t Unit, uint8_t QIndex);


/*******************************************************************************
  Function: R_AVB_CurrentDescGet

  Get current descriptor address

  Parameters:
    Unit   - Instance number
    QIndex - queue index
    Option - see <r_avb_TxRxOption_t>

  Returns:
    current descriptor address
*/
uint32_t R_AVB_CurrentDescGet(uint32_t Unit, uint8_t QIndex, r_avb_TxRxOption_t Option);


/*******************************************************************************
  Function: R_AVB_RxSet

  Set Rx parameters

  Parameters:
    Unit     - Instance number
    RxConfig - see <r_avb_RxConfig_t>

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_RxSet(uint32_t Unit, r_avb_RxConfig_t *RxConfig);


/*******************************************************************************
  Function: R_AVB_RxQueueSet

  set Rx queue

  Parameters:
    Unit     - Instance number
    QConfig  - queue configuration, see <r_avb_QConfig_t>
    QIndex   - queue index

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_RxQueueSet(uint32_t Unit, r_avb_QConfig_t *QConfig, uint32_t QIndex);


/*******************************************************************************
  Function: R_AVB_RxPaddingSet

  set padding parameters

  Parameters:
    Unit    - Instance number
    Padding - padding data

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_RxPaddingSet(uint32_t Unit, r_avb_PaddingConfig_t *Padding);


/*******************************************************************************
  Function: R_AVB_RxTruncSet

  set Rx truncation

  Parameters:
    Unit   - Instance number
    Trunc  - truncation parameter

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_RxTruncSet(uint32_t Unit, r_avb_TruncConfig_t *Trunc);


/*******************************************************************************
  Function: R_AVB_UFWarningLevelSet

  set unread frame counter warning level

  Parameters:
    Unit         - Instance number
    WarningValue - number of unread frames reaching warning level
    ConfigNum    - configuration

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_UFWarningLevelSet(uint32_t Unit, uint8_t WarningValue, uint8_t ConfigNum);


/*******************************************************************************
  Function: R_AVB_UFStopLevelSet

  set unread frame counter stop level

  Parameters:
    Unit      - Instance number
    StopValue - number of unread frames reaching stop level
    ConfigNum - configuration

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_UFStopLevelSet(uint32_t Unit, uint8_t StopValue, uint8_t ConfigNum);


/*******************************************************************************
  Function: R_AVB_UFCounterGet

  get unread frame counter

  Parameters:
    Unit   - Instance number
    QIndex - index of queue

  Returns:
    number of unread frames
*/
uint32_t R_AVB_UFCounterGet(uint32_t Unit, uint32_t QIndex);


/*******************************************************************************
  Function: R_AVB_UFCounterDec

  decrease unread frame counter

  Parameters:
    Unit      - Instance number
    DecCount  - value to be decreased
    QIndex    - queue index

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_UFCounterDec(uint32_t Unit, uint32_t DecCount, uint32_t QIndex);


/*******************************************************************************
  Function: R_AVB_RxFilterSet

  set Rx filter

  Parameters:
    Unit      - Instance number
    SepFilter - seperation filter parameter

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_RxFilterSet(uint32_t Unit, r_avb_SepFilter_t *SepFilter);


/*******************************************************************************
  Function: R_AVB_RxDescChainConfig

  configure Rx descriptor chain

  Parameters:
    Unit     - Instance number
    ChConfig - Rx channel configuration, see <r_avb_RxChConfig_t>

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_RxDescChainConfig(uint32_t Unit, r_avb_RxChConfig_t *ChConfig);


/*******************************************************************************
  Function: R_AVB_RxDescChainUpdate

  update Rx descriptor chain

  Parameters:
    Unit        - Instance number
    DescPtr     - pointer to the to be updated descriptor
    ChConfig    - channel configuration, see <r_avb_RxChConfig_t>

  Returns:
    last processed descriptor address
*/
uint32_t R_AVB_RxDescChainUpdate(uint32_t Unit, uint32_t DescPtr, r_avb_RxChConfig_t *ChConfig);


/*******************************************************************************
  Function: R_AVB_RxQueueProcess

  process Rx queue

  Parameters:
    Unit       - Instance number
    RxFramePtr - pointer to Rx frame structure
    ChConfig   - channel configuration, see <r_avb_RxChConfig_t>

  Returns:
    void
*/
void R_AVB_RxQueueProcess(uint32_t Unit, uint32_t RxFramePtr, r_avb_RxChConfig_t *ChConfig);

/*******************************************************************************
  Function: R_AVB_TxSet

  Set Tx parameters

  Parameters:
    Unit     - Instance number
    TxConfig - see <r_avb_TxConfig_t>

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_TxSet(uint32_t Unit, r_avb_TxConfig_t *TxConfig);


/*******************************************************************************
  Function: R_AVB_TxReqStart

  start Tx request

  Parameters:
    Unit   - Instance number
    QIndex - queue index

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_TxReqStart(uint32_t Unit, uint32_t QIndex);


/*******************************************************************************
  Function: R_AVB_MacStatusFifoSet

  set MAC status FIFO

  Parameters:
    Unit   - Instance number
    Option - see <r_avb_Option_t>

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_MacStatusFifoSet(uint32_t Unit, r_avb_Option_t Option);


/*******************************************************************************
  Function: R_AVB_TimestampFifoSet

  set timestamp FIFO

  Parameters:
    Unit   - Instance number
    Option - see <r_avb_Option_t>

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_TimestampFifoSet(uint32_t Unit, r_avb_Option_t Option);


/*******************************************************************************
  Function: R_AVB_MacStatusFifoGet

  Get Mac status FIFO entry

  Parameters:
    Unit      - Instance number
    MacStatus - Mac status entry, see <r_avb_MACStatusFifo_t>

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_MacStatusFifoGet(uint32_t Unit, r_avb_MACStatusFifo_t *MacStatus);


/*******************************************************************************
  Function: R_AVB_MacStatusFifoLevelGet

  get Mac status FIFO level get

  Parameters:
    Unit   - Instance number

  Returns:
    Mac status fifo level
*/
uint32_t R_AVB_MacStatusFifoLevelGet(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_MacStatusFifoRelease

  release Mac status FIFO

  Parameters:
    Unit   - Instance number

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_MacStatusFifoRelease(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_TimestampFifoGet

  get timestamp FIFO

  Parameters:
    Unit   - Instance number
    Timestamp - timestamp entry, see <r_avb_TSFifo_t>

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_TimestampFifoGet(uint32_t Unit, r_avb_TSFifo_t *Timestamp);


/*******************************************************************************
  Function: R_AVB_TimestampFifoLevelGet

  get timestamp FIFO fill level

  Parameters:
    Unit   - Instance number

  Returns:
    Timestamp FIFO fill level
*/
uint32_t R_AVB_TimestampFifoLevelGet(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_TimestampFifoRelease

  release timestamp FIFO entry

  Parameters:
    Unit   - Instance number

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_TimestampFifoRelease(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_CbsCntStatusGet

  get CBS counter status

  Parameters:
    Unit      - Instance number
    CbsStatus - CBS status, see <r_avb_CBSCntStatus_t>
    QClass    - class of the queue

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_CbsCntStatusGet(uint32_t Unit, r_avb_CBSCntStatus_t *CbsStatus, r_avb_CBSCntClass_t QClass);


/*******************************************************************************
  Function: R_AVB_CbsParamSet

  set CBS parameters

  Parameters:
    Unit   - Instance number
    Param  - Cbs parameter, see <r_avb_CbsParam_t>
    QClass - queue class, see <r_avb_CBSCntClass_t>

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_CbsParamSet(uint32_t Unit, r_avb_CbsParam_t *Param, r_avb_CBSCntClass_t QClass);


/*******************************************************************************
  Function: R_AVB_SingleDescFrameSend

  send frame (single frame single buffer)

  Parameters:
    Unit   - Instance number
    QIndex - queue index
    Frame  - frame to be sent, see <r_avb_TxSingleFrame_t>

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_SingleDescFrameSend(uint32_t Unit, uint32_t QIndex, r_avb_TxSingleFrame_t *Frame);
r_avb_Error_t R_AVB_SingleDescGetNextFreeTxBuffer(uint32_t Unit, uint32_t QIndex, r_avb_TxSingleFrame_t *Frame);

/*******************************************************************************
  Function: R_AVB_MultiDescFrameSend

  send frame (single frame multi buffer)

  Parameters:
    Unit   - Instance number
    QIndex - queue index
    Frame  - frame to be sent, see <r_avb_TxMultiFrame_t>

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_MultiDescFrameSend(uint32_t Unit, uint32_t QIndex, r_avb_TxMultiFrame_t *Frame);



/*******************************************************************************
  Group: Interrupt Configuration
*/

/*******************************************************************************
  Function: R_AVB_ErrStatusGet

  get error status

  Parameters:
    Unit      - Instance number
    ErrStatus - Error status

  Returns:
    void
*/
void R_AVB_ErrStatusGet(uint32_t Unit, r_avb_ErrStatus_t *ErrStatus);


/*******************************************************************************
  Function: R_AVB_DescIntMaskSet

  set descriptor interrupt mask

  Parameters:
    Unit   - Instance number
    IntNum - interrupt number
    Option - see <r_avb_Option_t>

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_DescIntMaskSet(uint32_t Unit, uint32_t IntNum, r_avb_Option_t Option);


/*******************************************************************************
  Function: R_AVB_DescIntGet

  get descriptor interrupt status

  Parameters:
    Unit   - Instance number

  Returns:
    interupt status
*/
uint32_t R_AVB_DescIntGet(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_ErrIntMaskSet

  set error interrupt mask

  Parameters:
    Unit  - Instance number
    Mask  - interrupt mask

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_ErrIntMaskSet(uint32_t Unit, r_avb_ErrorInt_t *Mask);


/*******************************************************************************
  Function: R_AVB_ErrIntGet

  get error interrupt

  Parameters:
    Unit   - Instance number

  Returns:
    error interrupt
*/
uint32_t R_AVB_ErrIntGet(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_RxIntMaskSet

  set Rx interrupt mask

  Parameters:
    Unit   - Instance number
    Mask   - interrupt mask

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_RxIntMaskSet(uint32_t Unit, uint32_t Mask);


/*******************************************************************************
  Function: R_AVB_RxIntGet

  get Rx interrupt

  Parameters:
    Unit   - Instance number

  Returns:
    Rx interrupt
*/
uint32_t R_AVB_RxIntGet(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_RxWarningIntMaskSet

  set Rx warning interrupt mask

  Parameters:
    Unit   - Instance number
    Mask   - interrupt mask

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_RxWarningIntMaskSet(uint32_t Unit, uint32_t Mask);


/*******************************************************************************
  Function: R_AVB_RxWarningIntGet

  get Rx warning interrupt

  Parameters:
    Unit   - Instance number

  Returns:
    Rx warning interrupt
*/
uint32_t R_AVB_RxWarningIntGet(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_RxQFullIntMaskSet

  set Rx queue full interrupt mask

  Parameters:
    Unit   - Instance number
    Mask   - interrupt mask

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_RxQFullIntMaskSet(uint32_t Unit, uint32_t Mask);


/*******************************************************************************
  Function: R_AVB_RxQFullIntGet

  get Rx queue full interrupt

  Parameters:
    Unit   - Instance number

  Returns:
    Rx queue full interrupt
*/
uint32_t R_AVB_RxQFullIntGet(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_TxIntMaskSet

  set Tx interrupt mask

  Parameters:
    Unit   - Instance number
    Mask   - interrupt mask

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_TxIntMaskSet(uint32_t Unit, uint32_t Mask);


/*******************************************************************************
  Function: R_AVB_TxIntGet

  get Tx interrupt

  Parameters:
    Unit   - Instance number

  Returns:
    Tx interrupt
*/
uint32_t R_AVB_TxIntGet(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_TxMacStatusFifoIntGet

  get Tx Mac status fifo interrupt

  Parameters:
    Unit   - Instance number

  Returns:
    Tx Mac status fifo interrupt
*/
uint32_t R_AVB_TxMacStatusFifoIntGet(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_TxTSFifoIntGet

  get Tx timestamp fifo interrupt

  Parameters:
    Unit   - Instance number

  Returns:
    Tx timestamp fifo interrupt
*/
uint32_t R_AVB_TxTSFifoIntGet(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_GPtpIntMaskSet

  set gPTP interrupt mask

  Parameters:
    Unit   - Instance number
    Mask   - interrupt mask

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_GPtpIntMaskSet(uint32_t Unit, uint32_t Mask);


/*******************************************************************************
  Function: R_AVB_GPtpIntGet

  get gPTP interrupt

  Parameters:
    Unit   - Instance number

  Returns:
    gPTP interrupt status
*/
uint32_t R_AVB_GPtpIntGet(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_IntSummaryGet

  get interrupt summary

  Parameters:
    Unit   - Instance number

  Returns:
    interrupt summary
*/
uint32_t R_AVB_IntSummaryGet(uint32_t Unit);


/*******************************************************************************
  Group: AVB Error and ISR Functions
*/

/*******************************************************************************
  Function: R_AVB_SetErrorCallback

  Set a user function as error handler.

  When the driver detects any error, it will call this function.

  Parameters:
  ErrorCallback - Pointer to a user function

  Returns:
  void
*/
void R_AVB_SetErrorCallback(void (*ErrorCallback )(uint32_t Unit, uint32_t Error));


/*******************************************************************************
  Function: R_AVB_SetIsrCallback

  Assign a user callback for the given interrupt of a unit.

  The function will be called after the driver ISR has
  processed the interrupt.

  Parameters:
  Unit          - Instance number
  Interrupt       - What interrupt,  see: <r_avb_Interrupt_t>
  Isr           - Isr function pointer

  Returns:
  see: <r_avb_Error_t>
*/

 r_avb_Error_t R_AVB_SetIsrCallback(uint32_t Unit, r_avb_Interrupt_t Interrupt,
                                 void (*Isr)(void));


/*******************************************************************************
  Function: R_AVB_Isr

  AVB interrupt service routine.

  This function shall be called by device interrupt handler
  (xxxxxx_isr.c) and can be found in avb\src\avb_isr.c.

  Parameters:
  Unit       - Instance number
  Interrupt  - see <r_avb_Interrupt_t>

  Returns:
  void
*/

void R_AVB_Isr(uint32_t Unit, r_avb_Interrupt_t Interrupt);



/*******************************************************************************
  Function: R_AVB_EnableInt

  Enable the AVB interrupt 'Interrupt'.

  Parameters:
  Unit       - Instance number
  Interrupt  - Interrupt type see: <r_avb_Interrupt_t>

  Returns:
  void
*/

void R_AVB_EnableInt(uint32_t Unit, r_avb_Interrupt_t Interrupt);


/*******************************************************************************
  Function: R_AVB_DisableInt

  Disable the AVB interrupt 'Interrupt'.

  Parameters:
  Unit       - Instance number
  Interrupt  - Interrupt type see: <r_avb_Interrupt_t>

  Returns:
  void
*/

void R_AVB_DisableInt(uint32_t Unit, r_avb_Interrupt_t Interrupt);


void R_AVB_RxReadDone(uint32_t Unit,uint32_t RxFramePtr,r_avb_RxChConfig_t *ChConfig);

uint16_t R_AVB_SYS_LinkStatus(uint32_t Unit);
r_avb_Error_t R_AVB_SYS_Loopback(uint32_t Unit, uint32_t mode);
uint32_t loc_EthPhyLoopback(void);
r_avb_Error_t R_AVB_SYS_Reset(uint32_t Unit);

#ifdef __cplusplus
}
#endif

#endif /* AVB_API_H_  */
