


#include "init.h"
//#include "types.h"
#include "stdint.h"
#include "stdarg.h"
#include "debug.h"


void kernel_init(void)
{
  //  char* p = (char*)0xb8000;

    init_all();
    char a[7]="32a55AA";
    //int b = 567;
    //int c = a;
    //int d = &b;
    //printk("abc%s11 %d",a,b);
    printk("abc%s11 ",a);

    ASSERT(0);

    while (1)
    {
      /* code */
    }
    
   // p[0] = 'C';
   // p[1] = 0xa;
  // print_char('S');
  // init_idt(); 524272 524268  2097105  2097100
  
}
