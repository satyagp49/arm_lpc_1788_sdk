/**********************************************************************
* $Id$		bsp.h			2011-06-02
*//**
* @file		bsp.h
* @brief	Contains basic information about the board that can
* 			be using with the current code package. It may
* 			include some header file for the components mounted
* 			on the board. Or else some neccessary hardware (IOs)
* 			settings for the using board may be involved.
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


/* Peripheral group ----------------------------------------------------------- */
/** @defgroup BoardSupport Board Support
 * @ingroup LPC177x_8xCMSIS_Board_Support
 * @{
 */

#ifndef __BSP_H
#define __BSP_H


//ADC input preset on this board
#define BRD_ADC_PREPARED_CHANNEL		(ADC_CHANNEL_2)
#define BRD_ADC_PREPARED_INTR			  (ADC_ADINTEN2)

#define BRD_ADC_PREPARED_CH_PORT		  (0)
#define BRD_ADC_PREPARED_CH_PIN			  (25)
#define BRD_ADC_PREPARED_CH_FUNC_NO		(1)


//LED indicators preset
#define BRD_LED_1_CONNECTED_PORT		(3)
#define BRD_LED_1_CONNECTED_PIN			(23)
#define BRD_LED_1_CONNECTED_MASK		(1 << BRD_LED_1_CONNECTED_PIN)

#define BRD_LED_2_CONNECTED_PORT		(3)
#define BRD_LED_2_CONNECTED_PIN			(24)
#define BRD_LED_2_CONNECTED_MASK		(1 << BRD_LED_2_CONNECTED_PIN)

#define BRD_LED_3_CONNECTED_PORT		(3)
#define BRD_LED_3_CONNECTED_PIN			(25)
#define BRD_LED_3_CONNECTED_MASK		(1 << BRD_LED_2_CONNECTED_PIN)

#define BRD_LED_4_CONNECTED_PORT		(3)
#define BRD_LED_4_CONNECTED_PIN			(26)
#define BRD_LED_4_CONNECTED_MASK		(1 << BRD_LED_2_CONNECTED_PIN)

#define BRD_LED_5_CONNECTED_PORT		(3)
#define BRD_LED_5_CONNECTED_PIN			(27)
#define BRD_LED_5_CONNECTED_MASK		(1 << BRD_LED_2_CONNECTED_PIN)

#define BRD_LED_6_CONNECTED_PORT		(3)
#define BRD_LED_6_CONNECTED_PIN			(28)
#define BRD_LED_6_CONNECTED_MASK		(1 << BRD_LED_2_CONNECTED_PIN)

#define BRD_LED_7_CONNECTED_PORT		(3)
#define BRD_LED_7_CONNECTED_PIN			(29)
#define BRD_LED_7_CONNECTED_MASK		(1 << BRD_LED_2_CONNECTED_PIN)

#define BRD_LED_8_CONNECTED_PORT		(3)
#define BRD_LED_8_CONNECTED_PIN			(31)
#define BRD_LED_8_CONNECTED_MASK		(1 << BRD_LED_2_CONNECTED_PIN)

//PIO interrupt preset
#define BRD_PIO_USED_INTR_PORT			(0)
#define BRD_PIO_USED_INTR_PIN			  (13)
#define BRD_PIO_USED_INTR_MASK			(1 << BRD_PIO_USED_INTR_PIN)


//MCI power active levell
#define BRD_MCI_POWERED_ACTIVE_LEVEL	(1)


//Timer preset
#define BRD_TIMER_USED				      (LPC_TIM2)
#define BRD_TIM_INTR_USED			(TIMER2_IRQn)

#define BRD_TIM_CAP_LINKED_PORT		(0)
#define BRD_TIM_CAP_LINKED_PIN		(4)

void  BSP_LED_Init (void);
void  BSP_LED_Toggle (uint8_t port, uint32_t mask);
void  BSP_LED_On (uint8_t port, uint32_t mask);
void  BSP_LED_Off (uint8_t port, uint32_t mask);

#endif//BSP_H

/**
 * @}
 */
