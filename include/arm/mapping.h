#ifndef __MAPPING_H
#define __MAPPING_H
#include "stdint.h"
#include "arm/memory.h"

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

enum procedure_type
{
    KERNEL = 0,
    NORMAL_PROCESS = 1
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

uint64_t find_physical_address();
uint64_t mapping(uint64_t dirAddress, uint64_t index, uint64_t address, enum attributes attris);

#endif