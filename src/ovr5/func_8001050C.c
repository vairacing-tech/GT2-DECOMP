// builds only with GCC 2.8.1
#include "common.h"

extern void gt2_ovr5_load_license(void);
extern void func_80010368(void*);
extern u8 D_801C98E0[];

void func_8001050C(void) {
    s32 offset;
    void* ptr;

    offset = 0x10BD8;
    ptr = (void*)(((s32)(D_801C98E0 + offset)) & ~3);
    gt2_ovr5_load_license();
    func_80010368(ptr);
}
