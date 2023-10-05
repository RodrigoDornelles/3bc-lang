#include "3bc_types.h"
#include "bus/bus_mem_0000.h"
#include "util/util_stoi.h"
#include "util/util_asm.h"
#include "types/types_interpreter.h"
#include <stdio.h>

/**
 * @brief
 * representation of the menomonics for registers
 * with their respective opcodes.
 *
 * @note must be ordered.
 *
 * @par JOKE
 * why you need for CPP if C language is already 'complete and total'?
 * { .keyword.name = "mode", .opcode = 7 } <-- not allowed in C++
 */
static const struct tbc_keyword_opcode_st opcodes_register[] = { { "aloc", 2 },
    { "back", 1 }, { "call", 1 }, { "fake", 2 }, { "fcal", 2 }, { "fgto", 2 },
    { "free", 1 }, { "fret", 2 }, { "goto", 1 }, { "math", 1 }, { "micr", 3 },
    { "mili", 4 }, { "mode", 7 }, { "moff", 3 }, { "muse", 4 }, { "nb02", 1 },
    { "nb08", 2 }, { "nb10", 3 }, { "nb16", 4 }, { "ncal", 5 }, { "ngto", 5 },
    { "nill", 0 }, { "nret", 5 }, { "pcal", 4 }, { "pgto", 4 }, { "pret", 4 },
    { "pull", 3 }, { "push", 5 }, { "real", 1 }, { "seco", 5 }, { "spin", 4 },
    { "strb", 1 }, { "strc", 5 }, { "stri", 3 }, { "stro", 2 }, { "strx", 4 },
    { "zcal", 3 }, { "zgto", 3 }, { "zret", 3 } };

static const tbc_i8_t opcodes_register_size
    = sizeof(opcodes_register) / sizeof(struct tbc_keyword_opcode_st);

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
        if (self->rc == TBC_RET_CLEAN) {
            self->rc = TBC_RET_OK;
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
        tokens_n = util_asm_split(tokens, tokens_idk, line, sizeof(tokens)/sizeof(*tokens), line_n);

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