/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            This example describes how to use RS485 functionality on UART of LPC1788
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
#include "lpc_types.h"
#include "lpc177x_8x.h"
#include "debug_frmwrk.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_pinsel.h"

/* Private function prototypes -----------------------------------------------*/
void USART_Configuration(void);

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
    /* 485_TX_EN   P4.26 */
    /* 485_RX_EN   P4.27 */
	PINSEL_ConfigPin(4,26,0);	   /* P4.26 - GPIO */
    GPIO_SetDir(4, (1<<26), 1);	   /* Output Mode */

	PINSEL_ConfigPin(4,27,0);	   /* P4.27 - GPIO */
    GPIO_SetDir(4, (1<<27), 1);	   /* Output Mode */

	USART_Configuration();

	/* RS485 Output Mode */
	GPIO_SetValue( 4, (1<<26) );   /* 485_TX_EN Enable */
	GPIO_SetValue( 4, (1<<27) );   /* 485_RX_EN Disable */ 
 
	UARTPuts_( UART_3, "*****************************************************************" );
	UARTPuts_( UART_3, "*                                                               *" );
	UARTPuts_( UART_3, "*   Thank you for using HY-LPC1788-SDK Development Board £¡^_^  *" );
	UARTPuts_( UART_3, "*                                                               *" );
	UARTPuts_( UART_3, "*****************************************************************" );

	/* Infinite loop */
	while(1)
	{
		/* RS485 Input Mode */
		GPIO_ClearValue( 4, (1<<26) );  /* 485_TX_EN Disable */ 
		GPIO_ClearValue( 4, (1<<27) );  /* 485_RX_EN Enable */
	
	    /* Serial port receive data */
		/* import HY-LPC1788-SDK */
		while( UARTGetChar(UART_3) !='H');
		while( UARTGetChar(UART_3) !='Y');
		while( UARTGetChar(UART_3) !='-');
		while( UARTGetChar(UART_3) !='L');
		while( UARTGetChar(UART_3) !='P');
		while( UARTGetChar(UART_3) !='C');
		while( UARTGetChar(UART_3) !='1');
		while( UARTGetChar(UART_3) !='7');
		while( UARTGetChar(UART_3) !='8');
		while( UARTGetChar(UART_3) !='8');
		while( UARTGetChar(UART_3) !='-');
		while( UARTGetChar(UART_3) !='S');
		while( UARTGetChar(UART_3) !='D');
		while( UARTGetChar(UART_3) !='K');
	
		/* RS485 Output Mode */
		GPIO_SetValue( 4, (1<<26) ); 	/* 485_TX_EN Enable */
		GPIO_SetValue( 4, (1<<27) );    /* 485_RX_EN Disable */ 
		Delay(0xfffff);

	    UARTPuts_( UART_3, "RS485 receive data OK");
	}
}

/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : Configure USART1 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_Configuration(void)
{ 
	UART_CFG_Type UARTConfigStruct;
	/*
	 * Initialize UART3 pin connect
	 * P4.28: TXD
	 * P4.29: RXD
	 */
	PINSEL_ConfigPin(4, 28, 2);
	PINSEL_ConfigPin(4, 29, 2);

	/* Initialize UART Configuration parameter structure to default state:
	 * Baudrate = 115200bps
	 * 8 data bit
	 * 1 Stop bit
	 * None parity
	 */
	UART_ConfigStructInit(&UARTConfigStruct);
	/* Re-configure baudrate to 115200bps */
	UARTConfigStruct.Baud_rate = 115200;

	/* Initialize DEBUG_UART_PORT peripheral with given to corresponding parameter */
	UART_Init(UART_3, &UARTConfigStruct);

	/* Enable UART Transmit */
	UART_TxCmd(UART_3, ENABLE);
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
