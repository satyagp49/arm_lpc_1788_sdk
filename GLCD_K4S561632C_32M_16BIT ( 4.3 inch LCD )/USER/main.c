/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            This example describes how to use GLCD on LPC177x_8x
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2012-8-16
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
#include "GLCD.h"
#include "lpc_types.h"


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
    SDRAM_32M_16BIT_Init();	  
    GLCD_Init();

	GLCD_Clear(Black);
	Delay(0xffffff);

	GLCD_Clear(White);
	Delay(0xffffff);

	GLCD_Clear(Red);
	Delay(0xffffff);

	GLCD_Clear(Green);
	Delay(0xffffff);

	GLCD_Clear(Blue);
	Delay(0xffffff);
	 
	GUI_Text( ( GLCD_X_SIZE - 120 ) / 2, GLCD_Y_SIZE / 2 - 8, "HY-LPC1788-Core", White, Blue);
	GUI_Text( ( GLCD_X_SIZE - 136 ) / 2, GLCD_Y_SIZE / 2 + 8, "Development Board", White, Blue);
	 
	while( 1 )
	{ 	

	}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
