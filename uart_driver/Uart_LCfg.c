/**
 * @file Uart_Cfg.c
 * @brief Configrution source file for the Uart module.
 *
 * This file contains the source Configrution for the Uart module in accordance
 *
 * @copyright [Cairo Racing team -Formula students]
 * @authors [Farah Ahmed]
 * @date [04 Feb 2024]
 *
 * @SWversion 1.0.0
 *
 * @remarks
 *    -Project          : CURT UART MODULE
 *    -Platform         : ARM
 *    -Peripherial      : STM32F103C8T6
 *    -AUTOSAR Version  : NOT AVAILBLE
 */
/*==================================================================================================================================*/

/**
 * \file UART_CFG.c
 * \section Brief
 * This is UART services CFG
 * \section Details
 * The Configrable File For UART
 * \section Scope
 * Public
 *
 *
 *
 */
#include <Uart.h>
#include <Uart_Regs.h>

/**
 * @brief Definition of post build file configurations version
 *
 *
 * @details
 * - Type: Struct
 * - Range: 3
 * - Resolution: Fixed
 * - Unit: Bits
 */

const USART_ConfigType arrOfUART = {
/************************************ USART1 ************************************/
UART1, USART_STD_BAUD_9600, DATA_8_BIT, OneStopbit, USART_MODE_TXRX,
		Paritycontroldisabled, UE_DISEBLE,
		/************************************ USART2 ************************************/
		UART2, USART_STD_BAUD_9600, DATA_8_BIT, OneStopbit, USART_MODE_TXRX,
		Paritycontroldisabled, UE_ENABLE,
		/************************************ USART3 ************************************/
		UART3, USART_STD_BAUD_9600, DATA_8_BIT, OneStopbit, USART_MODE_TXRX,
		Paritycontroldisabled, UE_DISEBLE };
