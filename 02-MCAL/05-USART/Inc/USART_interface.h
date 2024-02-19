#ifndef   USART_INTERFACE_H_
#define   USART_INTERFACE_H_

/********************************************************************************
 ************************ ### FLAGS ENUM SECTION ### ****************************
 ********************************************************************************/
/*	number of USART Peripherals
 * @USART_PrephNumber
 * */
typedef enum{

	USART_NUM1,
	USART_NUM2,
	USART_NUM3,
	USART_NUM4,
	USART_NUM5

}USART_PrephNumber;
/********************************************************************************/
/********************************************************************************
 ************************ ### FLAGS ENUM SECTION ### ****************************
 ********************************************************************************/
/*
 * Interrupts Flag ID
 * @USART_FlagID_t
 * */
typedef enum{

	PARITY_ERROR_FLAG_ID,
	FRAMING_ERROR_FLAG_ID,
	NOISE_ERROR_FLAG_ID,
	OVERRUN_ERROR_FLAG_ID,
	IDLE_LINE_DETECTED_FLAG_ID,
	READ_DATA_REG_NOT_EMPTY_FLAG_ID,
	TRANSMISSION_COMPLETE_FLAG_ID,
	TRANSMIT_DATA_REG_EMPTY_FLAG_ID,
	LIN_BREAK_DETECTION_FLAG_ID,
	CTS__FLAG_ID

}USART_FlagID_t;
/********************************************************************************/

/********************************************************************************
 ****************** ### REGISTER BITS ENUMS SECTION ### *************************
 ********************************************************************************/
/*
 * Status register
 * @USART_SR_t
 * */
typedef enum{

	SR_PE,
	SR_FE,
	SR_NE,
	SR_ORE,
	SR_IDLE,
	SR_RXNE,
	SR_TC,
	SR_TXE,
	SR_LBD,
	SR_CTS

}USART_SR_t;

/*
 * Data register (USART_DR)
 * @USART_DR_t
 * */
typedef enum{

	DR_DR0

}USART_DR_t;

/*
 * Baud rate register (USART_BRR)
 * @USART_BRR_t
 * */
typedef enum{

	BRR_DIV_FRACTION=0,
	BRR_DIV_MANTISSA=4

}USART_BRR_t;

/*
 * Control register 1 (USART_CR1)
 * @USART_CR1_t
 * */
typedef enum{

	CR1_SBK,
	CR1_RWU,
	CR1_RE,
	CR1_TE,
	CR1_IDLEIE,
	CR1_RXNEIE,
	CR1_TCIE,
	CR1_TXEIE,
	CR1_PEIE,
	CR1_PS,
	CR1_PCE,
	CR1_WAKE,
	CR1_M,
	CR1_UE

}USART_CR1_t;

/*
 * Control register 2 (USART_CR1)
 * @USART_CR2_t
 * */
typedef enum{

	CR2_ADD0=0,			/*Bits 3:0 ADD[3:0]: Address of the USART node*/
	CR2_LBDL=5,
	CR2_LBDIE,
	CR2_LBCL=8,
	CR2_CPHA,
	CR2_CPOL,
	CR2_CLKEN,
	CR2_STOP0=12,		/*Bits 13:12 STOP: STOP bits*/
	CR2_LINEN=14

}USART_CR2_t;

/*
 * Control register 3 (USART_CR1)
 * @USART_CR3_t
 * */
typedef enum{

	CR3_EIE=0,
	CR3_IREN,
	CR3_IRLP,
	CR3_HDSEL,
	CR3_NACK,
	CR3_SCEN,
	CR3_DMAR,
	CR3_DMAT,
	CR3_RTSE,
	CR3_CTSE,
	CR3_CTSIE

}USART_CR3_t;
/********************************************************************************/

/********************************************************************************
 ********************** ### STATUS ENUMS SECTION ### ****************************
 ********************************************************************************/
/*IN Status register (USART_SR)*/
/*
 * Bit 0 PE: Parity error
 * @USART_ParityErr_t
 * */
typedef enum{

	NO_PARITY_ERROR,
	PARITY_ERROR

}USART_ParityErr_t;

/*
 * Bit 1 FE: Framing error
 * @USART_FramingErr_t
 * */
typedef enum{

	NO_FRAMING_ERROR,
	FRAMING_ERROR

}USART_FramingErr_t;

/*
 * Bit 2 NE: Noise error flag
 * @USART_NoiseErr_t
 * */
typedef enum{

	NO_NOISE_ERROR,
	NOISE_ERROR

}USART_NoiseErr_t;

/*
 * Bit 3 ORE: Overrun error
 * @USART_OverrunErr_t
 * */
typedef enum{

	NO_OVERRUN_ERROR,
	OVERRUN_ERROR

}USART_OverrunErr_t;

/*
 * Bit 4 IDLE: IDLE line detected
 * @USART_IDLELine_t
 * */
typedef enum{

	NO_IDLE_LINE_DETECTED,
	IDLE_LINE_DETECTED

}USART_IDLELine_t;

/*
 * Bit 5 RXNE: Read data register not empty
 * @USART_ReadDataNotEmpty_t
 * */
typedef enum{

	DATA_IS_NOT_RECEIVED,
	RECEIVED_DATA_IS_READY

}USART_ReadDataNotEmpty_t;

/*
 * Bit 6 TC: Transmission complete
 * @USART_TransComplete_t
 * */
typedef enum{

	TRANSMISSION_IS_NOT_COMPLETE,
	TRANSMISSION_IS_COMPLETE

}USART_TransComplete_t;

/*
 * Bit 7 TXE: Transmit data register empty
 * @USART_TransDataRegEmp_t
 * */
typedef enum{

	DATA_IS_NOT_TRANS_TO_SHIFT_REG,
	DATA_IS_TRANS_TO_SHIFT_REG

}USART_TransDataRegEmp_t;

/*
 * Bit 8 LBD: LIN break detection flag
 * @LIN_BREAK_NOT_DETECTED
 * */
typedef enum{

	LIN_BREAK_NOT_DETECTED,
	LIN_BREAK_DETECTED

}USART_LinBreak_t;

/*
 * Bit 9 CTS: CTS flag
 * @USART_CTSFlag_t
 * */
typedef enum{

	NO_CHANGE_OCCURRED,
	A_CHANGE_OCCURRED

}USART_CTSFlag_t;

/*Control register 1 (USART_CR1)*/

/*
 * Bit 13 UE: USART enable
 * @USART_UsartEnable_t
 * */
typedef enum{

	USART_USART_DISABLE=0,
	USART_USART_ENABLE

}USART_UsartEnable_t;
/*
 * Bit 12 M: Word length
 * @USART_WordLength_t
 * */
typedef enum{

	_8_DATA_BITS=0,
	_9_DATA_BITS

}USART_WordLength_t;
/*
 * Bit 11 WAKE: Wakeup method
 * @USART_WakeUpMethod_t
 * */
typedef enum{

	IDLE_LINE=0,
	ADDRESS_MARK

}USART_WakeUpMethod_t;
/*
 * Bit 10 PCE: Parity control enable
 * @USART_ParityControl_t
 * */
typedef enum{

	PARITY_CONTROL_DISABLE=0,
	PARITY_CONTROL_ENABLE

}USART_ParityControl_t;
/*
 * Bit 9 PS: Parity selection
 * @USART_ParitySelection_t
 * */
typedef enum{

	EVEN_PARITY=0,
	ODD_PARITY

}USART_ParitySelection_t;

/*
 * Bit 8 PEIE: PE interrupt enable
 * @USART_PEInterruptEn_t
 * */
typedef enum{

	PE_INTERRUPT_INHIBITED=0,
	PE_INTERRUPT_ENABLED

}USART_PEInterruptEn_t;
/*
 * Bit 7 TXEIE: TXE interrupt enable
 * @USART_TXEIntEn_t
 * */
typedef enum{

	TXE_INTERRUPT_INHIBITED=0,
	TXE_INTERRUPT_ENABLED

}USART_TXEIntEn_t;
/*
 * Bit 6 TCIE: Transmission complete interrupt enable
 * @USART_TCIntEn_t
 * */
typedef enum{

	TC_INTERRUPT_INHIBITED=0,
	TC_INTERRUPT_ENABLED

}USART_TCIntEn_t;
/*
 * Bit 5 RXNEIE: RXNE interrupt enable
 * @USART_RXNEIntEn_t
 * */
typedef enum{

	RXNE_INTERRUPT_INHIBITED=0,
	RXNE_INTERRUPT_ENABLED

}USART_RXNEIntEn_t;
/*
 * Bit 4 IDLEIE: IDLE interrupt enable
 * @USART_IDLEIntEn_t
 * */
typedef enum{

	IDLE_INTERRUPT_INHIBITED=0,
	IDLE_INTERRUPT_ENABLED

}USART_IDLEIntEn_t;
/*
 * Bit 3 TE: Transmitter enable
 * @USART_TransmitterEn_t
 * */
typedef enum{

	TRANSMITTER_DISABLE=0,
	TRANSMITTER_ENABLE

}USART_TransmitterEn_t;
/*
 * Bit 2 RE: Receiver enable
 * @USART_ReceiverEn_t
 * */
typedef enum{

	RECEIVER_DISABLE=0,
	RECEIVER_ENABLE

}USART_ReceiverEn_t;
/*
 * Bit 1 RWU: Receiver wakeup
 * @USART_ReceiverWakeUp_t
 * */
typedef enum{

	RECEIVER_IN_ACTIVE_MODE=0,
	RECEIVER_IN_MUTE_MODE

}USART_ReceiverWakeUp_t;
/*
 * Bit 0 SBK: Send break
 * @USART_SendBreak_t
 * */
typedef enum{

	NO_BREAK_CHAR_IS_TRANSMITTED=0,
	BREAK_CHAR_WILL_BE_TRANSMITTED

}USART_SendBreak_t;

/*Control register 2 (USART_CR2)*/

/*
 * Bits 13:12 STOP: STOP bits
 * @USART_StopBits_t
 * */
typedef enum{

	_1_STOP_BIT=0,
	_0P5_STOP_BIT,
	_2_STOP_BIT,
	_1P5_STOP_BIT

}USART_StopBits_t;

/*
 * Bit 11 CLKEN: Clock enable
 * @USART_ClockEnable_t
 * */
typedef enum{

	CLOCK_DISABLE=0,			/*Asynchronous*/
	CLOCK_ENABLE				/*Synchronous*/

}USART_ClockEnable_t;

/*Control register 3 (USART_CR3)*/

/*
 * Bit 10 CTSIE: CTS interrupt enable
 * @USART_CTSIntEnable_t
 * */
typedef enum{

	CTS_INTERRUPT_INHIBITED=0,
	CTS_INTERRUPT_ENABLED

}USART_CTSIntEnable_t;
/*
 * Bit 9 CTSE: CTS enable
 * @USART_CTSEnable_t
 * */
typedef enum{

	CTS_DISABLE=0,
	CTS_ENABLE

}USART_CTSEnable_t;
/*
 * Bit 8 RTSE: RTS enable
 * @USART_RTSEnable_t
 * */
typedef enum{

	RTS_DISABLE=0,
	RTS_ENABLE

}USART_RTSEnable_t;
/*
 * Bit 7 DMAT: DMA enable transmitter
 * @USART_DMATransEnable_t
 * */
typedef enum{

	DMA_TRANSMITTER_DISABLE=0,
	DMA_TRANSMITTER_ENABLE

}USART_DMATransEnable_t;
/*
 * Bit 6 DMAR: DMA enable receiver
 * @USART_DMAReceiverEnable_t
 * */
typedef enum{

	DMA_RECEIVER_DISABLE=0,
	DMA_RECEIVER_ENABLE

}USART_DMAReceiverEnable_t;
/*
 * Bit 0 EIE: Error interrupt enable
 * @USART_ErrorIntEn_t
 * */
typedef enum{

	ERROR_INTERRUPT_INHIBITED=0,
	ERROR_INTERRUPT_ENABLE

}USART_ErrorIntEn_t;
/**************************/

/*
 * @brief: Hardware flow control on/off
 * @USART_HWFlowControl_t
 * */
typedef enum{

	USART_HW_FLOW_CONTROL_ON=0,		/*Hardware flow control on*/
	USART_HW_FLOW_CONTROL_OFF		/*Hardware flow control off*/

}USART_HWFlowControl_t;

/*
 * @brief: USART mode (in transmitter , receiver mode or both modes)
 * @USART_Mode_t
 * */
typedef enum{

	USART_RX=0,			/*Rx Only*/
	USART_TX,			/*Tx Only*/
	USART_RXTX			/*Both Rx and Tx*/

}USART_Mode_t;
/**************************/
/********************************************************************************/


/********************************************************************************
 ****************** ### CONFIGURATION ENUMS SECTION ### *************************
 ********************************************************************************/
/*
 * USART configurations
 * @USART_ConfigReg_t
 * */
typedef struct{

	USART_Mode_t			USART_MODE;
	uint32_t				USART_BAUDRATE;
	USART_StopBits_t		USART_STOPBITS;
	USART_WordLength_t		USART_WORDLENGTH;
	USART_ParityControl_t	USART_PARITYBIT;
	USART_HWFlowControl_t	USART_HWFLOWCONTROL;
	USART_PrephNumber		USART_USARTNUMBER;
	USART_ClockEnable_t		USART_SYNCHMODE;

}USART_ConfigReg_t;


/********************************************************************************/

/********************************************************************************
 *************** ### FUNCTION DECLARATION SECTION ### ************************
 ********************************************************************************/
/*
 * @fn:		USART_ReadIntFlag
 * @brief:
 * @param:	Copy_USARTNumber		(ENUM: @USART_PrephNumber)
 * @param:	Copy_ITFlagID			(ENUM: @USART_FlagID_t)
 * @param:	Copy_u8ITFlagValue		uint8_t pointer to save the flag value
 * @retval:	Local_ErrorState		(ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_ReadIntFlag(USART_PrephNumber Copy_USARTNumber ,USART_FlagID_t Copy_ITFlagID ,uint8_t* Copy_u8ITFlagValue);
/*INITIALIZATION*/
/*
 * @fn:		USART_Init
 * @brief:
 * @param:	Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_Init(const USART_ConfigReg_t* Copy_InitConfig);

/****** ### WAITING ### ******/
/*
 * @fn:		USART_TransmitData
 * @brief:
 * @param:	Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @param:  Copy_Data				uint8_t
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_TransmitData(const USART_ConfigReg_t* Copy_InitConfig ,uint8_t Copy_Data);
/*
 * @fn:		USART_ReceiveData
 * @brief:
 * @param:	Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @param:  Copy_Data			  pointer uint16_t
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_ReceiveData(const USART_ConfigReg_t* Copy_InitConfig ,uint16_t* Copy_Data);

/****** ### DMA ### ******/
/*
 * @fn:		USART_TransmitDataEnable_DMA
 * @brief:
 * @param:	Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_TransmitDataEnable_DMA(const USART_ConfigReg_t* Copy_InitConfig );

/*
 * @fn:		USART_ReceiveDataEnable_DMA
 * @brief:
 * @param:	Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_ReceiveDataEnable_DMA(const USART_ConfigReg_t* Copy_InitConfig );


/****** ### INTERRUPT ### ******/
/*
 * @fn:		USART_SetCallBack
 * @brief: set the callback function
 * @param:	USART_NUM		    (ENUM: @USART_PrephNumber)
 * @param:	FLAG_ID		  		(ENUM: @USART_FlagID_t)
 * @param:	Copy_pvCallBack		  pointer to void function
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_SetCallBack( USART_PrephNumber USART_NUM ,USART_FlagID_t FLAG_ID,void (*Copy_pvCallBack)(void));
/*
 * @fn:		USART_IRQ_Handler
 * @brief: Handle the IRQ interrupt
 * @param:	USART_NUM		    (ENUM: @USART_PrephNumber)
 * @retval:	void
 * */
void USART_IRQ_Handler( USART_PrephNumber USART_NUM);
/*
 * @fn:		USART_Transmit_IT
 * @brief: transmit data with interrupt enabled
 * @param:	Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @param:	Copy_Data		  		uint8_t
 * @param:	Copy_pvCallBack		  pointer to void function
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_Transmit_IT(const USART_ConfigReg_t* Copy_InitConfig , uint8_t Copy_Data,void (*Copy_pvCallBack)(void));
/*
 * @fn:		USART_Receive_IT
 * @brief: transmit data with interrupt enabled
 * @param:	Copy_InitConfig		  pointer to (STRUCT: @USART_ConfigReg_t)
 * @param:	Copy_Data		  		pointer to uint16_t
 * @param:	Copy_pvCallBack		  pointer to void function
 * @retval:	Local_ErrorState				 (ENUM: @ErrorState_t)
 *			USART status
 * */
ErrorState_t USART_Receive_IT(const USART_ConfigReg_t* Copy_InitConfig , uint16_t* Copy_Data,void (*Copy_pvCallBack)(void));



/********************************************************************************/



















#endif
