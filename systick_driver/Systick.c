/**
 * @file Systick.c
 * @brief source file for the Systick module.
 *
 * This file contains the declarations and definitions for the Systick module in accordance
 * with the AUTOSAR standard.
 *
 * @copyright [Cairo Racing team -Formula students]
 * @author [ Mohamed Mabrouk, Ahmed Yassin , Farah Ahmed]
 * @date [17 0ct 2023]
 *
 * @SWversion 1.0.0
 *
 * @remarks
 *    -Project          : AUTOSAR  R22-11 MCAL
 *    -Platform         : ARM
 *    -Peripherial      : STM32F103C8T6
 *    -AUTOSAR Version  : R22-11
 */
 /*==================================================================================================================================*/
/****************************************************************************
*****************************  Includes   ***********************************
*****************************************************************************/
#include "Systick.h"
#include "Det.h"

/*==================================================================================================================================*/

/****************************************************************************
*****************************  Global Variables   ***************************
*****************************************************************************/

/* Systick_Configs store the default values of port that you declare it in Lcfg.c  */
static Systick_ConfigType Systick_Configs;
uint8 SingleIntervalFlag = 0 ;

 /*==================================================================================================================================*/
/****************************************************************************
*****************************  Functions Definition   ***************************
*****************************************************************************/

/**
 * \section Service_Name
 * Systick_Init
 *
 * \section Description
 * Function to Initialize the Systick driver
 * \section Req_ID
 * Systick_0x01
 *
 * \section Scope
 * Public
 *
 * \section Re-entrancy
 * Non Reentrant
 *
 * \section Sync_Async
 * Synchronous
 *
 * \param[in] ConfigPtr \ Pointer to a selected configuration structure
 * \param[inout] None
 * \param[out] None
 * \return void
 *
 * @startuml
 * start
 *
 * if (Clock Mode is AHB Div 8) then (yes)
 * :Clk=AHB Div 8;
 * elseif (Clock Mode is AHB) then (yes)
 * :Clk=AHB;
 * endif
 * if (Mode == BUSYWAIT) then (yes)
 * :Counting Mode = BUSYWAIT;
 * elseif (Mode == SINGLE_INTERVAL) then (yes)
 * :Counting Mode = SINGLE_INTERVAL;
 * elseif (Mode = PERIODIC_INTERVAL) then (yes)
 * :Counting Mode = PERIODIC_INTERVAL;
 * endif
 *
 * end
 * @enduml
*/
void Systick_Init(const Systick_ConfigType* ConfigPtr)
{
    /* Check if ConfigPtr is not NULL */
    if (ConfigPtr != NULL_PTR)
    {
        /* set sysTick control register with clock configuration */
        SYSTICK->CTRL = ((ConfigPtr->Clk) << 2);

        /* set the configuration of the Lcfg.c into the global variable */
        Systick_Configs.SysTick_ChannelMode = ConfigPtr->SysTick_ChannelMode;
        Systick_Configs.Copy_ptr = ConfigPtr->Copy_ptr;
    }
    else
    {
        /* report error: ConfigPtr is NULL */
        Det_ReportError(SYSTICK_MODULE_ID, SYSTICK_INSTANCE_ID,SYSTICK_INIT_SID,SYSTICK_E_PARAM_POINTER);
    }
}

/**
 * \section Service_Name
 * Systick_DeInit
 *
 * \section Description
 * Function to Deinitialize the Systick driver
 * \section Req_ID
 * Systick_0x02
 *
 * \section Scope
 * Public
 *
 * \section Re-entrancy
 * Non Reentrant
 *
 * \section Sync_Async
 * Synchronous
 *
 * \param[in] ConfigPtr \ Pointer to a selected configuration structure
 * \param[inout] None
 * \param[out] None
 * \return void
 *
 * @startuml
 * start
 *
 * :CLEAR THE CTRL REGISTER;
 * :CLEAR THE VAL REGISTER;
 *
 * end
 * @enduml
*/
void Systick_DeInit(void)
{
	/*Disableing the systick*/
	SYSTICK->VAL = 0x0;
}
/**
 * \section Service_Name
 * Systick_GetTimeElapsed
 *
 * \section Description
 * Function to Return the time already elapsed.
 * \section Req_ID
 * Systick_0x03
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
 * \param[in] None
 * \param[inout] None
 * \param[out] None
 * \return Systick_ValueType
 *
 * @startuml
 * start
 * :LOAD_Register - VAL_Register;
 * :Return the Value of Elapsed Time;
 *
 * end
 * @enduml
*/
Systick_ValueType Systick_GetTimeElapsed(void)
{
    // Calculate the elapsed time using the reload value and the current value
	return (SYSTICK->LOAD - SYSTICK->VAL);
}
/**
 * \section Service_Name
 * Systick_GetTimeRemaining
 *
 * \section Description
 * Function to Return the time remaining until the target time is reached.
 * \section Req_ID
 * Systick_0x04
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
 * \param[in] None
 * \param[inout] None
 * \param[out] None
 * \return Systick_ValueType
 *
 * @startuml
 * start
 * :Get Value From VAL_Register;
 * :Return the Value of TimeRemaining;
 *
 * end
 * @enduml
*/
Systick_ValueType Systick_GetTimeRemaining(void)
{
	/*returns the remaining time of val register*/
	return (SYSTICK->VAL);
}
/**
 * \section Service_Name
 * Systick_StartTimer
 *
 * \section Description
 * Function to Starts Systick timer.
 * \section Req_ID
 * Systick_0x05
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
 * \param[in] Value
 * \param[inout] None
 * \param[out] None
 * \return void
 *
 * @startuml
 * start
 * 
 * :CLEAR THE VAL REGISTER;
 * :PUT THE TIME NEEDED IN LOAD REGISTER;
 *
 * switch (Timer Mode?)
 * case ( )
 * :Enable the Counter;
 * while (Count_flag=0)
 * :Stay Still Till Counter Finish;
 * endwhile
 * :Disable the Counter;
 * case ( ) 
 * :Save the callbackFunc Address;
 * :Set The SingleIntervalFlag;
 * :Enable TICK INTERRUPT;
 * :Enable the Counter;
 * case ( )
 * :Save the callbackFunc Address;
 * :Enable TICK INTERRUPT;
 * :Enable the Counter;
 * endswitch
 * 
 * end
 * @enduml
*/
void Systick_StartTimer(Systick_ValueType Value)
{
    /* Clear the current value register */
    SYSTICK->VAL = 0;
    /* Load the number of ticks to wait in microseconds */
    SYSTICK->LOAD = Value*1000;
    switch (Systick_Configs.SysTick_ChannelMode)
    {
        case SYSTICK_BUSYWAIT:
            /* Set the enable bit to begin counting */
            SET_BIT(SYSTICK->CTRL, SYSTICK_CTRL_ENABLE);
            /* Wait until the COUNTFLAG becomes 1 (indicating the time has elapsed) */
            while (!GET_BIT(SYSTICK->CTRL, SYSTICK_CTRL_COUNTFLAG));
            /* Clear the enable bit to stop counting */
            CLEAR_BIT(SYSTICK->CTRL, SYSTICK_CTRL_ENABLE);
            break;
        case SYSTICK_SINGLE_INTERVAL:
            /* set the callback pointer */
            SysTickCallback = Systick_Configs.Copy_ptr;
            /* mark that you entered this function */
            SingleIntervalFlag = 1;
            /* set the interrupt and enable bits to begin counting */
            SET_BIT(SYSTICK->CTRL, SYSTICK_CTRL_TICKINT);
            SET_BIT(SYSTICK->CTRL, SYSTICK_CTRL_ENABLE);
            break;
        case SYSTICK_PERIODIC_INTERVAL:
            /* Set the callback pointer */
            SysTickCallback = Systick_Configs.Copy_ptr;
            /* Set the interrupt and enable bits to begin counting */
            SET_BIT(SYSTICK->CTRL, SYSTICK_CTRL_TICKINT);
            SET_BIT(SYSTICK->CTRL, SYSTICK_CTRL_ENABLE);
            break;
    }
    
    if (*SysTickCallback == NULL_PTR)
    {
    	/* report error: SysTickCallback is NULL */
        Det_ReportError(SYSTICK_MODULE_ID, SYSTICK_INSTANCE_ID, SYSTICK_START_TIMER_SID, SYSTICK_E_PARAM_POINTER);
    }
    else
    {
        // Do Nothing
    }
}

/**
 * \section Service_Name
 * Systick_StopTimer
 *
 * \section Description
 * Function to Stop a Systick timer.
 * \section Req_ID
 * Systick_0x06
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
 * \param[in] None
 * \param[inout] None
 * \param[out] None
 * \return void
 *
 * @startuml
 * start
 * 
 * :Disable The Counter;
 * :CLEAR THE VAL REGISTER;
 * 
 * end
 * @enduml
*/
void Systick_StopTimer(void)
{
	/*Clear the value of Enable bit*/
	CLEAR_BIT(SYSTICK->CTRL, SYSTICK_CTRL_ENABLE);
	SYSTICK->VAL = 0;
}
/**
 * \section Service_Name
 * Systick_SetMode
 *
 * \section Description
 * Function to Set the operation mode of the Systick.
 * \section Req_ID
 * Systick_0x07
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
 * \param[in] Mode
 * \param[inout] None
 * \param[out] None
 * \return void
 *
 * @startuml
 * start
 *
 * switch (Timer Mode?)
 * case ( )
 * :Set the Mode to BUSYWAIT;
 * case ( ) 
 * :Set the Mode to SINGLE_INTERVAL;
 * case ( )
 * :Set the Mode to PERIODIC_INTERVAL;
 * endswitch
 *
 * end
 * @enduml
*/
void Systick_SetMode(Systick_ModeType Mode)
{
	/*Setting given mode into the LCfg.c */
	Systick_Configs.SysTick_ChannelMode = Mode;
}
/**
 * \section Service_Name
 * SysTick_Handler
 *
 * \section Description
 * Interrupt Fuction.
 * \section Req_ID
 * Systick_0x08
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
 * \param[in] None
 * \param[inout] None
 * \param[out] None
 * \return void
 *
 * @startuml
 * start
 *
 * if (SingleIntervalFlag) then (yes)
 * :Clear Tick Interrupt;
 * :Disable Counter;
 * :SingleIntervalFlag=0;
 * endif
 * :Clear CountFlag;
 * :Jump to given function to be excuted when ISR flag is fired;
 *
 * end
 * @enduml
*/
void SysTick_Handler()
{
    /* call the callback function (if set) to handle the SysTick interrupt */
    if (SysTickCallback != NULL_PTR)
    {
        SysTickCallback();  /* Call the callback function */
    }
    else
    {
    	/* report error: SysTickCallback is NULL */
        Det_ReportError(SYSTICK_MODULE_ID, SYSTICK_INSTANCE_ID, SYSTICK_START_TIMER_SID, SYSTICK_E_PARAM_POINTER);
       
    }

    /* Stop continuous counting in single interval mode */
    if (SingleIntervalFlag == SYSTICK_ONE_SHOT)
    {
        CLEAR_BIT(SYSTICK->CTRL, SYSTICK_CTRL_TICKINT); /* disable SysTick interrupt */
        CLEAR_BIT(SYSTICK->CTRL, SYSTICK_CTRL_ENABLE);  /* disable SysTick timer */
        SingleIntervalFlag = 0;  /* reset the mark flag */
    }

    /* clear the countflag */
    CLEAR_BIT(SYSTICK->CTRL, SYSTICK_CTRL_COUNTFLAG); 
}



/**
 * \section Service_Name
 *  Systick_GetVersionInfo 
 *
 * \section Description
 * update the version
 *
 * \section Req_ID
 * Systick_0x09
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

void Systick_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    if (versioninfo != NULL_PTR)
    {
    /* Copy the Module Id */
	versioninfo->moduleID  = SYSTICK_MODULE_ID         ;
	/* Copy Software Version */
	versioninfo->sw_version = SYSTICK_SW_MAJOR_VERSION ;
    }
    else
	{
	Det_ReportError(SYSTICK_MODULE_ID, SYSTICK_INSTANCE_ID, SYSTICK_GET_VERSION_INFO_SID, SYSTICK_E_PARAM_POINTER);
	}

}
