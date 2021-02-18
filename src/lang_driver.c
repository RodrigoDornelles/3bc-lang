#include "3bc.h"
#ifdef _3BC_ARDUINO
#include <Arduino.h>
#include <avr/pgmspace.h>
#endif

#define print_file(file,type, val);\
switch(type){\
case STRI: fprintf(file, "%lu", (unsigned long) val); break;\
case STRO: fprintf(file, "%o", (unsigned int) val); break;\
case STRC: fprintf(file, "%c", (unsigned char) val); break;\
case STRX: fprintf(file, "%x", (unsigned int) val); break;}

#define print_error(string) fprintf(stderr, "> ERROR DESCRIPTION: %s\n", string);break

#ifdef _3BC_PC_NOT_WINDOWS
struct termios term_old_attr;
struct termios term_new_attr;
#endif

file_t* program_file;

void lang_driver_run()
{
    while(tape_program_avaliable()? tape_program_exe(): lang_interpreter_line(program_file));
}

#ifdef _3BC_COMPUTER
void lang_driver_init(int argc, char **argv)
#endif
#ifdef _3BC_ARDUINO
void lang_driver_init()
#endif
{
    #ifdef _3BC_COMPUTER
    /**
     * Capture computer signals
     */
    signal(SIGINT, lang_driver_exit);
    
    if (argc <= 1) {
        program_file = stdin;
    }
    else {
        program_file = fopen(argv[argc - 1], "r");
    }
    #endif

    tape_memory_init();
    tape_program_init();

    #ifdef _3BC_PC_NOT_WINDOWS
    /**
     * Turn possible terminal uncannonical mode 
     * whiout conio.h in linux/unix builds
     */
    tcgetattr(0, &term_old_attr);
    tcgetattr(0, &term_new_attr);

    term_new_attr.c_lflag &= ~ICANON;
    term_new_attr.c_lflag &= ~ECHO;

    term_new_attr.c_cc[VTIME] = 0;
    term_new_attr.c_cc[VMIN] = 1;
    #endif

    #ifdef _3BC_ARDUINO
    arduino_serial_begin();
    #endif
}

void lang_driver_exit(int sig)
{
    #ifdef _3BC_PC_NOT_WINDOWS
    tcsetattr(STDIN_FILENO, TCSANOW, &term_old_attr);
    #endif

    #ifdef _3BC_COMPUTER
    if (program_file != stdin) {
        fclose(program_file);
    }
    #endif

    tape_memory_destroy();
    tape_program_destroy();
    tape_sort_destroy();

    #ifdef _3BC_ARDUINO
    while(1);
    #endif

    #ifdef _3BC_COMPUTER
    exit(sig);
    #endif
}

void lang_driver_output_1(reg_t type, val_t val)
{
    #ifdef _3BC_COMPUTER
    print_file(stdout, type, val);
    #endif

    #ifdef _3BC_ARDUINO
    static char output[8];
    switch (type) {
        case STRC:
            format(output, ("%c"), val);
            break;
        
        case STRX:
            format(output, ("%x"), val);
            break;

        case STRI:
            format(output, ("%d"), val);
            break;

        case STRO:
            format(output, ("%o"), val);
            break;
    }

    arduino_serial_print(1, output);
    #endif
}

void lang_driver_output_2(reg_t type, val_t val)
{
    print_file(stderr, type, val);

    #ifdef _3BC_ARDUINO
    lang_driver_output_1(type, val);
    /** @todo second serial output **/
    /** arduino_serial_print(2, type, val); **/
    #endif
}

void lang_driver_error(error_3bc_t error_code)
{
    #ifdef _3BC_ARDUINO
    /** smaller log erros for economy rom memory **/
    static char error_code_string[32];
    format(error_code_string, ("\n\n[3BC] Fatal error: %d"), error_code);
    arduino_serial_print(1, error_code_string);
    #endif

    #ifdef _3BC_COMPUTER
    fprintf(stderr, "\n[3BC] CRITICAL ERROR ABORTED THE PROGRAM");
    fprintf(stderr, "\n> ERROR LINE: %d", CLINE + 1);
    fprintf(stderr, "\n> ERROR CODE: %d\n", error_code);

    switch(error_code)
    {
        case ERROR_CPU_ZERO: print_error("CPU MODE IS NOT DEFINED"); 
        case ERROR_CPU_PROTECT: print_error("CPU MODE IS PROTECTED");
        case ERROR_CPU_RESERVED: print_error("CPU MODE IS RESERVED");
        case ERROR_INVALID_REGISTER: print_error("INVALID REGISTER");
        case ERROR_INVALID_ADDRESS: print_error("INVALID ADDRESS");
        case ERROR_INVALID_CONSTANT: print_error("INVALID CONSTANT");
        case ERROR_INVALID_CPU: print_error("INVALID CPU");
        case ERROR_INVALID_LABEL: print_error("INVALID LABEL");
        case ERROR_PARAM_DUALITY: print_error("DUALITY ADDRES WITH VALUE IS NOT ALLOWED");
        case ERROR_PARAM_REQUIRE_VALUE: print_error("VALUE IS REQUIRED");
        case ERROR_PARAM_REQUIRE_ADDRESS: print_error("ADDRESS IS REQUIRED");
        case ERROR_PARAM_BLOCKED_VALUE: print_error("VALUE IS NOT ALLOWED");
        case ERROR_PARAM_BLOCKED_ADDRESS: print_error("ADDRESS IS NOT ALLOWED");
        case ERROR_NUMBER_NO_DIGITS: print_error("NUMBER WHIOUT DIGITS");
        case ERROR_NUMBER_UNDERFLOW: print_error("NUMBER UNDERFLOW");
        case ERROR_NUMBER_OVERFLOW: print_error("NUMBER OVERFLOW");
        case ERROR_NUMBER_WRONG_BASE: print_error("NUMBER WRONG BASE");
        case ERROR_NUMBER_UNKOWN: print_error("NUMBER UNKNOWN");
        case ERROR_NUMBER_DIRTY: print_error("NUMBER DIRTY");
        case ERROR_TAPE_LABEL: print_error("FAILURE TO EXPAND THE LABEL LIST");
        case ERROR_TAPE_MEMORY: print_error("FAILURE TO EXPAND THE MEMORY");
        case ERROR_TAPE_PROGRAM: print_error("FAILURE TO EXPAND THE PROGRAM");
        case ERROR_TAPE_SORT: print_error("FAILURE TO EXPAND THE SORT");
        case ERROR_INVALID_MEMORY_CONFIG: print_error("INVALID MEMORY TYPE CONFIG");
        case ERROR_INVALID_MEMORY_CLAMP:  print_error("INVALID MEMORY TYPE CLAMP");
        case ERROR_VOID_HELPER_MAX_MIN: print_error("MAX/MIN CANNOT BE EMPTY");
        default: print_error("UNKNOWN ERROR");
    }
    #endif

    lang_driver_exit(error_code);
}

/**
 * detect keyboard input
 */
val_t lang_driver_input(reg_t type, mem_t addres)
{
    static unsigned int value;
    static char c[2] = "\0";
    static bool invalid;
    
    do {
        invalid = false;

        /** capture input **/
        #ifdef _3BC_PC_NOT_WINDOWS
        tcsetattr(STDIN_FILENO,TCSANOW, &term_new_attr);
        c[0] = getchar();
        tcsetattr(STDIN_FILENO,TCSANOW, &term_old_attr);
        #endif 

        #ifdef _3BC_PC_WINDOWS
        c[0] = getch();
        #endif

        /** validate input **/
        switch (type) {
            case STRC: 
                /** verify is a ASCII alphabet's letter/symbol **/
                invalid |= (c[0] < 0x20 || c[0] > 0x7E);
                value = c[0];
                break;

            case STRI: 
                invalid |= !sscanf(c, "%d", &value);
                break;
            
            case STRO: 
                invalid |= !sscanf(c, "%o", &value);
                break;

            case STRX:
                invalid |= !sscanf(c, "%x", &value);
                break;
        }

        /** validade input inner memory clamp limits **/
        if ((tape_memory_type_get(addres) & MEM_CONFIG_MIN_VALUE) == MEM_CONFIG_MIN_VALUE) {
            invalid |= tape_memory_value_min_get(addres) > value;
        }
        if ((tape_memory_type_get(addres) & MEM_CONFIG_MAX_VALUE) == MEM_CONFIG_MAX_VALUE) {
            invalid |= tape_memory_value_max_get(addres) < value;
        }
    
    }
    while (invalid);

    return (val_t) value;
}

/**
 * convert string in any numeric base
 */
bool lang_driver_strtol(const char* string, signed long int* value)
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
            lang_driver_error(ERROR_NUMBER_WRONG_BASE); 
    }

    if (decode == endptr){
        lang_driver_error(ERROR_NUMBER_NO_DIGITS);
    }
    else if (errno == ERANGE && *value == LONG_MIN){
        lang_driver_error(ERROR_NUMBER_UNDERFLOW);
    }
    else if (errno == ERANGE && *value == LONG_MAX){
        lang_driver_error(ERROR_NUMBER_OVERFLOW);
    }
    #ifdef EINVAL
    /** not in all c99 implementations **/
    else if (errno == EINVAL){ 
        lang_driver_error(ERROR_NUMBER_WRONG_BASE); 
    }
    #endif
    else if (errno != 0 && *value == 0){
        lang_driver_error(ERROR_NUMBER_UNKOWN);    
    }
    else if (errno == 0 && *endptr != 0){
        lang_driver_error(ERROR_NUMBER_DIRTY);    
    }

    return true;
}