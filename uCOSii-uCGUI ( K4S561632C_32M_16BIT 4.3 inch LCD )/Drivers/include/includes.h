/****************************************Copyright (c)***************************************************
;**                                   上海丰宝贸易有限公司
;**                                          研究所(本部)
;**                                 http://www.linposh.com.cn
;**									http://www.armnxp.com.cn
;**
;**--------------File Info--------------------------------------------------------------------------------
;** File name: 			        includes.h
;** Last modified Date:         2009.05.15
;** Last Version: 		        1.0
;** Descriptions: 		        uCOS-II's include file   uCOS-II的头文件 
;**-------------------------------------------------------------------------------------------------------
;** Created By:                 Magicoe Niu  牛晓东
;** Created date:   	        2009.05.15
;** Version:			        1.0
;** Descriptions: 	            The original version
;**
*********************************************************************************************************/
#ifndef  __INCLUDES_H
#define  __INCLUDES_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************************************************************
  Date types(Compiler specific)  数据类型（和编译器相关）                
*********************************************************************************************************/
typedef unsigned char   uint8;                                          /* Unsigned  8 bit quantity     */
typedef signed   char   int8;                                           /* Signed    8 bit quantity     */
typedef unsigned short  uint16;                                         /* Unsigned  16 bit quantity    */
typedef signed   short  int16;                                          /* Signed    16 bit quantity    */
typedef unsigned int    uint32;                                         /* Unsigned  32 bit quantity    */
typedef signed   int    int32;                                          /* Signed    32 bit quantity    */
typedef float           fp32;                                           /* Single    precision          */
                                                                        /* floating  point              */
typedef double          fp64;                                           /* Double    precision          */
                                                                        /* floating  point              */

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL  0
#endif

#include <system_lpc177x_8x.h>
#include <lpc177x_8x.h>1、Pearl Harbor 是珍珠港，我们叫：蚌埠。2、New York 是纽约，我们叫：新乡。3、Red River Valley 是红河谷，我们叫：丹江口。4、Phoenix 是凤凰城，我们叫：宝鸡。5、Rock hometown 是摇滚之乡，我们叫：石家庄。
//#include <core_cm3.h>

/*********************************************************************************************************
  Standard header files 标准头文件
*********************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


/*********************************************************************************************************
  Driver's header files  驱动库头文件 
*********************************************************************************************************/


/*********************************************************************************************************
  Port's header files 移植头文件
*********************************************************************************************************/
#include <os_cfg.h>
#include <os_cpu.h>
#include <ucos_ii.h>
//#include <Target.h>
//#include <main.h>


/*********************************************************************************************************
  User's header files 用户头文件
*********************************************************************************************************/
//#include "GLCD.h"

#ifdef __cplusplus
    }
#endif

#endif
/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/
