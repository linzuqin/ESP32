#include "myhttp.h"
#define TAG     "MyHttp"
static http_data_t http_data = {0};
static esp_http_client_handle_t http_client_handle = NULL;

static esp_err_t http_event_handle(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER");
            ESP_LOGI(TAG , "%.*s", evt->data_len, (char*)evt->data);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {
                ESP_LOGI(TAG,"%.*s", evt->data_len, (char*)evt->data);
                if(http_data.token_ack_flag == 0)
                {
                    cJSON* result_js = cJSON_Parse((char*)evt->data);
                    if (result_js != NULL) {
                        cJSON* code_js = cJSON_GetObjectItem(result_js , "code");
                        if(code_js != NULL)
                        {
                            http_data.result_code = code_js->valueint;
                        }
                        if(http_data.result_code == 0)
                        {
                            cJSON* info_js = cJSON_GetObjectItem(result_js , "info");
                            if(info_js != NULL)
                            {
                                cJSON* token_js = cJSON_GetObjectItem(info_js , "token");
                                if(token_js != NULL && token_js->valuestring != NULL)
                                {
                                    http_data.token = token_js->valuestring;
                                    http_data.token_ack_flag = 1;
                                }
                            }
                        }
                        cJSON_Delete(result_js);
                    }
                }
            }
 
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            break;
        default:
            break;
    }
    return ESP_OK;
}

/*哈希函数*/
/*通过散列算法将不定长消息输出固定长度数据输出*/
static void calc_hmd5(char* key,char *content,unsigned char *output)
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

static void core_hex2str(uint8_t *input, uint32_t input_len, char *output, uint8_t lowercase)
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

/**
 * @brief Get the client ID based on the device's MAC address.
 *
 * This function retrieves the MAC address of the device, formats it as a string,
 * and returns it as the client ID.
 *
 * @return A pointer to the client ID string.
 */
static char * get_clientid(void)
{
    uint8_t mac[8];
    static char client_id[32] = {0};
    esp_wifi_get_mac(WIFI_IF_STA,mac);
    snprintf(client_id,sizeof(client_id),"%02X%02X%02X%02X%02X%02X",
    mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    return client_id;
}

/**
 * @brief This function retrieves a token from the server.
 * 
 * Steps:
 * 1. Create and initialize the HTTP client configuration structure.
 * 2. Initialize the HTTP client handle.
 * 3. Set the HTTP headers for the request.
 * 4. Create the JSON body for the request.
 * 5. Add the current timestamp, product key, device name, and client ID to the JSON body.
 * 6. Calculate the HMAC-MD5 signature and add it to the JSON body.
 * 7. Set the JSON body as the POST field for the HTTP client.
 * 8. Perform the HTTP POST request.
 * 9. Log the HTTP response status and content length.
 */
static void Myhttp_Get_token(void)
{
    /*step1：创建结构体 并初始化参数*/
    esp_http_client_config_t config = {
        .method = HTTP_METHOD_POST,
        .url = "/auth",
        .host = HTTP_URL,
        .user_data = http_data.rx,
        .event_handler = http_event_handle,
    };
    http_data.token_ack_flag = 0;
    /*step2:初始化句柄*/
    http_client_handle = esp_http_client_init(&config);

    /*step3:设置句柄连接参数*/
    esp_http_client_set_header(http_client_handle , "Content-Type" , "application/json");
    esp_http_client_set_header(http_client_handle , "Content-Length" , "214");

    /*获取body*/
    /*创建json节点*/
    cJSON* body_js = cJSON_CreateObject();

    /*time*/
    char time_str[16];
    time_t t = time(0);
    snprintf(time_str,16,"%lld000",t);
    cJSON_AddStringToObject(body_js , "timestamp" , time_str);

    /*product Key*/
    cJSON_AddStringToObject(body_js , "ProductKey" , ProductKey);

    /*DeviceName*/
    cJSON_AddStringToObject(body_js , "deviceName" , ALILOT_DEVICE_NAME);

    /*clientld*/
    cJSON_AddStringToObject(body_js , "clientId" , get_clientid());

    char *body_str = cJSON_PrintUnformatted(body_js);
    cJSON_Delete(body_js);

    /*sign*/
    static char str_password[33];
    char sign_content[256];
    unsigned char password[16];
    snprintf(sign_content,256,"clientId%sdeviceName%sproductKey%stimestamp%s",
    get_clientid(),ALILOT_DEVICE_NAME,ProductKey,time_str);
    calc_hmd5(DeviceSecret,sign_content,password);
    core_hex2str(password,16,str_password,0);
    cJSON_AddStringToObject(body_js , "sign" , str_password);

    esp_http_client_set_post_field(http_client_handle , body_str , strlen(body_str));

    /*发送*/
    esp_err_t err = esp_http_client_perform(http_client_handle);
    if (err == ESP_OK)
    {
        ESP_LOGI(TAG, "HTTP POST Status = %d, content_length = %" PRId64 "",
                 esp_http_client_get_status_code(http_client_handle),
                 esp_http_client_get_content_length(http_client_handle));
    }

    cJSON_free(body_str);
}

static void myhttp_task(void *params)
{
    uint8_t attemp = 0;
    uint8_t attemp_max_num = 10;
    while(http_data.result_code == 0 && attemp <= attemp_max_num)
    {
        Myhttp_Get_token();
        attemp ++;
        vTaskDelay(pdMS_TO_TICKS(1*1000));
    }

    if(attemp > attemp_max_num)
    {
        ESP_LOGE(TAG,"TOKEN GET FAIL");
    }
}

/**
 * @brief Starts the HTTP task.
 *
 * This function creates and starts a FreeRTOS task that runs the `myhttp_task` function.
 * The task is pinned to no specific core and has a stack size of 1024 bytes.
 *
 * @param None
 * @return None
 */
void My_http_start(void)
{
    xTaskCreatePinnedToCore(myhttp_task, "myhttp_run", 1024, NULL,3, NULL, tskNO_AFFINITY);
}

