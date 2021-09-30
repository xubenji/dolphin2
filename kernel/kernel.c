#include "printk.h"
#include "init.h"

void kernel_init(void){
    init();
    //printk("heelop2");
    while(1){}
    //test_print();
}
