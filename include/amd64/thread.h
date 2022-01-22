#ifndef _THREAD_H_
#define _THREAD_H_
#include "amd64/trap.h"
#include "stdint.h"

enum task_type
{
    THREAD,
    PROCESS,
};

enum task_status
{
    TASK_RUNNING,
    TASK_READY,
    TASK_BLOCKED,
    TASK_WAITTING,
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
    struct TrapFrame registerAddress;
    struct task_list *before;
    struct task_list *next;
};

static struct task_list tasks[64];
struct TrapFrame registerList[64];

struct task_list *p;
struct task_list *tHead;

void init_thread(void);
void create_thread(char *name, enum task_type type, uint64_t functionAddress);
void set_task_status(char *name, struct task_list *p, uint64_t functionAddress, enum task_type type);
uint64_t link_task(struct task_list *temp);
void save_registers(struct TrapFrame *curThread, struct TrapFrame *tf);

#endif