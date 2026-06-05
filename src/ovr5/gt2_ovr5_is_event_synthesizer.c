// builds only with GCC 2.8.1
#include "common.h"

extern s32 gt2_main_strcmp(char*, const char*);

const char str_gt2_free_race_prefix[] = "FREERACE";
const char str_gt2_free_champ_prefix[] = "FREECHAMP";

s32 gt2_ovr5_is_event_synthesizer(char* arg0) {
    char buf[64];
    s32 i;

    for (i = 0; i < 8; i++) {
        buf[i] = ((u8*)arg0)[i];
        if (((s8*)arg0)[i] == '\0') {
            break;
        }
    }
    buf[i] = '\0';

    if (gt2_main_strcmp(buf, str_gt2_free_race_prefix) == 0) {
        return 1;
    }

    for (i = 0; i < 9; i++) {
        buf[i] = ((u8*)arg0)[i];
        if (((s8*)arg0)[i] == '\0') {
            break;
        }
    }
    buf[i] = '\0';

    return gt2_main_strcmp(buf, str_gt2_free_champ_prefix) == 0;
}
