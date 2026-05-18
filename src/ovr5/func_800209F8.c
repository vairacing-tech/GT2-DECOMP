#include "common.h"

typedef struct {
    u8 pad0[0x10];
    s16 x;
    s16 y;
} gt2_ovr5_pair16_at_0x10;

extern gt2_ovr5_pair16_at_0x10 D_8005299C;

void func_800209F8(s32 unused, s16 x, s16 y) {
    D_8005299C.x = x;
    D_8005299C.y = y;
}
