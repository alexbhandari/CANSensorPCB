/** @file hal_stdtypes.h
*   @brief HALCoGen standard types header File
*   @date 28.Aug.2015
*   @version 04.05.01
*   
*   This file contains:
*   - Type and Global definitions which are relevant for all drivers.
*/

/* 
* Copyright (C) 2009-2015 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef __HAL_STDTYPES_H__
#define __HAL_STDTYPES_H__

#include <stdint.h>

/* USER CODE BEGIN (0) */
/* USER CODE END */
/************************************************************/
/* Type Definitions                                         */
/************************************************************/
#ifndef _UINT64_DECLARED
typedef unsigned long long uint64;
#define	_UINT64_DECLARED
#endif

#ifndef _UINT32_DECLARED
typedef unsigned int uint32;
#define	_UINT32_DECLARED
#endif

#ifndef _UINT16_DECLARED
typedef unsigned short uint16;
#define	_UINT16_DECLARED
#endif

#ifndef _UINT8_DECLARED
typedef unsigned char uint8;
#define	_UINT8_DECLARED
#endif

#ifndef _BOOLEAN_T_DECLARED
typedef unsigned char boolean;
typedef unsigned char boolean_t;
#define	_BOOLEAN_T_DECLARED
#endif

#ifndef _SINT64_T_DECLARED
typedef signed long long sint64;
#define	_SINT64_T_DECLARED
#endif

#ifndef _SINT32_DECLARED
typedef signed int sint32;
#define	_SINT32_DECLARED
#endif

#ifndef _SINT16_DECLARED
typedef signed short sint16;
#define	_SINT16_DECLARED
#endif

#ifndef _SINT8_DECLARED
typedef signed char sint8;
#define	_SINT8_DECLARED
#endif

#ifndef _FLOAT32_DECLARED
typedef float float32;
#define	_FLOAT32_DECLARED
#endif

#ifndef _FLOAT64_DECLARED
typedef double float64;
#define	_FLOAT64_DECLARED
#endif

/************************************************************/
/* Global Definitions                                       */
/************************************************************/
/** @def NULL
*   @brief NULL definition
*/
#ifndef NULL
    #define NULL ((void *) 0U)
#endif

/** @def TRUE
*   @brief definition for TRUE
*/
#ifndef TRUE
    #define TRUE (boolean)1U
#endif

/** @def FALSE
*   @brief BOOLEAN definition for FALSE
*/
#ifndef FALSE
    #define FALSE (boolean)0U
#endif

/* USER CODE BEGIN (1) */
/* USER CODE END */

#endif /* __HAL_STDTYPES_H__ */
