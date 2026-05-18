// builds only with GCC 2.8.1
#include "common.h"
#include "gt2_ovr5_loader.h"

void gt2_memset(void*, s32, s32);
void gt2_main_task0b20(void*, s32, s32);

void func_800226A0(gt2_ovr5_loader_state* state, s32 arg1, s32 arg2) {
    gt2_memset(state, 0, 0x2BC);
    gt2_main_task0b20(state, arg1, arg2);
}
