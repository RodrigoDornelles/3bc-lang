/**
 * @file src/types/types_bool.h
 * @short define boolean type
 * @brief ISO C Standard:  7.16  Boolean type and values
 * @li <https://github.com/gcc-mirror/gcc/blob/master/gcc/ginclude/stdbool.h>
 * @li <https://github.com/cc65/cc65/blob/master/include/stdbool.h>
 * @li <https://clang.llvm.org/doxygen/stdbool_8h_source.html>
 */
#ifndef H_TYPES_BOOL_TBC
#define H_TYPES_BOOL_TBC

#if !defined(DOXYGEN) && defined(__cplusplus) && defined(__GNUC__) && !defined(__STRICT_ANSI__)
/* Supporting _Bool in C++ is a GCC extension. */
#define _Bool bool
#endif

#if (defined(__cplusplus) && defined(__STDC_VERSION__) && __STDC_VERSION__ > 201710L) \
    || defined(__bool_true_false_are_defined) \
    || defined(__STDBOOL_H) \
    || defined(DOXYGEN)
/* already defined. */
#else

#if !defined(__bool_true_false_are_defined)
#define __bool_true_false_are_defined 1
#endif

#if defined(__CC65_STD__) || defined(__CC65_STD_CC65__)
typedef unsigned char _Bool;
#endif

#if defined(__cplusplus) && __cplusplus < 201103L
#define bool bool
#define false false
#define true true
#else
#define bool _Bool
#define true ((unsigned char)1u)
#define false ((unsigned char)0u)
#endif

#endif
 
#endif
