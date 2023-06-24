#define TBC_SOURCE_ENTRY
#include "alu/alu_math.h"
#include "bus/bus_alu_lang.h"

#if !defined(TBC_SCU_OPTIONAL_FIX)

const tbc_method_ft tbc_layout_alu = alu_math;

#endif
