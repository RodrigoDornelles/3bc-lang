#define _3BC_SCU_FIX_2
#define _3BC_SCU_FIX
#include "3bc.h"

void driver_program_error(struct app_3bc_s *const app, enum error_3bc_e error_code)
{
    /**
     * NOTE: if the current line does not exist,
     * it was because it was interpreting a line which failed.
     */
    line_3bc_t error_line
        = app->program.curr != NULL && error_code >= ERROR_CPU_ZERO
        ? app->program.curr->line
        : app->program.last_line;

#ifdef _3BC_COMPACT
    /** smaller log erros for economy rom memory **/
    char error_code_string[64];
    snprintf(error_code_string, sizeof(error_code_string),
        "\n\n[3BC] %3d Fatal error 0x%06X in line: %6d\n", app->id, error_code,
        error_line);
    driver_tty_output_raw(app, app->tty_error, error_code_string);
#else
    char error_code_string[128];
    snprintf(error_code_string, sizeof(error_code_string),
        "\n[3BC] CRITICAL ERROR ABORTED THE PROGRAM\n> MACHINE ID:\t%08d\n> "
        "ERROR LINE:\t%08d\n> ERROR CODE:\t0x%06X\n> DESCRIPTION: ",
        app->id, error_line, error_code);
    driver_tty_output_raw(app, app->tty_error, error_code_string);

    switch ((long)(error_code)) {
#if defined(SIGSEGV)
        ERROR_LOG_3BC(SIGSEGV, "SEGMENT FAULT");
#endif
        ERROR_LOG_3BC(ERROR_CPU_ZERO, "CPU MODE IS NOT DEFINED");
        ERROR_LOG_3BC(ERROR_CPU_RESERVED, "CPU MODE IS RESERVED");
        ERROR_LOG_3BC(ERROR_INVALID_REGISTER, "INVALID CPU REGISTER");
        ERROR_LOG_3BC(ERROR_INVALID_ADDRESS, "INVALID ADDRESS");
        ERROR_LOG_3BC(ERROR_INVALID_CONSTANT, "INVALID CONSTANT");
        ERROR_LOG_3BC(ERROR_INVALID_CPU_MODE, "INVALID CPU MODE");
        ERROR_LOG_3BC(ERROR_INVALID_LABEL, "INVALID LABEL");
        ERROR_LOG_3BC(ERROR_INVALID_RETURN, "INVALID PROCEDURE RETURN");
        ERROR_LOG_3BC(
            ERROR_PARAM_DUALITY, "DUALITY ADDRES WITH VALUE IS NOT ALLOWED");
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
        ERROR_LOG_3BC(ERROR_NUMBER_ZERO, "NUMBER ZERO IS NOT EXPECTED");
        ERROR_LOG_3BC(ERROR_OUT_OF_MEMORY, "OUT OF MEMORY");
        ERROR_LOG_3BC(ERROR_NONE_TTY, "NONE TTY");
        ERROR_LOG_3BC(ERROR_UNSUPPORTED, "UNSUPPORTED FEATURE");
        ERROR_LOG_3BC(ERROR_MEMORY_CONFIG, "MEMORY CONFIG");
        ERROR_LOG_3BC(ERROR_OPEN_FILE, "CANNOT OPEN FILE");
        ERROR_LOG_3BC(ERROR_NULL_POINTER, "NULL POINTER");
        ERROR_LOG_3BC(ERROR_CHAR_SCAPE, "INVALID CHARACTER ESCAPE");
        ERROR_LOG_3BC(ERROR_CHAR_SIZE, "INVALID CHARACTER SIZE");
        ERROR_LOG_3BC(ERROR_COLUMNS, "WRONG NUMBER OF COLUMNS");
    default:
        driver_tty_output_raw(app, app->tty_error, "UNKNOWN ERROR");
    }

    driver_tty_output_raw(app, app->tty_error, "\n");
#endif

    /** TODO: no closign when else **/
    if (error_code >= ERROR_CPU_ZERO) {
        driver_power_signal(SIGTERM);
    }
}

/**
 * run processor instructions,
 * this is a core of virtual machine
 */
void driver_program_tick(struct app_3bc_s *const app)
{
    instruction_3bc(app, app->program.curr->column.reg,
        app->program.curr->column.adr, app->program.curr->column.dta);

    /** go next line **/
    app->program.curr = app->program.curr->next;
}