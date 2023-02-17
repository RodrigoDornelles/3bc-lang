#include "pkg_std_hello.h"
#include "sys_common_mock.h"
#include "ds_prog_array.h"
#include "sys_nes_output.h"
#include "sys_posix_output.h"

#if defined(TBC_CONSOLE_NES)
const tbc_pkg_st tbc_pkg_standard = {
    {
        &ds_prog_array888_load,
        &ds_prog_arrayc_next,
        &sys_common_mock_none,
        &sys_common_mock_exit_force,
        &sys_common_mock_exit_force,
        &ds_prog_arrayc_exist,
    },{
       &sys_nes_output
    }
};
#else
const tbc_pkg_st tbc_pkg_standard = {
    {
        &ds_prog_array3912_load,
        &ds_prog_arrayc_next,
        &sys_common_mock_none,
        &sys_common_mock_exit_force,
        &sys_common_mock_exit_force,
        &ds_prog_arrayc_exist,
    },{
        &sys_posix_output
    }
};
#endif
