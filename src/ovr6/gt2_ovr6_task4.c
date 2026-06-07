// builds only with GCC 2.8.1
#include "common.h"

extern void gt2_callback_double_buffer_flip_prep(void);
extern void gt2_main_flip_double_buffers(s32*, const char*, s32*);
extern s32 D_8017C9E0;
extern s32 D_801F0CF0;

const char str_gt2_psx_movie_loop[] = "12psxMovieLoop";

s32* gt2_ovr6_task4(void) {
    if (D_8017C9E0 == 0) {
        gt2_callback_double_buffer_flip_prep();
        gt2_main_flip_double_buffers(&D_8017C9E0, str_gt2_psx_movie_loop, &D_801F0CF0);
    }

    return &D_8017C9E0;
}
