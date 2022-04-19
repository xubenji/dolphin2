#include "amd64/trap.h"
#include "amd64/memory.h"
#include "debug.h"
#include "printk.h"
#include "amd64/trap.h"
#include "amd64/init.h"
#include "task.h"

void test()
{
    while (1)
    {
        for (int i = 0; i < 1000000; i++)
        {
            /* code */
        }
        
        printk("yes");
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
    create_task("1111", KERNEL, &test, -1);
    enable_interruption();
}