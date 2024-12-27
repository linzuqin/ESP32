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

/*事件类型*/
typedef enum
{
    ALIOT_DM_POST,      //常规属性上报
    ALIOT_DM_SET_ACK,   //属性设置回复
    ALIOT_DM_EVENT,     //事件上报
}ALIOT_TYPE;

/*设备属性上报主题*/
#define    Attribute_TOPIC "/"ProductKey"/"ALILOT_DEVICE_NAME"/thing/event/property/post"



/*上报数据结构体*/
typedef struct{
    char *data_str;
    int len;
    cJSON *str;         //根节点
    char *topic;        //主题
}Alilot_t;

void mqtt_start(void);


#endif
