
#include "gui_guider.h"
#include "littlevgl_support.h"
#include "lvgl.h"
#include "events_init.h"

#include "demo_common.h"
#include "lvgl_demo.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

static volatile bool s_input_signal = false;         // S1 button switch page signal

/*******************************************************************************
 * Functions
 ******************************************************************************/
/*!
* @brief Sets the input signal
*/
void setInputSignal(bool state)
{
    s_input_signal = state;
}

/*!
* @brief Gets the input signal state
*/
bool getInputSignal()
{
    return s_input_signal;
}

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void set_red_led(bool state)
{
	LEDRedState = state;
    setLedRedImgState(state);

    GPIO_PinWrite(BOARD_USER_LED_RED_GPIO, BOARD_USER_LED_RED_GPIO_PIN, state ? 1U : 0U);
}

void set_green_led(bool state)
{
	LEDGreenState = state;
    setLedGreenImgState(state);

    GPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, state ? 1U : 0U);
}

void set_blue_led(bool state)
{
	LEDBlueState = state;
    setLedBlueImgState(state);

    GPIO_PinWrite(BOARD_USER_LED_BLUE_GPIO, BOARD_USER_LED_BLUE_GPIO_PIN, state ? 1U : 0U);
}

bool get_red_led()
{
	return LEDRedState;
}

bool get_green_led()
{
	return LEDGreenState;
}

bool get_blue_led()
{
	return LEDBlueState;
}

/*!
* @brief Init color LEDs
*/
void initLEDs()
{
	set_red_led(false);
	set_green_led(false);
	set_blue_led(false);
}
