#ifndef HTTP_WEATHER_H
#define HTTP_WEATHER_H

/**********INCLUDE**********/
#include "esp_http_client.h"
#include "cJSON.h"
#include "esp_log.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include <stdio.h>
#include <string.h>

/**********DEFINE**********/
/*公钥*/
#define Public_KEY      "P3mSu0-Rj-mGh3iwS"

/*私钥*/
#define Personal_KEY    "ScPoJ3ivFZQgiSuP1"

/*位置*/
#define MY_LOCATION     "FuJian FuZhou"

/*语言*/
#define MY_LANGUAGE     "zh-Hans"

#define MY_UNIT         "c"

/*接口地址*/
#define MY_URL          "https://api.seniverse.com/v3/weather/now.json?key="Personal_KEY"&location="MY_LOCATION"&language="MY_LANGUAGE"&unit="MY_UNIT

/*数据最大长度*/
#define DATA_MAX_LEN    1024

/*位置数据结构体*/
typedef struct{
    char* id;       //位置ID
    char* name;     //位置名称
    char* country;  //国家
    char* path;     //详细地址
    char* timezone; //时区
    char* timezone_offset;  //时差
}location_t;

/*天气数据结构体*/
typedef struct{
    char* text;     //天气
    char* code;     //天气编号
    char* temp;     //温度
}Weather_data_t;

/*天气数据结构体*/
typedef struct{
    char *data;             //数据
    uint16_t data_len;      //数据长度
    Weather_data_t weather;      //天气数据
    location_t location;         //位置
    char  last_update_time[25];  //平台数据上一次更新时间
}Weather_t;

/*启动htpp获取天气任务*/
void http_weather_get_start(void);

#endif