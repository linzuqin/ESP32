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



int app_digital_clock_1_min_value = 34;
int app_digital_clock_1_hour_value = 21;
int app_digital_clock_1_sec_value = 16;
void setup_scr_app(lv_ui *ui)
{
    //Write codes app
    ui->app = lv_obj_create(NULL);
    ui->g_kb_app = lv_keyboard_create(ui->app);
    lv_obj_add_event_cb(ui->g_kb_app, kb_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui->g_kb_app, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_font(ui->g_kb_app, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_size(ui->app, 800, 480);
    lv_obj_set_scrollbar_mode(ui->app, LV_SCROLLBAR_MODE_OFF);

    //Write style for app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->app, 159, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->app, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->app, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->app, lv_color_hex(0x00344C), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->app, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes app_cont_1
    ui->app_cont_1 = lv_obj_create(ui->app);
    lv_obj_set_pos(ui->app_cont_1, 0, 0);
    lv_obj_set_size(ui->app_cont_1, 800, 60);
    lv_obj_set_scrollbar_mode(ui->app_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for app_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->app_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->app_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->app_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->app_cont_1, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_cont_1, 9, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->app_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->app_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->app_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->app_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->app_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->app_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->app_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->app_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes app_datetext_1
    ui->date_text = lv_label_create(ui->app);
    lv_label_set_text(ui->date_text, "2025/01/04");
    lv_obj_set_style_text_align(ui->date_text, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui->date_text, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->date_text, app_datetext_1_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->date_text, 606, 8);
    lv_obj_set_size(ui->date_text, 194, 43);

    //Write style for app_datetext_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
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

    //Write codes app_digital_clock_1
    static bool app_digital_clock_1_timer_enabled = false;
    ui->time_text = lv_dclock_create(ui->app, "21:34:16");
    if (!app_digital_clock_1_timer_enabled) {
        lv_timer_create(app_digital_clock_1_timer, 1000, NULL);
        app_digital_clock_1_timer_enabled = true;
    }
    lv_obj_set_pos(ui->time_text, 0, 8);
    lv_obj_set_size(ui->time_text, 180, 43);

    //Write style for app_digital_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
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

    //Write codes app_weather_button
    ui->app_weather_button = lv_imgbtn_create(ui->app);
    lv_obj_add_flag(ui->app_weather_button, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->app_weather_button, LV_IMGBTN_STATE_RELEASED, NULL, &_weather_alpha_90x80, NULL);
    lv_imgbtn_set_src(ui->app_weather_button, LV_IMGBTN_STATE_PRESSED, NULL, &_weather_alpha_90x80, NULL);
    lv_imgbtn_set_src(ui->app_weather_button, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_weather_alpha_90x80, NULL);
    lv_imgbtn_set_src(ui->app_weather_button, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_weather_alpha_90x80, NULL);
    ui->app_weather_button_label = lv_label_create(ui->app_weather_button);
    lv_label_set_text(ui->app_weather_button_label, "");
    lv_label_set_long_mode(ui->app_weather_button_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->app_weather_button_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->app_weather_button, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->app_weather_button, 255, 138);
    lv_obj_set_size(ui->app_weather_button, 90, 80);

    //Write style for app_weather_button, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->app_weather_button, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->app_weather_button, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->app_weather_button, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->app_weather_button, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_weather_button, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->app_weather_button, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->app_weather_button, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->app_weather_button, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->app_weather_button, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->app_weather_button, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->app_weather_button, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->app_weather_button, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for app_weather_button, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->app_weather_button, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->app_weather_button, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->app_weather_button, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->app_weather_button, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->app_weather_button, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->app_weather_button, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for app_weather_button, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->app_weather_button, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->app_weather_button, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->app_weather_button, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->app_weather_button, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->app_weather_button, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->app_weather_button, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for app_weather_button, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->app_weather_button, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->app_weather_button, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes app_camera_button
    ui->app_camera_button = lv_imgbtn_create(ui->app);
    lv_obj_add_flag(ui->app_camera_button, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->app_camera_button, LV_IMGBTN_STATE_RELEASED, NULL, &_camera_alpha_90x80, NULL);
    lv_imgbtn_set_src(ui->app_camera_button, LV_IMGBTN_STATE_PRESSED, NULL, &_camera_alpha_90x80, NULL);
    lv_imgbtn_set_src(ui->app_camera_button, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_camera_alpha_90x80, NULL);
    lv_imgbtn_set_src(ui->app_camera_button, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_camera_alpha_90x80, NULL);
    ui->app_camera_button_label = lv_label_create(ui->app_camera_button);
    lv_label_set_text(ui->app_camera_button_label, "");
    lv_label_set_long_mode(ui->app_camera_button_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->app_camera_button_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->app_camera_button, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->app_camera_button, 55, 138);
    lv_obj_set_size(ui->app_camera_button, 90, 80);

    //Write style for app_camera_button, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->app_camera_button, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->app_camera_button, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->app_camera_button, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->app_camera_button, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_camera_button, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->app_camera_button, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->app_camera_button, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->app_camera_button, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->app_camera_button, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->app_camera_button, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->app_camera_button, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->app_camera_button, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for app_camera_button, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->app_camera_button, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->app_camera_button, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->app_camera_button, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->app_camera_button, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->app_camera_button, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->app_camera_button, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for app_camera_button, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->app_camera_button, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->app_camera_button, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->app_camera_button, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->app_camera_button, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->app_camera_button, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->app_camera_button, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for app_camera_button, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->app_camera_button, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->app_camera_button, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes app_control_button
    ui->app_control_button = lv_imgbtn_create(ui->app);
    lv_obj_add_flag(ui->app_control_button, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->app_control_button, LV_IMGBTN_STATE_RELEASED, NULL, &_control_alpha_90x80, NULL);
    lv_imgbtn_set_src(ui->app_control_button, LV_IMGBTN_STATE_PRESSED, NULL, &_control_alpha_90x80, NULL);
    lv_imgbtn_set_src(ui->app_control_button, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_control_alpha_90x80, NULL);
    lv_imgbtn_set_src(ui->app_control_button, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_control_alpha_90x80, NULL);
    ui->app_control_button_label = lv_label_create(ui->app_control_button);
    lv_label_set_text(ui->app_control_button_label, "");
    lv_label_set_long_mode(ui->app_control_button_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->app_control_button_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->app_control_button, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->app_control_button, 455, 138);
    lv_obj_set_size(ui->app_control_button, 90, 80);

    //Write style for app_control_button, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->app_control_button, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->app_control_button, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->app_control_button, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->app_control_button, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_control_button, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->app_control_button, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->app_control_button, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->app_control_button, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->app_control_button, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->app_control_button, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->app_control_button, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->app_control_button, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for app_control_button, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->app_control_button, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->app_control_button, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->app_control_button, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->app_control_button, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->app_control_button, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->app_control_button, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for app_control_button, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->app_control_button, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->app_control_button, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->app_control_button, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->app_control_button, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->app_control_button, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->app_control_button, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for app_control_button, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->app_control_button, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->app_control_button, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes app_music_button
    ui->app_music_button = lv_imgbtn_create(ui->app);
    lv_obj_add_flag(ui->app_music_button, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->app_music_button, LV_IMGBTN_STATE_RELEASED, NULL, &_music_alpha_90x80, NULL);
    lv_imgbtn_set_src(ui->app_music_button, LV_IMGBTN_STATE_PRESSED, NULL, &_music_alpha_90x80, NULL);
    lv_imgbtn_set_src(ui->app_music_button, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_music_alpha_90x80, NULL);
    lv_imgbtn_set_src(ui->app_music_button, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_music_alpha_90x80, NULL);
    ui->app_music_button_label = lv_label_create(ui->app_music_button);
    lv_label_set_text(ui->app_music_button_label, "");
    lv_label_set_long_mode(ui->app_music_button_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->app_music_button_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->app_music_button, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->app_music_button, 655, 138);
    lv_obj_set_size(ui->app_music_button, 90, 80);

    //Write style for app_music_button, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->app_music_button, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->app_music_button, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->app_music_button, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->app_music_button, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_music_button, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->app_music_button, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->app_music_button, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->app_music_button, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->app_music_button, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->app_music_button, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->app_music_button, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->app_music_button, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for app_music_button, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->app_music_button, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->app_music_button, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->app_music_button, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->app_music_button, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->app_music_button, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->app_music_button, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for app_music_button, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->app_music_button, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->app_music_button, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->app_music_button, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->app_music_button, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->app_music_button, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->app_music_button, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for app_music_button, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->app_music_button, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->app_music_button, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes app_camer
    ui->app_camer = lv_label_create(ui->app);
    lv_label_set_text(ui->app_camer, "摄像头");
    lv_label_set_long_mode(ui->app_camer, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->app_camer, 55, 227);
    lv_obj_set_size(ui->app_camer, 100, 21);

    //Write style for app_camer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->app_camer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_camer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->app_camer, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->app_camer, &lv_font_SourceHanSerifSC_Regular_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->app_camer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->app_camer, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->app_camer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->app_camer, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->app_camer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->app_camer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->app_camer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->app_camer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->app_camer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->app_camer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes app_weathe
    ui->app_weathe = lv_label_create(ui->app);
    lv_label_set_text(ui->app_weathe, "天气");
    lv_label_set_long_mode(ui->app_weathe, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->app_weathe, 250, 227);
    lv_obj_set_size(ui->app_weathe, 100, 21);

    //Write style for app_weathe, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->app_weathe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_weathe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->app_weathe, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->app_weathe, &lv_font_SourceHanSerifSC_Regular_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->app_weathe, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->app_weathe, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->app_weathe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->app_weathe, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->app_weathe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->app_weathe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->app_weathe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->app_weathe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->app_weathe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->app_weathe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes app_contro
    ui->app_contro = lv_label_create(ui->app);
    lv_label_set_text(ui->app_contro, "控制面板");
    lv_label_set_long_mode(ui->app_contro, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->app_contro, 452, 227);
    lv_obj_set_size(ui->app_contro, 100, 21);

    //Write style for app_contro, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->app_contro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_contro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->app_contro, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->app_contro, &lv_font_SourceHanSerifSC_Regular_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->app_contro, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->app_contro, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->app_contro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->app_contro, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->app_contro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->app_contro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->app_contro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->app_contro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->app_contro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->app_contro, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes app_musi
    ui->app_musi = lv_label_create(ui->app);
    lv_label_set_text(ui->app_musi, "音乐");
    lv_label_set_long_mode(ui->app_musi, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->app_musi, 652, 227);
    lv_obj_set_size(ui->app_musi, 100, 21);

    //Write style for app_musi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->app_musi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_musi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->app_musi, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->app_musi, &lv_font_SourceHanSerifSC_Regular_21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->app_musi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->app_musi, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->app_musi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->app_musi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->app_musi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->app_musi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->app_musi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->app_musi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->app_musi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->app_musi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes app_imgbtn_5
    ui->app_imgbtn_5 = lv_imgbtn_create(ui->app);
    lv_obj_add_flag(ui->app_imgbtn_5, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->app_imgbtn_5, LV_IMGBTN_STATE_RELEASED, NULL, &_sleep_alpha_50x50, NULL);
    lv_imgbtn_set_src(ui->app_imgbtn_5, LV_IMGBTN_STATE_PRESSED, NULL, &_sleep_alpha_50x50, NULL);
    lv_imgbtn_set_src(ui->app_imgbtn_5, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_sleep_alpha_50x50, NULL);
    lv_imgbtn_set_src(ui->app_imgbtn_5, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_sleep_alpha_50x50, NULL);
    ui->app_imgbtn_5_label = lv_label_create(ui->app_imgbtn_5);
    lv_label_set_text(ui->app_imgbtn_5_label, "");
    lv_label_set_long_mode(ui->app_imgbtn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->app_imgbtn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->app_imgbtn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->app_imgbtn_5, 0, 60);
    lv_obj_set_size(ui->app_imgbtn_5, 50, 50);

    //Write style for app_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->app_imgbtn_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->app_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->app_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->app_imgbtn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_imgbtn_5, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->app_imgbtn_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->app_imgbtn_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->app_imgbtn_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->app_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->app_imgbtn_5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->app_imgbtn_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->app_imgbtn_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for app_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->app_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->app_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->app_imgbtn_5, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->app_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->app_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->app_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for app_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->app_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->app_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->app_imgbtn_5, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->app_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->app_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->app_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for app_imgbtn_5, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->app_imgbtn_5, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->app_imgbtn_5, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes app_temp_picture
    ui->app_temp_picture = lv_img_create(ui->app);
    lv_obj_add_flag(ui->app_temp_picture, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->app_temp_picture, &_temp_alpha_47x45);
    lv_img_set_pivot(ui->app_temp_picture, 50,50);
    lv_img_set_angle(ui->app_temp_picture, 0);
    lv_obj_set_pos(ui->app_temp_picture, 223, 8);
    lv_obj_set_size(ui->app_temp_picture, 47, 45);

    //Write style for app_temp_picture, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->app_temp_picture, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->app_temp_picture, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_temp_picture, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->app_temp_picture, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes app_temp
    ui->temp_data = lv_label_create(ui->app);
    lv_label_set_text(ui->temp_data, "25.6");
    lv_label_set_long_mode(ui->temp_data, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->temp_data, 257, 20);
    lv_obj_set_size(ui->temp_data, 78, 26);

    //Write style for app_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
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

    //Write codes app_label_2
    ui->app_label_2 = lv_label_create(ui->app);
    lv_label_set_text(ui->app_label_2, "℃");
    lv_label_set_long_mode(ui->app_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->app_label_2, 324, 21);
    lv_obj_set_size(ui->app_label_2, 33, 25);

    //Write style for app_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->app_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->app_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->app_label_2, &lv_font_SourceHanSerifSC_Regular_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->app_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->app_label_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->app_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->app_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->app_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->app_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->app_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->app_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->app_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->app_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes app_humi_picture
    ui->app_humi_picture = lv_img_create(ui->app);
    lv_obj_add_flag(ui->app_humi_picture, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->app_humi_picture, &_humi_alpha_47x45);
    lv_img_set_pivot(ui->app_humi_picture, 50,50);
    lv_img_set_angle(ui->app_humi_picture, 0);
    lv_obj_set_pos(ui->app_humi_picture, 420, 8);
    lv_obj_set_size(ui->app_humi_picture, 47, 45);

    //Write style for app_humi_picture, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->app_humi_picture, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->app_humi_picture, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_humi_picture, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->app_humi_picture, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes app_humi
    ui->app_humi = lv_label_create(ui->app);
    lv_label_set_text(ui->app_humi, "25.6");
    lv_label_set_long_mode(ui->app_humi, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->app_humi, 460, 20);
    lv_obj_set_size(ui->app_humi, 78, 26);

    //Write style for app_humi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->app_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->app_humi, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->app_humi, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->app_humi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->app_humi, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->app_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->app_humi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->app_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->app_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->app_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->app_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->app_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->app_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes app_label_3
    ui->app_label_3 = lv_label_create(ui->app);
    lv_label_set_text(ui->app_label_3, "%");
    lv_label_set_long_mode(ui->app_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->app_label_3, 527, 20);
    lv_obj_set_size(ui->app_label_3, 33, 25);

    //Write style for app_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->app_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->app_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->app_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->app_label_3, &lv_font_montserratMedium_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->app_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->app_label_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->app_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->app_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->app_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->app_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->app_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->app_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->app_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->app_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of app.


    //Update current screen layout.
    lv_obj_update_layout(ui->app);

    //Init events for screen.
    events_init_app(ui);
}
