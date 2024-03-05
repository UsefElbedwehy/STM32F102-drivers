
#include <stdint.h>
#include "Stm32F103xx.h"
#include "SYSTICK_prv.h"
#include "SYSTICK_interface.h"

/*
@fn 	SYSTICK_DelayMs
@brief	 Timer in ms
@param[in] Copy_u32TimeMs
@retval void
 */
void SYSTICK_DelayMs(uint32_t Copy_u32TimeMs)
{
	uint32_t Local_ReloadVal = 0;

	Local_ReloadVal = ((Copy_u32TimeMs) / ( _10POW3 * ( 8.0 / 8000000UL)));

	/*CLK SRC*/
	SYSTICK->SYSTICK_CSR &=~ (SET_BIT<<CLKSOURCE);
	/*Set reload value*/
	SYSTICK->SYSTICK_RVR = Local_ReloadVal;

	/*Reset current SYSTICK counter value*/
	SYSTICK->SYSTICK_CVR = INITIAL_LOAD_VAL;

	/*Enable SYSTICK*/
	SYSTICK->SYSTICK_CSR |= (SET_BIT<<ENABLE);
	/*Busy waiting count flag*/
	while((((SYSTICK->SYSTICK_CSR)>>COUNTFLAG)&GET_NUM) != READY_FLAG);

	SYSTICK->SYSTICK_CSR &=~ (SET_BIT<<ENABLE);
}
/*
@fn 	SYSTICK_DelayUs
@brief	 Timer in Ms
@param[in] Copy_u32TimeUs
@retval void
 */
void SYSTICK_DelayUs(uint32_t Copy_u32TimeUs)
{
	/*CLK SRC*/
	SYSTICK->SYSTICK_CSR |= (SET_BIT << CLKSOURCE);
	/*RELOAD VALUE*/
	SYSTICK->SYSTICK_RVR = (Copy_u32TimeUs * (SYSTEM_FREQUANCY / _10POW6));
	/*Reset current SYSTICK counter value*/
	SYSTICK->SYSTICK_CVR = INITIAL_LOAD_VAL;
	/*Enable SYSTICK*/
	SYSTICK->SYSTICK_CSR |= (SET_BIT << ENABLE);
	/*Busy waiting count flag*/
	while((((SYSTICK->SYSTICK_CSR) >> COUNTFLAG) & GET_NUM) != READY_FLAG)
	{
		/*do nothing*/
	}
}
