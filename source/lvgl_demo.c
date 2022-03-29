#include <stdio.h>

#include "gui_guider.h"
#include "littlevgl_support.h"
#include "lvgl.h"
#include "events_init.h"

#include "demo_common.h"
#include "audio_demo.h"
#include "lvgl_demo.h"
#include "globals.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef enum _activePage
{
    PAGE_NONE       = -1,
    PAGE_MENU       = 0,
    PAGE_LED        = 1,
    PAGE_AV         = 2,
} activePage;

#define MIC_GRAPH_POINTS 50
#define MIC_GRAPH_MIDDLE_POINT 50

#define CUSTOM_GRAPH_POINTS 50
#define CUSTOM_GRAPH_BASE_POINT 0
#define CUSTOM_GRAPH_REFRESH_INTERVAL 10

/*******************************************************************************
 * Variables
 ******************************************************************************/

static volatile bool s_lvgl_initialized = false;
static volatile activePage s_active_page = PAGE_NONE;

lv_ui guider_ui;

static bool s_lgvl_ready = false;

static void (*s_page_refresh)(void) = NULL;

static char s_text_area_buffer[100];

static lv_chart_series_t *s_mic_1_series = NULL;
static lv_chart_series_t *s_mic_2_series = NULL;
static lv_chart_series_t *s_mic_3_series = NULL;
static lv_chart_series_t *s_mic_4_series = NULL;

static volatile lv_coord_t s_mic_1_buffer[MIC_GRAPH_POINTS];
static volatile lv_coord_t s_mic_2_buffer[MIC_GRAPH_POINTS];
static volatile lv_coord_t s_mic_3_buffer[MIC_GRAPH_POINTS];
static volatile lv_coord_t s_mic_4_buffer[MIC_GRAPH_POINTS];

static int s_mic_1_buffer_count = 0;
static int s_mic_2_buffer_count = 0;
static int s_mic_3_buffer_count = 0;
static int s_mic_4_buffer_count = 0;

static uint8_t audio_channels[2];
static volatile bool *mic_states[4] = {&MIC1Checked, &MIC2Checked, &MIC3Checked, &MIC4Checked};

static int s_enabled_mic_count = 0;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void refreshAVPage(void);
void initMicGraph(void);

/*******************************************************************************
 * Functions
 ******************************************************************************/
void setLedRedImgState(bool state)
{
    if (s_active_page != PAGE_LED)
    {
        return;
    }

    if(state)
    	lv_led_on(guider_ui.led_screen_red_led);
    else
    	lv_led_off(guider_ui.led_screen_red_led);
}

void setLedGreenImgState(bool state)
{
    if (s_active_page != PAGE_LED)
    {
        return;
    }

    if(state)
    	lv_led_on(guider_ui.led_screen_green_led);
    else
    	lv_led_off(guider_ui.led_screen_green_led);
}

void setLedBlueImgState(bool state)
{
    if (s_active_page != PAGE_LED)
    {
        return;
    }

    if(state)
    	lv_led_on(guider_ui.led_screen_blue_led);
    else
    	lv_led_off(guider_ui.led_screen_blue_led);
}

/*!
* @brief Init color LEDs
*/
void initDefaultPageInteractions()
{
    initLEDs();

    s_page_refresh = NULL;
}

/*!
* @brief Opens the menu screen
*/
void openMenuScreen()
{
    s_active_page = PAGE_MENU;

    initDefaultPageInteractions();
}

/*!
* @brief Opens the LED screen
*/
void openLEDScreen()
{
    s_active_page = PAGE_LED;

    initDefaultPageInteractions();
}

/*!
* @brief Opens the A/V screen
*/
void openAVScreen()
{
    s_active_page = PAGE_AV;

    initDefaultPageInteractions();

    initMicGraph();

	s_page_refresh = &refreshAVPage;
}

/*!
* @brief Initializes microphone graph 
*/
void initMicGraph(void)
{
    lv_chart_set_point_count(guider_ui.audio_screen_mic_chart, MIC_GRAPH_POINTS);

    s_mic_1_buffer_count = 0;
    s_mic_2_buffer_count = 0;
    s_mic_3_buffer_count = 0;
    s_mic_4_buffer_count = 0;

	s_mic_1_series = lv_chart_add_series(guider_ui.audio_screen_mic_chart, LV_COLOR_RED);
	s_mic_2_series = lv_chart_add_series(guider_ui.audio_screen_mic_chart, LV_COLOR_YELLOW);
	s_mic_3_series = lv_chart_add_series(guider_ui.audio_screen_mic_chart, LV_COLOR_BLUE);
	s_mic_4_series = lv_chart_add_series(guider_ui.audio_screen_mic_chart, LV_COLOR_CYAN);

	MIC1Checked = false;
	MIC2Checked = false;
	MIC3Checked = false;
	MIC4Checked = false;

	audio_channels[0] = 0;
	audio_channels[1] = 0;

    lv_chart_refresh(guider_ui.audio_screen_mic_chart);
}

/*!
 * @brief enable or disable inactive mic checkboxes.
 */
void enableInactiveMicCheckboxes(bool state)
{
    if (s_active_page != PAGE_AV)
    {
        return;
    }
    
    if (!MIC1Checked)
    {
        if (state)
        {
            lv_obj_clear_state(guider_ui.audio_screen_mic_cb_1, LV_STATE_DISABLED);
        }
        else
        {
            lv_checkbox_set_state(guider_ui.audio_screen_mic_cb_1, LV_BTN_STATE_DISABLED);
        }
    }
    
    if (!MIC2Checked)
    {
        if (state)
        {
            lv_obj_clear_state(guider_ui.audio_screen_mic_cb_2, LV_STATE_DISABLED);
        }
        else
        {
            lv_checkbox_set_state(guider_ui.audio_screen_mic_cb_2, LV_BTN_STATE_DISABLED);
        }
    }
    
    if (!MIC3Checked)
    {
        if (state)
        {
            lv_obj_clear_state(guider_ui.audio_screen_mic_cb_3, LV_STATE_DISABLED);
        }
        else
        {
            lv_checkbox_set_state(guider_ui.audio_screen_mic_cb_3, LV_BTN_STATE_DISABLED);
        }
    }
    
    if (!MIC4Checked)
    {
        if (state)
        {
            lv_obj_clear_state(guider_ui.audio_screen_mic_cb_4, LV_STATE_DISABLED);
        }
        else
        {
            lv_checkbox_set_state(guider_ui.audio_screen_mic_cb_4, LV_BTN_STATE_DISABLED);
        }
    }
}

/*!
 * @brief enable microphone.
 */
void enableMic(int mic, bool state)
{
    if (s_active_page != PAGE_AV)
    {
        return;
    }

    switch (mic)
    {
        case 1:
            MIC1Checked = state;

            if (state)
            {
                lv_chart_init_points(guider_ui.audio_screen_mic_chart, s_mic_1_series, MIC_GRAPH_MIDDLE_POINT);
                s_mic_1_buffer_count = 0;

                s_enabled_mic_count++;
            }
            else
            {
                lv_chart_clear_series(guider_ui.audio_screen_mic_chart, s_mic_1_series);
                s_mic_1_buffer_count = 0;

                s_enabled_mic_count--;
            }
            
            enableMicChannel(0, state);

            break;
        case 2:
            MIC2Checked = state;

            if (state)
            {
                lv_chart_init_points(guider_ui.audio_screen_mic_chart, s_mic_2_series, MIC_GRAPH_MIDDLE_POINT);
                s_mic_2_buffer_count = 0;

                s_enabled_mic_count++;
            }
            else
            {
                lv_chart_clear_series(guider_ui.audio_screen_mic_chart, s_mic_2_series);
                s_mic_2_buffer_count = 0;

                s_enabled_mic_count--;
            }
            
            enableMicChannel(1, state);

            break;
        case 3:
            MIC3Checked = state;

            if (state)
            {
                lv_chart_init_points(guider_ui.audio_screen_mic_chart, s_mic_3_series, MIC_GRAPH_MIDDLE_POINT);
                s_mic_3_buffer_count = 0;

                s_enabled_mic_count++;
            }
            else
            {
                lv_chart_clear_series(guider_ui.audio_screen_mic_chart, s_mic_3_series);
                s_mic_3_buffer_count = 0;

                s_enabled_mic_count--;
            }
            
            enableMicChannel(2, state);

            break;
        case 4:
            MIC4Checked = state;

            if (state)
            {
                lv_chart_init_points(guider_ui.audio_screen_mic_chart, s_mic_4_series, MIC_GRAPH_MIDDLE_POINT);
                s_mic_4_buffer_count = 0;

                s_enabled_mic_count++;
            }
            else
            {
                lv_chart_clear_series(guider_ui.audio_screen_mic_chart, s_mic_4_series);
                s_mic_4_buffer_count = 0;

                s_enabled_mic_count--;
            }
            
            enableMicChannel(3, state);

            break;
        default:
            PRINTF("Error: Invalid mic index: %d.\r\n", mic);
    }
	uint8_t *temp = getEnabledChannels();
	audio_channels[0] = *(temp++);
	audio_channels[1] = *(temp);
    enableInactiveMicCheckboxes(s_enabled_mic_count < 2);
}

/*!
 * @brief adds data to display on microphone graph.
 */
void addMicData(int mic, int16_t value)
{
    if (s_active_page != PAGE_AV)
    {
        return;
    }

    if (value > 100) 
        value = 100;
    else if (value < 0) 
        value = 0;

    taskENTER_CRITICAL();

    switch (mic)
    {
        case 1:
            if (MIC1Checked && (s_mic_1_buffer_count < MIC_GRAPH_POINTS))
            {
                s_mic_1_buffer[s_mic_1_buffer_count] = value;
                s_mic_1_buffer_count++;
            }
            break;
        case 2:
            if (MIC2Checked && (s_mic_2_buffer_count < MIC_GRAPH_POINTS))
            {
                s_mic_2_buffer[s_mic_2_buffer_count] = value;
                s_mic_2_buffer_count++;
            }
            break;
        case 3:
            if (MIC3Checked && (s_mic_3_buffer_count < MIC_GRAPH_POINTS))
            {
                s_mic_3_buffer[s_mic_3_buffer_count] = value;
                s_mic_3_buffer_count++;
            }
            break;
        case 4:
            if (MIC4Checked && (s_mic_4_buffer_count < MIC_GRAPH_POINTS))
            {
                s_mic_4_buffer[s_mic_4_buffer_count] = value;
                s_mic_4_buffer_count++;
            }
            break;
        default:
            PRINTF("Error: Invalid mic index: %d.\r\n", mic);
    }

    taskEXIT_CRITICAL();
}

/*!
 * @brief refreshes the microphone graph.
 */
void refreshMicGraph(void)
{
    int i;

    if (s_active_page != PAGE_AV)
    {
        return;
    }

    taskENTER_CRITICAL();

    // update mic 1 graph
    for (i = 0; i < s_mic_1_buffer_count; i++)
    {
        lv_chart_set_next(guider_ui.audio_screen_mic_chart, s_mic_1_series, s_mic_1_buffer[i]);
    }
    s_mic_1_buffer_count = 0;

    // update mic 2 graph
    for (i = 0; i < s_mic_2_buffer_count; i++)
    {
        lv_chart_set_next(guider_ui.audio_screen_mic_chart, s_mic_2_series, s_mic_2_buffer[i]);
    }
    s_mic_2_buffer_count = 0;

    // update mic 3 graph
    for (i = 0; i < s_mic_3_buffer_count; i++)
    {
        lv_chart_set_next(guider_ui.audio_screen_mic_chart, s_mic_3_series, s_mic_3_buffer[i]);
    }
    s_mic_3_buffer_count = 0;

    // update mic 4 graph
    for (i = 0; i < s_mic_4_buffer_count; i++)
    {
        lv_chart_set_next(guider_ui.audio_screen_mic_chart, s_mic_4_series, s_mic_4_buffer[i]);
    }
    s_mic_4_buffer_count = 0;

    taskEXIT_CRITICAL();
    
    lv_chart_refresh(guider_ui.audio_screen_mic_chart);
}

static void sync_enabled_mic()
{
	// check if different mics are enabled from console
	uint8_t *temp = getEnabledChannels();
	uint8_t left_channel = *(temp++);
	uint8_t right_channel = *(temp);

	if (audio_channels[0] != left_channel || audio_channels[1] != right_channel)
	{
		int temp;
		MIC1Checked = false;
		MIC2Checked = false;
		MIC3Checked = false;
		MIC4Checked = false;

		if (left_channel != 0)
		{
			*mic_states[left_channel-1] = true;
		}
		if (right_channel != 0)
		{
			*mic_states[right_channel-1] = true;
		}

		for (int i=0; i<4; i++)
		{
			if (*mic_states[i]==false)
			{
				enableMic(i+1, *mic_states[i]);
			}
		}
		for (int i=0; i<4; i++)
		{
			switch(i)
			{
				case 0:
					lv_checkbox_set_state(guider_ui.audio_screen_mic_cb_1, *mic_states[i]==true?LV_BTN_STATE_CHECKED_PRESSED:LV_BTN_STATE_RELEASED);
					break;
				case 1:
					lv_checkbox_set_state(guider_ui.audio_screen_mic_cb_2, *mic_states[i]==true?LV_BTN_STATE_CHECKED_PRESSED:LV_BTN_STATE_RELEASED);
					break;
				case 2:
					lv_checkbox_set_state(guider_ui.audio_screen_mic_cb_3, *mic_states[i]==true?LV_BTN_STATE_CHECKED_PRESSED:LV_BTN_STATE_RELEASED);
					break;
				case 3:
					lv_checkbox_set_state(guider_ui.audio_screen_mic_cb_4, *mic_states[i]==true?LV_BTN_STATE_CHECKED_PRESSED:LV_BTN_STATE_RELEASED);
					break;
				default:
					break;
			}
		}

		s_enabled_mic_count = 0;
		for (int i=0; i<4; i++)
		{
			if (*mic_states[i])
			{
				enableMic(i+1, *mic_states[i]);
			}
		}
		audio_channels[0] = left_channel;
		audio_channels[1] = right_channel;
	}
}
/*!
 * @brief refreshes the A/V page.
 */
void refreshAVPage(void)
{
	sync_enabled_mic();
	refreshMicGraph();
}


/*!
 * @brief FreeRTOS tick hook.
 */
void vApplicationTickHook_lvgl(void)
{
    if (s_lvgl_initialized)
    {
        lv_tick_inc(1);
    }
}

/*!
 * @brief returns 'true' if lvgl task has been properly initialized.
 */
bool isLvglReady(void)
{
    return s_lgvl_ready;
}


/*******************************************************************************
 * Freertos Task: lvgl
 * @brief - There are total 6 pages, task handles all gui object events, navigation
 ******************************************************************************/
void lvgl_task(void *param)
{
    lv_port_pre_init();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    s_lvgl_initialized = true;

    setup_ui(&guider_ui);
    events_init(&guider_ui);

    s_lgvl_ready = true;

	set_red_led(false);
	set_green_led(false);
	set_blue_led(false);
    s_page_refresh = NULL;

    openMenuScreen();

    for (;;)
    {
        if (getInputSignal())
        {
            switch (s_active_page)
            {
                case PAGE_LED:
                    openAVScreen();
                    break;
                
                case PAGE_AV:
                    openMenuScreen();
                    break;

                case PAGE_MENU:
                    openLEDScreen();
                    break;
            }

            setInputSignal(false);
        }

        if (s_page_refresh != NULL)
        {
            (*s_page_refresh)();
        }
        lv_task_handler();
        vTaskDelay(5);
    }
}
