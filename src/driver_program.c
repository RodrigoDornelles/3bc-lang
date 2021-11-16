#define _3BC_SCU_FIX_2
#define _3BC_SCU_FIX
#include "3bc.h"

void driver_program_error(enum error_3bc_e error_code)
{
    /**
     * NOTE: if the current line does not exist,
     * it was because it was interpreting a line which failed.
     */
    line_3bc_t error_line = APP_3BC->program.curr != NULL && error_code >= ERROR_CPU_ZERO?
        APP_3BC->program.curr->line:
        APP_3BC->program.last_line;

    #ifdef _3BC_COMPACT
    /** smaller log erros for economy rom memory **/
    char error_code_string[48];
    snprintf(error_code_string, sizeof(error_code_string), "\n\n[3BC] Fatal error 0x%06X in line: %d\n", error_code, error_line);
    driver_tty_output_raw(APP_3BC->tty_error, error_code_string);
    #else
    char error_code_string[128];
    snprintf(error_code_string, sizeof(error_code_string), "\n[3BC] CRITICAL ERROR ABORTED THE PROGRAM\n> ERROR LINE: %06d\n> ERROR CODE: 0x%06X\n> ERROR DESCRIPTION: ", error_line, error_code);
    driver_tty_output_raw(APP_3BC->tty_error, error_code_string);

    switch((long) (error_code))
    {
        ERROR_LOG_3BC(SIGSEGV, "SEGMENT FAULT");
        ERROR_LOG_3BC(ERROR_CPU_ZERO, "CPU MODE IS NOT DEFINED"); 
        ERROR_LOG_3BC(ERROR_CPU_RESERVED, "CPU MODE IS RESERVED");
        ERROR_LOG_3BC(ERROR_INVALID_REGISTER, "INVALID CPU REGISTER");
        ERROR_LOG_3BC(ERROR_INVALID_ADDRESS, "INVALID ADDRESS");
        ERROR_LOG_3BC(ERROR_INVALID_CONSTANT, "INVALID CONSTANT");
        ERROR_LOG_3BC(ERROR_INVALID_CPU_MODE, "INVALID CPU MODE");
        ERROR_LOG_3BC(ERROR_INVALID_LABEL, "INVALID LABEL");
        ERROR_LOG_3BC(ERROR_PARAM_DUALITY, "DUALITY ADDRES WITH VALUE IS NOT ALLOWED");
        ERROR_LOG_3BC(ERROR_PARAM_REQUIRE_ANY, "VALUE OR ADDRESS IS REQUIRED");
        ERROR_LOG_3BC(ERROR_PARAM_REQUIRE_VALUE, "VALUE IS REQUIRED");
        ERROR_LOG_3BC(ERROR_PARAM_REQUIRE_ADDRESS, "ADDRESS IS REQUIRED");
        ERROR_LOG_3BC(ERROR_PARAM_BLOCKED_VALUE, "VALUE IS NOT ALLOWED");
        ERROR_LOG_3BC(ERROR_PARAM_BLOCKED_ADDRESS, "ADDRESS IS NOT ALLOWED");
        ERROR_LOG_3BC(ERROR_NUMBER_NO_DIGITS, "NUMBER WHIOUT DIGITS");
        ERROR_LOG_3BC(ERROR_NUMBER_UNDERFLOW, "NUMBER UNDERFLOW");
        ERROR_LOG_3BC(ERROR_NUMBER_OVERFLOW, "NUMBER OVERFLOW");
        ERROR_LOG_3BC(ERROR_NUMBER_WRONG_BASE, "NUMBER WRONG BASE");
        ERROR_LOG_3BC(ERROR_NUMBER_NEGATIVE, "NUMBER NEGATIVE IS NOT EXPECTED");
        ERROR_LOG_3BC(ERROR_INVALID_RETURN, "INVALID PROCEDURE RETURN");
        ERROR_LOG_3BC(ERROR_DIVISION_BY_ZERO, "DIVISION BY ZERO");
        ERROR_LOG_3BC(ERROR_OUT_OF_MEMORY, "OUT OF MEMORY");
        ERROR_LOG_3BC(ERROR_NONE_TTY, "NONE TTY");
        ERROR_LOG_3BC(ERROR_UNSUPPORTED, "UNSUPPORTED FEATURE");
        ERROR_LOG_3BC(ERROR_INVALID_MEMORY_CONFIG, "INVALID MEMORY TYPE CONFIG");
        ERROR_LOG_3BC(ERROR_INVALID_MEMORY_CLAMP, "INVALID MEMORY TYPE CLAMP");
        ERROR_LOG_3BC(ERROR_VOID_HELPER_MAX_MIN, "MAX/MIN CANNOT BE EMPTY");
        ERROR_LOG_3BC(ERROR_OPEN_FILE, "CANNOT OPEN FILE");
        ERROR_LOG_3BC(ERROR_NULL_POINTER, "NULL POINTER");
        ERROR_LOG_3BC(ERROR_CHAR_SCAPE, "INVALID CHARACTER ESCAPE");
        ERROR_LOG_3BC(ERROR_CHAR_SIZE, "INVALID CHARACTER SIZE");
        ERROR_LOG_3BC(ERROR_COLUMNS, "WRONG NUMBER OF COLUMNS");
        default: driver_tty_output_raw(APP_3BC->tty_error, "UNKNOWN ERROR");
    }

    driver_tty_output_raw(APP_3BC->tty_error, "\n");
    #endif

    #if defined(_3BC_COMPUTER) || defined(_3BC_PC_1970)
    driver_power_exit(error_code >= ERROR_CPU_ZERO? SIGTERM: error_code);
    #elif defined(_3BC_ARDUINO)
    driver_power_exit();
    #endif
}

/**
 * run processor instructions,
 * this is a core of virtual machine
 */
void driver_program_tick(app_3bc_t app)
{
    instruction_3bc(
        app,
        app->program.curr->column.reg,
        app->program.curr->column.adr,
        app->program.curr->column.dta
    );

    /** go next line **/
    app->program.curr = app->program.curr->next;
}