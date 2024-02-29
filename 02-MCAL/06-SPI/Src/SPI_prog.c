/********************************************************************************
 ********************************************************************************
 ********************************************************************************
 * @File	:	SPI_prog.c
 * @Author	:	Usef Elbedwehy
 * @Brief	:	Main program body of SPI
 * @layer	:	MCAL
 * @Date	:	29 February 2024
 ********************************************************************************
 ********************************************************************************
 ********************************************************************************
 ********************************************************************************/

/********************************************************************************
 *********************** ### INCLUDE SECTION ### ********************************
 ********************************************************************************/
#include <stdint.h>

#include "ErrType.h"
#include "Stm32F103xx.h"

#include "SPI_prv.h"
#include "SPI_interface.h"
/********************************************************************************/

/********************************************************************************
 ******************* ### GLOBAL VARIABLE SECTION ### ****************************
 ********************************************************************************/
/********************************************************************************/
static SPI_Reg_t* SPIx[SPI_PERIPH_NUMBER] = {SPI1 , SPI2 , SPI3 };

static void (*G_pvCallBackFunc[SPI_PERIPH_NUMBER][FLAGS_NUMBER])(void) = { NULL };

static uint16_t* G_ReceivedData[SPI_PERIPH_NUMBER] = {NULL};
/********************************************************************************/

/********************************************************************************
 *************** ### FUNCTION IMPLEMENTATION SECTION ### ************************
 ********************************************************************************/

/********************************************************************************/

/*
 * @fn:		SPI_Init
 * @brief: function to initialize the SPI peripheral with passed configurations
 * @param: Init 				pointer to (STRUCT: @SPI_Config_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_Init(const SPI_Config_t* Init)
{

	ErrorState_t Local_ErrorState = OK;

	if((Init == NULL))
	{
		Local_ErrorState = NULL_POINTER;
		return Local_ErrorState;
	}
	if((Init->SPI_BAUD_RATE <= SPI_FpclkBy256) && (Init->SPI_BAUD_RATE >= SPI_FpclkBy2)
			&& (Init->SPI_NUM <= SPI_NUM3) && (Init->SPI_NUM >= SPI_NUM1)
			&& (Init->SPI_DATA_FRAME <= _16_DATAFRAME) && (Init->SPI_DATA_FRAME >= _8_DATAFRAME)
			&& (Init->SPI_SM_MODE <= SPI_SW_SM) && (Init->SPI_SM_MODE >= SPI_HW_SM)
			&& (Init->SPI_MODE <= SPI_SIMPLEX_TX_MODE) && (Init->SPI_MODE >= SPI_FULL_DUPLEX_MODE)
			&& (Init->SPI_FRAME_FORMAT <= SPI_LSB) && (Init->SPI_FRAME_FORMAT >= SPI_MSB)
			&& (Init->SPI_INT_STATE <= SPI_INT_ENABLED) && (Init->SPI_INT_STATE >= SPI_INT_DISABLED)
			&& (Init->SPI_CLOCK_PORITY <= SPI_CK_1_IDLE) && (Init->SPI_CLOCK_PORITY >= SPI_CK_0_IDLE)
			&& (Init->SPI_CLOCK_PHASE <= SPI_SECOND_CLK_TRANSITION) && (Init->SPI_CLOCK_PHASE >= SPI_FIRST_CLK_TRANSITION)
			&& (Init->SPI_CRC_STATUS <= SPI_CRC_ENABLED) && (Init->SPI_CRC_STATUS >= SPI_CRC_DISABLED)
			&& (Init->SPI_MASTER_SLAVE_MODE <= SPI_MASTER) && (Init->SPI_MASTER_SLAVE_MODE >= SPI_SLAVE)
			&& (Init->SPI_SS_OUTPUT_MODE <= SPI_SS_ENABLED) && (Init->SPI_SS_OUTPUT_MODE >= SPI_SS_DISABLED) )
	{

		/*if Master: Set BaudRate*/
		if(Init->SPI_MASTER_SLAVE_MODE == SPI_MASTER)
		{
			SPIx[Init->SPI_NUM]->SPI_CR1 |= ( Init->SPI_BAUD_RATE << CR1_BR0 );
		}
		/*SPI MODE*/
		switch(Init->SPI_MODE)
		{
		case SPI_FULL_DUPLEX_MODE:
			/* 2-line unidirectional data mode selected */
			SPIx[Init->SPI_NUM]->SPI_CR1 &=~ ( SET_MASK << CR1_BIDIMODE );
			/*FULL DUPLEX*/
			SPIx[Init->SPI_NUM]->SPI_CR1 &=~ ( SET_MASK << CR1_RXONLY );
			break;
		case SPI_HALF_DUPLEX_RX_MODE:
			/* 1-line bidirectional data mode selected */
			SPIx[Init->SPI_NUM]->SPI_CR1 |= ( SET_MASK << CR1_BIDIMODE );
			/*RX MODE*/
			SPIx[Init->SPI_NUM]->SPI_CR1 &=~ ( SET_MASK << CR1_BIDIOE );
			break;
		case SPI_HALF_DUPLEX_TX_MODE:
			/* 1-line bidirectional data mode selected */
			SPIx[Init->SPI_NUM]->SPI_CR1 |= ( SET_MASK << CR1_BIDIMODE );
			/*TX MODE*/
			SPIx[Init->SPI_NUM]->SPI_CR1 |= ( SET_MASK << CR1_BIDIOE );
			break;
		case SPI_SIMPLEX_RX_MODE:
			/* 2-line unidirectional data mode selected */
			SPIx[Init->SPI_NUM]->SPI_CR1 &=~ ( SET_MASK << CR1_BIDIMODE );
			SPIx[Init->SPI_NUM]->SPI_CR1 |= ( SET_MASK << CR1_RXONLY );

			break;
		case SPI_SIMPLEX_TX_MODE:
			/* 2-line unidirectional data mode selected */
			SPIx[Init->SPI_NUM]->SPI_CR1 &=~ ( SET_MASK << CR1_BIDIMODE );
			SPIx[Init->SPI_NUM]->SPI_CR1 &=~ ( SET_MASK << CR1_RXONLY );
			break;
		default :
			Local_ErrorState = NOK;
			break;
		}

		/*DATA FRAME*/
		SPIx[Init->SPI_NUM]->SPI_CR1 |= ( Init->SPI_DATA_FRAME << CR1_DFF );
		/*Set CPOL and CPHA*/
		SPIx[Init->SPI_NUM]->SPI_CR1 |= ( Init->SPI_CLOCK_PORITY << CR1_CPOL );
		SPIx[Init->SPI_NUM]->SPI_CR1 |= ( Init->SPI_CLOCK_PHASE << CR1_CPHA );
		/*FRAME FORMATE: MSB or LSB*/
		SPIx[Init->SPI_NUM]->SPI_CR1 |= ( Init->SPI_FRAME_FORMAT << CR1_LSBFIRST );
		if(Init->SPI_MASTER_SLAVE_MODE == SPI_SLAVE)
		{
			/*HW or SW slave management*/
			if(Init->SPI_SM_MODE == SPI_SW_SM)
			{
				/*Enable software slave management*/
				/*SW: SSM = 1*/
				SPIx[Init->SPI_NUM]->SPI_CR1 |= ( SET_MASK << CR1_SSM );
			}
			else if(Init->SPI_SM_MODE == SPI_HW_SM)
			{
				/*Disable software slave management*/
				/*HW: SSM = 0*/
				SPIx[Init->SPI_NUM]->SPI_CR1 &=~ ( SET_MASK << CR1_SSM );
				/*SS pin Output mode: Enabled or disabled*/
				SPIx[Init->SPI_NUM]->SPI_CR2 |= ( Init->SPI_SS_OUTPUT_MODE << CR2_SSOE );
			}
		}
		/*Set Master or slave*/
		SPIx[Init->SPI_NUM]->SPI_CR1 |= ( Init->SPI_MASTER_SLAVE_MODE << CR1_MSTR );
		/*SPI Enable*/
		SPIx[Init->SPI_NUM]->SPI_CR1 |= ( SET_MASK << CR1_SPE );
	}
	else
	{
		Local_ErrorState = NOK;
	}

	return Local_ErrorState;
}

/*
 * @fn:		SPI_GetFlag
 * @brief: function to get the flag status
 * @param: SPI_Number 				(ENUM: @SPI_Num_t)
 * @param: FlagID 				(ENUM: @SPI_FlagID_t)
 * @param: FlagStatus 				pointer to (uint8_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_GetFlag(SPI_Num_t SPI_Number ,SPI_FlagID_t FlagID,uint8_t* FlagStatus )
{

	ErrorState_t Local_ErrorState = OK;

	if(FlagStatus == NULL)
	{
		Local_ErrorState = NULL_POINTER;
		return Local_ErrorState;
	}
	if( (SPI_Number >= SPI_NUM1) && (SPI_Number <= SPI_NUM3)
			&& (FlagID >= SPI_RxBUFFER_NOT_EMPTY_FLAG_ID) && (FlagID <= BUSY_FLAG_ID))
	{
		*FlagStatus = ( (SPIx[SPI_Number]->SPI_SR >> FlagID) & GET_MASK );
	}
	else
	{
		Local_ErrorState = NOK;
	}

	return Local_ErrorState;
}

/*
 * @fn:		SPI_Enable_DMA
 * @brief: function to enable the DMA line
 * @param: SPI_Number 				(ENUM: @SPI_Num_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_Enable_DMA(SPI_Num_t SPI_Number)
{
	ErrorState_t Local_ErrorState = OK;

	if((SPI_Number >= SPI_NUM1) && (SPI_Number <= SPI_NUM3))
	{
		/*Enable DMA transmitter line*/
		SPIx[SPI_Number]->SPI_CR2 |= (SET_MASK << CR2_TXDMAEN);
		/*Enable DMA receiver line*/
		SPIx[SPI_Number]->SPI_CR2 |= (SET_MASK << CR2_RXDMAEN);
	}
	else
	{
		Local_ErrorState = NOK;
	}

	return Local_ErrorState;
}

/*
 * @fn:		SPI_Disable_DMA
 * @brief: function to Disable the DMA line
 * @param: SPI_Number 				(ENUM: @SPI_Num_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_Disable_DMA(SPI_Num_t SPI_Number)
{
	ErrorState_t Local_ErrorState = OK;

	if((SPI_Number >= SPI_NUM1) && (SPI_Number <= SPI_NUM3))
	{
		/*Disable DMA transmitter line*/
		SPIx[SPI_Number]->SPI_CR2 &=~ (SET_MASK << CR2_TXDMAEN);
		/*Disable DMA receiver line*/
		SPIx[SPI_Number]->SPI_CR2 &=~ (SET_MASK << CR2_RXDMAEN);
	}
	else
	{
		Local_ErrorState = NOK;
	}

	return Local_ErrorState;
}

/*
 * @fn: SPI_Transceive
 * @brief:
 * @param: Init 				pointer to (STRUCT: @SPI_Config_t)
 * @param: TrasmitData			uint16_t
 * @param: ReceivedData			pointer to (uint16_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_Transceive(const SPI_Config_t* Init ,uint16_t TrasmitData ,uint16_t* ReceivedData)
{
	ErrorState_t Local_ErrorState = OK;

	uint8_t		Local_FlagStatus = NOT_READY_FLAG;

	if(ReceivedData == NULL)
	{
		Local_ErrorState = NULL_POINTER;
	}
	else
	{
		SPI_GetFlag(Init->SPI_NUM, SPI_TxBUFFER_EMPTY_FLAG_ID, &Local_FlagStatus);
		/*wait until Transmit buffer empty*/
		while(Local_FlagStatus != READY_FLAG)
		{
			SPI_GetFlag(Init->SPI_NUM, SPI_TxBUFFER_EMPTY_FLAG_ID, &Local_FlagStatus);
		}
		/*transmit Data*/
		SPIx[Init->SPI_NUM]->SPI_DR = TrasmitData;

		Local_FlagStatus = NOT_READY_FLAG;
		SPI_GetFlag(Init->SPI_NUM, SPI_RxBUFFER_NOT_EMPTY_FLAG_ID, &Local_FlagStatus);
		/*wait until Receive buffer not empty*/
		while(Local_FlagStatus != READY_FLAG)
		{
			SPI_GetFlag(Init->SPI_NUM, SPI_RxBUFFER_NOT_EMPTY_FLAG_ID, &Local_FlagStatus);
		}
		/*receive Data*/
		*ReceivedData = SPIx[Init->SPI_NUM]->SPI_DR;

	}
	return Local_ErrorState;
}

/*
 * @fn:		SPI_SetCallBack
 * @brief: function to set the callback function
 * @param: SPI_Number 				(ENUM: @SPI_Num_t)
 * @param: FlagID 				(ENUM: @SPI_FlagID_t)
 * @param: pvCallBack 				pointer to void function
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_SetCallBack(SPI_Num_t SPI_Number ,SPI_FlagID_t FlagID,void (*pvCallBack)(void))
{

	ErrorState_t Local_ErrorState = OK;

	if(pvCallBack == NULL)
	{
		Local_ErrorState = NULL_POINTER;
	}
	else
	{
		G_pvCallBackFunc[SPI_Number][FlagID] = pvCallBack;
	}

	return Local_ErrorState;
}

/*
 * @fn:		SPI_Enable_IT
 * @brief: function to set the callback function
 * @param: Init 				pointer to (STRUCT: @SPI_Config_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_Enable_IT(const SPI_Config_t* Init)
{
	ErrorState_t Local_ErrorState = OK;

	if(Init == NULL)
	{
		Local_ErrorState = NULL_POINTER;
	}
	else
	{
		/*Set the Tx buffer empty interrupt enable*/
		SPIx[Init->SPI_NUM]->SPI_CR2 &=~ ( (Init->SPI_Int_ENABLE_STATUS.TXEIE) << CR2_TXEIE );
		SPIx[Init->SPI_NUM]->SPI_CR2 |= ( (Init->SPI_Int_ENABLE_STATUS.TXEIE) << CR2_TXEIE );

		/*Set the RX buffer not empty interrupt enable*/
		SPIx[Init->SPI_NUM]->SPI_CR2 &=~ ( (Init->SPI_Int_ENABLE_STATUS.RXNEIE) << CR2_RXNEIE );
		SPIx[Init->SPI_NUM]->SPI_CR2 |= ( (Init->SPI_Int_ENABLE_STATUS.RXNEIE) << CR2_RXNEIE );

		/*Set the Error interrupt enable*/
		SPIx[Init->SPI_NUM]->SPI_CR2 &=~ ( (Init->SPI_Int_ENABLE_STATUS.ERRIE) << CR2_ERRIE );
		SPIx[Init->SPI_NUM]->SPI_CR2 |= ( (Init->SPI_Int_ENABLE_STATUS.ERRIE) << CR2_ERRIE );

	}

	return Local_ErrorState;
}

/*
 *@fn:	SPI_Transceive_IT
 *@brief:
 * @param: Init 				pointer to (STRUCT: @SPI_Config_t)
 * @param: TrasmitData			pointer to uint16_t
 * @param: ReceivedData			pointer to (uint16_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_Transceive_IT(const SPI_Config_t* Init ,uint16_t* TrasmitData ,uint16_t* ReceivedData)
{
	ErrorState_t Local_ErrorState = OK;

	if((Init == NULL))
	{
		Local_ErrorState = NULL_POINTER;
	}
	else
	{

		if(ReceivedData != NULL)
		{

			/*Set the receive variable Globally*/
			G_ReceivedData[Init->SPI_NUM] = ReceivedData;
			/*set call function of Rx Globally*/
			G_pvCallBackFunc[Init->SPI_NUM][SPI_RxBUFFER_NOT_EMPTY_FLAG_ID] = Init->pvRxFunc;
			/*Master Initiate the communication by sending data while slave start when received data*/
			if(Init->SPI_MASTER_SLAVE_MODE == SPI_MASTER)
			{
				/*Send Garbage to initiate the communication*/
				SPIx[Init->SPI_NUM]->SPI_DR = GARBAGE_DATA;
				/*enable RX buffer not empty interrupt*/
				SPIx[Init->SPI_NUM]->SPI_CR2 |= (SET_MASK << CR2_RXNEIE);
			}
			else if(Init->SPI_MASTER_SLAVE_MODE == SPI_SLAVE)
			{
				/*enable RX buffer not empty interrupt*/
				SPIx[Init->SPI_NUM]->SPI_CR2 |= (SET_MASK << CR2_RXNEIE);
			}
		}
		if(TrasmitData != NULL)
		{
			uint8_t L_FlagStatus = NOT_READY_FLAG;
			/*wait till Transmit buffer empty*/
			SPI_GetFlag(Init->SPI_NUM, SPI_TxBUFFER_EMPTY_FLAG_ID, &L_FlagStatus);
			while(L_FlagStatus != READY_FLAG){
				SPI_GetFlag(Init->SPI_NUM, SPI_TxBUFFER_EMPTY_FLAG_ID, &L_FlagStatus);
			}
			/*set call function of Tx*/
			G_pvCallBackFunc[Init->SPI_NUM][SPI_TxBUFFER_EMPTY_FLAG_ID] = Init->pvTxFunc;
			/*Send data*/
			SPIx[Init->SPI_NUM]->SPI_DR = *TrasmitData;
			/*enable Tx buffer empty interrupt*/
			SPIx[Init->SPI_NUM]->SPI_CR2 |= (SET_MASK << CR2_TXEIE);
		}

	}

	return Local_ErrorState;
}

/*
 * @fn: SPI_IRQ_Handler
 * @brief: handle the IRQs
 * @param: SPI_Number  (ENUM: @SPI_Num_t)
 * @retval: void
 *
 * */
void SPI_IRQ_Handler(SPI_Num_t SPI_Number)
{
	uint8_t L_FlagStatus = NOT_READY_FLAG;
	SPI_GetFlag(SPI_Number, SPI_TxBUFFER_EMPTY_FLAG_ID, &L_FlagStatus);
	if(L_FlagStatus == READY_FLAG)
	{
		if(G_ReceivedData != NULL)
		{
			*G_ReceivedData[SPI_Number] = SPIx[SPI_Number]->SPI_DR;
		}
		/*Callback*/
		G_pvCallBackFunc[SPI_Number][SPI_TxBUFFER_EMPTY_FLAG_ID]();
	}

	L_FlagStatus = NOT_READY_FLAG;
	SPI_GetFlag(SPI_Number, SPI_RxBUFFER_NOT_EMPTY_FLAG_ID, &L_FlagStatus);
	if(L_FlagStatus == READY_FLAG)
	{

		/*Callback*/
		G_pvCallBackFunc[SPI_Number][SPI_RxBUFFER_NOT_EMPTY_FLAG_ID]();
	}
	/*Disable  Rx Buffer Not Empty Interrupt */
	SPIx[SPI_Number]->SPI_CR2 &=~ (SET_MASK << CR2_RXNEIE);
	/* Disable  Tx Buffer Not Empty Interrupt */
	SPIx[SPI_Number]->SPI_CR2 &=~ (SET_MASK << CR2_TXEIE);

}

/********************************************************************************/

/********************************************************************************
 ****************** ### INTERRUPT HANDLER SECTION ### ***************************
 ********************************************************************************/

/*SPI1 interrupt handler*/
void SPI1_IRQHandler(void)
{
	SPI_IRQ_Handler(SPI_NUM1);
}

/*SPI2 interrupt handler*/
void SPI2_IRQHandler(void)
{
	SPI_IRQ_Handler(SPI_NUM2);
}

/*SPI3 interrupt handler*/
void SPI3_IRQHandler(void)
{
	SPI_IRQ_Handler(SPI_NUM3);
}

/********************************************************************************/
