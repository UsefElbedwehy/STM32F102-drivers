#ifndef   CLCD_INTERFACE_H
#define    CLCD_INTERFACE_H

/*
 * @fn		:	CLCD_Init
 * @brief	:	Initializes the configurations the character 16x2 LCD
 * @param	:	void
 * @retval	:	void
 *
 * */
void CLCD_Init(void);

/*
 * @fn		:	CLCD_SendCmd
 * @brief	:	to send command to the character 16x2 LCD
 * @param	:	Copy_u8Cmd 		(uint8_t)
 * @retval	:	void
 *
 * */
void CLCD_SendCmd(uint8_t Copy_u8Cmd);

/*
 * @fn		:	CLCD_SendData
 * @brief	:	to send Data to the character 16x2 LCD
 * @param	:	Copy_u8Data			(uint8_t)
 * @retval	:	void
 *
 * */
void CLCD_SendData(uint8_t Copy_u8Data);

/*
 * @fn		:	CLCD_PrintChar
 * @brief	:	to send data (of type char) to the character 16x2 LCD
 *  										you can send anything from the asci table
 * @param	:	Copy_u8Data  -> for example : 'a'  , 'A' ,or '0'
 * @retval	:	void
 *
 * */
void CLCD_PrintChar(uint8_t Copy_u8Data);

/*
 * @fn		:	CLCD_PrintString
 * @brief	:	to send data (of type String) to the character 16x2 LCD
 *  						you can send anything between " "
 * @param	:	Copy_pvData  pointer to string -> for example : "Driver"  ,or "Data is 6/3/2024"
 * @retval	:	void
 *
 * */
void CLCD_PrintString(char* Copy_pvData);

/*
 * @fn		:	CLCD_PrintNumber
 * @brief	:	to send data numbers (of type int32_t) to the character 16x2 LCD
 *  						you can send anything between " "
 * @param	:	Copy_u32Number  	pointer to string -> for example : "1234"
 * @retval	:	void
 *
 * */
void CLCD_PrintNumber(int32_t Copy_u32Number);

/*
 * @fn		:	CLCD_GoToXY
 * @brief	:	to set the courser location
 * @param	:	Copy_u8XAddress  	(uint8_t)
 * @param	:	Copy_u8YAddress  	(uint8_t)
 * @retval	:	void
 *
 * */
void CLCD_GoToXY(uint8_t Copy_u8XAddress ,uint8_t Copy_u8YAddress );

/*
 * @fn		:	CLCD_ClearDisplay
 * @brief	:	to clear the display of the character 16*2 LCD
 * @param	:	void
 * @retval	:	void
 *
 * */
void CLCD_ClearDisplay(void);

#endif
