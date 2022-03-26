#include "amd64/register.h"
#include "task.h"
#include "stdint.h"

void set_task_register(int pid, uint64_t functionAddress, enum task_type type)
{
    if (type == KERNEL)
    {
        registerList[pid].rip = functionAddress;
        registerList[pid].errorcode = 0;
        registerList[pid].rflags = 663;
        registerList[pid].cs = 8;
        registerList[pid].rsp = 0xffff800000000000 + 0x400000 - (pid * 0x1000);
    }
    else
    {
        //后期可能需要修改的地方
        registerList[pid].rsp = 0x1000;
    }
}

void save_registers(struct TrapFrame *curTask, struct TrapFrame *tf)
{
    curTask->ss = tf->ss;
    curTask->rsp = tf->rsp;
    curTask->rflags = tf->rflags;
    curTask->cs = tf->cs;
    curTask->rip = tf->rip;
    curTask->errorcode = tf->errorcode;
    curTask->trapno = tf->trapno;
    curTask->rax = tf->rax;
    curTask->rbx = tf->rbx;
    curTask->rcx = tf->rcx;
    curTask->rdx = tf->rdx;
    curTask->rsi = tf->rsi;
    curTask->rdi = tf->rdi;
    curTask->rbp = tf->rbp;
    curTask->r8 = tf->r8;
    curTask->r9 = tf->r9;
    curTask->r10 = tf->r10;
    curTask->r11 = tf->r11;
    curTask->r12 = tf->r12;
    curTask->r13 = tf->r13;
    curTask->r14 = tf->r14;
    curTask->r15 = tf->r15;
}