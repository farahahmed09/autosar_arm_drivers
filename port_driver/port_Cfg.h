/******************************************************************
 * File: port_Cfg.h
 * @brief: This file contains the configuration declarations for the Port module.
 * 
 * Author: Farah Ahmed
 * Date: April 5, 2024
 * 
 * AUTOSAR Version: 3.2.0
 * Target MCU: TIVAC123GH6PM
 ********************************************************************/


#ifndef _PORT_CFG_H
#define _PORT_CFG_H

#include "std_types.h"

/* Module version 1.0.0 , initial release */
#define PORT_CFG_SW_MAJOR_VERSION      (1)
#define PORT_CFG_SW_MINOR_VERSION      (0)
#define PORT_CFG_SW_PATCH_VERSION      (0)

/* AUTOSAR version 4.0.3 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION      (4)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION      (0)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION      (3)

/* Pre-compile option for Development Error Detection */
#define PORT_DEV_ERROR_DETECT               (STD_ON)
/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API               (STD_OFF)
/* Pre-compile option for presence of Port_SetPinDirection  API */
#define  PORT_SET_PIN_DIRECTION_API         (STD_OFF)
/* Pre-compile option for presence of Port_SetPinMode  API */
#define  PORT_SET_PIN_MODE_API              (STD_OFF)

/* Number of configured port channels */
#define PORT_CONFIGURED_PINS            (39)





/* PORTA pins */
#define PortConf_PA0                  ((Port_PinType)PA0)
#define PortConf_PA1                  ((Port_PinType)PA1)
#define PortConf_PA2                  ((Port_PinType)PA2)
#define PortConf_PA3                  ((Port_PinType)PA3)
#define PortConf_PA4                  ((Port_PinType)PA4)
#define PortConf_PA5                  ((Port_PinType)PA5)
#define PortConf_PA6                  ((Port_PinType)PA6)
#define PortConf_PA7                  ((Port_PinType)PA7)


/* PORTB pins */
#define PortConf_PB0                  ((Port_PinType)PB0)
#define PortConf_PB1                  ((Port_PinType)PB1)
#define PortConf_PB2                  ((Port_PinType)PB2)
#define PortConf_PB3                  ((Port_PinType)PB3)
#define PortConf_PB4                  ((Port_PinType)PB4)
#define PortConf_PB5                  ((Port_PinType)PB5)
#define PortConf_PB6                  ((Port_PinType)PB6)
#define PortConf_PB7                  ((Port_PinType)PB7)

/* PORTC pins , jtag pins are excluded */
#define PortConf_PC4                  ((Port_PinType)PC4)
#define PortConf_PC5                  ((Port_PinType)PC5)
#define PortConf_PC6                  ((Port_PinType)PC6)
#define PortConf_PC7                  ((Port_PinType)PC7)

/* PORTD pins */
#define PortConf_PD0                  ((Port_PinType)PD0)
#define PortConf_PD1                  ((Port_PinType)PD1)
#define PortConf_PD2                  ((Port_PinType)PD2)
#define PortConf_PD3                  ((Port_PinType)PD3)
#define PortConf_PD4                  ((Port_PinType)PD4)
#define PortConf_PD5                  ((Port_PinType)PD5)
#define PortConf_PD6                  ((Port_PinType)PD6)
#define PortConf_PD7                  ((Port_PinType)PD7)

/* PORTE pins */
#define PortConf_PE0                  ((Port_PinType)PE0)
#define PortConf_PE1                  ((Port_PinType)PE1)
#define PortConf_PE2                  ((Port_PinType)PE2)
#define PortConf_PE3                  ((Port_PinType)PE3)
#define PortConf_PE4                  ((Port_PinType)PE4)
#define PortConf_PE5                  ((Port_PinType)PE5)

/* PORTF pins */
#define PortConf_PF0                  ((Port_PinType)PF0)
#define PortConf_PF1                  ((Port_PinType)PF1)
#define PortConf_PF2                  ((Port_PinType)PF2)
#define PortConf_PF3                  ((Port_PinType)PF3)
#define PortConf_PF4                  ((Port_PinType)PF4)



/* Default Configuration */
#define PortConf_DEFAULT_MODE           ((Port_PinModeType)Gpio_Mode)
#define PortConf_DEFAULT_DIRECTION      ((Port_PinDirectionType)PORT_PIN_IN)
#define PortConf_DEFAULT_RESISTOR       ((Port_PinResistorType)PULL_UP)
#define PortConf_DEFAULT_INITIAL_VALUE  ((Port_PinInitialValue)NO_INITIAL)
#define PortConf_DEFAULT_DIR_CH         ((uint8)STD_OFF)
#define PortConf_DEFAULT_MODE_CH        ((uint8)STD_OFF)
#define PortConf_DEFAULT_ENABLE         ((Port_PinEnable)Disable)


/* PORT Configured Port ID's */
#define PortConf_LED1_PIN_TYPE          ((Port_PinType)PF1)
#define PortConf_SW1_PIN_TYPE           ((Port_PinType)PF4)

/* PORT configured mode */
#define PortConf_LED1_MODE_TYPE         ((Port_PinModeType)Gpio_Mode)
#define PortConf_SW1_MODE_TYPE          ((Port_PinModeType)Gpio_Mode)

/* PORT configured direction */
#define PortConf_LED1_DIRECTION_TYPE    ((Port_PinDirectionType)PORT_PIN_OUT)
#define PortConf_SW1_DIRECTION_TYPE     ((Port_PinDirectionType)PORT_PIN_IN)

/* PORT resistor type */
#define PortConf_LED1_RESISTOR_TYPE     ((Port_PinResistorType)NONE) /* Output pin */
#define PortConf_SW1_RESISTOR_TYPE      ((Port_PinResistorType)PULL_UP)

/* PORT initial value */
#define PortConf_LED1_INITIAL_VALUE     ((Port_PinInitialValue)INITIAL_LOW)
#define PortConf_SW1_INITIAL_VALUE      ((Port_PinInitialValue)INITIAL_HIGH)

/* change direction enable */
#define PortConf_LED1_DIR_CH                  ((uint8)STD_OFF)
#define PortConf_SW1_DIR_CH                   ((uint8)STD_OFF)

/* change mode enable */
#define PortConf_LED1_MODE_CH                 ((uint8)STD_OFF)
#define PortConf_SW1_MODE_CH                  ((uint8)STD_OFF)

/* this pin is enabled means that this pin is used in the project */
#define PortConf_LED1_ENABLE                  ((Port_PinEnable)Enable)
#define PortConf_SW1_ENABLE                   ((Port_PinEnable)Enable)

#endif /* _PORT_CFG_H */
