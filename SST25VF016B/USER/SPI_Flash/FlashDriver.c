/****************************************Copyright (c)**************************************************                         
**
**                                 http://www.powermcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			FlashDriver.c
** Descriptions:		None
**
**------------------------------------------------------------------------------------------------------
** Created by:			AVRman
** Created date:		2012-8-18
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
#include "SST25VF016B.h"
#include "FlashDriver.h"

/* Private variables ---------------------------------------------------------*/
static uint32_t CurReadAddr;	/* current read address */
static uint32_t CurWriteAddr;	/* current write address */

/*******************************************************************************
* Function Name  : df_read_open
* Description    : Read initialize functions
* Input          : - addr: read address
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_read_open(uint32_t addr)
{
	CurReadAddr = addr;	/* current read address */
}


/*******************************************************************************
* Function Name  : df_write_open
* Description    : Write initialize functions
* Input          : - addr: write address
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_write_open(uint32_t addr)
{
	CurWriteAddr=addr;	/* current write address */
}

/*******************************************************************************
* Function Name  : df_read
* Description    : Read functions
* Input          : - buf: received data of pointer
*                  - size: read data of size
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_read(uint8_t *buf,uint16_t size)
{
	if( CurReadAddr + size <= MAX_ADDR )
	{
		SSTF016B_ReadData( CurReadAddr, buf, size );
		CurReadAddr += size;
	}
}

/*******************************************************************************
* Function Name  : df_write
* Description    : Write functions
* Input          : - buf: write data of pointer
*                  - size: write data of size
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_write(uint8_t *buf,uint16_t size)
{
	if( CurWriteAddr + size <= MAX_ADDR )
	{
		SSTF016B_WriteReg( CurWriteAddr, buf, size );
		CurWriteAddr += size;
	}
}

/*******************************************************************************
* Function Name  : df_read_seek
* Description    : adjustment read address 	
* Input          : - addr: new read address
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_read_seek(uint32_t addr)
{
	df_read_close();
	df_read_open(addr);
}

/*******************************************************************************
* Function Name  : df_write_seek
* Description    : adjustment write address
* Input          : - addr: new write address 
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_write_seek(uint32_t addr)
{
	df_write_close();
	df_write_open(addr); 
}

/*******************************************************************************
* Function Name  : df_read_close
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_read_close(void)
{
}

/*******************************************************************************
* Function Name  : df_write_close
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void df_write_close(void)
{
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
