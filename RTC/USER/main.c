/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            This example describes how to calibrate real time clock
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
#include "debug_frmwrk.h"
#include "lpc177x_8x_rtc.h"
#include "lpc177x_8x_clkpwr.h"


/** @defgroup RTC_Calibration	RTC Calibration
 * @ingroup RTC_Examples
 * @{
 */

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief		RTC interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void RTC_IRQHandler(void)
{
	uint32_t secval;

	/* This is increment counter interrupt*/
	if (RTC_GetIntPending(LPC_RTC, RTC_INT_COUNTER_INCREASE))
	{
		secval = RTC_GetTime (LPC_RTC, RTC_TIMETYPE_SECOND);

		/* Send debug information */
		_DBG ("Second: "); _DBD(secval);
		_DBG_("");

		/* Clear pending interrupt */
		RTC_ClearIntPending(LPC_RTC, RTC_INT_COUNTER_INCREASE);
	}
}

/*-------------------------MAIN FUNCTION------------------------------*/
/*********************************************************************//**
 * @brief		c_entry: Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int c_entry (void)
{
	/* Initialize debug via UART0
	 * – 115200bps
	 * – 8 data bit
	 * – No parity
	 * – 1 stop bit
	 * – No flow control
	 */
	debug_frmwrk_init();

	_DBG_("*****************************************************************\n");
	_DBG_("*                                                               *\n");
	_DBG_("*   Thank you for using HY-LPC1788-SDK Development Board £¡^_^  *\n");
	_DBG_("*                                                               *\n");
	_DBG_("*****************************************************************\n");

    _DBG_("********************************************************************************\n");
    _DBG_(" Hello NXP Semiconductors \n");
    _DBG_(" RTC Calibration demo \n");
    _DBG_("\t - MCU: LPC177x_8x \n");
    _DBG_("\t - Core: ARM CORTEX-M3 \n");
    _DBG_("\t - UART Communication: 115200 bps \n");
    _DBG_(" This example describes how to calibrate RTC \n");
    _DBG_("********************************************************************************\n");

	/* In this example:
	 * Suppose that the RTC need periodically adjust after each 5 second.
	 * And the time counter need by incrementing the counter by 2 instead of 1
	 * We will observe timer counter after calibration via serial display
	 */
	/* Init RTC module */
	RTC_Init(LPC_RTC);

	/* Enable rtc (starts increase the tick counter and second counter register) */
	RTC_ResetClockTickCounter(LPC_RTC);
	RTC_Cmd(LPC_RTC, ENABLE);

	/* Set current time = 0 */
	RTC_SetTime (LPC_RTC, RTC_TIMETYPE_SECOND, 0);

	/* Setting Timer calibration
	 * Calibration value =  5s;
	 * Direction = Forward calibration
	 * So after each 5s, calibration logic can periodically adjust the time counter by
	 * incrementing the counter by 2 instead of 1
	 */
	RTC_CalibConfig(LPC_RTC, 5, RTC_CALIB_DIR_FORWARD);
	RTC_CalibCounterCmd(LPC_RTC, ENABLE);

	/* Set the CIIR for second counter interrupt*/
	RTC_CntIncrIntConfig (LPC_RTC, RTC_TIMETYPE_SECOND, ENABLE);

    /* Enable RTC interrupt */
    NVIC_EnableIRQ(RTC_IRQn);

    /* Loop forever */
    while(1)
	{
	}
}


/* With ARM and GHS toolsets, the entry point is main() - this will
   allow the linker to generate wrapper code to setup stacks, allocate
   heap area, and initialize and copy code and data segments. For GNU
   toolsets, the entry point is through __start() in the crt0_gnu.asm
   file, and that startup code will setup stacks and data */
int main(void)
{
    return c_entry();
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
