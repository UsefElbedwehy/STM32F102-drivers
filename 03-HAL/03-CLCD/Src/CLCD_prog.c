/********************************************************************************
 ********************************************************************************
 ********************************************************************************
 * @File	:	I2C_prog.c
 * @Author	:	Usef Elbedwehy
 * @Brief	:	Main program body of I2C
 * @layer	:	MCAL
 * @Date	:	1 March 2024
 ********************************************************************************
 ********************************************************************************
 ********************************************************************************
 ********************************************************************************/

/********************************************************************************
 ************************** ### INCLUDE SECTION ### *****************************
 ********************************************************************************/
#include <stdint.h>

#include "GPIO_prv.h"
#include "GPIO_interface.h"

#include "SYSTICK_prv.h"
#include "SYSTICK_interface.h"

#include "CLCD_prv.h"
#include "CLCD_interface.h"


/********************************************************************************/
void CLCD_Init(void)
{
	PinConfig_t CLCD_PinD4 = {
			.Port		=	CLCD_DATA_PORT,
			.PinNum		=	CLCD_D4,
			.Mode		=	OUTPUT_MODE2MHZ,
			.OutputConf	=	GP_OUTPUT_PP,
			.InputConf	=	INPUT_PUPD
	};
	PinConfig_t CLCD_PinD5 = {
			.Port		=	CLCD_DATA_PORT,
			.PinNum		=	CLCD_D5,
			.Mode		=	OUTPUT_MODE2MHZ,
			.OutputConf	=	GP_OUTPUT_PP,
			.InputConf	=	INPUT_PUPD
	};
	PinConfig_t CLCD_PinD6 = {
			.Port		=	CLCD_DATA_PORT,
			.PinNum		=	CLCD_D6,
			.Mode		=	OUTPUT_MODE2MHZ,
			.OutputConf	=	GP_OUTPUT_PP,
			.InputConf	=	INPUT_PUPD
	};
	PinConfig_t CLCD_PinD7 = {
			.Port		=	CLCD_DATA_PORT,
			.PinNum		=	CLCD_D7,
			.Mode		=	OUTPUT_MODE2MHZ,
			.OutputConf	=	GP_OUTPUT_PP,
			.InputConf	=	INPUT_PUPD
	};

	PinConfig_t CLCD_PinRS = {
			.Port		=	CLCD_CONTROL_PORT,
			.PinNum		=	CLCD_RS,
			.Mode		=	OUTPUT_MODE2MHZ,
			.OutputConf	=	GP_OUTPUT_PP,
			.InputConf	=	INPUT_PUPD
	};
	PinConfig_t CLCD_PinEN = {
			.Port		=	CLCD_CONTROL_PORT,
			.PinNum		=	CLCD_EN,
			.Mode		=	OUTPUT_MODE2MHZ,
			.OutputConf	=	GP_OUTPUT_PP,
			.InputConf	=	INPUT_PUPD
	};
	GPIO_u8PinInit(&CLCD_PinD4);
	GPIO_u8PinInit(&CLCD_PinD5);
	GPIO_u8PinInit(&CLCD_PinD6);
	GPIO_u8PinInit(&CLCD_PinD7);
	GPIO_u8PinInit(&CLCD_PinRS);
	GPIO_u8PinInit(&CLCD_PinEN);
	SYSTICK_DelayMs(50);
	/*FUNCTION SET*/
	CLCD_SendCmd(FUNCTION_SET);
	/*DISPLAY ON/OFF CONTROL*/
		CLCD_SendCmd(DISPLAY_ON_OFF_CONTROL);
	/*DISPLAY CLEAR*/
	CLCD_SendCmd(DISPLAY_CLEAR);
	/*ENTRY MODE SET*/
	CLCD_SendCmd(RETURN_HOME);
	SYSTICK_DelayMs(50);
}

void CLCD_SendCmd(uint8_t Copy_u8Cmd)
{
	/*D4~D7 are connected as unusual: D7->B12 .... D4->B15
	 * so we have to reverse data
	 * since we have to send the higher data then the lower
	 * but we have reversed data so the higher become lower
	 * so we will reverse then send lower first*/
	uint8_t Local_u8Var = 0;
	uint8_t Local_u8ReversedData = 0;
	uint8_t Local_u8Counter = 0;
	while(Local_u8Counter < 8)
	{
		Local_u8Var = ((Copy_u8Cmd >> Local_u8Counter) & 0x01);
		Local_u8ReversedData |= ( Local_u8Var << (7 - Local_u8Counter) );
		Local_u8Counter++;
	}
	/*R/W is set to W by Hardware*/
	/*RS = 0 : Instruction write operation*/
	GPIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_RS, PIN_LOW);
	/*Write the new lower data Data*/
	GPIO_Write4Bits(CLCD_DATA_PORT, CLCD_D7, Local_u8ReversedData );
	/*E pulse*/
	GPIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_EN, PIN_HIGH);
	SYSTICK_DelayMs(2);
	GPIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_EN, PIN_LOW);
	/*Write the new higher data Data*/
	GPIO_Write4Bits(CLCD_DATA_PORT, CLCD_D7, (Local_u8ReversedData >> 4) );
	/*E pulse*/
	GPIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_EN, PIN_HIGH);
	SYSTICK_DelayMs(2);
	GPIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_EN, PIN_LOW);


}
void CLCD_SendData(uint8_t Copy_u8Data)
{
	/*D4~D7 are connected as unusual: D7->B12 .... D4->B15
	 * so we have to reverse data
	 * since we have to send the higher data then the lower
	 * but we have reversed data so the higher become lower
	 * so we will reverse then send lower first*/
	uint8_t Local_u8Var = 0;
	uint8_t Local_u8ReversedData = 0;
	uint8_t Local_u8Counter = 0;
	while(Local_u8Counter < 8)
	{
		Local_u8Var = ((Copy_u8Data >> Local_u8Counter) & 0x01);
		Local_u8ReversedData |= ( Local_u8Var << (7 - Local_u8Counter) );
		Local_u8Counter++;
	}
	/*R/W is set to W by Hardware*/
	/*RS = 1 : Data write operation*/
	GPIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_RS, PIN_HIGH);
	/*Write the new lower data Data*/
	GPIO_Write4Bits(CLCD_DATA_PORT, CLCD_D7, Local_u8ReversedData );
	/*E pulse*/
	GPIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_EN, PIN_HIGH);
	SYSTICK_DelayMs(2);
	GPIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_EN, PIN_LOW);
	/*Write the new higher data Data*/
	GPIO_Write4Bits(CLCD_DATA_PORT, CLCD_D7, (Local_u8ReversedData >> 4) );
	/*E pulse*/
	GPIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_EN, PIN_HIGH);
	SYSTICK_DelayMs(2);
	GPIO_u8SetPinValue(CLCD_CONTROL_PORT, CLCD_EN, PIN_LOW);
}


void CLCD_PrintWord(char* Copy_pvData)
{
	uint8_t Local_u8Counter = 0;
	while(Copy_pvData[Local_u8Counter] != '\0')
	{
		CLCD_SendData(Copy_pvData[Local_u8Counter]);
		Local_u8Counter++;
		SYSTICK_DelayMs(50);
	}
}
