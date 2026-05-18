// builds only with GCC 2.8.1
#include "common.h"

u8* func_800224B0(u8*, s32);
u8* func_800224C4(u8*, s32);
u8* func_800224D4(void);

void func_80022634(s32 index, u32* out_count, u8** out_items) {
    u8* base = func_800224D4();
    *out_count = *(u16*)func_800224C4(base, index);
    *out_items = func_800224B0(base, index);
}
