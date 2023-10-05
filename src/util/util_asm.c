#include <stdbool.h>
#include "util_asm.h"
#include "types/types_null.h"

/**
 * @short parameter divider
 * @details Just like a @c split in  @b JS and @b Python or 
 * @c `explode` in @c PHP, this function separates the string text
 * according to the space between keywords giving a maximum number of tokens.
 * @param[out] dest array of tokens
 * @param[out] dest array of token sizes
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
tbc_i8_t util_asm_split(char** dest, tbc_u8_t* destn, char* src, tbc_u8_t dn, tbc_u8_t sn)
{
    tbc_u8_t ret = -2;
    tbc_u8_t size;
    char* token = NULL;
    bool in_quotes = false;

    do {
        if (dest == NULL) {
            break;
        }
        if (destn == NULL) {
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
                    *destn++ = size;
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
                    *destn++ = size;
                    *dest++ = token;
                }
                token = NULL;
            } else if (*src == '"') {
                in_quotes = !in_quotes;
                if (!in_quotes) {
                    if (token != NULL) {
                        *destn++ = ++size;
                        *dest++ = token;
                    }
                    token = NULL;
                } else {
                    token = src;
                    size = 0;
                    ++ret;
                }
            } else {
                if (token == NULL) {
                    token = src;
                    size = 0;
                    ++ret;
                }
            }
            if (token != NULL) {
                ++size;
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
 * @return instruction length
 * @retval -1 empty line
 * @retval -2 wrong paramters
 * @retval -3 when expected closing quote
 */
tbc_i8_t util_asm_line(char **beg, char **mid, char **end, char *src, tbc_u8_t sn)
{
    tbc_u8_t i = 0;
    tbc_i8_t length = -2;
    bool in_quotes = false;

    do {
        if (beg == NULL) {
            break;
        }
        if (mid == NULL) {
            break;
        }
        if (end == NULL) {
            break;
        }
        if (src == NULL) {
            break;
        }
        if (i == 0 && src[i] == '\0'){
            length = -1;
            break;
        }

        *beg = NULL;
        *mid = NULL;
        *end = NULL;
        length = 0;

        while (i < sn) {
            if (src[i] == '\0' || src[i] == '\n' || (src[i] == ',' && !in_quotes)) {
                if (src[i] == '\n' || src[i] == ',') {
                    ++i;
                }
                if (*beg != NULL || *mid != NULL) {
                    *end = &src[i];
                }
                break;
            }

            if (!in_quotes) {
                if (*mid == NULL && (src[i] == '#' || src[i] == ';')) {
                    *mid = &src[i];
                }

                if (*mid != NULL && i >= 1 && (
                    (src[i] == '#' && src[i - 1] == '#') ||
                    (src[i] == ';' && src[i - 1] == ';'))) {
                    *mid = &src[i];
                }

                if (*beg == NULL && src[i] != ' ' && src[i] != '.') {
                    *beg = &src[i];
                }
            }

            if (beg != NULL && *mid == NULL && (src[i] == '\'' ||  src[i] == '"')) {
                in_quotes = !in_quotes;
            }

            if (*beg != NULL && *mid == NULL) {
                ++length;
            }

            ++i;
        }

        if (*beg == *mid) {
            *beg = NULL;
        }

        if (*mid != NULL) {
            (*mid)++;
        }

        if (in_quotes) {
            length = -3;
        }
    }
    while(0);

    return length;
}
