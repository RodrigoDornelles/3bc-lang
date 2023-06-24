#define TBC_SOURCE_ENTRY
#include "bus/bus_cfg_hello.h"
#include "types/types_null.h"
#include "types/types_stack.h"

#if !defined(TBC_SCU_OPTIONAL_FIX)
static const tbc_layout_cfg_st ___layout_cfg[] = {
    {sizeof(tbc_stack_basic_prog_st)}
};

const tbc_layout_cfg_st* tbc_cfg_standard = ___layout_cfg;
const tbc_u8_t tbc_cfg_size = sizeof(___layout_cfg)/sizeof(___layout_cfg[0]);
#endif
