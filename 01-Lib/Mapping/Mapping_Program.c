
s32 MAPPING_s32Map_Value(s32 Copy_s32InputMax,s32 Copy_s32InputMin,s32 Copy_s32OutputMax,s32 Copy_s32OutputMin,s32 Copy_s32InputValue)
{
	s32	Local_s32OutputValue;
	Local_s32OutputValue=(((Copy_s32OutputMax-Copy_s32OutputMin)*(Copy_s32InputValue-Copy_s32InputMin))/(Copy_s32InputMax-Copy_s32InputMin))+Copy_s32OutputMin;
	return Local_s32OutputValue;
}