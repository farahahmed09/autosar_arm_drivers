/*
 * @file Uart_Regs.h
 * @brief Registers Header file for the Uart module.
 *
 * This file contains the Registers of the Uart module in accordance
 * with the AUTOSAR standard.
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

#ifndef UART_Private_h
#define UART_Private_h

#include "Common_Macros.h"
#include "Platform_Types.h"

/**
 * \file UART_Regs.h
 * \section Brief
 * This is USART Private.
 * \section Details
 * The Registers for the UART needs
 * \section Scope
 * Private
 *
 *
 *
*/
typedef struct
{
	union
{
	uint32 R;
    struct
	{
	uint32 PE    :1;
	uint32 FE    :1;
	uint32 NF    :1;
	uint32 ORE   :1;
	uint32 IDLE  :1;
    uint32 RXNE  :1;
    uint32 TC    :1;
	uint32 TXE   :1;
	uint32 LBD   :1;
	uint32 CTS   :1;
	uint32 unsed :22;
	}B;	
}SR;
	
	union
	{
	uint32 R;
	}DR;
	
	union
	{
	uint32 R;
    struct
	{
	uint32 DIV_Fraction :4;
	uint32 DIV_Mantissa :12;
	uint32 UNUSED       :16;
	}B;	
	}BR;
	
	union
	{
	uint32 R;
    struct
	{
	uint32 SBK   :1;
	uint32 RWU   :1;
	uint32 REnTE :2;
    uint32 IDLEIE:1;
    uint32 RXNEIE:1;
	uint32 TCIE  :1;
	uint32 TXEIE :1;
	uint32 PEIE  :1;
	uint32 PSnPCE:2;
	uint32 WAKE  :1;
	uint32 M     :1;
	uint32 UE    :1;
	uint32 RES   :1;
	uint32 OVER8 :1;
	uint32 UNSED :16;
	
	}B;	
	}CR1;
	
union
	{
	uint32 R;
    struct
	{
	uint32 ADD   :4;
	uint32 RES   :1;
	uint32 LBDL  :1;
	uint32 LBDIE :1;
    uint32 RES_1 :1;
    uint32 LBCL  :1;
	uint32 CPHA  :1;
	uint32 CPOL  :1;
	uint32 CLKEN :1;
	uint32 STOP  :2;
	uint32 LINE  :1;
	uint32 RES_2 :1;
	uint32 UNSED :16;
	}B;	
	}CR2;
	uint32 CR3;
	uint32 GTPR;
}USART_t;
/*
USART 1 IN APB2
USART 2&3 IN APB1
*/
#define  BASE_ADRESS_USART1      0x40013800
#define  BASE_ADRESS_USART2      0x40004400
#define  BASE_ADRESS_USART3      0x40004800

#define MUART1 ((volatile USART_t *)BASE_ADRESS_USART1)
#define MUART2 ((volatile USART_t *)BASE_ADRESS_USART2)
#define MUART3 ((volatile USART_t *)BASE_ADRESS_USART3)


#endif
