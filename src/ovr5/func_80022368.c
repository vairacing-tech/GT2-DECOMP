// builds only with GCC 2.8.1
#include "common.h"

u8* func_80022368(u8* base, s32 index) {
    return base + *(u16*)(base + (index << 1) + 8);
}
