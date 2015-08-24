/****************************************Copyright (c)**************************************************                         
**
**                                 http://www.powermcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			SST25VF016B.h
** Descriptions:		SST25VF016B Head function 
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

#ifndef __SST25VF016B_H 
#define __SST25VF016B_H

/* Includes ------------------------------------------------------------------*/
#include "lpc_types.h"
#include "lpc177x_8x_ssp.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_pinsel.h"


/* Private typedef -----------------------------------------------------------*/
typedef enum ERTYPE{ Sec1, Sec8, Sec16, Chip } ErType;  
typedef enum IDTYPE{ Manufacturer_ID, Device_ID, JEDEC_ID } idtype;

/* Private define ------------------------------------------------------------*/
#define MAX_ADDR		0x1FFFFF	/* Maximum address */
#define	SEC_MAX     	511         /* Maximum sectors */
#define SEC_SIZE		0x1000      /* Sector size */

/* PORT number that /CS pin assigned on */
#define CS_PORT_NUM		2
/* PIN number that  /CS pin assigned on */
#define CS_PIN_NUM		19

#define SPI_FLASH_CS_LOW()    GPIO_ClearValue( CS_PORT_NUM, (1<<CS_PIN_NUM) );  
#define SPI_FLASH_CS_HIGH()   GPIO_SetValue( CS_PORT_NUM, (1<<CS_PIN_NUM) ); 

/* Private function prototypes -----------------------------------------------*/
void  SPI_FLASH_Init     (void);
int   SSTF016B_Erase     (uint32_t sec1, uint32_t sec2);
int   SSTF016B_ReadID    (idtype IDType,uint32_t* RcvbufPt);
int   SSTF016B_WriteReg  (uint32_t Dst, uint8_t* SndbufPt,uint32_t NByte);
int   SSTF016B_ReadData  (uint32_t Dst, uint8_t* RcvBufPt ,uint32_t NByte);

#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
