#include "pkg_std_lang.h"
#include "3bc_types.h"
#include "sys_common_mock.h"
#include "sys_common_std.h"
#include "sys_common_pfa.h"
#include "sys_common_pexa.h"

#if defined(TBC_OPT_ULTRA_COMPACT)
const tbc_pkg_st tbc_pkg_standard = {
    {
        &sys_common_pfa888_load,
        &sys_common_pfac_next,
        &sys_common_pfac_clean,
        &sys_common_pfa888_insert,
        &sys_common_pexams_expand,
        &sys_common_pfac_exist,
    },{
        &sys_common_std9945_put
    }
};
#else 
const tbc_pkg_st tbc_pkg_standard = {
    {
        &sys_common_pfa3912_load,
        &sys_common_pfac_next,
        &sys_common_pfac_clean,
        &sys_common_pfa3912_insert,
        &sys_common_pexams_expand,
        &sys_common_pfac_exist,
    },{
        &sys_common_std9945_put
    }
};
#endif
