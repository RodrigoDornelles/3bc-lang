#ifndef H_DETECT_WARNING_TBC
#define H_DETECT_WARNING_TBC

/**
 * @brief Warning type
 * @li @b TBC_WARNING_STD ISO standard
 * @li @b TBC_WARNING_MSVC Microsoft standard
 * @li @b TBC_WARNING_NOT Compiler does not suport project warnings
 * @li @b TBC_WARNING_ERR Project warnings as errors
 */
#if defined(_MSC_VER) || defined(__Z88DK) || defined(Z80)
#define TBC_WARNING_MSVC
#elif !defined(TBC_WARNING_NOT) || !defined(TBC_WARNING_ERR)
#define TBC_WARNING_STD
#endif

#endif
