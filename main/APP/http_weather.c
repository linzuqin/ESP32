#include "http_weather.h"

/*获取天气信息标志位*/
uint8_t Get_Weather_Flag = 0;
/*http连接任务句柄*/
esp_http_client_handle_t esp_http_client_handle;
Weather_t Weather_data;

/*打印解析出来的天气信息*/
void weather_data_LOGI(Weather_t data)
{
    ESP_LOGI(TAG,"**********location*********")
    ESP_LOGI(TAG,"id:%s",data.location.id);
    ESP_LOGI(TAG,"name:%s",data.location.name);
    ESP_LOGI(TAG,"country:%s",data.location.country);
    ESP_LOGI(TAG,"path:%s",data.location.path);
    ESP_LOGI(TAG,"timezone:%s",data.location.timezone);
    ESP_LOGI(TAG,"timezone_offset:%s",data.location.timezone_offset);
    ESP_LOGI(TAG,"**********now*********")
    ESP_LOGI(TAG,"text:%s",data.weather.text);
    ESP_LOGI(TAG,"code:%s",data.weather.code);
    ESP_LOGI(TAG,"temperature:%s",data.weather.temp);
    ESP_LOGI(TAG,"last_update:%s",data.last_update_time);
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
    cJSON *result_arr = cJSON_GetObjectItem(weather_data , "result");
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
    memcpy(weather_data.last_update_time,cJSON_GetObjectItem(result,"last_update")->valuestring,sizeof(cJSON_GetObjectItem(result,"last_update")->valuestring));
    
    /**********获取location数据**********/
    cJSON* location = cJSON_GetObjectItem(result,"location");
    weather_data.location.id = cJSON_GetObjectItem(location,"id")->valuestring;
    weather_data.location.name = cJSON_GetObjectItem(location,"name")->valuestring;
    weather_data.location.country = cJSON_GetObjectItem(location,"country")->valuestring;
    weather_data.location.path = cJSON_GetObjectItem(location,"path")->valuestring;
    weather_data.location.timezone = cJSON_GetObjectItem(location,"timezone")->valuestring;
    weather_data.location.timezone_offset = cJSON_GetObjectItem(location,"timezone_offset")->valuestring;

    /**********获取now数据**********/
    cJSON* now = cJSON_GetObjectItem(result,"now");
    weather_data.weather.text = cJSON_GetObjectItem(now,"text")->valuestring;
    weather_data.weather.code = cJSON_GetObjectItem(now,"code")->valuestring;
    weather_data.weather.temp = cJSON_GetObjectItem(now,"temperature")->valuestring;
    weather_data_LOGI(weather_data);
    cJSON_free(weather_data);
   __fail_exit:
        cJSON_free(weather_data);
        return;
}

/*http任务*/
void http_weathe_task(void)
{ 
    /*设置http连接参数*/
    esp_http_client_config_t http_client_cfg = {
        .url = MY_URL;
    };

    /*设置http句柄参数*/
    esp_http_client_handle = esp_http_client_init(&http_client_cfg);

    /*发送GET请求*/
    esp_http_client_set_method(esp_http_client_handle , HTTP_METHOD_GET);

    while(1)
    {
        Weather_data->data_len = 0;
        if(Get_Weather_Flag == 1)
        {
            esp_err_t err = esp_http_client_open(esp_http_client_handle , 0);
            if(err != ESP_OK)
            {
                ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
                //goto __fail_delay;
            }

            Weather_data->data_len = esp_http_client_fetch_headers(esp_http_client_handle);
            if(Weather_data->data_len < 0 || Weather_data->data_len > Weather_data->data_len )
            {
                ESP_LOGE(TAG, "DATA_LEN error");
                //goto __fail_delay;                
            }

            if(esp_http_client_read_response(esp_http_client_handle , Weather_data->data , RESPONSE_BODY_MAX_SIZE) < 0)
            {
                ESP_LOGE(TAG, "Failed to read response");
                //goto __fail_delay;        
            }

            ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %d",
            esp_http_client_get_status_code(esp_http_client_handle),     //获取响应状态信息
            esp_http_client_get_content_length(esp_http_client_handle)); //获取响应信息长度
            ESP_LOGI(TAG,"%s", Weather_data->data);
            cJSON_Weather_data_parse(weather_data->data);
            esp_http_client_close(esp_http_client_handle);  // 断开连接
            memset(&Weather_data->data, 0, sizeof(Weather_data->data));
        }
    }
}

void http_weather_get_start(void)
{
    xTaskCreatePinnedToCore(weather_task, "weather_task", 3072, NULL,3,NULL, 1);
}