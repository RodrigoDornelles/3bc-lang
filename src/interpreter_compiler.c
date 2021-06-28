
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
    static char text_line[LINE_LIMIT + 3];
    static char text_reg[6], text_mem[12], text_val[12];
    static register_3bc_t reg;
    static address_3bc_t mem;
    static data_3bc_t val;
    char i;

    /** when end stream close it **/
    if(feof(stream)) {
        return 0;
    }
    /** try scan line **/
    if(fgets(text_line, sizeof (text_line), stream) == NULL){
        return 1;
    }

    /** more 1 line read **/
    APP_3BC->program.last_line += 1;

    /** line soo long **/
    if (text_line[LINE_LIMIT + 1] != 0) {
        driver_program_error(ERROR_LONG_LINE);
    }
    /** ignore comments **/
    for (i = 0; i < sizeof(text_line); i++) if (text_line[i] == '#') {
        text_line[i] = '\0';
        break;
    }
    /** scan string paterns **/
    if (!sscanf(text_line, "%s %s %s", text_reg, text_mem, text_val)){
        return 1;
    }
    /** blank line **/
    if(!text_line[0] || text_line[0] == '\0' || text_line[0] == '\n') {
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
    
    /** add new line **/
    tape_program_line_add(reg, mem, val);
    return 1;
}