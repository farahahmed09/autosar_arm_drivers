/******************************************************************
 * File: port_private.h
 * @brief: This file contains the private declarations and private function prototypes for the Port module.
 * 
 * Author: Farah Ahmed
 * Date: April 5, 2024
 * 
 * AUTOSAR Version: 3.2.0
 * Target MCU: TIVAC123GH6PM
 ********************************************************************/
#ifndef _PORT_PRIVATE_H
#define _PORT_PRIVATE_H

#include "port.h"
#include "std_types.h"


/* Definition of port numbers */
#define PORTA       (0) /* Port A */
#define PORTB       (1) /* Port B */
#define PORTC       (2) /* Port C */
#define PORTD       (3) /* Port D */
#define PORTE       (4) /* Port E */
#define PORTF       (5) /* Port F */

/*******************************************************************************
 *                              FUNCTION PROTOTYPES                            *
 *******************************************************************************/

/**
 * @brief: Retrieves the port number of a given pin ID.
 * 
 * @param copy_pinId: The ID of the pin.
 * @return: The port number of the specified pin.
 */
uint8 Port_GetNumber(uint8 copy_pinId);

/**
 * @brief: Retrieves the pin number of a given port number and pin ID.
 * 
 * @param copy_portNum: The port number.
 * @param copy_pinId: The ID of the pin.
 * @return: The pin number of the specified port and pin ID.
 */
uint8 Pin_GetNumber(uint8 copy_portNum, uint8 copy_pinId);


#endif /* _PORT_PRIVATE_H */
