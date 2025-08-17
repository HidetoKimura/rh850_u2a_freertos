/**
 * @file
 * Ethernet Interface Skeleton
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/*
 * This file is a skeleton for developing Ethernet network interface
 * drivers for lwIP. Add code to the low_level functions and do a
 * search-and-replace for the word "ethernetif" to replace it with
 * something that better describes your network interface.
 */

#include <string.h>
#include "inc\common.h"

#include "modules\eth\r_eth.h"

#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "netif/etharp.h"


/* Define those to better describe your network interface. */
#define IFNAME0 'e'
#define IFNAME1 'n'
#define ETHAVB0     0


extern r_avb_RxChConfig_t locRxBeConfig;


extern ethernet_t eth_config[ETHAVBCOUNT];
/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
struct ethernetif {
  struct eth_addr *ethaddr;
  /* Add whatever per-interface state that is needed here. */
};

/* Forward declarations. */
void  ethernetif_input(struct netif *netif);
err_t ethernetif_init(struct netif *netif);

/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
static void
low_level_init(struct netif *netif)
{
  /* set MAC hardware address length */
  netif->hwaddr_len = ETHARP_HWADDR_LEN;

  /* set MAC hardware address */
  netif->hwaddr[0] = eth_config[ETHAVB0].mac_address[0];
  netif->hwaddr[1] = eth_config[ETHAVB0].mac_address[1];
  netif->hwaddr[2] = eth_config[ETHAVB0].mac_address[2];
  netif->hwaddr[3] = eth_config[ETHAVB0].mac_address[3];
  netif->hwaddr[4] = eth_config[ETHAVB0].mac_address[4];
  netif->hwaddr[5] = eth_config[ETHAVB0].mac_address[5];

  /* maximum transfer unit */
  netif->mtu = 1500;
  
  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;
 
  /* Do whatever else is needed to initialize interface. */  
}


/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

uint32_t memcpy_from_pbuf(unsigned char *dest, struct pbuf *p)
{
 unsigned count=0;
 uint32_t tot_len = p->tot_len;
 while(count<tot_len)
 {
  memcpy (dest+count,p->payload,p->len);    // the data is copied from p->payload to the destination address (start address + count offset)
  count+=p->len;                            // the count offset is updated
  p=p->next;                                // the source address is set to the next pbuf address from the pbuf chain
 }
 return tot_len;
}

static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{

  r_avb_TxSingleFrame_t frameTx;
 

#if ETH_PAD_SIZE
  pbuf_remove_header(p, ETH_PAD_SIZE); /* drop the padding word */
#endif
R_AVB_SingleDescGetNextFreeTxBuffer(ETHAVB0, 0, &frameTx);
frameTx.Length=memcpy_from_pbuf((unsigned char *) frameTx.Address, p);
frameTx.Timestamp = R_AVB_DISABLE;
frameTx.MacStatus = R_AVB_DISABLE;
frameTx.Tag = 1;
R_AVB_SingleDescFrameSend(ETHAVB0, 0, &frameTx);


#if ETH_PAD_SIZE
  pbuf_add_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

  LINK_STATS_INC(link.xmit);
  /* Increment counter for total number of sent frames */
  eth_config[ETHAVB0].sent_frames++;
  return ERR_OK;
}


void memcpy_to_pbuf(  struct pbuf *p,unsigned char *src,unsigned int tot_len)
{
 unsigned count=0;

 while(count<tot_len)
 {
  memcpy (p->payload, src+count,p->len);
  count+=p->len;
  p=p->next;
 }
}

/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *
low_level_input(struct netif *netif)
{

  struct pbuf *p;
  r_avb_RxSingleFrame_t locRxFrame;
  r_avb_RxSingleFrame_t *locRxFrameptr;

 locRxFrameptr=&locRxFrame;


  /* Obtain the size of the packet and put it into the "len"
     variable. */

   ethernet_AvbRx(locRxFrameptr);

  /* We allocate a pbuf chain of pbufs from the pool. */
   
  #if ETH_PAD_SIZE
    p = pbuf_alloc(PBUF_RAW, locRxFrame.FrameLength + ETH_PAD_SIZE, PBUF_POOL);  /* Compensate for data misalignment */
  #else
    p = pbuf_alloc(PBUF_RAW, locRxFrame.FrameLength, PBUF_POOL);
  #endif

  
  if (p != NULL) {

    #if ETH_PAD_SIZE
        pbuf_remove_header(p, ETH_PAD_SIZE); /* drop the padding word */
    #endif

    /* We iterate over the pbuf chain until we have read the entire*/
    /* packet into the pbuf. */
    memcpy_to_pbuf(p,(unsigned char *)locRxFrame.FrameAddr,locRxFrame.FrameLength);
    
    /*acknowledge that packet has been read*/
    ethernet_AvbRxdone((uint32_t)&locRxFrame);
    #if ETH_PAD_SIZE
      pbuf_add_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
    #endif
    LINK_STATS_INC(link.recv);

  } else {
    /* drop packet(); */
    LINK_STATS_INC(link.memerr);
    LINK_STATS_INC(link.drop);
    MIB2_STATS_NETIF_INC(netif, ifindiscards);
  }
  
  /* Increment counter for total number of received frames */
  eth_config[ETHAVB0].received_frames++;


  return p;  
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
 void
ethernetif_input(struct netif *netif)
{
  //struct ethernetif *ethernetif;
  struct eth_hdr *ethhdr;
  struct pbuf *p;

  //ethernetif = netif->state;


  while(ethernet_AvbRx_count()>0)
  {
    #ifdef DEBUG_FLOW
        printf("Receive ethernetif_input count: %i \r\n",ethernet_AvbRx_count());
    #endif
    /* move received packet into a new pbuf */
    p = low_level_input(netif);
    /* no packet could be read, silently ignore this */
    if (p == NULL) return;
    /* points to packet payload, which starts with an Ethernet header */
    ethhdr = p->payload;

 
    switch (htons(ethhdr->type)) {
    /* IP or ARP packet? */
    case ETHTYPE_IP:
    case ETHTYPE_ARP:
  #if PPPOE_SUPPORT
    /* PPPoE packet? */
    case ETHTYPE_PPPOEDISC:
    case ETHTYPE_PPPOE:
  #endif /* PPPOE_SUPPORT */
      /* full packet send to tcpip_thread to process */
     #ifdef DEBUG_FLOW
        if(p->tot_len>500)
        {
        __NOP();
        }
    #endif
      if (netif->input(p, netif)!=ERR_OK)
       { 
            #ifdef DEBUG_FLOW
        printf("ERROR\r\n");
    #endif
         pbuf_free(p);
         p = NULL;
       }
      break;
  
    default:
      pbuf_free(p);
      p = NULL;
      break;
     
    }

  }
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t
ethernetif_init(struct netif *netif)
{
  struct ethernetif *ethernetif;

  LWIP_ASSERT("netif != NULL", (netif != NULL));
    
  ethernetif = mem_malloc(sizeof(struct ethernetif));
  if (ethernetif == NULL) {
    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_init: out of memory\n"));
    return ERR_MEM;
  }

  #if LWIP_NETIF_HOSTNAME
    /* Initialize interface hostname */
    netif->hostname = "RH850_DEMO";
  #endif /* LWIP_NETIF_HOSTNAME */

  /*
   * Initialize the snmp variables and counters inside the struct netif.
   * The last argument should be replaced with your link speed, in units
   * of bits per second.
   */
  NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, 100000000);

  netif->state = ethernetif;
  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;
  /* We directly use etharp_output() here to save a function call.
   * You can instead declare your own function an call etharp_output()
   * from it if you have to do some checks before sending (e.g. if link
   * is available...) */
  netif->output = etharp_output;
  netif->linkoutput = low_level_output;
  
  ethernetif->ethaddr = (struct eth_addr *)&(netif->hwaddr[0]);
  
  /* initialize the hardware */
  low_level_init(netif);

  return ERR_OK;
}


