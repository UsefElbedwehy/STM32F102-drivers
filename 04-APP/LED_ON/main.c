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

#include "LED_prv.h"
#include "LED_interface.h"

int main(void)
{

	RCC_SetClkSts(CLK_SRC_HSE, RCC_ON);
	RCC_SetSysClk(CLK_SRC_HSE);
    RCC_APB2EnableClock(APB2_IOPC);
    RCC_APB2EnableClock(APB2_IOPA);

    LED_Init(PORTC, PIN15);
    LED_Init(PORTC, PIN14);
    LED_Init(PORTC, PIN13);
    LED_Init(PORTA, PIN1);
    LED_Init(PORTA, PIN2);

    LED_On(PORTC, PIN15);
    LED_On(PORTC, PIN14);
    LED_On(PORTC, PIN13);
    LED_On(PORTA, PIN1);
    LED_On(PORTA, PIN2);

    while(1)
	{

	}
}
