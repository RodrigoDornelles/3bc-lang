#include "bus_cfg_hello.h"
#include "types_null.h"
#include "types_stack.h"

static const tbc_layout_cfg_st ___layout_cfg[] = {
    {sizeof(tbc_stack_basic_prog_st)}
};

const tbc_layout_cfg_st* tbc_cfg_standard = ___layout_cfg;
const tbc_u8_t tbc_cfg_size = sizeof(___layout_cfg)/sizeof(___layout_cfg[0]);
