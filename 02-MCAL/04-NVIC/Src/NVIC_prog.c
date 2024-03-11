#include <stdint.h>

#include "Stm32F103xx.h"
#include "ErrType.h"

#include "NVIC_prv.h"
#include "NVIC_interface.h"

/*
 * @fn	  :	NVIC_EnableIRQ
 * @brief : Enables an interrupt or exception.
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_EnableIRQ(NVIC_IRQn_t IRQn)
{
	ErrorState_t Local_ErrorState = NVIC_OK;
	uint8_t Local_RegNumber = (IRQn / 32);
	uint8_t Local_PinNumber = (IRQn % 32);

	if((IRQn >= NVIC_IRQ_WWDG) && (IRQn <= NVIC_IRQ_OTG_FS))
	{

		NVIC->NVIC_ISER[Local_RegNumber] |= (NVIC_SET_MASK << Local_PinNumber);
	}
	else
	{
		Local_ErrorState = NVIC_NOK;
	}
	return Local_ErrorState;
}

/*
 * @fn	  :	NVIC_DisableIRQ
 * @brief : Disables an interrupt or exception.
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_DisableIRQ(NVIC_IRQn_t IRQn)
{
	ErrorState_t Local_ErrorState = NVIC_OK;
	uint8_t Local_RegNumber = (IRQn / 32);
	uint8_t Local_PinNumber = (IRQn % 32);

	if((IRQn >= NVIC_IRQ_WWDG) && (IRQn <= NVIC_IRQ_OTG_FS))
	{

		NVIC->NVIC_ICER[Local_RegNumber] |= (NVIC_SET_MASK << Local_PinNumber);
	}
	else
	{
		Local_ErrorState = NVIC_NOK;
	}
	return Local_ErrorState;
}

/*
 * @fn	  :	NVIC_SetPendingIRQ
 * @brief : Sets the pending status of interrupt or exception to 1
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_SetPendingIRQ(NVIC_IRQn_t IRQn)
{
	ErrorState_t Local_ErrorState = NVIC_OK;
	uint8_t Local_RegNumber = (IRQn / 32);
	uint8_t Local_PinNumber = (IRQn % 32);

	if((IRQn >= NVIC_IRQ_WWDG) && (IRQn <= NVIC_IRQ_OTG_FS))
	{

		NVIC->NVIC_ISPR[Local_RegNumber] |= (NVIC_SET_MASK << Local_PinNumber);
	}
	else
	{
		Local_ErrorState = NVIC_NOK;
	}
	return Local_ErrorState;
}

/*
 * @fn	  :	NVIC_ClearPendingIRQ
 * @brief : Clears the pending status of interrupt or exception to 0.
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_ClearPendingIRQ(NVIC_IRQn_t IRQn)
{
	ErrorState_t Local_ErrorState = NVIC_OK;
	uint8_t Local_RegNumber = (IRQn / 32);
	uint8_t Local_PinNumber = (IRQn % 32);

	if((IRQn >= NVIC_IRQ_WWDG) && (IRQn <= NVIC_IRQ_OTG_FS))
	{

		NVIC->NVIC_ICPR[Local_RegNumber] |= (NVIC_SET_MASK << Local_PinNumber);
	}
	else
	{
		Local_ErrorState = NVIC_NOK;
	}
	return Local_ErrorState;
}

/*
 * @fn	  :	NVIC_GetPendingIRQ
 * @brief : Reads the pending status of interrupt or exception.
 * 			This function returns non-zero value
 * 			if the pending status is set to 1.
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @param : Copy_u8PendingVal	pointer to uint8_t
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_GetPendingIRQ(NVIC_IRQn_t IRQn , uint8_t* Copy_u8PendingVal)
{
	ErrorState_t Local_ErrorState = NVIC_OK;
	uint8_t Local_RegNumber = (IRQn / 32);
	uint8_t Local_PinNumber = (IRQn % 32);

	if((IRQn >= NVIC_IRQ_WWDG) && (IRQn <= NVIC_IRQ_OTG_FS))
	{
		*Copy_u8PendingVal = (( NVIC->NVIC_ISPR[Local_RegNumber] >> Local_PinNumber) & NVIC_GET_MASK );
	}
	else
	{
		Local_ErrorState = NVIC_NOK;
	}
	return Local_ErrorState;
}

/*
 * @fn	  :	NVIC_SetIRQnPriority
 * @brief : Sets the priority of an interrupt or exception
 * 			with configurable priority level to 1.
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @param : priority			(ENUM: @NVIC_IRQn_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_SetIRQnPriority(NVIC_IRQn_t IRQn, uint32_t priority)
{
	ErrorState_t Local_ErrorState = NVIC_OK;

	if((IRQn >= NVIC_IRQ_WWDG) && (IRQn <= NVIC_IRQ_OTG_FS))
	{
		NVIC->NVIC_IPR[IRQn] &=~ (0b1111 << 4);
		NVIC->NVIC_IPR[IRQn] |= (priority << 4);
	}
	else
	{
		Local_ErrorState = NVIC_NOK;
	}
	return Local_ErrorState;
}

/*
 * @fn	  :	NVIC_GetPriority
 * @brief : Reads the priority of an interrupt or exception with
			configurable priority level. This function return the
			current priority level.
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @param : Copy_u8PriorityVal	uint8_t
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_GetPriority(NVIC_IRQn_t IRQn ,uint8_t* Copy_u8PriorityVal)
{
	ErrorState_t Local_ErrorState = NVIC_OK;

	if((IRQn >= NVIC_IRQ_WWDG) && (IRQn <= NVIC_IRQ_OTG_FS))
	{
		*Copy_u8PriorityVal = (NVIC->NVIC_IPR[IRQn] >> 4);
	}
	else
	{
		Local_ErrorState = NVIC_NOK;
	}

	return Local_ErrorState;
}

/*
 * @fn	  :	NVIC_GetActiveFlag
 * @brief : Reads the Active flag of an interrupt or exception with
			configurable priority level. This function return the
			active flag state.
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @param : Copy_pu8PendingVal	pointer to uint8_t
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_GetActiveFlag(NVIC_IRQn_t IRQn ,uint8_t* Copy_pu8PendingVal)
{
	ErrorState_t Local_ErrorState = NVIC_OK;
	uint8_t Local_RegNumber = (IRQn / 32);
	uint8_t Local_PinNumber = (IRQn % 32);

	if((IRQn >= NVIC_IRQ_WWDG) && (IRQn <= NVIC_IRQ_OTG_FS))
	{
		*Copy_pu8PendingVal = (( NVIC->NVIC_IABR[Local_RegNumber] >> Local_PinNumber) & NVIC_GET_MASK );
	}
	else
	{
		Local_ErrorState = NVIC_NOK;
	}

	return Local_ErrorState;
}

