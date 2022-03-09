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

void malloc_page()
{

}

uint64_t find_physical_address()
{
    pageInfor.pPhysicalAdrress = pageHead;
    printk("find: %x\n", pageInfor.pPhysicalAdrress);
}