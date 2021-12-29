#ifndef __MEMORY_H
#define __MEMORY_H
#define VIRTUAL_BASE_ADDR 0xffff800000000000

#include "stdint.h"

struct E820{
    uint64_t address;
    uint64_t length;
    uint32_t type;
} __attribute__((packed));

struct FreeMemRegion{
    uint64_t address;
    uint64_t length;
};

void init_memory(void);
uint64_t link_page(uint64_t address, uint64_t size);
void init_pages(uint64_t total_mem);
uint64_t link_page_dirs(uint64_t pageDirAddress, uint64_t offset, uint64_t startMemory);
uint64_t map_all_pages(uint64_t freePages);

#endif