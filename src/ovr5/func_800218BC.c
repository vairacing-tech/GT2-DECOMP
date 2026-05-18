#include "common.h"

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0x8];
    s32 unk18;
    u8 pad1C[0x2];
    s16 unk1E;
    u8 pad20[0x4];
    u8 unk24;
    u8 unk25;
} gt2_ovr5_state_800B9514;

extern gt2_ovr5_state_800B9514 D_800B9514;

void func_800218BC(void) {
    D_800B9514.unkC = 0;
    D_800B9514.unk24 = 0;
    D_800B9514.unk25 = 0;
    D_800B9514.unk18 = 0;
    D_800B9514.unk1E = 0;
}
