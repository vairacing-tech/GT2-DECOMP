// builds only with GCC 2.8.1
#include "common.h"

void func_8001DD3C(u16* arg0) {
    switch ((s16)(arg0[0] - 1)) {
    case 5:
        arg0[0] = 6;
        return;
    case 0:
    case 1:
        arg0[0] = 1;
        return;
    case 2:
    case 3:
        arg0[0] = 3;
        return;
    case 4:
        arg0[0] = 5;
        break;
    }
}
