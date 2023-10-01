#include "3bc_types.h"
#include "bus/bus_mem_0000.h"
#include "util/util_stoi.h"
#include "util/util_asm.h"
#include "types/types_interpreter.h"
#include <stdio.h>

/**
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
    char* tokens[3];
    char* line;
    char* tmp;
    /** @todo better name for @c tokens_idk (i dont known a better name)*/
    tbc_i8_t tokens_idk[3];
    tbc_i8_t tokens_n;
    tbc_i8_t line_n;
    util_stoi_ft cast;

    do {
        if (self->state != FSM_3BC_READING) {
            break;
        }
        
        /* seperate line */
        line_n = util_asm_line(&line, &tmp, &interpreter->io.eval, interpreter->io.eval, interpreter->line_size);

        /* end of program */
        if (line_n == -1) {
            self->rc = TBC_RET_EXIT_FORCE;
            break;
        }

        if (line_n < 0) {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_INVALID_SYNTAX;
            break;
        }
        
        /* separate tokens */
        tokens_n = util_asm_split(tokens, line, sizeof(tokens)/sizeof(*tokens), line_n);

        if (tokens_n < 0) {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_INVALID_SYNTAX;
            break;
        }

        if (tokens_n != 1 && tokens_n != 3) {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_COLUMNS;
            break;
        }

        /* define tokens lenghts */
        tokens_idk[0] = tokens[1] - tokens[0] - 1;
        tokens_idk[1] = tokens[2] - tokens[1] - 1;
        tokens_idk[2] = line_n - (tokens[2] - tokens[0]);

        cast = util_stoi_auto(&tokens[0], &tokens_idk[0], tokens[0], tokens_idk[0]);
        if(cast == NULL || cast(&self->cpu.rx, tokens[0], 8, tokens_idk[0]) != 0) {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_INVALID_REGISTER;
            break;
        }
        cast = util_stoi_auto(&tokens[1], &tokens_idk[1], tokens[1], tokens_idk[1]);
        if(cast == NULL || cast(&self->cpu.ry, tokens[1], 16, tokens_idk[1]) != 0) {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_INVALID_ADR;
            break;
        }
        cast = util_stoi_auto(&tokens[2], &tokens_idk[2], tokens[2], tokens_idk[2]);
        if(cast == NULL || cast(&self->cpu.rz, tokens[2], 16, tokens_idk[2]) != 0) {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache_l1.error = ERROR_INVALID_CONSTANT;
            break;
        }

        self->rc = TBC_RET_FULL;
    }
    while(0);
}