/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



int camera_digital_clock_1_min_value = 29;
int camera_digital_clock_1_hour_value = 0;
int camera_digital_clock_1_sec_value = 43;
void setup_scr_camera(lv_ui *ui)
{
    //Write codes camera
    ui->camera = lv_obj_create(NULL);
    ui->g_kb_camera = lv_keyboard_create(ui->camera);
    lv_obj_add_event_cb(ui->g_kb_camera, kb_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui->g_kb_camera, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_font(ui->g_kb_camera, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_size(ui->camera, 800, 480);
    lv_obj_set_scrollbar_mode(ui->camera, LV_SCROLLBAR_MODE_OFF);

    //Write style for camera, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->camera, 159, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->camera, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->camera, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->camera, lv_color_hex(0x00344C), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->camera, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->camera, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes camera_cont_1
    ui->camera_cont_1 = lv_obj_create(ui->camera);
    lv_obj_set_pos(ui->camera_cont_1, 0, 0);
    lv_obj_set_size(ui->camera_cont_1, 800, 60);
    lv_obj_set_scrollbar_mode(ui->camera_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for camera_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->camera_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->camera_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->camera_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->camera_cont_1, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->camera_cont_1, 9, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->camera_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->camera_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->camera_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->camera_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->camera_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->camera_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->camera_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->camera_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes camera_datetext_1
    ui->date_text = lv_label_create(ui->camera);
    lv_label_set_text(ui->date_text, "2025/01/04");
    lv_obj_set_style_text_align(ui->date_text, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui->date_text, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->date_text, camera_datetext_1_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->date_text, 599, 8);
    lv_obj_set_size(ui->date_text, 194, 43);

    //Write style for camera_datetext_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->date_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->date_text, &lv_font_Alatsi_Regular_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->date_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->date_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->date_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->date_text, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->date_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes camera_digital_clock_1
    static bool camera_digital_clock_1_timer_enabled = false;
    ui->time_text = lv_dclock_create(ui->camera, "0:29:43");
    if (!camera_digital_clock_1_timer_enabled) {
        lv_timer_create(camera_digital_clock_1_timer, 1000, NULL);
        camera_digital_clock_1_timer_enabled = true;
    }
    lv_obj_set_pos(ui->time_text, 5, 8);
    lv_obj_set_size(ui->time_text, 180, 43);

    //Write style for camera_digital_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->time_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->time_text, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->time_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->time_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->time_text, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->time_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes camera_imgbtn_1
    ui->camera_imgbtn_1 = lv_imgbtn_create(ui->camera);
    lv_obj_add_flag(ui->camera_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->camera_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_back_alpha_50x50, NULL);
    lv_imgbtn_set_src(ui->camera_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, &_back_alpha_50x50, NULL);
    lv_imgbtn_set_src(ui->camera_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_back_alpha_50x50, NULL);
    lv_imgbtn_set_src(ui->camera_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_back_alpha_50x50, NULL);
    ui->camera_imgbtn_1_label = lv_label_create(ui->camera_imgbtn_1);
    lv_label_set_text(ui->camera_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->camera_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->camera_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->camera_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->camera_imgbtn_1, 0, 60);
    lv_obj_set_size(ui->camera_imgbtn_1, 50, 50);

    //Write style for camera_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->camera_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->camera_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->camera_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->camera_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->camera_imgbtn_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->camera_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->camera_imgbtn_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->camera_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->camera_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->camera_imgbtn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->camera_imgbtn_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->camera_imgbtn_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for camera_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->camera_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->camera_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->camera_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->camera_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->camera_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->camera_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for camera_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->camera_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->camera_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->camera_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->camera_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->camera_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->camera_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for camera_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->camera_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->camera_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes camera_label_4
    ui->camera_label_4 = lv_label_create(ui->camera);
    lv_label_set_text(ui->camera_label_4, "%");
    lv_label_set_long_mode(ui->camera_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->camera_label_4, 527, 20);
    lv_obj_set_size(ui->camera_label_4, 33, 25);

    //Write style for camera_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->camera_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->camera_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->camera_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->camera_label_4, &lv_font_montserratMedium_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->camera_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->camera_label_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->camera_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->camera_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->camera_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->camera_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->camera_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->camera_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->camera_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->camera_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes camera_humi
    ui->camera_humi = lv_label_create(ui->camera);
    lv_label_set_text(ui->camera_humi, "25.6");
    lv_label_set_long_mode(ui->camera_humi, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->camera_humi, 460, 20);
    lv_obj_set_size(ui->camera_humi, 78, 26);

    //Write style for camera_humi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->camera_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->camera_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->camera_humi, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->camera_humi, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->camera_humi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->camera_humi, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->camera_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->camera_humi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->camera_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->camera_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->camera_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->camera_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->camera_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->camera_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes camera_label_2
    ui->camera_label_2 = lv_label_create(ui->camera);
    lv_label_set_text(ui->camera_label_2, "℃");
    lv_label_set_long_mode(ui->camera_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->camera_label_2, 324, 21);
    lv_obj_set_size(ui->camera_label_2, 33, 25);

    //Write style for camera_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->camera_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->camera_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->camera_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->camera_label_2, &lv_font_SourceHanSerifSC_Regular_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->camera_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->camera_label_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->camera_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->camera_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->camera_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->camera_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->camera_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->camera_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->camera_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->camera_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes camera_temp
    ui->temp_data = lv_label_create(ui->camera);
    lv_label_set_text(ui->temp_data, "25.6");
    lv_label_set_long_mode(ui->temp_data, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->temp_data, 257, 20);
    lv_obj_set_size(ui->temp_data, 78, 26);

    //Write style for camera_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->temp_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->temp_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->temp_data, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->temp_data, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->temp_data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->temp_data, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->temp_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->temp_data, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->temp_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->temp_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->temp_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->temp_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->temp_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->temp_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes camera_temp_picture
    ui->camera_temp_picture = lv_img_create(ui->camera);
    lv_obj_add_flag(ui->camera_temp_picture, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->camera_temp_picture, &_temp_alpha_47x45);
    lv_img_set_pivot(ui->camera_temp_picture, 50,50);
    lv_img_set_angle(ui->camera_temp_picture, 0);
    lv_obj_set_pos(ui->camera_temp_picture, 223, 8);
    lv_obj_set_size(ui->camera_temp_picture, 47, 45);

    //Write style for camera_temp_picture, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->camera_temp_picture, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->camera_temp_picture, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->camera_temp_picture, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->camera_temp_picture, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes camera_humi_picture
    ui->camera_humi_picture = lv_img_create(ui->camera);
    lv_obj_add_flag(ui->camera_humi_picture, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->camera_humi_picture, &_humi_alpha_47x45);
    lv_img_set_pivot(ui->camera_humi_picture, 50,50);
    lv_img_set_angle(ui->camera_humi_picture, 0);
    lv_obj_set_pos(ui->camera_humi_picture, 420, 8);
    lv_obj_set_size(ui->camera_humi_picture, 47, 45);

    //Write style for camera_humi_picture, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->camera_humi_picture, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->camera_humi_picture, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->camera_humi_picture, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->camera_humi_picture, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of camera.


    //Update current screen layout.
    lv_obj_update_layout(ui->camera);

    //Init events for screen.
    events_init_camera(ui);
}
