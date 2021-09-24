#include "printk.h"

void kernel_init(void){
    
    //output("aaaHello, world!hahahah\r\n");

    // display a pixmap
    //lfb_showpicture();

    test_print();
    
}

/*
void show(){
    char* p = (char*)0xb8000;

    p[0] = 'C';
    p[1] = 0xa;
    __asm__ __volatile__("1: jmp 1b");
}
*/  
