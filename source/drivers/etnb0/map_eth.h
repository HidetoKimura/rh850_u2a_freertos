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
* File Name         : 
* Component Version : 1.0.0
* Description       : 
***********************************************************************************************************************/

#ifndef _MAP_ETH_H
#define _MAP_ETH_H



/* MAPPED ETH: ETNB */


//#include "ethernet.h>"
// #include <ethernet.h>

#ifdef  APPLICATION_INTERFACE   /* optional UART settings */
#endif

/* FURTHER ETNB OPERATION PROPERTIES */

#define ETH_HTTP_WEBSITETEXT     'R',  'H',  '8',  '5',  '0',  '/',  'U',  '2',  'A'

#define ETH_OK             ( true )
#define ETH_ERROR          ( false )
#define ETH_TIMEOUT        ( 100L )


#define EE_ETNB_BASEADDRESS           ( 0xFF0A2000 ) /* Base address of ETNB unit */

/* Network Board V2 UPD60611 PHY piggy board */
//#define ETH_PHY_UPD60611                             /* PHY Type 100BASE-T4 */
//#define ETH_PHY_UPD60611_BASE         ( 7 )          /* Base Address of PHY registers */

/* Network Board V2 KSZ8041 PHY piggy board */
//#define ETH_PHY_KSZ8041                              /* PHY Type 100BASE-T4 */
//#define ETH_PHY_KSZ8041_BASE          ( 0 )          /* Base Address of PHY registers */

/* LAN8700 PHY of Network Board V1 and PHY piggy board and Starter Kit */
#define ETH_PHY_LAN8700                              /* PHY Type 100BASE-T4 */
#define ETH_PHY_LAN8700_BASE          ( 31 )         /* Base Address of PHY registers */

/* alternative BroadR-Reach PHY selectable */
// #define ETH_PHY_BCM89810                             /* PHY Type BroadR-Reach 100BASE-T1 */
// #define ETH_PHY_BROADRREACH_BASE      ( 1 )          /* Base Address of PHY registers */

#define EE_ETNB_MDIO_DELAY            ( 100 )        /* MDIO speed adaptation (based on CPU speed) */


/* NETIF DATA ALIGNMENT DEFINITION */


//#define ETH_PAD_SIZE        ( 2 )          // Padding of payload to avoid misaligned longword access

#endif


