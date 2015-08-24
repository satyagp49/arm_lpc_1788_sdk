/****************************************Copyright (c)**************************************************                         
**
**                                 http://www.powermcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			WAV.C
** Descriptions:		None
**
**------------------------------------------------------------------------------------------------------
** Created by:			AVRman
** Created date:		2010-11-17
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
#include "wav.h"
#include <stdio.h>

/* Private variables ---------------------------------------------------------*/
WavHeader userWav;


/*******************************************************************************
* Function Name  : WAV_IsValid
* Description    : ÅÐ¶ÏWAV¸ñÊ½
* Input          : - header£ºWAV file header
* Output         : None
* Return         : Returns 1 if the header of a Wav file is valid; otherwise returns 0
* Attention		 : None
*******************************************************************************/
uint8_t WAV_IsValid(const WavHeader *header)
{
    return ((header->chunkID == WAV_CHUNKID)
            && (header->format == WAV_FORMAT)
            && (header->subchunk1Size == 0x10));
}

/*******************************************************************************
* Function Name  : DisplayWavInfo
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void DisplayWavInfo(void)
{   
//    _DBG_( "  Wave file header information \r\n");
//    _DBG_( "-------------------------------- \r\n");
//    _DBG_( "  - Chunk Size      = %d\r\n", userWav.chunkSize);
//    printf( "  - Num. Channels   = %d\r\n", userWav.numChannels);
//    printf( "  - Sample Rate     = %d\r\n", userWav.sampleRate);
//    printf( "  - Byte Rate       = %d\r\n", userWav.byteRate);
//    printf( "  - Block Align     = %d\r\n", userWav.blockAlign);
//    printf( "  - Bits Per Sample = %d\r\n", userWav.bitsPerSample);
}	
