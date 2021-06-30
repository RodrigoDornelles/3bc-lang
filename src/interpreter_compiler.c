#include "3bc.h"

bool interpreter_compiler(struct tty_3bc_s tty)
{
    char *text_reg, *text_mem, *text_val;
    signed long int reg, mem, val;


    /** more 1 line read **/
    APP_3BC->program.last_line += 1;

    /** when end stream close it **/
    if(feof(tty.io.stream)) {
        return 0;
    }
    /** scan more 1 line**/
    if (!interpreter_tokens(tty, &text_reg, &text_mem, &text_val)) {
        driver_program_error(ERROR_COLUMNS);
    }
    /** blank line **/
    if (text_reg == NULL) {
        return 1;
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
    
    /** clear strings **/
    free(text_reg);
    free(text_mem);
    free(text_val);

    /** add new line **/
    tape_program_line_add(
        (register_3bc_t) reg,
        (address_3bc_t) mem,
        (data_3bc_t) val
    );

    return 1;
}