#include <stdint.h>
#include "RCC_Interface.h"
#include "RCC_Private.h"



/* choose the clock source and its state
 * Copy_uint16ClkType: 1-PLL 2-HSE 3-HSI
 * Copy_uint16Status: 1-ON 2-OFF
 * */
uint16_t RCC_VoidSetClkSts(ClockSrc_t Copy_uint16ClkType,State_t Copy_uint16Status)
{
	uint16_t Local_TimeOut=0;
	uint16_t Local_ErrorState=0;
	if(Copy_uint16ClkType==PLL)
	{
		switch(Copy_uint16Status)
		{
		case ON :
			/*PLL ON*/
			RCC->RCC_CR |= (1<<24);

			/*Waiting the PLL ready flag*/
			while((((RCC->RCC_CR>>25)&0x01)!=1) && (Local_TimeOut<TIMEOUT))
			{
				/*counter(Time Out)*/
				Local_TimeOut++;
			};
			break;
		case OFF:
			/*PLL OFF*/
			RCC->RCC_CR&=~(1<<24);
			break;
		default : Local_ErrorState=1;
		break;
		}
	}
	else if(Copy_uint16ClkType==HSE)
	{
		switch(Copy_uint16Status)
		{
		case ON :
			/*HSE ON*/
			RCC->RCC_CR |= (1<<16);
			/*Waiting the HSE ready flag*/
			while((((RCC->RCC_CR>>17)&0x01)!=1) && (Local_TimeOut<TIMEOUT))
			{
				/*counter(Time Out)*/
				Local_TimeOut++;
			};
			break;
		case OFF:
			/*HSE OFF*/
			RCC->RCC_CR&=~(1<<16);
			break;
		default : Local_ErrorState=1;
		break;
		}
	}
	else if(Copy_uint16ClkType==HSI)
	{
		switch(Copy_uint16Status)
		{
		case ON :
			/*HSI ON*/
			RCC->RCC_CR |= (1<<0);
			/*Waiting the HSI ready flag*/
			while((((RCC->RCC_CR>>1)&0x01)!=1) && (Local_TimeOut<TIMEOUT))
			{
				/*counter(Time Out)*/
				Local_TimeOut++;
			};
			break;
		case OFF:
			/*HSI OFF*/
			RCC->RCC_CR&=~(1<<0);
			break;
		default : Local_ErrorState=1;
		break;
		}
	}else{
		Local_ErrorState=1;
	}
	return Local_ErrorState;

}
/* choose the system clock source
 * Copy_uint16ClkType: 1-PLL 2-HSE 3-HSI
 * */
uint16_t RCC_VoidSetSysClk(ClockSrc_t Copy_uint16ClkType)
{
	uint16_t Local_ErrorState=0;
	switch(Copy_uint16ClkType)
	{
	case PLL: /*10*/
		RCC->RCC_CFGR |= (1<<1);
		RCC->RCC_CFGR &=~ (1<<0);
		break;
	case HSE: /*01*/
		RCC->RCC_CFGR &=~ (1<<1);
		RCC->RCC_CFGR |= (1<<0);
		break;
	case HSI: /*00*/
		RCC->RCC_CFGR&=~(1<<1);
		RCC->RCC_CFGR&=~(1<<0);
		break;
	default: Local_ErrorState=1;
	break;
	}

	return Local_ErrorState;
}
/*Copy_uint16Config : 1-HSE
 *                    2-HALF_HSE    */
uint16_t RCC_VoidHSEConfig(HSEConfig_t Copy_uint16Config)
{
	uint16_t Local_ErrorState=0;
	switch(Copy_uint16Config)
	{
	case NORMAL_HSE:	/*HSE clock not divided*/
		RCC->RCC_CFGR|=(1<<17);
		break;
	case HALF_HSE:/*HSE clock divided by 2*/
		RCC->RCC_CFGR|=(1<<17);
		break;
	default:Local_ErrorState=1;
	break;
	}
	return Local_ErrorState;
}
/**Copy_uint16PLLMux options:
 * PLL_M1 - PLL_M2 - PLL_M3 - PLL_M4 - PLL_M5 - PLL_M6 - PLL_M7 - PLL_M8
 * PLL_M9 - PLL_M10 - PLL_M11 - PLL_M12 - PLL_M13 - PLL_M14 - PLL_M15 - PLL_M16
 **Copy_uint16PLLSrc options: 1-HSI/2
                              2-HSE   * * */

uint16_t RCC_VoidPLLConfig(PllMultiFac_t Copy_uint16PLLMux,PLLSrcConfig_t Copy_uint16PLLSrc)
{
	uint16_t Local_ErrorState=0;
	/*PLL source*/
	switch(Copy_uint16PLLSrc)
	{
	case SRC_HSE:	/*HSE oscillator clock selected as PLL input clock*/
		RCC->RCC_CFGR|=(1<<17);
		break;
	case HALF_HSI:	/*HSI oscillator clock / 2 selected as PLL input clock*/
		RCC->RCC_CFGR&=~(1<<16);
		break;
	default: Local_ErrorState=1;
	break;
	}
	/*PLL multiplication factor*/
	RCC->RCC_CFGR |=(Copy_uint16PLLMux<<18);

	return Local_ErrorState;
}
/*Copy_uint16Peripheral option:
 * DMA1,	DMA2,	SRAM,	FLITF,
	CRC,	FSMC,	SDIO,*/
void RCC_AHBEnableClock(AHBPeriperals_t Copy_uint16Peripheral)
{
	RCC->RCC_APB1ENR|=(1<<Copy_uint16Peripheral);
}
void RCC_AHBDisableClock(AHBPeriperals_t Copy_uint16Peripheral)
{
	RCC->RCC_APB1ENR&=~(1<<Copy_uint16Peripheral);
}
/*Copy_uint16Peripheral option:
 *  TIM2,     TIM3,	    TIM4,	  TIM5,
 *  TIM6,	  TIM7, 	TIM12,	  TIM13,
	TIM14,	  WWDG,	    SPI2,     SPI3,
	USART2,	  USART3,	UART4,	  UART5,
	I2C1,	  I2C2,	    USB,	  BKP,
	PWR,	  DAC 		* * * * * * * * */
void RCC_APB1EnableClock(APB1Peripherals_t Copy_uint16Peripheral)
{
	RCC->RCC_APB1ENR|=(1<<Copy_uint16Peripheral);
}
void RCC_APB1DisableClock(APB1Peripherals_t Copy_uint16Peripheral)
{
	RCC->RCC_APB1ENR&=~(1<<Copy_uint16Peripheral);
}
/*Copy_uint16Peripheral option:
 * AFIO,	IOPA,	IOPB,	IOPC,
	IOPD,	IOPE,	IOPF,	IOPG,
	ADC1,	ADC2,	TIM1,	SPI1,
	TIM8,	USART,	ADC3,	TIM9,
	TIM10,	TIM11*/
void RCC_APB2EnableClock(APB2Peripherals_t Copy_uint16Peripheral)
{
	RCC->RCC_APB2ENR|=(1<<Copy_uint16Peripheral);
}
void RCC_APB2DisableClock(APB2Peripherals_t Copy_uint16Peripheral)
{
	RCC->RCC_APB2ENR&=~(1<<Copy_uint16Peripheral);
}
