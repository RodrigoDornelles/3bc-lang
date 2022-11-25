#ifndef H_NAMEBALE_TYPES_TBC
#define H_NAMETABLE_TYPES_TBC

#include "func.h"

struct ___tbc_program_s {
    tbc_func_ft load;
    tbc_func_ft next;
    tbc_func_ft insert;
    tbc_func_ft cleanup;
}

#endif
