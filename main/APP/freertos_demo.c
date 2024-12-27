/**
 ****************************************************************************************************
 * @file        freertos.c
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

#include "freertos_demo.h"
/*FreeRTOS*********************************************************************************************/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/******************************************************************************************************/
/*FreeRTOS配置*/

/* TASK1 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK1_PRIO      1                   /* 任务优先级 */
#define TASK1_STK_SIZE  5*1024              /* 任务堆栈大小 */
TaskHandle_t            Task1Task_Handler;  /* 任务句柄 */
void task1(void *pvParameters);             /* 任务函数 */

/******************************************************************************************************/

/**
 * @brief       FreeRTOS例程入口函数
 * @param       无
 * @retval      无
 */
void freertos_demo(void)
{
    /* 创建任务1 */
    // xTaskCreatePinnedToCore((TaskFunction_t )task1,                 /* 任务函数 */
    //                         (const char*    )"task1",               /* 任务名称 */
    //                         (uint16_t       )TASK1_STK_SIZE,        /* 任务堆栈大小 */
    //                         (void*          )NULL,                  /* 传入给任务函数的参数 */
    //                         (UBaseType_t    )TASK1_PRIO,            /* 任务优先级 */
    //                         (TaskHandle_t*  )&Task1Task_Handler,    /* 任务句柄 */
    //                         (BaseType_t     ) 0);                   /* 该任务哪个内核运行 */

}
