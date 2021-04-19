/**
 * MACROS ENVIRONMENT (PLATAFORM DETECT)
 */
#if defined(ARDUINO)
#define _3BC_ARDUINO
#ifndef format
#define format(buffer, string, ...) snprintf(buffer, sizeof(string), string, __VA_ARGS__);
#endif
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
#ifndef APP_3BC
#define APP_3BC                     (lang_bootstrap())
#endif

#ifndef AUX
#define AUX                         (tape_aux_get())
#endif

#ifndef LABEL_HASH_SIZE
#ifdef _3BC_ARDUINO
#define LABEL_HASH_SIZE             (8) 
#else
#define LABEL_HASH_SIZE             (128)
#endif
#endif

/**
 * FUNCTIONS MACROS
 */
#define lang_line(a,b,c)                tape_program_line_add(a,b,c)
#define PARSER_UNPACK(c)                (tolower(c[0])+tolower(c[1])+tolower(c[2])+tolower(c[3]))
#define PARSER_PACK(c1,c2,c3,c4,v,r,...)  case(c1+c2+c3+c4):*v=r;return(true)


/**
 * INSTRUCTIONS PACK MACROS
 */
#define CPU_PACK_ZEROMODE(mode);     case(mode):switch(reg){default:return(&cpu_not_mode);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);}
#define CPU_PACK_RESERVED(mode);     case(mode):switch(reg){default:return(&cpu_mode_reserved);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);}
#define CPU_PACK_PROTECTED(mode);    case(mode):switch(reg){default:return(&cpu_mode_protected);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);}
#define CPU_PACK1(mode,a);           case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);}
#define CPU_PACK2(mode,a,b);         case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);}
#define CPU_PACK3(mode,a,b,c);       case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);case(0b011):return(&c);}
#define CPU_PACK4(mode,a,b,c,d);     case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);case(0b011):return(&c);case(0b100):return(&d);}
#define CPU_PACK5(mode,a,b,c,d,e);   case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);case(0b011):return(&c);case(0b100):return(&d);case(0b101):return(&e);}
#define CPU_PACK6(mode,a,b,c,d,e,f); case(mode):switch(reg){default:return(&cpu_not_exist);case(0b000):return(&cpu_null);case(0b111):return(&cpu_mode);case(0b001):return(&a);case(0b010):return(&b);case(0b011):return(&c);case(0b100):return(&d);case(0b101):return(&e);case(0b110):return(&f);}