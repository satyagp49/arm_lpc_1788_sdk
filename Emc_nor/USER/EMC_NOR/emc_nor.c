/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               emc_nor.c
** Descriptions:            The emc NOR application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2011-2-16
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
#include "emc_nor.h"
#include "lpc177x_8x_timer.h"

/* Private define ------------------------------------------------------------*/
#define NOR_FLASH_START_ADDR       ((uint32_t)0x90000000)
#define NOR_FLASH_END_ADDR         ((uint32_t)0x90800000)

/* Delay definition */   
#define SectorErase_Timeout        ((uint32_t)0x00A00000)
#define ChipErase_Timeout          ((uint32_t)0x30000000) 
#define Program_Timeout            ((uint32_t)0x00001400)

#define ADDR_SHIFT(A)              (NOR_FLASH_START_ADDR + (2 * (A)))
#define NOR_WRITE(Address, Data)   (*(volatile short *)(Address) = (Data))

#define BUFFER_SIZE                0x400

#define WRITE_READ_ADDR            0x8000

#define SECTOR_SIZE                64 * 1024
#define SECTOR_NUM                 128

/* Private variables ---------------------------------------------------------*/
static uint16_t TxBuffer[SECTOR_SIZE/4];
static uint16_t RxBuffer[SECTOR_SIZE/4];

/*******************************************************************************
* Function Name  : EMC_NOR_Init
* Description    : Configures the FSMC and GPIOs to interface with the NOR memory.
*                  This function must be called before any write/read operation
*                  on the NOR.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void EMC_NOR_Init(void)
{
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	EMC_STATIC_MEM_Config_Type config;

	/**************************************************************************
	* Initialize EMC for NOR FLASH
	**************************************************************************/
	config.CSn = 1;
	config.AddressMirror = 0;
	config.ByteLane = 1;
	config.DataWidth = 16;
	config.ExtendedWait = 0;
	config.PageMode = 0;
	config.WaitWEn = 2;
	config.WaitOEn = 2;
	config.WaitWr = 0x1f;
	config.WaitPage = 0x1f;
	config.WaitRd = 0x1f;
	config.WaitTurn = 0x1f;	
	StaticMem_Init(&config);

    // init timer
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue	= 1;

		// Set configuration for Tim_config and Tim_MatchConfig
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);
	TIM_Waitms(100);

	//delay time
 	TIM_Waitms(10);

  	return;
}

/******************************************************************************
* Function Name  : EMC_NOR_ReadID
* Description    : Reads NOR memory's Manufacturer and Device Code.
* Input          : - NOR_ID: pointer to a NOR_IDTypeDef structure which will hold
*                    the Manufacturer and Device Code.
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void EMC_NOR_ReadID(NOR_IDTypeDef* NOR_ID)
{
  NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
  NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
  NOR_WRITE(ADDR_SHIFT(0x0555), 0x0090);

  NOR_ID->Manufacturer_Code = *(volatile short *) ADDR_SHIFT(0x0000);
  NOR_ID->Device_Code1 = *(volatile short *) ADDR_SHIFT(0x0001);
  NOR_ID->Device_Code2 = *(volatile short *) ADDR_SHIFT(0x000E);
  NOR_ID->Device_Code3 = *(volatile short *) ADDR_SHIFT(0x000F);
}

/*******************************************************************************
* Function Name  : EMC_NOR_EraseSector
* Description    : Erases the specified Nor memory Sector.
* Input          : - SectorAddr: address of the block to erase.
* Output         : None
* Return         : NOR_Status:The returned value can be: NOR_SUCCESS, NOR_ERROR
*                  or NOR_TIMEOUT
* Attention		 : None
*******************************************************************************/
NOR_Status EMC_NOR_EraseSector(uint32_t SectorAddr)
{
  NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
  NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
  NOR_WRITE(ADDR_SHIFT(0x0555), 0x0080);
  NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
  NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
  NOR_WRITE((NOR_FLASH_START_ADDR + SectorAddr), 0x30);

  return (EMC_NOR_GetStatus(SectorErase_Timeout));
}

/*******************************************************************************
* Function Name  : EMC_NOR_EraseChip
* Description    : Erases the entire chip.
* Input          : None                      
* Output         : None
* Return         : NOR_Status:The returned value can be: NOR_SUCCESS, NOR_ERROR
*                  or NOR_TIMEOUT
* Attention		 : None
*******************************************************************************/
NOR_Status EMC_NOR_EraseChip(void)
{
  NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
  NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
  NOR_WRITE(ADDR_SHIFT(0x0555), 0x0080);
  NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
  NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
  NOR_WRITE(ADDR_SHIFT(0x0555), 0x0010);

  return (EMC_NOR_GetStatus(ChipErase_Timeout));
}

/******************************************************************************
* Function Name  : EMC_NOR_WriteWord
* Description    : Writes a word to the NOR memory. 
* Input          : - WriteAddr : NOR memory internal address to write to.
*                  - Data : Data to write. 
* Output         : None
* Return         : NOR_Status:The returned value can be: NOR_SUCCESS, NOR_ERROR
*                  or NOR_TIMEOUT
* Attention		 : None
*******************************************************************************/
NOR_Status EMC_NOR_WriteWord(uint32_t WriteAddr, uint16_t Data)
{
  NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
  NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
  NOR_WRITE(ADDR_SHIFT(0x0555), 0x00A0);
  NOR_WRITE((NOR_FLASH_START_ADDR + WriteAddr), Data);

  return (EMC_NOR_GetStatus(Program_Timeout));
}

/*******************************************************************************
* Function Name  : EMC_NOR_WriteBuffer
* Description    : Writes a half-word buffer to the FSMC NOR memory. 
* Input          : - pBuffer : pointer to buffer. 
*                  - WriteAddr : NOR memory internal address from which the data 
*                    will be written.
*                  - NumHalfwordToWrite : number of Half words to write. 
* Output         : None
* Return         : NOR_Status:The returned value can be: NOR_SUCCESS, NOR_ERROR
*                  or NOR_TIMEOUT
* Attention		 : None
*******************************************************************************/
NOR_Status EMC_NOR_WriteBuffer(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite)
{
  NOR_Status status = NOR_ONGOING; 

  do
  {
    /* Transfer data to the memory */
    status = EMC_NOR_WriteWord(WriteAddr, *pBuffer++);
    WriteAddr = WriteAddr + 2;
    NumHalfwordToWrite--;
  }
  while((status == NOR_SUCCESS) && (NumHalfwordToWrite != 0));
  
  return (status); 
}

/******************************************************************************
* Function Name  : EMC_NOR_ReadWord
* Description    : Reads a word from the NOR memory. 
* Input          : - ReadAddr : NOR memory internal address to read from.
* Output         : None
* Return         : word read from the NOR memory
* Attention		 : None
*******************************************************************************/
uint16_t EMC_NOR_ReadWord(uint32_t ReadAddr)
{
  NOR_WRITE(ADDR_SHIFT(0x00555), 0x00AA); 
  NOR_WRITE(ADDR_SHIFT(0x002AA), 0x0055);  
  NOR_WRITE((NOR_FLASH_START_ADDR + ReadAddr), 0x00F0 );

  return (*(volatile short *)((NOR_FLASH_START_ADDR + ReadAddr)));
}

/*******************************************************************************
* Function Name  : EMC_NOR_ReadBuffer
* Description    : Reads a block of data from the FSMC NOR memory.
* Input          : - pBuffer : pointer to the buffer that receives the data read 
*                    from the NOR memory.
*                  - ReadAddr : NOR memory internal address to read from.
*                  - NumHalfwordToRead : number of Half word to read.
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void EMC_NOR_ReadBuffer(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead)
{
  NOR_WRITE(ADDR_SHIFT(0x0555), 0x00AA);
  NOR_WRITE(ADDR_SHIFT(0x02AA), 0x0055);
  NOR_WRITE((NOR_FLASH_START_ADDR + ReadAddr), 0x00F0);

  for(; NumHalfwordToRead != 0x00; NumHalfwordToRead--) /* while there is data to read */
  {
    /* Read a Halfword from the NOR */
    *pBuffer++ = *(volatile short *)((NOR_FLASH_START_ADDR + ReadAddr));
    ReadAddr = ReadAddr + 2; 
  }  
}

/******************************************************************************
* Function Name  : EMC_NOR_ReturnToReadMode
* Description    : Returns the NOR memory to Read mode.
* Input          : None
* Output         : None
* Return         : NOR_SUCCESS
* Attention		 : None
*******************************************************************************/
NOR_Status EMC_NOR_ReturnToReadMode(void)
{
  NOR_WRITE(NOR_FLASH_START_ADDR, 0x00F0);

  return (NOR_SUCCESS);
}

/******************************************************************************
* Function Name  : EMC_NOR_Reset
* Description    : Returns the NOR memory to Read mode and resets the errors in
*                  the NOR memory Status Register.
* Input          : None
* Output         : None
* Return         : NOR_SUCCESS
* Attention		 : None
*******************************************************************************/
NOR_Status EMC_NOR_Reset(void)
{
  NOR_WRITE(ADDR_SHIFT(0x00555), 0x00AA); 
  NOR_WRITE(ADDR_SHIFT(0x002AA), 0x0055); 
  NOR_WRITE(NOR_FLASH_START_ADDR, 0x00F0); 

  return (NOR_SUCCESS);
}

/******************************************************************************
* Function Name  : EMC_NOR_GetStatus
* Description    : Returns the NOR operation status.
* Input          : - Timeout: NOR progamming Timeout
* Output         : None
* Return         : NOR_Status:The returned value can be: NOR_SUCCESS, NOR_ERROR
*                  or NOR_TIMEOUT
* Attention		 : None
*******************************************************************************/
NOR_Status EMC_NOR_GetStatus(uint32_t Timeout)
{ 
  uint16_t val1 = 0x00, val2 = 0x00;
  NOR_Status status = NOR_ONGOING; 
  uint32_t timeout = Timeout;
  
  uint32_t i;

  for ( i = 0; i < 500; i++ );

  /* Get the NOR memory operation status -------------------------------------*/
  while((Timeout != 0x00) && (status != NOR_SUCCESS))
  {
    Timeout--;

	  /* Read DQ6 and DQ5 */
    val1 = *(volatile short *)(NOR_FLASH_START_ADDR);
    val2 = *(volatile short *)(NOR_FLASH_START_ADDR);

    /* If DQ6 did not toggle between the two reads then return NOR_Success */
    if((val1 & 0x0040) == (val2 & 0x0040)) 
    {
      return NOR_SUCCESS;
    }

    if((val1 & 0x0020) != 0x0020)
    {
      status = NOR_ONGOING;
    }

    val1 = *(volatile short *)(NOR_FLASH_START_ADDR);
    val2 = *(volatile short *)(NOR_FLASH_START_ADDR);
    
    if((val1 & 0x0040) == (val2 & 0x0040)) 
    {
      return NOR_SUCCESS;
    }
    else if((val1 & 0x0020) == 0x0020)
    {
      return NOR_ERROR;
    }
  }

  if(Timeout == 0x00)
  {
    status = NOR_TIMEOUT;
  } 

  /* Return the operation status */
  return (status);
}

 #include "debug_frmwrk.h"
  NOR_IDTypeDef NOR_ID;

/******************************************************************************
* Function Name  : EMC_NOR_Test
* Description    : NOR Test
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void EMC_NOR_Test(void)
{ 
  uint32_t index;
  uint16_t sector;
  uint8_t nor_error;

  /* Initialize the FSMC NOR Flash Interface */
  EMC_NOR_Init();
  /* Set the NOR read modes */
  EMC_NOR_ReturnToReadMode();

  EMC_NOR_ReadID(&NOR_ID);

  EMC_NOR_ReturnToReadMode();

  if( ( NOR_ID.Manufacturer_Code == 0x0001 ) && (NOR_ID.Device_Code1 == 0x227E) &&
	  ( NOR_ID.Device_Code2 == 0x2210 ) && ( NOR_ID.Device_Code3 == 0x2200 ) )
  {
     _DBG_("\r\nNOR Type = S29GL064N 8M NOR Flash  ---------  ");
  }

  else
  {
	 _DBG_("\r\nNOR Type = Unknow  ---------  ");
  }

  nor_error = 0;
  sector = 100;

  /* Erase the NOR memory Sector to write on */
  EMC_NOR_EraseSector( sector * SECTOR_SIZE ); 
  
  /* Write data to FSMC NOR memory */
  /* Fill the buffer to send */
  for (index = 0; index < SECTOR_SIZE / 4; index++ )
  {
      TxBuffer[index] = index%50000 + sector;
  }
  	
  EMC_NOR_WriteBuffer(TxBuffer, sector * SECTOR_SIZE, SECTOR_SIZE / 4);

  /* Read data from FSMC NOR memory */
  memset( RxBuffer, 0 , sizeof(RxBuffer) );
  EMC_NOR_ReadBuffer(RxBuffer, sector * SECTOR_SIZE, SECTOR_SIZE / 4);  
                     
  if( memcmp( (char*)TxBuffer, (char*)RxBuffer, sizeof(RxBuffer) ) == 0 )
  {

  }
  else
  {
     nor_error++;
  }

  for (index = 0; index < SECTOR_SIZE / 4; index++ )
  {
      TxBuffer[index] = index%50000 + sector * sector;
  }

  EMC_NOR_WriteBuffer(TxBuffer, sector * SECTOR_SIZE + SECTOR_SIZE/2, SECTOR_SIZE / 4);

  /* Read data from FSMC NOR memory */
  memset( RxBuffer, 0 , sizeof(RxBuffer) );
  EMC_NOR_ReadBuffer(RxBuffer, sector * SECTOR_SIZE + SECTOR_SIZE/2, SECTOR_SIZE / 4);  
                     
  if( memcmp( (char*)TxBuffer, (char*)RxBuffer, sizeof(RxBuffer) ) == 0 )
  {
  }
  else
  {
     nor_error++;
  }		

  if( nor_error == 0 )
  {
	  _DBG_("Nor Flash OK \r\n");
  }
  else
  {
	  _DBG_("Nor Flash error \r\n");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
