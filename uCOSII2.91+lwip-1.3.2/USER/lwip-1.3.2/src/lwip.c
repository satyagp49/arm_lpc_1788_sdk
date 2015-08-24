/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               LWIP.c
** Descriptions:            None
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2011-3-10
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lwip/memp.h"
#include "lwIP.h"
#include "lwIP/tcp.h"
#include "lwIP/udp.h"
#include "lwIP/tcpip.h"
#include "netif/etharp.h"
#include "lwIP/dhcp.h"
#include "ethernetif.h"
#include "arch/sys_arch.h"
#include <includes.h>

#include "debug_frmwrk.h"

/* Private variables ---------------------------------------------------------*/
struct netif _netif;

/* Global Rx Buffer data */
uint8_t __attribute__ ((aligned (4))) gTxBuf[EMAC_MAX_PACKET_SIZE];

/* Private function prototypes -----------------------------------------------*/
static void TcpipInitDone          (void *arg);


/*******************************************************************************
* Function Name  : TcpipInitDone
* Description    : TcpipInitDone wait for tcpip init being done
* Input          : - arg: the semaphore to be signaled
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void TcpipInitDone(void *arg)
{
    sys_sem_t *sem;
    sem = arg;
    sys_sem_signal(*sem);
}

/*******************************************************************************
* Function Name  : Ethernet_Initialize
* Description    : Ethernet Initialize function
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Ethernet_Initialize(void)
{	 
    Init_EMAC();
}

/*******************************************************************************
* Function Name  : ethernet_send
* Description    : transmit an Ethernet frame to MAC/DMA controller
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int ethernet_send(void *pPacket, int size)
{

}

/*******************************************************************************
* Function Name  : Init_lwIP
* Description    : Init_lwIP initialize the LwIP
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Init_lwIP(void)
{
    struct ip_addr ipaddr;
    struct ip_addr netmask;
    struct ip_addr gw;

    sys_sem_t sem;
    
    sys_init();
    
    /* Initializes the dynamic memory heap defined by MEM_SIZE.*/
    mem_init();
    
    /* Initializes the memory pools defined by MEMP_NUM_x.*/
    memp_init();
    
    pbuf_init();	
    netif_init();
    
	debug_frmwrk_init();

    _DBG_("TCP/IP initializing... \r\n");
    sem = sys_sem_new(0);
    tcpip_init(TcpipInitDone, &sem);
    sys_sem_wait(sem);
    sys_sem_free(sem);
    _DBG_("TCP/IP initialized. \r\n");
      
#if LWIP_DHCP
    /* Enable DHCP client*/
    ipaddr.addr = 0;
    netmask.addr = 0;
    gw.addr = 0;
#else
    /* Enable static IP */
    IP4_ADDR(&ipaddr, emacIPADDR0, emacIPADDR1, emacIPADDR2, emacIPADDR3 );
    IP4_ADDR(&netmask,emacNET_MASK0, emacNET_MASK1, emacNET_MASK2, emacNET_MASK3 );
    IP4_ADDR(&gw, emacGATEWAY_ADDR0, emacGATEWAY_ADDR1, emacGATEWAY_ADDR2, emacGATEWAY_ADDR3 );
#endif
    
    
    netif_add(&_netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);
    netif_set_default(&_netif);
    
#if LWIP_DHCP
    dhcp_start(&_netif);
#endif
    netif_set_up(&_netif);
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
