// builds only with GCC 2.8.1
#include "common.h"

typedef struct {
    u32 unk0;
    u32 unk4;
} gt2_ovr5_entry8;

extern s16 D_800529A2;
extern gt2_ovr5_entry8* D_800B9510;

u32 func_80020C24(void) {
    return D_800B9510[D_800529A2].unk4 & 0xFFFFFF;
}
