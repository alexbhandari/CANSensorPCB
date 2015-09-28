/** @file sys_vim.h
*   @brief Vectored Interrupt Module Header File
*   @date 28.Aug.2015
*   @version 04.05.01
*   
*   This file contains:
*   - VIM Type Definitions
*   - VIM General Definitions
*   .
*   which are relevant for Vectored Interrupt Controller.
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



#ifndef __SYS_VIM_H__
#define __SYS_VIM_H__

#include "reg_vim.h"
/* USER CODE BEGIN (0) */
/* USER CODE END */


/* VIM Type Definitions */

/** @typedef t_isrFuncPTR
*   @brief ISR Function Pointer Type Definition
*
*   This type is used to access the ISR handler.
*/
typedef void (*t_isrFuncPTR)();

/* USER CODE BEGIN (1) */
/* USER CODE END */


/* VIM General Configuration */

#define VIM_CHANNELS 64U

/* USER CODE BEGIN (2) */
/* USER CODE END */

/* Interrupt Handlers */

extern void esmHighInterrupt(void);
extern void phantomInterrupt(void);
extern void can1HighLevelInterrupt(void);
extern void can2HighLevelInterrupt(void);

/* USER CODE BEGIN (3) */
/* USER CODE END */


#endif
