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
/* Module :  r_canfd.c                                                       */
/* History:                                                                  */
/*              V1.00: Initial version                                       */
/*                                                                           */
/*===========================================================================*/
/* Description:                                                              */
/* Functions for CAN-FD initialization and testing.                          */
/*                                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_canfd.h"
#include "drivers\rscanfd\r_rscfd.h"
#include "drivers\rscanfd\r_rscfd_cfg.h"
#include "modules\systimer\r_systimer.h"
/*===========================================================================*/
/* Variables */
/*===========================================================================*/
/* Create Can_FrameType for send and receive data */





rscfd_unit_cfg_t g_rscfd_unit_cfg[1] = {
    {
        .unit = RSCFD_UNIT_0,                /* CANFD unit 0 */
        .clock_source = RSCFD_CLK_SRC_OSC,   /* Clock source: Oscillator */
        .dlc_check = RSCFD_DLC_CHECK_DIS,    /* DLC check disabled */
        .rx_buff_cnt = RSCFD_RX_BUFF_CNT_2,  /* Number of receive buffers: 2 */
        .rx_buff_size = RSCFD_RX_BUFF_SIZE_64,/* Size of receive buffers: 64 bytes */
        .hw_delay = 100000                   /* Hardware delay: 100000 */
    }
};

rscfd_chnl_cfg_t chnl_cfg[2] = {
    {
    .chnl = RSCFD_CHNL_0,                /* Channel 0 */
    .interface = RSCFD_CHNL_INTERF_CLASSICAL, /* Classical CAN interface */
    .testmode = RSCFD_CHNL_TEST_DIS,     /* Test mode disabled */
    .error_irq = RSCFD_ERR_IRQ_DIS,      /* Error interrupt disabled */
    .nom_rate = RSCFD_CHNL_NBR_500K_20M, /* Nominal bit rate: 500K, Clock Input: 20M */
    .hist_en = RSCFD_CHNL_HIST_DIS,      /* History disabled */
    .data_rate = RSCFD_CHNL_DBR_500K_20M,/* Data bit rate: 500K, Clock Input: 20M */
    .comp = RSCFD_CHNL_COMP_DIS,         /* Compensation disabled */
    .rx_rule_cnt = 1,                    /* Number of receive rules: 1 */
    .comp_ofst = 0,                      /* Compensation offset: 0 */
    .hw_delay = 100000                   /* Hardware delay: 100000 */
    },
    {
    .chnl = RSCFD_CHNL_1,                /* Channel 1 */
    .interface = RSCFD_CHNL_INTERF_CLASSICAL, /* Classical CAN interface */
    .testmode = RSCFD_CHNL_TEST_DIS,     /* Test mode disabled */
    .error_irq = RSCFD_ERR_IRQ_DIS,      /* Error interrupt disabled */
    .nom_rate = RSCFD_CHNL_NBR_500K_20M, /* Nominal bit rate: 500K, Clock Input: 20M */
    .hist_en = RSCFD_CHNL_HIST_DIS,      /* History disabled */
    .data_rate = RSCFD_CHNL_DBR_500K_20M,/* Data bit rate: 500K, Clock Input: 20M */
    .comp = RSCFD_CHNL_COMP_DIS,         /* Compensation disabled */
    .rx_rule_cnt = 1,                    /* Number of receive rules: 1 */
    .comp_ofst = 0,                      /* Compensation offset: 0 */
    .hw_delay = 100000                   /* Hardware delay: 100000 */
    }
};

rscfd_rx_rule_cfg_t rx_rule_cfg[2] = {
    {
        .page = RSCFD_RX_PAGE_0_0,               /* which RSCFD unit and page */
        .rule = RSCFD_RX_RULE_0,                 /* which rule within the page */
        .id = 0,                                 /* A: ID filter */
        .id_type = RSCFD_ID_TYPE_STD,            /* A: standard/extended ID */
        .source = RSCFD_RX_SRC_OTHER_NODE,       /* A: messages origin */
        .min_dlc = RSCFD_DLC_0_BYTES,            /* A: minimum payload to accept */
        .mask_id = 0,                            /* B: ID bits mask */
        .mask_id_type = RSCFD_RX_ID_TYPE_MASK_ON,/* B: IDE bit mask */
        .dest = RSCFD_RX_DST_BUFF_0_0,           /* C: message destination */
        .ptr = 0                                 /* C: message pointer to store */
    },
    {
        .page = RSCFD_RX_PAGE_0_0,               /* which RSCFD unit and page */
        .rule = RSCFD_RX_RULE_1,                 /* which rule within the page */
        .id = 0,                                 /* A: ID filter */
        .id_type = RSCFD_ID_TYPE_STD,            /* A: standard/extended ID */
        .source = RSCFD_RX_SRC_OTHER_NODE,       /* A: messages origin */
        .min_dlc = RSCFD_DLC_0_BYTES,            /* A: minimum payload to accept */
        .mask_id = 0,                            /* B: ID bits mask */
        .mask_id_type = RSCFD_RX_ID_TYPE_MASK_ON,/* B: IDE bit mask */
        .dest = RSCFD_RX_DST_BUFF_0_1,           /* C: message destination */
        .ptr = 0                                 /* C: message pointer to store */
    }
};


/*****************************************************************************
** Function:    R_CANFD_Init
** Description: Configures CAN Channels and the corresponding pins.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_CANFD_Init(void)
{


    /* Initialize CANFD unit reset */
    R_RSCFD_InitUnitRst(g_rscfd_unit_cfg, 1);

    /* Initialize CANFD channel reset */
    R_RSCFD_InitChnlRst(chnl_cfg, 2);

    /* Initialize CANFD receive rules reset */
    R_RSCFD_InitRxRulesRst(rx_rule_cfg, 2);

    /* Initialize CANFD unit operation */
    R_RSCFD_InitUnitOper(g_rscfd_unit_cfg, 1);

    /* Initialize CANFD channel operation */
    R_RSCFD_InitChnlOper(chnl_cfg, 2);



    
}

/*****************************************************************************
** Function:    R_CANFD_Test
** Description: Sends a CAN frame on a channel and compares with received data 
**              on another channel. 
** Parameter:   None
** Return:      R_OK - Received frame matches sent frame.
**              R_ERROR - Mismatch detected.
******************************************************************************/
r_Error_t R_CANFD_Test(void){
    rscfd_msg_t rx_can_Frame;   /* Define a variable to store the received CAN frame */
    rscfd_msg_t tx_can_Frame;   /* Define a variable to store the transmitted CAN frame */
    uint8_t rx_payload[64];     /* Define a buffer to store the payload of the received CAN frame */
    uint8_t tx_payload[64];     /* Define a buffer to store the payload of the transmitted CAN frame */
    uint32_t i;
    uint64_t time;
    
    /* Payload data for transmission */
    tx_payload[0]=0x01;
    tx_payload[1]=0x02;
    tx_payload[2]=0x03;
    tx_payload[3]=0x04;
    tx_payload[4]=0x05;
    tx_payload[5]=0x06;
    tx_payload[6]=0x07;
    tx_payload[7]=0x08;

    /* Configuration transmitted frame */
    tx_can_Frame.id = 0x5aa;                             /* Message ID */
    tx_can_Frame.id_type = RSCFD_ID_TYPE_STD;            /* Message ID type (Standard) */
    tx_can_Frame.ptr = 0;                                /* Message pointer */
    tx_can_Frame.label = RSCFD_LABEL_0;                  /* Message label */
    tx_can_Frame.timestamp = 0;                          /* Message timestamp */
    tx_can_Frame.bytes = RSCFD_PAYLOAD_SIZE_8_BYTES;     /* Number of bytes in payload */
    tx_can_Frame.payload = (rscfd_payload_t *)tx_payload; /* Message payload */

   
    /* Assign the payload buffer to the received CAN frame */
    rx_can_Frame.payload = (rscfd_payload_t *) rx_payload; 


    /* Transmit CAN frame using buffer */
    R_RSCFD_TxByBuff(RSCFD_TX_BUFF_0_0, RSCFD_MSG_MODE_CLASSICAL, &tx_can_Frame);

    
    /* Wait until a new message is received in the receive buffer (timeout 10ms )*/
    time = R_SysTimer_Read();
    while(R_RSCFD_GetRxBuffMsgNew(RSCFD_RX_BUFF_0_1) == 0 ) {
        if(R_SysTimer_Read() > time+R_SYSTIMER_10MSECOND) {
            return R_ERROR;
        }
    }


    /* Read the received message from the receive buffer */
    if( R_RSCFD_ReadRxBuff(RSCFD_RX_BUFF_0_1, &rx_can_Frame) == RSCFD_RESULT_NEWMSG)
    {
        /* Compare the received frame with the transmitted frame */
        if(rx_can_Frame.id == tx_can_Frame.id)
        {
            if(rx_can_Frame.bytes == tx_can_Frame.bytes)
            {
                for(i=0; i<rx_can_Frame.bytes; i++)
                {
                    if(rx_can_Frame.payload->BYTE[i] != tx_can_Frame.payload->BYTE[i])
                    {
                        return R_ERROR;
                    }
                }
            }
            else
            {
                return R_ERROR;
            }
        }
        else
        {
            return R_ERROR;
        }
    }
    else
    {
        return R_ERROR;
    }

    return R_OK;
}



