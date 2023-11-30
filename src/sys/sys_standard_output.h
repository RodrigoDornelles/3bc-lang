/**
 * @file src/sys/sys_standard_output.h
 * @short host driver standard libc output **api**
 * @brief no existing public methods.
 */
#ifndef H_SYS_STANDARD_OUTPUT_TBC
#define H_SYS_STANDARD_OUTPUT_TBC

#ifdef __cplusplus
extern "C" {
#endif

#if defined(TBC_SOURCE_ENTRY)
#include "3bc_types.h"

void sys_standard_output(struct app_3bc_s* const self);
#endif

#ifdef __cplusplus
}
#endif

#endif
