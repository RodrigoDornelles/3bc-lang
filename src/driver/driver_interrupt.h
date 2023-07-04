#ifndef H_DRIVER_INTERRUPT_TBC
#define H_DRIVER_INTERRUPT_TBC

#include "3bc_types.h"

#ifdef __cplusplus

extern "C" {

#endif

#if defined(TBC_SOURCE_ENTRY)

/** @short private */
int driver_interrupt(struct app_3bc_s* const self);

#else

/** @short public */
int driver_interrupt(void* self);

#endif

#ifdef __cplusplus

}

#endif

#endif
