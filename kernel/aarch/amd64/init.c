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
    init_thread();
    init_print();
    init_idt();

    // init_memory();
}