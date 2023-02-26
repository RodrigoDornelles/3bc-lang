#ifndef H_TYPES_PRIMITIVE_TBC
#define H_TYPES_PRIMITIVE_TBC

#include "3bc_detect.h"

#if defined(TBC_CC_STD_99)
#include <inttypes.h>
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
#elif defined(TBC_ARCH_BITS_8)
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
#else
#error [3BC] unknown compiler arch please upgrade to ISO C99 STANDARD.
#endif

#endif
