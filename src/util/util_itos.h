#ifndef H_UTIL_ITOS_TBC
#define H_UTIL_ITOS_TBC

#include "types/types_primitive.h"
#include "types/types_null.h"

tbc_u8_t util_itos16(char* dest, void *src, tbc_u8_t dn, const tbc_u8_t sc);
tbc_u8_t util_itos10(char* dest, void *src, tbc_u8_t dn, const tbc_u8_t sc);
tbc_u8_t util_itos8(char* dest, void *src, tbc_u8_t dn, const tbc_u8_t sc);
tbc_u8_t util_itos2(char* dest, void *src, tbc_u8_t dn, const tbc_u8_t sc);

#endif
