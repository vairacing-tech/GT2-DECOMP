// builds only with GCC 2.8.1
#include "common.h"

extern s32 gt2_main_strcmp(char*, const char*);

const char str_gt2_machine_test_g400[] = "G400";
const char str_gt2_machine_test_g1000[] = "G1000";
const char str_gt2_machine_test_gmax[] = "GMAX";

s32 gt2_ovr5_get_machine_test_game_mode(char* arg0) {
    if (gt2_main_strcmp(arg0, str_gt2_machine_test_g400) == 0) {
        return 7;
    }

    if (gt2_main_strcmp(arg0, str_gt2_machine_test_g1000) == 0) {
        return 8;
    }

    if (gt2_main_strcmp(arg0, str_gt2_machine_test_gmax) == 0) {
        return 9;
    }

    return -1;
}
