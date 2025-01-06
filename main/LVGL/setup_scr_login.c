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
#include "lv_dclock.h"
#include "lv_analogclock.h"


int login_time_min_value = 34;
int login_time_hour_value = 21;
int login_time_sec_value = 16;
void setup_scr_login(lv_ui *ui)
{
    //Write codes login
    ui->login = lv_obj_create(NULL);
    ui->g_kb_login = lv_keyboard_create(ui->login);
    lv_obj_add_event_cb(ui->g_kb_login, kb_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui->g_kb_login, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_font(ui->g_kb_login, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_size(ui->login, 800, 480);
    lv_obj_set_scrollbar_mode(ui->login, LV_SCROLLBAR_MODE_OFF);

    //Write style for login, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->login, 159, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->login, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->login, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->login, lv_color_hex(0x00344C), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->login, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->login, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes login_cont_1
    ui->login_cont_1 = lv_obj_create(ui->login);
    lv_obj_set_pos(ui->login_cont_1, 0, 0);
    lv_obj_set_size(ui->login_cont_1, 800, 60);
    lv_obj_set_scrollbar_mode(ui->login_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for login_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->login_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->login_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->login_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->login_cont_1, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->login_cont_1, 9, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->login_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->login_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->login_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->login_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->login_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->login_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->login_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->login_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes login_password
    ui->login_password = lv_textarea_create(ui->login);
    lv_textarea_set_text(ui->login_password, "请输入密码");
    lv_textarea_set_placeholder_text(ui->login_password, "");
    lv_textarea_set_password_bullet(ui->login_password, "*");
    lv_textarea_set_password_mode(ui->login_password, false);
    lv_textarea_set_one_line(ui->login_password, true);
    lv_textarea_set_accepted_chars(ui->login_password, "");
    lv_textarea_set_max_length(ui->login_password, 64);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->login_password, ta_event_cb, LV_EVENT_ALL, ui->g_kb_login);
#endif
    lv_obj_set_pos(ui->login_password, 187, 159);
    lv_obj_set_size(ui->login_password, 428, 57);

    //Write style for login_password, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->login_password, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->login_password, &lv_font_SourceHanSerifSC_Regular_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->login_password, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->login_password, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->login_password, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->login_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->login_password, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->login_password, 248, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->login_password, lv_color_hex(0x00a7eb), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->login_password, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->login_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->login_password, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->login_password, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->login_password, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->login_password, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for login_password, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->login_password, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->login_password, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->login_password, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->login_password, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes login_login_key
    ui->login_login_key = lv_btn_create(ui->login);
    ui->login_login_key_label = lv_label_create(ui->login_login_key);
    lv_label_set_text(ui->login_login_key_label, "");
    lv_label_set_long_mode(ui->login_login_key_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->login_login_key_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->login_login_key, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->login_login_key_label, LV_PCT(100));
    lv_obj_set_pos(ui->login_login_key, 336, 263);
    lv_obj_set_size(ui->login_login_key, 117, 102);

    //Write style for login_login_key, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->login_login_key, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->login_login_key, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->login_login_key, 44, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->login_login_key, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->login_login_key, lv_color_hex(0x0d4b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->login_login_key, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->login_login_key, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->login_login_key, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->login_login_key, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->login_login_key, &_right_jiantou_117x102, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->login_login_key, 205, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->login_login_key, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->login_login_key, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->login_login_key, &lv_font_SourceHanSerifSC_Regular_46, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->login_login_key, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->login_login_key, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes login_date
    ui->login_date = lv_label_create(ui->login);
    lv_label_set_text(ui->login_date, "2025/01/04");
    lv_obj_set_style_text_align(ui->login_date, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui->login_date, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->login_date, login_date_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->login_date, 599, 8);
    lv_obj_set_size(ui->login_date, 194, 43);

    //Write style for login_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->login_date, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->login_date, &lv_font_Alatsi_Regular_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->login_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->login_date, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->login_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->login_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->login_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->login_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->login_date, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->login_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->login_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->login_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes login_time
    static bool login_time_timer_enabled = false;
    ui->login_time = lv_dclock_create(ui->login, "21:34:16");
    if (!login_time_timer_enabled) {
        lv_timer_create(login_time_timer, 1000, NULL);
        login_time_timer_enabled = true;
    }
    lv_obj_set_pos(ui->login_time, 5, 8);
    lv_obj_set_size(ui->login_time, 180, 43);

    //Write style for login_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->login_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->login_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->login_time, &lv_font_montserratMedium_35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->login_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->login_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->login_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->login_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->login_time, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->login_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->login_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->login_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->login_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes login_Welcome
    ui->login_Welcome = lv_label_create(ui->login);
    lv_label_set_text(ui->login_Welcome, "Welcome");
    lv_label_set_long_mode(ui->login_Welcome, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->login_Welcome, 303, 8);
    lv_obj_set_size(ui->login_Welcome, 194, 43);

    //Write style for login_Welcome, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->login_Welcome, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->login_Welcome, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->login_Welcome, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->login_Welcome, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->login_Welcome, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->login_Welcome, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->login_Welcome, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->login_Welcome, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->login_Welcome, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->login_Welcome, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->login_Welcome, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->login_Welcome, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->login_Welcome, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->login_Welcome, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of login.


    //Update current screen layout.
    lv_obj_update_layout(ui->login);

    //Init events for screen.
    events_init_login(ui);
}
