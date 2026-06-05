// builds only with GCC 2.8.1
#include "common.h"

extern s32 gt2_main_strcmp(char*, const char*);

const char str_gt2_international_league_pfl[] = "PFL";
const char str_gt2_international_league_epl_and_event_ids[] =
    "EPL\0"
    "GJL0001\0"
    "GJL0002\0"
    "GJL0003\0"
    "GBL0001\0"
    "GBL0002\0"
    "GBL0003\0"
    "GFL0001\0"
    "GFL0002\0"
    "GGL0001\0"
    "GGL0002\0"
    "GGL0003\0"
    "GIL0001\0"
    "GIL0002\0"
    "GUL0001\0"
    "GUL0002\0"
    "GUL0003\0"
    "PFL0001\0"
    "PFL0002\0"
    "PFL0003\0"
    "EPL0001\0"
    "EPL0002\0"
    "EPL0003";

s32 gt2_ovr5_is_international_league(char* arg0) {
    char buf[4];
    s32 i;

    for (i = 0; i < 3; i++) {
        buf[i] = ((u8*)arg0)[i];
        if (((s8*)arg0)[i] == '\0') {
            break;
        }
    }
    buf[i] = '\0';

    if (gt2_main_strcmp(buf, str_gt2_international_league_pfl) == 0) {
        return 1;
    }

    return gt2_main_strcmp(buf, str_gt2_international_league_epl_and_event_ids) == 0;
}
