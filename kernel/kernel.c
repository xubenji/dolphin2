#include "init.h"
//#include "types.h"
#include "stdint.h"
#include "stdarg.h"

void kernel_init(void)
{
  //  char* p = (char*)0xb8000;

    init_all();
    char a[7]="32a55AA";
    int b = 567;
    int c = a;
    int d = &b;
    printk("abc%s11 %d  adress A:%x  address B:%x",a,b,a,&b);
    while (1)
    {
      /* code */
    }
    
   // p[0] = 'C';
   // p[1] = 0xa;
  // print_char('S');
  // init_idt(); 524272 524268  2097105  2097100
  
}