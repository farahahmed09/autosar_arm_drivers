/*
 * @file Systick.h
 * @brief Header file for the Systick module.
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

#ifndef SYSTICK_H
#define SYSTICK_H

/****************************************************************************
*****************************  Includes   ***********************************
*****************************************************************************/

#include "Systick_Regs.h"
#include "Systick_Cfg.h"
#include "Common_Macros.h"

/**
 * @brief Defination of SYSTICK Module Id
 *
 *
 * @details
 * - Type: define
 * - Range: 100U
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define SYSTICK_MODULE_ID    				(100U)

 /**
  * @brief Defination of SYSTICK Instance ID
  *
  *
  * @details
  * - Type: define
  * - Range: 255U
  * - Resolution: Fixed
  * - Unit: Bits
  */

  /* SYSTICK Instance Id */
#define SYSTICK_INSTANCE_ID    				(255U)

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
#define SYSTICK_SW_VERSION      	     	(1U)

 /**
   * @brief Defination of AUTOSAR Version R23-11
   *
   *
   * @details
   * - Type: define
   * - Range: 22U
   * - Resolution: Fixed
   * - Unit: Bits
   */
#define SYSTICK_AR_RELEASE_VERSION  	 	(22U)

/**
 * @brief AUTOSAR checking between Std Types and SYSTICK Modules
 */
#if (STD_TYPES_AR_RELEASE_VERSION != SYSTICK_AR_RELEASE_VERSION)
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/**
 * @brief AUTOSAR Version checking between SYSTICK_Cfg.h and SYSTICK.h files
 */
#if (SYSTICK_CFG_AR_RELEASE_VERSION != SYSTICK_AR_RELEASE_VERSION)
#error "The AR version of SYSTICK_Cfg.h does not match the expected version"
#endif

/**
 * @brief Software Version checking between SYSTICK_Cfg.h and SYSTICK.h files
 */
#if (SYSTICK_CFG_SW_VERSION != SYSTICK_SW_VERSION)
#error "The SW version of SYSTICK_Cfg.h does not match the expected version"
#endif

/* ===================================================================================================
												 Development Errors Id
	 ===================================================================================================*/

/**
 * @brief Defination of passing parameters to be used in Det_ReportError as uninitialized driver in code
 *
 *
 * @details
 * - Type: define
 * - Range: 0x0A
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define SYSTICK_E_UNINIT					 0x0A      /* API service called without module initialization */
/**
 * @brief Defination of passing parameters to be used in Det_ReportError as already initialized driver in code
 *
 *
 * @details
 * - Type: define
 * - Range: 0x0D
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define SYSTICK_E_ALREADY_INITIALIZED		 0x0D      /* API service for initialization called when already initialized */
/**
 * @brief Defination of type of error in passing parameters to be used in Det_ReportError as Failed initialization in code
 *
 *
 * @details
 * - Type: define
 * - Range: 0x0E
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define SYSTICK_E_INIT_FAILED				 0x0E     /*API error return code: Init function failed  */
/**
 * @brief Defination of passing parameters to be used in Det_ReportError as Wrong Channel in code
 *
 *
 * @details
 * - Type: define
 * - Range: 0x14
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define SYSTICK_E_PARAM_CHANNEL				 0x14    /* API parameter checking: invalid channel */
/**
 * @brief Defination of passing parameters to be used in Det_ReportError as Invalid value in code
 *
 *
 * @details
 * - Type: define
 * - Range: 0x15
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define SYSTICK_E_PARAM_VALUE                0x15     /* API parameter checking: invalid value */
/**
 * @brief Defination of passing parameters to be used in Det_ReportError as Wrong Null pointer in code
 *
 *
 * @details
 * - Type: define
 * - Range: 0x16
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define SYSTICK_E_PARAM_POINTER				 0x16      /* API parameter checking: invalid pointer */
/**
 * @brief Defination of passing parameters to be used in Det_ReportError as Wrong Predef Timer in code
 *
 *
 * @details
 * - Type: define
 * - Range: 0x17
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define SYSTICK_E_PARAM_PREDEF_TIMER         0x17      /* API parameter checking: invalid Predef Timer */
/**
 * @brief Defination of type of error in passing parameters to be used in Det_ReportError as Wrong Mode in code
 *
 *
 * @details
 * - Type: define
 * - Range: 0x1F
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define SYSTICK_E_PARAM_MODE                 0x1F      /* API parameter checking: invalid mode */

/* ===================================================================================================
											Runtime Errors Id
   ===================================================================================================*/
/**
 * @brief Defination of type of error in passing parameters to be used in Det_ReportError as Calling Timer channel while it is still busy in code
 *
 *
 * @details
 * - Type: define
 * - Range: 0x0B
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define SYSTICK_E_BUSY                        0x0B      /* API service called when timer channel is still busy */

/**
 * @brief Defination of type of error in passing parameters to be used in Det_ReportError as Using a Wrong Mode of timer in code
 *
 *
 * @details
 * - Type: define
 * - Range: 0x0C
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define SYSTICK_E_MODE                        0x0C      /* API service called when driver is in wrong mode */

 /* ===================================================================================================
							     		 API Service Id Macros
    ===================================================================================================*/
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
#define SYSTICK_GET_VERSION_INFO_SID        (uint8)0x00

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
#define SYSTICK_INIT_SID                    (uint8)0x01

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
#define SYSTICK_DEINIT_SID                  (uint8)0x02
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

#define SYSTICK_GET_TIME_ELAPSED_SID        (uint8)0x03
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

#define SYSTICK_GET_TIME_REMAINING_SID      (uint8)0x04
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

#define SYSTICK_START_TIMER_SID             (uint8)0x05
							   /**
								* @brief Defination of API to be used in Det_ReportError
								*
								*
								* @details
								* - Type: define
								* - Range: 0x06
								* - Resolution: Fixed
								* - Unit: Bits
								*/

#define SYSTICK_STOP_TIMER_SID              (uint8)0x06
								/**
								 * @brief Defination of API to be used in Det_ReportError
								 *
								 *
								 * @details
								 * - Type: define
								 * - Range: 0x07
								 * - Resolution: Fixed
								 * - Unit: Bits
								 */

#define SYSTICK_ENABLE_NOTIFICATION_SID     (uint8)0x07
								 /**
								  * @brief Defination of API to be used in Det_ReportError
								  *
								  *
								  * @details
								  * - Type: define
								  * - Range: 0x08
								  * - Resolution: Fixed
								  * - Unit: Bits
								  */

#define SYSTICK_DISABLE_NOTIFICATION_SID    (uint8)0x08
								  /**
								   * @brief Defination of API to be used in Det_ReportError
								   *
								   *
								   * @details
								   * - Type: define
								   * - Range: 0x09
								   * - Resolution: Fixed
								   * - Unit: Bits
								   */

#define SYSTICK_SET_MODE_SID                (uint8)0x09
								   /**
									* @brief Defination of API to be used in Det_ReportError
									*
									*
									* @details
									* - Type: define
									* - Range: 0x0A
									* - Resolution: Fixed
									* - Unit: Bits
									*/

#define SYSTICK_DISABLE_WAKEUP_SID          (uint8)0x0A
/**
 * @brief Defination of API to be used in Det_ReportError
 *
 *
 * @details
 * - Type: define
 * - Range: 0x0B
 * - Resolution: Fixed
 * - Unit: Bits
 */

#define SYSTICK_ENABLE_WAKEUP_SID           (uint8)0x0B
/**
 * @brief Defination of API to be used in Det_ReportError
 *
 *
 * @details
 * - Type: define
 * - Range: 0x0C
 * - Resolution: Fixed
 * - Unit: Bits
 */
#define SYSTICK_CHECK_WAKEUP_SID            (uint8)0x0C


#define SYSTICK_MODULE_UNINITIALIZED 			(0U)
#define SYSTICK_MODULE_INITIALIZED 				(1U)


/*============================================================================*/

/* ===================================================================================================
											Module Data Types
   ===================================================================================================*/
typedef uint32 Systick_ValueType;   /* Type definition for SysTick timer value */

typedef enum
{
    SYSTICK_BUSYWAIT,              /* Mode for busy waiting */
    SYSTICK_SINGLE_INTERVAL,       /* Mode for single interval */
    SYSTICK_PERIODIC_INTERVAL      /* Mode for periodic interval */
} Systick_ModeType;


typedef enum
{
    SYSTICK_PERIODIC,   /* Periodic mode for SysTick */
    SYSTICK_ONE_SHOT    /* One-shot mode for SysTick */
} SysTick_Periodicity;  


	typedef enum
{
    SYSTICK_CTRL_ENABLE = 0,    /* Bit position for the sysTick enable bit in the control register */
    SYSTICK_CTRL_TICKINT,       /* Bit position for the sysTick tick interrupt enable bit in the control register */
    SYSTICK_CTRL_CLKSOURCE,     /* Bit position for the sysTick clock source selection bit in the control register */
    SYSTICK_CTRL_COUNTFLAG = 16,/* Bit position for the sysTick count flag bit in the control register */

    SYSTICK_AHB_8 = 0,          /* Value representing AHB srescaler of 8 for SysTick clock */
    SYSTICK_AHB,                /* Value representing AHB srescaler of 1 for SysTick clock */
} Systick_Def;                  /* Enum defining bit positions and values for SysTick control register */


typedef enum
{
    SYSTICK_PREDEF_TIMER_1US_16BIT,    /* Predefined timer type: 16-bit timer with 1us resolution */
    SYSTICK_PREDEF_TIMER_1US_24BIT,    /* Predefined timer type: 24-bit timer with 1us resolution */
    SYSTICK_PREDEF_TIMER_1US_32BIT,    /* Predefined timer type: 32-bit timer with 1us resolution */
    SYSTICK_PREDEF_TIMER_100US_32BIT   /* Predefined timer type: 32-bit timer with 100us resolution */
} SysTick_PredefTimerType;             /* Enum defining predefined SysTick timer types */



/* Structure to hold the configuration data for the Port Driver */
typedef struct
{
	Systick_Def Clk;
	Systick_ModeType SysTick_ChannelMode;
	void (*Copy_ptr);
} Systick_ConfigType;

extern const Systick_ConfigType Systick_Configuration;
/*============================================================================*/

/* ===================================================================================================
										   Function Prototypes
   ===================================================================================================*/

/**
 * @brief Callback pointer for SysTick.
 */
void (*SysTickCallback) (void);

/**
 * @brief Initialize the SysTick module.
 *
 * @param[in] ConfigPtr - Pointer to the configuration structure.
 * @return     None
 */
void Systick_Init(const Systick_ConfigType* ConfigPtr);

/**
 * @brief Deinitialize the SysTick module.
 *
 * @param[in]   None
 * @param[out]  None
 * @return      None
 */
void Systick_DeInit(void);

/**
 * @brief Get the time elapsed since the SysTick timer started.
 *
 * @param[in]  None
 * @return Elapsed timer value (in number of ticks).
 */
Systick_ValueType Systick_GetTimeElapsed(void);

/**
 * @brief Get the time remaining until the target time is reached.
 *
 * @param[in]  None
 * @return Remaining timer value (in number of ticks) until the target time is reached.
 */
Systick_ValueType Systick_GetTimeRemaining(void);

/**
 * @brief Start the SysTick timer with a given value.
 *
 * @param[in] Value - The number of ticks to wait.
 * @param[out]  None
 * @return      None
 *
 */
void Systick_StartTimer(Systick_ValueType Value);

/**
 * @brief Stop the SysTick timer.
 *
 * @param[in]   None
 * @param[out]  None
 * @return      None
 */
void Systick_StopTimer(void);

/**
 * @brief Set the mode of the SysTick.
 *
 * @param[in] Mode - The mode to set.
 * @param[out]  None
 * @return      None
 */
void Systick_SetMode(Systick_ModeType Mode);

//Std_ReturnType Systick_GetPredefTimerValue(Systick_PredefTimerType PredefTimer, uint32* TimeValuePtr);

/**
 * @brief Get the version information of the SysTick module.
 *
 * @param[in]  None
 * @param[out] VersionInfoPtr - Pointer to store the version information.
 * @return     none
 *
 */
void Systick_GetVersionInfo(Std_VersionInfoType* versioninfo);

#endif
