/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The FreeRTOS application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-8
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
#include "FreeRTOS.h"
#include "task.h"


/* Private define ------------------------------------------------------------*/
#define LED_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE )

#define LED_TASK_PRIORITY			( tskIDLE_PRIORITY + 1 )

/* Private function prototypes -----------------------------------------------*/
static void prvSetupHardware( void );
void GPIO_Configuration(void);
void vLEDTask(void * pvArg);

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
	xTaskCreate( vLEDTask , ( signed char * ) NULL , LED_TASK_STACK_SIZE , NULL , LED_TASK_PRIORITY , NULL );
	/* Start the scheduler. */
	vTaskStartScheduler();	
	
	return 0;}

/*******************************************************************************
* Function Name  : vLEDTask
* Description    : LED Task
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void vLEDTask(void * pvArg)
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

	while(1)
	{
		/*====LED-ON=======*/
		GPIO_ClearValue( 2, (1<<21) ); 
		GPIO_ClearValue( 1, (1<<13) );  
		GPIO_ClearValue( 5, (1<<0) );  
		GPIO_ClearValue( 5, (1<<1) );  
		vTaskDelay(500);	
		
		/*====LED-OFF=======*/
		GPIO_SetValue( 2, (1<<21) ); 
		GPIO_SetValue( 1, (1<<13) );  
		GPIO_SetValue( 5, (1<<0) );  
		GPIO_SetValue( 5, (1<<1) );  
		vTaskDelay(500);	 
	}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
