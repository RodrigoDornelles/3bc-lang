#include "util/util_keyword.h"
#include "types/types_null.h"

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
tbc_i16_t util_keyword(char *const src, tbc_keyword_st *const kl, tbc_i16_t kn)
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
