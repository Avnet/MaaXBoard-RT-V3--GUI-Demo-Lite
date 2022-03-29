/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl/lvgl.h"
#include "custom.h"

#if (LV_USE_GUIDER_SIMULATOR == 0)
#include "lvgl_demo.h"
#include "demo_common.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
volatile bool LEDRedState;
volatile bool LEDGreenState;
volatile bool LEDBlueState;

volatile bool MIC1Checked;
volatile bool MIC2Checked;
volatile bool MIC3Checked;
volatile bool MIC4Checked;

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
}

#if (LV_USE_GUIDER_SIMULATOR == 1)
void NavigateToLEDScreen()
{
}

void NavigateToAudioScreen()
{
}

void NavigateToHomeScreen()
{
}

void ToggleLEDState(eLED led, bool state)
{
}

void ToggleMicState(int mic, bool state)
{
}

#else
void NavigateToLEDScreen()
{
    openLEDScreen();
}

void NavigateToAudioScreen()
{
    openAVScreen();
}

void NavigateToHomeScreen()
{
    openMenuScreen();
}

void ToggleLEDState(eLED led, bool state)
{
    switch (led)
    {
    case eLEDRed:
        set_red_led(state);
        break;

    case eLEDGreen:
        set_green_led(state);
        break;

    case eLEDBlue:
        set_blue_led(state);
        break;

    default:
        break;
    }
}

void ToggleMicState(int mic, bool state)
{
    enableMic(mic, state);
}
#endif

