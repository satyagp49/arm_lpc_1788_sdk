/****************************************Copyright (c)**************************************************                         
**
**                                 http://www.powermcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			WAV.h
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

#ifndef __WAV_H
#define __WAV_H

/* Includes ------------------------------------------------------------------*/
#include "uda1380.h"

/* Private define ------------------------------------------------------------*/
#define WAV_CHUNKID       0x46464952	/* WAV letters "RIFF" */
#define WAV_FORMAT        0x45564157	/* WAV letters "WAVE" */
#define WAV_SUBCHUNKID    0x20746D66    /* WAV letters "fmt" */

/* Private typedef -----------------------------------------------------------*/

/*------------------------------------------------------------------------------
   Standard WAV file header information.
------------------------------------------------------------------------------*/
typedef struct _WavHeader
{
	/* Contains the letters "RIFF" in ASCII form */
	unsigned int  chunkID;
	/* Size of the rest of the chunk following this number */
	unsigned int  chunkSize;
	/* Contains the letters "WAVE" */
	unsigned int format;
	/* Contains the letters "fmt" */
	unsigned int subchunk1ID;
	/* 16 for PCM.  This is the size of the rest of the Subchunk
       which follows this number */
	unsigned int  subchunk1Size;
	/* PCM = 1 (i.e. Linear quantization). Values other than 1 indicate some
       form of compression */
	unsigned short audioFormat;
	/* Mono = 1, Stereo = 2, etc */
	unsigned short numChannels;
	/* 8000, 44100, etc */
	unsigned int   sampleRate;
	/* SampleRate * NumChannels * BitsPerSample/8 */
	unsigned int   byteRate;
	/* NumChannels * BitsPerSample/8 */
	unsigned short blockAlign; 
	/* 8 bits = 8, 16 bits = 16, etc */
	unsigned short bitsPerSample;
	/* Contains the letters "data" */
	unsigned int subchunk2ID;
	/* Number of bytes in the data */
	unsigned int subchunk2Size;

} WavHeader;

/* Private variables ---------------------------------------------------------*/
extern WavHeader userWav;

/* Private function prototypes -----------------------------------------------*/
void DisplayWavInfo(void);
uint8_t WAV_IsValid(const WavHeader *header);

#endif 

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

