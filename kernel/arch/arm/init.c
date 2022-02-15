#include "arm/uart.h"
#include "arm/lib.h"
#include "printk.h"
#include "stdint.h"

void init_all(){
    init_uart();
    printk("test!!!!!");
    printk("We current at level: %d\n", (uint64_t)get_el());
    init_timer();
    enable_irq();
    while (1)
    {
        /* code */
    }
    
}

