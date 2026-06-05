// builds only with GCC 2.8.1
#include "common.h"

extern void gt2_callback_double_buffer_flip(void);
extern void gt2_main_flip_double_buffers(s32*, const char*, s32*);
extern s32 D_801C3050;
extern s32 D_801F0CE0;

const char str_gt2_loading_menu[] = "13GTLoadingMenu";

s32* func_80014FEC(void) {
    if (D_801C3050 == 0) {
        gt2_callback_double_buffer_flip();
        gt2_main_flip_double_buffers(&D_801C3050, str_gt2_loading_menu, &D_801F0CE0);
    }

    return &D_801C3050;
}
