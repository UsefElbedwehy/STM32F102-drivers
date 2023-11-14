/***********************************************************************************/
/************** 	Author : Usef Elbedwehy              		************************************/
/**************	 	Layer : MACL 						             ***********************************/
/**************	 	SWC : RCC    						            ***********************************/
/************** 	Version : V1         						   		**********************************/
/********************************************************************************/
#ifndef   RCC_INTERFACE_H_
#define   RCC_INTERFACE_H_

uint16_t RCC_VoidSetClkSts(uint16_t Copy_uint16ClkType,uint16_t Copy_uint16Status);
uint16_t RCC_VoidSetSysClk(uint16_t Copy_uint16ClkType);
uint16_t RCC_VoidHSEConfig(uint16_t Copy_uint16Config);
uint16_t RCC_VoidPLLConfig(uint16_t Copy_uint16PLLMux,uint16_t Copy_uint16PLLSrc);
void RCC_AHBEnableClock(uint16_t Copy_uint16Peripheral);
void RCC_AHBDisableClock(uint16_t Copy_uint16Peripheral);
void RCC_APB1EnableClock(uint16_t Copy_uint16Peripheral);
void RCC_APB1DisableClock(uint16_t Copy_uint16Peripheral);
void RCC_APB2EnableClock(uint16_t Copy_uint16Peripheral);
void RCC_APB2DisableClock(uint16_t Copy_uint16Peripheral);




#endif
