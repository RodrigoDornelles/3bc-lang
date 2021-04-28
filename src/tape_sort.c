#include "3bc.h"

address_3bc_t* addresses_list;
address_3bc_t address_last;

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

void tape_sort_insert(address_3bc_t addres)
{
    address_3bc_t* new_tape;
    address_3bc_t index;

    /** prevent repeat address sort **/
    if (addresses_list != NULL) {
        address_3bc_t i;
        for(i = 0; i < address_last; i += 1) if (addresses_list[i] == addres) {
            return;
        }
    }

    /** expand list of addresses **/
    new_tape = (address_3bc_t*) realloc(addresses_list, sizeof (address_3bc_t*) * (address_last += 1));

    /** was not possible expand sort tape **/
    if (new_tape == NULL) {
        lang_driver_error(ERROR_TAPE_SORT);
    }

    /** insert address **/
    index = address_last - 1;
    addresses_list = new_tape;
    addresses_list[index] = addres;

    /** sort address **/
    while (index >= 1) {
        /** get values **/  
        address_3bc_t prev_addres = addresses_list[index - 1];
        data_3bc_t prev_value = tape_memory_data_get(prev_addres);
        address_3bc_t addres = addresses_list[index];
        data_3bc_t value = tape_memory_data_get(addres);
        
        /** finished order **/
        if (value >= prev_value) {
            break;
        }

        /** spin values **/
        tape_memory_data_set(prev_addres, value);
        tape_memory_data_set(addres, prev_value);

        /** next number **/
        index -= 1;
    }
}