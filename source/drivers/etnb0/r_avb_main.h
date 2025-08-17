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
#ifndef AVB_MAIN_H_
#define AVB_MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
  Title: AVB Internal Interface

  Only the driver modules shall include this header.
*/

/*******************************************************************************
  Section: Global Defines
*/

#undef  DEF_EXTERN_
#ifndef AVB_MAIN_GLOBALS_
#define DEF_EXTERN_ extern
#else
#define DEF_EXTERN_
#endif


/*******************************************************************************
  Section: Global Types
*/

/*******************************************************************************
  Type: r_avb_Dev_t

  Device instance specific data.

  All instance specific data is kept within that structure.

  Members:
    MacAddr             - MAC address
    BaseAddr            - Avb part base address
    DescTableAddr       - Descriptor table address
    LastTxDesc          - Last tx descriptor address
    NextRxDesc          - Next free rx descriptor address
    RxBufMode           - Reception buffer operation mode
    RxBeTimestamp       - Rx timestamp function status of best effort channel
    RxSTimestamp        - Rx timestamp function status of stream channel
    RxBeQueueBuf        - Rx BE buffer addresses
    RxNcQueueBuf        - Rx NC buffer addresses
    RxSQueueBuf         - Rx stream buffer address
    DescIntEnable       - Descriptor processed interrupt enable
    TxDescIntFlag       - Tx descriptor interrupt flag, value: 0-15, 0 for no interrupt
    RxDescIntFlag       - Rx descriptor interrupt flag, value: 0-15, 0 for no interrupt
    DevStatus           - Device status
    IsrCallback         - Pointer to Isr callback functions
*/
typedef struct {
    uint8_t              MacAddr[6];
    uint32_t             BaseAddr;
    uint32_t             DescTableAddr;
    uint32_t             LastTxDesc[R_AVB_TXQ_NUM];
    uint32_t             NextTxDesc[R_AVB_TXQ_NUM];
    uint32_t             NextRxDesc[R_AVB_RXQ_NUM];
    r_avb_RxBufMode_t    RxBufMode[R_AVB_RXQ_NUM];
    r_avb_Option_t       RxBeTimestamp;
    r_avb_Option_t       RxSTimestamp;
    uint32_t             TxQueueBuf[R_AVB_TXQ_NUM][R_AVB_TXDESC_Q_NUM - 1];
    uint32_t             RxBeQueueBuf[R_AVB_RXDESC_BE_NUM - 1];
    uint32_t             RxNcQueueBuf[R_AVB_RXDESC_NC_NUM - 1];
    uint32_t             RxSQueueBuf[R_AVB_RXSTREAMQ_NUM][R_AVB_RXDESC_S_NUM - 1];
    uint32_t             DescIntEnable[R_AVB_DESCINT_NUM];
    uint32_t             TxDescIntFlag[R_AVB_TXQ_NUM];
    uint32_t             RxDescIntFlag[R_AVB_RXQ_NUM];
    r_avb_OpStatus_t     DevStatus;
    void                 (*IsrCallback[R_AVB_INT_NUM])(void);
} r_avb_Dev_t;


/*******************************************************************************
  Variable: r_avb_Dev

  Array for device instance specific data.
*/

r_avb_Dev_t r_avb_Dev[R_AVB_MACRO_NUM];

uint32_t R_AVB_SYS_AllocRxMemBuffer(uint32_t Unit, uint32_t MemSize);
uint32_t R_AVB_SYS_AllocTxMemBuffer(uint32_t Unit, uint32_t MemSize);
/*******************************************************************************
  Function: R_AVB_CheckMacroParams

  Performs a range check for standard sprite (unit) parameters.
  Calls error handler in case something does not match.

  For unused parameters fill in a 0 there

 Parameters:
  Unit          - Avb Macro instance number

  Returns:
  see: <r_avb_Error_t>

*/
r_avb_Error_t R_AVB_CheckMacroParams(uint32_t Unit);

/*******************************************************************************
  Title: Generic AVB Support Functions

  The generic AVB driver uses these functions. They have
  to be implemented within the driver library for a concrete
  device.
*/

/*******************************************************************************
  Section: Global Functions
*/

/*******************************************************************************
  Function: R_AVB_SYS_BaseAddr

  Returns the base address of dedicated macro unit.

  Parameters:
  Unit       - Instance number

  Returns:
  Macro base address
*/
uint32_t R_AVB_SYS_BaseAddr(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_SYS_IntCInit

  Initialize AVB interrupts

  Parameters:
    Unit   - Instance number

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_SYS_IntCInit(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_SYS_EnableInt

  Enable the interrupt handling for 'Interrupt'.

  Parameters:
  Unit       - Instance number
  Interrupt  - Interrupt type see: <eeavb_Interrupt_t>

  Returns:
  void
*/
void R_AVB_SYS_EnableInt(uint32_t Unit, r_avb_Interrupt_t Interrupt);


/*******************************************************************************
  Function: R_AVB_SYS_DisableInt

  Disable the interrupt handling for 'Interrupt'.

  Parameters:
  Unit       - Instance number
  Interrupt  - Interrupt type see: <eeavb_Interrupt_t>

  Returns:
  void
*/
void R_AVB_SYS_DisableInt(uint32_t Unit, r_avb_Interrupt_t Interrupt);


/*******************************************************************************
  Function: R_AVB_SYS_AllocDescBuffer

  allocate memory for descriptor

  Parameters:
    Unit   - Instance number

  Returns:
    see <r_avb_Error_t>
*/
r_avb_Error_t R_AVB_SYS_AllocDescBuffer(uint32_t Unit);


/*******************************************************************************
  Function: R_AVB_ErrorHandler

  Central error function.

  When the driver detects any error, it will call this function.
  In case there is a registered error callback user function,
  it  will be called. If a user handler is missing an endless loop is entered.

  Parameters:
  Unit       - Instance number
  Error      - Error code, see: <r_avb_Error_t>

  Returns:
  void
*/

void R_AVB_ErrorHandler(uint32_t Unit, r_avb_Error_t Error);


#ifdef __cplusplus
}
#endif

#endif /* AVB_MAIN_H_  */
