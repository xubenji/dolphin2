#ifndef _MEMORY_H
#define _MEMORY_H

#ifdef MEM
#define SIZE_MEM MEM
#endif

#include "stdint.h"
#include "task.h"
#include "malloc.h"

struct page
{
    struct page *next;
};

struct last_phy_vir_address
{
    uint64_t lastPhyAddress;
    uint64_t lastVirAddress;
};

#define PHYSICAL_MEM_SIZE 256 //单位MB，unit mb
struct page *pageHead, *pageTail;
struct last_phy_vir_address processAddr;

#define KERNEL_BASE 0xffff000000000000
#define MEMORY_END P2V(0x30000000)
#define PAGE_SIZE (2 * 1024 * 1024)

#define P2V(p) ((uint64_t)(p) + KERNEL_BASE)
#define V2P(v) ((uint64_t)(v)-KERNEL_BASE)

#define PA_UP(v) ((((uint64_t)v + PAGE_SIZE - 1) >> 21) << 21)
#define PA_DOWN(v) (((uint64_t)v >> 21) << 21)

void init_memory(void);
static void free_region(uint64_t v, uint64_t e);
uint64_t find_physical_address();
void set_process_malloc(uint64_t ttbr1_el1, uint64_t directory1, uint64_t directory2, enum task_type program);
uint64_t mapping(uint64_t dirAddress, uint64_t index, uint64_t address, enum attributes attris);
void free_page(uint64_t pageAmount);
int get_page_attri(enum attributes attris);

#endif
