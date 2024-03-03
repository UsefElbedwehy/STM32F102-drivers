#ifndef		I2C_INTERFACE_H_
#define		I2C_INTERFACE_H_

/********************************************************************************
 ************************ ### I2C ENUM SECTION ### ****************************
 ********************************************************************************/

/*
 * number of I2C peripherals
 * @I2C_PeriphNumber_t
 * */
typedef enum{

	I2C_NUM1,
	I2C_NUM2,
	I2C_PERIPHERALS_NUMBER

}I2C_PeriphNum_t;
/********************************************************************************/

/********************************************************************************
 ************************ ### FLAGS ENUM SECTION ### ****************************
 ********************************************************************************/
typedef enum{

	I2C_START_BIT_FLAG_ID,
	I2C_ADDRESS_SENT_FLAG_ID,
	I2C_BYTE_TRANS_FINISHED_FLAG_ID,
	I2C_10_BIT_HEADER_SENT_FLAG_ID,
	I2C_STOP_DETECTION_FLAG_ID,
	I2C_DATA_REG_NOT_EMPTY_FLAG_ID=6,
	I2C_DATA_REG_EMPTY_FLAG_ID,
	I2C_BUS_ERROR_FLAG_ID,
	I2C_ATRIB_LOST_FLAG_ID,
	I2C_ACK_FAILURE_FLAG_ID,
	I2C_OVR_FLAG_ID,
	I2C_PEC_ERR_RECEPTION_FLAG_ID,
	I2C_TIMEOUT_FLAG_ID=14

}I2C_FlagID_t;
/********************************************************************************/

/********************************************************************************
 ****************** ### REGISTER BITS ENUMS SECTION ### *************************
 ********************************************************************************/

/*
 * I2C Control register 1 (I2C_CR1)
 * @I2C_CR1_t
 * */
typedef enum{

	I2C_CR1_PE		 ,		/*Peripheral enable*/
	I2C_CR1_SMBUS	 ,		/*SMBus mode*/
	I2C_CR1_SMBTYPE=3,      /*SMBus type*/
	I2C_CR1_ENARP	 ,      /*ARP enable*/
	I2C_CR1_ENPEC	 ,      /*PEC enable*/
	I2C_CR1_ENGC 	 ,      /*General call enable*/
	I2C_CR1_NOSTRETCH,      /*Clock stretching disable (Slave mode)*/
	I2C_CR1_START    ,      /*Start generation*/
	I2C_CR1_STOP     ,      /*Stop generation*/
	I2C_CR1_ACK      ,      /*Acknowledge enable*/
	I2C_CR1_POS      ,      /*Acknowledge/PEC Position (for data reception)*/
	I2C_CR1_PEC      ,      /*Packet error checking*/
	I2C_CR1_ALERT    ,      /*SMBus alert*/
	I2C_CR1_SWRST=15		/*Software reset*/

}I2C_CR1_t;

/*
 * I2C Control register 2 (I2C_CR2)
 * @I2C_CR2_t
 * */
typedef enum{

	I2C_CR2_FREQ0=0		 ,		/*Peripheral clock frequency: Bits 5:0 FREQ[5:0]*/
	I2C_CR2_ITERREN=8	 ,		/*Error interrupt enable*/
	I2C_CR2_ITEVTEN		 ,		/*Event interrupt enable*/
	I2C_CR2_ITBUFEN      ,		/*Buffer interrupt enable*/
	I2C_CR2_DMAEN        ,		/*DMA requests enable*/
	I2C_CR2_LAST				/*DMA last transfer*/

}I2C_CR2_t;

/*
 * I2C Own address register 1 (I2C_OAR1)
 * @I2C_OAR1_t
 * */
typedef enum{

	I2C_OAR1_ADD0=0		 ,		/*Interface address*/
	I2C_OAR1_ADD_1_7=1	 ,		/*Interface address*/
	I2C_OAR1_ADD_8_9=8	 ,		/*Interface address*/
	I2C_OAR1_ADDMODE=15      	/*Addressing mode (slave mode)*/

}I2C_OAR1_t;

/*
 * I2C Own address register 2 (I2C_OAR2)
 * @I2C_OAR2_t
 * */
typedef enum{

	I2C_OAR2_ENDUAL=0		 ,		/*Dual addressing mode enable*/
	I2C_OAR2_ADD2_1_7=1	   			/*Interface address*/

}I2C_OAR2_t;

/*
 * I2C Data register (I2C_DR)
 * @I2C_DR_t
 * */
typedef enum{

	I2C_DR_DR0=0				/*8-bit data register*/

}I2C_DR_t;

/*
 * I2C Status register 1 (I2C_SR1)
 * @I2C_SR1_t
 * */
typedef enum{

	I2C_SR1_SB=0		,		/*Start bit (Master mode)*/
	I2C_SR1_ADDR        ,		/*Address sent (master mode)/matched (slave mode)*/
	I2C_SR1_BTF         ,		/*Byte transfer finished*/
	I2C_SR1_ADD10       ,		/*10-bit header sent (Master mode) */
	I2C_SR1_STOPF       ,		/*Stop detection (slave mode) */
	I2C_SR1_RxNE=6      ,		/*Data register not empty (receivers)*/
	I2C_SR1_TxE         ,		/*Data register empty (transmitters)*/
	I2C_SR1_BERR        ,		/*Bus error*/
	I2C_SR1_ARLO        ,		/*Arbitration lost (master mode)*/
	I2C_SR1_AF          ,		/*Acknowledge failure*/
	I2C_SR1_OVR         ,		/*Overrun/Underrun*/
	I2C_SR1_PECERR      ,		/*PEC Error in reception*/
	I2C_SR1_TIMEOUT=14  ,		/*Timeout or Tlow error*/
	I2C_SR1_SMBALERT     		/*SMBus alert*/

}I2C_SR1_t;

/*
 * I2C Status register 2 (I2C_SR2)
 * @I2C_SR2_t
 * */
typedef enum{

	I2C_SR2_MSL=0		,		/*Master/slave*/
	I2C_SR2_BUSY        ,		/*Bus busy*/
	I2C_SR2_TRA         ,		/*Transmitter/receiver*/
	I2C_SR2_GENCALL=4   ,		/*General call address (Slave mode)  */
	I2C_SR2_SMBDEFAULT	,		/*SMBus device default address (Slave mode) */
	I2C_SR2_SMBHOST     ,		/*SMBus host header (Slave mode)*/
	I2C_SR2_DUALF       ,		/*Dual flag (Slave mode)*/
	I2C_SR2_PEC_0_7				/*Packet error checking register : Bits 15:8 PEC[7:0]*/

}I2C_SR2_t;

/*
 * I2C Clock control register (I2C_CCR)
 * @I2C_CCR_t
 * */
typedef enum{

	I2C_CCR_CCR0_0_11=0		,		/*Bits 11:0 CCR[11:0]: Clock control register in Fm/Sm mode (Master mode) */
	I2C_CCR_DUTY=14         ,		/*Fm mode duty cycle*/
	I2C_CCR_F_PER_S=15      		/*I2C master mode selection*/

}I2C_CCR_t;

/*
 * I2C TRISE register (I2C_TRISE)
 * @I2C_TRISE_t
 * */
typedef enum{

	I2C_TRISE_TRISE_0_5=0				/*Bits 5:0 TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)*/

}I2C_TRISE_t;
/********************************************************************************/

/********************************************************************************
 ********************** ### STATUS ENUMS SECTION ### ****************************
 ********************************************************************************/
/**/
typedef enum{

	I2C_CONTROL_READ,
	I2C_CONTROL_WRITE

}I2C_ControlState;

typedef enum{

	I2C_READ,
	I2C_WRITE

}I2C_ReadWrite_t;
/********************************************************************************/


/********************************************************************************
 ****************** ### CONFIGURATION ENUMS SECTION ### *************************
 ********************************************************************************/

/*
 * Mode selection
 * @I2C_ModeSelection_t
 * */
typedef enum{

	I2C_SLAVE_MODE  ,
	I2C_MASTER_MODE

}I2C_ModeSelection_t;

/***/
typedef enum{

	I2C_NACK,
	I2C_ACK

}I2C_Ack_t;

/***/
typedef enum{

	I2C_SM,
	I2C_FM

}I2C_ClkSpeedMode_t;

/***/
typedef enum{

	I2C_FM_2,
	I2C_FM_16_9

}I2C_DutyCycle_t;

typedef enum{

	CLK_STRETCH_ENABLE,
	CLK_STRETCH_DISABLE

}I2C_NoStretchStatus_t;
/********************************************************************************/

/********************************************************************************
 ****************** ### CONFIGURATION STRUCT SECTION ### ************************
 ********************************************************************************/
typedef struct{

	I2C_PeriphNum_t			I2C_NUMBER;
	I2C_Ack_t				I2C_ACK_MODE;

	I2C_ModeSelection_t		I2C_MODE;

	/*Slave mode only*/
	I2C_NoStretchStatus_t	I2C_NoStretchStatus;

	/*Master mode only*/
	I2C_ClkSpeedMode_t		I2C_CLK_SPEED_MODE;		/*FM OR SM*/
	I2C_DutyCycle_t			I2C_FM_MODE_DUTY_CYCLE;	/*Based on Duty*/
	uint16_t 				I2C_SCL_FREQ;			/**/
	uint8_t					I2C_PERIPH_FREQ;	/*Range: 2 to 50*/

}I2C_Config_t;
/********************************************************************************/


/********************************************************************************
 ****************** ### FUNCTION DECLARATION SECTION ### ************************
 ********************************************************************************/

/*
 * @fn:		I2C_MasterInit
 * @brief:	initialize the master configurations
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @retval:	Local_ErrorSate	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t I2C_MasterInit(const I2C_Config_t* C_Init);

/*
 * @fn:		I2C_SlaveInit
 * @brief:	initialize the slave configurations
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @retval:	Local_ErrorSate	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t I2C_SlaveInit(const I2C_Config_t* C_Init);

/*
 * @fn:		I2C_SendStartCondition
 * @brief:	to send start condition
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @param:	C_SlaveAddress		(uint8_t)
 * @param:	C_Control		(ENUM: @I2C_ReadWrite_t)
 * @retval:	Local_ErrorSate	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t I2C_SendStartCondition(const I2C_Config_t* C_Init ,uint8_t C_SlaveAddress ,I2C_ReadWrite_t C_Control);

/*
 * @fn:		I2C_SendRepeatedStartCondition
 * @brief:	to send repeated start condition
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @param:	C_SlaveAddress		(uint8_t)
 * @param:	C_Control		(ENUM: @I2C_ReadWrite_t)
 * @retval:	Local_ErrorSate	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t I2C_SendRepeatedStartCondition(const I2C_Config_t* C_Init ,uint8_t C_SlaveAddress ,I2C_ReadWrite_t C_Control);

/*
 * @fn:		I2C_MasterWriteData
 * @brief:	master send data to slave 	(MASTER TRASNMITTER)
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @param:	C_u8Data		(uint8_t)
 * @param:	C_DataSize		(uint8_t)
 * @retval:	Local_ErrorSate	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t I2C_MasterWriteData(const I2C_Config_t* C_Init ,uint8_t C_u8Data ,uint8_t C_DataSize);

/*
 * @fn:		I2C_MasterReadData
 * @brief:	Master reads received data		(MASTER RECEIVER)
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @param:	C_u8ReceivedData	pointer to uint8_t
 * @param:	C_DataSize		(uint8_t)
 * @retval:	Local_ErrorSate	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t I2C_MasterReadData(const I2C_Config_t* C_Init ,uint8_t* C_u8ReceivedData ,uint8_t C_DataSize);

/*
 * @fn:		I2C_SendStopCondition
 * @brief:	close the communication
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @retval:	Local_ErrorSate	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t I2C_SendStopCondition(const I2C_Config_t* C_Init);
/********************************************************************************/

/********************************************************************************
 ****************** ### PRIVATE FUNCTION SECTION ### ***************************
 ********************************************************************************/

/*
 * @fn: I2C_ClockControl
 * @brief: to set the clock configuration according to the clock mode
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @retval: void
 *
 * */
static void I2C_ClockControl(const I2C_Config_t* C_Init);

/*
 * @fn: I2C_ClearFlag
 * @brief: clear flags by reading SR1 and SR2 registers
 * @param: C_I2C_Number 	(ENUM: @I2C_PeriphNum_t)
 * @retval: C_I2C_Number (uint16_t) ---- note: its invalid number we just need to clear the flag registers
 *
 * */
static uint16_t I2C_ClearFlag( I2C_PeriphNum_t C_I2C_Number);

/********************************************************************************/

#endif
