/**
*@file       Dio_prg.c
*@version    1.0.0
*@brief      AUTOSAR Based
*@details    Dio Configratuions Header File.
*@authors    Ahmed Yassin, Farah Ahmed and Mohamed Mabrouk
*/

/*===========================================================================
*   Project          : AUTOSAR  R22-11 MCAL
*   Platform         : ARM
*   Peripherial      : STM32F103C8T6
*   AUTOSAR Version  : R22-11
*   SW Version       : 1.0.0
============================================================================*/
#ifndef DIO_CFG_H_
#define DIO_CFG_H_

 /**
  * @brief Defination of Module Version
  *
  *
  * @details
  * - Type: define
  * - Range: 1
  * - Resolution: Fixed
  * - Unit: Bits
  */

/*============================================================================*/
/*
 * Module Version 1
 */
#define DIO_CFG_SW_VERSION         1
 /**
   * @brief Defination of AUTOSAR Version R22-11
   *
   *
   * @details
   * - Type: define
   * - Range: 22
   * - Resolution: Fixed
   * - Unit: Bits
   */
/*
 * AUTOSAR Version R22-11
 */
#define DIO_CFG_AR_RELEASE_VERSION 22
 
	/**
	   * @brief Defination of number of PORTS that there are in it.
	   *
	   *
	   * @details
	   * - Type: define
	   * - Range: 3
	   * - Resolution: Fixed
	   * - Unit: Bits
	   */
#define NUM_OF_PORTS   3
	   /**
			  * @brief Defination of number of Pins that there are in it.
			  *
			  *
			  * @details
			  * - Type: define
			  * - Range: 48
			  * - Resolution: Fixed
			  * - Unit: Bits
			  */
#define NUM_OF_PINS    48

#endif
