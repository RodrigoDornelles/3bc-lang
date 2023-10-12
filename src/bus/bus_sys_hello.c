#define TBC_SOURCE_ENTRY
#include "detect/detect_opt.h"
#include "detect/detect_libc.h"
#include "detect/detect_system.h"
#include "detect/detect_system.h"
#include "bus/bus_sys_hello.h"
#include "ds/ds_prog_array.h"
#include "sys/sys_common_mock.h"
#include "sys/sys_conio_output.h"
#include "sys/sys_nes_output.h"
#include "sys/sys_posix_output.h"
#include "sys/sys_windows_output.h"

#if !defined(TBC_SCU_OPTIONAL_FIX)

const tbc_pkg_st tbc_pkg_standard = {
    {
#if defined(TBC_OPT_COMPACT_2)
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
#if defined(TBC_SYSTEM_ID_NES)
        &sys_nes_output
#elif defined(TBC_LIBC_WINDOWS)
        &sys_windows_output
#elif defined(TBC_LIBC_CONIO)
        &sys_conio_output,
#else
        &sys_posix_output
#endif 
    }
};

#endif
