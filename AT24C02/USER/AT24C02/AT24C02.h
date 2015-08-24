/****************************************Copyright (c)**************************************************                         
**
**                                 http://www.powermcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			AT24C02.c
** Descriptions:		None
**
**------------------------------------------------------------------------------------------------------
** Created by:			AVRman
** Created date:		2012-8-20
** Version:				1.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			
** Modified date:	
** Version:
** Descriptions:		
********************************************************************************************************/
#ifndef __AT24C02_H
#define __AT24C02_H

/* Includes ------------------------------------------------------------------*/
#include "lpc177x_8x.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_pinsel.h"

/* Private define ------------------------------------------------------------*/
#define SCL_H         GPIO_SetValue(2, (1<<15))
#define SCL_L         GPIO_ClearValue(2, (1<<15))
   
#define SDA_H         GPIO_SetValue(2, (1<<14))
#define SDA_L         GPIO_ClearValue(2, (1<<14))

#define SDA_read      (GPIO_ReadValue(2)&(1<<14))

#define I2C_PageSize  8

#define ADDR_24LC02		0xA0

/* Private function prototypes -----------------------------------------------*/
void I2C_Configuration(void);
int I2C_WriteByte(uint8_t SendByte, uint16_t WriteAddress, uint8_t DeviceAddress);
int I2C_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint16_t ReadAddress,  uint8_t DeviceAddress);

#endif 
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
