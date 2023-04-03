#include "bus_sys_lang.h"
#include "3bc_types.h"
#include "ds_prog_array.h"
#include "ds_ram_array.h"
#include "sys_common_mock.h"
#include "sys_common_pexa.h"
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
        &ds_prog_arrayc_clean,
#if defined(TBC_OPT_ULTRA_COMPACT)
        &ds_prog_array888_insert,
#else
        &ds_prog_array3912_insert,
#endif
        &sys_common_pexams_expand,
        &ds_prog_arrayc_exist,
    },{
#if defined(TBC_CONSOLE_NES)
        &sys_nes_output
#elif defined(TBC_KERNEL_NT)
        &sys_windows_output
#else
        &sys_posix_output
#endif 
    },{
        &ds_ram_array_read,
        &ds_ram_array_write,
    }
};
