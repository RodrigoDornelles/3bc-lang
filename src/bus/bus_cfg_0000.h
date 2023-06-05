#ifndef H_BUS_CFG_0000
#define H_BUS_CFG_0000

#include "3bc_types.h"

typedef struct ___layout_cfg_s tbc_layout_cfg_st;

struct ___layout_cfg_s {
    const tbc_u8_t size;
#if !defined(TBC_OPT_ULTRA_COMPACT)
    const void* pointer;
    const tbc_method_ft* init;
#endif
};

extern const tbc_layout_cfg_st* tbc_cfg_standard;
extern const tbc_u8_t tbc_cfg_size;

#endif
