#include "util_djb2.h"

/**
 * @brief hash djb2 algorithm
 * @param[out] dest integer destination
 * @param[in] src string source
 * @param[in] dn integer destination length @b (bits)
 * @param[in] sn string source length @b (bytes)
 * @pre @c sn must be 8, 16 or 32.
 * @pre @c sn @b cannot be @b 64 bits.
 * @note the character @c '\n' is a terminator of hash.
 * @return status of digest
 * @retval ERROR_UNKNOWN when success
 * @retval ERROR_NUMBER_INVALID_BASE when failed
 * @retval ERROR_NUMBER_NO_DIGITS when failed
 */
tbc_error_et util_djb2(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn)
{
    tbc_u8_t index = 0;
    tbc_error_et res = ERROR_UNKNOWN;

    switch (dn) {
        case 8:
        {
            tbc_u8_t hash = 5;
            while (index < sn && src[index] != '\n' && src[index] != '\0') {
                hash = ((hash << 5) + hash) + src[index];
                ++index;
            }
            if (index > 0) {
                *((tbc_u8_t*)dest) = hash;
            }
            break;
        }
        case 16:
        {
            tbc_u16_t hash = 5381;
            while (index < sn && src[index] != '\n' && src[index] != '\0') {
                hash = ((hash << 5) + hash) + src[index];
                ++index;
            }
            if (index > 0) {
                *((tbc_u16_t*)dest) = hash;
            }
            break;
        }
        case 32:
        {
            tbc_u32_t hash = 5381;
            while (index < sn && src[index] != '\n' && src[index] != '\0') {
                hash = ((hash << 5) + hash) + src[index];
                ++index;
            }
            if (index > 0) {
                *((tbc_u32_t*)dest) = hash;
            }
            break;
        }
        default:
            res = ERROR_NUMBER_INVALID_BASE;
            break;
    }

    if (index == 0 && res == ERROR_UNKNOWN) {
        res = ERROR_NUMBER_NO_DIGITS;
    }

    return res;
}