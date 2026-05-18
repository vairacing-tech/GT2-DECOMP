// builds only with GCC 2.8.1
#include "common.h"

extern s32 D_80052A44;

u8* func_80021C5C(u8*, s32);

u8* func_80021CB4(u8* dst, s32 tag) {
    u8* entry;

    if (D_80052A44 == tag) {
        return dst;
    }

    D_80052A44 = tag;
    entry = func_80021C5C(dst, 1);
    *(s32*)entry = tag;
    return entry + 4;
}
