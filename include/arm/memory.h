#ifndef _MEMORY_H
#define _MEMORY_H

#include "stdint.h"

#define KERNEL_BASE 0xffff000000000000

#define P2V(p) ((uint64_t)(p) + KERNEL_BASE)
#define V2P(v) ((uint64_t)(v) - KERNEL_BASE)


#endif
