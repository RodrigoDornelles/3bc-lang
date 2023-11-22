/**
 * @file detect_unsupported.c
 * @brief recognize not supported features.
 */
#ifndef H_DETECT_UNSUPPORTED_TBC
#define H_DETECT_UNSUPPORTED_TBC

#if defined(__NES__) || defined(__PCE__) || defined(__ATARI5200__)
#ifndef TBC_UNSUPPORTED_CLOCK
#define TBC_UNSUPPORTED_CLOCK
#endif
#endif

#if defined(__NES__) || defined(__PCE__) || defined(__ATARI5200__) || defined(TBC_TCC_NOSTDINC)
#ifndef TBC_UNSUPPORTED_FILES
#define TBC_UNSUPPORTED_FILES
#endif
#endif

#if defined(__Z88DK) 
#ifndef TBC_UNSUPPORTED_INTYPES
#define TBC_UNSUPPORTED_INTYPES
#endif
#endif

#if defined(ARDUINO_ARCH_AVR)
#ifndef TBC_UNSUPPORTED_LOG2
#define TBC_UNSUPPORTED_LOG2
#endif
#endif

#if defined(__Z88DK) 
#ifndef TBC_UNSUPPORTED_MALLOC
#define TBC_UNSUPPORTED_MALLOC
#endif
#endif

#if defined(__CC65_STD__) || defined(__CC65_STD_CC65__)
#ifndef TBC_UNSUPPORTED_MATH
#define TBC_UNSUPPORTED_MATH
#endif
#endif

/* some shortcuts */

#if defined(TBC_UNSUPPORTED_MATH)
#ifndef TBC_UNSUPPORTED_LOG
#define TBC_UNSUPPORTED_LOG
#endif
#endif

#if defined(TBC_UNSUPPORTED_LOG)
#ifndef TBC_UNSUPPORTED_LOG2
#define TBC_UNSUPPORTED_LOG2
#endif
#ifndef TBC_UNSUPPORTED_LOG10
#define TBC_UNSUPPORTED_LOG10
#endif
#endif

#endif
