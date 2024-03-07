
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

	Local_ReloadVal = (Copy_u32TimeMs) * ( (SYSTEM_FREQUANCY / EXTERNAL_CLK_PRESCALLER) / _10POW3 );

	/*CLK SRC -> AHB/8 */
	SYSTICK->SYSTICK_CSR &=~ (SET_MASK << SYSTICK_CSR_CLKSOURCE);
	/*Set reload value*/
	SYSTICK->SYSTICK_RVR = Local_ReloadVal;

	/*Reset current SYSTICK counter value*/
	SYSTICK->SYSTICK_CVR = INITIAL_LOAD_VAL;

	/* Disable Exception For Busy Waiting */
	( SYSTICK->SYSTICK_CSR ) &=~ ( SET_MASK << SYSTICK_CSR_TICKINT )  ;

	/*Enable SYSTICK*/
	SYSTICK->SYSTICK_CSR |= (SET_MASK << SYSTICK_CSR_ENABLE);
	/*Busy waiting count flag*/
	while(((SYSTICK->SYSTICK_CSR >> SYSTICK_CSR_COUNTFLAG) & GET_MASK) == 0);
	/*Disable SYSTICK*/
	SYSTICK->SYSTICK_CSR &=~ (SET_MASK << SYSTICK_CSR_ENABLE);
}

/*
@fn 	SYSTICK_DelayUs
@brief	 Timer in Ms
@param[in] Copy_u32TimeUs
@retval void
 */
void SYSTICK_DelayUs(uint32_t Copy_u32TimeUs)
{
	uint32_t Local_ReloadVal = 0;
	/*CLK SRC -> AHB/8 */
	SYSTICK->SYSTICK_CSR |= (SET_MASK << SYSTICK_CSR_CLKSOURCE);
	/*RELOAD VALUE*/
	Local_ReloadVal = (Copy_u32TimeUs) * ( (SYSTEM_FREQUANCY / EXTERNAL_CLK_PRESCALLER) / _10POW6 );
	SYSTICK->SYSTICK_RVR = Local_ReloadVal;

	/*Reset current SYSTICK counter value*/
	SYSTICK->SYSTICK_CVR = INITIAL_LOAD_VAL;

	/* Disable Exception For Busy Waiting */
	( SYSTICK->SYSTICK_CSR ) &=~ ( SET_MASK << SYSTICK_CSR_TICKINT )  ;

	/*Enable SYSTICK*/
	SYSTICK->SYSTICK_CSR |= (SET_MASK << SYSTICK_CSR_ENABLE);
	/*Busy waiting count flag*/
	while( ( ( SYSTICK->SYSTICK_CSR >> SYSTICK_CSR_COUNTFLAG) & GET_MASK) == 0 );
	/*Disable SYSTICK*/
	SYSTICK->SYSTICK_CSR &=~ (SET_MASK << SYSTICK_CSR_ENABLE);
}
