// builds only with GCC 2.8.1
#include "common.h"
#include "gt2_vol_cache.h"

void gt2_main_task0b110(unsigned short);                          /* extern */

void gt2_main_task0b11(unsigned int arg0) {
    gt2_main_task0b110(gt2_vol_cached_dir_indices[arg0]);
}
