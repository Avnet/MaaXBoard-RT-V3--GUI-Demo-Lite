/*
 * globals.h
 *
 *  Created on: May 27, 2021
 *      Author: gulziibayar
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "fsl_pit.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "event_groups.h"
#include "fsl_lpuart_freertos.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Freertos task can be enabled by setting 1, disabled by setting 0 */
#define GUI_EN			1
#define CONSOLE_EN		1
#define AUDIO_EN		1

/* Maaxboard RT Version*/
#define MAAXBOARD_VERSION_MAJOR	"1"
#define MAAXBOARD_VERSION_MINOR	"0"
#define MAAXBOARD_VERSION_DATE	"2022-03-10"
#define MAAXBOARD_VERSION_STRING	"Avnet GUI Demo Lite v"MAAXBOARD_VERSION_MAJOR"."MAAXBOARD_VERSION_MINOR" ["MAAXBOARD_VERSION_DATE"]"


/* CLI definitions */
#define DEMO_LPUART LPUART1
#define DEMO_LPUART_CLK_FREQ BOARD_DebugConsoleSrcFreq()
#define DEMO_LPUART_IRQn LPUART1_IRQn

#define USER_LED_GREEN_GPIO GPIO8
#define USER_LED_RED_GPIO GPIO9
#define USER_LED_BLUE_GPIO GPIO9

#define GREEN_PIN	28u
#define RED_PIN		7u
#define BLUE_PIN	9u

/* PIT Timer used for runtime analysis on Freertos */
#define PIT1_PERIPHERAL PIT1
/* Definition of clock source frequency. */
#define PIT1_CLK_FREQ 240000000UL
/* Definition of ticks count for channel 0 - deprecated. */
#define PIT1_0_TICKS 23999U
/* PIT1 interrupt vector ID (number) - deprecated. */
#define PIT1_0_IRQN PIT0_IRQn
/* PIT1 interrupt handler identifier - deprecated. */
#define PIT1_0_IRQHANDLER PIT0_IRQHandler
/* Definition of channel number for channel 0. */
#define PIT1_CHANNEL_0 kPIT_Chnl_0
/* Definition of ticks count for channel 0. */
#define PIT1_CHANNEL_0_TICKS 23999U
/* PIT1 interrupt vector ID (number). */
#define PIT1_IRQN PIT1_IRQn
/* PIT1 interrupt handler identifier. */
#define PIT1_IRQHANDLER PIT1_IRQHandler


/* struct wrapper for freertos console task input parameter */
typedef struct
{
	lpuart_rtos_handle_t *uart_handle;
}custom_console_instance_t;

typedef enum
{
	GUI_TASK,
	CONSOLE_TASK
}requesting_task;


#endif /* GLOBALS_H_ */
