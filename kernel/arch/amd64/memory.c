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

/**
 * function: init_malloc
 * @param [uint64_t] cr3: the value of cr3
 * @param [uint64_t] firstDir: first-directory' value
 * @param [uint64_t] secondDir: second_directory's value
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
 */
void init_malloc(uint64_t cr3, uint64_t firstDir, uint64_t secondDir, enum task_type program)
{
    if (program == KERNEL)
    {
        dir0.dirState = IN_USE;
        dir0.address = 0x70000;
        dir0.usedAmount = 1;
        dir0.attri = CR3;
        dir0.next = 0;

        dir1.dirState = IN_USE;
        dir1.address = 0x73000;
        dir1.usedAmount = 1;
        dir1.attri = FRIST_DIR;
        dir1.next = 0;

        dir2.dirState = IN_USE;
        dir2.address = 0x74000;
        dir2.usedAmount = *ecx;
        dir2.attri = SECOND_DIR;
        dir2.next = pageDirAddress + 0x1000;

        pageInfor.dirAddress = 0x74000;
        pageInfor.pPhysicalAdrress = pageHead;
        pageInfor.virtualAddress = *ecx * 1024 * 1024 * 2 + BASE_VIRTUAL_ADDRESS;

        printk("init malloc\n");
    }
    else
    {
    }
}

/**
 * function: malloc_page
 * @param [uint64_t] pageAmount: The amount of page that you need to malloc.
 * @return [void]
 * description: Input the amount of page that you need to malloc, then the function will complete it.
 * 输入需要映射的page的数量，程序会完成这个操作。
 */
void *malloc_page(uint64_t pageAmount)
{
    find_physical_address();
    for (uint32_t i = 0; i < pageAmount; i++)
    {
        dir2.usedAmount = mapping(dir2.address, dir2.usedAmount, pageInfor.pPhysicalAdrress, SECOND_DIR);
        struct page *p = pageInfor.pPhysicalAdrress;
        if (p->next == NULL)
        {
            printk("p_address: %x %d", p, i);
            ASSERT(1 < 0, "malloc_page(): run out the physical memory");
        }
        pageInfor.pPhysicalAdrress = pageInfor.pPhysicalAdrress->next;
        if (dir2.usedAmount == 0)
        {
            dir2.address = dir2.next;
            dir2.next += 0x1000;
            dir1.usedAmount = mapping(dir1.address, dir1.usedAmount, dir2.address, FRIST_DIR);
            if (dir1.usedAmount == 0)
            {
                printk("run out of the virtual memory!!!");
                return NULL;
            }
        }
    }
    pageInfor.virtualAddress += pageAmount * 2 * 1024 * 1024;
    // pageInfor.virtualAddress += 0x40000000;

    /* test code */
    uint64_t *test = 0xffff8000006ffff0;
    *test = 12;
}

/**
 * function: free_page
 * @param [uint64_t] pageAccount : The amount of pages that you want to release.
 * @return [void]
 * description: release the page.
 * 释放页。
 */
void *free_page(uint64_t pageAmount)
{
    uint64_t *cr3 = dir0.address;
    uint32_t index = pageInfor.virtualAddress >> 39;
    index = index & 0x1ff;
    uint64_t *firstDirArray = (cr3[index] >> 12) << 12;
    uint64_t *secondDirArray;
    for (uint32_t i = 0; i < pageAmount; i++)
    {
        index = pageInfor.virtualAddress >> 30;
        index = index & 0x1ff;
        uint64_t *secondDirArray = (firstDirArray[index] >> 12) << 12;
        index = ((pageInfor.virtualAddress << 34) >> 34) / 0x200000;
        pageTail->next = secondDirArray[index - 1];
        secondDirArray[index - 1] = 0;
        if (index - 1 == 0)
        {
            dir2.next -= 0x1000;
        }
        pageTail = pageTail->next;
        pageTail->next = NULL;
        pageInfor.virtualAddress -= 0x200000; // 2MB
    }
    dir2.usedAmount -= pageAmount;
}

uint64_t find_physical_address()
{
    pageInfor.pPhysicalAdrress = pageHead;
    printk("find: %x\n", pageInfor.pPhysicalAdrress);
}

uint64_t mapping(uint64_t dirAddress, uint64_t index, uint64_t address, enum attributes attris)
{
    uint64_t *dirArray = dirAddress;
    dirArray[index] = address;
    if (attris == SECOND_DIR)
    {
        dirArray[index] += 0x83;
    }
    else if (attris == FRIST_DIR)
    {
        dirArray[index] += 0x03;
    }
    if (index >= 511)
    {
        return 0;
    }
    else
    {
        return index + 1;
    }
}