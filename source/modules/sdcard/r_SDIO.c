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
/* This file contains high level functions related to command and            */
/* communication handlers for selected Digital Cards.                        */
/*                                                                           */
/*===========================================================================*/

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "inc\common.h"
#include "r_SDIO.h"
#include "shared.h"
#include "drivers\gpio\r_gpio_helper.h"
#include "drivers\mmca\r_MMCA.h"


/*******************************************************************************
  Global variables
*******************************************************************************/
sdio_info_t		g_sdio_info;
uint32_t		g_sdio_data_rd[128] 	= {0};
static void 	(*SDIO_callback)() 	= SDIO_default_callback;
uint32_t		g_sdiotimeoutvalue			= 0;

volatile uint32_t  g_buff_rd[128] = {0};
volatile uint32_t  g_buff_wr[128] = {0};

r_SdioStatus_t g_SdioStatus;

/*******************************************************************************
  Local Functions
*******************************************************************************/

/*******************************************************************************
* Function Name: SDIO_default_callback
* Description  : Dummy function
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_default_callback(void)
{
    NOP();
    
    // Do nothing
}

/*******************************************************************************
* Function Name: SDIO_restart
* Description  : Restarts g_sdio_info variables
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_restart(void)
{
    g_sdio_info.state 			= SDIO_STATE_INIT;
    g_sdio_info.status 			= SDIO_OK;
    g_sdio_info.step 				= SDIO_STEP_0;
    g_sdio_info.rca 				= 0;
    g_sdio_info.address			= 0;
    g_sdio_info.size				= 0;
    g_sdio_info.r1.u32			= 0;
    g_sdio_info.r2_cid.u32[0]		= 0;
    g_sdio_info.r2_cid.u32[1]		= 0;
    g_sdio_info.r2_cid.u32[2]		= 0;
    g_sdio_info.r2_cid.u32[3]		= 0;
    g_sdio_info.r2_csd.u32[0]		= 0;
    g_sdio_info.r2_csd.u32[1]		= 0;
    g_sdio_info.r2_csd.u32[2]		= 0;
    g_sdio_info.r2_csd.u32[3]		= 0;
    g_sdio_info.r3.u32			= 0;
    g_sdio_info.r6.u32			= 0;
    g_sdio_info.r7.u32			= 0;
    g_sdio_info.flags.u32			= 0;
    g_sdio_info.mmca.cmd_set.u32 	= 0;
    g_sdio_info.mmca.arg			= 0;
    g_sdio_info.mmca.data			= 0;
    g_sdio_info.mmca.block_set.u32= 0;
}


//#define DEBUG_ERRORS
#ifdef DEBUG_ERRORS
volatile uint32_t 	debug_test_cmdvio  = 0;
volatile uint32_t 	debug_test_bufvio  = 0;
volatile uint32_t 	debug_test_wdaterr = 0;
volatile uint32_t 	debug_test_rdaterr = 0;
volatile uint32_t 	debug_test_ridxerr = 0;
volatile uint32_t 	debug_test_rsperr  = 0;
volatile uint32_t 	debug_test_crcsto  = 0;
volatile uint32_t 	debug_test_wdatto  = 0;
volatile uint32_t 	debug_test_rdatto  = 0;
volatile uint32_t 	debug_test_rbsyto  = 0;
volatile uint32_t 	debug_test_rspto   = 0;
volatile uint32_t 	store_error_flags  = 0;

volatile uint32_t 	cmd_read_single  = 0;
volatile uint32_t 	cmd_write_single  = 0;
volatile uint32_t 	cmd_read_multi  = 0;
volatile uint32_t 	cmd_write_multi  = 0;

volatile uint32_t 	cmd_write_single_step  = 0xFF;
volatile uint32_t 	cmd_write_multi_step  = 0xFF;



#endif

/*******************************************************************************
* Function Name: SDIO_Error_Handler
* Description  : SDIO Interruption error flag handler 
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_Error_Handler(void)
{

    #ifdef DEBUG_ERRORS
        store_error_flags = mmca_p->int_reg.u32;
    #endif


    if (mmca_p->int_reg.reg.cmdvio) // Command Issuance Error
    {
        mmca_p->int_reg.reg.cmdvio = 0; // Clearing flag.
        g_sdio_info.state = SDIO_STATE_INACTIVE;

        #ifdef DEBUG_ERRORS
            debug_test_cmdvio++;
        #endif

    }
    else if (mmca_p->int_reg.reg.bufvio) // Buffer Access Error
    {
        mmca_p->int_reg.reg.bufvio = 0; // Clearing flag.
        g_sdio_info.state = SDIO_STATE_INACTIVE;

        #ifdef DEBUG_ERRORS
            debug_test_bufvio++;
        #endif

    }
    else if (mmca_p->int_reg.reg.wdaterr) // Write Data Error
    {
        mmca_p->int_reg.reg.wdaterr = 0; // Clearing flag.
        g_sdio_info.state = SDIO_STATE_INACTIVE;

        #ifdef DEBUG_ERRORS
            debug_test_wdaterr++;
        #endif

    }
    else if (mmca_p->int_reg.reg.rdaterr) // Read Data Error
    {
        mmca_p->int_reg.reg.rdaterr = 0; // Clearing flag.
        g_sdio_info.state = SDIO_STATE_INACTIVE;

        #ifdef DEBUG_ERRORS
            debug_test_rdaterr++;
        #endif

    }
    else if (mmca_p->int_reg.reg.ridxerr) // Response Index Error
    {
        mmca_p->int_reg.reg.ridxerr = 0; // Clearing flag.
        g_sdio_info.state = SDIO_STATE_INACTIVE;

        #ifdef DEBUG_ERRORS
            debug_test_ridxerr++;
        #endif

    }
    else if (mmca_p->int_reg.reg.rsperr) // Response Error
    {
        mmca_p->int_reg.reg.rsperr = 0; // Clearing flag.
        g_sdio_info.state = SDIO_STATE_INACTIVE;

        #ifdef DEBUG_ERRORS
            debug_test_rsperr++;
        #endif

    }
    else if (mmca_p->int_reg.reg.crcsto) // CRC Status Timeout
    {
        mmca_p->int_reg.reg.crcsto = 0; // Clearing flag.
        g_sdio_info.state = SDIO_STATE_INACTIVE;

        #ifdef DEBUG_ERRORS
            debug_test_crcsto++;
        #endif

    }
    else if (mmca_p->int_reg.reg.wdatto) // Write Data Timeout
    {
        mmca_p->int_reg.reg.wdatto = 0; // Clearing flag.
        g_sdio_info.state = SDIO_STATE_INACTIVE;

        #ifdef DEBUG_ERRORS
            debug_test_wdatto++;
        #endif

    }
    else if (mmca_p->int_reg.reg.rdatto) // Read Data Timeout
    {
        mmca_p->int_reg.reg.rdatto = 0; // Clearing flag.
        g_sdio_info.state = SDIO_STATE_INACTIVE;

        #ifdef DEBUG_ERRORS
            debug_test_rdatto++;
        #endif

    }
    else if (mmca_p->int_reg.reg.rbsyto) // Response Busy Timeout
    {
        mmca_p->int_reg.reg.rbsyto = 0; // Clearing flag.
        g_sdio_info.state = SDIO_STATE_INACTIVE;

        #ifdef DEBUG_ERRORS
            debug_test_rbsyto++;
        #endif

    }
    else if (mmca_p->int_reg.reg.rspto) // Response Timeout
    {
        mmca_p->int_reg.reg.rspto = 0; // Clearing flag.
        if (mmca_p->cmd_set.u32 == CMD8)
        {
            // Command transmission error, no response from SD Memory Card.
            // Means that: Ver2.00 or later SD Memory Card (voltage mismatch)
            //          or Ver1.X SD Memory Card
            //          or Not SD Memory Card
            g_sdio_info.flags.reg.hcs = SDIO_HCS_SDSC;
            g_sdio_info.status = SDIO_OK;
        }
        else
        {
            // An actual error occured.
            g_sdio_info.state = SDIO_STATE_INACTIVE;

            #ifdef DEBUG_ERRORS
                debug_test_rspto++;
            #endif

        }
    }
    else
    {
        // Do nothing	
    }
}

/*******************************************************************************
* Function Name: SDIO_Command_Handler
* Description  : Handles all the command responses from card
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_Command_Handler(void)
{
    switch(mmca_p->cmd_set.u32)
    {
        case CMD0:
        {
            // Do nothing here
            break;
        }
        case CMD2:
        {
            g_sdio_info.r2_cid.u32[0] = mmca_p->resp0;
            g_sdio_info.r2_cid.u32[1] = mmca_p->resp1;
            g_sdio_info.r2_cid.u32[2] = mmca_p->resp2;
            g_sdio_info.r2_cid.u32[3] = mmca_p->resp3;

            break;
        }
        case CMD3:
        {
            g_sdio_info.r6.u32 = mmca_p->resp0;
            break;
        }
        case CMD6:
        {
            g_sdio_info.r1.u32 = mmca_p->resp0;
            break;
        }
        case CMD7:
        {
            g_sdio_info.r1.u32 = mmca_p->resp0;
            break;
        }
        case CMD8:
        {
            g_sdio_info.r7.u32 = mmca_p->resp0;
            g_sdio_info.flags.reg.hcs = SDIO_HCS_SDHC_SDXC;
            break;
        }
        case CMD9:
        {
            g_sdio_info.r2_csd.u32[0] = mmca_p->resp0;
            g_sdio_info.r2_csd.u32[1] = mmca_p->resp1;
            g_sdio_info.r2_csd.u32[2] = mmca_p->resp2;
            g_sdio_info.r2_csd.u32[3] = mmca_p->resp3;

            break;
        }
        case CMD16:
        {
            g_sdio_info.r1.u32 = mmca_p->resp0;
            
            #ifdef DEBUG_ERRORS
                // check SD cards errors
                if( (g_sdio_info.r1.u32 & 0xFFF9E008) != 0){
                    while(1){
                        NOP();
                    }
                }
            #endif
            
            break;

        }
        case CMD17:
        {
            g_sdio_info.r1.u32 = mmca_p->resp0;

            #ifdef DEBUG_ERRORS
                // check SD cards errors
                if( (g_sdio_info.r1.u32 & 0xFFF9E008) != 0){
                    while(1){
                        NOP();
                    }
                }
            #endif

            break;
        }
        case CMD18:
        {
            g_sdio_info.r1.u32 = mmca_p->resp0;

            #ifdef DEBUG_ERRORS
                // check SD cards errors
                if( (g_sdio_info.r1.u32 & 0xFFF9E008) != 0){
                    while(1){
                        NOP();
                    }
                }
            #endif


            break;
        }
        case CMD23:
        {
            g_sdio_info.r1.u32 = mmca_p->resp0;

            #ifdef DEBUG_ERRORS
                // check SD cards errors
                if( (g_sdio_info.r1.u32 & 0xFFF9E008) != 0){
                    while(1){
                        NOP();
                    }
                }
            #endif

            break;
        }
        case CMD24:
        {
            g_sdio_info.r1.u32 = mmca_p->resp0;

            #ifdef DEBUG_ERRORS
                // check SD cards errors
                if( (g_sdio_info.r1.u32 & 0xFFF9E008) != 0){
                    while(1){
                        NOP();
                    }
                }
            #endif

            break;
        }
        case CMD25:
        {
            g_sdio_info.r1.u32 = mmca_p->resp0;

            #ifdef DEBUG_ERRORS
                // check SD cards errors
                if( (g_sdio_info.r1.u32 & 0xFFF9E008) != 0){
                    while(1){
                        NOP();
                    }
                }
            #endif

            break;
        }
        case CMD55:
        {
            g_sdio_info.r1.u32 = mmca_p->resp0;

            #ifdef DEBUG_ERRORS
                // check SD cards errors
                if( (g_sdio_info.r1.u32 & 0xFFF9E008) != 0){
                    while(1){
                        NOP();
                    }
                }
            #endif

            break;
        }
        case ACMD6:
        {
            g_sdio_info.r1.u32 = mmca_p->resp0;


            break;
        }
        case ACMD41:
        {
            g_sdio_info.r3.u32 = mmca_p->resp0;
            break;
        }
        default:
            break;
    }
}

/*******************************************************************************
* Function Name: SDIO_Status_Handler
* Description  : Interrupt handler for all status changes
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_Status_Handler(void)
{

    #ifdef DEBUG_ERRORS
        // check SD cards errors
        if( (g_sdio_info.r1.u32 & 0xFFF9E008) != 0){
            while(1){
                NOP();
            }
        }
    #endif


    if (mmca_p->int_reg.reg.cmd12dre) //  Automatic CMD12 Issuance & Buffer Read Complete
    {
        mmca_p->int_reg.reg.cmd12dre = 0; // Clearing flag.
    }
    else if (mmca_p->int_reg.reg.cmd12rbe) // Automatic CMD12 Issuance Response Busy Complete
    {
        mmca_p->int_reg.reg.cmd12rbe = 0; // Clearing flag.
    }
    else if (mmca_p->int_reg.reg.cmd12cre) // Automatic CMD12 Response Complete
    {
        mmca_p->int_reg.reg.cmd12cre = 0; // Clearing flag.
    }
    else if (mmca_p->int_reg.reg.dtrane) // Data Transmission Complete
    {
        // All blocks of data have been written.
        mmca_p->int_reg.reg.dtrane = 0; // Clearing flag.
        g_sdio_info.status = SDIO_OK;
    }
    else if (mmca_p->int_reg.reg.bufre) // Buffer Read Complete
    {
        // All blocks of data have been received and the data have been read from the buffer.
        mmca_p->int_reg.reg.bufre = 0;  // Clearing flag.
        g_sdio_info.status = SDIO_OK;
    }
    else if (mmca_p->int_reg.reg.bufwen) // Buffer Write Ready
    {
        uint32_t i;
        
        mmca_p->int_reg.reg.bufwen = 0; // Clearing flag.
        
        for (i = 0; i < (mmca_p->block_set.reg.blksiz / 4); i++)
        {
            mmca_p->data = g_sdio_info.mmca.data[i];
        }
        if (mmca_p->block_set.reg.blksiz % 4)
        {
            mmca_p->data = g_sdio_info.mmca.data[i];
        }
        SDIO_callback();
        
    }
    else if (mmca_p->int_reg.reg.bufren) // Buffer Read Ready
    {
        uint32_t i;
        
        mmca_p->int_reg.reg.bufren = 0; // Clearing flag.
        
        for (i = 0; i < (mmca_p->block_set.reg.blksiz / 4); i++)
        {
            g_sdio_info.mmca.data[i] = mmca_p->data;
        }
        if (mmca_p->block_set.reg.blksiz % 4)
        {
            g_sdio_info.mmca.data[i] = mmca_p->data;
        }
        SDIO_callback();
    }
    else if (mmca_p->int_reg.reg.rbsye) // Response Busy Complete
    {
        mmca_p->int_reg.reg.rbsye = 0; // Clearing flag.
    }
    else if (mmca_p->int_reg.reg.crspe) // Command/Response Complete
    {
        mmca_p->int_reg.reg.crspe = 0; // Clearing flag.
        SDIO_Command_Handler();
        if (mmca_p->cmd_set.reg.wdat == 0) // Command without data transfer?
        {
            g_sdio_info.status = SDIO_OK;
        }else{
            /* write/read*/
            NOP();
        }
    }
    else
    {
        // Do nothing
    }
}

/*******************************************************************************
* Function Name: SDIO_To_Idle
* Description  : Sequence to move from any state to IDLE
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_To_Idle(void)
{
    if (g_sdio_info.state == SDIO_STATE_INACTIVE)
    {
        return;
    }
    switch(g_sdio_info.step)
    {
        case SDIO_STEP_0:
        {
            g_sdio_info.mmca.cmd_set.u32	= CMD0;
            g_sdio_info.mmca.arg 			= 0;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_1:
        {
            g_sdio_info.state = SDIO_STATE_IDLE;
            g_sdio_info.step = SDIO_STEP_0;
            break;
        }
        default:
        {
            break;
        }
    }
}

/*******************************************************************************
* Function Name: SDIO_To_Ready
* Description  : Sequence to go from IDLE to READY state
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_To_Ready(void)
{
    if (g_sdio_info.state != SDIO_STATE_IDLE)
    {
        return;
    }
    switch(g_sdio_info.step)
    {
        case SDIO_STEP_0:
        {
            g_sdio_info.mmca.cmd_set.u32	= CMD8;
            g_sdio_info.mmca.arg 			= SDIO_CMD8_ARG;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_1:
        {
            sdio_cmd8_t sdio_cmd8;
            sdio_cmd8.u32 = SDIO_CMD8_ARG;

            if (!(g_sdio_info.r7.reg.vha == sdio_cmd8.reg.vhs) || 
                !(g_sdio_info.r7.reg.echo_pattern == sdio_cmd8.reg.check_pattern))
            {
                // Non-compatible voltage range or check pattern is not correct.
                // Unusable Card!
                g_sdio_info.state = SDIO_STATE_INACTIVE;
                g_sdio_info.step = SDIO_STEP_0;
            }
            else
            {
                // Compatible voltage range and check pattern is correct.
                g_sdio_info.mmca.cmd_set.u32	= CMD55;
                g_sdio_info.mmca.arg 			= 0;
                
                R_MMCA_SendCommand(&g_sdio_info.mmca);
                g_sdio_info.status = SDIO_BUSY;
                g_sdio_info.step++;
            }
            break;
        }
        case SDIO_STEP_2:
        {
            sdio_acmd41_t sdio_acmd41;
            sdio_acmd41.u32 = SDIO_ACMD41_ARG;
            // Perform a SDIO Software Reset (Workaround for ACMD41)
            R_MMCA_Reset();
            // End of workaround.
            
            g_sdio_info.mmca.cmd_set.u32	= ACMD41;
            sdio_acmd41.reg.hcs 				= g_sdio_info.flags.reg.hcs;
            g_sdio_info.mmca.arg 			= sdio_acmd41.u32;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_3:
        {
            if (g_sdio_info.r3.reg.busy == 0)
            {
                g_sdio_info.mmca.cmd_set.u32	= CMD55;
                g_sdio_info.mmca.arg 			= 0;
                
                R_MMCA_SendCommand(&g_sdio_info.mmca);
                g_sdio_info.status = SDIO_BUSY;
                
                g_sdio_info.step = SDIO_STEP_2; // go back to SDIO_STEP_2
            }
            else
            {
                if (g_sdio_info.r3.reg.ccs == 1)
                {
                    // Ver2.00 or later High Capacity or Extended Capacity SD Memory Card.
                    NOP();
                }
                else
                {
                    // Ver1.X Standard Capacity SD Memory Card
                    // or Ver2.00 or later Standard Capacity SD Memory Card.
                    NOP();
                }
                g_sdio_info.state = SDIO_STATE_READY;
                

                if ( (g_sdio_info.r3.reg.s18a == 1))
                {
                    // Send CMD11 to switch voltage to 1.8V
                    // but Renesas' MMCA/SDIO Hardware does not support this.
                    NOP();
                }
                g_sdio_info.step = SDIO_STEP_0;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

/*******************************************************************************
* Function Name: SDIO_To_Identification
* Description  : Sequence to go from READY to IDENTIFICATION state
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_To_Identification(void)
{
    if (g_sdio_info.state != SDIO_STATE_READY)
    {
        return;
    }
    switch (g_sdio_info.step)
    {
        case SDIO_STEP_0:
        {
            g_sdio_info.mmca.cmd_set.u32	= CMD2;
            g_sdio_info.mmca.arg 			= 0;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_1:
        {
            g_sdio_info.state = SDIO_STATE_IDENTIFICATION;
            g_sdio_info.step = SDIO_STEP_0;
            break;
        }
        default:
        {
            break;
        }
    }
}



/*******************************************************************************
* Function Name: SDIO_To_Identification
* Description  : Sequence to go from READY to IDENTIFICATION state
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_To_IdentificationCSD(void)
{
    if (g_sdio_info.state != SDIO_STATE_STANDBY)
    {
        return;
    }
    switch (g_sdio_info.step)
    {
        case SDIO_STEP_0:
        {
            g_sdio_info.mmca.cmd_set.u32	= CMD9;
            g_sdio_info.mmca.arg 			= (g_sdio_info.rca << 16) & 0xFFFF0000;;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_1:
        {
            g_sdio_info.state = SDIO_STATE_IDENTIFICATION_CSD;
            g_sdio_info.step = SDIO_STEP_0;
            break;
        }
        default:
        {
            break;
        }
    }
}



/*******************************************************************************
* Function Name: SDIO_To_Standby
* Description  : Sequence to go from IDENTIFICATION to STAND-BY state
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_To_Standby(void)
{
    if (g_sdio_info.state != SDIO_STATE_IDENTIFICATION)
    {
        return;
    }
    switch (g_sdio_info.step)
    {
        case SDIO_STEP_0:
        {
            g_sdio_info.mmca.cmd_set.u32	= CMD3;
            g_sdio_info.mmca.arg 			= 0;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_1:
        {
            g_sdio_info.rca = (uint32_t) g_sdio_info.r6.reg.rca;
            g_sdio_info.state = SDIO_STATE_STANDBY;
            g_sdio_info.step = SDIO_STEP_0;
            break;
        }
        default:
        {
            break;
        }
    }
}

/*******************************************************************************
* Function Name: SDIO_To_Standby
* Description  : Sequence to go from STAND-BY to TRANSFER state
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_To_Transfer(void)
{
    if (g_sdio_info.state != SDIO_STATE_IDENTIFICATION_CSD)
    {
        return;
    }
    switch (g_sdio_info.step)
    {
        case SDIO_STEP_0:
        {
            g_sdio_info.mmca.cmd_set.u32	= CMD7;
            g_sdio_info.mmca.arg 			= (g_sdio_info.rca << 16) & 0xFFFF0000;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_1:
        {
            g_sdio_info.state = SDIO_STATE_TRANSFER;
            g_sdio_info.step = SDIO_STEP_0;
            break;
        }
        default:
        {
            break;
        }
    }
}

/*******************************************************************************
* Function Name: SDIO_Set_4Bit_Bus
* Description  : Sequence to set 4-bit width bus
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_Set_4Bit_Bus(void)
{
    if (g_sdio_info.state != SDIO_STATE_TRANSFER)
    {
        return;
    }
    switch (g_sdio_info.step)
    {
        case SDIO_STEP_0:
        {
            g_sdio_info.mmca.cmd_set.u32	= CMD55;
            g_sdio_info.mmca.arg 			= (g_sdio_info.rca << 16) & 0xFFFF0000;
            
            g_sdio_info.mmca.data 		= &g_sdio_data_rd[0];
            g_sdio_info.mmca.block_set.u32= 0;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_1:
        {
            g_sdio_info.mmca.cmd_set.u32	= ACMD6;
            g_sdio_info.mmca.arg			= 2; // Bus width is 0b10 = 2 = 4bits width
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_2:
        {
            g_sdio_info.flags.reg.bus_width = 1;
            g_sdio_info.step = SDIO_STEP_0;
            break;
        }
        default:
        {
            break;
        }
    }
}

/*******************************************************************************
* Function Name: SDIO_Set_High_Speed
* Description  : Sequence to set High-Speed communication
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_Set_High_Speed(void)
{
    if (g_sdio_info.state != SDIO_STATE_TRANSFER)
    {
        return;
    }
    switch (g_sdio_info.step)
    {
        case SDIO_STEP_0:
        {
            sdio_cmd6_t cmd6_arg;
            cmd6_arg.u32 = 0xFFFFFFF1;	// [31] Mode: 0b1 (switch function)
                                        // [30:16] Reserved: 0x7FFF
                                        // [15:12] Function group 4 for Power Limit: 0xF (No influence)
                                        // [11:8] Function group 3 for Drive Strength: 0xF (No influence)
                                        // [7:4] Function group 2 for Command System: 0xF (No influence)
                                        // [3:0] Function group 1 for Access Mode: 0x1 (High-Speed / SDR25)
            
            g_sdio_info.mmca.arg 					= cmd6_arg.u32;	
            g_sdio_info.mmca.cmd_set.u32			= CMD6;
            g_sdio_info.mmca.block_set.reg.blkcnt = 0;
            g_sdio_info.mmca.block_set.reg.blksiz = 0x0040;
            g_sdio_info.mmca.data 				= &g_sdio_data_rd[0];
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_1:
        {
            sdio_sw_function_sts_t* sw_sts_p;
            sw_sts_p = (sdio_sw_function_sts_t*) g_sdio_info.mmca.data;
            
            if (sw_sts_p->reg.func_sel_fg1)
            {
                R_MMCA_SetHighSpeed();
                g_sdio_info.flags.reg.high_speed = 1;
            }
            g_sdio_info.step = SDIO_STEP_0;
            break;
        }
        default:
        {
            break;
        }
    }
}

/*******************************************************************************
* Function Name: SDIO_Read_Memory_Single
* Description  : Sequence for reading a single block of data
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_Read_Memory_Single(void)
{
    if (g_sdio_info.state != SDIO_STATE_TRANSFER)
    {
        return;
    }
    switch (g_sdio_info.step)
    {
        case SDIO_STEP_0:
        {


            #ifdef DEBUG_ERRORS
                cmd_read_single  = 1;
            #endif


            g_sdio_info.mmca.cmd_set.u32	= CMD16;
            g_sdio_info.mmca.arg 			= g_sdio_info.size;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_1:
        {
            g_sdio_info.mmca.cmd_set.u32	= CMD17;
            g_sdio_info.mmca.arg 			= g_sdio_info.address;
            g_sdio_info.mmca.block_set.reg.blksiz = g_sdio_info.size;
            g_sdio_info.mmca.block_set.reg.blkcnt = 0;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_2:
        {

            #ifdef DEBUG_ERRORS
                cmd_read_single  = 0;
            #endif

            g_sdio_info.flags.reg.tx_type  = SDIO_WAITING;
            SDIO_callback				 = SDIO_default_callback;
            g_sdio_info.flags.reg.tx_ready = 1;
            g_sdio_info.step = SDIO_STEP_0;
            break;
        }
        default:
        {
            break;
        }
    }
}

/*******************************************************************************
* Function Name: SDIO_Read_Memory_Multi
* Description  : Sequence for reading multiple blocks of data
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_Read_Memory_Multi(void)
{
    if (g_sdio_info.state != SDIO_STATE_TRANSFER)
    {
        return;
    }
    switch (g_sdio_info.step)
    {
        case SDIO_STEP_0:
        {

            #ifdef DEBUG_ERRORS
                cmd_read_multi  = 1;
            #endif

            g_sdio_info.mmca.cmd_set.u32	= CMD16;
            g_sdio_info.mmca.arg 			= 512; // Fixed value (512 bytes) for multi block transfer
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_1:
        {
            g_sdio_info.mmca.cmd_set.u32	= CMD23;
            g_sdio_info.mmca.arg 			= g_sdio_info.size;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_2:
        {
            g_sdio_info.mmca.cmd_set.u32			= CMD18;
            g_sdio_info.mmca.arg 					= g_sdio_info.address;
            g_sdio_info.mmca.block_set.reg.blksiz = 512; // Fixed value (512 bytes) for multi block transfer
            g_sdio_info.mmca.block_set.reg.blkcnt = g_sdio_info.size;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_3:
        {

            #ifdef DEBUG_ERRORS
                cmd_read_multi  = 0;
            #endif

            g_sdio_info.flags.reg.tx_type  = SDIO_WAITING;
            SDIO_callback				 = SDIO_default_callback;
            g_sdio_info.flags.reg.tx_ready = 1;
            g_sdio_info.step = SDIO_STEP_0;
            break;
        }
        default:
        {
            break;
        }
    }
}

/*******************************************************************************
* Function Name: SDIO_Write_Memory_Single
* Description  : Sequence for reading a single block of data
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_Write_Memory_Single(void)
{

    volatile uint64_t my_cnt = 0;

    if (g_sdio_info.state != SDIO_STATE_TRANSFER)
    {
        return;
    }
    switch (g_sdio_info.step)
    {
        case SDIO_STEP_0:
        {

            //my_cnt = 0x200000;
            //while(my_cnt>0){
            //	my_cnt--;
            //	NOP();
            //}

            #ifdef DEBUG_ERRORS
                cmd_write_single  = 1;
                cmd_write_single_step  = 1;
                if( (MMCA0CE_HOST_STS1 & 0x80000000) == 0x80000000){
                    while(1){
                        NOP();
                    }
                }


            #endif

            g_sdio_info.mmca.cmd_set.u32	= CMD16;
            g_sdio_info.mmca.arg 			= g_sdio_info.size;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_1:
        {


            #ifdef DEBUG_ERRORS
                cmd_write_single_step  = 2;
                if( (MMCA0CE_HOST_STS1 & 0x80000000) == 0x80000000){
                    while(1){
                        NOP();
                    }
                }
            #endif

            g_sdio_info.mmca.cmd_set.u32	= CMD24;
            g_sdio_info.mmca.arg 			= g_sdio_info.address;
            g_sdio_info.mmca.block_set.reg.blksiz = g_sdio_info.size;
            g_sdio_info.mmca.block_set.reg.blkcnt = 0;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_2:
        {

            #ifdef DEBUG_ERRORS
                cmd_write_single  = 0;
                cmd_write_single_step  = 3;

                if( (MMCA0CE_HOST_STS1 & 0x80000000) == 0x80000000){
                    while(1){
                        NOP();
                    }
                }

            #endif

            g_sdio_info.flags.reg.tx_type  = SDIO_WAITING;
            SDIO_callback				 = SDIO_default_callback;
            g_sdio_info.flags.reg.tx_ready = 1;
            g_sdio_info.step = SDIO_STEP_0;
            break;
        }
        default:
        {
            break;
        }
    }
}



/*******************************************************************************
* Function Name: SDIO_Write_Memory_Multi
* Description  : Sequence for writing multiple blocks of data
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_Write_Memory_Multi(void)
{
    if (g_sdio_info.state != SDIO_STATE_TRANSFER)
    {
        return;
    }
    switch (g_sdio_info.step)
    {
        case SDIO_STEP_0:
        {

            #ifdef DEBUG_ERRORS
                cmd_write_multi  = 1;
                cmd_write_multi_step = 0;
            #endif

            g_sdio_info.mmca.cmd_set.u32	= CMD16;
            g_sdio_info.mmca.arg 			= 512; // Fixed value (512 bytes) for multi block transfer
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_1:
        {

            #ifdef DEBUG_ERRORS
                cmd_write_multi_step = 1;
            #endif

            g_sdio_info.mmca.cmd_set.u32	= CMD23;
            g_sdio_info.mmca.arg 			= g_sdio_info.size;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_2:
        {
            #ifdef DEBUG_ERRORS
                cmd_write_multi_step = 2;
            #endif

            g_sdio_info.mmca.cmd_set.u32			= CMD25;
            g_sdio_info.mmca.arg 					= g_sdio_info.address;
            g_sdio_info.mmca.block_set.reg.blksiz = 512; // Fixed value (512 bytes) for multi block transfer
            g_sdio_info.mmca.block_set.reg.blkcnt = g_sdio_info.size;
            
            R_MMCA_SendCommand(&g_sdio_info.mmca);
            g_sdio_info.status = SDIO_BUSY;
            g_sdio_info.step++;
            break;
        }
        case SDIO_STEP_3:
        {

            #ifdef DEBUG_ERRORS
                cmd_write_multi  = 0;
                cmd_write_multi_step = 3;
            #endif

            g_sdio_info.flags.reg.tx_type  = SDIO_WAITING;
            SDIO_callback				 = SDIO_default_callback;
            g_sdio_info.flags.reg.tx_ready = 1;
            g_sdio_info.step = SDIO_STEP_0;
            break;
        }
        default:
        {
            break;
        }
    }
}

/*******************************************************************************
* Function Name: SDIO_Interrupt
* Description  : Interrupt handler
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_Interrupt(void)
{
    if (g_sdio_info.state == SDIO_STATE_INACTIVE)
    {
        mmca_p->int_reg.u32 = 0;
        return;
    }
    else
    {
        if (mmca_p->int_reg.u32 & MMCA_INT_ERRORS)
        {
            SDIO_Error_Handler();
        }
        else // (mmca_p->int_reg.u32 & MMCA_INT_STATUS)
        {
            SDIO_Status_Handler();
        }
    }
}

/*******************************************************************************
  Global Functions
*******************************************************************************/

/*******************************************************************************
* Function Name: SDIO_Init
* Description  : This function initializes SDIO
* Arguments    : None
* Return Value : None
*******************************************************************************/
void SDIO_Init(void)
{
    R_MMCA_Init();
    R_MMCA_EnableInterrupt(&SDIO_Interrupt);
    SDIO_restart();
}

/*******************************************************************************
* Function Name: SDIO_Update
* Description  : This function updates the SDIO states step by step
* Arguments    : None
* Return Value : None
*******************************************************************************/

void SDIO_Update(void)
{
    if (SDIO_card_detection()==card_detected) // pin DET = 1
    {
        g_SdioStatus.cardDetection = card_detected;
        if (g_sdio_info.status == SDIO_OK) // SDIO is not processing any command
        {
            switch (g_sdio_info.state)
            {
                case SDIO_STATE_INIT:
                    if (g_sdio_info.flags.reg.delay == 0)
                    {
                        g_sdio_info.flags.reg.delay = 1;
                        // wait 1 sec
                        g_sdiotimeoutvalue = g_SystemStatus.RunTimeMs + 1000;
                    }
                    else
                    {
                        if (g_sdiotimeoutvalue> g_SystemStatus.RunTimeMs)
                        {
                            g_sdio_info.flags.reg.delay = 0;
                            g_sdio_info.state = SDIO_STATE_INIT_DELAYED;
                        }
                    }
                    break;
                case SDIO_STATE_INIT_DELAYED:
                    SDIO_To_Idle();
                    break;
                case SDIO_STATE_INACTIVE:
                    // Do nothing, Unusable card
                    break;
                case SDIO_STATE_IDLE:
                    SDIO_To_Ready();
                    break;
                case SDIO_STATE_READY:
                    SDIO_To_Identification();
                    break;
                case SDIO_STATE_IDENTIFICATION:
                    SDIO_To_Standby();
                    break;
                case SDIO_STATE_STANDBY:
                    SDIO_To_IdentificationCSD();
                    break;
                case SDIO_STATE_IDENTIFICATION_CSD:
                    SDIO_To_Transfer();
                    break;
                case SDIO_STATE_TRANSFER:
                    if (g_sdio_info.flags.reg.bus_width == 0) // Means actual bus width is 4
                    {
                        SDIO_Set_4Bit_Bus();
                    }
                    else if (g_sdio_info.flags.reg.high_speed == 0 	// Clock still in Low Speed 
                          && g_sdio_info.r3.reg.ccs == 1)				// AND Card Capacity Status (CCS): SDHC or SDXC
                    {
                        SDIO_Set_High_Speed();
                    }
                    else if (g_sdio_info.flags.reg.tx_type == SDIO_READ_SINGLE)
                    {
                        SDIO_Read_Memory_Single();
                    }
                    else if (g_sdio_info.flags.reg.tx_type == SDIO_READ_MULTI)
                    {
                        SDIO_Read_Memory_Multi();
                    }
                    else if (g_sdio_info.flags.reg.tx_type == SDIO_WRITE_SINGLE)
                    {
                        SDIO_Write_Memory_Single();
                    }
                    else if (g_sdio_info.flags.reg.tx_type == SDIO_WRITE_MULTI)
                    {
                        SDIO_Write_Memory_Multi();
                    }
                    else
                    {
                        g_sdio_info.flags.reg.tx_ready = 1;
                        // Do nothing. Just waiting for a request
                    }
                    break;
                default:
                    break;
            }
        }
    }
    else
    {
        if (g_sdio_info.state != SDIO_STATE_INIT)
        {
            if(g_SdioStatus.cardDetection == card_not_detected)
            {
                return;
            }
            SDIO_restart();
            R_MMCA_Reset();
        }
    }
}

/*******************************************************************************
* Function Name: SDIO_Start_Transmission
* Description  : Starts a transmission (Rx or Tx)
* Arguments    : tx_type - 
*					Type of transmission
*				 data -
*					Pointer to where to store read data or where to write it
*				 size -
*					Number of bytes (or blocks) to read/write
*				 address -
*					SD memory address
*				 sdio_callback_p -
*					Pointer to a function that will be called each time 512 (or less) bytes are read/written
* Return Value : Status of the request (was made or not)
*******************************************************************************/
sdio_status_t SDIO_Start_Transmission(sdio_tx_type_t tx_type, uint32_t *data, uint32_t size, uint32_t address, sdio_callback_t *sdio_callback_p)
{
    if (tx_type != SDIO_WAITING)
    {
        g_sdio_info.flags.reg.tx_type 	= tx_type;
        g_sdio_info.mmca.data 			= data;
        g_sdio_info.size 					= size;
        g_sdio_info.address 				= address;
        SDIO_callback					= sdio_callback_p;
        g_sdio_info.flags.reg.tx_ready	= 0;
        
        return SDIO_OK;
    }
    else
    {
        return SDIO_ERROR;
    }
}

/*******************************************************************************
* Function Name: SDIO_Get_State
* Description  : Returns the actual state of the SD memory
* Arguments    : None
* Return Value : Actual state of the SD memory
*******************************************************************************/
sdio_state_t SDIO_Get_State(void)
{
    return g_sdio_info.state;
}

/*******************************************************************************
* Function Name: SDIO_Get_Status
* Description  : Returns the status of the driver (OK or BUSY)
* Arguments    : None
* Return Value : Status of the driver
*******************************************************************************/
sdio_status_t SDIO_Get_Status(void)
{
    return g_sdio_info.status;
}

/*******************************************************************************
* Function Name: SDIO_Ready_To_Transfer
* Description  : Returns whether or not SD card is ready for transfer
* Arguments    : None
* Return Value : Readiness of the SD card for transfer
*******************************************************************************/
uint32_t SDIO_Ready_To_Transfer(void)
{
    return g_sdio_info.flags.reg.tx_ready;
}


/*******************************************************************************
* Function Name: SDIO_card_detection
* Description  : Check weather the SD Card is connected or NOT.
* Arguments    : None
* Return Value : "card_not_detected" if the card is not detected.
                 "card_detected" if the card is detected.
*******************************************************************************/

SDIO_cardDetectionState_t SDIO_card_detection(void)
{
    if (readGpio(24,10) == 1)
    {
        g_sdio_info.state = SDIO_STATE_INACTIVE;
        g_SdioStatus.cardDetection = card_not_detected;
        return card_not_detected;
    }
    else
    {
        return card_detected;
    }
}

/******************************************************************************
* Function Name: error_SD_Card
* Description  : SD Card error condition handling
* Arguments    : None
* Return Value : None
******************************************************************************/

void error_SD_Card(void){
    /* Error occured during SD Card initialization */
    /* E.g. removed SD card or any other communication errors */
    g_SdioStatus.cardDetection = card_not_detected;
    g_SdioStatus.SdTest = SDIO_TEST_ERROR;
}

/*****************************************************************************
** Function:    read_single_sdio_callback
** Description: This callback is called every time 512 bytes are received from 
                SD card are available in DATA buffer.
** Parameter:   None
** Return:      None
******************************************************************************/

void read_single_sdio_callback(void) 
{

}

void run_SD_read(BYTE pdrv, uint32_t *buff_run, LBA_t sector_run, UINT count_run)
{

    /* Start user code for main. Do not edit comment generated here */
    uint32_t  counter 		= 1;
    uint32_t  temp_i 		= 0;
    uint32_t  *ptr;

    while (1)
    {
        SDIO_Update();

        if( SDIO_Get_State() == SDIO_STATE_INACTIVE){
            /* SD Card removed or any communication error */
            error_SD_Card();	
            break;
        }

        if (SDIO_Ready_To_Transfer())
        {
            if (counter == 1)
            {
                /*_____________________________SDIO_READ_SINGLE_________________________________________*/
                
                SDIO_Start_Transmission(SDIO_READ_SINGLE, (uint32_t *)&g_buff_rd[0], count_run*512, sector_run , &read_single_sdio_callback);
                counter++;
            }

            else if(counter == 2)
            {
                counter = 0;

                ptr=(uint32_t *)g_buff_rd;

                for(temp_i=0;temp_i<128;temp_i++){
                ptr[temp_i]= sys_htonl(ptr[temp_i]);
                }

                for(temp_i=0;temp_i<128;temp_i++)
                {
                    buff_run[temp_i] = g_buff_rd[temp_i];
                }

                return;
            }
            
        }
    }
    
}

/*****************************************************************************
** Function:    write_single_sdio_callback
** Description: This callback is called every time 512 bytes are received from 
                SD card are available in DATA buffer.
** Parameter:   None
** Return:      None
******************************************************************************/

void write_single_sdio_callback(void) 
{

}

void run_SD_write(BYTE pdrv, uint32_t *buff_wr_run, LBA_t sector_run, UINT count_run)
{

    /* Start user code for main. Do not edit comment generated here */
    uint32_t  counter 		= 1;
    uint32_t  temp_i 		= 0;

    for(temp_i=0;temp_i<128;temp_i++)
    {
        g_buff_wr[temp_i] = sys_htonl(buff_wr_run[temp_i]);
    }

    while (1)
    {
        SDIO_Update();

        if( SDIO_Get_State() == SDIO_STATE_INACTIVE){
            /* SD Card removed or any communication error */
            error_SD_Card();
            break;
        }
        
        if (SDIO_Ready_To_Transfer())
        {
            if (counter == 1)
            {
                /*_____________________________SDIO_WRITE_SINGLE_________________________________________*/
                
                SDIO_Start_Transmission(SDIO_WRITE_SINGLE, (uint32_t *)&g_buff_wr[0], count_run*512, sector_run , &write_single_sdio_callback);
                counter++;
            }
    
            else if(counter == 2)
            {
                counter = 0;
                return;
            }
        }
    }
}

/*****************************************************************************
** Function:    SDIO_SystemTest
** Description: This is the SD Card System Test. It will do the following: -
                1. Create a file
                2. Write to the file.
                3. Read from the file.
                4. Compare the contents of what was written vs read.
                5. Delete the file.
** Parameter:   None
** Return:      sdio_test_result_t
******************************************************************************/

sdio_test_result_t SDIO_SystemTest(void){

    FATFS FatFs_SystemTest;    /* Work area (filesystem object) for logical drive */
    FIL fil_SystemTest;        /* File object */
    FRESULT fr_SystemTest;     /* FatFs return code */
    UINT bw_SystemTest;        /* Bytes written */
    char write_open_file_SystemTest[50];
    char line_SystemTest[100]; /* Line buffer */
    char file_create_path_SystemTest[50] = "/renesas_testfile.txt";
    char write_data_SystemTest[50] = "renesas";
    char line_compare_buffer_SystemTest[100];
    uint8_t SDIO_flag_mount_success = 0;
    uint8_t SDIO_flag_write_success = 0;
    uint8_t SDIO_flag_read_success = 0;
    uint8_t SDIO_flag_file_create_success = 0;
    uint8_t SDIO_flag_data_cmp_success = 0;
    uint8_t SDIO_flag_delete_success = 0;
    sdio_test_result_t SDIO_test_result = SDIO_TEST_ERROR;
    
    g_SdioStatus.SdTest = SDIO_TEST_ERROR; /* Guard condition to ensure secure-fail start for test. */
    g_SdioStatus.cardDetection =     card_not_detected;; /* Guard condition to ensure secure-fail start for test. */
    

    /* Create a file. */
    /* Give a work area to the default drive */
    fr_SystemTest = f_mount(&FatFs_SystemTest, "", 1);
    if(fr_SystemTest != FR_OK)
    {
        SDIO_flag_mount_success = 0;
    }
    else if(fr_SystemTest == FR_OK)
    {
        SDIO_flag_mount_success = 1;
    }
    
    strcpy(write_open_file_SystemTest, file_create_path_SystemTest); 

    fr_SystemTest = f_open(&fil_SystemTest, file_create_path_SystemTest, FA_CREATE_NEW | FA_WRITE | FA_READ);
    if(fr_SystemTest != FR_OK)
    {
        SDIO_flag_file_create_success = 0;
    }
    else if(fr_SystemTest == FR_OK)
    {
        SDIO_flag_file_create_success = 1;
    }

    /* Write to the file. */

    fr_SystemTest = f_write(&fil_SystemTest, write_data_SystemTest, strlen(write_data_SystemTest), &bw_SystemTest);
    if(fr_SystemTest != FR_OK)
    {
        SDIO_flag_write_success = 0;
    }
    else if(fr_SystemTest == FR_OK)
    {
        SDIO_flag_write_success = 1;
    }

    /* Close the file */
    f_close(&fil_SystemTest);
    f_mount(NULL, "", 0);

    /* Only read & compare the data if the file creation and writing to it is successful. */

    if(SDIO_flag_file_create_success & SDIO_flag_write_success)
    {
        /* Read from the file. */

        /* Give a work area to the default drive */
        fr_SystemTest = f_mount(&FatFs_SystemTest, "", 1);
        if(fr_SystemTest != FR_OK)
        {
            SDIO_flag_mount_success = 0;
        }
        else if(fr_SystemTest == FR_OK)
        {
            SDIO_flag_mount_success = 1;
        }

        fr_SystemTest = f_open(&fil_SystemTest, file_create_path_SystemTest, FA_READ);

        /* Read every line and display it */
        while (f_gets(line_SystemTest, sizeof line_SystemTest, &fil_SystemTest)) {
            strcpy(line_compare_buffer_SystemTest, line_SystemTest);
        }

        if(fr_SystemTest != FR_OK)
        {
            SDIO_flag_read_success = 0;
        }

        else if(fr_SystemTest == FR_OK)
        {
            SDIO_flag_read_success = 1;
        }

        /* Close the file */
        f_close(&fil_SystemTest);

        /* Compare the data. */

        if((strcmp(line_compare_buffer_SystemTest, write_data_SystemTest)) == 0)
        {
            /* Store the PASS result. */
            SDIO_flag_data_cmp_success = 1;
        }
        else {
            /* Store the FAIL result. */
            SDIO_flag_data_cmp_success = 0;
        }
    }

    /* Prepare deletion. */
    memset(line_compare_buffer_SystemTest, '\0', sizeof(line_compare_buffer_SystemTest));  /* Clear the string. */

    /* Delete the file. */
    
    fr_SystemTest = f_unlink(file_create_path_SystemTest);
    if(fr_SystemTest != FR_OK)
    {
        SDIO_flag_delete_success = 0;
    }
    else if(fr_SystemTest == FR_OK)
    {
        SDIO_flag_delete_success = 1;
    }

    /* Only if all the below criteria are successfully met is the test OK. It is important to ensure that */
    /* the file which was created is deleted as well or else the next automated test cycle will try to */
    /* re-create the existing file resulting in the test failures. */
    if( SDIO_flag_file_create_success && SDIO_flag_write_success && SDIO_flag_read_success && \
        SDIO_flag_data_cmp_success && SDIO_flag_delete_success && SDIO_flag_mount_success)
    {
        SDIO_test_result = SDIO_TEST_OK;
    }
    else{
       SDIO_test_result = SDIO_TEST_ERROR;
    }

    f_mount(NULL, "", 0);

    return SDIO_test_result;
}
