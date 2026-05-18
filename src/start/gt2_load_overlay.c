// Builds only with GCC 2.8.1.
#include "common.h"
#include "structs.h"

extern gt2_overlay_continuation_args D_801C945C;
extern gt2_saved_registers D_801C942C;
extern void func_8005DAD8(s32);
extern void gt2_main_task201_reload_regs(gt2_saved_registers*, s32) __attribute__((noreturn));

void gt2_load_overlay(s32 overlay_index, s32 entrypoint, ...) {
#ifdef MATCHING
    register s32 entrypoint_reg asm("s0");
    register s32* stack_ptr asm("sp");
#else
    s32 entrypoint_reg;
    s32* stack_ptr;
#endif

    entrypoint_reg = entrypoint;
    D_801C945C.arg0 = stack_ptr[8];
    D_801C945C.arg1 = stack_ptr[9];
    D_801C945C.arg2 = stack_ptr[10];
    D_801C945C.arg3 = stack_ptr[11];
    func_8005DAD8(overlay_index);
    gt2_main_task201_reload_regs(&D_801C942C, entrypoint_reg);
}
