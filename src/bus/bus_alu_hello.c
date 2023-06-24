#define TBC_SOURCE_ENTRY
#include "alu/alu_none.h"
#include "bus/bus_alu_hello.h"

#if !defined(TBC_SCU_OPTIONAL_FIX)

const tbc_method_ft tbc_layout_alu = alu_none;

#endif
