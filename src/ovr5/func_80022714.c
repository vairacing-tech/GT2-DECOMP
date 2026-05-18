// builds only with GCC 2.8.1
#include "common.h"
#include "gt2_ovr5_loader.h"

u32 gt2_main_task0b21(gt2_ovr5_loader_state*, s32, s32, s32);

void func_80022714(gt2_ovr5_loader_state* state, s32 arg1) {
    u32 read_size = gt2_main_task0b21(state, arg1, 0, 1);
    state->read_dst = state->base + ((read_size + 3) & ~3);
}
