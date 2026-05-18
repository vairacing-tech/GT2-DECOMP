// Builds only with GCC 2.8.1
#include "common.h"
#include "structs.h"

extern void gt2_ovr0_task0a_ovr_func0(gt2_overlay_archive_state*);                    /* extern */
extern gt2_overlay_archive_state gt2_overlay_archive;

void gt2_ovr0_task0a_ovr_entrypoint(void) {
    gt2_ovr0_task0a_ovr_func0(&gt2_overlay_archive);
}
