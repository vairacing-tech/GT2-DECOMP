// builds only with GCC 2.8.1
#include "common.h"
#include "gt2_vol_cache.h"

void gt2_main_shared_racegtarcade_func6 (unsigned short); /* extern */

void
gt2_main_shared_gtracemenu_func0 (int arg0)
{
  gt2_main_shared_racegtarcade_func6 (gt2_vol_cached_dir_indices[arg0]);
}
