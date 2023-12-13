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
#include "GPIO_interface.h"
#include "GPIO_prv.h"

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
uint8_t GPIO_u8PinInit(const PinConfig_t* Copy_PinConfig)
{
	uint8_t Local_u8ErrorState=OK;
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
			Local_u8ErrorState=NOK;
		}

	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
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
uint8_t GPIO_u8SetPinValue(Port_t	Port , Pin_t	PinNum , PinVal_t PinVal)
{
	uint8_t Local_u8ErrorState=OK;
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
			Local_u8ErrorState=NOK;
		}
	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
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
uint8_t GPIO_u8TogglePinValue(Port_t	Port , Pin_t	PinNum )
{
	uint8_t Local_u8ErrorState=OK;

	if((Port<=PORTG) && (PinNum<=PIN15))
	{

		GPIOx[Port]->GPIOx_ODR ^=(TOGGLE_BIT_VAL<<PinNum);

	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
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
uint8_t GPIO_u8ReadPinValue(Port_t	Port , Pin_t	PinNum , PinVal_t*	PinVal)
{
	uint8_t Local_u8ErrorState=OK;

		if((Port<=PORTG) && (PinNum<=PIN15))
		{

			*PinVal = (((GPIOx[Port]->GPIOx_IDR)>>PinNum)&GET_BIT_VAL);

		}
		else
		{
			Local_u8ErrorState=NOK;
		}

		return Local_u8ErrorState;
}

