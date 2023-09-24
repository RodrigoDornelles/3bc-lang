#ifndef H_UTIL_ASM_TBC
#define H_UTIL_ASM_TBC

#include "types/types_primitive.h"

tbc_i8_t util_asm_tokens(char** dest, char* src, tbc_u8_t dn, tbc_u8_t sn, char** end);
tbc_i8_t util_asm_line(char** dest, char* src, tbc_u8_t dn, tbc_u8_t sn, char** end);

#endif
