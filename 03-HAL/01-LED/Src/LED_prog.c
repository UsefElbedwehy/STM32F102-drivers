/********************************************************************************
 ********************************************************************************
 ********************************************************************************
 * @File	:	LED_prog.c
 * @Author	:	Usef Elbedwehy
 * @Brief	:	Main program body of LED
 * @layer	:	HAL
 * @Date	:	3 March 2024
 ********************************************************************************
 ********************************************************************************
 ********************************************************************************
 ********************************************************************************/
/********************************************************************************
 *********************** ### INCLUDE SECTION ### ********************************
 ********************************************************************************/
#include <stdint.h>

#include "ErrType.h"
#include "Stm32F103xx.h"

#include "GPIO_prv.h"
#include "GPIO_interface.h"

#include "LED_prv.h"
#include "LED_interface.h"
/********************************************************************************/

/********************************************************************************
 *************** ### FUNCTION IMPLEMENTATION SECTION ### ************************
 ********************************************************************************/
void LED_Init(Port_t	Port , Pin_t	PinNum )
{

	PinConfig_t Copy_PinConfig={
			.Port 		= Port				,
			.PinNum 	= PinNum			,
			.Mode		= OUTPUT_MODE2MHZ	,
			.OutputConf	= GP_OUTPUT_PP		,
			.InputConf	= FLOATING_INPUT
	};
	/*GPIO pin initialization*/
	GPIO_u8PinInit(&Copy_PinConfig);
}

void LED_On(Port_t	Port , Pin_t	PinNum )
{
	GPIO_u8SetPinValue(Port, PinNum, PIN_HIGH);
}

void LED_Off(Port_t	Port , Pin_t	PinNum )
{
	GPIO_u8SetPinValue(Port, PinNum, PIN_LOW);
}

void LED_Toggle(Port_t	Port , Pin_t	PinNum )
{
	GPIO_u8TogglePinValue(Port, PinNum);
}






/********************************************************************************/






