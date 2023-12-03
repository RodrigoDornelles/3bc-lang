#ifndef H_MACRO_SIZES_TBC
#define H_MACRO_SIZES_TBC

#include "detect/detect_opt.h"

#ifndef TBC_MAX_RAM
#ifdef TBC_OPT_COMPACT_1
/** @todo investigate memory usage on arduino **/
#define TBC_MAX_RAM (128u)
#else
#define TBC_MAX_RAM (512u)
#endif
#endif

#ifndef TBC_MACHINE_SIZE
#define TBC_MACHINE_SIZE (sizeof(tbc_app_st))
#endif

#endif