// builds only with GCC 2.8.1
#include "common.h"

s32 func_80030D18(s32 arg0) {
    s32 result = 0;

    switch (arg0) {
        case 1:
        case 2:
            result = 1;
            break;

        case 3:
        case 4:
        case 6:
            result = 2;
            break;

        case 5:
            result = 3;
            break;
    }

    return result;
}
