/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            This example describes how to use UART1 interface on LPC177x_8x
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
#include "lpc_types.h"
#include "lpc177x_8x.h"
#include "debug_frmwrk.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_pinsel.h"

/* Private function prototypes -----------------------------------------------*/
void USART_Configuration(void);

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
	USART_Configuration();

	UARTPuts_( UART_1, "*****************************************************************" );
	UARTPuts_( UART_1, "*                                                               *" );
	UARTPuts_( UART_1, "*   Thank you for using HY-LPC1788-SDK Development Board £¡^_^  *" );
	UARTPuts_( UART_1, "*                                                               *" );
	UARTPuts_( UART_1, "*****************************************************************" );

	/* Infinite loop */
	while(1)
	{
	    /* Serial port receive data */
		/* import HY-LPC1788-SDK */
		while( UARTGetChar(UART_1) !='H');
		while( UARTGetChar(UART_1) !='Y');
		while( UARTGetChar(UART_1) !='-');
		while( UARTGetChar(UART_1) !='L');
		while( UARTGetChar(UART_1) !='P');
		while( UARTGetChar(UART_1) !='C');
		while( UARTGetChar(UART_1) !='1');
		while( UARTGetChar(UART_1) !='7');
		while( UARTGetChar(UART_1) !='8');
		while( UARTGetChar(UART_1) !='8');
		while( UARTGetChar(UART_1) !='-');
		while( UARTGetChar(UART_1) !='S');
		while( UARTGetChar(UART_1) !='D');
		while( UARTGetChar(UART_1) !='K');
	
		/* successful received data */
	    UARTPuts_( UART_1, "receive data OK");
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
	 * Initialize UART1 pin connect
	 * P0.15: TXD
	 * P0.16: RXD
	 */
	PINSEL_ConfigPin(0, 15, 1);
	PINSEL_ConfigPin(0, 16, 1);

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
	UART_Init(UART_1, &UARTConfigStruct);

	/* Enable UART Transmit */
	UART_TxCmd(UART_1, ENABLE);

}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
