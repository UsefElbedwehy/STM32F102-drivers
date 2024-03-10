#ifndef  SCB_INTERFACE_H_
#define  SCB_INTERFACE_H_

#include "ErrType.h"

typedef enum{

	_16G_0SG=0,
	_8G_2SG=4,
	_4G_4SG=5,
	_2G_8SG=6,
	_0G_16SG=7

}SCB_PriorityGroup_t;

typedef enum{

	AIRCR_VECTRESET 	= 0	,
	AIRCR_VECTCLRACTIVE = 1	,
	AIRCR_SYSRESETREQ 	= 2	,
	AIRCR_PRIGROUP 		= 8	,
	AIRCR_ENDIANNESS 	= 15,
	AIRCR_VECTKEY 		= 16

}SCB_AIRCR_t;

/*@SHCSR_Reg_t*/
typedef enum{

	SHCSR_MEMFAULTACT=0,
	SHCSR_BUSFAULTACT,
	SHCSR_USGFAULTACT=3,
	SHCSR_SVCALLACT=7,
	SHCSR_MONITORACT,
	SHCSR_PENDSVACT=10,
	SHCSR_SYSTICKACT,
	SHCSR_USGFAULTPENDED,
	SHCSR_MEMFAULTPENDED,
	SHCSR_BUSFAULTPENDED,
	SHCSR_SVCALLPENDED,
	SHCSR_MEMFAULTENA,
	SHCSR_BUSFAULTENA,
	SHCSR_USGFAULTENA

}SCB_SHCSR_t;

typedef enum{

	UFSR_UNDEFINSTR   ,
	UFSR_INVSTATE     ,
	UFSR_INVPC        ,
	UFSR_NOCP		  ,
	UFSR_UNALIGNED = 8,
	UFSR_DIVBYZERO = 9

}SCB_UFSR_t;


/*
 * @fn    : SCB_SetPriorityGroup
 * @brief : splits the PRI_n fields in the Interrupt Priority Registers
 * 										into separate group priority and subpriority fields.
 * @param : PriorityGroup    (ENUM: @SCB_PriorityGroup_t)
 * @retval:  Local_ErrorState (ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SCB_SetPriorityGroup(SCB_PriorityGroup_t PriorityGroup);

/*
 * @fn    : SCB_SetSysHandlerState
 * @brief : enables the system handlers
 * @param : SCB_SHCSR_Bit    (ENUM: @SCB_SHCSR_t)
 * @retval:  Local_ErrorState (ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SCB_SetSysHandlerState(SCB_SHCSR_t SCB_SHCSR_Bit);

/*
 * @fn    : SCB_ClearSysHandlerState
 * @brief : disables the system handlers
 * @param : SCB_SHCSR_Bit    (ENUM: @SCB_SHCSR_t)
 * @retval:  Local_ErrorState (ENUM: @ErrorState_t)
 *
 * */
ErrorState_t SCB_ClearSysHandlerState(SCB_SHCSR_t SCB_SHCSR_Bit);

/*
 * @fn    : SCB_EnableDivByZero
 * @brief : enables division by zero usage fault exception
 * @param : SCB_SHCSR_Bit    (ENUM: @SCB_UFSR_t)
 * @retval:  Local_ErrorState (ENUM: @ErrorState_t)
 *
 * */
void SCB_EnableDivByZero(SCB_UFSR_t SCB_UFSR_Bit);

/*
 * @fn    : SCB_DisableDivByZero
 * @brief : disables division by zero usage fault exception
 * @param : SCB_SHCSR_Bit    (ENUM: @SCB_UFSR_t)
 * @retval:  Local_ErrorState (ENUM: @ErrorState_t)
 *
 * */
void SCB_DisableDivByZero(SCB_UFSR_t SCB_UFSR_Bit);

#endif
