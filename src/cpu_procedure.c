#include "3bc.h"

void cpu_procedure_call(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    ds_procedure_lifo_push(APP_3BC->program.curr, value);
    APP_3BC->program.label_target = value;
}

void cpu_procedure_back(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    APP_3BC->program.curr = ds_procedure_lifo_pop();
    tape_router_cpu_set(MODE_PROCEDURE);
}

void cpu_procedure_fcal(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    REQUIRED_VALUE
    if (AUX != 0) {
        ds_procedure_lifo_push(APP_3BC->program.curr, value);
        APP_3BC->program.label_target = value;
    }
}

void cpu_procedure_zcal(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    REQUIRED_VALUE
    if (AUX == 0) {
        ds_procedure_lifo_push(APP_3BC->program.curr, value);
        APP_3BC->program.label_target = value;
    }
}

void cpu_procedure_pcal(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    REQUIRED_VALUE
    if (AUX > 0) {
        ds_procedure_lifo_push(APP_3BC->program.curr, value);
        APP_3BC->program.label_target = value;
    }
}

void cpu_procedure_ncal(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    REQUIRED_VALUE
    if (AUX < 0) {
        ds_procedure_lifo_push(APP_3BC->program.curr, value);
        APP_3BC->program.label_target = value;
    }
}

void cpu_procedure_fret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    if (AUX != 0) {
        APP_3BC->program.curr = ds_procedure_lifo_pop();
        tape_router_cpu_set(MODE_PROCEDURE);
    }
}

void cpu_procedure_zret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    if (AUX == 0) {
        APP_3BC->program.curr = ds_procedure_lifo_pop();
        tape_router_cpu_set(MODE_PROCEDURE);
    }
}

void cpu_procedure_pret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    if (AUX > 0) {
        APP_3BC->program.curr = ds_procedure_lifo_pop();
        tape_router_cpu_set(MODE_PROCEDURE);
    }
}

void cpu_procedure_nret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    if (AUX < 0) {
        APP_3BC->program.curr = ds_procedure_lifo_pop();
        tape_router_cpu_set(MODE_PROCEDURE);
    }
}

void cpu_procedure_tco_back(PARAMS_DEFINE)
{
    VALIDATE_NOT_ADRESS
    REQUIRED_VALUE
    APP_3BC->program.curr = ds_procedure_lifo_burst(value);
    tape_router_cpu_set(MODE_PROCEDURE);
}

void cpu_procedure_tco_fret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    REQUIRED_VALUE
    if (AUX != 0) {
        APP_3BC->program.curr = ds_procedure_lifo_burst(value);
        tape_router_cpu_set(MODE_PROCEDURE);
    }
}

void cpu_procedure_tco_zret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    REQUIRED_VALUE
    if (AUX == 0) {
        APP_3BC->program.curr = ds_procedure_lifo_burst(value);
        tape_router_cpu_set(MODE_PROCEDURE);
    }
}

void cpu_procedure_tco_pret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    REQUIRED_VALUE
    if (AUX > 0) {
        APP_3BC->program.curr = ds_procedure_lifo_burst(value);
        tape_router_cpu_set(MODE_PROCEDURE);
    }
}

void cpu_procedure_tco_nret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    REQUIRED_VALUE
    if (AUX < 0) {
        APP_3BC->program.curr = ds_procedure_lifo_burst(value);
        tape_router_cpu_set(MODE_PROCEDURE);
    }
}
