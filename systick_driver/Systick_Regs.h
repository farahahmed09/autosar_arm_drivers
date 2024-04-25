/*
 * @file Systick_Regs.h
 * @brief Header file for the Systick registers.
 *
 * This file contains the declarations and definitions for the Systick module in accordance
 * with the AUTOSAR standard.
 *
 * @copyright [Cairo Racing team -Formula students]
 * @author [Farah Ahmed , ahmed yassin , mohamed mabrouk]
 * @date [16 0ct 2023]
 *
 * @SWversion 1.0.0
 *
 * @remarks
 *    -Project          : AUTOSAR  R22-11 MCAL
 *    -Platform         : ARM
 *    -Peripherial      : STM32F103C8T6
 *    -AUTOSAR Version  : R22-11
 */
 /*==================================================================================================================================*/

#ifndef SYSTICK_REGS_H
#define SYSTICK_REGS_H

 /*==================================================================================================================================*/


/****************************************************************************
********************************** Includes *********************************
*****************************************************************************/
#include "Std_Types.h"
#include "Platform_Types.h"

/*============================================================================*/
/*---------------------------------Registers definition---------------------------------*/
typedef struct
{
	volatile uint32 CTRL;
	volatile uint32 LOAD;
	volatile uint32 VAL;
	volatile uint32 CALIB;
}SYSTICK_Regs;

/* Systick Base Addresses */
#define SYSTICK_BASE_ADDRESS	((volatile uint32*)(0xE000E010))

#define SYSTICK	((volatile SYSTICK_Regs*)(SYSTICK_BASE_ADDRESS))


#endif
