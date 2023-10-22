#include "util_stoi.h"
#include "types/types_null.h"

/**
 * @short cast func select
 * @details return a parse string to integer function according the number base.
 * @param[out] dest string destination
 * @param[out] dn lenght destination
 * @param[in] src string input
 * @param[in] sn string lenght
 * @return function pointer
 * @retval NULL when unknown base
 * @retval !NULL when found base
 */
util_stoi_ft util_stoi_auto(char** dest, tbc_i8_t* dn, char *src, tbc_i8_t sn)
{
    util_stoi_ft func = NULL;

    do{
        if (src == NULL) {
            break;
        }
        if (dest == NULL) {
            break;
        }
        if (*src == '-') {
            ++src;
            --sn;
        }
        if ('1' <= *src && *src <= '9') {
            func = &util_stoi10;
        }
        if ('0' == *src){
            ++src;
            --sn;
            if ('1' <= (*src) && (*src) <= '9'){
                func = &util_stoi10;
                break;
            }
            else if (*src == 'b') {
                func = &util_stoi2;
            }
            else if (*src == 'o') {
                func = &util_stoi8;
            }
            else if (*src == 'd' || *src == 'i') {
                func = &util_stoi10;
            }
            else if (*src == 'x') {
                func = &util_stoi16;
            }
            else {
                func = &util_stoi10;
                --src;
                ++sn;
                break;
            }
            ++src;
            --sn;
        }
    }
    while(0);

    if (func != NULL) {
        *dn = sn;
        *dest = src;
    }

    return func;
}

/**
 * @short hexadecimal
 * @brief @par casting string to integer
 * @details parse string to integer in base 16.
 * @param[out] dest integer destination
 * @param[in] src string source
 * @param[in] dn integer destination length @b (bits)
 * @param[in] sn string source length @b (bytes)
 * @return status of parsing
 * @retval @ref ERROR_UNKNOWN when success  
 * @retval @ref ERROR_NUMBER_OVERFLOW when fail
 * @retval @ref ERROR_NUMBER_NO_DIGITS when fail
 * @retval @ref ERROR_NUMBER_WRONG_BASE when fail
 * @retval @ref ERROR_NUMBER_SIZE_TOO_LONG when fail
 * @startebnf
 * base16 =
 * ("0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "A" | "B" | "C" | "D" | "E" | "F"),
 * {"0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "A" | "B" | "C" | "D" | "E" | "F" | "_"};
 * @endebnf
 */
tbc_error_et util_stoi16(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn)
{
    char c;
    tbc_u8_t index = 0;
    tbc_u8_t digits = 0;
    tbc_error_et res = ERROR_UNKNOWN;
    do {
        if (dn <= 8) {
            tbc_u8_t copy8 = 0;
            do {
                c = src[index];
                if (c == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (c == '\0') {
                    break;
                }
                c |= 0x20;
                copy8 <<= 4;
                digits += digits || (c > '0')? 4: 0;
                if (c >= '0' && c <= '9') {
                    copy8 |= c - '0';
                } else if (c >= 'a' && c <= 'f') {
                    copy8 |= c - 'a' + 0xA;
                } else {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                ++index;
            }
            while(index < sn);
            if (digits > dn) {
                res = ERROR_NUMBER_OVERFLOW;
            }
            if (digits > 0 && res == ERROR_UNKNOWN) {
                *((tbc_u8_t*)dest) = copy8;
            }
            break;
        }
        if (dn <= 16) {
            tbc_u16_t copy16 = 0;
            do {
                c = src[index];
                if (c == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (c == '\0') {
                    break;
                }
                c |= 0x20;
                copy16 <<= 4;
                digits += digits || (c > '0')? 4: 0;
                if (c >= '0' && c <= '9') {
                    copy16 |= c - '0';
                } else if (c >= 'a' && c <= 'f') {
                    copy16 |= c - 'a' + 0xA;
                } else {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                ++index;
            }
            while(index < sn);
            if (digits > dn) {
                res = ERROR_NUMBER_OVERFLOW;
            }
            if (digits > 0 && res == ERROR_UNKNOWN) {
                *((tbc_u16_t*)dest) = copy16;
            }
            break;
        }
        if (dn <= 32) {
            tbc_u32_t copy32 = 0;
            do {
                c = src[index];
                if (c == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (c == '\0') {
                    break;
                }
                c |= 0x20;
                copy32 <<= 4;
                digits += digits || (c > '0')? 4: 0;
                if (c >= '0' && c <= '9') {
                    copy32 |= c - '0';
                } else if (c >= 'a' && c <= 'f') {
                    copy32 |= c - 'a' + 0xA;
                } else {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                ++index;
            }
            while(index < sn);
            if (digits > dn) {
                res = ERROR_NUMBER_OVERFLOW;
            }
            if (digits > 0 && res == ERROR_UNKNOWN) {
                *((tbc_u32_t*)dest) = copy32;
            }
            break;
        }
 #if !defined(TBC_NOT_INT64)
        if (dn <= 64)
        {
            tbc_u64_t copy64 = 0;
            do {
                c = src[index];
                if (c == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (c == '\0') {
                    break;
                }
                c |= 0x20;
                copy64 <<= 4;
                digits += digits || (c > '0')? 4: 0;
                if (c >= '0' && c <= '9') {
                    copy64 |= c - '0';
                } else if (c >= 'a' && c <= 'f') {
                    copy64 |= c - 'a' + 0xA;
                } else {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                ++index;
            }
            while(index < sn);
            if (digits > dn) {
                res = ERROR_NUMBER_OVERFLOW;
            }
            if (digits > 0 && res == ERROR_UNKNOWN) {
                *((tbc_u64_t*)dest) = copy64;
            }
            break;
        }
#endif
        res = ERROR_NUMBER_SIZE_TOO_LONG;
    }
    while(0);

    if (digits == 0 && res == ERROR_UNKNOWN) {
        res = ERROR_NUMBER_NO_DIGITS;
    }

    return res;
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
tbc_error_et util_stoi10(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn)
{
    tbc_u8_t index = 0;
    tbc_error_et res = ERROR_UNKNOWN;
    do {
        if (dn <= 8 ) {
            tbc_u8_t copy8 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] < '0' || src[index] > '9') {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy8 *= 10u;
                copy8 += src[index] - '0';
                ++index;
            }
            while(index < sn);
            if (res == ERROR_UNKNOWN) {
                *((tbc_u8_t*)dest) = copy8;
            }
            break;
        }
        if (dn <= 16) {
            tbc_u16_t copy16 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] < '0' || src[index] > '9') {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy16 *= 10;
                copy16 += src[index] - '0';
                ++index;
            }
            while(index < sn);
            if (res == ERROR_UNKNOWN) {
                *((tbc_u16_t*)dest) = copy16;
            }
            break;
        }
        if (dn <= 32) {
            tbc_u32_t copy32 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] < '0' || src[index] > '9') {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy32 *= 10;
                copy32 += src[index] - '0';
                ++index;
            }
            while(index < sn);
            if (res == ERROR_UNKNOWN) {
                *((tbc_u32_t*)dest) = copy32;
            }
            break;
        }
 #if !defined(TBC_NOT_INT64)
        if (dn <= 64) {
            tbc_u64_t copy64 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] < '0' || src[index] > '9') {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy64 *= 10;
                copy64 += src[index] - '0';
                ++index;
            }
            while(index < sn);
            if (res == ERROR_UNKNOWN) {
                *((tbc_u64_t*)dest) = copy64;
            }
            break;
        }
#endif
        res = ERROR_NUMBER_SIZE_TOO_LONG;
    }
    while(0);

    if (index == 0 && res != ERROR_UNKNOWN) {
        res = ERROR_NUMBER_NO_DIGITS;
    }

    return res;
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
 * @retval @ref ERROR_UNKNOWN when success 
 * @retval @ref ERROR_NUMBER_OVERFLOW when fail
 * @retval @ref ERROR_NUMBER_NO_DIGITS when fail
 * @retval @ref ERROR_NUMBER_WRONG_BASE when fail
 * @retval @ref ERROR_NUMBER_SIZE_TOO_LONG when fail
 * @startebnf
 * base8 =
 * ("0" | "1" | "2" | "3" | "4" | "5" | "6" | "7"),
 * {"0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "_"};
 * @endebnf
 */
tbc_error_et util_stoi8(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn)
{
    tbc_u8_t index = 0;
    tbc_u8_t digits = 0;
    tbc_error_et res = ERROR_UNKNOWN;

    do {
        if (sn == 0) {
            break;
        }

        if (dn <= 8) {
            tbc_u8_t copy8 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] == '0') {
                    digits += digits > 0? 3: 0;
                }
                else if ('1' <= src[index] && src[index] <= '7') {
                    digits += 3;
                } else {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy8 <<= 3;
                copy8 |= src[index] - '0';
                ++index;
            }
            while(index < sn);
            if (digits > dn) {
                res = ERROR_NUMBER_OVERFLOW;
            }
            if (digits > 0 && res == ERROR_UNKNOWN) {
                *((tbc_u8_t*)dest) = copy8;
            }
            break;
        }
        if (dn <= 16) {
            tbc_u16_t copy16 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] == '0') {
                    digits += digits > 0? 3: 0;
                }
                else if ('1' <= src[index] && src[index] <= '7') {
                    digits += 3;
                } else {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy16 <<= 3;
                copy16 |= src[index] - '0';
                ++index;
            }
            while(index < sn);
            if (digits > dn) {
                res = ERROR_NUMBER_OVERFLOW;
            }
            if (digits > 0 && res == ERROR_UNKNOWN) {
                *((tbc_u16_t*)dest) = copy16;
            }
            break;
        }
        if (dn <= 32) {
            tbc_u32_t copy32 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] == '0') {
                    digits += digits > 0? 3: 0;
                }
                else if ('1' <= src[index] && src[index] <= '7') {
                    digits += 3;
                } else {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy32 <<= 3;
                copy32 |= src[index] - '0';
                ++index;
            }
            while(index < sn);
            if (digits > dn) {
                res = ERROR_NUMBER_OVERFLOW;
            }
            if (digits > 0 && res == ERROR_UNKNOWN) {
                *((tbc_u32_t*)dest) = copy32;
            }
            break;
        }
 #if !defined(TBC_NOT_INT64)
        if (dn <= 64) {
            tbc_u64_t copy64 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] == '0') {
                    digits += digits > 0? 3: 0;
                }
                else if ('1' <= src[index] && src[index] <= '7') {
                    digits += 3;
                } else {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy64 <<= 3;
                copy64 |= src[index] - '0';
                ++index;
            }
            while(index < sn);
            if (digits > dn) {
                res = ERROR_NUMBER_OVERFLOW;
            }
            if (digits > 0 && res == ERROR_UNKNOWN) {
                *((tbc_u64_t*)dest) = copy64;
            }
            break;
        }
#endif
        res = ERROR_NUMBER_SIZE_TOO_LONG;
        break;
    }
    while(0);

    if (digits == 0 && res == ERROR_UNKNOWN) {
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
 * @retval @ref ERROR_UNKNOWN when success 
 * @retval @ref ERROR_NUMBER_OVERFLOW when fail
 * @retval @ref ERROR_NUMBER_NO_DIGITS when fail
 * @retval @ref ERROR_NUMBER_WRONG_BASE when fail
 * @retval @ref ERROR_NUMBER_SIZE_TOO_LONG when fail
 * @startebnf
 * base2 =
 * ("0" | "1"),
 * {"0" | "1" | "_"};
 * @endebnf
 */
tbc_error_et util_stoi2(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn)
{
    tbc_u8_t index = 0;
    tbc_u8_t digits = 0;
    tbc_error_et res = ERROR_UNKNOWN;
    
    do {
        if (sn == 0) {
            break;
        }

        if (dn <= 8) {
            tbc_u8_t copy8 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] == '1') {
                    ++digits;
                }
                else if (src[index] == '0') {
                    digits += !!digits;

                } else {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy8 <<= 1;
                copy8 |= src[index] == '1';
                ++index;
            }
            while(index < sn);
            if (digits > dn) {
                res = ERROR_NUMBER_OVERFLOW;
            }
            if (digits > 0 && res == ERROR_UNKNOWN) {
                *((tbc_u8_t*)dest) = copy8;
            }
            break;
        }
        if (dn <= 16) {
            tbc_u16_t copy16 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] == '1') {
                    ++digits;
                }
                else if (src[index] == '0') {
                    digits += !!digits;

                } else {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy16 <<= 1;
                copy16 |= src[index] == '1';
                ++index;
            }
            while(index < sn);
            if (digits > dn) {
                res = ERROR_NUMBER_OVERFLOW;
            }
            if (digits > 0 && res == ERROR_UNKNOWN) {
                *((tbc_u16_t*)dest) = copy16;
            }
            break;
        }
        if (dn <= 32) {
            tbc_u32_t copy32 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] == '1') {
                    ++digits;
                }
                else if (src[index] == '0') {
                    digits += !!digits;

                } else {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy32 <<= 1;
                copy32 |= src[index] == '1';
                ++index;
            }
            while(index < sn);
            if (digits > dn) {
                res = ERROR_NUMBER_OVERFLOW;
            }
            if (digits > 0 && res == ERROR_UNKNOWN) {
                *((tbc_u32_t*)dest) = copy32;
            }
            break;
        }
 #if !defined(TBC_NOT_INT64)
        if (dn <= 64) {
            tbc_u64_t copy64 = 0;
            do {
                if (src[index] == '_' && index > 0) {
                    ++index;
                    continue;
                }
                if (src[index] == '\0') {
                    break;
                }
                if (src[index] == '1') {
                    ++digits;
                }
                else if (src[index] == '0') {
                    digits += !!digits;

                } else {
                    res = ERROR_NUMBER_WRONG_BASE;
                    break;
                }
                copy64 <<= 1;
                copy64 |= src[index] == '1';
                ++index;
            }
            while(index < sn);
            if (digits > dn) {
                res = ERROR_NUMBER_OVERFLOW;
            }
            if (digits > 0 && res == ERROR_UNKNOWN) {
                *((tbc_u64_t*)dest) = copy64;
            }
            break;
        }
#endif
        res = ERROR_NUMBER_SIZE_TOO_LONG;
    }
    while (0);

    if (digits == 0 && res == ERROR_UNKNOWN) {
        res = ERROR_NUMBER_NO_DIGITS;
    }

    return res;
}
