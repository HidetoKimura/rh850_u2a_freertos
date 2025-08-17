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
#ifndef _R_AT_RAM_IF_H_
#define _R_AT_RAM_IF_H_


#ifdef __cplusplus
extern "C" {
#endif

#define R_RAM_WRITE(SIZE, ADDR, VALUE)  R_DEV_WRITE_REG(SIZE, ADDR, VALUE)
#define R_RAM_READ(SIZE, ADDR)          R_DEV_READ_REG(SIZE, ADDR)

/***********************************************************
  Section: Functions
*/

/***********************************************************
  Function: R_ATF_Ram_Init

  Set base address of RAM for application

  Parameters:
    BaseAddr - base address
    RamSize  - size of all available memory (in Byte)
    
  Returns:
    void
*/
void R_ATF_Ram_Init(uint32_t BaseAddr, uint32_t RamSize);


/***********************************************************
  Function: R_ATF_Ram_Alloc

  Allocate RAM with given size

  Parameters:
    RamSize   - size of memory to be allocated
    
  Returns:
    Begin address of allocated memory
*/
uint32_t R_ATF_Ram_Alloc(uint32_t RamSize);


/***********************************************************
  Function: R_ATF_Ram_NextFreeAddrGet

  Get next free memory address  

  Parameters:
    void
    
  Returns:
    next free memory address
*/
uint32_t R_ATF_Ram_NextFreeAddrGet(void);


/***********************************************************
  Function: R_ATF_Ram_FreeMemSizeGet

  Get size of the remaining free memory 

  Parameters:
    void
    
  Returns:
    size of the free memory (in Byte)
*/
uint32_t R_ATF_Ram_FreeMemSizeGet(void);


/***********************************************************
  Function: R_ATF_Ram_BaseAddrGet

  Get base address of RAM

  Parameters:
    void
    
  Returns:
    base address of RAM
*/
uint32_t R_ATF_Ram_BaseAddrGet(void);



#ifdef __cplusplus
}
#endif

#endif /* _R_AT_RAM_IF_H_ */
