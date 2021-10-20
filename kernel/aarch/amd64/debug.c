#include "amd64/debug.h"
#include "amd64/put.h"
#include "stdint.h"

void error_check(uint8_t *file, uint64_t line){
    puts("-------------------------------\n");
    puts("         EEROR_CHECK\n");
    puts("-------------------------------\n");
    __asm__ __volatile__("1: jmp 1b");
}

