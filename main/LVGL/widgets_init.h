/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef WIDGET_INIT_H
#define WIDGET_INIT_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "gui_guider.h"
#include "analogclock/lv_analogclock.h"
#include "dclock/lv_dclock.h"
__attribute__((unused)) void kb_event_cb(lv_event_t *e);
__attribute__((unused)) void ta_event_cb(lv_event_t *e);
#if LV_USE_ANALOGCLOCK != 0
void clock_count(int *hour, int *min, int *sec);
#endif


void screen_datetext_1_event_handler(lv_event_t *e);
void screen_datetext_1_calendar_event_handler(lv_event_t *e);
void screen_datetext_1_init_calendar(lv_obj_t *obj, char * s);
void screen_digital_clock_1_timer(lv_timer_t *timer);
void login_date_event_handler(lv_event_t *e);
void login_date_calendar_event_handler(lv_event_t *e);
void login_date_init_calendar(lv_obj_t *obj, char * s);
void login_time_timer(lv_timer_t *timer);
void app_datetext_1_event_handler(lv_event_t *e);
void app_datetext_1_calendar_event_handler(lv_event_t *e);
void app_datetext_1_init_calendar(lv_obj_t *obj, char * s);
void app_digital_clock_1_timer(lv_timer_t *timer);
void camera_datetext_1_event_handler(lv_event_t *e);
void camera_datetext_1_calendar_event_handler(lv_event_t *e);
void camera_datetext_1_init_calendar(lv_obj_t *obj, char * s);
void camera_digital_clock_1_timer(lv_timer_t *timer);
void weather_datetext_1_event_handler(lv_event_t *e);
void weather_datetext_1_calendar_event_handler(lv_event_t *e);
void weather_datetext_1_init_calendar(lv_obj_t *obj, char * s);
void weather_digital_clock_1_timer(lv_timer_t *timer);
void control_datetext_1_event_handler(lv_event_t *e);
void control_datetext_1_calendar_event_handler(lv_event_t *e);
void control_datetext_1_init_calendar(lv_obj_t *obj, char * s);
void control_digital_clock_1_timer(lv_timer_t *timer);
void music_datetext_1_event_handler(lv_event_t *e);
void music_datetext_1_calendar_event_handler(lv_event_t *e);
void music_datetext_1_init_calendar(lv_obj_t *obj, char * s);
void music_digital_clock_1_timer(lv_timer_t *timer);

#ifdef __cplusplus
}
#endif
#endif
