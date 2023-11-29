/**
 * @file src/driver/driver_interrupt.h
 * @short guest driver event loop **api**
 */
#ifndef H_DRIVER_INTERRUPT_TBC
#define H_DRIVER_INTERRUPT_TBC

#ifdef __cplusplus
extern "C" {
#endif

#if defined(TBC_SOURCE_ENTRY)
#include "3bc_types.h"

int driver_interrupt(struct app_3bc_s* const self);
#else

/** 
 * @public
 * @short virtual machine ticket 
 */
int driver_interrupt(void* self);
#endif

#ifdef __cplusplus
}
#endif

#endif
