#ifndef		SPI_INTERFACE_H_
#define		SPI_INTERFACE_H_

/********************************************************************************
 ************************ ### FLAGS ENUM SECTION ### ****************************
 ********************************************************************************/
/*	SPI Flag ID
 * @SPI_FlagID_t
 * */
typedef enum{

	SPI_RxBUFFER_NOT_EMPTY_FLAG_ID,
	SPI_TxBUFFER_EMPTY_FLAG_ID,
	CHANNEL_SIDE_FLAG_ID,
	UNDERRUN_FLAG_ID,
	CRC_ERROR_FLAG_ID,
	MODE_FAULT_FLAG_ID,
	OVERRUN_FLAG_ID,
	BUSY_FLAG_ID,
	FLAGS_NUMBER

}SPI_FlagID_t;


/*	states of RXEIE
 * @SPI_Rx_Int_t
 * */
typedef enum{

	RX_INT_DISABLE,
	RX_INT_ENABLE

}SPI_Rx_Int_t;


/*	states of TXEIE
 * @SPI_Tx_Int_t
 * */
typedef enum{

	TX_INT_DISABLE,
	TX_INT_ENABLE

}SPI_Tx_Int_t;


/*	states of ERRIE
 * @SPI_Error_Int_t
 * */
typedef enum{

	ERROR_INT_DISABLE,
	ERROR_INT_ENABLE

}SPI_Error_Int_t;

/*	states of INT
 * @SPI_IntEnStatus_t
 * */
typedef struct{

	SPI_Rx_Int_t		TXEIE;
	SPI_Tx_Int_t		RXNEIE;
	SPI_Error_Int_t		ERRIE;

}SPI_IntEnStatus_t;
/********************************************************************************/

/********************************************************************************
 ****************** ### REGISTER BITS ENUMS SECTION ### *************************
 ********************************************************************************/
/*
 * SPI control register 1 (SPI_CR1)
 * @SPI_CR1_t
 * */
typedef enum{

	CR1_CPHA,
	CR1_CPOL,
	CR1_MSTR,
	CR1_BR0=3,
	CR1_SPE=6,
	CR1_LSBFIRST,
	CR1_SSI,
	CR1_SSM,
	CR1_RXONLY,
	CR1_DFF,
	CR1_CRCNEXT,
	CR1_CRCEN,
	CR1_BIDIOE,
	CR1_BIDIMODE

}SPI_CR1_t;

/*
 * SPI control register 2 (SPI_CR2)
 * @SPI_CR2_t
 * */
typedef enum{

	CR2_RXDMAEN,
	CR2_TXDMAEN,
	CR2_SSOE=2,
	CR2_ERRIE=5,
	CR2_RXNEIE,
	CR2_TXEIE,

}SPI_CR2_t;

/*
 * SPI status register (SPI_SR)
 * @SPI_SR_t
 * */
typedef enum{

	SR_RXNE,
	SR_TXE,
	SR_CHSIDE,
	SR_UDR,
	SR_CRCERR,
	SR_MODF,
	SR_OVR,
	SR_BSY

}SPI_SR_t;

/*
 * SPI data register (SPI_DR)
 * @SPI_DR_t
 * */
typedef enum{

	SPI_DR

}SPI_DR_t;

/*
 * SPI CRC polynomial register (SPI_CRCPR)
 * @SPI_CRCPR_t
 * */
typedef enum{

	SPI_CRCPOLY

}SPI_CRCPR_t;

/*
 * SPI RX CRC register (SPI_RXCRCR)
 * @SPI_RXCRCR_t
 * */
typedef enum{

	SPI_RXCRC

}SPI_RXCRCR_t;

/*
 * SPI TX CRC register (SPI_TXCRCR)
 * @SPI_TXCRCR_t
 * */
typedef enum{

	SPI_TXCRC

}SPI_TXCRCR_t;

/********************************************************************************/
/********************************************************************************
 ****************** ### CONFIGURATION STRUCT SECTION ### *************************
 ********************************************************************************/
/*
 * SPI Peripheral numbers
 * @SPI_Num_t
 * */
typedef enum{

	SPI_NUM1,
	SPI_NUM2,
	SPI_NUM3

}SPI_Num_t;

/*
 * Bit 11 DFF: Data frame format
 * @SPI_DataFrame_t
 * */
typedef enum{

	_8_DATAFRAME,		/*8-bit data frame format is selected for transmission/reception*/
	_16_DATAFRAME		/*16-bit data frame format is selected for transmission/reception*/

}SPI_DataFrame_t;

/*
 * SPI mode
 * @SPI_Mode_t
 * */
typedef enum{

	SPI_FULL_DUPLEX_MODE,				/*Transmit and receive*/
	SPI_HALF_DUPLEX_RX_MODE,				/*Receive-only mode*/
	SPI_HALF_DUPLEX_TX_MODE,				/*transmit-only mode*/
	SPI_SIMPLEX_RX_MODE,
	SPI_SIMPLEX_TX_MODE

}SPI_Mode_t;

typedef enum{

	SPI_HW_SM,
	SPI_SW_SM

}SPI_SM_Mode_t;

typedef enum{

	SPI_MSB,
	SPI_LSB

}SPI_FrameFormat_t;

typedef enum{

	SPI_FpclkBy2,
	SPI_FpclkBy4,
	SPI_FpclkBy8,
	SPI_FpclkBy16,
	SPI_FpclkBy32,
	SPI_FpclkBy64,
	SPI_FpclkBy128,
	SPI_FpclkBy256

}SPI_BaudRate_t;

typedef enum{

	SPI_INT_DISABLED,
	SPI_INT_ENABLED

}SPI_InterruptState_t;

typedef enum{

	SPI_CK_0_IDLE,
	SPI_CK_1_IDLE

}SPI_ClkPority_t;

typedef enum{

	SPI_FIRST_CLK_TRANSITION,
	SPI_SECOND_CLK_TRANSITION

}SPI_ClkPhase_t;


typedef enum{

	SPI_CRC_DISABLED,
	SPI_CRC_ENABLED

}SPI_CRC_Status_t;

typedef enum{

	SPI_SLAVE,
	SPI_MASTER

}SPI_MasterSlaveMode;

typedef enum{

	SPI_SS_DISABLED,
	SPI_SS_ENABLED

}SPI_SS_OutputEn_t;
/********************************************************************************/

/********************************************************************************
 ****************** ### CONFIGURATION STRUCT SECTION ### *************************
 ********************************************************************************/
typedef struct{

	SPI_Num_t				SPI_NUM;
	SPI_DataFrame_t			SPI_DATA_FRAME;
	SPI_SM_Mode_t  	 		SPI_SM_MODE;
	SPI_Mode_t				SPI_MODE;
	SPI_FrameFormat_t 		SPI_FRAME_FORMAT;
	SPI_BaudRate_t			SPI_BAUD_RATE;
	SPI_InterruptState_t	SPI_INT_STATE;
	SPI_ClkPority_t			SPI_CLOCK_PORITY;
	SPI_ClkPhase_t			SPI_CLOCK_PHASE;
	SPI_CRC_Status_t		SPI_CRC_STATUS;
	SPI_MasterSlaveMode		SPI_MASTER_SLAVE_MODE;
	SPI_SS_OutputEn_t		SPI_SS_OUTPUT_MODE;
	SPI_IntEnStatus_t		SPI_Int_ENABLE_STATUS;
	void (*pvTxFunc)(void);
	void (*pvRxFunc)(void);

}SPI_Config_t;
/********************************************************************************/
/*
 * @fn:		SPI_Init
 * @brief: function to initialize the SPI peripheral with passed configurations
 * @param: Init 				pointer to (STRUCT: @SPI_Config_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_Init(const SPI_Config_t* Init);
/*
 * @fn:		SPI_GetFlag
 * @brief: function to get the flag status
 * @param: SPI_Number 				(ENUM: @SPI_Num_t)
 * @param: FlagID 				(ENUM: @SPI_FlagID_t)
 * @param: FlagStatus 				pointer to (uint8_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_GetFlag(SPI_Num_t SPI_Number ,SPI_FlagID_t FlagID,uint8_t* FlagStatus );

/*
 * @fn:		SPI_EnableTransmit_DMA
 * @brief: function to enable the DMA transmit line
 * @param: SPI_Number 				(ENUM: @SPI_Num_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_EnableTransmit_DMA(SPI_Num_t SPI_Number);

/*
 * @fn:		SPI_EnableReceive_DMA
 * @brief: function to enable the DMA receive line
 * @param: SPI_Number 				(ENUM: @SPI_Num_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_EnableReceive_DMA(SPI_Num_t SPI_Number);

/*
 * @fn:		SPI_DisableTransmit_DMA
 * @brief: function to Disable the DMA Transmit line
 * @param: SPI_Number 				(ENUM: @SPI_Num_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_DisableTransmit_DMA(SPI_Num_t SPI_Number);

/*
 * @fn:		SPI_DisableReceive_DMA
 * @brief: function to Disable the DMA Receive line
 * @param: SPI_Number 				(ENUM: @SPI_Num_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_DisableReceive_DMA(SPI_Num_t SPI_Number);

/*
 * @fn: SPI_Receive
 * @brief: receive data
 * @param: Init 				pointer to (STRUCT: @SPI_Config_t)
 * @param: ReceivedData			pointer to (uint16_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_Receive(const SPI_Config_t* Init ,uint16_t* ReceivedData);

/*
 * @fn: SPI_Transmit
 * @brief: transmit data
 * @param: Init 				pointer to (STRUCT: @SPI_Config_t)
 * @param: TrasmitData			uint16_t
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_Transmit(const SPI_Config_t* Init ,uint16_t TrasmitData );

/*
 * @fn: SPI_Transceive
 * @brief:
 * @param: Init 				pointer to (STRUCT: @SPI_Config_t)
 * @param: TrasmitData			uint16_t
 * @param: ReceivedData			pointer to (uint16_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_Transceive(const SPI_Config_t* Init ,uint16_t TrasmitData ,uint16_t* ReceivedData);

/*
 * @fn:		SPI_Enable_IT
 * @brief: function to set the callback function
 * @param: Init 				pointer to (STRUCT: @SPI_Config_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_Enable_IT(const SPI_Config_t* Init);

/*
 *@fn:	SPI_Transmit_IT with interrupt
 *@brief: to transmit data
 * @param: Init 				pointer to (STRUCT: @SPI_Config_t)
 * @param: TrasmitData			pointer to uint16_t
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_Transmit_IT(const SPI_Config_t* Init ,uint16_t TrasmitData );

/*
 *@fn:	SPI_Receive_IT
 *@brief: to receive data with interrupt
 * @param: TrasmitData			pointer to uint16_t
 * @param: ReceivedData			pointer to (uint16_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_Receive_IT(const SPI_Config_t* Init ,uint16_t* ReceivedData);

/*
 *@fn:	SPI_Transceive_IT
 *@brief:
 * @param: Init 				pointer to (STRUCT: @SPI_Config_t)
 * @param: TrasmitData			pointer to uint16_t
 * @param: ReceivedData			pointer to (uint16_t)
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_Transceive_IT(const SPI_Config_t* Init ,uint16_t* TrasmitData ,uint16_t* ReceivedData);

/*
 * @fn:		SPI_SetCallBack
 * @brief: function to set the callback function
 * @param: SPI_Number 				(ENUM: @SPI_Num_t)
 * @param: FlagID 				(ENUM: @SPI_FlagID_t)
 * @param: pvCallBack 				pointer to void function
 * @retval: Local_ErrorState	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SPI_SetCallBack(SPI_Num_t SPI_Number ,SPI_FlagID_t FlagID,void (*pvCallBack)(void));

/*
 * @fn: SPI_IRQ_Handler
 * @brief: handle the IRQs
 * @param: SPI_Number  (ENUM: @SPI_Num_t)
 * @retval: void
 *
 * */
void SPI_IRQ_Handler(SPI_Num_t SPI_Number);

#endif
