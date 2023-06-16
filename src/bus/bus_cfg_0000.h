#ifndef H_BUS_CFG_0000
#define H_BUS_CFG_0000

#include "3bc_types.h"

typedef struct ___layout_cfg_s tbc_layout_cfg_st;

struct ___layout_cfg_s {
    const tbc_u8_t size;
};

extern const tbc_layout_cfg_st* tbc_cfg_standard;
extern const tbc_u8_t tbc_cfg_size;

#endif
