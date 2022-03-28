/**
 * Name:
 * Author: Benji Xu <benjixu2020@gmail.com>
 * Date: 2022-02-26 02:01:26
 * LastEditTime: 2022-02-26 02:17:15
 * LastEditors: Benji Xu
 * FilePath: /dolphin2/kernel/arch/arm/memory.c
 * Description: This is paging for arm64
 * 描述: 这是基于arm64的分页管理
 * 虚拟地址的 0x3f200000～0x3f200000+0x1044 无法使用，注意
 */

#include "arm/memory.h"
#include "printk.h"
#include "debug.h"
#include "stddef.h"
#include "task.h"
#include "malloc.h"

uint64_t pageSize = 0x200000; // 2mb

static struct page freeMemory;
extern char end;

void init_memory()
{
    printk("physical mem:%d\n", SIZE_MEM);

    uint64_t startMemory = 0x400000;
    uint64_t pages = SIZE_MEM / 2 - 2;
    ASSERT(pages > 0, "init_page(): memory is too small (memory must bigger than 4 MB)");

    uint64_t address = startMemory;
    pageHead = startMemory;

    /************************************************************************** 
     * 将所有的可以利用的物理页用单链表连接起来
     **************************************************************************/
    for (uint32_t i = 0; i < pages - 1; i++)
    {
        address = link_page(address, pageSize);
    }
    pageTail = address;
    pageTail->next = NULL;
}

void set_kernel_malloc(uint64_t ttbr1_el1, uint64_t directory1, uint64_t directory2, enum task_type program)
{
    if (program == KERNEL)
    {
        dir0.dirState = IN_USE;
        dir0.address = 0x82000;
        dir0.usedAmount = 1;
        dir0.attri = DIR0;
        dir0.next = 0; //只开启512gb虚拟内存空间

        dir1.dirState = IN_USE;
        dir1.address = 0x83000;
        dir1.usedAmount = 1;
        dir1.attri = DIR1;
        dir1.next = 0;

        dir2.dirState = IN_USE;
        dir2.address = 0x200000;
        dir2.usedAmount = 2;
        dir2.attri = DIR2;
        dir2.next = 0x200000 + 0x1000;

        pageInfor.dirAddress = 0x200000;
        pageHead = pageHead;
        pageInfor.virtualAddress = 2 * 1024 * 1024 * 2 + KERNEL_BASE;
    }
    else
    {
        set_task_malloc(ttbr1_el1, directory1, directory2);
    }
}

int get_page_attri(enum attributes attris)
{
    switch (attris)
    {
    case DIR2:
        return 0x405;
        break;
    case DIR1:
        return 0;
    default:
        return 0;
        break;
    }
}