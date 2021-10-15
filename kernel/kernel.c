#include "init.h"

void kernel_init(void)
{
  //  char* p = (char*)0xb8000;

    init_all();
    printk("abc");

   // p[0] = 'C';
   // p[1] = 0xa;
  // print_char('S');
  // init_idt();
  
}