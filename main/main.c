
#include "main.h"
EventGroupHandle_t s_wifi_ev;
QueueHandle_t sign ;
init_t device_init;
sensor_t my_sensor_data;
#define TAG "main"
/**
 * @brief       程序入口
 * @param       无
 * @retval      无
 */
void app_main(void)
{
    esp_err_t ret;
    sign = xSemaphoreCreateMutex();

    ret= nvs_flash_init();  /* 初始化NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_LOGI(TAG,"ESP CURRENTI VERSION:%s",Get_app_version());
    s_wifi_ev = xEventGroupCreate();

    /*DHT11初始化*/
    ret = dht11_init();
    if(ret != 0)
    {
        ESP_LOGE(TAG,"DHT11 INIT FAIL");
        device_init.dht11_init_flag = 0;
    }else{
        ESP_LOGI(TAG,"DHT11 INIT FINISH");
        device_init.dht11_init_flag = 1;
    }

    /*WIFI连接初始化*/
    WIFI_TASK_INIT();
    //freertos_demo();    /* 运行FreeRTOS例程 */
    while(1)
    {
        EventBits_t bits = xEventGroupWaitBits(s_wifi_ev,EV_WIFI_CONNECTED_BIT,pdTRUE,pdFALSE,pdMS_TO_TICKS(5000));
        if(bits&EV_WIFI_CONNECTED_BIT)
        {
                Alilot_mqtt_start();
                http_weather_get_start();       
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(1*1000));
    }

    while(1)
    {
        esp_initialize_sntp();
        if(device_init.dht11_init_flag == 1)
        {
            dht11_read_data(&my_sensor_data.dht11_temp,&my_sensor_data.dht11_humi);
        }
        vTaskDelay(pdMS_TO_TICKS(1*1000));

    }
}
