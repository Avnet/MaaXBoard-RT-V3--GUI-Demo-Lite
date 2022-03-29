/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl/lvgl.h"
#include "custom.h"
#include "custom.h"

#include "custom.h"

#include "custom.h"
#include "custom.h"
#include "custom.h"




void events_init(lv_ui *ui)
{
}

static void main_screen_led_screen_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_CLICKED:
	{
		if (!lv_debug_check_obj_valid(guider_ui.led_screen))
			setup_scr_led_screen(&guider_ui);
		lv_scr_load_anim(guider_ui.led_screen, LV_SCR_LOAD_ANIM_OVER_LEFT, 0, 0, true);
		NavigateToLEDScreen();
	}
		break;
	default:
		break;
	}
}

static void main_screen_audio_screen_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_CLICKED:
	{
		if (!lv_debug_check_obj_valid(guider_ui.audio_screen))
			setup_scr_audio_screen(&guider_ui);
		lv_scr_load_anim(guider_ui.audio_screen, LV_SCR_LOAD_ANIM_OVER_LEFT, 0, 0, true);
		NavigateToAudioScreen();
	}
		break;
	default:
		break;
	}
}

void events_init_main_screen(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->main_screen_led_screen_btn, main_screen_led_screen_btnevent_handler);
	lv_obj_set_event_cb(ui->main_screen_audio_screen_btn, main_screen_audio_screen_btnevent_handler);
}

static void led_screen_green_led_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_CLICKED:
	{
		LEDGreenState = !LEDGreenState; 
		ToggleLEDState(eLEDGreen, LEDGreenState);
	}
		break;
	default:
		break;
	}
}

static void led_screen_red_led_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_CLICKED:
	{
		LEDRedState = !LEDRedState; 
		ToggleLEDState(eLEDRed, LEDRedState);
	}
		break;
	default:
		break;
	}
}

static void led_screen_blue_led_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_CLICKED:
	{
		LEDBlueState = !LEDBlueState; 
		ToggleLEDState(eLEDBlue, LEDBlueState);
	}
		break;
	default:
		break;
	}
}

static void led_screen_home_btn_1event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		if (!lv_debug_check_obj_valid(guider_ui.main_screen))
			setup_scr_main_screen(&guider_ui);
		lv_scr_load_anim(guider_ui.main_screen, LV_SCR_LOAD_ANIM_OVER_RIGHT, 0, 0, true);
		NavigateToHomeScreen();
	}
		break;
	default:
		break;
	}
}

void events_init_led_screen(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->led_screen_green_led_btn, led_screen_green_led_btnevent_handler);
	lv_obj_set_event_cb(ui->led_screen_red_led_btn, led_screen_red_led_btnevent_handler);
	lv_obj_set_event_cb(ui->led_screen_blue_led_btn, led_screen_blue_led_btnevent_handler);
	lv_obj_set_event_cb(ui->led_screen_home_btn_1, led_screen_home_btn_1event_handler);
}

static void audio_screen_home_btn_1event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_RELEASED:
	{
		if (!lv_debug_check_obj_valid(guider_ui.main_screen))
			setup_scr_main_screen(&guider_ui);
		lv_scr_load_anim(guider_ui.main_screen, LV_SCR_LOAD_ANIM_OVER_RIGHT, 0, 0, true);
		NavigateToHomeScreen();
	}
		break;
	default:
		break;
	}
}

static void audio_screen_mic_cb_1event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		MIC1Checked = !MIC1Checked;
		ToggleMicState(1, MIC1Checked);
	}
		break;
	default:
		break;
	}
}

static void audio_screen_mic_cb_2event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		MIC2Checked = !MIC2Checked;
		ToggleMicState(2, MIC2Checked);
	}
		break;
	default:
		break;
	}
}

static void audio_screen_mic_cb_3event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		MIC3Checked = !MIC3Checked;
		ToggleMicState(3, MIC3Checked);
	}
		break;
	default:
		break;
	}
}

static void audio_screen_mic_cb_4event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		MIC4Checked = !MIC4Checked;
		ToggleMicState(4, MIC4Checked);
	}
		break;
	default:
		break;
	}
}

void events_init_audio_screen(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->audio_screen_home_btn_1, audio_screen_home_btn_1event_handler);
	lv_obj_set_event_cb(ui->audio_screen_mic_cb_1, audio_screen_mic_cb_1event_handler);
	lv_obj_set_event_cb(ui->audio_screen_mic_cb_2, audio_screen_mic_cb_2event_handler);
	lv_obj_set_event_cb(ui->audio_screen_mic_cb_3, audio_screen_mic_cb_3event_handler);
	lv_obj_set_event_cb(ui->audio_screen_mic_cb_4, audio_screen_mic_cb_4event_handler);
}
