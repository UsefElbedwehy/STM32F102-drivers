#ifndef  NVIC_INTERFACE_H_
#define  NVIC_INTERFACE_H_


typedef enum{

	NVIC_IRQ_WWDG=0,
	NVIC_IRQ_PVD,
	NVIC_IRQ_TAMPER,
	NVIC_IRQ_RTC,
	NVIC_IRQ_FLASH,
	NVIC_IRQ_RCC_,
	NVIC_IRQ_EXTI0,
	NVIC_IRQ_EXTI1,
	NVIC_IRQ_EXTI2,
	NVIC_IRQ_EXTI3,
	NVIC_IRQ_EXTI4,
	NVIC_IRQ_DMA1_Channel1,
	NVIC_IRQ_DMA1_Channel2,
	NVIC_IRQ_DMA1_Channel3,
	NVIC_IRQ_DMA1_Channel4,
	NVIC_IRQ_DMA1_Channel5,
	NVIC_IRQ_DMA1_Channel6,
	NVIC_IRQ_DMA1_Channel7,
	NVIC_IRQ_ADC1_2,
	NVIC_IRQ_CAN1_TX,
	NVIC_IRQ_CAN1_RX0,
	NVIC_IRQ_CAN1_RX1,
	NVIC_IRQ_CAN1_SCE,
	NVIC_IRQ_EXTI9_5,
	NVIC_IRQ_TIM1_BRK,
	NVIC_IRQ_TIM1_UP,
	NVIC_IRQ_TIM1_TRG_COM,
	NVIC_IRQ_TIM1_CC,
	NVIC_IRQ_TIM2,
	NVIC_IRQ_TIM3,
	NVIC_IRQ_TIM4,
	NVIC_IRQ_I2C1_EV,
	NVIC_IRQ_I2C1_ER,
	NVIC_IRQ_I2C2_EV,
	NVIC_IRQ_I2C2_ER,
	NVIC_IRQ_SPI1,
	NVIC_IRQ_SPI2,
	NVIC_IRQ_USART1,
	NVIC_IRQ_USART2,
	NVIC_IRQ_USART3,
	NVIC_IRQ_EXTI15_10,
	NVIC_IRQ_RTC_Alarm,
	NVIC_IRQ_OTG_FS_WKUP,
	NVIC_IRQ_TIM5=50,
	NVIC_IRQ_SPI3,
	NVIC_IRQ_UART4,
	NVIC_IRQ_UART5,
	NVIC_IRQ_TIM6,
	NVIC_IRQ_TIM7,
	NVIC_IRQ_DMA2_Channel1,
	NVIC_IRQ_DMA2_Channel2,
	NVIC_IRQ_DMA2_Channel3,
	NVIC_IRQ_DMA2_Channel4,
	NVIC_IRQ_DMA2_Channel5,
	NVIC_IRQ_ETH,
	NVIC_IRQ_ETH_WKUP,
	NVIC_IRQ_CAN2_TX,
	NVIC_IRQ_CAN2_RX0,
	NVIC_IRQ_CAN2_RX1,
	NVIC_IRQ_CAN2_SCE,
	NVIC_IRQ_OTG_FS

}NVIC_IRQn_t;

/*
 * @fn	  :	NVIC_EnableIRQ
 * @brief : Enables an interrupt or exception.
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_EnableIRQ(NVIC_IRQn_t IRQn);

/*
 * @fn	  :	NVIC_DisableIRQ
 * @brief : Disables an interrupt or exception.
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_DisableIRQ(NVIC_IRQn_t IRQn);

/*
 * @fn	  :	NVIC_SetPendingIRQ
 * @brief : Sets the pending status of interrupt or exception to 1
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_SetPendingIRQ(NVIC_IRQn_t IRQn);

/*
 * @fn	  :	NVIC_ClearPendingIRQ
 * @brief : Clears the pending status of interrupt or exception to 0.
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_ClearPendingIRQ(NVIC_IRQn_t IRQn);

/*
 * @fn	  :	NVIC_GetPendingIRQ
 * @brief : Reads the pending status of interrupt or exception.
 * 			This function returns non-zero value
 * 			if the pending status is set to 1.
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @param : Copy_u8PendingVal	pointer to uint8_t
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_GetPendingIRQ(NVIC_IRQn_t IRQn , uint8_t* Copy_u8PendingVal);

/*
 * @fn	  :	NVIC_SetIRQnPriority
 * @brief : Sets the priority of an interrupt or exception
 * 			with configurable priority level to 1.
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @param : priority			(ENUM: @NVIC_IRQn_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_SetIRQnPriority(NVIC_IRQn_t IRQn, uint32_t priority);

/*
 * @fn	  :	NVIC_GetPriority
 * @brief : Reads the priority of an interrupt or exception with
			configurable priority level. This function return the
			current priority level.
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @param : Copy_u8PriorityVal	uint8_t
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_GetPriority(NVIC_IRQn_t IRQn ,uint8_t* Copy_u8PriorityVal);

/*
 * @fn	  :	NVIC_GetActiveFlag
 * @brief : Reads the Active flag of an interrupt or exception with
			configurable priority level. This function return the
			active flag state.
 * @param : IRQn				(ENUM: @NVIC_IRQn_t)
 * @param : Copy_pu8PendingVal	pointer to uint8_t
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t NVIC_GetActiveFlag(NVIC_IRQn_t IRQn ,uint8_t* Copy_pu8PendingVal);
















#endif
