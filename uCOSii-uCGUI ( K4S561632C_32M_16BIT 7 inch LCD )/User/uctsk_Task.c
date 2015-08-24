/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               uctsk_Task.c
** Descriptions:            The uctsk_Task application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-24
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
#include "includes.h"
#include "GLCD.h"

/* Private variables ---------------------------------------------------------*/
static  OS_STK         App_TaskBlinkStk          [APP_TASK_BLINK_STK_SIZE];
static  OS_STK         App_Task_UCGUI_Stk        [APP_TASK_UCGUI_STK_SIZE];
static  OS_STK         App_Task_TouchPanel_Stk   [APP_TASK_TouchPanel_STK_SIZE];

/* Private function prototypes -----------------------------------------------*/
       void MainTask         (void);	   
static void uctsk_Blink      (void);
static void uctsk_UCGUI      (void);
static void uctsk_TouchPanel (void);
extern void _ExecCalibration (int x_size, int y_size);

 
void  App_UCGUI_TaskCreate (void)
{
    INT8U  os_err;

	os_err = os_err; 

	os_err = OSTaskCreate((void (*)(void *)) uctsk_UCGUI,				
                          (void          * ) 0,							
                          (OS_STK        * )&App_Task_UCGUI_Stk[APP_TASK_UCGUI_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_UCGUI_PRIO  );							

	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_UCGUI_PRIO, "Task UCGUI", &os_err);
	#endif
   
    os_err = OSTaskCreate((void (*)(void *)) uctsk_TouchPanel,				
                          (void          * ) 0,							
                          (OS_STK        * )&App_Task_TouchPanel_Stk[APP_TASK_TouchPanel_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_TouchPanel_PRIO  );

	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_TouchPanel_PRIO, "TASK TouchPanel Messages", &os_err);
	#endif

	os_err = OSTaskCreate((void (*)(void *)) uctsk_Blink,				
                          (void          * ) 0,							
                          (OS_STK        * )&App_TaskBlinkStk[APP_TASK_BLINK_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_BLINK_PRIO  );							

	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_BLINK_PRIO, "Task LED Blink", &os_err);
	#endif
}							 


static void uctsk_UCGUI (void) 
{   
   GUI_Init();
   _ExecCalibration( GLCD_X_SIZE, GLCD_Y_SIZE );	  /* ´¥ÃþÆÁÐ£×¼   */
   	for(;;)
   	{  
	  GUIDEMO_main(); 
    }
}


static void uctsk_TouchPanel (void) 
{  
    TP_Init();

   	for(;;)
   	{  
	   GUI_TOUCH_Exec();
	   OSTimeDlyHMSM(0, 0, 0, 25);	 /* 20 MS  */
    }
}

static void uctsk_Blink (void) 
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
    for(;;)
   	{ 
		/*====LED-ON=======*/
		GPIO_ClearValue( 2, (1<<21) ); 
		GPIO_ClearValue( 1, (1<<13) );  
		GPIO_ClearValue( 5, (1<<0) );  
		GPIO_ClearValue( 5, (1<<1) );  
		OSTimeDlyHMSM(0, 0, 1, 0);	 /* 20 MS  */
		/*====LED-OFF=======*/
		GPIO_SetValue( 2, (1<<21) ); 
		GPIO_SetValue( 1, (1<<13) );  
		GPIO_SetValue( 5, (1<<0) );  
		GPIO_SetValue( 5, (1<<1) );
		OSTimeDlyHMSM(0, 0, 1, 0);	 /* 20 MS  */   
    }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
