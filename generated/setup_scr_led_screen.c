/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_led_screen(lv_ui *ui){

	//Write codes led_screen
	ui->led_screen = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for led_screen
	static lv_style_t style_led_screen_main;
	lv_style_reset(&style_led_screen_main);

	//Write style state: LV_STATE_DEFAULT for style_led_screen_main
	lv_style_set_bg_color(&style_led_screen_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_led_screen_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->led_screen, LV_OBJ_PART_MAIN, &style_led_screen_main);

	//Write codes led_screen_green_led_btn
	ui->led_screen_green_led_btn = lv_btn_create(ui->led_screen, NULL);

	//Write style LV_BTN_PART_MAIN for led_screen_green_led_btn
	static lv_style_t style_led_screen_green_led_btn_main;
	lv_style_reset(&style_led_screen_green_led_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_led_screen_green_led_btn_main
	lv_style_set_radius(&style_led_screen_green_led_btn_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_led_screen_green_led_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_led_screen_green_led_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_led_screen_green_led_btn_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_led_screen_green_led_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_led_screen_green_led_btn_main, LV_STATE_DEFAULT, lv_color_make(0x41, 0xc2, 0x62));
	lv_style_set_border_width(&style_led_screen_green_led_btn_main, LV_STATE_DEFAULT, 4);
	lv_style_set_border_opa(&style_led_screen_green_led_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_led_screen_green_led_btn_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_led_screen_green_led_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->led_screen_green_led_btn, LV_BTN_PART_MAIN, &style_led_screen_green_led_btn_main);
	lv_obj_set_pos(ui->led_screen_green_led_btn, 258, 560);
	lv_obj_set_size(ui->led_screen_green_led_btn, 200, 54);
	ui->led_screen_green_led_btn_label = lv_label_create(ui->led_screen_green_led_btn, NULL);
	lv_label_set_text(ui->led_screen_green_led_btn_label, "GREEN LED");
	lv_obj_set_style_local_text_color(ui->led_screen_green_led_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_obj_set_style_local_text_font(ui->led_screen_green_led_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_Montserrat_medium_24);

	//Write codes led_screen_red_led_btn
	ui->led_screen_red_led_btn = lv_btn_create(ui->led_screen, NULL);

	//Write style LV_BTN_PART_MAIN for led_screen_red_led_btn
	static lv_style_t style_led_screen_red_led_btn_main;
	lv_style_reset(&style_led_screen_red_led_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_led_screen_red_led_btn_main
	lv_style_set_radius(&style_led_screen_red_led_btn_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_led_screen_red_led_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_led_screen_red_led_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_led_screen_red_led_btn_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_led_screen_red_led_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_led_screen_red_led_btn_main, LV_STATE_DEFAULT, lv_color_make(0x41, 0xc2, 0x62));
	lv_style_set_border_width(&style_led_screen_red_led_btn_main, LV_STATE_DEFAULT, 4);
	lv_style_set_border_opa(&style_led_screen_red_led_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_led_screen_red_led_btn_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_led_screen_red_led_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->led_screen_red_led_btn, LV_BTN_PART_MAIN, &style_led_screen_red_led_btn_main);
	lv_obj_set_pos(ui->led_screen_red_led_btn, 30, 560);
	lv_obj_set_size(ui->led_screen_red_led_btn, 200, 54);
	ui->led_screen_red_led_btn_label = lv_label_create(ui->led_screen_red_led_btn, NULL);
	lv_label_set_text(ui->led_screen_red_led_btn_label, "RED LED");
	lv_obj_set_style_local_text_color(ui->led_screen_red_led_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_obj_set_style_local_text_font(ui->led_screen_red_led_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_Montserrat_medium_24);

	//Write codes led_screen_blue_led_btn
	ui->led_screen_blue_led_btn = lv_btn_create(ui->led_screen, NULL);

	//Write style LV_BTN_PART_MAIN for led_screen_blue_led_btn
	static lv_style_t style_led_screen_blue_led_btn_main;
	lv_style_reset(&style_led_screen_blue_led_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_led_screen_blue_led_btn_main
	lv_style_set_radius(&style_led_screen_blue_led_btn_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_led_screen_blue_led_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_led_screen_blue_led_btn_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_led_screen_blue_led_btn_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_led_screen_blue_led_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_led_screen_blue_led_btn_main, LV_STATE_DEFAULT, lv_color_make(0x41, 0xc2, 0x62));
	lv_style_set_border_width(&style_led_screen_blue_led_btn_main, LV_STATE_DEFAULT, 4);
	lv_style_set_border_opa(&style_led_screen_blue_led_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_led_screen_blue_led_btn_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_led_screen_blue_led_btn_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->led_screen_blue_led_btn, LV_BTN_PART_MAIN, &style_led_screen_blue_led_btn_main);
	lv_obj_set_pos(ui->led_screen_blue_led_btn, 490, 560);
	lv_obj_set_size(ui->led_screen_blue_led_btn, 200, 54);
	ui->led_screen_blue_led_btn_label = lv_label_create(ui->led_screen_blue_led_btn, NULL);
	lv_label_set_text(ui->led_screen_blue_led_btn_label, "BLUE LED");
	lv_obj_set_style_local_text_color(ui->led_screen_blue_led_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_obj_set_style_local_text_font(ui->led_screen_blue_led_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_Montserrat_medium_24);

	//Write codes led_screen_home_btn_1
	ui->led_screen_home_btn_1 = lv_imgbtn_create(ui->led_screen, NULL);

	//Write style LV_IMGBTN_PART_MAIN for led_screen_home_btn_1
	static lv_style_t style_led_screen_home_btn_1_main;
	lv_style_reset(&style_led_screen_home_btn_1_main);

	//Write style state: LV_STATE_DEFAULT for style_led_screen_home_btn_1_main
	lv_style_set_text_color(&style_led_screen_home_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_image_recolor(&style_led_screen_home_btn_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_led_screen_home_btn_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_led_screen_home_btn_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->led_screen_home_btn_1, LV_IMGBTN_PART_MAIN, &style_led_screen_home_btn_1_main);
	lv_obj_set_pos(ui->led_screen_home_btn_1, 310, 1150);
	lv_obj_set_size(ui->led_screen_home_btn_1, 100, 100);
	lv_imgbtn_set_src(ui->led_screen_home_btn_1,LV_BTN_STATE_RELEASED,&_home_icon_alpha_100x100);
	lv_imgbtn_set_checkable(ui->led_screen_home_btn_1, true);

	//Write codes led_screen_red_led
	ui->led_screen_red_led = lv_led_create(ui->led_screen, NULL);

	//Write style LV_LED_PART_MAIN for led_screen_red_led
	static lv_style_t style_led_screen_red_led_main;
	lv_style_reset(&style_led_screen_red_led_main);

	//Write style state: LV_STATE_DEFAULT for style_led_screen_red_led_main
	lv_style_set_radius(&style_led_screen_red_led_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_led_screen_red_led_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0x0d, 0x1d));
	lv_style_set_bg_grad_color(&style_led_screen_red_led_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0x0d, 0x1d));
	lv_style_set_bg_grad_dir(&style_led_screen_red_led_main, LV_STATE_DEFAULT, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_led_screen_red_led_main, LV_STATE_DEFAULT, 255);
	lv_style_set_shadow_color(&style_led_screen_red_led_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_shadow_width(&style_led_screen_red_led_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_led_screen_red_led_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_led_screen_red_led_main, LV_STATE_DEFAULT, 3);
	lv_style_set_border_opa(&style_led_screen_red_led_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->led_screen_red_led, LV_LED_PART_MAIN, &style_led_screen_red_led_main);
	lv_obj_set_pos(ui->led_screen_red_led, 95, 507);
	lv_obj_set_size(ui->led_screen_red_led, 70, 40);
	lv_led_set_bright(ui->led_screen_red_led, 255);

	//Write codes led_screen_green_led
	ui->led_screen_green_led = lv_led_create(ui->led_screen, NULL);

	//Write style LV_LED_PART_MAIN for led_screen_green_led
	static lv_style_t style_led_screen_green_led_main;
	lv_style_reset(&style_led_screen_green_led_main);

	//Write style state: LV_STATE_DEFAULT for style_led_screen_green_led_main
	lv_style_set_radius(&style_led_screen_green_led_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_led_screen_green_led_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_color(&style_led_screen_green_led_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_dir(&style_led_screen_green_led_main, LV_STATE_DEFAULT, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_led_screen_green_led_main, LV_STATE_DEFAULT, 255);
	lv_style_set_shadow_color(&style_led_screen_green_led_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_shadow_width(&style_led_screen_green_led_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_led_screen_green_led_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_led_screen_green_led_main, LV_STATE_DEFAULT, 3);
	lv_style_set_border_opa(&style_led_screen_green_led_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->led_screen_green_led, LV_LED_PART_MAIN, &style_led_screen_green_led_main);
	lv_obj_set_pos(ui->led_screen_green_led, 324, 507);
	lv_obj_set_size(ui->led_screen_green_led, 70, 40);
	lv_led_set_bright(ui->led_screen_green_led, 255);

	//Write codes led_screen_blue_led
	ui->led_screen_blue_led = lv_led_create(ui->led_screen, NULL);

	//Write style LV_LED_PART_MAIN for led_screen_blue_led
	static lv_style_t style_led_screen_blue_led_main;
	lv_style_reset(&style_led_screen_blue_led_main);

	//Write style state: LV_STATE_DEFAULT for style_led_screen_blue_led_main
	lv_style_set_radius(&style_led_screen_blue_led_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_led_screen_blue_led_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xcc, 0xff));
	lv_style_set_bg_grad_color(&style_led_screen_blue_led_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xcc, 0xff));
	lv_style_set_bg_grad_dir(&style_led_screen_blue_led_main, LV_STATE_DEFAULT, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_led_screen_blue_led_main, LV_STATE_DEFAULT, 255);
	lv_style_set_shadow_color(&style_led_screen_blue_led_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_shadow_width(&style_led_screen_blue_led_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_led_screen_blue_led_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_led_screen_blue_led_main, LV_STATE_DEFAULT, 3);
	lv_style_set_border_opa(&style_led_screen_blue_led_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->led_screen_blue_led, LV_LED_PART_MAIN, &style_led_screen_blue_led_main);
	lv_obj_set_pos(ui->led_screen_blue_led, 553, 507);
	lv_obj_set_size(ui->led_screen_blue_led, 70, 40);
	lv_led_set_bright(ui->led_screen_blue_led, 255);

	//Write codes led_screen_img_1
	ui->led_screen_img_1 = lv_img_create(ui->led_screen, NULL);

	//Write style LV_IMG_PART_MAIN for led_screen_img_1
	static lv_style_t style_led_screen_img_1_main;
	lv_style_reset(&style_led_screen_img_1_main);

	//Write style state: LV_STATE_DEFAULT for style_led_screen_img_1_main
	lv_style_set_image_recolor(&style_led_screen_img_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_led_screen_img_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_led_screen_img_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->led_screen_img_1, LV_IMG_PART_MAIN, &style_led_screen_img_1_main);
	lv_obj_set_pos(ui->led_screen_img_1, 24, 24);
	lv_obj_set_size(ui->led_screen_img_1, 100, 100);
	lv_obj_set_click(ui->led_screen_img_1, true);
	lv_img_set_src(ui->led_screen_img_1,&_AvnetIcon310x310_alpha_100x100);
	lv_img_set_pivot(ui->led_screen_img_1, 0,0);
	lv_img_set_angle(ui->led_screen_img_1, 0);

	//Write codes led_screen_label_2
	ui->led_screen_label_2 = lv_label_create(ui->led_screen, NULL);
	lv_label_set_text(ui->led_screen_label_2, "LED CONTROL");
	lv_label_set_long_mode(ui->led_screen_label_2, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->led_screen_label_2, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for led_screen_label_2
	static lv_style_t style_led_screen_label_2_main;
	lv_style_reset(&style_led_screen_label_2_main);

	//Write style state: LV_STATE_DEFAULT for style_led_screen_label_2_main
	lv_style_set_radius(&style_led_screen_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_led_screen_label_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_led_screen_label_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_led_screen_label_2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_led_screen_label_2_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_led_screen_label_2_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_led_screen_label_2_main, LV_STATE_DEFAULT, &lv_font_Montserrat_medium_30);
	lv_style_set_text_letter_space(&style_led_screen_label_2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_led_screen_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_led_screen_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_led_screen_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_led_screen_label_2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->led_screen_label_2, LV_LABEL_PART_MAIN, &style_led_screen_label_2_main);
	lv_obj_set_pos(ui->led_screen_label_2, 160, 45);
	lv_obj_set_size(ui->led_screen_label_2, 386, 0);

	//Init events for screen
	events_init_led_screen(ui);
}