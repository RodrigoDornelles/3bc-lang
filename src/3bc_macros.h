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
 * CONSTS MACROS
 */
#define APP_3BC                     (lang_bootstrap())
#ifdef _3BC_ARDUINO
#define LABEL_HASH_SIZE             (8) 
#else
#define LABEL_HASH_SIZE             (128)
#endif

/**
 * FUNCTIONS MACROS
 */
#define lang_line(a,b,c)                tape_program_line_add(a,b,c)
#define PARSER_UNPACK(c)                (tolower(c[0])+tolower(c[1])+tolower(c[2])+tolower(c[3]))
#define PARSER_PACK(c1,c2,c3,c4,v,r,...)  case(c1+c2+c3+c4):*v=r;return(true)