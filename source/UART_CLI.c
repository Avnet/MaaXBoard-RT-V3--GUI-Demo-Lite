/*
 * UART_CLI.c
 *
 *  Created on: May 14, 2021
 *      Author: gulziibayar
 */

/* @Brief
 * MaaxBoard RT CLI use LPUART1 on J17 Debug UART 3 pin header.
 * Adding new command:
 * 1. create the function with these 3 parameters. pcWriteBuffer is the output buffer sending string to console,
 * 	  after command execution. Look for other functions.
 * 		static BaseType_t newFunction( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
 * 		{}
 * 2. create the new struct like below
 * 		static const CLI_Command_Definition_t taskNewFuncCommandStruct =
 *		{
 *			"newfunc",
 *			"--------- UTILITY --------------------\r\n"
 *			" newfunc      : newfunc description \r\n",
 *			newFunction,
 *			0
 *		};
 * 3. FreeRTOS_CLIRegisterCommand( &taskNewFuncCommandStruct )
 *
 * For more: https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_CLI/FreeRTOS_Plus_Command_Line_Interface.html
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

#include "fsl_debug_console.h"
#include "UART_CLI.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"
#include "timers.h"
#include "board.h"
#include "fsl_lpuart_freertos.h"
#include "fsl_lpuart.h"
#include "FreeRTOS_CLI.h"
#include <stdio.h>
#include "globals.h"
#include "fsl_lpuart.h"
#include "demo_common.h"
#include "audio_demo.h"
/*******************************************************************************
 * Globals
 ******************************************************************************/

static lpuart_rtos_handle_t *handle;

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Task priorities. */
#define uart_task_PRIORITY (configMAX_PRIORITIES - 1)

#define MAX_INPUT_LENGTH    50
//#define MAX_OUTPUT_LENGTH   configCOMMAND_INT_MAX_OUTPUT_SIZE
#define MAX_OUTPUT_LENGTH   128
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* Constant TEXT for cli */

const char *TEXT_WELCOME            = "**** MaaxBoard RT CLI ****\r\n>";
const char *TEXT_ABORT_CMD			= "\r\n***Command Aborted****\r\n>";
const char *TEXT_BUFFER_OVERRUN     = "\r\nRing buffer overrun!\r\n";
const char *TEXT_HW_OVERRUN 		= "\r\nHardware buffer overrun!\r\n";
const char *TEXT_VT100_CLEARSCREEN  = "\033[2J\033[H";
const char *TEXT_LED_ERROR			= "\r\nParam error: eg: led 101\r\n";
const char *TEXT_AUDIO_ERROR		= "\r\nParam error: eg: am 01 (L->empty, R->mic1, Note: L!=R; 0-no sound)\r\n";
const char *TEXT_CMD_ERROR			= "\r\nCommand Error\r\n";
const char *TEXT_FREETOS_STATS		= "\r\nTask                    Abs Time        %Time\r\n"
										   "____________________________________________\r\n";

/*******************************************************************************
 * Code
 ******************************************************************************/

extern volatile uint32_t cmdEnable;
// pointer used points to allocated temporary memory on the heap.
static void *ptr_temp = NULL;
static char *ptr_aux = NULL;
static volatile EventBits_t bits;

/*!
 * @brief Application entry point.
 */

/* Utility function prototypes */
static uint16_t copyTillNewLine(char * dest, char *src);

/* Console functions starts here */

/*****************************************************************************\
 * Function:    clearCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function clears the screen. It is run by the CLI interpreter
\*****************************************************************************/
static BaseType_t clearCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    static int processed = 0;

    const char *clearScreen = TEXT_VT100_CLEARSCREEN;
    // Only allowed to write up top xWriteBufferLen bytes ...
    strncpy(pcWriteBuffer,&clearScreen[processed],xWriteBufferLen-1);
    pcWriteBuffer[xWriteBufferLen-1]=0;

    processed = processed + xWriteBufferLen-1;
    if(processed < (int)strlen(clearScreen))
        return pdTRUE;

    processed = 0;
    return pdFALSE;
}

/*****************************************************************************\
 * Function:    audioCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function controls audio output. E.g. am 12 -> left -> mic1, right -> mic2 will be heard on the audio output.
 *     Note: Only up to mic can be chosen.	E.g. am 01 -> left -> nothing, right -> mic2
\*****************************************************************************/
static BaseType_t audioCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    /* Expecting one parameter */
    int8_t *pcParameter1;
    BaseType_t xParameter1StringLength;
    int length = 0;

    pcParameter1 = (int8_t *)FreeRTOS_CLIGetParameter
                        (
                          /* The command string itself. */
                          pcCommandString,
                          /* Return the first parameter. */
                          1,
                          /* Store the parameter string length. */
                          &xParameter1StringLength
                        );
    /* Terminate parameter. */
    pcParameter1[ xParameter1StringLength ] = 0x00;

    uint8_t validInput = 1;
    /* input parameter validation */
    if (xParameter1StringLength == 2)
    {
    	uint8_t count = 0;
    	uint8_t sum = 0;
    	for (uint8_t i=0; i<2; i++)
    	{
    		if(pcParameter1[i] >= 0x30 && pcParameter1[i] <= 0x34)
    		{
    			count++;
    		}
    	}
    	if (count==2)
    	{
    		if (pcParameter1[0] == pcParameter1[1] && pcParameter1[0] != 0x30)
    		{
    		    strncpy(pcWriteBuffer,TEXT_AUDIO_ERROR,xWriteBufferLen-1);
    		    pcWriteBuffer[xWriteBufferLen-1]=0;
    		    return pdFALSE;
    		}
    		disableAllMicChannels();
    		// enable mic here
    		for (uint8_t i=0; i<2; i++)
    		{
    			if (pcParameter1[i] != 0x30)
				{
    				enableAudioMicChannels(i, pcParameter1[i]-0x30);
				}
    		}

    		length += sprintf(pcWriteBuffer+length, "\r\nSuccess: Audio L->");
    		uint8_t temp[10];
    		if (pcParameter1[0]==0x30)
    		{
    			length += sprintf(pcWriteBuffer+length, "empty");
    		}
    		else
    		{
    			length += sprintf(pcWriteBuffer+length, "mic%c", pcParameter1[0]);
    		}

    		length += sprintf(pcWriteBuffer+length, ", R->");
    		if (pcParameter1[1]==0x30)
			{
				length += sprintf(pcWriteBuffer+length, "empty");
			}
			else
			{
				length += sprintf(pcWriteBuffer+length, "mic%c", pcParameter1[1]);
			}
    		length += sprintf(pcWriteBuffer+length, " are selected.");

    		//length += sprintf(pcWriteBuffer+length, "\r\n*** Audio L->mic#%c, R->mic#%c are selected\r\n", pcParameter1[0]==0x30?'_':pcParameter1[0], pcParameter1[1]==0x30?'_':pcParameter1[1]);
    		pcWriteBuffer[xWriteBufferLen-1]=0;
    		return pdFALSE;
    	}
    }

    // Only allowed to write up top xWriteBufferLen bytes ...
    strncpy(pcWriteBuffer,TEXT_AUDIO_ERROR,xWriteBufferLen-1);
    pcWriteBuffer[xWriteBufferLen-1]=0;

    return pdFALSE;
}

/*****************************************************************************\
 * Function:    controlLedCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function controls individual leds. E.g. led 101 -> red on, green off, blue on
\*****************************************************************************/
static BaseType_t controlLedCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    /* Expecting one parameter */
    int8_t *pcParameter1;
    BaseType_t xParameter1StringLength;

    pcParameter1 = (int8_t *)FreeRTOS_CLIGetParameter
                        (
                          /* The command string itself. */
                          pcCommandString,
                          /* Return the first parameter. */
                          1,
                          /* Store the parameter string length. */
                          &xParameter1StringLength
                        );
    /* Terminate parameter. */
    pcParameter1[ xParameter1StringLength ] = 0x00;

    uint8_t validInput = 1;
    /* input parameter validation */
    if (xParameter1StringLength == 3) {
    	uint8_t count = 0;
    	for (uint8_t i=0; i<3; i++) {
    		if(pcParameter1[i] == 0x31 || pcParameter1[i] == 0x30) {
    			count++;
    		}
    	}
    	if (count==3) {
    		set_red_led(pcParameter1[0]==0x30?0:1);
    		set_green_led(pcParameter1[1]==0x30?0:1);
    		set_blue_led(pcParameter1[2]==0x30?0:1);
    		pcWriteBuffer[0] = 0; // to make sure
    		return pdFALSE;
    	}
    }

    // Only allowed to write up top xWriteBufferLen bytes ...
    strncpy(pcWriteBuffer,TEXT_LED_ERROR,xWriteBufferLen-1);
    pcWriteBuffer[xWriteBufferLen-1]=0;

    return pdFALSE;
}

/*****************************************************************************\
 * Function:    exitCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function disables printing mouse, keyboard data on the console.
\*****************************************************************************/
static BaseType_t exitCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    static int processed = 0;

    char *text = "\r\nquit\r\n";
    // Only allowed to write up top xWriteBufferLen bytes ...
    strncpy(pcWriteBuffer,&text[processed],xWriteBufferLen-1);
    pcWriteBuffer[xWriteBufferLen-1]=0;

    cmdEnable = 0;
    return pdFALSE;
}

#if configGENERATE_RUN_TIME_STATS
/*****************************************************************************\
 * Function:    taskStatsCommand
 * Input:       char *pcWriteBufer,size_t xWriteBufferLen,const char *pcCommandString
 * Returns:     BaseType_t
 * Description:
 *     This function returns list of tasks.
\*****************************************************************************/
static BaseType_t taskStatsCommand( char *pcWriteBuffer,size_t xWriteBufferLen, const char *pcCommandString )
{
    (void)pcCommandString;
    static int processed = 0;
    int char_cnt = 0;
    UBaseType_t cnt;
    BaseType_t xReturn;
    char *text;
    // initial call
    if (processed == 0)
    {
    	cnt = uxTaskGetNumberOfTasks();
    	if (cnt>0 && cnt<20)
    	{
    		ptr_temp = pvPortMalloc(40*cnt);
    		vTaskGetRunTimeStats((char *)ptr_temp);
    		ptr_aux = (char *)ptr_temp;
    		text = (char *)TEXT_FREETOS_STATS;
    		strncpy(pcWriteBuffer,&text[0],xWriteBufferLen-1);
    		processed++;
    		xReturn = pdTRUE;
    	}
    	else
    	{
    		// more than 20 or 0 tasks
    		text = "\r\ncan't list more than 20\r\n";
    	    // Only allowed to write up top xWriteBufferLen bytes ...
    	    strncpy(pcWriteBuffer,&text[0],xWriteBufferLen-1);
    		xReturn = pdFALSE;
    	}
    }
    else if (processed == 1)
    {
    	char_cnt = copyTillNewLine(pcWriteBuffer, ptr_aux);
		ptr_aux = ptr_aux + char_cnt;
		if (char_cnt)
		{
			xReturn = pdTRUE;
		}
		else
		{
			xReturn = pdFALSE;
	    	// free the memory
	    	vPortFree(ptr_temp);
	    	pcWriteBuffer[0] = 0;
	    	processed = 0;
		}
    }
    return xReturn;
}
#endif


/* Utility functions */

/*****************************************************************************\
 * Function:    copyTillNewLine
 * Input:       char * dest, char *src
 * Returns:     number bytes copied
 * Description:
 *     This function copies the src data to destination until first \n or 0.
\*****************************************************************************/
static uint16_t copyTillNewLine(char * dest, char *src)
{
	uint16_t cnt = 0;
	while(*src!=0 && *src!='\n')
	{
		*(dest++) = *(src++);
		cnt++;
	}
    // terminate the string
    if (*src=='\n')
    {
        *(dest++) = *src;
        cnt++;
    }
    *dest = 0;
	return cnt;
}

/* Console command structs */
/***************** PERIPHERALS COMMANDS ************************/
static const CLI_Command_Definition_t controlLedCommandStruct =
{
    "led",
    "--------- PERIPHERALS ----------------\r\n"
    " led ***    : RGB LEDs on/off \r\n",
	controlLedCommand,
    1
};

/***************** A&V COMMANDS *******************************/
static const CLI_Command_Definition_t audioCommandStruct =
{
    "am",
    "--------- AUDIO & VIDEO --------------\r\n"
    " am ##      : Audio L/R output (mic# 1-4)\r\n",
	audioCommand,
    1
};

/***************** UTILITY COMMANDS ****************************/
#if configGENERATE_RUN_TIME_STATS
static const CLI_Command_Definition_t taskStatsCommandStruct =
{
    "stats",
    "--------- UTILITY --------------------\r\n"
    " stats      : RTOS Statistics \r\n",
	taskStatsCommand,
    0
};
#endif
static const CLI_Command_Definition_t clearCommandStruct =
{
    "clr",
    " clr        : Clear the terminal \r\n",
    clearCommand,
    0
};

static const CLI_Command_Definition_t exitCommandStruct =
{
    "q",
    " q/ctrl+c   : Abort the command \r\n",
	exitCommand,
    0
};

static const CLI_Command_Definition_t helpCommandStruct =
{
    "h",
    " ? / h      : Menu Help \r\n"
	"========= "
	MAAXBOARD_VERSION_STRING
	"\r\n",
	prvHelpCommand,
    0
};

/*******************************************************************************
 * Freetos Task: console_task
 * @brief receive console application using lpuart1 peripheral.
 ******************************************************************************/
void console_task(void *pvParameters)
{
	custom_console_instance_t *t_console_instance = (custom_console_instance_t *)pvParameters;
	handle = t_console_instance->uart_handle;
	char pcOutputString[ MAX_OUTPUT_LENGTH ], pcInputString[ MAX_INPUT_LENGTH ];

	memset( pcInputString, 0x00, MAX_INPUT_LENGTH );
	uint8_t cRxedChar, cInputIndex = 0;
	BaseType_t xMoreDataToFollow;
    int error;
    size_t n = 0;

    /* Send introduction message. */
    if (kStatus_Success != LPUART_RTOS_Send(handle, (uint8_t *)TEXT_WELCOME, strlen(TEXT_WELCOME)))
    {
        vTaskSuspend(NULL);
    }

    /* Registering cli commands */
    /***************** PERIPHERALS COMMANDS ************************/
    FreeRTOS_CLIRegisterCommand( &controlLedCommandStruct );

    /***************** AUDIO & VIDEO *******************************/
    FreeRTOS_CLIRegisterCommand( &audioCommandStruct);

    /***************** UTILITY COMMANDS ****************************/
#if configGENERATE_RUN_TIME_STATS
    FreeRTOS_CLIRegisterCommand( &taskStatsCommandStruct );
#endif
    FreeRTOS_CLIRegisterCommand( &clearCommandStruct );
    FreeRTOS_CLIRegisterCommand( &exitCommandStruct );
    FreeRTOS_CLIRegisterCommand( &helpCommandStruct );

    /* Receive user input and send it back to terminal. */

    while(1)
    {
    	LPUART_RTOS_Receive(handle, &cRxedChar, sizeof( cRxedChar ), &n);
		if( cRxedChar == '\r' )
		{
			/* A newline character was received, so the input command string is
			complete and can be processed.  Transmit a line separator, just to
			make the output easier to read. */
			LPUART_RTOS_Send(handle,&cRxedChar,1);
			/* The command interpreter is called repeatedly until it returns
			pdFALSE.  See the "Implementing a command" documentation for an
			exaplanation of why this is. */
			do
			{
				/* Send the command string to the command interpreter.  Any
				output generated by the command interpreter will be placed in the
				pcOutputString buffer. */
				xMoreDataToFollow = FreeRTOS_CLIProcessCommand
				(
					pcInputString,   /* The command string.*/
					pcOutputString,  /* The output buffer. */
					MAX_OUTPUT_LENGTH/* The size of the output buffer. */
				);
				/* Write the output generated by the command interpreter to the
				console. */
				if (pcOutputString[0] !=0)
				{
					LPUART_RTOS_Send(handle, pcOutputString, strlen( pcOutputString ) );
				}
			} while( xMoreDataToFollow != pdFALSE );
			//print prompt after each command
			sprintf(pcOutputString, "\r\n> ", 4);
			LPUART_RTOS_Send(handle, pcOutputString, strlen( pcOutputString ) );
			/* All the strings generated by the input command have been sent.
			Processing of the command is complete.  Clear the input string ready
			to receive the next command. */
			cInputIndex = 0;
			memset( pcInputString, 0x00, MAX_INPUT_LENGTH );
		}
		else if (cRxedChar == 0x03)	// end of text, ctrl+c
		{
			cmdEnable = 0;
			LPUART_RTOS_Send(handle, (uint8_t *)TEXT_ABORT_CMD, strlen(TEXT_ABORT_CMD));
		}
		else
		{
		/* The if() clause performs the processing after a newline character
		is received.  This else clause performs the processing if any other
		character is received. */
			if( cRxedChar == 8 ) // backspace character
			{
				LPUART_RTOS_Send(handle,&cRxedChar,1);
				/* Backspace was pressed.  Erase the last character in the input
				buffer - if there are any. */
				if( cInputIndex > 0 )
				{
					cInputIndex--;
					pcInputString[ cInputIndex ] = '\0';
				}
			}
			else
			{
				/* A character was entered.  It was not a new line, backspace
				or carriage return, so it is accepted as part of the input and
				placed into the input buffer.  When a \n is entered the complete
				string will be passed to the command interpreter. */
				if( cInputIndex < MAX_INPUT_LENGTH )
				{
					LPUART_RTOS_Send(handle,&cRxedChar,1);
					pcInputString[ cInputIndex ] = cRxedChar;
					cInputIndex++;
				}
			}
		}
		vTaskDelay(100/portTICK_PERIOD_MS);
    }
    vTaskSuspend(NULL);
}
