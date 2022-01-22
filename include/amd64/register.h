#ifndef _REGISTER_H
#define _REGISTER_H
#include "amd64/trap.h"
#include "stdint.h"

struct TrapFrame registerList[64];

void set_task_register(int pid, uint64_t functionAddress);
void save_registers(struct TrapFrame *curThread, struct TrapFrame *tf);

#endif
