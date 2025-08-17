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
* File Name         : r_MMCA.c
* Component Version : 1.0.0
* Description       : This file implements the MMCA module.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inc\common.h"
#include "r_MMCA.h"

/***********************************************************************************************************************
Global variables
***********************************************************************************************************************/
mmca_attributes_t* mmca_attributes;
static void (*MMCA_int)() = R_MMCA_IrqDefault;

/***********************************************************************************************************************
External functions
***********************************************************************************************************************/
extern void PrintText(char* TextArray);

/***********************************************************************************************************************
Private functions
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name : R_
* Description   : 
* Arguments     : None
* Return Value  : None
***********************************************************************************************************************/
static void MMCA_PortConfiguration(void)
{
    // done via Smart Configurator. See void R_Pins_Create(void) function.
}

/***********************************************************************************************************************
Public functions
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name : R_MMCA_IrqDefault
* Description   : 
* Arguments     : None
* Return Value  : None
***********************************************************************************************************************/
void R_MMCA_IrqDefault(void)
{
    // Do nothing
}

/***********************************************************************************************************************
* Function Name: R_MMCA_Interrupt
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MMCA_Interrupt(void)
{
    MMCA_int();
}

/***********************************************************************************************************************
* Function Name: R_MMCA_Init
* Description  : MMCA Initialization
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MMCA_Init(void)
{
    MMCA_PortConfiguration();
    
    //SYSCTRLMSRKCPROT = MMCA_PROT_ENABLE;  			/* enable MMCA clock */
    //SYSCTRLMS_MMCA_0 = 0;
    //SYSCTRLMSRKCPROT = MMCA_PROT_DISABLE;
    
    while (mmca_p->host_sts1.reg.cmdseq == 1);  	/* Wait during command sequence execution */
    
    mmca_p->buf_acc.u32 = MMCA_CLEAR_REGISTER;  	/* Initialize Buffer Access Configuration Register */
    mmca_p->buf_acc.u32 |= MMCA_DMATYP_CLEAR 		// DMA transfer disabled
                        |  MMCA_DMAWEN_W_DISABLED  	// Disable DMA transfer request for buffer writing
                        |  MMCA_DMAREN_R_DISABLED;	// Disable DMA transfer request for buffer reading
    mmca_p->buf_acc.u32 |= MMCA_ATYP_NOT_SWAP_BYTE; //= MMCA_ATYP_SWAP_BYTE;	// Buffer access: not swapped byte-wise
    mmca_p->int_reg.u32 = MMCA_CLEAR_REGISTER;  	/* Initialize Interrupt Flag Register */
    
    R_MMCA_SetLowSpeed();
}

/***********************************************************************************************************************
* Function Name: R_MMCA_EnableInterrupt
* Description  : 
* Arguments    : mmca_int_function_p -			
* Return Value : None
***********************************************************************************************************************/
void R_MMCA_EnableInterrupt(mmca_int_function_t *mmca_int_function_p)
{

    INTC2.EIC696.BIT.EIMK696 = 1; // Interrupt processing is disabled.
    INTC2.EIC696.BIT.EIP696  = 7; // Interrupt priority: 7
    INTC2.EIC696.BIT.EITB696 = 1; // Table vector method
    
    mmca_p->int_en.u32 = MMCA_CLEAR_REGISTER;		/* Initialize Interrupt Enable Register */
    mmca_p->int_en.u32 |= MMCA_MCMD12DRE_DISABLE	// Disables interrupt output by the CMD12DRE flag
                       |  MMCA_MCMD12RBE_DISABLE	// Disables interrupt output by the CMD12RBE flag
                       |  MMCA_MCMD12CRE_DISABLE	// Disables interrupt output by the CMD12CRE flag
                       |  MMCA_MDTRANE_ENABLE		// Enables interrupt output by the DTRANE flag
                       |  MMCA_MBUFRE_ENABLE		// Enables interrupt output by the BUFRE flag
                       |  MMCA_MBUFWEN_ENABLE		// Enables interrupt output by the BUFWEN flag
                       |  MMCA_MBUFREN_ENABLE		// Enables interrupt output by the BUFREN flag
                       |  MMCA_MRBSYE_ENABLE		// Enables interrupt output by the RBSYE flag
                       |  MMCA_MCRSPE_ENABLE		// Enables interrupt output by the CRSPE flag
                       |  MMCA_MCMDVIO_ENABLE		// Enables interrupt output by the CMDVIO flag
                       |  MMCA_MBUFVIO_ENABLE		// Enables interrupt output by the BUFVIO flag
                       |  MMCA_MWDATERR_ENABLE		// Enables interrupt output by the WDATERR flag
                       |  MMCA_MRDATERR_ENABLE		// Enables interrupt output by the RDATERR flag
                       |  MMCA_MRIDXERR_ENABLE		// Enables interrupt output by the RIDXERR flag
                       |  MMCA_MRSPERR_ENABLE		// Enables interrupt output by the RSPERR flag
                       |  MMCA_MCRCSTO_ENABLE		// Enables interrupt output by the CRCSTO flag
                       |  MMCA_MWDATTO_ENABLE		// Enables interrupt output by the WDATTO flag
                       |  MMCA_MRDATTO_ENABLE		// Enables interrupt output by the RDATTO flag
                       |  MMCA_MRBSYTO_ENABLE		// Enables interrupt output by the RBSYTO flag
                       |  MMCA_MRSPTO_ENABLE;		// Enables interrupt output by the RSPTO flag
    
    MMCA_int = mmca_int_function_p;
    
    INTC2.EIC696.BIT.EIMK696 = 0; /* Interrupt processing is enabled. */
}

/**********************************************************************************************************************
* Function Name: R_MMCA_Reset
* Description  : 
* Arguments    : None
* Return Value : None
**********************************************************************************************************************/
void R_MMCA_Reset(void)
{
    /* Store configuration register values before resetting */
    uint32_t tmp_BUFF_ACC  = mmca_p->buf_acc.u32;
    uint32_t tmp_INT_EN    = mmca_p->int_en.u32;
    uint32_t tmp_CLK_CTRL  = mmca_p->clk_ctrl.u32;
    uint32_t tmp_BLOCK_SET = mmca_p->block_set.u32;
    
    mmca_p->swresa.reg.swrst = 1;
    mmca_p->swresa.reg.swrst = 0;
    
    /* Load configuration register values back again */
    mmca_p->buf_acc.u32   = tmp_BUFF_ACC;
    mmca_p->int_en.u32	  = tmp_INT_EN;
    mmca_p->clk_ctrl.u32  = tmp_CLK_CTRL;
    mmca_p->block_set.u32 = tmp_BLOCK_SET;
}

/***********************************************************************************************************************
* Function Name: R_MMCA_SendCommand
* Description  : 
* Arguments    : attr Pointer to a mmca_attributes_t structure.
* Return Value : None
***********************************************************************************************************************/
void R_MMCA_SendCommand(mmca_attributes_t* attr)
{
    mmca_attributes 		= attr;
    mmca_p->arg 			= attr->arg;
    mmca_p->block_set.u32 	= attr->block_set.u32;
    mmca_p->cmd_set.u32 	= attr->cmd_set.u32;
}

/***********************************************************************************************************************
* Function Name: R_MMCA_SetLowSpeed
* Description  : Set MMC module to low speed mode.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MMCA_SetLowSpeed(void)
{
    while (mmca_p->clk_ctrl.reg.mmcbusbsy == 1);  	/* Wait until MMC bus is not busy.  
                                                       Note: When MMC bus is busy, do not set CLKEN bit and 
                                                       the CLKDIV bit of the MMCAnCE_CLK_CTRL register. */
    mmca_p->clk_ctrl.u32 = MMCA_CLEAR_REGISTER;  	// Initialize Clock Control Register
    mmca_p->clk_ctrl.u32 |= MMCA_CLKEN_ENABLE		  // Outputs the MMC clock				(Assuming a 80MHz MMC module clock)
                         |  MMCA_CLKDIV_256			  // MMCA module clock / 256   			(312.5kHz clock will be output)
                         |  MMCA_SRSPTO_256			  // 256 MMC clock cycles					(8.192 mSec for Response timeout)
                         |  MMCA_SRBSYTO_22			  // 2^19 (524288) MMC clock cycles		(1.6777216 Sec for Response busy
                                                  //  timeout)
                         |  MMCA_SRWDTO_22;			  // 2^19 (524288) MMC clock cycles		(1.6777216 Sec for Write data/
                                                  //  read data timeout)
}

/***********************************************************************************************************************
* Function Name: R_MMCA_SetHighSpeed
* Description  : Set MMC module to high speed mode.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MMCA_SetHighSpeed(void)
{
    while (mmca_p->clk_ctrl.reg.mmcbusbsy == 1);  /* Wait until MMC bus is not busy. 
                                                       Note: When MMC bus is busy, do not set CLKEN bit and 
                                                       the CLKDIV bit of the MMCAnCE_CLK_CTRL register. */
    mmca_p->clk_ctrl.u32 = MMCA_CLEAR_REGISTER;		// Initialize Clock Control Register
    mmca_p->clk_ctrl.u32 |= MMCA_CLKEN_ENABLE		  // Outputs the MMC clock 				(Assuming a 80MHz MMC module clock)
                         |  MMCA_CLKDIV_2			    // MMCA module clock / 2   				(40MHz clock will be output)
                         |  MMCA_SRSPTO_256			  // 256 MMC clock cycles					(6.4 uSec for Response timeout)
                         |  MMCA_SRBSYTO_26			  // 2^26 (67108864) MMC clock cycles		(1.6777216 Sec for Response
                                                  //  busy timeout)
                         |  MMCA_SRWDTO_26;			  // 2^26 (67108864) MMC clock cycles		(1.6777216 Sec for Write data/
                                                  //  read data timeout)
    
}

