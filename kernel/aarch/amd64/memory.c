#include "amd64/memory.h"
#include "printk.h"
#include "debug.h"

static struct FreeMemRegion FreeMemRegion[50];

void init_memory(void){
    int32_t count=*(int32_t*)0x9000;
    uint64_t total_mem=0;
    struct E820 *mem_map=(struct E820*)0x9008;
    int free_region_count=0;

    ASSERT(count <= 50);

    for(int32_t i = 0; i< count; i++){
        if(mem_map[i].type == 1){
            FreeMemRegion[free_region_count].address = mem_map[i].address;
            FreeMemRegion[free_region_count].length = mem_map[i].length;
            total_mem += mem_map[i].length;
            free_region_count++;
        }
    }

}
