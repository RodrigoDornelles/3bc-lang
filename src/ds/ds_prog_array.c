#include "ds_prog_array.h"

/**
 * @brief increment program
 */
void ds_prog_arrayc_next(tbc_app_st *const self)
{
    self->cin.tty_storage.io.arr.index += 3;
}

/**
 * @brief erase program
 */
void ds_prog_arrayc_clean(tbc_app_st *const self)
{
    while (self->cin.tty_storage.io.arr.index && self->cin.tty_storage.io.arr.ptr) {
        self->cin.tty_storage.io.arr.ptr[self->cin.tty_storage.io.arr.index] = 0;
        --self->cin.tty_storage.io.arr.index;
    }
}

/**
 * @brief program avaliable
 */
void ds_prog_arrayc_exist(tbc_app_st *const self)
{
    if (self->cin.tty_storage.io.arr.index < self->cin.tty_storage.io.arr.size) {
        self->rc = TBC_RET_FULL;
    } else {
        self->rc = TBC_RET_CLEAN;
    }
}

/**
 * @brief put program memory into cpu
 */
void ds_prog_array888_load(tbc_app_st *const self)
{
    tbc_line_t program_counter = self->cin.tty_storage.io.arr.index;
    self->cache_l0.rx = self->cin.tty_storage.io.arr.ptr[program_counter];
    self->cache_l0.ry = self->cin.tty_storage.io.arr.ptr[++program_counter];
    self->cache_l0.rz = self->cin.tty_storage.io.arr.ptr[++program_counter];
}

/**
 * @brief put cpu into program memory
 * @note must be placed from interpreter to cpu memory previously.
 */
void ds_prog_array888_insert(tbc_app_st *const self)
{
    tbc_line_t program_counter = self->cin.tty_storage.io.arr.index;
    self->cin.tty_storage.io.arr.ptr[program_counter] = self->cache_l0.rx;
    self->cin.tty_storage.io.arr.ptr[++program_counter] = self->cache_l0.ry;
    self->cin.tty_storage.io.arr.ptr[++program_counter] = self->cache_l0.rz;
}

/**
 * @brief put program memory into cpu
 */
void ds_prog_array3912_load(tbc_app_st *const self)
{
    /** reg = 0b00000111 */
    self->cache_l0.rx = (0x7 & self->cin.tty_storage.io.arr.ptr[self->cin.tty_storage.io.arr.index]);
    /** dta = (0b00001000 << 5) | 0b11111111 */
    self->cache_l0.ry = self->cin.tty_storage.io.arr.ptr[self->cin.tty_storage.io.arr.index + 1];
    self->cache_l0.ry |= (0x8 & self->cin.tty_storage.io.arr.ptr[self->cin.tty_storage.io.arr.index]) << 5;
    /** dta = (0b11110000 << 4) | 0b11111111 */
    self->cache_l0.rz = self->cin.tty_storage.io.arr.ptr[self->cin.tty_storage.io.arr.index + 2];
    self->cache_l0.rz |= (0xf0 & self->cin.tty_storage.io.arr.ptr[self->cin.tty_storage.io.arr.index]) << 4;
}

/**
 * @brief put cpu into program memory
 * @note must be placed from interpreter to cpu memory previously.
 */
void ds_prog_array3912_insert(tbc_app_st *const self)
{
    /** reg = 0b00000111 */
    self->cin.tty_storage.io.arr.ptr[self->cin.tty_storage.io.arr.index + 0] = (0x7 & self->cache_l0.rx);
    /** dta = (0b00001000 << 5) | 0b11111111 */
    self->cin.tty_storage.io.arr.ptr[self->cin.tty_storage.io.arr.index + 1] = self->cache_l0.ry;
    self->cin.tty_storage.io.arr.ptr[self->cin.tty_storage.io.arr.index + 1] |= (0x8 & self->cache_l0.rx) << 5;
    /** dta = (0b11110000 << 4) | 0b11111111 */
    self->cin.tty_storage.io.arr.ptr[self->cin.tty_storage.io.arr.index + 2] = self->cache_l0.rz;
    self->cin.tty_storage.io.arr.ptr[self->cin.tty_storage.io.arr.index + 2] |= (0xf0 & self->cache_l0.rx) << 4;
}
