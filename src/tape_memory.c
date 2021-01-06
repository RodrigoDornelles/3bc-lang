#include "3bc.h"
#define _MEM3BC(obj)               ((*memory_pointers[addres].p).obj)
#define _VALCONFIG(value, conf)    ((value&(conf))==(conf))
#define _MEMCONFIG(conf)           ((((*memory_pointers[addres].p).configuration)&(conf)) == (conf))

struct memory_s {
    val_t value;
    val_t v_min;
    val_t v_max;
    conf_t configuration;
};

struct pointer_s {
    struct memory_s* p;
    bool allocated;
};

static compass_t memory_end;
struct pointer_s* memory_pointers;
struct memory_s* memory_tape;

/**
 * set memory address type configurations
 */
void tape_memory_type_set(mem_t addres, val_t value)
{
    tape_memory_resize(addres);
    tape_memory_safe(addres);

    /** not allow normalize whitout clamp (limit max & min) **/
    if (value & MEM_CONFIG_NORMALIZE &&  !_VALCONFIG(value, MEM_CONFIG_MIN_VALUE | MEM_CONFIG_MAX_VALUE)) {
        lang_driver_error(ERROR_INVALID_MEMORY_CONFIG);
        return;
    }
    
    /** verifiy valid value between max & min **/
    if (_MEM3BC(v_min) > _MEM3BC(v_max) && _VALCONFIG(value, MEM_CONFIG_MIN_VALUE | MEM_CONFIG_MAX_VALUE)) {
        lang_driver_error(ERROR_INVALID_MEMORY_CLAMP);
        return;
    }

    /** update memory address type **/
    _MEM3BC(configuration) = value;

    /** force the memory address value correctly **/
    tape_memory_set(addres, tape_memory_get(addres));
}

/**
 * set memory address range value minimal
 */
void tape_memory_value_min(mem_t addres, val_t value)
{
    tape_memory_resize(addres);
    tape_memory_safe(addres);

    /** set min range memory address value **/
    _MEM3BC(v_min) = value;
    
    /** automatically changes the type to have a high pass filter **/
    tape_memory_type_set(addres, _MEM3BC(configuration) | MEM_CONFIG_MIN_VALUE);

    /** forces the memory address value between limits **/
    tape_memory_set(addres, tape_memory_get(addres));
}

/**
 * set memory address range value maximum
 */
void tape_memory_value_max(mem_t addres, val_t value)
{
    tape_memory_resize(addres);
    tape_memory_safe(addres);

    /** set max range memory address value **/
    _MEM3BC(v_max) = value;

    /** automatically changes the type to have a low pass filter **/
    tape_memory_type_set(addres, _MEM3BC(configuration) | MEM_CONFIG_MAX_VALUE);

    /** forces the memory address value between limits **/
    tape_memory_set(addres, tape_memory_get(addres));
}

/**
 * returns memory address alocated value
 */
val_t tape_memory_get(mem_t addres) 
{
    tape_memory_resize(addres);
    tape_memory_safe(addres);
    return (val_t) _MEM3BC(value);
}

/**
 * update memory address value definied
 */
void tape_memory_set(mem_t addres, val_t value)
{
    tape_memory_resize(addres);
    tape_memory_safe(addres);

    /** maximum without normalize **/
    if(value > _MEM3BC(v_max) && _MEMCONFIG(MEM_CONFIG_MAX_VALUE) && !_MEMCONFIG(MEM_CONFIG_NORMALIZE)) {
        value = _MEM3BC(v_max);
    }
    /** minimum without normalize **/
    else if (value < _MEM3BC(v_min) && _MEMCONFIG(MEM_CONFIG_MIN_VALUE) && !_MEMCONFIG(MEM_CONFIG_NORMALIZE)) {
        value = _MEM3BC(v_min);
    }
    /** normalize value **/
    else if ((_MEM3BC(v_min) > value || value > _MEM3BC(v_max)) && _MEMCONFIG(MEM_CONFIG_NORMALIZE)) {
        value = ((value - _MEM3BC(v_min)) % (_MEM3BC(v_max) - _MEM3BC(v_min))) + _MEM3BC(v_min);
    }

    _MEM3BC(value) = value;
}

/**
 * expand the size of existing memory within the virtual machine,
 * abstraction of what would increase the size of the address tape
 */
void tape_memory_resize(mem_t addres)
{
    if (addres < memory_end) {
        return;
    }

    void* new_tape = realloc(memory_pointers, sizeof (struct pointer_s) * (memory_end = addres + 1));

    /** was not possible expand memory tape **/
    if (new_tape == NULL) {
        lang_driver_error(ERROR_TAPE_MEMORY);
        return;
    }

    memory_pointers = new_tape;
}

/**
 * free memory in the address
 */
void tape_memory_free(mem_t addres)
{
    free(memory_pointers[addres].p);
    memory_pointers[addres].allocated = false;
}

/**
 * free all memory allocated by the program during execution
 */
void tape_memory_destroy()
{
    compass_t i, j;
    tape_memory_resize(0);
    for(i = 0, j = memory_end - 1; i < j; i++, tape_memory_free(i));
    free(memory_pointers);
}

/**
 * prevents that memory is not physically allocated,
 * make sure there is always a blank if it is first called
 */
void tape_memory_safe(mem_t addres)
{
    if (memory_pointers[addres].allocated == false) {
        /** alloc physically **/
        memory_pointers[addres].p = malloc(sizeof (struct memory_s));
        memory_pointers[addres].allocated = true;

        /** initial memory configurations **/
        _MEM3BC(configuration) = 0;
        _MEM3BC(v_min) = 0;
        _MEM3BC(v_max) = 0;
        _MEM3BC(value) = 0;
    }
}