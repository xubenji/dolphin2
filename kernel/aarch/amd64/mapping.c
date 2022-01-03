/*
 * Name: mapping.c
 * Author: Benji Xu <benjixu2020@gmail.com>
 * Date: 2021-12-30 01:02:11
 * LastEditTime: 2022-01-02 03:39:32
 * LastEditors: Benji Xu
 * FilePath: /dolphin2/kernel/aarch/amd64/mapping.c
 * Description: this .c file is going to implement the malloc
 * 描述: 这个点C文件是为了实现malloc
 */
#include "printk.h"
#include "debug.h"
#include "stddef.h"
#include "debug.h"
#include "amd64/memory.h"
#include "amd64/mapping.h"

#define BASE_VIRTUAL_ADDRESS 0xffff800000000000

struct page_infor pageInfor = {0, 0, 0};
struct page_dir_manage cr3Infor;
struct page_dir_manage firstDirInfor;
struct page_dir_manage secondDirInfor;
uint64_t *ecx = 0x90000;

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
void init_malloc(uint64_t cr3, uint64_t firstDir, uint64_t secondDir, enum procedure_type program)
{
    if (program == KERNEL)
    {
        cr3Infor.dirState = IN_USE;
        cr3Infor.address = 0x70000;
        cr3Infor.usedAmount = 1;
        cr3Infor.attri = CR3;
        cr3Infor.next = 0;

        firstDirInfor.dirState = IN_USE;
        firstDirInfor.address = 0x73000;
        firstDirInfor.usedAmount = 1;
        firstDirInfor.attri = FRIST_DIR;
        firstDirInfor.next = 0;

        secondDirInfor.dirState = IN_USE;
        secondDirInfor.address = 0x74000;
        secondDirInfor.usedAmount = *ecx;
        secondDirInfor.attri = SECOND_DIR;
        secondDirInfor.next = pageDirAddress + 0x1000;

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
        secondDirInfor.usedAmount = mapping(secondDirInfor.address, secondDirInfor.usedAmount, pageInfor.pPhysicalAdrress, SECOND_DIR);
        struct page *p = pageInfor.pPhysicalAdrress;
        if (p->next == NULL)
        {
            printk("p_address: %x %d", p, i);
            ASSERT(1 < 0, "malloc_page(): run out the physical memory");
        }
        pageInfor.pPhysicalAdrress = pageInfor.pPhysicalAdrress->next;
        if (secondDirInfor.usedAmount == 0)
        {
            secondDirInfor.address = secondDirInfor.next;
            secondDirInfor.next += 0x1000;
            firstDirInfor.usedAmount = mapping(firstDirInfor.address, firstDirInfor.usedAmount, secondDirInfor.address, FRIST_DIR);
            if (firstDirInfor.usedAmount == 0)
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
    uint64_t *cr3 = cr3Infor.address;
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
            secondDirInfor.next -= 0x1000;
        }
        pageTail = pageTail->next;
        pageTail->next = NULL;
        pageInfor.virtualAddress -= 0x200000; // 2MB
    }
}

uint64_t find_physical_address()
{
    pageInfor.pPhysicalAdrress = pageHead;
    printk("find: %x\n", pageInfor.pPhysicalAdrress);
}

uint64_t mapping(uint64_t dirAddress, uint64_t index, uint64_t Address, enum attributes attris)
{
    uint64_t *dirArray = dirAddress;
    dirArray[index] = Address;
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
