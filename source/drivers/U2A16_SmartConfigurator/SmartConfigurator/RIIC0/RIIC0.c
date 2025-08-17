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
* File Name        : RIIC0.c
* Component Version: 1.5.0
* Device(s)        : R7F702300BFABA
* Description      : This file implements device driver for RIIC0.
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
#include "RIIC0.h"
/* Start user code for include. Do not edit comment generated here */
#include <stdbool.h>
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t          g_riic0_mode_flag;               /* RIIC0 master transmit receive flag */
volatile uint8_t          g_riic0_state;                   /* RIIC0 state */
volatile uint16_t         g_riic0_slave_address;           /* RIIC0 slave address */
volatile uint8_t *        gp_riic0_tx_address;             /* RIIC0 transmit buffer address */
volatile uint16_t         g_riic0_tx_count;                /* RIIC0 transmit data number */
volatile uint8_t *        gp_riic0_rx_address;             /* RIIC0 receive buffer address */
volatile uint16_t         g_riic0_rx_count;                /* RIIC0 receive data number */
volatile uint16_t         g_riic0_rx_length;               /* RIIC0 receive data length */
volatile uint8_t          g_riic0_dummy_read_count;        /* RIIC0 count for dummy read */
volatile uint8_t          g_riic0_stop_generation;         /* RIIC0 stop condition generation flag */
extern volatile uint32_t  g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
volatile uint8_t          g_riic0_busy; 
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_RIIC0_Create
* Description  : This function initializes the IIC Bus Interface.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RIIC0_Create(void)
{
    /* Reset RIIC0 */
    RIIC0.CR1.UINT32 &= _RIIC_DISABLE;
    RIIC0.CR1.UINT32 |= _RIIC_RESET;
    RIIC0.CR1.UINT32 |= _RIIC_INTERNAL_RESET;
    /* Set RIIC0 setting */
    RIIC0.MR1.UINT32 = _RIIC_CLOCK_SELECTION_8;
    RIIC0.BRL.UINT32 = _RIIC_RIICBRL_DEFAULT_VALUE | _RIIC0_BITRATE_LOW_LEVEL_PERIOD;
    RIIC0.BRH.UINT32 = _RIIC_RIICBRH_DEFAULT_VALUE | _RIIC0_BITRATE_HIGH_LEVEL_PERIOD;
    RIIC0.MR2.UINT32 = _RIIC_SDAO_DELAY_COUNTER_NO;
    RIIC0.MR3.UINT32 = _RIIC_DIGITAL_NF_STAGE_SINGLE;
    RIIC0.FER.UINT32 = _RIIC_SCL_SYNC_CIRCUIT_USED | _RIIC_NOISE_FILTER_USED | _RIIC_TRANSFER_SUSPENSION_ENABLED | 
                       _RIIC_NACK_ARBITRATION_DISABLE | _RIIC_MASTER_ARBITRATION_ENABLE | 
                       _RIIC_TIMEOUT_FUNCTION_DISABLED;
    RIIC0.IER.UINT32 = _RIIC_TRANSMIT_DATA_EMPTY_INT_ENABLE | _RIIC_TRANSMIT_END_INT_ENABLE | 
                       _RIIC_RECEIVE_COMPLETE_INT_ENABLE | _RIIC_START_CONDITION_INT_ENABLE | 
                       _RIIC_STOP_CONDITION_INT_ENABLE | _RIIC_TIMEOUT_INT_DISABLE | 
                       _RIIC_ARBITRATION_LOST_INT_DISABLE | _RIIC_NACK_RECEPTION_INT_ENABLE;
    /* Cancel internal reset */
    RIIC0.CR1.UINT32 &= _RIIC_CLEAR_INTERNAL_RESET;
    /* Synchronization processing */
    g_cg_sync_read = RIIC0.MR1.UINT32;
    __syncp();

    /* Set RIIC0SCL pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(13U);
    PORT0.PCR17_3.UINT32 = (PORT0.PCR17_3.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR17_3.UINT32 |= _PCR_SET_PODC;
    PORT0.PCR17_3.UINT32 &= _PCR_CLEAR_PDSC;
    PORT0.PCR17_3.UINT32 &= _PCR_CLEAR_PUCC;
    PORT0.PCR17_3.UINT32 |= _PCR_ALT_OUT4;
    PORT0.PCR17_3.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR17_3.UINT32 &= _PCR_CLEAR_PM;
    PORT0.PCR17_3.UINT32 |= _PCR_SET_PBDC;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set RIIC0SDA pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(13U);
    PORT0.PCR17_2.UINT32 = (PORT0.PCR17_2.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR17_2.UINT32 |= _PCR_SET_PODC;
    PORT0.PCR17_2.UINT32 &= _PCR_CLEAR_PDSC;
    PORT0.PCR17_2.UINT32 &= _PCR_CLEAR_PUCC;
    PORT0.PCR17_2.UINT32 |= _PCR_ALT_OUT4;
    PORT0.PCR17_2.UINT32 |= _PCR_SET_PMC;
    PORT0.PCR17_2.UINT32 &= _PCR_CLEAR_PM;
    PORT0.PCR17_2.UINT32 |= _PCR_SET_PBDC;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    R_RIIC0_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_RIIC0_Start
* Description  : This function starts the IIC Bus Interface.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RIIC0_Start(void)
{
    /* Clear RIIC0 interrupt request and enable operation */
    INTC2.EIC687.BIT.EIRF687 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC688.BIT.EIRF688 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC686.BIT.EIRF686 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC685.BIT.EIRF685 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC687.BIT.EIMK687 = _INT_PROCESSING_ENABLED;
    INTC2.EIC688.BIT.EIMK688 = _INT_PROCESSING_ENABLED;
    INTC2.EIC686.BIT.EIMK686 = _INT_PROCESSING_ENABLED;
    INTC2.EIC685.BIT.EIMK685 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_RIIC0_Stop
* Description  : This function stops the IIC Bus Interface.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RIIC0_Stop(void)
{
    /* Disable RIIC0 interrupt operation and clear request */
    INTC2.EIC687.BIT.EIMK687 = _INT_PROCESSING_DISABLED;
    INTC2.EIC688.BIT.EIMK688 = _INT_PROCESSING_DISABLED;
    INTC2.EIC686.BIT.EIMK686 = _INT_PROCESSING_DISABLED;
    INTC2.EIC685.BIT.EIMK685 = _INT_PROCESSING_DISABLED;
    INTC2.EIC687.BIT.EIRF687 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC688.BIT.EIRF688 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC686.BIT.EIRF686 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC685.BIT.EIRF685 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = RIIC0.MR1.UINT32;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_RIIC0_Master_Send
* Description  : This function writes data to a slave device.
* Arguments    : adr -
*                    address of slave device
*                tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    transmit data length
* Return Value : status -
*                    MD_OK, MD_ERROR1 or MD_ERROR2
***********************************************************************************************************************/
MD_STATUS R_RIIC0_Master_Send(uint16_t adr, uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (RIIC0.CR2.UINT32 & _RIIC_BUS_BUSY)
    {
        status = MD_ERROR1;
    }
    else if (adr > _RIIC_ADDRESS_10BIT)
    {
        status = MD_ERROR2;
    }
    else
    {
        /* Set parameter */
        g_riic0_tx_count = tx_num;
        gp_riic0_tx_address = tx_buf;
        g_riic0_slave_address = adr;
        g_riic0_mode_flag = _RIIC_MASTER_TRANSMIT;

        if (adr <= _RIIC_ADDRESS_7BIT)
        {
            g_riic0_state = _RIIC_MASTER_SENDS_ADR_7_W;
        }
        else
        {
            g_riic0_state = _RIIC_MASTER_SENDS_ADR_10A_W;
        }

        R_RIIC0_StartCondition();    /* Issue a start condition */

        /* Set flag for generating stop condition when transmission finishes */
        g_riic0_stop_generation = 1U;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_RIIC0_Master_Send_Without_Stop
* Description  : This function writes data to a slave device.
* Arguments    : adr -
*                    address of slave device
*                tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    transmit data length
* Return Value : status -
*                    MD_OK, MD_ERROR1 or MD_ERROR2
***********************************************************************************************************************/
MD_STATUS R_RIIC0_Master_Send_Without_Stop(uint16_t adr, uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (RIIC0.CR2.UINT32 & _RIIC_BUS_BUSY)
    {
        status = MD_ERROR1;
    }
    else if (adr > _RIIC_ADDRESS_10BIT)
    {
        status = MD_ERROR2;
    }
    else
    {
        /* Set parameter */
        g_riic0_tx_count = tx_num;
        gp_riic0_tx_address = tx_buf;
        g_riic0_slave_address = adr;
        g_riic0_mode_flag = _RIIC_MASTER_TRANSMIT;

        if (adr <= _RIIC_ADDRESS_7BIT)
        {
            g_riic0_state = _RIIC_MASTER_SENDS_ADR_7_W;
        }
        else
        {
            g_riic0_state = _RIIC_MASTER_SENDS_ADR_10A_W;
        }

        R_RIIC0_StartCondition();    /* Issue a start condition */

        /* Set flag for not generating stop condition when transmission finishes */
        g_riic0_stop_generation = 0U;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_RIIC0_Master_Receive
* Description  : This function reads data from a slave device.
* Arguments    : adr -
*                    address of slave device
*                rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    number of bytes to be received
* Return Value : status -
*                    MD_OK, MD_ERROR1 or MD_ERROR2
***********************************************************************************************************************/
MD_STATUS R_RIIC0_Master_Receive(uint16_t adr, uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (adr > _RIIC_ADDRESS_10BIT)
    {
        status = MD_ERROR2;
    }
    else
    {
        /* Set parameter */
        g_riic0_rx_length = rx_num;
        g_riic0_rx_count = 0U;
        gp_riic0_rx_address = rx_buf;
        g_riic0_slave_address = adr;
        g_riic0_dummy_read_count = 0U;
        g_riic0_mode_flag = _RIIC_MASTER_RECEIVE;

        if (adr <= _RIIC_ADDRESS_7BIT)
        {
            g_riic0_state = _RIIC_MASTER_SENDS_ADR_7_R;
        }
        else
        {
            g_riic0_state = _RIIC_MASTER_SENDS_ADR_10A_W;
        }

        if (RIIC0.CR2.UINT32 & _RIIC_BUS_BUSY)
        {
            /* Has a stop been issued or detected? */
            if ((_RIIC_STOP_CONDITION_REQUEST & RIIC0.CR2.UINT32) || (_RIIC_STOP_CONDITION_DETECTED &
                 RIIC0.SR2.UINT32))
            {
                /* Wait for the bus to become idle */
                do
                {
                    /* Arbitration lost or timeout? */
                    if ((_RIIC_TIMEOUT_DETECTED & RIIC0.SR2.UINT32) || (_RIIC_ARBITRATION_LOST &
                         RIIC0.SR2.UINT32))
                    {
                        return (MD_ERROR4);
                    }
                } while (_RIIC_BUS_BUSY & RIIC0.CR2.UINT32);

                /* Issue a start condition */
                R_RIIC0_StartCondition();
            }
            /* Bus is busy and it is master mode (MST = 1) */
            else if (_RIIC_MASTER_MODE & RIIC0.CR2.UINT32)
            {
                /* Issue a restart condition */
                RIIC0.SR2.UINT32 &= (uint32_t) ~_RIIC_START_CONDITION_DETECTED;
                RIIC0.IER.UINT32 |= _RIIC_START_CONDITION_INT_ENABLE;
                RIIC0.CR2.UINT32 |= _RIIC_RESTART_CONDITION_REQUEST;
            }
            else
            {
                /* Another master must have the bus */
                status = MD_ERROR5;
            }
        }
        else
        {
            /* Issue a start condition */
            R_RIIC0_StartCondition();
        }
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_RIIC0_StartCondition
* Description  : This function generate IIC start condition.
* Arguments    : None
* Return Value : None -
***********************************************************************************************************************/
void R_RIIC0_StartCondition(void)
{
    /* Set start condition flag */
    RIIC0.CR2.UINT32 |= _RIIC_START_CONDITION_REQUEST;
}

/***********************************************************************************************************************
* Function Name: R_RIIC0_StopCondition
* Description  : This function generate IIC stop condition.
* Arguments    : None
* Return Value : None -
***********************************************************************************************************************/
void R_RIIC0_StopCondition(void)
{
    /* Set stop condition flag */
    RIIC0.CR2.UINT32 |= _RIIC_STOP_CONDITION_REQUEST;
}

/* Start user code for adding. Do not edit comment generated here */


r_Riic_Busy_State_t  R_RIIC0_busy_state(void)
{
    if( (_RIIC_BUS_BUSY & RIIC0.CR2.UINT32) != 0) 
    {
        return R_RIIC_BUSY;
    }
    if(g_riic0_busy == 1)
    {
	    return R_RIIC_BUSY;
    }

     return R_RIIC_NOT_BUSY;
    

}

void  R_RIIC0_set_busy(void)
{
    g_riic0_busy=1;
}


/* End user code. Do not edit comment generated here */
