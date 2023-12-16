#define TBC_SOURCE_ENTRY
#include "3bc_types.h"
#include "bus/bus_mem_0000.h"
#include "util/util_djb2.h"
#include "util/util_stoi.h"
#include "util/util_ascii.h"
#include "util/util_dsl.h"
#include "lang/lang_3bc_cli.h"
#include "lang/lang_3bc_compile.h"

/** @todo remove <stdio.h> */
#ifndef TBC_TCC_NOSTDINC
#include <stdio.h>
#endif

union ___u8_u16_t {
    void* ptr;
    tbc_u8_t* u8;
    tbc_u16_t* u16;
};

/**
 * @brief
 * representation of the menomonics for registers
 * with their respective opcodes.
 *
 * @pre must be ordered.
 */
const char opcodes_key[] = "aloc"
    "back"  "call"  "fake"  "fcal"  "fgto"
    "free"  "fret"  "goto"  "math"  "micr"
    "mili"  "mode"  "moff"  "muse"  "nb02"
    "nb08"  "nb10"  "nb16"  "ncal"  "ngto"
    "nill"  "nret"  "pcal"  "pgto"  "pret"
    "pull"  "push"  "real"  "seco"  "spin"
    "strb"  "strc"  "stri"  "stro"  "strx"
    "zcal"  "zgto"  "zret";

const tbc_u8_t opcodes_val[] = { 2,
   1, 1, 2, 2, 2,
   1, 2, 1, 1, 3,
   4, 7, 3, 4, 1,
   2, 3, 4, 5, 5,
   0, 5, 4, 4, 4,
   3, 5, 1, 5, 4,
   1, 5, 3, 2, 4,
   3, 3, 3
};

static const tbc_u8_t column_size[] = {3, 9 ,12};
static const tbc_u8_t column_errors[] = {ERROR_INVALID_REGISTER,
    ERROR_INVALID_ADR, ERROR_INVALID_CONSTANT };

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
    union ___u8_u16_t cpu_r[3];
    char* tokens[3];
    char negative;
    char* line;
    char* tmp;
    /** @todo better name for @c tokens_idk (i dont known a better name)*/
    tbc_i8_t tokens_idk[3];
    tbc_i8_t tokens_n;
    tbc_i8_t line_n;
    util_stoi_ft cast;
    tbc_u8_t i = 0;

    cpu_r[0].ptr = &self->cpu.rx;
    cpu_r[1].ptr = &self->cpu.ry;
    cpu_r[2].ptr = &self->cpu.rz;

    do {
        if (self->state != FSM_3BC_READING) {
            break;
        }
        if (self->rc == TBC_RET_CLEAN) {
            self->rc = TBC_RET_OK;
            break;
        }
        if (interpreter->type == TBC_IT_STARTED_INFO) {
            lang_3bc_cli_put(self, 'i');
            self->rc = TBC_RET_EXIT_FORCE;
            break;
        }

        /* seperate line */
        line_n = util_dsl_line(&line, &tmp, &interpreter->io.eval, interpreter->io.eval, interpreter->line_size);

        /* end of program */
        if (line_n == -1) {
            self->rc = TBC_RET_EXIT_FORCE;
            break;
        }

        if (line_n < 0) {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache.l1.error = ERROR_INVALID_SYNTAX;
            break;
        }
        
        /* separate tokens */
        tokens_n = util_dsl_split(tokens, tokens_idk, line, sizeof(tokens)/sizeof(*tokens), line_n);

        if (tokens_n < 0) {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache.l1.error = ERROR_INVALID_SYNTAX;
            break;
        }

        if (!(tokens_n == 3 || (tokens[0][tokens_idk[0] - 1] == ':'))) {
            self->rc = TBC_RET_THROW_ERROR;
            self->cache.l1.error = ERROR_COLUMNS;
            break;
        }

        if(tokens_n == 1) {
            tbc_u16_t hash;
            util_djb2(&hash, tokens[0], 16, tokens_idk[0]);
            self->cache.l1.error = lang_3bc_compile_label_insert(interpreter, hash);
            if (self->cache.l1.error != ERROR_UNKNOWN) {
                self->rc = TBC_RET_THROW_ERROR;
            }
            break;
        }

        /* magic array parser*/
        while (i < tokens_n) {
            cast = util_stoi_auto(&tokens[i], &tokens_idk[i], tokens[i], tokens_idk[i]);
            if (cast != NULL) {
                self->cache.l1.error = cast(cpu_r[i].ptr, tokens[i], column_size[i], tokens_idk[i]);
            }
            else if (tokens[i][0] == ':') {                
                self->cache.l1.error = util_djb2(cpu_r[i].ptr, tokens[i], column_size[i], tokens_idk[i]);
            }
            else if (tokens[i][0] == '\'') {
                negative = util_ascii(tokens[i], tokens_idk[i]);
                if (negative == 0x15) {
                    self->cache.l1.error = ERROR_CHAR_SCAPE;
                    break;
                } 
                if (column_size[i] > 8) {
                    *cpu_r[i].u16 = negative;
                } else {
                    *cpu_r[i].u8 = negative;
                }
            }
            else if (tokens_idk[i] == 4) {
                tbc_i16_t key = util_dsl_keyword(tokens[i], opcodes_key, sizeof(opcodes_key));
                if (key >= 0) {
                    if (column_size[i] > 8) {
                        *cpu_r[i].u16 = opcodes_val[key];
                    } else {
                        *cpu_r[i].u8 = opcodes_val[key];
                    }
                } else {
                    self->cache.l1.error = ERROR_INVALID_MNEMONIC;
                }
            }
            else {
                self->cache.l1.error = column_errors[i];
            }
            if (self->cache.l1.error != ERROR_UNKNOWN) {
                self->rc = TBC_RET_THROW_ERROR;
                break;
            }
            ++i;
        }

        if (self->rc == TBC_RET_THROW_ERROR) {
            break;
        }

        self->rc = TBC_RET_FULL;
        ++interpreter->line;
    }
    while(0);
}

tbc_error_et lang_3bc_compile_label_insert(tbc_interpreter_root_st *const interpreter, tbc_u16_t hash)
{
    tbc_u16_t index;
    tbc_error_et res = ERROR_UNKNOWN;
    tbc_interpreter_label_st* segment_label;
    
    do {
        if ((interpreter->index_line + interpreter->index_label + sizeof(tbc_interpreter_label_st)) >= interpreter->segment_size) {
            res = ERROR_MEM_BUILDER_LABEL_OUT;
            break;
        }

        while (index <= interpreter->index_label) {
            index += sizeof(tbc_interpreter_label_st);
            segment_label = &interpreter->segments[interpreter->segment_size - index];
            if (segment_label->hash == hash) {
                res = ERROR_INVALID_LABEL_EXIST;
                break;
            }
        }

        segment_label->hash = hash;
        segment_label->line = interpreter->line;
        interpreter->index_label = index;
    }
    while(0);

    return res;
}
