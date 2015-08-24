/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            This example describes how to use UART interface on LPC177x_8x
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

	_DBG_("*****************************************************************\n");
	_DBG_("*                                                               *\n");
	_DBG_("*   Thank you for using HY-LPC1788-SDK Development Board £¡^_^  *\n");
	_DBG_("*                                                               *\n");
	_DBG_("*****************************************************************\n");

    /* Serial port receive data */
	/* import HY-LPC1788-SDK */
	while(_DG !='H');
	while(_DG !='Y');
	while(_DG !='-');
	while(_DG !='L');
	while(_DG !='P');
	while(_DG !='C');
	while(_DG !='1');
	while(_DG !='7');
	while(_DG !='8');
	while(_DG !='8');
	while(_DG !='-');
	while(_DG !='S');
	while(_DG !='D');
	while(_DG !='K');

	/* successful received data */
    _DBG_("received data OK\n");

	/* Infinite loop */
	while(1)
	{
	}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
