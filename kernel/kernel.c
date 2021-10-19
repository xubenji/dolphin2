#include "init.h"
//#include "types.h"
#include "stdint.h"
#include "stdarg.h"

void kernel_init(void)
{
  //  char* p = (char*)0xb8000;

    init_all();
    char a[5]="32a55";
    int b = 567;
    printk("abc%s11 %d",a,b);
    while (1)
    {
      /* code */
    }
    
   // p[0] = 'C';
   // p[1] = 0xa;
  // print_char('S');
  // init_idt();
  
}