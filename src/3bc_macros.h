#if defined(ARDUINO)
#define _3BC_ARDUINO
#else
#define _3BC_COMPUTER
#ifdef _WIN32
#define _3BC_PC_WINDOWS
#else 
#define _3BC_PC_NOT_WINDOWS
#endif
#endif