
#include "main.h"
EventGroupHandle_t s_wifi_ev;
QueueHandle_t sign ;
init_t device_init;
sensor_t my_sensor_data;
i2c_obj_t i2c0_master;

#define TAG "main"
/**
 * @brief       程序入口
 * @param       无
 * @retval      无
 */
void app_main(void)
{
    esp_err_t ret;
    
    ret = nvs_flash_init();             /* 初始化NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    i2c0_master = iic_init(I2C_NUM_0);  /* 初始化IIC0 */
    xl9555_init(i2c0_master);           /* IO扩展芯片初始化 */

    s_wifi_ev = xEventGroupCreate();
    sign = xSemaphoreCreateMutex();
    /*WIFI连接初始化*/
    WIFI_TASK_INIT();

    /*LVGL初始化*/
    LVGL_TASK_START();
    
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
            //dht11_read_data(&my_sensor_data.dht11_temp,&my_sensor_data.dht11_humi);
        }
        vTaskDelay(pdMS_TO_TICKS(1*1000));

    }
}
