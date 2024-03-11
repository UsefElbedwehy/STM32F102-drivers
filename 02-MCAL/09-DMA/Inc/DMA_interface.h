#ifndef		DMA_INTERFACE_H_
#define		DMA_INTERFACE_H_

/********************************************************************************
 ************************* ### FLAGs ENUM ### ***********************************
 ********************************************************************************/
typedef enum{

	DMA_CHANNELx_GLOBAL_INTERRUPT_FLAG,
	DMA_CHANNELx_TRANSFER_COMPLETE_FLAG,
	DMA_CHANNELx_HALF_TRANSFER_FLAG,
	DMA_CHANNELx_TRANSFER_ERROR_FLAG,
	DMA_CHANNELx_MAX_FLAG_NUMBER

}DMA_FlagID_t;
/********************************************************************************/

/********************************************************************************
 ************************* ### Register Bits ENUMs ### **************************
 ********************************************************************************/
/*
 *
 * @DMA_ISR_t
 * */
typedef enum{

	DMA_ISR_GIF1		,
	DMA_ISR_TCIF1       ,
	DMA_ISR_HTIF1       ,
	DMA_ISR_TEIF1       ,
	DMA_ISR_GIF2        ,
	DMA_ISR_TCIF2       ,
	DMA_ISR_HTIF2       ,
	DMA_ISR_TEIF2       ,
	DMA_ISR_GIF3        ,
	DMA_ISR_TCIF3       ,
	DMA_ISR_HTIF3       ,
	DMA_ISR_TEIF3       ,
	DMA_ISR_GIF4        ,
	DMA_ISR_TCIF4       ,
	DMA_ISR_HTIF4       ,
	DMA_ISR_TEIF4       ,
	DMA_ISR_GIF5        ,
	DMA_ISR_TCIF5       ,
	DMA_ISR_HTIF5       ,
	DMA_ISR_TEIF5       ,
	DMA_ISR_GIF6        ,
	DMA_ISR_TCIF6       ,
	DMA_ISR_HTIF6       ,
	DMA_ISR_TEIF6       ,
	DMA_ISR_GIF7        ,
	DMA_ISR_TCIF7       ,
	DMA_ISR_HTIF7       ,
	DMA_ISR_TEIF7

}DMA_ISR_t;

/*
 *
 * @DMA_IFCR_t
 * */
typedef enum{

	DMA_IFCR_CGIF1      ,
	DMA_IFCR_CTCIF1     ,
	DMA_IFCR_CHTIF1     ,
	DMA_IFCR_CTEIF1     ,
	DMA_IFCR_CGIF2      ,
	DMA_IFCR_CTCIF2     ,
	DMA_IFCR_CHTIF2     ,
	DMA_IFCR_CTEIF2     ,
	DMA_IFCR_CGIF3      ,
	DMA_IFCR_CTCIF3     ,
	DMA_IFCR_CHTIF3     ,
	DMA_IFCR_CTEIF3     ,
	DMA_IFCR_CGIF4      ,
	DMA_IFCR_CTCIF4     ,
	DMA_IFCR_CHTIF4     ,
	DMA_IFCR_CTEIF4     ,
	DMA_IFCR_CGIF5      ,
	DMA_IFCR_CTCIF5     ,
	DMA_IFCR_CHTIF5     ,
	DMA_IFCR_CTEIF5     ,
	DMA_IFCR_CGIF6      ,
	DMA_IFCR_CTCIF6     ,
	DMA_IFCR_CHTIF6     ,
	DMA_IFCR_CTEIF6     ,
	DMA_IFCR_CGIF7      ,
	DMA_IFCR_CTCIF7     ,
	DMA_IFCR_CHTIF7     ,
	DMA_IFCR_CTEIF7

}DMA_IFCR_t;


/*
 * @Register: DMA channel x configuration register
 * @DMA_IFCR_t
 * */
typedef enum{

	DMA_CCRx_EN				 ,
	DMA_CCRx_TCIE            ,
	DMA_CCRx_HTIE            ,
	DMA_CCRx_TEIE            ,
	DMA_CCRx_DIR             ,
	DMA_CCRx_CIRC            ,
	DMA_CCRx_PINC            ,
	DMA_CCRx_MINC            ,
	DMA_CCRx_PSIZE__= 8      ,
	DMA_CCRx_MSIZE__= 10     ,
	DMA_CCRx_PL__	= 12     ,
	DMA_CCRx_MEM2MEM= 14

}DMA_CCRx_t;

/*
 * @Register: DMA channel x number of data register
 * @brief: Number of data to be transferred (0 up to 65535).
 * This register can only be written when the channel is disabled.
 * Once the channel is enabled, this register is read-only,
 * indicating the remaining bytes to be transmitted.
 * @DMA_CNDTRx_t
 * */
typedef enum{

	DMA_CNDTRx_NDT__

}DMA_CNDTRx_t;

/*
 * @Register: DMA channel x peripheral address register
 * @note: This register must not be written when the channel is enabled.
 * @DMA_CPARx_t
 * */
typedef enum{

	DMA_CPARx_PA__

}DMA_CPARx_t;

/*
 * @Register: DMA channel x memory address register
 * @note: This register must not be written when the channel is enabled.
 * @DMA_CMARx_t
 * */
typedef enum{

	DMA_CMARx_MA__

}DMA_CMARx_t;
/********************************************************************************/

/********************************************************************************
 *********************** ### Configuration enums ### ****************************
 ********************************************************************************/
/*
 * DMA PERIPHERALs
 * @DMA_Number_t
 * */
typedef enum{

	DMA_NUM_1,
	DMA_NUM_2

}DMA_Number_t;

/*
 * DMA CHANNELs
 * @DMA_Channel_t
 * */
typedef enum{

	DMA_CHANNEL_1,
	DMA_CHANNEL_2,
	DMA_CHANNEL_3,
	DMA_CHANNEL_4,
	DMA_CHANNEL_5,
	DMA_CHANNEL_6,
	DMA_CHANNEL_7,
	DMA_MAX_CHANNEL_NUMBER

}DMA_Channel_t;

/*
 * DMA Priorities
 * @DMA_Priority_t
 * */
typedef enum{

	DMA_PRIORITY_LOW              ,
	DMA_PRIORITY_MEDUIM           ,
	DMA_PRIORITY_HIGH             ,
	DMA_PRIORITY_VERY_HIGH

}DMA_Priority_t;

/*
 * @ENUM: DMA DATA TRANSFER DIRECTION
 * @DMA_DataTransDir_t
 * */
typedef enum{

	DMA_DIR_P2P              ,
	DMA_DIR_P2M              ,
	DMA_DIR_M2M              ,
	DMA_DIR_M2P

}DMA_DataTransDir_t;

typedef enum{

	DMA_CIRCULAR_DISABLED,
	DMA_CIRCULARENABLED

}DMA_CircularMode_t;

typedef enum{

	DMA_8_BITS_PSIZE,
	DMA_16_BITS_PSIZE,
	DMA_32_BITS_PSIZE

}DMA_PSIZE_t;

typedef enum{

	DMA_8_BITS_MSIZE,
	DMA_16_BITS_MSIZE,
	DMA_32_BITS_MSIZE

}DMA_MSIZE_t;

typedef enum{

	DMA_PINC_DISABLE,
	DMA_PINC_ENABLE

}DMA_PINC_t;

typedef enum{

	DMA_MINC_DISABLE,
	DMA_MINC_ENABLE

}DMA_MINC_t;

typedef enum{

	DMA_INTERRUPT_DISABLED,
	DMA_INTERRUPT_ENABLED

}DMA_INT_t;

typedef enum{

	DMA_INT_TCIE_DISABLED,
	DMA_INT_TCIE_ENABLED

}DMA_IntTCIE_t;

typedef enum{

	DMA_INT_THIE_DISABLED,
	DMA_INT_THIE_ENABLED

}DMA_IntTHIE_t;

typedef enum{

	DMA_INT_TEIE_DISABLED,
	DMA_INT_TEIE_ENABLED

}DMA_IntTEIE_t;

typedef struct{

	DMA_IntTCIE_t	DMA_INTERRUPT_TCIE;
	DMA_IntTHIE_t	DMA_INTERRUPT_THIE;
	DMA_IntTEIE_t	DMA_INTERRUPT_TEIE;

}DMA_Interrupt_t;
/********************************************************************************/

/********************************************************************************
 ********************* ### Configurations structure ### *************************
 ********************************************************************************/
typedef struct{

	DMA_Number_t 		DMA_NUMBER			;
	DMA_Channel_t		DMA_CHANNEL_NUMBER	;
	DMA_Priority_t		DMA_PRIORITY		;
	DMA_DataTransDir_t  DMA_DATA_TRANS_DIR	;
	DMA_CircularMode_t	DMA_CIRCULAR_MODE	;
	DMA_PSIZE_t			DMA_PERIPH_SIZE		;
	DMA_MSIZE_t			DMA_MEM_SIZE		;
	DMA_PINC_t			DMA_PERIPH_INC		;
	DMA_MINC_t			DMA_MEM_INC			;
	DMA_INT_t			DMA_INT_EN_STATE	;
	DMA_Interrupt_t		DMA_INTs_STATE		;

}DMA_InitConfig_t;
/********************************************************************************/

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
ErrorState_t DMA_Init(const DMA_InitConfig_t* Init);

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
ErrorState_t DMA_Start(const DMA_InitConfig_t* Init,uint8_t* Copy_pu8Src, uint8_t* Copy_pu8Dst, uint32_t Copy_u32Size);

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
ErrorState_t DMA_Start_IT(const DMA_InitConfig_t* Init,uint8_t* Copy_pu8Src, uint8_t* Copy_pu8Dst, uint32_t Copy_u32Size);

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
ErrorState_t DMA_SetCallBack(DMA_Number_t  DMA_Number ,DMA_Channel_t Channel_Number ,DMA_FlagID_t FlagID ,void (*pv_CallBack)(void));

/*
 *@fn		: DMA_IRQ_Handler
 *@brief	: Set the call back function
 *@param	: DMA_Number		(ENUM: @DMA_Number_t)
 *@param	: Channel_Number			(ENUM: @DMA_Channel_t)
 *@retval	: void
 *
 * */
void DMA_IRQ_Handler(DMA_Number_t  DMA_Number ,DMA_Channel_t Channel_Number);
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
static void DMA_InterruptEnable(const DMA_InitConfig_t* Init);

/*
 *@fn		: DMA_ClearInterruptFlags
 *@brief	: to clear the interrupts flags
 *@param	: DMA_Number			(ENUM:@DMA_Number_t )
 *@param	: Channel_Number		(ENUM:@DMA_Channel_t )
 *@retval	: void
 *
 * */
static void DMA_ClearInterruptFlags(DMA_Number_t  DMA_Number ,DMA_Channel_t Channel_Number);

/*
 *@fn		: DMA_ClearInterruptFlags
 *@brief	: to clear the interrupts flags
 *@param	: DMA_Number			(ENUM:@DMA_Number_t )
 *@param	: Channel_Number		(ENUM:@DMA_Channel_t )
 *@param	: Copy_FlagID			(ENUM:@DMA_FlagID_t )
 *@retval	: void
 *
 * */
static void DMA_ClearInterruptFlag(DMA_Number_t  DMA_Number ,DMA_Channel_t Channel_Number ,DMA_FlagID_t Copy_FlagID);

/*
 *@fn		: DMA_ClearInterruptFlags
 *@brief	: to clear the interrupts flags
 *@param	: DMA_Number			(ENUM:@DMA_Number_t )
 *@param	: Channel_Number		(ENUM:@DMA_Channel_t )
 *@param	: Copy_FlagID			(ENUM:@DMA_FlagID_t )
 *@retval	: uint8_t
 *
 * */
static uint8_t DMA_GetInterruptFlags(DMA_Number_t  DMA_Number ,DMA_Channel_t Channel_Number, DMA_FlagID_t Copy_FlagID);

/*
 *@fn		: DMA_SetDataTransferDirection
 *@brief	: to set the data transfer direction ( M2M , M2P , P2P ,or M2P)
 *@param	: Init			constant pointer to struct (@DMA_InitConfig_t)
 *@retval	: void
 *
 * */
static void DMA_SetDataTransferDirection(const DMA_InitConfig_t* Init);

/* ----------------------------------------------------------------------------------------------------------------------------------*/
/*************************************************************************************************************************************/

#endif
