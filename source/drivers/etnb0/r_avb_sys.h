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

#ifndef AVB_SYS_H_
#define AVB_SYS_H_

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
  Function: R_AVB_SYS_AllocRxMemBuffer

  allocate memory for Rx frames

  Parameters:
    Unit    - Instance number
    MemSize - size of allocated memory

  Returns:
    start address of allocated memory
*/
uint32_t R_AVB_SYS_AllocRxMemBuffer(uint32_t Unit, uint32_t MemSize);
uint32_t R_AVB_SYS_AllocTxMemBuffer(uint32_t Unit, uint32_t MemSize);

/*******************************************************************************
  Function: R_AVB_SYS_ConfigPhy_...

  configure PHY device (reset and initialization)

  Parameters:
    Unit   - Instance number

  Returns:
    void
*/

void R_AVB_SYS_ConfigPhy(uint32_t Unit);
void R_AVB_SYS_ConfigPhy_BroadCom(uint32_t Unit);
void R_AVB_SYS_ConfigPhy_Marvell(uint32_t Unit, r_avb_Speed_t *Speed);
void R_AVB_SYS_ConfigPhy_Marvell_BReach(uint32_t Unit, r_avb_Speed_t* Speed, uint8_t SelfTestLoop); 
void R_AVB_SYS_ReadPhyMarvell( uint32_t Unit, uint32_t *ReadArray );
void R_AVB_SYS_WritePhyMarvell( uint32_t Unit, uint16_t Page, uint16_t Register, uint16_t Value );
void R_AVB_SYS_ConfigPhy_ExLoop( uint32_t Unit );

/*******************************************************************************
  Function: R_AVB_SYS_Read/WritePhy_...

  read/write PHY device (Management register set)

  Parameters:
    RegBase  - Base Address on management bus
    Unit     - Instance number
    Page     - Register page
    Register - Register number
    Value    - Register value

  Returns:
    void
*/

void R_AVB_SYS_ReadPhy( uint8_t RegBase, uint32_t Unit, uint32_t *ReadArray );
void R_AVB_SYS_WritePhy( uint8_t RegBase, uint32_t Unit, uint16_t Page, uint16_t Register, uint16_t Value );

#ifdef __cplusplus
}
#endif


#endif /* AVB_SYS_H_ */
