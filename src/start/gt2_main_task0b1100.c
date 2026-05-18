// builds only with GCC 2.8.1
#include "common.h"

extern char gt2_vol_header_ptr[24 * 0x800];

typedef void (*gt2_vol_reader)(unsigned int, unsigned int, unsigned int);

void gt2_main_task0b1100(int file_data_index, unsigned int dst, gt2_vol_reader reader) {
    char* gtfs_header = gt2_vol_header_ptr;
    unsigned int* entry = (unsigned int*)(gtfs_header + (file_data_index << 2));
    unsigned int* next_entry = (unsigned int*)(gtfs_header + ((file_data_index + 1) << 2));
    unsigned int packed_value = entry[4];

    reader(dst, packed_value >> 11, (next_entry[4] & ~0x7FF) - packed_value);
}
