// builds only with GCC 2.8.1
#include "common.h"

extern s32 D_80052A4C;
extern s32 D_80052A50[];
extern u8 D_800BA144;

void func_80022758(void*, s32);
void func_80022794(void*, s32);

void func_800228D4(s32 index) {
    if (D_80052A4C != index) {
        D_80052A4C = index;
        func_80022758(&D_800BA144, D_80052A50[index]);
        func_80022794(&D_800BA144, 0);
    }
}
