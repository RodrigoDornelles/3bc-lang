//#include "../src/3bc.h"
#include "../src/mos6502_nes/screen.c"

#ifndef NULL
#define NULL 0
#endif

typedef char bool;
#define true 1
#define false 0

void put_str(unsigned int adr,const char *str)
{
    vram_adr(adr);
	for (;*str != NULL; vram_put(*str), str++);
}

int main()
{
    //struct app_3bc_s* const VM = lang_3bc_init(0, NULL);
    /**
     * put transpiled program here.
     * @example:*
    lang_3bc_line(VM, MODE, NILL, MODE_STRING);
    lang_3bc_line(VM, STRC, NILL, 'H');
    lang_3bc_line(VM, STRC, NILL, 'E');
    lang_3bc_line(VM, STRC, NILL, 'L');
    lang_3bc_line(VM, STRC, NILL, 'L');
    lang_3bc_line(VM, STRC, NILL, 'O');
    lang_3bc_line(VM, STRC, NILL, 0x20);
    lang_3bc_line(VM, STRC, NILL, 'W');
    lang_3bc_line(VM, STRC, NILL, 'O');
    lang_3bc_line(VM, STRC, NILL, 'R');
    lang_3bc_line(VM, STRC, NILL, 'L');
    lang_3bc_line(VM, STRC, NILL, 'D');
    lang_3bc_line(VM, STRC, NILL, '!');
    lang_3bc_line(VM, STRC, NILL, '\n');
     /**/

    put_str(NTADR_A(11,16), "Oi meu chapa");
    ppu_on_all();

    while (true)
    {
        ppu_wait_nmi();
        //lang_3bc_update(VM)
    }
        
    return 0;
}
