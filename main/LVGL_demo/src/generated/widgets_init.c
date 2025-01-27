/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include "gui_guider.h"
#include "widgets_init.h"
#include <stdlib.h>


__attribute__((unused)) void kb_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

__attribute__((unused)) void ta_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
#if LV_USE_KEYBOARD || LV_USE_ZH_KEYBOARD
    lv_obj_t *ta = lv_event_get_target(e);
#endif
    lv_obj_t *kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED)
    {
#if LV_USE_ZH_KEYBOARD != 0
        lv_zh_keyboard_set_textarea(kb, ta);
#endif
#if LV_USE_KEYBOARD != 0
        lv_keyboard_set_textarea(kb, ta);
#endif
        lv_obj_move_foreground(kb);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED)
    {

#if LV_USE_ZH_KEYBOARD != 0
        lv_zh_keyboard_set_textarea(kb, ta);
#endif
#if LV_USE_KEYBOARD != 0
        lv_keyboard_set_textarea(kb, ta);
#endif
        lv_obj_move_background(kb);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

#if LV_USE_ANALOGCLOCK != 0
void clock_count(int *hour, int *min, int *sec)
{
    (*sec)++;
    if(*sec == 60)
    {
        *sec = 0;
        (*min)++;
    }
    if(*min == 60)
    {
        *min = 0;
        if(*hour < 12)
        {
            (*hour)++;
        } else {
            (*hour)++;
            *hour = *hour %12;
        }
    }
}
#endif

static lv_obj_t * screen_datetext_1_calendar;

void screen_datetext_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(screen_datetext_1_calendar == NULL) {
            screen_datetext_1_init_calendar(btn, s);
        }
    }
}

void screen_datetext_1_init_calendar(lv_obj_t *obj, char * s)
{
    if (screen_datetext_1_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        screen_datetext_1_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(screen_datetext_1_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(screen_datetext_1_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(screen_datetext_1_calendar, highlighted_days, 1);
        lv_obj_align(screen_datetext_1_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(screen_datetext_1_calendar, screen_datetext_1_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(screen_datetext_1_calendar);
        lv_obj_update_layout(scr);
    }
}

void screen_datetext_1_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.screen_datetext_1, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(screen_datetext_1_calendar);
        screen_datetext_1_calendar = NULL;
    }
}


extern int screen_digital_clock_1_hour_value;
extern int screen_digital_clock_1_min_value;
extern int screen_digital_clock_1_sec_value;

void screen_digital_clock_1_timer(lv_timer_t *timer)
{
    clock_count_24(&screen_digital_clock_1_hour_value, &screen_digital_clock_1_min_value, &screen_digital_clock_1_sec_value);
    if (lv_obj_is_valid(guider_ui.screen_digital_clock_1))
    {
        lv_dclock_set_text_fmt(guider_ui.screen_digital_clock_1, "%d:%02d:%02d", screen_digital_clock_1_hour_value, screen_digital_clock_1_min_value, screen_digital_clock_1_sec_value);
    }
}
static lv_obj_t * login_date_calendar;

void login_date_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(login_date_calendar == NULL) {
            login_date_init_calendar(btn, s);
        }
    }
}

void login_date_init_calendar(lv_obj_t *obj, char * s)
{
    if (login_date_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        login_date_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(login_date_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(login_date_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(login_date_calendar, highlighted_days, 1);
        lv_obj_align(login_date_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(login_date_calendar, login_date_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(login_date_calendar);
        lv_obj_update_layout(scr);
    }
}

void login_date_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.login_date, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(login_date_calendar);
        login_date_calendar = NULL;
    }
}


extern int login_time_hour_value;
extern int login_time_min_value;
extern int login_time_sec_value;

void login_time_timer(lv_timer_t *timer)
{
    clock_count_24(&login_time_hour_value, &login_time_min_value, &login_time_sec_value);
    if (lv_obj_is_valid(guider_ui.login_time))
    {
        lv_dclock_set_text_fmt(guider_ui.login_time, "%d:%02d:%02d", login_time_hour_value, login_time_min_value, login_time_sec_value);
    }
}
static lv_obj_t * app_datetext_1_calendar;

void app_datetext_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(app_datetext_1_calendar == NULL) {
            app_datetext_1_init_calendar(btn, s);
        }
    }
}

void app_datetext_1_init_calendar(lv_obj_t *obj, char * s)
{
    if (app_datetext_1_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        app_datetext_1_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(app_datetext_1_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(app_datetext_1_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(app_datetext_1_calendar, highlighted_days, 1);
        lv_obj_align(app_datetext_1_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(app_datetext_1_calendar, app_datetext_1_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(app_datetext_1_calendar);
        lv_obj_update_layout(scr);
    }
}

void app_datetext_1_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.app_datetext_1, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(app_datetext_1_calendar);
        app_datetext_1_calendar = NULL;
    }
}


extern int app_digital_clock_1_hour_value;
extern int app_digital_clock_1_min_value;
extern int app_digital_clock_1_sec_value;

void app_digital_clock_1_timer(lv_timer_t *timer)
{
    clock_count_24(&app_digital_clock_1_hour_value, &app_digital_clock_1_min_value, &app_digital_clock_1_sec_value);
    if (lv_obj_is_valid(guider_ui.app_digital_clock_1))
    {
        lv_dclock_set_text_fmt(guider_ui.app_digital_clock_1, "%d:%02d:%02d", app_digital_clock_1_hour_value, app_digital_clock_1_min_value, app_digital_clock_1_sec_value);
    }
}
static lv_obj_t * camera_datetext_1_calendar;

void camera_datetext_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(camera_datetext_1_calendar == NULL) {
            camera_datetext_1_init_calendar(btn, s);
        }
    }
}

void camera_datetext_1_init_calendar(lv_obj_t *obj, char * s)
{
    if (camera_datetext_1_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        camera_datetext_1_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(camera_datetext_1_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(camera_datetext_1_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(camera_datetext_1_calendar, highlighted_days, 1);
        lv_obj_align(camera_datetext_1_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(camera_datetext_1_calendar, camera_datetext_1_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(camera_datetext_1_calendar);
        lv_obj_update_layout(scr);
    }
}

void camera_datetext_1_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.camera_datetext_1, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(camera_datetext_1_calendar);
        camera_datetext_1_calendar = NULL;
    }
}


extern int camera_digital_clock_1_hour_value;
extern int camera_digital_clock_1_min_value;
extern int camera_digital_clock_1_sec_value;

void camera_digital_clock_1_timer(lv_timer_t *timer)
{
    clock_count_24(&camera_digital_clock_1_hour_value, &camera_digital_clock_1_min_value, &camera_digital_clock_1_sec_value);
    if (lv_obj_is_valid(guider_ui.camera_digital_clock_1))
    {
        lv_dclock_set_text_fmt(guider_ui.camera_digital_clock_1, "%d:%02d:%02d", camera_digital_clock_1_hour_value, camera_digital_clock_1_min_value, camera_digital_clock_1_sec_value);
    }
}
static lv_obj_t * weather_datetext_1_calendar;

void weather_datetext_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(weather_datetext_1_calendar == NULL) {
            weather_datetext_1_init_calendar(btn, s);
        }
    }
}

void weather_datetext_1_init_calendar(lv_obj_t *obj, char * s)
{
    if (weather_datetext_1_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        weather_datetext_1_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(weather_datetext_1_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(weather_datetext_1_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(weather_datetext_1_calendar, highlighted_days, 1);
        lv_obj_align(weather_datetext_1_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(weather_datetext_1_calendar, weather_datetext_1_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(weather_datetext_1_calendar);
        lv_obj_update_layout(scr);
    }
}

void weather_datetext_1_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.weather_datetext_1, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(weather_datetext_1_calendar);
        weather_datetext_1_calendar = NULL;
    }
}


extern int weather_digital_clock_1_hour_value;
extern int weather_digital_clock_1_min_value;
extern int weather_digital_clock_1_sec_value;

void weather_digital_clock_1_timer(lv_timer_t *timer)
{
    clock_count_24(&weather_digital_clock_1_hour_value, &weather_digital_clock_1_min_value, &weather_digital_clock_1_sec_value);
    if (lv_obj_is_valid(guider_ui.weather_digital_clock_1))
    {
        lv_dclock_set_text_fmt(guider_ui.weather_digital_clock_1, "%d:%02d:%02d", weather_digital_clock_1_hour_value, weather_digital_clock_1_min_value, weather_digital_clock_1_sec_value);
    }
}
static lv_obj_t * control_datetext_1_calendar;

void control_datetext_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(control_datetext_1_calendar == NULL) {
            control_datetext_1_init_calendar(btn, s);
        }
    }
}

void control_datetext_1_init_calendar(lv_obj_t *obj, char * s)
{
    if (control_datetext_1_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        control_datetext_1_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(control_datetext_1_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(control_datetext_1_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(control_datetext_1_calendar, highlighted_days, 1);
        lv_obj_align(control_datetext_1_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(control_datetext_1_calendar, control_datetext_1_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(control_datetext_1_calendar);
        lv_obj_update_layout(scr);
    }
}

void control_datetext_1_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.control_datetext_1, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(control_datetext_1_calendar);
        control_datetext_1_calendar = NULL;
    }
}


extern int control_digital_clock_1_hour_value;
extern int control_digital_clock_1_min_value;
extern int control_digital_clock_1_sec_value;

void control_digital_clock_1_timer(lv_timer_t *timer)
{
    clock_count_24(&control_digital_clock_1_hour_value, &control_digital_clock_1_min_value, &control_digital_clock_1_sec_value);
    if (lv_obj_is_valid(guider_ui.control_digital_clock_1))
    {
        lv_dclock_set_text_fmt(guider_ui.control_digital_clock_1, "%d:%02d:%02d", control_digital_clock_1_hour_value, control_digital_clock_1_min_value, control_digital_clock_1_sec_value);
    }
}
static lv_obj_t * music_datetext_1_calendar;

void music_datetext_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        char * s = lv_label_get_text(btn);
        if(music_datetext_1_calendar == NULL) {
            music_datetext_1_init_calendar(btn, s);
        }
    }
}

void music_datetext_1_init_calendar(lv_obj_t *obj, char * s)
{
    if (music_datetext_1_calendar == NULL) {
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        music_datetext_1_calendar = lv_calendar_create(lv_layer_top());
        lv_obj_t * scr = lv_obj_get_screen(obj);
        lv_coord_t scr_height = lv_obj_get_height(scr);
        lv_coord_t scr_width = lv_obj_get_width(scr);
        lv_obj_set_size(music_datetext_1_calendar, scr_width * 0.8, scr_height * 0.8);
        char * year = strtok(s, "/");
        char * month = strtok(NULL, "/");
        char * day = strtok(NULL, "/");
        lv_calendar_set_showed_date(music_datetext_1_calendar, atoi(year), atoi(month));
        lv_calendar_date_t highlighted_days[1];       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = atoi(year);
        highlighted_days[0].month = atoi(month);
        highlighted_days[0].day = atoi(day);
        lv_calendar_set_highlighted_dates(music_datetext_1_calendar, highlighted_days, 1);
        lv_obj_align(music_datetext_1_calendar,LV_ALIGN_CENTER, 0, 0);

        lv_obj_add_event_cb(music_datetext_1_calendar, music_datetext_1_calendar_event_handler, LV_EVENT_ALL,NULL);
        lv_calendar_header_arrow_create(music_datetext_1_calendar);
        lv_obj_update_layout(scr);
    }
}

void music_datetext_1_calendar_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        lv_calendar_get_pressed_date(obj,&date);
        char buf[16];
        lv_snprintf(buf,sizeof(buf),"%d/%02d/%02d", date.year, date.month,date.day);
        lv_label_set_text(guider_ui.music_datetext_1, buf);
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
        lv_obj_del(music_datetext_1_calendar);
        music_datetext_1_calendar = NULL;
    }
}


extern int music_digital_clock_1_hour_value;
extern int music_digital_clock_1_min_value;
extern int music_digital_clock_1_sec_value;

void music_digital_clock_1_timer(lv_timer_t *timer)
{
    clock_count_24(&music_digital_clock_1_hour_value, &music_digital_clock_1_min_value, &music_digital_clock_1_sec_value);
    if (lv_obj_is_valid(guider_ui.music_digital_clock_1))
    {
        lv_dclock_set_text_fmt(guider_ui.music_digital_clock_1, "%d:%02d:%02d", music_digital_clock_1_hour_value, music_digital_clock_1_min_value, music_digital_clock_1_sec_value);
    }
}

