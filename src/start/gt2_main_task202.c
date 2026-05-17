// Builds only with GCC 2.8.1.
#include "common.h"

extern s32 D_80092E88;
extern void gt2_main_task2020(void);

void gt2_main_task202(void) {
    if (D_80092E88 != 0) {
        gt2_main_task2020();
    }
}
