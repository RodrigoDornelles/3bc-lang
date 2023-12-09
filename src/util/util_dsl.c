/**
 * @file util_dsl.c
 *
 * @brief Domain-Specific Language (DSL) Utility
 *
 * @author Rodrigo Dornelles
 *
 * @details
 * This file provides a utility for creating simple language lexers without
 * precedence tracking.
 *
 * @copyright
 * It is distributed under the GNU Affero General Public
 * License (AGPL) version 3 or any later version. For more details, please
 * refer to https://www.gnu.org/licenses/
 */

#include <stdbool.h>
#include "util_dsl.h"
#include "detect/detect_cpu.h"
#include "types/types_null.h"

/**
 * @brief extract tokens fom string
 * @details Just like a @c split in  @b JS and @b Python or 
 * @c explode in @c PHP, this function separates the string text
 * according to the space between keywords giving a maximum number of tokens.
 * @param[out] dest array of tokens
 * @param[out] destn array of token sizes
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
 * @brief extract line from string
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
 * @short keyword index from string
 * @brief find opcode value given a list of keywords
 * @details binary search optimized for 4-letter keywords in string.
 * @note this function is case unsensitive.
 * @note this function has operation complexity @f$O(log (n))@f$.
 * @note this function has endless optimization.
 * @note this function has old processors optimization.
 * @param[in] src string source
 * @param[in] keys keyword list @b (char*)
 * @param[in] kn keyword list size @b (bytes)
 * @pre @c keys must be ordered
 * @pre @c keys must be lowcase
 * @pre @c kn must be @c keys*4 also size of string.
 * @return index of keyword
 * @retval -1 when not found
 * @retval -2 wrong paramters
 * @retval 0..16_383 when found
 *
 */
tbc_i16_t util_dsl_keyword(const char *const src, const char *const keys, tbc_u16_t kn)
{
    tbc_i16_t res = -2;
    tbc_i16_t low = 0;
    tbc_i16_t high = ((kn - 1) >> 2);
    tbc_i16_t mid;
    tbc_i32_t sum;
    tbc_keyword_ut key;

    do {
        if (src == NULL) {
            break;
        }
        if (keys == NULL) {
            break;    
        }
        if (kn <= 0) {
            break;
        }

        /* correct params */
        res = -1;

#if defined(TBC_CPU_BYTE_SEXBE)
        /* copy normal */
        key.name[0] = src[0];
        key.name[1] = src[1];
        key.name[2] = src[2];
        key.name[3] = src[3];
#elif defined(TBC_CPU_BYTE_SEXLE)
        /* copy reversed */
        key.name[0] = src[3];
        key.name[1] = src[2];
        key.name[2] = src[1];
        key.name[3] = src[0];
#else
#error "[3BC] CPU sex not found."
#endif
        /* force to lowercase */
        key.compare |= 0x20202020;

        /* binary search */
        do {
            /* find middle (overflow protected) */
            mid = (low+high) >> 1;

#if defined(TBC_CPU_BYTE_SEXBE)
            /* native cpu sub */
            sum = ((tbc_keyword_ut*)keys)[mid].compare - key.compare;
#else
            /* force big endian sub */
            sum = 0;
            sum |= ((tbc_keyword_ut*)keys)[mid].name[3];
            sum |= ((tbc_keyword_ut*)keys)[mid].name[2] << 8;
            sum |= ((tbc_keyword_ut*)keys)[mid].name[1] << 16;
            sum |= ((tbc_keyword_ut*)keys)[mid].name[0] << 24;
            sum -= key.compare;
#endif

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
