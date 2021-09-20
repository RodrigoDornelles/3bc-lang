#include "3bc.h"

bool interpreter_syntax_registers(const char* string, signed long int* value)
{
    /** mnemonic translate world to register **/
    switch(PARSER_UNPACK(string))
    {
        PARSER_PACK('n', 'i', 'l', 'l', value, NILL);
        PARSER_PACK('m', 'o', 'd', 'e', value, MODE);

        PARSER_PACK('s', 't', 'r', 'b', value, STRB);
        PARSER_PACK('s', 't', 'r', 'i', value, STRI);
        PARSER_PACK('s', 't', 'r', 'c', value, STRC);
        PARSER_PACK('s', 't', 'r', 'o', value, STRO);
        PARSER_PACK('s', 't', 'r', 'x', value, STRX);

        PARSER_PACK('f', 'r', 'e', 'e', value, FREE);
        PARSER_PACK('a', 'l', 'o', 'c', value, ALOC);
        PARSER_PACK('p', 'u', 'l', 'l', value, PULL);
        PARSER_PACK('p', 'u', 's', 'h', value, PUSH);

        PARSER_PACK('m', 'o', 'f', 'f', value, MOFF);
        PARSER_PACK('m', 'm', 'a', 'x', value, MMAX);
        PARSER_PACK('m', 'm', 'i', 'n', value, MMIN);

        PARSER_PACK('g', 'o', 't', 'o', value, GOTO);
        PARSER_PACK('f', 'g', 't', 'o', value, FGTO);
        PARSER_PACK('z', 'g', 't', 'o', value, ZGTO);
        /** COLISIONS: SPIN, PGTO, MUSE **/
        PARSER_PACK('p', 'g', 't', 'o', value, PGTO); 
        PARSER_PACK('n', 'g', 't', 'o', value, NGTO);

        PARSER_PACK('n', 'b', '0', '2', value, NB02);
        PARSER_PACK('n', 'b', '0', '8', value, NB08);
        PARSER_PACK('n', 'b', '1', '0', value, NB10);
        PARSER_PACK('n', 'b', '1', '6', value, NB16);
        /** COLISIONS: MATH, TAIL **/
        PARSER_PACK('m', 'a', 't', 'h', value, MATH);

        PARSER_PACK('c', 'a', 'l', 'l', value, CALL);
        PARSER_PACK('f', 'r', 's', 't', value, FRST);
        PARSER_PACK('z', 'r', 's', 't', value, ZRST);
        PARSER_PACK('p', 'r', 's', 't', value, PRST);
        PARSER_PACK('n', 'r', 's', 't', value, NRST);
        PARSER_PACK('b', 'a', 'c', 'k', value, BACK);
    }

    /** passing register as numerical (octo, bin) **/
    if(interpreter_parser_strtol(string, value)){
        return true;
    }

    return false;
}

bool interpreter_syntax_constants(const char* string, signed long int* value)
{
    switch(PARSER_UNPACK(string))
    {
        PARSER_PACK('n', 'i', 'l', 'l', value, NILL);
        PARSER_PACK('f', 'u', 'l', 'l', value, SHRT_MAX);
        PARSER_PACK('s', 'k', 'i', 'p', value, interpreter_parser_skip());
    }

    if (interpreter_parser_strtol(string, value)){
        return true;
    }
    else if (interpreter_parser_strchar(string, value)){
        return true;    
    }
    else if (interpreter_parser_strhash(string, value)) {
        return true;
    }

    return false;
}