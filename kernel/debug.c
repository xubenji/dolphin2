#include "debug.h"
#include "amd64/put.h"
#include "stdint.h"
#include "printk.h"

void error_check(uint8_t *file, uint64_t line){
    printk("\n-------------------------------\n");
    printk("         EEROR_CHECK\n");
    printk("-------------------------------\n");
    printk("Assertion Failed:[%s:%u]", file, line);
    while (1)
    {
        
    }
    
    //__asm__ __volatile__("1: jmp 1b");
}

