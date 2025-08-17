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
* File Name        : MSPI30.c
* Component Version: 1.4.0
* Device(s)        : R7F702300BFABA
* Description      : This file implements device driver for MSPI30.
***********************************************************************************************************************/
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "MSPI30.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
volatile uint32_t  g_mspi30_tx_num;                         /* mspi30 transmit data number */
volatile uint32_t  g_mspi30_rx_num;                         /* mspi30 receive data number */
volatile uint32_t  g_mspi30_rx_total_num;                   /* mspi30 receive data total times */
volatile uint16_t * gp_mspi30_tx_address;                   /* mspi30 transmit buffer address */
volatile uint16_t * gp_mspi30_rx_address;                   /* mspi30 receive buffer address */
/* Start user code for global. Do not edit comment generated here */
volatile uint8_t g_mspi30_busy;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_MSPI30_Create
* Description  : This function initializes the MSPI30 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI30_Create(void)
{
    /* Set MSPI3 control setting */
    MSPI3.CTL1.UINT32 = _MSPI_SAMPLE_STANDARD | _MSPI_CLOCK_DEFAULT_LOW | _MSPI_MSPISOUT_ENABLE_LOW_IDLE_LOW | 
                        _MSPI_CS7_SIGNAL_ACTIVE_LOW | _MSPI_CS6_SIGNAL_ACTIVE_LOW | _MSPI_CS5_SIGNAL_ACTIVE_LOW | 
                        _MSPI_CS4_SIGNAL_ACTIVE_LOW | _MSPI_CS3_SIGNAL_ACTIVE_LOW | _MSPI_CS2_SIGNAL_ACTIVE_LOW | 
                        _MSPI_CS1_SIGNAL_ACTIVE_LOW | _MSPI_CS0_SIGNAL_ACTIVE_LOW | _MSPI_MASTER_MODE | 
                        _MSPI_CS_SIGNAL_IGNORED | _MSPI_SAMPLE_STANDARD;
    MSPI3.CTL2.UINT8 = _MSPI_CONSISTENCY_DISABLE | _MSPI_LOOPBACK_DISABLE;
    /* Enable MSPI3 operation */
    MSPI3.CTL0.UINT8 = _MSPI_FUNCTION_ENABLE;
    /* Set MSPI3 configuration setting */
    MSPI3.CFG00.UINT32 = _MSPI_TRANSMISSION_ENABLE | _MSPI_RECEPTION_ENABLE | _MSPI_DIRECT_MODE | 
                         _MSPI_CHANNEL_PRIORITY_LEVEL8 | _MSPI_CHANNEL_LOCK_OPERATION_DISABLE | 
                         _MSPI_CHANNEL_OPERATION_END | _MSPI_INTMSPITX_INTERRUPT_ENABLE | 
                         _MSPI_INTMSPIRX_INTERRUPT_ENABLE | _MSPI_INTMSPIFE_INTERRUPT_ENABLE | 
                         _MSPI_INTMSPIERR_INTERRUPT_ENABLE;
    MSPI3.CFG01.UINT32 = _MSPI_SPCK_IDLE_LOW | _MSPI_SCK_PHASE_SHIFT_ODD_EDGES | _MSPI_COMMUNICATION_MSB | 
                         _MSPI_HOLD_ACTIVE_LEVEL | _MSPI_IDLE_TIME_NOT_INSERTED | _MSPI_CS_IDLE_LEVEL_INACTIVE | 
                         _MSPI_NO_CHECK | _MSPI_SAFE_SPI_DISABLE;
    MSPI3.CFG02.UINT16 = _MSPI30_FRAME_LENGTH;
    MSPI3.CFG03.UINT16 = _MSPI_CLOCK_FREQUENCY_DIVISION_4 | _MSPI30_CLOCK_FREQUENCY_DIVISION;
    MSPI3.CFG04.UINT32 = _MSPI_FIFO_SIZE_8 | _MSPI30_HARDWARE_TRIGGER_DISABLE;
    MSPI3.RASTAD0.UINT16 = _MSPI30_RAMSTART_ADDRESS;
    MSPI3.SEUP0.UINT16 = _MSPI30_SETUP_TIME;
    MSPI3.HOLD0.UINT16 = _MSPI30_HOLD_TIME;
    MSPI3.IDLE0.UINT16 = _MSPI30_IDLE_TIME;
    MSPI3.INDA0.UINT16 = _MSPI30_INTER_DATA_TIME;
    MSPI3.CFSET0.UINT16 = _MSPI30_FRAME_COUNT;
    MSPI3.SSEL0.UINT16 = _MSPI_DEACTIVATE_CS0 | _MSPI_DEACTIVATE_CS1 | _MSPI_DEACTIVATE_CS2 | _MSPI_DEACTIVATE_CS3 | 
                         _MSPI_DEACTIVATE_CS4 | _MSPI_DEACTIVATE_CS5 | _MSPI_DEACTIVATE_CS6 | _MSPI_DEACTIVATE_CS7;
    MSPITG.CTL3.UINT32 &= _MSPI_CHANNEL0_TRIGGER_SET_CLEAR;
    MSPITG.CTL3.UINT32 |= _MSPI_TRIGGER1_NONE_TRIGGER2_NONE;
    MSPITG.CTL3.UINT32 |= _MSPI_CHANNEL0_DMA_TRIGGER_ENABLE;
    MSPI3_INTF.MSPI3INTMSK0.UINT32 &= _MSPI_CHANNEL0_INTERRUPT_NOT_MASKED;
    MSPI3_INTF.MSPI3INTMSK1.UINT32 &= _MSPI_CHANNEL0_INTERRUPT_NOT_MASKED;
    MSPI3_INTF.MSPI3INTMSK3.UINT32 &= _MSPI_CHANNEL0_INTERRUPT_NOT_MASKED;
    MSPI3_INTF.MSPI3INTMSK2.UINT32 &= _MSPI_CHANNEL0_INTERRUPT_NOT_MASKED;
    /* Synchronization processing */
    g_cg_sync_read = MSPI3.CTL1.UINT32;
    __syncp();

    /* Set MSPI3SC pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(18U);
    PORT0.PCR22_4.UINT32 = (PORT0.PCR22_4.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR22_4.UINT32 &= _PCR_CLEAR_PDSC;
    PORT0.PCR22_4.UINT32 &= _PCR_CLEAR_PUCC;
    PORT0.PCR22_4.UINT32 |= _PCR_ALT_OUT4;
    PORT0.PCR22_4.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR22_4.UINT32 &= _PCR_CLEAR_PM;
    PORT0.PCR22_4.UINT32 &= _PCR_ALT_OUT_SETTING;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set MSPI3SO pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(18U);
    PORT0.PCR22_0.UINT32 = (PORT0.PCR22_0.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR22_0.UINT32 &= _PCR_CLEAR_PDSC;
    PORT0.PCR22_0.UINT32 &= _PCR_CLEAR_PUCC;
    PORT0.PCR22_0.UINT32 |= _PCR_DIRECT_ALT_MODE4;
    PORT0.PCR22_0.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR22_0.UINT32 &= _PCR_DIRECT_ALT_MODE_SETTING;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set MSPI3SI pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(18U);
    PORT0.PCR22_1.UINT32 = (PORT0.PCR22_1.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR22_1.UINT32 |= _PCR_ALT_IN4;
    PORT0.PCR22_1.UINT32 |= _PCR_SET_PMC;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    R_MSPI30_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_MSPI30_Start
* Description  : This function starts the MSPI30 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI30_Start(void)
{
    /* Enable MSPI3 channel 0 operation */
    MSPI3.CSTS0.UINT8 = _MSPI_CHANNEL_SET_ENABLE_FLAG;
}

/***********************************************************************************************************************
* Function Name: R_MSPI30_Stop
* Description  : This function stops the MSPI3 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI30_Stop(void)
{
    /* Disable MSPI3 channel 0 operation */
    MSPI3.CSTC0.UINT8 = _MSPI_CHANNEL_CLEAR_ENABLE_FLAG;
    /* Synchronization processing */
    g_cg_sync_read = MSPI3.CTL0.UINT8;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_MSPI30_Send
* Description  : This function sends MSPI3 data.
* Arguments    : tx_buf -
*                    send buffer pointer
* Return Value : MD_STATUS -
*                    the status of sending
***********************************************************************************************************************/
MD_STATUS R_MSPI30_Send(uint16_t* const tx_buf)
{
    /* Set transmit setting */
    gp_mspi30_tx_address = (uint16_t *)tx_buf;
    g_mspi30_tx_num = _MSPI30_FRAME_COUNT;

    return MD_OK;
}

/***********************************************************************************************************************
* Function Name: R_MSPI30_Receive
* Description  : This function receives MSPI3 data.
* Arguments    : rx_buf -
*                    receive buffer pointer
* Return Value : MD_STATUS -
*                    the status of receiving
***********************************************************************************************************************/
MD_STATUS R_MSPI30_Receive(uint16_t* rx_buf)
{
    /* Set receive setting */
    gp_mspi30_rx_address = rx_buf;
    g_mspi30_rx_total_num = _MSPI30_FRAME_COUNT;
    g_mspi30_rx_num = 0U;

    return MD_OK;
}

/***********************************************************************************************************************
* Function Name: R_MSPI30_Software_Trigger
* Description  : This function sets software trigger.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MSPI30_Software_Trigger()
{
    MSPI3.CSTS0.UINT8 = _MSPI_CHANNEL_SET_ACTIVE_FLAG | _MSPI_CHANNEL_SET_ENABLE_FLAG;
}

/* Start user code for adding. Do not edit comment generated here */
void R_MSPI30_busy_wait(void)
{
    while(g_mspi30_busy==1);
}
void R_MSPI30_set_busy(void)
{
    g_mspi30_busy=1;
}
/* End user code. Do not edit comment generated here */
