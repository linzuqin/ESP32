#include "ntp_time.h"

#define TAG "NTP"
extern lv_ui guider_ui;


void digital_clock_1_timer(lv_timer_t *timer)
{
    struct tm timeinfo;
    time_t now_time;
    time(&now_time);                         // 获取网络时间, 64bit的秒计数     
    localtime_r(&now_time, &timeinfo);       // 转换成具体的时间参数
    clock_count_24(&timeinfo.tm_hour, &timeinfo.tm_min, &timeinfo.tm_sec);
    if (lv_obj_is_valid(guider_ui.time_text))
    {
            lv_dclock_set_text_fmt(guider_ui.time_text,"%02d:%02d:%02d",timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    }
}

void esp_initialize_sntp(void)
{
    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);    // 设置单播模式
    esp_sntp_setservername(0, "pool.ntp.org");	    // 设置访问服务器
    esp_sntp_setservername(1, "ntp.aliyun.com");
    esp_sntp_setservername(2, "210.72.145.44");     // 国家授时中心服务器 IP 地址

    esp_sntp_init();                                //初始化
        // //延时等待SNTP初始化完成
    do {
        vTaskDelay(100 / portTICK_PERIOD_MS);
    } while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET);

    setenv("TZ", "CST-8", 1);                   //东八区
    tzset();

}

/**
 * @brief 启动sntp获取网络时间
 * @param 无
 * @return 无
 * @note tm_mon: 从0开始            tm_year: 距离1900年的差值，默认是70
 *       tm_yday: 一年的过去的天数   tm_isdst: 是否为夏时制
 */
void sntp_task(void *param){
    time_t now;
    static bool digital_clock_timer_enabled = false;
    static struct tm timeinfo;

    esp_initialize_sntp();
    // 成功获取网络时间后停止NTP请求，不然设备重启后会造成获取网络时间失败的现象
    // 大概是服务器时根据心跳时间来删除客户端的，如果不是stop结束的客户端，下次连接服务器时就会出错
	esp_sntp_stop();
    ESP_LOGI(TAG  , "ESP NTP Finish");

    /*初始化时获取时间设置到LVGL界面上*/
    time(&now);                 // 获取网络时间, 64bit的秒计数     
    localtime_r(&now, &timeinfo);       // 转换成具体的时间参数
    lv_dclock_set_text_fmt(guider_ui.time_text,"%02d:%02d:%02d",timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    // char date_text[50];
    // sprintf(date_text,"%04d/%02d/%02d",timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday);
    lv_label_set_text_fmt(guider_ui.date_text , "%04d/%02d/%02d",timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday); 

    /*启动LVGL定时器 保证数字时钟能够自动运行*/
    if (!digital_clock_timer_enabled) {
        lv_timer_create(digital_clock_1_timer, 1000, NULL);
        digital_clock_timer_enabled = true;
    }

    while (1)
    {   
        time(&now);                         // 获取网络时间, 64bit的秒计数     
        tzset();                            // 更新本地C库时间
        localtime_r(&now, &timeinfo);       // 转换成具体的时间参数

        ESP_LOGI(TAG, "%4d-%02d-%02d %02d:%02d:%02d week:%d", timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, 
        timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, timeinfo.tm_wday); 

        vTaskDelay(600000 / portTICK_PERIOD_MS);
    }
}

void ntp_task_start(void)
{
    xTaskCreatePinnedToCore(sntp_task, "sntp_time_task", 4096, NULL,3, NULL, tskNO_AFFINITY);
}
