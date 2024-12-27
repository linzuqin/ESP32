#include "mqtt_alilot.h"

static esp_mqtt_client_handle_t mqtt_hanlde;

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
// void mqtt_event_callback(void* event_handler_arg,
//                                     esp_event_base_t event_base,
//                                     int32_t event_id,
//                                     void* event_data)
// {
//     esp_mqtt_event_handle_t data = (esp_mqtt_event_handle_t)event_data;
//     switch(event_id)
//     {
//         case MQTT_EVENT_CONNECTED:      //MQTT连接成功
//             ESP_LOGI(TAG,"MQTT CONNECT SUCCESSFULLY");
//             break;
        
//         case MQTT_EVENT_DISCONNECTED:   //MQTT断开连接
//             ESP_LOGI(TAG,"MQTT DISCONNECT");
//             break;
        
//         case MQTT_EVENT_PUBLISHED:      //MQTT服务器下发数据
//             ESP_LOGI(TAG,"MQTT PUB...");
//             break;

//         case MQTT_EVENT_SUBSCRIBED:     //MQTT服务器上报
//             ESP_LOGI(TAG,"MQTT SUB...");
//             break;

//         case MQTT_EVENT_DATA:
//             ESP_LOGI(TAG,"TOPIC:%s",data->topic);
//             ESP_LOGI(TAG,"DATA: %s",data->data);
//             break;

//     }
// }

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

void mqtt_start(void)
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
    //esp_mqtt_client_register_event(mqtt_hanlde,ESP_EVENT_ANY_ID,mqtt_event_callback,NULL);

    /*启动mqtt连接*/
    esp_mqtt_client_start(mqtt_hanlde);
}
