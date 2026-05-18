#include "common.h"

extern void* D_80092870;
extern void* gt2_main_gtmode_get_part(void*, s32, s32);

void* func_80021A40(s32 car_id) {
    return gt2_main_gtmode_get_part(D_80092870, 0, car_id);
}
