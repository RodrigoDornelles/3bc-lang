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

void cpu_test_none_tty(PARAMS_DEFINE)
{
    APP_3BC->tty_output.type = STREAM_TYPE_NONE;
    driver_tty_output_raw(APP_3BC->tty_output, NULL);
}

void cpu_test_unsupported(PARAMS_DEFINE)
{
    driver_program_error(ERROR_UNSUPPORTED);
}

void cpu_test_scape_characters(PARAMS_DEFINE)
{
    APP_3BC->tty_output.type = STREAM_TYPE_FUNCTION_CALL;
    APP_3BC->tty_output.io.lambda = &print_char;
}

int main(int argc, char **argv)
{
    lang_init(argc, argv);
    lang_fpga(MODE_CUSTOM_1, 1, &cpu_test_signal);
    lang_fpga(MODE_CUSTOM_1, 2, &cpu_test_none_tty);
    lang_fpga(MODE_CUSTOM_1, 3, &cpu_test_unsupported);
    lang_fpga(MODE_CUSTOM_1, 4, &cpu_test_scape_characters);
    lang_run();
    lang_exit(0);
}
