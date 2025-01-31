#ifndef _MYHTTP_H_
#define _MYHTTP_H_
#include "esp_http_client.h"
#include "cJSON.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include <time.h>
#include <sys/time.h>
#include "esp_timer.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "mbedtls/md5.h"
#include "mbedtls/md.h"
#include <stdio.h>
#include <string.h>

/*设备名称*/
#define ALILOT_DEVICE_NAME     "esp32_s3"

/*产品密钥*/
#define ProductKey      "k0ocyUXJ9bJ"

/*设备密钥*/
#define DeviceSecret    "aa2b4a4388d50be009e6a3ff90a8b33b"

#define HTTP_URL "iot-06z00d9wc4x18a6.http.iothub.aliyuncs.com"

#define HTTP_MAX_RECEIVE_LEN    512
typedef struct{
    char rx[HTTP_MAX_RECEIVE_LEN];              //接收数组
    uint16_t len;                               //数据长度
    uint8_t token_ack_flag;                     //是否收到平台返回的token数据 0：未收到
    uint16_t result_code;                       //返回码
    char *token;                                //通信密钥
}http_data_t;




#endif
