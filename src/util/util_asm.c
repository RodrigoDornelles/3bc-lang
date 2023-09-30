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

/**
 * @brief line mark
 * @details receives a text and marks the beginning of how many characters it has,
 * where the comments begin and where they end.
 * 
 * @param[out] beg begin of instruction.
 * @param[out] mid end of instruction/end of comment.
 * @param[out] end end of comment.
 * @param[in] src text instruction
 * @param[in] sn text size
 * @return instruction lenght
 */
tbc_i8_t util_asm_line(char **beg, char **mid, char **end, char *src, tbc_u8_t sn)
{
    *beg = NULL;
    *mid = NULL;
    *end = NULL;
    tbc_u8_t i = 0;
    tbc_i8_t length = 0;

    int foundContent = 0;
    int foundComment = 0;

    for (;i < sn; i++) {
        if (!foundContent && src[i] != ' ' && src[i] != '.') {
            *beg = &src[i];
            foundContent = 1;
        }

        if (src[i] == '#' || src[i] == ';') {
            foundComment = 1;
            *mid = &src[i];
        }

        if (src[i] == '\0' || src[i] == '\n' || src[i] == '\r') {
            *end = &src[i];
            break;
        }
        
        if (*beg != NULL && *mid == NULL) {
            length++;
        }
    }

    if (foundContent && foundComment) {
        *end = *mid;
        (*mid)++;
    }

    return length;
}
