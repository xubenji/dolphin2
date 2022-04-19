
#include "printk.h"
#include "debug.h"
#include "stddef.h"
#include "task.h"
#include "malloc.h"

void set_task_malloc(uint64_t d0, uint64_t d1, uint64_t d2)
{
    dir0.dirState = IN_USE;
    dir0.address = d0;
    dir0.usedAmount = 0;
    dir0.attri = DIR0;
    dir0.next = 0;

    dir1.address = IN_USE;
    dir1.address = d1;
    dir1.usedAmount = 0;
    dir1.attri = DIR1;
    dir1.next = 0;

    dir2.dirState = IN_USE;
    dir2.address = d2;
    dir2.usedAmount = 0;
    dir2.attri = DIR2;
    dir2.next = 0;

    pageInfor.virtualAddress = 0;
}

/**
 * function: malloc_page
 * @param [uint64_t] pageAmount: The amount of page that you need to malloc.
 * @return [void]
 * description: Input the amount of page that you need to malloc, then the function will complete it.
 * 输入需要映射的page的数量，程序会完成这个操作。
 */
void malloc_page(uint64_t pageAmount)
{
    dir0.usedAmount = 1;
    for (uint32_t i = 0; i < pageAmount; i++)
    {
        dir2.usedAmount = mapping(dir2.address, dir2.usedAmount, pageHead, DIR2);
        if (pageHead->next == NULL)
        {
            printk("p_address: %x %d", p, i);
            ASSERT(1 < 0, "malloc_page(): run out the physical memory");
        }
        processAddr.lastPhyAddress = pageHead;
        pageHead = pageHead->next;
        if (dir2.usedAmount == 0)
        {
            dir2.address = dir2.next;
            dir2.next += 0x1000;
            dir1.usedAmount = mapping(dir1.address, dir1.usedAmount, dir2.address, DIR1);
            if (dir1.usedAmount == 0)
            {
                printk("run out of the virtual memory!!!");
                return NULL;
            }
        }
    }
    pageInfor.virtualAddress += pageAmount * 2 * 1024 * 1024;
    processAddr.lastVirAddress = pageInfor.virtualAddress - PAGE_SIZE;
}

/**
 * function: free_page
 * @param [uint64_t] pageAccount : The amount of pages that you want to release.
 * @return [void]
 * description: release the page.
 * 释放页。
 */
void free_page(uint64_t pageAmount)
{
    uint64_t *dir0Array = dir0.address;
    int index = pageInfor.virtualAddress >> 39;
    index = index & 0x1ff;
    uint64_t *dir1Array = (dir0Array[index] >> 12) << 12;
    uint64_t *dir2Array;
    for (uint32_t i = 0; i < pageAmount; i++)
    {
        if (index - 1 == 0)
        {
            dir2.next -= 0x1000;
            dir2.usedAmount = 512;
        }
        index = pageInfor.virtualAddress >> 30;
        index = index & 0x1ff;
        dir2Array = (dir1Array[index] >> 12) << 12;
        index = ((pageInfor.virtualAddress << 34) >> 34) / 0x200000;
        pageTail->next = dir2Array[index - 1];
        dir2Array[index - 1] = 0;
        pageTail = pageTail->next;
        pageTail->next = NULL;
        pageInfor.virtualAddress -= 0x200000; // 2MB
        dir2.usedAmount -= 1;
    }
}

uint64_t mapping(uint64_t dirAddress, uint64_t index, uint64_t address, enum attributes attris)
{
    uint64_t *dirArray = dirAddress;
    dirArray[index] = address;
    dirArray[index] += get_page_attri(attris);
    if (index == 200)
    {
        printk("500\n");
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

uint64_t link_page(uint64_t address, uint64_t offset)
{
    struct page *p = address;
    p->next = address + offset;
    return address + offset;
}