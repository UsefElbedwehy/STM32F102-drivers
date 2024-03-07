#ifndef  SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

/*
 * @CSR_t
 * */
typedef enum{
	SYSTICK_CSR_ENABLE=0,
	SYSTICK_CSR_TICKINT,
	SYSTICK_CSR_CLKSOURCE,
	SYSTICK_CSR_COUNTFLAG=16
}SYSTICK_CSR_t;

/*
@fn 	SYSTICK_DelayMs
@brief	 Timer in milliseconds
@param[in] Copy_u32TimeMs
@retval void
 */
void SYSTICK_DelayMs(uint32_t Copy_u32TimeMs);

/*
@fn 	SYSTICK_DelayUs
@brief	 Timer in Microseconds
@param[in] Copy_u32TimeMs
@retval void
 */
void SYSTICK_DelayUs(uint32_t Copy_u32TimeUs);


#endif
