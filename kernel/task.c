/** 
 * Name: task.c
 * Author: Benji Xu <benjixu2020@gmail.com>
 * Date: 2022-01-20 12:21:48
 * LastEditTime: 2022-01-22 06:10:46
 * LastEditors: Benji Xu
 * FilePath: /dolphin2/kernel/task.c
 * Description: task scheduling fit into the x86 and arm. 
 * 描述: 任务调度代码，适用于x86和arm
 */
#include "stdint.h"
#include "printk.h"
#include "task.h"

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

/** 
 * @function: init_thread
 * @param [void]
 * @return [void]
 * description: 初始化线程所需要的环境，其实就是把kernel进程初始化为0号进程，并且把kernel线程设置为正在运行
 */
void init_thread(void)
{

    char name[64] = "000000000";
    for (int i = 0; i < 64; i++)
    {
        tasks[0].name[i] = name[i];
    }
    tasks[0].status = TASK_RUNNING;
    tasks[0].type = THREAD;
    tasks[0].pid = 0;
    set_task_register(0, 0);
    p = &tasks[0];
    tHead = p;
    tHead->before = p;
    tHead->next = p;
    tasksNum = 1;

    //测试代码
    create_thread("111111", THREAD, &test_print1);
    create_thread("2222222", THREAD, &test_print2);
    create_thread("33333333333", THREAD, &test_print3);
}

void create_thread(char *name, enum task_type type, uint64_t functionAddress)
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
    tasksNum ++;
    link_task(&tasks[tasksNum - 1]);
    set_task_status(name, &tasks[tasksNum - 1], functionAddress, type);
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

