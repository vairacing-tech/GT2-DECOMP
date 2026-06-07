// builds only with GCC 2.8.1
#include "common.h"

extern s32* func_80016328(void);
extern void func_80085B3C(s32*, const char*, s32*);
extern s32 D_800A8D60;
extern s32 D_801C6C10;

const char str_gt2_arcade_race_loop[] = "14ArcadeRaceLoop";
const char str_gt2_arcade_race_loop_empty[] = "";

s32* func_80017048(void) {
    if (D_801C6C10 == 0) {
        func_80016328();
        func_80085B3C(&D_801C6C10, str_gt2_arcade_race_loop, &D_800A8D60);
    }

    return &D_801C6C10;
}
