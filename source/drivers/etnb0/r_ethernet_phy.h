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
#ifndef R_ETHERNET_PHY_H
#define R_ETHERNET_PHY_H

typedef enum {
    R_PHY_ERR_OK         = 0x00,
    R_PHY_ERR_NG         ,
    R_PHY_ERR_RANGE      ,
    R_PHY_ERR_OPMODE     ,
    R_PHY_ERR_INVNUM     ,
    R_PHY_ERR_LOCKED     ,
    R_PHY_ERR_NOTLOCKED
} r_phy_Error_t;


typedef enum  {
    link_status_up = 1,
    link_status_down = 0
}   link_status_t;





typedef enum  {
    phy_loop_back_enabled = 1,
    phy_loop_back_disabled = 0
}   phy_loop_back_t;

typedef enum  {
    link_speed_10M,
    link_speed_100M,
    link_speed_1G,
    link_speed_2_5G
} link_speed_t;



typedef void (*phy_write_t)(uint32_t , uint8_t , uint8_t ,uint16_t);
typedef uint16_t (*phy_read_t)(uint32_t , uint8_t , uint8_t );


typedef struct
{
    uint8_t              phy_adress;
    uint32_t             ethernet_unit;
    phy_read_t           phy_read;
    phy_write_t          phy_write;
} phy_dev_t;


// Function declarations
r_phy_Error_t r_ethernetPhy_getLinkStatus(phy_dev_t *dev,link_status_t *status) ;
r_phy_Error_t  r_ethernetPhy_getLinkSpeed(phy_dev_t *dev, link_speed_t *speed);
r_phy_Error_t  r_ethernetPhy_setLoopBack(phy_dev_t *dev, phy_loop_back_t loopBack);
void r_ethernetPhy_init(phy_dev_t *dev);


#endif // R_ETHERNET_PHY_LAN8700_H
