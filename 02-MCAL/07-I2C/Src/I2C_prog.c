/********************************************************************************
 ********************************************************************************
 ********************************************************************************
 * @File	:	I2C_prog.c
 * @Author	:	Usef Elbedwehy
 * @Brief	:	Main program body of I2C
 * @layer	:	MCAL
 * @Date	:	1 March 2024
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

#include "I2C_prv.h"
#include "I2C_interface.h"

/********************************************************************************/

/********************************************************************************
 ******************* ### GLOBAL VARIABLE SECTION ### ****************************
 ********************************************************************************/
static I2C_Reg_t* I2Cx[I2C_PERIPHERALS_NUMBER] = { I2C1 , I2C2 };

//static void (*G_pvCallBack[I2C_PERIPHERALS_NUMBER][7])(void) = {NULL};

/********************************************************************************/

/********************************************************************************
 *************** ### FUNCTION IMPLEMENTATION SECTION ### ************************
 ********************************************************************************/

/*
 * @fn:		I2C_MasterInit
 * @brief:	initialize the master configurations
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @retval:	Local_ErrorSate	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t I2C_MasterInit(const I2C_Config_t* C_Init)
{
	ErrorState_t Local_ErrorSate = I2C_OK;

	if(C_Init == NULL)
	{
		Local_ErrorSate = I2C_NULL_POINTER;
		return Local_ErrorSate;
	}
	if((C_Init->I2C_ACK_MODE <= I2C_ACK) && (C_Init->I2C_ACK_MODE >= I2C_NACK)
			&& (C_Init->I2C_CLK_SPEED_MODE  <= I2C_FM) && (C_Init->I2C_CLK_SPEED_MODE >= I2C_SM)
			&& (C_Init->I2C_FM_MODE_DUTY_CYCLE  <= I2C_FM_16_9) && (C_Init->I2C_FM_MODE_DUTY_CYCLE >= I2C_FM_2)
			&& (C_Init->I2C_MODE  <= I2C_MASTER_MODE) && (C_Init->I2C_MODE >= I2C_SLAVE_MODE)
			&& (C_Init->I2C_NUMBER  <= I2C_NUM2) && (C_Init->I2C_NUMBER >= I2C_NUM1)
			&& (C_Init->I2C_NoStretchStatus  <= CLK_STRETCH_DISABLE) && (C_Init->I2C_NoStretchStatus >= CLK_STRETCH_ENABLE)
			&& (C_Init->I2C_PERIPH_FREQ  <=  50) && (C_Init->I2C_PERIPH_FREQ >= 2) )
	{
		/*Controls the SCL clock in master mode.*/
		I2C_ClockControl(C_Init);
		/*ACK enable/Disable*/
		I2Cx[C_Init->I2C_NUMBER]->I2C_CR1 |= (C_Init->I2C_ACK_MODE << I2C_CR1_ACK);

		/*I2C Enable*/
		I2Cx[C_Init->I2C_NUMBER]->I2C_CR1 |= (SET_MASK << I2C_CR1_PE);
	}
	else
	{
		Local_ErrorSate = I2C_NOK;
	}

	return Local_ErrorSate;
}

/*
 * @fn:		I2C_SlaveInit
 * @brief:	initialize the slave configurations
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @retval:	Local_ErrorSate	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t I2C_SlaveInit(const I2C_Config_t* C_Init)
{
	ErrorState_t Local_ErrorSate = I2C_OK;

	if(C_Init == NULL)
	{
		Local_ErrorSate = I2C_NULL_POINTER;
		return Local_ErrorSate;
	}
	if((C_Init->I2C_ACK_MODE <= I2C_ACK) && (C_Init->I2C_ACK_MODE >= I2C_NACK)
			&& (C_Init->I2C_CLK_SPEED_MODE  <= I2C_FM) && (C_Init->I2C_CLK_SPEED_MODE >= I2C_SM)
			&& (C_Init->I2C_FM_MODE_DUTY_CYCLE  <= I2C_FM_16_9) && (C_Init->I2C_FM_MODE_DUTY_CYCLE >= I2C_FM_2)
			&& (C_Init->I2C_MODE  <= I2C_MASTER_MODE) && (C_Init->I2C_MODE >= I2C_SLAVE_MODE)
			&& (C_Init->I2C_NUMBER  <= I2C_NUM2) && (C_Init->I2C_NUMBER >= I2C_NUM1)
			&& (C_Init->I2C_NoStretchStatus  <= CLK_STRETCH_DISABLE) && (C_Init->I2C_NoStretchStatus >= CLK_STRETCH_ENABLE)
			&& (C_Init->I2C_PERIPH_FREQ  <=  50) && (C_Init->I2C_PERIPH_FREQ >= 2))
	{

		/*CLOCK STRETCHING ENABLE/DISABLE*/
		I2Cx[C_Init->I2C_NUMBER]->I2C_CR1 |= (C_Init->I2C_NoStretchStatus << I2C_CR1_NOSTRETCH);
		/*I2C Enable*/
		I2Cx[C_Init->I2C_NUMBER]->I2C_CR1 |= (SET_MASK << I2C_CR1_PE);
	}
	else
	{
		Local_ErrorSate = I2C_NOK;
	}

	return Local_ErrorSate;
}

/*
 * @fn:		I2C_SendStartCondition
 * @brief:	to send start condition
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @param:	C_SlaveAddress		(uint8_t)
 * @param:	C_Control		(ENUM: @I2C_ReadWrite_t)
 * @retval:	Local_ErrorSate	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t I2C_SendStartCondition(const I2C_Config_t* C_Init ,uint8_t C_SlaveAddress ,I2C_ReadWrite_t C_Control)
{

	ErrorState_t Local_ErrorSate = I2C_OK;
	uint8_t	Local_u8Address = OK;

	if(C_Init != NULL)
	{
		/*check if busy, if busy wait*/
		while(((I2Cx[C_Init->I2C_NUMBER]->I2C_SR2 >> I2C_SR2_BUSY) & READ_VAL_MASK) == BUSY_FLAG);
		/*Send start condition*/
		I2Cx[C_Init->I2C_NUMBER]->I2C_CR1 |= (SET_MASK << I2C_CR1_START);
		/*wait until start condition flag is raised*/
		while(((I2Cx[C_Init->I2C_NUMBER]->I2C_SR1 >> I2C_SR1_SB) & READ_VAL_MASK) != READY_FLAG);

		/*set slave address*/
		Local_u8Address = (C_SlaveAddress << I2C_OAR1_ADD_1_7);
		/*set LSB control bit*/
		Local_u8Address |= (uint8_t)(C_Control);
		/* one address byte is sent*/
		I2Cx[C_Init->I2C_NUMBER]->I2C_DR = Local_u8Address;

		/*wait until address flag is raised*/
		while(((I2Cx[C_Init->I2C_NUMBER]->I2C_SR1 >> I2C_SR1_ADDR) & READ_VAL_MASK) != READY_FLAG);
		/*Then the master waits for a read of the SR1 register followed by a read of the SR2*/
		I2C_ClearFlag(C_Init->I2C_NUMBER);

	}
	else
	{
		Local_ErrorSate = I2C_NULL_POINTER;
	}


	return Local_ErrorSate;
}

/*
 * @fn:		I2C_SendRepeatedStartCondition
 * @brief:	to send repeated start condition
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @param:	C_SlaveAddress		(uint8_t)
 * @param:	C_Control		(ENUM: @I2C_ReadWrite_t)
 * @retval:	Local_ErrorSate	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t I2C_SendRepeatedStartCondition(const I2C_Config_t* C_Init ,uint8_t C_SlaveAddress ,I2C_ReadWrite_t C_Control)
{

	ErrorState_t Local_ErrorSate = I2C_OK;
	uint8_t	Local_u8Address = OK;

	if(C_Init != NULL)
	{
		/*Send start condition*/
		I2Cx[C_Init->I2C_NUMBER]->I2C_CR1 |= (SET_MASK << I2C_CR1_START);
		/*wait until start condition flag is raised*/
		while(((I2Cx[C_Init->I2C_NUMBER]->I2C_SR1 >> I2C_SR1_SB) & READ_VAL_MASK) != READY_FLAG);

		/*set slave address*/
		Local_u8Address = (C_SlaveAddress << I2C_OAR1_ADD_1_7);
		/*set LSB control bit*/
		Local_u8Address |= (uint8_t)(C_Control);
		/* one address byte is sent*/
		I2Cx[C_Init->I2C_NUMBER]->I2C_DR = Local_u8Address;

		/*wait until address flag is raised*/
		while(((I2Cx[C_Init->I2C_NUMBER]->I2C_SR1 >> I2C_SR1_ADDR) & READ_VAL_MASK) != READY_FLAG);
		/*Then the master waits for a read of the SR1 register followed by a read of the SR2*/
		I2C_ClearFlag(C_Init->I2C_NUMBER);

	}
	else
	{
		Local_ErrorSate = I2C_NULL_POINTER;
	}


	return Local_ErrorSate;
}


/*
 * @fn:		I2C_MasterWriteData
 * @brief:	master send data to slave 	(MASTER TRASNMITTER)
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @param:	C_u8Data		(uint8_t)
 * @param:	C_DataSize		(uint8_t)
 * @retval:	Local_ErrorSate	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t I2C_MasterWriteData(const I2C_Config_t* C_Init ,uint8_t C_u8Data ,uint8_t C_DataSize)
{
	ErrorState_t Local_ErrorSate = I2C_OK;
	uint8_t Local_u8Counter = 0;
	if(C_Init != NULL)
	{
		for(Local_u8Counter = 0 ; Local_u8Counter < C_DataSize ; Local_u8Counter++)
		{
			/*wait until : Data register empty (transmitters) is set*/
			while(((I2Cx[C_Init->I2C_NUMBER]->I2C_SR1 >> I2C_SR1_TxE) & READ_VAL_MASK) != READY_FLAG);
			/*Send data*/
			I2Cx[C_Init->I2C_NUMBER]->I2C_DR = C_u8Data;
		}

	}
	else
	{
		Local_ErrorSate = I2C_NULL_POINTER;
	}

	return Local_ErrorSate;
}

/*
 * @fn:		I2C_MasterReadData
 * @brief:	Master reads received data		(MASTER RECEIVER)
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @param:	C_u8ReceivedData	pointer to uint8_t
 * @param:	C_DataSize		(uint8_t)
 * @retval:	Local_ErrorSate	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t I2C_MasterReadData(const I2C_Config_t* C_Init ,uint8_t* C_u8ReceivedData ,uint8_t C_DataSize)
{
	ErrorState_t Local_ErrorSate = I2C_OK;
	uint8_t Local_u8Counter = 0;

	if((C_Init == NULL) || (C_u8ReceivedData == NULL))
	{
		Local_ErrorSate = I2C_NULL_POINTER;
	}
	else
	{
		for(Local_u8Counter = 0 ; Local_u8Counter < C_DataSize ; Local_u8Counter++)
		{
			/*wait until : Data register empty (transmitters) is set*/
			while(((I2Cx[C_Init->I2C_NUMBER]->I2C_SR1 >> I2C_SR1_RxNE) & READ_VAL_MASK) != READY_FLAG);
			/*Receive Data*/
			*C_u8ReceivedData = I2Cx[C_Init->I2C_NUMBER]->I2C_DR;

			if((Local_u8Counter + 2 ) == C_DataSize)
			{
				/*ACK=0*/
				I2Cx[C_Init->I2C_NUMBER]->I2C_CR1 &=~ (SET_MASK << I2C_CR1_ACK);
			}
		}

	}

	return Local_ErrorSate;
}

/*
 * @fn:		I2C_SendStopCondition
 * @brief:	close the communication
 * @param:	C_Init		pointer to (STRUCT: @I2C_Config_t)
 * @retval:	Local_ErrorSate	(ENUM: @ErrorState_t)
 *
 * */
ErrorState_t I2C_SendStopCondition(const I2C_Config_t* C_Init)
{
	ErrorState_t Local_ErrorSate = I2C_OK;

	if(C_Init != NULL)
	{
		/*wait until : Data register empty (transmitters) is set*/
		while(((I2Cx[C_Init->I2C_NUMBER]->I2C_SR1 >> I2C_SR1_TxE) & READ_VAL_MASK) != READY_FLAG);
		/*wait until : Data register empty (transmitters) is set*/
		while(((I2Cx[C_Init->I2C_NUMBER]->I2C_SR1 >> I2C_SR1_BTF) & READ_VAL_MASK) != READY_FLAG);
		/*Send stop request*/
		I2Cx[C_Init->I2C_NUMBER]->I2C_CR1 |= (SET_MASK << I2C_CR1_STOP);
	}
	else
	{
		Local_ErrorSate = I2C_NULL_POINTER;
	}


	return Local_ErrorSate;
}



/********************************************************************************/

/********************************************************************************
 ****************** ### PRIVATE FUNCTION SECTION ### ***************************
 ********************************************************************************/
static void I2C_ClockControl(const I2C_Config_t* C_Init)
{
	uint16_t CCR_VALUE = 0;
	uint16_t SCL_FREQ = C_Init->I2C_SCL_FREQ;
	float Local_Periph_PTime;
	uint8_t Local_Periph_Freq = C_Init->I2C_PERIPH_FREQ;
	/*The minimum allowed frequency is 2 MHz,
				the maximum frequency is limited by the maximum APB frequency
				and cannot exceed 50 MHz (peripheral intrinsic maximum limit).*/
	if(Local_Periph_Freq > MAX_PERIPH_CLK_FREQ)
	{
		Local_Periph_Freq = MAX_PERIPH_CLK_FREQ;
	}
	else if(Local_Periph_Freq < MIN_PERIPH_CLK_FREQ)
	{
		Local_Periph_Freq = MIN_PERIPH_CLK_FREQ;
	}

	/*Set Peripheral Clock*/
	I2Cx[C_Init->I2C_NUMBER]->I2C_CR2 |= ( Local_Periph_Freq << I2C_CR2_FREQ0 );

	/* I2C master mode selection*/
	/*FAST MODE (FM) or STANDARD MODE (SM)*/
	if(C_Init->I2C_CLK_SPEED_MODE == I2C_SM)
	{
		/*STANDARD MODE*/
		I2Cx[C_Init->I2C_NUMBER]->I2C_CCR &=~ ( SET_MASK << I2C_CCR_F_PER_S );

		/*Calculate CCR value*/
		Local_Periph_PTime = (float)(1 / (Local_Periph_Freq*1000000UL));
		CCR_VALUE = (uint16_t)( (float)(1/(SCL_FREQ*1000UL))/(float)(2*Local_Periph_PTime)) ;
		/*Set Clock*/
		I2Cx[C_Init->I2C_NUMBER]->I2C_CCR |= ( CCR_VALUE << I2C_CCR_CCR0_0_11 );
	}
	else if(C_Init->I2C_CLK_SPEED_MODE == I2C_FM)
	{
		/*FAST MODE*/
		I2Cx[C_Init->I2C_NUMBER]->I2C_CCR |= ( SET_MASK << I2C_CCR_F_PER_S );
		/*Fm mode duty cycle*/
		switch(C_Init->I2C_FM_MODE_DUTY_CYCLE)
		{
		case I2C_FM_2:
			/* Fm mode tlow/thigh = 2*/
			I2Cx[C_Init->I2C_NUMBER]->I2C_CCR &=~ ( SET_MASK << I2C_CCR_DUTY );
			/*Calculate CCR value*/
			Local_Periph_PTime = (float)(1 / Local_Periph_Freq);
			CCR_VALUE = (uint16_t)( (float)(1/SCL_FREQ)/(float)(3*Local_Periph_PTime)) ;
			/*Set Clock*/
			I2Cx[C_Init->I2C_NUMBER]->I2C_CCR |= ( CCR_VALUE << I2C_CCR_CCR0_0_11 );
			break;

		case I2C_FM_16_9:
			/* Fm mode tlow/thigh = 16/9 */
			I2Cx[C_Init->I2C_NUMBER]->I2C_CCR |= ( SET_MASK << I2C_CCR_DUTY );
			/*Calculate CCR value*/
			Local_Periph_PTime = (float)(1 / Local_Periph_Freq);
			CCR_VALUE = (uint16_t)( (float)(1/SCL_FREQ)/(float)(25*Local_Periph_PTime)) ;
			/*Set Clock*/
			I2Cx[C_Init->I2C_NUMBER]->I2C_CCR |= ( CCR_VALUE << I2C_CCR_CCR0_0_11 );
			break;
		}
	}


}

/*
 * @fn: I2C_ClearFlag
 * @brief: clear flags by reading SR1 and SR2 registers
 * @param: C_I2C_Number 	(ENUM: @I2C_PeriphNum_t)
 * @retval: C_I2C_Number (uint16_t) ---- note: its invalid number we just need to clear the flag registers
 *
 * */
static uint16_t I2C_ClearFlag( I2C_PeriphNum_t C_I2C_Number)
{
	uint16_t Local_FlagVal = 0;


	Local_FlagVal = I2Cx[C_I2C_Number]->I2C_SR1 ;
	Local_FlagVal = I2Cx[C_I2C_Number]->I2C_SR2 ;

	return Local_FlagVal;
}
/********************************************************************************/
