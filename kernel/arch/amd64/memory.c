/*
 * Name: memory.c
 * Author: Benji Xu <benjixu2020@gmail.com>
 * Date: 2021-10-29 21:06:10
 * LastEditTime: 2021-12-29 23:55:28
 * LastEditors: Benji Xu
 * FilePath: /dolphin2/kernel/aarch/amd64/memory.c
 * Description: memory manage subsystem in x86_x64, we use the 2m page.
 * 描述: 应用在x86_x64指令集下的内存管理，我们使用2mb的页大小。
 */
#include "amd64/memory.h"
#include "printk.h"
#include "debug.h"
#include "stddef.h"
#include "amd64/mapping.h"

uint64_t pageSize = 0x200000; //2mb

static struct free_mem_region FreeMemRegion[50];

/**
 * @function: init_memory
 * @param [null]
 * @return [null]
 * description: Init the memory, collecting the memory information and put it into the screen | 收集电脑内存信息，并且将信息打印到屏幕上
 */
void init_memory(void)
{
    int32_t count = *(int32_t *)0x9000;
    totalMemory = 0;
    struct E820 *mem_map = (struct E820 *)0x9008;
    int free_region_count = 0;

    ASSERT(count <= 50, "init_memory():");

    for (int32_t i = 0; i < count; i++)
    {
        if (mem_map[i].type == 1)
        {
            FreeMemRegion[free_region_count].address = mem_map[i].address;
            FreeMemRegion[free_region_count].length = mem_map[i].length;
            totalMemory += mem_map[i].length;
            free_region_count++;
        }
        printk("%x  %uKB  %u\n", mem_map[i].address, mem_map[i].length / 1024, (uint64_t)mem_map[i].type);
    }
    printk("Total memory is %uMB\n", totalMemory / 1024 / 1024);

    init_pages(totalMemory);

    init_malloc(0, 0, 0, KERNEL);
    malloc_page(513);
    free_page(3);
}

/**
 * @function: init_pages
 * @param [uint64_t] totalMemory: the total memory size in bytes. | 以字节来表示的内存大小
 * @return [null]
 * @description: Init the pages, using single link list to manage the free pages. | 初始化页，使用单链表来管理可以使用的页
 */
void init_pages(uint64_t totalMemory)
{
    /* 收集内存电脑内存信息，包括了可以使用的内存大小。
     * 在load.asm中，kernel已经使用了6mb的内存，所以ecx的大小是3。
     * collect the memory information, including the usable memory size.
     * In the load.asm, kernel used 6mb memory, so the ecx is 3.
    /*-----------------------------------------------------------------------*/
    uint16_t *ecx;
    ecx = 0x90000;
    uint64_t starMemory = *ecx * 1024 * 1024 * 2;
    uint64_t pages = (totalMemory / 1024 / 1024 / 2) - *ecx;
    ASSERT(pages > 2, "page_num(): memory is too small (memory < 4MB)");

    /* 映射机器的所有可以利用的物理页，
     *-----------------------------------------------------------------------*/
    map_all_physical_pages(pages);

    /* 将所有的可以利用的物理页用单链表连接起来
     *-----------------------------------------------------------------------*/
    uint64_t address = starMemory;
    pageHead = starMemory;
    for (uint32_t i = 0; i < pages; i++)
    {
        address = link_page(address, pageSize);
    }
    pageTail = address;
    pageTail->next = NULL;
}

/**
 * @function: map_all_physical_pages
 * @param [uint64_t] freePages: Usable phyical pages | 可以使用的物理页数量
 * @return [uint64_t]
 * @description: Mapping all usable physical pages, this is physical address,
 *              so that the kernel can access all phyical address.
 * 描述: 将所有可以使用的物理页映射，注意这里是映射的物理地址。
 *      这样操作完成以后内核可以访问所有的物理地址。
 */
uint64_t map_all_physical_pages(uint64_t freePages)
{
    if (freePages < 508)
    {
        return NULL;
    }
    else
    {
        uint32_t pages = (freePages - 508);
        pageDirAddress = 0x75000;
        for (uint64_t i = 0; i <= (freePages - 512) / 512; i++)
        {
            pageDirAddress = 0x75000 + 0x1000 * i; //在load.asm中 0x70000～0x74000已经被映射完了，所以我们这里从0x7500开始。
            uint64_t *FirstDir0x71000;
            FirstDir0x71000 = 0x71000;
            FirstDir0x71000[i + 1] = pageDirAddress;
            FirstDir0x71000[i + 1] += 0x7;
            for (uint64_t j = 0; j < 512; j++)
            {
                if (j >= pages)
                {
                    break;
                }
                pageDirAddress[j] = 0x40000000 * (i + 1) + 2 * 1024 * 1024 * j;
                pageDirAddress[j] = pageDirAddress[j] + 0x83;
            }
            pages -= 512;
        }
        head = 1024 * 1024 * 2 + 0x2000;
        head->address = pageDirAddress;
    }
}

uint64_t link_page(uint64_t address, uint64_t offset)
{
    struct page *p = address;
    p->next = address + offset;
    return address + offset;
}
