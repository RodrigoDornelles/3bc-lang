#include "3bc_types.h"
#include "bus/bus_mem_0000.h"
#include "types/types_interpreter.h"

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
 * @par Finite State Machine
 * @startuml
 * [*] --> TBC_STATE_LANG_READ
 * TBC_STATE_LANG_READ --> TBC_STATE_LANG_LINE_SCAN
 * TBC_STATE_LANG_LINE_SCAN --> TBC_STATE_LANG_TYPE_TOKEN
 * TBC_STATE_LANG_TYPE_TOKEN --> TBC_STATE_LANG_LABEL_SCAN
 * TBC_STATE_LANG_TYPE_TOKEN --> TBC_STATE_LANG_COMMENT
 * TBC_STATE_LANG_COMMENT --> TBC_STATE_LANG_READ
 * TBC_STATE_LANG_LABEL_SCAN --> TBC_STATE_LANG_LABEL_COMMIT
 * TBC_STATE_LANG_LABEL_COMMIT --> TBC_STATE_LANG_READ
 * TBC_STATE_LANG_LABEL_COMMIT --> TBC_STATE_LANG_LINE_COMMIT
 * TBC_STATE_LANG_TYPE_TOKEN --> TBC_STATE_LANG_PARSE_RX
 * TBC_STATE_LANG_PARSE_RX --> TBC_STATE_LANG_PARSE_RY
 * TBC_STATE_LANG_PARSE_RY --> TBC_STATE_LANG_PARSE_RZ
 * TBC_STATE_LANG_PARSE_RZ --> TBC_STATE_LANG_LABEL_COMMIT
 * TBC_STATE_LANG_PARSE_RZ --> TBC_STATE_LANG_LINE_COMMIT
 * TBC_STATE_LANG_LINE_COMMIT --> TBC_STATE_LANG_LINE_PUSH
 * TBC_STATE_LANG_LINE_PUSH --> TBC_STATE_LANG_LINE_PUSH
 * TBC_STATE_LANG_LINE_PUSH --> [*]
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
    tbc_u8_t index;

    do {
        if (self->state != FSM_3BC_READING) {
            break;
        }
        switch (interpreter->state) {
            case TBC_STATE_LANG_READ:
                index = 0;
                while (index < interpreter->line_size) {
                    /* end of file */
                    if (*interpreter->io.argument == '\0') {
                        break;
                    }
                    /* linefeed */
                    if (*interpreter->io.argument == '\n') {
                        break;
                    }
                    /* alternative linefeed */
                    if (index >= 1 && 
                        interpreter->segments[index - 1] != '\'' &&
                        *interpreter->io.argument == ',') {
                        break;
                    }

                    interpreter->segments[index] = *interpreter->io.argument;
                    ++interpreter->io.argument;
                    ++index;
                }
                interpreter->segments[index] = '\0';
                interpreter->state = TBC_STATE_LANG_LINE_SCAN;
                break;

            case TBC_STATE_LANG_LINE_SCAN:
                /** @todo printf("line '%s'\n", interpreter->segments);*/
                break;

        }
    }
    while(0);
}