/**
 * @file src/driver/driver_stack.h
 * @short guest driver stack memory **api**
 * @brief controll of stack limits
 */
#ifndef H_DRIVER_STACK_TBC
#define H_DRIVER_STACK_TBC

#ifdef __cplusplus
extern "C" {
#endif

#if defined(TBC_SOURCE_ENTRY)
#include "3bc_types.h"

void driver_stack_init(struct app_3bc_s* const self, tbc_u8_t* buf, tbc_u8_t len);
#else

/**
 * @public
 * @short stack memory intialize
 */
void driver_stack_init(void* self, char* buf, unsigned char size);
#endif

#ifdef __cplusplus
}
#endif

#endif
