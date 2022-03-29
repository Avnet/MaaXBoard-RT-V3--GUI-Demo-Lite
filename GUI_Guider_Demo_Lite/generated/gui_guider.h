/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *main_screen;
	lv_obj_t *main_screen_led_screen_btn;
	lv_obj_t *main_screen_led_screen_btn_label;
	lv_obj_t *main_screen_audio_screen_btn;
	lv_obj_t *main_screen_audio_screen_btn_label;
	lv_obj_t *main_screen_img_1;
	lv_obj_t *main_screen_label_4;
	lv_obj_t *led_screen;
	lv_obj_t *led_screen_green_led_btn;
	lv_obj_t *led_screen_green_led_btn_label;
	lv_obj_t *led_screen_red_led_btn;
	lv_obj_t *led_screen_red_led_btn_label;
	lv_obj_t *led_screen_blue_led_btn;
	lv_obj_t *led_screen_blue_led_btn_label;
	lv_obj_t *led_screen_home_btn_1;
	lv_obj_t *led_screen_home_btn_1_label;
	lv_obj_t *led_screen_red_led;
	lv_obj_t *led_screen_green_led;
	lv_obj_t *led_screen_blue_led;
	lv_obj_t *led_screen_img_1;
	lv_obj_t *led_screen_label_2;
	lv_obj_t *audio_screen;
	lv_obj_t *audio_screen_home_btn_1;
	lv_obj_t *audio_screen_home_btn_1_label;
	lv_obj_t *audio_screen_mic_chart;
	lv_obj_t *audio_screen_img_1;
	lv_obj_t *audio_screen_mic_cb_1;
	lv_obj_t *audio_screen_mic_cb_2;
	lv_obj_t *audio_screen_mic_cb_3;
	lv_obj_t *audio_screen_mic_cb_4;
	lv_obj_t *audio_screen_label_1;
	lv_obj_t *audio_screen_label_2;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_main_screen(lv_ui *ui);
void setup_scr_led_screen(lv_ui *ui);
void setup_scr_audio_screen(lv_ui *ui);
LV_IMG_DECLARE(_home_icon_alpha_100x100);
LV_IMG_DECLARE(_AvnetIcon310x310_alpha_100x100);

#ifdef __cplusplus
}
#endif
#endif
