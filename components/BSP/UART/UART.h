#ifndef UART_H
#define UART_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void uart_init(uint32_t baud_rate);
int uart_send_data(const char* data);
int uart_receive_data(char* buffer, int max_len) ;

#ifdef __cplusplus
}
#endif

#endif // UART_H