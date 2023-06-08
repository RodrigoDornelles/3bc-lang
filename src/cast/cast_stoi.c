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
tbc_return_et cast_stoi16(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn)
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
tbc_return_et cast_stoi10(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn)
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
tbc_return_et cast_stoi8(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn)
{

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
tbc_return_et cast_stoi2(void *const dest, char *const src, const tbc_u8_t dn, tbc_u8_t sn)
{

}
