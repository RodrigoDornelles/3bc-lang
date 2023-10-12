#ifndef H_DETECT_COMPILER_TBC
#define H_DETECT_COMPILER_TBC

#include "detect_warning.h"

/**
 * @brief Language version
 */
#if defined(__STDC_VERSION__)
#if (__STDC_VERSION__ >= 202311L)
#define TBC_COMPILER_IS_C23
#define TBC_COMPILER_HAS_C23
#define TBC_COMPILER_HAS_C17
#define TBC_COMPILER_HAS_C11
#define TBC_COMPILER_HAS_C99
#elif (__STDC_VERSION__ >= 201710L)
#define TBC_COMPILER_IS_C17
#define TBC_COMPILER_HAS_C17
#define TBC_COMPILER_HAS_C11
#define TBC_COMPILER_HAS_C99
#elif (__STDC_VERSION__ >= 201112L)
#define TBC_COMPILER_IS_C11
#define TBC_COMPILER_HAS_C11
#define TBC_COMPILER_HAS_C99
#elif (__STDC_VERSION__ >= 199901L)
#define TBC_COMPILER_IS_C99
#define TBC_COMPILER_HAS_C99
#else
#define TBC_COMPILER_IS_C89
#endif
#else
#define TBC_COMPILER_IS_C89
#endif

/**
 * @brief Compiler version
 * @li @b TBC_COMPILER_ID_TCC <https://bellard.org/tcc/> 
 * @li @b TBC_COMPILER_ID_CC65 <https://cc65.github.io/> 
 * @li @b TBC_COMPILER_ID_CLANG <https://clang.llvm.org/> 
 * @li @b TBC_COMPILER_ID_GCC <https://gcc.gnu.org/> 
 * @li @b TBC_COMPILER_ID_MSVC <https://visualstudio.microsoft.com/> 
 * @li @b TBC_COMPILER_ID_Z88DK <https://z88dk.org/>  
 */
#if defined(__TINYC__) || defined(__TINYCC__)
#define TBC_COMPILER_NAME "TCC"
#define TBC_COMPILER_ID_TCC
#elif defined(__CC65_STD__) || defined(__CC65_STD_CC65__)
#define TBC_COMPILER_NAME "CC65"
#define TBC_COMPILER_ID_CC65
#elif defined(__llvm__) || defined(__clang__)
#define TBC_COMPILER_NAME "CLANG"
#define TBC_COMPILER_ID_CLANG
#elif defined(__GNUC__)
#define TBC_COMPILER_NAME "CLANG"
#define TBC_COMPILER_ID_GCC
#elif defined(_MSC_VER)
#define TBC_COMPILER_NAME "MSVC"
#define TBC_COMPILER_ID_MSVC
#elif defined(__Z88DK) || defined(Z80)
#define TBC_COMPILER_NAME "Z88DK"
#define TBC_COMPILER_ID_Z88DK
#else
#define TBC_COMPILER_NAME "UNKWNON"
#define TBC_COMPILER_ID_UNKWNON
#if defined(TBC_WARNING_ERR)
#error "[3BC] Compiler Unknown"
#elif defined(TBC_WARNING_STD)
#warning "[3BC] Compiler Unknown"
#elif defined(TBC_WARNING_MSVC)
#pragma message("[3BC] Compiler Unknown")
#endif
#endif


/**
 * @brief Compiler nickname
 */
#if defined(TBC_COMPILER_NICKNAME)
#define TBC_COMPILER_FULLNAME TBC_COMPILER_NICKNAME
#elif defined(__VERSION__)
#define TBC_COMPILER_FULLNAME __VERSION__
#else
#define TBC_COMPILER_FULLNAME TBC_COMPILER_NAME
#endif

#endif
