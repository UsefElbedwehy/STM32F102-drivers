/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file GPIO_prog.c
 * @author Usef Elbedwehy
 * @brief The main GPIO main source file, including function's definitions
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
#include <stdint.h>
#include "Stm32F103xx.h"

#include "ErrType.h"
#include "GPIO_prv.h"
#include "GPIO_interface.h"


/*
 * * * * * * * * * * * * * * * * *
          GPIO ARRAY
 * * * * * * * * * * * * * * * * *
 */
static GPIO_Reg_t* GPIOx[GPIO_PERIPHERAL_NUM]= {  	GPIOA,
		GPIOB,
		GPIOC,
		GPIOD,
		GPIOE,
		GPIOF,
		GPIOG
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @fn GPIO_u8PinInit
 * @brief the function initiatizes the GPIO pin according to
 *  the input parameters
 * @param[in] Copy_PinConfig: the initialization value of pins
 * @retval Local_u8ErrorState
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  PinConfig:	Port, PinNum, Mode,
 *              OutputConfig, InputConfig
 */
ErrorState_t GPIO_u8PinInit(const PinConfig_t* Copy_PinConfig)
{
	ErrorState_t Local_ErrorState=OK;
	/*Check weather the pointer points to Null or Not*/
	if(Copy_PinConfig != NULL)
	{
		/*Check weather the configurations are valid or Not*/
		if((Copy_PinConfig->Port <= PORTG) && (Copy_PinConfig->PinNum <= PIN15) &&
				(Copy_PinConfig->Mode <= OUTPUT_MODE50MHZ) && (Copy_PinConfig->InputConf <= INPUT_PUPD )
				&& (Copy_PinConfig->OutputConf <=AF_OUTPUT_OD) )
		{
			/* * * * * Select GPIO Mode: Input, OUTPUT_MODE10MHZ, OUTPUT_MODE10MHZ, OUTPUT_MODE10MHZ * * * * */
			if(Copy_PinConfig->PinNum <= PIN7)
			{
				/*Pins from PIN0 to PIN7*/
				GPIOx[Copy_PinConfig->Port]->GPIOx_CRL &=~(CRL_MASK<<(CRL_PIN_ACCESS*Copy_PinConfig->PinNum)) ;
				GPIOx[Copy_PinConfig->Port]->GPIOx_CRL |= ( Copy_PinConfig->Mode <<(CRL_PIN_ACCESS*Copy_PinConfig->PinNum));

				/*Check weather the mode is input or output*/
				if(Copy_PinConfig->Mode == INPUT_MODE)
				{
					/*input*/
					GPIOx[Copy_PinConfig->Port]->GPIOx_CRL &=~(CRL_MASK<<(CNF_OFFSET+(CRL_PIN_ACCESS*Copy_PinConfig->PinNum))) ;
					GPIOx[Copy_PinConfig->Port]->GPIOx_CRL |= ( Copy_PinConfig->InputConf <<(CNF_OFFSET+(CRL_PIN_ACCESS*Copy_PinConfig->PinNum)));
				}else
				{
					/*output*/
					GPIOx[Copy_PinConfig->Port]->GPIOx_CRL &=~(CRL_MASK<<(CNF_OFFSET+(CRL_PIN_ACCESS*Copy_PinConfig->PinNum))) ;
					GPIOx[Copy_PinConfig->Port]->GPIOx_CRL |= ( Copy_PinConfig->OutputConf <<(CNF_OFFSET+(CRL_PIN_ACCESS*Copy_PinConfig->PinNum)));
				}

			}
			else
			{
				/*****from PIN8 to PIN15*****/
				GPIOx[Copy_PinConfig->Port]->GPIOx_CRH &=~(CRH_MASK<<(CRH_PIN_ACCESS*((Copy_PinConfig->PinNum)%H_FAC))) ;
				GPIOx[Copy_PinConfig->Port]->GPIOx_CRH |= ( Copy_PinConfig->Mode <<(CRH_PIN_ACCESS*((Copy_PinConfig->PinNum)%H_FAC)));

				/*Check weather the mode is input or output*/
				if(Copy_PinConfig->Mode == INPUT_MODE)
				{
					/*input*/
					GPIOx[Copy_PinConfig->Port]->GPIOx_CRH &=~(CRH_MASK<<( CNF_OFFSET+ (CRH_PIN_ACCESS*((Copy_PinConfig->PinNum) %H_FAC) ) ) ) ;
					GPIOx[Copy_PinConfig->Port]->GPIOx_CRH |= ( Copy_PinConfig->InputConf <<(CNF_OFFSET+( CRH_PIN_ACCESS* ( (Copy_PinConfig->PinNum) %H_FAC) ) ) );
				}else
				{
					/*output*/
					GPIOx[Copy_PinConfig->Port]->GPIOx_CRH &=~(CRH_MASK<<( CNF_OFFSET+ (CRH_PIN_ACCESS*((Copy_PinConfig->PinNum) %H_FAC) ) ) ) ;
					GPIOx[Copy_PinConfig->Port]->GPIOx_CRH |= ( Copy_PinConfig->OutputConf <<(CNF_OFFSET+( CRH_PIN_ACCESS* ( (Copy_PinConfig->PinNum) %H_FAC) ) ) );
				}
			}
		}
		else
		{
			Local_ErrorState=NOK;
		}

	}
	else
	{
		Local_ErrorState=NULL_POINTER;
	}
	return Local_ErrorState;
}

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                            GPIO SET PIN VALUE
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @fn GPIO_u8SetPinValue
 * @brief the function Set the GPIO pin value
 * @param[in] Port ,PinNum ,PinVal
 * @retval Local_u8ErrorState
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
ErrorState_t GPIO_u8SetPinValue(Port_t	Port , Pin_t	PinNum , PinVal_t PinVal)
{
	ErrorState_t Local_ErrorState=OK;

	if((Port<=PORTG) && (PinNum<=PIN15))
	{
		if(PinVal == PIN_LOW)
		{
			GPIOx[Port]->GPIOx_ODR &=~ (CLEAR_BIT_VAL<<PinNum); /*CLEAR*/
		}
		else if(PinVal == PIN_HIGH)
		{
			GPIOx[Port]->GPIOx_ODR |= (SET_BIT_VAL<<PinNum);	/*SET*/
		}
		else
		{
			Local_ErrorState=NOK;
		}
	}
	else
	{
		Local_ErrorState=NOK;
	}

	return Local_ErrorState;
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                            GPIO TOGGLE PIN VALUE
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @fn GPIO_u8TogglePinValue
 * @brief the function Toggle the GPIO pin value
 * @param[in] Port ,PinNum
 * @retval Local_u8ErrorState
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
ErrorState_t GPIO_u8TogglePinValue(Port_t	Port , Pin_t	PinNum )
{
	ErrorState_t Local_ErrorState = OK;

	if((Port<=PORTG) && (PinNum<=PIN15))
	{

		GPIOx[Port]->GPIOx_ODR ^=(TOGGLE_BIT_VAL<<PinNum);

	}
	else
	{
		Local_ErrorState = NOK;
	}

	return Local_ErrorState;
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                            GPIO READ PIN VALUE
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @fn GPIO_u8ReadPinValue
 * @brief the function Read the GPIO pin value
 * @param[in] Port ,PinNum
 * @param[out] PinVal
 * @retval Local_u8ErrorState
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
ErrorState_t GPIO_u8ReadPinValue(Port_t	Port , Pin_t	PinNum , PinVal_t*	PinVal)
{
	ErrorState_t Local_ErrorState=OK;

	if((Port<=PORTG) && (PinNum<=PIN15))
	{

		*PinVal = (((GPIOx[Port]->GPIOx_IDR)>>PinNum)&GET_BIT_VAL);

	}
	else
	{
		Local_ErrorState = NOK;
	}

	return Local_ErrorState;
}

/*
 *@fn		: GPIO_Write4Bits
 *@brief	: to set 4 Consecutive bits with the given value
 *@param	: Port				(ENUM: @Port_t)
 *@param	: PinNum			(ENUM: @Pin_t)
 *@param	: Copy_u8Val		(uint8_t)
 *@retval	: Local_ErrorState 	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t GPIO_Write4Bits(Port_t	Port , Pin_t	PinNum , uint8_t Copy_u8Val)
{
	ErrorState_t Local_ErrorState = OK;

	if((Port <= PORTG) && (Port >= PORTA)
			&& (PinNum <= PIN15) && (PinNum >= PIN1))
	{
		Copy_u8Val &= 0b00001111;
		GPIOx[Port]->GPIOx_ODR &=~ ( 0b1111 << PinNum);
		GPIOx[Port]->GPIOx_ODR |= ( Copy_u8Val << PinNum);
	}
	else
	{
		Local_ErrorState=NOK;
	}

	return Local_ErrorState;
}


/*
 *@fn		: GPIO_Write8Bits
 *@brief	: to set 8 Consecutive bits with the given value
 *@param	: Port				(ENUM: @Port_t)
 *@param	: PinNum			(ENUM: @Pin_t)
 *@param	: Copy_u8Val		(uint8_t)
 *@retval	: Local_ErrorState 	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t GPIO_Write8Bits(Port_t	Port , Pin_t PinNum , uint8_t Copy_u8Val)
{
	ErrorState_t Local_ErrorState=OK;

	if((Port <= PORTG) && (Port >= PORTA)
			&& (PinNum <= PIN15) && (PinNum >= PIN1))
	{
		GPIOx[Port]->GPIOx_ODR &=~ ( 0b11111111 << PinNum);
		GPIOx[Port]->GPIOx_ODR |= ( Copy_u8Val << PinNum);
	}
	else
	{
		Local_ErrorState=NOK;
	}

	return Local_ErrorState;
}

/*
 *@fn		: GPIO_Write16Bits
 *@brief	: to set 16 Consecutive bits with the given value
 *@param	: Port				(ENUM: @Port_t)
 *@param	: PortSection		(ENUM: @PortSection_t)
 *@param	: Copy_u16Val		(uint16_t)
 *@retval	: Local_ErrorState 	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t GPIO_Write16Bits(Port_t	Port , PortSection_t PortSection , uint16_t Copy_u16Val)
{
	ErrorState_t Local_ErrorState=OK;

	if((Port <= PORTG) && (Port >= PORTA))
	{
		if(PortSection == LOWER_SECTION)
		{
			GPIOx[Port]->GPIOx_ODR &=~  0xFFFF ;
			GPIOx[Port]->GPIOx_ODR |=  Copy_u16Val ;
		}
		else
		{
			GPIOx[Port]->GPIOx_ODR &=~ ( 0xFFFF << 8);
			GPIOx[Port]->GPIOx_ODR |= ( Copy_u16Val << 8);
		}
	}
	else
	{
		Local_ErrorState=NOK;
	}

	return Local_ErrorState;
}

/*
 *@fn		: GPIO_Write16Bits
 *@brief	: to set 32 bits (whole the port) with the given value
 *@param	: Port				(ENUM: @Port_t)
 *@param	: Copy_u32Val		(uint32_t)
 *@retval	: Local_ErrorState 	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t GPIO_WritePort(Port_t	Port , uint32_t Copy_u32Val)
{
	ErrorState_t Local_ErrorState=OK;

	if((Port <= PORTG) && (Port >= PORTA))
	{
		GPIOx[Port]->GPIOx_ODR &=~ ( 0xFFFFFFFF);
		GPIOx[Port]->GPIOx_ODR |= ( Copy_u32Val );
	}
	else
	{
		Local_ErrorState=NOK;
	}

	return Local_ErrorState;
}
