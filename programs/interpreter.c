/**
 * @file interpreter.c
 * @brief Program example for a 3bc syntax interpreter
 * using a single virtual machine.
 */

#include "pre/pre_sizes.h"
#include "lang/lang_3bc_cli.h"
#include "lang/lang_3bc_compile.h"
#include "driver/driver_stack.h"
#include "driver/driver_interrupt.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    int exitcode = -1;
    static tbc_u8_t stack[255];
    static tbc_u8_t vm[TBC_MACHINE_SIZE];

    driver_stack_init(vm, stack, sizeof(stack));
    lang_3bc_cli_init(vm, argc, argv);

    while (exitcode == -1) {
        lang_3bc_compile(vm);
        exitcode = driver_interrupt(vm);
    }

    return exitcode;
}
