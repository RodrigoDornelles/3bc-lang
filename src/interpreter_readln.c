#define TBC_SOURCE_ENTRY
#include "3bc.h"

#if defined(TBC_INTERPRETER) && !defined(TBC_SCU_OPTIONAL_FIX)
/**
 * Interpret text and insert to virtual machine.
 *
 * EXAMPLE: interpreter_compiler(app, "MODE 0 2");
 * RETURN: NULL if the entire string is compiled.
 * RETURN: Pointer to the rest of the string that can be compiled.
 */
char* interpreter_readln(struct app_3bc_s* const app, char* line)
{
    char *text_reg, *text_mem, *text_val;
    signed long int reg, mem, val;

    /** scan more 1 line**/
    if (!interpreter_tokens(line, &text_reg, &text_mem, &text_val, &line)) {
        driver_program_error(app, ERROR_COLUMNS);
    }
    /** blank line **/
    if (text_reg == NULL) {
        return line;
    }
    /** parse string to register and validate **/
    if (!interpreter_syntax_registers(app, text_reg, &reg)) {
        driver_program_error(app, ERROR_INVALID_REGISTER);
    }
    /** parse string to address and validate **/
    if (!interpreter_syntax_constants(app, text_mem, &mem)) {
        driver_program_error(app, ERROR_INVALID_ADDRESS);
    }
    /** parse string to constant and validate **/
    if (!interpreter_syntax_constants(app, text_val, &val)) {
        driver_program_error(app, ERROR_INVALID_CONSTANT);
    }

    /** add new line **/
    ds_program_fifo_line_add(app, reg, mem, val);

    return line;
}
#endif
