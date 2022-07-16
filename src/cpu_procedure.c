#define TBC_SOURCE_ENTRY
#include "3bc.h"

void cpu_procedure_call(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    ds_procedure_lifo_push(app);
    app->program.label_target = value;
}

void cpu_procedure_back(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    app->program.curr = ds_procedure_lifo_pop(app);
    driver_mode_set(app, MODE_PROCEDURE);
}

void cpu_procedure_fcal(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if (AUX != 0) {
        ds_procedure_lifo_push(app);
        app->program.label_target = value;
    }
}

void cpu_procedure_zcal(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if (AUX == 0) {
        ds_procedure_lifo_push(app);
        app->program.label_target = value;
    }
}

void cpu_procedure_pcal(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if (AUX > 0) {
        ds_procedure_lifo_push(app);
        app->program.label_target = value;
    }
}

void cpu_procedure_ncal(PARAMS_DEFINE)
{
    REQUIRED_VALUE
    VALIDATE_NOT_ADRESS
    if (AUX < 0) {
        ds_procedure_lifo_push(app);
        app->program.label_target = value;
    }
}

void cpu_procedure_fret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    if (AUX != 0) {
        app->program.curr = ds_procedure_lifo_pop(app);
        driver_mode_set(app, MODE_PROCEDURE);
    }
}

void cpu_procedure_zret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    if (AUX == 0) {
        app->program.curr = ds_procedure_lifo_pop(app);
        driver_mode_set(app, MODE_PROCEDURE);
    }
}

void cpu_procedure_pret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    if (AUX > 0) {
        app->program.curr = ds_procedure_lifo_pop(app);
        driver_mode_set(app, MODE_PROCEDURE);
    }
}

void cpu_procedure_nret(PARAMS_DEFINE)
{
    VALIDATE_NOT_VALUES
    VALIDATE_NOT_ADRESS
    if (AUX < 0) {
        app->program.curr = ds_procedure_lifo_pop(app);
        driver_mode_set(app, MODE_PROCEDURE);
    }
}
