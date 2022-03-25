#include "stdint.h"
#include "task.h"
#include "arm/register.h"

void set_task_register(int pid, uint64_t functionAddress, enum task_type type)
{
    registerList[pid].elr_el1 = functionAddress;
    if (type == KERNEL)
    {
        registerList[pid].sp = 0x80000 - (pid * 0x1000);
        registerList[pid].spsr_el1 = 0;
    }
    else
    {
        //后期可能需要修改的地方
        registerList[pid].sp = 0x10000;
        registerList[pid].spsr_el1 = 0;
    }
}

void save_registers(struct trap_frame *curTask, struct trap_frame *tf, uint64_t elr_el1, uint64_t spsr_el1, uint64_t sp)
{
    curTask->x0 = tf->x0;
    curTask->x1 = tf->x1;
    curTask->x2 = tf->x2;
    curTask->x3 = tf->x3;
    curTask->x4 = tf->x4;
    curTask->x5 = tf->x5;
    curTask->x6 = tf->x6;
    curTask->x7 = tf->x7;
    curTask->x8 = tf->x8;
    curTask->x9 = tf->x9;
    curTask->x10 = tf->x10;
    curTask->x11 = tf->x11;
    curTask->x12 = tf->x12;
    curTask->x13 = tf->x13;
    curTask->x14 = tf->x14;
    curTask->x15 = tf->x15;
    curTask->x16 = tf->x16;
    curTask->x17 = tf->x17;
    curTask->x18 = tf->x18;
    curTask->x19 = tf->x19;
    curTask->x20 = tf->x20;
    curTask->x21 = tf->x21;
    curTask->x22 = tf->x22;
    curTask->x23 = tf->x23;
    curTask->x24 = tf->x24;
    curTask->x25 = tf->x25;
    curTask->x26 = tf->x26;
    curTask->x27 = tf->x27;
    curTask->x28 = tf->x28;
    curTask->x29 = tf->x29;
    curTask->x30 = tf->x30;
    curTask->sp = sp;
    curTask->spsr_el1 = spsr_el1;
    curTask->elr_el1 = elr_el1;
}