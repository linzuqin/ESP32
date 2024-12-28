/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-12-01
 * @brief       FreeRTOS 任务创建与删除实验(动态方法)
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 ESP32-S3开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include "freertos_demo.h"
#include "APP/WIFI.h"
#include "APP/mqtt_alilot.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

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
            Alilot_mqtt_start();
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(1*1000));
    }

    while(1)
    {

        vTaskDelay(pdMS_TO_TICKS(1*1000));

    }
}
