// Builds only with GCC 2.8.1.
#include "common.h"

extern s32 D_80092E88;

void gt2_main_task200_spu_voice00_vol(void) {
#ifdef MATCHING
    register s32 spin_count asm("a2");
    register s32 any_voice_active asm("a1");
    register s32 voice_index asm("a0");
    register s32 timeout asm("t0");
    register volatile u8* voice_base asm("a3");
    register volatile u8* voice_ptr asm("v1");
#else
    s32 spin_count;
    s32 any_voice_active;
    s32 voice_index;
    s32 timeout;
    volatile u8* voice_base;
    volatile u8* voice_ptr;
#endif

    if (D_80092E88 != 0) {
        spin_count = 0;
        timeout = 0x675BFF;
        voice_base = (volatile u8*)0x1F801C00;
        while (1) {
            if (timeout < spin_count) {
                return;
            }
            any_voice_active = 0;
            voice_index = any_voice_active;
            voice_ptr = voice_base;
            do {
                if (*(volatile u16*)(voice_ptr + 0xC) != 0) {
                    any_voice_active = 1;
                }
                voice_index++;
                voice_ptr += 0x10;
            } while (voice_index < 0x18);
            if (any_voice_active == 0) {
                return;
            }
            spin_count++;
        }
    }
}
