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
#include "r_eth.h"

#include "drivers\gpio\r_gpio_helper.h"
#include "drivers\etnb0\r_avb_api.h"
#include "drivers\etnb0\r_at_ram_if.h"
#include "drivers\etnb0\r_config_avb.h"
#include "drivers\etnb0\r_ethernet_phy.h"

#include "modules\systimer\r_systimer.h"

#include "lwip\ip_addr.h"
#include "lwip\init.h"
#include "lwip\netif.h"
#include "netif\ethernet.h"
#include "netif\etharp.h"
#include "lwip\timeouts.h"
#include "lwip\apps\httpd.h"
#include "lwip\apps\lwiperf.h"

#include "shared.h"
/*******************************************************************************
  Section: local defines
*/

/* configure MAC address */
#define MAC_ADDRESS_01 0x12
#define MAC_ADDRESS_02 0x34
#define MAC_ADDRESS_03 0x56
#define MAC_ADDRESS_04 0x78
#define MAC_ADDRESS_05 0x9a
#define MAC_ADDRESS_06 0xbc

/* configure IP address */
#define IPv4_ADDRESS_HH 192
#define IPv4_ADDRESS_HL 168
#define IPv4_ADDRESS_LH 10
#define IPv4_ADDRESS_LL 35

/* configure gateway IP address  */
#define IPv4_GATEWAY_HH 192
#define IPv4_GATEWAY_HL 168
#define IPv4_GATEWAY_LH 10
#define IPv4_GATEWAY_LL 1

/* configure net mask */
#define IPv4_NETMASK_HH 255
#define IPv4_NETMASK_HL 255
#define IPv4_NETMASK_LH 255
#define IPv4_NETMASK_LL 0


#if USE_DHCP
#define DHCP 1
#endif

#define USE_AVB




phy_dev_t phy0;
ethernet_t eth_config[ETHAVBCOUNT];

void r_ethernetConfigInit(void) {
  eth_config[ETHETNB0].link_status = link_status_down;
  eth_config[ETHETNB0].link_speed = link_speed_100M;
  eth_config[ETHETNB0].phy_loop_back_test = phy_loop_back_test_nok;

  eth_config[ETHETNB0].ip_address[0]= IPv4_ADDRESS_HH;
  eth_config[ETHETNB0].ip_address[1]= IPv4_ADDRESS_HL;
  eth_config[ETHETNB0].ip_address[2]= IPv4_ADDRESS_LH;
  eth_config[ETHETNB0].ip_address[3]= IPv4_ADDRESS_LL;

  eth_config[ETHETNB0].netmask[0]= IPv4_NETMASK_HH;
  eth_config[ETHETNB0].netmask[1]= IPv4_NETMASK_HL;
  eth_config[ETHETNB0].netmask[2]= IPv4_NETMASK_LH;
  eth_config[ETHETNB0].netmask[3]= IPv4_NETMASK_LL;

  eth_config[ETHETNB0].gateway[0]= IPv4_GATEWAY_HH;
  eth_config[ETHETNB0].gateway[1]= IPv4_GATEWAY_HL;
  eth_config[ETHETNB0].gateway[2]= IPv4_GATEWAY_LH;
  eth_config[ETHETNB0].gateway[3]= IPv4_GATEWAY_LL;

  eth_config[ETHETNB0].mac_address[0] = MAC_ADDRESS_01;
  eth_config[ETHETNB0].mac_address[1] = MAC_ADDRESS_02;
  eth_config[ETHETNB0].mac_address[2] = MAC_ADDRESS_03;
  eth_config[ETHETNB0].mac_address[3] = MAC_ADDRESS_04;
  eth_config[ETHETNB0].mac_address[4] = MAC_ADDRESS_05;
  eth_config[ETHETNB0].mac_address[5] = MAC_ADDRESS_06;
  
  eth_config[ETHETNB0].phy_dev = &phy0;

  eth_config[ETHETNB0].phy_dev->phy_adress = 31;
  eth_config[ETHETNB0].phy_dev->ethernet_unit = ETHETNB0;
  eth_config[ETHETNB0].phy_dev->phy_read = (phy_read_t)R_AVB_MacPhyRead;
  eth_config[ETHETNB0].phy_dev->phy_write = (phy_write_t)R_AVB_MacPhyWrite;

}



extern err_t ethernetif_init(struct netif *netif);
extern  void ethernetif_input(struct netif *netif);
void ethernet_AvbDataIsr(void);



/*******************************************************************************
  Section: local variables
*/

uint32_t locTxStatus = 1;
uint32_t locRxCnt;
uint32_t locRxStatus=0;

struct netif netif;

static r_avb_RxChConfig_t locRxBeConfig;


/*************************************************************************************************  
*   Function Name : init_lwip
*   Description   : initialize the lightweight ip stack
*   Arguments     : none
*   Return Value  : none
*************************************************************************************************/
void ethernet_InitLwip (void) 
{
    /* Network interface variables */
    ip_addr_t ipaddr, netmask, gw;
    
    /* Set default network address variables. Check config.h for configuration. */
    IP4_ADDR(&gw, IPv4_GATEWAY_HH, IPv4_GATEWAY_HL, IPv4_GATEWAY_LH, IPv4_GATEWAY_LL);
    IP4_ADDR(&ipaddr, IPv4_ADDRESS_HH, IPv4_ADDRESS_HL, IPv4_ADDRESS_LH, IPv4_ADDRESS_LL);
    IP4_ADDR(&netmask, IPv4_NETMASK_HH, IPv4_NETMASK_HL, IPv4_NETMASK_LH, IPv4_NETMASK_LL);
     
    IP4_ADDR(&ipaddr, IPv4_ADDRESS_HH, IPv4_ADDRESS_HL, IPv4_ADDRESS_LH, IPv4_ADDRESS_LL);
 
    /* The lwIP single-threaded core: initialize the network stack */ 
    lwip_init();
    
    /* Bring up the network interface */
    /* Hint: netif_init(); was already called by lwip_init(); above */
    netif_add(&netif, &ipaddr, &netmask, &gw, NULL, ethernetif_init,netif_input);
    
    /* ethhw_init() is user-defined */
    /* use ip_input instead of ethernet_input for non-ethernet hardware */
    /* (this function is assigned to netif.input and should be called by the hardware driver) */
    netif_set_default(&netif);
    netif_set_up(&netif);
    
    
    /* If DHCP is set in config.h DHCP configuration overwrites standard network address configuration from above */
    
 }



//--------------------------------------------------------------------------
// Interrupt Functions
//--------------------------------------------------------------------------
/*************************************************************************************************  
*   Function Name : INTETNB0DATA, INTETNB1DATA
*   Description   : interrupt function
*                   if there is a new ethernetframe the local status bit is set to 1 
*   Arguments     : none
*   Return Value  : none
*************************************************************************************************/


void INTETNB0DATA_callback(void)
{
    ethernet_AvbDataIsr();
   
}


/*************************************************************************************************  
*   Function Name : ethernet_AvbRx_count
*   Description   : returns the number of received frames
*   Arguments     : none
*   Return Value  : number of received frames
*************************************************************************************************/
uint32_t ethernet_AvbRx_count(void)
{
  return R_AVB_UFCounterGet(ETHETNB0, R_AVB_BECHANNEL);  
}


/*************************************************************************************************  
*   Function Name : ethernet_AvbRx
*   Description   : process the received frames
*   Arguments     : pointer to the received frame
*   Return Value  : none
*************************************************************************************************/
void  ethernet_AvbRx(r_avb_RxSingleFrame_t *frameptr)
{
  uint32_t ris0;
  ris0     = 1;

  
  switch(ris0)
            {
            case 1: /* best effort queue */

                //for (i = 0; i < rxcnt; i++)
                {
                    R_AVB_RxQueueProcess(ETHETNB0, (uint32_t) frameptr, &locRxBeConfig);


                   //     locRxFrame[locRxCnt].FrameAddr = rxframe.FrameAddr;
                    //    locRxFrame[locRxCnt].FrameLength = rxframe.FrameLength;
                    //    locRxCnt ++;

                }

                R_AVB_UFCounterGet(ETHETNB0, R_AVB_BECHANNEL);
                break;

            case 2: /* network control queue */
                break;

            case 4: /* stream 1 reserved */
                break;

            case 8: /* stream 2 reserved*/
                break;

            default:
                break;
            }
  

}


/*************************************************************************************************  
*   Function Name : ethernet_AvbRx
*   Description   : process the received frames
*   Arguments     : pointer to the received frame
*   Return Value  : none
*************************************************************************************************/
void  ethernet_AvbRxdone(uint32_t RxFramePtr)
{
  
R_AVB_RxReadDone(ETHETNB0,RxFramePtr,&locRxBeConfig);
R_AVB_UFCounterDec(ETHETNB0,1,R_AVB_BECHANNEL);

}

/*************************************************************************************************  
*   Function Name : ethernet_AvbDataIsr
*   Description   : interrupt function
*   Arguments     : node
*   Return Value  : none
*************************************************************************************************/
void ethernet_AvbDataIsr(void)
{
    uint32_t txstatus;
    uint32_t ris0;

    txstatus = R_AVB_TxIntGet(ETHETNB0);
    ris0     = R_AVB_RxIntGet(ETHETNB0);


        /*  tx handling */
        if (txstatus & 0xf)
        {
            locTxStatus = 1;
        }

        /* rx handling */
        if (ris0 & 0xf)
        {
           locRxStatus = 1;
        }

}

/*************************************************************************************************  
*   Function Name : ethernet_EthEtnb0IntInit
*   Description   : configure the ethernet interrupt
*   Arguments     : node
*   Return Value  : none
*************************************************************************************************/
static void ethernet_EthEtnb0IntInit(void)
{
    INTC2.EIBD645.BIT.PEID=1;
    INTC2.EIC645.BIT.EIRF645 = 0;
    INTC2.EIC645.BIT.EITB645 = 1;
    INTC2.EIC645.BIT.EIMK645 = 0;
}
/*************************************************************************************************  
*   Function Name : ethernet_RxChannelInit
*   Description   : Initialize the receive channel configuration for best effort traffic
*   Arguments     : none
*   Return Value  : none
*************************************************************************************************/
static void ethernet_RxChannelInit(void)
{
  /* Configure best effort channel parameters */
  locRxBeConfig.ChNum    = R_AVB_BECHANNEL;      /* Best effort channel number */
  locRxBeConfig.ChType   = R_AVB_RX_BE;          /* Channel type: Best effort */
  locRxBeConfig.BufMode  = R_AVB_RX_SFSB;        /* Single frame single buffer mode */
  locRxBeConfig.PHLength = 0;                     /* Protocol Header Length */
  locRxBeConfig.PLength  = 0;                     /* Protocol Length */

  /* Apply the RX descriptor chain configuration */
  R_AVB_RxDescChainConfig(ETHETNB0, &locRxBeConfig);
}

/*************************************************************************************************  
*   Function Name : ethernet_EthEtnb0Init
*   Description   : Initialize the Ethernet AVB interface with the specified configuration
*   Arguments     : none
*   Return Value  : r_avb_Error_t - Error code indicating success/failure
*************************************************************************************************/
uint32_t ethernet_EthEtnb0Init()
{
  r_avb_Error_t     result;

  r_avb_ComConfig_t comconfig;
  r_avb_RxConfig_t  rxconfig;
  r_avb_TxConfig_t  txconfig;
  r_avb_ErrorInt_t  errorint;

  r_avb_MacMode_t   mac_mode;
  r_avb_MacInt_t    max_int_mask;

  r_avb_Config_t    avbconfig;
  r_avb_MacConfig_t macconfig;

  comconfig.Lbme = 0;
  comconfig.Boc  = 0;
  comconfig.Csel = R_AVB_GPTP_PBUS;

  rxconfig.Effs = R_AVB_DISABLE;
  rxconfig.Encf = R_AVB_ENABLE;
  rxconfig.Esf  = R_AVB_AVBNMDISC;
  rxconfig.Ets0 = R_AVB_DISABLE;
  rxconfig.Ets2 = R_AVB_DISABLE;
  rxconfig.Rfcl = 0x1800;

  txconfig.Tsm0 = R_AVB_TXNORMAL;
  txconfig.Tsm1 = R_AVB_TXNORMAL;
  txconfig.Tsm2 = R_AVB_TXNORMAL;
  txconfig.Tsm3 = R_AVB_TXNORMAL;
  txconfig.Tqp  = R_AVB_NONAVB;

  errorint.Mree  = R_AVB_ENABLE;
  errorint.Mtee  = R_AVB_ENABLE;
  errorint.Qee   = R_AVB_ENABLE;
  errorint.See   = R_AVB_ENABLE;
  errorint.Clle0 = R_AVB_ENABLE;
  errorint.Clle1 = R_AVB_ENABLE;
  errorint.Cule0 = R_AVB_ENABLE;
  errorint.Cule1 = R_AVB_ENABLE;
  errorint.Tffe  = R_AVB_ENABLE;
  errorint.Mffe  = R_AVB_ENABLE;

  avbconfig.BufBaseAddr = R_ATF_Ram_NextFreeAddrGet();
  avbconfig.ComConfig   = &comconfig;
  avbconfig.RxConfig    = &rxconfig;
  avbconfig.TxConfig    = &txconfig;
  avbconfig.ErrorInt    = &errorint;


  mac_mode.Speed          = R_AVB_100M;


  mac_mode.Duplex         = R_AVB_FDUPLEX;
  mac_mode.PromMode       = R_AVB_DISABLE;
  mac_mode.MagicDection   = R_AVB_DISABLE;
  mac_mode.TxFlowCtrl     = R_AVB_DISABLE;
  mac_mode.RxFlowCtrl     = R_AVB_DISABLE;
  mac_mode.PFrameRxMode   = R_AVB_DISABLE;
  mac_mode.ZPFrameTx      = R_AVB_DISABLE;
  mac_mode.ZPFrameRx      = R_AVB_DISABLE;
  mac_mode.DPad           = R_AVB_DISABLE;
  mac_mode.RxCrcMode      = R_AVB_DISABLE;
  mac_mode.Tpe            = R_AVB_DISABLE;
  mac_mode.Rpe            = R_AVB_DISABLE;

  max_int_mask.Icdim      = R_AVB_DISABLE;
  max_int_mask.Mpdim      = R_AVB_DISABLE;
  max_int_mask.Linkim     = R_AVB_DISABLE;
  max_int_mask.Phyim      = R_AVB_DISABLE;

  macconfig.MaxFrameLen  = 1518;
  macconfig.Mac_Mode     = &mac_mode;
  macconfig.Mac_Int_Mask = &max_int_mask;
  macconfig.MacAddr     = eth_config[ETHETNB0].mac_address;

  macconfig.SelfTestLoop = 0;
  
  
  ethernet_EthEtnb0IntInit();

  result = R_AVB_Init(ETHETNB0, &avbconfig, &macconfig);
      
  if (result != R_AVB_ERR_OK)
  {
    return result;
  }


  /* set RIC0 interrupt */
  R_AVB_RxIntMaskSet(ETHETNB0, 0xf);

  /* set RIC1 interrupt */
  R_AVB_RxWarningIntMaskSet(ETHETNB0, 0); //0x8000000f);

  /* set RIC2 interrupt */
  R_AVB_RxQFullIntMaskSet(ETHETNB0, 0x8000000f);

  /* set TIC interrupt */
  R_AVB_TxIntMaskSet(ETHETNB0, 0xc0f);

  /* set GIC interrupt */
  R_AVB_GPtpIntMaskSet(ETHETNB0, 0);

  ethernet_RxChannelInit();

  return result;
}


/*************************************************************************************************  
*   Function Name : ethernet_ListenNetwork
*   Description   : Enable MAC communication for both RX and TX channels
*   Arguments     : none
*   Return Value  : none
*************************************************************************************************/
void ethernet_ListenNetwork(void)
{
  R_AVB_MacCommunicationSet(ETHETNB0, R_AVB_RX, R_AVB_ENABLE);
  R_AVB_MacCommunicationSet(ETHETNB0, R_AVB_TX, R_AVB_ENABLE);
}

/*************************************************************************************************  
*   Function Name : ethernet_StopListenNetwork
*   Description   : Disable MAC communication for both RX and TX channels
*   Arguments     : none
*   Return Value  : none
*************************************************************************************************/
void ethernet_StopListenNetwork(void)
{
  R_AVB_MacCommunicationSet(ETHETNB0, R_AVB_RX, R_AVB_DISABLE);
  R_AVB_MacCommunicationSet(ETHETNB0, R_AVB_TX, R_AVB_DISABLE);
}
/*************************************************************************************************  
*   Function Name : lwiperf_report
*   Description   : Callback function for lwIP iPerf server reporting
*   Arguments     : arg - User argument (unused)
*                   report_type - Type of iPerf report
*                   local_addr/port - Local endpoint details
*                   remote_addr/port - Remote endpoint details
*                   bytes_transferred - Total bytes transferred
*                   ms_duration - Test duration in milliseconds
*                   bandwidth_kbitpsec - Calculated bandwidth in kbits/sec
*   Return Value  : none
*************************************************************************************************/
static void
lwiperf_report(void *arg, enum lwiperf_report_type report_type,
  const ip_addr_t* local_addr, u16_t local_port, const ip_addr_t* remote_addr, u16_t remote_port,
  u32_t bytes_transferred, u32_t ms_duration, u32_t bandwidth_kbitpsec)
{
  LWIP_UNUSED_ARG(arg);
  LWIP_UNUSED_ARG(local_addr);
  LWIP_UNUSED_ARG(local_port);
}

/*************************************************************************************************  
*   Function Name : R_ETH_Init
*   Description   : Initialize Ethernet interface including PHY, MAC, and network stack
*   Arguments     : none
*   Return Value  : 0 on success, non-zero on failure
*************************************************************************************************/
uint8_t R_ETH_Init(void)
{
  link_status_t link_status;
  
  // Initialize ATF RAM and ethernet configuration
  R_ATF_Ram_Init((uint32_t)ATF_Ram_area, (int32_t)sizeof(ATF_Ram_area));
  r_ethernetConfigInit();
  
  // Enable PHY by releasing reset
  setGpioHigh(20,0);
  r_ethernetPhy_init(eth_config[ETHETNB0].phy_dev);
  
  // Initialize Ethernet hardware
  ethernet_EthEtnb0Init();

  // Perform loopback test
  if(R_ETH_loopback()==0)
  {
    eth_config[ETHETNB0].phy_loop_back_test = phy_loop_back_test_ok;
  }
  else
  {
    eth_config[ETHETNB0].phy_loop_back_test = phy_loop_back_test_nok;
  }
  
  // Initialize network stack and services
  ethernet_InitLwip();
  httpd_init();
  lwiperf_start_tcp_server_default(lwiperf_report, NULL);

  // Check initial link status and enable if up
  if( r_ethernetPhy_getLinkStatus(eth_config[ETHETNB0].phy_dev,&link_status) == R_PHY_ERR_OK )
  {
    if(link_status == link_status_up)
    {
      eth_config[ETHETNB0].link_status = link_status_up;
      R_AVB_OpModeChange(ETHETNB0, R_AVB_OPERATION);
      ethernet_ListenNetwork();
    }
  }
   
  return( 0 );
}

/*************************************************************************************************  
*   Function Name : R_ETH_Handler
*   Description   : Main ethernet handling function for link status and packet processing
*   Arguments     : none
*   Return Value  : none
*************************************************************************************************/
void R_ETH_Handler(void)
{
  uint32_t current_tick=0;
  link_status_t link_status;

  // Link status monitoring and management
  if(eth_config[ETHETNB0].link_status != link_status_up)
  {
    // Try to establish link if currently down
    if( r_ethernetPhy_getLinkStatus(eth_config[ETHETNB0].phy_dev, &link_status) == R_PHY_ERR_OK )
    {
      if (link_status == link_status_up)
      {
        eth_config[ETHETNB0].link_status = link_status_up;
        R_AVB_OpModeChange(ETHETNB0, R_AVB_OPERATION);
        ethernet_ListenNetwork();
      }
    }
  }
  else
  {
    // Periodic link check when link is up
    if (g_SystemStatus.RunTimeMs%500==0)
    {
      if( r_ethernetPhy_getLinkStatus(eth_config[ETHETNB0].phy_dev, &link_status) == R_PHY_ERR_OK )
      {
        if (link_status == link_status_down)
        {
          if (eth_config[ETHETNB0].link_status == link_status_up)
          {
            eth_config[ETHETNB0].link_status = link_status_down;
            ethernet_StopListenNetwork();
          }
        }
      }
    }
  }

  // Process received packets
  if(1 == locRxStatus)
  {
      locRxStatus = 0;
      ethernetif_input(&netif);
  }

  // Handle lwIP timeouts
  if(g_SystemStatus.RunTimeMs!=current_tick)
  {
    sys_check_timeouts();
    current_tick=g_SystemStatus.RunTimeMs;
  }
}

/*************************************************************************************************  
*   Function Name : R_ETH_loopback
*   Description   : Perform PHY loopback test by sending and receiving a test frame
*   Arguments     : none
*   Return Value  : 0 on success, 1 on failure
*************************************************************************************************/
uint8_t R_ETH_loopback(void)
{
  uint32_t i;
  uint64_t time;
  uint8_t*               locTxBuf_ptr;
  uint8_t*              locRxBuf_ptr;
  uint8_t              return_value=0;
  r_avb_TxSingleFrame_t frameTx;
  r_avb_RxSingleFrame_t locRxFrame;
  r_ethernetPhy_setLoopBack(eth_config[ETHETNB0].phy_dev, phy_loop_back_enabled);
  r_ethernetPhy_setLoopBack(eth_config[ETHETNB0].phy_dev, phy_loop_back_enabled);
  R_AVB_OpModeChange(ETHETNB0, R_AVB_OPERATION);
  ethernet_ListenNetwork();


  R_AVB_SingleDescGetNextFreeTxBuffer(ETHETNB0, 0, &frameTx);

  locTxBuf_ptr=(uint8_t *)frameTx.Address;
  locTxBuf_ptr[0] = 0xff;
  locTxBuf_ptr[1] = 0xff;
  locTxBuf_ptr[2] = 0xff;
  locTxBuf_ptr[3] = 0xff;
  locTxBuf_ptr[4] = 0xff;
  locTxBuf_ptr[5] = 0xff;
  locTxBuf_ptr[6] = 0x91; 
  locTxBuf_ptr[7] = 0xe0; 
  locTxBuf_ptr[8] = 0xf0; 
  locTxBuf_ptr[9] = 0x00; 
  locTxBuf_ptr[10] = 0x00; 
  locTxBuf_ptr[11] = 0x01; 
  for(i=6; i<100; i++)
  {
      locTxBuf_ptr[i] = i;
  }
    /*The Ethernet type (ET) is 08:00.*/
  locTxBuf_ptr[12] = 0x08;
  locTxBuf_ptr[13] = 0x00;


  frameTx.Address   = (uint32_t)locTxBuf_ptr;
  frameTx.Length    = 64;
  frameTx.Timestamp = R_AVB_DISABLE;
  frameTx.MacStatus = R_AVB_DISABLE;
  frameTx.Tag = 1;
  R_AVB_SingleDescFrameSend(ETHETNB0, 0, &frameTx);

  time = R_SysTimer_Read();
    while( locRxStatus == 0  ) {
        if(R_SysTimer_Read() > time+R_SYSTIMER_10MSECOND) {
            return_value=1;
        }
    }

  if( locRxStatus == 1 ) 
  {
    locRxStatus = 0;
    R_AVB_RxQueueProcess(ETHETNB0, (uint32_t) &locRxFrame, &locRxBeConfig);
    /* Check payload & Header returned, without CRC */
    locRxBuf_ptr = ( uint8_t *)( locRxFrame.FrameAddr );
    for( i=0; i<60; i++ )
    {
      if( locTxBuf_ptr[ i ] != locRxBuf_ptr[ i ] )return_value=1;
    }
    ethernet_AvbRxdone( (uint32_t)&locRxFrame );
  }
   
  r_ethernetPhy_setLoopBack(eth_config[ETHETNB0].phy_dev, phy_loop_back_disabled);
  ethernet_StopListenNetwork();
return return_value;
}
