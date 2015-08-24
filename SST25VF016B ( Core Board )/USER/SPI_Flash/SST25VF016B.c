/****************************************Copyright (c)**************************************************                         
**
**                                 http://www.powermcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			SST25VF016B.c
** Descriptions:		SST25VF016B functionality
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

/*******************************************************************************
* Function Name  : LPC17xx_SPI_SendRecvByte
* Description    : Send one byte then recv one byte of response
* Input          : - byte_s: byte_s
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
uint8_t LPC17xx_SPI_SendRecvByte (uint8_t byte_s)
{
	/* wait for current SSP activity complete */
	while (SSP_GetStatus(LPC_SSP0, SSP_STAT_BUSY) ==  SET);

	SSP_SendData(LPC_SSP0, (uint16_t) byte_s);

	while (SSP_GetStatus(LPC_SSP0, SSP_STAT_RXFIFO_NOTEMPTY) == RESET);
	return (SSP_ReceiveData(LPC_SSP0));
}

/*******************************************************************************
* Function Name  : SPI_FLASH_Init
* Description    : SPI FLASH Configuration
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void SPI_FLASH_Init(void)
{
    SSP_CFG_Type SSP_ConfigStruct;
	/*
	 * Initialize SPI pin connect
	 * P2.19 - SSEL - used as GPIO
	 * P2.22 - SCK
	 * P2.26 - MISO
	 * P2.27 - MOSI
	 */

	PINSEL_ConfigPin(2, 19, 0);	 /* P2.19 - GPIO */
	PINSEL_ConfigPin(2, 22, 2);	 /* SSP0_SCK */
	PINSEL_ConfigPin(2, 26, 2);	 /* SSP0_MISO */
	PINSEL_ConfigPin(2, 27, 2);	 /* SSP0_MOSI */

    /* P2.19 CS is output */
    GPIO_SetDir(CS_PORT_NUM, (1<<CS_PIN_NUM), 1);

	/* initialize SSP configuration structure to default */
	SSP_ConfigStructInit(&SSP_ConfigStruct);
	/* Initialize SSP peripheral with parameter given in structure above */
	SSP_Init(LPC_SSP0, &SSP_ConfigStruct);
	/* Enable SSP peripheral */
	SSP_Cmd(LPC_SSP0, ENABLE);
}

/*****************************************************************************
* Function Name  : Flash_ReadWriteByte
* Description    : send a byte to SST25VF016B
* Input          : - data: send data
* Output         : None
* Return         : return data
* Attention		 : None
*******************************************************************************/
uint8_t Flash_ReadWriteByte(uint8_t data)		
{
   return LPC17xx_SPI_SendRecvByte( data );                                
}


/*******************************************************************************
* Function Name  : SSTF016B_ReadData
* Description    : SST25VF016B read function, can be choose	read ID or read data 
* Input          : - Dst: Destination address 0x0 - MAX_ADDR
*                  - RcvBufPt: Receive buffer pointer
*                  - NByte: number of bytes to be read	
* Output         : successful return OK, failed return ERROR
* Return         : return result
*******************************************************************************/
int SSTF016B_ReadData(uint32_t Dst, uint8_t* RcvBufPt ,uint32_t NByte)
{
	uint32_t i = 0;

	if ( ( Dst+NByte > MAX_ADDR ) || ( NByte == 0 ) )	
	{
		return -1;	 /*	ERROR */
	}
	
    SPI_FLASH_CS_LOW();
	Flash_ReadWriteByte(0x0B); 						/* Send read command */
	Flash_ReadWriteByte(((Dst & 0xFFFFFF) >> 16));	/* Send 3 byte address command */
	Flash_ReadWriteByte(((Dst & 0xFFFF) >> 8));
	Flash_ReadWriteByte(Dst & 0xFF);
	Flash_ReadWriteByte(0xFF);						/* Sending a dummy byte in order to read data	*/
	for ( i = 0; i < NByte; i++ )		
	{
       RcvBufPt[i] = Flash_ReadWriteByte(0xFF);		/* Read data */
	}
    SPI_FLASH_CS_HIGH();

	return 0;
}

/*******************************************************************************
* Function Name  : SSTF016B_ReadID
* Description    : SST25VF016B read ID function 
* Input          : - IDType: choose in JEDEC_ID, Device_ID, Manufacturer_ID
* Output         : - RcvbufPt: Receive buffer pointer
* Return         : successful return OK, failed return ERROR
*******************************************************************************/
int SSTF016B_ReadID(idtype IDType,uint32_t* RcvbufPt)
{
	uint32_t temp = 0;
              
	if (IDType == JEDEC_ID)
	{
		SPI_FLASH_CS_LOW();	
				
		Flash_ReadWriteByte(0x9F);		 		         /* Send read JEDEC ID command (9Fh) */
    	        
        temp = (temp | Flash_ReadWriteByte(0x00)) << 8;  /* Receive Data */
		temp = (temp | Flash_ReadWriteByte(0x00)) << 8;	
        temp = (temp | Flash_ReadWriteByte(0x00)); 	     /* temp value is 0xBF2541 */

        SPI_FLASH_CS_HIGH();

		*RcvbufPt = temp;
		return 0;
	}
	
	if ((IDType == Manufacturer_ID) || (IDType == Device_ID) )
	{
	    SPI_FLASH_CS_LOW();	
		
		Flash_ReadWriteByte(0x90);				/* Send read ID command (90h or ABh) */
    	Flash_ReadWriteByte(0x00);				/* Send address	*/
		Flash_ReadWriteByte(0x00);				/* Send address	*/
		Flash_ReadWriteByte(IDType);		    /* Send address - 00H or 01H */
		temp = Flash_ReadWriteByte(0x00);	    /* Receive Data */

        SPI_FLASH_CS_HIGH();

		*RcvbufPt = temp;
		return 0;
	}
	else
	{
		return -1;	
	}
}

/*******************************************************************************
* Function Name  : SSTF016B_WriteReg
* Description    : SST25VF016B write functions, can write a more data to the specified address
* Input          : - Dst: Destination address 0x0 - MAX_ADDR
*                  - RcvBufPt: Write buffer pointer
*                  - NByte: number of bytes to be write	
* Output         : None
* Return         : successful return OK, failed return ERROR
*******************************************************************************/
int SSTF016B_WriteReg(uint32_t Dst, uint8_t* SndbufPt,uint32_t NByte)
{
	uint8_t temp = 0,StatRgVal = 0;
	uint32_t i = 0;

	if ( ( ( Dst + NByte - 1 > MAX_ADDR ) || ( NByte == 0 ) ) )
	{
		return -1;	 /*	ERROR */
	}

	SPI_FLASH_CS_LOW();				 
	Flash_ReadWriteByte(0x05);							    /* Send Read Status Register command */
	temp = Flash_ReadWriteByte(0xFF);					    /* Save the read status register value */
	SPI_FLASH_CS_HIGH();								

	SPI_FLASH_CS_LOW();				
	Flash_ReadWriteByte(0x50);
	SPI_FLASH_CS_HIGH();	
		
	SPI_FLASH_CS_LOW();				
	Flash_ReadWriteByte(0x01);							    /* Send write status register command */
	Flash_ReadWriteByte(0);								    /* chip can be written */
	SPI_FLASH_CS_HIGH();			
	
	for(i = 0; i < NByte; i++)
	{
		SPI_FLASH_CS_LOW();				
		Flash_ReadWriteByte(0x06);						    /* Send write enable command */
		SPI_FLASH_CS_HIGH();			

		SPI_FLASH_CS_LOW();					
		Flash_ReadWriteByte(0x02); 						    /* Send byte data programming command */
		Flash_ReadWriteByte((((Dst+i) & 0xFFFFFF) >> 16));  /* Send 3 byte address command */
		Flash_ReadWriteByte((((Dst+i) & 0xFFFF) >> 8));
		Flash_ReadWriteByte((Dst+i) & 0xFF);
		Flash_ReadWriteByte(SndbufPt[i]);					/* Write data */
		SPI_FLASH_CS_HIGH();			

		do
		{
		  	SPI_FLASH_CS_LOW();					 
			Flash_ReadWriteByte(0x05);					    /* Send Read Status Register command */
			StatRgVal = Flash_ReadWriteByte(0xFF);			/* Save the read status register value */
			SPI_FLASH_CS_HIGH();							
  		}
		while (StatRgVal == 0x03 );					        /* waiting until chip is idle */

	}

	SPI_FLASH_CS_LOW();					
	Flash_ReadWriteByte(0x06);							    /* Send write enable command */
	SPI_FLASH_CS_HIGH();			

	SPI_FLASH_CS_LOW();					
	Flash_ReadWriteByte(0x50);							    
	SPI_FLASH_CS_HIGH();
			
	SPI_FLASH_CS_LOW();				
	Flash_ReadWriteByte(0x01);							    /* Send write status register command */
	Flash_ReadWriteByte(temp);						     	/* Recovery status register */
	SPI_FLASH_CS_HIGH();

	return 0;		
}

/*******************************************************************************
* Function Name  : SSTF016B_Erase
* Description    : According to the sector number choose an efficient algorithms to erase
* Input          : - sec1: Start sector number ( 0 ~ 511 )
*                  - sec2: final sector number ( 0 ~ 511 )
* Output         : None
* Return         : successful return OK, failed return ERROR
*******************************************************************************/
int SSTF016B_Erase( uint32_t sec1, uint32_t sec2 )
{
	uint8_t  temp1 = 0,temp2 = 0,StatRgVal = 0;
    uint32_t SecnHdAddr = 0;	  			
	uint32_t no_SecsToEr = 0;				   			    /* number of sectors to be erased */
	uint32_t CurSecToEr = 0;	  						    /* sector to be erase */
															 
	if ( ( sec1 > SEC_MAX ) || ( sec2 > SEC_MAX ) )	
	{
		return -1;	 /*	ERROR */
	}
   	
   	SPI_FLASH_CS_LOW();			 
	Flash_ReadWriteByte(0x05);								/* Send Read Status Register command */
	temp1 = Flash_ReadWriteByte(0x00);						/* Save read status register value */
	SPI_FLASH_CS_HIGH();								

	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x50);								/* status register can be written */
	SPI_FLASH_CS_HIGH();			

	SPI_FLASH_CS_LOW();								  	
	Flash_ReadWriteByte(0x01);								/* send write status register command */
	Flash_ReadWriteByte(0);									/* chip can be written */
	SPI_FLASH_CS_HIGH();
	
	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x06);								/* Send write enable command */
	SPI_FLASH_CS_HIGH();			

	/* starting sector number is greater than the final sector number, internal adjustments */
	if ( sec1 > sec2 )
	{
	   temp2 = sec1;
	   sec1  = sec2;
	   sec2  = temp2;
	} 
	/* If starting and ending sector number equal, then erase a single sector */
	if ( sec1 == sec2 )	
	{
		SPI_FLASH_CS_LOW();				
		Flash_ReadWriteByte(0x06);						      /* Send write enable command */
		SPI_FLASH_CS_HIGH();			

	    SecnHdAddr = SEC_SIZE * sec1;				          /* Calculating the starting address of the sectors */
	    SPI_FLASH_CS_LOW();	
    	Flash_ReadWriteByte(0x20);							  /* Send sector erase command */
	    Flash_ReadWriteByte(((SecnHdAddr & 0xFFFFFF) >> 16)); /* Send 3 byte address command */
   		Flash_ReadWriteByte(((SecnHdAddr & 0xFFFF) >> 8));
   		Flash_ReadWriteByte(SecnHdAddr & 0xFF);
  		SPI_FLASH_CS_HIGH();			
		do
		{
		  	SPI_FLASH_CS_LOW();			 
			Flash_ReadWriteByte(0x05);						  /* Send Read Status Register command */
			StatRgVal = Flash_ReadWriteByte(0x00);			  /* Save read status register value */
			SPI_FLASH_CS_HIGH();								
  		}
		while (StatRgVal == 0x03);				              /* Waits until the chip is idle	*/
		return 0;			
	}
	
    /* According to starting sector number and final sector number, Select a fastest erase algorithm */	
	if ( sec2 - sec1 == SEC_MAX )	
	{
		SPI_FLASH_CS_LOW();			
		Flash_ReadWriteByte(0x60);							  /* Send Chip Erase command (60h or C7h) */
		SPI_FLASH_CS_HIGH();			
		do
		{
		  	SPI_FLASH_CS_LOW();			 
			Flash_ReadWriteByte(0x05);						  /* Send Read Status Register command */
			StatRgVal = Flash_ReadWriteByte(0x00);			  /* Save read status register value */
			SPI_FLASH_CS_HIGH();								
  		}
		while (StatRgVal == 0x03);					          /* Waits until the chip is idle */
   		return (ENABLE);
	}
	
	no_SecsToEr = sec2 - sec1 +1;					          /* Get the number of sectors to be erased */
	CurSecToEr  = sec1;								          /* starting sector to erase */
	
	/* take 8 sector erase algorithm */
	while (no_SecsToEr >= 8)
	{
		SPI_FLASH_CS_LOW();				
		Flash_ReadWriteByte(0x06);						      /* Send write enable command */
		SPI_FLASH_CS_HIGH();			

	    SecnHdAddr = SEC_SIZE * CurSecToEr;			          /* Calculating the starting address of the sectors */
	    SPI_FLASH_CS_LOW();	
	    Flash_ReadWriteByte(0x52);							  /* Send 32KB erase command */
	    Flash_ReadWriteByte(((SecnHdAddr & 0xFFFFFF) >> 16)); /* Send 3 byte address command */
   		Flash_ReadWriteByte(((SecnHdAddr & 0xFFFF) >> 8));
   		Flash_ReadWriteByte(SecnHdAddr & 0xFF);
  		SPI_FLASH_CS_HIGH();			
		do
		{
		  	SPI_FLASH_CS_LOW();			 
			Flash_ReadWriteByte(0x05);						  /* Send Read Status Register command */
			StatRgVal = Flash_ReadWriteByte(0x00);			  /* Save read status register value	*/
			SPI_FLASH_CS_HIGH();								
  		}
		while (StatRgVal == 0x03);					          /* Waits until the chip is idle */
		CurSecToEr  += 8;
		no_SecsToEr -=  8;
	}
	/* using sector erase algorithm erase remaining sectors */
	while (no_SecsToEr >= 1)
	{
		SPI_FLASH_CS_LOW();				
		Flash_ReadWriteByte(0x06);						      /* Send write enable command */
		SPI_FLASH_CS_HIGH();			

	    SecnHdAddr = SEC_SIZE * CurSecToEr;			          /* Calculating the starting address of the sectors */
	    SPI_FLASH_CS_LOW();	
    	Flash_ReadWriteByte(0x20);							  /* Send sector erase command */
	    Flash_ReadWriteByte(((SecnHdAddr & 0xFFFFFF) >> 16)); /* Send 3 byte address command */
   		Flash_ReadWriteByte(((SecnHdAddr & 0xFFFF) >> 8));
   		Flash_ReadWriteByte(SecnHdAddr & 0xFF);
  		SPI_FLASH_CS_HIGH();			
		do
		{
		  	SPI_FLASH_CS_LOW();			 
			Flash_ReadWriteByte(0x05);						  /* Send Read Status Register command */
			StatRgVal = Flash_ReadWriteByte(0x00);			  /* Save read status register value */
			SPI_FLASH_CS_HIGH();								
  		}
		while (StatRgVal == 0x03);					          /* Waits until the chip is idle */
		CurSecToEr  += 1;
		no_SecsToEr -=  1;
	}
    /* erase end, restore the status register */
	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x06);								  /* Send write enable command */
	SPI_FLASH_CS_HIGH();			

	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x50);								  /* status register can be written */
	SPI_FLASH_CS_HIGH();			
	SPI_FLASH_CS_LOW();			
	Flash_ReadWriteByte(0x01);								  /* send write status register command */
	Flash_ReadWriteByte(temp1);								  /* Recovery status register */
	SPI_FLASH_CS_HIGH();    
	return 0;
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

