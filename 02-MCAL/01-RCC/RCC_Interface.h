#ifndef   RCC_INTERFACE_H_
#define   RCC_INTERFACE_H_

/*@ClockSrc_t*/
typedef enum{

	CLK_SRC_PLL=0,
	CLK_SRC_HSE,
	CLK_SRC_HSI

}ClockSrc_t;

/*@HSEConfig_t*/
typedef enum{

	NORMAL_HSE=0,
	HALF_HSE

}HSEConfig_t;

/*@PLLSrcConfig_t*/
typedef enum{

	PLL_SRC_HALF_HSI=0,
	PLL_SRC_HSE

}PLLSrcConfig_t;

/*@State_t*/
typedef enum{

	RCC_ON=0,
	RCC_OFF

}RCC_State_t;

/* PLL multiplication factor
 * ready to be masked
 * maskable
 * @PllMultiFac_t */
typedef enum{

	   PLL_M1=0,
	   PLL_M2,
	   PLL_M3,
	   PLL_M4,
	   PLL_M5,
	   PLL_M6,
	   PLL_M7,
	   PLL_M8,
	   PLL_M9,
	   PLL_M10,
	   PLL_M11,
	   PLL_M12,
	   PLL_M13,
	   PLL_M14,
	   PLL_M15,
	   PLL_M16

}PllMultiFac_t;

/*@AHBPeriperals_t*/
typedef enum{

	AHB_DMA1,
	AHB_DMA2,
	AHB_SRAM,
	AHB_FLITF=4,
	AHB_CRC=6,
	AHB_FSMC=8,
	AHB_SDIO=10

}AHBPeriperals_t;

/*@APB1Peripherals_t*/
typedef enum{

	APB1_TIM2,
	APB1_TIM3,
	APB1_TIM4,
	APB1_TIM5,
	APB1_TIM6,
	APB1_TIM7,
	APB1_TIM12,
	APB1_TIM13,
	APB1_TIM14,
	APB1_WWDG=11,
	APB1_SPI2=14,
	APB1_SPI3,
	APB1_USART2=17,
	APB1_USART3,
	APB1_UART4,
	APB1_UART5,
	APB1_I2C1,
	APB1_I2C2,
	APB1_USB,
	APB1_BKP=27,
	APB1_PWR,
	APB1_DAC

}APB1Peripherals_t;

/*@APB2Peripherals_t*/
typedef enum{

	APB2_AFIO,
	APB2_IOPA=2,
	APB2_IOPB,
	APB2_IOPC,
	APB2_IOPD,
	APB2_IOPE,
	APB2_IOPF,
	APB2_IOPG,
	APB2_ADC1,
	APB2_ADC2,
	APB2_TIM1,
	APB2_SPI1,
	APB2_TIM8,
	APB2_USART,
	APB2_ADC3,
	APB2_TIM9=19,
	APB2_TIM10,
	APB2_TIM11

}APB2Peripherals_t;

/*
 * Clock control register (RCC_CR)
 * @RCC_CR_t
 * */
typedef enum{

	CR_HSION,
	CR_HSIRDY,
	CR_HSITRIM0=3,
	CR_HSICAL=8,
	CR_HSEON=16,
	CR_HSERDY,
	CR_HSEBYP,
	CR_CSSON,
	CR_PLLON=24,
	CR_PLLRDY=25

}RCC_CR_t;

/*
 * Clock configuration register (RCC_CFGR)
 * @RCC_CFGR_t
 * */
typedef enum{

	CFGR_SW0=0,
	CFGR_SW1=1,
	CFGR_SWS0=2,
	CFGR_HPRE0=4,
	CFGR_PPRE1=8,
	CFGR_PPRE2=11,
	CFGR_ADCPRE=14,
	CFGR_PLLSRC=16,
	CFGR_PLLXTPRE,
	CFGR_PLLMUL0,
	CFGR_USBPRE=22,
	CFGR_MCO0=24

}RCC_CFGR_t;


/*
 * @fn:		RCC_SetClkSts
 * @brief:	Set clock status (ON , OFF)
 * @param:	Copy_ClockType		(enum: @ClockSrc_t)
 * @param:	Copy_Status			(enum: @RCC_State_t)
 * @retval:	Local_ErrorState	(enum: @ErrorState_t)
 * */
ErrorState_t RCC_SetClkSts(ClockSrc_t Copy_ClockType,RCC_State_t Copy_Status);

ErrorState_t RCC_SetSysClk(ClockSrc_t Copy_ClockType);

ErrorState_t RCC_HSEConfig(HSEConfig_t Copy_HSEConfig);

ErrorState_t RCC_PLLConfig(PllMultiFac_t Copy_PLLMux,PLLSrcConfig_t Copy_PLLSrc);

/*
 * @fn:		RCC_AHBEnableClock
 * @brief:	Enable AHB clock for peripheral
 * @param:	Copy_Peripheral		(ENUM: @AHBPeriperals_t)
 * @retval:	void
 * */
void RCC_AHBEnableClock(AHBPeriperals_t Copy_Peripheral );

/*
 * @fn:		RCC_AHBDisableClock
 * @brief:	Disable AHB clock for peripheral
 * @param:	Copy_Peripheral		(ENUM: @AHBPeriperals_t)
 * @retval:	void
 * */
void RCC_AHBDisableClock(AHBPeriperals_t Copy_Peripheral );

/*
 * @fn:		RCC_APB1EnableClock
 * @brief:	Enable APB1 clock for peripheral
 * @param:	Copy_Peripheral		(ENUM: @APB1Peripherals_t)
 * @retval:	void
 * */
void RCC_APB1EnableClock(APB1Peripherals_t Copy_Peripheral);

/*
 * @fn:		RCC_APB1DisableClock
 * @brief:	Disable APB1 clock for peripheral
 * @param:	Copy_Peripheral		(ENUM: @APB1Peripherals_t)
 * @retval:	void
 * */
void RCC_APB1DisableClock(APB1Peripherals_t Copy_Peripheral);

/*
 * @fn:		RCC_APB2EnableClock
 * @brief:	Enable APB2 clock for peripheral
 * @param:	Copy_Peripheral		(ENUM: @APB2Peripherals_t)
 * @retval:	void
 * */
void RCC_APB2EnableClock(APB2Peripherals_t Copy_Peripheral);

/*
 * @fn:		RCC_APB2DisableClock
 * @brief:	Disable APB2 clock for peripheral
 * @param:	Copy_Peripheral		(ENUM: @APB2Peripherals_t)
 * @retval:	void
 * */
void RCC_APB2DisableClock(APB2Peripherals_t Copy_Peripheral);




#endif
