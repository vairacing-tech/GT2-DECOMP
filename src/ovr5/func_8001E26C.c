// builds only with GCC 2.8.1
#include "common.h"

#define GT2_OVR5_FIXED_BOUND 0x989680

typedef struct gt2_ovr5_position_bounds_state {
    s16 pos_x;
    s16 pos_y;
    u8 pad_04[8];
    u16 initial_x;
    u16 initial_y;
    s32 bound_x;
    s32 bound_y;
    s32 pos_x_fixed;
    s32 pos_y_fixed;
} gt2_ovr5_position_bounds_state;

void func_8001E26C(gt2_ovr5_position_bounds_state* state, s32 mode) {
    s32 bound_x = 0;
    s32 bound_y = 0;

    state->pos_x = state->initial_x;
    state->pos_y = state->initial_y;
    state->pos_x_fixed = state->pos_x << 8;
    state->pos_y_fixed = state->pos_y << 8;

    switch (mode - 2) {
    case 2:
        bound_x = GT2_OVR5_FIXED_BOUND;
        break;
    case 5:
        bound_x = GT2_OVR5_FIXED_BOUND;
        bound_y = GT2_OVR5_FIXED_BOUND;
        break;
    case 4:
        bound_x = -GT2_OVR5_FIXED_BOUND;
        bound_y = GT2_OVR5_FIXED_BOUND;
        break;
    case 0:
        bound_y = GT2_OVR5_FIXED_BOUND;
        break;
    case 3:
        bound_x = -GT2_OVR5_FIXED_BOUND;
        break;
    case 6:
        bound_x = -GT2_OVR5_FIXED_BOUND;
        bound_y = -GT2_OVR5_FIXED_BOUND;
        break;
    case 7:
        bound_x = GT2_OVR5_FIXED_BOUND;
        bound_y = -GT2_OVR5_FIXED_BOUND;
        break;
    case 1:
        bound_y = -GT2_OVR5_FIXED_BOUND;
        break;
    }

    state->bound_x = bound_x;
    state->bound_y = bound_y;
}
