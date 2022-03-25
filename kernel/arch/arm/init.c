#include "arm/uart.h"
#include "arm/lib.h"
#include "arm/memory.h"
#include "printk.h"
#include "stdint.h"
#include "task.h"
#include "arm/handler.h"

void test_print3()
{
    while (1)
    {
        // __asm__(
        //     "mrs x0, currentel"
        //     );

        for (int i = 0; i < 10000; i++)
        {
            /* code */
        }

        int tt = 0x1234;
    }
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

    // uint64_t phy = processAddr.lastPhyAddress;
    // uint64_t vir = processAddr.lastVirAddress;

    // /* test code */
    // uint64_t *test = 0x800000 + KERNEL_BASE;
    // uint64_t *test2 = 0x600000 + KERNEL_BASE;
    // *test = 12;
    // *test2 = 13;

    init_task();

    uint64_t print3 = &test_print3;
    create_task("4444", PROCESS, print3 - KERNEL_BASE, -1);

    uint64_t *t = 0x800000;
    *t = 0x405 | 1 << 6;

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
