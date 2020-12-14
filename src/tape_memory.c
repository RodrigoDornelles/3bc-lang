#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct memory_s {
    val_t value;
    val_t v_min;
    val_t v_max;
    bool reversable;
};

struct pointer_s {
    struct memory_s* p;
    bool alocated;
};

static compass_t memory_end;
struct pointer_s* memory_pointers;
struct memory_s* memory_tape;

val_t tape_memory_get(mem_t addres) 
{
    tape_memory_resize(addres);
    if (memory_pointers[addres].alocated == false) {
        tape_memory_set(addres, 0);
    }

    return (val_t) (*memory_pointers[addres].p).value;
}

void tape_memory_set(mem_t addres, val_t value)
{
    tape_memory_resize(addres);
    if (memory_pointers[addres].alocated == false) {
        memory_pointers[addres].p = malloc(sizeof (struct memory_s));
        memory_pointers[addres].alocated = true;
    }

    (*memory_pointers[addres].p).value = value;
}

void tape_memory_resize(mem_t addres)
{
    if (addres >= memory_end) {
        compass_t memory_clean = memory_end;
        memory_end = addres + 1;
        memory_pointers = realloc(memory_pointers, sizeof (struct pointer_s) * (memory_end));
    }
}

/**
 * @todo free memory
 */
void tape_memory_free(mem_t addres)
{
    free(memory_pointers[addres].p);
    memory_pointers[addres].alocated = false;
}

void tape_memory_destroy()
{
    for(compass_t addres = 0; addres < memory_end; addres++, tape_memory_free(addres));
    free(memory_pointers);
}