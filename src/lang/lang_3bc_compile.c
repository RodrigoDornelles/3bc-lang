#include "3bc_types.h"
#include "bus/bus_mem_0000.h"
#include "types/types_interpreter.h"

static void lang_3bc_compile_output(tbc_app_st *const self);

/**
 * @par Fluxogram
 * @startuml
 * start
 * repeat
 * repeat :read char;
 * repeat while (line end?) is (no) not (yes)
 * repeat :parse line;
 * repeat while (multine line?) is (yes) not (no)
 * if (has label?) then (no)
 * break
 * else (yes)
 * endif
 * repeat while (label pos?) is (forward) not (backward)
 * repeat :commit;
 * repeat while (more lines?) is (yes)
 * stop
 * @enduml
 *
 * @par Extended Backus-Naur Form
 * @startebnf
 * line = instruction, [comment] | comment | tag;
 * instruction = register, address, constant;
 * comment = ("#" | ";"), {?any ASCII character? (* Ignore everything until\nline break or end of file *)}-;
 * register = mnemonic | number | nill;
 * address = character | number | hash | nill;
 * constant = character | number | hash | label | nill;
 * mnemonic = 4*"a-Z0-9";
 * number = ?0-9?, {?0-9? | "_"} | "0b", ?0-1?, {?0-1? | "_"} | "0o", ?0-7?, {?0-7? | "_"} | ("0d" | "0i"), ?0-9?, {?0-9? | "_"} | "0x", ?0-9A-F?, {?0-9A-F? | "_"};
 * nill = "nill";
 * character = "'", ?any ASCII character? , "'" | "'", "\", ("0" | "t" | "n" | "'" | "\") , "'" ;
 * hash = ":", { ?non-special ASCII character? }-;
 * label = "$", { ?non-special ASCII character? }-;
 * tag = { ?non-special ASCII character? }-, ":";
 * @endebnf
 */
void lang_3bc_compile(tbc_app_st *const self)
{
    tbc_interpreter_root_st *const interpreter = self->stack.cfg.interpreter;
    do {
        if (self->state != FSM_3BC_VACUUM) {
            break;
        }
        if(interpreter->type == TBC_IT_ERROR_OPEN_FILE) {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_OPEN_FILE;
            break;
        }
        if(interpreter->type == TBC_IT_INLINE) {
            self->rc = TBC_RET_EXIT_FORCE;
            break;
        }
    }
    while(0);
}