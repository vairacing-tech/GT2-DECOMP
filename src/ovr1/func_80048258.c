// builds only with GCC 2.8.1
#include "common.h"

extern void func_80080038(void);
extern void func_80085B3C(s32*, const char*, s32*);
extern s32 D_801C9140;
extern s32 D_801F0CE0;

const char str_gt2_quick_menu[] = "9QuickMenu";

s32* func_80048258(void) {
    if (D_801C9140 == 0) {
        func_80080038();
        func_80085B3C(&D_801C9140, str_gt2_quick_menu, &D_801F0CE0);
    }

    return &D_801C9140;
}
