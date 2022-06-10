#include "3bc.h"

/**
 * JOKE:
 *
 * anyone asks me why this code spaghetti,
 * easy, arduino-cli/arduino-ide forced me.
 */

#if !(defined(ARDUINO) && defined(_3BC_SCU_FIX_2))                             \
    || (!defined(ARDUINO) && defined(_3BC_SCU_FIX))

#if (!defined(_3BC_ENABLE_INTERPRETER) && !defined(_3BC_DISABLE_INTERPRETER))  \
    || (defined(_3BC_ENABLE_INTERPRETER) && defined(_3BC_DISABLE_INTERPRETER))
#error                                                                         \
    "Required define '_3BC_ENABLE_INTERPRETER' or '_3BC_DISABLE_INTERPRETER' after include header '3bc.h'"

#elif defined(_3BC_DISABLE_INTERPRETER)
int interpreter_3bc(struct app_3bc_s *const app)
{
    return EOF;
}

#elif defined(_3BC_ENABLE_INTERPRETER)
int interpreter_3bc(struct app_3bc_s *const app);
char* interpreter_3bc_compiler(struct app_3bc_s *const app, char* line);
bool interpreter_3bc_parser_strtol(
    struct app_3bc_s *const app, const char* string, signed long int* value);
bool interpreter_3bc_parser_strchar(
    struct app_3bc_s *const app, const char* string, signed long int* value);
bool interpreter_3bc_parser_strhash(const char* string, signed long int* value);
int interpreter_3bc_parser_skip();
int interpreter_3bc_read(struct app_3bc_s *const app);
bool interpreter_3bc_syntax_registers(
    struct app_3bc_s *const app, const char* string, signed long int* value);
bool interpreter_3bc_syntax_constants(
    struct app_3bc_s *const app, const char* string, signed long int* value);
bool interpreter_3bc_tokens(
    char* line, char** reg, char** mem, char** val, char** line_end);

/**
 *  Default entry point to the interpreter, works asynchronously.
 *
 * RETURN: EOF if there is nothing else to read.
 * RETURN: 1 if the interpretation was successful.
 */
int interpreter_3bc(struct app_3bc_s *const app)
{
    int character = fgetc(app->tty_source.io.stream);

#if defined(_3BC_NUTTX)
    if (app->tty_source.type == STREAM_TYPE_COMPUTER_STD) {
        driver_tty_output(app, app->tty_keylog, STRC, character);
    }
#endif

    /** end of file **/
    if (character == EOF && app->cache_l3.buffer.storage == NULL) {
        return EOF;
    }

    /** end of line **/
    if (character == '\n' || character == '\r' || character == '\0'
        || character == EOF) {
/** REPL nuttx compatibily **/
#if defined(_3BC_NUTTX)
        if (app->tty_source.type == STREAM_TYPE_COMPUTER_STD) {
            driver_tty_output(app, app->tty_keylog, STRC, '\n');
        }
#endif

        /** mark end of string **/
        {
            char* new_buffer = (char*)realloc(app->cache_l3.buffer.storage,
                sizeof(char) * (++app->cache_l3.buffer.size));
            if (new_buffer == NULL) {
                driver_program_error(app, ERROR_OUT_OF_MEMORY);
            }
            app->cache_l3.buffer.storage = new_buffer;
            app->cache_l3.buffer.storage[app->cache_l3.buffer.size - 1] = '\0';
        }

        /** insert to vm **/
        char* line = app->cache_l3.buffer.storage;
        do {
            app->program.last_line += 1;
            line = interpreter_3bc_compiler(app, line);
        } while (line != NULL);

        /** reset buffer **/
        {
            free(app->cache_l3.buffer.storage);
            app->cache_l3.buffer.storage = NULL;
            app->cache_l3.buffer.size = 0;
        }

        return 1;
    }

    /** expand the  buffer **/
    {
        char* new_buffer = (char*)realloc(app->cache_l3.buffer.storage,
            sizeof(char) * (++app->cache_l3.buffer.size));

        if (new_buffer == NULL) {
            driver_program_error(app, ERROR_OUT_OF_MEMORY);
        }

        app->cache_l3.buffer.storage = new_buffer;
        app->cache_l3.buffer.storage[app->cache_l3.buffer.size - 1] = character;
    }

    return 0;
}

/**
 * Interpret text and insert to virtual machine.
 *
 * EXAMPLE: interpreter_3bc_compiler(app, "MODE 0 2");
 * RETURN: NULL if the entire string is compiled.
 * RETURN: Pointer to the rest of the string that can be compiled.
 */
char* interpreter_3bc_compiler(struct app_3bc_s *const app, char* line)
{
    char *text_reg, *text_mem, *text_val;
    signed long int reg, mem, val;

    /** scan more 1 line**/
    if (!interpreter_3bc_tokens(line, &text_reg, &text_mem, &text_val, &line)) {
        driver_program_error(app, ERROR_COLUMNS);
    }
    /** blank line **/
    if (text_reg == NULL) {
        return line;
    }
    /** parse string to register and validate **/
    if (!interpreter_3bc_syntax_registers(app, text_reg, &reg)) {
        driver_program_error(app, ERROR_INVALID_REGISTER);
    }
    /** parse string to address and validate **/
    if (!interpreter_3bc_syntax_constants(app, text_mem, &mem)) {
        driver_program_error(app, ERROR_INVALID_ADDRESS);
    }
    /** parse string to constant and validate **/
    if (!interpreter_3bc_syntax_constants(app, text_val, &val)) {
        driver_program_error(app, ERROR_INVALID_CONSTANT);
    }

    /** add new line **/
    ds_program_fifo_line_add(app, reg, mem, val);

    return line;
}

/**
 * convert string in any numeric base
 */
bool interpreter_3bc_parser_strtol(
    struct app_3bc_s *const app, const char* string, signed long int* value)
{
    char* endptr = NULL;
    char decode[32];
    char type;

    /** verify valid number **/
    if (string[0] != '-' && !isdigit(string[0])) {
        return false;
    }

    /** protect original string **/
    strcpy(decode, string);

    /** custom base with sign **/
    if (decode[0] == '-' && decode[1] == '0' && !isdigit(decode[2])
        && decode[2] != '\0') {
        type = tolower(decode[2]);
        memmove(&decode[2], &decode[3], sizeof(decode) - 3);
    }
    /** custom base whiout sign **/
    else if (decode[0] == '0' && !isdigit(decode[1]) && decode[1] != '\0') {
        type = tolower(decode[1]);
        memmove(&decode[1], &decode[2], sizeof(decode) - 2);
    }
    /** decimal base **/
    else {
        type = 'd';
    }

    /** reset error **/
    errno = 0;

    /** convert string to number **/
    switch (type) {
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
        driver_program_error(app, ERROR_NUMBER_WRONG_BASE);
    }

    if (decode == endptr) {
        driver_program_error(app, ERROR_NUMBER_NO_DIGITS);
    } else if (errno == ERANGE && *value == LONG_MIN) {
        driver_program_error(app, ERROR_NUMBER_UNDERFLOW);
    } else if (errno == ERANGE && *value == LONG_MAX) {
        driver_program_error(app, ERROR_NUMBER_OVERFLOW);
    }
#if defined(EINVAL)
    /** not in all c99 implementations **/
    else if (errno == EINVAL) {
        driver_program_error(app, ERROR_NUMBER_WRONG_BASE);
    }
#endif
    else if (errno != 0 && *value == 0) {
        driver_program_error(app, ERROR_NUMBER_WRONG_BASE);
    } else if (errno == 0 && *endptr != 0) {
        driver_program_error(app, ERROR_NUMBER_WRONG_BASE);
    }

    return true;
}

bool interpreter_3bc_parser_strchar(
    struct app_3bc_s *const app, const char* string, signed long int* value)
{
    /** not init with (') **/
    if (string[0] != 0x27) {
        return false;
    }

    /** not ends with (') **/
    if (string[2] != 0x27 && string[3] != 0x27) {
        driver_program_error(app, ERROR_CHAR_SIZE);
    }

    /** single char **/
    if (string[3] != 0x27) {
        *value = string[1];
        return true;
    }

    /** not scape **/
    if (string[1] != '\\') {
        driver_program_error(app, ERROR_CHAR_SIZE);
    }

    /** scape controll char **/
    switch (string[2]) {
    case '0':
        *value = 0x00;
        break;
    case 'a':
        *value = 0x07;
        break;
    case 'b':
        *value = 0x08;
        break;
    case 't':
        *value = 0x09;
        break;
    case 'n':
        *value = 0x0A;
        break;
    case '\'':
        *value = 0x27;
        break;
    case '\\':
        *value = 0x5c;
        break;
    default:
        driver_program_error(app, ERROR_CHAR_SCAPE);
    }

    return true;
}

/**
 * Text Equivalent Hash Generator.
 */
bool interpreter_3bc_parser_strhash(const char* string, signed long int* value)
{
    register unsigned long hash = 5381;
    int c;

    /** is not hash **/
    if (string[0] != ':') {
        return false;
    }

    /** djb2 algorithm **/
    for (; (c = *string++); hash = ((hash << 5) + hash) + c)
        ;
    *value = hash % SHRT_MAX;

    return true;
}

/**
 * algorithm of djb2 hash to string "skip" + count every two calls
 */
int interpreter_3bc_parser_skip()
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

bool interpreter_3bc_syntax_registers(
    struct app_3bc_s *const app, const char* string, signed long int* value)
{
    /** mnemonic translate world to register **/
    switch (PARSER_UNPACK(string)) {
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
        PARSER_PACK('s', 'p', 'i', 'n', value, SPIN);
        PARSER_PACK('p', 'u', 's', 'h', value, PUSH);

        PARSER_PACK('m', 'o', 'f', 'f', value, MOFF);
        PARSER_PACK('m', 'u', 's', 'e', value, MUSE);

        PARSER_PACK('g', 'o', 't', 'o', value, GOTO);
        PARSER_PACK('f', 'g', 't', 'o', value, FGTO);
        PARSER_PACK('z', 'g', 't', 'o', value, ZGTO);
        PARSER_PACK('p', 'g', 't', 'o', value, PGTO);
        PARSER_PACK('n', 'g', 't', 'o', value, NGTO);

        PARSER_PACK('n', 'b', '0', '2', value, NB02);
        PARSER_PACK('n', 'b', '0', '8', value, NB08);
        PARSER_PACK('n', 'b', '1', '0', value, NB10);
        PARSER_PACK('n', 'b', '1', '6', value, NB16);

        PARSER_PACK('m', 'a', 't', 'h', value, MATH);

        PARSER_PACK('c', 'a', 'l', 'l', value, CALL);
        PARSER_PACK('f', 'c', 'a', 'l', value, FCAL);
        PARSER_PACK('z', 'c', 'a', 'l', value, ZCAL);
        PARSER_PACK('p', 'c', 'a', 'l', value, PCAL);
        PARSER_PACK('n', 'c', 'a', 'l', value, NCAL);

        PARSER_PACK('f', 'r', 'e', 't', value, FRET);
        PARSER_PACK('z', 'r', 'e', 't', value, ZRET);
        PARSER_PACK('p', 'r', 'e', 't', value, PRET);
        PARSER_PACK('n', 'r', 'e', 't', value, NRET);
        PARSER_PACK('b', 'a', 'c', 'k', value, BACK);

        PARSER_PACK('r', 'e', 'a', 'l', value, REAL);
        PARSER_PACK('f', 'a', 'k', 'e', value, FAKE);
        PARSER_PACK('m', 'i', 'c', 'r', value, MICR);
        PARSER_PACK('m', 'i', 'l', 'i', value, MILI);
        PARSER_PACK('s', 'e', 'c', 'o', value, SECO);
    }

    /** passing register as numerical (octo, bin) **/
    if (interpreter_3bc_parser_strtol(app, string, value)) {
        return true;
    }

    return false;
}

bool interpreter_3bc_syntax_constants(
    struct app_3bc_s *const app, const char* string, signed long int* value)
{
    switch (PARSER_UNPACK(string)) {
        PARSER_PACK('n', 'i', 'l', 'l', value, NILL);
        PARSER_PACK('f', 'u', 'l', 'l', value, SHRT_MAX);
        PARSER_PACK('s', 'k', 'i', 'p', value, interpreter_3bc_parser_skip());
    }

    if (interpreter_3bc_parser_strtol(app, string, value)) {
        return true;
    } else if (interpreter_3bc_parser_strchar(app, string, value)) {
        return true;
    } else if (interpreter_3bc_parser_strhash(string, value)) {
        return true;
    }

    return false;
}

/**
 * Separator in columns and rows.
 *
 * REFERENCE: 'reg' receive the first column
 * REFERENCE: 'mem' receive the second column
 * REFERENCE: 'val' receive the thirdy column
 * REFERENCE: 'line_end' NULL if the string is used completely.
 * REFERENCE: 'line_end' Pointer to the rest of the text if there are still
 * other lines. RETURN: true if the number of columns is valid. RETURN: true if
 * the number of columns is valid.
 *
 */
bool interpreter_3bc_tokens(
    char* line, char** reg, char** mem, char** val, char** line_end)
{
    unsigned char columns = 0;
    char* pointer = line;

    /** reset strings **/
    *line_end = NULL;
    *reg = NULL;
    *mem = NULL;
    *val = NULL;

    do {
        /** search for the beginning of the column **/
        for (; strchr("\t. ", *pointer) != NULL && pointer[0] != '\0';
             pointer++)
            ;

        /** skip comments **/
        if (strchr("#;", *pointer) != NULL) {
            for (;
                 pointer[0] != '\n' && pointer[0] != '\0' && pointer[0] != EOF;
                 pointer++)
                ;
            break;
        }

        /** end of line **/
        if ((pointer[0] == '\n' && pointer[1] == '\0') || pointer[0] == '\0') {
            break;
        }

        /** partial end of line **/
        if (pointer[0] == '\n' || pointer[0] == ',') {
            pointer[0] = '\0';
            *line_end = ++pointer;
            break;
        }

        /** insert columun **/
        switch (++columns) {
        case 1:
            *reg = pointer;
            break;

        case 2:
            *mem = pointer;
            break;

        case 3:
            *val = pointer;
            break;
        }

        /** skip literal char **/
        if (pointer[0] == '\'') {
            do {
                pointer++;
                if (pointer[0] == '\\') {
                    pointer++;
                }
            } while (pointer[0] != '\'' && pointer[0] != '\0');
        }

        /** skip other literals **/
        for (; strchr("\t,. ", *pointer) == NULL && pointer[0] != '\0';
             pointer++)
            ;

        /** mark end of column **/
        if (pointer[0] != '\0' && pointer[0] != ',') {
            pointer[0] = '\0';
            pointer++;
        }
    } while (pointer[0] != '\0');

    /** validate number of columns **/
    return columns == 3 || columns == 0;
}
#endif
#endif
