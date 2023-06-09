#include "cast_stoi.h"
#include "types_null.h"

/**
 * @short hexadecimal
 * @brief @par casting string to integer
 * @details parse string to integer in base 16.
 * @param[out] dest integer destination
 * @param[in] src string source
 * @param[in] dn integer destination length @b (bits)
 * @param[in] sn string source length @b (bytes)
 * @return status of parsing
 * @retval 0 when sucess
 * @retval 1 when error
 * @startebnf
 * base16 =
 * ("0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "A" | "B" | "C" | "D" | "E" | "F"),
 * {"0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "A" | "B" | "C" | "D" | "E" | "F" | "_"};
 * @endebnf
 */
tbc_error_et cast_stoi16(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn)
{

}

/**
 * @short decimal
 * @brief @par casting string to integer
 * @details parse string to integer in base 10.
 * @param[out] dest integer destination
 * @param[in] src string source
 * @param[in] dn integer destination length @b (bits)
 * @param[in] sn string source length @b (bytes)
 * @return status of parsing
 * @retval 0 when sucess
 * @retval 1 when error
 * @startebnf
 * base10 =
 * ("0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"),
 * {"0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "_"};
 * @endebnf
 */
tbc_error_et cast_stoi10(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn)
{

}

/**
 * @short octal
 * @brief @par casting string to integer
 * @details parse string to integer in base 8.
 * @param[out] dest integer destination
 * @param[in] src string source
 * @param[in] dn integer destination length @b (bits)
 * @param[in] sn string source length @b (bytes)
 * @return status of parsing
 * @retval 0 when sucess
 * @retval 1 when error
 * @startebnf
 * base8 =
 * ("0" | "1" | "2" | "3" | "4" | "5" | "6" | "7"),
 * {"0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "_"};
 * @endebnf
 */
tbc_error_et cast_stoi8(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn)
{
    tbc_u8_t index = 0;
    tbc_u8_t dn3bits = (dn/3) + 1;
    tbc_error_et res = ERROR_UNKNOWN;
    switch(dn) {
        case 8:
        {
            tbc_u8_t copy8 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] < '0' || src[index] > '7') {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy8 <<= 3;
                copy8 |= src[index] - '0';
                ++index;
            }
            while(index < sn && index < dn3bits);
            if (res == ERROR_UNKNOWN) {
                *((tbc_u8_t*)dest) = copy8;
            }
            break;
        }
        case 10:
        case 13:
        case 16:
        {
            tbc_u16_t copy16 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] < '0' || src[index] > '7') {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy16 <<= 3;
                copy16 |= src[index] - '0';
                ++index;
            }
            while(index < sn && index < dn3bits);
            if (res == ERROR_UNKNOWN) {
                *((tbc_u16_t*)dest) = copy16;
            }
            break;
        }
        case 32:
        {
            tbc_u32_t copy32 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] < '0' || src[index] > '7') {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy32 <<= 3;
                copy32 |= src[index] - '0';
                ++index;
            }
            while(index < sn && index < dn3bits);
            if (res == ERROR_UNKNOWN) {
                *((tbc_u32_t*)dest) = copy32;
            }
            break;
        }
        case 64:
        {
            tbc_u64_t copy64 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] < '0' || src[index] > '7') {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy64 <<= 3;
                copy64 |= src[index] - '0';
                ++index;
            }
            while(index < sn && index < dn3bits);
            if (res == ERROR_UNKNOWN) {
                *((tbc_u64_t*)dest) = copy64;
            }
            break;
        }
    }

    if (index == 0) {
        res = ERROR_NUMBER_NO_DIGITS;
    }

    return res;
}

/**
 * @short binary
 * @brief @par casting string to integer
 * @details parse string to integer in base 2.
 * @param[out] dest integer destination
 * @param[in] src string source
 * @param[in] dn integer destination length @b (bits)
 * @param[in] sn string source length @b (bytes)
 * @return status of parsing
 * @retval 0 when sucess
 * @retval 1 when error
 * @startebnf
 * base2 =
 * ("0" | "1"),
 * {"0" | "1" | "_"};
 * @endebnf
 */
tbc_error_et cast_stoi2(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn)
{
    tbc_u8_t index = 0;
    tbc_error_et res = ERROR_UNKNOWN;
    switch(dn) {
        case 8:
        {
            tbc_u8_t copy8 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] != '0' && src[index] != '1') {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy8 <<= 1;
                copy8 |= src[index] == '1';
                ++index;
            }
            while(index < sn && index < dn);
            if (res == ERROR_UNKNOWN) {
                *((tbc_u8_t*)dest) = copy8;
            }
            break;
        }
        case 10:
        case 13:
        case 16:
        {
            tbc_u16_t copy16 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] != '0' && src[index] != '1') {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy16 <<= 1;
                copy16 |= src[index] == '1';
                ++index;
            }
            while(index < sn && index < dn);
            if (res == ERROR_UNKNOWN) {
                *((tbc_u16_t*)dest) = copy16;
            }
            break;
        }
        case 32:
        {
            tbc_u32_t copy32 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] != '0' && src[index] != '1') {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy32 <<= 1;
                copy32 |= src[index] == '1';
                ++index;
            }
            while(index < sn && index < dn);
            if (res == ERROR_UNKNOWN) {
                *((tbc_u32_t*)dest) = copy32;
            }
            break;
        }
        case 64:
        {
            tbc_u64_t copy64 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] != '0' && src[index] != '1') {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy64 <<= 1;
                copy64 |= src[index] == '1';
                ++index;
            }
            while(index < sn && index < dn);
            if (res == ERROR_UNKNOWN) {
                *((tbc_u64_t*)dest) = copy64;
            }
            break;
        }
    }

    if (index == 0) {
        res = ERROR_NUMBER_NO_DIGITS;
    }

    return res;
}
