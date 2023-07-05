#define TBC_SOURCE_ENTRY
#include "3bc.h"
#include "lang/lang_3bc_cli.h"
#include "util/util_itos.h"
#include "util/util_args.h"
#include "bus/bus_sys_0000.h"
#include "pre/pre_date.h"

struct ___info_txt_s {
    const char* ptr;
    tbc_i8_t len;
};
static const char ___msg_version[] = VERSION_3BC"\n";
static const char ___msg_info_00[] = "[3BC] VIRTUAL MACHINE INFORMATION\n";
static const char ___msg_info_01[] = "> AUTHOR: Rodrigo Dornelles (C) 2020\n";
static const char ___msg_info_02[] = "> LICENSE: AGPL 3.0 or higher\n";
static const char ___msg_info_03[] = "> VERSION: ";
static const char ___msg_info_04[] = "> COMPILER: "__VERSION__"\n";
static const char ___msg_info_05[] = "> BUILD DATE: ";
static const char ___msg_info_06[] = {
    TBC_YEAR_CH0, TBC_YEAR_CH1, TBC_YEAR_CH2, TBC_YEAR_CH3,
    '-', TBC_MONTH_CH0, TBC_MONTH_CH1,
    '-', TBC_DAY_CH0, TBC_DAY_CH1, '\n', '\0'
};
static const char ___msg_info_07[] = "> STACK SIZE: ";
static const char ___msg_info_08[] = "> STACK FREE: ";
static const char ___msg_info_09[] = "> OBJECT SIZE: ";
static const char ___msg_info_10[] = " (bytes)\n";
static const tbc_u8_t ___len_version = (tbc_i8_t) sizeof(___msg_version) * (-1);
static const struct ___info_txt_s ___infos_txt[] = {
    {___msg_info_00, (tbc_i8_t) sizeof(___msg_info_00) * (-1)},
    {___msg_info_01, (tbc_i8_t) sizeof(___msg_info_01) * (-1)},
    {___msg_info_02, (tbc_i8_t) sizeof(___msg_info_02) * (-1)},
    {___msg_info_03, (tbc_i8_t) sizeof(___msg_info_03) * (-1)},
    {___msg_version, (tbc_i8_t) sizeof(___msg_version) * (-1)},
    {___msg_info_04, (tbc_i8_t) sizeof(___msg_info_04) * (-1)},
    {___msg_info_05, (tbc_i8_t) sizeof(___msg_info_05) * (-1)},
    {___msg_info_06, (tbc_i8_t) sizeof(___msg_info_06) * (-1)},
};

void lang_3bc_cli_init(tbc_app_st *const self, int argc, char** argv)
{
    do {
        if (util_args_has(argc, argv, 'v') != NULL) {
            self->cache_l3.buffer.storage = (char*) ___msg_version;
            self->cache_l3.buffer.size = ___len_version;
            tbc_pkg_standard.io.write(self);
            self->rc = TBC_RET_EXIT_FORCE;
            break;
        }
        if (util_args_has(argc, argv, 'i') != NULL) {
            tbc_u8_t i = 0;
            tbc_u8_t sizefreestack = self->stack.mem->st - self->stack.mem->sp;
            tbc_u16_t sizeobject = sizeof(tbc_app_st);

            while (i < sizeof(___infos_txt)/sizeof(___infos_txt[0])) {
                self->cache_l3.buffer.storage = (char*) ___infos_txt[i].ptr;
                self->cache_l3.buffer.size = ___infos_txt[i].len;
                tbc_pkg_standard.io.write(self);
                ++i;
            }
            
            self->cache_l3.buffer.storage = (char*) ___msg_info_07;
            self->cache_l3.buffer.size =  (tbc_i8_t) sizeof(___msg_info_07) * (-1);
            tbc_pkg_standard.io.write(self);
            self->cache_l3.fixbuf.size = util_itos10(self->cache_l3.fixbuf.storage, &self->stack.mem->st, sizeof(self->cache_l3.fixbuf.storage), 8);
            tbc_pkg_standard.io.write(self);
            self->cache_l3.buffer.storage = (char*) ___msg_info_10;
            self->cache_l3.buffer.size =  (tbc_i8_t) sizeof(___msg_info_10) * (-1);
            tbc_pkg_standard.io.write(self);

            self->cache_l3.buffer.storage = (char*) ___msg_info_08;
            self->cache_l3.buffer.size =  (tbc_i8_t) sizeof(___msg_info_08) * (-1);
            tbc_pkg_standard.io.write(self);
            self->cache_l3.fixbuf.size = util_itos10(self->cache_l3.fixbuf.storage, &sizefreestack, sizeof(self->cache_l3.fixbuf.storage), 8);
            tbc_pkg_standard.io.write(self);
            self->cache_l3.buffer.storage = (char*) ___msg_info_10;
            self->cache_l3.buffer.size =  (tbc_i8_t) sizeof(___msg_info_10) * (-1);
            tbc_pkg_standard.io.write(self);

            self->cache_l3.buffer.storage = (char*) ___msg_info_09;
            self->cache_l3.buffer.size =  (tbc_i8_t) sizeof(___msg_info_09) * (-1);
            tbc_pkg_standard.io.write(self);
            self->cache_l3.fixbuf.size = util_itos10(self->cache_l3.fixbuf.storage, &sizeobject, sizeof(self->cache_l3.fixbuf.storage), 16);
            tbc_pkg_standard.io.write(self);
            self->cache_l3.buffer.storage = (char*) ___msg_info_10;
            self->cache_l3.buffer.size =  (tbc_i8_t) sizeof(___msg_info_10) * (-1);
            tbc_pkg_standard.io.write(self);

            self->rc = TBC_RET_EXIT_FORCE;
            break;
        }
    }
    while(0);
}

void lang_3bc_cli_compile(tbc_app_st *const self)
{

}
