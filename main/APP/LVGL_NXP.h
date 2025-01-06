#ifndef _LVGL_NXP_H_
#define _LVGL_NXP_H_
#include "../../../components/LVGL/src/core/lv_obj.h"
/**
 * @brief           Calculate the digital clock by the 24-hours mode
 * @param obj       pointer to the values for hour/minute/seconds and the bool value to select AM/PM
 * @return          selection end index. The function of lv_dclock_24_timer_cb will call it.
 */
void clock_count_24(int * hour, int * minute, int * seconds);

void lv_dclock_set_text_fmt(lv_obj_t * obj, const char * fmt, ...) LV_FORMAT_ATTRIBUTE(2, 3);

lv_obj_t * lv_dclock_create(lv_obj_t * parent, char * input_time);

void lv_dclock_refr_text(lv_obj_t * obj);

typedef struct {
    lv_obj_t obj;
    char * text;

#if LV_DCLOCK_TEXT_SELECTION
    uint32_t sel_start;
    uint32_t sel_end;
#endif

    lv_point_t offset; /*Text draw position offset*/
    uint8_t static_txt : 1;             /*Flag to indicate the text is static*/
    uint8_t recolor : 1;                /*Enable in-line letter re-coloring*/
    uint8_t expand : 1;                 /*Ignore real width (used by the library with LV_LABEL_LONG_SCROLL)*/
} lv_dclock_t;

#endif
