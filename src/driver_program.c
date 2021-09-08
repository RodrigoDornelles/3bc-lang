#include "3bc.h"

#define print_error(string) fprintf(stderr, "> ERROR DESCRIPTION: %s\n", string);break
#define print_signal(string) fprintf(stderr, "> ERROR DESCRIPTION: %s\n", string);exit(error_code)

void driver_program_run()
{
    while(tape_program_avaliable()? tape_program_exe(): interpreter_compiler(APP_3BC->tty_source));
}

/**
 * TODO: use tty_error
 * TODO: use _3BC_COMPACT
 */
void driver_program_error(enum error_3bc_e error_code)
{
    /**
     * NOTE: if the current line does not exist,
     * it was because it was interpreting a line which failed.
     */
    line_3bc_t error_line = APP_3BC->program.curr != NULL && error_code >= ERROR_CPU_ZERO?
        APP_3BC->program.curr->line:
        APP_3BC->program.last_line;

    #ifdef _3BC_ARDUINO
    /** smaller log erros for economy rom memory **/
    char error_code_string[48];
    snprintf(error_code_string,  48, "\n\n[3BC] Fatal error 0x%06X in line: %d", error_code, error_line);
    #endif

    #ifdef _3BC_COMPUTER
    fprintf(stderr, "\n[3BC] CRITICAL ERROR ABORTED THE PROGRAM");
    fprintf(stderr, "\n> ERROR LINE: %06d", error_line);
    fprintf(stderr, "\n> ERROR CODE: 0x%06X\n", error_code);

    switch((long) (error_code))
    {
        case SIGSEGV: print_error("SEGMENT FAULT");
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
        case ERROR_OPEN_FILE: print_error("CANNOT OPEN FILE");
        case ERROR_LONG_LINE: print_error("EXCEED LINE COLUMN LIMIT");
        case ERROR_CHAR_SCAPE: print_error("INVALID CHARACTER ESCAPE");
        case ERROR_CHAR_SIZE: print_error("INVALID CHARACTER SIZE");
        case ERROR_COLUMNS: print_error("WRONG NUMBER OF COLUMNS");
        case ERROR_UNSUPPORTED: print_error("UNSUPPORTED FEATURE");
        default: print_error("UNKNOWN ERROR");
    }
    #endif

    #if defined(_3BC_COMPUTER)
    if(error_code >= ERROR_CPU_ZERO){
        driver_power_exit(SIGTERM);
    }
    driver_power_safe_exit(error_code);
    #else
    driver_power_exit();
    #endif

    #if defined(_3BC_ARDUINO)
    /** TODO: some thing? **/
    while(1);
    #endif
}