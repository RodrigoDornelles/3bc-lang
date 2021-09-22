#include "3bc.h"

void ds_procedure_lifo_push(struct line_node_s* line_node, label_3bc_t label)
{
    struct procedure_3bc_s* procedure = (struct procedure_3bc_s*) malloc(sizeof(struct procedure_3bc_s));

    if (procedure == NULL) {
        driver_program_error(ERROR_OUT_OF_MEMORY);
    }

    procedure->prev = APP_3BC->program.stack;
    procedure->remember = line_node;
    procedure->label = label;

    APP_3BC->program.stack = procedure;
}

struct line_node_s* ds_procedure_lifo_burst(label_3bc_t label)
{
    struct line_node_s* line_node;

    while (APP_3BC->program.stack == NULL || APP_3BC->program.stack->label != label) {
        line_node = ds_procedure_lifo_pop();
    }

    return line_node;
}

struct line_node_s* ds_procedure_lifo_pop()
{
    struct line_node_s* line_node;
    struct procedure_3bc_s* procedure;

    if (APP_3BC->program.stack == NULL) {
        driver_program_error(ERROR_INVALID_RETURN);
    }
    
    procedure = APP_3BC->program.stack->prev;
    line_node = APP_3BC->program.stack->remember;
    free(APP_3BC->program.stack);

    APP_3BC->program.stack = procedure;

    return line_node;
}
