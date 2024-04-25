/******************************************************************************************
 * File : port.h
 * @brief: This file contains the type declarations and function prototypes for the Port driver.
 * 
 * Author: Farah Ahmed
 * Date: April 5, 2024
 * 
 * AUTOSAR Version: 3.2.0
 * Target MCU: TIVAC123GH6PM
 **********************************************************************************************/

#ifndef _PORT_H
#define _PORT_H

#include "std_types.h"
#include "common_macros.h"
#include "port_private.h"
#include "port_Cfg.h"

/* Port vendor ID */
#define PORT_VENDOR_ID    (1000U)

/* Port Module ID */
#define PORT_MODULE_ID    (124U)

/* Port Instance ID */
#define PORT_INSTANCE_ID  (0U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Module version 1.0.0, initial release */
#define PORT_SW_MAJOR_VERSION      (1)
#define PORT_SW_MINOR_VERSION      (0)
#define PORT_SW_PATCH_VERSION      (0)

/* AUTOSAR version 4.0.3 */
#define PORT_AR_RELEASE_MAJOR_VERSION      (4)
#define PORT_AR_RELEASE_MINOR_VERSION      (0)
#define PORT_AR_RELEASE_PATCH_VERSION      (3)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION) || \
     (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION) || \
     (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif



#include "port_Cfg.h"

/* Software Version checking between port_Cfg.h and port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION) || \
     (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION) || \
     (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of port_Cfg.h does not match the expected version"
#endif

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for initializing the port module. */
#define PORT_INIT_SID                          (0x00)
/* Service ID for setting the direction of a pin. */ 
#define PORT_SET_PIN_DIRECTION_SID             (0x01)
/* Service ID for refreshing the direction of all port pins. */
#define PORT_REFRESH_PORT_DIRECTION_SID        (0x02)
/* Service ID for getting the version information of the port module. */
#define PORT_GET_VERSION_INFO_SID              (0x03) 
/* Service ID for setting the mode of a pin. */
#define PORT_SET_PIN_MODE_SID                  (0x04)   

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* Invalid pin parameter. */
#define PORT_E_PARAM_PIN                       (0x05)  
/* Pin direction cannot be changed. */
#define PORT_E_DIRECTION_UNCHANGEABLE          (0x06) 
/* Invalid port configuration parameter. */ 
#define PORT_E_PARAM_CONFIG                    (0x07) 
 /* Invalid pin mode parameter. */
#define PORT_E_PARAM_INVALID_MODE              (0x08)  
/* Pin mode cannot be changed. */
#define PORT_E_MODE_UNCHANGEABLE               (0x09)
/* Port module is uninitialized. */  
#define PORT_E_UNINIT                          (0x0A)  
/* Invalid pointer parameter. */
#define PORT_E_PARAM_POINTER                   (0x0B) 
/* Invalid initial value of output pin */
#define PORT_E_PARAM_INITIAL_VALUE             (0x0C) 

/*******************************************************************************
 *                              Module Data Types "NON-AUTOSAR"                 *
 *******************************************************************************/
typedef enum
{
  PA0 , PA1, PA2, PA3, PA4, PA5, PA6, PA7,
  PB0 = 8,  PB1, PB2, PB3, PB4, PB5, PB6, PB7 = 15,
  PC4 =20, PC5, PC6, PC7 = 23,
  PD0 = 24, PD1, PD2, PD3, PD4, PD5, PD6, PD7 = 31,
  PE0 = 32, PE1, PE2, PE3, PE4, PE5,
  PF0 = 38, PF1, PF2, PF3, PF4
}Port_PinId;

typedef enum
{
   Gpio_Mode = 0,
   Uart_Mode = 1,
   SSI_PORTD_Mode = 1,
   Uart1_PortC_Mode = 2,
   SSI_Mode = 2,
   CAN0_PORTF_Mode = 3,
   I2C_Mode = 3,
   M0PWM_Mode = 4,
   M1PWM_Mode = 5,
   IDX_Mode = 6,
   PHA_Mode = 6,
   PHB_Mode = 6,
   TXCCP_Mode = 7,
   WTXCCP_Mode = 7,
   CAN_Mode = 8,
   USB_Mode = 8,
   NMI_Mode = 8,
   ADC_Mode = 10
}Port_ModeId;
 
typedef enum
{
  PULL_UP,
  PULL_DOWN, 
  NONE
}Port_PinResistorType;

typedef enum
{
    INITIAL_LOW,
    INITIAL_HIGH,
    NO_INITIAL
}Port_PinInitialValue;

typedef enum
{
    Disable ,
    Enable
}Port_PinEnable;


/*******************************************************************************
 *                              Module Data Types "AUTOSAR"                     *
 *******************************************************************************/
 
typedef uint8 Port_PinType;
typedef uint8 Port_PinModeType; 

typedef enum
{
  PORT_PIN_IN, 
  PORT_PIN_OUT
} Port_PinDirectionType;


typedef struct
{
  Port_PinType pin_id;
  Port_PinModeType mode ;
  Port_PinDirectionType direction ;
  Port_PinResistorType resistor;
  Port_PinInitialValue initial_value;
  uint8 d_ch;
  uint8 m_ch;
  Port_PinEnable pin_enable ;
}Port_ChannelConfig;
typedef struct 
{
    Port_ChannelConfig arr[PORT_CONFIGURED_PINS];
}Port_ConfigType;

extern const Port_ConfigType Port_Configuration;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port module.
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr);

/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): port pin id number / port pin direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Set port pin direction.
************************************************************************************/
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(void);

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): Pointer to where to store version information
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);

/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): port pin id number / new port pin mode
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the pin mode.
************************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);

#endif /* _PORT_H */
