#include "pkg_std_hello.h"
#include "sys_common_mock.h"
#include "sys_common_pfa.h"
#include "sys_nes_output.h"
#include "sys_posix_output.h"

#if defined(TBC_CONSOLE_NES)
const tbc_pkg_st tbc_pkg_standard = {
    {
        &sys_common_pfa888_load,
        &sys_common_pfac_next,
        &sys_common_mock_none,
        &sys_common_mock_exit_force,
        &sys_common_mock_exit_force,
        &sys_common_pfac_exist,
    },{
       &sys_nes_output
    }
};
#else
const tbc_pkg_st tbc_pkg_standard = {
    {
        &sys_common_pfa3912_load,
        &sys_common_pfac_next,
        &sys_common_mock_none,
        &sys_common_mock_exit_force,
        &sys_common_mock_exit_force,
        &sys_common_pfac_exist,
    },{
        &sys_posix_output
    }
};
#endif
