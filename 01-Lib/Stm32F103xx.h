#ifndef STM32F103XX_H_
#define STM32F103XX_H_
/**************Various Memory Base Addresses***************/
#define SRAM_BASE_ADDRESS  					0x20000000UL
#define FLASH_BASE_ADDRESS 					0x08000000UL
#define SYSTEM_MEMORY_BASE_ADDRESS	0x1FFFB000UL
/***************AHB Peripherals Base Addresses****************/
#define RCC_BASE_ADDRESS 						0x40021000UL    /*RESET AND CLOCK CONTROL BASE ADDRESS*/
/***************APB1 Peripherals Base Addresses****************/

/***************APB2 Peripherals Base Addresses****************/
#define GPIOA_BASE_ADDRESS         0x40010800UL				 /*GENERAL PURPOSE INPUT OUTPOT (PORTA) BASE ADDRESS*/
#define GPIOB_BASE_ADDRESS			0x40010C00UL               /*GENERAL PURPOSE INPUT OUTPOT (PORTB) BASE ADDRESS*/
#define GPIOC_BASE_ADDRESS			0x40011000UL               /*GENERAL PURPOSE INPUT OUTPOT (PORTC) BASE ADDRESS*/
#define GPIOD_BASE_ADDRESS			0x40011400UL               /*GENERAL PURPOSE INPUT OUTPOT (PORTD) BASE ADDRESS*/
#define GPIOE_BASE_ADDRESS			0x40011800UL               /*GENERAL PURPOSE INPUT OUTPOT (PORTE) BASE ADDRESS*/
#define GPIOF_BASE_ADDRESS			0x40011C00UL               /*GENERAL PURPOSE INPUT OUTPOT (PORTF) BASE ADDRESS*/
#define GPIOG_BASE_ADDRESS			0x40012000UL               /*GENERAL PURPOSE INPUT OUTPOT (PORTG) BASE ADDRESS*/
                                                                                             
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
#define GPIOA		((GPIO_Reg_t*))(GPIOA_BASE_ADDRESS))
#define GPIOB		((GPIO_Reg_t*))(GPIOB_BASE_ADDRESS))
#define GPIOC		((GPIO_Reg_t*))(GPIOC_BASE_ADDRESS))
#define GPIOD		((GPIO_Reg_t*))(GPIOD_BASE_ADDRESS))
#define GPIOE		((GPIO_Reg_t*))(GPIOE_BASE_ADDRESS))
#define GPIOF		((GPIO_Reg_t*))(GPIOF_BASE_ADDRESS))
#define GPIOG		((GPIO_Reg_t*))(GPIOG_BASE_ADDRESS))

#endif