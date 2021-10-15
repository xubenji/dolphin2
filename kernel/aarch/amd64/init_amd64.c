#include "amd64/trap.h"

void init_all(){
    init_print();
    init_idt();
}