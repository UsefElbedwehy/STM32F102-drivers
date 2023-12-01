#ifndef   RCC_INTERFACE_H_
#define   RCC_INTERFACE_H_

uint16_t RCC_VoidSetClkSts(ClockSrc_t Copy_uint16ClkType,State_t Copy_uint16Status);
uint16_t RCC_VoidSetSysClk(ClockSrc_t Copy_uint16ClkType);
uint16_t RCC_VoidHSEConfig(HSEConfig_t Copy_uint16Config);
uint16_t RCC_VoidPLLConfig(PllMultiFac_t Copy_uint16PLLMux,PLLSrcConfig_t Copy_uint16PLLSrc);
void RCC_AHBEnableClock(AHBPeriperals_t Copy_uint16Peripheral);
void RCC_AHBDisableClock(AHBPeriperals_t Copy_uint16Peripheral);
void RCC_APB1EnableClock(APB1Peripherals_t Copy_uint16Peripheral);
void RCC_APB1DisableClock(APB1Peripherals_t Copy_uint16Peripheral);
void RCC_APB2EnableClock(APB2Peripherals_t Copy_uint16Peripheral);
void RCC_APB2DisableClock(APB2Peripherals_t Copy_uint16Peripheral);




#endif
