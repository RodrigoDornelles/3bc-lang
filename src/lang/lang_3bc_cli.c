#define TBC_SOURCE_ENTRY
#include "bus/bus_mem_0000.h"
#include "bus/bus_sys_0000.h"
#include "i18n/i18n_0000.h"
#include "lang/lang_3bc_cli.h"
#include "util/util_stoi.h"
#include "util/util_itos.h"
#include "util/util_args.h"
#include "types/types_interpreter.h"
#include "pre/pre_sizes.h"
#include "detect/detect_libc.h"
#if defined(TBC_LIBC_POSIX)
#include <fcntl.h>
#endif

void lang_3bc_cli_init(tbc_app_st *const self, int argc, char** argv, void* buf, tbc_u16_t size)
{
    char* param;
    tbc_interpreter_root_st *const interpreter = self->stack.cfg.interpreter;
    interpreter->segments = buf;
    interpreter->line_size = TBC_DEFAULT_LINE_SIZE;
    
    do {
        char* param;
        /* config flags */
        if ((param = util_args_get(argc, argv, 'l')) != NULL) {
            tbc_u8_t new_line_size;
            if (util_stoi10(&new_line_size, param, 8, 3) != 0) {
                self->rc = TBC_RET_THROW_ERROR;
                self->cache.l1.error = ERROR_FLAG_LINE;
                break;
            }
            interpreter->line_size = new_line_size;
        }
        /* info flags */
        if (util_args_has(argc, argv, 'h') != NULL) {
            lang_3bc_cli_put(self, 'h');
            self->rc = TBC_RET_EXIT_FORCE;
            break;
        }
        if (util_args_has(argc, argv, 'v') != NULL) {
            lang_3bc_cli_put(self, 'v');
            self->rc = TBC_RET_EXIT_FORCE;
            break;
        }
        if (util_args_has(argc, argv, 'V') != NULL) {
            lang_3bc_cli_put(self, 'V');
            self->rc = TBC_RET_EXIT_FORCE;
            break;
        }
        if (util_args_has(argc, argv, 'i') != NULL) {
            lang_3bc_cli_put(self, 'i');
            self->rc = TBC_RET_EXIT_FORCE;
            break;
        }
        if (util_args_has(argc, argv, 'I') != NULL) {
            interpreter->type = TBC_IT_STARTED_INFO;
            break;
        }
        /* program flag */
        if ((param = util_args_get(argc, argv, 'e')) != NULL) {
            interpreter->type = TBC_IT_INLINE;
            interpreter->io.eval = param;
            break;
        }
        /* program param */
        if ((param = util_args_param(argc, argv, "le", 0)) != NULL) {
#if !defined(TBC_NOT_FILES) && defined(TBC_LIBC_POSIX)
            int fileid = open(param, O_RDONLY);
            if (fileid != -1) {   
                interpreter->type = TBC_IT_COMPILER;
                interpreter->io.fileid = fileid;
                break;
            }
#endif
            self->rc = TBC_RET_THROW_ERROR;
            self->cache.l1.error = ERROR_OPEN_FILE;
            break;
        }

        interpreter->type = TBC_IT_REPL;
        interpreter->line_size = 0;
    }
    while(0);
}

void lang_3bc_cli_put(tbc_app_st *const self, char key)
{
    tbc_u8_t sizetotalstack = self->stack.raw.buffer != NULL? self->stack.mem->st: sizeof(self->stack.cfgmin) - (sizeof(void*) * 2);
    tbc_u8_t sizefreestack = self->stack.raw.buffer != NULL? self->stack.mem->st - self->stack.mem->sp: 0;
    tbc_u16_t sizeobject = sizeof(tbc_app_st);
    tbc_u8_t i = 0, j = 0;

    switch (key)
    {
        case 'v':
            self->cache.l3.buffer.storage = (char*) tbc_i18n_commons[I18N_COMMON_VERSION].ptr;
            self->cache.l3.buffer.size = -tbc_i18n_commons[I18N_COMMON_VERSION].len;
            tbc_pkg_standard.io.write(self);
            break;
        
        case 'V':
            while (i <= I18N_COMMON_VERPLUS) {
                self->cache.l3.buffer.storage = (char*) tbc_i18n_commons[i].ptr;
                self->cache.l3.buffer.size = -tbc_i18n_commons[i].len;
                tbc_pkg_standard.io.write(self);
                ++i;
            }
            break;
        case 'h':
            while (i < tbc_i18n_help_len) {
                self->cache.l3.buffer.storage = (char*) tbc_i18n_help_arr[i].ptr;
                self->cache.l3.buffer.size = -tbc_i18n_help_arr[i].len;
                if (tbc_i18n_help_arr[i].len == 0) {
                    self->cache.l3.buffer.storage = (char*) tbc_i18n_commons[I18N_COMMON_WEBSITE].ptr;
                    self->cache.l3.buffer.size = -tbc_i18n_commons[I18N_COMMON_WEBSITE].len;
                }
                tbc_pkg_standard.io.write(self);
                ++i;
            }
            break;
        case 'i':
            while (i < tbc_i18n_info_len) {
                self->cache.l3.buffer.storage = (char*) tbc_i18n_info_arr[i].ptr;
                self->cache.l3.buffer.size = -tbc_i18n_info_arr[i].len;
                if (tbc_i18n_info_arr[i].len == 0) {
                    switch (j) {
                        case 0:
                        self->cache.l3.buffer.storage = (char*) tbc_i18n_commons[I18N_COMMON_VERSION].ptr;
                        self->cache.l3.buffer.size = -tbc_i18n_commons[I18N_COMMON_VERSION].len;
                        break;
                        case 1:
                        self->cache.l3.buffer.storage = (char*) tbc_i18n_commons[I18N_COMMON_VERPLUS].ptr;
                        self->cache.l3.buffer.size = -tbc_i18n_commons[I18N_COMMON_VERPLUS].len;
                        break;
                        case 2:
                        self->cache.l3.fixbuf.size = util_itos10(self->cache.l3.fixbuf.storage, &sizetotalstack, sizeof(self->cache.l3.fixbuf.storage), 8);
                        break;
                        case 3:
                        self->cache.l3.fixbuf.size = util_itos10(self->cache.l3.fixbuf.storage, &sizefreestack, sizeof(self->cache.l3.fixbuf.storage), 8);
                        break;
                        case 4:
                        self->cache.l3.fixbuf.size = util_itos10(self->cache.l3.fixbuf.storage, &sizeobject, sizeof(self->cache.l3.fixbuf.storage), 16);
                        break;
                        case 5:
                        self->cache.l3.fixbuf.size = util_itos10(self->cache.l3.fixbuf.storage, &tbc_total_heap, sizeof(self->cache.l3.fixbuf.storage), sizeof(tbc_total_heap) * 8);
                        break;
                    }
                    ++j;
                }
                tbc_pkg_standard.io.write(self);
                ++i;
            }
            break;
    }
}
