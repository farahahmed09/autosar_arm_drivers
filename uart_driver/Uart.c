/**
 * @file Uart.c
 * @brief source file for the Uart module.
 *
 * This file contains the declarations and definitions for the Uart module in accordance
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

/****************************************************************************
 *****************************  Includes   ***********************************
 *****************************************************************************/

/**
 * \file UART_Program.c
 * \section Brief
 * This is UART services Prg
 * \section Details
 * The module drives the UART functionality for SW
 * \section Scope
 * Public
 *
 *
 *
 */
#include <Uart.h>
#include <Uart_Cfg.h>
#include <Uart_Regs.h>
#include "Rcc.h"
#include "Dio.h"
#include "Port.h"

/*
 DIV BY 16
 ENABLE USART
 CHOICE 8 BIT Copy_uint8Data
 NO ADRESS AND NO LINE
 ParitycontrolEnabled
 CHOICE EVEN PARITY BIT
 TRANSIMATE IS ENABLE
 BOUD RATE 9600

 */

//uint8 received_string[MAX_STRING_TO_BE_RECEIVED_USART];
void (*USART1_CallBack)(void);
void (*USART2_CallBack)(void);
void (*USART3_CallBack)(void);

const USART_ConfigType *UART_PTR = NULL_PTR;
volatile USART_t *UART_NUM = NULL_PTR;

/***********************************[1]***********************************************
 * Service Name: UART_VidInit
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Renterancy: Reentrant
 * Parameters (in): Constant USART_ConfigType
 * Parameters (InOut): None
 * Parameters (Out): None
 * Return value: None
 * Description: Set the configration of the given UART(s) to be enabled.
 ************************************************************************************/

/**
 * \section Service_Name
 * UART_VidInit
 *
 * \section Service_ID_hex
 * 0x01
 *
 * \section Sync_Async
 * Synchronous
 *
 * \section Renterancy
 * Reentrant
 *
 * \section Parameters_in
 * \param[in] Constant USART_ConfigType(Pointer of Arrays)\PeripheralID--->Global Array to configrate the used UART(S).
 * \param[out] None
 * \param[in-out] None
 *
 * \section Return_value
 * None
 *
 * \section Description
 *  Set the configration of the given UART(s) to be enabled.
 * 
 * \section Activity_diagram
 *
 * \startuml 
 *   start
 *   :Get all the configurations from The Global Array to Struct;
 *	if(Is there any UARTS configurations in the global Array?) then (Yes)
 *	repeat
 *  if (UART is enabled to Initalize) then (Yes)
 *  switch (Which UART is used?)
 *	case ( A)
 *	:UART1;
 *	case ( B)
 *	:UART2;
 *	case ( C)
 *	:UART3;
 *	endswitch
 *	:Enable the RCC for the UART;
 *  :Configurate the UART Pins;
 *	:Set the UART WordSize;
 *	:Set the UART Stop-Bits;
 *  :Set UART Mode;
 *  if (ParityControl Bit is Enabled) then (Yes)
 *	switch (ParitySelection)
 *	case ( A)
 * 	:EVEN;
 *	case ( B)
 *	:ODD;
 *	endswitch
 *  else (no)
 *  endif
 *	:Set the buadrate;
 *	:ENABLE THE UART;
 * 	else (no)
 * endif
 *	repeat while (There's other UARTs left to Initalize?) is (Yes) not (no)
 *	else (no)
 *	endif
 * end
 * \enduml
 */

void USART_VidInit(const USART_ConfigType *USART_CFG) {
    /* Set the global pointer to the provided USART configuration */
	UART_PTR = USART_CFG;
    /* check if the pointer is null */
	if (UART_PTR == NULL_PTR) 
    {
		return;
	} 
    else 
    {
        /* Iterate through each UART in the configuration */
		for (int i = 0; i < NUMBER_OF_USED_UARTS; i++) 
        {
            /*  skip the disabled uarts */
			if (UART_PTR->UART_Array[i].USARTEnableType == UE_DISEBLE) {
				continue;
			} 
            else 
            {
                /* Configure the GPIO pins based on the selected UART */
				switch (UART_PTR->UART_Array[i].USARTid) 
                {
				case UART1:
					Port_SetPinDirection(A9, PORT_PIN_OUT_2MHz);
					Port_SetPinDirection(A10, PORT_PIN_IN);
					Port_SetPinMode(A9, AF_OPP);
					Port_SetPinMode(A10, FLOATING_INPUT);
					UART_NUM = MUART1;
					break;
				case UART2:
					Port_SetPinDirection(A2, PORT_PIN_OUT_2MHz);
					Port_SetPinDirection(A3, PORT_PIN_IN);
					Port_SetPinMode(A2, AF_OPP);
					Port_SetPinMode(A3, FLOATING_INPUT);
					UART_NUM = MUART2;
					break;
				case UART3:
					Port_SetPinDirection(B10, PORT_PIN_OUT_2MHz);
					Port_SetPinDirection(B11, PORT_PIN_IN);
					Port_SetPinMode(B10, AF_OPP);
					Port_SetPinMode(B11, FLOATING_INPUT);
					UART_NUM = MUART3;
					break;
				}
                /* configure uart parameters */
				UART_NUM->BR.R = USART_CFG->UART_Array[i].USARTBaud;
				UART_NUM->CR1.B.M = USART_CFG->UART_Array[i].USARTWordLength;
				UART_NUM->CR2.B.STOP = USART_CFG->UART_Array[i].USARTStopBits;
				UART_NUM->CR1.B.REnTE = USART_CFG->UART_Array[i].USARTMode;
				UART_NUM->CR1.B.PSnPCE =
						USART_CFG->UART_Array[i].USARTParitySelection;
				/* Start the USART */
				UART_NUM->CR1.B.UE = UE_ENABLE;
			}
		}
	}
}
/***********************************[2]***********************************************
 * Service Name: USART_ReceiveByte
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Renterancy: Non-Reentrant
 * Parameters (in): UART_ID
 * Parameters (InOut): None
 * Parameters (Out): None
 * Return value: Copy_uint8Data
 * Description: Recieve the Sent Data by the user.
 ************************************************************************************/

/**
 * \section Service_Name
 * USART_ReceiveByte
 *
 * \section Service_ID_hex
 * 0x02
 *
 * \section Sync_Async
 * Synchronous
 *
 * \section Renterancy
 * Non-Reentrant
 *
 * \section Parameters_in
 * \param[in] UART_ID
 * \param[out] None
 * \param[in-out] None
 *
 * \section Return_value
 * Copy_uint8Data
 *
 * \section Description
 *  Recieve the Sent Data by the user.
 * 
 * \section Sequence_diagram
 *
 * @startuml
 * participant USART1_ReceiveByte as "USART1_ReceiveByte()"
 * participant UART_ID as "UART_ID"
 * participant Copy_uint8Data as "Copy_uint8Data"
 * participant Copy_U32TimeOut as "Copy_U32TimeOut"
 *
 * USART_ReceiveByte -> UART_ID : Read UART ID
 * activate UART_ID
 * UART_ID -> Copy_uint8Data : Initialize Copy_uint8Data variable
 * activate Copy_uint8Data
 *
 *
 * @enduml
 * \section Activity_diagram
 * \startuml 
 *   start
 *  :Initialize local variables;
 *  switch (Which UART is used?)
 *	case ( A)
 *	:UART1;
 *	case ( B)
 *	:UART2;
 *	case ( C)
 *	:UART3;
 *	endswitch
 *  while (Data has been sent) is (No)
 *  if(Timeout is less than 5s) then (Yes)
 *  :Increment timeout;
 *	else (no)
 *  :Data equals rublish;
 *	end
 *	endif
 *  endwhile (Yes)
 *  :Data is received;
 *  :timeout equals 0;
 *	:return recievedData;
 * end
 * \enduml
 */
uint8 USART_ReceiveByte(USART_ID UART_ID, uint32 Copy_U32TimeOut) {
	uint8 Copy_U8Data = 0;
    /* variable to track the timeout */
	uint32 THRESHOLD_VALUE = 0;
    /* switch on the used uart */
	switch (UART_ID) {
	case UART1:
		UART_NUM = MUART1;
		break;
	case UART2:
		UART_NUM = MUART2;
		break;
	case UART3:
		UART_NUM = MUART3;
		break;
	}
    /* wait for the flag to be set or the timeout */
	while ((UART_NUM->SR.B.RXNE == 0)
			&& (THRESHOLD_VALUE < Copy_U32TimeOut * 1000))
		THRESHOLD_VALUE++;
    // Check if the timeout didn't occur
	if ((THRESHOLD_VALUE != (Copy_U32TimeOut * 1000))) {
        /* Read the received data from the data register*/
		Copy_U8Data = UART_NUM->DR.R;
		THRESHOLD_VALUE = 0;
	} else
		Copy_U8Data = '\0';
        /* clear the flag */
	UART_NUM->SR.B.RXNE = 0;
    /* return the data */
	return Copy_U8Data;
}
/***********************************[3]***********************************************
 * Service Name: USART_VidSendChar
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Renterancy: Non-Reentrant
 * Parameters (in): UART_ID, Copy_uint8Data
 * Parameters (InOut): None
 * Parameters (Out): None
 * Return value: void
 * Description: send char .
 ************************************************************************************/
/**
 * \section Service_Name
 * USART_VidSendChar
 *
 *
 * \section Service_ID_hex
 * 0x06
 *
 * \section Sync_Async
 * Synchronous
 *
 * \section Renterancy
 * Non-Reentrant
 *
 * \section Parameters_in
 * \param[in] UART_ID, Copy_uint8Data
 * \param[out] None
 * \param[in-out] None
 *
 * \section Return_value
 * Void
 *
 * \section Description
 *  send char.
 *
 * \section Sequence_diagram
 *
 * \startuml
 *  actor User
 *
 *	User -> Code: USART_VidSendChar(Copy_uint8Data)
 *	activate Code
 *
 *	Code -> MUART: Choose which UART is used
 *	Code -> MUART: Set MUART->SR.B.TC to 0
 *	activate MUART
 *	MUART --> Code: MUART->SR.B.TC set to 0
 *	deactivate MUART
 *
 *	Code -> MUART: Assign Copy_uint8Data to MUART->DR.R
 *	activate MUART
 *	MUART --> Code: Copy_uint8Data assigned to MUART->DR.R
 *	deactivate MUART
 *
 *	Code -> MUART: Check if MUART->SR.B.TC is false
 *	activate MUART
 *	alt (Condition is true)
 *	  MUART --> Code: Condition is true
 *	  Code -> Code: Continue loop
 *	  loop
 *	else (Condition is false)
 *	  MUART --> Code: Condition is false
 *	  Code -> Code: Break loop
 *	end
 *	deactivate MUART
 *
 *	Code -> MUART: Set MUART->SR.B.TC to 0
 *	activate MUART
 *	MUART --> Code: MUART->SR.B.TC set to 0
 *	deactivate MUART
 *
 *	deactivate Code
 *
 * \enduml
 *
 * \section Activity_diagram
 *
 * \startuml
 *  start
 *  switch (Which UART is used?)
 *	case ( A)
 *	:UART1;
 *	case ( B)
 *	:UART2;
 *	case ( C)
 *	:UART3;
 *	endswitch
 *  :Initialize MUART->SR.B.TC to 0;
 *  :MUART->DR.R = Copy_uint8Data;
 *	repeat
 *	  :Check if MUART->SR.B.TC is false;
 *	  if (Condition)
 *		--> repeat
 *	  else
 *		break
 *   endif
 *	repeat while (Condition)
 *	:MUART->SR.B.TC = 0;
 * end
 * \enduml
 */
void USART_VidSendChar(USART_ID UART_ID, uint8 Copy_uint8Data) {
    /* switch to select the used uart */
	switch (UART_ID) {
	case UART1:
		UART_NUM = MUART1;
		break;
	case UART2:
		UART_NUM = MUART2;
		break;
	case UART3:
		UART_NUM = MUART3;
		break;
	}
    /* clear the flag before sending */
	UART_NUM->SR.B.TC = 0;
    /* load the data to be transmitted into the data register */
	UART_NUM->DR.R = Copy_uint8Data;
    /* wait for the flag */
	while (!UART_NUM->SR.B.TC)
		;
}

/***********************************[4]***********************************************
 * Service Name: USART_TransmitString
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Renterancy: Non-Reentrant
 * Parameters (in): UART_ID, Pointer to string
 * Parameters (InOut): None
 * Parameters (Out): None
 * Return value: None
 * Description: Transmit the  DataString .
 ************************************************************************************/
/**
 * \section Service_Name
 * USART_TransmitString
 *
 *
 * \section Service_ID_hex
 * 0x08
 *
 * \section Sync_Async
 * Synchronous
 *
 * \section Renterancy
 * Non-Reentrant
 *
 * \section Parameters_in
 * \param[in] UART_ID, Pointer to string, Copy_uint8Length, Copy_U32TimeOut
 * \param[out] None
 * \param[in-out] None
 * \section Return_value
 * Void
 *
 * \section Description
 *  send a string of data.
 *
 * \section Sequence_diagram
 * \startuml
 *  actor User
 *
 * User -> Code: SendStringWithHash(string_Copy_uint8Data)
 * activate Code
 *
 * Code -> Code: Initialize i to 0
 * Code -> Code: Check if string_Copy_uint8Data[i] is not null
 * activate Code
 *
 * Code -> UART: Send character string_Copy_uint8Data[i]
 * activate UART
 * UART --> Code: Character sent
 *
 * Code -> Code: Increment i
 * Code --> Code: Check if string_Copy_uint8Data[i] is not null
 * deactivate Code
 *
 * Code -> Code: Check if string_Copy_uint8Data[i] is not null
 * activate Code
 * Code -> UART: Choose UART_ID
 * Code -> UART: Send character string_Copy_uint8Data[i]
 * activate UART
 * UART --> Code: Character sent
 *
 * Code -> UART: Send character '#'
 * activate UART
 * UART --> Code: Character sent
 *
 * deactivate Code
 * \enduml
 *
 * \section Activity_diagram
 *
 * \startuml
 *  start
 * :Initialize i to 0;
 *  repeat
 * :Check if string_Copy_uint8Data[i] is not null;
 * if (Condition)
 *  :Send string_Copy_uint8Data[i] over UART;
 *     --> Continue
 *    else
 *      break
 *    endif
 *     --> repeat
 *  repeat while (Condition)
 * :Send '#' over UART;
 * stop
 * \enduml
 */

void USART_TransmitString(USART_ID UART_ID, uint8 *string_Copy_uint8Data,
		uint32 Copy_uint8Length, uint32 Copy_U32TimeOut) {
    // Variable to track timeout threshold
	uint32 THRESHOLD_VALUE = 0;
	for (int i = 0; i < Copy_uint8Length; i++)
     {
        /* Send each character via USART*/
		USART_VidSendChar(UART_ID, string_Copy_uint8Data[i]);
        /* wait for the flag or timeout */
		while ((!UART_NUM->SR.B.TC)&& (THRESHOLD_VALUE < Copy_U32TimeOut * 1000))
			THRESHOLD_VALUE++;
        /* check if timeout occured */
		if (THRESHOLD_VALUE == Copy_U32TimeOut * 1000)
			string_Copy_uint8Data = '\0';
		else 
        {
            /* reset the threshold */
			THRESHOLD_VALUE = 0;
		}
	}
}

/***********************************[5]***********************************************
 * Service Name: USART_ReceiveString
 * Service ID[hex]: 0x05
 * Sync/Async: Synchronous
 * Renterancy: Non-Reentrant
 * Parameters (in): UART_ID
 * Parameters (InOut): None
 * Parameters (Out): None
 * Return value: pointer to string
 * Description: Recieve the Sent DataString by the user.
 ************************************************************************************/

/**
 * \section Service_Name
 * USART5_ReceiveString
 *
 *
 * \section Service_ID_hex
 * 0x05
 *
 * \section Sync_Async
 * Synchronous
 *
 * \section Renterancy
 * Non-Reentrant
 *
 * \section Parameters_in
 *
 * \param[in] UART_ID
 *
 * \param[out] None
 *
 * \param[in-out] None
 *
 * \section Return_value
 * pointer to string
 *
 * \section Description
 *  Recieve the Sent DataString by the user.
 *
 * \section Sequence_diagram
 * \startuml
 *  actor User
 *
 * User -> Code: ReceiveString(UART_ID)
 * activate Code
 *
 * Code -> Code: Initialize i to 0
 * activate Code
 *
 * Code -> UART: Receive character
 * activate UART
 * UART --> Code: Character Received
 *
 * Code -> Code: Increment i
 * Code --> Code: Check if received_string[i] is not null
 * deactivate Code
 *
 * Code -> Code: Check if received_string1[i] is not null
 * activate Code
 * Code -> UART: Choose UART_ID
 * Code -> UART: receive character received_string1[i]
 * activate UART
 * UART --> Code: Character Recieved
 *
 * Code -> UART: Set Last Element in Array '\0'
 * activate UART
 * UART --> Code: Character received
 *
 * deactivate Code
 * \enduml
 * \section Activity_diagram
 *
 * \startuml
 *  start
 *  :Initialize local variables;
 *  switch (Which UART is used?)
 *	case ( A)
 *	:UART1;
 *	case ( B)
 *	:UART2;
 *	case ( C)
 *	:UART3;
 *	endswitch
 *  while (Reach end of the string) is (NO)
 *  :store the received data in the string;
 *  endwhile (YES)
 *  :put null terminator at the end of the string;
 *  :return recievedDataString;
 * end
 * \enduml
 */
/*
 uint8* USART_ReceiveString(USART_ID UART_ID) {
 uint8 i = 0;
 received_string[i] = USART_ReceiveByte(UART_ID);
 while (received_string[i] != '\r') {
 ++i;
 received_string[i] = USART_ReceiveByte(UART_ID);
 }
 received_string[i] = '\0';
 return (received_string);
 }
 */

/* Set the callback function for USART1 interrupt */

void USART1_VidSetCallBack(void (*ptr)(void)) {
	USART1_CallBack = ptr;
}

/* Set the callback function for USART2 interrupt */
void USART2_VidSetCallBack(void (*ptr)(void)) {
	USART2_CallBack = ptr;
}

/* Set the callback function for USART3 interrupt */
void USART3_VidSetCallBack(void (*ptr)(void)) {
	USART3_CallBack = ptr;
}

void USART1_IRQHandler(void) {
    /* Clear the USART1 status register */
	MUART1->SR.R = 0;
	USART1_CallBack();
}

void USART2_IRQHandler(void) {
    /* Clear the USART2 status register */
	MUART2->SR.R = 0;
	USART1_CallBack();
}

void USART3_IRQHandler(void) {
    /* Clear the USART1 status register */
	MUART3->SR.R = 0;
	USART1_CallBack();
}
