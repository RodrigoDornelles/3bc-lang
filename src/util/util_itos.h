#ifndef H_util_itos_TBC
#define H_util_itos_TBC

#include "types_primitive.h"
#include "types_null.h"

tbc_u8_t util_itos16(char* dest, void *src, tbc_u8_t dn, const tbc_u8_t sc);
tbc_u8_t util_itos10(char* dest, void *src, tbc_u8_t dn, const tbc_u8_t sc);
tbc_u8_t util_itos8(char* dest, void *src, tbc_u8_t dn, const tbc_u8_t sc);
tbc_u8_t util_itos2(char* dest, void *src, tbc_u8_t dn, const tbc_u8_t sc);

#endif
