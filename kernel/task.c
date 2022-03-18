/**
 * Name: task.c
 * Author: Benji Xu <benjixu2020@gmail.com>
 * Date: 2022-01-20 12:21:48
 * LastEditTime: 2022-03-11 23:55:12
 * LastEditors: Benji Xu
 * FilePath: /dolphin2/kernel/task.c
 * Description: task scheduling fit into the x86 and arm.
 * I suggest you pay more attention on set_task_register(),
 * because only this function call the code having to do with the cpu arch.
 * 描述: 任务调度代码，适用于x86和arm。你只需要注意set_task_register。
 * 因为只有这个函数调用了和处理器架构相关的代码。
 */
#include "stdint.h"
#include "printk.h"
#include "task.h"
#include "arm/memory.h"

int tasksNum = 0;

void test_print1()
{
    while (1)
    {
        for (int i = 0; i < 10000; i++)
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
        for (int i = 0; i < 10000; i++)
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
        for (int i = 0; i < 10000; i++)
        {
            /* code */
        }
        printk(" 3cc3 ");
    }
}

/**
 * @function: init_task
 * @param [void]
 * @return [void]
 * description: 初始化进程所需要的环境，其实就是把kernel进程初始化为0号进程，并且把kernel进程设置为正在运行
 */
void init_task(void)
{

    char name[64] = "000000000";
    for (int i = 0; i < 64; i++)
    {
        tasks[0].name[i] = name[i];
    }
    tasks[0].status = TASK_RUNNING;
    tasks[0].type = KERNEL;
    tasks[0].pid = 0;
    set_task_register(0, 0);
    p = &tasks[0];
    tHead = p;
    tHead->before = p;
    tHead->next = p;
    tasksNum = 1;

    //测试代码
    // uint64_t print1 = &test_print1;
    // uint64_t print2 = &test_print2;
    // uint64_t print3 = &test_print3 - KERNEL_BASE;
    // create_task("111111", KERNEL, &test_print1);
    // create_task("2222222", KERNEL, &test_print2);
    // create_task("33333333333", KERNEL, &test_print3);
}

/**
 * function: create_task
 * @param [char] *name 进程的名字 ｜ name of the thread
 * @param [enum task_type] type 任务的类型 ｜ the type of task(KERNEL or nomral PROCESS?)
 * @param [uint64_t] functionAddress 进程运行的起始地址 ｜ the entry address of the process
 * @param [int] pid:检查要创建的线程是否属于某一个进程，如果不输入任意一个进程pid为-1 ｜ To check if the thread to create belongs one process. if not, it equal -1
 * @return [void]
 * description: 这是创建任务的函数，不管是线程还是进程我们统一称为任务，操作系统只调度任务，而不会调度进程。也有可能多个任务共享同一个虚拟地址空间，也有可能多个任务并不共享虚拟地址空间。
 */
void create_task(char *name, enum task_type type, uint64_t functionAddress, int pid)
{
    if (pid == -1)
    {
        for (int i = 0; i < tasksNum; i++)
        {
            if (tasks[i].status == TASK_DIED)
            {
                p = &tasks[i];
                set_task_status(name, p, functionAddress, type);
                return;
            }
        }
        tasksNum++;
        link_task(&tasks[tasksNum - 1]);
        set_task_status(name, &tasks[tasksNum - 1], functionAddress, type);

        set_task_memory();

        malloc_page(1);
        uint64_t dir0 = processAddr.lastPhyAddress + 0x1f0000;
        uint64_t dir1 = dir0 + 0x1000;
        uint64_t dir2 = processAddr.lastPhyAddress;
        set_page_dir_address_for_task();
        int pages = 1;
        set_task_virtual_address(dir0, dir1, dir2, pages);
    }
    else
    {
    }
}

/**
 * @function: set_task_status
 * @param [char] *name: the name of the task
 * @param [task_list] *p: the pointer of to set task
 * @param [uint64_t] functionAddress: the task address
 * @param [enum task_type] type: the type of the task
 * @return [void]
 * description: 设置任务的状态，其实就是初始化任务所需要的数据，还把一些初始值填入寄存器
 */
void set_task_status(char *name, struct task_list *p, uint64_t functionAddress, enum task_type type)
{
    for (int i = 0; i < 64; i++)
    {
        p->name[i] = name[i];
    }
    p->status = TASK_WAITTING;
    p->pid = p->before->pid + 1;
    set_task_register(p->pid, functionAddress);
}

/**
 * @function: link_list
 * @param [task_list] *tempTask: to set task's pointer
 * @return [void]
 * description: 将新任务的结构体加入双链表
 */
uint64_t link_task(struct task_list *tempTask)
{
    p->next = tempTask;
    tempTask->before = p;
    p = p->next;
    p->next = tHead;
    tHead->before = p;
}

void set_task_memory()
{
    
}

void set_task_virtual_address(uint64_t dir0, uint64_t dir1, uint64_t dir2, int pages)
{
    p->dir0 = dir0;
    p->dir1 = dir1;
    p->dir2 = dir2;
}