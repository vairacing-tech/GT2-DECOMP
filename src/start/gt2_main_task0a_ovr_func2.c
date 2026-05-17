// Builds only with GCC 2.8.1.
#include "common.h"
#include "structs.h"

extern gt2_heap_block* D_800A8D50;
extern void gt2_main_task0a_ovr_func20(gt2_heap_block*, u32);

void* gt2_main_task0a_ovr_func2(u32 requested_size) {
    gt2_heap_block* block;
    gt2_heap_block* best_block;
    u32 aligned_size;
    void* result;

    best_block = NULL;
    aligned_size = (requested_size + 0xF) & ~0xF;
    block = D_800A8D50;

    while (block != NULL) {
        if (block->used == 0 && block->size >= aligned_size) {
            if (best_block == NULL || (u32)block->size < (u32)best_block->size) {
                best_block = block;
            }
        }
        block = block->next;
    }

    if (best_block != NULL) {
        gt2_main_task0a_ovr_func20(best_block, aligned_size);
        best_block->used = 1;
        result = best_block + 1;
    } else {
        result = NULL;
    }

    return result;
}
