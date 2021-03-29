
void kernel_init(){
     char* p = (char*)0xb8000;

    p[0] = 'C';
    p[1] = 0xa;
    __asm__ __volatile__("1: jmp 1b");
}