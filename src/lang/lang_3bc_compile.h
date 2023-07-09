#ifndef H_LANG_3BC_COMPILE_TBC
#define H_LANG_3BC_COMPILE_TBC

#include "3bc_types.h"

#ifdef __cplusplus

extern "C" {

#endif

#if defined(TBC_SOURCE_ENTRY)

void lang_3bc_compile(tbc_app_st *const self);

#else

void lang_3bc_compile(void* self);

#endif

#ifdef __cplusplus

}

#endif

#endif
