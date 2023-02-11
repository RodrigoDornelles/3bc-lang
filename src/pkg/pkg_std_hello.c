#include "../sys/sys_common_mock.h"
#include "../sys/sys_common_pfa.h"

const tbc_pkg_st tbc_pkg_standard = {
    {
#if defined(TBC_OPT_ULTRA_COMPACT)
        &sys_common_pfa3912_load,
#else
        &sys_common_pfa888_load,
#endif
        &sys_common_pfac_next,
        &sys_common_mock_none,
        &sys_common_mock_exit_force,
        &sys_common_mock_exit_force,
        &sys_common_pfac_exist,
    },{
#if defined(TBC_CONSOLE_NES)
        &sys_nes6502_cof2020n_put
#else
        &sys_common_std9945_put
#endif
    }
};
