#include "sys_nes6502_cof.h"

union ___cursor_tty_u {
    tbc_u16_t vram_address;
    tbc_u8_t vram_pack[2];
};

union ___cursor_tty_u cursor_tty;

static void sys_nes6502_cof2020n_put(tbc_app_st *const self, tbc_u8_t file_id, const char* buf);

/**
 * @brief install cof2020n driver
 */
void sys_nes6502_cof2020n_install(tbc_app_st *const self)
{
    self->pkg_func.std.put = (void*) &sys_nes6502_cof2020n_put;
    self->cout.tty_output.type = STREAM_TYPE_POSIX_FILEID;
    self->cout.tty_output.io.fid = 1;
    cursor_tty.vram_address = 0;
}

/**
 * @brief stream text in entire TV screen
 * @link https://www.nesdev.org/wiki/PPU_memory_map
 * @link https://www.nesdev.org/wiki/PPU_nametables
 * @link https://www.nesdev.org/wiki/PPU_registers
 */
static void sys_nes6502_cof2020n_put(tbc_app_st *const self, tbc_u8_t file_id, const char* buf)
{
    *((unsigned char*) 0x2001) = 0b00000000;

    if (cursor_tty.vram_address == 0) {
        cursor_tty.vram_address = 0x2020;
        *((unsigned char*) 0x2006) = cursor_tty.vram_pack[1];
        *((unsigned char*) 0x2006) = cursor_tty.vram_pack[0];
    }

    while(*buf != '\0') {
        if (*buf == '\r') {
            ++buf;
            continue;
        }
        if (*buf == '\n') {
            cursor_tty.vram_address += 32;
            cursor_tty.vram_address &= 0xffe0;
            *((unsigned char*) 0x2006) = cursor_tty.vram_pack[1];
            *((unsigned char*) 0x2006) = cursor_tty.vram_pack[0];
            ++buf;
            continue;
        }

        *((unsigned char*) 0x2007) = *buf;
        ++cursor_tty.vram_address;
        ++buf;
    }

    *((unsigned char*) 0x2001) = 0b00011110;
}
