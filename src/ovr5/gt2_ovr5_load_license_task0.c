// builds only with GCC 2.8.1
#include "common.h"

extern char* gt2_main_strcpy_slim(char*, char*);
extern s32 gt2_main_strcmp(char*, char*);
extern char* D_80024418[];

s32 gt2_ovr5_load_license_task0(char* arg0) {
    char buf[16];
    s32 i;
    s32 ret;
    char** license_names;

    ret = 0;
    gt2_main_strcpy_slim(buf, arg0);
    i = ret;
    license_names = D_80024418;
    buf[3] = '\0';

    do {
        if (gt2_main_strcmp(*license_names, buf) == 0) {
            ret = i;
        }
        i++;
        license_names++;
    } while (i < 6);

    return ret;
}
