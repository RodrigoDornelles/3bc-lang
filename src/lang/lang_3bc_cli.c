#define TBC_SOURCE_ENTRY
#include "lang/lang_3bc_cli.h"
#include "lang/lang_3bc_put.h"
#include "util/util_itos.h"
#include "util/util_args.h"
#include "types/types_interpreter.h"
#if defined(TBC_USE_POSIX)
#include <fcntl.h>
#endif

void lang_3bc_cli_init(tbc_app_st *const self, int argc, char** argv)
{
    do {
        char* prog;
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
        if ((prog = util_args_get(argc, argv, 'e')) != NULL) {
            ((tbc_interpreter_root_st*)self->stack.cfg.interpreter)->type = TBC_IT_INLINE;
            ((tbc_interpreter_root_st*)self->stack.cfg.interpreter)->io.argument = prog;
            break;
        }
        if ((prog = util_args_param(argc, argv, "e", 0)) != NULL) {
            int fileid = open(prog, O_RDONLY);
            if (fileid == -1) {
                ((tbc_interpreter_root_st*)self->stack.cfg.interpreter)->type = TBC_IT_ERROR_OPEN_FILE;
                break;
            }
            break;
        }

        ((tbc_interpreter_root_st*)self->stack.cfg.interpreter)->type = TBC_IT_REPL;
    }
    while(0);
}

void lang_3bc_cli_compile(tbc_app_st *const self)
{
    if (self->state == FSM_3BC_VACUUM) {
        if(((tbc_interpreter_root_st*)self->stack.cfg.interpreter)->type == TBC_IT_ERROR_OPEN_FILE) {
            ((tbc_interpreter_root_st*)self->stack.cfg.interpreter)->type = TBC_IT_NONE;
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_OPEN_FILE;
        }
        if(((tbc_interpreter_root_st*)self->stack.cfg.interpreter)->type == TBC_IT_INLINE) {
            
        }
    }
}
