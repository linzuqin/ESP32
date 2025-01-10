#ifndef _lvgl_ui_H_
#define _lvgl_ui_H_

#include "ltdc.h"
#include "touch.h"
#include "esp_timer.h"
#include "lvgl.h"
#include "demos/lv_demos.h"

#include "freertos/event_groups.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "APP/sensor.h"
#include "gui_guider.h"

#define SCREEN_MAX_WIDTH    800    
#define SCREEN_MAX_HEIGHT   480

//void lvgl_demo(void);                                                                               /* lvgl_demo入口函数 */
void lv_port_disp_init(void);                                                                       /* 初始化并注册显示设备 */
void lv_port_indev_init(void);                                                                      /* 初始化并注册输入设备 */
void touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);                               /* 图形库的触摸屏读取回调函数 */

void LVGL_TASK_START(void);

#endif
