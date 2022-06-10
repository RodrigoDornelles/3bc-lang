#define _3BC_ENABLE_CUSTOM
#include "src/3bc.h"

void print_char(char* buffer)
{
    fprintf(stdout, "%02X", *buffer);
}

void cpu_test_signal(PARAMS_DEFINE)
{
    driver_power_signal(value);
}

void cpu_test_error(PARAMS_DEFINE)
{
    driver_program_error(app, (enum error_3bc_e)value);
}

void cpu_test_none_tty(PARAMS_DEFINE)
{
    app->tty_output.type = STREAM_TYPE_NONE;
    driver_tty_output_raw(app, app->tty_output, NULL);
}

void cpu_test_unsupported(PARAMS_DEFINE)
{
    driver_program_error(app, ERROR_UNSUPPORTED);
}

void cpu_test_scape_characters(PARAMS_DEFINE)
{
    app->tty_output.type = STREAM_TYPE_FUNCTION_CALL;
    app->tty_output.io.lambda = &print_char;
}

int main(int argc, char** argv)
{
    app_3bc_t VM = lang_3bc_init(argc, argv);
    lang_3bc_custom(VM, MODE_CUSTOM_1, 1, &cpu_test_signal);
    lang_3bc_custom(VM, MODE_CUSTOM_1, 2, &cpu_test_none_tty);
    lang_3bc_custom(VM, MODE_CUSTOM_1, 3, &cpu_test_unsupported);
    lang_3bc_custom(VM, MODE_CUSTOM_1, 4, &cpu_test_scape_characters);
    lang_3bc_custom(VM, MODE_CUSTOM_1, 5, &cpu_test_error);
    while (lang_3bc_update(VM))
        ;
    return 0;
}
