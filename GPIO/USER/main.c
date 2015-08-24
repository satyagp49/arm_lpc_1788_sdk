/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            This example describes how to use GPIO on LPC177x_8x
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
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_pinsel.h"


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
	/* LED1   P2.21 CORE and SDK Both*/
	/* LED2   P1.13 SDK Only */      
	/* LED3   P5.0  SDK Only */        
	/* LED4   P5.1  SDK Only */    		
	PINSEL_ConfigPin(2,21,0);	   /* P2.21 - GPIO */
    GPIO_SetDir(2, (1<<21), 1);

	PINSEL_ConfigPin(1,13,0);	   /* P2.21 - GPIO */
    GPIO_SetDir(1, (1<<13), 1);

	PINSEL_ConfigPin(5,0,0);	   /* P2.21 - GPIO */
    GPIO_SetDir(5, (1<<0), 1);

	PINSEL_ConfigPin(5,1,0);	   /* P2.21 - GPIO */
    GPIO_SetDir(5, (1<<1), 1);

    for(;;)
   	{  
		/*====LED-ON=======*/
		GPIO_ClearValue( 2, (1<<21) ); 
		GPIO_ClearValue( 1, (1<<13) );  
		GPIO_ClearValue( 5, (1<<0) );  
		GPIO_ClearValue( 5, (1<<1) );  
		Delay(0xfffff);
		Delay(0xfffff);	
		/*====LED-OFF=======*/
		GPIO_SetValue( 2, (1<<21) ); 
		GPIO_SetValue( 1, (1<<13) );  
		GPIO_SetValue( 5, (1<<0) );  
		GPIO_SetValue( 5, (1<<1) );  
		Delay(0xfffff);
		Delay(0xfffff);
    }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
