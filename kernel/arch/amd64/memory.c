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
#include "task.h"
#include "malloc.h"
#include "stdbool.h"

#define BASE_VIRTUAL_ADDRESS 0xffff800000000000

struct page_infor pageInfor = {0, 0, 0};
struct page_dir_manage dir0;
struct page_dir_manage dir1;
struct page_dir_manage dir2;
uint64_t *ecx = 0x90000;

uint64_t pageSize = 0x200000; // 2mb

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

    set_kernel_malloc();
    //实际分配的要比这个多一点，因为在load里面已经分配了3个页
    malloc_page(1023);
    free_page(12);
}

/**
 * @function: init_pages
 * @param [uint64_t] totalMemory: the total memory size in bytes. | 以字节来表示的内存大小
 * @return [null]
 * description: Init the pages, using single link list to manage the free pages. | 初始化页，使用单链表来管理可以使用的页
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
    map_all_physical_pages(pages + *ecx);

    /* 将所有的可以利用的物理页用单链表连接起来
     *-----------------------------------------------------------------------*/
    uint64_t address = starMemory;
    pageHead = starMemory;
    for (uint32_t i = 0; i < pages - 1; i++)
    {
        address = link_page(address, pageSize);
    }

    pageTail = address;
    pageTail->next = NULL;
    struct page *temp = pageHead;

    set_kernel_malloc();

    for (int i = 0; i < *ecx; i++)
    {
        uint64_t *new = dir2.address;
        uint64_t *old = 0x74000;
        new[i] = old[i];
    }
    uint64_t *t = 0x73000;
    t[0] = dir2.address + 0x03;
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
bool map_all_physical_pages(int freePages)
{
    // if (freePages < 508)
    // {
    //     return NULL;
    // }
    // else
    // {
    //     uint32_t pages = (freePages - 508);
    //     pageDirAddress = 0x75000;
    //     for (uint64_t i = 0; i <= (freePages - 512) / 512; i++)
    //     {
    //         pageDirAddress = 0x75000 + 0x1000 * i; //在load.asm中 0x70000～0x74000已经被映射完了，所以我们这里从0x7500开始。
    //         uint64_t *FirstDir0x71000;
    //         FirstDir0x71000 = 0x71000;
    //         FirstDir0x71000[i + 1] = pageDirAddress;
    //         FirstDir0x71000[i + 1] += 0x7;
    //         for (uint64_t j = 0; j < 512; j++)
    //         {
    //             if (j >= pages)
    //             {
    //                 break;
    //             }
    //             pageDirAddress[j] = 0x40000000 * (i + 1) + 2 * 1024 * 1024 * j;
    //             pageDirAddress[j] = pageDirAddress[j] + 0x83;
    //         }
    //         pages -= 512;
    //     }
    //     head = 1024 * 1024 * 2 + 0x2000;
    //     head->address = pageDirAddress;
    // }
    if (freePages > 512)
    {
        freePages = freePages - 512;
    }
    else
    {
        return false;
    }
    int dir = freePages / 512 + 1;
    uint64_t *dir1A = 0x71000;
    uint64_t *dir2A = 0x1000;
    *dir2A = 0;
    for (int i = 0; i < dir + 1; i++)
    {
        dir1A[i + 1] = dir2A;
        dir1A[i + 1] += 0x27;
        for (int j = 0; j < 512; j++)
        {
            freePages -= 1;
            if (freePages >= 0)
            {
                dir2A[j] = 0x40000000;
                dir2A[j] = dir2A[j] * (i + 1);
                dir2A[j] += 2 * 1024 * 1024 * j + 0x87; //0x87是属性 10000011b
            }
            else
            {
                return true;
            }
        }
        dir2A = 0x1000 + 0x1000 * (i + 1);
    }
}

/**
 * function: init_malloc
 * @param [uint64_t] cr3: the value of cr3
 * @param [uint64_t] firstDir: first-directory' value
 * @param [uint64_t] secondDir: DIR1ectory's value
 * @param [enum procedure_type] program: the process's type. normal process or kernel process.
 * @return [void]
 * description:
 * Init the cr3's value, first-page directory address, second-page directory address, and others information.
 * In the 64-bits system, if we set up the page to 2mb, we need 3 level page directory list.
 * We have to implement the process, so we need a different page directory because the different process has their own page directory.
 * If we don't need to implement the process, we don't need to arrange each page directory for each process.
 * We can use the kernel's page directory address. The cr3's value for kernel is 0x70000.
 * 初始化cr3寄存器的值，第一阶页目录表的地址，第二阶页目录表的地址和其他信息，在64位下，2mb页需要三阶页目录表。
 * 我们需要实现进程这个概念，所以我们需要不同的页目录表和页表，因为每一个进程都有他独自的页目录表和页表
 * 如果我们不需要实现进程，我们可以直接使用内核的页表，内核的cr3保存的地址是在0x70000
 * 0x73000是管虚拟地址的，0x71000是直接物理地址。所以内核访问比较大的地址，它会走0x73000
 * 0x73000在0x70000的第256个位
 */
void set_kernel_malloc()
{
    dir0.dirState = IN_USE;
    dir0.address = 0x70000;
    dir0.usedAmount = 1;
    dir0.attri = DIR0;
    dir0.next = 0;

    dir1.dirState = IN_USE;
    dir1.address = 0x73000;
    dir1.usedAmount = 1;
    dir1.attri = DIR1;
    dir1.next = 0;

    dir2.dirState = IN_USE;
    dir2.address = 0x100000;
    dir2.usedAmount = *ecx;
    dir2.attri = DIR1;
    dir2.next = 0x100000 + 0x1000;

    pageInfor.dirAddress = 0x100000;
    pageInfor.virtualAddress = *ecx * 1024 * 1024 * 2 + BASE_VIRTUAL_ADDRESS;

    printk("init malloc\n");
}

int get_page_attri(enum attributes attris)
{
    switch (attris)
    {
    case DIR2:
        return 0x83;
        break;
    case DIR1:
        return 0x03;
    default:
        return 0;
        break;
    }
}