#include <stdbool.h>
#include "util_asm.h"
#include "types/types_null.h"

/**
 * @short parameter divider
 * @details Just like a @c split in  @b JS and @b Python or 
 * @c `explode` in @c PHP, this function separates the string text
 * according to the space between keywords giving a maximum number of tokens.
 * @param[in] dest array of pointers
 * @param[in] src string
 * @param[in] dn number of pointers
 * @param[in] sn lenght of string
 * @pre @c dest can not be @c constant
 * @return number of tokens founded
 * @retval 0 when not found tokens
 * @retval -1 when exced number of tokens
 * @retval -2 wrong paramters
 * @retval -3 when expected closing quote
 * @retval 1..127 tokens count
 */
tbc_i8_t util_asm_split(char** dest, char* src, tbc_u8_t dn, tbc_u8_t sn)
{
    tbc_u8_t ret = -2;
    char* token = NULL;
    bool in_quotes = false;

    do {
        if (dest == NULL) {
            break;
        }
        if (src == NULL) {
            break;
        }
        if (dn == 0) {
            break;
        }
        if (sn == 0) {
            break;
        }

        ret = 0;

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
    }
    while(0);

    if (in_quotes) {
        ret = -3;
    }

    return ret;
}


tbc_i8_t util_asm_line(char** dest, char* src, tbc_u8_t dn, tbc_u8_t sn, char** end)
{

}
