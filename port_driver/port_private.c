/*********************************************************************************
 * File: port_private.c
 * @brief: This file contains the private functions definition for the Port module.
 * 
 * Author: Farah Ahmed
 * Date: April 5, 2024
 * 
 * AUTOSAR Version: 3.2.0
 * Target MCU: TIVAC123GH6PM
 ********************************************************************************/
#include "port_private.h"
#include "common_macros.h"
#include "port_regs.h"
#include "port.h"

/**
 * @brief: Retrieves the port number of a given pin ID.
 * 
 * @param copy_pinId: The ID of the pin.
 * @return: The port number of the specified pin.
 */


uint8 Port_GetNumber(uint8 copy_pinId)
{
    if (copy_pinId <= 7)
    {
        return PORTA;
    }

    if (copy_pinId >= 8 && copy_pinId <= 15)
    {
        return PORTB;
    }

    if (copy_pinId >= 20 && copy_pinId <= 23)
    {
        return PORTC;
    }

    if (copy_pinId >= 24 && copy_pinId <= 31)
    {
        return PORTD;
    }

    if (copy_pinId >= 32 && copy_pinId <= 37)
    {
        return PORTE;
    }

    if (copy_pinId >= 38 && copy_pinId <= 42)
    {
        return PORTF;
    }

    return 0 ;
}

/**
 * @brief: Retrieves the pin number of a given port number and pin ID.
 * 
 * @param copy_portNum: The port number.
 * @param copy_pinId: The ID of the pin.
 * @return: The pin number of the specified port and pin ID.
 */
uint8 Pin_GetNumber(uint8 copy_portNum, uint8 copy_pinId)
{
    uint8 number = 0;
    switch (copy_portNum)
    {
    case PORTA:
        number = copy_pinId;
        break;
    case PORTB:
        number = copy_pinId - 8;
        break;
    case PORTC:
        number = copy_pinId - 16;
        break;
    case PORTD:
        number = copy_pinId - 24;
        break;
    case PORTE:
        number = copy_pinId - 32;
        break;
    case PORTF:
        number = copy_pinId - 38;
        break;
    }
    return number;
}


