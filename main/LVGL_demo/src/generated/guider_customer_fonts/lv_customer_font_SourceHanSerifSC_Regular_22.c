/*
 * Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/
/*******************************************************************************
 * Size: 22 px
 * Bpp: 4
 * Opts: undefined
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef LV_CUSTOMER_FONT_SOURCEHANSERIFSC_REGULAR_22
#define LV_CUSTOMER_FONT_SOURCEHANSERIFSC_REGULAR_22 1
#endif

#if LV_CUSTOMER_FONT_SOURCEHANSERIFSC_REGULAR_22

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+2103 "℃" */
    0x0, 0x7b, 0xa3, 0x0, 0x0, 0x0, 0x17, 0xbb,
    0x95, 0x0, 0xa, 0x60, 0x1b, 0x30, 0x0, 0x5,
    0xf9, 0x20, 0x2b, 0xb0, 0x1b, 0x0, 0x2, 0xa0,
    0x0, 0x4f, 0x80, 0x0, 0x7, 0xd0, 0x2a, 0x0,
    0x1, 0xb0, 0x0, 0xde, 0x0, 0x0, 0x4, 0xd0,
    0xc, 0x10, 0x7, 0x60, 0x4, 0xf9, 0x0, 0x0,
    0x1, 0x90, 0x2, 0xba, 0xb8, 0x0, 0x8, 0xf4,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xb, 0xf2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xd, 0xf1, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xd, 0xf0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xc, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x9, 0xf3, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x6, 0xf7, 0x0, 0x0,
    0x0, 0x90, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfc,
    0x0, 0x0, 0x2, 0xf0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x8f, 0x40, 0x0, 0x5, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xb, 0xf4, 0x0, 0x8, 0xf0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7d, 0xda,
    0xdb, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x11, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 352, .box_w = 20, .box_h = 18, .ofs_x = 1, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 8451, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t lv_customer_font_SourceHanSerifSC_Regular_22 = {
#else
lv_font_t lv_customer_font_SourceHanSerifSC_Regular_22 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 22,          /*The maximum line height required by the font*/
    .base_line = 3.3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
};



#endif /*#if LV_CUSTOMER_FONT_SOURCEHANSERIFSC_REGULAR_22*/

