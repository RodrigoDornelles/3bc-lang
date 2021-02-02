#if defined(ARDUINO)
#define _3BC_ARDUINO
#define format(buffer, string, ...) snprintf(buffer, sizeof(string), string, __VA_ARGS__);
#else
/**
 * @todo detect is separeted compiling for computer
 */
#define _3BC_REQUIRE_INSTRUCTIONS
#define _3BC_COMPUTER
#ifdef _WIN32
#define _3BC_PC_WINDOWS
#else 
#define _3BC_PC_NOT_WINDOWS
#endif
#endif