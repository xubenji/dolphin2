#include "arm/uart.h"
#include "arm/lib.h"
#include "arm/memory.h"
#include "printk.h"
#include "stdint.h"
#include "task.h"
#include "arm/handler.h"

int test11()
{
    uint64_t x = 0x8888888;
    while (1)
    {
        /* code */
    }
    
    return 0;
}

void init_all()
{
    init_uart();
    printk("test!!!!!");

    printk("We current at level: %d\n", (uint64_t)get_el());

    init_memory();

//     uint64_t *page = 0x88000;
//     *page = *page | 1 << 6;

//     // page = 0x87000;
//     // *page = ((*page >> 10) << 10) + 0x447;

//     // page = 0x86000;
//     // *page = ((*page >> 10) << 10) + 0x447;

//    // load_ttbr0();

//     uint64_t *t = &test11;
//     uint64_t tt = t;
//     tt = (tt << 16) >> 16;
//     switch_el(tt);

//     uint64_t *p = 0x80000;
//     *p = 250;
    printk("We current at level: %d\n", (uint64_t)get_el());

    printk("teste2\n");

    set_process_malloc(0, 0, 0, KERNEL);
    malloc_page(2);

    uint64_t phy = processAddr.lastPhyAddress;
    uint64_t vir = processAddr.lastVirAddress;

    /* test code */
    uint64_t *test = 0x800000 + KERNEL_BASE;
    uint64_t *test2 = 0x600000 + KERNEL_BASE;
    *test = 12;
    *test2 = 13;

    while (1)
    {
        /* code */
    }

    init_task();
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
