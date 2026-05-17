// Builds only with GCC 2.8.1.
#include "common.h"
#include "structs.h"

void gt2_main_task0a_ovr_func20(gt2_heap_block* block, u32 requested_size) {
#ifdef MATCHING
    register gt2_heap_block* block_reg asm("a3");
    register u8* split_base asm("a0");
    register gt2_heap_block* split_block asm("a2");
    register u32 temp_v0 asm("v0");
    register u32 temp_v1 asm("v1");
#else
    gt2_heap_block* block_reg;
    u8* split_base;
    gt2_heap_block* split_block;
    u32 temp_v0;
    u32 temp_v1;
#endif

    block_reg = block;
    // Break value equivalence with the incoming a0 so the matching build keeps using a3.
    __asm__ volatile("" : "+r"(block_reg));
    temp_v0 = block_reg->size;
    temp_v1 = requested_size + 0x20;
    split_base = (u8*)block_reg + requested_size;
    if (temp_v0 < temp_v1) {
        return;
    }

    temp_v0 = (u32)block_reg->prev;
    *(gt2_heap_block**)(split_base + 0x10) = (gt2_heap_block*)temp_v0;
    temp_v1 = (u32)block_reg->next;
    split_block = (gt2_heap_block*)(split_base + 0x10);
    split_block->next = (gt2_heap_block*)temp_v1;
    temp_v0 = block_reg->size;
    split_block->size = temp_v0;
    temp_v1 = block_reg->used;
    split_block->used = temp_v1;

    temp_v1 = (u32)block_reg->next;
    block_reg->size = requested_size;
    temp_v0 = split_block->size;
    block_reg->next = split_block;
    *(gt2_heap_block**)(split_base + 0x10) = block_reg;
    split_block->used = 0;
    temp_v0 = temp_v0 - 0x10;
    temp_v0 = temp_v0 - requested_size;
    split_block->size = temp_v0;

    if (temp_v1 != 0) {
        ((gt2_heap_block*)temp_v1)->prev = split_block;
    }
}
