#include "arm/memory.h"
#include "arm/mapping.h"
#include "printk.h"
#include "debug.h"
#include "stddef.h"
#include "debug.h"

struct page_infor pageInfor = {0, 0, 0};
struct page_dir_manage dir0;
struct page_dir_manage dir1;
struct page_dir_manage dir2;

void init_malloc(uint64_t ttbr1_el1, uint64_t directory1, uint64_t directory2, enum procedure_type program)
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
        pageInfor.pPhysicalAdrress = pageHead;
        pageInfor.virtualAddress = 2 * 1024 * 1024 * 2 + KERNEL_BASE;
    }
    else
    {
    }
}

void malloc_page(uint64_t pageAmount)
{
    
    for (uint32_t i = 0; i < pageAmount; i++)
    {
        dir2.usedAmount = mapping(dir2.address, dir2.usedAmount, pageInfor.pPhysicalAdrress, DIR2);
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
            dir1.usedAmount = mapping(dir1.address, dir1.usedAmount, dir1.address, DIR1);
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
    if (attris == DIR2)
    {
        dirArray[index] += 0x405;
    }
    else if (attris == DIR1)
    {
        dirArray[index] += 0x0;
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

/**
 * function: free_page
 * @param [uint64_t] pageAccount : The amount of pages that you want to release.
 * @return [void]
 * description: release the page.
 * 释放页。
 */
void free_page(uint64_t pageAmount)
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