/**
 * @file src/driver/driver_gc.h
 * @short guest driver garbage colector **api**
 * @brief no existing public methods.
 */
#ifndef H_DRIVER_GC_TBC
#define H_DRIVER_GC_TBC

#ifdef __cplusplus
extern "C" {
#endif

#if defined(TBC_SOURCE_ENTRY)
#include "3bc_types.h"

void driver_gc(struct app_3bc_s* const self);
#endif

#ifdef __cplusplus
}
#endif

#endif
