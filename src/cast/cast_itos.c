#include "cast_itos.h"

/**
 * @short [0-9] to char*
 * @brief @par casting integer to string
 * @details string formater intenger numbers in base 10
 * and return number of bytes writed in buffer.
 * @note this function has <b>space complexity</b> @f$O(1)@f$
 * can be more slow in some hardwares than standard library,
 * but is minify and safety for old devices.
 * @param[out] dest string destination
 * @param[in] src integer destination
 * @param[in] dn string destination length @b (bytes)
 * @param[in] sn integer destinatin length @b (bits)
 * @pre @c dn minimum 2 @b bytes.
 * @pre @c sn must be 8, 10, 13, 16, 32 or 64 @b bits.
 * @return number of bytes writed
 * @retval 1..127 success
 * @retval 0 when invalid sizes @c dn or @c sn
 * @retval 0 when invalid buffer @c dest
 * @retval 0 when invalid source @c src
 */
tbc_u8_t cast_itos10(char* dest, void *src, tbc_u8_t dn, const tbc_u8_t sn)
{
    tbc_u8_t len = 0;
    
    do {
        /* invalid destination */
        if (dest == NULL) {
            break;
        }
        /* invalid source */
        if (src == NULL) {
            break;
        }
        /* invalid destination size */
        if (dn < 2) {
            break;
        }
        /* evaluate */
        switch (sn) {
            case 8:
            {
                tbc_u8_t src8 = *((tbc_u8_t*)src);
                do {
                    dest[len] = ('0' + (src8 % 10));
                    src8 = (src8 / 10);
                    ++len;
                }
                while (src8 && len <= (dn - 1));
                break;
            }
            case 10:
            case 13:
            case 16:
            {
                tbc_u16_t src16 = *((tbc_u16_t*)src);
                do {
                    dest[len] = ('0' + (src16 % 10));
                    src16 = (src16 / 10);
                    ++len;
                }
                while (src16 && len <= (dn - 1));
                break;
            }
            case 32:
            {
                tbc_u32_t src32 = *((tbc_u32_t*)src);
                do {
                    dest[len] = ('0' + (src32 % 10));
                    src32 = (src32 / 10);
                    ++len;
                }
                while (src32 && len <= (dn - 1));
                break;
            }
            case 64:
#if !defined(TBC_NOT_INT64)
            {
                tbc_u64_t src64 = *((tbc_u64_t*)src);
                do {
                    dest[len] = ('0' + (src64 % 10));
                    src64 = (src64 / 10);
                    ++len;
                }
                while (src64 && len <= (dn - 1));
                break;
            }
#endif
            default:
                break;
        }

        /* formating */
        if (len > 0) {
            tbc_u8_t i = (len - 1);
            tbc_u8_t o = 0;

            /* terminator */
            dest[len] = '\0';

            /* xor swap */
            while (i > o) {
                if (dest[i] != dest[o]) {
                    dest[i] ^= dest[o];
                    dest[o] ^= dest[i];
                    dest[i] ^= dest[o];
                }
                --i;
                ++o;
            }
        }
    }
    while(0);

    return len;
}
