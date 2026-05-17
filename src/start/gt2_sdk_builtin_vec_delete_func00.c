// Builds only with GCC 2.8.1.
#include "common.h"
#include "structs.h"

void gt2_sdk_builtin_vec_delete_func00(gt2_heap_block* block) {
#ifdef MATCHING
    register u32 temp_v0 asm("v0");
    register u32 temp_v1 asm("v1");
#else
    u32 temp_v0;
    u32 temp_v1;
#endif

    temp_v1 = (u32)block->next;
    if (temp_v1 != 0) {
        temp_v0 = (u32)((gt2_heap_block*)temp_v1)->next;
        if (temp_v0 != 0) {
            ((gt2_heap_block*)temp_v0)->prev = block;
        }
        block->next = (gt2_heap_block*)temp_v0;
        temp_v0 = block->size;
        temp_v1 = ((gt2_heap_block*)temp_v1)->size;
        temp_v0 = temp_v0 + 0x10;
        temp_v0 = temp_v0 + temp_v1;
        block->size = temp_v0;
    }
}
