/** @file system.c 
*   @brief System Driver Source File
*   @date 28.Aug.2015
*   @version 04.05.01
*
*   This file contains:
*   - API Functions
*   .
*   which are relevant for the System driver.
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

#include "system.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @fn void systemInit(void)
*   @brief Initializes System Driver
*
*   This function initializes the System driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void systemInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */

    /** @b Initialize @b Flash @b Wrapper: */

    /** - Setup flash read mode, address wait states and data wait states */
    flashWREG->FRDCNTL =  0x01000000U 
                       | (3U << 8U) 
                       | (1U << 4U) 
                       |  1U;

    /** - Setup flash bank power modes */
    flashWREG->FBFALLBACK = 0x05050000
                          | (SYS_SLEEP << 14U) 
                          | (SYS_SLEEP << 12U) 
                          | (SYS_SLEEP << 10U) 
                          | (SYS_SLEEP << 8U) 
                          | (SYS_ACTIVE << 6U) 
                          | (SYS_ACTIVE << 4U) 
                          | (SYS_ACTIVE << 2U) 
                          |  SYS_ACTIVE;

    /** @b Initialize @b Lpo: */

    systemREG1->LPOMONCTL = (1U << 24U)
                          | (8U << 8U)
                          |  8U;

    /** @b Initialize @b Secondary Pll: */

    systemREG2->PLLCTL3 = ((2U - 1U) << 22U)
                        | ((10U - 1U) << 8U)
                        |  (1U - 1U);


    /** @b Initialize @b Pll: */

    /** - Setup pll control register 1:
    *     - Setup reset on oscillator slip 
    *     - Setup bypass on pll slip
    *     - Setup Pll output clock divider
    *     - Setup reset on oscillator fail
    *     - Setup reference clock divider 
    *     - Setup Pll multiplier          
    */
    systemREG1->PLLCTL1 =  0x00000000U 
                        |  0x20000000U 
                        | (0U << 24U) 
                        |  0x00000000U 
                        | (5U << 16U) 
                        | (119U << 8U);

    /** - Setup pll control register 1 
    *     - Enable/Disable frequency modulation
    *     - Setup spreading rate
    *     - Setup bandwidth adjustment
    *     - Setup internal Pll output divider
    *     - Setup spreading amount
    */
    systemREG1->PLLCTL2 = 0x00000000U
                        | (255U << 22U)
                        | (7U << 12U)
                        | (1U << 9U)
                        |  61U;


    /** @b Initialize @b Clock @b Tree: */

    /** - Start clock source lock */
    systemREG1->CSDIS = 0x00000000U 
                      | 0x00000000U 
                      | 0x00000000U 
                      | 0x00000008U 
                      | 0x00000004U 
                      | 0x00000000U 
                      | 0x00000000U;

    /** - Wait for until clocks are locked */
    while ((systemREG1->CSVSTAT & ((systemREG1->CSDIS ^ 0xFF) & 0xFF)) != ((systemREG1->CSDIS ^ 0xFF) & 0xFF));

    /** - Setup GCLK, HCLK and VCLK clock source for normal operation, power down mode and after wakeup */
    systemREG1->GHVSRC = (SYS_OSC << 24U) 
                       | (SYS_OSC << 16U) 
                       |  SYS_PLL;

    /** - Power-up all peripherals */
    pcrREG->PSPWRDWNCLR0 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR1 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR2 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR3 = 0xFFFFFFFFU;

    /** - Setup synchronous peripheral clock dividers for VCLK1 and VCLK2 */
    systemREG1->CLKCNTL  = (systemREG1->CLKCNTL & 0xFFF0FFFFU) 
                         | (15U << 16U); 
    systemREG1->CLKCNTL  = (systemREG1->CLKCNTL & 0xF0F0FFFFU) 
						 | (1U << 24U)  
						 | (1U << 16U);  

    /** - Setup RTICLK1 and RTICLK2 clocks */
    systemREG1->RCLKSRC = (1U << 24U)
                        | (SYS_VCLK << 16U) 
                        | (1U << 8U)  
                        |  SYS_VCLK;

    /** - Setup asynchronous peripheral clock sources for AVCLK1 and AVCLK2 */
    systemREG1->VCLKASRC = (SYS_FR_PLL << 8U)
                         |  SYS_VCLK;

    /** - Enable Peripherals */
    systemREG1->CLKCNTL |= 1U << 8U;

    /** - set ECLK pins functional mode */
    systemREG1->SYSPC1 = 0U;

    /** - set ECLK pins default output value */
    systemREG1->SYSPC4 = 0U;

    /** - set ECLK pins output direction */
    systemREG1->SYSPC2 = 1U;

    /** - set ECLK pins open drain enable */
    systemREG1->SYSPC7 = 0U;

    /** - set ECLK pins pullup/pulldown enable */
    systemREG1->SYSPC8 = 0U;

    /** - set ECLK pins pullup/pulldown select */
    systemREG1->SYSPC9 = 1U;

    /** - Setup ECLK */
    systemREG1->ECPCNTL = (0U << 24U)
                        | (0U << 23U)
                        | ((8U - 1U) & 0xFFFFU);

    /** @note: HCLK >= VCLK2 >= VCLK_sys */

/* USER CODE BEGIN (4) */
/* USER CODE END */
}

void systemPowerDown(uint32 mode)
{
/* USER CODE BEGIN (5) */
/* USER CODE END */
    /* Disable clock sources */
    systemREG1->CSDISSET = mode & 0x000000FFU;

    /* Disable clock domains */
    systemREG1->CDDIS = (mode >> 8U) & 0x00000FFFU;

    /* Idle CPU */
	/*SAFETYMCUSW 88 S MR:2.1 <REVIEWED> "Assembly in C needed" */
    asm(" wfi");
/* USER CODE BEGIN (6) */
/* USER CODE END */
}


/* USER CODE BEGIN (7) */
/* USER CODE END */
