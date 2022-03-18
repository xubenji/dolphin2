#ifndef _THREAD_H_
#define _THREAD_H_
#include "stdint.h"
#define tasksNumber 64

enum task_type
{
    KERNEL = 0,
    PROCESS = 1,
};

//我们设置了六种状态，初始值为TASK_WAIITING = 0
enum task_status
{
    TASK_WAITTING,
    TASK_READY,
    TASK_BLOCKED,
    TASK_RUNNING,
    TASK_HANGING,
    TASK_DIED
};

//包含了线程和进程
struct task_list
{
    char name[1024];
    uint32_t pid;
    enum task_type type;
    enum task_status status;
    struct task_list *before;
    struct task_list *next;
    uint64_t dir0;
    uint64_t dir1;
    uint64_t dir2;
};

struct task_list tasks[tasksNumber];
struct task_list *p;
struct task_list *tHead;

void init_task(void);
void create_task(char *name, enum task_type type, uint64_t functionAddress, int pid);
void set_task_status(char *name, struct task_list *p, uint64_t functionAddress, enum task_type type);
uint64_t link_task(struct task_list *temp);
void set_task_memory();
void set_page_dir_address_for_task();
void set_task_virtual_address(uint64_t dir0, uint64_t dir1, uint64_t dir2, int pages);

#endif