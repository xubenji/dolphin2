/*
#include "arm/mini_uart.h"

void output(char* str){
    uart_init();

    uart_send_string(str);

    while (1) {
		uart_send(uart_recv());
    }
}
*/

#include "arm/lfb.h"
#include "arm/uart.h"
#include "arm/lfb.h"
#include "arm/mbox.h"

void init(){
   uart_init();

    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message
    
    mbox[2] = MBOX_TAG_GETSERIAL;   // get serial number command
    mbox[3] = 8;                    // buffer size
    mbox[4] = 8;
    mbox[5] = 0;                    // clear output buffer
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST; 

   //uart_puts("hello");
   //lfb_init();
   //lfb_showpicture();
}