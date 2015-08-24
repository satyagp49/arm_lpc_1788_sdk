/**********************************************************************
* $Id$		Emc_SdramDemo.c		2011-06-02
*//**
* @file		Emc_SdramDemo.c
* @brief	This example describes how to use EMC interface on LPC177x_8x
* 				to connect with external SDRAM
* @version	1.0
* @date		02. June. 2011
* @author	NXP MCU SW Application Team
*
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/
#include <stdio.h>
#include "lpc_types.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_pinsel.h"

 
#include "TouchPanel.h"

#include "glcd.h"
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
	TP_Init(); 
    SDRAM_32M_16BIT_Init();
	GLCD_Init();

	TouchPanel_Calibrate( GLCD_X_SIZE, GLCD_Y_SIZE);
	/* Infinite loop */
	while (1)	
	{
		calibrate();
	}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
