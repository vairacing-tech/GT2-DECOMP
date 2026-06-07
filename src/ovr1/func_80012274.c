// builds only with GCC 2.8.1
#include "common.h"

extern s32* func_80016368(void);
extern void func_80085B3C(s32*, const char*, s32*);
extern s32 D_800A94D0;
extern s32 D_800A94F0;

const char str_gt2_race_development[] = "15RaceDevelopment";
const char str_gt2_race_development_empty[] = "";

s32* func_80012274(void) {
    if (D_800A94D0 == 0) {
        func_80016368();
        func_80085B3C(&D_800A94D0, str_gt2_race_development, &D_800A94F0);
    }

    return &D_800A94D0;
}
