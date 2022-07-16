#define TBC_SOURCE_ENTRY
#include "3bc.h"

void ds_procedure_lifo_push(struct app_3bc_s* const app)
{
    struct procedure_3bc_s* procedure
        = (struct procedure_3bc_s*)malloc(sizeof(struct procedure_3bc_s));

    if (procedure == NULL) {
        driver_program_error(app, ERROR_OUT_OF_MEMORY);
    }

    procedure->prev = app->program.stack;
    procedure->remember = app->program.curr;

    app->program.stack = procedure;
}

struct line_node_s* ds_procedure_lifo_pop(struct app_3bc_s* const app)
{
    struct line_node_s* line_node;
    struct procedure_3bc_s* procedure;

    if (app->program.stack == NULL) {
        driver_program_error(app, ERROR_INVALID_RETURN);
    }

    procedure = app->program.stack->prev;
    line_node = app->program.stack->remember;
    free(app->program.stack);

    app->program.stack = procedure;

    return line_node;
}
