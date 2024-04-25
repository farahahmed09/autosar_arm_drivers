/*
 * @file Systick_Cfg.h
 * @brief Configrution Header file for the Systick module.
 *
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

#ifndef SYSTICK_CFG_H_
#define SYSTICK_CFG_H_

/*============================================================================*/

/*
 * Module Version 1.0.0
 */
#define SYSTICK_SW_MAJOR_VERSION                (1U)
#define SYSTICK_SW_MINOR_VERSION              	(0U)
#define SYSTICK_SW_PATCH_VERSION              	(0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define SYSTICK_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define SYSTICK_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define SYSTICK_CFG_AR_RELEASE_PATCH_VERSION     (3U)

#define SYSTICK_CFG_AR_RELEASE_VERSION 			 (22U)
#define SYSTICK_CFG_SW_VERSION					 (1U)


/* Pre-compile option for Development Error Detect */
#define SYSTICK_DEV_ERROR_DETECT                    (STD_ON)

/* function SYSTICK_SetMode is only available if the configuration parameter SystickReportWakeupSource is enabled */
#define SYSTICK_WAKEUP_FUNCTIONALITY_API            (STD_ON)

/* Pre-compile option for enable or disable notification */
#define SYSTICK_ENABLE_DISABLE_NOTIFICATION_API     (STD_ON)

/* Pre-compile option for Version Info API */
#define SYSTICK_VERSION_INFO_API        			(STD_ON)

/* Pre-compile option for DeInit API */
#define SystickDeInitApi              			    (STD_ON)

/* Pre-compile option for GetTimeElapsed API */
#define SystickTimeElapsedApi        			    (STD_ON)

/* Pre-compile option for SYSTICKTimeRemainingApi API */
#define SystickTimeRemainingApi       			    (STD_ON)

/* Pre-compile option to support SYSTICK as wakeup source */
#define SystickReportWakeupSource      				(STD_ON)

/*******************************************************************************/

#define NUM_OF_PORTS   3
#define NUM_OF_PINS    48

#endif /* SYSTICK_CFG_H */
