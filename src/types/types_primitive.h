#ifndef H_TYPES_PRIMITIVE_TBC
#define H_TYPES_PRIMITIVE_TBC

#include "3bc_detect.h"

#if (defined(TBC_CC_STD_99) && !defined(TBC_NOT_INTYPES)) || defined(DOXYGEN)
#include <inttypes.h>
#include <stddef.h>
/** signed 8 bits **/
typedef int8_t tbc_i8_t;
/** signed 16 bits **/
typedef int16_t tbc_i16_t;
/** signed 32 bits **/
typedef int32_t tbc_i32_t;
/** signed 64 bits **/
typedef int64_t tbc_i64_t;
/** unsigned 8 bits **/
typedef uint8_t tbc_u8_t;
/** unsigned 16 bits **/
typedef uint16_t tbc_u16_t;
/** unsigned 32 bits **/
typedef uint32_t tbc_u32_t;
/** unsigned 64 bits **/
typedef uint64_t tbc_u64_t;
/** architeture pointer size */
typedef size_t tbc_size_t;
#elif defined(TBC_ARCH_BITS_64)
/** signed 8 bits **/
typedef signed char tbc_i8_t;
/** signed 16 bits **/
typedef signed short tbc_i16_t;
/** signed 32 bits **/
typedef signed int tbc_i32_t;
/** signed 64 bits **/
typedef signed long tbc_i64_t;
/** unsigned 8 bits **/
typedef unsigned char tbc_u8_t;
/** unsigned 16 bits **/
typedef unsigned short tbc_u16_t;
/** unsigned 32 bits **/
typedef unsigned int tbc_u32_t;
/** unsigned 64 bits **/
typedef unsigned long tbc_u64_t;
/** architeture pointer size */
typedef unsigned long tbc_size_t;
#elif defined(TBC_ARCH_BITS_32)
/** signed 8 bits **/
typedef signed char tbc_i8_t;
/** signed 16 bits **/
typedef signed short tbc_i16_t;
/** signed 32 bits **/
typedef signed int tbc_i32_t;
/** signed 64 bits **/
typedef signed long long tbc_i64_t;
/** unsigned 8 bits **/
typedef unsigned char tbc_u8_t;
/** unsigned 16 bits **/
typedef unsigned short tbc_u16_t;
/** unsigned 32 bits **/
typedef unsigned int tbc_u32_t;
/** unsigned 64 bits **/
typedef unsigned long long tbc_u64_t;
/** not support integer 64 bits */
#ifndef TBC_NOT_INT64
#define TBC_NOT_INT64
#endif
/** architeture pointer size */
typedef unsigned int tbc_size_t;
#elif defined(TBC_ARCH_BITS_16)
/** signed 8 bits **/
typedef signed char tbc_i8_t;
/** signed 16 bits **/
typedef signed short tbc_i16_t;
/** signed 32 bits **/
typedef signed int tbc_i32_t;
/** unsigned 8 bits **/
typedef unsigned char tbc_u8_t;
/** unsigned 16 bits **/
typedef unsigned short tbc_u16_t;
/** unsigned 32 bits **/
typedef unsigned int tbc_u32_t;
/** architeture pointer size */
typedef unsigned short tbc_size_t;
#elif defined(TBC_ARCH_BITS_8)
/** not support integer 64 bits */
#ifndef TBC_NOT_INT64
#define TBC_NOT_INT64
#endif
/** signed 8 bits **/
typedef signed char tbc_i8_t;
/** signed 16 bits **/
typedef signed int tbc_i16_t;
/** signed 32 bits **/
typedef signed long tbc_i32_t;
/** unsigned 8 bits **/
typedef unsigned char tbc_u8_t;
/** unsigned 16 bits **/
typedef unsigned int tbc_u16_t;
/** unsigned 32 bits **/
typedef unsigned long tbc_u32_t;
/** 
 * @brief architeture pointer size
 * @note 8 bits archs uses 16 bits pointer.
 */
typedef unsigned int tbc_size_t;
#else
#error [3BC] unknown compiler arch please upgrade to ISO C99 STANDARD.
#endif

#endif
