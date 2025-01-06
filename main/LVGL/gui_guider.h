/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "lv_dclock.h"
#include "lv_analogclock.h"
typedef struct
{
  
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *g_kb_screen;
	lv_obj_t *screen_label_1;
	lv_obj_t *screen_datetext_1;
	lv_obj_t *screen_digital_clock_1;
	lv_obj_t *screen_cont_1;
	lv_obj_t *screen_cont_2;
	lv_obj_t *screen_label_2;
	lv_obj_t *screen_label_3;
	lv_obj_t *screen_label_4;
	lv_obj_t *screen_label_5;
	lv_obj_t *screen_TEMP;
	lv_obj_t *screen_HUMI;
	lv_obj_t *login;
	bool login_del;
	lv_obj_t *g_kb_login;
	lv_obj_t *login_cont_1;
	lv_obj_t *login_password;
	lv_obj_t *login_login_key;
	lv_obj_t *login_login_key_label;
	lv_obj_t *login_date;
	lv_obj_t *login_time;
	lv_obj_t *login_Welcome;
	lv_obj_t *app;
	bool app_del;
	lv_obj_t *g_kb_app;
	lv_obj_t *app_cont_1;
	lv_obj_t *app_datetext_1;
	lv_obj_t *app_digital_clock_1;
	lv_obj_t *app_weather_button;
	lv_obj_t *app_weather_button_label;
	lv_obj_t *app_camera_button;
	lv_obj_t *app_camera_button_label;
	lv_obj_t *app_control_button;
	lv_obj_t *app_control_button_label;
	lv_obj_t *app_music_button;
	lv_obj_t *app_music_button_label;
	lv_obj_t *app_camer;
	lv_obj_t *app_weathe;
	lv_obj_t *app_contro;
	lv_obj_t *app_musi;
	lv_obj_t *app_imgbtn_5;
	lv_obj_t *app_imgbtn_5_label;
	lv_obj_t *app_temp_picture;
	lv_obj_t *app_humi;
	lv_obj_t *app_label_2;
	lv_obj_t *app_humi_picture;
	lv_obj_t *app_hum;
	lv_obj_t *app_label_3;
	lv_obj_t *camera;
	bool camera_del;
	lv_obj_t *g_kb_camera;
	lv_obj_t *camera_cont_1;
	lv_obj_t *camera_datetext_1;
	lv_obj_t *camera_digital_clock_1;
	lv_obj_t *camera_imgbtn_1;
	lv_obj_t *camera_imgbtn_1_label;
	lv_obj_t *camera_label_4;
	lv_obj_t *camera_humi;
	lv_obj_t *camera_label_2;
	lv_obj_t *camera_temp;
	lv_obj_t *camera_temp_picture;
	lv_obj_t *camera_humi_picture;
	lv_obj_t *weather;
	bool weather_del;
	lv_obj_t *g_kb_weather;
	lv_obj_t *weather_cont_1;
	lv_obj_t *weather_datetext_1;
	lv_obj_t *weather_digital_clock_1;
	lv_obj_t *weather_imgbtn_1;
	lv_obj_t *weather_imgbtn_1_label;
	lv_obj_t *weather_label_4;
	lv_obj_t *weather_humi;
	lv_obj_t *weather_label_2;
	lv_obj_t *weather_temp;
	lv_obj_t *weather_temp_picture;
	lv_obj_t *weather_humi_picture;
	lv_obj_t *control;
	bool control_del;
	lv_obj_t *g_kb_control;
	lv_obj_t *control_cont_1;
	lv_obj_t *control_datetext_1;
	lv_obj_t *control_digital_clock_1;
	lv_obj_t *control_imgbtn_1;
	lv_obj_t *control_imgbtn_1_label;
	lv_obj_t *control_label_4;
	lv_obj_t *control_humi;
	lv_obj_t *control_label_2;
	lv_obj_t *control_temp;
	lv_obj_t *control_temp_picture;
	lv_obj_t *control_humi_picture;
	lv_obj_t *music;
	bool music_del;
	lv_obj_t *g_kb_music;
	lv_obj_t *music_cont_1;
	lv_obj_t *music_datetext_1;
	lv_obj_t *music_digital_clock_1;
	lv_obj_t *music_label_4;
	lv_obj_t *music_humi;
	lv_obj_t *music_label_2;
	lv_obj_t *music_temp;
	lv_obj_t *music_temp_picture;
	lv_obj_t *music_humi_picture;
	lv_obj_t *music_imgbtn_1;
	lv_obj_t *music_imgbtn_1_label;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);


extern lv_ui guider_ui;


void setup_scr_screen(lv_ui *ui);
void setup_scr_login(lv_ui *ui);
void setup_scr_app(lv_ui *ui);
void setup_scr_camera(lv_ui *ui);
void setup_scr_weather(lv_ui *ui);
void setup_scr_control(lv_ui *ui);
void setup_scr_music(lv_ui *ui);

LV_IMG_DECLARE(_right_jiantou_117x102);
LV_IMG_DECLARE(_weather_alpha_90x80);
LV_IMG_DECLARE(_weather_alpha_90x80);
LV_IMG_DECLARE(_weather_alpha_90x80);
LV_IMG_DECLARE(_weather_alpha_90x80);
LV_IMG_DECLARE(_camera_alpha_90x80);
LV_IMG_DECLARE(_camera_alpha_90x80);
LV_IMG_DECLARE(_camera_alpha_90x80);
LV_IMG_DECLARE(_camera_alpha_90x80);
LV_IMG_DECLARE(_control_alpha_90x80);
LV_IMG_DECLARE(_control_alpha_90x80);
LV_IMG_DECLARE(_control_alpha_90x80);
LV_IMG_DECLARE(_control_alpha_90x80);
LV_IMG_DECLARE(_music_alpha_90x80);
LV_IMG_DECLARE(_music_alpha_90x80);
LV_IMG_DECLARE(_music_alpha_90x80);
LV_IMG_DECLARE(_music_alpha_90x80);
LV_IMG_DECLARE(_sleep_alpha_50x50);
LV_IMG_DECLARE(_sleep_alpha_50x50);
LV_IMG_DECLARE(_sleep_alpha_50x50);
LV_IMG_DECLARE(_sleep_alpha_50x50);
LV_IMG_DECLARE(_temp_alpha_47x45);
LV_IMG_DECLARE(_humi_alpha_47x45);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_temp_alpha_47x45);
LV_IMG_DECLARE(_humi_alpha_47x45);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_temp_alpha_47x45);
LV_IMG_DECLARE(_humi_alpha_47x45);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_temp_alpha_47x45);
LV_IMG_DECLARE(_humi_alpha_47x45);
LV_IMG_DECLARE(_temp_alpha_47x45);
LV_IMG_DECLARE(_humi_alpha_47x45);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_back_alpha_50x50);
LV_IMG_DECLARE(_back_alpha_50x50);

LV_FONT_DECLARE(lv_font_Acme_Regular_65)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_28)
LV_FONT_DECLARE(lv_font_montserratMedium_81)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_36)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_60)
LV_FONT_DECLARE(lv_font_montserratMedium_60)
LV_FONT_DECLARE(lv_font_montserratMedium_55)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_35)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_46)
LV_FONT_DECLARE(lv_font_montserratMedium_35)
LV_FONT_DECLARE(lv_font_montserratMedium_28)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_21)
LV_FONT_DECLARE(lv_font_montserratMedium_24)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_22)
LV_FONT_DECLARE(lv_font_montserratMedium_22)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_18)


#ifdef __cplusplus
}
#endif
#endif
