#include "3bc.h"

bool lang_interpreter_world(const char text_reg[6], int* reg)
{
    /** mnemonic translate world to register **/
    switch(PARSER_UNPACK(text_reg))
    {
        PARSER_PACK('n', 'i', 'l', 'l', reg, NILL);
        PARSER_PACK('m', 'o', 'd', 'e', reg, MODE);

        PARSER_PACK('s', 't', 'r', 'i', reg, STRI);
        PARSER_PACK('s', 't', 'r', 'c', reg, STRC);
        PARSER_PACK('s', 't', 'r', 'o', reg, STRO);
        PARSER_PACK('s', 't', 'r', 'x', reg, STRX);

        PARSER_PACK('f', 'r', 'e', 'e', reg, FREE);
        PARSER_PACK('a', 'l', 'o', 'c', reg, ALOC);
        PARSER_PACK('p', 'u', 'l', 'l', reg, PULL);
        PARSER_PACK('p', 'u', 's', 'h', reg, PUSH);
        PARSER_PACK('t', 'c', 'f', 'g', reg, TCFG);

        PARSER_PACK('g', 'o', 't', 'o', reg, GOTO);
        PARSER_PACK('f', 'g', 't', 'o', reg, FGTO);
        PARSER_PACK('z', 'g', 't', 'o', reg, ZGTO);
        PARSER_PACK('p', 'g', 't', 'o', reg, SPIN, PGTO, TMAX);
        PARSER_PACK('n', 'g', 't', 'o', reg, NGTO, TMIN);

        PARSER_PACK('n', 'b', '0', '2', reg, NB02);
        PARSER_PACK('n', 'b', '0', '8', reg, NB08);
        PARSER_PACK('n', 'b', '1', '0', reg, NB10);
        PARSER_PACK('n', 'b', '1', '6', reg, NB16);

        PARSER_PACK('m', 'a', 't', 'h', reg, MATH);
    }

    /** passing register as numerical (octo, bin) **/
    if(lang_driver_strtol(text_reg, (signed long int *) reg)){
        return true;
    }

    return false;
}

bool lang_driver_strword(const char* string, signed long int* value)
{
    switch(PARSER_UNPACK(string))
    {
        PARSER_PACK('n', 'i', 'l', 'l', value, NILL);
        PARSER_PACK('f', 'u', 'l', 'l', value, SHRT_MAX);
        PARSER_PACK('s', 'k', 'i', 'p', value, lang_driver_skip());
    }

    return false;
}