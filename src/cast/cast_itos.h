#ifndef H_CAST_ITOS_TBC
#define H_CAST_ITOS_TBC

#include "3bc_types.h"

tbc_u8_t cast_itos16(char* dest, void *src, tbc_u8_t dn, const tbc_u8_t sc);
tbc_u8_t cast_itos10(char* dest, void *src, tbc_u8_t dn, const tbc_u8_t sc);
tbc_u8_t cast_itos8(char* dest, void *src, tbc_u8_t dn, const tbc_u8_t sc);
tbc_u8_t cast_itos2(char* dest, void *src, tbc_u8_t dn, const tbc_u8_t sc);

#endif
