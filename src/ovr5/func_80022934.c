// builds only with GCC 2.8.1
#include "common.h"
#include "gt2_ovr5_loader.h"

extern s32 D_80052A4C;
extern gt2_ovr5_loader_state D_800BA144;

void func_80022838(gt2_ovr5_loader_state*);

void func_80022934(void) {
    D_80052A4C = -1;
    func_80022838(&D_800BA144);
}
