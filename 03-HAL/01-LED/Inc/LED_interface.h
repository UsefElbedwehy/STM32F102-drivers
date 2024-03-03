#ifndef  LED_INTERFACE_H_
#define  LED_INTERFACE_H_

#include "GPIO_interface.h"

/********************************************************************************
 ****************** ### FUNCTION DECLARATION SECTION ### ************************
 ********************************************************************************/
void LED_Init(Port_t	Port , Pin_t	PinNum );

void LED_On(Port_t	Port , Pin_t	PinNum );

void LED_Off(Port_t	Port , Pin_t	PinNum );

void LED_Toggle(Port_t	Port , Pin_t	PinNum );
/********************************************************************************/

#endif
