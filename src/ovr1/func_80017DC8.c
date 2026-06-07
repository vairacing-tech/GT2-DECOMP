// builds only with GCC 2.8.1
#include "common.h"

extern void func_80085B3C(s32*, const char*, s32*);
extern s32* func_80016328(void);
extern s32 D_800A8D60;
extern s32 D_801C6C20;

const char str_gt2_gran_turismo_race_loop[] = "19GranTurismoRaceLoop";

s32* func_80017DC8(void) {
    if (D_801C6C20 == 0) {
        func_80016328();
        func_80085B3C(&D_801C6C20, str_gt2_gran_turismo_race_loop, &D_800A8D60);
    }

    return &D_801C6C20;
}
