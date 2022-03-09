#include "arm/uart.h"
#include "arm/lib.h"
#include "arm/memory.h"
#include "printk.h"
#include "stdint.h"
#include "task.h"

void init_all()
{
    init_uart();
    printk("test!!!!!");

    printk("We current at level: %d\n", (uint64_t)get_el());
    uint64_t * p = 0x600000;
    *p = 250;
    init_memory();
    printk("teste2\n");
    while (1)
    {
        /* code */
    }
    
    init_thread();
    init_timer();
    enable_irq();
    while (1)
    {
        for (int i = 0; i < 100; i++)
        {
            /* code */
        }
        printk(" T000 ");
        /* code */
    }
}
