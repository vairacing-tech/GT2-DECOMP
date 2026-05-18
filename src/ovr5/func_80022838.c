// builds only with GCC 2.8.1
#include "common.h"
#include "gt2_ovr5_loader.h"

void gt2_main_shared_arcadegt_func6(void*);

void func_80022838(gt2_ovr5_loader_state* state) {
    if (state->active != 0) {
        gt2_main_shared_arcadegt_func6(state->payload);
    }
    state->active = 0;
}
