#include "3bc.h"

#define PARSER_PACK(c1,c2,c3,c4,reg,...)\
case c1+c2+c3+c4: return reg;\
case c1+c2+c3+c4-128: return reg

char lang_interpreter_line(file_t* stream)
{
    static char text_line[32];
    static char text_reg[6], text_mem[12], text_val[12];
    static reg_t reg;
    static mem_t mem;
    static val_t val;
    char i;

    if(feof(stream)) {
        return 0;
    }
    if(fgets(text_line, 32, stream) == NULL){
        return 1;
    }
    for (i = 0; i < 32; i++) if (text_line[i] == '#') {
        text_line[i] = '\0';
        break;
    }
    if (!sscanf(text_line, "%5s %11s %11s", text_reg, text_mem, text_val)) {
        return 1;
    }
    if(text_line[0] == '\0' || text_line[0] == '\n') {
        return 1;
    }
    if(strcasecmp(text_reg, "exit") == 0) {
        return 0;
    }

    reg = (reg_t) lang_interpreter_world(text_reg);
    mem = (mem_t) lang_interpreter_value(text_mem);
    val = (val_t) lang_interpreter_value(text_val);

    if (reg || mem || val) {
        lang_line(reg, mem, val);
    }

    return 1;
}

reg_t lang_interpreter_world(const char text_reg[6])
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
    if(lang_driver_strtol(text_reg, (val_t *) &text_reg[0])){
        return (reg_t) text_reg[0];
    }

    lang_driver_error(ERROR_INTERPRETER_REGISTER);
    return RETURN_EXIT;
}

signed int lang_interpreter_value(const char text_value[12])
{
    static signed int value;
    if (lang_driver_strtol(text_value, (val_t *) &value)){
        return value;
    }
    else if (sscanf(text_value, "'%c'", (char *) &value)){
        return value;
    }
    else if (strcasecmp(text_value, "nill") == 0) {
        return 0x0;
    }
    else if (strcasecmp(text_value, "full") == 0) {
        static val_t full = 0;
        return ~full;
    }

    lang_driver_error(ERROR_INTERPRETER_NUMBER);
    return RETURN_EXIT;
}
