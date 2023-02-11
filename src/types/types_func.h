#ifndef H_TYPES_FUNC_TBC
#define H_TYPES_FUNC_TBC

#include "types_primitive.h"
#include <stdbool.h>

typedef union ___tbc_func_u tbc_func_ft;

union ___tbc_func_u {
    /** any pointer **/
    void* ptr;
    /** void func(char*) **/
    void (*func_pstr_rv)(char*);
    /** bool func(uint8_t, uint8_t, uint8_t) **/
    bool (*func_p8u_p8u_p8u_rb)(tbc_u8_t, tbc_u8_t, tbc_u8_t);
};

#endif
