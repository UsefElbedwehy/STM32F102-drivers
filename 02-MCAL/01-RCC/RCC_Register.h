/***********************************************************************************/
/************** 	Author : Usef Elbedwehy              		************************************/
/**************	 	Layer : MACL 						             ***********************************/
/**************	 	SWC : RCC    						            ***********************************/
/************** 	Version : V1         						   		**********************************/
/********************************************************************************/
#ifndef  RCC_REGISTER_H_
#define  RCC_REGISTER_H_

typedef struct{
	uint32_t RCC_CR;
	uint32_t RCC_CFGR;
	uint32_t RCC_CIR;
	uint32_t RCC_APB2RSTR;
	uint32_t RCC_APB1RSTR;
	uint32_t RCC_AHBENR;
	uint32_t RCC_APB2ENR;
	uint32_t RCC_APB1ENR;
	uint32_t RCC_BDCR;
	uint32_t RCC_CSR;
	uint32_t RCC_AHBRSTR;
	uint32_t RCC_CFGR2;
}RCC_Reg_t;

RCC_Reg_t* RCC = (RCC_Reg_t*)(0x40021000);


#endif
