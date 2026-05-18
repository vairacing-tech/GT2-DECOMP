// builds only with GCC 2.8.1
#include "common.h"

typedef struct {
    u32 unk0;
    u8 pad4[3];
    s8 unk7;
} gt2_ovr5_entry8_tail_byte;

extern s16 D_800529A2;
extern gt2_ovr5_entry8_tail_byte* D_800B9510;

s8 func_80020C00(void) {
    return D_800B9510[D_800529A2].unk7;
}
