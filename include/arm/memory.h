#ifndef _MEMORY_H
#define _MEMORY_H

#ifdef MEM
#define SIZE_MEM MEM
#endif

#include "stdint.h"
enum state
{
    FREE = 0,
    IN_USE = 1,
    USED = 2
};

enum attributes
{
    DIR0 = 0,
    DIR1 = 1,
    DIR2 = 2
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

struct page
{
    struct page *next;
};

#define PHYSICAL_MEM_SIZE 256 //单位MB，unit mb
struct page *pageHead, *pageTail;

#define KERNEL_BASE 0xffff000000000000
#define MEMORY_END P2V(0x30000000)
#define PAGE_SIZE (2 * 1024 * 1024)

#define P2V(p) ((uint64_t)(p) + KERNEL_BASE)
#define V2P(v) ((uint64_t)(v)-KERNEL_BASE)

#define PA_UP(v) ((((uint64_t)v + PAGE_SIZE - 1) >> 21) << 21)
#define PA_DOWN(v) (((uint64_t)v >> 21) << 21)

void init_memory(void);
static void free_region(uint64_t v, uint64_t e);
uint64_t link_page(uint64_t address, uint64_t offset);
uint64_t find_physical_address();
uint64_t mapping(uint64_t dirAddress, uint64_t index, uint64_t address, enum attributes attris);
void free_page(uint64_t pageAmount);

#endif
