/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            This example describes how to use button on LPC177x_8x
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2012-8-13
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
#include "lpc_types.h"
#include "lpc177x_8x.h"
#include "debug_frmwrk.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_pinsel.h"


/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configure GPIO Pin
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GPIO_Configuration(void)
{
	/* ISP	     P2.10 */
	/* KEY_UP	 P0.17 */
	/* KEY_DOWN	 P0.18 */
	/* KEY_LEFT	 P0.19 */
	/* KEY_RIGHT P0.20 */
    /* KEY_OK	 P0.21 */
	/* KEY_EXIT	 P0.22 */

	PINSEL_ConfigPin(2,10,0);	   /* P2.10 - GPIO */
	PINSEL_ConfigPin(0,17,0);	   /* P0.17 - GPIO */
	PINSEL_ConfigPin(0,18,0);	   /* P0.18 - GPIO */
	PINSEL_ConfigPin(0,19,0);	   /* P0.19 - GPIO */
	PINSEL_ConfigPin(0,20,0);	   /* P0.20 - GPIO */
	PINSEL_ConfigPin(0,21,0);	   /* P0.21 - GPIO */
	PINSEL_ConfigPin(0,22,0);	   /* P0.22 - GPIO */

    GPIO_SetDir(2, (1<<10), 0);    /* Input Mode */
    GPIO_SetDir(0, (1<<17), 0);    /* Input Mode */
    GPIO_SetDir(0, (1<<18), 0);	   /* Input Mode */
    GPIO_SetDir(0, (1<<19), 0);	   /* Input Mode */
    GPIO_SetDir(0, (1<<20), 0);	   /* Input Mode */
    GPIO_SetDir(0, (1<<21), 0);	   /* Input Mode */
    GPIO_SetDir(0, (1<<22), 0);	   /* Input Mode */
}

/*******************************************************************************
* Function Name  : Delay
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void  Delay (uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{
	debug_frmwrk_init();
    GPIO_Configuration();

	_DBG_("*****************************************************************\n");
	_DBG_("*                                                               *\n");
	_DBG_("*   Thank you for using HY-LPC1788-SDK Development Board £¡^_^  *\n");
	_DBG_("*                                                               *\n");
	_DBG_("*****************************************************************\n");

	/* Infinite loop */
	while(1)
	{
        if( !(GPIO_ReadValue(2)&(1<<10))  )
		{   
			Delay(0x2fffff);
			if( !(GPIO_ReadValue(2)&(1<<10))  )
			_DBG_("ISP is press\n");
		}

        if( !(GPIO_ReadValue(0)&(1<<17))  )
		{   
			Delay(0x2fffff);
			if( !(GPIO_ReadValue(0)&(1<<17))  )
			_DBG_("KEY_UP is press\n");
		}

        if( !(GPIO_ReadValue(0)&(1<<18))  )
		{   
			Delay(0x2fffff);
			if( !(GPIO_ReadValue(0)&(1<<18))  )
			_DBG_("KEY_DOWM is press\n");
		}

        if( !(GPIO_ReadValue(0)&(1<<19))  )
		{   
			Delay(0x2fffff);
			if( !(GPIO_ReadValue(0)&(1<<19))  )
			_DBG_("KEY_LEFT is press\n");
		}

        if( !(GPIO_ReadValue(0)&(1<<20))  )
		{   
			Delay(0x2fffff);
			if( !(GPIO_ReadValue(0)&(1<<20))  )
			_DBG_("KEY_RIGHT is press\n");
		}

        if( !(GPIO_ReadValue(0)&(1<<21))  )
		{   
			Delay(0x2fffff);
			if( !(GPIO_ReadValue(0)&(1<<21))  )
			_DBG_("KEY_OK is press\n");
		}

        if( !(GPIO_ReadValue(0)&(1<<22))  )
		{   
			Delay(0x2fffff);
			if( !(GPIO_ReadValue(0)&(1<<22))  )
			_DBG_("KEY_EXIT is press\n");
		}
	}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
