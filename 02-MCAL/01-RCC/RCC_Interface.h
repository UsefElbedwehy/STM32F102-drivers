#ifndef   RCC_INTERFACE_H_
#define   RCC_INTERFACE_H_

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
