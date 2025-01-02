#ifndef ALILOT_OTA_H_
#define ALILOT_OTA_H_

#include "esp_err.h"
#include "esp_log.H"
#include "esp_https_ota.h"
#include "string.h"
#include "freertos/freertos.h"
#include "freertos/task.h"
#include "esp_crt_bundle.h"
typedef void(*alilot_ota_finish_callback_t)(int code);

/*设置阿里云OTA升级参数*/
esp_err_t alilot_ota_config(const char* url , alilot_ota_finish_callback_t f);

/*启动阿里云OTA升级*/
esp_err_t alilot_ota_start(void);
#endif
