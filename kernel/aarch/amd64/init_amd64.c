#include "amd64/init_amd64.h"

void init(){
    char* p = (char*)BASE;

    p[0] = 'C';
    p[1] = 0xa;
    __asm__ __volatile__("1: jmp 1b");
    
}