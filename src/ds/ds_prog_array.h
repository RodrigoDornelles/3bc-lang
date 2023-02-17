#ifndef H_ds_prog_array_TBC
#define H_ds_prog_array_TBC

#include "3bc_types.h"

/**
 * @def pkg_common_pfa888 ds_prog_array888_install
 * @brief driver program pfa888 (generic)
 * @details fixed array 3x8 bits
 * @note fast but limited data and address columns.
 * @todo MOVE IT!
 */
void ds_prog_array888_install(tbc_app_st *const self);

/**
 * @def pkg_common_pfa3912 ds_prog_array3912_install
 * @brief driver program pfa888 (generic)
 * @details fixed array 3 + 9 + 12 bits
 * @note complete columns but is slow.
 * @todo MOVE IT!
 */
void ds_prog_array3912_install(tbc_app_st *const self);


void ds_prog_arrayc_next(tbc_app_st *const self);
void ds_prog_arrayc_clean(tbc_app_st *const self);
void ds_prog_arrayc_exist(tbc_app_st *const self);
void ds_prog_array888_load(tbc_app_st *const self);
void ds_prog_array888_insert(tbc_app_st *const self);
void ds_prog_array3912_load(tbc_app_st *const self);
void ds_prog_array3912_insert(tbc_app_st *const self);

#endif
