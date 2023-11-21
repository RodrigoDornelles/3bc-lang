#define TBC_SOURCE_ENTRY
#include "bus/bus_mem_hello.h"
#include "types/types_null.h"

#if !defined(TBC_SCU_OPTIONAL_FIX)

size_t tbc_total_heap = 0;

const tbc_mem_st tbc_mem = {
    NULL,
    NULL,
    NULL
};

#endif
