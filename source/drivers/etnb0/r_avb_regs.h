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

#ifndef AVB_REGS_H_
#define AVB_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
  Title: AVB Register Offsets

  Only the driver modules shall include this header.
*/

/*******************************************************************************
  Section: Global Defines
*/

/***********************************************************
  Constants: AVB Register Offsets
*/
#define R_AVB_CCC        0x0
#define R_AVB_DBAT       0x4
#define R_AVB_DLR        0x8
#define R_AVB_CSR        0xc
#define R_AVB_CDARBASE   0x10
#define R_AVB_ESR        0x88
#define R_AVB_PSR        0x8c
#define R_AVB_RCR        0x90
#define R_AVB_RQCBASE    0x94
#define R_AVB_RPC        0xb0
#define R_AVB_RTCBASE    0xb4
#define R_AVB_UFCW       0xbc
#define R_AVB_UFCS       0xc0
#define R_AVB_UFCVBASE   0xc4
#define R_AVB_UFCDBASE   0xe0
#define R_AVB_SFO        0xfc
#define R_AVB_SFPBASE    0x100
#define R_AVB_SFMBASE    0x1c0
#define R_AVB_TGC        0x300
#define R_AVB_TCCR       0x304
#define R_AVB_TSR        0x308
#define R_AVB_MFA        0x30c
#define R_AVB_TFA0       0x310
#define R_AVB_TFA1       0x314
#define R_AVB_TFA2       0x318
#define R_AVB_CIVRBASE   0x320
#define R_AVB_CIVR0      0x320
#define R_AVB_CIVR1      0x324
#define R_AVB_CDVRBASE   0x328
#define R_AVB_CDVR0      0x328
#define R_AVB_CDVR1      0x32c
#define R_AVB_CULBASE    0x330
#define R_AVB_CUL0       0x330
#define R_AVB_CUL1       0x334
#define R_AVB_CLLBASE    0x338
#define R_AVB_CLL0       0x338
#define R_AVB_CLL1       0x33c

#define R_AVB_DIC        0x350
#define R_AVB_DIS        0x354
#define R_AVB_EIC        0x358
#define R_AVB_EIS        0x35c
#define R_AVB_RIC0       0x360
#define R_AVB_RIS0       0x364
#define R_AVB_RIC1       0x368
#define R_AVB_RIS1       0x36c
#define R_AVB_RIC2       0x370
#define R_AVB_RIS2       0x374
#define R_AVB_TIC        0x378
#define R_AVB_TIS        0x37c
#define R_AVB_ISS        0x380

#define R_AVB_GCCR       0x390
#define R_AVB_GMTT       0x394
#define R_AVB_GPTC       0x398
#define R_AVB_GTI        0x39c
#define R_AVB_GTOBASE    0x3a0
#define R_AVB_GTO0       0x3a0
#define R_AVB_GTO1       0x3a4
#define R_AVB_GTO2       0x3a8
#define R_AVB_GIC        0x3ac
#define R_AVB_GIS        0x3b0
#define R_AVB_GCPT       0x3b4
#define R_AVB_GCTBASE    0x3b8
#define R_AVB_GCT0       0x3b8
#define R_AVB_GCT1       0x3bc
#define R_AVB_GCT2       0x3c0


/***********************************************************
  Constants: MAC Register Offsets
*/
#define R_AVB_ECMR    0x500     /* MAC mode register */
#define R_AVB_RFLR    0x508     /* receive frame length register */
#define R_AVB_ECSR    0x510     /* MAC status register */
#define R_AVB_ECSIPR  0x518     /* MAC interrupt permission register */
#define R_AVB_PIR     0x520     /* PHY interface register */
#define R_AVB_PLSR    0x528     /* PHY link status register */
#define R_AVB_APFTP   0x554     /* automatic pause frame time parameter register */
#define R_AVB_MPR     0x558     /* manual pause frame register */
#define R_AVB_PFTCR   0x55C     /* pause frame transmit counter register */
#define R_AVB_PFRCR   0x560     /* pause frame receive counter register */
#define R_AVB_GECMR   0x5B0     /* Gether mode register */
#define R_AVB_MAHR    0x5C0     /* MAC address high register */
#define R_AVB_MALR    0x5C8     /* MAC address low register */

#define R_AVB_TROCR   0x700     /* transmit retry over count register */
#define R_AVB_CDCR    0x708     /* delayed collision detect counter register */
#define R_AVB_LCCR    0x710     /* lost carrier counter register */
#define R_AVB_CEFCR   0x740     /* CRC error frame receive counter register */
#define R_AVB_FRECR   0x748     /* frame receive error counter register */
#define R_AVB_TSFRCR  0x750     /* too short frame receive counter register */
#define R_AVB_TLFRCR  0x758     /* too long frame receive counter register */
#define R_AVB_RFCR    0x760     /* residual-bit frame receive counter register */
#define R_AVB_MAFCR   0x778     /* multicast address frame counter register */
#define R_AVB_IFCTL   0x1000    /* Communication interface control register */

/*******************************************************************************
  Section: Global Types
  
  AVB Register Definitions
*/

/***********************************************************
  Type: r_avb_RegCccBits_t

  Content of register CCC

  Members:
    Opc     - operation command
    Dtsr    - data transfer suspend request
    Tdis    - transmission disable
    Csel    - clock select
    Boc     - byte order configuration
    Lbme    - loopback mode enable
    Res1-5  - reserved

*/
typedef struct {
    uint32_t Opc   : 2;
    uint32_t Res1  : 6;
    uint32_t Dtsr  : 1;
    uint32_t Tdis  : 1;
    uint32_t Res2  : 6;
    uint32_t Csel  : 2;
    uint32_t Res3  : 2;
    uint32_t Boc   : 1;
    uint32_t Res4  : 3;
    uint32_t Lbme  : 1;
    uint32_t Res5  : 7;
} r_avb_CccBits_t;


/***********************************************************
  Union: r_avb_Ccc_t

  Simplifies Bit and Byte access to register

  Members:
    Bit   - Allow bit access.
    Word  - Allow access of the whole word.
*/
typedef union {
    r_avb_CccBits_t  Bit;
    uint32_t         Word;
} r_avb_Ccc_t;


/***********************************************************
  Type: r_avb_CsrBits_t

  Content of register CSR

  Members:
    Ops     - operation status
    Dts     - data transfer suspened
    Tpo0    - transmission process ongoing (best effort)
    Tpo1    - transmission process ongoing (network control)
    Tpo2    - transmission process ongoing (stream class B)
    Tpo3    - transmission process ongoing (stream class A)
    Rpo     - reception process ongoing
    Res1-3  - reserved

*/
typedef struct {
    uint32_t Ops   : 4;
    uint32_t Res1  : 4;
    uint32_t Dts   : 1;
    uint32_t Res2  : 7;
    uint32_t Tpo0  : 1;
    uint32_t Tpo1  : 1;
    uint32_t Tpo2  : 1;
    uint32_t Tpo3  : 1;
    uint32_t Rpo   : 1;
    uint32_t Res3  : 11;
} r_avb_CsrBits_t;


/***********************************************************
  Union: r_avb_Csr_t

  Simplifies Bit and Byte access to register

  Members:
    Bit   - Allow bit access.
    Word  - Allow access of the whole word.
*/
typedef union {
    r_avb_CsrBits_t  Bit;
    uint32_t         Word;
} r_avb_Csr_t;


/***********************************************************
  Type: r_avb_EsrBits_t

  Content of register ESR

  Members:
    Eqn     - error queue number
    Et      - error type
    Eil     - error information lost
    Res1-2  - reserved

*/
typedef struct {
    uint32_t Eqn   : 5;
    uint32_t Res1  : 3;
    uint32_t Et    : 4;
    uint32_t Eil   : 1;
    uint32_t Res2  : 19;
} r_avb_EsrBits_t;


/***********************************************************
  Union: r_avb_Esr_t

  Simplifies Bit and Byte access to register

  Members:
    Bit   - Allow bit access.
    Word  - Allow access of the whole word.
*/
typedef union {
    r_avb_EsrBits_t  Bit;
    uint32_t         Word;
} r_avb_Esr_t;


/***********************************************************
  Type: r_avb_RcrBits_t

  Content of register RCR

  Members:
    Effs    - enable faulty frame storage
    Encf    - enable network control filtering
    Esf     - enable stream filtering
    Ets0    - enable timestamp storage 0 (best effort)
    Ets2    - enable timestamp storage 2 (stream)
    Rfcl    - reception FIFO critical level
    Res1-2  - reserved

*/
typedef struct {
    uint32_t Effs  : 1;
    uint32_t Encf  : 1;
    uint32_t Esf   : 2;
    uint32_t Ets0  : 1;
    uint32_t Ets2  : 1;
    uint32_t Res1  : 10;
    uint32_t Rfcl  : 13;
    uint32_t Res2  : 3;
} r_avb_RcrBits_t;


/***********************************************************
  Union: r_avb_Rcr_t

  Simplifies Bit and Byte access to register

  Members:
    Bit   - Allow bit access.
    Word  - Allow access of the whole word.
*/
typedef union {
    r_avb_RcrBits_t  Bit;
    uint32_t         Word;
} r_avb_Rcr_t;


/***********************************************************
  Type: r_avb_UfcwcsBits_t

  Content of register UFCW/UFCS

  Members:
    WlSl0   - number of unread frames when to reach warning level/stop level 0
    WlSl1   - number of unread frames when to reach warning level/stop level 1
    WlSl2   - number of unread frames when to reach warning level/stop level 2
    WlSl3   - number of unread frames when to reach warning level/stop level 3
    Res0-3  - reserved
*/
typedef struct {
    uint32_t WlSl0  : 6;
    uint32_t Res0   : 2;
    uint32_t WlSl1  : 6;
    uint32_t Res1   : 2;
    uint32_t WlSl2  : 6;
    uint32_t Res2   : 2;
    uint32_t WlSl3  : 6;
    uint32_t Res3   : 2;
} r_avb_UfcwcsBits_t;


/***********************************************************
  Union: r_avb_Ufcwcs_t

  Simplifies Bit and Byte access to register

  Members:
    Bit   - Allow bit access.
    Word  - Allow access of the whole word.
*/
typedef union {
    r_avb_UfcwcsBits_t  Bit;
    uint32_t            Word;
} r_avb_Ufcwcs_t;


/***********************************************************
  Type: r_avb_TgcBits_t

  Content of register TGC

  Members:
    Tsm0   - transmit synchronisation mode0 (best effort)
    Tsm1   - transmit synchronisation mode1 (network control)
    Tsm2   - transmit synchronisation mode2 (stream class B)
    Tsm3   - transmit synchronisation mode3 (stream class A)
    Tqp    - transmission queues priority
    Tbd0   - transmit buffer depth 0 (best effort)
    Tbd1   - transmit buffer depth 1 (network control)
    Tbd2   - transmit buffer depth 2 (stream class B)
    Tbd3   - transmit buffer depth 3 (stream class A)
    Res1-5 - reserved
*/
typedef struct {
    uint32_t Tsm0   : 1;
    uint32_t Tsm1   : 1;
    uint32_t Tsm2   : 1;
    uint32_t Tsm3   : 1;
    uint32_t Tqp    : 2;
    uint32_t Res1   : 2;
    uint32_t Tbd0   : 2;
    uint32_t Res2   : 2;
    uint32_t Tbd1   : 2;
    uint32_t Res3   : 2;
    uint32_t Tbd2   : 2;
    uint32_t Res4   : 2;
    uint32_t Tbd3   : 2;
    uint32_t Res5   : 10;
} r_avb_TgcBits_t;


/***********************************************************
  Union: r_avb_Tgc_t

  Simplifies Bit and Byte access to register

  Members:
    Bit   - Allow bit access.
    Word  - Allow access of the whole word.
*/
typedef union {
    r_avb_TgcBits_t  Bit;
    uint32_t         Word;
} r_avb_Tgc_t;


/***********************************************************
  Type: r_avb_TccrBits_t

  Content of register TCCR

  Members:
    Tsrq0   - transmission start request queue0 (best effort)
    Tsrq1   - transmission start request queue1 (network control)
    Tsrq2   - transmission start request queue2 (stream class B)
    Tsrq3   - transmission start request queue3 (stream class A)
    Tfen    - timestamp FIFO enable
    Tfr     - timestamp FIFO release
    Mfen    - MAC status FIFO enable
    Mfr     - MAC status FIFO release
    Res1-3  - reserved
*/
typedef struct {
    uint32_t Tsrq0   : 1;
    uint32_t Tsrq1   : 1;
    uint32_t Tsrq2   : 1;
    uint32_t Tsrq3   : 1;
    uint32_t Res1    : 4;
    uint32_t Tfen    : 1;
    uint32_t Tfr     : 1;
    uint32_t Res2    : 6;
    uint32_t Mfen    : 1;
    uint32_t Mfr     : 1;
    uint32_t Res3    : 14;
} r_avb_TccrBits_t;


/***********************************************************
  Union: r_avb_Tccr_t

  Simplifies Bit and Byte access to register

  Members:
    Bit   - Allow bit access.
    Word  - Allow access of the whole word.
*/
typedef union {
    r_avb_TccrBits_t  Bit;
    uint32_t          Word;
} r_avb_Tccr_t;


/***********************************************************
  Type: r_avb_MfaBits_t

  Content of register MFA

  Members:
    Msv    - MAC status value
    Mst    - Tag number from descriptor identifying the frame MAC status relation
    Res1-2 - reserved
*/
typedef struct {
    uint32_t Msv  : 4;
    uint32_t Res1 : 12;
    uint32_t Mst  : 10;
    uint32_t Res2 : 6;
} r_avb_MfaBits_t;


/***********************************************************
  Union: r_avb_Mfa_t

  Simplifies Bit and Byte access to register

  Members:
    Bit   - Allow bit access.
    Word  - Allow access of the whole word.
*/
typedef union {
    r_avb_MfaBits_t  Bit;
    uint32_t         Word;
} r_avb_Mfa_t;


/***********************************************************
  Type: r_avb_EicBits_t

  Content of register EIC

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
    Res     - reserved
*/
typedef struct {
    uint32_t Mree  : 1;
    uint32_t Mtee  : 1;
    uint32_t Qee   : 1;
    uint32_t See   : 1;
    uint32_t Clle0 : 1;
    uint32_t Clle1 : 1;
    uint32_t Cule0 : 1;
    uint32_t Cule1 : 1;
    uint32_t Tffe  : 1;
    uint32_t Mffe  : 1;
    uint32_t Res   : 22;
} r_avb_EicBits_t;


/***********************************************************
  Union: r_avb_Eic_t

  Simplifies Bit and Byte access to register

  Members:
    Bit   - Allow bit access.
    Word  - Allow access of the whole word.
*/
typedef union {
    r_avb_EicBits_t  Bit;
    uint32_t         Word;
} r_avb_Eic_t;


/***********************************************************
  Type: r_avb_EcmrBits_t

  Content of register ECMR

  Members:
    Prm         - Promiscuous mode
    Dpm         - duplex mode
    Tpe         - transmission enable
    Rpe         - reception enable
    Mpm         - magic packet detection
    Cer         - debugging function bit
    Txf         - transmission flow control
    Rxf         - reception flow control
    Pfr         - pause frame reception mode
    Tzpf        - zero pause frame transmission with Time = 0
    Rzpf        - zero pause frame reception with Time = 0
    Dpad        - data padding disable (1 for disable, 0 for enable!!!!!!)
    Cxser       - carrier extension short error
    Rcsc        - reception checksum calculation
    Tcpt        - debugging function bit
    Rcpt        - debugging function bit
    Trccm       - Counter clear mode
    Crscm       - Crs check mode
    T1tm        - tint1 test mode
    Res1 - Res7 - reserved
*/
typedef struct {
    uint32_t Prm   : 1;
    uint32_t Dpm   : 1;
    uint32_t Res1  : 3;
    uint32_t Tpe   : 1;
    uint32_t Rpe   : 1;
    uint32_t Res2  : 2;
    uint32_t Mpm   : 1;
    uint32_t Res3  : 2;
    uint32_t Cer   : 1;
    uint32_t Res4  : 3;
    uint32_t Txf   : 1;
    uint32_t Rxf   : 1;
    uint32_t Pfr   : 1;
    uint32_t Tzpf  : 1;
    uint32_t Rzpf  : 1;
    uint32_t Dpad  : 1;
    uint32_t Cxser : 1;
    uint32_t Rcsc  : 1;
    uint32_t Tcpt  : 1;
    uint32_t Rcpt  : 1;
    uint32_t Trccm : 1;
    uint32_t Crscm : 1;
    uint32_t Res7  : 3;
    uint32_t T1tm  : 1;
} r_avb_EcmrBits_t;


/***********************************************************
  Union: r_avb_Ecmr_t

  Simplifies Bit and Byte access to register

  Members:
    Bit   - Allow bit access.
    Word  - Allow access of the whole word.
*/
typedef union {
    r_avb_EcmrBits_t Bit;
    uint32_t         Word;
} r_avb_Ecmr_t;


/***********************************************************
  Type: r_avb_EcsiprBits_t

  Content of register Ecsipr

  Members:
    Fcim   - illegal carrier detection interrupt enable
    Mpdim  - magic packet detection interrupt enable
    Linkim - link signal change interrupt enable
    Phyim  - PHY Pin interrupt enable
    Res1   - reserved
*/
typedef struct {
    uint32_t Fcim   : 1;
    uint32_t Mpdim  : 1;
    uint32_t Linkim : 1;
    uint32_t Phyim  : 1;
    uint32_t Res1   : 28;
} r_avb_EcsiprBits_t;


/***********************************************************
  Union: r_avb_Ecsipr_t

  Simplifies Bit and Byte access to register

  Members:
    Bit   - Allow bit access.
    Word  - Allow access of the whole word.
*/
typedef union {
    r_avb_EcsiprBits_t Bit;
    uint32_t          Word;
} r_avb_Ecsipr_t;


/***********************************************************
  Type: r_avb_GecmrBits_t

  Content of register Gecmr

  Members:
    Speed   - transmission speed
    Bse     - burst transmission enable
    Res1    - reserved
*/
typedef struct {
    uint32_t    Speed : 1;
    uint32_t    Bse   : 1;
    uint32_t    Res1  : 30;
} r_avb_GecmrBits_t;


/***********************************************************
  Union: r_avb_Gecmr_t

  Simplifies Bit and Byte access to register

  Members:
    Bit   - Allow bit access.
    Word  - Allow access of the whole word.
*/
typedef union {
    r_avb_GecmrBits_t Bit;
    uint32_t             Word;
} r_avb_Gecmr_t;


#ifdef __cplusplus
}
#endif

#endif /* AVB_REGS_H_ */
