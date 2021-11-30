#include "amd64/memory.h"
#include "printk.h"
#include "debug.h"
#include "stddef.h"

uint64_t pageSize = 0x200000;

struct page
{
    struct page *next;
};

struct page_dir
{
    struct page_dir *next;
    uint64_t *phead;
};

struct page *pageHead, *pageTail;

static struct FreeMemRegion FreeMemRegion[50];

//     mov eax,(0xffff800000000000>>39)
//     and eax,0x1ff

//     mov dword[0x70000+eax*8],0x73003

//     mov eax,(0xffff800000000000>>30)
//     and eax,0x1ff
//     mov dword[0x73000+eax*8],0x74003

//     mov esi,0x74000
//     mov eax,10000011b
//     mov ecx,2   ;512 is 1gb, 2 refers 4mb, so 0~4mb is occupied by kernel.
//     mov dword[0x90000],ecx
// .loop2:
//     mov [esi],eax
//     add eax, 2*1024*1024
//     add esi,8
//     loop .loop2

uint64_t link_page_dirs(uint64_t pageDirAddress, uint64_t offset, uint64_t pageAddress)
{
    struct page_dir *p = pageDirAddress;
    p->next = pageDirAddress + offset;
    p->phead = pageAddress;
    return pageDirAddress + offset;
}

uint64_t link_page(uint64_t address, uint64_t offset)
{
    struct page *p = address;
    p->next = address + offset;
    return address + offset;
}

void init_pages(uint64_t startMemory, uint64_t pages, uint64_t total_mem)
{
    uint16_t *ecx;
    ecx = 0x90000;
    uint64_t start_memory = *ecx * 1024 * 1024 * 2;
    pages = total_mem / 1024 / 1024 / 2;
    ASSERT(pages > 2, "page_num(): memory is too small (memory < 4MB)");

    /**
     *  取出页目录表地址，在load.asm中
     * 
     * 
     */
    uint64_t *PAGE_DIR_INIT = 0x9008;
    uint64_t *PAGE_DIR_FIRST = 0x900a;
    uint64_t *PAGE_DIR_SECOND = 0x9018;

    uint64_t address = start_memory;
    pageHead->next = start_memory;
    for (uint32_t i = 0; i < pages; i++)
    {
        address = link_page(address, pageSize);
    }
    pageTail = address;
    pageTail->next = NULL;

    uint64_t pageDirNumber = pages / 512;
    address = start_memory;
    for (uint64_t i = 0; i < pageDirNumber; i++)
    {
        address = address + i * 512 * pageSize;
        //link_page_dirs();
    }
    
}

void init_memory(void)
{
    int32_t count = *(int32_t *)0x9000;
    uint64_t total_mem = 0;
    struct E820 *mem_map = (struct E820 *)0x9008;
    int free_region_count = 0;

    ASSERT(count <= 50, "init_memory():");

    for (int32_t i = 0; i < count; i++)
    {
        if (mem_map[i].type == 1)
        {
            FreeMemRegion[free_region_count].address = mem_map[i].address;
            FreeMemRegion[free_region_count].length = mem_map[i].length;
            total_mem += mem_map[i].length;
            free_region_count++;
        }
        printk("%x  %uKB  %u\n", mem_map[i].address, mem_map[i].length / 1024, (uint64_t)mem_map[i].type);
    }
    printk("Total memory is %uMB\n", total_mem / 1024 / 1024);
}
