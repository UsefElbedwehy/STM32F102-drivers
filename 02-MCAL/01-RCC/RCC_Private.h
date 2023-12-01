#ifndef   RCC_PRIVATE_H_
#define   RCC_PRIVATE_H_

#define TIMEOUT   4000

/*@ClockSrc_t*/
typedef enum{
	PLL=0,
	HSE,
	HSI

}ClockSrc_t;

/*@HSEConfig_t*/
typedef enum{
	NORMAL_HSE=0,
	HALF_HSE
}HSEConfig_t;

/*@PLLSrcConfig_t*/
typedef enum{
	HALF_HSI=0,
	SRC_HSE
}PLLSrcConfig_t;

/*@State_t*/
typedef enum{
	ON=0,
	OFF
}State_t;

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
	DMA1,
	DMA2,
	SRAM,
	FLITF=4,
	CRC=6,
	FSMC=8,
	SDIO=10,
}AHBPeriperals_t;

/*@APB1Peripherals_t*/
typedef enum{
	TIM2,
	TIM3,
	TIM4,
	TIM5,
	TIM6,
	TIM7,
	TIM12,
	TIM13,
	TIM14,
	WWDG=11,
	SPI2=14,
	SPI3,
	USART2=17,
	USART3,
	UART4,
	UART5,
	I2C1,
	I2C2,
	USB,
	BKP=27,
	PWR,
	DAC
}APB1Peripherals_t;

/*@APB2Peripherals_t*/
typedef enum{
	AFIO,
	IOPA=2,
	IOPB,
	IOPC,
	IOPD,
	IOPE,
	IOPF,
	IOPG,
	ADC1,
	ADC2,
	TIM1,
	SPI1,
	TIM8,
	USART,
	ADC3,
	TIM9=19,
	TIM10,
	TIM11
}APB2Peripherals_t;

#endif
