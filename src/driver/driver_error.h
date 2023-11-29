/**
 * @file src/driver/driver_error.h
 * @short guest driver error handler **api**
 * @brief no existing public methods.
 */

#ifndef H_DRIVER_ERROR_TBC
#define H_DRIVER_ERROR_TBC

#ifdef __cplusplus
extern "C" {
#endif

#if defined(TBC_SOURCE_ENTRY)
#include "3bc_types.h"

void driver_error(struct app_3bc_s* const self);
#endif

#ifdef __cplusplus
}
#endif

#endif
