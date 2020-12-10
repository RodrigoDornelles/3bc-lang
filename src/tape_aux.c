#include "header.h"

static val_t memory_aux;

val_t tape_aux_get()
{
    return memory_aux;
}

void tape_aux_set(val_t value)
{
    memory_aux = value;
}

void tape_aux_free()
{
    memory_aux = 0;
}