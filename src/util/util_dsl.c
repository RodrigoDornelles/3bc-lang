#include <stdbool.h>
#include "util_dsl.h"
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
tbc_i8_t util_dsl_split(char** dest, tbc_u8_t* destn, char* src, tbc_u8_t dn, tbc_u8_t sn)
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
tbc_i8_t util_dsl_line(char **beg, char **mid, char **end, char *src, tbc_u8_t sn)
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

/**
 * @short keyword to opcode
 * @brief @par find opcode value given a list of keywords
 * @details binary search optimized for 4-letter keywords in an array
 * that contains a sorted key and a 2-byte (16bit) value.
 * @note this function is case unsensitive.
 * @note this function has operation complexity @f$O(log (n))@f$.
 * @note this function has endless optimization.
 * @todo this function has old processors optimization.
 * @param[in] src string source
 * @param[in] kl keyword list @b (array) of @c tbc_keyword_st
 * @param[in] kn keyword size @b (bytes)
 * @pre @c kl must be ordered by key
 * @pre @c kl must be lowcase keywords
 * @return index of keyword
 * @retval -1 when not found
 * @retval -2 wrong paramters
 * @retval 0..32_768 when found
 *
 */
tbc_i16_t util_dsl_keyword(const char *const src, const tbc_keyword_st *const kl, tbc_i16_t kn)
{
    tbc_i16_t res = -2;
    tbc_i16_t low = 0;
    tbc_i16_t high = (kn - 1);
    tbc_i16_t mid;
    tbc_i32_t sum;
    tbc_keyword_st my;

    do {
        if (src == NULL) {
            break;
        }
        if (kl == NULL) {
            break;    
        }
        if (kn <= 0) {
            break;
        }

        /* correct params */
        res = -1;

        /* copy reversed */
        my.key.name[0] = src[3];
        my.key.name[1] = src[2];
        my.key.name[2] = src[1];
        my.key.name[3] = src[0];

        /* force to lowercase */
        my.key.compare |= 0x20202020;

        /* binary search */
        do {
            /* find middle */
            mid = (low + high) / 2;

            /* force litle endian sub */
            sum = 0;
            sum |= kl[mid].key.name[3];
            sum |= kl[mid].key.name[2] << 8;
            sum |= kl[mid].key.name[1] << 16;
            sum |= kl[mid].key.name[0] << 24;
            sum -= *(tbc_i32_t*)&my.key.compare;

            /* found */
            if (sum == 0) {
                res = mid;
                break;
            }
            /* on left */
            if (sum > 0) {
                high = mid - 1;
            }
            /* on right */
            if (sum < 0) {
                low = mid + 1;
            }
        } while (low <= high);
    }
    while(0);
    
    return res;
}
