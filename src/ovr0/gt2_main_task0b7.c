// builds only with GCC 2.8.1
#include "common.h"
#include "gt2_vol_cache.h"

extern int D_801C93C4;

void gt2_main_task0b7(void) {
    D_801C93C4 =
        (gt2_vol_cached_dir_indices[GT2_VOL_CACHE_SLOT_REPLAY_SCEA_LAST]
        - gt2_vol_cached_dir_indices[GT2_VOL_CACHE_SLOT_REPLAY_SCEA_FIRST]) - 1;
}
