// builds only with GCC 2.8.1
#include "common.h"
#include "gt2_ovr5_loader.h"

extern s32 D_80052A4C;
extern s32 D_80052A50[];
extern gt2_ovr5_loader_state D_800BA144;

void func_80022758(gt2_ovr5_loader_state*, s32);
void func_80022794(gt2_ovr5_loader_state*, s32);

void func_800228D4(s32 index) {
    if (D_80052A4C != index) {
        D_80052A4C = index;
        func_80022758(&D_800BA144, D_80052A50[index]);
        func_80022794(&D_800BA144, 0);
    }
}
