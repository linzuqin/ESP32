/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-12-01
 * @brief       LVGL V8移植 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 ESP32-S3 开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "main.h"
#define TAG "main"
lv_ui guider_ui;

i2c_obj_t i2c0_master;
EventGroupHandle_t s_wifi_ev;
QueueHandle_t sign ;
init_t device_init;
sensor_t my_sensor_data;

/**
 * @brief       板级初始化
 * @param       无
 * @retval      无
 */
void board_init(void)
{
    uart_init(115200);
    esp_err_t ret;
    
    ret = nvs_flash_init();             /* 初始化NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    i2c0_master = iic_init(I2C_NUM_0);  /* 初始化IIC0 */
    xl9555_init(i2c0_master);           /* IO扩展芯片初始化 */
}

/**
 * @brief       程序入口
 * @param       无
 * @retval      无
 */
void app_main(void)
{
    board_init();                       /* 板级初始化 */
    lvgl_demo();                        /* 运行LVGL例程 */

    s_wifi_ev = xEventGroupCreate();
    sign = xSemaphoreCreateMutex();
    /*WIFI连接初始化*/
    WIFI_TASK_INIT();
    ESP_LOGI(TAG,"current version : %s",Get_app_version());

    while(1)
    {
        EventBits_t bits = xEventGroupWaitBits(s_wifi_ev,EV_WIFI_CONNECTED_BIT,pdTRUE,pdFALSE,pdMS_TO_TICKS(5000));
        if(bits&EV_WIFI_CONNECTED_BIT)
        {
            Alilot_mqtt_start();
            http_weather_get_start();   
            ntp_task_start();
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(1*10));
    }

    while(1)
    {
        if(device_init.dht11_init_flag == 1)
        {
            //dht11_read_data(&my_sensor_data.dht11_temp,&my_sensor_data.dht11_humi);
        }
        vTaskDelay(pdMS_TO_TICKS(1*10));

    }
}
  