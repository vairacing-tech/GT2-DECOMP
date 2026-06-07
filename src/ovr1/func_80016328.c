// builds only with GCC 2.8.1
#include "common.h"

extern void func_80085B78(s32*, const char*);
extern s32 D_800A8D60;

const char str_gt2_race_menu_loop[] = "12RaceMenuLoop";

s32* func_80016328(void) {
    if (D_800A8D60 == 0) {
        func_80085B78(&D_800A8D60, str_gt2_race_menu_loop);
    }

    return &D_800A8D60;
}
