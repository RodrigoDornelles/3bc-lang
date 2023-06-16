#ifndef H_util_stoi_TBC
#define H_util_stoi_TBC

#include "types_errors.h"
#include "types_primitive.h"

tbc_error_et util_stoi16(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn);
tbc_error_et util_stoi10(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn);
tbc_error_et util_stoi8(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn);
tbc_error_et util_stoi2(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn);

#endif
