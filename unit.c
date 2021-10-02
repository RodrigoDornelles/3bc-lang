#define _3BC_ENABLE_CUSTOM
#include "src/3bc.h"

void cpu_test_signal(PARAMS_DEFINE)
{
    driver_power_signal(value);
}

int main(int argc, char **argv)
{
    lang_init(argc, argv);

    lang_fpga(MODE_CUSTOM_1, 1, &cpu_test_signal);
    lang_run();
    lang_exit(0);
}
