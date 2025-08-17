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
#ifndef _ETH_H
#define _ETH_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "drivers\etnb0\r_avb_api.h"
#include "drivers\etnb0\r_ethernet_phy.h"

/***********************************************************************************************************************
Defines
***********************************************************************************************************************/
//#define false 1
//#define true 0

#define ETHETNB0     0
#define ETHAVBCOUNT 1



typedef enum  {
    phy_loop_back_test_ok = 1,
    phy_loop_back_test_nok = 0
}   phy_loop_back_test_t;

typedef struct{
    link_status_t link_status;
    link_speed_t link_speed;
    phy_loop_back_test_t phy_loop_back_test;
    uint8_t initialized;
    uint32_t sent_frames;
    uint32_t received_frames;
    uint8_t  mac_address[6];
    uint8_t  ip_address[4];
    uint8_t  netmask[4];
    uint8_t  gateway[4];
    phy_dev_t* phy_dev;  
}ethernet_t;

uint8_t  R_ETH_Init(void);
void R_ETH_Handler(void);
void INTETNB0DATA_callback(void);
void  ethernet_AvbRxdone(uint32_t RxFramePtr);
void  ethernet_AvbRx(r_avb_RxSingleFrame_t *frameptr);
uint32_t ethernet_AvbRx_count(void);
uint8_t R_ETH_loopback(void);
extern ethernet_t eth_config[ETHAVBCOUNT];


#endif
