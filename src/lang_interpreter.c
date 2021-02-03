#include "3bc.h"

#define PARSER_PACK(c1,c2,c3,c4,r,...)\
case c1+c2+c3+c4: *reg=r;return true;\
case c1+c2+c3+c4-128: *reg=r;return true

char lang_interpreter_line(file_t* stream)
{
    static char text_line[32];
    static char text_reg[6], text_mem[12], text_val[12];
    static reg_t reg;
    static mem_t mem;
    static val_t val;
    char i;

    /** when end stream close it **/
    if(feof(stream)) {
        return 0;
    }
    if(fgets(text_line, 32, stream) == NULL){
        return 1;
    }
    /** ignore comments **/
    for (i = 0; i < 32; i++) if (text_line[i] == '#') {
        text_line[i] = '\0';
        break;
    }
    /** scan string paterns **/
    if (!sscanf(text_line, "%5s %11s %11s", text_reg, text_mem, text_val)) {
        return 1;
    }
    /** blank line **/
    if(text_line[0] == '\0' || text_line[0] == '\n') {
        return 1;
    }
    /*** exit interpreter **/
    if(strcasecmp(text_reg, "exit") == 0) {
        return 0;
    }

    /** parse string to register and validate **/
    if (!lang_interpreter_world(text_reg, (int*) &reg)){
        lang_driver_error(ERROR_INVALID_REGISTER);
    }
    /** parse string to address and validate **/
    if (!lang_interpreter_value(text_mem, (int*) &mem)){
        lang_driver_error(ERROR_INVALID_ADDRESS);
    }
    /** parse string to constant and validate **/
    if (!lang_interpreter_value(text_val, (int*) &val)){
        lang_driver_error(ERROR_INVALID_CONSTANT);
    }
    
    /** add new line **/
    lang_line(reg, mem, val);
    return 1;
}

bool lang_interpreter_world(const char text_reg[6], int* reg)
{
    /** mnemonic translate world to register **/
    switch(text_reg[0] + text_reg[1] + text_reg[2] + text_reg[3])
    {
        PARSER_PACK('n', 'i', 'l', 'l', NILL);
        PARSER_PACK('m', 'o', 'd', 'e', MODE);

        PARSER_PACK('s', 't', 'r', 'i', STRI);
        PARSER_PACK('s', 't', 'r', 'c', STRC);
        PARSER_PACK('s', 't', 'r', 'o', STRO);
        PARSER_PACK('s', 't', 'r', 'x', STRX);
        PARSER_PACK('s', 't', 'r', 'u', STRU);

        PARSER_PACK('f', 'r', 'e', 'e', FREE);
        PARSER_PACK('a', 'l', 'o', 'c', ALOC);
        PARSER_PACK('p', 'u', 'l', 'l', PULL);
        PARSER_PACK('p', 'u', 's', 'h', PUSH);
        PARSER_PACK('t', 'c', 'f', 'g', TCFG);

        PARSER_PACK('g', 'o', 't', 'o', GOTO);
        PARSER_PACK('f', 'g', 't', 'o', FGTO);
        PARSER_PACK('z', 'g', 't', 'o', ZGTO);
        PARSER_PACK('p', 'g', 't', 'o', SPIN, PGTO, TMAX);
        PARSER_PACK('n', 'g', 't', 'o', NGTO, TMIN);

        PARSER_PACK('m', 'a', 't', 'h', MATH);
    }

    /** passing register as numerical (octo, bin) **/
    if(lang_driver_strtol(text_reg, (val_t *) reg)){
        return true;
    }

    return false;
}

bool lang_interpreter_value(const char text_value[12], int* value)
{
    if (lang_driver_strtol(text_value, (val_t *) value)){
        return true;
    }
    else if (sscanf(text_value, "'%c'", (char *) value)){
        return true;    
    }
    else if (strcasecmp(text_value, "nill") == 0){
        *value = 0;
        return true;
    }
    else if (strcasecmp(text_value, "full") == 0){
        *value = ~0;
        return true;
    }

    return false;
}
