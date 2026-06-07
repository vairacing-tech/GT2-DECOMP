// builds only with GCC 2.8.1
#include "common.h"

extern void func_80054B9C(s32, s32, s32);

void func_800551BC(u8* arg0, u8* arg1, s32 arg2, s32 arg3) {
    register u8* item asm("$9");
    register u8* data asm("$8");
    register s32 out asm("$4");
    register s32 value asm("$5");
    register s32 temp asm("$2");

    item = arg0;
    data = arg1;
    out = arg2;
    __asm__ volatile("" : "+r"(item), "+r"(data), "+r"(out));
    value = 0;

    switch (*(s8*)(item + 0xC)) {
        case 0:
            value = data[0x61];
            if (arg3 != 0) {
                value = data[0x60];
            }
            break;

        case 1:
            value = data[0x5D];
            if (arg3 != 0) {
                value = data[0x5C];
            }
            break;

        case 3:
            value = data[0x68];
            if (arg3 != 0) {
                value = data[0x64];
            }
            break;

        case 2:
            value = data[0x6A];
            if (arg3 != 0) {
                value = data[0x66];
            }
            break;

        case 4:
            value = data[0x5B];
            if (arg3 != 0) {
                value = data[0x5A];
            }
            break;

        case 5:
            temp = data[0x5F];
            value = temp - 0x80;
            if (arg3 != 0) {
                temp = data[0x5E];
                value = temp - 0x80;
            }
            break;

        case 6:
            value = data[0x6D];
            if (arg3 != 0) {
                value = data[0x6C];
            }
            break;

        case 7:
            value = data[0x51];
            if (arg3 != 0) {
                value = data[0x50];
            }
            break;

        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            temp = *(s8*)(item + 0xC);
            temp -= 8;
            temp <<= 1;
            temp = (s32)data + temp;
            value = *(u16*)(temp + 0x3C);
            break;

        case 17:
            value = data[0x53];
            if (arg3 != 0) {
                value = data[0x52];
            }
            break;

        case 22:
            value = data[0x74];
            break;

        case 23:
            value = data[0x75];
            break;
    }

    func_80054B9C(out, value, item[0xD]);
}
