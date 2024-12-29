#ifndef _WIFI_H_
#define _WIFI_H_

#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_smartconfig.h"
#include "string.h"
#include "freertos/semphr.h" 
#include "APP/mqtt_alilot.h"
#include "freertos/event_groups.h"

#define EV_WIFI_CONNECTED_BIT           (1<<0)
#define EV_WIFI_DISCONNECTED_BIT        (1<<1)

#define WIFI_CONNECTED_BIT              EV_WIFI_CONNECTED_BIT
#define WIFI_FAIL_BIT                   EV_WIFI_DISCONNECTED_BIT
/*wifi连接状态*/
typedef enum {
    WIFI_EV_READY,              //WIFI MANAGER初始化完成
    WIFI_EV_CONNECT_SUCCESS,    //获取IP成功
    WIFI_EV_SNTP,               //EVSNTP联网成功
    WIFI_EV_CONNECT_TIMEOUT,    //连接超时
    WIFI_EV_DISCONNECTED,       //断开连接
    WIFI_EV_MAX,
} wifi_ev_t;

#define WIFI_SSID       "main"
#define WIFI_PASSWORD   "12345678"

void WIFI_TASK_INIT(void);


#endif
