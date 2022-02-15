#include "interruption.h"

void enable_interruption(void)
{
    __asm__ __volatile__("sti");
}

void disable_interruption(void)
{
    __asm__ __volatile__("cli");
}