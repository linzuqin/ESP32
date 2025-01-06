/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.login, guider_ui.login_del, &guider_ui.screen_del, setup_scr_login, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, false, false);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen, screen_event_handler, LV_EVENT_ALL, ui);
}

static void login_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.login_del, setup_scr_screen, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 200, false, false);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void login_password_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        lv_textarea_set_text(guider_ui.login_password, "");
        lv_obj_set_style_text_color(guider_ui.login_password, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
        break;
    }
    default:
        break;
    }
}

static void login_login_key_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        if (strcmp(lv_textarea_get_text(guider_ui.login_password),"123456")==0) {
            ui_load_scr_animation(&guider_ui, &guider_ui.app, guider_ui.app_del, &guider_ui.login_del, setup_scr_app, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, false);
        } else {
            lv_textarea_set_text(guider_ui.login_password, "password error");
            lv_obj_set_style_text_color(guider_ui.login_password, lv_color_hex(0xf60404), LV_PART_MAIN|LV_STATE_DEFAULT);
        }
        break;
    }
    default:
        break;
    }
}

void events_init_login (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->login, login_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->login_password, login_password_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->login_login_key, login_login_key_event_handler, LV_EVENT_ALL, ui);
}

static void app_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.app_del, setup_scr_screen, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 400, 100, false, false);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void app_weather_button_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.weather, guider_ui.weather_del, &guider_ui.app_del, setup_scr_weather, LV_SCR_LOAD_ANIM_FADE_ON, 200, 50, true, true);
        break;
    }
    default:
        break;
    }
}

static void app_camera_button_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.camera, guider_ui.camera_del, &guider_ui.app_del, setup_scr_camera, LV_SCR_LOAD_ANIM_FADE_ON, 200, 50, true, true);
        break;
    }
    default:
        break;
    }
}

static void app_control_button_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.control, guider_ui.control_del, &guider_ui.app_del, setup_scr_control, LV_SCR_LOAD_ANIM_FADE_ON, 200, 50, true, true);
        break;
    }
    default:
        break;
    }
}

static void app_music_button_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.music, guider_ui.music_del, &guider_ui.app_del, setup_scr_music, LV_SCR_LOAD_ANIM_FADE_ON, 200, 50, true, true);
        break;
    }
    default:
        break;
    }
}

static void app_imgbtn_5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.app_del, setup_scr_screen, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 400, 200, false, false);
        break;
    }
    default:
        break;
    }
}

void events_init_app (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->app, app_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->app_weather_button, app_weather_button_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->app_camera_button, app_camera_button_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->app_control_button, app_control_button_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->app_music_button, app_music_button_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->app_imgbtn_5, app_imgbtn_5_event_handler, LV_EVENT_ALL, ui);
}

static void camera_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.app, guider_ui.app_del, &guider_ui.camera_del, setup_scr_app, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, false);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void camera_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.app, guider_ui.app_del, &guider_ui.camera_del, setup_scr_app, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 50, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_camera (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->camera, camera_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->camera_imgbtn_1, camera_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
}

static void weather_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.app, guider_ui.app_del, &guider_ui.weather_del, setup_scr_app, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, true, false);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void weather_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.app, guider_ui.app_del, &guider_ui.weather_del, setup_scr_app, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 50, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_weather (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->weather, weather_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->weather_imgbtn_1, weather_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
}

static void control_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.app, guider_ui.app_del, &guider_ui.control_del, setup_scr_app, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, true, false);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void control_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.app, guider_ui.app_del, &guider_ui.control_del, setup_scr_app, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 50, true, false);
        break;
    }
    default:
        break;
    }
}

void events_init_control (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->control, control_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->control_imgbtn_1, control_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
}

static void music_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.app, guider_ui.app_del, &guider_ui.music_del, setup_scr_app, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void music_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.app, guider_ui.app_del, &guider_ui.music_del, setup_scr_app, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 50, true, false);
        break;
    }
    default:
        break;
    }
}

void events_init_music (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->music, music_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->music_imgbtn_1, music_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
