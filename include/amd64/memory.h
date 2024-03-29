#ifndef __MEMORY_H
#define __MEMORY_H
#define VIRTUAL_BASE_ADDR 0xffff800000000000

#include "stdint.h"
#include "task.h"
#include "malloc.h"
#include "stdbool.h"

uint64_t usedDirectoryManageAddresss; //已经使用了的页目录表地址，我们这里是0x74000 + 映射物理地址所占用的空间, 代表的是已经使用的页目录表地址，一个页目录表是8字节。
struct page *pageHead, *pageTail;     //可以使用的物理内存，这是一个单链表，每次分配一个页给某一个进程，pageHead就向前移动一个，每次释放一个页，pageTail就向后移动一个
uint64_t totalMemory;                 //电脑的全部可以使用的物理内存大小
uint64_t *pageDirAddress;

struct E820
{
    uint64_t address;
    uint64_t length;
    uint32_t type;
} __attribute__((packed));

struct free_mem_region
{
    uint64_t address;
    uint64_t length;
};

struct page_dir
{
    struct page_dir *next;
    uint64_t *phead;
};

struct page_dir_manage *head;

void init_memory(void);
void init_pages(uint64_t totalMemory);
bool map_all_physical_pages(int freePages);
uint64_t link_page_dirs(uint64_t pageDirAddress, uint64_t offset, uint64_t startMemory);
uint64_t link_page(uint64_t address, uint64_t size);
void set_kernel_malloc();
void *free_page(uint64_t pageAccount);
uint64_t find_physical_address();
uint64_t mapping(uint64_t dirAddress, uint64_t index, uint64_t Address, enum attributes attris);

#endif