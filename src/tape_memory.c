#include "3bc.h"
#define _MEM3BC(obj)               ((*memory_pointers[addres].p).obj)
#define _VALCONFIG(value, conf)    ((value&(conf))==(conf))
#define _MEMCONFIG(conf)           ((((*memory_pointers[addres].p).configuration)&(conf)) == (conf))

struct memory_s {
    data_3bc_t value;
    data_3bc_t v_min;
    data_3bc_t v_max;
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
 * reset primitive state memory
 */
void tape_memory_init()
{
    /** prevent wild pointers **/
    memory_pointers = NULL;
    memory_tape = NULL;
    memory_end = 0;
}

/**
 * get memory address type configurations
 */
data_3bc_t tape_memory_type_get(address_3bc_t addres)
{
    tape_memory_resize(addres);
    tape_memory_safe(addres);

    return _MEM3BC(configuration);
}

/**
 * set memory address range value minimal
 */
data_3bc_t tape_memory_value_min_get(address_3bc_t addres)
{
    tape_memory_resize(addres);
    tape_memory_safe(addres);

    return _MEM3BC(v_min);
}

/**
 * set memory address range value maximum
 */
data_3bc_t tape_memory_value_max_get(address_3bc_t addres)
{
    tape_memory_resize(addres);
    tape_memory_safe(addres);

    return _MEM3BC(v_max);
}

/**
 * set memory address type configurations
 */
void tape_memory_type_set(address_3bc_t addres, data_3bc_t value)
{
    tape_memory_resize(addres);
    tape_memory_safe(addres);

    /** not allow normalize whitout clamp (limit max & min) **/
    if (value & MEM_CONFIG_NORMALIZE &&  !_VALCONFIG(value, MEM_CONFIG_MIN_VALUE | MEM_CONFIG_MAX_VALUE)) {
        lang_driver_error(ERROR_INVALID_MEMORY_CONFIG);
    }
    
    /** verifiy valid value between max & min **/
    if (_MEM3BC(v_min) > _MEM3BC(v_max) && _VALCONFIG(value, MEM_CONFIG_MIN_VALUE | MEM_CONFIG_MAX_VALUE)) {
        lang_driver_error(ERROR_INVALID_MEMORY_CLAMP);
    }

    /** update memory address type **/
    _MEM3BC(configuration) = value;

    /** force the memory address value correctly **/
    tape_memory_set(addres, tape_memory_get(addres));
}

/**
 * set memory address range value minimal
 */
void tape_memory_value_min_set(address_3bc_t addres, data_3bc_t value)
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
void tape_memory_value_max_set(address_3bc_t addres, data_3bc_t value)
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
data_3bc_t tape_memory_get(address_3bc_t addres) 
{
    tape_memory_resize(addres);
    tape_memory_safe(addres);
    return (data_3bc_t) _MEM3BC(value);
}

/**
 * update memory address value definied
 */
void tape_memory_set(address_3bc_t addres, data_3bc_t value)
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
    /** custom underflow/overflow **/
    else if ((_MEM3BC(v_min) > value || value > _MEM3BC(v_max)) && _MEMCONFIG(MEM_CONFIG_NORMALIZE)) {
        value = ((value + _MEM3BC(v_min) + 2) % (_MEM3BC(v_max) - _MEM3BC(v_min) + 1)) + _MEM3BC(v_min);
    }

    _MEM3BC(value) = value;
}

/**
 * expand the size of existing memory within the virtual machine,
 * abstraction of what would increase the size of the address tape
 */
void tape_memory_resize(address_3bc_t addres)
{
    /** verify that it is not necessary to expand memory **/
    if (addres < memory_end) {
        return;
    }

    /** expand tape memory **/
    struct pointer_s* new_tape = (struct pointer_s*) realloc(memory_pointers, sizeof (struct pointer_s) * (addres + 1));

    /** eliminate possible wild pointers **/
    for (;memory_end <= addres; new_tape[memory_end++].allocated = false);

    /** was not possible expand memory tape **/
    if (new_tape == NULL) {
        lang_driver_error(ERROR_TAPE_MEMORY);
    }

    /** take memory tape **/
    memory_pointers = new_tape;
}

/**
 * free memory in the address
 */
void tape_memory_free(address_3bc_t addres)
{
    /** prevent clean freed memory **/ 
    if (memory_pointers[addres].allocated == false) {
        return;
    }

    /** prevent data access before is no longer useful (security) **/
    tape_memory_reset(addres);   
        tape_memory_reset(addres);   
    tape_memory_reset(addres);   

    /** clean memory address **/
    free(memory_pointers[addres].p);
    memory_pointers[addres].allocated = false;
}

/**
 * free all memory allocated by the program during execution
 */
void tape_memory_destroy()
{
    compass_t i, j;
    
    /** memory was not used **/
    if (memory_end == 0) {
        return;
    }

    /** clean out all memory alocated **/
    for(i = 0, j = memory_end - 1; i < j; i++, tape_memory_free(i));
    free(memory_pointers);
}

/**
 * prevents that memory is not physically allocated,
 * make sure there is always a blank if it is first called
 */
void tape_memory_safe(address_3bc_t addres)
{
    if (memory_pointers[addres].allocated == false) {
        /** alloc physically **/
        memory_pointers[addres].p = (struct memory_s*) malloc(sizeof (struct memory_s));
        memory_pointers[addres].allocated = true;
        tape_memory_reset(addres);
    }
}

/**
 * initial memory configurations
 */
void tape_memory_reset(address_3bc_t addres)
{
    _MEM3BC(configuration) = 0;
    _MEM3BC(v_min) = 0;
    _MEM3BC(v_max) = 0;
    _MEM3BC(value) = 0;
}