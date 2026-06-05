// builds only with GCC 2.8.1
#include "common.h"

extern s32 gt2_main_strcmp(char*, const char*);

const char str_gt2_world_cup_prefix[] = "GTW";

s32 gt2_ovr5_is_gt_world_cup(char* arg0) {
    char buf[4];
    s32 i;

    for (i = 0; i < 3; i++) {
        buf[i] = ((u8*)arg0)[i];
        if (((s8*)arg0)[i] == '\0') {
            break;
        }
    }

    buf[i] = '\0';
    return gt2_main_strcmp(buf, str_gt2_world_cup_prefix) == 0;
}
