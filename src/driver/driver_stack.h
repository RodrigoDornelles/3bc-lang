#ifndef H_DRIVER_STACK_TBC
#define H_DRIVER_STACK_TBC

#include "3bc_types.h"

#ifdef __cplusplus

extern "C" {

#endif

#if defined(TBC_SOURCE_ENTRY)

void driver_stack_init(struct app_3bc_s* const self, tbc_u8_t* buf, tbc_u8_t len);

#else

void driver_stack_init(void* self, tbc_u8_t* buf, tbc_u8_t size);

#endif

#ifdef __cplusplus

}

#endif

#endif
