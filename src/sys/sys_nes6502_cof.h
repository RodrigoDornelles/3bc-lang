#ifndef H_SYS_NES6502_COF_TBC
#define H_SYS_NES6502_COF_TBC

#include "3bc_types.h"

/**
 * @def pkg_nes_output_fullscreen sys_nes6502_cout2000_install
 * @brief driver output fullscren start in $2020 (Nintendo 8 Bits)
 * @details fullscreen C standard output
 * @todo MOVE IT!
 */
void sys_nes6502_cof2020n_install(tbc_app_st *const self);
void sys_nes6502_cof2020n_put(tbc_app_st *const self);


#endif