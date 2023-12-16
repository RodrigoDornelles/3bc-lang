#ifndef H_LANG_3BC_COMPILE_TBC
#define H_LANG_3BC_COMPILE_TBC

#include "3bc_types.h"

#ifdef __cplusplus

extern "C" {

#endif

#if defined(TBC_SOURCE_ENTRY)

#include "types/types_errors.h"
#include "types/types_interpreter.h"

void lang_3bc_compile(tbc_app_st *const self);
tbc_error_et lang_3bc_compile_label_insert(tbc_interpreter_root_st *const, tbc_u16_t hash);
bool lang_3bc_compile_label_search(tbc_interpreter_root_st *const interpreter, tbc_u16_t hash, tbc_u16_t *const line);

#else

void lang_3bc_compile(void* self);

#endif

#ifdef __cplusplus

}

#endif

#endif
