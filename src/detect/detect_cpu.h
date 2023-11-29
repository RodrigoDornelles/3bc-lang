/**
 * @file src/detect/detect_cpu.h
 * @brief recognize the hardware
 * @par Joke
 * @code{.unparsed}
 * Personally, I find "bytesex" a curious term!
 * I tend to easily confuse the word  length in English,
 * so imagine writing "endianness" all the time with two times 'N' and 'S'...
 * I'm just a latin american guy.
 * @endcode
 * @par Songs
 * @li @b Belchior - Apenas Um Rapaz Latino-americano
 * @endverbatim
 * @par Links
 * @li <https://linux.bytesex.org/>
 * @li <https://www.google.com/search?q=bytesex+site:opensource.apple.com>
 */
#ifndef H_DETECT_CPU_TBC
#define H_DETECT_CPU_TBC

#include "detect_warning.h"

#if defined(DOXYGEN)
#define TBC_CPU_ARCH_32BITS
#define TBC_CPU_ARCH_64BITS
#define TBC_CPU_ARCH_8BITS
#define TBC_CPU_BYTE_SEXBE
#define TBC_CPU_BYTE_SEXLE
#define TBC_CPU_TYPE_ARM
#define TBC_CPU_TYPE_AVR
#define TBC_CPU_TYPE_ECMA
#define TBC_CPU_TYPE_INTEL
#define TBC_CPU_TYPE_M6502
#define TBC_CPU_TYPE_POWERPC
#define TBC_CPU_TYPE_RISCV
#define TBC_CPU_TYPE_ZIGLOG
#elif defined(ARDUINO_ARCH_AVR)
#define TBC_CPU_NAME "AVR"
#define TBC_CPU_ARCH_8BITS
#define TBC_CPU_TYPE_AVR
#define TBC_CPU_BYTE_SEXLE
#elif defined(__CC65_STD__) || defined(__CC65_STD_CC65__)
#define TBC_CPU_NAME "6502"
#define TBC_CPU_ARCH_8BITS
#define TBC_CPU_TYPE_M6502
#define TBC_CPU_BYTE_SEXLE
#elif defined(__Z88DK) || defined(__Z80) || defined(Z80)
#define TBC_CPU_NAME "Z80"
#define TBC_CPU_ARCH_8BITS
#define TBC_CPU_TYPE_ZIGLOG
#elif defined(__arm) || defined(__arm__) || defined(_M_ARM)
#define TBC_CPU_NAME "ARM32"
#define TBC_CPU_ARCH_32BITS
#define TBC_CPU_TYPE_ARM
#define TBC_CPU_BYTE_SEXLE
#elif defined(EMSCRIPTEN)
#define TBC_CPU_NAME "ECMA"
#define TBC_CPU_ARCH_32BITS
#define TBC_CPU_TYPE_ECMA
#define TBC_CPU_BYTE_SEXLE
#elif defined(__i386) || defined(__i386__) || defined(_M_IX86)
#define TBC_CPU_NAME "INTEL"
#define TBC_CPU_ARCH_32BITS
#define TBC_CPU_TYPE_INTEL
#define TBC_CPU_BYTE_SEXLE
#elif defined(__ppc32__) || defined(__ppc__)
#define TBC_CPU_NAME "PPC32"
#define TBC_CPU_ARCH_32BITS
#define TBC_CPU_TYPE_POWERPC
/** @todo test if powerpc works with big endian */
#define TBC_CPU_BYTE_SEXBE
#elif defined(__riscv) && (!defined(__riscv_xlen) || __riscv_xlen != 64)
#define TBC_CPU_NAME "RISCV"
#define TBC_CPU_ARCH_32BITS
#define TBC_CPU_TYPE_RISCV
#define TBC_CPU_BYTE_SEXLE
#elif defined(__s390__)
#define TBC_CPU_NAME "s390"
#define TBC_CPU_ARCH_32BITS
#define TBC_CPU_TYPE_IBMZ
#define TBC_CPU_BYTE_SEXBE
#elif defined(__aarch64__) || defined(_M_ARM64)
#define TBC_CPU_NAME "ARM64"
#define TBC_CPU_ARCH_64BITS
#define TBC_CPU_TYPE_ARM
#define TBC_CPU_BYTE_SEXLE
#elif defined(__x86_64) || defined(__x86_64__) || defined(_M_AMD64)
#define TBC_CPU_NAME "AMD64"
#define TBC_CPU_ARCH_64BITS
#define TBC_CPU_TYPE_INTEL
#define TBC_CPU_BYTE_SEXLE
#elif defined(__ppc64__)
#define TBC_CPU_NAME "PPC64"
#define TBC_CPU_ARCH_64BITS
#define TBC_CPU_TYPE_POWERPC
#define TBC_CPU_BYTE_SEXLE
#elif defined(ESP_PLATFORM) || defined(ARDUINO_ARCH_ESP8266) ||\
    (defined(__riscv) && (defined(__riscv_xlen) && __riscv_xlen == 64))
#define TBC_CPU_NAME "RISC64"
#define TBC_CPU_ARCH_32BITS
#define TBC_CPU_TYPE_RISCV
#define TBC_CPU_BYTE_SEXLE
#elif defined(__s390x__)
/** @todo to detect_unsupported.h */
#define TBC_NOT_INT64
#define TBC_CPU_NAME "s390x"
#define TBC_CPU_ARCH_64BITS
#define TBC_CPU_TYPE_IBMZ
#define TBC_CPU_BYTE_SEXBE
#else
#define TBC_CPU_NAME "UNKNOWN"
#define TBC_CPU_ARCH_8BITS
#define TBC_CPU_BYTE_SEXLE
#if defined(TBC_WARNING_ERR)
#error "[3BC] CPU Unknown"
#elif defined(TBC_WARNING_STD)
#warning "[3BC] CPU Unknown"
#elif defined(TBC_WARNING_MSVC)
#pragma message("[3BC] CPU Unknown")
#endif
#endif

#endif
