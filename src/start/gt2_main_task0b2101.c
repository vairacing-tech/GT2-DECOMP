// builds only with GCC 2.8.1
#include "common.h"

extern char gt2_vol_header_ptr[24 * 0x800];

unsigned int gt2_main_task0b2101(int file_data_index) {
    char* gtfs_header = gt2_vol_header_ptr;
    unsigned int* entry = (unsigned int*)(gtfs_header + (file_data_index << 2));
    unsigned int* next_entry = (unsigned int*)(gtfs_header + ((file_data_index + 1) << 2));

    return (next_entry[4] & ~0x7FF) - entry[4];
}
