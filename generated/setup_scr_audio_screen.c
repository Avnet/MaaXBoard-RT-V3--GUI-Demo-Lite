/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_audio_screen(lv_ui *ui){

	//Write codes audio_screen
	ui->audio_screen = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for audio_screen
	static lv_style_t style_audio_screen_main;
	lv_style_reset(&style_audio_screen_main);

	//Write style state: LV_STATE_DEFAULT for style_audio_screen_main
	lv_style_set_bg_color(&style_audio_screen_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_audio_screen_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->audio_screen, LV_OBJ_PART_MAIN, &style_audio_screen_main);

	//Write codes audio_screen_home_btn_1
	ui->audio_screen_home_btn_1 = lv_imgbtn_create(ui->audio_screen, NULL);

	//Write style LV_IMGBTN_PART_MAIN for audio_screen_home_btn_1
	static lv_style_t style_audio_screen_home_btn_1_main;
	lv_style_reset(&style_audio_screen_home_btn_1_main);

	//Write style state: LV_STATE_DEFAULT for style_audio_screen_home_btn_1_main
	lv_style_set_text_color(&style_audio_screen_home_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_audio_screen_home_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_audio_screen_home_btn_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_audio_screen_home_btn_1_main, LV_STATE_DEFAULT, 255);

	//Write style state: LV_STATE_PRESSED for style_audio_screen_home_btn_1_main
	lv_style_set_text_color(&style_audio_screen_home_btn_1_main, LV_STATE_PRESSED, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_image_recolor(&style_audio_screen_home_btn_1_main, LV_STATE_PRESSED, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor_opa(&style_audio_screen_home_btn_1_main, LV_STATE_PRESSED, 0);

	//Write style state: LV_STATE_CHECKED for style_audio_screen_home_btn_1_main
	lv_style_set_text_color(&style_audio_screen_home_btn_1_main, LV_STATE_CHECKED, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_image_recolor(&style_audio_screen_home_btn_1_main, LV_STATE_CHECKED, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor_opa(&style_audio_screen_home_btn_1_main, LV_STATE_CHECKED, 0);
	lv_obj_add_style(ui->audio_screen_home_btn_1, LV_IMGBTN_PART_MAIN, &style_audio_screen_home_btn_1_main);
	lv_obj_set_pos(ui->audio_screen_home_btn_1, 310, 1150);
	lv_obj_set_size(ui->audio_screen_home_btn_1, 100, 100);
	lv_imgbtn_set_src(ui->audio_screen_home_btn_1,LV_BTN_STATE_RELEASED,&_home_icon_alpha_100x100);
	lv_imgbtn_set_checkable(ui->audio_screen_home_btn_1, true);

	//Write codes audio_screen_mic_chart
	ui->audio_screen_mic_chart = lv_chart_create(ui->audio_screen, NULL);

	//Write style LV_CHART_PART_BG for audio_screen_mic_chart
	static lv_style_t style_audio_screen_mic_chart_bg;
	lv_style_reset(&style_audio_screen_mic_chart_bg);

	//Write style state: LV_STATE_DEFAULT for style_audio_screen_mic_chart_bg
	lv_style_set_bg_color(&style_audio_screen_mic_chart_bg, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_color(&style_audio_screen_mic_chart_bg, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_dir(&style_audio_screen_mic_chart_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_audio_screen_mic_chart_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_audio_screen_mic_chart_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_audio_screen_mic_chart_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_audio_screen_mic_chart_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_bottom(&style_audio_screen_mic_chart_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->audio_screen_mic_chart, LV_CHART_PART_BG, &style_audio_screen_mic_chart_bg);

	//Write style LV_CHART_PART_SERIES_BG for audio_screen_mic_chart
	static lv_style_t style_audio_screen_mic_chart_series_bg;
	lv_style_reset(&style_audio_screen_mic_chart_series_bg);

	//Write style state: LV_STATE_DEFAULT for style_audio_screen_mic_chart_series_bg
	lv_style_set_line_color(&style_audio_screen_mic_chart_series_bg, LV_STATE_DEFAULT, lv_color_make(0x7d, 0x84, 0x90));
	lv_style_set_line_width(&style_audio_screen_mic_chart_series_bg, LV_STATE_DEFAULT, 2);
	lv_style_set_line_opa(&style_audio_screen_mic_chart_series_bg, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->audio_screen_mic_chart, LV_CHART_PART_SERIES_BG, &style_audio_screen_mic_chart_series_bg);
	lv_obj_set_pos(ui->audio_screen_mic_chart, 55, 290);
	lv_obj_set_size(ui->audio_screen_mic_chart, 610, 420);
	lv_chart_set_type(ui->audio_screen_mic_chart,LV_CHART_TYPE_LINE);
	lv_chart_set_range(ui->audio_screen_mic_chart,0,100);
	lv_chart_set_div_line_count(ui->audio_screen_mic_chart, 3, 5);
	lv_chart_set_point_count(ui->audio_screen_mic_chart, 5);
	lv_chart_series_t * audio_screen_mic_chart_0 = lv_chart_add_series(ui->audio_screen_mic_chart, lv_color_make(0x00, 0x00, 0x00));
	lv_chart_set_next(ui->audio_screen_mic_chart, audio_screen_mic_chart_0,0);

	//Write codes audio_screen_img_1
	ui->audio_screen_img_1 = lv_img_create(ui->audio_screen, NULL);

	//Write style LV_IMG_PART_MAIN for audio_screen_img_1
	static lv_style_t style_audio_screen_img_1_main;
	lv_style_reset(&style_audio_screen_img_1_main);

	//Write style state: LV_STATE_DEFAULT for style_audio_screen_img_1_main
	lv_style_set_image_recolor(&style_audio_screen_img_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_audio_screen_img_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_audio_screen_img_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->audio_screen_img_1, LV_IMG_PART_MAIN, &style_audio_screen_img_1_main);
	lv_obj_set_pos(ui->audio_screen_img_1, 24, 24);
	lv_obj_set_size(ui->audio_screen_img_1, 100, 100);
	lv_obj_set_click(ui->audio_screen_img_1, true);
	lv_img_set_src(ui->audio_screen_img_1,&_AvnetIcon310x310_alpha_100x100);
	lv_img_set_pivot(ui->audio_screen_img_1, 0,0);
	lv_img_set_angle(ui->audio_screen_img_1, 0);

	//Write codes audio_screen_mic_cb_1
	ui->audio_screen_mic_cb_1 = lv_checkbox_create(ui->audio_screen, NULL);
	lv_checkbox_set_text(ui->audio_screen_mic_cb_1, "MIC 1");

	//Write style LV_CHECKBOX_PART_BG for audio_screen_mic_cb_1
	static lv_style_t style_audio_screen_mic_cb_1_bg;
	lv_style_reset(&style_audio_screen_mic_cb_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_audio_screen_mic_cb_1_bg
	lv_style_set_radius(&style_audio_screen_mic_cb_1_bg, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_audio_screen_mic_cb_1_bg, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_color(&style_audio_screen_mic_cb_1_bg, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_dir(&style_audio_screen_mic_cb_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_audio_screen_mic_cb_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_audio_screen_mic_cb_1_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_audio_screen_mic_cb_1_bg, LV_STATE_DEFAULT, &lv_font_Montserrat_medium_30);
	lv_style_set_text_letter_space(&style_audio_screen_mic_cb_1_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->audio_screen_mic_cb_1, LV_CHECKBOX_PART_BG, &style_audio_screen_mic_cb_1_bg);

	//Write style LV_CHECKBOX_PART_BULLET for audio_screen_mic_cb_1
	static lv_style_t style_audio_screen_mic_cb_1_bullet;
	lv_style_reset(&style_audio_screen_mic_cb_1_bullet);

	//Write style state: LV_STATE_DEFAULT for style_audio_screen_mic_cb_1_bullet
	lv_style_set_radius(&style_audio_screen_mic_cb_1_bullet, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_audio_screen_mic_cb_1_bullet, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_color(&style_audio_screen_mic_cb_1_bullet, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_dir(&style_audio_screen_mic_cb_1_bullet, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_audio_screen_mic_cb_1_bullet, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_audio_screen_mic_cb_1_bullet, LV_STATE_DEFAULT, lv_color_make(0x02, 0xa2, 0xb1));
	lv_style_set_border_width(&style_audio_screen_mic_cb_1_bullet, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->audio_screen_mic_cb_1, LV_CHECKBOX_PART_BULLET, &style_audio_screen_mic_cb_1_bullet);
	lv_obj_set_pos(ui->audio_screen_mic_cb_1, 60, 730);

	//Write codes audio_screen_mic_cb_2
	ui->audio_screen_mic_cb_2 = lv_checkbox_create(ui->audio_screen, NULL);
	lv_checkbox_set_text(ui->audio_screen_mic_cb_2, "MIC 2");

	//Write style LV_CHECKBOX_PART_BG for audio_screen_mic_cb_2
	static lv_style_t style_audio_screen_mic_cb_2_bg;
	lv_style_reset(&style_audio_screen_mic_cb_2_bg);

	//Write style state: LV_STATE_DEFAULT for style_audio_screen_mic_cb_2_bg
	lv_style_set_radius(&style_audio_screen_mic_cb_2_bg, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_audio_screen_mic_cb_2_bg, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_color(&style_audio_screen_mic_cb_2_bg, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_dir(&style_audio_screen_mic_cb_2_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_audio_screen_mic_cb_2_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_audio_screen_mic_cb_2_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_audio_screen_mic_cb_2_bg, LV_STATE_DEFAULT, &lv_font_Montserrat_medium_30);
	lv_style_set_text_letter_space(&style_audio_screen_mic_cb_2_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->audio_screen_mic_cb_2, LV_CHECKBOX_PART_BG, &style_audio_screen_mic_cb_2_bg);

	//Write style LV_CHECKBOX_PART_BULLET for audio_screen_mic_cb_2
	static lv_style_t style_audio_screen_mic_cb_2_bullet;
	lv_style_reset(&style_audio_screen_mic_cb_2_bullet);

	//Write style state: LV_STATE_DEFAULT for style_audio_screen_mic_cb_2_bullet
	lv_style_set_radius(&style_audio_screen_mic_cb_2_bullet, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_audio_screen_mic_cb_2_bullet, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_color(&style_audio_screen_mic_cb_2_bullet, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_dir(&style_audio_screen_mic_cb_2_bullet, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_audio_screen_mic_cb_2_bullet, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_audio_screen_mic_cb_2_bullet, LV_STATE_DEFAULT, lv_color_make(0x02, 0xa2, 0xb1));
	lv_style_set_border_width(&style_audio_screen_mic_cb_2_bullet, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->audio_screen_mic_cb_2, LV_CHECKBOX_PART_BULLET, &style_audio_screen_mic_cb_2_bullet);
	lv_obj_set_pos(ui->audio_screen_mic_cb_2, 200, 730);

	//Write codes audio_screen_mic_cb_3
	ui->audio_screen_mic_cb_3 = lv_checkbox_create(ui->audio_screen, NULL);
	lv_checkbox_set_text(ui->audio_screen_mic_cb_3, "MIC 3");

	//Write style LV_CHECKBOX_PART_BG for audio_screen_mic_cb_3
	static lv_style_t style_audio_screen_mic_cb_3_bg;
	lv_style_reset(&style_audio_screen_mic_cb_3_bg);

	//Write style state: LV_STATE_DEFAULT for style_audio_screen_mic_cb_3_bg
	lv_style_set_radius(&style_audio_screen_mic_cb_3_bg, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_audio_screen_mic_cb_3_bg, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_color(&style_audio_screen_mic_cb_3_bg, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_dir(&style_audio_screen_mic_cb_3_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_audio_screen_mic_cb_3_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_audio_screen_mic_cb_3_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_audio_screen_mic_cb_3_bg, LV_STATE_DEFAULT, &lv_font_Montserrat_medium_30);
	lv_style_set_text_letter_space(&style_audio_screen_mic_cb_3_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->audio_screen_mic_cb_3, LV_CHECKBOX_PART_BG, &style_audio_screen_mic_cb_3_bg);

	//Write style LV_CHECKBOX_PART_BULLET for audio_screen_mic_cb_3
	static lv_style_t style_audio_screen_mic_cb_3_bullet;
	lv_style_reset(&style_audio_screen_mic_cb_3_bullet);

	//Write style state: LV_STATE_DEFAULT for style_audio_screen_mic_cb_3_bullet
	lv_style_set_radius(&style_audio_screen_mic_cb_3_bullet, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_audio_screen_mic_cb_3_bullet, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_color(&style_audio_screen_mic_cb_3_bullet, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_dir(&style_audio_screen_mic_cb_3_bullet, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_audio_screen_mic_cb_3_bullet, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_audio_screen_mic_cb_3_bullet, LV_STATE_DEFAULT, lv_color_make(0x02, 0xa2, 0xb1));
	lv_style_set_border_width(&style_audio_screen_mic_cb_3_bullet, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->audio_screen_mic_cb_3, LV_CHECKBOX_PART_BULLET, &style_audio_screen_mic_cb_3_bullet);
	lv_obj_set_pos(ui->audio_screen_mic_cb_3, 340, 730);

	//Write codes audio_screen_mic_cb_4
	ui->audio_screen_mic_cb_4 = lv_checkbox_create(ui->audio_screen, NULL);
	lv_checkbox_set_text(ui->audio_screen_mic_cb_4, "MIC 4");

	//Write style LV_CHECKBOX_PART_BG for audio_screen_mic_cb_4
	static lv_style_t style_audio_screen_mic_cb_4_bg;
	lv_style_reset(&style_audio_screen_mic_cb_4_bg);

	//Write style state: LV_STATE_DEFAULT for style_audio_screen_mic_cb_4_bg
	lv_style_set_radius(&style_audio_screen_mic_cb_4_bg, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_audio_screen_mic_cb_4_bg, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_color(&style_audio_screen_mic_cb_4_bg, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_dir(&style_audio_screen_mic_cb_4_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_audio_screen_mic_cb_4_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_audio_screen_mic_cb_4_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_audio_screen_mic_cb_4_bg, LV_STATE_DEFAULT, &lv_font_Montserrat_medium_30);
	lv_style_set_text_letter_space(&style_audio_screen_mic_cb_4_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->audio_screen_mic_cb_4, LV_CHECKBOX_PART_BG, &style_audio_screen_mic_cb_4_bg);

	//Write style LV_CHECKBOX_PART_BULLET for audio_screen_mic_cb_4
	static lv_style_t style_audio_screen_mic_cb_4_bullet;
	lv_style_reset(&style_audio_screen_mic_cb_4_bullet);

	//Write style state: LV_STATE_DEFAULT for style_audio_screen_mic_cb_4_bullet
	lv_style_set_radius(&style_audio_screen_mic_cb_4_bullet, LV_STATE_DEFAULT, 6);
	lv_style_set_bg_color(&style_audio_screen_mic_cb_4_bullet, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_color(&style_audio_screen_mic_cb_4_bullet, LV_STATE_DEFAULT, lv_color_make(0x5a, 0x61, 0x73));
	lv_style_set_bg_grad_dir(&style_audio_screen_mic_cb_4_bullet, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_audio_screen_mic_cb_4_bullet, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_audio_screen_mic_cb_4_bullet, LV_STATE_DEFAULT, lv_color_make(0x02, 0xa2, 0xb1));
	lv_style_set_border_width(&style_audio_screen_mic_cb_4_bullet, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->audio_screen_mic_cb_4, LV_CHECKBOX_PART_BULLET, &style_audio_screen_mic_cb_4_bullet);
	lv_obj_set_pos(ui->audio_screen_mic_cb_4, 480, 730);

	//Write codes audio_screen_label_1
	ui->audio_screen_label_1 = lv_label_create(ui->audio_screen, NULL);
	lv_label_set_text(ui->audio_screen_label_1, "AUDIO GRAPH");
	lv_label_set_long_mode(ui->audio_screen_label_1, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->audio_screen_label_1, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for audio_screen_label_1
	static lv_style_t style_audio_screen_label_1_main;
	lv_style_reset(&style_audio_screen_label_1_main);

	//Write style state: LV_STATE_DEFAULT for style_audio_screen_label_1_main
	lv_style_set_radius(&style_audio_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_audio_screen_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_audio_screen_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_audio_screen_label_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_audio_screen_label_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_audio_screen_label_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_audio_screen_label_1_main, LV_STATE_DEFAULT, &lv_font_Montserrat_medium_30);
	lv_style_set_text_letter_space(&style_audio_screen_label_1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_audio_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_audio_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_audio_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_audio_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->audio_screen_label_1, LV_LABEL_PART_MAIN, &style_audio_screen_label_1_main);
	lv_obj_set_pos(ui->audio_screen_label_1, 166, 45);
	lv_obj_set_size(ui->audio_screen_label_1, 386, 0);

	//Init events for screen
	events_init_audio_screen(ui);
}