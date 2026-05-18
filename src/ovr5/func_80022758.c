// builds only with GCC 2.8.1
#include "common.h"
#include "gt2_ovr5_loader.h"

void gt2_main_task0b11(s32, u32);
void gt2_main_shared_arcade_func3(u32);

void func_80022758(gt2_ovr5_loader_state* state, s32 slot) {
    gt2_main_task0b11(slot, state->read_dst);
    gt2_main_shared_arcade_func3(state->read_dst);
}
