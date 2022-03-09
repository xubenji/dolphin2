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
#include "arm/mapping.h"
#include "printk.h"
#include "debug.h"
#include "stddef.h"
#include "debug.h"

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
    for (uint32_t i = 0; i < pages - 1; i++)
    {
        address = link_page(address, pageSize);
    }
    pageTail = address;
    pageTail->next = NULL;

    init_malloc(0, 0, 0, KERNEL);
    malloc_page(500);
}

static void free_region(uint64_t v, uint64_t e)
{
    for (uint64_t start = PA_UP(v); start + PAGE_SIZE <= e; start += PAGE_SIZE)
    {
        if (start + PAGE_SIZE <= MEMORY_END)
        {
            kfree(start);
        }
    }
}

uint64_t link_page(uint64_t address, uint64_t offset)
{
    struct page *p = address;
    p->next = address + offset;
    return address + offset;
}
