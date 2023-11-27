/**
 * @file driver_interrupt.h
 * @brief recognize the software
 */
#ifndef H_DETECT_SYSTEM_TBC
#define H_DETECT_SYSTEM_TBC

#include "detect_warning.h"

/**
 * @brief Operational System/Plataform
 */
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(_WIN64)
#define TBC_SYSTEM_NAME "WINDOWS"
#define TBC_SYSTEM_ID_WINDOWS
#elif defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
#define TBC_SYSTEM_NAME "LINUX"
#define TBC_SYSTEM_ID_LINUX
#elif defined(__APPLE__)
#define TBC_SYSTEM_NAME "DARWIN"
#define TBC_SYSTEM_ID_DARWIN
#elif defined(__unix__) || defined(BSD)
#define TBC_SYSTEM_NAME "BSD"
#define TBC_SYSTEM_ID_BSD
#elif defined(__nuttx__)
/** @todo replace '__nuttx__' by another compiler constant */
#define TBC_SYSTEM_NAME "NUTTX"
#define TBC_SYSTEM_ID_NUTTX
#elif defined(EMSCRIPTEN)
#define TBC_SYSTEM_NAME "EMSCRIPTEN"
#define TBC_SYSTEM_ID_EMSCRIPTEN
#elif defined(ARDUINO)
#define TBC_SYSTEM_NAME "ARDUINO"
#define TBC_SYSTEM_ID_ARDUINO
#elif defined(__NES__)
#define TBC_SYSTEM_NAME "NES"
#define TBC_SYSTEM_ID_NES
#elif defined(__PCE__)
#define TBC_SYSTEM_NAME "PCE"
#define TBC_SYSTEM_ID_PCE
#elif defined(__ATARI5200__)
#define TBC_SYSTEM_NAME "ATARI"
#define TBC_SYSTEM_ID_ATARI
#elif defined(__C64__)
#define TBC_SYSTEM_NAME "C65"
#define TBC_SYSTEM_ID_C64
#elif defined(__MSX__)
#define TBC_SYSTEM_NAME "MSX"
#define TBC_SYSTEM_ID_MSX
#elif defined(__PET__)
#define TBC_SYSTEM_NAME "PET"
#define TBC_SYSTEM_ID_PET
#if defined(TBC_WARNING_ERR)
#error "[3BC] COMMODORE PET SEEMS NOT TO HAVE ENOUGH MEMORY."
#elif defined(TBC_WARNING_STD)
#warning "[3BC] COMMODORE PET SEEMS NOT TO HAVE ENOUGH MEMORY."
#elif defined(TBC_WARNING_MSVC)
#pragma message("[3BC] COMMODORE PET SEEMS NOT TO HAVE ENOUGH MEMORY.")
#endif
#else
#if defined(TBC_WARNING_ERR)
#error "[3BC] System Unknown"
#elif defined(TBC_WARNING_STD)
#warning "[3BC] System Unknown"
#elif defined(TBC_WARNING_MSVC)
#pragma message("[3BC] System Unknown")
#endif
#endif

#endif
