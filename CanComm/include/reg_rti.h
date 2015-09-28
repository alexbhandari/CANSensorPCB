/** @file reg_rti.h
*   @brief RTI Register Layer Header File
*   @date 28.Aug.2015
*   @version 04.05.01
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the RTI driver.
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


#ifndef __REG_RTI_H__
#define __REG_RTI_H__

#include "sys_common.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Rti Register Frame Definition */
/** @struct rtiBase
*   @brief RTI Register Frame Definition
*
*   This type is used to access the RTI Registers.
*/
/** @typedef rtiBASE_t
*   @brief RTI Register Frame Type Definition
*
*   This type is used to access the RTI Registers.
*/
typedef volatile struct rtiBase
{
    uint32 GCTRL;          /**< 0x0000: Global Control Register   */
    uint32 TBCTRL;         /**< 0x0004: Timebase Control Register */
    uint32 CAPCTRL;        /**< 0x0008: Capture Control Register  */
    uint32 COMPCTRL;       /**< 0x000C: Compare Control Register  */
    struct
    {
        uint32 FRCx;       /**< 0x0010,0x0030: Free Running Counter x Register         */
        uint32 UCx;        /**< 0x0014,0x0034: Up Counter x Register                   */
        uint32 CPUCx;      /**< 0x0018,0x0038: Compare Up Counter x Register           */
        uint32   rsvd1;    /**< 0x001C,0x003C: Reserved                                */
        uint32 CAFRCx;     /**< 0x0020,0x0040: Capture Free Running Counter x Register */
        uint32 CAUCx;      /**< 0x0024,0x0044: Capture Up Counter x Register           */
        uint32   rsvd2[2U]; /**< 0x0028,0x0048: Reserved                                */
    } CNT[2U];               /**< Counter x selection:
                                    - 0: Counter 0
                                    - 1: Counter 1                                       */
    struct
    {
        uint32 COMPx;      /**< 0x0050,0x0058,0x0060,0x0068: Compare x Register        */
        uint32 UDCPx;      /**< 0x0054,0x005C,0x0064,0x006C: Update Compare x Register */
    } CMP[4U];               /**< Compare x selection:
                                    - 0: Compare 0 
                                    - 1: Compare 1
                                    - 2: Compare 2
                                    - 3: Compare 3                                       */
    uint32 TBLCOMP;        /**< 0x0070: External Clock Timebase Low Compare Register   */
    uint32 TBHCOMP;        /**< 0x0074: External Clock Timebase High Compare Register  */
    uint32   rsvd3[2U];     /**< 0x0078: Reserved                                       */
    uint32 SETINT;         /**< 0x0080: Set/Status Interrupt Register                  */
    uint32 CLEARINT;       /**< 0x0084: Clear/Status Interrupt Register                */
    uint32 INTFLAG;        /**< 0x0088: Interrupt Flag Register                        */
    uint32   rsvd4;        /**< 0x008C: Reserved                                       */
} rtiBASE_t;

/** @def rtiREG1
*   @brief RTI1 Register Frame Pointer
*
*   This pointer is used by the RTI driver to access the RTI1 registers.
*/
#define rtiREG1 ((rtiBASE_t *)0xFFFFFC00U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
