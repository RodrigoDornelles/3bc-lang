#ifndef H_MACRO_CONSTS_TBC
#define H_MACRO_CONSTS_TBC

/**
 * @par mask @c 0x1 in @c TBC_RRX
 * @brief Required RX
 * @c 0b0001
 */
#define TBC_RRX (0x1)

/**
 * @par mask @c 0x2 in @c TBC_RRY
 * @brief Required RY
 * @c 0b0010
 */
#define TBC_RRY (0x2)

/**
 * @par mask @c 0x4 in @c TBC_RRX
 * @brief Forbidden RX
 * @c 0b0100
 */
#define TBC_NRX (0x4)

/**
 * @par mask @c 0x8 in @c TBC_RRT
 * @brief Forbidden RT
 * @c 0b1000
 */
#define TBC_NRY (0x8)

/**
 * @short alias to @ref TBC_DUAL_AZ
 * @brief use this to check if it matches any type of duality.
 * (@ref TBC_DUAL_AZ or @ref TBC_DUAL_NZ)
 */
#define TBC_DUAL (0x5)

/**
 * @par mask @c 0x5 in @c TBC_DUAL_AZ
 * @short Duality (allowed zero)
 * @brief exclusive use RX or RY
 * @li when uses RX and RY causes error.
 * @c 0b0101
 */
#define TBC_DUAL_AZ (0x5)

/**
 * @par mask @c 0x7 in @c TBC_DUAL_NZ
 * @short Duality (non zero)
 * @brief exclusive use RX or RY
 * @li when you uses RX and RY causes error.
 * @li when don't uses RX or RY causes error.
 * @c 0b0111
 */
#define TBC_DUAL_NZ (0x7)

#endif
