#ifndef _REGISTER_H
#define _REGISTER_H
#include "amd64/trap.h"
#include "stdint.h"
#include "task.h"

//64为任务总数，registerList表示任务数组
struct TrapFrame registerList[64];

void set_task_register(int pid, uint64_t functionAddress, enum task_type type);
void save_registers(struct TrapFrame *curThread, struct TrapFrame *tf);

#endif
