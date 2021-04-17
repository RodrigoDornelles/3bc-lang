/**
 * MACROS ENVIRONMENT (PLATAFORM DETECT)
 */
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

/**
 * GLOBAL MACROS
 */
#define APP_3BC                     (lang_bootstrap())
#define lang_line(a,b,c)            tape_program_line_add(a,b,c)
#ifdef _3BC_ARDUINO
#define LABEL_HASH_SIZE             (8) 
#else
#define LABEL_HASH_SIZE             (128)
#endif