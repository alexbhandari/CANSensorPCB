/** @file sys_main.c 
*   @brief Application main file
*   @date 28.Aug.2015
*   @version 04.05.01
*
*   This file contains an empty main function,
*   which can be used for the application.
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


/** @mainpage TMS570LS20216SZWT Micro Controller Driver Documentation
*   @date 28.Aug.2015
*
*   @section sec1 Introduction
*   This document describes the TMS570 microcontroller peripheral drivers.
*
*   @section sec2 Drivers
*   @subsection sec2sub1 RTI Driver
*   Real Time Interface Module Driver.
*   @subsection sec2sub2 GIO Driver
*   General Purpose Input Output Module Driver.
*   @subsection sec2sub3 SCI Driver
*   Serial Communication Interface Module Driver.
*   @subsection sec2sub4 SPI Driver
*   Serial Peripheral Interface Module Driver.
*   @subsection sec2sub5 CAN Driver
*   Controller Area Network Module Driver.
*   @subsection sec2sub6 ADC Driver
*   Analog to Digital Converter Module Driver.
*   @subsection sec2sub7 LIN Driver
*   Local Interconnect Network Module Driver.
*   @subsection sec2sub8 HET Driver
*   High End Timer Module Driver.
*/

/* USER CODE BEGIN (0) */
/* USER CODE END */


/* Include Files */

#include "sys_common.h"
#include "system.h"

/* USER CODE BEGIN (1) */

#include "can.h"
#include "esm.h"
#include "sys_core.h"

#define D_COUNT 8

uint 32 cnt=0, error =0, tx_done =0;
uint8 tx_data[D_COUNT][8] = {0};
uint8 rx_data[D_COUNT][8] = {0};
uint8 *tx_ptr = &tx_data[0][0];
uint8 *rx_ptr = &rx_data[0][0];
uint8 *dptr=0;

void dumpSomeData();
/* USER CODE END */

/* USER CODE BEGIN (2) */
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/
void main(void)
{
/* USER CODE BEGIN (3) */

	/* enable irq inturrupt in Cortex R4 */
	_enable_inturrupt_();

	dumpSomeData();

	canInit();

	canEnableErrorNotification(canREG1);
	canEnableErrorNotification(canREG2);

	for(cnt=0;cnt<D_COUNT;cnt++)
	{
		canTransmit(canREG1, canMESSAGE_BOX1,
		 tx_ptr); /* transmitting 8 different chunks 1 by 1 */
		while(tx_done == 0) {}; //wait for transfer to complete
		tx_done=0;
		tx_prt+=8; //next chunk
	}

	tx_ptr = &tx_data[0][0];
	rx_ptr = &rx_data[0][0];

	for(cnt=1;cnt<63;cnt++)
	{
		if(*tx_ptr++ != *rx_ptr++)
		{
			error++; //data error
		}
	}

	while(1){}; //wait forever after tx-rx completes

/* USER CODE END */
}


/* USER CODE BEGIN (4) */
//writing some data to ram
void dumpSomeData()
{
	uint32 tmp = 0x11;

	cnt = (D_COUNT*8)-1;
	dptr = &tx_data[0][0];
	*dptr = tmp;

	while(cnt--)
	{
		tmp = *dptr++;
		*dptr = tmp + 0x11;
	}
}

/* can interrupt notification */
/* Note: You need to remove canMessageNotification from notification.c to avoid redefinition */
void canMessageNotification(canBASE_t *node, uint32 messageBox)
{
	/* node 1 - transfer request */
	if(node==canREG1)
	{
		tx_done=1; //confirm transfer request
	}
	
	/* node 2 - recieve complete */
	if(node==canREG2)
	{
		while(!canIsRxMessageArrived(canREG2,canMESSAGE_BOX1));
		canGetData(canREG2, canMESSAGE_BOX1,rx_ptr); //copy to RAM
		rx_ptr+=8; 
	}
	/* Note: since only message box 1 is used on both nodes we don't check it here */
}
/* USER CODE END */
