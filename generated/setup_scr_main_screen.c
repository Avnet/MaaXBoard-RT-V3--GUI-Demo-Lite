/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_main_screen(lv_ui *ui){

	//Write codes main_screen
	ui->main_screen = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for main_screen
	static lv_style_t style_main_screen_main;
	lv_style_reset(&style_main_screen_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_main
	lv_style_set_bg_color(&style_main_screen_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_main_screen_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->main_screen, LV_OBJ_PART_MAIN, &style_main_screen_main);

	//Write codes main_screen_led_screen_btn
	ui->main_screen_led_screen_btn = lv_btn_create(ui->main_screen, NULL);

	//Write style LV_BTN_PART_MAIN for main_screen_led_screen_btn
	static lv_style_t style_main_screen_led_screen_btn_main;
	lv_style_reset(&style_main_screen_led_screen_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_led_screen_btn_main
	lv_style_set_radius(&style_main_screen_led_screen_btn_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_main_screen_led_screen_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_screen_led_screen_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_screen_led_screen_btn_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_led_screen_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_main_screen_led_screen_btn_main, LV_STATE_DEFAULT, lv_color_make(0x41, 0xc2, 0x62));
	lv_style_set_border_width(&style_main_screen_led_screen_btn_main, LV_STATE_DEFAULT, 4);
	lv_style_set_border_opa(&style_main_screen_led_screen_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_main_screen_led_screen_btn_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_main_screen_led_screen_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->main_screen_led_screen_btn, LV_BTN_PART_MAIN, &style_main_screen_led_screen_btn_main);
	lv_obj_set_pos(ui->main_screen_led_screen_btn, 100, 560);
	lv_obj_set_size(ui->main_screen_led_screen_btn, 210, 54);
	ui->main_screen_led_screen_btn_label = lv_label_create(ui->main_screen_led_screen_btn, NULL);
	lv_label_set_text(ui->main_screen_led_screen_btn_label, "LED CONTROL");
	lv_obj_set_style_local_text_color(ui->main_screen_led_screen_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_obj_set_style_local_text_font(ui->main_screen_led_screen_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_Montserrat_medium_24);

	//Write codes main_screen_audio_screen_btn
	ui->main_screen_audio_screen_btn = lv_btn_create(ui->main_screen, NULL);

	//Write style LV_BTN_PART_MAIN for main_screen_audio_screen_btn
	static lv_style_t style_main_screen_audio_screen_btn_main;
	lv_style_reset(&style_main_screen_audio_screen_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_audio_screen_btn_main
	lv_style_set_radius(&style_main_screen_audio_screen_btn_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_main_screen_audio_screen_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_screen_audio_screen_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_screen_audio_screen_btn_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_audio_screen_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_main_screen_audio_screen_btn_main, LV_STATE_DEFAULT, lv_color_make(0x41, 0xc2, 0x62));
	lv_style_set_border_width(&style_main_screen_audio_screen_btn_main, LV_STATE_DEFAULT, 4);
	lv_style_set_border_opa(&style_main_screen_audio_screen_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_main_screen_audio_screen_btn_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_main_screen_audio_screen_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->main_screen_audio_screen_btn, LV_BTN_PART_MAIN, &style_main_screen_audio_screen_btn_main);
	lv_obj_set_pos(ui->main_screen_audio_screen_btn, 400, 560);
	lv_obj_set_size(ui->main_screen_audio_screen_btn, 210, 54);
	ui->main_screen_audio_screen_btn_label = lv_label_create(ui->main_screen_audio_screen_btn, NULL);
	lv_label_set_text(ui->main_screen_audio_screen_btn_label, "AUDIO GRAPH");
	lv_obj_set_style_local_text_color(ui->main_screen_audio_screen_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_obj_set_style_local_text_font(ui->main_screen_audio_screen_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_Montserrat_medium_24);

	//Write codes main_screen_img_1
	ui->main_screen_img_1 = lv_img_create(ui->main_screen, NULL);

	//Write style LV_IMG_PART_MAIN for main_screen_img_1
	static lv_style_t style_main_screen_img_1_main;
	lv_style_reset(&style_main_screen_img_1_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_img_1_main
	lv_style_set_image_recolor(&style_main_screen_img_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_main_screen_img_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_main_screen_img_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->main_screen_img_1, LV_IMG_PART_MAIN, &style_main_screen_img_1_main);
	lv_obj_set_pos(ui->main_screen_img_1, 24, 24);
	lv_obj_set_size(ui->main_screen_img_1, 100, 100);
	lv_obj_set_click(ui->main_screen_img_1, true);
	lv_img_set_src(ui->main_screen_img_1,&_AvnetIcon310x310_alpha_100x100);
	lv_img_set_pivot(ui->main_screen_img_1, 0,0);
	lv_img_set_angle(ui->main_screen_img_1, 0);

	//Write codes main_screen_label_4
	ui->main_screen_label_4 = lv_label_create(ui->main_screen, NULL);
	lv_label_set_text(ui->main_screen_label_4, "GUI GUIDER DEMO");
	lv_label_set_long_mode(ui->main_screen_label_4, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->main_screen_label_4, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for main_screen_label_4
	static lv_style_t style_main_screen_label_4_main;
	lv_style_reset(&style_main_screen_label_4_main);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_label_4_main
	lv_style_set_radius(&style_main_screen_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_main_screen_label_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_screen_label_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_screen_label_4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_label_4_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_main_screen_label_4_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_main_screen_label_4_main, LV_STATE_DEFAULT, &lv_font_Montserrat_medium_40);
	lv_style_set_text_letter_space(&style_main_screen_label_4_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_main_screen_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_main_screen_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_main_screen_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_main_screen_label_4_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->main_screen_label_4, LV_LABEL_PART_MAIN, &style_main_screen_label_4_main);
	lv_obj_set_pos(ui->main_screen_label_4, 160, 45);
	lv_obj_set_size(ui->main_screen_label_4, 452, 0);

	//Init events for screen
	events_init_main_screen(ui);
}