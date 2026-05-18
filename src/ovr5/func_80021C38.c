// builds only with GCC 2.8.1
#include "common.h"

extern s32 D_800B953C;
extern s32 D_80052A44;
extern u8 D_80052A48;

s32 func_80021C38(s32 arg0) {
    D_800B953C = arg0;
    D_80052A48 = 0;
    D_80052A44 = -1;
    return arg0 + 4;
}
