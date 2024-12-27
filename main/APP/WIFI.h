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

#define WIFI_SSID       "HONGNIUDIANZI"
#define WIFI_PASSWORD   "15059176224"

void WIFI_Init(void);


#endif
