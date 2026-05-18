// builds only with GCC 2.8.1
#include "common.h"

u8* func_800224B0(u8* base, s32 index) {
    return base + *(u16*)(base + (index << 2));
}
