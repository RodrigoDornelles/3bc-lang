
#define LINE_LIMIT 29

/** 
 * Textually parse an instruction line
 * 
 * 
 * NOTE:
 * -> the line size the actual interpretation is (limit + 1) seeing the line break.
 * -> the character after limit has different from nul, that line was crossed.
 * -> text_line has the size (limit + 3) to respect text limit (line + 1).
 */
bool interpreter_compiler(file_t* stream)
{
    char* text_reg = NULL;
    char* text_mem = NULL;
    char* text_val = NULL;
    register_3bc_t reg;
    address_3bc_t mem;
    data_3bc_t val;

    /** more 1 line read **/
    APP_3BC->program.last_line += 1;

    /** when end stream close it **/
    if(feof(stream)) {
        return 0;
    }

    /** scan more 1 line**/
    if (!interpreter_tokens(stream, &text_reg, &text_mem, &text_val)) {
        driver_program_error(ERROR_COLUMNS);
    }

    /** blank line **/
    if (text_reg == NULL) {
        return 1;
    }

    /** parse string to register and validate **/
    if (!interpreter_syntax_registers(text_reg, (long int*) &reg)){
        driver_program_error(ERROR_INVALID_REGISTER);
    }
    /** parse string to address and validate **/
    if (!interpreter_syntax_constants(text_mem, (long int*) &mem)){
        driver_program_error(ERROR_INVALID_ADDRESS);
    }
    /** parse string to constant and validate **/
    if (!interpreter_syntax_constants(text_val, (long int*) &val)){
        driver_program_error(ERROR_INVALID_CONSTANT);
    }
    
    /** clear strings **/
    free(text_reg);
    free(text_mem);
    free(text_val);

    /** add new line **/
    tape_program_line_add(reg, mem, val);
    return 1;
}