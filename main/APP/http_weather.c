#include "http_weather.h"
#define TAG "HTTP"
/*获取天气信息标志位*/
uint8_t Get_Weather_Flag = 0;
/*http连接任务句柄*/
esp_http_client_handle_t esp_http_client_handle;
Weather_t Weather_data;
extern QueueHandle_t sign ;

char *weather_details[WEATHER_TYPE_NUM] = {"晴(国内白天)","晴(国内夜晚)","晴(国外白天)","晴(国外夜晚)","多云","晴间多云(白天)","晴间多云(夜晚)",
                            "大部多云(白天)","大部多云(夜晚)","阴","阵雨","雷阵雨","雷阵雨伴有冰雹","小雨","中雨","大雨","暴雨",
                            "大暴雨","特大暴雨","冻雨","雨夹雪","阵雪","小雪","中雪","大雪","暴雪","浮尘","扬沙","沙尘暴","强沙尘暴",
                            "雾","霾","风","大风","飓风","热带风暴","龙卷风","龙卷风","冷","热"};

/*打印解析出来的天气信息*/
void weather_data_LOGI(Weather_t data)
{
    struct tm timeinfo;

    ESP_LOGI(TAG,"**********location*********");
    ESP_LOGI(TAG,"id:%s",data.location.id);
    ESP_LOGI(TAG,"name:%s",data.location.name);
    ESP_LOGI(TAG,"country:%s",data.location.country);
    ESP_LOGI(TAG,"path:%s",data.location.path);
    ESP_LOGI(TAG,"timezone:%s",data.location.timezone);
    ESP_LOGI(TAG,"timezone_offset:%s",data.location.timezone_offset);
    ESP_LOGI(TAG,"**********now*********");
    ESP_LOGI(TAG,"text:%s",data.weather.text);
    ESP_LOGI(TAG,"code:%s",data.weather.code);
    ESP_LOGI(TAG,"details:%s",data.weather.details);
    ESP_LOGI(TAG,"temperature:%s",data.weather.temp);
    ESP_LOGI(TAG,"last_update:%s",data.last_update_time);
    time_t t=0;
    time(&t);                 // 获取网络时间, 64bit的秒计数     
    localtime_r(&t, &timeinfo);       // 转换成具体的时间参数
        // ESP_LOGI(TAG, "%4d-%02d-%02d %02d:%02d:%02d week:%d", timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, 
        // timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, timeinfo.tm_wday); 
    ESP_LOGI(TAG,"NOW_TIME:%4d-%02d-%02d %02d:%02d:%02d week:%d", timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, 
        timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, timeinfo.tm_wday);
}

/*天气数据解析*/
static void cJSON_Weather_data_parse(char *data)
{
    cJSON* weather_data = cJSON_Parse(data);

    if(weather_data == NULL)
    {
        ESP_LOGI(TAG,"weather_data error");
        goto __fail_exit;
    }

    /*获取result数组*/
    cJSON *result_arr = cJSON_GetObjectItem(weather_data , "results");
    if(result_arr == NULL)
    {
        ESP_LOGI(TAG,"can't find result_arr");
        goto __fail_exit;
    }

    /*获取result数据*/
    cJSON* result = cJSON_GetArrayItem(result_arr,0);
    if(result == NULL)
    {
        ESP_LOGI(TAG,"can't find result");
        goto __fail_exit;
    }
    
    /*获取上一次更新时间*/
    memcpy(Weather_data.last_update_time,cJSON_GetObjectItem(result,"last_update")->valuestring,strlen(cJSON_GetObjectItem(result,"last_update")->valuestring));
    
    /**********获取location数据**********/
    cJSON* location = cJSON_GetObjectItem(result,"location");
    Weather_data.location.id = cJSON_GetObjectItem(location,"id")->valuestring;
    Weather_data.location.name = cJSON_GetObjectItem(location,"name")->valuestring;
    Weather_data.location.country = cJSON_GetObjectItem(location,"country")->valuestring;
    Weather_data.location.path = cJSON_GetObjectItem(location,"path")->valuestring;
    Weather_data.location.timezone = cJSON_GetObjectItem(location,"timezone")->valuestring;
    Weather_data.location.timezone_offset = cJSON_GetObjectItem(location,"timezone_offset")->valuestring;

    /**********获取now数据**********/
    cJSON* now = cJSON_GetObjectItem(result,"now");
    Weather_data.weather.text = cJSON_GetObjectItem(now,"text")->valuestring;
    Weather_data.weather.code = cJSON_GetObjectItem(now,"code")->valuestring;
    Weather_data.weather.temp = cJSON_GetObjectItem(now,"temperature")->valuestring;
    if(atoi(Weather_data.weather.code) >= 0 && atoi(Weather_data.weather.code) <= WEATHER_TYPE_NUM)
    {
        Weather_data.weather.details = weather_details[atoi(Weather_data.weather.code)];
    }else{
        Weather_data.weather.details="未知";
    }
    weather_data_LOGI(Weather_data);
    //cJSON_free(weather_data);
   __fail_exit:
        cJSON_Delete(weather_data);
        return;
}

/*http任务*/
void http_weathe_task( void * arg )
{ 
    /*设置http连接参数*/
    esp_http_client_config_t http_client_cfg = {
        .url = MY_URL,
    };

    /*设置http句柄参数*/
    esp_http_client_handle = esp_http_client_init(&http_client_cfg);

    /*发送GET请求*/
    esp_http_client_set_method(esp_http_client_handle , HTTP_METHOD_GET);
    while(1)
    {
        xSemaphoreTake(sign, portMAX_DELAY); /* 获取互斥信号量 */
        
        memset(Weather_data.data , 0 , DATA_MAX_LEN);
        memset(Weather_data.last_update_time , 0 , 50);

        Weather_data.data_len = 0;
        Get_Weather_Flag = 1;
        if(Get_Weather_Flag == 1)
        {
            esp_err_t err = esp_http_client_open(esp_http_client_handle , 0);
            if(err != ESP_OK)
            {
                ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
                goto __fail_delay;
            }

            Weather_data.data_len = esp_http_client_fetch_headers(esp_http_client_handle);
            if(Weather_data.data_len == 0 || Weather_data.data_len > DATA_MAX_LEN )
            {
                ESP_LOGE(TAG, "DATA_LEN error");
                goto __fail_delay;                
            }

            if(esp_http_client_read_response(esp_http_client_handle , Weather_data.data , DATA_MAX_LEN) < 0)
            {
                ESP_LOGE(TAG, "Failed to read response");
                goto __fail_delay;        
            }
            ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %lld",
            esp_http_client_get_status_code(esp_http_client_handle),     //获取响应状态信息
            esp_http_client_get_content_length(esp_http_client_handle)); //获取响应信息长度
            //ESP_LOGI(TAG,"%s", Weather_data.data);
            cJSON_Weather_data_parse(Weather_data.data);
            esp_http_client_close(esp_http_client_handle);  // 断开连接
            memset(&Weather_data.data, 0, sizeof(Weather_data.data));
        }
        xSemaphoreGive(sign); /* 释放互斥信号量 */
    __fail_delay:
        for (size_t i = 0; i < REQUEST_INTERVAL * 60; i++)
            vTaskDelay(1000 / portTICK_PERIOD_MS);    
            }
}

void http_weather_get_start(void)
{
    xTaskCreatePinnedToCore(http_weathe_task, "http_run", 8192, NULL,3, NULL, tskNO_AFFINITY);
}