/*
 * @file Uart.h
 * @brief Header file for the Uart module.
 *
 * This file contains the declarations and definitions for the Uart module in accordance
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

#ifndef UART_Interface_h
#define UART_Interface_h

/**
 * \mainpage
 * \section Brief
 * This is file includes headers and Macros for the USART Section.
 * \section Details
 * We have functions explaind in function/3 to each USART.
 * \section SoftwareContext
 * This is the Software Context
 * this service is used to use UART by init it then we can transimate and recieve
 *
 *
 *
 */

/****************************************************************************
*****************************  Includes   ***********************************
*****************************************************************************/

#include <Uart_Cfg.h>
#include <Uart_Regs.h>

  
  /*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Enable of USART prescalar and outputs */
typedef uint8 USART_Enable;    

/* Enable of USART Parity Control*/
typedef uint8 USART_ParityControlEnable;    

/* Enable of USART PE Interrupt */
typedef uint8 USART_PE_InterruptEnable;

/* Enable of USART TXE Interrupt */
typedef uint8 USART_TXE_InterruptEnable;

/* Enable of USART Transmission Complete Interrupt */
typedef uint8 USART_TC_InterruptEnable;

/* Enable of USART RXNE Interrupt */
typedef uint8 USART_RXNE_InterruptEnable;

/* Enable of USART IDLE Interrupt */
typedef uint8 USART_IDLE_InterruptEnable;

/* Enable of USART Transmitter */
typedef uint8 USART_TransmitterEnable;

/* Enable of USART Receiver */
typedef uint8 USART_ReceiverEnable;

/* Enable of USART LIN Mode */
typedef uint8 USART_LINEnable;

/* Enable of Clock */
typedef uint8 USART_ClockEnable;

/* Enable of USART LIN Break Detection Interrupt */
typedef uint8 USART_LIN_BreakDetectInterruptEnable;

/* Enable of USART CTS Interrupt */
typedef uint8 USART_CTS_InterruptEnable;

/* Enable of USART CTS */
typedef uint8 USART_CTSEnable;

/* Enable of USART RTS */
typedef uint8 USART_RTSEnable;

/* Enable of USART DMA Transmitter */
typedef uint8 USART_DMATransmitterEnable;

/* Enable of USART DMA receiver */
typedef uint8 USART_DMAReceiverEnable;

/* Enable of USART Smartcard mode */
typedef uint8 USART_SmartCardEnable;

/* Enable of USART Smartcard NACK */
typedef uint8 USART_SmartCardNACKEnable;

/* Enable of USART IrDA mode */
typedef uint8 USART_IrDAEnable;

/* Enable of USART Error Interrupt */
typedef uint8 USART_Error_InterruptEnable;

/* USART Guard Time */
typedef uint8 USART_GuardTime;

/* USART Prescaler */
typedef uint8 USART_Prescaler;


/*---------------------------------general enums-------------------------------*/
/**
  * @brief Enumeration for Choosing the PIN.
  *
  *
  * @details
  * - Type: OverSampling enum
  * - Range: 2
  * - Resolution: 1U
  * - Unit: Bits
  */

typedef enum {
	oversamplingby16, oversamplingby8

}OVER8;

/**
  * @brief Enumeration for Choosing the PIN.
  *
  *
  * @details
  * - Type: Enable enum
  * - Range: 2
  * - Resolution: 1U
  * - Unit: Bits
  */
typedef enum {
	UE_DISEBLE, UE_ENABLE

} UE;
/**
  * @brief Enumeration for Choosing the PIN.
  *
  *
  * @details
  * - Type: Data Length enum
  * - Range: 2
  * - Resolution: 1U
  * - Unit: Bits
  */
typedef enum {
	DATA_8_BIT, DATA_9_BIT

} M;
/**
  * @brief Enumeration for Choosing the PIN.
  *
  *
  * @details
  * - Type: State enum
  * - Range: 2
  * - Resolution: 1U
  * - Unit: Bits
  */
typedef enum {
	IdleLine, AddressMark

} WAKE;
/**
  * @brief Enumeration for Choosing the PIN.
  *
  *
  * @details
  * - Type: Parity enum
  * - Range: 3
  * - Resolution: 1U
  * - Unit: Bits
  */
typedef enum {
	Paritycontroldisabled, Evenparity = 1, ODDparity = 3
} PSnPCE;

/**
  * @brief Enumeration for Choosing the PIN.
  *
  *
  * @details
  * - Type: OverSampling enum
  * - Range: 2
  * - Resolution: 1U
  * - Unit: Bits
  */

typedef enum {
	TE_DISEBLE, TE_ENABLE

} TE;
typedef enum {
	RE_DISEBLE, RE_ENABLE

} RE;
/**
  * @brief Enumeration for Choosing the PIN.
  *
  *
  * @details
  * - Type: Stop bits enum
  * - Range: 2
  * - Resolution: 1U
  * - Unit: Bits
  */
typedef enum {
	OneStopbit, HalfStopbit, towStopbit, oneAndHalfStopbit
} STOP;
/**
  * @brief Enumeration for Choosing the PIN.
  *
  *
  * @details
  * - Type: Mode enum
  * - Range: 2
  * - Resolution: 1U
  * - Unit: Bits
  */
typedef enum {
	USART_MODE_ONLY_RX = 1, USART_MODE_ONLY_TX, USART_MODE_TXRX
} USART_MODE;
/**
  * @brief Enumeration for Choosing the PIN.
  *
  *
  * @details
  * - Type: UART Number enum
  * - Range: 2
  * - Resolution: 1U
  * - Unit: Bits
  */
typedef enum {
	UART1, UART2, UART3
} USART_ID;
/**
  * @brief Enumeration for Choosing the PIN.
  *
  *
  * @details
  * - Type: Baud Rate enum
  * - Range: 10
  * - Resolution: 1U
  * - Unit: Bits
  */
typedef enum {
	USART_STD_BAUD_2400 = 0xd05,
	USART_STD_BAUD_9600 = 0x341,
	USART_STD_BAUD_19200 = 0x1a0,
	USART_STD_BAUD_38400 = 0xd0,
	USART_STD_BAUD_57600 = 0x8a,
	USART_STD_BAUD_115200 = 0x45,
	USART_STD_BAUD_230400 = 0x22,
	USART_STD_BAUD_460800 = 0x11,
	USART_STD_BAUD_921600 = 0x8,
	USART_STD_BAUD_2250000 = 0x3,
} USART_BAUD;
/**
  * @brief Struct of array of struct for Choosing the Configurations of each UART.
  *
  *
  * @details
  * - Type: struct
  * - Unit: Bits
  */
/* Structure to hold the configuration data for the UART Driver */
typedef struct {
	USART_ID USARTid;
	USART_BAUD USARTBaud;
	M USARTWordLength;
	STOP USARTStopBits;
	USART_MODE USARTMode;
	PSnPCE USARTParitySelection;
	    //u8 USART_HWFlowControl;
    //u8 UART_dma_mode;
	UE USARTEnableType;
	  //USART_PE_InterruptEnable    USARTPEInterruptEnable;

} USART_Configurations;

typedef struct {
	USART_Configurations UART_Array[NUMBER_OF_USED_UARTS];
} USART_ConfigType;

extern const USART_ConfigType arrOfUART;
/**
 * @brief initializes the configuration of multiple UART together
 *
 * @param[in] ConfigPtr pointer to the configuration structure containing all the configurations
 */
void USART_VidInit(const USART_ConfigType *USART_CFG);
/**
 * @brief Transmit Data Function
 *
 * @param[in] UARTID       UART id (contains UART number).
 * @param[in] string_Copy_U8Data Pointer to data.
 * @param[in] Copy_U8Length       Length of the pointer data.
 * @param[in] Copy_U32TimeOut TimeOut for the function
 */
void USART_TransmitString(USART_ID UART_ID, uint8 *string_Copy_U8Data,
		uint32 Copy_U8Length, uint32 Copy_U32TimeOut);
/**
 * @brief Receive Data Function
 *
 * @param[in] UARTID       UART id (contains UART number).
 * @param[in] Copy_U32TimeOut TimeOut for the function
 */
uint8 USART_ReceiveByte(USART_ID UART_ID, uint32 Copy_U32TimeOut);
//uint8* USART_ReceiveString(USART_ID UART_ID);
#endif
