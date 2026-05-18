// builds only with GCC 2.8.1
#include "common.h"

extern u8* D_800A8D80;
u8* func_800223B0(u8*, s32);

u8* func_8002237C(u8* base, s32 index) {
    return func_800223B0(D_800A8D80, *(u16*)(base + (index << 1)));
}
