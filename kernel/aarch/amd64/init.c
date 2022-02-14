#include "amd64/trap.h"
#include "amd64/memory.h"
#include "debug.h"
#include "printk.h"
#include "amd64/trap.h"
#include "amd64/init.h"
#include "task.h"

//初始化所有服务
void init_all()
{
    disable_interruption();
    init_print();
    init_idt();
    init_thread();
    // init_memory();
    enable_interruption();
}