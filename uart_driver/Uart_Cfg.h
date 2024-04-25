/**
 * @file Uart_Cfg.c
 * @brief Configrution Header file for the Uart module.
 *
 * This file contains the Header Configrution for the Uart module in accordance
 *
 * @copyright [Cairo Racing team -Formula students]
 * @authors [ Farah Ahmed]
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

#ifndef UART_Config_h
#define UART_Config_h

/**
 * \file UART_cfg.h
 * \section Brief
 * This is UART configuration
 * \section Details
 * The available configuration allowed in the UART
 * \section Scope
 * Private
 *
 *
 *
*/

#include <Uart_Regs.h>

#define NUMBER_OF_USED_UARTS 	3
#define F_CPU              8000000
#define MAX_STRING_TO_BE_RECEIVED_USART 100

#endif
