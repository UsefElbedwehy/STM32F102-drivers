#include <stdint.h>

#include "Stm32F103xx.h"
#include "ErrType.h"
#include "RCC_Private.h"
#include "RCC_Interface.h"


/*
 * @fn:		RCC_SetClkSts
 * @brief:	Set clock status (ON , OFF)
 * @param:	Copy_ClockType		(enum: @ClockSrc_t)
 * @param:	Copy_Status			(enum: @RCC_State_t)
 * @retval:	Local_ErrorState	(enum: @ErrorState_t)
 * */
ErrorState_t RCC_SetClkSts(ClockSrc_t Copy_ClockType,RCC_State_t Copy_Status)
{

	ErrorState_t Local_ErrorState=OK;
	uint16_t Local_TimeOut=0;

	/***Clock type***/
	if(Copy_ClockType == CLK_SRC_PLL)
	{
		/***Clock type is PLL***/
		switch(Copy_Status)
		{
		/*PLL ON*/
		case RCC_ON :	RCC->RCC_CR |= ( SET_MASK << CR_PLLON );
		/*Waiting the PLL ready flag*/
		while( ( ( ( RCC->RCC_CR >> CR_PLLRDY ) & GET_MASK ) != PLL_READY_FLAG ) && ( Local_TimeOut <= TIMEOUT ) )
		{
			/*counter(Time Out)*/
			Local_TimeOut++;
		}
		break;
		/*PLL OFF*/
		case RCC_OFF:	RCC->RCC_CR &=~ ( SET_MASK << CR_PLLON );	break;

		default : Local_ErrorState = NOK;							break;
		}
	}
	else if(Copy_ClockType == CLK_SRC_HSE)
	{
		/***Clock type is HSE***/
		switch(Copy_Status)
		{
		/*HSE ON*/
		case RCC_ON :		RCC->RCC_CR |= ( SET_MASK << CR_HSEON );
		/*Waiting the HSE ready flag*/
		while( ( ( ( RCC->RCC_CR >> CR_HSERDY ) & GET_MASK ) != HSE_READY_FLAG ) && ( Local_TimeOut <= TIMEOUT ) )
		{
			/*counter(Time Out)*/
			Local_TimeOut++;
		}
		break;
		/*HSE OFF*/
		case RCC_OFF:	RCC->RCC_CR &=~ ( SET_MASK << CR_HSEON );	break;

		default : Local_ErrorState = NOK;							break;
		}
	}
	else if(Copy_ClockType == CLK_SRC_HSI)
	{
		/***Clock type is HSI***/
		switch(Copy_Status)
		{
		/*HSI ON*/
		case RCC_ON :		RCC->RCC_CR |= ( SET_MASK << CR_HSION );
		/*Waiting the HSI ready flag*/
		while( ( ( ( RCC->RCC_CR >> CR_HSIRDY ) & GET_MASK ) != HSI_READY_FLAG ) && ( Local_TimeOut <= TIMEOUT ) )
		{
			/*counter(Time Out)*/
			Local_TimeOut++;
		}
		break;
		/*HSI OFF*/
		case RCC_OFF:	RCC->RCC_CR &=~ ( SET_MASK << CR_HSION );	break;

		default : Local_ErrorState = NOK;							break;
		}
	}
	else
	{
		Local_ErrorState = NOK;
	}
	return Local_ErrorState;

}

/*
 * @fn:		RCC_SetSysClk
 * @brief:	Set system clock (PLL, HSE, HSI)
 * @param:	Copy_ClockType		(enum: @ClockSrc_t)
 * @retval:	Local_ErrorState	(enum: @ErrorState_t)
 * */
ErrorState_t RCC_SetSysClk(ClockSrc_t Copy_ClockType)
{
	ErrorState_t Local_ErrorState = OK;
	switch(Copy_ClockType)
	{
	/* PLL selected as system clock*/
	case CLK_SRC_PLL:

		RCC->RCC_CFGR |=  ( SET_MASK << CFGR_SW1 );
		RCC->RCC_CFGR &=~ ( SET_MASK << CFGR_SW0 );

		break;
		/* HSE selected as system clock*/
	case CLK_SRC_HSE:

		RCC->RCC_CFGR &=~ ( SET_MASK << CFGR_SW1 );
		RCC->RCC_CFGR |=  ( SET_MASK << CFGR_SW0 );

		break;
		/*HSI selected as system clock*/
	case CLK_SRC_HSI:

		RCC->RCC_CFGR &=~ ( SET_MASK << CFGR_SW1 );
		RCC->RCC_CFGR &=~ ( SET_MASK << CFGR_SW0 );

		break;

	default: Local_ErrorState = NOK;	break;
	}

	return Local_ErrorState;
}

/*
 * @fn:		RCC_HSEConfig
 * @brief:	Set HSE clock configurations
 * @param:	Copy_HSEConfig		(enum: @HSEConfig_t)
 * @retval:	Local_ErrorState	(enum: @ErrorState_t)
 * */
ErrorState_t RCC_HSEConfig(HSEConfig_t Copy_HSEConfig)
{
	ErrorState_t Local_ErrorState = OK;
	if( (Copy_HSEConfig <= HALF_HSE) && (Copy_HSEConfig >= NORMAL_HSE) )
	{
		switch(Copy_HSEConfig)
		{
		/*HSE clock not divided*/
		case NORMAL_HSE:	RCC->RCC_CFGR &=~ ( SET_MASK << CFGR_PLLXTPRE );	break;
		/*HSE clock divided by 2*/
		case HALF_HSE:		RCC->RCC_CFGR |=  ( SET_MASK << CFGR_PLLXTPRE );	break;

		default:Local_ErrorState = NOK;						break;
		}
	}
	else
	{
		Local_ErrorState = NOK;
	}

	return Local_ErrorState;
}

/*
 * @fn:		RCC_PLLConfig
 * @brief:	Set PLL clock configurations
 * @param:	Copy_PLLMux			(enum: @PllMultiFac_t)
 * @param:	Copy_PLLSrc			(enum: @PLLSrcConfig_t)
 * @retval:	Local_ErrorState	(enum: @ErrorState_t)
 * */
ErrorState_t RCC_PLLConfig(PllMultiFac_t Copy_PLLMux,PLLSrcConfig_t Copy_PLLSrc)
{
	ErrorState_t Local_ErrorState = NOK;
	/*PLL source*/
	switch(Copy_PLLSrc)
	{
	/*HSE oscillator clock selected as PLL input clock*/
	case PLL_SRC_HSE:		RCC->RCC_CFGR |=  ( SET_MASK << CFGR_PLLSRC );		break;
	/*HSI oscillator clock / 2 selected as PLL input clock*/
	case PLL_SRC_HALF_HSI:	RCC->RCC_CFGR &=~ ( SET_MASK << CFGR_PLLSRC );		break;

	default: Local_ErrorState = NOK;							break;
	}

	/*PLL multiplication factor*/
	RCC->RCC_CFGR |= ( Copy_PLLMux << CFGR_PLLMUL0);

	return Local_ErrorState;
}

/*
 * @fn:		RCC_AHBEnableClock
 * @brief:	Enable AHB clock for peripheral
 * @param:	Copy_Peripheral		(ENUM: @AHBPeriperals_t)
 * @retval:	void
 * */
void RCC_AHBEnableClock(AHBPeriperals_t Copy_Peripheral )
{
	RCC->RCC_APB1ENR |= ( SET_MASK << Copy_Peripheral );
}

/*
 * @fn:		RCC_AHBDisableClock
 * @brief:	Disable AHB clock for peripheral
 * @param:	Copy_Peripheral		(ENUM: @AHBPeriperals_t)
 * @retval:	void
 * */
void RCC_AHBDisableClock(AHBPeriperals_t Copy_Peripheral )
{
	RCC->RCC_APB1ENR &=~ ( SET_MASK << Copy_Peripheral );
}

/*
 * @fn:		RCC_APB1EnableClock
 * @brief:	Enable APB1 clock for peripheral
 * @param:	Copy_Peripheral		(ENUM: @APB1Peripherals_t)
 * @retval:	void
 * */
void RCC_APB1EnableClock(APB1Peripherals_t Copy_Peripheral)
{
	RCC->RCC_APB1ENR |= ( SET_MASK << Copy_Peripheral );
}

/*
 * @fn:		RCC_APB1DisableClock
 * @brief:	Disable APB1 clock for peripheral
 * @param:	Copy_Peripheral		(ENUM: @APB1Peripherals_t)
 * @retval:	void
 * */
void RCC_APB1DisableClock(APB1Peripherals_t Copy_Peripheral)
{
	RCC->RCC_APB1ENR &=~ ( SET_MASK << Copy_Peripheral );
}

/*
 * @fn:		RCC_APB2EnableClock
 * @brief:	Enable APB2 clock for peripheral
 * @param:	Copy_Peripheral		(ENUM: @APB2Peripherals_t)
 * @retval:	void
 * */
void RCC_APB2EnableClock(APB2Peripherals_t Copy_Peripheral)
{
	RCC->RCC_APB2ENR |= ( SET_MASK << Copy_Peripheral );
}

/*
 * @fn:		RCC_APB2DisableClock
 * @brief:	Disable APB2 clock for peripheral
 * @param:	Copy_Peripheral		(ENUM: @APB2Peripherals_t)
 * @retval:	void
 * */
void RCC_APB2DisableClock(APB2Peripherals_t Copy_Peripheral)
{
	RCC->RCC_APB2ENR &=~ ( SET_MASK << Copy_Peripheral );
}
