#ifndef H_LANG_3BC_CLI_TBC
#define H_LANG_3BC_CLI_TBC

#include "3bc_types.h"

#ifdef __cplusplus

extern "C" {

#endif

#if defined(TBC_SOURCE_ENTRY)

void lang_3bc_cli_init(tbc_app_st *const self, int argc, char** argv);

#else

void lang_3bc_cli_init(void* self, int argc, char** argv);

#endif

#ifdef __cplusplus

}

#endif

#endif
