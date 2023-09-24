#include "util_asm.h"
#include "types/types_null.h"

tbc_i8_t util_asm_tokens(char** dest, char *const src, tbc_u8_t dn, tbc_u8_t sn, char** end)
{
    tbc_u8_t ret = 0;
    char* token = NULL;
    bool in_quotes = false;

    while (1) {
        if (*src == '\0' || sn == 0) {
            if (token != NULL) {
                *dest++ = token;
            }
            break;
        }
        if (token != NULL && ret > dn) {
            ret = -1;
            break;
        }
        if ((*src == ' ' || *src == '.') && !in_quotes) {
            if (token != NULL) {
                *dest++ = token;
            }
            token = NULL;
        } else if (*src == '"') {
            in_quotes = !in_quotes;
            if (!in_quotes) {
                if (token != NULL) {
                    *dest++ = token;
                }
                token = NULL;
            } else {
                token = src;
                ++ret;
            }
        } else {
            if (token == NULL) {
                token = src;
                ++ret;
            }
        }
        ++src;
        --sn;
    }

    if (end != NULL) {
        *end = *src;
    }

    if (in_quotes) {
        ret = -3;
    }

    return ret;
}


tbc_u8_t util_asm_line(char** dest, char* src, tbc_u8_t dn, tbc_u8_t sn, char** end)
{

}
