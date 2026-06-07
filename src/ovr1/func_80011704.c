// builds only with GCC 2.8.1
#include "common.h"

extern void func_80010298(void);
extern void func_800103C0(void*, s32);
extern void func_800113C0(void*, s32);

void func_80011704(u8* arg0) {
    register s32 state asm("$16");
    register u8* self asm("$17");

    self = arg0;
    func_80010298();

    state = 0;
    switch (self[0x106]) {
        case 1:
            state = 1;
            goto call_103c0;

        case 2:
            state = 2;
call_103c0:
            func_800103C0(self, state);
            return;

        case 3:
            state = 12;
            break;

        case 0:
            state = 0;
            break;

        case 4:
            state = 7;
            break;

        case 5:
            state = 8;
            break;

        case 6:
            state = 9;
            break;

        case 7:
            state = 10;
            break;

        case 8:
            state = 11;
            break;
    }

    func_800113C0(self, state);
}

static const s32 D_8002EEBC = 0;
