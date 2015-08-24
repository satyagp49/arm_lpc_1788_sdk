/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               uctsk_LWIP.c
** Descriptions:            The uctsk_LWIP application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2011-3-2
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
#include "search.h"
#include "webpage.h"
#include <includes.h> 
/* lwIP includes. */
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/memp.h"
#include "lwip/stats.h"
#include "netif/loopif.h"
#include "ip.h"

/* Private variables ---------------------------------------------------------*/
static  OS_STK  AppLWIPTaskStk[APP_TASK_LWIP_STK_SIZE];
uint8_t webpage [sizeof(WebSide)];

/* Private function prototypes -----------------------------------------------*/
static  void    uctsk_LWIP  (void *pdata);
static  void    ADC_Configuration(void);
static  void    vHandler_HTTP(struct netconn  *pstConn);
static  void    __Handler_HTTPGet(struct netconn  *pstConn);


void  App_LWIPTaskCreate (void)
{
    CPU_INT08U  os_err;

	os_err = os_err; /* prevent warning... */

	os_err = OSTaskCreate((void (*)(void *)) uctsk_LWIP,				
                          (void          * ) 0,							
                          (OS_STK        * )&AppLWIPTaskStk[APP_TASK_LWIP_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_LWIP_PRIO  );							

	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_LWIP_PRIO, "Task LWIP", &os_err);
	#endif
}

static  void    uctsk_LWIP(void *pdata)
{

	struct netconn  *__pstConn, *__pstNewConn; 

    Init_lwIP();

	ADC_Configuration();

    __pstConn = netconn_new(NETCONN_TCP);
    netconn_bind(__pstConn, NULL,80);
    netconn_listen(__pstConn);

	for(;;)
   	{
		__pstNewConn = netconn_accept(__pstConn);
		
		if(__pstNewConn != NULL)
		{			
			vHandler_HTTP(__pstNewConn);
			while(netconn_delete(__pstNewConn) != ERR_OK)
			{
				OSTimeDlyHMSM(0, 0, 0, 10);
			}
		}
    }
}

/*******************************************************************************
* Function Name  : vHandler_HTTP
* Description    : HTTP处理
* Input          : - pstConn: 指向struct netconn结构的指针
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void vHandler_HTTP(struct netconn  *pstConn)
{
	struct netbuf 		*__pstNetbuf;
	INT8S			*__pbData;
	u16_t			__s32Len;

 	__pstNetbuf = netconn_recv(pstConn);
	if(__pstNetbuf != NULL)
	{
		netbuf_data (__pstNetbuf, (void *)&__pbData, &__s32Len );

		if( strstr( (void *)__pbData, "GET" ) != NULL )
		{
			__Handler_HTTPGet(pstConn); 
	    }
	}
	netbuf_delete(__pstNetbuf);	
	netconn_close(pstConn);
}

/*******************************************************************************
* Function Name  : __Handler_HTTPGet
* Description    : 处理HTTP协议的GET请求
* Input          : - pstConn: 指向struct netconn结构的指针
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void __Handler_HTTPGet(struct netconn  *pstConn)
{
    static uint16_t pagecount = 0;
	uint16_t AD_value;
	int8_t *ptr;

	/* Start conversion */
//	ADC_StartCmd(LPC_ADC,ADC_START_NOW);
	/* Wait conversion complete */
//	while (!(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_5,ADC_DATA_DONE)));
//	AD_value = ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_5);

	memcpy ( webpage , WebSide ,sizeof(WebSide) );

	if( ( ptr = memstrExt( (void *)webpage,"AD8%",strlen("AD8%"),sizeof(webpage)) ) != NULL )
	{
		sprintf( (void *)ptr, "%3d", AD_value);       /* insert AD converter value */
	}	

	if( ( ptr = memstrExt( (void *)webpage,"AD7%",strlen("AD7%"),sizeof(webpage)) ) != NULL )
	{ 
		AD_value = ( AD_value * 100 ) / 4000;
		* ( ptr + 0 ) = '0' + AD_value / 100;
		* ( ptr + 1 ) = '0' + ( AD_value / 10 ) % 10;
		* ( ptr + 2 ) = '0' + AD_value % 10;
	}

	if( ( ptr = memstrExt( (void *)webpage,"AD1%",strlen("AD1%"),sizeof(webpage)) ) != NULL )
	{ 
		sprintf( (void *)ptr, "%3u", ++pagecount );  
	}		
	netconn_write(pstConn, "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n", \
	              strlen("HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n"), NETCONN_COPY);

    netconn_write(pstConn, webpage, sizeof(webpage), NETCONN_COPY);	/* HTTP网页 */
}

/*******************************************************************************
* Function Name  : ADC_Configuration
* Description    : Configure the ADC.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void ADC_Configuration(void)
{

}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
