/**
 * @file src/sys/sys_nes_output.c
 * @short host driver famicom videogame output **source code**
 * @brief print text as an terminal across
 * the entire television screen.
 */
#define TBC_SOURCE_ENTRY
#include "sys_nes_output.h"

union ___cursor_tty_u {
    tbc_u16_t vram_address;
    tbc_u8_t vram_pack[2];
};

union ___cursor_tty_u cursor_tty;

static void sys_nes_output_init(void);

/**
 * @brief startup PPU, palete, scroll, sprites, nametable...
 * @li https://www.nesdev.org/wiki/PPU_registers
 * @li https://www.nesdev.org/wiki/PPU_palettes
 * @li https://www.nesdev.org/wiki/PPU_scrolling
 * @li https://www.nesdev.org/wiki/PPU_OAM
 */
static void sys_nes_output_init()
{
    /* init PPU */
    *((unsigned char*) 0x2000) = 0b10101000;

    /* init palette */
    *((unsigned char*) 0x2006) = 0x3F;
    *((unsigned char*) 0x2006) = 0x00;
    *((unsigned char*) 0x2007) = 0x0F; /** @note color 0: black */
    *((unsigned char*) 0x2007) = 0x30; /** @note color 1: white */
    *((unsigned char*) 0x2007) = 0x30; /** @note color 2: white */
    *((unsigned char*) 0x2007) = 0x30; /** @note color 3: white */

    /* reset scroll */
    *((unsigned char*) 0x2005) = 0x00;
    *((unsigned char*) 0x2005) = 0x00;

    /* hide all sprites */
    cursor_tty.vram_pack[0] = 0x41;
    *((unsigned char*) 0x2003) = 0x00;
    while(--cursor_tty.vram_pack[0]) {
        *((unsigned char*) 0x2004) = 0xf0;
        *((unsigned char*) 0x2004) = 0x00;
        *((unsigned char*) 0x2004) = 0x00;
        *((unsigned char*) 0x2004) = 0xf0;
    }

    /* clear screen */
    cursor_tty.vram_address = 0x2000;
    *((unsigned char*) 0x2006) = cursor_tty.vram_pack[1];
    *((unsigned char*) 0x2006) = cursor_tty.vram_pack[0];
    do {
        *((unsigned char*) 0x2007) = ' ';
        ++cursor_tty.vram_address;
    }
    while(cursor_tty.vram_address <= (0x2400 - 0x60));

    /* reset cursor position */
    cursor_tty.vram_address = 0x2020;
    *((unsigned char*) 0x2006) = cursor_tty.vram_pack[1];
    *((unsigned char*) 0x2006) = cursor_tty.vram_pack[0];
}

/**
 * @brief stream text in entire TV screen
 * @li https://www.nesdev.org/wiki/PPU_memory_map
 * @li https://www.nesdev.org/wiki/PPU_nametables
 * @li https://www.nesdev.org/wiki/PPU_registers
 * @li https://www.nesdev.org/wiki/NMI_thread
 * @li https://www.nesdev.org/wiki/NMI
 */
void sys_nes_output(tbc_app_st *const self)
{
    /* interator */
    static tbc_u8_t* buffer;
    static tbc_u8_t index;
    static tbc_u8_t tile;

    /* reset */
    if(self->cache.l3.fixbuf.size < 0) {
        buffer = self->cache.l3.buffer.storage;
        self->cache.l3.fixbuf.size = -self->cache.l3.fixbuf.size;
    } else {
        buffer = self->cache.l3.fixbuf.storage;
    }
    index = 0;

    /* first put */
    if (cursor_tty.vram_address == 0) {
        sys_nes_output_init();
    }

    /* wait nmi */
    while(*((signed char*) 0x2002) > 0) {
        continue;
    }

    /* turn off PPU */
    *((unsigned char*) 0x2001) = 0b00000000;

    /* update nametable cursor position */
    *((unsigned char*) 0x2006) = cursor_tty.vram_pack[1];
    *((unsigned char*) 0x2006) = cursor_tty.vram_pack[0];

    /* streamming */
    while(1) {
        /* cache tile to improve perfomance */
        tile = buffer[index];
        ++index;
        
        /* end of of max size*/
        if (index > self->cache.l3.fixbuf.size) {
            break;
        }

        /* terminator */
        if (tile == '\0') {
            break;
        }
        
        /* special char: carrier return */
        if (tile == '\r') {
            /* ignore */
            continue;
        }

        /* 0x60 is three lines to end screen */
        if (cursor_tty.vram_address >= (0x2400 - 0x60)) {
            sys_nes_output_init();
            index = 0;
            continue;
        }

        /* special char: tab */
        if (tile == '\t') {
            /** 
             * @par joke
             * I really don't know how this @b tabulation works!
             */
            cursor_tty.vram_address |= 7;
            *((unsigned char*) 0x2006) = cursor_tty.vram_pack[1];
            *((unsigned char*) 0x2006) = cursor_tty.vram_pack[0];
            continue;
        }

        /* special char: break line */
        if (tile == '\n') {
            /* not feed in last character */
            if ((cursor_tty.vram_address & 31) == 0) {
                continue;
            }
            /* line feed */
            cursor_tty.vram_address += 32;
            /* carrier return */
            cursor_tty.vram_address &= 0xffe0;
            /* update cursor position into the nametable */
            *((unsigned char*) 0x2006) = cursor_tty.vram_pack[1];
            *((unsigned char*) 0x2006) = cursor_tty.vram_pack[0];
            continue;
        }

        /* put character to PPU */
        *((unsigned char*) 0x2007) = tile;
        ++cursor_tty.vram_address;
    }

    /* turn on PPU*/
    *((unsigned char*) 0x2001) = 0b00011110;
}
