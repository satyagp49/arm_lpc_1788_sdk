/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               emc_nor.h
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

#ifndef __EMC_NOR_H
#define __EMC_NOR_H

/* Includes ------------------------------------------------------------------*/
#include "lpc_types.h"
#include "lpc177x_8x_emc.h"
#include <string.h>
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  uint16_t Manufacturer_Code;
  uint16_t Device_Code1;
  uint16_t Device_Code2;
  uint16_t Device_Code3;
}
NOR_IDTypeDef;

/* NOR Status */
typedef enum
{
  NOR_SUCCESS = 0,
  NOR_ONGOING,
  NOR_ERROR,
  NOR_TIMEOUT
}
NOR_Status;

/* Private function prototypes -----------------------------------------------*/
void EMC_NOR_Init(void);
void EMC_NOR_Test(void);
void EMC_NOR_ReadID(NOR_IDTypeDef* NOR_ID);
NOR_Status EMC_NOR_EraseBlock(uint32_t BlockAddr);
NOR_Status EMC_NOR_EraseChip(void);
NOR_Status EMC_NOR_WriteHalfWord(uint32_t WriteAddr, uint16_t Data);
NOR_Status EMC_NOR_WriteBuffer(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite);
NOR_Status EMC_NOR_ProgramBuffer(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite);
uint16_t EMC_NOR_ReadHalfWord(uint32_t ReadAddr);
void EMC_NOR_ReadBuffer(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead);
NOR_Status EMC_NOR_ReturnToReadMode(void);
NOR_Status EMC_NOR_Reset(void);
NOR_Status EMC_NOR_GetStatus(uint32_t Timeout);

#endif /* __EMC_NOR_H */

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

