#ifndef GT2_VOL_CACHE_H
#define GT2_VOL_CACHE_H

#include "common.h"

typedef enum {
    GT2_VOL_CACHE_SLOT_CRSINFO = 0x06,
    GT2_VOL_CACHE_SLOT_REPLAY_SCEA_FIRST = 0xE4,
    GT2_VOL_CACHE_SLOT_REPLAY_SCEA_LAST = 0xE5,
    GT2_VOL_CACHE_SLOT_SYS_INS = 0xF7,
} gt2_vol_cache_slot;

extern u16 gt2_vol_cached_dir_indices[];

#endif
