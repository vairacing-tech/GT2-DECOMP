// builds only with GCC 2.8.1
#include "common.h"

extern s32 gt2_main_sharedovr_sprintf(char*, const char*, ...);

const char str_gt2_decimal_format[] = "%d";

void gt2_ovr5_format_number(s16* arg0, s32 arg1) {
    char buf[64];
    s32 i;

    gt2_main_sharedovr_sprintf(buf, str_gt2_decimal_format, arg1);

    i = 0;
    *arg0 = (s8)((u8*)buf)[0];
    arg0++;
    if (((s8*)buf)[0] != '\0') {
        do {
            i++;
            *arg0 = (s8)((u8*)buf)[i];
            arg0++;
        } while (((s8*)buf)[i] != '\0');
    }
}
