/**
*@file       Systick_LCfg.c
*@version    1.0.0
*@brief      AUTOSAR Based
*@details    Systick Configratuions Program File.
*@authors    Ahmed Yassin, Farah Ahmed and Mohamed Mabrouk
*/

/*===========================================================================
*   Project          : AUTOSAR  R22-11 MCAL
*   Platform         : ARM
*   Peripherial      : STM32F103C8T6
*   AUTOSAR Version  : R22-11
*   SW Version       : 1.0.0
============================================================================*/
extern void FUNC(void);
#include "Systick.h"

const Systick_ConfigType Systick_Configuration =
{
		SYSTICK_AHB_8, SYSTICK_PERIODIC_INTERVAL, FUNC
};
