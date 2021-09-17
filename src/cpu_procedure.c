#include "3bc.h"

void cpu_procedure_tail(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS   
    APP_3BC->program.curr = ds_procedure_lifo_burst(value);
}

void cpu_procedure_stop(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    APP_3BC->program.curr = ds_procedure_lifo_pop();
}

void cpu_procedure_call(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    ds_procedure_lifo_push(APP_3BC->program.curr, value);
    APP_3BC->program.label_target = value;
}
