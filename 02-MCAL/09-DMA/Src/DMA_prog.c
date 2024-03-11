/***********************************************************************************************************************************
 ***********************************************************************************************************************************
 ***********************************************************************************************************************************
 * @File	:	DMA_prog.c
 * @Author	:	Usef Elbedwehy
 * @Brief	:	Main program body of DMA
 * @layer	:	MCAL
 * @Date	:	11 March 2024
 ***********************************************************************************************************************************
 ***********************************************************************************************************************************
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 ************************************************ ### INCLUDE SECTION ### **********************************************************
 **********************************************************************************************************************************/
#include <stdint.h>

#include "ErrType.h"
#include "Stm32F103xx.h"

#include "DMA_prv.h"
#include "DMA_interface.h"
/***********************************************************************************************************************************/

/************************************************************************************************************************************
 ********************************************* ### GLOBAL VARIABLES SECTION ### *****************************************************
 ************************************************************************************************************************************/
static DMA_regDef_t* DMAx[DMA_NUMBERS] = { DMA1 , DMA2 };

static void (*DMA1_Gpv_CallBack[DMA_MAX_CHANNEL_NUMBER][DMA_CHANNELx_MAX_FLAG_NUMBER]) (void) = {NULL};
static void (*DMA2_Gpv_CallBack[DMA_MAX_CHANNEL_NUMBER][DMA_CHANNELx_MAX_FLAG_NUMBER]) (void) = {NULL};
/************************************************************************************************************************************/

/************************************************************************************************************************************
 ********************************************** ### Functions Declarations ### ******************************************************
 ************************************************************************************************************************************/

/*
 * @fn		: DMA_Init
 * @brief	: Initialize the DMA channel
 * @param	: Init			pointer to const (STRUCT: @DMA_InitConfig_t)
 * @retval	: Local_ErrorState		(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t DMA_Init(const DMA_InitConfig_t* Init)
{
	ErrorState_t Local_ErrorState = DMA_OK;

	if(Init == NULL)
	{
		Local_ErrorState = DMA_NULL_POINTER;
	}

	if(		   (Init->DMA_NUMBER >= DMA_NUM_1)
			&& (Init->DMA_NUMBER <= DMA_NUM_2)
			&& (Init->DMA_CHANNEL_NUMBER >= DMA_CHANNEL_1)
			&& (Init->DMA_CHANNEL_NUMBER <= DMA_CHANNEL_7)
			&& (Init->DMA_PRIORITY >= DMA_PRIORITY_LOW)
			&& (Init->DMA_PRIORITY <= DMA_PRIORITY_VERY_HIGH)
			&& (Init->DMA_DATA_TRANS_DIR >= DMA_DIR_P2P)
			&& (Init->DMA_DATA_TRANS_DIR <= DMA_DIR_M2P)
			&& (Init->DMA_CIRCULAR_MODE >= DMA_CIRCULAR_DISABLED)
			&& (Init->DMA_CIRCULAR_MODE <= DMA_CIRCULARENABLED)
			&& (Init->DMA_PERIPH_SIZE >= DMA_8_BITS_PSIZE)
			&& (Init->DMA_PERIPH_SIZE <= DMA_32_BITS_PSIZE)
			&& (Init->DMA_MEM_SIZE >= DMA_8_BITS_MSIZE)
			&& (Init->DMA_MEM_SIZE <= DMA_32_BITS_MSIZE)
			&& (Init->DMA_PERIPH_INC >= DMA_PINC_DISABLE)
			&& (Init->DMA_PERIPH_INC <= DMA_PINC_ENABLE)
			&& (Init->DMA_MEM_INC >= DMA_MINC_DISABLE)
			&& (Init->DMA_MEM_INC <= DMA_MINC_ENABLE)
			&& (Init->DMA_INT_EN_STATE >= DMA_INTERRUPT_DISABLED)
			&& (Init->DMA_INT_EN_STATE <= DMA_INTERRUPT_ENABLED)
			&& (Init->DMA_INTs_STATE.DMA_INTERRUPT_TCIE >= DMA_INT_TCIE_DISABLED)
			&& (Init->DMA_INTs_STATE.DMA_INTERRUPT_TCIE <= DMA_INT_TCIE_ENABLED)
			&& (Init->DMA_INTs_STATE.DMA_INTERRUPT_THIE >= DMA_INT_THIE_DISABLED)
			&& (Init->DMA_INTs_STATE.DMA_INTERRUPT_THIE <= DMA_INT_THIE_ENABLED)
			&& (Init->DMA_INTs_STATE.DMA_INTERRUPT_TEIE >= DMA_INT_TEIE_DISABLED)
			&& (Init->DMA_INTs_STATE.DMA_INTERRUPT_TEIE <= DMA_INT_TEIE_ENABLED))
	{
		/*SET PRIORITY*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR |= (Init->DMA_PRIORITY << DMA_CCRx_PL__);

		/* --- SET DATA TRANSFER DIRECTION --- */
		DMA_SetDataTransferDirection(Init);

		/*CIRCULAR MODE ENABLE/DISABLE*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR |= (Init->DMA_CIRCULAR_MODE << DMA_CCRx_CIRC);

		/*PERIPHERAL SIZE*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR |= (Init->DMA_PERIPH_SIZE << DMA_CCRx_PSIZE__);

		/*MEMORY SIZE*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR |= (Init->DMA_MEM_SIZE << DMA_CCRx_MSIZE__);

		/*PERIPHERAL INCREMENT ENABLE/DISABLE*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR |= (Init->DMA_PERIPH_INC << DMA_CCRx_PINC);

		/*MEMORY INCREMENT ENABLE/DISABLE*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR |= (Init->DMA_MEM_INC << DMA_CCRx_MINC);

	}
	else
	{
		Local_ErrorState = DMA_NOK;
	}

	return Local_ErrorState;
}

/*
 * @fn		: DMA_Start
 * @brief	: DMA start transfer
 * @param	: Init			pointer to const (STRUCT: @DMA_InitConfig_t)
 * @param	: Copy_pu8Src			pointer to (uint8_t)
 * @param	: Copy_pu8Dst			pointer to (uint8_t)
 * @param	: Copy_u32Size			(uint32_t)
 * @retval	: Local_ErrorState		(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t DMA_Start(const DMA_InitConfig_t* Init,uint8_t* Copy_pu8Src, uint8_t* Copy_pu8Dst, uint32_t Copy_u32Size)
{
	ErrorState_t Local_ErrorState = DMA_OK;

	if((Copy_pu8Src != NULL) && (Copy_pu8Dst != NULL))
	{
		/*Configure the source and destination*/
		switch(Init->DMA_DATA_TRANS_DIR)
		{
		case DMA_DIR_M2M:
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CMAR = (uint32_t)Copy_pu8Src;
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CPAR = (uint32_t)Copy_pu8Dst;
			break;
		case DMA_DIR_M2P:
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CMAR = (uint32_t)Copy_pu8Src;
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CPAR = (uint32_t)Copy_pu8Dst;
			break;
		case DMA_DIR_P2M:
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CPAR = (uint32_t)Copy_pu8Src;
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CMAR = (uint32_t)Copy_pu8Dst;
			break;
		case DMA_DIR_P2P:
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CPAR = (uint32_t)Copy_pu8Src;
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CMAR = (uint32_t)Copy_pu8Dst;
			break;
		}
		/*transfer size*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CNDTR = Copy_u32Size;

		/*ENABLE CHANNEL*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR |= (DMA_SET_MASK << DMA_CCRx_EN);
	}
	else
	{
		Local_ErrorState = DMA_NULL_POINTER;
	}

	return Local_ErrorState;
}

/*
 * @fn		: DMA_Start_IT
 * @brief	: DMA start transfer with interrupt notification
 * @param	: Init			pointer to const (STRUCT: @DMA_InitConfig_t)
 * @param	: Copy_pu8Src			pointer to (uint8_t)
 * @param	: Copy_pu8Dst			pointer to (uint8_t)
 * @param	: Copy_u32Size			(uint32_t)
 * @retval	: Local_ErrorState		(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t DMA_Start_IT(const DMA_InitConfig_t* Init,uint8_t* Copy_pu8Src, uint8_t* Copy_pu8Dst, uint32_t Copy_u32Size)
{
	ErrorState_t Local_ErrorState = DMA_OK;

	if((Init != NULL) && (Copy_pu8Src != NULL) && (Copy_pu8Dst != NULL))
	{

		/*Configure the source and destination*/
		switch(Init->DMA_DATA_TRANS_DIR)
		{
		case DMA_DIR_M2M:
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CMAR = (uint32_t)Copy_pu8Src;
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CPAR = (uint32_t)Copy_pu8Dst;
			break;
		case DMA_DIR_M2P:
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CMAR = (uint32_t)Copy_pu8Src;
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CPAR = (uint32_t)Copy_pu8Dst;
			break;
		case DMA_DIR_P2M:
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CPAR = (uint32_t)Copy_pu8Src;
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CMAR = (uint32_t)Copy_pu8Dst;
			break;
		case DMA_DIR_P2P:
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CPAR = (uint32_t)Copy_pu8Src;
			DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CMAR = (uint32_t)Copy_pu8Dst;
			break;
		}

		/*transfer size*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CNDTR = Copy_u32Size;
		/*Clear all interrupts flag*/
		DMA_ClearInterruptFlags(Init->DMA_NUMBER , Init->DMA_CHANNEL_NUMBER);
		/*Enable Configured interrupts*/
		DMA_InterruptEnable(Init);
		/*ENABLE CHANNEL*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR |= (DMA_SET_MASK << DMA_CCRx_EN);

	}
	else
	{
		Local_ErrorState = DMA_NULL_POINTER;
	}


	return Local_ErrorState;
}

/*
 *@fn		: DMA_SetCallBack
 *@brief	: Set the call back function
 *@param	: DMA_Number		(ENUM: @DMA_Number_t)
 *@param	: Channel_Number	(ENUM: @DMA_Channel_t)
 *@param	: FlagID			(ENUM: @DMA_FlagID_t)
 *@param	: pv_CallBack		pointer to void function
 *@retval	: Local_ErrorState  (ENUM: @ErrorState_t)
 *
 * */
ErrorState_t DMA_SetCallBack(DMA_Number_t  DMA_Number ,DMA_Channel_t Channel_Number ,DMA_FlagID_t FlagID ,void (*pv_CallBack)(void))
{
	ErrorState_t Local_ErrorState = DMA_OK;

	if(pv_CallBack == NULL)
	{
		Local_ErrorState = DMA_NULL_POINTER;
	}
	else
	{
		switch(DMA_Number)
		{
		case DMA_NUM_1:
			DMA1_Gpv_CallBack[Channel_Number][DMA_CHANNELx_TRANSFER_COMPLETE_FLAG] = pv_CallBack ;
			break;
		case DMA_NUM_2:
			DMA2_Gpv_CallBack[Channel_Number][DMA_CHANNELx_TRANSFER_COMPLETE_FLAG] = pv_CallBack ;
			break;
		}
	}

	return Local_ErrorState;
}

/*
 *@fn		: DMA_IRQ_Handler
 *@brief	: Set the call back function
 *@param	: DMA_Number		(ENUM: @DMA_Number_t)
 *@param	: Channel_Number			(ENUM: @DMA_Channel_t)
 *@retval	: void
 *
 * */
void DMA_IRQ_Handler(DMA_Number_t  DMA_Number ,DMA_Channel_t Channel_Number)
{
	if(DMA_Number == DMA_NUM_1)
	{
		/* ----- DMA1 ----- */
		/*GLOBAL INTERRUPT FLAG*/
		if(DMA_GetInterruptFlags(DMA_NUM_1 , Channel_Number , DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG) == DMA_READY_FLAG)
		{
			DMA_ClearInterruptFlag(DMA_NUM_1, Channel_Number, DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG);
			if( (DMA1_Gpv_CallBack[Channel_Number][DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG] != NULL))
			{
				DMA1_Gpv_CallBack[Channel_Number][DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG]();
			}

		}
		/*TRANSFER COMPLETE FLAG*/
		if(DMA_GetInterruptFlags(DMA_NUM_1 , Channel_Number , DMA_CHANNELx_TRANSFER_COMPLETE_FLAG) == DMA_READY_FLAG)
		{
			DMA_ClearInterruptFlag(DMA_NUM_1, Channel_Number, DMA_CHANNELx_TRANSFER_COMPLETE_FLAG);
			if((DMA1_Gpv_CallBack[Channel_Number][DMA_CHANNELx_TRANSFER_COMPLETE_FLAG] != NULL))
			{
				DMA1_Gpv_CallBack[Channel_Number][DMA_CHANNELx_TRANSFER_COMPLETE_FLAG]();
			}

		}
		/*HALF TRANSFER FLAG*/
		if(DMA_GetInterruptFlags(DMA_NUM_1 , Channel_Number , DMA_CHANNELx_HALF_TRANSFER_FLAG) == DMA_READY_FLAG)
		{
			DMA_ClearInterruptFlag(DMA_NUM_1, Channel_Number, DMA_CHANNELx_HALF_TRANSFER_FLAG);
			if((DMA1_Gpv_CallBack[Channel_Number][DMA_CHANNELx_HALF_TRANSFER_FLAG] != NULL))
			{
				DMA1_Gpv_CallBack[Channel_Number][DMA_CHANNELx_HALF_TRANSFER_FLAG]();
			}

		}
		/*TRANSFER ERROR FLAG*/
		if(DMA_GetInterruptFlags(DMA_NUM_1 , Channel_Number , DMA_CHANNELx_TRANSFER_ERROR_FLAG) == DMA_READY_FLAG)
		{
			DMA_ClearInterruptFlag(DMA_NUM_1, Channel_Number, DMA_CHANNELx_TRANSFER_ERROR_FLAG);
			if((DMA1_Gpv_CallBack[Channel_Number][DMA_CHANNELx_TRANSFER_ERROR_FLAG] != NULL))
			{
				DMA1_Gpv_CallBack[Channel_Number][DMA_CHANNELx_TRANSFER_ERROR_FLAG]();
			}

		}
	}
	else if(DMA_Number == DMA_NUM_2)
	{
		/* ----- DMA2 ----- */
		if(Channel_Number < DMA_CHANNEL_4)
		{
			/*GLOBAL INTERRUPT FLAG*/
			if(DMA_GetInterruptFlags(DMA_NUM_2 , Channel_Number , DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG) == DMA_READY_FLAG)
			{
				DMA_ClearInterruptFlag(DMA_NUM_2, Channel_Number, DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG);
				if( (DMA2_Gpv_CallBack[Channel_Number][DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG] != NULL))
				{
					DMA2_Gpv_CallBack[Channel_Number][DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG]();
				}

			}
			/*TRANSFER COMPLETE FLAG*/
			if(DMA_GetInterruptFlags(DMA_NUM_2 , Channel_Number , DMA_CHANNELx_TRANSFER_COMPLETE_FLAG) == DMA_READY_FLAG)
			{
				DMA_ClearInterruptFlag(DMA_NUM_2, Channel_Number, DMA_CHANNELx_TRANSFER_COMPLETE_FLAG);
				if((DMA2_Gpv_CallBack[Channel_Number][DMA_CHANNELx_TRANSFER_COMPLETE_FLAG] != NULL))
				{
					DMA2_Gpv_CallBack[Channel_Number][DMA_CHANNELx_TRANSFER_COMPLETE_FLAG]();
				}

			}
			/*HALF TRANSFER FLAG*/
			if(DMA_GetInterruptFlags(DMA_NUM_2 , Channel_Number , DMA_CHANNELx_HALF_TRANSFER_FLAG) == DMA_READY_FLAG)
			{
				DMA_ClearInterruptFlag(DMA_NUM_2, Channel_Number, DMA_CHANNELx_HALF_TRANSFER_FLAG);
				if((DMA2_Gpv_CallBack[Channel_Number][DMA_CHANNELx_HALF_TRANSFER_FLAG] != NULL))
				{
					DMA2_Gpv_CallBack[Channel_Number][DMA_CHANNELx_HALF_TRANSFER_FLAG]();
				}

			}
			/*TRANSFER ERROR FLAG*/
			if(DMA_GetInterruptFlags(DMA_NUM_2 , Channel_Number , DMA_CHANNELx_TRANSFER_ERROR_FLAG) == DMA_READY_FLAG)
			{
				DMA_ClearInterruptFlag(DMA_NUM_2, Channel_Number, DMA_CHANNELx_TRANSFER_ERROR_FLAG);
				if((DMA2_Gpv_CallBack[Channel_Number][DMA_CHANNELx_TRANSFER_ERROR_FLAG] != NULL))
				{
					DMA2_Gpv_CallBack[Channel_Number][DMA_CHANNELx_TRANSFER_ERROR_FLAG]();
				}

			}
		}
		else if(Channel_Number == DMA_CHANNEL_4)
		{
			/*---------- CHANNEL_4 -------------*/
			/*GLOBAL INTERRUPT FLAG*/
			if(DMA_GetInterruptFlags(DMA_NUM_2 , DMA_CHANNEL_4 , DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG) == DMA_READY_FLAG)
			{
				DMA_ClearInterruptFlag(DMA_NUM_2, DMA_CHANNEL_4, DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG);
				if( (DMA2_Gpv_CallBack[DMA_CHANNEL_4][DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG] != NULL))
				{
					DMA2_Gpv_CallBack[DMA_CHANNEL_4][DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG]();
				}

			}
			/*TRANSFER COMPLETE FLAG*/
			if(DMA_GetInterruptFlags(DMA_NUM_2 , DMA_CHANNEL_4 , DMA_CHANNELx_TRANSFER_COMPLETE_FLAG) == DMA_READY_FLAG)
			{
				DMA_ClearInterruptFlag(DMA_NUM_2, DMA_CHANNEL_4, DMA_CHANNELx_TRANSFER_COMPLETE_FLAG);
				if((DMA2_Gpv_CallBack[DMA_CHANNEL_4][DMA_CHANNELx_TRANSFER_COMPLETE_FLAG] != NULL))
				{
					DMA2_Gpv_CallBack[DMA_CHANNEL_4][DMA_CHANNELx_TRANSFER_COMPLETE_FLAG]();
				}

			}
			/*HALF TRANSFER FLAG*/
			if(DMA_GetInterruptFlags(DMA_NUM_2 , DMA_CHANNEL_4 , DMA_CHANNELx_HALF_TRANSFER_FLAG) == DMA_READY_FLAG)
			{
				DMA_ClearInterruptFlag(DMA_NUM_2, DMA_CHANNEL_4, DMA_CHANNELx_HALF_TRANSFER_FLAG);
				if((DMA2_Gpv_CallBack[DMA_CHANNEL_4][DMA_CHANNELx_HALF_TRANSFER_FLAG] != NULL))
				{
					DMA2_Gpv_CallBack[DMA_CHANNEL_4][DMA_CHANNELx_HALF_TRANSFER_FLAG]();
				}

			}
			/*TRANSFER ERROR FLAG*/
			if(DMA_GetInterruptFlags(DMA_NUM_2 , DMA_CHANNEL_4 , DMA_CHANNELx_TRANSFER_ERROR_FLAG) == DMA_READY_FLAG)
			{
				DMA_ClearInterruptFlag(DMA_NUM_2, DMA_CHANNEL_4, DMA_CHANNELx_TRANSFER_ERROR_FLAG);
				if((DMA2_Gpv_CallBack[DMA_CHANNEL_4][DMA_CHANNELx_TRANSFER_ERROR_FLAG] != NULL))
				{
					DMA2_Gpv_CallBack[DMA_CHANNEL_4][DMA_CHANNELx_TRANSFER_ERROR_FLAG]();
				}

			}
			/*---------- CHANNEL_5 -------------*/
			/*GLOBAL INTERRUPT FLAG*/
			if(DMA_GetInterruptFlags(DMA_NUM_2 , DMA_CHANNEL_5 , DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG) == DMA_READY_FLAG)
			{
				DMA_ClearInterruptFlag(DMA_NUM_2, DMA_CHANNEL_5, DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG);
				if( (DMA2_Gpv_CallBack[DMA_CHANNEL_5][DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG] != NULL))
				{
					DMA2_Gpv_CallBack[DMA_CHANNEL_5][DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG]();
				}

			}
			/*TRANSFER COMPLETE FLAG*/
			if(DMA_GetInterruptFlags(DMA_NUM_2 , DMA_CHANNEL_5 , DMA_CHANNELx_TRANSFER_COMPLETE_FLAG) == DMA_READY_FLAG)
			{
				DMA_ClearInterruptFlag(DMA_NUM_2, DMA_CHANNEL_5, DMA_CHANNELx_TRANSFER_COMPLETE_FLAG);
				if((DMA2_Gpv_CallBack[DMA_CHANNEL_5][DMA_CHANNELx_TRANSFER_COMPLETE_FLAG] != NULL))
				{
					DMA2_Gpv_CallBack[DMA_CHANNEL_5][DMA_CHANNELx_TRANSFER_COMPLETE_FLAG]();
				}

			}
			/*HALF TRANSFER FLAG*/
			if(DMA_GetInterruptFlags(DMA_NUM_2 , DMA_CHANNEL_5 , DMA_CHANNELx_HALF_TRANSFER_FLAG) == DMA_READY_FLAG)
			{
				DMA_ClearInterruptFlag(DMA_NUM_2, DMA_CHANNEL_5, DMA_CHANNELx_HALF_TRANSFER_FLAG);
				if((DMA2_Gpv_CallBack[DMA_CHANNEL_5][DMA_CHANNELx_HALF_TRANSFER_FLAG] != NULL))
				{
					DMA2_Gpv_CallBack[DMA_CHANNEL_5][DMA_CHANNELx_HALF_TRANSFER_FLAG]();
				}

			}
			/*TRANSFER ERROR FLAG*/
			if(DMA_GetInterruptFlags(DMA_NUM_2 , DMA_CHANNEL_5 , DMA_CHANNELx_TRANSFER_ERROR_FLAG) == DMA_READY_FLAG)
			{
				DMA_ClearInterruptFlag(DMA_NUM_2, DMA_CHANNEL_5, DMA_CHANNELx_TRANSFER_ERROR_FLAG);
				if((DMA2_Gpv_CallBack[DMA_CHANNEL_5][DMA_CHANNELx_TRANSFER_ERROR_FLAG] != NULL))
				{
					DMA2_Gpv_CallBack[DMA_CHANNEL_5][DMA_CHANNELx_TRANSFER_ERROR_FLAG]();
				}

			}
		}

	}

}
/*------------------------------------------------------------------------------------------------------------------------------------
 * ------------------------------------------------------- File Functions ------------------------------------------------------------
 * ----------------------------------------------------------------------------------------------------------------------------------*/
/*
 *@fn		: DMA_InterruptEnable
 *@brief	: to set the interrupts status (enable/disable)
 *@param	: Init			constant pointer to struct (@DMA_InitConfig_t)
 *@retval	: void
 *
 * */
static void DMA_InterruptEnable(const DMA_InitConfig_t* Init)
{
	/*Transfer complete interrupt enable/disable*/
	DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR &=~ (DMA_SET_MASK << DMA_CCRx_TCIE);
	DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR |= (Init->DMA_INTs_STATE.DMA_INTERRUPT_TCIE << DMA_CCRx_TCIE);
	/*Half transfer interrupt enable/disable*/
	DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR &=~ (DMA_SET_MASK << DMA_CCRx_HTIE);
	DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR |= (Init->DMA_INTs_STATE.DMA_INTERRUPT_THIE << DMA_CCRx_HTIE);
	/*Transfer error interrupt enable/disable*/
	DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR &=~ (DMA_SET_MASK << DMA_CCRx_TEIE);
	DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR |= (Init->DMA_INTs_STATE.DMA_INTERRUPT_TEIE << DMA_CCRx_TEIE);

}

/*
 *@fn		: DMA_ClearInterruptFlags
 *@brief	: to clear the interrupts flags
 *@param	: DMA_Number			(ENUM:@DMA_Number_t )
 *@param	: Channel_Number		(ENUM:@DMA_Channel_t )
 *@retval	: void
 *
 * */
static void DMA_ClearInterruptFlags(DMA_Number_t  DMA_Number ,DMA_Channel_t Channel_Number)
{
	/*Channel x global interrupt clear*/
	DMAx[DMA_Number]->DMA_IFCR |= (DMA_SET_MASK << (DMA_IFCR_CGIF1 + (4 * Channel_Number)) );
	/*Transfer complete interrupt enable/disable*/
	DMAx[DMA_Number]->DMA_IFCR |= (DMA_SET_MASK << (DMA_IFCR_CTCIF1 + (4 * Channel_Number)) );
	/*Half transfer interrupt enable/disable*/
	DMAx[DMA_Number]->DMA_IFCR |= (DMA_SET_MASK << (DMA_IFCR_CHTIF1 + (4 * Channel_Number)) );
	/*Transfer error interrupt enable/disable*/
	DMAx[DMA_Number]->DMA_IFCR |= (DMA_SET_MASK << (DMA_IFCR_CTEIF1 + (4 * Channel_Number)) );

}

/*
 *@fn		: DMA_ClearInterruptFlags
 *@brief	: to clear the interrupts flags
 *@param	: DMA_Number			(ENUM:@DMA_Number_t )
 *@param	: Channel_Number		(ENUM:@DMA_Channel_t )
 *@param	: Copy_FlagID			(ENUM:@DMA_FlagID_t )
 *@retval	: void
 *
 * */
static void DMA_ClearInterruptFlag(DMA_Number_t  DMA_Number ,DMA_Channel_t Channel_Number ,DMA_FlagID_t Copy_FlagID)
{
	switch(Copy_FlagID)
	{
	case DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG:
		/*Channel x global interrupt clear*/
		DMAx[DMA_Number]->DMA_IFCR |= (DMA_SET_MASK << (DMA_IFCR_CGIF1 + (4 * Channel_Number)) );
		break;
	case DMA_CHANNELx_TRANSFER_COMPLETE_FLAG:
		/*Transfer complete interrupt enable/disable*/
		DMAx[DMA_Number]->DMA_IFCR |= (DMA_SET_MASK << (DMA_IFCR_CTCIF1 + (4 * Channel_Number)) );
		break;
	case DMA_CHANNELx_HALF_TRANSFER_FLAG:
		/*Half transfer interrupt enable/disable*/
		DMAx[DMA_Number]->DMA_IFCR |= (DMA_SET_MASK << (DMA_IFCR_CHTIF1 + (4 * Channel_Number)) );
		break;
	case DMA_CHANNELx_TRANSFER_ERROR_FLAG:
		/*Transfer error interrupt enable/disable*/
		DMAx[DMA_Number]->DMA_IFCR |= (DMA_SET_MASK << (DMA_IFCR_CTEIF1 + (4 * Channel_Number)) );
		break;
	}

}

/*
 *@fn		: DMA_ClearInterruptFlags
 *@brief	: to clear the interrupts flags
 *@param	: DMA_Number			(ENUM:@DMA_Number_t )
 *@param	: Channel_Number		(ENUM:@DMA_Channel_t )
 *@param	: Copy_FlagID			(ENUM:@DMA_FlagID_t )
 *@retval	: uint8_t
 *
 * */
static uint8_t DMA_GetInterruptFlags(DMA_Number_t  DMA_Number ,DMA_Channel_t Channel_Number, DMA_FlagID_t Copy_FlagID)
{
	/*Channel x global interrupt clear*/
	return ((DMAx[DMA_Number]->DMA_IFCR >> (Copy_FlagID + (4 * Channel_Number))) & DMA_GET_MASK);
}

/*
 *@fn		: DMA_SetDataTransferDirection
 *@brief	: to set the data transfer direction ( M2M , M2P , P2P ,or M2P)
 *@param	: Init			constant pointer to struct (@DMA_InitConfig_t)
 *@retval	: void
 *
 * */
static void DMA_SetDataTransferDirection(const DMA_InitConfig_t* Init)
{
	switch(Init->DMA_DATA_TRANS_DIR)
	{
	case DMA_DIR_P2P:
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR &=~ (DMA_SET_MASK << DMA_CCRx_MEM2MEM);
		/*Read from peripheral*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR &=~ (DMA_SET_MASK << DMA_CCRx_DIR);
		break;
	case DMA_DIR_P2M:
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR &=~ (DMA_SET_MASK << DMA_CCRx_MEM2MEM);
		/*Read from peripheral*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR &=~ (DMA_SET_MASK << DMA_CCRx_DIR);
		break;
	case DMA_DIR_M2M:
		/*MEMORY TO MEMORY MODE ON*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR |= (DMA_SET_MASK << DMA_CCRx_MEM2MEM);
		/*Read from memory*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR |= (DMA_SET_MASK << DMA_CCRx_DIR);
		break;
	case DMA_DIR_M2P:
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR &=~ (DMA_SET_MASK << DMA_CCRx_MEM2MEM);
		/*Read from memory*/
		DMAx[Init->DMA_NUMBER]->DMA_ChannelReg[Init->DMA_CHANNEL_NUMBER].DMA_CCR |= (DMA_SET_MASK << DMA_CCRx_DIR);
		break;
	}
}
/* ----------------------------------------------------------------------------------------------------------------------------------*/
/*************************************************************************************************************************************/

/*************************************************************************************************************************************
 ************************************************ ### HANDLER SECTION ### ***********************************************************
 ************************************************************************************************************************************/
/* -------- DMA1 --------- */
/*DMA1 CHANNNEL1 IRQ HANDLER*/
void DMA1_Channel1_IRQHandler(void)
{
	DMA_IRQ_Handler(DMA_NUM_1 , DMA_CHANNEL_1);
}
/*DMA1 CHANNNEL2 IRQ HANDLER*/
void DMA1_Channel2_IRQHandler(void)
{
	DMA_IRQ_Handler(DMA_NUM_1 , DMA_CHANNEL_2);
}
/*DMA1 CHANNNEL3 IRQ HANDLER*/
void DMA1_Channel3_IRQHandler(void)
{
	DMA_IRQ_Handler(DMA_NUM_1 , DMA_CHANNEL_3);
}
/*DMA1 CHANNNEL4 IRQ HANDLER*/
void DMA1_Channel4_IRQHandler(void)
{
	DMA_IRQ_Handler(DMA_NUM_1 , DMA_CHANNEL_4);
}
/*DMA1 CHANNNEL5 IRQ HANDLER*/
void DMA1_Channel5_IRQHandler(void)
{
	DMA_IRQ_Handler(DMA_NUM_1 , DMA_CHANNEL_5);
}
/*DMA1 CHANNNEL6 IRQ HANDLER*/
void DMA1_Channel6_IRQHandler(void)
{
	DMA_IRQ_Handler(DMA_NUM_1 , DMA_CHANNEL_6);
}
/*DMA1 CHANNNEL7 IRQ HANDLER*/
void DMA1_Channel7_IRQHandler(void)
{
	DMA_IRQ_Handler(DMA_NUM_1 , DMA_CHANNEL_7);
}
/* -------- DMA2 --------- */
/*DMA2 CHANNNEL1 IRQ HANDLER*/
void DMA2_Channel1_IRQHandler(void)
{
	DMA_IRQ_Handler(DMA_NUM_2 , DMA_CHANNEL_1);
}
/*DMA2 CHANNNEL2 IRQ HANDLER*/
void DMA2_Channel2_IRQHandler(void)
{
	DMA_IRQ_Handler(DMA_NUM_2 , DMA_CHANNEL_2);
}
/*DMA2 CHANNNEL3 IRQ HANDLER*/
void DMA2_Channel3_IRQHandler(void)
{
	DMA_IRQ_Handler(DMA_NUM_2 , DMA_CHANNEL_3);
}
/*DMA2 CHANNNEL4 and CHANNNEL5 IRQ HANDLER*/
void DMA2_Channel4_5_IRQHandler(void)
{
	DMA_IRQ_Handler(DMA_NUM_2 , DMA_CHANNEL_4);
}
/************************************************************************************************************************************/

