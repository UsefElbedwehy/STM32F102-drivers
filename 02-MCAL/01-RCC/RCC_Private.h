/***********************************************************************************/
/************** 	Author : Usef Elbedwehy              		************************************/
/**************	 	Layer : MACL 						             ***********************************/
/**************	 	SWC : RCC    						            ***********************************/
/************** 	Version : V1         						   		**********************************/
/********************************************************************************/
#ifndef   RCC_PRIVATE_H_
#define   RCC_PRIVATE_H_
/*clock sources*/
#define PLL 	 	0
#define HSE 	 	1
#define HSI 	 	2
#define HALF_HSI 	3
#define HALF_HSE 	4
/*states*/
#define ON    		0
#define OFF   		1
/* PLL multiplication factor
 * ready to be masked
 * maskable*/
#define PLL_M1  	0
#define PLL_M2  	1
#define PLL_M3  	2
#define PLL_M4  	3
#define PLL_M5  	4
#define PLL_M6  	5
#define PLL_M7  	6
#define PLL_M8  	7
#define PLL_M9  	8
#define PLL_M10 	9
#define PLL_M11 	10
#define PLL_M12 	11
#define PLL_M13 	12
#define PLL_M14 	13
#define PLL_M15 	14
#define PLL_M16 	15
/*AHB peripherals*/
enum{
	DMA1,
	DMA2,
	SRAM,
	FLITF=4,
	CRC=6,
	FSMC=8,
	SDIO=10,
};
/*APB1 peripherals*/
enum{
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
};
/*APB2 peripherals*/
enum{
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
};

#endif
