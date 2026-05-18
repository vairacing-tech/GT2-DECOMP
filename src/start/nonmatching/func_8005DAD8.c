// Reference reconstruction only.
//
// The original binary delays the stack-frame allocation until after:
//   move a1, a0
//   lui  a0, %hi(gt2_overlay_archive)
//   addiu a0, a0, %lo(gt2_overlay_archive)
//
// The current GCC 2.8.1-based build path emits the frame allocation first for
// every equivalent C shape tested so far, so the exact build keeps the original
// assembly until that compiler-scheduling gap is resolved deliberately.
#include "common.h"
#include "structs.h"

extern gt2_overlay_archive_state gt2_overlay_archive;
extern s32 D_801C93D0;
extern s32 D_801C93E0;
extern s32 D_800A8D5C;
extern void gt2_main_task200_spu_voice00_vol(gt2_overlay_archive_state*, s32);
extern void gt2_main_task202(void);
extern void gt2_main_task2001(s32*, s32, s32);
extern void gt2_main_gzip_decompress_setup(s32, s32);
extern void gt2_ovr0_task0a_ovr_func0(void);
extern void FlushCache(void);
extern void gt2_sysinit_task0(void);

void func_8005DAD8(s32 overlay_index) {
    gt2_overlay_archive_entry* entry;
    s32 payload_base;

    gt2_main_task200_spu_voice00_vol(&gt2_overlay_archive, overlay_index);
    gt2_main_task202();

    entry = &gt2_overlay_archive.entries[overlay_index];
    if (gt2_overlay_archive.cached_payload != 0) {
        payload_base = gt2_overlay_archive.cached_payload;
    } else {
        payload_base = (s32)&D_800A8D5C;
        gt2_main_task2001((s32*)payload_base, D_801C93D0, D_801C93E0);
    }

    gt2_main_gzip_decompress_setup(
        payload_base + entry->payload_offset,
        (s32)gt2_ovr0_task0a_ovr_func0
    );
    FlushCache();
    gt2_sysinit_task0();
}
