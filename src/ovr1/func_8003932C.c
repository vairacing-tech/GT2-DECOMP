// builds only with GCC 2.8.1
#include "common.h"

extern s32 func_80075A5C(s32, s32);
extern s32 func_80075BF4(s32, s32);

s32 func_8003932C(u8* arg0) {
    register u8* self asm("$16");
    register u8* ptr asm("$2");
    s32 value;
    s32 sum;

    self = arg0;
    value = 0;

    switch (self[0x370]) {
        case 0:
        case 4:
        case 5:
            value = *(s32*)(self + 0x638);
            break;

        case 1:
        case 2:
            value = *(s32*)(self + 0x634);
            break;

        case 3:
            sum = *(s32*)(self + 0x634) + *(s32*)(self + 0x638);
            value = sum / 2;
            break;

        case 6:
            value = *(s32*)(self + 0x638) + func_80075A5C(*(s16*)(self + 0x374), *(s32*)(self + 0x634) - *(s32*)(self + 0x638));
            break;
    }

    if (self[0x618] == 0) {
        value = -value;
    }

    ptr = 0;
    if (value > 0) {
        ptr = self + (self[0x618] << 2);
        value = func_80075BF4(*(s32*)(ptr + 0x3A4), value);
        ptr = (u8*)func_80075BF4(0x28C, value);
    }

    return (s32)ptr;
}

static const s32 D_80046C58 = 0;
