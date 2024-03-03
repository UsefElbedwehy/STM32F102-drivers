/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Usef Elbedwehy
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

#include "ErrType.h"

#include "RCC_Private.h"
#include "RCC_Interface.h"

#include "BZR_prv.h"
#include "BZR_interface.h"


int main(void)
{

	RCC_SetClkSts(CLK_SRC_HSE, RCC_ON);
	RCC_SetSysClk(CLK_SRC_HSE);
	RCC_APB2EnableClock(APB2_IOPB);

	BZR_Init();
	BZR_On();
	BZR_Off();

	/* Loop forever */
	while(1)
	{

	}
}
