/**
 *@file       Dio_prg.c
 *@version    1.0.0
 *@brief      AUTOSAR Based
 *@details    Dio Header File.
 *@authors     Ahmed Yassin, Farah Ahmed and Mohamed Mabrouk
 */

/*===========================================================================
 *   Project          : AUTOSAR  R22-11 MCAL
 *   Platform         : ARM
 *   Peripherial      : STM32F103C8T6
 *   AUTOSAR Version  : R22-11
 *   SW Version       : 1.0.0
 ============================================================================*/
#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

/*============================================================================*/
/**
* \file DIO.h
*
* @section Introduction
*
* Welcome to the documentation for reset and clock control (DIO) driver designed for
* the STM32F103 microcontroller.
* This documentation provides a comprehensive overview of the DIO driver's functionality, usage,
* and API within the context of embedded systems.
*
*
* \section Scope
* Public
*
* \section References
* - **stm32f10xxx-cortexm3-programming-manual**
*
* \section Component_History
*  - **V.1.0.0:** Initial release.
*
* \section Author
* 
*
*/
/****************************************************************************
 *****************************  Includes   ***********************************
 *****************************************************************************/

#include "Common_Macros.h"
#include "Dio_Regs.h"
#include "Dio_Cfg.h"

/****************************************************************************
 *                        Version info                                      *
 *****************************************************************************/

 /**
  * @brief Defination of RCC Module Id
  *
  *
  * @details
  * - Type: define
  * - Range: 120U
  * - Resolution: Fixed
  * - Unit: Bits
  */
 
 /* DIO Module Id */
#define DIO_MODULE_ID    	(120U)

/**
 * @brief Defination of Dio Instance ID
 *
 *
 * @details
 * - Type: define
 * - Range: 0U
 * - Resolution: Fixed
 * - Unit: Bits
 */

/* DIO Instance Id */
#define DIO_INSTANCE_ID    				(0U)

/**
 * @brief Defination of Module Version 1
 *
 *
 * @details
 * - Type: define
 * - Range: 1U
 * - Resolution: Fixed
 * - Unit: Bits
 */

/*
 * Module Version 1
 */
#define DIO_SW_VERSION      	     	(1U)

 /**
  * @brief Defination of AUTOSAR Version R22-11
  *
  *
  * @details
  * - Type: define
  * - Range: 22U
  * - Resolution: Fixed
  * - Unit: Bits
  */

/*
 * AUTOSAR Version R22-11
 */
#define DIO_AR_RELEASE_VERSION  	 	(22U)

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
 
 /**
  * @brief Defination of passing parameters to be used in Det_ReportError as wrong Channel in code
  *
  *
  * @details
  * - Type: define
  * - Range: 0x0A
  * - Resolution: Fixed
  * - Unit: Bits
  */
 
 /* DET code to report Invalid Channel */
#define DIO_E_PARAM_INVALID_CHANNEL_ID (uint8)0x0A

/**
 * @brief Defination of type of error in passing parameter to be used in Det_ReportError as wrong configurations in code
 *
 *
 * @details
 * - Type: define
 * - Range: 0x10
 * - Resolution: Fixed
 * - Unit: Bits
 */

/* Dio_Init API service called with NULL pointer parameter */
#define DIO_E_PARAM_CONFIG             (uint8)0x10

/**
 * @brief Defination of passing parameters to be used in Det_ReportError as wrong Port_id in code
 *
 *
 * @details
 * - Type: define
 * - Range: 0x14
 * - Resolution: Fixed
 * - Unit: Bits
 */

/* DET code to report Invalid Port */
#define DIO_E_PARAM_INVALID_PORT_ID    (uint8)0x14

/**
 * @brief Defination of passing parameters to be used in Det_ReportError as wrong Group in code
 *
 *
 * @details
 * - Type: define
 * - Range: 0x1F
 * - Resolution: Fixed
 * - Unit: Bits
 */


/* DET code to report Invalid Channel Group */
#define DIO_E_PARAM_INVALID_GROUP      (uint8)0x1F

/**
 * @brief Defination of passing parameters to be used in Det_ReportError as Wrong Null pointer in code
 *
 *
 * @details
 * - Type: define
 * - Range: 0x20
 * - Resolution: Fixed
 * - Unit: Bits
 */

/*
 * The API service shall return immediately without any further action,
 * beside reporting this development error.
 */
#define DIO_E_PARAM_POINTER             (uint8)0x20

 /**
  * @brief Defination of passing parameters to be used in Det_ReportError as uninitialized driver in code
  *
  *
  * @details
  * - Type: define
  * - Range: 0x0E
  * - Resolution: Fixed
  * - Unit: Bits
  */

/*
 * API service used without module initialization is reported using following
 * error code (Not exist in AUTOSAR 4.0.3 DIO SWS Document.
 */
#define DIO_E_UNINIT                   (uint8)0xF0

 /**
  * @brief AUTOSAR checking between Std Types and Dio Modules
  */

/* AUTOSAR checking between Std Types and Dio Modules */
#if (STD_TYPES_AR_RELEASE_VERSION != DIO_AR_RELEASE_VERSION)
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/**
 * @brief AUTOSAR Version checking between Dio_Cfg.h and Dio.h files
 */

/* AUTOSAR Version checking between Dio_Cfg.h and Dio.h files */
#if (DIO_CFG_AR_RELEASE_VERSION != DIO_AR_RELEASE_VERSION)
  #error "The AR version of Dio_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_Cfg.h and Dio.h files */
#if (DIO_CFG_SW_VERSION != DIO_SW_VERSION)
  #error "The SW version of Dio_Cfg.h does not match the expected version"
#endif
/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
 /**
  * @brief Defination of API to be used in Det_ReportError
  *
  *
  * @details
  * - Type: define
  * - Range: 0x00
  * - Resolution: Fixed
  * - Unit: Bits
  */
 /* Service ID for DIO read Channel */
#define DIO_READ_CHANNEL_SID           (uint8)0x00

/**
 * @brief Defination of API to be used in Det_ReportError
 *
 *
 * @details
 * - Type: define
 * - Range: 0x01
 * - Resolution: Fixed
 * - Unit: Bits
 */
/* Service ID for DIO write Channel */
#define DIO_WRITE_CHANNEL_SID          (uint8)0x01

/**
 * @brief Defination of API to be used in Det_ReportError
 *
 *
 * @details
 * - Type: define
 * - Range: 0x02
 * - Resolution: Fixed
 * - Unit: Bits
 */

/* Service ID for DIO read Port */
#define DIO_READ_PORT_SID              (uint8)0x02

/**
 * @brief Defination of API to be used in Det_ReportError
 *
 *
 * @details
 * - Type: define
 * - Range: 0x03
 * - Resolution: Fixed
 * - Unit: Bits
 */

/* Service ID for DIO write Port */
#define DIO_WRITE_PORT_SID             (uint8)0x03

/**
 * @brief Defination of API to be used in Det_ReportError
 *
 *
 * @details
 * - Type: define
 * - Range: 0x04
 * - Resolution: Fixed
 * - Unit: Bits
 */

/* Service ID for DIO ReadChannelGroup */
#define Dio_ReadChannelGroup           (uint8)0x04

/**
 * @brief Defination of API to be used in Det_ReportError
 *
 *
 * @details
 * - Type: define
 * - Range: 0x05
 * - Resolution: Fixed
 * - Unit: Bits
 */

/* Service ID for DIO WriteChannelGroup */
#define DIO_WriteChannelGroup          (uint8)0x05

/**
 * @brief Defination of API to be used in Det_ReportError
 *
 *
 * @details
 * - Type: define
 * - Range: 0x11
 * - Resolution: Fixed
 * - Unit: Bits
 */

/* Service ID for DIO flip Channel */
#define DIO_FLIP_CHANNEL_SID           (uint8)0x11

/**
 * @brief Defination of API to be used in Det_ReportError
 *
 *
 * @details
 * - Type: define
 * - Range: 0x12
 * - Resolution: Fixed
 * - Unit: Bits
 */

/* Service ID for DIO GetVersionInfo */
#define DIO_GET_VERSION_INFO_SID       (uint8)0x12
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

  /**
  * @brief Enumeration for Level of Pin.
  *
  *
  * @details
  * - Type: enum
  * - Range: 0:1
  * - Resolution: 1U
  * - Unit: Bits
  */

typedef enum {
	STD_Dio_LOW, STD_Dio_HIGH
} Dio_LevelType;

/**
  * @brief Enumeration for Level of Port.
  *
  *
  * @details
  * - Type: enum
  * - Range: 0,0xFF
  * - Resolution: 1U
  * - Unit: Bits
  */

typedef enum {
	STD_PORTLOW, STD_PORTHIGH = 0xFF
} Dio_PortLevelType;

/**
  * @brief Enumeration for Choosing the Channel.
  *
  *
  * @details
  * - Type: enum
  * - Range: 48
  * - Resolution: 1U
  * - Unit: Bits
  */

typedef enum {
	A0 = 0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15,

	B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, B13, B14, B15,

	C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15

} Dio_ChannelType;

/**
  * @brief Enumeration for Choosing the Port.
  *
  *
  * @details
  * - Type: enum
  * - Range: 3
  * - Resolution: 1U
  * - Unit: Bits
  */

typedef enum {
	PORTA, PORTB, PORTC

} Dio_PortType;
/*============================================================================*/

/****************************************************************************
 ********************* Function definitions **********************************
 *****************************************************************************/

/*====================================================================================*/
/**
 *
 * This function Read the value of channel.
 *
 * @param[in]     ChannelId     Type Dio_ChannelType     Range 0:48
 * @param[out] None
 * @return    Dio_LevelType   Type uint8             Range 0,1
 */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
/**
 *
 * This function Write a value to channel.
 *
 * @param[in]     ChannelId     Type Dio_ChannelType     Range 0:48
 * @param[in]    Level			Type Dio_LevelType       Range 0:1
 * @return    none
 */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);
/**
 *
 * This function Read the value of a Port.
 *
 * @param[in]     ChannelId     Type Dio_ChannelType     Range 0:48
 * @param[in]    Level			Type Dio_LevelType       Range 0:1
 * @return    Dio_PortLevelType Type Region_Enum         Range 0,0xFF
 */
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);
/**
 *
 * This function write a value to Port.
 *
 * @param[in]     PortId     Type Dio_PortType			  Range 0:2
 * @param[in]    Level		 Type Dio_PortLevelType       Range 0,0xFF
 * @return    none
 */
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);
/**
 *
 * This function That Flip the value of channel.
 *
 * @param[in]     ChannelId     Type Dio_ChannelType     Range 0:48
 * @param[out]    none
 * @return        Dio_LevelType Type Region_Enum         Range 0:1
 */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
/*====================================================================================*/
/**
 *
 * This function sets the value of pin.
 *
 * @param[in]     ChannelId     Type Dio_ChannelType     Range 0:48,
 *				  gpio_ptr		Type GPIO_REG
 * @param[in]    Level			Type Dio_LevelType       Range 0:1
 * @return    none
 */
void Dio_SetPinValue(GPIO_REG *gpio_ptr, Dio_ChannelType ChannelId,
		Dio_LevelType Level);
/**
 *
 * This function Toggle the value of pin.
 *
 * @param[in]     ChannelId     Type Dio_ChannelType     Range 0:48,
 *				  gpio_ptr		Type GPIO_REG
 * @param[out]    none
 * @return    none
 */
void Dio_TogglePin(GPIO_REG *gpio_ptr, Dio_ChannelType ChannelId);
/**
 *
 * This function sets the value of port.
 *
 * @param[in]     gpio_ptr		Type GPIO_REG
 * @param[in]    Level			Type Dio_LevelType       Range 0:1
 * @return    none
 */
void Dio_SetPortValue(GPIO_REG *gpio_ptr, Dio_LevelType Level);
/*====================================================================================*/

#endif /* DIO_PRIVATE_H_ */
