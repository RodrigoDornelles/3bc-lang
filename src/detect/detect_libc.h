#ifndef H_DETECT_LIBC_TBC
#define H_DETECT_LIBC_TBC

#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_AVR)
#ifndef TBC_LIBC_ARDUINO
#define TBC_LIBC_ARDUINO
#endif
#endif

#if defined(__CC65_STD__) || defined(__CC65_STD_CC65__) || defined(__MSX__)
#ifndef TBC_LIBC_CONIO
#define TBC_LIBC_CONIO
#endif
#endif

#if !defined(TBC_TCC_NOSTDINC)
#if defined(__linux) || defined(__linux__) || defined(__gnu_linux__) ||\
     defined(__APPLE__) || defined(__unix__) || defined(BSD)
#ifndef TBC_LIBC_POSIX
#define TBC_LIBC_POSIX
#endif
#endif
#endif

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(_WIN64)
#ifndef TBC_LIBC_WINDOWS
#define TBC_LIBC_WINDOWS
#endif
#endif

#endif
