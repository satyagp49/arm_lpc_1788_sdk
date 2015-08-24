/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            This example describes how to use SST25VF016B functionality on SPI of LPC1788
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2012-8-18
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
#include <string.h>
#include "lpc_types.h"
#include "SST25VF016B.h"
#include "FlashDriver.h"
#include "debug_frmwrk.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_pinsel.h"

/* Private variables ---------------------------------------------------------*/
uint8_t  ReadBuffer[256];
uint8_t  WriteBuffer[256];

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
    uint16_t  i;
    uint32_t  ChipID = 0;	
	
	SPI_FLASH_Init();

	debug_frmwrk_init();

	_DBG_("*****************************************************************\n");
	_DBG_("*                                                               *\n");
	_DBG_("*   Thank you for using HY-LPC1788-SDK Development Board £¡^_^  *\n");
	_DBG_("*                                                               *\n");
	_DBG_("*****************************************************************\n");

  	SSTF016B_ReadID( JEDEC_ID, &ChipID );

    ChipID &= ~0xff000000;				/* retain low 24 bits data */
	if ( ChipID != 0xBF2541 ) 			/* ChipID is 0xBF2541 */
	{	
		_DBG_("HY-LPC1788-SDK SPI Flash SST25VF016B Read ID False");
    }

	df_write_open( 0 );
	df_read_open( 0 );
	SSTF016B_Erase( 0, 0 );
	
	for( i = 0; i < 256; i++ )
	{
	    WriteBuffer[i] = i;
	}

	df_write( WriteBuffer, sizeof(WriteBuffer) );

	df_read( ReadBuffer, sizeof(ReadBuffer) );

	/* Matching data */
	if( memcmp( WriteBuffer, ReadBuffer, sizeof(WriteBuffer) ) == 0 )  
	{
		_DBG_("HY-LPC1788-SDK SPI Flash SST25VF016B OK");
	}
	else
	{
		_DBG_("HY-LPC1788-SDK SPI Flash SST25VF016B False");
	}

    for(;;)
   	{  
    }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
