// builds only with GCC 2.8.1
#include "common.h"
#include "gt2_ovr5_loader.h"

extern s32 D_80092E74;
extern gt2_ovr5_loader_state D_800BA144;
extern u8 D_800BA404;

void gt2_main_task200_spu_voice00_vol(void);
void func_800226A0(gt2_ovr5_loader_state*, void*, s32);
void func_80022714(gt2_ovr5_loader_state*, s32);
void gt2_unknown_taskF0(s32);

void func_80022874(void) {
    s32 previous_audio_state = D_80092E74;

    gt2_main_task200_spu_voice00_vol();
    func_800226A0(&D_800BA144, &D_800BA404, 0x7800);
    func_80022714(&D_800BA144, 0xEC);
    gt2_unknown_taskF0(previous_audio_state);
}
