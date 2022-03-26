#ifndef _MALLOC_H
#define _MALLOC_H
#include "stdint.h"

#define PAGE_SIZE 0x200000 //2MiB

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

struct page_infor pageInfor;
struct page_dir_manage dir0;
struct page_dir_manage dir1;
struct page_dir_manage dir2;

void set_task_malloc(uint64_t dir0, uint64_t dir1, uint64_t dir2);
void malloc_page(uint64_t pageAmount);
uint64_t link_page(uint64_t address, uint64_t offset);

#endif
