#include "3bc.h"

/**
 * convert string in any numeric base
 */
bool interpreter_parser_strtol(const char* string, signed long int* value)
{
    static char decode[32];
    static char* endptr;
    static char type;
    
    /** verify valid number **/
    if (string[0] != '-' && !isdigit(string[0])){
        return false;
    }

    /** protect original string **/
    strcpy(decode, string);

    /** custom base with sign **/
    if(decode[0] == '-' && decode[1] == '0' && !isdigit(2) && decode[2] != '\0'){
        type = tolower(decode[2]);
        memmove(&decode[2], &decode[3], strlen(decode) - 2);
    }
    /** custom base whiout sign **/
    else if(decode[0] == '0' && !isdigit(1) && decode[1] != '\0') {
        type = tolower(decode[1]);
        memmove(&decode[1], &decode[2], strlen(decode) - 1);
    }
    /** decimal base **/
    else {
        type = 'd';
    }

    /** reset error **/
    errno = 0;

    /** convert string to number **/
    switch(type) {
        case 'x':
            /** base hexadecimal **/
            *value = strtol(decode, &endptr, 16);
            break;

        case 'i':
        case 'd':
            /** base decimal **/
            *value = strtol(decode, &endptr, 10);
            break;

        case 'o':
            /** base octal **/
            *value = strtol(decode, &endptr, 8);
            break;

        case 'b':
            /** base binary **/
            *value = strtol(decode, &endptr, 2);
            break;

        default:
            /** base invalid **/
            driver_program_error(ERROR_NUMBER_WRONG_BASE); 
    }

    if (decode == endptr){
        driver_program_error(ERROR_NUMBER_NO_DIGITS);
    }
    else if (errno == ERANGE && *value == LONG_MIN){
        driver_program_error(ERROR_NUMBER_UNDERFLOW);
    }
    else if (errno == ERANGE && *value == LONG_MAX){
        driver_program_error(ERROR_NUMBER_OVERFLOW);
    }
    #ifdef EINVAL
    /** not in all c99 implementations **/
    else if (errno == EINVAL){ 
        driver_program_error(ERROR_NUMBER_WRONG_BASE); 
    }
    #endif
    else if (errno != 0 && *value == 0){
        driver_program_error(ERROR_NUMBER_UNKOWN);    
    }
    else if (errno == 0 && *endptr != 0){
        driver_program_error(ERROR_NUMBER_DIRTY);    
    }

    return true;
}

bool interpreter_parser_strchar(const char* string, signed long int* value)
{
    /** not init with (') **/
    if (string[0] != 0x27) {
        return false;
    }

    /** not ends with (') **/
    if (string[2] != 0x27 && string[3] != 0x27) {
        driver_program_error(ERROR_CHAR_SIZE);
    }

    /** single char **/
    if (string[3] != 0x27) {
        *value = string[1];
        return true;
    }

    /** not scape **/
    if (string[1] != '\\') {
        driver_program_error(ERROR_CHAR_SIZE);
    }

    /** scape controll char **/
    switch (string[2]) 
    {
        case '0': *value = 0x00; break;
        case 'a': *value = 0x07; break;
        case 'b': *value = 0x08; break;
        case 't': *value = 0x09; break;
        case 'n': *value = 0x0A; break;
        case '\'': *value = 0x27; break;
        case '\\': *value = 0x5c; break;
        default: driver_program_error(ERROR_CHAR_SCAPE);
    }

    return true;
}

bool interpreter_parser_strhash(const char* string, signed long int* value)
{
    register unsigned long hash = 5381;
    int c;

    /** is not hash **/
    if (string[0] != '"') {
        return false;
    }

    /** djb2 algorithm **/
    for(;(c = *string++); hash = ((hash << 5) + hash) + c);
    *value = hash % SHRT_MAX;

    return true;
}

/**
 * algorithm of djb2 hash to string "skip" + count every two calls
 */
int interpreter_parser_skip()
{
    static int counter = 0;
    register unsigned long hash = 15376; /* hash to skip */
    int c = (counter++) / 2; /** count after 2 calls **/

    do {
        hash = ((hash << 5) + hash) + (c % 10) + '0';
        c /= 10;
    } while (c > 0);

    return hash % SHRT_MAX;
}
