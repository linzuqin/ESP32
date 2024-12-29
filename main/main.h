#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include "freertos_demo.h"
#include "APP/WIFI.h"
#include "APP/mqtt_alilot.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "APP/http_weather.h"

/*是否连接阿里云 若不链接阿里云 则默认http协议连接心知天气获取天气信息*/
#define CONNECT_ALILOT  1




#endif
