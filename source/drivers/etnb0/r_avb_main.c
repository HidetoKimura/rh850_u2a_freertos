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
#include "inc\common.h"
#include "r_typedefs.h"
#include "r_config_avb.h"
#include "r_avb_api.h"
//#include "r_avb_sys.h"
#include "r_avb_regs.h"
#include "r_avb_main.h"
#include "r_at_ram_if.h"

#define EE_ETNB_MDIO_DELAY            ( 100 ) 
/*******************************************************************************
  Section: Local Constants
*/

/*******************************************************************************
  Constant: loc_AvbVersion

  A string containig the macro driver version information
*/
static const int8_t  loc_AvbDrvVer[] = R_VERSION(AVB, R_AVB_VERSION_HI, R_AVB_VERSION_LO);



/*******************************************************************************
  Section: Local Variables
*/

/*******************************************************************************
  Variable: loc_ErrorHandler

  A function pointer to a user callback (Applications error handler)

  The value is assigned by the application using the driver
*/
static void (*loc_ErrorHandler )(uint32_t Unit, uint32_t Error) = 0u;


/***********************************************************
  Section: Local functions
*/

/***********************************************************
  Function: loc_OpModeGet

  Get avb operation mode

  Parameters:
    Unit  - Instance number

  Returns:
    see <r_avb_OpStatus_t>
*/
static r_avb_OpStatus_t loc_OpModeGet(uint32_t Unit) {
    r_avb_OpStatus_t opmode;
    r_avb_Csr_t   csr;

    csr.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CSR);
    switch (csr.Bit.Ops) {
        case 1: opmode = R_AVB_RESET;
                break;

        case 2: opmode = R_AVB_CONFIG;
                break;

        case 4: opmode = R_AVB_OPERATION;
                break;

        case 8: opmode = R_AVB_STANDBY;
                break;

        default:break;
    }

    return opmode;
}


/***********************************************************
  Function: loc_CommonConfig

  Common configuration

  Parameters:
    Unit      - Instance number
    ComConfig - see <r_avb_ComConfig_t>

  Returns:
    void
*/
static void loc_CommonConfig(uint32_t Unit, r_avb_ComConfig_t *ComConfig) {
    r_avb_Ccc_t ccc;

    ccc.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CCC);
    ccc.Bit.Lbme = ComConfig->Lbme;
    ccc.Bit.Boc  = ComConfig->Boc;
    ccc.Bit.Csel = ComConfig->Csel;
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CCC, ccc.Word);
}


/***********************************************************
  Function: loc_RxMemAlloc

  Allocate buffer memory for Rx queues

  Parameters:
    Unit  - Instance number

  Returns:
    void
*/
static void loc_RxMemAlloc(uint32_t Unit) {
    int i, j;
    uint32_t addr;

    addr = R_AVB_SYS_AllocRxMemBuffer(Unit, (R_AVB_RXDESC_BE_NUM - 1) * R_AVB_VLFRAME_SIZE);

    /* buffer for Rx BE queue */
    for (i = 0; i < R_AVB_RXDESC_BE_NUM - 1; i++) {
        r_avb_Dev[Unit].RxBeQueueBuf[i] = addr;
        addr += R_AVB_VLFRAME_SIZE;
    }

    addr = R_AVB_SYS_AllocRxMemBuffer(Unit, (R_AVB_RXDESC_NC_NUM - 1) * R_AVB_VLFRAME_SIZE);

    /* buffer for Rx NC queue */
    for (i = 0; i < R_AVB_RXDESC_NC_NUM - 1; i++) {
        r_avb_Dev[Unit].RxNcQueueBuf[i] = addr;
        addr += R_AVB_VLFRAME_SIZE;
    }

    addr = R_AVB_SYS_AllocRxMemBuffer(Unit, R_AVB_RXSTREAMQ_NUM * (R_AVB_RXDESC_S_NUM - 1) * R_AVB_VLFRAME_SIZE);

    /* buffer for Rx stream queue */
    for (i = 0; i < R_AVB_RXSTREAMQ_NUM; i++) {
        for (j = 0; j < R_AVB_RXDESC_S_NUM - 1; j++) {
            r_avb_Dev[Unit].RxSQueueBuf[i][j] = addr;
            addr += R_AVB_VLFRAME_SIZE;
        }
    }
}


static void loc_TxMemAlloc(uint32_t Unit) {
    int i,j;
    uint32_t addr;

    addr = R_AVB_SYS_AllocTxMemBuffer(Unit, R_AVB_TXQ_NUM*(R_AVB_TXDESC_Q_NUM - 1) * R_AVB_VLFRAME_SIZE);

    /* buffer for Tx 0 queue */
    for (i = 0; i < R_AVB_TXQ_NUM; i++) {
    for (j = 0; j < R_AVB_TXDESC_Q_NUM - 1; j++) {
        r_avb_Dev[Unit].TxQueueBuf[i][j] = addr;
        addr += R_AVB_VLFRAME_SIZE;
    }
    }

   
}


/***********************************************************
  Function: loc_DescConfig

  Configure descriptor

  Parameters:
    Unit   - Instance number

  Returns:
    void
*/
static void loc_DescConfig(uint32_t Unit) {
    int i, j;
    uint32_t chainaddr;
    r_avb_LinkDesc_t   *linkaddr;
    r_avb_DataDesc_t   *datadesc;
    r_avb_ExtDataDesc_t *extdatadesc;

    /* init tx descriptor */
    linkaddr = (r_avb_LinkDesc_t *)(r_avb_Dev[Unit].DescTableAddr);

    /* Tx Queues */
    for (i = 0; i < R_AVB_TXQ_NUM; i++) {
        chainaddr = linkaddr->Dptr;
        r_avb_Dev[Unit].NextTxDesc[i]=(uint32_t)chainaddr;
        datadesc  = (r_avb_DataDesc_t *)(chainaddr);

        for (j = 0; j < R_AVB_TXDESC_Q_NUM; j++) {
            if (j == R_AVB_TXDESC_Q_NUM - 1) {
                datadesc->Header.Dt   = R_AVB_DESC_LINKFIX;
                datadesc->Header.Die  = 0;
                datadesc->Header.Ctrl = 0;
                datadesc->Header.Ds   = 0;
                datadesc->Dptr        = chainaddr;
            } else {
                datadesc->Header.Dt   = R_AVB_DESC_FEMPTY;
                datadesc->Header.Die  = 0;
                datadesc->Header.Ctrl = 0;
                datadesc->Header.Ds   = 0;
                datadesc->Dptr        = r_avb_Dev[Unit].TxQueueBuf[i][j];
                datadesc ++;
            }
        }
        linkaddr ++;
    }

    /* Rx Queues */
        /* BE Queue */
    chainaddr = linkaddr->Dptr;

    if (r_avb_Dev[Unit].RxBeTimestamp == R_AVB_DISABLE) {
        /* timestamp for best effor disabled */
        datadesc  = (r_avb_DataDesc_t *)(chainaddr);
        r_avb_Dev[Unit].NextRxDesc[R_AVB_BECHANNEL] = (uint32_t)datadesc;

        for (i = 0; i < R_AVB_RXDESC_BE_NUM; i++) {
            if (i == R_AVB_RXDESC_BE_NUM - 1) {
                datadesc->Header.Dt   = R_AVB_DESC_LINKFIX;
                datadesc->Header.Die  = 0;
                datadesc->Header.Ctrl = 0;
                datadesc->Header.Ds   = 0;
                datadesc->Dptr        = chainaddr;
            } else {
                datadesc->Header.Dt   = R_AVB_DESC_FEMPTY;
                datadesc->Header.Die  = 0;
                datadesc->Header.Ctrl = 0;
                datadesc->Header.Ds   = R_AVB_VLFRAME_SIZE;
                datadesc->Dptr        = r_avb_Dev[Unit].RxBeQueueBuf[i];
                datadesc ++;
            }
        }
    } else {
        /* timestamp for best effort enabled */
        extdatadesc  = (r_avb_ExtDataDesc_t *)(chainaddr);
        r_avb_Dev[Unit].NextRxDesc[R_AVB_BECHANNEL] = (uint32_t)extdatadesc;

        for (i = 0; i < R_AVB_RXDESC_BE_NUM; i++) {
            if (i == R_AVB_RXDESC_BE_NUM - 1) {
                datadesc = (r_avb_DataDesc_t *)extdatadesc;
                datadesc->Header.Dt   = R_AVB_DESC_LINKFIX;
                datadesc->Header.Die  = 0;
                datadesc->Header.Ctrl = 0;
                datadesc->Header.Ds   = 0;
                datadesc->Dptr        = chainaddr;
            } else {
                extdatadesc->Header.Dt   = R_AVB_DESC_FEMPTY;
                extdatadesc->Header.Die  = 0;
                extdatadesc->Header.Ctrl = 0;
                extdatadesc->Header.Ds   = R_AVB_VLFRAME_SIZE;
                extdatadesc->Dptr        = r_avb_Dev[Unit].RxBeQueueBuf[i];
                extdatadesc->Timestamp.Timestamp0 = 0;
                extdatadesc->Timestamp.Timestamp1 = 0;
                extdatadesc->Timestamp.Timestamp2 = 0;
                extdatadesc ++;
            }
        }
    }
    linkaddr ++;

        /* NC Queue */
    chainaddr = linkaddr->Dptr;
    extdatadesc  = (r_avb_ExtDataDesc_t *)(chainaddr);
    r_avb_Dev[Unit].NextRxDesc[R_AVB_NCCHANNEL] = (uint32_t)extdatadesc;

    for (i = 0; i < R_AVB_RXDESC_NC_NUM; i++) {
        if (i == R_AVB_RXDESC_NC_NUM - 1) {
            datadesc = (r_avb_DataDesc_t *)extdatadesc;
            datadesc->Header.Dt   = R_AVB_DESC_LINKFIX;
            datadesc->Header.Die  = 0;
            datadesc->Header.Ctrl = 0;
            datadesc->Header.Ds   = 0;
            datadesc->Dptr        = chainaddr;
        } else {
            extdatadesc->Header.Dt   = R_AVB_DESC_FEMPTY;
            extdatadesc->Header.Die  = 0;
            extdatadesc->Header.Ctrl = 0;
            extdatadesc->Header.Ds   = R_AVB_VLFRAME_SIZE;
            extdatadesc->Dptr        = r_avb_Dev[Unit].RxNcQueueBuf[i];
            extdatadesc->Timestamp.Timestamp0 = 0;
            extdatadesc->Timestamp.Timestamp1 = 0;
            extdatadesc->Timestamp.Timestamp2 = 0;
            extdatadesc ++;
        }
    }
    linkaddr ++;

        /* Rx Stream Queues */
    if (r_avb_Dev[Unit].RxSTimestamp == R_AVB_DISABLE) {
        /* timestamp disabled */
        for (i = 0; i < R_AVB_RXSTREAMQ_NUM; i++) {
            chainaddr  = linkaddr->Dptr;
            datadesc = (r_avb_DataDesc_t *)(chainaddr);
            r_avb_Dev[Unit].NextRxDesc[i + 2] = (uint32_t)datadesc;

            for (j = 0; j < R_AVB_RXDESC_S_NUM; j++) {
                if (j == R_AVB_RXDESC_S_NUM - 1) {
                    datadesc->Header.Dt   = R_AVB_DESC_LINKFIX;
                    datadesc->Header.Die  = 0;
                    datadesc->Header.Ctrl = 0;
                    datadesc->Header.Ds   = 0;
                    datadesc->Dptr        = chainaddr;
                } else {
                    datadesc->Header.Dt   = R_AVB_DESC_FEMPTY;
                    datadesc->Header.Die  = 0;
                    datadesc->Header.Ctrl = 0;
                    datadesc->Header.Ds   = R_AVB_VLFRAME_SIZE;
                    datadesc->Dptr        = r_avb_Dev[Unit].RxSQueueBuf[i][j];
                    datadesc ++;
                }
            }
            linkaddr ++;
        }
    } else {
        /* timestamp enabled */
        for (i = 0; i < R_AVB_RXSTREAMQ_NUM; i++) {
            chainaddr  = linkaddr->Dptr;
            extdatadesc = (r_avb_ExtDataDesc_t *)(chainaddr);
            r_avb_Dev[Unit].NextRxDesc[i + 2] = (uint32_t)extdatadesc;

            for (j = 0; j < R_AVB_RXDESC_S_NUM; j++) {
                if (j == R_AVB_RXDESC_S_NUM - 1) {
                    datadesc = (r_avb_DataDesc_t *)extdatadesc;
                    datadesc->Header.Dt   = R_AVB_DESC_LINKFIX;
                    datadesc->Header.Die  = 0;
                    datadesc->Header.Ctrl = 0;
                    datadesc->Header.Ds   = 0;
                    datadesc->Dptr        = chainaddr;

                } else {
                    extdatadesc->Header.Dt   = R_AVB_DESC_FEMPTY;
                    extdatadesc->Header.Die  = 0;
                    extdatadesc->Header.Ctrl = 0;
                    extdatadesc->Header.Ds   = R_AVB_VLFRAME_SIZE;
                    extdatadesc->Dptr        = r_avb_Dev[Unit].RxSQueueBuf[i][j];
                    extdatadesc->Timestamp.Timestamp0 = 0;
                    extdatadesc->Timestamp.Timestamp1 = 0;
                    extdatadesc->Timestamp.Timestamp2 = 0;
                    extdatadesc ++;
                }
            }
            linkaddr ++;
        }
    }
}


/*******************************************************************************
  Function: loc_DescUpdate

  update descriptor chain (without timestamp support)

  Parameters:
    Unit     - Instance number
    DescPtr  - pointer to descriptor to be updated
    ChConfig - see <r_avb_RxChConfig_t>

  Returns:
    last descriptor address
*/
static uint32_t loc_DescUpdate(uint32_t Unit, uint32_t DescPtr, r_avb_RxChConfig_t *ChConfig) {
    uint32_t             descint;
    r_avb_DataDesc_t    *datadesc;

    datadesc = (r_avb_DataDesc_t *)DescPtr;

    switch (r_avb_Dev[Unit].RxBufMode[ChConfig->ChNum]) {
    case R_AVB_RX_SFSB:     /* single buffer single frame */
        datadesc->Header.Dt   = R_AVB_DESC_FEMPTY;
        if (r_avb_Dev[Unit].DescIntEnable[R_AVB_RXDESCINT_OFFSET + ChConfig->ChNum] == 1) {
            descint = r_avb_Dev[Unit].RxDescIntFlag[ChConfig->ChNum];
        } else {
            descint = 0;
        }

        datadesc->Header.Die  = descint;
        datadesc->Header.Ctrl = 0;
        datadesc->Header.Ds   = R_AVB_BFRAME_SIZE;
        break;

    case R_AVB_RX_SFMB:     /* single buffer multi frame */
        /* MAC header */
        datadesc->Header.Dt   = R_AVB_DESC_FEMPTY;
        if (r_avb_Dev[Unit].DescIntEnable[R_AVB_RXDESCINT_OFFSET + ChConfig->ChNum] == 1) {
            descint = r_avb_Dev[Unit].RxDescIntFlag[ChConfig->ChNum];
        } else {
            descint = 0;
        }

        datadesc->Header.Die  = descint;
        datadesc->Header.Ctrl = 0;
        datadesc->Header.Ds   = R_AVB_NORMALMAC_HSIZE;

        datadesc++;
        while ((datadesc->Header.Dt == R_AVB_DESC_LINKFIX) || (datadesc->Header.Dt == R_AVB_DESC_LINK)) {
            datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
        }

        /* payload header */
        datadesc->Header.Dt   = R_AVB_DESC_FEMPTY;
        datadesc->Header.Die  = descint;
        datadesc->Header.Ctrl = 0;
        datadesc->Header.Ds   = ChConfig->PHLength;

        datadesc++;
        while ((datadesc->Header.Dt == R_AVB_DESC_LINKFIX) || (datadesc->Header.Dt == R_AVB_DESC_LINK)) {
            datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
        }

        /* payload */
        datadesc->Header.Dt   = R_AVB_DESC_FEMPTY;
        datadesc->Header.Die  = descint;
        datadesc->Header.Ctrl = 0;
        datadesc->Header.Ds   = ChConfig->PLength;
        break;
    }

    return (uint32_t)datadesc;
}


/*******************************************************************************
  Function: loc_DescTsUpdate

  update descriptor chain (without timestamp support)

  Parameters:
    Unit     - Instance number
    DescPtr  - pointer to descriptor to be updated
    ChConfig - see <r_avb_RxChConfig_t>

  Returns:
    last descriptor address
*/
static uint32_t loc_DescTsUpdate(uint32_t Unit, uint32_t DescPtr, r_avb_RxChConfig_t *ChConfig) {
    uint32_t             descint;
    r_avb_ExtDataDesc_t *extdatadesc;

    extdatadesc = (r_avb_ExtDataDesc_t *)DescPtr;

    switch (r_avb_Dev[Unit].RxBufMode[ChConfig->ChNum]) {
    case R_AVB_RX_SFSB:     /* single buffer single frame */
        extdatadesc->Header.Dt   = R_AVB_DESC_FEMPTY;
        if (r_avb_Dev[Unit].DescIntEnable[R_AVB_RXDESCINT_OFFSET + ChConfig->ChNum] == 1) {
            descint = r_avb_Dev[Unit].RxDescIntFlag[ChConfig->ChNum];
        } else {
            descint = 0;
        }

        extdatadesc->Header.Die  = descint;
        extdatadesc->Header.Ctrl = 0;
        extdatadesc->Header.Ds   = R_AVB_VLFRAME_SIZE;
        extdatadesc->Timestamp.Timestamp0 = 0;
        extdatadesc->Timestamp.Timestamp1 = 0;
        extdatadesc->Timestamp.Timestamp2 = 0;
        break;

    case R_AVB_RX_SFMB:     /* single buffer multi frame */
        /* MAC header */
        extdatadesc->Header.Dt   = R_AVB_DESC_FEMPTY;
        if (r_avb_Dev[Unit].DescIntEnable[R_AVB_RXDESCINT_OFFSET + ChConfig->ChNum] == 1) {
            descint = r_avb_Dev[Unit].RxDescIntFlag[ChConfig->ChNum];
        } else {
            descint = 0;
        }

        extdatadesc->Header.Die  = descint;
        extdatadesc->Header.Ctrl = 0;
        extdatadesc->Header.Ds   = R_AVB_VLANMAC_HSIZE;
        extdatadesc->Timestamp.Timestamp0 = 0;
        extdatadesc->Timestamp.Timestamp1 = 0;
        extdatadesc->Timestamp.Timestamp2 = 0;

        extdatadesc++;
        while ((extdatadesc->Header.Dt == R_AVB_DESC_LINKFIX) || (extdatadesc->Header.Dt == R_AVB_DESC_LINK)) {
            extdatadesc = (r_avb_ExtDataDesc_t *)extdatadesc->Dptr;
        }

        /* payload header */
        extdatadesc->Header.Dt   = R_AVB_DESC_FEMPTY;
        extdatadesc->Header.Die  = descint;
        extdatadesc->Header.Ctrl = 0;
        extdatadesc->Header.Ds   = ChConfig->PHLength;
        extdatadesc->Timestamp.Timestamp0 = 0;
        extdatadesc->Timestamp.Timestamp1 = 0;
        extdatadesc->Timestamp.Timestamp2 = 0;

        extdatadesc++;
        while ((extdatadesc->Header.Dt == R_AVB_DESC_LINKFIX) || (extdatadesc->Header.Dt == R_AVB_DESC_LINK)) {
            extdatadesc = (r_avb_ExtDataDesc_t *)extdatadesc->Dptr;
        }

        /* payload */
        extdatadesc->Header.Dt   = R_AVB_DESC_FEMPTY;
        extdatadesc->Header.Die  = descint;
        extdatadesc->Header.Ctrl = 0;
        extdatadesc->Header.Ds   = ChConfig->PLength;
        extdatadesc->Timestamp.Timestamp0 = 0;
        extdatadesc->Timestamp.Timestamp1 = 0;
        extdatadesc->Timestamp.Timestamp2 = 0;
        break;
    }

    return (uint32_t)extdatadesc;
}



/*******************************************************************************
  Section: Global Functions
*/

/*******************************************************************************
  Function: R_AVB_CheckMacroParams

  See: <avb_main.h>
*/
r_avb_Error_t R_AVB_CheckMacroParams(uint32_t Unit) {
    /* Feel free to add any more usefull parameter checks */
    if (R_AVB_MACRO_NUM <= Unit)
    {
        return  R_AVB_ERR_RANGE;
    }
    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_ErrorHandler

  See: <avb_main.h>
*/
void R_AVB_ErrorHandler(uint32_t Unit, r_avb_Error_t Error) {
    if (0 != loc_ErrorHandler)
    {      /* we've got a registered error handler here ...*/
        loc_ErrorHandler(Unit, (uint32_t) Error);      /* ... and we gonna use it!*/
    }
    else
    {
        for(;;)
        {        /* we don't have a handler */
        }        /* so, let's wait here */
    }
}


/*******************************************************************************
  Section: Global API Functions

  See: <avb_api.h>
*/

/*******************************************************************************
  Function: R_AVB_GetVersionStr
*/
const int8_t * R_AVB_GetVersionStr(void) {
    return (const int8_t *) loc_AvbDrvVer;
}


/*******************************************************************************
  Function: R_AVB_GetMajorVersion
*/
uint16_t R_AVB_GetMajorVersion(void) {
    return R_AVB_VERSION_HI;
}


/*******************************************************************************
  Function: R_AVB_GetMinorVersion
*/
uint16_t R_AVB_GetMinorVersion(void) {
    return R_AVB_VERSION_LO;
}


/*******************************************************************************
  Function: R_AVB_Init
*/
r_avb_Error_t R_AVB_Init(uint32_t Unit, r_avb_Config_t *AvbConfig, r_avb_MacConfig_t *MacConfig) {
    int i;
    r_avb_Error_t err;

    err = R_AVB_CheckMacroParams(Unit);

    if (R_AVB_ERR_OK != err) {
        return err;
    }

    if (0 == r_avb_Dev[Unit].BaseAddr) {
        r_avb_Dev[Unit].DevStatus = R_AVB_OpModeGet(Unit);

        r_avb_Dev[Unit].BaseAddr = R_AVB_SYS_BaseAddr(Unit);

        for (i = 0; i < 6; i++) {
            r_avb_Dev[Unit].MacAddr[i] = MacConfig->MacAddr[i];
        }

        /* initialize descriptor processed interrupt status */
        for (i = 0; i < R_AVB_DESCINT_NUM; i++) {
            r_avb_Dev[Unit].DescIntEnable[i] = 0;
        }

        /* change operation mode to config */
        R_AVB_OpModeChange(Unit, R_AVB_CONFIG);
        loc_CommonConfig(Unit, AvbConfig->ComConfig);

        /* configure Error interrupt mask*/
        R_AVB_ErrIntMaskSet(Unit, AvbConfig->ErrorInt);

        /* config reception part */
        R_AVB_RxSet(Unit, AvbConfig->RxConfig);

        /* config transmission part */
        R_AVB_TxSet(Unit, AvbConfig->TxConfig);

        /* config message handler */
        r_avb_Dev[Unit].DescTableAddr = AvbConfig->BufBaseAddr;
        if (R_AVB_SYS_AllocDescBuffer(Unit) != R_AVB_ERR_OK) {
            return R_AVB_ERR_NG;
        }
        R_AVB_DescTableBaseSet(Unit, r_avb_Dev[Unit].DescTableAddr);

        /* prepare descriptor and buffer */
        loc_RxMemAlloc(Unit);
        loc_TxMemAlloc(Unit);
        loc_DescConfig(Unit);   /* configure descriptor chain */

        /* config MAC */
        R_AVB_MacInit(Unit, MacConfig);

        /* init interrupt */
        //R_AVB_SYS_IntCInit(Unit);

        err = R_AVB_ERR_OK;

    } else {
        /* please, no double-init*/
        err = R_AVB_ERR_LOCKED;
    }

    return err;
}


/*******************************************************************************
  Function: R_AVB_DeInit
*/
r_avb_Error_t R_AVB_DeInit(uint32_t Unit) {
    r_avb_Error_t err;

    err = R_AVB_CheckMacroParams(Unit);

    if (R_AVB_ERR_OK  != err) {
        return err;
    }
    if (0 != r_avb_Dev[Unit].BaseAddr) {
        r_avb_Dev[Unit].BaseAddr = 0;
        
    } else {
        /* nothing to do at this point of time  */
        err = R_AVB_ERR_NOTLOCKED;
    }
    return err;
}


/***********************************************************
  Function: R_AVB_OpModeChange
*/
r_avb_Error_t R_AVB_OpModeChange(uint32_t Unit, r_avb_OpStatus_t Mode) {
    r_avb_Csr_t csr;
    r_avb_Ccc_t ccc;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if (r_avb_Dev[Unit].DevStatus != Mode) {
        if (r_avb_Dev[Unit].DevStatus == R_AVB_OPERATION) {
            ccc.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CCC);
            ccc.Bit.Dtsr = 1;
            R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CCC, ccc.Word);

            do {
                csr.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CSR);
            } while (!csr.Bit.Dts);
        }

        ccc.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CCC);
        ccc.Bit.Opc = Mode;
        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CCC, ccc.Word);

        do {
            csr.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CSR);
            csr.Bit.Ops >>= Mode;
        } while (!(csr.Bit.Ops));

        r_avb_Dev[Unit].DevStatus = Mode;
        return R_AVB_ERR_OK;

    } else {
        return R_AVB_ERR_OPMODE;
    }
}


/*******************************************************************************
  Function: R_AVB_OpModeGet
*/
r_avb_OpStatus_t R_AVB_OpModeGet(uint32_t Unit) {
    r_avb_OpStatus_t opmode;
    r_avb_Csr_t      csr;

    csr.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CSR);
    switch (csr.Bit.Ops) {
        case 1: opmode = R_AVB_RESET;
                break;

        case 2: opmode = R_AVB_CONFIG;
                break;

        case 4: opmode = R_AVB_OPERATION;
                break;

        case 8: opmode = R_AVB_STANDBY;
                break;

        default:break;
    }

    return opmode;
}


/*******************************************************************************
  Function: R_AVB_TxStatusGet
*/
uint8_t R_AVB_TxStatusGet(uint32_t Unit) {
    uint8_t        txstatus;
    r_avb_Csr_t csr;

    csr.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CSR);
    txstatus = (uint8_t)((csr.Word >> 16) & 0xf);

    return txstatus;
}


/*******************************************************************************
  Function: R_AVB_RxStatusGet
*/
uint8_t R_AVB_RxStatusGet(uint32_t Unit) {
    uint8_t     rxstatus;
    r_avb_Csr_t csr;

    csr.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CSR);
    rxstatus = (uint8_t)(csr.Bit.Rpo);

    return rxstatus;
}





/*******************************************************************************
  Function: R_AVB_GPtpTimeCapSrcSel
*/
r_avb_Error_t R_AVB_GPtpTimeCapSrcSel(uint32_t Unit, r_avb_TCapSrc_t TCapSrc) {
    uint32_t val;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
    if ((val & 0x3) != 0) {
        return R_AVB_ERR_NG;
    } else {
        val |= (TCapSrc << 8);
        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR, val);
    }

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_GPtpMaxTxTimeSet
*/
r_avb_Error_t R_AVB_GPtpMaxTxTimeSet(uint32_t Unit, uint32_t MaxTime) {
    uint32_t val;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }
    if (R_AVB_OpModeGet(Unit) == R_AVB_OPERATION) {
        val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
        if (val & 0x20) {
            return R_AVB_ERR_NG;
        }
    }

    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GMTT, MaxTime);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_GPtpMaxTxTimeLoad
*/
r_avb_Error_t R_AVB_GPtpMaxTxTimeLoad(uint32_t Unit) {
    uint32_t val;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
    val |= (1 << 5);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR, val);

    do {
        val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
    } while (val & 0x20);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_GPtpTimerIncSet
*/
r_avb_Error_t R_AVB_GPtpTimerIncSet(uint32_t Unit, uint32_t Increment) {
    uint32_t val;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }
    if (R_AVB_OpModeGet(Unit) == R_AVB_OPERATION) {
        val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
        if (val & 0x8) {
            return R_AVB_ERR_NG;
        }
    }

    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GTI, Increment);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_GPtpTimerIncLoad
*/
r_avb_Error_t R_AVB_GPtpTimerIncLoad(uint32_t Unit) {
    uint32_t val;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
    val |= (1 << 3);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR, val);

    do {
        val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
    } while (val & 0x8);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_GPtpTimerOffsetSet
*/
r_avb_Error_t R_AVB_GPtpTimerOffsetSet(uint32_t Unit, r_avb_TimeStamp_t *Offset) {
    uint32_t val;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }
    if (R_AVB_OpModeGet(Unit) == R_AVB_OPERATION) {
        val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
        if (val & 0x4) {
            return R_AVB_ERR_NG;
        }
    }

    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GTO0, Offset->Timestamp0);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GTO1, Offset->Timestamp1);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GTO2, Offset->Timestamp2);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_GPtpTimerOffsetLoad
*/
r_avb_Error_t R_AVB_GPtpTimerOffsetLoad(uint32_t Unit) {
    uint32_t val;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
    val |= (1 << 2);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR, val);

    do {
        val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
    } while (val & 0x4);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_PresTimeCompSet
*/
r_avb_Error_t R_AVB_PresTimeCompSet(uint32_t Unit, uint32_t CompTime) {
    uint32_t val;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }
    if (R_AVB_OpModeGet(Unit) == R_AVB_OPERATION) {
        val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
        if (val & 0x10) {
            return R_AVB_ERR_NG;
        }
    }

    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GPTC, CompTime);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_PresTimeCompLoad
*/
r_avb_Error_t R_AVB_PresTimeCompLoad(uint32_t Unit) {
    uint32_t val;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
    val |= (1 << 4);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR, val);

    do {
        val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
    } while (val & 0x10);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_GPtpTimeCapture
*/
r_avb_Error_t R_AVB_GPtpTimeCapture(uint32_t Unit, r_avb_TimeStamp_t *Time) {
    uint32_t    val;
    r_avb_Ccc_t ccc;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
    ccc.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CCC);

    if (((val & 0x3) == 0) && (ccc.Bit.Csel != 0) && (R_AVB_OpModeGet(Unit) == R_AVB_OPERATION)) {
        val |= 3;
        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR, val);

        do {
            val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
        } while ((val & 0x3) != 0);

        Time->Timestamp0 = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCT0);
        Time->Timestamp1 = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCT1);
        Time->Timestamp2 = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCT2);

    } else {
        return R_AVB_ERR_NG;
    }

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_GPtpTimerReset
*/
r_avb_Error_t R_AVB_GPtpTimerReset(uint32_t Unit) {
    uint32_t    val;
    r_avb_Ccc_t ccc;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
    ccc.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CCC);

    if (((val & 0x3) == 0) && (ccc.Bit.Csel != 0) && (loc_OpModeGet(Unit) == R_AVB_OPERATION)) {
        val |= 1;
        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR, val);
    } else {
        return R_AVB_ERR_NG;
    }

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_SwPresTimeCapture
*/
uint32_t R_AVB_SwPresTimeCapture(uint32_t Unit) {
    uint32_t    prestime;
    uint32_t    val;
    r_avb_Ccc_t ccc;

    prestime = 0;
    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
    ccc.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CCC);

    if (((val & 0x3) == 0) && (ccc.Bit.Csel != 0) && (R_AVB_OpModeGet(Unit) == R_AVB_OPERATION)) {
        val |= 3;
        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR, val);

        do {
            val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCCR);
        } while ((val & 0x3) != 0);

        prestime = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCT0);
    }

    return prestime;
}


/*******************************************************************************
  Function: R_AVB_HwPresTimeCapture
*/
uint32_t R_AVB_HwPresTimeCapture(uint32_t Unit) {
    uint32_t intstatus;
    uint32_t prestime;

    prestime = 0;
    intstatus = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GIS);

    if (intstatus & R_AVB_GPTPPRESTIME_CAP) {
        prestime = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GCPT);
    }

    return prestime;
}


/*******************************************************************************
  Function: R_AVB_DescTableBaseSet
*/
r_avb_Error_t R_AVB_DescTableBaseSet(uint32_t Unit, uint32_t BaseAddr) {
    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    } else if (R_AVB_OpModeGet(Unit) != R_AVB_CONFIG) {
        return R_AVB_ERR_OPMODE;
    } else {
        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_DBAT, BaseAddr);
    }
    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_QBaseAddrLoad
*/
r_avb_Error_t R_AVB_QBaseAddrLoad(uint32_t Unit, uint8_t QIndex) {
    uint32_t index = 0;
    uint32_t tccr_tsrq;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }
    
    if (r_avb_Dev[Unit].DevStatus == R_AVB_OPERATION) {
        if (QIndex < (R_AVB_TXQ_NUM + R_AVB_RXQ_NUM)) {
            if (QIndex < R_AVB_TXQ_NUM) {
                tccr_tsrq = (uint8_t)(R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TCCR) & 0xf);
                if (tccr_tsrq == 0) {
                    index = 1 << QIndex;
                    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_DLR, index);
                }
            } else {
                index = 1 << QIndex;
                R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_DLR, index);
            }
        }
    }
    
    return R_AVB_ERR_OK;
    
}


/*******************************************************************************
  Function: R_AVB_CurrentDescGet
*/
uint32_t R_AVB_CurrentDescGet(uint32_t Unit, uint8_t QIndex, r_avb_TxRxOption_t Option) {
    uint32_t descaddr;

    if (Option == R_AVB_TX) {
        if (QIndex > 3) {
            descaddr = 0;
        } else {
            descaddr = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CDARBASE + QIndex * 4);
        }
    } else {
        if (QIndex > 18) {
            descaddr = 0;
        } else {
            descaddr = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CDARBASE + (QIndex + 4) * 4);
        }
    }

    return descaddr;
}


/*******************************************************************************
  Function: R_AVB_RxSet
*/
r_avb_Error_t R_AVB_RxSet(uint32_t Unit, r_avb_RxConfig_t *RxConfig) {
    r_avb_Rcr_t rcr;
    
    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if (r_avb_Dev[Unit].DevStatus == R_AVB_CONFIG) {
        rcr.Word = 0;
        rcr.Bit.Effs = RxConfig->Effs;
        rcr.Bit.Encf = RxConfig->Encf;
        rcr.Bit.Esf  = RxConfig->Esf;
        rcr.Bit.Ets0 = RxConfig->Ets0;
        rcr.Bit.Ets2 = RxConfig->Ets2;
        rcr.Bit.Rfcl = RxConfig->Rfcl;

        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_RCR, rcr.Word);
    }

    r_avb_Dev[Unit].RxBeTimestamp = RxConfig->Ets0;
    r_avb_Dev[Unit].RxSTimestamp = RxConfig->Ets2;
    
    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_RxQueueSet
*/
r_avb_Error_t R_AVB_RxQueueSet(uint32_t Unit, r_avb_QConfig_t *QConfig, uint32_t QIndex) {
    uint32_t config;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if ((r_avb_Dev[Unit].DevStatus == R_AVB_CONFIG) && (QIndex < 18)) {
        config = (((QConfig->Rsm) << ((QIndex % 4) * 8)) |
                 ((QConfig->Tsel) << ((QIndex % 4) * 8 + 2)) |
                 ((QConfig->Ufcc) << ((QIndex % 4) * 8 + 4)));

        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_RQCBASE + (QIndex / 4) * 4, config);
        return R_AVB_ERR_OK;
    } else {
        return R_AVB_ERR_OPMODE;
    }
}


/*******************************************************************************
  Function: R_AVB_RxPaddingSet
*/
r_avb_Error_t R_AVB_RxPaddingSet(uint32_t Unit, r_avb_PaddingConfig_t *Padding) {
    uint32_t val;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if (r_avb_Dev[Unit].DevStatus == R_AVB_CONFIG) {
        val = (Padding->Dcnt << 16) | (Padding->Pcnt << 8);

        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_RPC, val);
        return R_AVB_ERR_OK;
    } else {
        return R_AVB_ERR_OPMODE;
    }
}


/*******************************************************************************
  Function: R_AVB_RxTruncSet
*/
r_avb_Error_t R_AVB_RxTruncSet(uint32_t Unit, r_avb_TruncConfig_t *Trunc) {
    uint32_t val;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if (r_avb_Dev[Unit].DevStatus == R_AVB_CONFIG) {
        val = ((Trunc->Mfl1) << 16) | (Trunc->Mfl0);

        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_RTCBASE, val);
        return R_AVB_ERR_OK;
    } else {
        return R_AVB_ERR_OPMODE;
    }
}


/*******************************************************************************
  Function: R_AVB_UFWarningLevelSet
*/
r_avb_Error_t R_AVB_UFWarningLevelSet(uint32_t Unit, uint8_t WarningValue, uint8_t ConfigNum) {
    r_avb_Ufcwcs_t ufcw;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if (r_avb_Dev[Unit].DevStatus == R_AVB_CONFIG) {
        ufcw.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_UFCW);

        switch(ConfigNum) {
            case 0: ufcw.Bit.WlSl0 = WarningValue;
                    break;

            case 1: ufcw.Bit.WlSl1 = WarningValue;
                    break;

            case 2: ufcw.Bit.WlSl2 = WarningValue;
                    break;

            case 3: ufcw.Bit.WlSl3 = WarningValue;
                    break;

            default: break;
        }

        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_UFCW, ufcw.Word);

        return R_AVB_ERR_OK;
    } else {
        return R_AVB_ERR_OPMODE;
    }
}


/*******************************************************************************
  Function: R_AVB_UFStopLevelSet
*/
r_avb_Error_t R_AVB_UFStopLevelSet(uint32_t Unit, uint8_t StopValue, uint8_t ConfigNum) {
    r_avb_Ufcwcs_t ufcs;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if (r_avb_Dev[Unit].DevStatus == R_AVB_CONFIG) {
        ufcs.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_UFCS);

        switch(ConfigNum) {
            case 0: ufcs.Bit.WlSl0 = StopValue;
                    break;

            case 1: ufcs.Bit.WlSl1 = StopValue;
                    break;

            case 2: ufcs.Bit.WlSl2 = StopValue;
                    break;

            case 3: ufcs.Bit.WlSl3 = StopValue;
                    break;

            default: break;
        }

        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_UFCS, ufcs.Word);

        return R_AVB_ERR_OK;
    } else {
        return R_AVB_ERR_OPMODE;
    }
}


/*******************************************************************************
  Function: R_AVB_UFCounterGet
*/
uint32_t R_AVB_UFCounterGet(uint32_t Unit, uint32_t QIndex) {
    uint32_t  ufcv;
    uint32_t  count;

    ufcv =  R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_UFCVBASE + QIndex / 4);
    count = (ufcv >> ((QIndex % 4) * 8)) & 0x3f;

    return count;
}


/*******************************************************************************
  Function: R_AVB_UFCounterDec
*/
r_avb_Error_t R_AVB_UFCounterDec(uint32_t Unit, uint32_t DecCount, uint32_t QIndex) {
    uint32_t cnt;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if ((DecCount <= 0x3F) && (QIndex < 18)) {
        cnt = DecCount << ((QIndex % 4) * 8);
         R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_UFCDBASE + QIndex / 4, cnt);

        return R_AVB_ERR_OK;
    } else {
        return R_AVB_ERR_NG;
    }
}


/*******************************************************************************
  Function: R_AVB_RxFilterSet
*/
r_avb_Error_t R_AVB_RxFilterSet(uint32_t Unit, r_avb_SepFilter_t *SepFilter) {
    uint32_t regoffset;
    
    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if (r_avb_Dev[Unit].DevStatus == R_AVB_CONFIG) {
        /* offset */
        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_SFO, SepFilter->Offset);

        /* pattern */
        if (SepFilter->QIndex < 16) {
            regoffset = (SepFilter->QIndex * 2) * 4;
            R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_SFPBASE + regoffset, SepFilter->LPattern);
            R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_SFPBASE + regoffset + 4, SepFilter->HPattern);
        } else {
            return R_AVB_ERR_NG;
        }

        /* mask */
        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_SFMBASE, SepFilter->LMask);
        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_SFMBASE + 4, SepFilter->HMask);

        return R_AVB_ERR_OK;
    } else {
        return R_AVB_ERR_OPMODE;
    }
}


/*******************************************************************************
  Function: R_AVB_RxDescChainConfig
*/
r_avb_Error_t R_AVB_RxDescChainConfig(uint32_t Unit, r_avb_RxChConfig_t *ChConfig) {
    r_avb_LinkDesc_t     *linkaddr;
    r_avb_DataDesc_t     *datadesc;
    r_avb_ExtDataDesc_t  *extdatadesc;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if (ChConfig->ChNum > R_AVB_RXQ_NUM - 1) {
        return R_AVB_ERR_INVNUM;
    }

    linkaddr = (r_avb_LinkDesc_t *)(r_avb_Dev[Unit].DescTableAddr);
    linkaddr += (R_AVB_RXBEQ_OFFSET + ChConfig->ChNum);

    r_avb_Dev[Unit].RxBufMode[ChConfig->ChNum] = ChConfig->BufMode;
    r_avb_Dev[Unit].NextRxDesc[ChConfig->ChNum] = (uint32_t)(linkaddr->Dptr);

    if (ChConfig->ChNum == R_AVB_BECHANNEL) {
        /* best effort channel */
        if (r_avb_Dev[Unit].RxBeTimestamp == R_AVB_DISABLE) {
            datadesc = (r_avb_DataDesc_t *)r_avb_Dev[Unit].NextRxDesc[ChConfig->ChNum];
            do {
                datadesc = (r_avb_DataDesc_t *)R_AVB_RxDescChainUpdate(Unit, (uint32_t)datadesc, ChConfig);
                datadesc++;
            } while (datadesc->Header.Dt != R_AVB_DESC_LINKFIX);
        } else {
            extdatadesc = (r_avb_ExtDataDesc_t *)r_avb_Dev[Unit].NextRxDesc[ChConfig->ChNum];
            do {
                extdatadesc = (r_avb_ExtDataDesc_t *)R_AVB_RxDescChainUpdate(Unit, (uint32_t)extdatadesc, ChConfig);
                extdatadesc++;
            } while (extdatadesc->Header.Dt != R_AVB_DESC_LINKFIX);
        }

    } else if (ChConfig->ChNum == R_AVB_NCCHANNEL) {
        /* network control channel */
        extdatadesc = (r_avb_ExtDataDesc_t *)r_avb_Dev[Unit].NextRxDesc[ChConfig->ChNum];
        do {
            extdatadesc = (r_avb_ExtDataDesc_t *)R_AVB_RxDescChainUpdate(Unit, (uint32_t)extdatadesc, ChConfig);
            extdatadesc++;
        } while (extdatadesc->Header.Dt != R_AVB_DESC_LINKFIX);

    } else {
        /* stream channel */
        if (r_avb_Dev[Unit].RxSTimestamp == R_AVB_DISABLE) {
            datadesc = (r_avb_DataDesc_t *)r_avb_Dev[Unit].NextRxDesc[ChConfig->ChNum];
            do {
                datadesc = (r_avb_DataDesc_t *)R_AVB_RxDescChainUpdate(Unit, (uint32_t)datadesc, ChConfig);
                datadesc++;
            } while (datadesc->Header.Dt != R_AVB_DESC_LINKFIX);
        } else {
            extdatadesc = (r_avb_ExtDataDesc_t *)r_avb_Dev[Unit].NextRxDesc[ChConfig->ChNum];
            do {
                extdatadesc = (r_avb_ExtDataDesc_t *)R_AVB_RxDescChainUpdate(Unit, (uint32_t)extdatadesc, ChConfig);
                extdatadesc++;
            } while (extdatadesc->Header.Dt != R_AVB_DESC_LINKFIX);
        }
    }

    /* reload desc. base address */
    R_AVB_QBaseAddrLoad(Unit, ChConfig->ChNum + R_AVB_RXBEQ_OFFSET);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_RxDescChainUpdate
*/
uint32_t R_AVB_RxDescChainUpdate(uint32_t Unit, uint32_t DescPtr, r_avb_RxChConfig_t *ChConfig) {
    uint32_t lastdesc;

    switch (ChConfig->ChType) {
    default:
    case R_AVB_RX_BE:
        if (r_avb_Dev[Unit].RxBeTimestamp == R_AVB_DISABLE) {
            lastdesc = loc_DescUpdate(Unit, DescPtr, ChConfig);
        } else {
            lastdesc = loc_DescTsUpdate(Unit, DescPtr, ChConfig);
        }
        break;

    case R_AVB_RX_S:
        if (r_avb_Dev[Unit].RxSTimestamp == R_AVB_DISABLE) {
            lastdesc = loc_DescUpdate(Unit, DescPtr, ChConfig);
        } else {
            lastdesc = loc_DescTsUpdate(Unit, DescPtr, ChConfig);
        }
        break;

    case R_AVB_RX_NC:
        lastdesc = loc_DescTsUpdate(Unit, DescPtr, ChConfig);
        break;
    }

    return lastdesc;

}


/*******************************************************************************
  Function: R_AVB_TxSet
*/
r_avb_Error_t R_AVB_TxSet(uint32_t Unit, r_avb_TxConfig_t *TxConfig) {
    r_avb_Tgc_t tgc;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if (r_avb_Dev[Unit].DevStatus != R_AVB_CONFIG) {
        return R_AVB_ERR_OPMODE;

    } else {
        tgc.Word = 0;
        tgc.Bit.Tsm0 = TxConfig->Tsm0;
        tgc.Bit.Tsm1 = TxConfig->Tsm1;
        tgc.Bit.Tsm2 = TxConfig->Tsm2;
        tgc.Bit.Tsm3 = TxConfig->Tsm3;
        tgc.Bit.Tqp  = TxConfig->Tqp;
        tgc.Bit.Tbd0 = 2;
        tgc.Bit.Tbd1 = 2;
        tgc.Bit.Tbd2 = 2;
        tgc.Bit.Tbd3 = 2;

        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TGC, tgc.Word);
        return R_AVB_ERR_OK;
    }
}


/*******************************************************************************
  Function: R_AVB_TxReqStart
*/
r_avb_Error_t R_AVB_TxReqStart(uint32_t Unit, uint32_t QIndex) {
    r_avb_Tccr_t tccr;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if (QIndex > 3) {
        return R_AVB_ERR_NG;
    }

    tccr.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TCCR);
    tccr.Word |= (1 << QIndex);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TCCR, tccr.Word);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_MacStatusFifoSet
*/
r_avb_Error_t R_AVB_MacStatusFifoSet(uint32_t Unit, r_avb_Option_t Option) {
    r_avb_Tccr_t tccr;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    tccr.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TCCR);
    tccr.Bit.Mfen = Option;
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TCCR, tccr.Word);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_TimestampFifoSet
*/
r_avb_Error_t R_AVB_TimestampFifoSet(uint32_t Unit, r_avb_Option_t Option) {
    r_avb_Tccr_t tccr;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    tccr.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TCCR);
    tccr.Bit.Tfen = Option;
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TCCR, tccr.Word);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_MacStatusFifoGet
*/
r_avb_Error_t R_AVB_MacStatusFifoGet(uint32_t Unit, r_avb_MACStatusFifo_t *MacStatus) {
     r_avb_Mfa_t mfa;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if (R_AVB_MacStatusFifoLevelGet(Unit) == 0) {
        MacStatus->Valid       = 0;
        MacStatus->StatusTag   = 0;
        MacStatus->StatusValue = 0;
    } else {
        mfa.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_MFA);
        MacStatus->Valid       = 1;
        MacStatus->StatusTag   = mfa.Bit.Mst;
        MacStatus->StatusValue = mfa.Bit.Msv;
    }

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_MacStatusFifoLevelGet
*/
uint32_t R_AVB_MacStatusFifoLevelGet(uint32_t Unit) {
    uint32_t val;

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TSR);
    val = (val >> 16) & 0x1f;

    return val;
}


/*******************************************************************************
  Function: R_AVB_MacStatusFifoRelease
*/
r_avb_Error_t R_AVB_MacStatusFifoRelease(uint32_t Unit) {
    r_avb_Tccr_t tccr;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    tccr.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TCCR);
    tccr.Bit.Mfr = 1;
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TCCR, tccr.Word);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_TimestampFifoGet
*/
r_avb_Error_t R_AVB_TimestampFifoGet(uint32_t Unit, r_avb_TSFifo_t *Timestamp) {
    uint32_t val = 0;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if (R_AVB_TimestampFifoLevelGet(Unit) == 0) {
        Timestamp->Valid = 0;
        Timestamp->Tag   = 0;
        (Timestamp->Timestamp).Timestamp0 = 0;
        (Timestamp->Timestamp).Timestamp1 = 0;
        (Timestamp->Timestamp).Timestamp2 = 0;
    } else {
        val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TFA2);
        Timestamp->Valid = 1;
        Timestamp->Tag   = (uint16_t)((val >> 16) & 0x3ff);
        (Timestamp->Timestamp).Timestamp0 = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TFA0);
        (Timestamp->Timestamp).Timestamp1 = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TFA1);
        (Timestamp->Timestamp).Timestamp2 = (uint16_t)(val & 0xffff);
    }

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_TimestampFifoLevelGet
*/
uint32_t R_AVB_TimestampFifoLevelGet(uint32_t Unit) {
    uint32_t val;

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TSR);
    val = (val >> 8) & 0x7;

    return val;
}


/*******************************************************************************
  Function: R_AVB_TimestampFifoRelease
*/
r_avb_Error_t R_AVB_TimestampFifoRelease(uint32_t Unit) {
    r_avb_Tccr_t tccr;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    tccr.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TCCR);
    tccr.Bit.Tfr = 1;
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TCCR, tccr.Word);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_CbsCntStatusGet
*/
r_avb_Error_t R_AVB_CbsCntStatusGet(uint32_t Unit, r_avb_CBSCntStatus_t *CbsStatus, r_avb_CBSCntClass_t QClass) {
    uint32_t val;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TSR);
    *CbsStatus = (r_avb_CBSCntStatus_t)((val >> (QClass * 2)) & 0x3);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_CbsParamSet
*/
r_avb_Error_t R_AVB_CbsParamSet(uint32_t Unit, r_avb_CbsParam_t *Param, r_avb_CBSCntClass_t QClass) {
    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if ((Param->CbsInc > 0xffff) || (Param->CbsDec < 0xffff0000)) {
        return R_AVB_ERR_INVNUM;
    }

    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CIVRBASE + QClass * 4, Param->CbsInc);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CDVRBASE + QClass * 4, Param->CbsDec);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CULBASE + QClass * 4,  Param->CbsUppLimit);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_CLLBASE + QClass * 4,  Param->CbsLowLimit);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_ErrStatusGet
*/
void R_AVB_ErrStatusGet(uint32_t Unit, r_avb_ErrStatus_t *ErrStatus) {
    r_avb_Esr_t    status;

    status.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_ESR);

    ErrStatus->ErrLost = status.Bit.Eil;
    ErrStatus->ErrQueueNum = status.Bit.Eqn;
    ErrStatus->ErrType = status.Bit.Et;
}


/*******************************************************************************
  Function: R_AVB_DescIntMaskSet
*/
r_avb_Error_t R_AVB_DescIntMaskSet(uint32_t Unit, uint32_t IntNum, r_avb_Option_t Option) {
    uint32_t val;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    if ((IntNum > 0) && (IntNum < 16)) {
        val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_DIC);

        if (Option == R_AVB_ENABLE) {
            val |= (1 << IntNum);
            R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_DIC, val);
        } else {
            val &= (~(1 << IntNum));
            R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_DIC, val);
        }

        r_avb_Dev[Unit].DescIntEnable[IntNum-1] = Option;
    } else {
        return R_AVB_ERR_INVNUM;
    }

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_DescIntGet
*/
uint32_t R_AVB_DescIntGet(uint32_t Unit) {
    uint32_t val;

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_DIS);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_DIS, 0);

    return val;
}


/***********************************************************
  Function: R_AVB_ErrIntMaskSet
*/
r_avb_Error_t R_AVB_ErrIntMaskSet(uint32_t Unit, r_avb_ErrorInt_t *Mask) {
    r_avb_Eic_t eic;

    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    eic.Word = 0;
    eic.Bit.Mree  = Mask->Mree;
    eic.Bit.Mtee  = Mask->Mtee;
    eic.Bit.Qee   = Mask->Qee;
    eic.Bit.See   = Mask->See;
    eic.Bit.Clle0 = Mask->Clle0;
    eic.Bit.Clle1 = Mask->Clle1;
    eic.Bit.Cule0 = Mask->Cule0;
    eic.Bit.Cule1 = Mask->Cule1;
    eic.Bit.Tffe  = Mask->Tffe;
    eic.Bit.Mffe  = Mask->Mffe;

    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_EIC, eic.Word);

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_ErrIntGet
*/
uint32_t R_AVB_ErrIntGet(uint32_t Unit) {
    uint32_t errint;

    errint = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_EIS);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_EIS, 0);

    return errint;
}


/*******************************************************************************
  Function: R_AVB_RxIntMaskSet
*/
r_avb_Error_t R_AVB_RxIntMaskSet(uint32_t Unit, uint32_t Mask) {
    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_RIC0, Mask & 0x3ffff);
    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_RxIntGet
*/
uint32_t R_AVB_RxIntGet(uint32_t Unit) {
    uint32_t val;

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_RIS0);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_RIS0, ~val);

    return val;
}


/*******************************************************************************
  Function: R_AVB_RxWarningIntMaskSet
*/
r_avb_Error_t R_AVB_RxWarningIntMaskSet(uint32_t Unit, uint32_t Mask) {
    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_RIC1, Mask & 0x8003ffff);
    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_RxWarningIntGet
*/
uint32_t R_AVB_RxWarningIntGet(uint32_t Unit) {
    uint32_t val;

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_RIS1);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_RIS1, 0);
    val &= 0x8003ffff;

    return val;
}


/*******************************************************************************
  Function: R_AVB_RxQFullIntMaskSet
*/
r_avb_Error_t R_AVB_RxQFullIntMaskSet(uint32_t Unit, uint32_t Mask) {
    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_RIC2, Mask & 0x8003ffff);
    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_RxQFullIntGet
*/
uint32_t R_AVB_RxQFullIntGet(uint32_t Unit) {
    uint32_t val;

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_RIS2);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_RIS2, 0);
    val &= 0x8003ffff;

    return val;
}


/*******************************************************************************
  Function: R_AVB_TxIntMaskSet
*/
r_avb_Error_t R_AVB_TxIntMaskSet(uint32_t Unit, uint32_t Mask) {
    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TIC, Mask & 0x00000f0f);
    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_TxIntGet
*/
uint32_t R_AVB_TxIntGet(uint32_t Unit) {
    uint32_t val;

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TIS);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TIS, ~(val & 0xf));
    val &= 0xf0f;

    return val;
}


/*******************************************************************************
  Function: R_AVB_TxMacStatusFifoIntGet
*/
uint32_t R_AVB_TxMacStatusFifoIntGet(uint32_t Unit) {
    uint32_t val;

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TIS);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TIS, ~val);
    val &= 0xc00;

    return val;
}


/*******************************************************************************
  Function: R_AVB_TxTSFifoIntGet
*/
uint32_t R_AVB_TxTSFifoIntGet(uint32_t Unit) {
    uint32_t val;

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TIS);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_TIS, ~val);
    val &= 0x300;

    return val;
}


/*******************************************************************************
  Function: R_AVB_GPtpIntMaskSet
*/
r_avb_Error_t R_AVB_GPtpIntMaskSet(uint32_t Unit, uint32_t Mask) {
    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GIC, Mask & 0x7);
    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_GPtpIntGet
*/
uint32_t R_AVB_GPtpIntGet(uint32_t Unit) {
    uint32_t val;

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GIS);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GIS, 0);
    val &= 0x7;

    return val;
}


/*******************************************************************************
  Function: R_AVB_IntSummaryGet
*/
uint32_t R_AVB_IntSummaryGet(uint32_t Unit) {
    uint32_t val;

    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_ISS);
    val &= 0xfffe3fc7;

    return val;
}


/*******************************************************************************
  Function: R_AVB_SetErrorCallback
*/
void R_AVB_SetErrorCallback(void(*ErrorCallback )(uint32_t Unit, uint32_t Error))
{
    loc_ErrorHandler = ErrorCallback;
}


/*******************************************************************************
  Function: loc_RxBeProcess

  process best effort queue

  Parameters:
    Unit       - Instance number
    RxFramePtr - pointer to rx frame

  Returns:
    void
*/
static void loc_RxBeProcess(uint32_t Unit, uint32_t RxFramePtr, uint32_t DescPtr) {
    r_avb_DataDesc_t     *datadesc;
    r_avb_ExtDataDesc_t  *extdatadesc;

    if (r_avb_Dev[Unit].RxBufMode[R_AVB_BECHANNEL] == R_AVB_RX_SFSB) {
        /* single frame single buffer */
        if (r_avb_Dev[Unit].RxBeTimestamp == R_AVB_ENABLE) {
            /* timestamp enabled */
            extdatadesc = (r_avb_ExtDataDesc_t *)DescPtr;

            if ((extdatadesc->Header).Dt == R_AVB_DESC_FSINGLE) {
                /* descriptor type correct */
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameAddr   = extdatadesc->Dptr;
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameLength = (extdatadesc->Header).Ds;
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->Timestamp   = extdatadesc->Timestamp;

            } else {
                /* descriptor type incorrect */
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameAddr   = 0;
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameLength = 0;
            }

            extdatadesc++;
            while (((extdatadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((extdatadesc->Header).Dt == R_AVB_DESC_LINK)) {
                extdatadesc = (r_avb_ExtDataDesc_t *)extdatadesc->Dptr;
            }

            r_avb_Dev[Unit].NextRxDesc[R_AVB_BECHANNEL] = (uint32_t)extdatadesc;

        } else {
            /* timestamp disabled */
            datadesc = (r_avb_DataDesc_t *)DescPtr;
            
            if ((datadesc->Header).Dt == R_AVB_DESC_FSINGLE) {
                /* descriptor type correct */
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameAddr   = datadesc->Dptr;
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameLength = (datadesc->Header).Ds;
            } else {
                /* descriptor type incorrect */
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameAddr   = 0;
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameLength = 0;
            }

            datadesc++;
            while (((datadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((datadesc->Header).Dt == R_AVB_DESC_LINK)) {
                datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
            }

            r_avb_Dev[Unit].NextRxDesc[R_AVB_BECHANNEL] = (uint32_t)datadesc;
        }
    } else {
        /* single frame multi buffer */
        if (r_avb_Dev[Unit].RxBeTimestamp == R_AVB_ENABLE) {
            /* timestamp enabled */
            extdatadesc = (r_avb_ExtDataDesc_t *)DescPtr;

            if ((extdatadesc->Header).Dt == R_AVB_DESC_FSTART) {
                /* start of frame */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHeader  = extdatadesc->Dptr;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHLength = (extdatadesc->Header).Ds;

                extdatadesc++;
                while (((extdatadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((extdatadesc->Header).Dt == R_AVB_DESC_LINK)) {
                    extdatadesc = (r_avb_ExtDataDesc_t *)extdatadesc->Dptr;
                }

                /* middle or end of frame */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHeader  = extdatadesc->Dptr;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHLength = (extdatadesc->Header).Ds;

                extdatadesc++;
                while (((extdatadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((extdatadesc->Header).Dt == R_AVB_DESC_LINK)) {
                    extdatadesc = (r_avb_ExtDataDesc_t *)extdatadesc->Dptr;
                }

                /* end of frame */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHeader  = extdatadesc->Dptr;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHLength = (extdatadesc->Header).Ds;

                /* timestamp */
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->Timestamp   = extdatadesc->Timestamp;

            } else {
                /* frame type incorrect */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHeader   = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHLength  = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHeader    = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHLength   = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlData      = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlDLength   = 0;
            }

            extdatadesc++;
            while (((extdatadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((extdatadesc->Header).Dt == R_AVB_DESC_LINK)) {
                extdatadesc = (r_avb_ExtDataDesc_t *)extdatadesc->Dptr;
            }

            r_avb_Dev[Unit].NextRxDesc[R_AVB_BECHANNEL] = (uint32_t)extdatadesc;

        } else {
            /* timestamp disabled */
            datadesc = (r_avb_DataDesc_t *)DescPtr;

            if ((datadesc->Header).Dt == R_AVB_DESC_FSTART) {
                /* start of frame */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHeader  = datadesc->Dptr;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHLength = (datadesc->Header).Ds;

                datadesc++;
                while (((datadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((datadesc->Header).Dt == R_AVB_DESC_LINK)) {
                    datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
                }

                /* middle of frame */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHeader  = datadesc->Dptr;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHLength = (datadesc->Header).Ds;

                datadesc++;
                while (((datadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((datadesc->Header).Dt == R_AVB_DESC_LINK)) {
                    datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
                }

                /* end of frame */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlData    = datadesc->Dptr;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlDLength = (datadesc->Header).Ds;

            } else {
                /* descriptor type incorrect */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHeader   = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHLength  = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHeader    = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHLength   = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlData      = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlDLength   = 0;
            }

            datadesc++;
            while ((datadesc->Header.Dt == R_AVB_DESC_LINKFIX) || (datadesc->Header.Dt == R_AVB_DESC_LINK)) {
                datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
            }

            r_avb_Dev[Unit].NextRxDesc[R_AVB_BECHANNEL] = (uint32_t)datadesc;
        }
    }
}


/*******************************************************************************
  Function: loc_RxNcProcess

  process network control queue

  Parameters:
    Unit       - Instance number
    RxFramePtr - pointer to rx frame

  Returns:
    void
*/
static void loc_RxNcProcess(uint32_t Unit, uint32_t RxFramePtr, uint32_t DescPtr) {
    r_avb_ExtDataDesc_t  *extdatadesc;

    if (r_avb_Dev[Unit].RxBufMode[R_AVB_NCCHANNEL] == R_AVB_RX_SFSB) {
        /* single frame single buffer */
        extdatadesc = (r_avb_ExtDataDesc_t *)DescPtr;

        if ((extdatadesc->Header).Dt == R_AVB_DESC_FSINGLE) {
            /* descriptor type correct */
            ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameAddr   = extdatadesc->Dptr;
            ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameLength = (extdatadesc->Header).Ds;
            ((r_avb_RxSingleFrame_t *)RxFramePtr)->Timestamp   = extdatadesc->Timestamp;
        } else {
            /* descriptor type incorrect */
            ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameAddr   = 0;
            ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameLength = 0;
        }

        extdatadesc++;
        while (((extdatadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((extdatadesc->Header).Dt == R_AVB_DESC_LINK)) {
            extdatadesc = (r_avb_ExtDataDesc_t *)extdatadesc->Dptr;
        }

        r_avb_Dev[Unit].NextRxDesc[R_AVB_NCCHANNEL] = (uint32_t)extdatadesc;

    } else {
        /* single frame multi buffer */
        extdatadesc = (r_avb_ExtDataDesc_t *)DescPtr;

        if ((extdatadesc->Header).Dt == R_AVB_DESC_FSTART) {
            /* start of frame */
            ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHeader  = extdatadesc->Dptr;
            ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHLength = (extdatadesc->Header).Ds;

            extdatadesc++;
            while (((extdatadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((extdatadesc->Header).Dt == R_AVB_DESC_LINK)) {
                extdatadesc = (r_avb_ExtDataDesc_t *)extdatadesc->Dptr;
            }

            /* middle of frame */
            ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHeader  = extdatadesc->Dptr;
            ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHLength = (extdatadesc->Header).Ds;

            extdatadesc++;
            while (((extdatadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((extdatadesc->Header).Dt == R_AVB_DESC_LINK)) {
                extdatadesc = (r_avb_ExtDataDesc_t *)extdatadesc->Dptr;
            }

            /* end of frame */
            ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlData    = extdatadesc->Dptr;
            ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlDLength = (extdatadesc->Header).Ds;

        } else {
            /* descriptor type incorrect */
            ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHeader   = 0;
            ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHLength  = 0;
            ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHeader    = 0;
            ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHLength   = 0;
            ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlData      = 0;
            ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlDLength   = 0;
        }

        extdatadesc++;
        while ((extdatadesc->Header.Dt == R_AVB_DESC_LINKFIX) || (extdatadesc->Header.Dt == R_AVB_DESC_LINK)) {
            extdatadesc = (r_avb_ExtDataDesc_t *)extdatadesc->Dptr;
        }

        r_avb_Dev[Unit].NextRxDesc[R_AVB_NCCHANNEL] = (uint32_t)extdatadesc;
    }
}


/*******************************************************************************
  Function: loc_RxSProcess

  process stream queue

  Parameters:
    Unit       - Instance number
    RxFramePtr - pointer to rx frame
    ChannelNum - stream channel number

  Returns:
    void
*/
static void loc_RxSProcess(uint32_t Unit, uint32_t RxFramePtr, uint32_t ChannelNum, uint32_t DescPtr) {
    r_avb_DataDesc_t     *datadesc;
    r_avb_ExtDataDesc_t  *extdatadesc;

    if (r_avb_Dev[Unit].RxBufMode[ChannelNum] == R_AVB_RX_SFSB) {
        /* single frame single buffer */
        if (r_avb_Dev[Unit].RxBeTimestamp == R_AVB_ENABLE) {
            /* timestamp enabled */
            extdatadesc = (r_avb_ExtDataDesc_t *)DescPtr;

            if ((extdatadesc->Header).Dt == R_AVB_DESC_FSINGLE) {
                /* descriptor type correct */
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameAddr   = extdatadesc->Dptr;
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameLength = (extdatadesc->Header).Ds;
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->Timestamp   = extdatadesc->Timestamp;
            } else {
                /* descriptor type incorrect */
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameAddr   = 0;
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameLength = 0;
            }

            extdatadesc++;
            while (((extdatadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((extdatadesc->Header).Dt == R_AVB_DESC_LINK)) {
                extdatadesc = (r_avb_ExtDataDesc_t *)extdatadesc->Dptr;
            }

            r_avb_Dev[Unit].NextRxDesc[ChannelNum] = (uint32_t)extdatadesc;

        } else {
            /* timestamp disabled */
            datadesc = (r_avb_DataDesc_t *)DescPtr;

            if ((datadesc->Header).Dt == R_AVB_DESC_FSINGLE) {
                /* descriptor type correct */
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameAddr   = datadesc->Dptr;
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameLength = (datadesc->Header).Ds;
            } else {
                /* descriptor type incorrect */
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameAddr   = 0;
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->FrameLength = 0;
            }

            datadesc++;
            while (((datadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((datadesc->Header).Dt == R_AVB_DESC_LINK)) {
                datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
            }

            r_avb_Dev[Unit].NextRxDesc[ChannelNum] = (uint32_t)datadesc;
        }

    } else {
        /* single frame multi buffer */
        if (r_avb_Dev[Unit].RxBeTimestamp == R_AVB_ENABLE) {
            /* timestamp enabled */
            extdatadesc = (r_avb_ExtDataDesc_t *)DescPtr;

            if ((extdatadesc->Header).Dt == R_AVB_DESC_FSTART) {
                /* start of frame */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHeader  = extdatadesc->Dptr;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHLength = (extdatadesc->Header).Ds;

                extdatadesc++;
                while (((extdatadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((extdatadesc->Header).Dt == R_AVB_DESC_LINK)) {
                    extdatadesc = (r_avb_ExtDataDesc_t *)extdatadesc->Dptr;
                }

                /* middle or end of frame */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHeader  = extdatadesc->Dptr;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHLength = (extdatadesc->Header).Ds;

                extdatadesc++;
                while (((extdatadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((extdatadesc->Header).Dt == R_AVB_DESC_LINK)) {
                    extdatadesc = (r_avb_ExtDataDesc_t *)extdatadesc->Dptr;
                }

                /* end of frame */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHeader  = extdatadesc->Dptr;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHLength = (extdatadesc->Header).Ds;

                /* timestamp */
                ((r_avb_RxSingleFrame_t *)RxFramePtr)->Timestamp   = extdatadesc->Timestamp;

            } else {
                /* descriptor type incorrect */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHeader   = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHLength  = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHeader    = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHLength   = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlData      = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlDLength   = 0;
            }

        } else {
            /* timestamp disabled */
            datadesc = (r_avb_DataDesc_t *)DescPtr;

            if ((datadesc->Header).Dt == R_AVB_DESC_FSTART) {
                /* start of frame */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHeader  = datadesc->Dptr;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHLength = (datadesc->Header).Ds;

                datadesc++;
                while (((datadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((datadesc->Header).Dt == R_AVB_DESC_LINK)) {
                    datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
                }

                /* middle of frame */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHeader  = datadesc->Dptr;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHLength = (datadesc->Header).Ds;

                datadesc++;
                while (((datadesc->Header).Dt == R_AVB_DESC_LINKFIX) || ((datadesc->Header).Dt == R_AVB_DESC_LINK)) {
                    datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
                }

                /* end of frame */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlData    = datadesc->Dptr;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlDLength = (datadesc->Header).Ds;

            } else {
                /* descriptor type incorrect */
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHeader   = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->MacHLength  = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHeader    = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlHLength   = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlData      = 0;
                ((r_avb_RxMultiFrame_t *)RxFramePtr)->PlDLength   = 0;
            }

            datadesc++;
            while ((datadesc->Header.Dt == R_AVB_DESC_LINKFIX) || (datadesc->Header.Dt == R_AVB_DESC_LINK)) {
                datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
            }

            r_avb_Dev[Unit].NextRxDesc[R_AVB_BECHANNEL] = (uint32_t)datadesc;
        }
    }
}


/*******************************************************************************
  Section: Global Functions
*/


r_avb_Error_t R_AVB_SingleDescGetNextFreeTxBuffer(uint32_t Unit, uint32_t QIndex, r_avb_TxSingleFrame_t *Frame) {
    r_avb_DataDesc_t *datadesc;
    datadesc = (r_avb_DataDesc_t *) r_avb_Dev[Unit].NextTxDesc[QIndex];

    while ((datadesc->Header.Dt == R_AVB_DESC_LINKFIX) || (datadesc->Header.Dt == R_AVB_DESC_LINK)) {
        datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
    }

    if(datadesc->Header.Dt==R_AVB_DESC_FEMPTY)
    {
        Frame->Address=datadesc->Dptr;
        Frame->Length=R_AVB_VLFRAME_SIZE;
        return R_AVB_ERR_OK;
    }
    else
    {
        Frame->Address=0;
        Frame->Length=0;
        return R_AVB_ERR_NG;
    }
    

}

/*******************************************************************************
  Function: R_AVB_SingleDescFrameSend
*/
r_avb_Error_t R_AVB_SingleDescFrameSend(uint32_t Unit, uint32_t QIndex, r_avb_TxSingleFrame_t *Frame) {
    r_avb_DataDesc_t *datadesc;
    r_avb_TxRxCtrl_t  txctrl;
   
    datadesc = (r_avb_DataDesc_t *)r_avb_Dev[Unit].NextTxDesc[QIndex];


    while ((datadesc->Header.Dt == R_AVB_DESC_LINKFIX) || (datadesc->Header.Dt == R_AVB_DESC_LINK)) {
        datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
    }

    if(datadesc->Header.Dt!=R_AVB_DESC_FEMPTY)
    {
        return R_AVB_ERR_NG;
    }
    txctrl.Word = 0;

    if (Frame->Timestamp == R_AVB_ENABLE) {
        txctrl.TxCtrl.Tsr = 1;
    }

    if (Frame->MacStatus == R_AVB_ENABLE) {
        txctrl.TxCtrl.Msr = 1;
    }
    
    /* build the descriptor */
    
    if (r_avb_Dev[Unit].DescIntEnable[QIndex] == 1) {
        datadesc->Header.Die  = r_avb_Dev[Unit].TxDescIntFlag[QIndex];
    } else {
        datadesc->Header.Die  = 0;
    }
    
    if(datadesc->Dptr  != Frame->Address)
    {
        return R_AVB_ERR_NG;
    }
    
    datadesc->Header.Ctrl = txctrl.Word;
    datadesc->Header.Ds   = Frame->Length;
    datadesc->Header.Dt   = R_AVB_DESC_FSINGLE;

    r_avb_Dev[Unit].LastTxDesc[QIndex] = (uint32_t)datadesc;
    datadesc++;
    r_avb_Dev[Unit].NextTxDesc[QIndex] = (uint32_t)datadesc;
   
    return R_AVB_TxReqStart(Unit, QIndex);
   
}




/*******************************************************************************
  Function: R_AVB_MultiDescFrameSend
*/
r_avb_Error_t R_AVB_MultiDescFrameSend(uint32_t Unit, uint32_t QIndex, r_avb_TxMultiFrame_t *Frame) {
    r_avb_DataDesc_t  *datadesc;
    r_avb_TxRxCtrl_t  txctrl;

    /* get next free descriptor */
    datadesc = (r_avb_DataDesc_t *)R_AVB_CurrentDescGet(Unit, QIndex, R_AVB_TX);
    if (datadesc == 0) {
        return R_AVB_ERR_NG;
    }

    while ((datadesc->Header.Dt == R_AVB_DESC_LINKFIX) || (datadesc->Header.Dt == R_AVB_DESC_LINK)) {
        datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
    }

    txctrl.Word = 0;
    if (Frame->Timestamp == R_AVB_ENABLE) {
        txctrl.TxCtrl.Tsr = 1;
    }

    if (Frame->MacStatus == R_AVB_ENABLE) {
        txctrl.TxCtrl.Msr = 1;
    }

    txctrl.TxCtrl.Tag = Frame->Tag;

    /* build the descriptor chain */
    /* MAC header */
    datadesc->Header.Dt   = R_AVB_DESC_FSTART;
    if (r_avb_Dev[Unit].DescIntEnable[QIndex] == 1) {
        datadesc->Header.Die  = r_avb_Dev[Unit].TxDescIntFlag[QIndex];
    } else {
        datadesc->Header.Die  = 0;
    }
    datadesc->Header.Ctrl = txctrl.Word;
    datadesc->Header.Ds   = Frame->MacLength;
    datadesc->Dptr        = Frame->MacHeader;

    datadesc ++;
    while ((datadesc->Header.Dt == R_AVB_DESC_LINKFIX) || (datadesc->Header.Dt == R_AVB_DESC_LINK)) {
        datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
    }

    /* Payload header */
    datadesc->Header.Dt   = R_AVB_DESC_FMID;
    datadesc->Header.Die  = 0;
    datadesc->Header.Ctrl = txctrl.Word;
    datadesc->Header.Ds   = Frame->PlHLength;
    datadesc->Dptr        = Frame->PlHeader;

    datadesc ++;
    while ((datadesc->Header.Dt == R_AVB_DESC_LINKFIX) || (datadesc->Header.Dt == R_AVB_DESC_LINK)) {
        datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
    }

    /* Payload */
    datadesc->Header.Dt   = R_AVB_DESC_FEND;
    datadesc->Header.Die  = 0;
    datadesc->Header.Ctrl = txctrl.Word;
    datadesc->Header.Ds   = Frame->PlLength;
    datadesc->Dptr        = Frame->Payload;

    r_avb_Dev[Unit].LastTxDesc[QIndex] = (uint32_t)datadesc;

    /* End of Set */
    datadesc ++;
    while ((datadesc->Header.Dt == R_AVB_DESC_LINKFIX) || (datadesc->Header.Dt == R_AVB_DESC_LINK)) {
        datadesc = (r_avb_DataDesc_t *)datadesc->Dptr;
    }

    datadesc->Header.Dt   = R_AVB_DESC_EOS;
    datadesc->Header.Die  = 0;
    datadesc->Header.Ctrl = 0;
    datadesc->Header.Ds   = 0;
    datadesc->Dptr        = 0;

    return R_AVB_TxReqStart(Unit, QIndex);
}


/*******************************************************************************
  Function: R_AVB_RxQueueProcess
*/
void R_AVB_RxQueueProcess(uint32_t Unit, uint32_t RxFramePtr, r_avb_RxChConfig_t *ChConfig) {
    uint32_t descaddr;
    
    descaddr = r_avb_Dev[Unit].NextRxDesc[ChConfig->ChNum];
    ((r_avb_RxSingleFrame_t *)RxFramePtr)->DescAddr = descaddr;
    
    if (ChConfig->ChNum == R_AVB_BECHANNEL) {           /* bese effort channel */
        loc_RxBeProcess(Unit, RxFramePtr, descaddr);
    } else if (ChConfig->ChNum == R_AVB_NCCHANNEL) {    /* network control channel */
        loc_RxNcProcess(Unit, RxFramePtr, descaddr);
    } else {                                            /* stream channel */
        loc_RxSProcess(Unit, RxFramePtr, ChConfig->ChNum, descaddr);
    }

    /* update descriptor chain */
    //R_AVB_RxDescChainUpdate(Unit, descaddr, ChConfig);
}

void R_AVB_RxReadDone(uint32_t Unit,uint32_t RxFramePtr,r_avb_RxChConfig_t *ChConfig) {

    R_AVB_RxDescChainUpdate(Unit, ((r_avb_RxSingleFrame_t *)RxFramePtr)->DescAddr, ChConfig);
}

/*******************************************************************************
  Section: Global Functions

*/

/*******************************************************************************
  Function: R_AVB_SYS_BaseAddr

  See: r_avb_sys.h for details
*/

uint32_t R_AVB_SYS_BaseAddr(uint32_t Unit) {

        return R_AVB_BASE;
    
}







/*******************************************************************************
  Function: R_AVB_SYS_AllocDescBuf
*/
r_avb_Error_t R_AVB_SYS_AllocDescBuffer(uint32_t Unit) {
    int i;
    uint32_t descaddr;
    r_avb_LinkDesc_t *linkdesc;

    linkdesc  = (r_avb_LinkDesc_t *)R_ATF_Ram_Alloc((R_AVB_TXQ_NUM + R_AVB_RXQ_NUM) * R_AVB_NORMAL_DESC_SIZE);

    descaddr  = R_ATF_Ram_Alloc(R_AVB_TXDESC_Q_NUM * R_AVB_NORMAL_DESC_SIZE * R_AVB_TXQ_NUM);

    if (descaddr == 0) {
        return R_AVB_ERR_NG;
    }

    /* alloc memory for tx descriptor */
    for (i = 0; i < R_AVB_TXQ_NUM; i++) {
        linkdesc->Header.Dt  = R_AVB_DESC_LINKFIX;
        linkdesc->Header.Die = 0;
        linkdesc->Header.Res = 0;
        linkdesc->Dptr       = descaddr;
        linkdesc++;
        descaddr += (R_AVB_TXDESC_Q_NUM * R_AVB_NORMAL_DESC_SIZE);
    }

    /* alloc memory for rx descriptor */
    descaddr  = R_ATF_Ram_Alloc((R_AVB_RXDESC_BE_NUM - 1) * R_AVB_SPECIAL_DESC_SIZE + R_AVB_NORMAL_DESC_SIZE);

    if (descaddr == 0) {
        return R_AVB_ERR_NG;
    }

    /* rx BE descriptor */
    linkdesc->Header.Dt  = R_AVB_DESC_LINKFIX;
    linkdesc->Header.Die = 0;
    linkdesc->Header.Res = 0;
    linkdesc->Dptr       = descaddr;

    linkdesc ++;

    descaddr = R_ATF_Ram_Alloc((R_AVB_RXDESC_NC_NUM - 1) * R_AVB_SPECIAL_DESC_SIZE + R_AVB_NORMAL_DESC_SIZE);

    if (descaddr == 0) {
        return R_AVB_ERR_NG;
    }

    /* rx NC descriptor */
    linkdesc->Header.Dt  = R_AVB_DESC_LINKFIX;
    linkdesc->Header.Die = 0;
    linkdesc->Header.Res = 0;
    linkdesc->Dptr       = descaddr;

    linkdesc ++;

    descaddr = R_ATF_Ram_Alloc(R_AVB_RXSTREAMQ_NUM * ((R_AVB_RXDESC_S_NUM - 1) * R_AVB_SPECIAL_DESC_SIZE + R_AVB_NORMAL_DESC_SIZE));

    if (descaddr == 0) {
        return R_AVB_ERR_NG;
    }

    /* rx stream descriptor */
    for (i = 0; i < R_AVB_RXSTREAMQ_NUM; i++) {
        linkdesc->Header.Dt  = R_AVB_DESC_LINKFIX;
        linkdesc->Header.Die = 0;
        linkdesc->Header.Res = 0;
        linkdesc->Dptr       = descaddr;

        linkdesc ++;

        /* descriptors with timestamp + link descriptor */
        descaddr  += ((R_AVB_RXDESC_S_NUM - 1) * R_AVB_SPECIAL_DESC_SIZE + R_AVB_NORMAL_DESC_SIZE);
    }

    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function:
*/
uint32_t R_AVB_SYS_AllocRxMemBuffer(uint32_t Unit, uint32_t MemSize) {
    uint32_t addr = 0;

    addr = R_ATF_Ram_Alloc(MemSize);

    return addr;
}

/*******************************************************************************
  Function:
*/
uint32_t R_AVB_SYS_AllocTxMemBuffer(uint32_t Unit, uint32_t MemSize) {
    uint32_t addr = 0;

    addr = R_ATF_Ram_Alloc(MemSize);

    return addr;
}



/***********************************************************
  Section: Constants
*/
static const uint32_t loc_MacCounter[R_AVB_CNT_LAST][2] = {
    {R_AVB_CNT_TROCR,  R_AVB_TROCR },
    {R_AVB_CNT_CDCR,   R_AVB_CDCR  },
    {R_AVB_CNT_LCCR,   R_AVB_LCCR  },
    {R_AVB_CNT_CEFCR,  R_AVB_CEFCR },
    {R_AVB_CNT_FRECR,  R_AVB_FRECR },
    {R_AVB_CNT_TSFRCR, R_AVB_TSFRCR},
    {R_AVB_CNT_TLFRCR, R_AVB_TLFRCR},
    {R_AVB_CNT_RFCR,   R_AVB_RFCR  },
    {R_AVB_CNT_MAFCR,  R_AVB_MAFCR }
};

/***********************************************************
  Section: External globals
*/
#ifdef __ghs
#pragma ghs startdata
extern uint8_t ETH_PHY_Initialized;
#pragma ghs enddata
#endif

/***********************************************************
  Section: Local Functions
*/

/***********************************************************
  Function: loc_PhyWrite1

  Write 1 into the MII management frame

  Parameters:
    Unit   - Instance number

  Returns:
    void
*/
void loc_PhyWrite1(uint32_t Unit) {
    int i;
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_PIR, 0x6);
    for( i=0; i<EE_ETNB_MDIO_DELAY; i++) NOP();
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_PIR, 0x7);
    for( i=0; i<EE_ETNB_MDIO_DELAY; i++) NOP();
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_PIR, 0x7);
    for( i=0; i<EE_ETNB_MDIO_DELAY; i++) NOP();
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_PIR, 0x6);
    for( i=0; i<EE_ETNB_MDIO_DELAY; i++) NOP();
}


/***********************************************************
  Function: loc_PhyWrite0

  Write 0 into the MII management frame

  Parameters:
    Unit   - Instance number

  Returns:
    void
*/
void loc_PhyWrite0(uint32_t Unit) {
    int i;
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_PIR, 0x2);
    for( i=0; i<EE_ETNB_MDIO_DELAY; i++) NOP();
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_PIR, 0x3);
    for( i=0; i<EE_ETNB_MDIO_DELAY; i++) NOP();
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_PIR, 0x3);
    for( i=0; i<EE_ETNB_MDIO_DELAY; i++) NOP();
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_PIR, 0x2);
    for( i=0; i<EE_ETNB_MDIO_DELAY; i++) NOP();
}


/***********************************************************
  Function: loc_PhyRead

  Read Phy register

  Parameters:
    Unit    - Instance number

  Returns:
    void
*/
uint16_t loc_PhyRead(uint32_t Unit) {
    int i,j;
    uint16_t val = 0;


    for (i = 0; i < 16; i++) {
       val <<= 1;
        val |= (uint16_t)((R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_PIR) & 0x8) >> 3);
        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_PIR, 1);
        for( j=0; j<EE_ETNB_MDIO_DELAY; j++) NOP();
        
        
        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_PIR, 0);
        for( j=0; j<EE_ETNB_MDIO_DELAY; j++) NOP();
 
        
    }

    return val;
}


/***********************************************************
  Function: loc_PhyWrite

  Write Phy register

  Parameters:
    Unit    - Instance number
    Value   - Value to be written

  Returns:
    void
*/
void loc_PhyWrite(uint32_t Unit, uint16_t Value) {
    int i;

    for (i = 0; i < 16; i++) {
        if ((Value & 0x8000) == 0) {
            loc_PhyWrite0(Unit);
        } else {
            loc_PhyWrite1(Unit);
        }

        Value <<= 1;
    }
}


/***********************************************************
  Function: loc_MIIFrameHeaderSet
  
  Set MII management Frame header

  Parameters:
    Unit    - Instance number
    PhyAddr - Phy address
    RegAddr - Register address
    Rw      - Read/Write, 0: read, 1: write

  Returns:
    void
*/
void loc_MIIFrameHeaderSet(uint32_t Unit, uint8_t PhyAddr, uint8_t RegAddr, uint8_t Rw) {
    int i;
    uint16_t data = 0;

    data = 1 << 14;

    /* ST + OP */
    if (Rw == 1) {
        data |= 1 << 12;
    } else {
        data |= 1 << 13;
    }

    /* Phy address */
    data |= ((uint16_t)PhyAddr << 7);

    /* Reg address */
    data |= ((uint16_t)RegAddr << 2);
    
    /* write preamble */
    for (i = 0; i < 32; i++) {
        loc_PhyWrite1(Unit);
    }

    /* write ST, OP, PHYAD, RegAD */ 
    for (i = 0; i < 14; i++) {
        if ((data & 0x8000) == 0) {
            loc_PhyWrite0(Unit);
        } else {
            loc_PhyWrite1(Unit);
        }
        data <<= 1;
    }
}


/***********************************************************
  Function: loc_PhyBusRelease

  MII management bus release flow

  Parameters:
    Unit  - Instance number

  Returns:
    void
*/
void loc_PhyBusRelease(uint32_t Unit) {
    int j;
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_PIR, 0x0);
    for( j=0; j<EE_ETNB_MDIO_DELAY; j++) NOP();
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_PIR, 0x1);
    for( j=0; j<EE_ETNB_MDIO_DELAY; j++) NOP();
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_PIR, 0x0);
    for( j=0; j<EE_ETNB_MDIO_DELAY; j++) NOP();
}


/*******************************************************************************
  Section: Global API Functions

  For comments see: <avb_api.h>
*/

/*******************************************************************************
  Function: R_AVB_MacInit
*/
r_avb_Error_t R_AVB_MacInit(uint32_t Unit, r_avb_MacConfig_t *MacConfig) {
    r_avb_Ecmr_t ecmr;
    r_avb_Ecsipr_t ecsipr;
    r_avb_Gecmr_t gecmr;
    
    if (Unit >= R_AVB_MACRO_NUM) {
        return R_AVB_ERR_RANGE;
    }

    /* set MAC address */
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_MALR,
                     ((uint32_t)MacConfig->MacAddr[4]<< 8) | ((uint32_t)MacConfig->MacAddr[5]));
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_MAHR,
                     ((uint32_t)MacConfig->MacAddr[0]<<24) | ((uint32_t)MacConfig->MacAddr[1]<<16) |
                     ((uint32_t)MacConfig->MacAddr[2]<< 8) | ((uint32_t)MacConfig->MacAddr[3]));

    /* set Rx frame length */
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_RFLR, MacConfig->MaxFrameLen);

    /* set MAC interrupt */
    ecsipr.Word = 0;
    ecsipr.Bit.Fcim   = (MacConfig->Mac_Int_Mask)->Icdim;
    ecsipr.Bit.Mpdim  = (MacConfig->Mac_Int_Mask)->Mpdim;
    ecsipr.Bit.Linkim = (MacConfig->Mac_Int_Mask)->Linkim;
    ecsipr.Bit.Phyim  = (MacConfig->Mac_Int_Mask)->Phyim;
    
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_ECSIPR, ecsipr.Word);

    /* clear all counters */
    R_AVB_MacAllCounterClear(Unit);

    /* Set a 100 Mbit/s default speed for the MAC */
    (MacConfig->Mac_Mode)->Speed = R_AVB_100M;    

 
    
    /* set transmission speed */
    gecmr.Bit.Speed = (MacConfig->Mac_Mode)->Speed;
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_GECMR, gecmr.Word);

    /* Set MAC mode register */
    ecmr.Word = 0;
    ecmr.Bit.Prm  = (MacConfig->Mac_Mode)->PromMode;
    ecmr.Bit.Dpm  = (MacConfig->Mac_Mode)->Duplex;
    ecmr.Bit.Mpm  = (MacConfig->Mac_Mode)->MagicDection;
    ecmr.Bit.Txf  = (MacConfig->Mac_Mode)->TxFlowCtrl;
    ecmr.Bit.Rxf  = (MacConfig->Mac_Mode)->RxFlowCtrl;
    ecmr.Bit.Pfr  = (MacConfig->Mac_Mode)->PFrameRxMode;
    ecmr.Bit.Tzpf = (MacConfig->Mac_Mode)->ZPFrameTx;
    ecmr.Bit.Rzpf = (MacConfig->Mac_Mode)->ZPFrameRx;
    ecmr.Bit.Dpad = (MacConfig->Mac_Mode)->DPad;
    ecmr.Bit.Rcsc = (MacConfig->Mac_Mode)->RxCrcMode;
    ecmr.Bit.Tpe  = (MacConfig->Mac_Mode)->Tpe;
    ecmr.Bit.Rpe  = (MacConfig->Mac_Mode)->Rpe;
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_ECMR, ecmr.Word);
    
    return R_AVB_ERR_OK;
}


/*******************************************************************************
  Function: R_AVB_MacPhyRead
*/
uint16_t R_AVB_MacPhyRead(uint32_t Unit, uint8_t PhyAddr, uint8_t RegAddr) {
    uint16_t val;
    
    /* frame header */
    loc_MIIFrameHeaderSet(Unit, PhyAddr, RegAddr, 0);
    
    /* TA */
    loc_PhyWrite0(Unit);
    loc_PhyBusRelease(Unit);
    
    /* read data */
    val = loc_PhyRead(Unit);

    return val;
}


/*******************************************************************************
  Function: R_AVB_MacPhyWrite
*/
void R_AVB_MacPhyWrite(uint32_t Unit, uint8_t PhyAddr, uint8_t RegAddr, uint16_t Value) {
    /* frame header */
    loc_MIIFrameHeaderSet(Unit, PhyAddr, RegAddr, 1);
    
    /* TA */
    loc_PhyWrite1(Unit);
    loc_PhyWrite0(Unit);
    
    /* write data */
    loc_PhyWrite(Unit, Value);
    
    /* bus release */
    loc_PhyBusRelease(Unit);
}


/*******************************************************************************
  Function: R_AVB_MacAllCounterClear
*/
void R_AVB_MacAllCounterClear(uint32_t Unit) {
    int i;

    for (i = R_AVB_CNT_FIRST; i < R_AVB_CNT_LAST; i++) {
        R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + loc_MacCounter[i][1], 0);
    }
}


/*******************************************************************************
  Function: R_AVB_MacCounterClear
*/
void R_AVB_MacCounterClear(uint32_t Unit, r_avb_MacCounter_t Counter) {
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + loc_MacCounter[Counter][1], 0);
}


/*******************************************************************************
  Function: R_AVB_MacCounterGet
*/
uint16_t R_AVB_MacCounterGet(uint32_t Unit, r_avb_MacCounter_t Counter) {
    uint16_t counter;

    counter = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + loc_MacCounter[Counter][1]);

    return counter;
}


/*******************************************************************************
  Function: R_AVB_MacIntStatusGet
*/
uint32_t R_AVB_MacIntStatusGet(uint32_t Unit) {
    uint32_t val;
    
    val = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_ECSR);
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_ECSR, 0xf);
    
    return val;
}


/*******************************************************************************  
  Function: R_AVB_MacCommunicationSet
*/
void R_AVB_MacCommunicationSet(uint32_t Unit, r_avb_TxRxOption_t Direction, r_avb_Option_t Option) {
    r_avb_Ecmr_t ecmr;
    
    ecmr.Word = R_AVB_READ_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_ECMR);
    if (Direction == R_AVB_RX) {
        ecmr.Bit.Rpe = Option;
    } else if (Direction == R_AVB_TX) {
        ecmr.Bit.Tpe = Option;
    }
    
    R_AVB_WRITE_REG(32, r_avb_Dev[Unit].BaseAddr + R_AVB_ECMR, ecmr.Word);
}
