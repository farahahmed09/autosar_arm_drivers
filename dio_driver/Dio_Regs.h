/**
 * @file	Dio_Regs.h
 * @brief header file for the Dio registers.
 *
 * This file contains the Registers for the Dio module in accordance
 * with the AUTOSAR standard.
 *
 * @copyright [Cairo Racing team -Formula students]
 * @author [Ahmed Yassin, Farah Ahmed and Mohamed Mabrouk]
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


#ifndef DIO_REGS_H
#define DIO_REGS_H


/****************************************************************************
*****************************  Includes   ***********************************
*****************************************************************************/
#include "Std_Types.h"
#include "Platform_Types.h"
/*============================================================================*/
/****************************************************************************
************************  Dio BASE ADDRESS   *************************************
*****************************************************************************/

/*Base Addresses for PORTA & PORTB & PORTC*/
#define GPIOA_BASE_ADDRESS		0x40010800
#define GPIOB_BASE_ADDRESS		0x40010C00
#define GPIOC_BASE_ADDRESS		0x40011000



 /**
  * \section Brief
  * Structure used in a pointer that helps access registers in the DIO peripheral.
  *
  * \section Details
  * - Type: Structure
  * - Range: 0x40010800 : 0x4001081C, 0x40010C00 : 0x400210C1C,0x40011000 : 0x4001101C
  * - Resolution: uint32
  * - Unit: Address
  */
/*Register Definitions*/
typedef struct {
	uint32 CRL;
	uint32 CRH;
	uint32 IDR;
	uint32 ODR;
	uint32 BSRR;
	uint32 BRR;
	uint32 LCK;
} GPIO_REG;

#define GPIOA          ((volatile GPIO_REG *)  (GPIOA_BASE_ADDRESS))
#define GPIOB          ((volatile GPIO_REG *)  (GPIOB_BASE_ADDRESS))
#define GPIOC          ((volatile GPIO_REG *)  (GPIOC_BASE_ADDRESS))
#endif
