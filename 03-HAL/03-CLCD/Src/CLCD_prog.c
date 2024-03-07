/********************************************************************************
 ********************************************************************************
 ********************************************************************************
 * @File	:	CLCD_prog.c
 * @Author	:	Usef Elbedwehy
 * @Brief	:	Main program body of CLCD
 * @layer	:	HAL
 * @Date	:	6 March 2024
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

/*
 * @fn		:	CLCD_Init
 * @brief	:	Initializes the configurations the character 16x2 LCD
 * @param	:	void
 * @retval	:	void
 *
 * */
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
	SYSTICK_DelayMs(2);
}


/*
 * @fn		:	CLCD_SendCmd
 * @brief	:	to send command to the character 16x2 LCD
 * @param	:	Copy_u8Cmd 		(uint8_t)
 * @retval	:	void
 *
 * */
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

/*
 * @fn		:	CLCD_SendData
 * @brief	:	to send Data to the character 16x2 LCD
 * @param	:	Copy_u8Data			(uint8_t)
 * @retval	:	void
 *
 * */
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

/*
 * @fn		:	CLCD_PrintChar
 * @brief	:	to send data (of type char) to the character 16x2 LCD
 *  										you can send anything from the asci table
 * @param	:	Copy_u8Data  -> for example : 'a'  , 'A' ,or '0'
 * @retval	:	void
 *
 * */
void CLCD_PrintChar(uint8_t Copy_u8Data)
{
	CLCD_SendData(Copy_u8Data);
}


/*
 * @fn		:	CLCD_PrintString
 * @brief	:	to send data (of type String) to the character 16x2 LCD
 *  						you can send anything between " "
 * @param	:	Copy_pvData  pointer to string -> for example : "Driver"  ,or "Data is 6/3/2024"
 * @retval	:	void
 *
 * */
void CLCD_PrintString(char* Copy_pvData)
{
	uint8_t Local_u8Counter = 0;
	while(Copy_pvData[Local_u8Counter] != '\0')
	{
		CLCD_SendData(Copy_pvData[Local_u8Counter]);
		Local_u8Counter++;

	}
}

/*
 * @fn		:	CLCD_PrintNumber
 * @brief	:	to send data numbers (of type int32_t) to the character 16x2 LCD
 *  						you can send anything between " "
 * @param	:	Copy_u32Number  	pointer to string -> for example : "1234"
 * @retval	:	void
 *
 * */
void CLCD_PrintNumber(int32_t Copy_u32Number)
{

	uint8_t Local_u8i =0;
	uint8_t Local_u8Counter =0;
	uint8_t Local_u8ReverseNum[8];
	if(Copy_u32Number == 0)
	{
		CLCD_SendData('0');
	}
	else if(Copy_u32Number < 0)
	{
		CLCD_SendData('-');
		Copy_u32Number *= (-1) ;
	}

	while(Copy_u32Number != 0)
	{
		Local_u8ReverseNum[Local_u8Counter] = (Copy_u32Number % 10) ;
		Copy_u32Number = Copy_u32Number / 10;
		Local_u8Counter ++;
	}
	for(Local_u8i=(Local_u8Counter); Local_u8i > 0 ; Local_u8i--)
	{
		CLCD_SendData( Local_u8ReverseNum[Local_u8i-1] + '0');
	}

}

/*
 * @fn		:	CLCD_GoToXY
 * @brief	:	to set the courser location
 * @param	:	Copy_u8XAddress  	(uint8_t)
 * @param	:	Copy_u8YAddress  	(uint8_t)
 * @retval	:	void
 *
 * */
void CLCD_GoToXY(uint8_t Copy_u8XAddress ,uint8_t Copy_u8YAddress )
{
	uint8_t Local_CurrentAddress = 0;
	switch(Copy_u8XAddress)
	{
	case 0:
		Local_CurrentAddress = Copy_u8YAddress;
		break;
	case 1:
		Local_CurrentAddress = Copy_u8YAddress + 0x40;
		break;
	}
	CLCD_SendCmd(Local_CurrentAddress + 128);
}

/*
 * @fn		:	CLCD_ClearDisplay
 * @brief	:	to clear the display of the character 16*2 LCD
 * @param	:	void
 * @retval	:	void
 *
 * */
void CLCD_ClearDisplay(void)
{
	CLCD_SendCmd(DISPLAY_CLEAR);
}
