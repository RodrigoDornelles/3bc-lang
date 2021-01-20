#include "3bc.h"

mem_t* addresses_list;
mem_t address_last;

void tape_sort_init()
{
    addresses_list = NULL;
    address_last = 0;
}

void tape_sort_destroy()
{
    if (addresses_list != NULL) {
        free(addresses_list);
        addresses_list = NILL;
    }
}

void tape_sort_insert(mem_t addres)
{
    mem_t* new_tape;
    mem_t index;

    /** prevent repeat address sort **/
    if (addresses_list != NULL) {
        mem_t i;
        for(i = 0; i < address_last; i += 1) if (addresses_list[i] == addres) {
            return;
        }
    }

    /** expand list of addresses **/
    new_tape = (mem_t*) realloc(addresses_list, sizeof (mem_t*) * (address_last += 1));

    /** was not possible expand sort tape **/
    if (new_tape == NULL) {
        lang_driver_error(ERROR_TAPE_SORT);
        return;
    }

    /** insert address **/
    index = address_last - 1;
    addresses_list = new_tape;
    addresses_list[index] = addres;

    /** sort address **/
    while (index >= 1) {
        /** get values **/  
        mem_t prev_addres = addresses_list[index - 1];
        val_t prev_value = tape_memory_get(prev_addres);
        mem_t addres = addresses_list[index];
        val_t value = tape_memory_get(addres);
        
        /** finished order **/
        if (value >= prev_value) {
            break;
        }

        /** spin values **/
        tape_memory_set(prev_addres, value);
        tape_memory_set(addres, prev_value);

        /** next number **/
        index -= 1;
    }
}