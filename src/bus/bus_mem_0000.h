#ifndef H_BUS_MEM_0000_TBC
#define H_BUS_MEM_0000_TBC

#include "3bc_types.h"

#include <stddef.h>

typedef struct ___tbc_mem_s tbc_mem_st;

struct ___tbc_mem_s {
    void (*free_func)(void*);
    void* (*malloc_func)(size_t);
    void* (*realloc_func)(void*, size_t);
};

extern const tbc_mem_st tbc_mem;

#endif
