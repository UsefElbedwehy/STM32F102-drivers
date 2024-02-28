#ifndef   RCC_PRIVATE_H_
#define   RCC_PRIVATE_H_

#define TIMEOUT   4000U

#define SET_MASK	1

#define GET_MASK	0x01

#define PLL_READY_FLAG	1
#define HSE_READY_FLAG	1
#define HSI_READY_FLAG	1

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

#endif
