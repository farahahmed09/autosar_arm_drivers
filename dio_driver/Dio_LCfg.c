/**
*@file       Dio_prg.c
*@version    1.0.0
*@brief      AUTOSAR Based
*@details    Dio Configratuions Program File.
*@authors    Ahmed Yassin, Farah Ahmed and Mohamed Mabrouk
*/

/*===========================================================================
*   Project          : AUTOSAR  R22-11 MCAL
*   Platform         : ARM
*   Peripherial      : STM32F103C8T6
*   AUTOSAR Version  : R22-11
*   SW Version       : 1.0.0
============================================================================*/
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_
/****************************************************************************
*****************************  Includes   ***********************************
*****************************************************************************/

#include "Dio.h"


void Dio_SetPinValue(GPIO_REG *gpio_ptr, Dio_ChannelType ChannelId,
		Dio_LevelType Level) {
	if (Level == STD_LOW) {
		/*turn off the level of the pin*/
		gpio_ptr->BRR = (1 << ChannelId);
	} else {
		/*turn on the level of the pin*/
		gpio_ptr->BSRR = (1 << ChannelId);
	}
}
void Dio_TogglePin(GPIO_REG *gpio_ptr, Dio_ChannelType ChannelId) {
	// check if the pin is in the lower pins (0 to 7)
	TOGGLE_BIT(gpio_ptr->ODR, ChannelId);
}

void Dio_SetPortValue(GPIO_REG *gpio_ptr, Dio_LevelType Level) {

	if (Level == STD_LOW) {
		/*turn off the level of the pin*/
		gpio_ptr->ODR = STD_PORTLOW;
	} else {
		/*turn on the level of the pin*/
		gpio_ptr->ODR = STD_PORTHIGH;
	}
}


#endif /* DIO_INTERFACE_H_ */

