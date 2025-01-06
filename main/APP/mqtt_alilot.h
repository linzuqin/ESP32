#ifndef _MQTT_ALILOT_H_
#define _MQTT_ALILOT_H_
#include "mqtt_client.h" 
#include "stdio.h"
#include "esp_log.h"
#include "mbedtls/md5.h"
#include "mbedtls/md.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "cJSON.h"
#include <time.h>
#include "WIFI.h"
#include "esp_ota_ops.h"
#include "ALILOT_OTA.h"
#include "esp_http_client.h"
#include "esp_crt_bundle.h"
/*mqtt服务器端口号*/
#define ALILOT_PORT   1883

/*mqtt服务器产品ID*/
#define MQTT_CLIENT_ID  "111"

/*mqtt服务器用户名*/
#define MQTT_USERNAME   "adsasd"

/*mqtt服务器密码*/
#define MQTT_PASSWORD   "123455678"

/*mqtt上报主题*/
#define MQTT_SUB_TOPIC  "/sys/#"

/*mqtt接收数据主题*/
#define MQTT_PUB_TOPIC  "dev/#"

/*设备名称*/
#define ALILOT_DEVICE_NAME     "esp32_s3"

/*产品密钥*/
#define ProductKey      "k0ocyUXJ9bJ"

/*设备密钥*/
#define DeviceSecret    "aa2b4a4388d50be009e6a3ff90a8b33b"

/*mqtt服务器网址*/
#define MQTT_URL        "mqtts://iot-06z00d9wc4x18a6.mqtt.iothub.aliyuncs.com"

/*设备属性上报主题*/
#define    POST_TOPIC "/"ProductKey"/"ALILOT_DEVICE_NAME"/thing/event/property/post"

/*设备属性下发主题*/
#define    SET_TOPIC    "/sys/"ProductKey"/"ALILOT_DEVICE_NAME"/thing/service/property/set"

/*设备属性下发应答*/
#define    SET_REPLY_TOPIC  "/sys/"ProductKey"/"ALILOT_DEVICE_NAME"/thing/service/property/set_reply"

/*上报OTA版本信息主题*/
#define     OTA_VERSION_TOPIC "/ota/device/inform/"ProductKey"/"ALILOT_DEVICE_NAME

/*OTA升级主题*/
#define     OTA_UPGRADE_TOPIC   "/ota/device/upgrade/"ProductKey"/"ALILOT_DEVICE_NAME

/*OTA升级进度上报主题*/
#define     OTA_PROCESS_TOPIC   "/ota/device/progress/"ProductKey"/"ALILOT_DEVICE_NAME

/*请求OTA升级*/
#define     ALILOT_OTA_GET_TOPIC      "/sys/"ProductKey"/"ALILOT_DEVICE_NAME"/thing/ota/firmware/get"

/*请求OTA升级应答主题*/
#define     ALILOT_OTA_GET_REPLY_TOPIC    "/sys/"ProductKey"/"ALILOT_DEVICE_NAME"/thing/ota/firmware/get_reply"

/*阿里云物理模型数量*/
#define Alilot_Model_NUM    10

/*上报数据结构体*/
typedef struct{
    char *data_str;
    int len;
    cJSON *root;         //根节点
    char *topic;        //主题
}Alilot_t;

/*事件类型*/
typedef enum
{
    ALIOT_data_POST,      //常规属性上报
    ALIOT_data_SET_ACK,   //属性设置回复
    ALIOT_data_EVENT,     //事件上报
    ALILOT_OTA_VERSION,   //OTA升级事件
}ALIOT_TYPE;

/*属性参数*/
typedef struct{
    char* name;             //属性标识符
    char* str_value;        //字符串值
    double double_value;    //浮点值
    int   int_value;        //整型值
}Property_t;

/*阿里云物理模型*/
typedef struct{
    char* name;             //属性标识符
    char* str_value;        //字符串值
    double double_value;    //浮点值
    int   int_value;        //整型值
}Alilot_Model_t;

void Alilot_post_version(const char* version);
const char* Get_app_version(void);
void Alilot_mqtt_start(void);
const char* Get_app_version(void);
void ALILOT_mqtt_set_ack(int code , char *message , char* id , char *version);


#endif
