/** 
 * Name: 
 * Author: Benji Xu <benjixu2020@gmail.com>
 * Date: 2021-11-04 03:56:41
 * LastEditTime: 2022-01-22 05:39:33
 * LastEditors: Benji Xu
 * FilePath: /dolphin2/kernel/kernel.c
 * Description: 
 * 描述: 无论是x86还是arm cpu执行完引导区的代码以后就开始执行这里的代码。
 */
#include "init.h"
#include "stdint.h"
#include "stdarg.h"
#include "debug.h"
#include "interruption.h"
#include "printk.h"


void kernel_init(void)
{
  //  char* p = (char*)0xb8000;

    // disable_interruption();
    init_all();
    // enable_interruption();
    printk("hello world\n");

    int a = 100;
    a =200;
    //ASSERT(3,2);
    ASSERT(0,1);

     printk("!!!!!!!!!!!!\n");    
    while (1)
    {
        for (int i = 0; i < 10000000; i++)
        {
            /* code */
        }
      //printk(" T000 ");
    }
    
    //__asm__ __volatile__("cli");
    
    // char a[7]="32a55AA";
    // //int b = 567;
    // //int c = a;
    // //int d = &b;
    // //printk("abc%s11 %d",a,b);
    // printk("abc%s11 ",a);
    // char * p = "A??c";
    // //int cc = 5;
    // int cc[3] = {1,2,3};
    // printk("test: %s %x %x", p, cc, &cc);
    // //ASSERT(0);

    // while (1)
    // {
    //   /* code */
    // }
    
   // p[0] = 'C';
   // p[1] = 0xa;
   // print_char('S');
   // init_idt(); 524272 524268  2097105  2097100
  
}
    