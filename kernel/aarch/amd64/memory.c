/*
 * @Author: your name
 * @Date: 2021-10-29 21:06:10
 * @LastEditTime: 2021-11-17 01:32:27
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /dolphin2/kernel/aarch/amd64/memory.c
 */
#include "amd64/memory.h"
#include "printk.h"
#include "debug.h"

int page_size = 0x200000;

struct Page{
    struct Page * next;
};

struct Page *head, *tail;

static struct FreeMemRegion FreeMemRegion[50];

void init_memory(void){
    int32_t count=*(int32_t*)0x9000;
    uint64_t total_mem=0;
    struct E820 *mem_map=(struct E820*)0x9008;
    int free_region_count=0;

    ASSERT(count <= 50, "init_memory():");

    for(int32_t i = 0; i< count; i++){
        if(mem_map[i].type == 1){
            FreeMemRegion[free_region_count].address = mem_map[i].address;
            FreeMemRegion[free_region_count].length = mem_map[i].length;
            total_mem += mem_map[i].length;
            free_region_count++;
        }
        printk("%x  %uKB  %u\n",mem_map[i].address,mem_map[i].length/1024,(uint64_t)mem_map[i].type);
    }
    printk("Total memory is %uMB\n",total_mem/1024/1024);

    uint16_t *ecx;
    ecx = 0x90000;
    uint64_t start_memory = *ecx * 1024 * 1024 * 2;
    uint32_t pages = total_mem/1024/1024/2;
    ASSERT(pages > 2, "page_num(): memory is too small (memory < 4MB)");
    uint64_t address = start_memory;

    struct Page * p;
    p = start_memory;

    struct Page * p2;
    p2 = start_memory + page_size;
    p2->next = start_memory + page_size * 2;
    p->next = p2;

    printk("\n p = %x %x %x\n", p, p->next, *p->next); 

    for (uint32_t i = 0; i < pages; i++){
        link_page(address);
        address += page_size;
    }
    
}

void link_page(uint64_t address){
    struct Page * p;
    p = address;
    p->next = address + page_size;
}
