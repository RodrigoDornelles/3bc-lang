#ifndef H_MACRO_CONSTS_TBC
#define H_MACRO_CONSTS_TBC

#ifndef TBC_MAX_RX
#define TBC_MAX_RX 7
#endif

#ifndef TBC_MAX_RY
#define TBC_MAX_RY 512
#endif

#ifndef TBC_MAX_RZ
#define TBC_MAX_RZ 1023
#endif

/**
 * @par mask @c 0x1 in @c TBC_RRZ
 * @brief Required RZ
 * @c 0b1
 */
#define TBC_RRZ (0x1)

/**
 * @par mask @c 0x2 in @c TBC_RRY
 * @brief Required RY
 * @c 0b10
 */
#define TBC_RRY (0x2)

/**
 * @par mask @c 0x4 in @c TBC_NRZ
 * @brief Forbidden RZ
 * @c 0b100
 */
#define TBC_NRZ (0x4)

/**
 * @par mask @c 0x8 in @c TBC_NRT
 * @brief Forbidden RT
 * @c 0b1000
 */
#define TBC_NRY (0x8)

/**
 * @short alias to @ref TBC_DUAL_AZ
 * @brief use this to check if it matches any type of duality.
 * @see @ref TBC_DUAL_AZ
 * @see @ref TBC_DUAL_NZ)
 */
#define TBC_DUAL (0x10)

/**
 * @par mask @c 0x10 in @c TBC_DUAL_AZ
 * @short Duality (allowed zero)
 * @brief exclusive use RZ or RY
 * @li when uses RZ and RY causes error.
 * @c 0b10000
 */
#define TBC_DUAL_AZ (0x10)

/**
 * @par mask @c 0x30 in @c TBC_DUAL_NZ
 * @short Duality (non zero)
 * @brief exclusive use RZ or RY
 * @li when you uses RZ and RY causes error.
 * @li when don't uses RZ or RY causes error.
 * @see @ref TBC_DUAL_AZ
 * @see @ref TBC_RXY
 * @c 0b110000
 */
#define TBC_DUAL_NZ (0x20|0x10)

/**
 * @par mask @c 0x30 in @c TBC_DUAL_NZ
 * @brief Required any column
 * @li when don't uses RZ or RY causes error.
 * @c 0b100000
 */
#define TBC_RYZ (0x20)

/**
 * @par mask @c 0xC in @c TBC_NXY
 * @brief Forbidden any column
 * @li when uses RZ or RY causes error.
 * @c 0b1100
 */
#define TBC_NYZ (0x4|0x8)

#endif
