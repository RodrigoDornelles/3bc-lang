#include "3bc.h"

#if !defined(_3BC_DISABLE_INTERPRETER)

void interpreter_compiler(app_3bc_t app, char* line)
{
    char *text_reg, *text_mem, *text_val;
    signed long int reg, mem, val;

    /** scan more 1 line**/
    if (!interpreter_tokens(line, &text_reg, &text_mem, &text_val)) {
        driver_program_error(ERROR_COLUMNS);
    }
    /** blank line **/
    if (text_reg == NULL) {
        return;
    }
    /** parse string to register and validate **/
    if (!interpreter_syntax_registers(text_reg, &reg)){
        driver_program_error(ERROR_INVALID_REGISTER);
    }
    /** parse string to address and validate **/
    if (!interpreter_syntax_constants(text_mem, &mem)){
        driver_program_error(ERROR_INVALID_ADDRESS);
    }
    /** parse string to constant and validate **/
    if (!interpreter_syntax_constants(text_val, &val)){
        driver_program_error(ERROR_INVALID_CONSTANT);
    }
    
    /** add new line **/
    tape_program_line_add(reg, mem, val);
}

#endif
