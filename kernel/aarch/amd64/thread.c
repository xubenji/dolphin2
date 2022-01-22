#include "stdlib.h"
#include "printk.h"
#include "amd64/trap.h"
#include "amd64/thread.h"

int tasksNum = 0;

void test_print1()
{
    while (1)
    {
        for (int i = 0; i < 30000000; i++)
        {
            /* code */
        }
        
        printk(" 1aa1 ");
    }
}

void test_print2()
{
    while (1)
    {
         for (int i = 0; i < 30000000; i++)
        {
            /* code */
        }
        printk(" 2bb2 ");
    }
}

void test_print3()
{
    while (1)
    {
         for (int i = 0; i < 30000000; i++)
        {
            /* code */
        }
        printk(" 3cc3 ");
    }
}

void init_thread()
{

    char name[64] = "000000000";
    for (int i = 0; i < 64; i++)
    {
        tasks[0].name[i] = name[i];
    }
    tasks[0].status = TASK_RUNNING;
    tasks[0].type = THREAD;
    tasks[0].registerAddress.errorcode = 0;
    tasks[0].registerAddress.cs = 8;
    tasks[0].registerAddress.rflags = 663;
    tasks[0].pid = 0;
    p = &tasks[0];
    tHead = p;
    tHead->before = p;
    tHead->next = p;
    tasksNum = 1;

    create_thread("111111", THREAD, &test_print1);
    create_thread("2222222", THREAD, &test_print2);
    create_thread("33333333333", THREAD, &test_print3);
}

void create_thread(char *name, enum task_type type, uint64_t functionAddress)
{
    // static struct TrapFrame tempFrame = {0};
    //  static struct task_list tempTask = {0};

    // tempTask.pid = p->pid + 1;

    // for (int i = 0; i < 64; i++)
    // {
    //     tempTask.name[i] = name[i];
    // }

    // //双链表来管理任务
    // tempTask.type = type;
    // tempTask.before = p;
    // tempTask.next = tHead;
    // p->next = &tempTask;
    // tHead->before = &tempTask;
    // p = p->next;

    // // p.pid = p.before.pid + 1;
    // tempTask.status = TASK_DIED;
    // //tempTask.registerAddress = tempRegister;
    // tempTask.registerAddress.rip = functionAddress;
    // tempTask.registerAddress.errorcode = 0;
    // tempTask.registerAddress.cs = 8;
    // tempTask.registerAddress.rflags = 663;
    // tempTask.registerAddress.rsp = 0xffff800000000000 + 0x400000 - (tempTask.pid * 0x1000);

    for (int i = 0; i < tasksNum; i++)
    {
        if (tasks[i].status == TASK_DIED)
        {
            p = &tasks[i];
            set_task_status(name, p, functionAddress, type);
            p->pid = p->before->pid + 1;
            return;
        }
    }
    tasksNum += 1;
    //p = &tasks[tasksNum];
    set_task_status(name, &tasks[tasksNum-1], functionAddress, type);
    link_task(&tasks[tasksNum-1]);
    p->pid = p->before->pid + 1;

    registerList[p->pid].rip = functionAddress;
    registerList[p->pid].errorcode = 0;
    registerList[p->pid].rflags = 663;
    registerList[p->pid].cs = 8;
    registerList[p->pid].rsp = 0xffff800000000000 + 0x400000 - (p->pid * 0x1000);
}

void set_task_status(char *name, struct task_list *p, uint64_t functionAddress, enum task_type type)
{
    for (int i = 0; i < 64; i++)
    {
        p->name[i] = name[i];
    }
    p->status = TASK_WAITTING;
    p->registerAddress.rip = functionAddress;
    p->registerAddress.errorcode = 0;
    p->registerAddress.cs = 8;
    p->registerAddress.rflags = 663;
    p->registerAddress.rsp = 0xffff800000000000 + 0x400000 - (p->pid * 0x1000);

    

}

uint64_t link_task(struct task_list *tempTask)
{
    p->next = tempTask;
    tempTask->before = p;
    p = p->next;
    p->next = tHead;
    tHead->before = p;
}

void save_registers(struct TrapFrame *curThread, struct TrapFrame *tf)
{
    curThread->ss = tf->ss;
    curThread->rsp = tf->rsp;
    curThread->rflags = tf->rflags;
    curThread->cs = tf->cs;
    curThread->rip = tf->rip;
    curThread->errorcode = tf->errorcode;
    curThread->trapno = tf->trapno;
    curThread->rax = tf->rax;
    curThread->rbx = tf->rbx;
    curThread->rcx = tf->rcx;
    curThread->rdx = tf->rdx;
    curThread->rsi = tf->rsi;
    curThread->rdi = tf->rdi;
    curThread->rbp = tf->rbp;
    curThread->r8 = tf->r8;
    curThread->r9 = tf->r9;
    curThread->r10 = tf->r10;
    curThread->r11 = tf->r11;
    curThread->r12 = tf->r12;
    curThread->r13 = tf->r13;
    curThread->r14 = tf->r14;
    curThread->r15 = tf->r15;
}