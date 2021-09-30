#include "arm/uart.h"

void puts(char * str){
    uart_puts(str);
}