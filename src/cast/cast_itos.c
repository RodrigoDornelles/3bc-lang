#include "cast_itos.h"

/**
 * @short [0-9] to char*
 * @brief casting integer to string
 * @pre @b bits: 8, 10, 13, 16, 32, 64.
 * @param[out] dest string destination
 * @param[in] src integer destination
 * @param[in] dn string destination length @b (bytes)
 * @param[in] sn integer destinatin length @b (bits)
 */
void cast_itos10(char* dest, void *src, tbc_u8_t dn, tbc_u8_t sn)
{
    tbc_u8_t i1 = 0, i2 = 0;
    
    /* evaluate */
    switch (sn) {
        case 8:
        {
            tbc_u8_t srcopied = *((tbc_u8_t*)src);
            while (srcopied && i1 < dn) {
                dest[i1] = ('0' + (srcopied % 10));
                srcopied = (srcopied / 10);
                ++i1;
            }
            break;
        }

        case 10:
        case 13:
        case 16:
        {
            tbc_u16_t srcopied = *((tbc_u16_t*)src);
            while (srcopied && i1 < dn) {
                dest[i1] = ('0' + (srcopied % 10));
                srcopied = (srcopied / 10);
                ++i1;
            }
            break;
        }
        case 32:
        {
            tbc_u32_t srcopied = *((tbc_u32_t*)src);
            while (srcopied && i1 < dn) {
                dest[i1] = ('0' + (srcopied % 10));
                srcopied = (srcopied / 10);
                ++i1;
            }
            break;
        }
        case 64:
        {
            tbc_u64_t srcopied = *((tbc_u64_t*)src);
            while (srcopied && i1 < dn) {
                dest[i1] = ('0' + (srcopied % 10));
                srcopied = (srcopied / 10);
                ++i1;
            }
            break;
        }
        default:
        {
            dest[i1] = '?';
            ++i1;
            break;
        }
    }

    /* terminator */
    dest[i1] = '\0';
    --i1;

    /* xor swap */
    while (i1 > i2) {
        dest[i1] ^= dest[i2];
        dest[i2] ^= dest[i1];
        dest[i1] ^= dest[i2];
        --i1;
        ++i2;
    }
}
