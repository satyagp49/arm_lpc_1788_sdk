/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            This example describes how to use EMC interface on LPC177x_8x
**							to connect with external SDRAM
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
#include "debug_frmwrk.h"
#include "lpc177x_8x_pinsel.h"
#include "SDRAM_K4M563233G_32M_32BIT.h"


/* Private functions ---------------------------------------------------------*/
void sdram_test(void);


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
 	sdram_test();
	/* Infinite loop */
	while( 1 )
	{
	}
}

/*********************************************************************//**
 * @brief		sdram_test: Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
void sdram_test (void)
{
	uint32_t i;
  	volatile uint32_t *wr_ptr;
  	volatile uint8_t *char_wr_ptr;
  	volatile uint16_t *short_wr_ptr;

	/* Initialize debug via UART0
	 * ?115200bps
	 * ?8 data bit
	 * ?No parity
	 * ?1 stop bit
	 * ?No flow control
	 */
	debug_frmwrk_init();

	_DBG_("*****************************************************************\n");
	_DBG_("*                                                               *\n");
	_DBG_("*   Thank you for using HY-LPC1788-SDK Development Board £¡^_^  *\n");
	_DBG_("*                                                               *\n");
	_DBG_("*****************************************************************\n");

	_DBG_("******************************************************************\n");
	_DBG_(" Hello NXP Semiconductors \n");
	_DBG_(" Test SDRAM K4S561632C with LPC1788 EMC \n");
	_DBG_("\t - MCU: LPC177x_8x \n");
	_DBG_("\t - Core: Cortex-M3 \n");
	_DBG_("\t - UART Comunication: 115200 kbps \n");
	_DBG_(" Write and verify data with on-board SDRAM\n");
	_DBG_("*******************************************************************\n");

  	/* initialize memory */
	_DBG_("Init SDRAM...");
    SDRAM_32M_32BIT_Init();

    wr_ptr = (uint32_t *)SDRAM_BASE_ADDR;
    char_wr_ptr = (uint8_t *)wr_ptr;
    /* Clear content before 8 bit access test */
    _DBG_("Clear content of SDRAM...");
    for ( i= 0; i < SDRAM_SIZE/4; i++ )
    {
	  *wr_ptr++ = 0x00;
    }

    /* 8 bit write */
    _DBG_("Writing in 8 bits format...");
    for (i=0; i<SDRAM_SIZE/4; i++)
    {
	  *char_wr_ptr++ = 0x11;
	  *char_wr_ptr++ = 0x22;
	  *char_wr_ptr++ = 0x33;
	  *char_wr_ptr++ = 0x44;
    }

  	/* verifying */
  	_DBG_("Verifying data...");
 	wr_ptr = (uint32_t *)SDRAM_BASE_ADDR;
  	for ( i= 0; i < SDRAM_SIZE/4; i++ )
  	{
		if ( *wr_ptr != 0x44332211 )	/* be aware of endianess */
		{
	  		/* byte comparison failure */
			_DBG_("Verifying fail, testing terminated!");
	  		while ( 1 );	/* fatal error */
		}
		wr_ptr++;
  	}

  	/* byte comparison succeed. */
  	_DBG_("Continue writing in 16 bits format...");
  	wr_ptr = (uint32_t *)SDRAM_BASE_ADDR;
  	short_wr_ptr = (uint16_t *)wr_ptr;

  	/* Clear content before 16 bit access test */
  	_DBG_("Clear content of SRAM...");
  	for ( i= 0; i < SDRAM_SIZE/4; i++ )
  	{
		*wr_ptr++ = 0;
  	}

  	/* 16 bit write */
  	_DBG_("Writing in 16 bits format...");
  	for (i=0; i<(SDRAM_SIZE/4); i++)
  	{
		*short_wr_ptr++ = 0x5AA5;
		*short_wr_ptr++ = 0xAA55;
  	}

  	/* Verifying */
  	wr_ptr = (uint32_t *)SDRAM_BASE_ADDR;

  	for ( i= 0; i < SDRAM_SIZE/4; i++ )
  	{
		if ( *wr_ptr != 0xAA555AA5 )	/* be aware of endianess */
		{
	  		/* 16-bit half word failure */
			_DBG_("Verifying fail, testing termintated!");
	  	    while ( 1 );	/* fatal error */
		}
		wr_ptr++;
  	}

    /* 8 bit continuous write */
    wr_ptr = (uint32_t *)SDRAM_BASE_ADDR;
    char_wr_ptr = (uint8_t *)wr_ptr;
    _DBG_("Writing in 8 bits continuous format...");
    for ( i= 0; i < SDRAM_SIZE/4; i++ )
    {
		*char_wr_ptr++ = (uint8_t)((i >> 0) & 0xff);
		*char_wr_ptr++ = (uint8_t)((i >> 8) & 0xff);
		*char_wr_ptr++ = (uint8_t)((i >>16) & 0xff);
		*char_wr_ptr++ = (uint8_t)((i >>24) & 0xff);
    }


  	/* verifying */
  	_DBG_("Verifying data...");
    wr_ptr = (uint32_t *)SDRAM_BASE_ADDR;
    char_wr_ptr = (uint8_t *)wr_ptr;
  	for ( i= 0; i < SDRAM_SIZE/4; i++ )
  	{
	    uint32_t data;

		data = ((uint32_t) *char_wr_ptr++) << 0;
		data |= ((uint32_t) *char_wr_ptr++) << 8;
		data |= ((uint32_t) *char_wr_ptr++) << 16;
		data |= ((uint32_t) *char_wr_ptr++) << 24;
		if ( data != i )	/* be aware of endianess */
		{
	  		/* byte comparison failure */
			_DBG_("Verifying fail, testing terminated!");
	  		while ( 1 );	/* fatal error */
		}
		wr_ptr++;
  	}

    /* 16 bit continuous write */
    wr_ptr = (uint32_t *)SDRAM_BASE_ADDR;
  	short_wr_ptr = (uint16_t *)wr_ptr;
    _DBG_("Writing in 16 bits continuous format...");
    for ( i= 0; i < SDRAM_SIZE/4; i++ )
    {
		*short_wr_ptr++ = (uint16_t)(i & 0xffff);
		*short_wr_ptr++ = (uint16_t)((i>>16) & 0xffff);
    }

  	/* verifying */
  	_DBG_("Verifying data...");
    wr_ptr = (uint32_t *)SDRAM_BASE_ADDR;
  	short_wr_ptr = (uint16_t *)wr_ptr;
  	for ( i= 0; i < SDRAM_SIZE/4; i++ )
  	{
	    uint32_t data;

		data = ((uint32_t) *short_wr_ptr++) << 0;
		data |= ((uint32_t) *short_wr_ptr++) << 16;
		if ( data != i )	/* be aware of endianess */
		{
	  		/* byte comparison failure */
			_DBG_("Verifying fail, testing terminated!");
	  		while ( 1 );	/* fatal error */
		}
		wr_ptr++;
  	}

    /* 32 bit continuous write */
    wr_ptr = (uint32_t *)SDRAM_BASE_ADDR;
    _DBG_("Writing in 32 bits continuous format...");
    for ( i= 0; i < SDRAM_SIZE/4; i++ )
    {
		*wr_ptr++ = i;
    }

  	/* verifying */
  	_DBG_("Verifying data...");
    wr_ptr = (uint32_t *)SDRAM_BASE_ADDR;
  	for ( i= 0; i < SDRAM_SIZE/4; i++ )
  	{
		if ( *wr_ptr != i )	/* be aware of endianess */
		{
	  		/* byte comparison failure */
			_DBG_("Verifying fail, testing terminated!");
	  		while ( 1 );	/* fatal error */
		}
		wr_ptr++;
  	}
	_DBG_("SDRAM test OK");
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
