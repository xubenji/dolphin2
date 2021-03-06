#include <stdio.h>
#include <../boot/init_boot.h>

int init_boot(){
    printf("This is init_boot, and I need the =>");
    boot();
    return 0;
}