#ifndef STM32F103XX_H_
#define STM32F103XX_H_
/**************Various Memory Base Addresses***************/
#define SRAM_BASE_ADDRESS  					0x20000000UL
#define FLASH_BASE_ADDRESS 					0x08000000UL
#define SYSTEM_MEMORY_BASE_ADDRESS	0x1FFFB000UL
/**************Core Peripherals Base Addresses***************/
#define SYSTICK_ADDRESS_BASE					0xE000E010UL
/***************AHB Peripherals Base Addresses****************/
#define RCC_BASE_ADDRESS 						0x40021000UL    /*RESET AND CLOCK CONTROL BASE ADDRESS*/
/***************APB1 Peripherals Base Addresses****************/
#define	USART5_BASE_ADDRESS			0x40005000UL				/*UNIVERASL SYNCH/ASYNCH RECEIVER TRANSMITTER 5*/
#define	USART4_BASE_ADDRESS			0x40004C00UL				/*UNIVERASL SYNCH/ASYNCH RECEIVER TRANSMITTER 4*/
#define	USART3_BASE_ADDRESS			0x40004800UL				/*UNIVERASL SYNCH/ASYNCH RECEIVER TRANSMITTER 3*/
#define	USART2_BASE_ADDRESS			0x40004400UL				/*UNIVERASL SYNCH/ASYNCH RECEIVER TRANSMITTER 2*/
/***************APB2 Peripherals Base Addresses****************/
#define GPIOA_BASE_ADDRESS         0x40010800UL				 /*GENERAL PURPOSE INPUT OUTPOT (PORTA) BASE ADDRESS*/
#define GPIOB_BASE_ADDRESS			0x40010C00UL               /*GENERAL PURPOSE INPUT OUTPOT (PORTB) BASE ADDRESS*/
#define GPIOC_BASE_ADDRESS			0x40011000UL               /*GENERAL PURPOSE INPUT OUTPOT (PORTC) BASE ADDRESS*/
#define GPIOD_BASE_ADDRESS			0x40011400UL               /*GENERAL PURPOSE INPUT OUTPOT (PORTD) BASE ADDRESS*/
#define GPIOE_BASE_ADDRESS			0x40011800UL               /*GENERAL PURPOSE INPUT OUTPOT (PORTE) BASE ADDRESS*/
#define GPIOF_BASE_ADDRESS			0x40011C00UL               /*GENERAL PURPOSE INPUT OUTPOT (PORTF) BASE ADDRESS*/
#define GPIOG_BASE_ADDRESS			0x40012000UL               /*GENERAL PURPOSE INPUT OUTPOT (PORTG) BASE ADDRESS*/

#define	USART1_BASE_ADDRESS			0x40013800UL				/*UNIVERASL SYNCH/ASYNCH RECEIVER TRANSMITTER 1*/
/***************RCC Register Definition Structure****************/
typedef struct{
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_AHBENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
	volatile uint32_t RCC_AHBRSTR;
	volatile uint32_t RCC_CFGR2;
}RCC_Reg_t;
/***************RCC Register Definition ****************/
RCC_Reg_t* RCC = (RCC_Reg_t*)(RCC_BASE_ADDRESS);

/***************GPIO Register Definition Structure****************/
typedef struct{
	volatile uint32_t GPIOx_CRL;
	volatile uint32_t GPIOx_CRH;
	volatile uint32_t GPIOx_IDR;
	volatile uint32_t GPIOx_ODR;
	volatile uint32_t GPIOx_BSRR;
	volatile uint32_t GPIOx_BRR;
	volatile uint32_t GPIOx_LCKR;
	volatile uint32_t AFIO_EVCR;
	volatile uint32_t AFIO_MAPR;
	volatile uint32_t AFIO_EXTICR1;
	volatile uint32_t AFIO_EXTICR2;
	volatile uint32_t AFIO_EXTICR3;
	volatile uint32_t AFIO_EXTICR4;
	volatile uint32_t AFIO_MAPR2;
}GPIO_Reg_t;
/***************GPIO Register Definition ****************/
#define GPIOA		((GPIO_Reg_t*)GPIOA_BASE_ADDRESS)
#define GPIOB		((GPIO_Reg_t*)GPIOB_BASE_ADDRESS)
#define GPIOC		((GPIO_Reg_t*)GPIOC_BASE_ADDRESS)
#define GPIOD		((GPIO_Reg_t*)GPIOD_BASE_ADDRESS)
#define GPIOE		((GPIO_Reg_t*)GPIOE_BASE_ADDRESS)
#define GPIOF		((GPIO_Reg_t*)GPIOF_BASE_ADDRESS)
#define GPIOG		((GPIO_Reg_t*)GPIOG_BASE_ADDRESS)
/***************SYSTICK Register Definition Structure****************/
typedef struct{
	volatile uint32_t SYSTICK_CSR; 			/* SysTick Control and Status Register - RW*/
	volatile uint32_t SYSTICK_RVR;			/* SysTick Reload Value Register - RW*/
	volatile uint32_t SYSTICK_CVR;			/* SysTick Current Value Register - RW*/
	volatile uint32_t SYSTICK_CALIB;		/* SysTick Calibration Value Register - RO*/

}SYSTICK_Reg_t;
/***************SYSTICK Register Definition ****************/
#define SYSTICK 		((SYSTICK_Reg_t*)SYSTICK_ADDRESS_BASE)

/***************USART Register Definition Structure****************/
typedef struct{

	volatile uint32_t USART_SR;
	volatile uint32_t USART_DR;
	volatile uint32_t USART_BRR;
	volatile uint32_t USART_CR1;
	volatile uint32_t USART_CR2;
	volatile uint32_t USART_CR3;
	volatile uint32_t USART_GTPR;

}USART_Reg_t;
/***************USART Register Definition ****************/
#define	USART1	((USART_Reg_t*)USART1_BASE_ADDRESS)
#define	USART2	((USART_Reg_t*)USART2_BASE_ADDRESS)
#define	USART3	((USART_Reg_t*)USART3_BASE_ADDRESS)
#define	USART4	((USART_Reg_t*)USART4_BASE_ADDRESS)
#define	USART5	((USART_Reg_t*)USART5_BASE_ADDRESS)


#endif
