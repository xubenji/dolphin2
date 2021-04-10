#include "arm/mini_uart.h"

void output(char* str){
    uart_init();

    uart_send_string(str);

    while (1) {
		uart_send(uart_recv());
    }
}