#include "ALILOT_OTA.h"

#define TAG "ALILOT_OTA"

/*OTA升级的http地址*/
static char alilot_ota_url[256];

/*OTA升级完成的回调函数*/
static alilot_ota_finish_callback_t s_ota_finish_f= NULL;

/*当前是否处于OTA升级标志位*/
static bool is_current_ota = false;

/*设置阿里云OTA升级url地址*/
esp_err_t alilot_ota_config(const char* url , alilot_ota_finish_callback_t f)
{
    memcpy(alilot_ota_url , url , strlen(url));
    s_ota_finish_f = f;
    return ESP_OK;
}

void alilot_ota_task(void *params)
{
    /*http客户端连接参数初始化*/
    esp_http_client_config_t http_cfg = {
        .url = alilot_ota_url,
        .timeout_ms = 10*1000,
        .crt_bundle_attach = esp_crt_bundle_attach,
        .keep_alive_enable = true,
    };

    /*配置ota升级参数*/
    esp_https_ota_config_t ota_cfg = {
        .http_config = &http_cfg,
    };

    esp_err_t err_code = ESP_OK;
    /*开始OTA升级*/
    ESP_LOGI(TAG,"OTA UPDATE START");
    err_code = esp_https_ota(&ota_cfg);
    if(err_code == ESP_OK)
    {
        if(s_ota_finish_f)
            s_ota_finish_f(0);
        vTaskDelay(pdMS_TO_TICKS(1500));
        esp_restart();
    }else{
        if(s_ota_finish_f)
            s_ota_finish_f(-1);
        is_current_ota = false;
        vTaskDelete(NULL);
    }
}

/*启动阿里云OTA升级*/
esp_err_t alilot_ota_start(void)
{
    /*若已在升级状态 则不进行升级*/
    if(is_current_ota)
        return ESP_FAIL;

    /*升级标志位赋值为true 表示开始升级*/
    is_current_ota = true;
    xTaskCreatePinnedToCore(alilot_ota_task , "alilot_ota",8192,NULL,4,NULL,1);
    return ESP_OK;
}