// builds only with GCC 2.8.1
#include "common.h"

extern void func_80080038(void);
extern void func_80085B3C(s32*, const char*, s32*);
extern s32 D_801C9100;
extern s32 D_801F0CE0;

const char str_gt2_pre_quick_menu_io[] = "14PreQuickMenuIO";

s32* func_80048208(void) {
    if (D_801C9100 == 0) {
        func_80080038();
        func_80085B3C(&D_801C9100, str_gt2_pre_quick_menu_io, &D_801F0CE0);
    }

    return &D_801C9100;
}
