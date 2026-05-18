#ifndef GT2_OVR5_LOADER_H
#define GT2_OVR5_LOADER_H

#include "common.h"

typedef struct {
    u32 base;
    u8 pad4[0x8];
    u8 payload[0x2A8];
    u32 read_dst;
    u8 active;
    u8 pad2B9[0x3];
} gt2_ovr5_loader_state;

#endif
