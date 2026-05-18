// builds only with GCC 2.8.1
#include "common.h"

extern void* D_8009286C;

u32 gt2_ovr5_get_main_car_part_number_by_car_id(s32);
u8* gt2_main_gtmode_get_part(void*, s32, s32);

u8 func_80021BEC(s32 car_id, s32 alternate_byte) {
    u8* part = gt2_main_gtmode_get_part(
        D_8009286C,
        0x1D,
        gt2_ovr5_get_main_car_part_number_by_car_id(car_id)
    );
    u8 value = part[7];

    if (alternate_byte != 0) {
        value = part[6];
    }

    return value;
}
