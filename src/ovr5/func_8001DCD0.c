// builds only with GCC 2.8.1
#include "common.h"

s32 func_8001DCD0(s16* arg0) {
    s32 ret = 0;

    switch (arg0[0]) {
    case 6:
        arg0[0] = 6;
        ret = 1;
        break;
    case 7:
        arg0[0] = 7;
        break;
    case 1:
    case 2:
        arg0[0] = 1;
        break;
    case 3:
    case 4:
        arg0[0] = 3;
        break;
    case 5:
        arg0[0] = 5;
        break;
    case 0:
        break;
    }

    return ret;
}
