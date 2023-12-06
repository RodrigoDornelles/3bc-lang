/**
 * @file src/detect/detect_libc.h
 * @short detect C library
 * @brief recognize system abi library 
 */
#ifndef H_DETECT_LIBC_TBC
#define H_DETECT_LIBC_TBC

/**
 * @short Arduino SDK
 * @c <Arduino.h> 
 * @date 2005
 * @author Arduino Team
 * @copyright GNU Lesser General Public License
 */
#if defined(DOXYGEN) || defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_AVR)
#ifndef TBC_LIBC_ARDUINO
#define TBC_LIBC_ARDUINO
#endif
#endif

/**
 * @short MS-DOS Library
 * @c <conio.h> 
 * @date 1981
 * @author Microsoft
 */
#if defined(DOXYGEN) || defined(__CC65_STD__) || defined(__CC65_STD_CC65__) || defined(__MSX__)
#ifndef TBC_LIBC_CONIO
#define TBC_LIBC_CONIO
#endif
#endif

/**
 * @short Tiny C Compiler Library
 * @c <tcclib.h>
 * @date 2001
 * @author Fabrice Bellard
 * @copyright GNU Lesser General Public License
 */
#if defined(DOXYGEN) || defined(TBC_TCC_NOSTDINC)
#ifndef TBC_LIBC_TCC
#define TBC_LIBC_TCC
#endif
#endif

/**
 * @short Posix Standard Library
 * @c <unistd.h>
 * @c <fcntl.h>
 * @date 2001
 * @author Fabrice Bellard
 * @copyright GNU Lesser General Public License
 */
#if defined(DOXYGEN) || !defined(TBC_TCC_NOSTDINC)
#if defined(DOXYGEN) ||\
     defined(__linux) || defined(__linux__) || defined(__gnu_linux__) ||\
     defined(__APPLE__) || defined(__unix__) || defined(BSD)
#ifndef TBC_LIBC_POSIX
#define TBC_LIBC_POSIX
#endif
#endif
#endif

/**
 * @short Windows API Library
 * @c <Windows.h> 
 * @date 1985
 * @author Microsoft
 */
#if defined(DOXYGEN) || defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(_WIN64)
#ifndef TBC_LIBC_WINDOWS
#define TBC_LIBC_WINDOWS
#endif
#endif

#endif
