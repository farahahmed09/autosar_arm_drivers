/**
 *@file       Dio_prg.c
 *@version  	 1.0.0
 *@brief    	 AUTOSAR Based
 *@details    Dio Program File.
 *@authors 	 Ahmed Yassin, Farah Ahmed and Mohamed Mabrouk
 */

/*===========================================================================
 *   Project          : AUTOSAR  R22-11 MCAL
 *   Platform         : ARM
 *   Peripherial      : STM32F103C8T6
 *   AUTOSAR Version  : R22-11
 *   SW Version       : 1.0.0
 ============================================================================*/

/****************************************************************************
 *****************************  Includes   ***********************************
 *****************************************************************************/

#include "Dio.h"
#include "Det.h"

/*====================================================================================*/

/**
 * \section Service_Name
 * Port_Init
 * \section Description
 * Function to Read PinLevel based on Dio_Config array
 * \section Req_ID
 * Dio_0x01
 *
 * \section Scope
 * Public
 *
 * \section Re-entrancy
 * Reentrant
 *
 * \section Sync_Async
 * Synchronous
 *
 * \param[in] ChannelId \Hold the Channel Id to get it's Address / Type u8 /Range [0 .. NUMBER_OF_Dio_PINS]
 * \param[inout] None
 * \param[out] None
 * \return Dio_LevelType
 *
 * @startuml
 * start
 * 
 *  switch (Which Port?)
 *	case ()
 *	:PORTA;
 *	case ( )
 *	:PORTB;
 *	case ( )
 *	:PORTC;
 *	endswitch
 * :return whether the pin is HIGH or LOW;
 * 
 * end
 * @enduml
 */

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId) {
	/*checks the given pin belongs to which port*/
	if (ChannelId >= A0 && ChannelId <= A15) {
		/*returns the value of the channel*/
		return ((GPIOA->IDR >> (ChannelId)) & STD_HIGH);
	} else if (ChannelId >= B0 && ChannelId <= B15) {
		/*  to clear the bit that we used in define port */
		CLEAR_BIT(ChannelId, 4);
		/*returns the value of the channel*/
		return ((GPIOB->IDR >> (ChannelId)) & STD_HIGH);
	} else if (ChannelId >= C0 && ChannelId <= C15) {
		/*  to clear the bit that we used in define port */
		CLEAR_BIT(ChannelId, 5);
		/*returns the value of the channel*/
		return ((GPIOC->IDR >> (ChannelId)) & STD_HIGH);
	} else {
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_SID,
		DIO_E_PARAM_INVALID_CHANNEL_ID);
	}
}
/**
 * \section Service_Name
 * Dio_WriteChannel
 *
 * \section Description
 * Function to Write PinLevel based on the parameters ChannelId and Level
 * \section Req_ID
 * Dio_0x02
 *
 * \section Scope
 * Public
 *
 * \section Re-entrancy
 * Reentrant
 *
 * \section Sync_Async
 * Synchronous
 *
 * \param[in] ChannelId \Hold the Channel Id to detect it's Address
 * \param[in] Level     \Hold the Level to change it's state
 * \param[inout] None
 * \param[inout] None
 * \return void
 *
 * @startuml
 * start
 * 
 * 
 *  switch (Which Port?)
 *  case ( )
 *  :PORTA;
 *  case ( )
 *  :PORTB;
 *  case ( )
 *  :PORTC;
 *  endswitch
 *  if (level is low) then (yes)
 *  :write zero on the pin;
 *  else (no)
 *  :write high on the pin;
 *  endif;
 *  
 * end
 * @enduml
 */

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level) {
	/*checks the given pin belongs to which port*/
	if (ChannelId >= A0 && ChannelId <= A15)
		Dio_SetPinValue( GPIOA, ChannelId, Level);
	else if (ChannelId >= B0 && ChannelId <= B15) {
		/*  to clear the bit that we used in define port */
		CLEAR_BIT(ChannelId, 4);
		Dio_SetPinValue( GPIOB, ChannelId, Level);
	}

	else if (ChannelId >= C0 && ChannelId <= C15) {
		/*  to clear the bit that we used in define port */
		CLEAR_BIT(ChannelId, 5);
		Dio_SetPinValue( GPIOC, ChannelId, Level);
	} else
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_SID,
		DIO_E_PARAM_INVALID_CHANNEL_ID);
}
/**
 * \section Service_Name
 * Dio_ReadChannel
 *
 * \section Description
 * Function to Read Port Levels based on the parameter PortId
 * \section Req_ID
 * Dio_0x03
 *
 * \section Scope
 * Public
 *
 * \section Re-entrancy
 * Reentrant
 *
 * \section Sync_Async
 * Synchronous
 *
 * \param[in]  PortId    \Hold the PortId Id to detect it's Address
 * \param[in] None
 * \param[inout] None
 * \param[inout] None
 * \return void
 * @startuml
 * start
 *  switch (Which Port?)
 *	case ()
 *	:PORTA;
 *	: read the value;
 *	case ( PortB)
 *	:PORTB;
 *	:read the value;
 *	case ( PortC)
 *	:PORTC;
 *	:read the value;
 *	endswitch
 * end
 * @enduml
 * 
 * 
 * 
 */
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId) {
	/*check the port given*/
	switch (PortId) {
	case PORTA:
		/*read the given port*/
		return (GPIOA->IDR);
		break;
	case PORTB:
		/*read the given port*/
		return (GPIOB->IDR);
		break;
	case PORTC:
		/*read the given port*/
		return (GPIOC->IDR);
		break;
	default:
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_PORT_SID,
		DIO_E_PARAM_INVALID_PORT_ID);
		break;
	}
}

/**
 * \section Service_Name
 * Dio_WritePort
 *
 * \section Description
 * Function to Write Port Levels based on the parameters PortId and Level
 * \section Req_ID
 * Dio_0x04
 *
 * \section Scope
 * Public
 *
 * \section Re-entrancy
 * Reentrant
 *
 * \section Sync_Async
 * Synchronous
 *
 * \param[in] PortId    \Hold the PortId Id to detect it's Address
 * \param[in] Level     \Hold the Level to change it's state
 * \param[inout] None
 * \param[inout] None
 * \return void
 * @startuml
 * start
 * 
 * 
 *  switch (Which Port?)
 *  case ( )
 *  :PORTA;
 *  case ( )
 *  :PORTB;
 *  case ( )
 *  :PORTC;
 *  endswitch
 *  if (level is low) then (yes)
 *  :write zero on it;
 *  else (no)
 *  :write high on it;
 *  endif;
 * 
 *  
 * end
 * @enduml
 */
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level) {
	switch (PortId) {
	case PORTA:
		/*turn on/off the port given*/
		Dio_SetPortValue( GPIOA, Level);
		break;
	case PORTB:
		/*turn on/off the port given*/
		Dio_SetPortValue( GPIOB, Level);
		break;
	case PORTC:
		/*turn on/off the port given*/
		Dio_SetPortValue( GPIOC, Level);
		break;
	default:
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_PORT_SID,
		DIO_E_PARAM_INVALID_PORT_ID);
		break;
	}
}

/**
 * \section Service_Name
 * Dio_FlipChannel
 *
 * \section Description
 * Function to toggle pin Level based on the parameter ChannelId
 * \section Req_ID
 * Dio_0x05
 *
 * \section Scope
 * Public
 *
 * \section Re-entrancy
 * Reentrant
 *
 * \section Sync_Async
 * Synchronous
 *
 * \param[in] ChannelId    \Hold the ChannelId to detect it's Address
 * \param[inout] None
 * \param[inout] None
 * \return void
 *
 * 
 * @startuml
 * start
 * 
 * 
 *  switch (Which Port?)
 *	case ( )
 *	:PORTA;
 *	case ( )
 *	:PORTB;
 *	case ( )
 *	:PORTC;
 *	endswitch
 *	if (pin is low) then (yes)
 *  :make it high;
 *  else (no)
 *  :make it low;
 *  endif;
 * 

 * 
 * end
 * @enduml
 */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId) {
if (ChannelId >= A0 && ChannelId <= A15) {
	/* toggling the bit that we use to turn on/off the pin*/
	Dio_TogglePin(GPIOA, ChannelId);
	/*retuns the level of the given pin after flipping*/
	return (GET_BIT(GPIOA->ODR, ChannelId));
} else if (ChannelId >= B0 && ChannelId <= B15) {
	/*  to clear the bit that we used in define port */
	CLEAR_BIT(ChannelId, 4);
	/* toggling the bit that we use to turn on/off the pin*/
	Dio_TogglePin(GPIOB, ChannelId);
	/*retuns the level of the given pin after flipping*/
	return (GET_BIT(GPIOB->ODR, ChannelId));
} else if (ChannelId >= C0 && ChannelId <= C15) {
	/*  to clear the bit that we used in define port */
	CLEAR_BIT(ChannelId, 5);
	/* toggling the bit that we use to turn on/off the pin*/
	Dio_TogglePin(GPIOC, ChannelId);
	/*retuns the level of the given pin after flipping*/
	return (GET_BIT(GPIOC->ODR, ChannelId));
} else {
	Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_FLIP_CHANNEL_SID,
	DIO_E_PARAM_INVALID_CHANNEL_ID);
}
}

/**
 * \section Service_Name
 *  Dio_GetVersionInfo 
 *
 * \section Description
 * update the version
 *
 * \section Req_ID
 * Dio_0x06
 *
 * \section Scope
 * Public
 *
 * \section Re-entrancy
 * Reentrant
 *
 * \section Sync_Async
 * Synchronous
 *
 * \section Parameters
 * \param[in] Std_VersionInfoType* VersionInfoPtr
 * \param[inout] None
 * \param[out] None
 * \return None
 *
 *
 *
 * \section Activity_Diagram
 *
 * @startuml
 *   start
 * 
 * 
 * if (ptr == null) then (yes)
 * :return;
 * else (no)
 * :access by ptr and update the parameters;
 * endif 
 * 
 * end
 * @enduml
 *
 */
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo) {
if (NULL_PTR == versioninfo) {
	/* Report to DET  */
	Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
	DIO_GET_VERSION_INFO_SID, DIO_E_PARAM_POINTER);
} //end if
else {
	/* Copy the module Id */
	versioninfo->moduleID = (uint16) DIO_MODULE_ID;

	/* Copy Software Version */
	versioninfo->sw_version = (uint8) DIO_SW_VERSION;
} //end else
}
