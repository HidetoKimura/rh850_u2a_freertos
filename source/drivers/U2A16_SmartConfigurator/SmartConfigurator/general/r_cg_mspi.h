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
* File Name        : r_cg_mspi.h
* Version          : 1.0.140
* Device(s)        : R7F702300BFABA
* Description      : General header file for MSPI peripheral.
***********************************************************************************************************************/

#ifndef MSPI_H
#define MSPI_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    MSPIn Control Register 0 (MSPInCTL0)
*/
/* This bit enables or disables the MSPI Function */
#define _MSPI_FUNCTION_DISABLE                      (0x00U) /* Disables the MSPIn function. */
#define _MSPI_FUNCTION_ENABLE                       (0x01U) /* Enables the MSPIn function. */

/*
    MSPIn Control Register 1 (MSPInCTL1)
*/
/* This bit selects Master/Slave Mode (MSPInMSSEL) */
#define _MSPI_MASTER_MODE                           (0x00000000UL) /* Master mode */
#define _MSPI_SLAVE_MODE                            (0x80000000UL) /* Slave mode */
/* This bit enables or disables the slave select signal(MSPInCSI) in slave mode (MSPInCSIE) */
#define _MSPI_CS_SIGNAL_IGNORED                     (0x00000000UL) /* Input CS signal is ignored in slave mode */
#define _MSPI_CS_SIGNAL_RECOGNIZED                  (0x20000000UL) /* Input CS signal is recognized in slave mode */
/* This bit controls the internal sampling timing for receive data in master mode (MSPInSAMP) */
#define _MSPI_SAMPLE_STANDARD                       (0x00000000UL) /* Standard sampling point of SPI protocol */
#define _MSPI_SAMPLE_NEXT_EDGE                      (0x10000000UL)    /* Next edge sampling point of SPI protocol */
/* This bit selects MSPIn Clock default level (MSPInCKR) */
#define _MSPI_CLOCK_DEFAULT_LOW                     (0x00000000UL) /* The default level of MSPInSCK is low */
#define _MSPI_CLOCK_DEFAULT_HIGH                    (0x08000000UL) /* The default level of MSPInSCK is high */
/* These bits select the MSPInSOUT function in Master mode (MSPInSOLS) */
#define _MSPI_MSPISOUT_ENABLE_LOW_END_HOLD          (0x00000000UL) /* MSPInSOUT:low after enable, holds level. */
#define _MSPI_MSPISOUT_ENABLE_LOW_IDLE_LOW          (0x01000000UL) /* MSPInSOUT:low after enable, idle set low. */
#define _MSPI_MSPISOUT_ENABLE_HIGH_END_HOLD         (0x02000000UL) /* MSPInSOUT:high after enable, holds level. */
#define _MSPI_MSPISOUT_ENABLE_HIGH_IDLE_HIGH        (0x03000000UL) /* MSPInSOUT:low after enable, idle set high. */
/* These bits control the polarity of MSPI7CS (MSPI7CSP) */
#define _MSPI_CS7_SIGNAL_ACTIVE_LOW                 (0x00000000UL) /* The MSPInCS signal is active low.. */
#define _MSPI_CS7_SIGNAL_ACTIVE_HIGH                (0x00000080UL) /* The MSPInCS signal is active high. */
/* These bits control the polarity of MSPI6CS (MSPI6CSP) */
#define _MSPI_CS6_SIGNAL_ACTIVE_LOW                 (0x00000000UL) /* The MSPInCS signal is active low.. */
#define _MSPI_CS6_SIGNAL_ACTIVE_HIGH                (0x00000040UL) /* The MSPInCS signal is active high. */
/* These bits control the polarity of MSPI5CS (MSPI5CSP) */
#define _MSPI_CS5_SIGNAL_ACTIVE_LOW                 (0x00000000UL) /* The MSPInCS signal is active low.. */
#define _MSPI_CS5_SIGNAL_ACTIVE_HIGH                (0x00000020UL) /* The MSPInCS signal is active high. */
/* These bits control the polarity of MSPI4CS (MSPI4CSP) */
#define _MSPI_CS4_SIGNAL_ACTIVE_LOW                 (0x00000000UL) /* The MSPInCS signal is active low.. */
#define _MSPI_CS4_SIGNAL_ACTIVE_HIGH                (0x00000010UL) /* The MSPInCS signal is active high. */
/* These bits control the polarity of MSPI3CS (MSPI3CSP) */
#define _MSPI_CS3_SIGNAL_ACTIVE_LOW                 (0x00000000UL) /* The MSPInCS signal is active low.. */
#define _MSPI_CS3_SIGNAL_ACTIVE_HIGH                (0x00000008UL) /* The MSPInCS signal is active high. */
/* These bits control the polarity of MSPI2CS (MSPI2CSP) */
#define _MSPI_CS2_SIGNAL_ACTIVE_LOW                 (0x00000000UL) /* The MSPInCS signal is active low.. */
#define _MSPI_CS2_SIGNAL_ACTIVE_HIGH                (0x00000004UL) /* The MSPInCS signal is active high. */
/* These bits control the polarity of MSPI1CS (MSPI1CSP) */
#define _MSPI_CS1_SIGNAL_ACTIVE_LOW                 (0x00000000UL) /* The MSPInCS signal is active low.. */
#define _MSPI_CS1_SIGNAL_ACTIVE_HIGH                (0x00000002UL) /* The MSPInCS signal is active high. */
/* These bits control the polarity of MSPI0CS (MSPI0CSP) */
#define _MSPI_CS0_SIGNAL_ACTIVE_LOW                 (0x00000000UL) /* The MSPInCS signal is active low.. */
#define _MSPI_CS0_SIGNAL_ACTIVE_HIGH                (0x00000001UL) /* The MSPInCS signal is active high. */

/*
    MSPI Control Register 2 (MSPInCTL2)
*/
/* This bit enables or disables the data consistency check (MSPInDCS) */
#define _MSPI_CONSISTENCY_DISABLE                   (0x00U) /* Disables the data consistency check. */
#define _MSPI_CONSISTENCY_ENABLE                    (0x02U) /* Enables the data consistency check. */
/* This bit enables or disables the loop-back mode (MSPInLBM) */
#define _MSPI_LOOPBACK_DISABLE                      (0x00U) /* Disables the loop-back mode. */
#define _MSPI_LOOPBACK_ENABLE                       (0x01U) /* Enables the loop-back mode. */

/*
    MSPIn Status Register 0 (MSPInSTR0)
*/
/* These bits indicate the number of the communicating channel (MSPInCNUMF) */
#define _MSPI_COMMUNICATING_CHANNEL_0               (0x00U) /* The communicating channel is channel 0. */
#define _MSPI_COMMUNICATING_CHANNEL_1               (0x10U) /* The communicating channel is channel 1. */
#define _MSPI_COMMUNICATING_CHANNEL_2               (0x20U) /* The communicating channel is channel 2. */
#define _MSPI_COMMUNICATING_CHANNEL_3               (0x30U) /* The communicating channel is channel 3. */
#define _MSPI_COMMUNICATING_CHANNEL_4               (0x40U) /* The communicating channel is channel 4. */
#define _MSPI_COMMUNICATING_CHANNEL_5               (0x50U) /* The communicating channel is channel 5. */
#define _MSPI_COMMUNICATING_CHANNEL_6               (0x60U) /* The communicating channel is channel 6. */
#define _MSPI_COMMUNICATING_CHANNEL_7               (0x70U) /* The communicating channel is channel 7. */
/* This bit indicates the communication status of master mode (MSPInCSF) */
#define _MSPI_MASTER_STATUS_ABNARMAL                (0x00U) /* All channels stop. */
#define _MSPI_MASTER_STATUS_NARMAL                  (0x01U) /* Narmal status. */

/*
    MSPIn Channel Status Register m (MSPInCSTRm)
*/
/* These bits indicate the number of received data not being read in fixed FIFO memory mode (MSPInFIRXNm) */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_0       (0x0000U) /* The number of received data not read is 0. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_1       (0x0100U) /* The number of received data not read is 1. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_2       (0x0200U) /* The number of received data not read is 2. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_3       (0x0300U) /* The number of received data not read is 3. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_4       (0x0400U) /* The number of received data not read is 4. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_5       (0x0500U) /* The number of received data not read is 5. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_6       (0x0600U) /* The number of received data not read is 6. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_7       (0x0700U) /* The number of received data not read is 7. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_8       (0x0800U) /* The number of received data not read is 8. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_9       (0x0900U) /* The number of received data not read is 9. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_10      (0x0A00U) /* The number of received data not read is 10. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_11      (0x0B00U) /* The number of received data not read is 11. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_12      (0x0C00U) /* The number of received data not read is 12. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_13      (0x0D00U) /* The number of received data not read is 13. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_14      (0x0E00U) /* The number of received data not read is 14. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_15      (0x0F00U) /* The number of received data not read is 15. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_16      (0x1000U) /* The number of received data not read is 16. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_17      (0x1100U) /* The number of received data not read is 17. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_18      (0x1200U) /* The number of received data not read is 18. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_19      (0x1300U) /* The number of received data not read is 19. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_20      (0x1400U) /* The number of received data not read is 20. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_21      (0x1500U) /* The number of received data not read is 21. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_22      (0x1600U) /* The number of received data not read is 22. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_23      (0x1700U) /* The number of received data not read is 23. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_24      (0x1800U) /* The number of received data not read is 24. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_25      (0x1900U) /* The number of received data not read is 25. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_26      (0x1A00U) /* The number of received data not read is 26. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_27      (0x1B00U) /* The number of received data not read is 27. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_28      (0x1C00U) /* The number of received data not read is 28. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_29      (0x1D00U) /* The number of received data not read is 29. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_30      (0x1E00U) /* The number of received data not read is 30. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_31      (0x1F00U) /* The number of received data not read is 31. */
#define _MSPI_RECEIVED_DATA_NOT_READ_NUMBER_32      (0x2000U) /* The number of received data not read is 32. */
/* This bit indicates a transmission data write request in Direct memory mode or Fixed FIFO memory mode (MSPInTXRQFm)
 */
#define _MSPI_NO_REQUEST_TO_WRITE_TRANSMISSION      (0x0000U) /* There is no request to write transmission data. */
#define _MSPI_A_REQUEST_TO_WRITE_TRANSMISSION       (0x0020U) /* There is a request to write transmission data. */
/* This bit indicates a reception data read request in Direct memory mode or Fixed FIFO memory mode. (MSPInRXRQFm) */
#define _MSPI_NO_REQUEST_TO_WRITE_RECEPTION         (0x0000U) /* There is no request to write reception data. */
#define _MSPI_A_REQUEST_TO_WRITE_RECEPTION          (0x0010U) /* There is a request to write reception data. */
/* This bit indicates whether the channel is active or inactive (MSPInACTFm) */
#define _MSPI_CHANNELM_INACTIVE                     (0x0000U) /* Channel m is inactive. */
#define _MSPI_CHANNELM_ACTIVE                       (0x0002U) /* Channel m is active. */
/* This bit indicates whether the channel is disabled or enabled (MSPInCHENm) */
#define _MSPI_CHANNELM_DISABLE                      (0x0000U) /* Channel m is disabled. */
#define _MSPI_CHANNELM_ENABLE                       (0x0001U) /* Channel m is enabled. */

/*
    MSPIn Channel Status Set Register m (MSPInCSTSm)
*/
/* This bit sets the channel active flag (MSPInACTFSm) */
#define _MSPI_CHANNEL_SET_NO_ACTIVE_FLAG            (0x00U) /* No function. */
#define _MSPI_CHANNEL_SET_ACTIVE_FLAG               (0x02U) /* Sets MSPInCSTRm.MSPInACTFm to 1. */
/* This bit sets the channel enable flag (MSPInCHENSm) */
#define _MSPI_CHANNEL_SET_NO_ENABLE_FLAG            (0x00U) /* No function */
#define _MSPI_CHANNEL_SET_ENABLE_FLAG               (0x01U) /* Sets MSPInCSTRm.MSPInCHENm to 1. */

/*
    MSPIn Channel Status Clear Register m (MSPInCSTCm)
*/
/* This bit clears the channel enable flag (MSPInCHENCm) */
#define _MSPI_CHANNEL_NO_CLEAR_ENABLE_FLAG          (0x00U) /* No function. */
#define _MSPI_CHANNEL_CLEAR_ENABLE_FLAG             (0x01U) /* Clears MSPInCSTRm.MSPInCHENm to 0. */

/*
    MSPIn channel Configuration Register m0 (MSPInCFGm0)
*/
/* This bit enables transmission (MSPInTXEm) */
#define _MSPI_TRANSMISSION_DISABLE                  (0x00000000UL) /* Transmission disabled. */
#define _MSPI_TRANSMISSION_ENABLE                   (0x20000000UL) /* Transmission enabled. */
/* This bit enables reception (MSPInRXEm) */
#define _MSPI_RECEPTION_DISABLE                     (0x00000000UL) /* Reception disabled. */
#define _MSPI_RECEPTION_ENABLE                      (0x10000000UL) /* Reception enabled. */
/* This bits selects channel mode (MSPInMDm) */
#define _MSPI_DIRECT_MODE                           (0x00000000UL) /* Direct memory mode. */
#define _MSPI_FIXED_BUFFER_MEMORY_MODE              (0x01000000UL) /* Fixed buffer memory mode. */
#define _MSPI_FIXED_FIFO_MEMORY_MODE                (0x02000000UL) /* Fixed FIFO memory mode. */
/* This bits select channel priority (MSPInPRIOm) */
#define _MSPI_CHANNEL_PRIORITY_LEVEL1               (0x00000000UL) /* Channel priority level 1. */
#define _MSPI_CHANNEL_PRIORITY_LEVEL2               (0x00100000UL) /* Channel priority level 2. */
#define _MSPI_CHANNEL_PRIORITY_LEVEL3               (0x00200000UL) /* Channel priority level 3. */
#define _MSPI_CHANNEL_PRIORITY_LEVEL4               (0x00300000UL) /* Channel priority level 4. */
#define _MSPI_CHANNEL_PRIORITY_LEVEL5               (0x00400000UL) /* Channel priority level 5. */
#define _MSPI_CHANNEL_PRIORITY_LEVEL6               (0x00500000UL) /* Channel priority level 6. */
#define _MSPI_CHANNEL_PRIORITY_LEVEL7               (0x00600000UL) /* Channel priority level 7. */
#define _MSPI_CHANNEL_PRIORITY_LEVEL8               (0x00700000UL) /* Channel priority level 8. */
/* This bit enables channel lock operation (MSPInLOCKm) */
#define _MSPI_CHANNEL_LOCK_OPERATION_DISABLE        (0x00000000UL) /* Disable the channel m lock operation */
#define _MSPI_CHANNEL_LOCK_OPERATION_ENABLE         (0x00010000UL) /* Enable the channel m lock operation */
/* This bit selects the operation of channel frame count end in the direct memory mode (MSPInFCCEm) */
#define _MSPI_CHANNEL_OPERATION_END                 (0x00000000UL) /* The channel operation ends. */
#define _MSPI_CHANNEL_OPERATION_CONTINUE            (0x00001000UL) /* The channel operation continues. */
/* This bit enables or disables the output of INTMSPInERRm interrupt (MSPInIEREm) */
#define _MSPI_INTMSPIERR_INTERRUPT_DISABLE          (0x00000000UL) /* Disables the interrupt output. */
#define _MSPI_INTMSPIERR_INTERRUPT_ENABLE           (0x00000008UL) /* Enables the interrupt output. */
/* This bit enables or disables the output of INTMSPInFEm interrupt (MSPInIFEEm) */
#define _MSPI_INTMSPIFE_INTERRUPT_DISABLE           (0x00000000UL) /* Disables the interrupt output. */
#define _MSPI_INTMSPIFE_INTERRUPT_ENABLE            (0x00000004UL) /* Enables the interrupt output.. */
/* This bit enables or disables the output of INTMSPInRXm interrupt (MSPInIRXEm) */
#define _MSPI_INTMSPIRX_INTERRUPT_DISABLE           (0x00000000UL) /* Enables the interrupt output. */
#define _MSPI_INTMSPIRX_INTERRUPT_ENABLE            (0x00000002UL) /* Enables the interrupt output. */
/* This bit enables or disables the output of INTMSPInTXm interrupt (MSPInITXEm) */
#define _MSPI_INTMSPITX_INTERRUPT_DISABLE           (0x00000000UL) /* Disables the interrupt output. */
#define _MSPI_INTMSPITX_INTERRUPT_ENABLE            (0x00000001UL) /* Enables the interrupt output. */

/*
    MSPIn channel Configuration Register m1 (MSPInCFGm1)
*/
/* This bit selects MSPInSCK clock polarity (MSPInCPOLm) */
#define _MSPI_SPCK_IDLE_LOW                         (0x00000000UL) /* SCK is Low during idling time. */
#define _MSPI_SPCK_IDLE_HIGH                        (0x02000000UL) /* SCK is High during idling time. */
/* This bit selects the MSPInSCK phase (MSPInCPHAm) */
#define _MSPI_SCK_PHASE_SHIFT_EVEN_EDGES            (0x00000000UL) /* Sampling on odd-numbered edges. */
#define _MSPI_SCK_PHASE_SHIFT_ODD_EDGES             (0x01000000UL) /* sampling on even-numbered edges. */
/* This bit selects the communication direction (MSPInDIRm) */
#define _MSPI_COMMUNICATION_MSB                     (0x00000000UL) /* Data is MSB first. */
#define _MSPI_COMMUNICATION_LSB                     (0x00100000UL) /* Data is LSB first. */
/* This bit controls the MSPInCS level for idle time in the Direct memory mode (MSPInICLSm) */
#define _MSPI_CS_IDLE_LEVEL_INACTIVE                (0x00000000UL) /* MSPInCS level is inactive level. */
#define _MSPI_CS_IDLE_LEVEL_ACTIVE                  (0x00040000UL) /* MSPInCS level holds active level. */
/* This bit controls whether to insert an idle period after each end of a frame (MSPInFIDLm) */
#define _MSPI_IDLE_TIME_NOT_INSERTED                (0x00000000UL) /* The idle time is not inserted. */
#define _MSPI_IDLE_TIME_INSERTED                    (0x00020000UL) /* The idle time is forcibly inserted. */
/* This bit controls whether to insert an idle period after the last frame end (MSPInCSRIm) */
#define _MSPI_HOLD_ACTIVE_LEVEL                     (0x00000000UL) /* Holds MSPInCS at the active level. */
#define _MSPI_HOLD_INACTIVE_LEVEL                   (0x00010000UL) /* MSPInCS returns to the inactive level. */
/* This bit masks the CRC error of the first frame in Safe-SPI protocol function (MSPInSAFCMm) */
#define _MSPI_NOT_MASK_CRC_FIRST_ERROR              (0x00000000UL) /* Does not mask the CRC error. */
#define _MSPI_MASK_CRC_FIRST_ERROR                  (0x00000800UL) /* Masks the CRC error of the first frame. */
/* This bit selects the format of the Safe-SPI protocol function (MSPInSAFSm) */
#define _MSPI_IN_OF_FRAME_FORMAT                    (0x00000000UL) /* In-frame format. */
#define _MSPI_OUT_OF_FRAME_FORMAT                   (0x00000200UL) /* Out-of-frame format. */
/* This bit enables Safe-SPI protocol function. (MSPInSAFEm) */
#define _MSPI_SAFE_SPI_DISABLE                      (0x00000000UL) /* Disables Safe SPI protocol function. */
#define _MSPI_SAFE_SPI_ENABLE                       (0x00000100UL) /* Enables Safe SPI protocol function. */
/* This bit selects odd parity check or even parity check, when parity check function is enabled (MSPInPSm0) */
#define _MSPI_ADD_ODD_OR_EXPECTED_ODD               (0x00000000UL) /* Adds odd parity. */
#define _MSPI_ADD_EVEN_OR_EXPECTED_EVEN             (0x00000010UL) /* Adds even parity. */
#define _MSPI_ZERO_CHECK_OR_NOCHECK                 (0x00000020UL) /* Adds no check parity. */
/* This bit enables the parity check (MSPInDECHKm) */
#define _MSPI_NO_CHECK                              (0x00000000UL) /* No check. */
#define _MSPI_PARITY_CHECK                          (0x00000001UL) /* Parity check. */

/*
    MSPIn channel Configuration Register m3 (MSPInCFGm3)
*/
/* These bits select the stage size of FIFO Buffer in Fixed FIFO memory mode (MSPInSIZEm) */
#define _MSPI_CLOCK_FREQUENCY_DIVISION_1            (0x0000U) /* MSPInCLK */
#define _MSPI_CLOCK_FREQUENCY_DIVISION_4            (0x0100U) /* MSPInCLK/4 */
#define _MSPI_CLOCK_FREQUENCY_DIVISION_16           (0x0200U) /* MSPInCLK/16 */
#define _MSPI_CLOCK_FREQUENCY_DIVISION_64           (0x0300U) /* MSPInCLK/64 */

/*
    MSPIn channel Configuration Register m4 (MSPInCFGm4)
*/
/* These bits select the stage size of FIFO Buffer in Fixed FIFO memory mode (MSPInSIZEm) */
#define _MSPI_FIFO_SIZE_8                           (0x00000000UL) /* The stage size of Buffer is 8 */
#define _MSPI_FIFO_SIZE_16                          (0x00000001UL) /* The stage size of Buffer is 16 */
#define _MSPI_FIFO_SIZE_32                          (0x00000002UL) /* The stage size of Buffer is 32 */

/*
    MSPInCS signal Selection Register m (MSPInSSELm)
*/
/* This bit activates the Job function for the next transfer (MSPInJOBENm) */
#define _MSPI_JOB_END                               (0x0000U) /* Job ends with this frame. */
#define _MSPI_JOB_CONTINUOUS                        (0x8000U) /* Job continuous after this frame */
/* These bits set whether to activate or deactivate the MSPInCS (MSPInCSRm) */
#define _MSPI_DEACTIVATE_CS7                        (0x0000U) /* Deactivates MSPInCS7 */
#define _MSPI_ACTIVATE_CS7                          (0x0080U) /* Activates MSPInCS7 for the communication */
/* These bits set whether to activate or deactivate the MSPInCS (MSPInCSRm) */
#define _MSPI_DEACTIVATE_CS6                        (0x0000U) /* Deactivates MSPInCS6 */
#define _MSPI_ACTIVATE_CS6                          (0x0040U) /* Activates MSPInCS6 for the communication */
/* These bits set whether to activate or deactivate the MSPInCS (MSPInCSRm) */
#define _MSPI_DEACTIVATE_CS5                        (0x0000U) /* Deactivates MSPInCS5 */
#define _MSPI_ACTIVATE_CS5                          (0x0020U) /* Activates MSPInCS5 for the communication */
/* These bits set whether to activate or deactivate the MSPInCS (MSPInCSRm) */
#define _MSPI_DEACTIVATE_CS4                        (0x0000U) /* Deactivates MSPInCS4 */
#define _MSPI_ACTIVATE_CS4                          (0x0010U) /* Activates MSPInCS4 for the communication */
/* These bits set whether to activate or deactivate the MSPInCS (MSPInCSRm) */
#define _MSPI_DEACTIVATE_CS3                        (0x0000U) /* Deactivates MSPInCS3 */
#define _MSPI_ACTIVATE_CS3                          (0x0008U) /* Activates MSPInCS3 for the communication */
/* These bits set whether to activate or deactivate the MSPInCS (MSPInCSRm) */
#define _MSPI_DEACTIVATE_CS2                        (0x0000U) /* Deactivates MSPInCS2 */
#define _MSPI_ACTIVATE_CS2                          (0x0004U) /* Activates MSPInCS2 for the communication */
/* These bits set whether to activate or deactivate the MSPInCS (MSPInCSRm) */
#define _MSPI_DEACTIVATE_CS1                        (0x0000U) /* Deactivates MSPInCS1 */
#define _MSPI_ACTIVATE_CS1                          (0x0002U) /* Activates MSPInCS1 for the communication */
/* These bits set whether to activate or deactivate the MSPInCS (MSPInCSRm) */
#define _MSPI_DEACTIVATE_CS0                        (0x0000U) /* Deactivates MSPInCS0 */
#define _MSPI_ACTIVATE_CS0                          (0x0001U) /* Activates MSPInCS0 for the communication */

/*
    MSPIn Frame Error Status Register m (MSPInFRERSTm)
*/
/* This bit indicates whether a transmission data consistency error was detected in communication frame (MSPInDCEFSTm)
 */
#define _MSPI_CONSISTENCY_ERROR_NO_DETECTED         (0x00U) /* No consistency error is detected */
#define _MSPI_CONSISTENCY_ERROR_DETECTED            (0x10U) /* A consistency error is detected */
/* This bit indicates whether a reception data CRC error was detected in communication frame (MSPInCEFSTm) */
#define _MSPI_CRC_ERROR_NO_DETECTED                 (0x00U) /* No CRC error is detected */
#define _MSPI_CRC_ERROR_DETECTED                    (0x02U) /* A CRC error is detected */
/* This bit indicates whether a reception data parity error was detected in communication frame (MSPInPEFSTm) */
#define _MSPI_PARITY_ERROR_NO_DETECTED              (0x00U) /* No parity error is detected */
#define _MSPI_PARITY_ERROR_DETECTED                 (0x01U) /* A parity error is detected */

/*
    MSPIn Frame Error Status Clear Register m (MSPInFRERSTCm)
*/
/* This bit clears the status flag of data consistency error (MSPInDCEFSCm) */
#define _MSPI_CONSISTENCY_ERROR_NO_FUNCTION         (0x00U) /* Not clear consistency error */
#define _MSPI_CONSISTENCY_ERROR_CLEAR               (0x10U) /* Clear consistency error */
/* This bit clears the status flag of CRC error (MSPInCEFSCm) */
#define _MSPI_CRC_ERROR_NO_FUNCTION                 (0x00U) /* Not clear CRC error */
#define _MSPI_CRC_ERROR_CLEAR                       (0x02U) /* Clear CRC error */
/* This bit indicates whether a reception data parity error was detected in communication frame (MSPInPEFSCm) */
#define _MSPI_PARITY_ERROR_NO_FUNCTION              (0x00U) /* Not clear parity error */
#define _MSPI_PARITY_ERROR_CLEAR                    (0x01U) /* Clear parity error */

/*
    MSPIn Channel Error Status Register m (MSPInCESTm)
*/
/* This bit indicates whether an over-read error was detected in Fixed FIFO memory mode. (MSPInOVREEm) */
#define _MSPI_CHANNEL_OVER_READ_ERROR_NO_DETECTED   (0x00U) /* No over-read error is detected */
#define _MSPI_CHANNEL_OVER_READ_ERROR_DETECTED      (0x80U) /* A over-read error is detected */
/* This bit indicates whether an over-write error was detected in Fixed FIFO memory mode. (MSPInOVWREm) */
#define _MSPI_CHANNEL_OVER_WRITE_ERROR_NO_DETECTED  (0x00U) /* No over-write error is detected */
#define _MSPI_CHANNEL_OVER_WRITE_ERROR_DETECTED     (0x40U) /* A over-write error is detected */
/* This bit indicates whether an over-run error was detected in Direct memory mode 
   or Fixed FIFO memory mode (MSPInOVRUEm) */
#define _MSPI_CHANNEL_OVER_RUN_ERROR_NO_DETECTED    (0x00U) /* No parity error is detected */
#define _MSPI_CHANNEL_OVER_RUN_ERROR_DETECTED       (0x20U) /* A parity error is detected */
/* This bit indicates whether a transmission data consistency error was detected (MSPInDCEm) */
#define _MSPI_CHANNEL_CONSISTENCY_ERROR_NO_DETECTED (0x00U) /* No consistency error is detected */
#define _MSPI_CHANNEL_CONSISTENCY_ERROR_DETECTED    (0x10U) /* A consistency error is detected */
/* This bit indicates whether a reception data CRC error was detected in communication frame (MSPInCEm) */
#define _MSPI_CHANNEL_CRC_ERROR_NO_DETECTED         (0x00U) /* No CRC error is detected */
#define _MSPI_CHANNEL_CRC_ERROR_DETECTED            (0x02U) /* A CRC error is detected */
/* This bit indicates whether a reception data parity error was detected in communication frame (MSPInPEm) */
#define _MSPI_CHANNEL_PARITY_ERROR_NO_DETECTED      (0x00U) /* No parity error is detected */
#define _MSPI_CHANNEL_PARITY_ERROR_DETECTED         (0x01U) /* A parity error is detected */

/*
    MSPIn Channel Status Clear Register m (MSPInCESTCm)
*/
/* This bit clears the status flag of over-read error (MSPInOVREECm) */
#define _MSPI_CHANNEL_OVER_READ_ERROR_CLEAR         (0x80U) /* A over-read error is cleard */
/* This bit clears the status flag of over-write error (MSPInOVWRECm) */
#define _MSPI_CHANNEL_OVER_WRITE_ERROR_CLEAR        (0x40U) /* A over-write error is cleard */
/* This bit clears the status flag of overrun error (MSPInOVRUECm) */
#define _MSPI_CHANNEL_OVER_RUN_ERROR_CLEAR          (0x20U) /* A parity error is cleard */
/* This bit clears the status flag of data consistency error (MSPInDCECm) */
#define _MSPI_CHANNEL_CONSISTENCY_ERROR_CLEAR       (0x10U) /* A consistency error is cleard */
/* This bit clears the status flag of CRC error (MSPInCECm) */
#define _MSPI_CHANNEL_CRC_ERROR_CLEAR               (0x02U) /* A CRC error is cleard */
/* This bit clears the status flag of reception data parity error (MSPInPECm) */
#define _MSPI_CHANNEL_PARITY_ERROR_CLEAR            (0x01U) /* A parity error is cleard */

/*
    MSPIn Interrupt Mask Register (MSPInINTMSKk)
*/
/* MSPIn interrupts output to INTC2 mask (MSPInINTMSKk) */
#define _MSPI_CHANNEL0_INTERRUPT_NOT_MASKED         (0xFFFFFFFEUL) /* Not masked */
#define _MSPI_CHANNEL1_INTERRUPT_NOT_MASKED         (0xFFFFFFFDUL) /* Not masked */
#define _MSPI_CHANNEL2_INTERRUPT_NOT_MASKED         (0xFFFFFFFBUL) /* Not masked */
#define _MSPI_CHANNEL3_INTERRUPT_NOT_MASKED         (0xFFFFFFF7UL) /* Not masked */
#define _MSPI_CHANNEL4_INTERRUPT_NOT_MASKED         (0xFFFFFFEFUL) /* Not masked */
#define _MSPI_CHANNEL5_INTERRUPT_NOT_MASKED         (0xFFFFFFDFUL) /* Not masked */
#define _MSPI_CHANNEL6_INTERRUPT_NOT_MASKED         (0xFFFFFFBFUL) /* Not masked */
#define _MSPI_CHANNEL7_INTERRUPT_NOT_MASKED         (0xFFFFFF7FUL) /* Not masked */
#define _MSPI_ALL_CHANNELS_INTERRUPT_MASKED         (0x000000FFUL) /* All masked */

/*
    MSPIn Interrupt Factor Register k (MSPInINTFk)
*/
/* MSPIn interrupts occurrence (MSPInINTFk) */
#define _MSPI_CHANNEL0_INTERRUPT_OCCURRED           (0x00000001UL) /* Channel0 interrupt has occurred */
#define _MSPI_CHANNEL1_INTERRUPT_OCCURRED           (0x00000002UL) /* Channel1 interrupt has occurred */
#define _MSPI_CHANNEL2_INTERRUPT_OCCURRED           (0x00000004UL) /* Channel2 interrupt has occurred */
#define _MSPI_CHANNEL3_INTERRUPT_OCCURRED           (0x00000008UL) /* Channel3 interrupt has occurred */
#define _MSPI_CHANNEL4_INTERRUPT_OCCURRED           (0x00000010UL) /* Channel4 interrupt has occurred */
#define _MSPI_CHANNEL5_INTERRUPT_OCCURRED           (0x00000020UL) /* Channel5 interrupt has occurred */
#define _MSPI_CHANNEL6_INTERRUPT_OCCURRED           (0x00000040UL) /* Channel6 interrupt has occurred */
#define _MSPI_CHANNEL7_INTERRUPT_OCCURRED           (0x00000080UL) /* Channel7 interrupt has occurred */

/*
    MSPIn Interrupt Factor Clear Register k (MSPInINTFCk)
*/
/* MSPIn interrupts flag clear (MSPInINTFCk) */
#define _MSPI_CHANNEL0_INTERRUPT_FLAG_CLEAR         (0x00000001UL) /* Channel0 clear interrupt flag */
#define _MSPI_CHANNEL1_INTERRUPT_FLAG_CLEAR         (0x00000002UL) /* Channel1 clear interrupt flag */
#define _MSPI_CHANNEL2_INTERRUPT_FLAG_CLEAR         (0x00000004UL) /* Channel2 clear interrupt flag */
#define _MSPI_CHANNEL3_INTERRUPT_FLAG_CLEAR         (0x00000008UL) /* Channel3 clear interrupt flag */
#define _MSPI_CHANNEL4_INTERRUPT_FLAG_CLEAR         (0x00000010UL) /* Channel4 clear interrupt flag */
#define _MSPI_CHANNEL5_INTERRUPT_FLAG_CLEAR         (0x00000020UL) /* Channel5 clear interrupt flag */
#define _MSPI_CHANNEL6_INTERRUPT_FLAG_CLEAR         (0x00000040UL) /* Channel6 clear interrupt flag */
#define _MSPI_CHANNEL7_INTERRUPT_FLAG_CLEAR         (0x00000080UL) /* Channel7 clear interrupt flag */

/*
    MSPI Trigger Control Register for MSPIn (MSPITGCTLn)
*/
/* Trigger Source Select For Channel 7 (SRCSEL7) */
#define _MSPI_CHANNEL7_TRIGGER_SET_CLEAR            (0x0FFFFFFFUL) /* Clear MSPIn7 trigger set */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_NONE           (0x00000000UL) /* No trigger is selected */
#define _MSPI_TRIGGER1_TX7_TRIGGER2_NONE            (0x20000000UL) /* Trigger1 selects TXn */
#define _MSPI_TRIGGER1_RX7_TRIGGER2_NONE            (0x40000000UL) /* Trigger1 selects RXn */
#define _MSPI_TRIGGER1_FE7_TRIGGER2_NONE            (0x60000000UL) /* Trigger1 selects FEn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_TX7            (0x80000000UL) /* Trigger2 selects TXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_RX7            (0xA0000000UL) /* Trigger2 selects RXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_FE7            (0xC0000000UL) /* Trigger2 selects FEn */
#define _MSPI_TRIGGER1_TX7_TRIGGER2_RX7             (0xE0000000UL) /* Trigger1 selects TXn, Trigger2 selects FEn */
/* Trigger Select for Channel 7 (TRGSEL7) */
#define _MSPI_CHANNEL7_DMA_TRIGGER_ENABLE           (0x00000000UL) /* MSPI channel DMA trigger enable */
#define _MSPI_CHANNEL7_DTS_TRIGGER_ENABLE           (0x10000000UL) /* MSPI channel DTS trigger enable */
/* Trigger Source Select For Channel 6 (SRCSEL6) */
#define _MSPI_CHANNEL6_TRIGGER_SET_CLEAR            (0xF0FFFFFFUL) /* Clear MSPIn6 trigger set */
#define _MSPI_TRIGGER1_TX6_TRIGGER2_NONE            (0x02000000UL) /* Trigger1 selects TXn */
#define _MSPI_TRIGGER1_RX6_TRIGGER2_NONE            (0x04000000UL) /* Trigger1 selects RXn */
#define _MSPI_TRIGGER1_FE6_TRIGGER2_NONE            (0x06000000UL) /* Trigger1 selects FEn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_TX6            (0x08000000UL) /* Trigger2 selects TXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_RX6            (0x0A000000UL) /* Trigger2 selects RXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_FE6            (0x0C000000UL) /* Trigger2 selects FEn */
#define _MSPI_TRIGGER1_TX6_TRIGGER2_RX6             (0x0E000000UL) /* Trigger1 selects TXn, Trigger2 selects FEn */
/* Trigger Select for Channel 6 (TRGSEL6) */
#define _MSPI_CHANNEL6_DMA_TRIGGER_ENABLE           (0x00000000UL) /* MSPI channel DMA trigger enable */
#define _MSPI_CHANNEL6_DTS_TRIGGER_ENABLE           (0x01000000UL) /* MSPI channel DTS trigger enable */
/* Trigger Source Select For Channel 5 (SRCSEL5) */
#define _MSPI_CHANNEL5_TRIGGER_SET_CLEAR            (0xFF0FFFFFUL) /* Clear MSPIn5 trigger set */
#define _MSPI_TRIGGER1_TX5_TRIGGER2_NONE            (0x00200000UL) /* Trigger1 selects TXn */
#define _MSPI_TRIGGER1_RX5_TRIGGER2_NONE            (0x00400000UL) /* Trigger1 selects RXn */
#define _MSPI_TRIGGER1_FE5_TRIGGER2_NONE            (0x00600000UL) /* Trigger1 selects FEn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_TX5            (0x00800000UL) /* Trigger2 selects TXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_RX5            (0x00A00000UL) /* Trigger2 selects RXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_FE5            (0x00C00000UL) /* Trigger2 selects FEn */
#define _MSPI_TRIGGER1_TX5_TRIGGER2_RX5             (0x00E00000UL) /* Trigger1 selects TXn, Trigger2 selects FEn */
/* Trigger Select for Channel 5 (TRGSEL5) */
#define _MSPI_CHANNEL5_DMA_TRIGGER_ENABLE           (0x00000000UL) /* MSPI channel DMA trigger enable */
#define _MSPI_CHANNEL5_DTS_TRIGGER_ENABLE           (0x00100000UL) /* MSPI channel DTS trigger enable */
/* Trigger Source Select For Channel 4 (SRCSEL4) */
#define _MSPI_CHANNEL4_TRIGGER_SET_CLEAR            (0xFFF0FFFFUL) /* Clear MSPIn4 trigger set */
#define _MSPI_TRIGGER1_TX4_TRIGGER2_NONE            (0x00020000UL) /* Trigger1 selects TXn */
#define _MSPI_TRIGGER1_RX4_TRIGGER2_NONE            (0x00040000UL) /* Trigger1 selects RXn */
#define _MSPI_TRIGGER1_FE4_TRIGGER2_NONE            (0x00060000UL) /* Trigger1 selects FEn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_TX4            (0x00080000UL) /* Trigger2 selects TXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_RX4            (0x000A0000UL) /* Trigger2 selects RXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_FE4            (0x000C0000UL) /* Trigger2 selects FEn */
#define _MSPI_TRIGGER1_TX4_TRIGGER2_RX4             (0x000E0000UL) /* Trigger1 selects TXn, Trigger2 selects FEn */
/* Trigger Select for Channel 4 (TRGSEL4) */
#define _MSPI_CHANNEL4_DMA_TRIGGER_ENABLE           (0x00000000UL) /* MSPI channel DMA trigger enable */
#define _MSPI_CHANNEL4_DTS_TRIGGER_ENABLE           (0x00010000UL) /* MSPI channel DTS trigger enable */
/* Trigger Source Select For Channel 3 (SRCSEL3) */
#define _MSPI_CHANNEL3_TRIGGER_SET_CLEAR            (0xFFFF0FFFUL) /* Clear MSPIn3 trigger set */
#define _MSPI_TRIGGER1_TX3_TRIGGER2_NONE            (0x00002000UL) /* Trigger1 selects TXn */
#define _MSPI_TRIGGER1_RX3_TRIGGER2_NONE            (0x00004000UL) /* Trigger1 selects RXn */
#define _MSPI_TRIGGER1_FE3_TRIGGER2_NONE            (0x00006000UL) /* Trigger1 selects FEn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_TX3            (0x00008000UL) /* Trigger2 selects TXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_RX3            (0x0000A000UL) /* Trigger2 selects RXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_FE3            (0x0000C000UL) /* Trigger2 selects FEn */
#define _MSPI_TRIGGER1_TX3_TRIGGER2_RX3             (0x0000E000UL) /* Trigger1 selects TXn, Trigger2 selects FEn */
/* Trigger Select for Channel 3 (TRGSEL3) */
#define _MSPI_CHANNEL3_DMA_TRIGGER_ENABLE           (0x00000000UL) /* MSPI channel DMA trigger enable */
#define _MSPI_CHANNEL3_DTS_TRIGGER_ENABLE           (0x00001000UL) /* MSPI channel DTS trigger enable */
/* Trigger Source Select For Channel 2 (SRCSEL2) */
#define _MSPI_CHANNEL2_TRIGGER_SET_CLEAR            (0xFFFFF0FFUL) /* Clear MSPIn2 trigger set */
#define _MSPI_TRIGGER1_TX2_TRIGGER2_NONE            (0x00000200UL) /* Trigger1 selects TXn */
#define _MSPI_TRIGGER1_RX2_TRIGGER2_NONE            (0x00000400UL) /* Trigger1 selects RXn */
#define _MSPI_TRIGGER1_FE2_TRIGGER2_NONE            (0x00000600UL) /* Trigger1 selects FEn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_TX2            (0x00000800UL) /* Trigger2 selects TXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_RX2            (0x00000A00UL) /* Trigger2 selects RXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_FE2            (0x00000C00UL) /* Trigger2 selects FEn */
#define _MSPI_TRIGGER1_TX2_TRIGGER2_RX2             (0x00000E00UL) /* Trigger1 selects TXn, Trigger2 selects FEn */
/* Trigger Select for Channel 2 (TRGSEL2) */
#define _MSPI_CHANNEL2_DMA_TRIGGER_ENABLE           (0x00000000UL) /* MSPI channel DMA trigger enable */
#define _MSPI_CHANNEL2_DTS_TRIGGER_ENABLE           (0x00000100UL) /* MSPI channel DTS trigger enable */
/* Trigger Source Select For Channel 1 (SRCSEL1) */
#define _MSPI_CHANNEL1_TRIGGER_SET_CLEAR            (0xFFFFFF0FUL) /* Clear MSPIn1 trigger set */
#define _MSPI_TRIGGER1_TX1_TRIGGER2_NONE            (0x00000020UL) /* Trigger1 selects TXn */
#define _MSPI_TRIGGER1_RX1_TRIGGER2_NONE            (0x00000040UL) /* Trigger1 selects RXn */
#define _MSPI_TRIGGER1_FE1_TRIGGER2_NONE            (0x00000060UL) /* Trigger1 selects FEn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_TX1            (0x00000080UL) /* Trigger2 selects TXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_RX1            (0x000000A0UL) /* Trigger2 selects RXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_FE1            (0x000000C0UL) /* Trigger2 selects FEn */
#define _MSPI_TRIGGER1_TX1_TRIGGER2_RX1             (0x000000E0UL) /* Trigger1 selects TXn, Trigger2 selects FEn */
/* Trigger Select for Channel 1 (TRGSEL1) */
#define _MSPI_CHANNEL1_DMA_TRIGGER_ENABLE           (0x00000000UL) /* MSPI channel DMA trigger enable */
#define _MSPI_CHANNEL1_DTS_TRIGGER_ENABLE           (0x00000010UL) /* MSPI channel DTS trigger enable */
/* Trigger Source Select For Channel 0 (SRCSEL0) */
#define _MSPI_CHANNEL0_TRIGGER_SET_CLEAR            (0xFFFFFFF0UL) /* Clear MSPIn0 trigger set */
#define _MSPI_TRIGGER1_TX0_TRIGGER2_NONE            (0x00000002UL) /* Trigger1 selects TXn */
#define _MSPI_TRIGGER1_RX0_TRIGGER2_NONE            (0x00000004UL) /* Trigger1 selects RXn */
#define _MSPI_TRIGGER1_FE0_TRIGGER2_NONE            (0x00000006UL) /* Trigger1 selects FEn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_TX0            (0x00000008UL) /* Trigger2 selects TXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_RX0            (0x0000000AUL) /* Trigger2 selects RXn */
#define _MSPI_TRIGGER1_NONE_TRIGGER2_FE0            (0x0000000CUL) /* Trigger2 selects FEn */
#define _MSPI_TRIGGER1_TX0_TRIGGER2_RX0             (0x0000000EUL) /* Trigger1 selects TXn, Trigger2 selects FEn */
/* Trigger Select for Channel 0 (TRGSEL0) */
#define _MSPI_CHANNEL0_DMA_TRIGGER_ENABLE           (0x00000000UL) /* MSPI channel DMA trigger enable */
#define _MSPI_CHANNEL0_DTS_TRIGGER_ENABLE           (0x00000001UL) /* MSPI channel DTS trigger enable */

/*
    MSPI DMA Trigger Alternative Select Register (MSPITGDMAALT)
*/
/* DMA Trigger Alternative Select for MSPI1-Ch7 (DMAAS17) */
#define _MSPI_CH17_DMA_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFF7FUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH17_DMA_ALTERNATIVE_TRIGGER_ENABLE   (0x00000080UL) /* Use Alternative Trigger Signals */
/* DMA Trigger Alternative Select for MSPI1-Ch6 (DMAAS16) */
#define _MSPI_CH16_DMA_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFFBFUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH16_DMA_ALTERNATIVE_TRIGGER_ENABLE   (0x00000040UL) /* Use Alternative Trigger Signals */
/* DMA Trigger Alternative Select for MSPI1-Ch3 (DMAAS13) */
#define _MSPI_CH13_DMA_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFFDFUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH13_DMA_ALTERNATIVE_TRIGGER_ENABLE   (0x00000020UL) /* Use Alternative Trigger Signals */
/* DMA Trigger Alternative Select for MSPI1-Ch2 (DMAAS12) */
#define _MSPI_CH12_DMA_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFFEFUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH12_DMA_ALTERNATIVE_TRIGGER_ENABLE   (0x00000010UL) /* Use Alternative Trigger Signals */
/* DMA Trigger Alternative Select for MSPI0-Ch7 (DMAAS07) */
#define _MSPI_CH07_DMA_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFFF7UL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH07_DMA_ALTERNATIVE_TRIGGER_ENABLE   (0x00000008UL) /* Use Alternative Trigger Signals */
/* DMA Trigger Alternative Select for MSPI0-Ch6 (DMAAS06) */
#define _MSPI_CH06_DMA_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFFFBUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH06_DMA_ALTERNATIVE_TRIGGER_ENABLE   (0x00000004UL) /* Use Alternative Trigger Signals */
/* DMA Trigger Alternative Select for MSPI0-Ch3 (DMAAS03) */
#define _MSPI_CH03_DMA_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFFFDUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH03_DMA_ALTERNATIVE_TRIGGER_ENABLE   (0x00000002UL) /* Use Alternative Trigger Signals */
/* DMA Trigger Alternative Select for MSPI0-Ch2 (DMAAS02) */
#define _MSPI_CH02_DMA_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFFFEUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH02_DMA_ALTERNATIVE_TRIGGER_ENABLE   (0x00000001UL) /* Use Alternative Trigger Signals */

/*
    MSPI DTS Trigger Alternative Select Register (MSPITGDTSALT)
*/
/* DTS Trigger Alternative Select for MSPI3-Ch7 (DTSAS37) */
#define _MSPI_CH37_DTS_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFDFFFUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH37_DTS_ALTERNATIVE_TRIGGER_ENABLE   (0x00002000UL) /* Use Alternative Trigger Signals */
/* DTS Trigger Alternative Select for MSPI3-Ch6 (DTSAS36) */
#define _MSPI_CH36_DTS_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFEFFFUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH36_DTS_ALTERNATIVE_TRIGGER_ENABLE   (0x00001000UL) /* Use Alternative Trigger Signals */
/* DTS Trigger Alternative Select for MSPI3-Ch5 (DTSAS35) */
#define _MSPI_CH35_DTS_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFF7FFUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH35_DTS_ALTERNATIVE_TRIGGER_ENABLE   (0x00000800UL) /* Use Alternative Trigger Signals */
/* DTS Trigger Alternative Select for MSPI3-Ch4 (DTSAS34) */
#define _MSPI_CH34_DTS_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFBFFUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH34_DTS_ALTERNATIVE_TRIGGER_ENABLE   (0x00000400UL) /* Use Alternative Trigger Signals */
/* DTS Trigger Alternative Select for MSPI2-Ch7 (DTSAS27) */
#define _MSPI_CH27_DTS_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFDFFUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH27_DTS_ALTERNATIVE_TRIGGER_ENABLE   (0x00000200UL) /* Use Alternative Trigger Signals */
/* DTS Trigger Alternative Select for MSPI2-Ch6 (DTSAS26) */
#define _MSPI_CH26_DTS_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFEFFUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH26_DTS_ALTERNATIVE_TRIGGER_ENABLE   (0x00000100UL) /* Use Alternative Trigger Signals */
/* DTS Trigger Alternative Select for MSPI2-Ch5 (DTSAS25) */
#define _MSPI_CH25_DTS_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFF7FUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH25_DTS_ALTERNATIVE_TRIGGER_ENABLE   (0x00000080UL) /* Use Alternative Trigger Signals */
/* DTS Trigger Alternative Select for MSPI2-Ch4 (DTSAS24) */
#define _MSPI_CH24_DTS_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFFBFUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH24_DTS_ALTERNATIVE_TRIGGER_ENABLE   (0x00000040UL) /* Use Alternative Trigger Signals */
/* DTS Trigger Alternative Select for MSPI1-Ch7 (DTSAS17) */
#define _MSPI_CH17_DTS_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFFDFUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH17_DTS_ALTERNATIVE_TRIGGER_ENABLE   (0x00000020UL) /* Use Alternative Trigger Signals */
/* DTS Trigger Alternative Select for MSPI1-Ch6 (DTSAS16) */
#define _MSPI_CH16_DTS_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFFEFUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH16_DTS_ALTERNATIVE_TRIGGER_ENABLE   (0x00000010UL) /* Use Alternative Trigger Signals */
/* DTS Trigger Alternative Select for MSPI1-Ch5 (DTSAS15) */
#define _MSPI_CH15_DTS_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFFF7UL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH15_DTS_ALTERNATIVE_TRIGGER_ENABLE   (0x00000008UL) /* Use Alternative Trigger Signals */
/* DTS Trigger Alternative Select for MSPI1-Ch4 (DTSAS14) */
#define _MSPI_CH14_DTS_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFFFBUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH14_DTS_ALTERNATIVE_TRIGGER_ENABLE   (0x00000004UL) /* Use Alternative Trigger Signals */
/* DTS Trigger Alternative Select for MSPI0-Ch7 (DTSAS07) */
#define _MSPI_CH07_DTS_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFFFDUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH07_DTS_ALTERNATIVE_TRIGGER_ENABLE   (0x00000002UL) /* Use Alternative Trigger Signals */
/* DTS Trigger Alternative Select for MSPI0-Ch6 (DTSAS06) */
#define _MSPI_CH06_DTS_ALTERNATIVE_TRIGGER_DISABLE  (0xFFFFFFFEUL) /* Not use Alternative Trigger Signals */
#define _MSPI_CH06_DTS_ALTERNATIVE_TRIGGER_ENABLE   (0x00000001UL) /* Use Alternative Trigger Signals */

#define _MSPI0_RAMBASE_ADDRESS                      (0xFFC77000UL) /* MSPI0 transmission/reception RAM memory base
                                                                                                          address */
#define _MSPI1_RAMBASE_ADDRESS                      (0xFFC7F000UL) /* MSPI1 transmission/reception RAM memory base
                                                                                                          address */
#define _MSPI2_RAMBASE_ADDRESS                      (0xFFD81000UL) /* MSPI2 transmission/reception RAM memory base
                                                                                                          address */
#define _MSPI3_RAMBASE_ADDRESS                      (0xFFCC1000UL) /* MSPI3 transmission/reception RAM memory base
                                                                                                          address */
#define _MSPI4_RAMBASE_ADDRESS                      (0xFFD83000UL) /* MSPI4 transmission/reception RAM memory base
                                                                                                          address */
#define _MSPI5_RAMBASE_ADDRESS                      (0xFFCC5000UL) /* MSPI5 transmission/reception RAM memory base
                                                                                                          address */
#define _MSPI6_RAMBASE_ADDRESS                      (0xFFD85000UL) /* MSPI6 transmission/reception RAM memory base
                                                                                                          address */
#define _MSPI7_RAMBASE_ADDRESS                      (0xFFCC9000UL) /* MSPI7 transmission/reception RAM memory base
                                                                                                          address */
#define _MSPI8_RAMBASE_ADDRESS                      (0xFFD87000UL) /* MSPI8 transmission/reception RAM memory base
                                                                                                          address */
#define _MSPI9_RAMBASE_ADDRESS                      (0xFFCCD000UL) /* MSPI9 transmission/reception RAM memory base
                                                                                                          address */

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
