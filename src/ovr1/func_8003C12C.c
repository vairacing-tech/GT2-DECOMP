// builds only with GCC 2.8.1
#include "common.h"

extern u8 D_801C98E0[];

extern s32 func_8003B73C(s32);
extern void func_80041E4C(s32);
extern void func_8003B69C(s32);
extern void func_8003BA64(s32);
extern void func_8003C3F4(void);
extern s32 func_80012378(void);
extern void func_80012410(void);

void func_8003C12C(void) {
    register s32 selected asm("$16");
    register s32 arg asm("$4");
    register u8* base asm("$2");
    register s32 offset asm("$3");

    arg = 0;
    base = D_801C98E0;
    offset = 0xBF7C;
    base += offset;
    selected = arg;

    switch (base[0xA]) {
        case 2:
        case 4:
        case 12:
            arg = 1;
            /* fallthrough */

        case 1:
            selected = -1;
            break;

        case 0:
            selected = (s32)D_801C98E0;
            base = (u8*)0xBF7C;
            selected += (s32)base;
            arg = func_8003B73C(*(s8*)(selected + 7));
            selected = *(u8*)(selected + 3);
            break;
    }

    func_80041E4C(arg);

    if (selected >= 0) {
        func_8003B69C(selected);
    }

    func_8003BA64(1);
    func_8003C3F4();

    if (func_80012378() != 0) {
        func_80012410();
    }
}

static const s32 D_80046C90 = 0;
