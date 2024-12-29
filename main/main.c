
#include "main.h"
EventGroupHandle_t s_wifi_ev;

/**
 * @brief       程序入口
 * @param       无
 * @retval      无
 */
void app_main(void)
{
    esp_err_t ret;
    
    ret= nvs_flash_init();  /* 初始化NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    s_wifi_ev = xEventGroupCreate();

    WIFI_TASK_INIT();
    //freertos_demo();    /* 运行FreeRTOS例程 */
    while(1)
    {
        EventBits_t bits = xEventGroupWaitBits(s_wifi_ev,EV_WIFI_CONNECTED_BIT,pdTRUE,pdFALSE,pdMS_TO_TICKS(5000));
        if(bits&EV_WIFI_CONNECTED_BIT)
        {
            #if CONNECT_ALILOT
                Alilot_mqtt_start();
            #else
                http_weather_get_start();
            #endif
            
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(1*1000));
    }

    while(1)
    {

        vTaskDelay(pdMS_TO_TICKS(1*1000));

    }
}
