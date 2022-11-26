#include "sys_common_pfa.h"
//#include "primitive.h"
//#include "tty.h"

static void sys_common_pfac_next(tbc_app_st *const self);
static void sys_common_pfac_clean(tbc_app_st *const self);
static void sys_common_pfa888_load(tbc_app_st *const self);
static void sys_common_pfa888_insert(tbc_app_st *const self);
static void sys_common_pfa3912_load(tbc_app_st *const self);
static void sys_common_pfa3912_insert(tbc_app_st *const self);

/** 
 * @brief program counter index
 * @todo move to application struct
 */
static tbc_line_t pc_index;

/**
 * @brief install pfa888 driver
 */
void sys_common_pfa888_install(tbc_app_st *const self)
{
    self->pkg_func.prog.next = (void*) &sys_common_pfac_next;
    self->pkg_func.prog.clean = (void*) &sys_common_pfac_clean;
    self->pkg_func.prog.load = (void*) &sys_common_pfa888_load;
    self->pkg_func.prog.insert = (void*) &sys_common_pfa888_insert;
    self->cin.tty_source.type = STREAM_TYPE_FIXED_ARRAY_1D;
    self->cin.tty_source.io.buf = NULL;
    pc_index = 0;
}

/**
 * @brief install pfa3912 driver
 */
void sys_common_pfa3912_install(tbc_app_st *const self)
{
    self->pkg_func.prog.next = (void*) &sys_common_pfac_next;
    self->pkg_func.prog.clean = (void*) &sys_common_pfac_clean;
    self->pkg_func.prog.load = (void*) &sys_common_pfa3912_load;
    self->pkg_func.prog.insert = (void*) &sys_common_pfa3912_insert;
    self->cin.tty_source.type = STREAM_TYPE_FIXED_ARRAY_1D;
    self->cin.tty_source.io.buf = NULL;
    pc_index = 0;
}

/**
 * @brief increment program
 */
static void sys_common_pfac_next(tbc_app_st *const self)
{
    pc_index += 3;
}

/**
 * @brief erase program
 */
static void sys_common_pfac_clean(tbc_app_st *const self)
{
    while (pc_index && self->cin.tty_source.io.buf) {
        self->cin.tty_source.io.buf[pc_index] = 0;
        --pc_index;
    }
}

/**
 * @brief put program memory into cpu
 */
static void sys_common_pfa888_load(tbc_app_st *const self)
{
    self->cache_l0.reg = self->cin.tty_source.io.buf[pc_index + 0];
    self->cache_l0.adr = self->cin.tty_source.io.buf[pc_index + 1];
    self->cache_l0.dta = self->cin.tty_source.io.buf[pc_index + 2];
}

/**
 * @brief put cpu into program memory
 * @note must be placed from interpreter to cpu memory previously.
 */
static void sys_common_pfa888_insert(tbc_app_st *const self)
{
    self->cin.tty_source.io.buf[pc_index + 0] = self->cache_l0.reg;
    self->cin.tty_source.io.buf[pc_index + 1] = self->cache_l0.adr;
    self->cin.tty_source.io.buf[pc_index + 2] = self->cache_l0.dta;
}

/**
 * @brief put program memory into cpu
 */
static void sys_common_pfa3912_load(tbc_app_st *const self)
{
    /** reg = 0b00000111 */
    self->cache_l0.reg = (0x7 & self->cin.tty_source.io.buf[pc_index]);
    /** dta = (0b00001000 << 5) | 0b11111111 */
    self->cache_l0.adr = self->cin.tty_source.io.buf[pc_index + 1];
    self->cache_l0.adr |= (0x8 & self->cin.tty_source.io.buf[pc_index]) << 5;
    /** dta = (0b11110000 << 4) | 0b11111111 */
    self->cache_l0.dta = self->cin.tty_source.io.buf[pc_index + 2];
    self->cache_l0.dta |= (0xf0 & self->cin.tty_source.io.buf[pc_index]) << 4;
}

/**
 * @brief put cpu into program memory
 * @note must be placed from interpreter to cpu memory previously.
 */
static void sys_common_pfa3912_insert(tbc_app_st *const self)
{
    /** reg = 0b00000111 */
    self->cin.tty_source.io.buf[pc_index + 0] = (0x7 & self->cache_l0.reg);
    /** dta = (0b00001000 << 5) | 0b11111111 */
    self->cin.tty_source.io.buf[pc_index + 1] = self->cache_l0.adr;
    self->cin.tty_source.io.buf[pc_index + 1] |= (0x8 & self->cache_l0.reg) << 5;
    /** dta = (0b11110000 << 4) | 0b11111111 */
    self->cin.tty_source.io.buf[pc_index + 2] = self->cache_l0.dta;
    self->cin.tty_source.io.buf[pc_index + 2] |= (0xf0 & self->cache_l0.reg) << 4;
}
