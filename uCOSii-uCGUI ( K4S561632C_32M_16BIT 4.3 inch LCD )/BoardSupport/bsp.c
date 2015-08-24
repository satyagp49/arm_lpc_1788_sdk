/*
*******************************************************************************
  Copyright (C), 2012-2014, Embest Tech. Co., Ltd.
  FileName		    : bsp.c
  Author          : lichy       
  Version 		    : 1.0.0     
  Date			      : 2012/02/28
  Description	    : 
  Function List   : 
  History		      :
  <author>  	    : lichy       
  <time>     	    : 2012/02/28
  <version >      : 1.0.0 	
  <desc>		      : build this moudle			 
*******************************************************************************
*/
#include "includes.h"
#include "bsp.h"

/*
******************************************************************************
  Function:       BSP_LED_Init
  Description:    
  Calls:          void
  Called By:     
  Input:          void      
  Output:         void
  Return:         none
  Others:         
******************************************************************************
*/
void  BSP_LED_Init (void)
{
//	GPIO_SetDir(BRD_LED_1_CONNECTED_PORT, BRD_LED_1_CONNECTED_MASK, GPIO_DIRECTION_OUTPUT);
//	GPIO_SetDir(BRD_LED_2_CONNECTED_PORT, BRD_LED_2_CONNECTED_MASK, GPIO_DIRECTION_OUTPUT);

//  BSP_LED_Off(BRD_LED_1_CONNECTED_PORT, BRD_LED_1_CONNECTED_MASK);
//	BSP_LED_Off(BRD_LED_2_CONNECTED_PORT, BRD_LED_2_CONNECTED_MASK);
}

/*
******************************************************************************
  Function:       BSP_LED_On
  Description:    
  Calls:          void
  Called By:     
  Input:          void      
  Output:         void
  Return:         none
  Others:         
******************************************************************************
*/
void  BSP_LED_On (uint8_t port, uint32_t mask)
{
//  GPIO_OutputValue(port, mask, 1);
}

/*
******************************************************************************
  Function:       BSP_LED_Off
  Description:    
  Calls:          void
  Called By:     
  Input:          void      
  Output:         void
  Return:         none
  Others:         
******************************************************************************
*/
void  BSP_LED_Off (uint8_t port, uint32_t mask)
{
//	 GPIO_OutputValue(port, mask, 0);
}

/*
******************************************************************************
  Function:       BSP_LED_Toggle
  Description:    
  Calls:          void
  Called By:     
  Input:          void      
  Output:         void
  Return:         none
  Others:         
******************************************************************************
*/
void  BSP_LED_Toggle (uint8_t port, uint32_t mask)
{
//  uint32_t value;

//  value = GPIO_ReadValue(port);
//	value &= mask;

//	if (value != 0) {
//    BSP_LED_Off(port, mask);
//  } else { 
//    BSP_LED_On(port, mask);
//  }	
}
