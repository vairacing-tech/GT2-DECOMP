#include "common.h"

typedef struct {
    u8 pad0[0x10];
    s16 x;
    s16 y;
} gt2_ovr5_pair16_at_0x10;

extern gt2_ovr5_pair16_at_0x10 D_80052958;

void func_800204D8(s32 unused, s16 x, s16 y) {
    D_80052958.x = x;
    D_80052958.y = y;
}
