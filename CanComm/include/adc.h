/** @file adc.h
*   @brief ADC Driver Header File
*   @date 28.Aug.2015
*   @version 04.05.01
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the ADC driver.
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


#ifndef __ADC_H__
#define __ADC_H__

#include "reg_adc.h"


/* USER CODE BEGIN (0) */
/* USER CODE END */


/* ADC General Definitions */

/** @def adcGROUP0
*   @brief Alias name for ADC event group
*
*   @note This value should be used for API argument @a group
*/
#define adcGROUP0 0U

/** @def adcGROUP1
*   @brief Alias name for ADC group 1
*
*   @note This value should be used for API argument @a group
*/
#define adcGROUP1 1U

/** @def adcGROUP2
*   @brief Alias name for ADC group 2
*
*   @note This value should be used for API argument @a group
*/
#define adcGROUP2 2U

/** @enum adcResolution
*   @brief Alias names for data resolution
*   This enumeration is used to provide alias names for the data resolution:
*     - 12 bit resolution
*     - 10 bit resolution
*     - 8  bit resolution
*/

enum adcResolution
{
    ADC_12_BIT = 0x00000000U, /**< Alias for 12 bit data resolution */
    ADC_10_BIT = 0x00000100U, /**< Alias for 10 bit data resolution */
    ADC_8_BIT  = 0x00000200U  /**< Alias for 8 bit data resolution  */
};

/** @enum adcFiFoStatus
*   @brief Alias names for FiFo status
*   This enumeration is used to provide alias names for the current FiFo states:
*     - FiFo is not full
*     - FiFo is full
*     - FiFo overflow occurred
*/

enum adcFiFoStatus
{
    ADC_FIFO_IS_NOT_FULL = 0U, /**< Alias for FiFo is not full       */
    ADC_FIFO_IS_FULL     = 1U, /**< Alias for FiFo is full           */
    ADC_FIFO_OVERFLOW    = 3U  /**< Alias for FiFo overflow occurred  */
};

/** @enum adcConversionStatus
*   @brief Alias names for conversion status
*   This enumeration is used to provide alias names for the current conversion states:
*     - Conversion is not finished
*     - Conversion is finished
*/

enum adcConversionStatus
{
    ADC_CONVERSION_IS_NOT_FINISHED = 0U, /**< Alias for current conversion is not finished */
    ADC_CONVERSION_IS_FINISHED     = 8U  /**< Alias for current conversion is  finished    */
};

/** @enum adcHwTriggerSource
*   @brief Alias names for hardware trigger source
*   This enumeration is used to provide alias names for the hardware trigger sources:
*     - event pin
*     - 10 bit resolution
*     - HET pin 8
*     - HET pin 10
*     - RTI compare 0 match
*     - HET pin 17
*     - HET pin 19 
*     - GIO port b pin 0
*     - GIO port b pin 1
*/

enum adcHwTriggerSource
{
    ADC_EVENT,     /**< Alias for event pin           */
    ADC_HET8,      /**< Alias for HET pin 8           */
    ADC_HET10,     /**< Alias for HET pin 10          */
    ADC_RTI_COMP0, /**< Alias for RTI compare 0 match */
    ADC_HET17,     /**< Alias for HET pin 17          */
    ADC_HET19,     /**< Alias for HET pin 19          */
    ADC_GIOB0,     /**< Alias for GIO port b pin 0    */
    ADC_GIOB1      /**< Alias for GIO port b pin 1    */
};

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @struct adcData
*   @brief ADC Conversion data structure
*
*   This type is used to pass adc conversion data.
*/
/** @typedef adcData_t
*   @brief ADC Data Type Definition
*/
typedef struct adcData
{
    uint32            id;     /**< Channel/Pin Id        */
    uint16 value;  /**< Conversion data value */
} adcData_t;


/* USER CODE BEGIN (2) */
/* USER CODE END */

/** 
 *  @defgroup ADC ADC
 *  @brief Analog To Digital Converter Module.
 *  
 *  The microcontroller includes two 12-bit ADC modules with selectable 10-bit or 12-bit resolution
 *
 *	Related Files
 *   - reg_adc.h
 *   - adc.h
 *   - adc.c
 *  @addtogroup ADC
 *  @{
 */
 
/* ADC Interface Functions */

void adcInit(void);
void adcStartConversion(adcBASE_t *adc, uint32 group);
void adcStopConversion(adcBASE_t *adc, uint32 group);
void adcResetFiFo(adcBASE_t *adc, uint32 group);
uint32  adcGetData(adcBASE_t *adc, uint32 group, adcData_t *data);
uint32  adcIsFifoFull(adcBASE_t *adc, uint32 group);
uint32  adcIsConversionComplete(adcBASE_t *adc, uint32 group);
void adcEnableNotification(adcBASE_t *adc, uint32 group);
void adcDisableNotification(adcBASE_t *adc, uint32 group);

/** @fn void adcNotification(adcBASE_t *adc, uint32 group)
*   @brief Group notification
*   @param[in] adc Pointer to ADC node:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*   @param[in] group number of ADC node:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   @note This function has to be provide by the user.
*/
void adcNotification(adcBASE_t *adc, uint32 group);

/**@}*/
/* USER CODE BEGIN (3) */
/* USER CODE END */


#endif
