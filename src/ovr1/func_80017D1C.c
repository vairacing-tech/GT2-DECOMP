// builds only with GCC 2.8.1
#include "common.h"

extern u8 D_801C98E0[];
extern s8 D_801EF5F2;

extern void func_80017438(void*, s32);
extern void func_80015F48(void*);
extern void func_80017498(void*, s32);

s32 func_80017D1C(s32 arg0) {
    u8 buffer[0x5E0];
    register u8* base asm("$2");
    register s32 offset asm("$3");
    register s32 ret asm("$4");
    s32 index;
    s32 status;

    base = D_801C98E0;
    offset = 0xBF7C;
    base += offset;
    index = base[0xA] - 1;

    switch (index) {
        case 11:
            arg0 = 1;
            /* fallthrough */

        case 0:
        case 1:
        case 2:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            func_80017438(buffer, arg0);
            func_80015F48(buffer);
            func_80017498(buffer, 2);
            break;

        case 3:
        case 4:
        case 5:
        default:
            break;
    }

    ret = 1;
    status = D_801EF5F2;
    if (status >= 0) {
        if (status >= 3) {
            if (status == 3) {
                ret = 4;
            }
        }
    }

    return ret;
}
