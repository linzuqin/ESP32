#include "UART.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "driver/uart.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define UART_NUM UART_NUM_0
#define BUF_SIZE 512
#define USART_TX_GPIO_PIN GPIO_NUM_43 
#define USART_RX_GPIO_PIN GPIO_NUM_44 /* 串口接收相关定义 */ 
static const char *TAG = "UART";

void UART_TASK(void*params)
{
    uint16_t len = 0;
    while(1)
    {
        uart_get_buffered_data_len(UART_NUM, (size_t*)&len);
        if(len > 0)
        {
            char *data = (char*)malloc(len + 1);
            uart_read_bytes(UART_NUM, (uint8_t*)data, len, pdMS_TO_TICKS(1000));
            data[len] = '\0';
            //ESP_LOGI(TAG, "UART received data: %s", data);
            free(data);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void uart_init(uint32_t baud_rate) {
    const uart_config_t uart_config = {
        .baud_rate = baud_rate,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(UART_NUM, &uart_config));

    // Set UART pins (using UART0 default pins ie no changes.)
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM, USART_TX_GPIO_PIN, USART_RX_GPIO_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    // Install UART driver, and get the queue.
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0));

    ESP_LOGI(TAG, "UART initialized successfully");

    xTaskCreatePinnedToCore(UART_TASK,"UART_TASK",1024,NULL,3,NULL,0);
}
int uart_send_data(const char* data) {
    int len = strlen(data);
    int txBytes = uart_write_bytes(UART_NUM, data, len);
    if (txBytes != len) {
        ESP_LOGE(TAG, "UART send data error");
        return -1;
    }
    ESP_LOGI(TAG, "UART send data: %s", data);
    return txBytes;
}

int uart_receive_data(char* buffer, int max_len) {
    int rxBytes = uart_read_bytes(UART_NUM, (uint8_t*)buffer, max_len, pdMS_TO_TICKS(1000));
    if (rxBytes < 0) {
        ESP_LOGE(TAG, "UART receive data error");
        return -1;
    }
    buffer[rxBytes] = '\0'; // Null-terminate the received data
    ESP_LOGI(TAG, "UART received data: %s", buffer);
    return rxBytes;
}