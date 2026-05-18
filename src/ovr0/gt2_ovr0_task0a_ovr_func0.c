// Builds only with GCC 2.8.1.
#include "common.h"
#include "structs.h"

typedef struct {
    u16 unk0;
    s32 load_base;
    u32 unk6;
    s32 payload_size;
} __attribute__((packed)) gt2_ovl_boot_header;

extern s32 D_801C93D0;
extern s32 D_801C93E0;
extern s32 D_801C93E8;
extern s32* gt2_main_task0a_ovr_func1(char*);
extern s32 gt2_main_task0a_ovr_func2(s32);
extern void gt2_main_task2001(s32*, s32, s32);
extern void gt2_main_memcpy(s32*, s32, s32);

const char str_gt2_ovl_name[] = "gt2.ovl";

void gt2_ovr0_task0a_ovr_func0(gt2_overlay_archive_state* archive) {
    gt2_ovl_boot_header* header;
#ifdef MATCHING
    register s32 temp_v1 asm("v1");
    register s32 temp_a0 asm("a0");
    register s32 temp_a1 asm("a1");
#else
    s32 temp_v1;
    s32 temp_a0;
    s32 temp_a1;
#endif
    s32 temp_v0;
    s32 temp_s0;

    header = (gt2_ovl_boot_header*)gt2_main_task0a_ovr_func1((char*)&str_gt2_ovl_name);
    temp_v1 = header->load_base;
    // Keep the unaligned header load before the global load, like the original code.
    __asm__ volatile("" ::: "memory");
    temp_a1 = D_801C93E8;
    temp_v1 = temp_v1 - temp_a1;
    archive->payload_load_delta = temp_v1;

    temp_v1 = header->payload_size;
    temp_v0 = *(volatile s32*)&archive->payload_load_delta;
    temp_a0 = temp_v1;
    // Break value equivalence so the matching build keeps using v1 for the stores below.
    __asm__ volatile("" : "+r"(temp_v1));
    archive->payload_size = temp_v1;
    // Preserve the original store-before-add scheduling.
    __asm__ volatile("" ::: "memory");

    temp_s0 = temp_a1 + temp_v0;
    D_801C93D0 = temp_s0;
    D_801C93E0 = temp_v1;
    archive->cached_payload = gt2_main_task0a_ovr_func2(temp_a0);

    if (archive->cached_payload == 0) {
        gt2_main_task2001((s32*)archive->entries, temp_s0, 0x30);
    } else {
        gt2_main_task2001((s32*)archive->cached_payload, temp_s0, archive->payload_size);
    }

    if (archive->cached_payload != 0) {
        gt2_main_memcpy((s32*)archive->entries, archive->cached_payload, 0x30);
    }
}
