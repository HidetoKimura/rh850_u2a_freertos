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
#include "r_ethernet_phy.h"


#define PHY_REG_CTRL    0
#define PHY_REG_STATUS  1
#define PHY_REG_ID1     2
#define PHY_REG_ID2     3
#define PHY_REG_ANAD    4
#define PHY_REG_ANLPBP  5
#define PHY_REG_ANEX    6
#define PHY_REG_ANLPNP  7
#define PHY_REG_SIREV   16
#define PHY_REG_MCTRL   17
#define PHY_REG_SMODE   18
#define PHY_REG_STAIND  27
#define PHY_REG_INTEST  28
#define PHY_REG_INTFLG  29
#define PHY_REG_INTMSK  30
#define PHY_REG_SCTRL   31


#define PHY_REG_CTRL_LOOPBACK 0x4000
#define PHY_REG_CTRL_RESET    0x8000
#define PHY_REG_CTRL_ANEG_EN  0x1000
#define PHY_REG_CTRL_DUPLEX   0x0100


r_phy_Error_t r_ethernetPhy_getLinkStatus(phy_dev_t *dev,link_status_t *status)    
{
    uint16_t val;

    val =dev->phy_read(dev->ethernet_unit , dev->phy_adress, PHY_REG_STATUS);
    if (0xffff == val) {
        return R_PHY_ERR_NG;
    }
    if (val & 0x0004) {
        *status = link_status_up;
    } else {
        *status = link_status_down;
    }

    return R_PHY_ERR_OK;
}

r_phy_Error_t  r_ethernetPhy_getLinkSpeed(phy_dev_t *dev, link_speed_t *speed)
{
    uint16_t val;

    val = dev->phy_read(dev->ethernet_unit , dev->phy_adress, PHY_REG_STATUS);
    if (0xffff == val) {
        return R_PHY_ERR_NG;
    }
    if (val & 0x0002) {
        *speed = link_speed_100M;
    } else {
        *speed = link_speed_10M;
    }

    return R_PHY_ERR_OK;
}

void r_ethernetPhy_init(phy_dev_t *dev)
{
    // Perform PHY initialization steps here
    // For example, configuring PHY registers, setting up interrupts, etc.
}


r_phy_Error_t  r_ethernetPhy_setLoopBack(phy_dev_t *dev, phy_loop_back_t loopBack)
{
    uint16_t val;

    val = dev->phy_read(dev->ethernet_unit , dev->phy_adress, PHY_REG_CTRL);
    if (0xffff == val) {
        return R_PHY_ERR_NG;
    }
    if (loopBack==phy_loop_back_enabled) {
        val  = val | PHY_REG_CTRL_LOOPBACK;
        val  = val | PHY_REG_CTRL_DUPLEX;
        val  = val & ~PHY_REG_CTRL_ANEG_EN;
    } else {
        val = val & ~PHY_REG_CTRL_LOOPBACK;
        val = val & ~PHY_REG_CTRL_DUPLEX;
        val = val | PHY_REG_CTRL_ANEG_EN;
    }
    dev->phy_write(dev->ethernet_unit , dev->phy_adress, PHY_REG_CTRL, val);
    
    return R_PHY_ERR_OK;
}
