/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            This example describes how to use software I2C to drive with AT24C02
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2012-8-20
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
#include "AT24C02.h"
#include "lpc_types.h"
#include "lpc177x_8x.h"
#include "debug_frmwrk.h"


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

	I2C_Configuration();

	debug_frmwrk_init();

	_DBG_("*****************************************************************\n");
	_DBG_("*                                                               *\n");
	_DBG_("*   Thank you for using HY-LPC1788-Core Development Board £¡^_^ *\n");
	_DBG_("*                                                               *\n");
	_DBG_("*****************************************************************\n");

	for( i = 0; i < 256; i++ )
	{
	    WriteBuffer[i] = i;
	}

	/* EEPROM AT24C02 write data */
   	_DBG_("HY-LPC1788-Core EEPROM AT24C02 write");

	for( i = 0; i < 256; i++ )
	{
	    while( I2C_WriteByte(WriteBuffer[i], i,  ADDR_24LC02) );
	}

   	_DBG_("HY-LPC1788-Core EEPROM AT24C02 write OK");

	/* EEPROM AT24C02 read data */
   	_DBG_("HY-LPC1788-Core EEPROM AT24C02 read");

	/* Matching data */
	while( I2C_ReadByte(ReadBuffer, sizeof(WriteBuffer),0, ADDR_24LC02) );

	if(  memcmp( WriteBuffer, ReadBuffer, sizeof(WriteBuffer) ) == 0 )
	{
	    _DBG_("HY-LPC1788-Core EEPROM AT24C02 read OK");
	}
	else
	{
	    _DBG_("HY-LPC1788-Core EEPROM AT24C02 read False");
	}
	/* Infinite loop */
	while(1)
	{
	}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
