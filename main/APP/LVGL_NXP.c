#include "LVGL_NXP.h"
#define MY_CLASS &lv_obj_class

/**
 * @brief           Calculate the digital clock by the 24-hours mode
 * @param obj       pointer to the values for hour/minute/seconds and the bool value to select AM/PM
 * @return          selection end index. The function of lv_dclock_24_timer_cb will call it.
 */
void clock_count_24(int * hour, int * minute, int * seconds)
{
    (*seconds)++;

    if(*seconds == 60) {
        *seconds = 0;
        (*minute)++;
    }

    if(*minute == 60) {
        *minute = 0;
        (*hour)++;
    }

    if(*hour == 24) {
        *hour = 0;
    }
}

void lv_dclock_set_text_fmt(lv_obj_t * obj, const char * fmt, ...)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    LV_ASSERT_NULL(fmt);
    lv_obj_invalidate(obj);
    lv_dclock_t * dclock = (lv_dclock_t *)obj;

    /*If text is NULL then refresh*/
    if(fmt == NULL) {
        lv_dclock_refr_text(obj);
        return;
    }

    if(dclock->text != NULL && dclock->static_txt == 0) {
        lv_mem_free(dclock->text);
        dclock->text = NULL;
    }

    va_list args;
    va_start(args, fmt);
    dclock->text = _lv_txt_set_text_vfmt(fmt, args);
    va_end(args);
    dclock->static_txt = 0; /*Now the text is dynamically allocated*/

    lv_dclock_refr_text(obj);
}

lv_obj_t * lv_dclock_create(lv_obj_t * parent, char * input_time)
{
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    if(lv_obj_is_valid(obj)) {
        lv_dclock_set_text_fmt(obj, "%s", input_time);
    }
    return obj;
}


void lv_dclock_refr_text(lv_obj_t * obj)
{

    lv_dclock_t * dclock = (lv_dclock_t *)obj;
    if(dclock->text == NULL) return;
#if LV_DCLOCK_LONG_TXT_HINT
    dclock->hint.line_start = -1; /*The hint is invalid if the text changes*/
#endif

    lv_area_t txt_coords;
    lv_obj_get_content_coords(obj, &txt_coords);
    lv_coord_t max_w         = lv_area_get_width(&txt_coords);
    const lv_font_t * font   = lv_obj_get_style_text_font(obj, LV_PART_MAIN);
    lv_coord_t line_space = lv_obj_get_style_text_line_space(obj, LV_PART_MAIN);
    lv_coord_t letter_space = lv_obj_get_style_text_letter_space(obj, LV_PART_MAIN);

    /*Calc. the height and longest line*/
    lv_point_t size;
    lv_text_flag_t flag = LV_TEXT_FLAG_NONE;
    if(dclock->recolor != 0) flag |= LV_TEXT_FLAG_RECOLOR;
    if(dclock->expand != 0) flag |= LV_TEXT_FLAG_EXPAND;
    if(lv_obj_get_style_width(obj, LV_PART_MAIN) == LV_SIZE_CONTENT && !obj->w_layout) flag |= LV_TEXT_FLAG_FIT;

    lv_txt_get_size(&size, dclock->text, font, letter_space, line_space, max_w, flag);

    lv_obj_refresh_self_size(obj);

    lv_obj_invalidate(obj);

}

