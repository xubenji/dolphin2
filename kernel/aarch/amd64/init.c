#include "amd64/trap.h"

//初始化所有服务
void init_all(){
    init_print();
    init_idt();
}