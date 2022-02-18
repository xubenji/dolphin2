#include "stdint.h"
#include "printk.h"
#include "task.h"
#include "arm/lib.h"
#include "arm/irq.h"
#include "arm/uart.h"
#include "arm/register.h"

void enable_timer(void);
uint32_t read_timer_status(void);
void set_timer_interval(uint32_t value);
uint32_t read_timer_freq(void);
void set_elr_el(uint64_t elr);
void disable_timer(void);
void irq_return(uint64_t sp);
void set_spsr_el(uint64_t spsr_el);

static uint32_t timer_interval = 0;
static uint64_t ticks = 0;

// void test_print1()
// {
//     int a = 100;
//     a = 200;

//     while (1)
//     {
//         printk("111111111111111111\n");
//     }
// }

// void test_print2()
// {
//     int a = 100;
//     a = 200;

//     while (1)
//     {
//         printk("222222222222222222\n");
//     }
// }

struct trap_frame r1 = {0};
struct trap_frame r2 = {0};

void init_timer(void)
{
    timer_interval = read_timer_freq() / 100;
    enable_timer();
    out_word(CNTP_EL0, (1 << 1));
    // r1.sp = 0x80000 - 0x1000;
    // r2.sp = 0x80000 - 0x2000;
    // r1.elr_el1 = &test_print1;
    // r2.elr_el1 = &test_print2;
}

static void timer_interrupt_handler(uint64_t esr, uint64_t elr, uint64_t sp, uint64_t spsr)
{
    uint32_t status = read_timer_status();
    disable_timer();
    if (status & (1 << 2))
    {
        while (p->status != TASK_RUNNING)
        {
            p = p->next;
        }

        p->status = TASK_WAITTING;
        save_registers(&registerList[p->pid], sp, elr, spsr, sp + (32 * 8));

        p = p->next;
        set_timer_interval(timer_interval);
        set_elr_el(registerList[p->pid].elr_el1);
        //set_spsr_el(r2.spsr_el1);
        p->status = TASK_RUNNING;
        irq_return(&registerList[p->pid]);

        // ticks++;
        // if (ticks % 2 == 0)
        // {

        //     save_registers(&r1, sp, elr, spsr, sp + (32 * 8));

        //     printk("r1 timer %d \r\n", ticks);
        //     set_timer_interval(timer_interval);
        //     set_elr_el(r2.elr_el1);
        //     // set_spsr_el(r2.spsr_el1);
        //     printk("r2 address:%x\n", &r2);
        //     irq_return(&r2, r2.sp);
        // }
        // else
        // {
        //     if (ticks > 1)
        //     {
        //         save_registers(&r2, sp, elr, spsr, sp + (32 * 8));
        //         set_spsr_el(r1.spsr_el1);
        //     }
        //     printk("r2 timer %d \r\n", ticks);
        //     set_timer_interval(timer_interval);
        //     set_elr_el(r1.elr_el1);

        //     printk("r1 address:%x\n", &r1);
        //     irq_return(&r1, r1.sp);
        // }
    }
}

void handler(uint64_t numid, uint64_t esr, uint64_t elr, uint64_t sp, uint64_t spsr)
{
    uint32_t irq;

    switch (numid)
    {
    case 1:
        printk("sync error at %x: %x\r\n", elr, esr);
        while (1)
        {
        }

    case 2:
        irq = in_word(CNTP_STATUS_EL0);
        if (irq & (1 << 1))
        {
            timer_interrupt_handler(esr, elr, sp, spsr);
        }
        else
        {
            printk("unknown irq \r\n");
            while (1)
            {
            }
        }
        break;

    default:
        printk("unknown exception\r\n");
        while (1)
        {
        }
    }
}