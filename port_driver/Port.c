/*********************************************************************************
 * File: port.c
 * @brief: This file contains functions definitions for the Port module.
 * 
 * Author: Farah Ahmed
 * Date: April 5, 2024
 * 
 * AUTOSAR Version: 3.2.0
 * Target MCU: TIVAC123GH6PM
 ********************************************************************************/
#include "port_Cfg.h"
#include "port.h"
#include "Det.h"
#include "port_regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif


/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/
/* global pointer used to access the configuration structure in .c file */
STATIC const Port_ChannelConfig *ptr = NULL_PTR ;
/* variable to ensure that the Port_Init is called */
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED ; 

/*******************************************************************************
 *                      Function Definition                                     *
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
void Port_Init(const Port_ConfigType* ConfigPtr)
{

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
     Det_ReportError(PORT_MODULE_ID , PORT_INSTANCE_ID , PORT_INIT_SID , PORT_E_PARAM_CONFIG);

	}
	else
	{
	    /* Do Nothing */
	}
#endif
	{

		Port_Status = PORT_INITIALIZED;
		ptr = ConfigPtr->arr; /* address of the first element in the array of stuctures to be used outside this function */
	}

	/*------------------------------------------Init of pins-------------------------------------------*/
	uint8 i ;
	for(i=0 ; i<PORT_CONFIGURED_PINS ; i++)
	{

        /* Pointer to the required Port Registers base address */
            volatile uint32 * PortGpio_Ptr = NULL_PTR;

            /* Get the port number and pin number */
            uint8 port_num = Port_GetNumber(ConfigPtr->arr[i].pin_id);
            uint8 pin_num = Pin_GetNumber(port_num ,ConfigPtr->arr[i].pin_id);

            /* Choose the base address register according to the port number */
            switch (port_num)
            {
                case 0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                        break;
                case 1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                        break;
                case 2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                        break;
                case 3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                        break;
                case 4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                        break;
                case 5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                        break;
            }

            /*----------------------------Special handling for certain pins-----------------------------------*/

            if (((port_num == PORTD) && (pin_num == 7)) || ((port_num == PORTF) && (pin_num == 0)))
            {
                /* Unlock the GPIOCR register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;
                /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , pin_num);
            }
            else
            {
                /* Do Nothing */
            }


          /*------------------------------------------------------------------------------------------------------------*/

            if(ConfigPtr->arr[i].pin_enable == Disable)
            {

                /*-----------------------configure this pin by the default configuration-------------------------------*/

                /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pin_num);

                /* Set the corresponding bit in the GPIOPUR register to enable the internal pull-up pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , pin_num);

                /* clear alternative function */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pin_num);

                /* Set the Mode configured in the GPIOPCTL register as gpio_mode */
                uint32 GPIOCTL = *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET);
                GPIOCTL = ((GPIOCTL) & (0xF0 << pin_num *4 ) ) | ((ConfigPtr->arr[i].mode) << pin_num *4 );


            }
            else if (ConfigPtr->arr[i].pin_enable == Enable)
            {

                /*------------------this pin is not configured as default configuration-------------------------*/
                /*---------------------configuration for direction/initial value/resistor type-----------------*/
                if (ConfigPtr->arr[i].direction == PORT_PIN_OUT)
                {
                    /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pin_num);

                    /* Provide initial value */
                    if (ConfigPtr->arr[i].initial_value == INITIAL_HIGH)
                    {
                        /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , pin_num);
                    }
                    else if (ConfigPtr->arr[i].initial_value == INITIAL_LOW)
                    {
                        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , pin_num);
                    }
                    else
                    {
                        /* Do Nothing */
                    }
                }
                else if (ConfigPtr->arr[i].direction== PORT_PIN_IN)
                {
                    /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pin_num);

                    /* Enable internal pull-up or pull-down resistors */
                    if (ConfigPtr->arr[i].resistor == PULL_UP)
                    {
                        /* Set the corresponding bit in the GPIOPUR register to enable the internal pull-up pin */
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , pin_num);
                    }
                    else if (ConfigPtr->arr[i].resistor == PULL_DOWN)
                    {
                        /* Set the corresponding bit in the GPIOPDR register to enable the internal pull-down pin */
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , pin_num);
                    }
                    else
                    {
                        /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull-up pin */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , pin_num);
                        /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull-down pin */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , pin_num);
                    }
                }
                else
                {
                    /* Do Nothing */
                }
                /*---------------------------------------------------------------------------------------------------------*/
                /*----------------------------------------------------------------------------------------------------------*/


                /*-------------------------------------configuration for mode ------------------------------------------*/

                /* Check if Mode is different from Gpio_Mode */
                if (ConfigPtr->arr[i].mode != Gpio_Mode)
                {
                    /* Set alternative function */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pin_num);
                }
                else
                {
                    /* clear alternative function */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pin_num);
                }

                /*-------------------------------------------------------------------------------------------------------------*/

                /*--------------------------------------Special handling for certain mode-------------------------------------*/
                if (ConfigPtr->arr[i].mode == ADC_Mode)
                {
                    /* Enable analog register */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pin_num);
                    /* Disable digital register */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET ) , pin_num);
                }
                else
                {
                    /* Enable digital register */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET ) , pin_num);
                    /* Disable analog register */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pin_num);
                }

               /*---------------------------------------------------------------------------------------------------------------*/

                /* Set the Mode configured in the GPIOPCTL register */
                uint32 GPIOCTL = *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET);
                GPIOCTL = ((GPIOCTL) & (0xF0 << pin_num *4) ) | ((ConfigPtr->arr[i].mode) << pin_num *4 );


            }


	}


}
/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): port pin id number / port pin direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: set port pin direction
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API== STD_ON)
void Port_SetPinDirection (Port_PinType Pin , Port_PinDirectionType Direction)
{

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        /* Report error: init function has not been called first */
        Det_ReportError(PORT_MODULE_ID , PORT_INSTANCE_ID , PORT_SET_PIN_DIRECTION_SID , PORT_E_UNINIT);
    }
    else
    {
        /* Do Nothing */
    }
#endif


    /* Local variable to hold the configuration index */
    uint8 copy_localConfigIndex;
    uint8 i ;
    /* Search for the pin to be configured*/
    for (i = 0; i < PORT_CONFIGURED_PINS; i++)
    {
        if (ptr[i].pin_id == Pin)
        {
            copy_localConfigIndex = i;
            break; // Exit the loop once the index of the passed pin id is found
        }
    }


    /*-----------------------------------------Error detection-----------------------------------------------*/

    #if (PORT_DEV_ERROR_DETECT == STD_ON)
        if(ptr[copy_localConfigIndex].d_ch == STD_OFF)
        {
            /* direction can not be changed during run time */
            Det_ReportError(PORT_MODULE_ID , PORT_INSTANCE_ID , PORT_SET_PIN_DIRECTION_SID ,PORT_E_DIRECTION_UNCHANGEABLE);
        }
        else
        {
            /* Do Nothing */
        }

        
        if (Pin > 38 )
        {
        	/* Report error:the Pin parameter is out of range */
            Det_ReportError(PORT_MODULE_ID , PORT_INSTANCE_ID , PORT_SET_PIN_DIRECTION_SID , PORT_E_PARAM_PIN);
        }
        else
        {
            /* Do Nothing */
        }

    #endif

     /*--------------------------------------------------------------------------------------------------------*/

    /*-------------------------No errors detected, proceed with configuring the pin----------------------------*/

    /* Pointer to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULL_PTR;

    /* Get the port number and pin number */
    uint8 port_num = Port_GetNumber(Pin);
    uint8 pin_num = Pin_GetNumber(port_num , Pin);

    /* Choose the base address register according to the port number */
    switch (port_num)
    {
        case 0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
        case 1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
        case 2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
        case 3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
        case 4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
        case 5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
    }

    /*----------------------------Special handling for certain pins-----------------------------------*/

    if (((port_num == PORTD) && (pin_num == 7)) || ((port_num == PORTF) && (pin_num == 0)))
    {
        /* Unlock the GPIOCR register */
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;
        /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , pin_num);
    }
    else
    {

    }

    /*--------------------------------------------------------------------------------------------------*/
    
    /*-----------------------------------------configure the direction-----------------------------------*/
    if (Direction == PORT_PIN_OUT)
    {
        /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pin_num);


    }
    else if (Direction == PORT_PIN_IN)
    {
        /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pin_num);

    }
    else
    {
        /* Do Nothing */
    }
    /*---------------------------------------------------------------------------------------------------------*/
}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction
************************************************************************************/

void Port_RefreshPortDirection (void)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        /* Report error: init function has not been called first */
        Det_ReportError(PORT_MODULE_ID , PORT_INSTANCE_ID , PORT_REFRESH_PORT_DIRECTION_SID , PORT_E_UNINIT);
    }
    else
    {
        /* Do Nothing */
    }

#endif

    /*-----------------------------------refresh the direction of configured pins-----------------------------------------*/
    uint8 i;
    for (i=0 ; i<PORT_CONFIGURED_PINS ; i++)
        {
            if(ptr[i].d_ch == STD_ON)
            {
                /* skip this pin don't refresh it */
                continue;

            }
            else
            {
                /* Do Nothing */
            }
            /* Pointer to the required Port Registers base address */
                volatile uint32 * PortGpio_Ptr = NULL_PTR;

                /* Get the port number and pin number */
                uint8 port_num = Port_GetNumber(ptr[i].pin_id);
                uint8 pin_num = Pin_GetNumber(port_num ,ptr[i].pin_id);

                /* Choose the base address register according to the port number */
                switch (port_num)
                {
                    case 0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                            break;
                    case 1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                            break;
                    case 2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                            break;
                    case 3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                            break;
                    case 4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                            break;
                    case 5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                            break;
                }

                /*----------------------------Special handling for certain pins-----------------------------------*/

                if (((port_num == PORTD) && (pin_num == 7)) || ((port_num == PORTF) && (pin_num == 0)))
                {
                    /* Unlock the GPIOCR register */
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;
                    /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , pin_num);
                }
                else
                {
                    /* Do Nothing */
                }



              /*------------------------------------------------------------------------------------------------------------*/

                if(ptr[i].pin_enable == Disable)
                {
                    /* this pin is configured as default configuration */
                    /* Refresh the direction as default direction -> input */

                    /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pin_num);


                }
                else if (ptr[i].pin_enable == Enable)
                {

                    /*------------------this pin is not configured as default configuration-------------------------*/
                    /*---------------------refresh the direction as configured--------------------------------------*/
                    if (ptr[i].direction == PORT_PIN_OUT)
                    {
                        /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pin_num);

                    }
                    else if (ptr[i].direction== PORT_PIN_IN)
                    {
                        /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pin_num);

                    }
                    else
                    {
                        /* Do Nothing */
                    }
                }

        }
}


/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): pointer to where to store version information
* Return value: None
* Description: returns the version information of this module
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInto (Std_VersionInfoType* versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
	}
	else
	{
	    /* Do Nothing */
	}
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
#endif
/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy:  reentrant
* Parameters (in): port pin id number / new port pin mode
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: sets the pin mode 
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode (Port_PinType Pin , Port_PinModeType Mode)
{

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        /* Report error: init function has not been called first */
        Det_ReportError(PORT_MODULE_ID , PORT_INSTANCE_ID , PORT_SET_PIN_DIRECTION_SID , PORT_E_UNINIT);
    }
    else
    {
        /* Do Nothing */
    }

#endif
    /* Local variable to hold the configuration index */
    uint8 copy_localConfigIndex;
    uint8 i ;

    /* Search for the configuration index corresponding to the given pin */
    for (i = 0; i < PORT_CONFIGURED_PINS ; i++)
    {
        if (ptr[i].pin_id == Pin)
        {
            copy_localConfigIndex = i;
            break; // Exit the loop once the index is found
        }
    }



    /*------------------------------------------Error detection--------------------------------------------*/
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
        

        if(ptr[copy_localConfigIndex].m_ch == STD_OFF)
        {
            /* direction can not be changed during run time */
            Det_ReportError(PORT_MODULE_ID , PORT_INSTANCE_ID , PORT_SET_PIN_DIRECTION_SID ,PORT_E_DIRECTION_UNCHANGEABLE);
        }
        else
        {
            /* Do Nothing */
        }

        if ( Mode > 10)
        {
        	/* Report error: mode is invalid */
            Det_ReportError(PORT_MODULE_ID , PORT_INSTANCE_ID , PORT_SET_PIN_MODE_SID , PORT_E_PARAM_INVALID_MODE);
        }
        else
        {
            /* Do Nothing */
        }

        
        if (Pin > 38 )
        {
        	/* Report error: the pin parameter is out of range */
            Det_ReportError(PORT_MODULE_ID , PORT_INSTANCE_ID ,  PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
        }
        else
        {
            /* Do Nothing */
        }
    #endif
     /*---------------------------------------------------------------------------------------------------------*/

    /*-------------------------No errors detected, proceed with configuring the pin-----------------------------*/



    /* Pointer to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULL_PTR;

    /* Get the port number and pin number */
    uint8 port_num = Port_GetNumber(Pin);
    uint8 pin_num = Pin_GetNumber(port_num , Pin);

    /* Choose the base address register according to the port number */
    switch (port_num)
    {
        case 0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
        case 1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
        case 2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
        case 3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
        case 4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
        case 5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
    }

    /*-----------------------------------Special handling for certain pins-----------------------------------*/
    if (((port_num == PORTD) && (pin_num == 7)) || ((port_num == PORTF) && (pin_num == 0)))
    {
        /* Unlock the GPIOCR register */
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;
        /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , pin_num);
    }
    else
    {

    }


    /* Check if Mode is different from Gpio_Mode */
    if (Mode != Gpio_Mode)
    {
        /* Set alternative function */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pin_num);
    }
    else
    {
        /* Clear alternative function */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pin_num);
    }

    /*-------------------------------------------------------------------------------------------------------------*/

    /*--------------------------------------Special handling for certain mode-------------------------------------*/
    if (Mode == ADC_Mode)
    {
        /* Enable analog register */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pin_num);
        /* Disable digital register */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET ) , pin_num);
    }
    else
    {
        /* Enable digital register */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET ) , pin_num);
        /* Disable analog register */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pin_num);
    }

   /*---------------------------------------------------------------------------------------------------------------*/

    /* Set the Mode configured in the GPIOPCTL register */
    uint32 GPIOCTL = *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET);
    GPIOCTL = ((GPIOCTL) & (0xF0 << pin_num *4)) |( Mode << pin_num*4 );
}
#endif
