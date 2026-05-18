// builds only with GCC 2.8.1
#include "common.h"

extern s32 D_80052A4C;
extern u8 D_800BA144;

void func_80022838(void*);

void func_80022934(void) {
    D_80052A4C = -1;
    func_80022838(&D_800BA144);
}
