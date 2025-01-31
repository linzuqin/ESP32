#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nvs_flash.h"
#include "APP/WIFI.h"
#include "APP/mqtt_alilot.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "APP/http_weather.h"
#include "APP/ntp_time.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "APP/sensor.h"
#include "iic.h"
#include "ltdc.h"
#include "xl9555.h"
#include "lvgl_demo.h"
#include "gui_guider.h"
#include "UART.h"

typedef struct{
    uint8_t lv_disp_init_flag;          //显示设备初始化完成标志位
    uint8_t lv_indev_init_falg;         //输入设备初始化完成标志位
    uint8_t dht11_init_flag;            //dht11初始化完成标志位
    uint8_t WIFI_init_falg;             //WIFI初始化完成标志位
}init_t;



#endif
