#include "3bc_detect.h"
#include "bus_sys_hello.h"
#include "ds_prog_array.h"
#include "sys_common_mock.h"
#include "sys_nes_output.h"
#include "sys_posix_output.h"
#include "sys_windows_output.h"

const tbc_pkg_st tbc_pkg_standard = {
    {
#if defined(TBC_OPT_ULTRA_COMPACT)
        &ds_prog_array888_load,
#else
        &ds_prog_array3912_load,
#endif
        &ds_prog_arrayc_next,
        &sys_common_mock_none,
        &sys_common_mock_exit_force,
        &sys_common_mock_exit_force,
        &ds_prog_arrayc_exist,
    },{
#if defined(TBC_CONSOLE_NES)
        &sys_nes_output
#elif defined(TBC_KERNEL_NT)
        &sys_windows_output
#else
        &sys_posix_output
#endif 
    }
};
