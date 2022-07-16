#define TBC_SOURCE_ENTRY
#include "3bc.h"

void cpu_null(PARAMS_DEFINE) { }

void cpu_mode(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    driver_mode_set(app, value);
}

void cpu_not_mode(PARAMS_DEFINE)
{
    driver_program_error(app, ERROR_CPU_ZERO);
}

void cpu_not_exist(PARAMS_DEFINE)
{
    driver_program_error(app, ERROR_INVALID_REGISTER);
}

void cpu_mode_reserved(PARAMS_DEFINE)
{
    driver_custom_call(app, reg, address, value);
}