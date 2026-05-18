#include "common.h"

extern void* D_8009286C;
extern void* gt2_main_gtmode_get_part_number_binary_chop(void*, s32, s32);

void* gt2_ovr5_get_main_car_part_number_by_car_id(s32 car_id) {
    return gt2_main_gtmode_get_part_number_binary_chop(D_8009286C, 0x1D, car_id);
}
