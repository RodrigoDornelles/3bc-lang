#ifndef H_SYS_COMMON_PFA_TBC
#define H_SYS_COMMON_PFA_TBC

/**
 * @def pkg_common_pfa888 sys_common_pfa888_install
 * @brief driver program pfa888 (generic)
 * @details fixed array 3x8 bits
 * @note fast but limited data and address columns.
 */
void sys_common_pfa888_install(tbc_app_st *const self);

/**
 * @def pkg_common_pfa3912 sys_common_pfa3912_install
 * @brief driver program pfa888 (generic)
 * @details fixed array 3 + 9 + 12 bits
 * @note complete columns but is slow.
 */
void sys_common_pfa3912_install(tbc_app_st *const self);

#endif
