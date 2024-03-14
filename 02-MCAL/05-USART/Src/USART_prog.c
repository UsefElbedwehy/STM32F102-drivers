/********************************************************************************
 ********************************************************************************
 ********************************************************************************
 * @File	:	USART_prog.c
 * @Author	:	Usef Elbedwehy
 * @Brief	:	Main program body of USART
 * @layer	:	MCAL
 * @Date	:	19 February 2024
 ********************************************************************************
 ********************************************************************************
 ********************************************************************************
 ********************************************************************************/

/********************************************************************************
 *********************** ### INCLUDE SECTION ### ********************************
 ********************************************************************************/
#include <stdint.h>

#include "Stm32F103xx.h"
#include "ErrType.h"

#include "USART_prv.h"
#include "USART_interface.h"
/********************************************************************************/

/********************************************************************************
 ******************* ### GLOBAL VARIABLE SECTION ### ****************************
 ********************************************************************************/
static USART_Reg_t* USARTx[NUMBER_OF_USART_PERIPH] = {USART1, USART2, USART3, USART4 ,USART5};

static void (*G_pvCallBackFunc[NUMBER_OF_USART_PERIPH][FLAGS_NUMBER])(void) = {NULL};

static uint16_t* Global_u16ReceiveData[NUMBER_OF_USART_PERIPH] = {NULL};

/********************************************************************************/

/********************************************************************************
 *************** ### FUNCTION IMPLEMENTATION SECTION ### ************************
 ********************************************************************************/

/*
 * @fn:		USART_Init
 * @brief:
 * @param:	Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_Init(const USART_ConfigReg_t* Copy_InitConfig)
{

	float USART_DIV = 0;

	uint32_t DIV_Fraction = 0;

	ErrorState_t Local_ErrorState = OK;

	if(Copy_InitConfig == NULL)
	{
		/*Null Pointer*/
		Local_ErrorState = NULL_POINTER;
		return Local_ErrorState;
	}

	/*Check the configurations*/
	if( ( Copy_InitConfig->USART_MODE <= USART_RXTX )
			&& ( Copy_InitConfig->USART_MODE >= USART_RX )
			&& ( Copy_InitConfig->USART_STOPBITS <= _1P5_STOP_BIT )
			&& ( Copy_InitConfig->USART_STOPBITS >= _1_STOP_BIT )
			&& ( Copy_InitConfig->USART_WORDLENGTH <= _9_DATA_BITS )
			&& ( Copy_InitConfig->USART_WORDLENGTH >= _8_DATA_BITS )
			&& ( Copy_InitConfig->USART_PARITYBIT <= PARITY_CONTROL_ENABLE )
			&& ( Copy_InitConfig->USART_PARITYBIT >= PARITY_CONTROL_DISABLE )
			&& ( Copy_InitConfig->USART_HWFLOWCONTROL <= USART_HW_FLOW_CONTROL_OFF )
			&& ( Copy_InitConfig->USART_HWFLOWCONTROL >= USART_HW_FLOW_CONTROL_ON )
			&& ( Copy_InitConfig->USART_USARTNUMBER <= USART_NUM5 )
			&& ( Copy_InitConfig->USART_USARTNUMBER >= USART_NUM1 )
			&& ( Copy_InitConfig->USART_SYNCHMODE <= CLOCK_ENABLE )
			&& ( Copy_InitConfig->USART_SYNCHMODE >= CLOCK_DISABLE ) )
	{

		/*Make sure the register is at reset value*/
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR1  &=~  CR1_REG_MASK;
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR2  &=~  CR2_REG_MASK;
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR3  &=~  CR3_REG_MASK;
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_GTPR &=~  GTP_REG_MASK;



		/*word length*/
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR1 |= ((Copy_InitConfig->USART_WORDLENGTH) << CR1_M);

		/*Stop bits*/
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR2 |= ((Copy_InitConfig->USART_STOPBITS) << CR2_STOP0);

		/*BAUDRATE*/
		USART_DIV = 8000000 / (float)(16U * Copy_InitConfig->USART_BAUDRATE);
		USART_DIV *= 1000UL;
		/* Set the Mantissa Part */
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_BRR |= (((uint32_t)USART_DIV / 1000UL) << BRR_DIV_MANTISSA);
		/* Calculte the Fraction */
		DIV_Fraction = (uint32_t)USART_DIV % 1000UL;
		DIV_Fraction = DIV_Fraction * 16;
		/* get Round */
		DIV_Fraction += 500UL;
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_BRR |= ((uint32_t)(DIV_Fraction / 1000UL) << BRR_DIV_FRACTION);
		/*Mode*/
		switch(Copy_InitConfig->USART_MODE)
		{
		case USART_RX:
			/*RECEIVER ENABLE*/
			USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR1 &=~ (SET_MASK << CR1_TE);
			USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR1 |= (SET_MASK << CR1_RE);
			break;
		case USART_TX:
			/*TRASNMITTER ENABLE*/
			USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR1 &=~ (SET_MASK << CR1_RE);
			USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR1 |= (SET_MASK << CR1_TE);
			break;
		case USART_RXTX:
			/*TRASNMITTER and RECEIVER ENABLE*/
			USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR1 |= (SET_MASK << CR1_RE);
			USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR1 |= (SET_MASK << CR1_TE);
			break;
		default: break;
		}

		/*Parity*/
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR1 |= ((Copy_InitConfig->USART_PARITYBIT) << CR1_PCE);

		/*SYNCHMODE*/
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR2 |= ((Copy_InitConfig->USART_SYNCHMODE) << CR2_CLKEN);

		/*HWFLOWCONTROL*/
		if((Copy_InitConfig->USART_HWFLOWCONTROL) == USART_HW_FLOW_CONTROL_ON)
		{
			/*CTS ENABLE*/
			USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR3 |= (SET_MASK << CR3_CTSE);
			/*RTS ENABLE*/
			USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR3 |= (SET_MASK << CR3_RTSE);
		}
		/*USART enable */
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR1 |= (SET_MASK << CR1_UE);

	}
	else
	{
		Local_ErrorState = NOK;
	}

	return Local_ErrorState;

}

/*WAITING*/

/*
 * @fn:		USART_TransmitData
 * @brief:
 * @param:	Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @param:  Copy_Data				uint8_t
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_TransmitData(const USART_ConfigReg_t* Copy_InitConfig ,uint8_t Copy_Data)
{
	uint8_t Local_FlagVal=0;
	ErrorState_t Local_ErrorState = OK;

	if(Copy_InitConfig != NULL)
	{
		USART_ReadIntFlag(Copy_InitConfig->USART_USARTNUMBER, TRANSMIT_DATA_REG_EMPTY_FLAG_ID, &Local_FlagVal);
		/*Wait Until Transmission Data Register Empty Flag is Set*/
		while(Local_FlagVal != READY_FLAG)
		{
			USART_ReadIntFlag(Copy_InitConfig->USART_USARTNUMBER, TRANSMIT_DATA_REG_EMPTY_FLAG_ID, &Local_FlagVal);
		}


		/*Send data to DR*/
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_DR = Copy_Data;

		Local_FlagVal=0;
		USART_ReadIntFlag(Copy_InitConfig->USART_USARTNUMBER, TRANSMISSION_COMPLETE_FLAG_ID, &Local_FlagVal);
		/*Wait for transfer complete flag is set*/
		while(Local_FlagVal != READY_FLAG)
		{
			USART_ReadIntFlag(Copy_InitConfig->USART_USARTNUMBER, TRANSMISSION_COMPLETE_FLAG_ID, &Local_FlagVal);
		}
		/*Clear transmit complete flag*/
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_SR &=~ (SET_MASK << SR_TC);
	}
	else
	{
		Local_ErrorState = NULL_POINTER;
	}

	return Local_ErrorState;
}

/*
 * @fn		: USART_TransmitString
 * @brief   : Usart transmit string
 * @param	: Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @param	: Copy_Data				  pointer to (char)
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 *
 * */
void USART_TransmitString(const USART_ConfigReg_t* Copy_InitConfig ,char* Copy_Data)
{
	uint8_t Local_counter = 0;
	while(Copy_Data[Local_counter] != '\0')
	{
		USART_TransmitData(Copy_InitConfig , Copy_Data[Local_counter]);
		Local_counter++;
	}

}

/*
 * @fn:		USART_ReceiveData
 * @brief:
 * @param:	Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @param:  Copy_Data			  pointer uint16_t
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_ReceiveData(const USART_ConfigReg_t* Copy_InitConfig ,uint16_t* Copy_Data)
{
	ErrorState_t Local_ErrorState = OK;
	uint8_t	Local_u8FlagVal=0;

	if((Copy_InitConfig != NULL) && (Copy_Data != NULL))
	{
		/*Clear receive data ready to be read flag*/
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_SR &=~ (SET_MASK << SR_RXNE);

		USART_ReadIntFlag(Copy_InitConfig->USART_USARTNUMBER, READ_DATA_REG_NOT_EMPTY_FLAG_ID, &Local_u8FlagVal);
		/*wait till Received data is ready to be read */
		while(Local_u8FlagVal == NOT_READY_FLAG)
		{
			USART_ReadIntFlag(Copy_InitConfig->USART_USARTNUMBER, READ_DATA_REG_NOT_EMPTY_FLAG_ID, &Local_u8FlagVal);
		}
		/*Receive data from DR*/
		*Copy_Data = USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_DR;
	}
	else
	{
		Local_ErrorState = NULL_POINTER;
	}

	return Local_ErrorState;
}

/****** ### DMA ### ******/

/*
 * @fn:		USART_TransmitDataEnable_DMA
 * @brief:
 * @param:	Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_TransmitDataEnable_DMA(const USART_ConfigReg_t* Copy_InitConfig )
{

	ErrorState_t Local_ErrorState = OK;

	if(Copy_InitConfig != NULL)
	{
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_SR &=~ (1<< SR_TC);
		/*Enable DMA transmitter*/
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR3 |= (SET_MASK << CR3_DMAT);
	}
	else
	{
		Local_ErrorState = NULL_POINTER;
	}

	return Local_ErrorState;
}

/*
 * @fn:		USART_ReceiveDataEnable_DMA
 * @brief:
 * @param:	Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_ReceiveDataEnable_DMA(const USART_ConfigReg_t* Copy_InitConfig )
{
	ErrorState_t Local_ErrorState = OK;

	if(Copy_InitConfig != NULL)
	{
		/*Enable DMA receiver*/
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR3 |= (SET_MASK << CR3_DMAR);
	}
	else
	{
		Local_ErrorState = NULL_POINTER;
	}

	return Local_ErrorState;
}

/****** ### INTERRUPT ### ******/

/*
 * @fn:		USART_Transmit_IT
 * @brief: transmit data with interrupt enabled
 * @param:	Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @param:	Copy_Data		  		uint8_t
 * @param:	Copy_pvCallBack		  pointer to void function
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_Transmit_IT(const USART_ConfigReg_t* Copy_InitConfig , uint8_t Copy_Data,void (*Copy_pvCallBack)(void))
{
	ErrorState_t Local_ErrorState = OK;

	if(Copy_pvCallBack != NULL)
	{
		/*Enable Transmit Complete interrupt*/
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR1 |= (SET_MASK << CR1_TCIE);
		/*Set call back function*/
		G_pvCallBackFunc[Copy_InitConfig->USART_USARTNUMBER][TRANSMISSION_COMPLETE_FLAG_ID] = Copy_pvCallBack;
		/*Send data*/
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_DR = Copy_Data;
	}
	else
	{
		Local_ErrorState=NULL_POINTER;
	}

	return Local_ErrorState;
}

/*
 * @fn:		USART_Receive_IT
 * @brief: transmit data with interrupt enabled
 * @param:	Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @param:	Copy_Data		  		pointer to uint16_t
 * @param:	Copy_pvCallBack		  pointer to void function
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_Receive_IT(const USART_ConfigReg_t* Copy_InitConfig , uint16_t* Copy_Data,void (*Copy_pvCallBack)(void))
{
	ErrorState_t Local_ErrorState = OK;

	if(Copy_pvCallBack != NULL)
	{
		/*Set call back function*/
		G_pvCallBackFunc[Copy_InitConfig->USART_USARTNUMBER][READ_DATA_REG_NOT_EMPTY_FLAG_ID] = Copy_pvCallBack;
		/*Receive data*/
		Global_u16ReceiveData[Copy_InitConfig->USART_USARTNUMBER] = Copy_Data;
		/*Enable RXE interrupt*/
		USARTx[Copy_InitConfig->USART_USARTNUMBER]->USART_CR1 |= (SET_MASK << CR1_RXNEIE);
	}
	else
	{
		Local_ErrorState = NULL_POINTER;
	}
	return Local_ErrorState;
}

/*
 * @fn:		USART_SetCallBack
 * @brief: set the callback function
 * @param:	USART_NUM		    (ENUM: @USART_PrephNumber)
 * @param:	FLAG_ID		  		(ENUM: @USART_FlagID_t)
 * @param:	Copy_pvCallBack		  pointer to void function
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_SetCallBack( USART_PrephNumber USART_NUM ,USART_FlagID_t FLAG_ID,void (*Copy_pvCallBack)(void))
{
	ErrorState_t Local_ErrorState = OK;

	if(Copy_pvCallBack != NULL)
	{
		/*Set the callback function*/
		G_pvCallBackFunc[USART_NUM][FLAG_ID] = Copy_pvCallBack;
	}
	else
	{
		Local_ErrorState = NULL_POINTER;
	}

	return Local_ErrorState;
}

/*
 * @fn:		USART_IRQ_Handler
 * @brief: Handle the IRQ interrupt
 * @param:	USART_NUM		    (ENUM: @USART_PrephNumber)
 * @retval:	void
 * */
void USART_IRQ_Handler( USART_PrephNumber USART_NUM)
{
	uint8_t FlagVal=0;
	/*check if Received data is ready to be read flag is set*/
	USART_ReadIntFlag(USART_NUM, READ_DATA_REG_NOT_EMPTY_FLAG_ID, &FlagVal);
	if(FlagVal == READY_FLAG)
	{
		/*read the received data*/
		*Global_u16ReceiveData[USART_NUM] = USARTx[USART_NUM]->USART_DR;

		if(G_pvCallBackFunc[USART_NUM][READ_DATA_REG_NOT_EMPTY_FLAG_ID] != NULL)
		{
			G_pvCallBackFunc[USART_NUM][READ_DATA_REG_NOT_EMPTY_FLAG_ID]();
		}
	}

	/*check if Transmission complete flag is set*/
	FlagVal=0;
	USART_ReadIntFlag(USART_NUM, TRANSMISSION_COMPLETE_FLAG_ID, &FlagVal);
	if(FlagVal == READY_FLAG)
	{
		/*Clear transmit complete flag*/
		USARTx[USART_NUM]->USART_SR &=~ (SET_MASK << SR_TC);
		if(G_pvCallBackFunc[USART_NUM][TRANSMISSION_COMPLETE_FLAG_ID] != NULL)
		{
			G_pvCallBackFunc[USART_NUM][TRANSMISSION_COMPLETE_FLAG_ID]();
		}
	}

}



/*
 * @fn:		USART_ReadIntFlag
 * @brief:
 * @param:	Copy_USARTNumber		(ENUM: @USART_PrephNumber)
 * @param:	Copy_ITFlagID			(ENUM: @USART_FlagID_t)
 * @param:	Copy_u8ITFlagValue		uint8_t pointer to save the flag value
 * @retval:	Local_ErrorState		(ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_ReadIntFlag(USART_PrephNumber Copy_USARTNumber ,USART_FlagID_t Copy_ITFlagID ,uint8_t* Copy_u8ITFlagValue)
{

	ErrorState_t Local_ErrorState = OK;

	if(Copy_u8ITFlagValue == NULL)
	{
		Local_ErrorState = NULL_POINTER;
		return Local_ErrorState;
	}
	else
	{
		/*GET BIT VALUE*/
		*Copy_u8ITFlagValue = ( ( (USARTx[Copy_USARTNumber]->USART_SR) >> Copy_ITFlagID ) & READ_VAL_MASK );

	}

	return Local_ErrorState;
}
/********************************************************************************/


/********************************************************************************
 ****************** ### INTERRUPT HANDLER SECTION ### ***************************
 ********************************************************************************/

/*USART1 INTERRUPT HANDLER*/
void USART1_IRQHandler(void)
{
	USART_IRQ_Handler(USART_NUM1);
}
/*USART2 INTERRUPT HANDLER*/
void USART2_IRQHandler(void)
{
	USART_IRQ_Handler(USART_NUM2);
}
/*USART3 INTERRUPT HANDLER*/
void USART3_IRQHandler(void)
{
	USART_IRQ_Handler(USART_NUM3);
}
/*USART4 INTERRUPT HANDLER*/
void UART4_IRQHandler(void)
{
	USART_IRQ_Handler(USART_NUM4);
}
/*USART5 INTERRUPT HANDLER*/
void UART5_IRQHandler(void)
{
	USART_IRQ_Handler(USART_NUM5);
}
/********************************************************************************/
