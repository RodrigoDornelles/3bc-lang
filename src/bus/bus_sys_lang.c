#define TBC_SOURCE_ENTRY
#include "bus/bus_sys_lang.h"
#include "ds/ds_prog_array.h"
#include "ds/ds_ram_array.h"
#include "sys/sys_common_mock.h"
#include "sys/sys_common_pexa.h"
#include "sys/sys_conio_output.h"
#include "sys/sys_nes_output.h"
#include "sys/sys_posix_output.h"
#include "sys/sys_windows_output.h"

#if !defined(TBC_SCU_OPTIONAL_FIX)

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
#elif defined(TBC_USE_CONIO)
        &sys_conio_output,
#else
        &sys_posix_output
#endif 
    },{
        &ds_ram_array_read,
        &ds_ram_array_write,
    }
};

#endif
