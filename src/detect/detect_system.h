/**
 * @file src/detect/detect_system.h
 * @brief recognize the software
 */
#ifndef H_DETECT_SYSTEM_TBC
#define H_DETECT_SYSTEM_TBC

#if defined(DOXYGEN) || defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(_WIN64)
#define TBC_SYSTEM_ID_WINDOWS
#endif

#if defined(DOXYGEN) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
#define TBC_SYSTEM_ID_LINUX
#endif

#if defined(DOXYGEN) || defined(__APPLE__)
#define TBC_SYSTEM_ID_DARWIN
#endif

#if defined(DOXYGEN) || defined(__unix__) || defined(BSD)
#define TBC_SYSTEM_ID_BSD
#endif

#if defined(DOXYGEN) || defined(__nuttx__)
/** @todo replace @c __nuttx__ by another compiler constant */
#define TBC_SYSTEM_ID_NUTTX
#endif

#if defined(DOXYGEN) || defined(EMSCRIPTEN)
#define TBC_SYSTEM_ID_EMSCRIPTEN
#endif

#if defined(DOXYGEN) || defined(ARDUINO)
#define TBC_SYSTEM_ID_ARDUINO
#endif

#if defined(DOXYGEN) || defined(__NES__)
#define TBC_SYSTEM_ID_NES
#endif

#if defined(DOXYGEN) || defined(__PCE__)
#define TBC_SYSTEM_ID_PCE
#endif

#if defined(DOXYGEN) || defined(__ATARI5200__)
#define TBC_SYSTEM_ID_ATARI
#endif

#if defined(DOXYGEN) || defined(__C64__)
#define TBC_SYSTEM_ID_C64
#endif

#if defined(DOXYGEN) || defined(__MSX__)
#define TBC_SYSTEM_ID_MSX
#endif

#if defined(DOXYGEN) || defined(__PET__)
#warning "[3BC] "
#define TBC_SYSTEM_ID_PET
#endif

#if defined(DOXYGEN)
#define TBC_SYSTEM_NAME "OPERATIONALSYSTEM"
#elif defined(TBC_SYSTEM_ID_WINDOWS)
#define TBC_SYSTEM_NAME "WINDOWS"
#elif defined(TBC_SYSTEM_ID_LINUX)
#define TBC_SYSTEM_NAME "LINUX"
#elif defined(TBC_SYSTEM_ID_DARWIN)
#define TBC_SYSTEM_NAME "DARWIN"
#elif defined(TBC_SYSTEM_ID_BSD)
#define TBC_SYSTEM_NAME "BSD"
#elif defined(TBC_SYSTEM_ID_NUTTX)
#define TBC_SYSTEM_NAME "NUTTX"
#elif defined(TBC_SYSTEM_ID_EMSCRIPTEN)
#define TBC_SYSTEM_NAME "EMSCRIPTEN"
#elif defined(TBC_SYSTEM_ID_ARDUINO)
#define TBC_SYSTEM_NAME "ARDUINO"
#elif defined(TBC_SYSTEM_ID_NES)
#define TBC_SYSTEM_NAME "NES"
#elif defined(TBC_SYSTEM_ID_PCE)
#define TBC_SYSTEM_NAME "PCE"
#elif defined(TBC_SYSTEM_ID_ATARI)
#define TBC_SYSTEM_NAME "ATARI"
#elif defined(TBC_SYSTEM_ID_C64)
#define TBC_SYSTEM_NAME "C64"
#elif defined(TBC_SYSTEM_ID_MSX)
#define TBC_SYSTEM_NAME "MSX"
#elif defined(TBC_SYSTEM_ID_PET)
#define TBC_SYSTEM_NAME "PET"
#else
#define TBC_SYSTEM_ID_UNKWNON
#define TBC_SYSTEM_NAME "UNKWNON"
#if defined(_MSC_VER) || defined(__Z88DK) 
#pragma message("[3BC] System Unknown")
#elif defined(TBC_WARNING_ERR)
#error "[3BC] System Unknown"
#elif !defined(TBC_WARNING_NOT)
#warning "[3BC] System Unknown"
#endif
#endif

#endif
