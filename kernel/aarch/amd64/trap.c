#include "amd64/trap.h"
#include "printk.h"
#include "debug.h"
#include "amd64/init.h"
#include "amd64/thread.h"

static struct IdtPtr idt_pointer;
static struct IdtEntry vectors[256];

static void init_idt_entry(struct IdtEntry *entry, uint64_t addr, uint8_t attribute)
{
    entry->low = (uint16_t)addr;
    entry->selector = 8;
    entry->attr = attribute;
    entry->mid = (uint16_t)(addr >> 16);
    entry->high = (uint32_t)(addr >> 32);
}

void init_idt(void)
{
    init_idt_entry(&vectors[0], (uint64_t)vector0, 0x8e);
    init_idt_entry(&vectors[1], (uint64_t)vector1, 0x8e);
    init_idt_entry(&vectors[2], (uint64_t)vector2, 0x8e);
    init_idt_entry(&vectors[3], (uint64_t)vector3, 0x8e);
    init_idt_entry(&vectors[4], (uint64_t)vector4, 0x8e);
    init_idt_entry(&vectors[5], (uint64_t)vector5, 0x8e);
    init_idt_entry(&vectors[6], (uint64_t)vector6, 0x8e);
    init_idt_entry(&vectors[7], (uint64_t)vector7, 0x8e);
    init_idt_entry(&vectors[8], (uint64_t)vector8, 0x8e);
    init_idt_entry(&vectors[10], (uint64_t)vector10, 0x8e);
    init_idt_entry(&vectors[11], (uint64_t)vector11, 0x8e);
    init_idt_entry(&vectors[12], (uint64_t)vector12, 0x8e);
    init_idt_entry(&vectors[13], (uint64_t)vector13, 0x8e);
    init_idt_entry(&vectors[14], (uint64_t)vector14, 0x8e);
    init_idt_entry(&vectors[16], (uint64_t)vector16, 0x8e);
    init_idt_entry(&vectors[17], (uint64_t)vector17, 0x8e);
    init_idt_entry(&vectors[18], (uint64_t)vector18, 0x8e);
    init_idt_entry(&vectors[19], (uint64_t)vector19, 0x8e);
    init_idt_entry(&vectors[32], (uint64_t)vector32, 0x8e);
    init_idt_entry(&vectors[39], (uint64_t)vector39, 0x8e);

    idt_pointer.limit = sizeof(vectors) - 1;
    idt_pointer.addr = (uint64_t)vectors;
    load_idt(&idt_pointer);
}


void handler(struct TrapFrame *tf)
{
    unsigned char isr_value;

    switch (tf->trapno)
    {
    case 32:
        eoi();

        //printk("timer");

        while (p->status != TASK_RUNNING)
        {
            p = p->next;
        }

        p->status = TASK_WAITTING;
        save_registers(&registerList[p->pid], tf);

        p = p->next;

        p->status = TASK_RUNNING;
        set_rsp(&registerList[p->pid]);

        // flage += 1;
        // if (flage < 2)
        // {
        //     set_rsp(&test1);
        // }
        // else if (flage % 2 == 0)
        // {
        //     save_registers(&test1,tf);

        //     set_rsp(&test2);
        // }
        // else
        // {
        //     test2.ss = tf->ss;
        //     test2.rsp = tf->rsp;
        //     test2.rflags = tf->rflags;
        //     test2.cs = tf->cs;
        //     test2.rip = tf->rip;
        //     test2.errorcode = tf->errorcode;
        //     test2.trapno = tf->trapno;
        //     test2.rax = tf->rax;
        //     test2.rbx = tf->rbx;
        //     test2.rcx = tf->rcx;
        //     test2.rdx = tf->rdx;
        //     test2.rsi = tf->rsi;
        //     test2.rdi = tf->rdi;
        //     test2.rbp = tf->rbp;
        //     test2.r8 = tf->r8;
        //     test2.r9 = tf->r9;
        //     test2.r10 = tf->r10;
        //     test2.r11 = tf->r11;
        //     test2.r12 = tf->r12;
        //     test2.r13 = tf->r13;
        //     test2.r14 = tf->r14;
        //     test2.r15 = tf->r15;

        //     set_rsp(&test1);
        // }

        // test1.cs =
        //  __asm__ __volatile__("cli");

        break;

    case 39:
        isr_value = read_isr();
        if ((isr_value & (1 << 7)) != 0)
        {
            eoi();
        }
        break;

    default:
        ASSERT(1 > 2, "defalut assert");
    }
}