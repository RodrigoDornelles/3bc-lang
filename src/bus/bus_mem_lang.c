#define TBC_SOURCE_ENTRY
#include "bus/bus_mem_lang.h"
#include "types/types_null.h"

size_t tbc_total_heap = 0;

#if defined(TBC_MALLOC_JEMALLOC)
extern void je_free(void*);
extern void* je_malloc(size_t);
static void* tbc_realloc(void*, size_t); 
#elif defined(TBC_MALLOC_FREERTOS)
extern void vPortFree(void*);
extern void* pvPortMalloc(size_t);
static void* tbc_realloc(void*, size_t); 
#elif !defined(TBC_NOT_MALLOC)
extern void free(void*);
extern void* malloc(size_t);
extern void* realloc(void*, size_t);
#endif

#if !defined(TBC_SCU_OPTIONAL_FIX)

const tbc_mem_st tbc_mem = {
#if defined(TBC_MALLOC_JEMALLOC)
    &je_free,
    &je_malloc,
    &tbc_realloc,
#elif defined(TBC_MALLOC_FREERTOS)
    &pvPortMalloc,
    &vPortFree,
    &tbc_realloc
#elif !defined(TBC_NOT_MALLOC)
    &free,
    &malloc,
    &realloc
#else
    NULL,
    NULL,
    NULL
#endif
};

#if defined(TBC_MALLOC_JEMALLOC) || defined(TBC_MALLOC_FREERTOS)
static void* tbc_realloc(void* ptr, size_t size) {
    size_t i = 0;
    void* newPtr = tbc_mem.malloc_func(size);
    if (newPtr != NULL) {
        while(i < size) {
            newPtr[i] = ptr[i];
            ++i;
        }
        tbc_mem.free_func(ptr);
        tbc_total_heap += size;
    }
    return newPtr;
}
#endif

#endif
