#define _3BC_SCU_FIX_2
#include "3bc.h"

#if defined(_3BC_ENABLE_CUSTOM)

function_3bc_t* custom_funcs = NULL;
unsigned char last_func = 0;

void ds_fpg_array_func_set(cpumode_3bc_t cpu_mode, register_3bc_t reg, function_3bc_t lambda)
{
    unsigned char atual_func = ((cpu_mode/10) - 1) * 6 + reg;
    
    /** expand array of functions **/
    if (custom_funcs == NULL || last_func <= atual_func){
        function_3bc_t* new_array = (function_3bc_t*) realloc(custom_funcs, sizeof(function_3bc_t) * atual_func + 1);
        
        if (new_array == NULL) {
            driver_program_error(ERROR_OUT_OF_MEMORY);
        }

        /** clean wild pointers **/
        for (;last_func <= atual_func; last_func++) {
            new_array[last_func] = NULL;
        }
    
        custom_funcs = new_array;
    } 

    /** update custom function **/
    custom_funcs[atual_func] = lambda;
}

void ds_fpg_array_func_call(cpumode_3bc_t cpu_mode, register_3bc_t reg, address_3bc_t address, data_3bc_t value)
{
    unsigned char atual_func = ((cpu_mode/10) - 1) * 6 + reg;
    
    /** custom function not found **/
    if (custom_funcs == NULL || custom_funcs[atual_func] == NULL || atual_func >= last_func) {
        driver_program_error(ERROR_CPU_RESERVED);
    }
    
    custom_funcs[atual_func](reg, address, value);
}
#endif
