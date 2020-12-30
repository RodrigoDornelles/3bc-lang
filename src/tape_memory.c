#include "3bc.h"
#define _MEM3BC(obj) ((*memory_pointers[addres].p).obj)

struct memory_s {
    val_t value;
    val_t v_min;
    val_t v_max;
    bool normalize;
};

struct pointer_s {
    struct memory_s* p;
    bool allocated;
};

static compass_t memory_end;
struct pointer_s* memory_pointers;
struct memory_s* memory_tape;

void tape_memory_reversable_toggle(mem_t addres, val_t value)
{
    _MEM3BC(normalize) = value;
}

void tape_memory_value_min(mem_t addres, val_t value)
{
    _MEM3BC(v_min) = value;
}

void tape_memory_value_max(mem_t addres, val_t value)
{
    _MEM3BC(v_max) = value;
}

val_t tape_memory_get(mem_t addres) 
{
    tape_memory_resize(addres);
    if (memory_pointers[addres].allocated == false) {
        tape_memory_set(addres, 0);
    }

    return (val_t) _MEM3BC(value);
}

void tape_memory_set(mem_t addres, val_t value)
{
    tape_memory_resize(addres);
    if (memory_pointers[addres].allocated == false) {
        memory_pointers[addres].p = malloc(sizeof (struct memory_s));
        memory_pointers[addres].allocated = true;
    }

    if(value > _MEM3BC(v_max) && !_MEM3BC(normalize) && _MEM3BC(v_max) != 0) {
        _MEM3BC(value) = _MEM3BC(v_max);
    }
    else if (value < _MEM3BC(v_min) && !_MEM3BC(normalize) && _MEM3BC(v_min) != 0) {
        _MEM3BC(value) = _MEM3BC(v_min);
    }
    else if ((_MEM3BC(v_min) > value || value > _MEM3BC(v_max)) && _MEM3BC(normalize)) {
        _MEM3BC(value) = ((value - _MEM3BC(v_min)) % (_MEM3BC(v_max) - _MEM3BC(v_min))) + _MEM3BC(v_min);
    }   
    else {
        _MEM3BC(value) = value;
    }
}

void tape_memory_resize(mem_t addres)
{
    if (addres < memory_end) {
        return;
    }

    void* new_tape = realloc(memory_pointers, sizeof (struct pointer_s) * (memory_end = addres + 1));

    if (new_tape == NULL) {
        lang_driver_error(ERROR_TAPE_MEMORY);
        return;
    }

    memory_pointers = new_tape;
}

void tape_memory_free(mem_t addres)
{
    free(memory_pointers[addres].p);
    memory_pointers[addres].allocated = false;
}

void tape_memory_destroy()
{
    tape_memory_resize(0);
    for(compass_t addres = 0; addres < (memory_end - 1); addres++, tape_memory_free(addres));
    free(memory_pointers);
}