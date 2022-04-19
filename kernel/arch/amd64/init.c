#include "amd64/trap.h"
#include "amd64/memory.h"
#include "debug.h"
#include "printk.h"
#include "amd64/trap.h"
#include "amd64/init.h"
#include "task.h"
#include "stddef.h"

void test()
{
    while (1)
    {
        /* code */

        for (int i = 0; i < 1000000; i++)
        {
            /* code */
        }
        uint64_t *p = 0x200000;
        *p = 0x55aa;
        printk(" test ");
    }
}

//初始化所有服务
void init_all()
{
    disable_interruption();
    init_print();
    init_idt();
    init_task();
    init_memory();
    uint64_t addr = &test;
    addr -= VIRTUAL_BASE_ADDR;
    create_task("1111", PROCESS, addr, -1);

    uint64_t *t = 0x600010;
    *t = 0x400000;
    *t += 0x83;

    enable_interruption();
}