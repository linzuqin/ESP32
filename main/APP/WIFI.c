#include "WIFI.h"
#define TAG     "WIFI"
static EventGroupHandle_t s_wifi_event_group;
extern EventGroupHandle_t s_wifi_ev;

/*wifi事件回调函数*/
void wifi_event_handle(void* event_handler_arg,
                                    esp_event_base_t event_base,
                                    int32_t event_id,
                                    void* event_data)
{
    static uint8_t timeout=0;      //重新连接次数
    if(event_base == WIFI_EVENT)
    {
        switch(event_id)
        {
            case WIFI_EVENT_STA_START:      //开始进行连接
                xEventGroupSetBits(s_wifi_ev,0);
                esp_wifi_connect();
                break;

            case WIFI_EVENT_STA_CONNECTED:  //连接成功
                ESP_LOGI(TAG,"ESP32 CONNECT TO WIFI SUCCESSFULLY");
                ESP_LOGI(TAG,"SSID:%s  PASSWORD:%s",WIFI_SSID,WIFI_PASSWORD);
                xEventGroupSetBits(s_wifi_ev,EV_WIFI_CONNECTED_BIT);
                break;

            case WIFI_EVENT_STA_DISCONNECTED:   //断开连接
                ESP_LOGI(TAG,"ESP32 WIFI DISCONNECT TIME:%d",timeout);
                xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
                xEventGroupSetBits(s_wifi_ev,EV_WIFI_DISCONNECTED_BIT);

                break;

            default:break;
        }
    }
    else if(event_base == IP_EVENT)
    {
        switch(event_id)
        {
            case IP_EVENT_STA_GOT_IP:   //获取到路由器分配的IP
                ESP_LOGI(TAG,"ESP32 GET IP SUCCESSFULLY");
                xEventGroupSetBits(s_wifi_event_group,WIFI_CONNECTED_BIT);

            default:break;

        }
    }
    else if(event_base == SC_EVENT)
    {
        switch(event_id)
        {
            case SC_EVENT_SCAN_DONE:        //扫描完成
                ESP_LOGI(TAG,"SC SCAN FINISH");
                break;

            case SC_EVENT_GOT_SSID_PSWD:    //从app中获取到了WiFi的ssid和password
            {
                smartconfig_event_got_ssid_pswd_t *data = (smartconfig_event_got_ssid_pswd_t *)event_data;
                wifi_config_t wifi_config = {0};
                snprintf((char *)wifi_config.sta.ssid , sizeof(wifi_config.sta.ssid),"%s",(char *)data->ssid);
                snprintf((char *)wifi_config.sta.password , sizeof(wifi_config.sta.password),"%s",(char *)data->password);
                wifi_config.sta.bssid_set = data->bssid_set;
                if(wifi_config.sta.bssid_set != 0)
                {
                    memcpy(wifi_config.sta.bssid,data->bssid,sizeof(data->bssid));
                    esp_wifi_disconnect();
                    esp_wifi_set_config(WIFI_IF_STA,&wifi_config);
                    esp_wifi_connect();
                }
                break;
            }

            case SC_EVENT_SEND_ACK_DONE:    //向APP应答接收完成
            {
                esp_smartconfig_stop();
                break;
            }
        }
    }
}

/*WIFI初始化*/
void WIFI_TASK(void * arg)
{
    /*初始化网卡*/
    ESP_ERROR_CHECK(esp_netif_init());

    /*初始化循环事件*/
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /*初始化sta模式*/
    esp_netif_create_default_wifi_sta();

    /*配置WIFI基础参数*/
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    /*注册WIFI连接事件*/
    esp_event_handler_register(WIFI_EVENT,ESP_EVENT_ANY_ID,wifi_event_handle,NULL);
    
    /*注册网络ip事件*/
    esp_event_handler_register(IP_EVENT,IP_EVENT_STA_GOT_IP,wifi_event_handle,NULL);

    /*注册smartconfig事件*/
    esp_event_handler_register(SC_EVENT,ESP_EVENT_ANY_ID,wifi_event_handle,NULL);

    /*配置sta模式参数*/
    wifi_config_t sta_cfg = {
        .sta.threshold.authmode = WIFI_AUTH_WPA2_PSK,   //配置加密模式
        .sta.pmf_cfg.capable = true,    //启用保护管理，增加安全性
        .sta.pmf_cfg.required = false,  //是否只连接启用了保护管理的设备
    };
    memset(sta_cfg.sta.ssid , 0 , sizeof(sta_cfg.sta.ssid));
    memcpy(sta_cfg.sta.ssid,WIFI_SSID,sizeof(WIFI_SSID));

    memset(sta_cfg.sta.password , 0 , sizeof(sta_cfg.sta.password));
    memcpy(sta_cfg.sta.password,WIFI_PASSWORD,sizeof(WIFI_PASSWORD));

    /*设置为sta模式*/
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

    /*设置sta参数*/
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA,&sta_cfg));

    /*启动WIFI*/
    esp_wifi_start();    
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,pdTRUE,pdFALSE,pdMS_TO_TICKS(5000));
        if(bits & WIFI_FAIL_BIT)
        {
            esp_wifi_connect(); //重连
        }
        if(bits & WIFI_CONNECTED_BIT)
        {

        }
    }
    vTaskDelete(NULL);
    /*选择smartconfig版本*/
    // esp_smartconfig_set_type(SC_TYPE_ESPTOUCH_AIRKISS);

    // smartconfig_start_config_t smart_config_cfg = SMARTCONFIG_START_CONFIG_DEFAULT();
    // esp_smartconfig_start(&smart_config_cfg);
}

void WIFI_TASK_INIT(void)
{
    s_wifi_event_group = xEventGroupCreate();
    xEventGroupSetBits(s_wifi_event_group,WIFI_FAIL_BIT);

    xTaskCreatePinnedToCore(WIFI_TASK, "wifi_manager", 4096, NULL, 1, NULL, tskNO_AFFINITY);
}