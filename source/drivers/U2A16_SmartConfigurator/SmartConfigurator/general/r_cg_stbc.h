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
* Copyright (C) 2018, 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : r_cg_stbc.h
* Version          : 1.0.140
* Device(s)        : R7F702300BFABA
* Description      : General header file for STBC peripheral.
***********************************************************************************************************************/

#ifndef STBC_H
#define STBC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Wake up factor register (WUFC0_A0)
*/
/* Clear the WUFy bits in the wake-up factor registers */
#define _STBC_WUFC0_A0_CLEAR                                       (0x003FFFE1UL) /* Wake-up event is cleared */

/*
    Wake up factor register (WUFC0_A1)
*/
/* Clear the WUFy bits in the wake-up factor registers */
#define _STBC_WUFC0_A1_CLEAR                                       (0x00FFFFFFUL) /* Wake-up event is cleared */
/*
    Wake up factor register (WUFC0_A2)
*/
/* Clear the WUFy bits in the wake-up factor registers */
#define _STBC_WUFC0_A2_CLEAR                                       (0x0007FFFFUL) /* Wake-up event is cleared */

/*
    Wake up factor register (WUFC0_I0)
*/
/* Clear the WUFy bits in the wake-up factor registers */
#define _STBC_WUFC0_I0_CLEAR                                       (0x0003FFFFUL) /* Wake-up event is cleared */

/*
    Wake up factor register (WUFC0_I1)
*/
/* Clear the WUFy bits in the wake-up factor registers */
#define _STBC_WUFC0_I1_CLEAR                                       (0x00FFFFFFUL) /* Wake-up event is cleared */
/*
    Wake up factor register (WUFMSK0_A0)
*/
/* Indicates enable a wake-up event (WUFMSK0_A00) */
#define _STBC_WUFMSK0_A0_FACTOR_TNMI                               (0xFFFFFFFEUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A05) */
#define _STBC_WUFMSK0_A0_FACTOR_INTWDTBA                           (0xFFFFFFDFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A06) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP0                              (0xFFFFFFBFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A07) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP1                              (0xFFFFFF7FUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A08) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP2                              (0xFFFFFEFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A09) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP3                              (0xFFFFFDFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A010) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP4                              (0xFFFFFBFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A011) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP5                              (0xFFFFF7FFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A012) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP6                              (0xFFFFEFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A013) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP7                              (0xFFFFDFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A014) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP8                              (0xFFFFBFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A015) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP9                              (0xFFFF7FFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A016) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP10                             (0xFFFEFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A017) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP11                             (0xFFFDFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A018) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP12                             (0xFFFBFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A019) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP13                             (0xFFF7FFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A020) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP14                             (0xFFEFFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A021) */
#define _STBC_WUFMSK0_A0_FACTOR_INTP15                             (0xFFDFFFFFUL) /* Wake-up event is enabled */

/*
Wake up factor register (WUFMSK0_A1)
*/
/* Indicates enable a wake-up event (WUFMSK0_A10) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP16                             (0xFFFFFFFEUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A11) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP17                             (0xFFFFFFFDUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A12) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP18                             (0xFFFFFFFBUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A13) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP19                             (0xFFFFFFF7UL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A14) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP20                             (0xFFFFFFEFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A15) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP21                             (0xFFFFFFDFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A16) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP22                             (0xFFFFFFBFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A17) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP23                             (0xFFFFFF7FUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A18) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP24                             (0xFFFFFEFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A19) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP25                             (0xFFFFFDFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A110) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP26                             (0xFFFFFBFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A111) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP27                             (0xFFFFF7FFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A112) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP28                             (0xFFFFEFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A113) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP29                             (0xFFFFDFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A114) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP30                             (0xFFFFBFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A115) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP31                             (0xFFFF7FFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A116) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP32                             (0xFFFEFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A117) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP33                             (0xFFFDFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A118) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP34                             (0xFFFBFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A119) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP35                             (0xFFF7FFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A120) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP36                             (0xFFEFFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A121) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP37                             (0xFFDFFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A122) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP38                             (0xFFBFFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A123) */
#define _STBC_WUFMSK0_A1_FACTOR_INTP39                             (0xFF7FFFFFUL) /* Wake-up event is enabled */

/*
Wake up factor register (WUFMSK0_A2)
*/
/* Indicates enable a wake-up event (WUFMSK0_A20) */
#define _STBC_WUFMSK0_A2_FACTOR_WUTRG0                             (0xFFFFFFFEUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A21) */
#define _STBC_WUFMSK0_A2_FACTOR_WUTRG1                             (0xFFFFFFFDUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A22) */
#define _STBC_WUFMSK0_A2_FACTOR_INTDCUTDI                          (0xFFFFFFFBUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A23) */
#define _STBC_WUFMSK0_A2_FACTOR_INTTAUJ2I0                         (0xFFFFFFF7UL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A24) */
#define _STBC_WUFMSK0_A2_FACTOR_INTTAUJ2I1                         (0xFFFFFFEFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A25) */
#define _STBC_WUFMSK0_A2_FACTOR_INTTAUJ2I2                         (0xFFFFFFDFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A26) */
#define _STBC_WUFMSK0_A2_FACTOR_INTTAUJ2I3                         (0xFFFFFFBFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A27) */
#define _STBC_WUFMSK0_A2_FACTOR_INTTAUJ3I0                         (0xFFFFFF7FUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A28) */
#define _STBC_WUFMSK0_A2_FACTOR_INTTAUJ3I1                         (0xFFFFFEFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A29) */
#define _STBC_WUFMSK0_A2_FACTOR_INTTAUJ3I2                         (0xFFFFFDFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A210) */
#define _STBC_WUFMSK0_A2_FACTOR_INTTAUJ3I3                         (0xFFFFFBFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A211) */
#define _STBC_WUFMSK0_A2_FACTOR_INTRTCA01S                         (0xFFFFF7FFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A212) */
#define _STBC_WUFMSK0_A2_FACTOR_INTRTCA0AL                         (0xFFFFEFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A213) */
#define _STBC_WUFMSK0_A2_FACTOR_INTRTCA0R                          (0xFFFFDFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A214) */
#define _STBC_WUFMSK0_A2_FACTOR_INTADC2I0                          (0xFFFFBFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A215) */
#define _STBC_WUFMSK0_A2_FACTOR_INTADC2I1                          (0xFFFF7FFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A216) */
#define _STBC_WUFMSK0_A2_FACTOR_INTADC2I2                          (0xFFFEFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A217) */
#define _STBC_WUFMSK0_A2_FACTOR_INTADC2I3                          (0xFFFDFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_A218) */
#define _STBC_WUFMSK0_A2_FACTOR_INTADC2I4                          (0xFFFBFFFFUL) /* Wake-up event is enabled */

/*
Wake up factor register (WUFMSK0_I0)
*/
/* Indicates enable a wake-up event (WUFMSK0_I00) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCANGRECC0                      (0xFFFFFFFEUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I01) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN0REC                        (0xFFFFFFFDUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I02) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN1REC                        (0xFFFFFFFBUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I03) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN2REC                        (0xFFFFFFF7UL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I04) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN3REC                        (0xFFFFFFEFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I05) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN4REC                        (0xFFFFFFDFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I06) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN5REC                        (0xFFFFFFBFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I07) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN6REC                        (0xFFFFFF7FUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I08) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN7REC                        (0xFFFFFEFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I09) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCANGRECC1                      (0xFFFFFDFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I010) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN8REC                        (0xFFFFFBFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I011) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN9REC                        (0xFFFFF7FFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I012) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN10REC                       (0xFFFFEFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I013) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN11REC                       (0xFFFFDFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I014) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN12REC                       (0xFFFFBFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I015) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN13REC                       (0xFFFF7FFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I016) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN14REC                       (0xFFFEFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I017) */
#define _STBC_WUFMSK0_I0_FACTOR_INTRCAN15REC                       (0xFFFDFFFFUL) /* Wake-up event is enabled */

/*
Wake up factor register (WUFMSK0_I1)
*/
/* Indicates enable a wake-up event (WUFMSK0_I10) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN30                          (0xFFFFFFFEUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I11) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN31                          (0xFFFFFFFDUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I12) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN32                          (0xFFFFFFFBUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I13) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN33                          (0xFFFFFFF7UL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I14) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN34                          (0xFFFFFFEFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I15) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN35                          (0xFFFFFFDFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I16) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN36                          (0xFFFFFFBFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I17) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN37                          (0xFFFFFF7FUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I18) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN38                          (0xFFFFFEFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I19) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN39                          (0xFFFFFDFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I110) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN310                         (0xFFFFFBFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I111) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN311                         (0xFFFFF7FFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I112) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN312                         (0xFFFFEFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I113) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN313                         (0xFFFFDFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I114) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN314                         (0xFFFFBFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I115) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN315                         (0xFFFF7FFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I116) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN316                         (0xFFFEFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I117) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN317                         (0xFFFDFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I118) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN318                         (0xFFFBFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I119) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN319                         (0xFFF7FFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I120) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN320                         (0xFFEFFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I121) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN321                         (0xFFDFFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I122) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN322                         (0xFFBFFFFFUL) /* Wake-up event is enabled */
/* Indicates enable a wake-up event (WUFMSK0_I123) */
#define _STBC_WUFMSK0_I1_FACTOR_INTRLIN323                         (0xFF7FFFFFUL) /* Wake-up event is enabled */

/*
Power save control register (STBC0PSC)
*/
/* Power save control (STBC0DISTRG) */
#define _STBC_DEEP_STOP_MODE_DISABLE                               (0x00000000UL) /* Writing 0 has no effect */
#define _STBC_DEEP_STOP_MODE_ENTERED                               (0x00000002UL) /* DeepSTOP mode is entered */

/*
Power stop trigger register (STBC0STPT)
*/
/* Power stop trigger (STBC0STPTRG) */
#define _STBC_STOP_MODE_DISABLE                                    (0x00000000UL) /* Writing 0 has no effect */
#define _STBC_STOP_MODE_ENTERED                                    (0x00000001UL) /* Stop mode is entered */

/*
Module Standby Register for modules (MSR_<name>)
*/
/* Setting this bit to 1 stops all clocks connected to modules */
#define _STBC_MODULE_CLOCK_OPERATED                                (0) /* Module clock is operating */
#define _STBC_MODULE_CLOCK_STOPPED                                 (1) /* All clocks connected to module are stopped */
/* This bit controls the operation of module clock in STOP(and DeepSTOP) and Cyclic STOP mode*/
#define _STBC_MODULE_CLOCK_NOT_MASK                                (0) /* Module Clock stops in STOP
                                                                       (and DeepSTOP )and Cyclic STOP mode */
#define _STBC_MODULE_CLOCK_MASK                                    (1) /* Module Clock operates in STOP
                                                                       (and DeepSTOP )and Cyclic STOP mode */

/*
reset factor clear register (RESFC)
*/
/* DeepSTOP Reset Flag Clear (DRESFC0) */
#define _RESFC_RESET_FLAG_CLEAR                                    (0x00001000UL) /* Clear flag */

/*
Software Module Reset Status Register (SWMRESS_<name>)
*/
/* Software Module Reset Status for module <name> */
#define _MODULE_RESET_BEING_PROCESSED_NO                           (0) /* Reset execution is not being processed. */
#define _MODULE_RESET_BEING_PROCESSED_YES                          (1) /* Reset execution is being processed. */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
