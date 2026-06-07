// builds only with GCC 2.8.1
#include "common.h"

extern u8 D_800AF230;
extern u8 D_801C98E0[];

extern u8* func_80060E94(s32);

s32 func_800418E8(void) {
    register s32 ret asm("$16");
    register u8* base asm("$2");
    register s32 offset asm("$3");
    register u8* ptr asm("$4");
    register s32 value asm("$2");
    register s32 one asm("$3");

    base = D_801C98E0;
    offset = 0xBF7C;
    base += offset;
    ret = 0;

    switch (base[0xA]) {
        case 3:
            ret = 1;
            break;

        case 0:
            base = func_80060E94(D_800AF230);
            if ((*(u16*)(base + 8) & 4) == 0) {
                base = D_801C98E0;
                offset = 0xBF7C;
                base += offset;
                one = base[4];
                value = 1;
                goto compare;
            }
            break;

        case 2:
        case 4:
        case 12:
            base = func_80060E94(D_800AF230);
            if ((*(u16*)(base + 8) & 4) == 0) {
                base = D_801C98E0;
                offset = 0xBF7C;
                ptr = base + offset;
                value = ptr[9];
                one = 1;
                if (value == one) {
                    return ret;
                }
                value = ptr[1];
                // Keep the shared compare label after this load-delay nop.
                __asm__ volatile("nop");
compare:
                if (value == one) {
                    ret = 2;
                }
            }
            break;
    }

    return ret;
}

static const s32 D_80046CDC = 0;
