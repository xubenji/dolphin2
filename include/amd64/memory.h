#ifndef __MEMORY_H
#define __MEMORY_H
#define VIRTUAL_BASE_ADDR 0xffff800000000000

#include "stdint.h"
#include "task.h"

uint64_t usedDirectoryManageAddresss; //已经使用了的页目录表地址，我们这里是0x74000 + 映射物理地址所占用的空间, 代表的是已经使用的页目录表地址，一个页目录表是8字节。
struct page *pageHead, *pageTail;
uint64_t totalMemory; //电脑的全部可以使用的物理内存大小
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

struct page
{
    struct page *next;
};

struct page_dir
{
    struct page_dir *next;
    uint64_t *phead;
};

enum state
{
    FREE = 0,
    IN_USE = 1,
    USED = 2
};

enum attributes
{
    CR3 = 0,
    FRIST_DIR = 1,
    SECOND_DIR = 2
};


struct page_dir_manage
{
    enum state dirState; //此页目录的状态，FREE是没有被使用，IN_USE是正在使用，USED是已经使用完了
    uint64_t address;
    uint64_t usedAmount;
    enum attributes attri;
    struct page_dir_manage *next;
};

struct page_infor
{
    uint64_t virtualAddress; //必须是2mb对齐
    struct page *pPhysicalAdrress;
    uint64_t dirAddress;
};

struct page_dir_manage *head;

void init_memory(void);
void init_pages(uint64_t totalMemory);
uint64_t map_all_physical_pages(uint64_t freePages);
uint64_t link_page_dirs(uint64_t pageDirAddress, uint64_t offset, uint64_t startMemory);
uint64_t link_page(uint64_t address, uint64_t size);
void init_malloc(uint64_t cr3, uint64_t firstDir, uint64_t secondDir, enum task_type program);
void *malloc_page(uint64_t pageAmount);
void *free_page(uint64_t pageAccount);
uint64_t find_physical_address();
uint64_t mapping(uint64_t dirAddress, uint64_t index, uint64_t Address, enum attributes attris);

#endif