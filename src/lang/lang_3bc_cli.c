#define TBC_SOURCE_ENTRY
#include "lang/lang_3bc_cli.h"
#include "lang/lang_3bc_put.h"
#include "util/util_stoi.h"
#include "util/util_args.h"
#include "types/types_interpreter.h"
#include "pre/pre_sizes.h"
#if defined(TBC_USE_POSIX)
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
                self->cache_l1.error = ERROR_FLAG_LINE;
                break;
            }
            interpreter->line_size = new_line_size;
        }
        /* info flags */
        if (util_args_has(argc, argv, 'v') != NULL) {
            lang_3bc_put(self, 'v');
            self->rc = TBC_RET_EXIT_FORCE;
            break;
        }
        if (util_args_has(argc, argv, 'i') != NULL) {
            lang_3bc_put(self, 'i');
            self->rc = TBC_RET_EXIT_FORCE;
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
#if !defined(TBC_NOT_FILES)
            int fileid = open(param, O_RDONLY);
            if (fileid != -1) {   
                interpreter->type = TBC_IT_COMPILER;
                interpreter->io.fileid = fileid;
                break;
            }
#endif
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_OPEN_FILE;
            break;
        }

        interpreter->type = TBC_IT_REPL;
        interpreter->line_size = 0;
    }
    while(0);
}
