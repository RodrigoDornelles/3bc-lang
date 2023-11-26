/**
 * @file detect_compiler.c
 * @brief recognize compiler
 */

#ifndef H_DETECT_COMPILER_TBC
#define H_DETECT_COMPILER_TBC

#if defined(DOXYGEN) || defined(__STDC_VERSION__)
#if defined(DOXYGEN) || (__STDC_VERSION__ >= 202311L)
/**
 * @short C STANDARD ISO 2023
 * @n <https://en.cppreference.com/w/c/23>
*/
#define TBC_COMPILER_HAS_C23
/**
 * @short C STANDARD ISO 2017
 * @n <https://en.cppreference.com/w/c/17>
*/
#define TBC_COMPILER_HAS_C17
/**
 * @short C STANDARD ISO 2011
 * @n <https://en.cppreference.com/w/c/11>
*/
#define TBC_COMPILER_HAS_C11
/**
 * @short C STANDARD ISO 1999
 * @n <https://en.cppreference.com/w/c/99>
*/
#define TBC_COMPILER_HAS_C99
#elif (__STDC_VERSION__ >= 201710L)
#define TBC_COMPILER_HAS_C17
#define TBC_COMPILER_HAS_C11
#define TBC_COMPILER_HAS_C99
#elif (__STDC_VERSION__ >= 201112L)
#define TBC_COMPILER_HAS_C11
#define TBC_COMPILER_HAS_C99
#elif (__STDC_VERSION__ >= 199901L)
#define TBC_COMPILER_HAS_C99
#endif
#endif

/**
 * @short Tiny C Compiler
 * @n <https://bellard.org/tcc/> 
 * @brief FAST! tcc generates x86 code. No byte code overhead.
 * Compile, assemble and link several times faster than GCC.
 * @date 2001
 * @author Fabrice Bellard
 * @copyright GNU Lesser General Public License
 */
#if defined(DOXYGEN) || defined(__TINYC__) || defined(__TINYCC__)
#define TBC_COMPILER_ID_TCC
#endif

/**
 * @short CC65
 * @n <https://cc65.github.io/> 
 * @brief a freeware C compiler for 6502 based systems.
 * @date 1998
 * @author Ullrich von Bassewitz
 * @copyright zLib
 */ 
#if defined(DOXYGEN) || defined(__CC65_STD__) || defined(__CC65_STD_CC65__)
#define TBC_COMPILER_ID_CC65
#endif

/**
 * @short LLVM C Language Compiler
 * @n <https://clang.llvm.org/> 
 * @brief The LLVM Core libraries provide a modern source and
 * target-independent optimizer, along with code generation support
 * for many popular CPUs.
 * @date 2003
 * @author Chris Lattner
 * @author Vikram Adve
 * @copyright Apache License 2.0 with LLVM Exceptions
 */ 
#if defined(DOXYGEN) || defined(__llvm__) || defined(__clang__)
#define TBC_COMPILER_ID_CLANG
#endif

/**
 * @short GNU Compiler Collection
 * @n <https://gcc.gnu.org/>
 * @brief The GNU Compiler Collection includes front ends for C, C++... 
 * as well as libraries for these languages 
 * @date 1987
 * @author Richard Stallman
 * @copyright GNU General Public License 3.0
 */ 
#if defined(DOXYGEN) || defined(__GNUC__)
#define TBC_COMPILER_ID_GCC
#endif

/**
 * @short Visual Studio
 * @n <https://visualstudio.microsoft.com/>
 * @brief cl.exe is a tool that controls the Microsoft C++ (MSVC) C and C++
 * compilers and linker.can be run only on operating systems that support
 * Microsoft Visual Studio for Windows.
 * @date 1997
 */
#if defined(DOXYGEN) || defined(_MSC_VER)
#define TBC_COMPILER_ID_MSVC
#endif

/**
 * @short z88dk
 * @n <https://z88dk.org/>
 * @brief z88dk is the only C and assembler development kit that comes ready
 * out-of-the-box to create programs for over 100 z80-family machines.
 * (8080, 8085, gbz80, z80, z180, ez80_z80, KC160, Rabbit 2000, 3000, 4000, 5000)
 * @date 1998
 * @author Dominic Morris et al.
 * @copyright Artistic License
 */
#if defined(DOXYGEN) || defined(__Z88DK) || defined(Z80)
#define TBC_COMPILER_ID_Z88DK
#endif

/**
 * @short Not detected
 * @n
 * @brief ANSI C generic compiler.
 */
#if defined(DOXYGEN)
#define TBC_COMPILER_ID_UNKWNON
#endif

/**
 * @brief Compiler short name
 **/
#if defined(DOXYGEN)
#define TBC_COMPILER_NAME "DOXYGEN"
#elif defined(TBC_COMPILER_ID_TCC)
#define TBC_COMPILER_NAME "TCC"
#elif defined(TBC_COMPILER_ID_CC65)
#define TBC_COMPILER_NAME "CC65"
#elif defined(TBC_COMPILER_ID_GCC)
#define TBC_COMPILER_NAME "GCC"
#elif defined(TBC_COMPILER_ID_CLANG)
#define TBC_COMPILER_NAME "CLANG"
#elif defined(TBC_COMPILER_ID_MSVC)
#define TBC_COMPILER_NAME "MSVC"
#elif defined(TBC_COMPILER_ID_Z88DK)
#define TBC_COMPILER_NAME "Z88DK"
#else
#define TBC_COMPILER_ID_UNKWNON
#define TBC_COMPILER_NAME "UNKWNON"
#if defined(_MSC_VER) || defined(__Z88DK) 
#pragma message("[3BC] Compiler Unknown")
#elif defined(TBC_WARNING_ERR)
#error "[3BC] Compiler Unknown"
#elif !defined(TBC_WARNING_NOT)
#warning "[3BC] Compiler Unknown"
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
