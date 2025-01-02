#include "mqtt_alilot.h"

static esp_mqtt_client_handle_t mqtt_hanlde;
static uint16_t data_id = 0;        //每条消息的ID
extern QueueHandle_t sign ;

#define TAG     "MQTT"

/*阿里证书*/
const char* g_aliot_ca = "-----BEGIN CERTIFICATE-----\n"
"MIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkG"
"A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv"
"b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAw"
"MDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i"
"YWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxT"
"aWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZ"
"jc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavp"
"xy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp"
"1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdG"
"snUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJ"
"U26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N8"
"9iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8E"
"BTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0B"
"AQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOz"
"yj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE"
"38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymP"
"AbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUad"
"DKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbME"
"HMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A==\n"
"-----END CERTIFICATE-----";

void matt_ota_callback(int code)
{
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root , "id" , "OTA_UPDATE");
    cJSON *params = cJSON_AddObjectToObject(root , "params");
    char code_str[4];
    sprintf(code_str,"%d",code);
    cJSON_AddStringToObject(params,"step",code_str);
    char desc[128];
    switch(code)
    {
        case -1:memcpy(desc,"升级失败",sizeof("升级失败"));break;
        case -2:memcpy(desc,"下载失败",sizeof("下载失败"));break;
        case -3:memcpy(desc,"校验失败",sizeof("校验失败"));break;
        case -4:memcpy(desc,"烧写失败",sizeof("烧写失败"));break;
        default:memcpy(desc,"升级成功",sizeof("升级成功"));break;
    }
    cJSON_AddStringToObject(params,"desc",desc);

    char * data_str = cJSON_PrintUnformatted(root);
    ESP_LOGI(TAG,"TOPIC->%s , payload->%s",OTA_PROCESS_TOPIC,data_str);
    esp_mqtt_client_publish(mqtt_hanlde , OTA_PROCESS_TOPIC , data_str , strlen(data_str) , 1,0);

    cJSON_free(data_str);
    cJSON_Delete(root);
}   

void mqtt_event_callback(void* event_handler_arg,
                                    esp_event_base_t event_base,
                                    int32_t event_id,
                                    void* event_data)
{
    esp_mqtt_event_handle_t data = (esp_mqtt_event_handle_t)event_data;
    switch(event_id)
    {
        case MQTT_EVENT_CONNECTED:      //MQTT连接成功
            ESP_LOGI(TAG,"MQTT CONNECT SUCCESSFULLY");
            Alilot_post_version(Get_app_version());

            /*订阅主题*/
            esp_mqtt_client_subscribe_single(mqtt_hanlde,OTA_UPGRADE_TOPIC,1);
            break;
        
        case MQTT_EVENT_DISCONNECTED:   //MQTT断开连接
            ESP_LOGI(TAG,"MQTT DISCONNECT");
            break;
        
        case MQTT_EVENT_PUBLISHED:      //MQTT服务器下发数据
            ESP_LOGI(TAG,"MQTT PUB...");
            break;

        case MQTT_EVENT_SUBSCRIBED:     //MQTT服务器上报
            ESP_LOGI(TAG,"MQTT SUB...");
            break;

        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG,"TOPIC:%s",data->topic);
            ESP_LOGI(TAG,"DATA: %s",data->data);
            if(strstr(data->topic , "/property/set"))
            {

            }
            break;

    }
}

char * get_clientid(void)
{
    uint8_t mac[8];
    static char client_id[32] = {0};
    esp_wifi_get_mac(WIFI_IF_STA,mac);
    snprintf(client_id,sizeof(client_id),"%02X%02X%02X%02X%02X%02X",
    mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    return client_id;
}

/*哈希函数*/
/*通过散列算法将不定长消息输出固定长度数据输出*/
void calc_hmd5(char* key,char *content,unsigned char *output)
{
    mbedtls_md_context_t md5_ctx;
    const mbedtls_md_info_t *md_info = mbedtls_md_info_from_type(MBEDTLS_MD_MD5);

    mbedtls_md_init(&md5_ctx);
    mbedtls_md_setup(&md5_ctx, md_info, 1);
    mbedtls_md_hmac_starts(&md5_ctx,(unsigned char *)key,strlen(key));
    mbedtls_md_hmac_update(&md5_ctx,(unsigned char *)content,strlen(content));
    mbedtls_md_hmac_finish(&md5_ctx,output);
    mbedtls_md_free(&md5_ctx);
}

void core_hex2str(uint8_t *input, uint32_t input_len, char *output, uint8_t lowercase)
{
    char *upper = "0123456789ABCDEF";
    char *lower = "0123456789abcdef";
    char *encode = upper;
    int i = 0, j = 0;

    if (lowercase) {
        encode = lower;
    }

    for (i = 0; i < input_len; i++) {
        output[j++] = encode[(input[i] >> 4) & 0xf];
        output[j++] = encode[(input[i]) & 0xf];
    }
    output[j] = 0;
}

/*根据事件类型创建数据结构体*/
static Alilot_t *Alilot_Creat_data(ALIOT_TYPE event)
{
    Alilot_t* data = (Alilot_t*)malloc(sizeof(Alilot_t));
    if(data)
    {
        memset(data,0,sizeof(Alilot_t));
        data->root = cJSON_CreateObject();
        char id[10];
        snprintf(id,10,"%d",data_id++);
        cJSON_AddStringToObject(data->root,"id",id);
        cJSON_AddStringToObject(data->root,"version","1.0");
        cJSON* sys_item = cJSON_AddObjectToObject(data->root , "sys");
        cJSON_AddNumberToObject(sys_item , "ack" , 0);
        switch(event)
        {
            case ALIOT_data_POST:      //常规属性上报
                cJSON_AddObjectToObject(data->root,"params");
                cJSON_AddStringToObject(data->root,"method","thing.event.property.post");
                break;
            case ALIOT_data_SET_ACK:   //属性设置回复
                cJSON_AddObjectToObject(data->root,"data");
                break;
            case ALIOT_data_EVENT:     //事件上报
                cJSON_AddObjectToObject(data->root,"params");
                break;
            case ALILOT_OTA_VERSION:
                cJSON_AddObjectToObject(data->root,"params");
                break;
            default:break;
        }
        
        return data;
    }
    return NULL;

}

/*将数据结构转为字符串*/
static void Alilot_generate_str(Alilot_t *data)
{
    if(data)    //确保数据结构体存在
    {
        if(data->data_str)  //若数组不为空
        {
            cJSON_free(data->data_str);
            data->data_str = NULL;
        }
        data->data_str = cJSON_PrintUnformatted(data->root);
        data->len = strlen(data->data_str);
    }
}

/*阿里云数据释放*/
static void Alilot_Free(Alilot_t *data)
{
    if(data)
    {
        if(data->data_str)              //若数组不为空
        {
            ESP_LOGI(TAG,"data_str free : %s",data->data_str);
            cJSON_free(data->data_str);
        }
        if(data->root)                   //若还存在根节点
        {
            //ESP_LOGI(TAG,"str Delet : %s",data->root);
            cJSON_Delete(data->root);
        }
    }
}

/*向阿里云数据结构体中添加整形类型数据*/
static void Alilot_Data_Add_int(Alilot_t* data,const char* name, int value)
{
    if(data)            //若传入的数据结构体不为空
    {
        cJSON* Data_params = cJSON_GetObjectItem(data->root,"params");
        if(Data_params)         //若成功获取params
        {
            cJSON* num_item = cJSON_AddObjectToObject(data->root,name);
            cJSON_AddNumberToObject(num_item , "value" , value);
            cJSON_AddNumberToObject(num_item , "time" , time(0)*1000ull);

        }
    }
}

/*向阿里云数据结构体中添加字符串类型数据*/
static void Alilot_Data_Add_str(Alilot_t* data,const char* name, const char * value)
{
    if(data)            //若传入的数据结构体不为空
    {
        cJSON* Data_params = cJSON_GetObjectItem(data->root,"params");
        if(Data_params)         //若成功获取params
        {
            cJSON* str_item = cJSON_AddObjectToObject(data->root,name);
            cJSON_AddStringToObject(str_item , "value" , value);
            cJSON_AddNumberToObject(str_item , "time" , time(0)*1000ull);

        }
    }
}

/*向阿里云数据结构体中添加浮点类型数据*/
static void Alilot_Data_Add_double(Alilot_t* data,const char* name, double value)
{
    if(data)            //若传入的数据结构体不为空
    {
        cJSON* Data_params = cJSON_GetObjectItem(data->root,"params");
        if(Data_params)         //若成功获取params
        {
            cJSON* num_item = cJSON_AddObjectToObject(data->root,name);
            cJSON_AddNumberToObject(num_item , "value" , value);
            cJSON_AddNumberToObject(num_item , "time" , time(0)*1000ull);

        }
    }
}

/*向阿里云服务器上报整型数据*/
void Aliot_post_property_int(const char* name,int value)
{
    Alilot_t *data = Alilot_Creat_data(ALIOT_data_POST);
    Alilot_Data_Add_int(data , name , value);
    Alilot_generate_str(data);
    esp_mqtt_client_publish(mqtt_hanlde , POST_TOPIC , data->data_str , data->len,1,0);
    Alilot_Free(data);
}

/*向阿里云服务器上报浮点型数据*/
void Aliot_post_property_double(const char* name,double value)
{
    Alilot_t *data = Alilot_Creat_data(ALIOT_data_POST);
    Alilot_Data_Add_double(data , name , value);
    Alilot_generate_str(data);
    esp_mqtt_client_publish(mqtt_hanlde , POST_TOPIC , data->data_str , data->len,1,0);
    Alilot_Free(data);
}

/*向阿里云服务器上报字符串数据*/
void Aliot_post_property_str(const char* name,char* value)
{
    Alilot_t *data = Alilot_Creat_data(ALIOT_data_POST);
    Alilot_Data_Add_str(data , name , value);
    Alilot_generate_str(data);
    esp_mqtt_client_publish(mqtt_hanlde , POST_TOPIC , data->data_str , data->len,1,0);
    Alilot_Free(data);
}

/*返回当前版本号*/
const char* Get_app_version(void)
{
    static char app_version[32];
    if(app_version[0] == 0)
    {
        const esp_partition_t *running = esp_ota_get_running_partition();
        esp_app_desc_t running_desc;
        esp_ota_get_partition_description(running,&running_desc);
        memcpy(app_version , running_desc.version,strlen(running_desc.version));
    }   
    return app_version;
}

/*向mqtt数据结构体中添加版本号节点*/
static void Alilot_Add_ota_version(Alilot_t* data,const char* version)
{
    if(data)
    {
        cJSON* param = cJSON_GetObjectItem(data->root , "params");
        if(param)
        {
            cJSON_AddStringToObject(param,"version",version);
        }
    }
}

/*向平台上报版本号*/
void Alilot_post_version(const char* version)
{
    Alilot_t *data = Alilot_Creat_data(ALILOT_OTA_VERSION);
    Alilot_Add_ota_version(data,version);
    Alilot_generate_str(data);
    esp_mqtt_client_publish(mqtt_hanlde , OTA_VERSION_TOPIC , data->data_str , data->len,1,0);
    Alilot_Free(data);
}

void Alilot_mqtt_run(void * arg )
{
    /*配置mqtt连接参数*/
    esp_mqtt_client_config_t mqtt_cfg={0};
    mqtt_cfg.broker.address.uri = MQTT_URL;
    mqtt_cfg.broker.address.port = 1883;

    /*获取client_id*/
    char client_id[128];
    snprintf(client_id,sizeof(client_id),"%s|securemode=2,signmethod=hmacmd5|",get_clientid());
    mqtt_cfg.credentials.client_id = client_id;

    /*获取username*/
    char username[128];
    snprintf(username,sizeof(username),"%s&%s",ALILOT_DEVICE_NAME,ProductKey);
    mqtt_cfg.credentials.username = username;

    /*获取password*/
    char sign_content[256];
    snprintf(sign_content,sizeof(sign_content),"clientId%sdeviceName%sproductKey%s",get_clientid(),ALILOT_DEVICE_NAME,ProductKey);
    unsigned char password_hex[16];    //计算出来的哈希值
    char password_str[33];              //最终计算出来的password
    calc_hmd5(DeviceSecret,sign_content,password_hex);
    core_hex2str(password_hex , 16 , password_str,0);
    mqtt_cfg.credentials.authentication.password = password_str;

    ESP_LOGI(TAG,"aliot connect->clientId:%s,username:%s,password:%s",client_id,username,password_str);

    /*TLS证书*/
    mqtt_cfg.broker.verification.certificate = g_aliot_ca;

    /*初始化mqtt连接句柄*/
    mqtt_hanlde = esp_mqtt_client_init(&mqtt_cfg);

    /*注册mqtt事件回调函数*/
    esp_mqtt_client_register_event(mqtt_hanlde,ESP_EVENT_ANY_ID,mqtt_event_callback,mqtt_hanlde);

    /*启动mqtt连接*/
    esp_mqtt_client_start(mqtt_hanlde);

    while(1)
    {
        xSemaphoreTake(sign, portMAX_DELAY); /* 获取互斥信号量 */


        xSemaphoreGive(sign); /* 释放互斥信号量 */
        vTaskDelay(60*1000/portTICK_PERIOD_MS);
    }
}

void Alilot_mqtt_start(void)
{
    xTaskCreatePinnedToCore(Alilot_mqtt_run, "aliot_run", 4096, NULL,3, NULL, tskNO_AFFINITY);
}

