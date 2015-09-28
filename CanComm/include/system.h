/** @file system.h
*   @brief System Driver Header File
*   @date 28.Aug.2015
*   @version 04.05.01
*   
*   This file contains:
*   - Definitions
*   - Types
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



#ifndef __SYS_SYSTEM_H__
#define __SYS_SYSTEM_H__

#include "reg_system.h"
#include "reg_pcr.h"
#include "reg_flash.h"


/* USER CODE BEGIN (0) */
/* USER CODE END */


/* System General Definitions */

/** @enum systemInterrupt
*   @brief Alias names for clock sources
*
*   This enumeration is used to provide alias names for the clock sources:
*     - IRQ
*     - FIQ
*/
enum systemInterrupt
{
    SYS_IRQ, /**< Alias for IRQ interrupt */
    SYS_FIQ  /**< Alias for FIQ interrupt */
};

/** @enum systemClockSource
*   @brief Alias names for clock sources
*
*   This enumeration is used to provide alias names for the clock sources:
*     - Oscillator
*     - Pll
*     - 32 kHz Oscillator
*     - External1
*     - Low Power Oscillator Low
*     - Low Power Oscillator High
*     - Flexray Pll
*     - External2
*     - Synchronous VCLK1
*/
enum systemClockSource
{
    SYS_OSC       = 0U, /**< Alias for oscillator clock Source                */
    SYS_PLL       = 1U, /**< Alias for Pll clock Source                       */
    SYS_O32       = 2U, /**< Alias for 32 kHz oscillator clock Source         */
    SYS_EXTERNAL  = 3U, /**< Alias for external clock Source                  */
    SYS_LPO_LOW   = 4U, /**< Alias for low power oscillator low clock Source  */
    SYS_LPO_HIGH  = 5U, /**< Alias for low power oscillator high clock Source */
    SYS_FR_PLL    = 6U, /**< Alias for flexray pll clock Source               */
    SYS_EXTERNAL2 = 7U, /**< Alias for external 2 clock Source                */
    SYS_VCLK      = 9U  /**< Alias for synchronous VCLK1 clock Source         */
};

#define SYS_DOZE_MODE   0x000F3F02U
#define SYS_SNOOZE_MODE 0x000F3F03U
#define SYS_SLEEP_MODE  0x000FFFFFU


/** @def SYS_PRE1
*   @brief Alias name for RTI1CLK PRE clock source
*
*   This is an alias name for the RTI1CLK pre clock source.
*   This can be either:
*     - Oscillator
*     - Pll
*     - 32 kHz Oscillator
*     - External
*     - Low Power Oscillator Low
*     - Low Power Oscillator High
*     - Flexray Pll
*/
/*SAFETYMCUSW 79 S MR:19.4 <REVIEWED> "Macro filled using GUI parameter cannot be avoided" */
#define SYS_PRE1 SYS_PLL

/** @def SYS_PRE2
*   @brief Alias name for RTI2CLK pre clock source
*
*   This is an alias name for the RTI2CLK pre clock source.
*   This can be either:
*     - Oscillator
*     - Pll
*     - 32 kHz Oscillator
*     - External
*     - Low Power Oscillator Low
*     - Low Power Oscillator High
*     - Flexray Pll
*/
/*SAFETYMCUSW 79 S MR:19.4 <REVIEWED> "Macro filled using GUI parameter cannot be avoided" */
#define SYS_PRE2 SYS_PLL

/* USER CODE BEGIN (1) */
/* USER CODE END */

/* FlashW General Definitions */


/** @enum flashWPowerModes
*   @brief Alias names for flash bank power modes
*
*   This enumeration is used to provide alias names for the flash bank power modes:
*     - sleep
*     - standby
*     - active
*/
enum flashWPowerModes
{
    SYS_SLEEP   = 0U, /**< Alias for flash bank power mode sleep   */
    SYS_STANDBY = 1U, /**< Alias for flash bank power mode standby */
    SYS_ACTIVE  = 3U  /**< Alias for flash bank power mode active  */
};

/* USER CODE BEGIN (2) */
/* USER CODE END */

/* System Interface Functions */
void systemInit(void);
void systemPowerDown(uint32 mode);


/* USER CODE BEGIN (3) */
/* USER CODE END */


#endif
