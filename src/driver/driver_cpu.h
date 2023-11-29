/**
 * @file src/driver/driver_cpu.h
 * @short guest driver virtual CPU **api**
 * @brief no existing public methods.
 */
#ifndef H_DRIVER_CPU_TBC
#define H_DRIVER_CPU_TBC

#ifdef __cplusplus
extern "C" {
#endif

#if defined(TBC_SOURCE_ENTRY)
#include "3bc_types.h"

void driver_cpu(struct app_3bc_s* const self);
#endif

#ifdef __cplusplus
}
#endif

#endif
