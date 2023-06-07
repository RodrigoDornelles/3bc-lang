#include "ds_prog_array.h"

/**
 * @brief increment program
 */
void ds_prog_arrayc_next(tbc_app_st *const self)
{
    ++self->stack.cfgmin.prog->index;
}

/**
 * @brief erase program
 */
void ds_prog_arrayc_clean(tbc_app_st *const self)
{
    tbc_line_t program_counter = (self->stack.cfgmin.prog->index * 3);
    while (program_counter && self->cin.tty_storage.io.arr.ptr) {
        self->cin.tty_storage.io.arr.ptr[program_counter] = 0;
        --program_counter;
    }
}

/**
 * @brief program avaliable
 */
void ds_prog_arrayc_exist(tbc_app_st *const self)
{
    if ((self->stack.cfgmin.prog->index * 3) < self->stack.cfgmin.prog->size) {
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
    tbc_line_t program_counter = self->stack.cfgmin.prog->index * 3;
    self->cpu.rx = self->cin.tty_storage.io.arr.ptr[program_counter];
    ++program_counter;
    self->cpu.ry = self->cin.tty_storage.io.arr.ptr[program_counter];
    ++program_counter;
    self->cpu.rz = self->cin.tty_storage.io.arr.ptr[program_counter];
}

/**
 * @brief put cpu into program memory
 * @note must be placed from interpreter to cpu memory previously.
 */
void ds_prog_array888_insert(tbc_app_st *const self)
{
    tbc_line_t program_counter = (self->stack.cfgmin.prog->index * 3);
    self->cin.tty_storage.io.arr.ptr[program_counter] = self->cpu.rx;
    ++program_counter;
    self->cin.tty_storage.io.arr.ptr[program_counter] = self->cpu.ry;
    ++program_counter;
    self->cin.tty_storage.io.arr.ptr[program_counter] = self->cpu.rz;
}

/**
 * @brief put program memory into cpu
 * reg = 0b00000111 
 * dta = (0b00001000 << 5) | 0b11111111
 * dta = (0b01110000 << 5) | 0b11111111
 */
void ds_prog_array3912_load(tbc_app_st *const self)
{
    tbc_line_t program_counter = (self->stack.cfgmin.prog->index * 3) + 2;
    self->cpu.rz = self->cin.tty_storage.io.arr.ptr[program_counter];
    --program_counter;
    self->cpu.ry = self->cin.tty_storage.io.arr.ptr[program_counter];
    --program_counter;
    self->cpu.rx = (0x7 & self->cin.tty_storage.io.arr.ptr[program_counter]);
    self->cpu.ry |= (0x8 & self->cin.tty_storage.io.arr.ptr[program_counter]) << 8;
    self->cpu.rz |= (0xf0 & self->cin.tty_storage.io.arr.ptr[program_counter]) << 8;
}

/**
 * @brief put cpu into program memory
 * @note must be placed from interpreter to cpu memory previously.
 * reg = 0b00000111
 * dta = (0b00001000 << 5) | 0b11111111
 * dta = (0b11110000 << 4) | 0b11111111
 */
void ds_prog_array3912_insert(tbc_app_st *const self)
{
    tbc_line_t program_counter = self->stack.cfgmin.prog->index * 3;
    self->cin.tty_storage.io.arr.ptr[program_counter] = (0x7 & self->cpu.rx);
    self->cin.tty_storage.io.arr.ptr[program_counter] |= (0x800 & self->cpu.rx) >> 8;
    self->cin.tty_storage.io.arr.ptr[program_counter] |= (0xf0000 & self->cpu.rz) >> 8;
    ++program_counter;
    self->cin.tty_storage.io.arr.ptr[program_counter] = self->cpu.ry;
    ++program_counter;
    self->cin.tty_storage.io.arr.ptr[program_counter] = self->cpu.rz;
}
