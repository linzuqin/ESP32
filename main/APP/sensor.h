#ifndef _SENSOR_H_
#define _SENSOR_H_
#include "driver/temperature_sensor.h"
#include <driver/rmt.h>
#include <soc/rmt_reg.h>
#include "driver/gpio.h" 
#include <esp_log.h>

#define TEMP_MIN        10              //温度测量最低温度
#define TEMP_MAX        50              //温度测量最高温度

/*内部温湿度传感器初始化*/
void temp_init(void);

/*获取内部温湿度传感器值*/
float temp_sensor_get(void);

/* 引脚定义 */
#define DHT11_DQ_GPIO_PIN       GPIO_NUM_0

/* DHT11引脚高低电平枚举 */
typedef enum 
{
    DHT11_PIN_RESET = 0u,
    DHT11_PIN_SET
}DHT11_GPIO_PinState;

/*传感器数据结构体*/
typedef struct{
    double dht11_temp;         //dht11温度
    double dht11_humi;         //dht11湿度
    double internal_temp;      //内部温度
    double internal_humi;      //内部湿度
}sensor_t;
/* IO操作 */
#define DHT11_DQ_IN     gpio_get_level(DHT11_DQ_GPIO_PIN)   /* 数据端口输入 */

/* DHT11端口定义 */
#define DHT11_DQ_OUT(x) do{ x ?                                                 \
                            gpio_set_level(DHT11_DQ_GPIO_PIN, DHT11_PIN_SET) :  \
                            gpio_set_level(DHT11_DQ_GPIO_PIN, DHT11_PIN_RESET); \
                        }while(0)

/* 函数声明 */
void dht11_reset(void);                                 /* 复位DHT11 */
uint8_t dht11_init(void);                               /* 初始化DHT11 */
uint8_t dht11_check(void);                              /* 等待DHT11的回应 */
uint8_t dht11_read_data(double *temp, double *humi);   /* 读取温湿度 */


#endif
