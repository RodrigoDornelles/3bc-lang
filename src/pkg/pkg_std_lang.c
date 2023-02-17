#include "pkg_std_lang.h"
#include "3bc_types.h"
#include "sys_common_mock.h"
#include "ds_prog_array.h"
#include "sys_common_pexa.h"
#include "sys_nes_output.h"
#include "sys_posix_output.h"

#if defined(TBC_OPT_ULTRA_COMPACT)
const tbc_pkg_st tbc_pkg_standard = {
    {
        &ds_prog_array888_load,
        &ds_prog_arrayc_next,
        &ds_prog_arrayc_clean,
        &ds_prog_array888_insert,
        &sys_common_pexams_expand,
        &ds_prog_arrayc_exist,
    },{
        &sys_posix_output
    }
};
#else 
const tbc_pkg_st tbc_pkg_standard = {
    {
        &ds_prog_array3912_load,
        &ds_prog_arrayc_next,
        &ds_prog_arrayc_clean,
        &ds_prog_array3912_insert,
        &sys_common_pexams_expand,
        &ds_prog_arrayc_exist,
    },{
        &sys_posix_output
    }
};
#endif
