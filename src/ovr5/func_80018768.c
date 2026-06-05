// builds only with GCC 2.8.1
#include "common.h"

extern s32 gt2_main_strcmp(char*, const char*);

const char str_gt2_free_race01[] = "FREERACE01";
const char str_gt2_free_race02[] = "FREERACE02";
const char str_gt2_free_race03[] = "FREERACE03";

s32 func_80018768(char* arg0) {
    if (gt2_main_strcmp(arg0, str_gt2_free_race01) == 0) {
        return 0;
    }

    if (gt2_main_strcmp(arg0, str_gt2_free_race02) == 0) {
        return 1;
    }

    if (gt2_main_strcmp(arg0, str_gt2_free_race03) == 0) {
        return 2;
    }

    return 3;
}
