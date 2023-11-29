/**
 * @file driver_extra.h
 * @brief additional usability behaviors
 */
#ifndef H_DETECT_EXTRA_TBC
#define H_DETECT_EXTRA_TBC

#include "detect_warning.h"

/**
 * @brief freeze program after finished with infinite loop
 */
#if defined(__NES__)
#define TBC_EXTRA_FREEZE_LOOP
#endif

#endif

