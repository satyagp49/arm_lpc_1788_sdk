/****************************************Copyright (c)**************************************************                         
**
**                                 http://www.powermcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			AT24C02.c
** Descriptions:		AT24C02 Function
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

/* Includes ------------------------------------------------------------------*/
#include "AT24C02.h"

/*******************************************************************************
* Function Name  : I2C_Configuration
* Description    : configuration
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void I2C_Configuration(void)
{
    PINSEL_ConfigPin(2,14,0);	   /* P2.14 - GPIO */
    PINSEL_ConfigPin(2,15,0);	   /* P2.14 - GPIO */

    GPIO_SetDir(2, (1<<14), 1);	   /* Output Mode */
    GPIO_SetDir(2, (1<<15), 1);	   /* Output Mode */
}

/*******************************************************************************
* Function Name  : I2C_delay
* Description    : delay time
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void I2C_delay(void)
{	
	uint8_t i = 200;
	while(i) 
	{ 
		i--; 
	} 
}

/*******************************************************************************
* Function Name  : I2C_Start
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int I2C_Start(void)
{
	SDA_H;
	SCL_H;
	I2C_delay();

	if( !SDA_read )
	{
		return -1;	/* SDA low, bus is busy, exit */
	}

	SDA_L;
	I2C_delay();

	if( SDA_read )
	{
		return -1;	/* SDA high, bus error, exit */
	}

	SDA_L;
	I2C_delay();
	return 0;
}

/*******************************************************************************
* Function Name  : I2C_Stop
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void I2C_Stop(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
}

/*******************************************************************************
* Function Name  : I2C_Ack
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void I2C_Ack(void)
{	
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}

/*******************************************************************************
* Function Name  : I2C_NoAck
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void I2C_NoAck(void)
{	
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}

/*******************************************************************************
* Function Name  : I2C_WaitAck
* Description    : None
* Input          : None
* Output         : None
* Return         : Return 0 ACK, Return -1 no ACK
* Attention		 : None
*******************************************************************************/
int I2C_WaitAck(void) 	
{
	SCL_L;
	I2C_delay();
	SDA_H;			
	I2C_delay();
	SCL_H;
	I2C_delay();
	if( SDA_read )
	{
		SCL_L;
		return -1;
	}
	SCL_L;
	return 0;
}

 /*******************************************************************************
* Function Name  : I2C_SendByte
* Description    : Send data high to low
* Input          : - SendByte: send data
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void I2C_SendByte(uint8_t SendByte) 
{
	uint8_t i = 8;

	while(i--)
	{
		SCL_L;
		I2C_delay();
		if( SendByte & 0x80 )
		{
			SDA_H;
		} 
		else 
		{
			SDA_L; 
		} 
		SendByte <<= 1;
		I2C_delay();
		SCL_H;
		I2C_delay();
	}
	SCL_L;
}


/*******************************************************************************
* Function Name  : I2C_ReceiveByte
* Description    : read data high to low
* Input          : None
* Output         : None
* Return         : return data
* Attention		 : None
*******************************************************************************/
int I2C_ReceiveByte(void)  
{ 
	uint8_t i = 8;
	uint8_t ReceiveByte = 0;
	
	SDA_H;				
	while(i--)
	{
		ReceiveByte <<= 1;      
		SCL_L;
		I2C_delay();
		SCL_H;
		I2C_delay();	
		if( SDA_read )
		{
			ReceiveByte |= 0x01;
		}
	}
	SCL_L;
	return ReceiveByte;
}

/*******************************************************************************
* Function Name  : I2C_WriteByte
* Description    : I2C write a byte data
* Input          : - SendByte: byte data
*           	   - WriteAddress: address
*                  - DeviceAddress: device address
* Output         : None
* Return         : Return 0 OK, Return -1 fail
* Attention		 : None
*******************************************************************************/           
int I2C_WriteByte( uint8_t SendByte, uint16_t WriteAddress, uint8_t DeviceAddress )
{		
    if( I2C_Start() )
	{
	    return -1;
	}

	/* Set high starting address + device address */
    I2C_SendByte( ( ( WriteAddress & 0x0700 ) >> 7 ) | DeviceAddress & 0xFFFE );

    if( I2C_WaitAck() )
	{
	    I2C_Stop(); 
		return -1;
	}

	/* Set low starting address */
    I2C_SendByte( (uint8_t) ( WriteAddress & 0x00FF ) );      
    I2C_WaitAck();	
    I2C_SendByte(SendByte);
    I2C_WaitAck();   
    I2C_Stop(); 
	/* Wait EEPROM AT24C02 write done */
    /* Systick_Delay_1ms(10); */
    return 0;
}									 

/*******************************************************************************
* Function Name  : I2C_ReadByte
* Description    : I2C read a byte data
* Input          : - pBuffer: read buffer
*           	   - length: read data size
*                  - ReadAddress: read address
*                  - DeviceAddress: device address
* Output         : None
* Return         : Return 0 OK, Return -1 fail
* Attention		 : None
*******************************************************************************/          
int I2C_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint16_t ReadAddress,  uint8_t DeviceAddress)
{		
    if( I2C_Start() )
	{
		return -1;
	}
	/* Set high starting address + device address */
    I2C_SendByte( ( ( ReadAddress & 0x0700) >> 7 ) | DeviceAddress & 0xFFFE );

    if( I2C_WaitAck() )
	{
		I2C_Stop(); 
		return -1;
	}
	
	/* Set low starting address */
    I2C_SendByte( (uint8_t) ( ReadAddress & 0x00FF ) );
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte( ( ( ReadAddress & 0x0700) >> 7 ) | DeviceAddress | 0x0001 );
    I2C_WaitAck();

    while(length)
    {
		*pBuffer = I2C_ReceiveByte();
		
		if(length == 1)
		{
			I2C_NoAck();
		}
		else 
		{
			I2C_Ack();
		}
		pBuffer++;
		length--;
    }
    I2C_Stop();

    return 0;
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
