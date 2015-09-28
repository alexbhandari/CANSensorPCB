/** @file sys_startup.c 
*   @brief Startup Source File
*   @date 28.Aug.2015
*   @version 04.05.01
*
*   This file contains:
*   - Include Files
*   - Type Definitions
*   - External Functions
*   - VIM RAM Setup
*   - Startup Routine
*   .
*   which are relevant for the Startup.
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


/* USER CODE BEGIN (0) */
/* USER CODE END */


/* Include Files */

#include "sys_common.h"
#include "system.h"
#include "sys_vim.h"
#include "sys_core.h"
#include "sys_memory.h"
#include "esm.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


/* Type Definitions */

typedef void (*handler_fptr)(const uint8 * in, uint8 * out);

/* USER CODE BEGIN (2) */
/* USER CODE END */


/* External Functions */

/*SAFETYMCUSW 94 S MR:11.1 <REVIEWED> "Startup code(handler pointers)" */
/*SAFETYMCUSW 122 S MR:20.11 <REVIEWED> "Startup code(exit and abort need to be present)" */
/*SAFETYMCUSW 296 S MR:8.6 <REVIEWED> "Startup code(library functions at block scope)" */
/*SAFETYMCUSW 298 S MR:  <REVIEWED> "Startup code(handler pointers)" */
/*SAFETYMCUSW 299 S MR:  <REVIEWED> "Startup code(typedef for handler pointers in library )" */
/*SAFETYMCUSW 326 S MR:8.2 <REVIEWED> "Startup code(Declaration for main in library)" */
/*SAFETYMCUSW 60 D MR:8.8 <REVIEWED> "Startup code(Declaration for main in library;Only doing an extern for the same)" */
/*SAFETYMCUSW 94 S MR:11.1 <REVIEWED> "Startup code(handler pointers)" */
/*SAFETYMCUSW 354 S MR:1.4 <REVIEWED> " Startup code(Extern declaration present in the library)" */

/*SAFETYMCUSW 218 S MR:20.2 <REVIEWED> "Functions from library" */

extern void __TI_auto_init(void);
extern void main(void);
extern void exit(int _status);

/* USER CODE BEGIN (3) */
/* USER CODE END */


/* Vim Ram Definition */
/** @struct vimRam
*   @brief Vim Ram Definition
*
*   This type is used to access the Vim Ram.
*/
/** @typedef vimRAM_t
*   @brief Vim Ram Type Definition
*
*   This type is used to access the Vim Ram.
*/
typedef volatile struct vimRam
{
    t_isrFuncPTR ISR[VIM_CHANNELS];
} vimRAM_t;

#define vimRAM ((vimRAM_t *)0xFFF82000U)

static const t_isrFuncPTR s_vim_init[64] =
{
    phantomInterrupt,
    esmHighInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    can1HighLevelInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    can2HighLevelInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
    phantomInterrupt,
};


/* Startup Routine */

/* USER CODE BEGIN (4) */
/* USER CODE END */

#pragma INTERRUPT(_c_int00, RESET)

void _c_int00()
{

    /* Enable VFP Unit */
    _coreEnableVfp_();
	
    /* Initialize Core Registers */
    _coreInitRegisters_();

    /* Initialize Stack Pointers */
    _coreInitStackPointer_();
	
    /* Enable IRQ offset via Vic controller */
    _coreEnableIrqVicOffset_();
	
    /* Initialize System */
    systemInit();
	
    /* Initialize memory */
    _memoryInit_();

    /* Initialize VIM table */
    {
        uint32 i;

        for (i = 0; i < 64U; i++)
        {
            vimRAM->ISR[i] = s_vim_init[i];
        }
    }

    /* set IRQ/FIQ priorities */
    vimREG->FIRQPR0 =  SYS_FIQ
                    | (SYS_FIQ <<  1U)
                    | (SYS_IRQ <<  2U)
                    | (SYS_IRQ <<  3U)
                    | (SYS_IRQ <<  4U)
                    | (SYS_IRQ <<  5U)
                    | (SYS_IRQ <<  6U)
                    | (SYS_IRQ <<  7U)
                    | (SYS_IRQ <<  8U)
                    | (SYS_IRQ <<  9U)
                    | (SYS_IRQ << 10U)
                    | (SYS_IRQ << 11U)
                    | (SYS_IRQ << 12U)
                    | (SYS_IRQ << 13U)
                    | (SYS_IRQ << 14U)
                    | (SYS_IRQ << 15U)
                    | (SYS_IRQ << 16U)
                    | (SYS_IRQ << 17U)
                    | (SYS_IRQ << 18U)
                    | (SYS_IRQ << 19U)
                    | (SYS_IRQ << 20U)
                    | (SYS_IRQ << 21U)
                    | (SYS_IRQ << 22U)
                    | (SYS_IRQ << 23U)
                    | (SYS_IRQ << 24U)
                    | (SYS_IRQ << 25U)
                    | (SYS_IRQ << 26U)
                    | (SYS_IRQ << 27U)
                    | (SYS_IRQ << 28U)
                    | (SYS_IRQ << 29U)
                    | (SYS_IRQ << 30U)
                    | (SYS_IRQ << 31U);

    vimREG->FIRQPR1 =  SYS_IRQ
                    | (SYS_IRQ <<  1U)
                    | (SYS_IRQ <<  2U)
                    | (SYS_IRQ <<  3U)
                    | (SYS_IRQ <<  4U)
                    | (SYS_IRQ <<  5U)
                    | (SYS_IRQ <<  6U)
                    | (SYS_IRQ <<  7U)
                    | (SYS_IRQ <<  8U)
                    | (SYS_IRQ <<  9U)
                    | (SYS_IRQ << 10U)
                    | (SYS_IRQ << 11U)
                    | (SYS_IRQ << 12U)
                    | (SYS_IRQ << 13U)
                    | (SYS_IRQ << 14U)
                    | (SYS_IRQ << 15U)
                    | (SYS_IRQ << 16U)
                    | (SYS_IRQ << 17U)
                    | (SYS_IRQ << 18U)
                    | (SYS_IRQ << 19U)
                    | (SYS_IRQ << 20U)
                    | (SYS_IRQ << 21U)
                    | (SYS_IRQ << 22U)
                    | (SYS_IRQ << 23U)
                    | (SYS_IRQ << 24U)
                    | (SYS_IRQ << 25U)
                    | (SYS_IRQ << 26U)
                    | (SYS_IRQ << 27U)
                    | (SYS_IRQ << 28U)
                    | (SYS_IRQ << 29U)
                    | (SYS_IRQ << 30U);

    /* enable interrupts */
    vimREG->REQMASKSET0 = 1U
                        | (0U << 1U)
                        | (0U << 2U)
                        | (0U << 3U)
                        | (0U << 4U)
                        | (0U << 5U)
                        | (0U << 6U)
                        | (0U << 7U)
                        | (0U << 8U)
                        | (0U << 9U)
                        | (0U << 10U)
                        | (0U << 11U)
                        | (0U << 12U)
                        | (0U << 13U)
                        | (0U << 14U)
                        | (0U << 15U)
                        | (1U << 16U)
                        | (0U << 17U)
                        | (0U << 18U)
                        | (0U << 19U)
                        | (0U << 20U)
                        | (0U << 21U)
                        | (0U << 22U)
                        | (0U << 23U)
                        | (0U << 24U)
                        | (0U << 25U)
                        | (0U << 26U)
                        | (0U << 27U)
                        | (0U << 28U)
                        | (0U << 29U)
                        | (0U << 30U)
                        | (0U << 31U);

    vimREG->REQMASKSET1 = 0U
                        | (0U << 1U)
                        | (0U << 2U)
                        | (1U << 3U)
                        | (0U << 4U)
                        | (0U << 5U)
                        | (0U << 6U)
                        | (0U << 7U)
                        | (0U << 8U)
                        | (0U << 9U)
                        | (0U << 10U)
                        | (0U << 11U)
                        | (0U << 12U)
                        | (0U << 13U)
                        | (0U << 14U)
                        | (0U << 15U)
                        | (0U << 16U)
                        | (0U << 17U)
                        | (0U << 18U)
                        | (0U << 19U)
                        | (0U << 20U)
                        | (0U << 21U)
                        | (0U << 22U)
                        | (0U << 23U)
                        | (0U << 24U)
                        | (0U << 25U)
                        | (0U << 26U)
                        | (0U << 27U)
                        | (0U << 28U)
                        | (0U << 29U)
                        | (0U << 30U);


    /* initialize global variable and constructors */
	__TI_auto_init();

/* USER CODE BEGIN (5) */
/* USER CODE END */

    /* call the application */
    main();
    exit(0);
}


/* USER CODE BEGIN (6) */
/* USER CODE END */
