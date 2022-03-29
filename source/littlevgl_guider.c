/**
 * @brief - Maaxboard RT Demo
 * @Description - Demo program can be interacted with both GUI and Console.
 * LPUART1 is used at baudrate 115200 for console application. It is physically available on debug UART 3-pin header.
 * LPUART6 is used for printing debug message. It is available on 40 pin header.
 *
 * Following commands are available on console
 *--------- PERIPHERALS ----------------
 * led ***    : RGB LEDs on/off
 *--------- AUDIO & VIDEO --------------
 * am ##      : Audio L/R output (mic# 1-4)
 *--------- UTILITY --------------------
 * stats      : RTOS Statistics
 * clr        : Clear the terminal
 * q/ctrl+c   : Abort the command
 * ? / h      : Menu Help
 */

/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "FreeRTOS.h"
#include "queue.h"
#include "event_groups.h"
#include "fsl_lpuart_freertos.h"

#include "fsl_debug_console.h"
#include "littlevgl_support.h"
#include "pin_mux.h"
#include "board.h"
#include "lvgl.h"
#include "gui_guider.h"
#include "events_init.h"

#include "fsl_soc_src.h"

#include "fsl_lpuart_freertos.h"
#include "fsl_lpuart.h"
#include "globals.h"
#include "demo_common.h"
#include "audio_demo.h"
#include "lvgl_demo.h"
#include "UART_CLI.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_CUSTOM_HOOKS 4

extern void (*g_os_tick_hooks[MAX_CUSTOM_HOOKS])(void);
extern void (*g_os_idle_hooks[MAX_CUSTOM_HOOKS])(void);

void (*g_os_tick_hooks[MAX_CUSTOM_HOOKS])(void) = {NULL};
void (*g_os_idle_hooks[MAX_CUSTOM_HOOKS])(void) = {NULL};

/*******************************************************************************
 * Variables
 ******************************************************************************/
portSTACK_TYPE *lvgl_task_stack = NULL;
TaskHandle_t lvgl_task_task_handler;

portSTACK_TYPE *console_task_stack = NULL;
TaskHandle_t console_task_task_handler;

volatile uint32_t cmdEnable = 0;

/******* UART handle definition ***************/
static lpuart_rtos_handle_t uart_rtos_handle;
static struct _lpuart_handle tuart_handle;
static uint8_t background_buffer[32];

lpuart_rtos_config_t lpuart_config = {
	.base		 = DEMO_LPUART,
    .baudrate    = 115200,
    .parity      = kLPUART_ParityDisabled,
    .stopbits    = kLPUART_OneStopBit,
    .buffer      = background_buffer,
    .buffer_size = sizeof(background_buffer),
};

static custom_console_instance_t t_console;

static uint32_t perfCounter = 0; 			/*!< counter used for freeRTOS tasks runtime analysis */

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
static void uart_init();

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief S1 button switch interrupt service ISR
 */
void BOARD_USER_BUTTON_IRQ_HANDLER(void)
{
    /* clear the interrupt status */
    GPIO_PortClearInterruptFlags(BOARD_USER_BUTTON_GPIO, 1U << BOARD_USER_BUTTON_GPIO_PIN);

    setInputSignal(true);

    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief PIT1 Timer interrupt service ISR
 */
void PIT1_IRQHANDLER(void)
{
	PIT_ClearStatusFlags(PIT1_PERIPHERAL, PIT1_CHANNEL_0, kPIT_TimerFlag);
	perfCounter++;
	//__DSB();
}

/*!
 * @brief Configures the PIT timer, it will be called by Freertos
 */
void AppConfigureTimerForRuntimeStats(void) {
	pit_config_t config;

	PIT_GetDefaultConfig(&config);
	config.enableRunInDebug = false;
	PIT_Init(PIT1_PERIPHERAL, &config);
	PIT_SetTimerPeriod(PIT1_PERIPHERAL, PIT1_CHANNEL_0, PIT1_CHANNEL_0_TICKS);
	PIT_EnableInterrupts(PIT1_PERIPHERAL, PIT1_CHANNEL_0, kPIT_TimerInterruptEnable);
	EnableIRQ(PIT1_IRQN);
	PIT_StartTimer(PIT1_PERIPHERAL, PIT1_CHANNEL_0);
}

/*!
 * @brief Returns 32bit counter value. Used for freertos runtime analysis
 */
uint32_t AppGetRuntimeCounterValueFromISR(void) {
	return perfCounter;
}

static inline int os_setup_tick_function(void (*func)(void))
{
    unsigned int i;

    for (i = 0; i < MAX_CUSTOM_HOOKS; i++)
        if (g_os_tick_hooks[i] && g_os_tick_hooks[i] == func)
            return 0;

    for (i = 0; i < MAX_CUSTOM_HOOKS; i++)
    {
        if (g_os_tick_hooks[i] == NULL)
        {
            g_os_tick_hooks[i] = func;
            break;
        }
    }

    if (i == MAX_CUSTOM_HOOKS)
        return -1;

    return 0;
}

/*!
 * @brief Main function
 */
int main(void)
{
    BaseType_t stat;

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_BootClockRUN();

    /*
     * Reset the displaymix, otherwise during debugging, the
     * debugger may not reset the display, then the behavior
     * is not right.
     */
    SRC_AssertSliceSoftwareReset(SRC, kSRC_DisplaySlice);

    BOARD_InitPins();
    BOARD_InitMipiPanelPins();
    BOARD_InitDebugConsole();

    if (detect_display())
    {
    	PRINTF("Display detected. Starting lvgl task\r\n");
    	BOARD_MIPIPanelTouch_I2C_Init();
    	#if defined(GUI_EN) && (GUI_EN==1)
    		/* 1. Freertos task: lvgl "Gui Guider"
    		 * displays GUI pages on 7 inch touch display. It uses lvgl library version 7.11.0  */
    	   stat = xTaskCreate(lvgl_task, "lvgl", configMINIMAL_STACK_SIZE + 800, lvgl_task_stack, tskIDLE_PRIORITY + 3, &lvgl_task_task_handler);
    	   assert(pdPASS == stat);
    	#endif
    }
    else
    {
    	PRINTF("Display not detected.\r\n");
    	BOARD_MIPIPanelTouch_I2C_Init();
    }

    /* initialize lpi2c2, lpi2c3 */
    BOARD_RTOS_I2C_Init(2);
    BOARD_RTOS_I2C_Init(3);
    /* configure uart for Maaxboard RT for console task*/
    uart_init();
	/* Init input switch GPIO. */
    EnableIRQ(BOARD_USER_BUTTON_IRQ);

	PRINTF("Debug Session");
	SDK_DelayAtLeastUs(1000000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);


	/******** Freertos task declarations ********/
	os_setup_tick_function(vApplicationTickHook_lvgl);


#if defined(CONSOLE_EN) && (CONSOLE_EN==1)
	/* 9. Freertos task: Console_task
	 * @brief: console application using lpuart1 peripheral */
    t_console.uart_handle = &uart_rtos_handle;
    stat = xTaskCreate(console_task, "Console_task", configMINIMAL_STACK_SIZE + 200, &t_console, 3, NULL);
    assert(pdPASS == stat);
#endif

#if defined(AUDIO_EN) && (AUDIO_EN==1)
	/* Audio task */
	/* 10. Freertos task: av_task
	 * @brief: read 4 microphones, output selected mic to audio codec */
    stat = xTaskCreate(audio_task_init, "av_task", configMINIMAL_STACK_SIZE + 200, NULL, 3, NULL);
    assert(pdPASS == stat);
#endif
    /* Init scheduler */
    vTaskStartScheduler();

    for (;;)
    {
    } /* should never get here */
}

static void uart_init()
{
	NVIC_SetPriority(DEMO_LPUART_IRQn, 5);
	lpuart_config.srcclk = DEMO_LPUART_CLK_FREQ;
	LPUART_RTOS_Init(&uart_rtos_handle, &tuart_handle, &lpuart_config);
}

/*!
 * @brief Malloc failed hook.
 */
void vApplicationMallocFailedHook(void)
{
    for (;;)
        ;
}

/*!
 * @brief Stack overflow hook.
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)pcTaskName;
    (void)xTask;

    for (;;)
        ;
}

/** The FreeRTOS Tick hook function. */
void vApplicationTickHook(void)
{
    int i;

    for (i = 0; i < MAX_CUSTOM_HOOKS; i++)
    {
        if (g_os_tick_hooks[i] != NULL)
            g_os_tick_hooks[i]();
    }
}

