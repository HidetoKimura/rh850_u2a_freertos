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
* File Name        : r_rlin.c
* Component Version: 1.0.0
* Description      : This file implements the RLIN module.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "inc\common.h"
#include "r_rlin.h"

/***********************************************************************************************************************
Public functions
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: R_RLIN31_BaudrateInit
* Description  : Initializes the baudrate for RLIN31.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RLIN31_BaudrateInit(void)
{
  // Force LIN to "reset mode" before setting baudrate
  do{
      RLN31.LCUC.UINT8 = 0x00u;
  }while(RLN31.LMST.UINT8 !=0u );
  
  /* LIN Wake-up Baud Rate Selector register  */
  RLN31.LWBR.UINT8 = 0X01u;
  
  /* LIN Baud Rate Prescaler1 */
  RLN31.LBRP01.UINT8[H] = 0x02;     /* Baudrate = PCLK / (((BRP value) + 1)*(number of samples per bit)) */
  RLN31.LBRP01.UINT8[L] = 0x81;     /* 40MHZ/((129+1)*16)=19200 */
}

/***********************************************************************************************************************
* Function Name: R_RLIN31_Init
* Description  : Initializes the RLIN31 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RLIN31_Init(void)
{
  do{
      RLN31.LCUC.UINT8 = 0x00u;
  }while(RLN31.LMST.UINT8 !=0u );
  
    /* LIN Mode Register */
  RLN31.LMD.UINT8 = 0x00u;    /* LIN System Clock: fa */
  
  /* LIN Break Field Configuration Register */
  RLN31.LBFC.UINT8 = 0x15u;   /* b3-b0=0101: break width 18Tbits; b5b4=01: break delimiter 2Tbit */
  

  
  RLN31.LSC.UINT8 = 0x17u;    /* Inter-byte(header/response) 7Tbits and interbyte 1Tbit */

  RLN31.LWUP.UINT8=0x30u;     /* b7-b4=0100: Wake-up Transmission low width 4 bits */

  RLN31.LIE.UINT8 = 0x03u;    /* Tx/Rx interrupt enabled */
  

  
  /* LIN Error Detection Enable Register */
  RLN31.LEDE.UINT8 = 0x0fu;   /* Enable error detection */
  
  RLN31.LDFC.UINT8 = 0x28u;   /* Enhanced checksum, response field length 8byte + checksum */
  
  /* Reset is cancelled / operating mode is caused */ 
  do
  {
    RLN31.LCUC.UINT8 = 0x03u;
  }while(RLN31.LMST.UINT8 != 0x03u);
}

/*****************************************************************************
** Function:    R_RLIN31_TxFrame
** Description: Transmits Data on Channel 1 of RLIN31.
** Parameter:   TxFrame - Frame to be transmitted
**                  ID - Frame ID
**                  DB - Data Buffer
** Return:      LIN_OK - No error occurred
**              LIN_ERROR - Error occurred
******************************************************************************/
/***********************************************************************************************************************
* Function Name: R_PWMD_Channel66Init
* Description  : Initializes the PWM channel 66.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
uint8_t R_RLIN31_TxFrame(uint8_t ID, uint8_t TxDB[])
{
  uint8_t PB = 0;
  uint8_t err = 0;
  
  /* Only 6 Bits are valid for ID */
  ID &= 0x3Fu;
  
  /* Parity Bit Calculation */
  if(ID&&0x17u)
    {
        PB |= 0x40;
    }
  if(!(ID&&0x3Au))
    {
        PB |= 0x80;
    }
  ID |= PB;
  
  while(RLN31.LTRC.UINT8&&0x03); /* Wait until an ongoing transmission is stopped */
  
  /* Set ID and Parity */
  RLN31.LIDB.UINT8 = ID;

  /* Fill LIN data buffer registers */
  RLN31.LDBR1.UINT8 = TxDB[0];    
  RLN31.LDBR2.UINT8 = TxDB[1];    
  RLN31.LDBR3.UINT8 = TxDB[2];
  RLN31.LDBR4.UINT8 = TxDB[3];
  RLN31.LDBR5.UINT8 = TxDB[4];
  RLN31.LDBR6.UINT8 = TxDB[5];
  RLN31.LDBR7.UINT8 = TxDB[6];
  RLN31.LDBR8.UINT8 = TxDB[7];  
  
  RLN31.LDFC.UINT8 |= 1u<<4;    /* Set mode to transmission */
  RLN31.LTRC.UINT8 |= 0x01u;    /* Set start bit */
  
  while(RLN31.LST.UINT8!=0x81u) /* Wait while frame transmission not completed */
  {    
    if((RLN31.LST.UINT8&8)==8u) /* If error occurred */
    {        
      err = RLN31.LEST.UINT8;
      return RLIN_ERROR;   /* Return error */
    }else{
      err = err; /* set dummy value to avoid Compiler warning */
    }
  }
  return RLIN_OK;
}

/*****************************************************************************
** Function:    R_RLIN31_RxFrame
** Description: Stores Data received on Channel 1 of RLIN31.
** Parameter:   RxDB - Receive Data Buffer
** Return:      LIN_OK - No error occurred
**              LIN_ERROR - Error occurred
**              LIN_NO_MSG - No message received
******************************************************************************/
uint8_t R_RLIN31_RxFrame(uint8_t RxDB[])
{
   
    while(RLN31.LTRC.UINT8&&0x03u); /* Wait until an ongoing transmission is stopped */
    
    if(RLN31.LST.UINT8==0x02u) /* Successful Frame Reception */
        { 
            RxDB[0] = RLN31.LDBR1.UINT8;
            RxDB[1] = RLN31.LDBR2.UINT8;
            RxDB[2] = RLN31.LDBR3.UINT8;
            RxDB[3] = RLN31.LDBR4.UINT8;
            RxDB[4] = RLN31.LDBR5.UINT8;
            RxDB[5] = RLN31.LDBR6.UINT8;
            RxDB[6] = RLN31.LDBR7.UINT8;
            RxDB[7] = RLN31.LDBR8.UINT8;
            
            return RLIN_OK;
        }
    else
        {
            if(RLN31.LST.UINT8==0x08u) /* An error occured */
                {
                    return RLIN_ERROR;
                }
            else
                {
                    return RLIN_NO_MSG;
                }
        }
}

