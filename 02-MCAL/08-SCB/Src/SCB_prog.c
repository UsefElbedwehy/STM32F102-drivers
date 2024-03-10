#include <stdint.h>

#include "ErrType.h"
#include "Stm32F103xx.h"

#include "SCB_prv.h"
#include "SCB_interface.h"


/*
 * @fn    : SCB_SetPriorityGroup
 * @brief : splits the PRI_n fields in the Interrupt Priority Registers
 * 										into separate group priority and subpriority fields.
 * @param : PriorityGroup    (ENUM: @SCB_PriorityGroup_t)
 * @retval:  Local_ErrorState (ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SCB_SetPriorityGroup(SCB_PriorityGroup_t PriorityGroup)
{
	ErrorState_t Local_ErrorState = SCB_OK;

	if((PriorityGroup >= _16G_0SG) && (PriorityGroup <= _0G_16SG))
	{
		SCB->SCB_AIRCR &= (PriorityGroup << AIRCR_PRIGROUP);
		SCB->SCB_AIRCR = (PriorityGroup << AIRCR_PRIGROUP) | (VECTORKEY_MASK << AIRCR_VECTKEY);
	}
	else
	{
		Local_ErrorState = SCB_NOK;
	}

	return Local_ErrorState;
}

/*
 * @fn    : SCB_EnableMemManageFault
 * @brief : enables memory manage fault exception
 * @param : void
 * @retval:  void
 *
 * */
void SCB_EnableMemManageFault(void)
{

	SCB->SCB_SHCRS |= ( SCB_SET_MASK << SHCSR_MEMFAULTENA);

}
/*
 * @fn    : SCB_DisableMemManageFault
 * @brief : disables memory manage fault exception
 * @param : void
 * @retval:  void
 *
 * */
void SCB_DisableMemManageFault(void)
{

	SCB->SCB_SHCRS &=~ ( SCB_SET_MASK << SHCSR_MEMFAULTENA);

}
/*
 * @fn    : SCB_EnableBusFault
 * @brief : enables memory bus exception
 * @param : void
 * @retval:  void
 *
 * */
void SCB_EnableBusFault(void)
{

	SCB->SCB_SHCRS |= ( SCB_SET_MASK << SHCSR_BUSFAULTENA);

}
/*
 * @fn    : SCB_DisableBusFault
 * @brief : disables bus fault exception
 * @param : void
 * @retval:  void
 *
 * */
void SCB_DisableBusFault(void)
{

	SCB->SCB_SHCRS &=~ ( SCB_SET_MASK << SHCSR_BUSFAULTENA);

}
/*
 * @fn    : SCB_EnableUsageFault
 * @brief : enables Usage fault exception
 * @param : void
 * @retval:  void
 *
 * */
void SCB_EnableUsageFault(void)
{

	SCB->SCB_SHCRS |= ( SCB_SET_MASK << SHCSR_USGFAULTENA);

}
/*
 * @fn    : SCB_DisableUsageFault
 * @brief : disables usage fault exception
 * @param : void
 * @retval:  void
 *
 * */
void SCB_DisableUsageFault(void)
{

	SCB->SCB_SHCRS &=~ ( SCB_SET_MASK << SHCSR_USGFAULTENA);

}




/*
 * @fn    : SCB_SetSysHandlerState
 * @brief : enables the system handlers
 * @param : SCB_SHCSR_Bit    (ENUM: @SCB_SHCSR_t)
 * @retval:  Local_ErrorState (ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SCB_SetSysHandlerState(SCB_SHCSR_t SCB_SHCSR_Bit)
{

	ErrorState_t Local_ErrorState = SCB_OK;

		if(( SCB_SHCSR_Bit >= SHCSR_MEMFAULTACT ) && (SCB_SHCSR_Bit <= SHCSR_USGFAULTENA))
		{
			SCB->SCB_SHCRS |= ( SCB_SET_MASK << SCB_SHCSR_Bit);
		}
		else
		{
			Local_ErrorState = SCB_NOK;
		}

		return Local_ErrorState;

}

/*
 * @fn    : SCB_ClearSysHandlerState
 * @brief : disables the system handlers
 * @param : SCB_SHCSR_Bit    (ENUM: @SCB_SHCSR_t)
 * @retval:  Local_ErrorState (ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SCB_ClearSysHandlerState(SCB_SHCSR_t SCB_SHCSR_Bit)
{

	ErrorState_t Local_ErrorState = SCB_OK;

		if(( SCB_SHCSR_Bit >= SHCSR_MEMFAULTACT ) && (SCB_SHCSR_Bit <= SHCSR_USGFAULTENA))
		{
			SCB->SCB_SHCRS &=~ ( SCB_SET_MASK << SCB_SHCSR_Bit);
		}
		else
		{
			Local_ErrorState = SCB_NOK;
		}

		return Local_ErrorState;

}

/*
 * @fn    : SCB_EnableDivByZero
 * @brief : enables division by zero usage fault exception
 * @param : SCB_SHCSR_Bit    (ENUM: @SCB_UFSR_t)
 * @retval:  Local_ErrorState (ENUM: @ErrorState_t)
 *
 * */
void SCB_EnableDivByZero(SCB_UFSR_t SCB_UFSR_Bit)
{

	SCB->SCB_UFSR |= (SCB_SET_MASK << UFSR_DIVBYZERO);

}

/*
 * @fn    : SCB_DisableDivByZero
 * @brief : disables division by zero usage fault exception
 * @param : SCB_SHCSR_Bit    (ENUM: @SCB_UFSR_t)
 * @retval:  Local_ErrorState (ENUM: @ErrorState_t)
 *
 * */
void SCB_DisableDivByZero(SCB_UFSR_t SCB_UFSR_Bit)
{

	SCB->SCB_UFSR &=~ (SCB_SET_MASK << UFSR_DIVBYZERO);

}
