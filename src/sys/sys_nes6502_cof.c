#include "sys_nes6502_cof.h"

union ___cursor_tty_u {
    tbc_u16_t vram_address;
    tbc_u8_t vram_pack[2];
};

union ___cursor_tty_u cursor_tty;

static void sys_nes6502_cof2020n_init(void);

/**
 * @brief install cof2020n driver
 */
void sys_nes6502_cof2020n_install(tbc_app_st *const self)
{
    self->pkg_func->std.put = (void*) &sys_nes6502_cof2020n_put;
    self->cout.tty_output.type = STREAM_TYPE_NES_FULLSCREEN;
    cursor_tty.vram_address = 0;
}

/**
 * @brief startup PPU, palete, scroll, sprites, nametable...
 * @link https://www.nesdev.org/wiki/PPU_registers
 * @link https://www.nesdev.org/wiki/PPU_palettes
 * @link https://www.nesdev.org/wiki/PPU_scrolling
 * @link https://www.nesdev.org/wiki/PPU_OAM
 */
static void sys_nes6502_cof2020n_init()
{
    /** init PPU */
    *((unsigned char*) 0x2000) = 0b10101000;

    /** init palette */
    *((unsigned char*) 0x2006) = 0x3F;
    *((unsigned char*) 0x2006) = 0x00;
    *((unsigned char*) 0x2007) = 0x0F; /**< color 0: black */
    *((unsigned char*) 0x2007) = 0x30; /**< color 1: white */
    *((unsigned char*) 0x2007) = 0x30; /**< color 2: white */
    *((unsigned char*) 0x2007) = 0x30; /**< color 3: white */

    /** reset scroll */
    *((unsigned char*) 0x2005) = 0x00;
    *((unsigned char*) 0x2005) = 0x00;

    /** hide all sprites */
    cursor_tty.vram_pack[0] = 0x41;
    *((unsigned char*) 0x2003) = 0x00;
    while(--cursor_tty.vram_pack[0]) {
        *((unsigned char*) 0x2004) = 0xf0;
        *((unsigned char*) 0x2004) = 0x00;
        *((unsigned char*) 0x2004) = 0x00;
        *((unsigned char*) 0x2004) = 0xf0;
    }

    /** reset cursor position */
    cursor_tty.vram_address = 0x2020;
}

/**
 * @brief stream text in entire TV screen
 * @link https://www.nesdev.org/wiki/PPU_memory_map
 * @link https://www.nesdev.org/wiki/PPU_nametables
 * @link https://www.nesdev.org/wiki/PPU_registers
 * @link https://www.nesdev.org/wiki/NMI_thread
 * @link https://www.nesdev.org/wiki/NMI
 */
void sys_nes6502_cof2020n_put(tbc_app_st *const self)
{
    /** interator */
    static tbc_u8_t index;
    static tbc_u8_t tile;

    /** reset */
    index = 0;

    /** first put */
    if (cursor_tty.vram_address == 0) {
        sys_nes6502_cof2020n_init();
    }

    /** turn off PPU */
    *((unsigned char*) 0x2001) = 0b00000000;

    /** wait nmi */
    while(*((signed char*) 0x2002) < 0) {
        continue;
    }

    /** update nametable cursor position */
    *((unsigned char*) 0x2006) = cursor_tty.vram_pack[1];
    *((unsigned char*) 0x2006) = cursor_tty.vram_pack[0];

    /** streamming */
    while(1) {
        /** cache tile to improve perfomance */
        tile = self->cache_l3.fixbuf.storage[index];
        ++index;
        
        /** end of of max size*/
        if (index > self->cache_l3.fixbuf.size) {
            break;
        }

        /** terminator */
        if (tile == '\0') {
            break;
        }
        
        /** special char: carrier return */
        if (tile == '\r') {
            /** ignore */
            continue;
        }

        /** special char: tab */
        if (tile == '\t') {
            /** 
             * tabulation
             * @joke I really don't know how it works!
             */
            cursor_tty.vram_address |= 7;
            *((unsigned char*) 0x2006) = cursor_tty.vram_pack[1];
            *((unsigned char*) 0x2006) = cursor_tty.vram_pack[0];
            continue;
        }

        /** special char: break line */
        if (tile == '\n') {
            /** line feed */
            cursor_tty.vram_address += 32;
            /** carrier return */
            cursor_tty.vram_address &= 0xffe0;
            /** update cursor position into the nametable */
            *((unsigned char*) 0x2006) = cursor_tty.vram_pack[1];
            *((unsigned char*) 0x2006) = cursor_tty.vram_pack[0];
            continue;
        }

        /** put character to PPU */
        *((unsigned char*) 0x2007) = tile;
        ++cursor_tty.vram_address;
    }

    /** turn on PPU*/
    *((unsigned char*) 0x2001) = 0b00011110;
}
